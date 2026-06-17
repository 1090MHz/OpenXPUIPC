// SPDX-License-Identifier: LGPL-3.0-or-later
// UDP server: receives FSUIPC-style action packets, queues them for processing
// on the X-Plane main thread via a flight loop callback.
#pragma once

#include "bridge.h"
#include <XPLMUtilities.h>
#include <XPLMProcessing.h>
#include <XPlaneUtilities/XPlaneLog.h>

#ifdef IBM
  #include <winsock2.h>
  #include <ws2tcpip.h>
  #pragma comment(lib, "ws2_32.lib")
  using socklen_t = int;
#else
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <unistd.h>
  #define INVALID_SOCKET (-1)
  #define SOCKET_ERROR   (-1)
  using SOCKET = int;
  inline int closesocket(int fd) { return ::close(fd); }
#endif

#include <cstdint>
#include <cstring>
#include <cstdio>
#include <atomic>
#include <thread>
#include <mutex>
#include <vector>

#include "protocol.h"

using namespace xpuipc;

// ---------- Pending request (received by UDP thread, processed on main thread) ----------
struct PendingRequest {
    sockaddr_in  from;
    socklen_t    fromlen;
    int          len;
    uint8_t      data[MAX_PACKET];
};

class UdpServer {
public:
    bool start(Bridge* bridge) {
        bridge_ = bridge;
#ifdef IBM
        WSADATA wsa;
        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            XPLANE_LOG_ERROR("UDP: WSAStartup failed");
            return false;
        }
#endif

        sock_ = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sock_ == INVALID_SOCKET) {
            XPLANE_LOG_ERROR("UDP: socket() failed");
            return false;
        }

        // Allow rebinding if a stale socket lingers from a previous session
        int reuse = 1;
        setsockopt(sock_, SOL_SOCKET, SO_REUSEADDR,
                   reinterpret_cast<const char*>(&reuse), sizeof(reuse));

        sockaddr_in addr{};
        addr.sin_family      = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port        = htons(UDP_PORT);

        if (bind(sock_, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == SOCKET_ERROR) {
            XPLANE_LOG_ERROR("UDP: bind() failed on port 5193");
            closesocket(sock_);
            sock_ = INVALID_SOCKET;
            return false;
        }

        running_ = true;
        thread_  = std::thread(&UdpServer::recv_loop, this);

        // Register a flight loop to process queued requests on the main thread
        XPLMCreateFlightLoop_t params{};
        params.structSize = sizeof(params);
        params.phase      = xplm_FlightLoop_Phase_AfterFlightModel;
        params.callbackFunc = flight_loop_cb;
        params.refcon       = this;
        flight_loop_ = XPLMCreateFlightLoop(&params);
        XPLMScheduleFlightLoop(flight_loop_, -1, 1);  // every frame

        XPLANE_LOG_INFO("UDP server listening on port 5193");
        return true;
    }

    void stop() {
        running_ = false;

        if (flight_loop_) {
            XPLMDestroyFlightLoop(flight_loop_);
            flight_loop_ = nullptr;
        }

        if (sock_ != INVALID_SOCKET) {
            closesocket(sock_);
            sock_ = INVALID_SOCKET;
        }
        if (thread_.joinable())
            thread_.join();
#ifdef IBM
        WSACleanup();
#endif
    }

private:
    // ---------- UDP receive thread (no SDK calls here) ----------
    void recv_loop() {
        while (running_) {
            PendingRequest req{};
            req.fromlen = sizeof(req.from);
            req.len = recvfrom(sock_, reinterpret_cast<char*>(req.data), MAX_PACKET, 0,
                               reinterpret_cast<sockaddr*>(&req.from), &req.fromlen);
            if (req.len <= 0) continue;

            {
                std::lock_guard<std::mutex> lock(queue_mutex_);
                queue_.push_back(std::move(req));
            }
        }
    }

    // ---------- Flight loop callback (main thread — safe to call SDK) ----------
    static float flight_loop_cb(float, float, int, void* refcon) {
        auto* self = static_cast<UdpServer*>(refcon);
        self->process_queue();
        return -1;  // every frame
    }

    void process_queue() {
        // Swap the queue under lock to minimize hold time
        std::vector<PendingRequest> work;
        {
            std::lock_guard<std::mutex> lock(queue_mutex_);
            work.swap(queue_);
        }

        for (auto& req : work) {
            process(req.data, req.len);

            // Send response back via the socket
            if (sock_ != INVALID_SOCKET) {
                sendto(sock_, reinterpret_cast<char*>(req.data), req.len, 0,
                       reinterpret_cast<sockaddr*>(&req.from), req.fromlen);
            }
        }
    }

    // ---------- Packet processing (runs on main thread) ----------
    void process(uint8_t* data, int size) {
        uint8_t* p   = data;
        uint8_t* end = data + size;

        while (p + 4 <= end) {
            uint32_t action = *reinterpret_cast<uint32_t*>(p);
            if (action == 0) break;

            switch (action) {
            case ACTION_READ:
            case ACTION_READTRUE: {
                if (p + sizeof(ReadHeader) > end) return;
                auto* hdr = reinterpret_cast<ReadHeader*>(p);
                p += sizeof(ReadHeader);
                if (p + hdr->size > end) return;
                bridge_->read(p, hdr->offset, hdr->size);
                p += hdr->size;
                break;
            }
            case ACTION_WRITE:
            case ACTION_WRITETRUE: {
                if (p + sizeof(WriteHeader) > end) return;
                auto* hdr = reinterpret_cast<WriteHeader*>(p);
                p += sizeof(WriteHeader);
                if (p + hdr->size > end) return;
                bridge_->write(p, hdr->offset, hdr->size);
                p += hdr->size;
                break;
            }
            default:
                *reinterpret_cast<uint32_t*>(p) = 0;
                return;
            }
        }
    }

    SOCKET              sock_ = INVALID_SOCKET;
    std::atomic<bool>   running_{false};
    std::thread         thread_;
    Bridge*             bridge_ = nullptr;

    // Queue: filled by recv thread, drained by flight loop
    std::mutex                  queue_mutex_;
    std::vector<PendingRequest> queue_;
    XPLMFlightLoopID            flight_loop_ = nullptr;
};
