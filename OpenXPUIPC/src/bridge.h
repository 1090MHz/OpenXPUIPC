// SPDX-License-Identifier: GPL-3.0-or-later
// Bridge engine: dispatches FSUIPC offset reads/writes via the offset table
//
// ARCHITECTURE NOTE:
// The IPC window procedure may be invoked from the X-Plane event-dispatch loop
// outside a valid XPLM callback context. Therefore, read() and write() MUST NOT
// call XPLM APIs or access DataRefs directly.
//
// All DataRef access is performed in update_high_rate_offsets() and
// update_low_rate_offsets(), which run from flight-loop callbacks and
// therefore execute in a valid XPLM context.
#pragma once

#include <XPlaneUtilities/XPlaneLog.h>
#include <XPLMDataAccess.h>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <fsuipc_offsets/fsuipc_offset_table.h>
#include "cfg_offset_table.h"
#include "impl/sim_state.h"
#include "weather_read.h"

// Forward declaration for FSUIPC text display message buffer
namespace xpuipc { extern char tts_message_buffer[128]; }

class Bridge {
public:
    Bridge() {
        // Register all production-ready category offset tables
        register_fsuipc_offset_tables(*this);

        // Register custom cfg table last so custom entries can override production offsets.
        register_table(cfg_offset_table());

        // Pre-build flat, cache-friendly lists of readable entries, split by
        // refresh rate. Avoids per-call unordered_map bucket traversal overhead
        // and lets high-rate and low-rate flight loops each refresh only their
        // own subset.
        read_list_high_.reserve(index_.size());
        read_list_low_.reserve(index_.size());
        for (const auto& [off, entry] : index_) {
            if (!entry->read || off + entry->size > sizeof(buf_)) continue;
            if (entry->rate == RefreshRate::Low)
                read_list_low_.emplace_back(off, entry);
            else
                read_list_high_.emplace_back(off, entry);
        }
    }

    // Called from the high-rate flight-loop callback (~18 Hz, valid XPLM
    // context). Refreshes fast-changing entries and processes any pending
    // write-handler calls.
    void update_high_rate_offsets() {
        // Refresh the flight-loop watchdog timestamp for suspended-simulation detection.
        sim_state::update_flight_loop_watchdog_timestamp();

        // 1. Process pending writes (apply to DataRefs)
        for (auto& pw : pending_writes_) {
            if (pw.entry && pw.entry->write)
                pw.entry->write(pw.data.data(),
                                static_cast<uint32_t>(pw.data.size()), dr_);
        }
        pending_writes_.clear();

        // 1b. Service any pending weather-read request (0xCC04 signature)
        weather_read_.process(buf_);

        // 2. Refresh high-rate entries into buf_ via pre-built flat list
        for (const auto& [off, entry] : read_list_high_)
            entry->read(buf_ + off, dr_);

        // 3. Increment activity counter (heartbeat for crash detection)
        sim_state::increment_activity_counter();
    }

    // Called from the low-rate flight-loop callback (slower cadence, valid
    // XPLM context). Refreshes entries tagged RefreshRate::Low, e.g. NavAid
    // searches, which are expensive to repeat every high-rate tick.
    void update_low_rate_offsets() {
        for (const auto& [off, entry] : read_list_low_)
            entry->read(buf_ + off, dr_);
    }

    // Read `size` bytes starting at `offset` into `dst`.
    // Just copies from the pre-populated shadow buffer — NO XPLM calls.
    void read(uint8_t* dst, uint32_t offset, uint32_t size) {
        if (offset + size > sizeof(buf_)) {
            std::memset(dst, 0, size);
            return;
        }
        std::memcpy(dst, buf_ + offset, size);

        // If the flight loop has stalled, X-Plane has opened the Flight
        // Configuration or Settings window and suspended simulation.
        // (The regular menu bar — File, Flight, View, Developer, Plugins —
        // runs in parallel and does not stop the loop.)
        // Override offset 0x3365 to 1 (sim suspended) regardless of the
        // stale shadow buffer value. Bridge::read() is called from the IPC
        // message pump, which keeps running even when the flight loop stops.
        if (!sim_state::is_flight_loop_watchdog_fresh()) {
            constexpr uint32_t MENU_FLAG_OFFSET = 0x3365;
            if (offset <= MENU_FLAG_OFFSET && MENU_FLAG_OFFSET < offset + size) {
                dst[MENU_FLAG_OFFSET - offset] = 1;
            }
        }
    }

