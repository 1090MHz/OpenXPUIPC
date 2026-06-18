// SPDX-License-Identifier: LGPL-3.0-or-later
#pragma once

#include <XPLMDataAccess.h>
#include <cstdint>

namespace autopilot {
inline constexpr uint32_t kAutothrottleSpeedEngage = 0x00001u;
inline constexpr uint32_t kHeadingSelectEngage     = 0x00002u;
inline constexpr uint32_t kRollHoldEngage          = 0x00004u;
inline constexpr uint32_t kSpeedByPitchEngage      = 0x00008u;
inline constexpr uint32_t kVerticalSpeedEngage     = 0x00010u;
inline constexpr uint32_t kAltitudeHoldArm         = 0x00020u;
inline constexpr uint32_t kFlightLevelChangeEngage = 0x00040u;
inline constexpr uint32_t kPitchHoldEngage         = 0x00080u;
inline constexpr uint32_t kNavArmed                = 0x00100u;
inline constexpr uint32_t kNavEngaged              = 0x00200u;
inline constexpr uint32_t kGlideslopeArmed         = 0x00400u;
inline constexpr uint32_t kGlideslopeEngaged       = 0x00800u;
inline constexpr uint32_t kAltitudeHoldEngaged     = 0x04000u;
}

// Autopilot state helpers — read sim/cockpit/autopilot/autopilot_state
inline uint32_t autopilot_state_mask(uint32_t mask) {
    static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/autopilot/autopilot_state");
    return r ? (static_cast<uint32_t>(XPLMGetDatai(r)) & mask) : 0u;
}

inline uint32_t autopilot_state_bool(uint32_t mask) {
    return autopilot_state_mask(mask) ? 1u : 0u;
}

inline uint32_t legacy_altitude_lock_value() {
    const uint32_t state = autopilot_state_mask(
        autopilot::kAltitudeHoldArm | autopilot::kAltitudeHoldEngaged);
    if (state == 0u) return 0u;
    if (state == autopilot::kAltitudeHoldArm ||
        state == autopilot::kAltitudeHoldEngaged) return 1u;
    return state;
}
