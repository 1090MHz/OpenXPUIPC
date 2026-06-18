// SPDX-License-Identifier: LGPL-3.0-or-later
// Core types and utilities shared by all FSUIPC offset tables.
//
// This header is included by every fsuipc_offsets/ category file.
// It intentionally contains NO implemented offset entries — only the
// types (OffsetEntry, ReaderFn, WriterFn) and helpers (put<>, take<>,
// write_cstr) needed to declare them.
#pragma once

#include "dataref_cache.h"
#include "impl/conversion.h"  // conv:: namespace (widely used across categories)
#include <XPLMDataAccess.h>
#include <XPLMPlanes.h>
#include <XPLMUtilities.h>
#include <cstdint>
#include <cstring>
#include <vector>

// Bring conv::from_bcd into scope for compatibility with existing code
using conv::from_bcd;

// Write a typed value into a byte buffer
template<typename T>
inline void put(uint8_t* dst, T val) { std::memcpy(dst, &val, sizeof(T)); }

// Read a typed value from a byte buffer
template<typename T>
inline T take(const uint8_t* src) { T v; std::memcpy(&v, src, sizeof(T)); return v; }

// Write a null-padded C string into a fixed-size byte buffer
inline void write_cstr(uint8_t* dst, uint32_t dst_size, const char* src) {
    if (!dst || dst_size == 0) return;
    std::memset(dst, 0, dst_size);
    if (src) std::strncpy(reinterpret_cast<char*>(dst), src, dst_size - 1);
}

// -------------------------------------------------------------------
// Offset entry definition
// -------------------------------------------------------------------
using ReaderFn = void(*)(uint8_t* dst, DataRefCache& dref);
using WriterFn = void(*)(const uint8_t* src, uint32_t size, DataRefCache& dref);

struct OffsetEntry {
    uint32_t offset;
    uint32_t size;
    ReaderFn read;
    WriterFn write;       // nullptr = read-only
    const char* desc;
};

// -------------------------------------------------------------------
// Override state (for throttle/pitch/roll disconnect)
// Used by Controls entries (0x0BB2, 0x0BB6) and override flags (0x310A).
// -------------------------------------------------------------------
struct OverrideState {
    bool throttle1 = false;
    bool throttle2 = false;
    bool pitch     = false;
    bool roll      = false;
};

inline OverrideState& overrides() {
    static OverrideState s;
    return s;
}