    // Write `size` bytes from `src` into the shadow buffer.
    // If there's a write handler, queues it for the next flight-loop update().
    void write(const uint8_t* src, uint32_t offset, uint32_t size) {
        if (offset + size > sizeof(buf_)) return;
        // Always store in buffer immediately (so readback works)
        std::memcpy(buf_ + offset, src, size);

        // Special handling for offset 0x3380 (FSUIPC text display message buffer):
        // Update the shared message buffer immediately to avoid race conditions
        // when 0x32FA (trigger) is written before 0x3380 (message) due to
        // separate IPC messages arriving in quick succession.
        constexpr uint32_t TEXT_MSG_OFFSET = 0x3380;
        constexpr uint32_t TEXT_MSG_SIZE = 128;
        if (offset == TEXT_MSG_OFFSET) {
            size_t copy_len = (size < TEXT_MSG_SIZE) ? size : TEXT_MSG_SIZE - 1;
            std::memcpy(xpuipc::tts_message_buffer, src, copy_len);
            xpuipc::tts_message_buffer[copy_len] = '\0';  // Ensure null termination
        }

        weather_read_.note_write(offset, size, buf_);

        const OffsetEntry* entry = find(offset);
        if (entry && entry->write) {
            pending_writes_.push_back({entry, {src, src + size}});
        }
    }

    // Called by register_fsuipc_offset_tables() to bulk-load a category table.
    void register_table(const std::vector<OffsetEntry>& table) {
        for (const auto& e : table)
            index_[e.offset] = &e;
    }

    const OffsetEntry* find(uint32_t offset) const {
        auto it = index_.find(offset);
        return it != index_.end() ? it->second : nullptr;
    }

    const char* desc(uint32_t offset) const {
        if (const auto* entry = find(offset))
            return entry->desc ? entry->desc : "";

        // Manually maintained logging aliases for partial reads of implemented entries.
        // Add cases when logs reveal missing descriptions, after confirming the data
        // is already provided by a registered entry. These aliases add no handlers.
        switch (offset) {
        case 0x0574:
            // Upper 32 bits of the 8-byte altitude entry at 0x0570.
            return "Altitude (integer metres)";
        // Weather-read protocol, handled by WeatherReadService.
        case 0xB800: return "METAR string being read (FSX)";
        case 0xCC00: return "New weather read block";
        case 0xCC04: return "Signature for weather reading (FS2004)";
        case 0xCC08: return "ICAO for weather reading (FS2004)";
        case 0xCC10: return "Weather read Latitude";
        case 0xCC18: return "Weather read Longitude";
        case 0xCC24: return "Weather read timestamp";
        default:
            return "";
        }
    }

    // Dump all known offset values within [offset, offset+size) at TRACE level.
    // Reads from the shadow buffer — no XPLM calls, safe from wndproc.
    void log_range(uint32_t offset, uint32_t size) const {
        for (const auto& [off, entry] : index_) {
            const bool inside = off >= offset && off + entry->size <= offset + size;
            const bool overlaps = off < offset + size && off + entry->size > offset;
            if (overlaps && !inside) {
                // Partial overlap: show the requested bytes that fall within this entry.
                const uint32_t lo = off > offset ? off : offset;
                const uint32_t hi = (off + entry->size < offset + size) ? off + entry->size : offset + size;
                uint64_t v = 0;
                std::memcpy(&v, buf_ + lo, hi - lo > 8 ? 8 : hi - lo);
                XPLANE_LOG_TRACE("  [0x{:04X}..0x{:04X}] part of {} @0x{:04X} = 0x{:X}",
                    lo, hi - 1, entry->desc, off, v);
            } else if (inside) {
                if (entry->size == 8) {
                    int64_t iv; std::memcpy(&iv, buf_ + off, 8);
                    double  dv; std::memcpy(&dv, buf_ + off, 8);
                    XPLANE_LOG_TRACE("  [0x{:04X}] {} = {} (0x{:X}) f={:.6f}",
                        off, entry->desc, iv, static_cast<uint64_t>(iv), dv);
                } else {
                    int32_t v = 0;
                    uint32_t n = entry->size < 4u ? entry->size : 4u;
                    std::memcpy(&v, buf_ + off, n);
                    XPLANE_LOG_TRACE("  [0x{:04X}] {} = {} (0x{:X})", off, entry->desc, v, static_cast<uint32_t>(v));
                }
            }
        }
    }

private:
    struct PendingWrite {
        const OffsetEntry*       entry;
        std::vector<uint8_t>     data;
    };

    DataRefCache dr_;
    WeatherReadService weather_read_;
    uint8_t buf_[0x10000]{};  // 64 KB shadow buffer, zero-initialized
    std::unordered_map<uint32_t, const OffsetEntry*> index_;
    std::vector<std::pair<uint32_t, const OffsetEntry*>> read_list_high_; // readable entries refreshed at high rate
    std::vector<std::pair<uint32_t, const OffsetEntry*>> read_list_low_;  // readable entries refreshed at low rate
    std::vector<PendingWrite> pending_writes_;
};
