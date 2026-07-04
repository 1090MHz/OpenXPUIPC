// SPDX-License-Identifier: GPL-3.0-or-later
// Lightweight simulator readiness state shared by plugin lifecycle and offsets.
#pragma once

#include <chrono>
#include <cstdint>

namespace sim_state
{
    // FSUIPC 0x3364 semantics: 0 = ready to fly, non-zero = loading/transition.
    static bool ready_to_fly = false;

    // FSUIPC 0x337E: heartbeat counter, incremented every flight loop tick.
    static uint16_t activity_counter = 0;

    // Real-world timestamp of the last watchdog update from the flight loop.
    // Used by Bridge::read() to detect when X-Plane has suspended simulation
    // (e.g. Flight Configuration or Settings window is open).
    static std::chrono::steady_clock::time_point flight_loop_watchdog_timestamp{};

    inline void set_ready_to_fly(bool v)   { ready_to_fly = v; }
    inline bool is_ready_to_fly()          { return ready_to_fly; }

    inline void increment_activity_counter() { ++activity_counter; }
    inline uint16_t get_activity_counter()   { return activity_counter; }

    // Called once per flight loop tick (from Bridge::update()) to refresh
    // the watchdog timestamp.
    inline void update_flight_loop_watchdog_timestamp()
    {
        flight_loop_watchdog_timestamp = std::chrono::steady_clock::now();
    }

    // Returns true if the flight loop watchdog is fresh (updated within
    // the last 150 ms). False → loop is stalled → X-Plane has suspended simulation
    // (Flight Configuration or Settings window open).
    inline bool is_flight_loop_watchdog_fresh()
    {
        using namespace std::chrono;
        return duration_cast<milliseconds>(steady_clock::now() - flight_loop_watchdog_timestamp).count() < 150;
    }

    // FSUIPC 0x3364: 0 = ready, non-zero = loading/transition.
    inline uint8_t fsuipc_ready_to_fly_flag()
    {
        return ready_to_fly ? uint8_t{0} : uint8_t{1};
    }
}
