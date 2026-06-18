// SPDX-License-Identifier: GPL-3.0-or-later
// Unit conversions and encoding helpers for FSUIPC ↔ X-Plane bridging
#pragma once
#include <cmath>
#include <cstdint>

namespace conv {

inline float kg_to_lbs(float kg)           { return kg / 0.45359237f; }
inline float lbs_to_kg(float lbs)          { return lbs * 0.45359237f; }
inline float kg_to_gallons(float kg)       { return kg_to_lbs(kg) / 6.699219f; }
inline float lbs_to_gallons(float lbs)    { return lbs / 6.699219f; }
inline float meters_to_knots(float mps)    { return mps * 1.9438444924406f; }

inline float inch_to_hpa(float inch) {
    return 1013.0f + (inch - 29.92f) / 0.02952998f;
}
inline float hpa_to_inch(float hpa) {
    return 29.92f + (hpa - 1013.0f) * 0.02952998f;
}

inline float wrap_heading(float hdg) {
    hdg = std::fmod(hdg, 360.0f);
    return hdg < 0.0f ? hdg + 360.0f : hdg;
}

inline int16_t to_bcd(int value) {
    int d1 = (value / 1000) % 10;
    int d2 = (value / 100)  % 10;
    int d3 = (value / 10)   % 10;
    int d4 =  value          % 10;
    return static_cast<int16_t>((d1 << 12) | (d2 << 8) | (d3 << 4) | d4);
}

inline int from_bcd(int16_t bcd) {
    int d1 = (bcd >> 12) & 0xF;
    int d2 = (bcd >> 8)  & 0xF;
    int d3 = (bcd >> 4)  & 0xF;
    int d4 =  bcd         & 0xF;
    return d1 * 1000 + d2 * 100 + d3 * 10 + d4;
}
inline int from_bcd(uint16_t bcd) { return from_bcd(static_cast<int16_t>(bcd)); }

// Angle encoding used in FSUIPC for 32-bit fractional revolution
constexpr double FSUIPC_360_32 = 65536.0 * 65536.0;            // 2^32
constexpr double FSUIPC_ALT_SCALE = FSUIPC_360_32 * 65536.0;   // 2^48 (m → FSUIPC altitude)
constexpr double FSUIPC_LAT_SCALE = 10001750.0 * FSUIPC_360_32 / 90.0;
constexpr double FSUIPC_LON_SCALE = FSUIPC_360_32 * FSUIPC_360_32 / 360.0; // 2^64 / 360

} // namespace conv
