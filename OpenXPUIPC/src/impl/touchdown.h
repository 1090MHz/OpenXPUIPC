// SPDX-License-Identifier: GPL-3.0-or-later
// Touchdown vertical-speed capture helper.
//
// X-Plane has no built-in "VS at touchdown" value.  This helper samples the
// VVI on every call while the aircraft is airborne, always keeping the most
// recent airborne reading.  When the on-ground flag goes true the last
// airborne sample is returned — it was captured while the aircraft was still
// in the air so the VVI has not yet begun recovering toward zero.  The value
// persists through rollout and taxi, then clears when airborne again.
//
// Usage:
//   #include "impl/touchdown.h"
//   put<int32_t>(dst, touchdown_vs());
//
// Return value: FSUIPC-encoded int32 — VSI / 256 = m/s  (same scale as 0x02C8)
#pragma once

#include <XPLMDataAccess.h>
#include <cstdint>

inline int32_t touchdown_vs()
{
    static XPLMDataRef r_on_ground = XPLMFindDataRef("sim/flightmodel/failures/onground_any");
    static XPLMDataRef r_vvi       = XPLMFindDataRef("sim/cockpit2/gauges/indicators/vvi_fpm_pilot");

    static bool    on_ground_last_frame = false;
    static int32_t last_airborne_vs     = 0;  // last VVI reading taken while airborne
    static int32_t latched_vs           = 0;  // held value reported after touchdown

    const bool on_ground = r_on_ground ? (XPLMGetDatai(r_on_ground) != 0) : false;

    if (!on_ground)
    {
        // Airborne: continuously refresh the last-known airborne VS and
        // clear any previous touchdown latch so the next landing is fresh.
        const float vs_fpm = r_vvi ? XPLMGetDataf(r_vvi) : 0.0f;
        last_airborne_vs = static_cast<int32_t>(vs_fpm / 60.0f / 3.28084f * 256.0f);
        latched_vs       = 0;
    }
    else if (on_ground && !on_ground_last_frame)
    {
        // Leading edge: just touched down — latch the last airborne sample.
        latched_vs = last_airborne_vs;
    }
    // While on_ground && on_ground_last_frame: taxiing/parked — hold latched value.

    on_ground_last_frame = on_ground;
    return latched_vs;
}

// G-Force at touchdown capture.
//
// IMPORTANT: Unlike touchdown_vs() which captures the last AIRBORNE reading,
// this function captures the PEAK G-FORCE in the first few frames AFTER
// touchdown. The impact G-force spike occurs when gear hits the ground, not
// while still airborne (where G-force is typically ~1.0g in level flight).
//
// Usage:
//   #include "impl/touchdown.h"
//   put<int16_t>(dst, touchdown_gforce());
//
// Return value: FSUIPC-encoded int16 — raw * 625 = G-force (same scale as 0x11BA)
inline int16_t touchdown_gforce()
{
    static XPLMDataRef r_on_ground = XPLMFindDataRef("sim/flightmodel/failures/onground_any");
    static XPLMDataRef r_gforce    = XPLMFindDataRef("sim/cockpit2/gauges/indicators/Gload_normal_g");

    static bool    on_ground_last_frame    = false; // aircraft on ground during previous frame
    static int16_t peak_g                  = 0;     // peak G-force captured after touchdown
    static int     frames_since_touchdown  = 0;     // frame counter after touchdown

    const bool on_ground = r_on_ground ? (XPLMGetDatai(r_on_ground) != 0) : false;
    const float current_g = r_gforce ? XPLMGetDataf(r_gforce) : 1.0f;
    const int16_t current_g_encoded = static_cast<int16_t>(current_g * 625.0f);

    if (!on_ground)
    {
        // Airborne: reset for next landing
        peak_g = 0;
        frames_since_touchdown = 0;
    }
    else if (on_ground && !on_ground_last_frame)
    {
        // Leading edge: just touched down — start capturing peak G-force
        peak_g = current_g_encoded;
        frames_since_touchdown = 0;
    }
    else if (frames_since_touchdown < 30)  // ~0.5 seconds at 60fps
    {
        // First 30 frames after touchdown: track peak G-force during impact
        if (current_g_encoded > peak_g)
            peak_g = current_g_encoded;
        frames_since_touchdown++;
    }
    // After capture window: hold peak value until airborne again

    on_ground_last_frame = on_ground;
    return peak_g;
}
