// OpenXPUIPC — FSUIPC IPC shared memory server
//
// Creates a UIPCMAIN window inside X-Plane's process and handles
// FSUIPC IPC requests via SendMessage. The WndProc runs on X-Plane's
// main thread, so DataRef access is safe without queuing.
#pragma once

#ifdef _WIN32

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <windows.h>

#include "bridge.h"
#include "protocol.h"

#include <XPLMUtilities.h>
#include <XPLMProcessing.h>
#include <XPlaneUtilities/XPlaneLog.h>

#include <cstdint>
#include <cstring>
#include <cstdio>

using namespace xpuipc;

// Window class name used by FSUIPC clients to find the server.
#ifndef XPUIPC_IPC_WINDOW_CLASS
#define XPUIPC_IPC_WINDOW_CLASS "UIPCMAIN"
#endif

    class IpcServer
    {
    public:
        bool start(Bridge *bridge)
        {
            bridge_ = bridge;
            instance_ = this;

            fsuipc_msg_ = RegisterWindowMessageA("FsasmLib:IPC");
            if (fsuipc_msg_ == 0)
            {
                XPLANE_LOG_ERROR("IPC: RegisterWindowMessage failed");
                return false;
            }

            WNDCLASSA wc{};
            wc.lpfnWndProc = wndproc;
            wc.hInstance = GetModuleHandleA(nullptr);
            wc.lpszClassName = XPUIPC_IPC_WINDOW_CLASS;

            if (!RegisterClassA(&wc))
            {
                DWORD err = GetLastError();
                if (err != ERROR_CLASS_ALREADY_EXISTS)
                {
                    XPLANE_LOG_ERROR("IPC: RegisterClass failed (error {})", err);
                    return false;
                }
            }

            hwnd_ = CreateWindowExA(
                WS_EX_CLIENTEDGE,
                XPUIPC_IPC_WINDOW_CLASS, "XPUIPC",
                WS_POPUP,
                0, 0, 10, 10,
                nullptr, nullptr,
                GetModuleHandleA(nullptr), nullptr);

            if (!hwnd_)
            {
                XPLANE_LOG_ERROR("IPC: CreateWindowEx failed (error {})", GetLastError());
                return false;
            }

            // Flight loop to process window messages
            XPLMCreateFlightLoop_t params{};
            params.structSize = sizeof(params);
            params.phase = xplm_FlightLoop_Phase_AfterFlightModel;
            params.callbackFunc = pump_cb;
            params.refcon = this;
            loop_ = XPLMCreateFlightLoop(&params);
            XPLMScheduleFlightLoop(loop_, -1.0f, 1);

            XPLANE_LOG_INFO("IPC server active ({} window created)", XPUIPC_IPC_WINDOW_CLASS);
            return true;
        }

        void stop()
        {
            if (loop_)
            {
                XPLMDestroyFlightLoop(loop_);
                loop_ = nullptr;
            }
            if (hwnd_)
            {
                DestroyWindow(hwnd_);
                hwnd_ = nullptr;
            }
            UnregisterClassA(XPUIPC_IPC_WINDOW_CLASS, GetModuleHandleA(nullptr));
            instance_ = nullptr;
            XPLANE_LOG_INFO("IPC server stopped");
        }

        int request_count() const { return request_count_; }

    private:
        // ---------- IPC request processing ----------
        LRESULT handle_ipc(WPARAM wParam)
        {
            ATOM atom = static_cast<ATOM>(wParam);
            char mapping_name[MAX_PATH] = {};
            if (GlobalGetAtomNameA(atom, mapping_name, MAX_PATH) == 0)
                return 0;

            HANDLE hMap = OpenFileMappingA(FILE_MAP_WRITE, FALSE, mapping_name);
            if (!hMap)
                return 0;

            BYTE *view = static_cast<BYTE *>(
                MapViewOfFile(hMap, FILE_MAP_WRITE, 0, 0, 0));
            if (!view)
            {
                CloseHandle(hMap);
                return 0;
            }

            ++request_count_;
            XPLANE_LOG_DEBUG("IPC request #{} (mapping: {})", request_count_, mapping_name);

            guarded_process(view);

            UnmapViewOfFile(view);
            CloseHandle(hMap);
            return 1; // FS6IPC_MESSAGE_SUCCESS
        }

        // SEH wrapper — split into two functions because MSVC C2712 forbids
        // __try in any function that defines C++ objects (even temporaries from
        // spdlog calls).  The inner function is pure SEH with only POD locals.
        DWORD guarded_process_seh(BYTE *view) noexcept
        {
            DWORD code = 0;
            __try
            {
                process_buffer(view);
            }
            __except (code = GetExceptionCode(), EXCEPTION_EXECUTE_HANDLER)
            {
            }
            return code;
        }

        void guarded_process(BYTE *view)
        {
            DWORD exc = guarded_process_seh(view);
            if (exc)
            {
                XPLANE_LOG_ERROR("IPC CRASH in process_buffer! exception code 0x{:08X}, request #{}",
                                 exc, request_count_);
                spdlog::default_logger()->flush();
            }
        }

        void process_buffer(BYTE *view)
        {
            BYTE *p = view;
            BYTE *end = view + MAX_PACKET;

            for (int n = 0; n < 1000; ++n)
            {
                if (p + 4 > end)
                    break;

                uint32_t action = 0;
                std::memcpy(&action, p, sizeof(action));
                if (action == 0)
                    break;

                if (p + 12 > end)
                    break;

                uint32_t offset = 0;
                uint32_t size = 0;
                std::memcpy(&offset, p + 4, sizeof(offset));
                std::memcpy(&size, p + 8, sizeof(size));

                if (action == IPC_READ32 || action == IPC_READ64)
                {
                    // READ header: [action][offset][size][pDest]
                    // pDest is 4 bytes for READ32, 8 bytes for READ64.
                    const uint32_t header_size = (action == IPC_READ32) ? 16u : 20u;
                    BYTE *dst = p + header_size;
                    if (dst + size > end)
                        break;

                    XPLANE_LOG_DEBUG("IPC READ  offset=0x{:04X} size={} [{}]", offset, size, bridge_->desc(offset));
                    bridge_->read(dst, offset, size);
                    // At TRACE level, dump all known offset values in the read range
                    bridge_->log_range(offset, size);
                    p = dst + size;
                }
                else if (action == IPC_WRITE)
                {
                    // WRITE header: 12 bytes [action][offset][size]
                    BYTE *src = p + 12;
                    if (src + size > end)
                        break;

                    uint32_t sample_u32 = 0;
                    uint16_t sample_u16 = 0;
                    uint8_t sample_u8 = 0;
                    if (size >= 4)
                        std::memcpy(&sample_u32, src, sizeof(sample_u32));
                    else if (size >= 2)
                        std::memcpy(&sample_u16, src, sizeof(sample_u16));
                    else if (size >= 1)
                        std::memcpy(&sample_u8, src, sizeof(sample_u8));

                    XPLANE_LOG_DEBUG("IPC WRITE offset=0x{:04X} size={} val=0x{:08X} [{}]",
                                     offset, size, size >= 4 ? sample_u32 : size >= 2 ? sample_u16 : sample_u8,
                                     bridge_->desc(offset));
                    bridge_->write(src, offset, size);
                    p = src + size;
                }
                else
                {
                    XPLANE_LOG_WARN("IPC unknown action {} at offset 0x{:04X}", action, offset);
                    break; // unknown action
                }
            }
        }

        // ---------- Window procedure ----------
        static LRESULT CALLBACK wndproc(HWND hwnd, UINT msg,
                                        WPARAM wParam, LPARAM lParam)
        {
            if (instance_ && msg == instance_->fsuipc_msg_)
                return instance_->handle_ipc(wParam);
            return DefWindowProcA(hwnd, msg, wParam, lParam);
        }

        // Flight-loop callback: dispatch the UIPCMAIN window message queue each frame.
        static float pump_cb(float, float, int, void *ref)
        {
            auto *self = static_cast<IpcServer *>(ref);
            MSG msg;
            while (PeekMessageA(&msg, self->hwnd_, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessageA(&msg);
            }
            return -1.0f; // reschedule every frame
        }

        Bridge *bridge_ = nullptr;
        HWND hwnd_ = nullptr;
        UINT fsuipc_msg_ = 0;
        XPLMFlightLoopID loop_ = nullptr;
        int request_count_ = 0;

        static inline IpcServer *instance_ = nullptr;
    };

    #endif // _WIN32
