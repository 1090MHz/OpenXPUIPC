// SPDX-License-Identifier: GPL-3.0-or-later
// Bridge engine: dispatches FSUIPC offset reads/writes via the offset table
//
// ARCHITECTURE NOTE:
// The IPC window procedure may be invoked from the X-Plane event-dispatch loop
// outside a valid XPLM callback context. Therefore, read() and write() MUST NOT
// call XPLM APIs or access DataRefs directly.
//
// All DataRef access is performed in update(), which runs from a flight-loop
// callback and therefore executes in a valid XPLM context.
#pragma once

#include <XPlaneUtilities/XPlaneLog.h>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <fsuipc_offsets/fsuipc_offset_table.h>
#include "cfg_offset_table.h"

class Bridge {
public:
    Bridge() {
        // Register all production-ready category offset tables
        register_fsuipc_offset_tables(*this);

        // Register custom cfg table last so custom entries can override production offsets.
        register_table(cfg_offset_table());

        // Pre-build a flat, cache-friendly list of readable entries for update().
        // Avoids per-call unordered_map bucket traversal overhead.
        read_list_.reserve(index_.size());
        for (const auto& [off, entry] : index_)
            if (entry->read && off + entry->size <= sizeof(buf_))
                read_list_.emplace_back(off, entry);
    }

    // Called from flight-loop callback (valid XPLM context).
    // Refreshes the shadow buffer from live DataRefs and processes
    // any pending write-handler calls.
    void update() {
        // 1. Process pending writes (apply to DataRefs)
        for (auto& pw : pending_writes_) {
            if (pw.entry && pw.entry->write)
                pw.entry->write(pw.data.data(),
                                static_cast<uint32_t>(pw.data.size()), dr_);
        }
        pending_writes_.clear();

        // 2. Refresh all read entries into buf_ via pre-built flat list
        for (const auto& [off, entry] : read_list_)
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
    }

    // Write `size` bytes from `src` into the shadow buffer.
    // If there's a write handler, queues it for the next flight-loop update().
    void write(const uint8_t* src, uint32_t offset, uint32_t size) {
        if (offset + size > sizeof(buf_)) return;
        // Always store in buffer immediately (so readback works)
        std::memcpy(buf_ + offset, src, size);

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
        auto* e = find(offset);
        return (e && e->desc) ? e->desc : "";
    }

    // Dump all known offset values within [offset, offset+size) at TRACE level.
    // Reads from the shadow buffer — no XPLM calls, safe from wndproc.
    void log_range(uint32_t offset, uint32_t size) const {
        for (const auto& [off, entry] : index_) {
            if (off >= offset && off + entry->size <= offset + size) {
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
    uint8_t buf_[0x10000]{};  // 64 KB shadow buffer, zero-initialized
    std::unordered_map<uint32_t, const OffsetEntry*> index_;
    std::vector<std::pair<uint32_t, const OffsetEntry*>> read_list_;  // flat copy of readable entries
    std::vector<PendingWrite> pending_writes_;
};
