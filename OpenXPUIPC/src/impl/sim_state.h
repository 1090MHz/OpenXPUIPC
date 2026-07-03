// SPDX-License-Identifier: GPL-3.0-or-later
// Lightweight simulator readiness state shared by plugin lifecycle and offsets.
#pragma once

#include <cstdint>

namespace sim_state
{
    // FSUIPC 0x3364 semantics: 0 = ready to fly, non-zero = loading/transition.
    static bool ready_to_fly = false;

    // Flight time tracking for menu/pause detection
    static float last_flight_time = -1.0f;
    static bool time_is_advancing = false;

    inline void set_ready_to_fly(bool is_ready)
    {
        ready_to_fly = is_ready;
    }

    inline bool is_ready_to_fly()
    {
        return ready_to_fly;
    }

    // Call from bridge update loop with current sim/time/total_flight_time_sec.
    // Tracks whether simulation time is advancing (not paused/in menu).
    inline void update_flight_time(float current_time)
    {
        if (last_flight_time < 0.0f)
        {
            // First call - initialize
            last_flight_time = current_time;
            time_is_advancing = false;
        }
        else
        {
            // Check if time advanced since last update
            time_is_advancing = (current_time > last_flight_time);
            last_flight_time = current_time;
        }
    }

    inline bool is_time_advancing()
    {
        return time_is_advancing;
    }

    inline uint8_t fsuipc_ready_to_fly_flag()
    {
        return is_ready_to_fly() ? static_cast<uint8_t>(0) : static_cast<uint8_t>(1);
    }

    // FSUIPC 0x3365: non-zero when sim unavailable due to menus/dialogs.
    // Detects menu/pause by checking if sim time is advancing.
    inline uint8_t fsuipc_menu_dialog_flag()
    {
        // If not ready to fly, definitely in menu/loading.
        // If ready but time not advancing, in menu/paused.
        return (is_ready_to_fly() && is_time_advancing()) 
            ? static_cast<uint8_t>(0) 
            : static_cast<uint8_t>(1);
    }
}
