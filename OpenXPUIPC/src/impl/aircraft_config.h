// SPDX-License-Identifier: GPL-3.0-or-later
// Aircraft configuration data loader.
//
// X-Plane stores aircraft-specific configuration in ACF files (e.g., payload 
// station names as "P acf/_fixed_name/0-8"). These properties are NOT exposed 
// as DataRefs, so we must parse the .acf file directly. This helper reads and
// caches those values when XPLM_MSG_PLANE_LOADED is received and provides them
// to FSUIPC offset handlers.
//
// Usage:
//   In plugin.cpp XPluginReceiveMessage():
//     if (inMsg == 102 && inParam == 0) // XPLM_MSG_PLANE_LOADED, user aircraft
//       aircraft_config::reload();
//
//   In offset handlers:
//     const char* name = aircraft_config::get_station_name(0); // Station 0-8

#pragma once

#include <XPLMPlanes.h>
#include <cstring>
#include <cstdio>
#include <array>
#include <fstream>
#include <string>
#include <regex>

namespace aircraft_config
{
    // Maximum payload stations in X-Plane
    constexpr int MAX_STATIONS = 9;
    constexpr int STATION_NAME_LENGTH = 16; // FSUIPC spec: 16 chars null-padded

    // Cached payload station names
    static std::array<char[STATION_NAME_LENGTH], MAX_STATIONS> station_names{};
    static bool loaded = false;

    // Reload aircraft configuration by parsing the .acf file.
    // Call this when XPLM_MSG_PLANE_LOADED is received for user aircraft.
    inline void reload()
    {
        // Clear existing names
        for (auto& name : station_names)
        {
            std::memset(name, 0, STATION_NAME_LENGTH);
        }

        // Get the path to the current aircraft's .acf file
        char acfFile[256] = {};
        char acfPath[512] = {};
        XPLMGetNthAircraftModel(0, acfFile, acfPath);
        
        // In X-Plane 12, acfPath contains the full path to the .acf file
        std::ifstream file(acfPath);
        if (!file.is_open())
        {
            loaded = true;
            return; // File not found or cannot open
        }

        // Parse the ACF file for payload station names
        // Format: "P acf/_fixed_name/0 StationName"
        std::regex pattern(R"(P acf/_fixed_name/(\d)\s+(.+))");
        std::smatch match;
        
        std::string line;
        while (std::getline(file, line))
        {
            if (std::regex_search(line, match, pattern))
            {
                // Extract index (0-8) and station name
                int index = match[1].str()[0] - '0';
                if (index < 0 || index >= MAX_STATIONS)
                    continue;
                
                std::string name = match[2].str();
                
                // Copy and null-pad to STATION_NAME_LENGTH
                size_t copy_len = (name.length() < STATION_NAME_LENGTH - 1) 
                                   ? name.length() 
                                   : STATION_NAME_LENGTH - 1;
                std::memcpy(station_names[index], name.c_str(), copy_len);
                station_names[index][copy_len] = '\0';
            }
        }

        file.close();
        loaded = true;
    }

    // Get the name of a payload station (0-8).
    // Returns a 16-byte buffer (null-padded, may not be null-terminated if full).
    inline const char* get_station_name(int index)
    {
        if (!loaded)
        {
            // Auto-load on first access if not explicitly reloaded
            reload();
        }

        if (index >= 0 && index < MAX_STATIONS)
        {
            return station_names[index];
        }
        
        // Return empty string for invalid index
        static const char empty[STATION_NAME_LENGTH] = {0};
        return empty;
    }

    // Get the number of active payload stations.
    // Returns the count of non-empty station names.
    inline int get_station_count()
    {
        if (!loaded)
        {
            reload();
        }

        int count = 0;
        for (const auto& name : station_names)
        {
            // Check if first character is non-null (station has a name)
            if (name[0] != '\0')
            {
                ++count;
            }
        }
        return count;
    }

    // Clear the cache (useful for cleanup or testing)
    inline void clear()
    {
        for (auto& name : station_names)
        {
            std::memset(name, 0, STATION_NAME_LENGTH);
        }
        loaded = false;
    }

} // namespace aircraft_config
