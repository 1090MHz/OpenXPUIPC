// SPDX-License-Identifier: GPL-3.0-or-later
// NavAid lookup helpers used by radio/navigation offset entries.
#pragma once

#include "dataref_cache.h"
#include <XPLMNavigation.h>

// Nav type masks for find_nav_station()
constexpr int NAV_VOR_ILS_DME = 1036 + 16 + 32;
constexpr int NAV_NDB         = 2;
constexpr int NAV_ILS_LOC     = 8 + 16; // xplm_Nav_ILS + xplm_Nav_Localizer (no VOR)

// Result of a NavAid lookup
struct NavStation {
    char  id[6];
    char  name[256];
    float lat;
    float lon;
    bool  found;
};

// Find the nearest NavAid matching freq_ref and nav_type_mask near the aircraft.
inline NavStation find_nav_station(DataRefCache& dr, const char* freq_ref,
                                   int nav_type_mask) {
    NavStation s{};
    int   freq = dr.get_i(freq_ref);
    float lat  = static_cast<float>(dr.get_d("sim/flightmodel/position/latitude"));
    float lon  = static_cast<float>(dr.get_d("sim/flightmodel/position/longitude"));

    XPLMNavRef ref = XPLMFindNavAid(nullptr, nullptr, &lat, &lon, &freq, nav_type_mask);
    if (ref != XPLM_NAV_NOT_FOUND) {
        XPLMGetNavAidInfo(ref, nullptr, &s.lat, &s.lon, nullptr,
                          &freq, nullptr, s.id, s.name, nullptr);
        s.found = true;
    }
    return s;
}
