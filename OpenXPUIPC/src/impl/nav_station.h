// SPDX-License-Identifier: GPL-3.0-or-later
// NavAid lookup helpers used by radio/navigation offset entries.
#pragma once

#include "dataref_cache.h"
#include <XPLMNavigation.h>
#include <cmath>
#include <string>
#include <unordered_map>

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

namespace detail {

// Below this movement, the nearest station can't plausibly have changed,
// so a cached search result is reused instead of re-searching.
constexpr float NAV_SEARCH_SKIP_NM = 0.5f;
constexpr float NM_PER_DEG_LAT = 60.0f; // 1 degree latitude == 60 nm, by definition of the nautical mile

// Flat-earth distance (nm) between two lat/lon points — accurate enough for
// a coarse "did we move far enough to matter" gate at these sub-degree
// separations, and far cheaper than a great-circle (Haversine/Vincenty)
// formula since it only needs one cosine, no atan2.
inline float approx_distance_nm(float lat1, float lon1, float lat2, float lon2) {
    const float mean_lat_rad = (lat1 + lat2) * 0.5f * (3.14159265f / 180.0f);
    const float dlat_nm = (lat2 - lat1) * NM_PER_DEG_LAT;
    const float dlon_nm = (lon2 - lon1) * NM_PER_DEG_LAT * std::cos(mean_lat_rad);
    return std::sqrt(dlat_nm * dlat_nm + dlon_nm * dlon_nm);
}

struct NavStationCacheEntry {
    bool       valid = false;
    int        freq  = 0;
    float      lat   = 0.0f;
    float      lon   = 0.0f;
    NavStation result{};
};

// Keyed by (freq_ref, nav_type_mask) so distinct offsets querying the same
// receiver/mask (e.g. station ID and name) share one cached search.
inline std::unordered_map<std::string, NavStationCacheEntry>& nav_station_cache() {
    static std::unordered_map<std::string, NavStationCacheEntry> cache;
    return cache;
}

} // namespace detail

// Find the nearest NavAid matching freq_ref and nav_type_mask near the aircraft.
// Re-searches only when the tuned frequency changes or the aircraft has moved
// more than detail::NAV_SEARCH_SKIP_NM since the last search for this
// receiver/mask; otherwise returns the cached result.
inline NavStation find_nav_station(DataRefCache& dr, const char* freq_ref,
                                   int nav_type_mask) {
    const int   tuned_freq = dr.get_i(freq_ref);
    const float lat = static_cast<float>(dr.get_d("sim/flightmodel/position/latitude"));
    const float lon = static_cast<float>(dr.get_d("sim/flightmodel/position/longitude"));

    auto& entry = detail::nav_station_cache()[std::string(freq_ref) + "|" + std::to_string(nav_type_mask)];
    if (entry.valid && entry.freq == tuned_freq &&
        detail::approx_distance_nm(entry.lat, entry.lon, lat, lon) < detail::NAV_SEARCH_SKIP_NM) {
        return entry.result;
    }

    NavStation s{};
    int freq = tuned_freq;
    float search_lat = lat;
    float search_lon = lon;
    XPLMNavRef ref = XPLMFindNavAid(nullptr, nullptr, &search_lat, &search_lon, &freq, nav_type_mask);
    if (ref != XPLM_NAV_NOT_FOUND) {
        XPLMGetNavAidInfo(ref, nullptr, &s.lat, &s.lon, nullptr,
                          &freq, nullptr, s.id, s.name, nullptr);
        s.found = true;
    }

    entry = {true, tuned_freq, lat, lon, s};
    return s;
}
