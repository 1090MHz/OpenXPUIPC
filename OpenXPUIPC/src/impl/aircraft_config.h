// SPDX-License-Identifier: GPL-3.0-or-later
// Aircraft configuration data loader.
//
// X-Plane stores aircraft-specific configuration in ACF files (e.g., payload 
// station names as "P acf/_fixed_name/0-8" and fuel tank names as 
// "P acf/_tank_name/0-8"). These properties are NOT exposed as DataRefs, so we 
// must parse the .acf file directly. This helper reads and caches those values 
// when XPLM_MSG_PLANE_LOADED is received and provides them to FSUIPC offset handlers.
//
// Usage:
//   In plugin.cpp XPluginReceiveMessage():
//     if (inMsg == 102 && inParam == 0) // XPLM_MSG_PLANE_LOADED, user aircraft
//       aircraft_config::reload();
//
//   In offset handlers:
//     const char* name = aircraft_config::get_station_name(0); // Station 0-8
//     const char* tank = aircraft_config::get_tank_name(0);    // Tank 0-8
//     uint16_t flags = aircraft_config::classify_tank_name(tank); // Keyword detection

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
    // Maximum payload stations and fuel tanks in X-Plane
    constexpr int MAX_STATIONS = 9;
    constexpr int MAX_TANKS = 9;
    constexpr int STATION_NAME_LENGTH = 16; // FSUIPC spec: 16 chars null-padded
    constexpr int TANK_NAME_LENGTH = 32;    // Allow longer names for fuel tanks

    // Cached payload station names
    static std::array<char[STATION_NAME_LENGTH], MAX_STATIONS> station_names{};
    
    // Cached fuel tank names
    static std::array<char[TANK_NAME_LENGTH], MAX_TANKS> tank_names{};
    
    static bool loaded = false;

    // Forward declaration for fuel tank mapper
    namespace detail {
        void rebuild_fuel_tank_map();
    }

    // Reload aircraft configuration by parsing the .acf file.
    // Call this when XPLM_MSG_PLANE_LOADED is received for user aircraft.
    inline void reload()
    {
        // Clear existing names
        for (auto& name : station_names)
        {
            std::memset(name, 0, STATION_NAME_LENGTH);
        }
        for (auto& name : tank_names)
        {
            std::memset(name, 0, TANK_NAME_LENGTH);
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

        // Parse the ACF file for payload station names and fuel tank names
        // Format: "P acf/_fixed_name/0 StationName" and "P acf/_tank_name/0 TankName"
        std::regex station_pattern(R"(P acf/_fixed_name/(\d)\s+(.+))");
        std::regex tank_pattern(R"(P acf/_tank_name/(\d)\s+(.+))");
        std::smatch match;
        
        std::string line;
        while (std::getline(file, line))
        {
            if (std::regex_search(line, match, station_pattern))
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
            else if (std::regex_search(line, match, tank_pattern))
            {
                // Extract index (0-8) and tank name
                int index = match[1].str()[0] - '0';
                if (index < 0 || index >= MAX_TANKS)
                    continue;
                
                std::string name = match[2].str();
                
                // Copy and null-pad to TANK_NAME_LENGTH
                size_t copy_len = (name.length() < TANK_NAME_LENGTH - 1) 
                                   ? name.length() 
                                   : TANK_NAME_LENGTH - 1;
                std::memcpy(tank_names[index], name.c_str(), copy_len);
                tank_names[index][copy_len] = '\0';
            }
        }

        file.close();
        loaded = true;
        
        // Rebuild fuel tank mapper now that tank names are loaded
        detail::rebuild_fuel_tank_map();
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

    // Get the name of a fuel tank (0-8).
    // Returns a 32-byte buffer (null-padded).
    inline const char* get_tank_name(int index)
    {
        if (!loaded)
        {
            reload();
        }

        if (index >= 0 && index < MAX_TANKS)
        {
            return tank_names[index];
        }
        
        // Return empty string for invalid index
        static const char empty[TANK_NAME_LENGTH] = {0};
        return empty;
    }

    // Classify a tank name by keywords (case-insensitive).
    // Returns bitmask: bit 0=left, 1=right, 2=center, 3=aux, 4=tip, 5=main, 
    //                  6=external, 7=trim, 8=header
    // Returns 0 if name is empty or unclassifiable.
    inline uint16_t classify_tank_name(const char* name)
    {
        if (!name || name[0] == '\0')
            return 0;

        // Convert to lowercase for comparison
        char lower[TANK_NAME_LENGTH];
        size_t i = 0;
        while (name[i] && i < TANK_NAME_LENGTH - 1)
        {
            lower[i] = (name[i] >= 'A' && name[i] <= 'Z') ? (name[i] + 32) : name[i];
            ++i;
        }
        lower[i] = '\0';

        uint16_t flags = 0;
        if (strstr(lower, "left") || strstr(lower, "l ") || strstr(lower, "lh"))   flags |= (1 << 0); // left
        if (strstr(lower, "right") || strstr(lower, "r ") || strstr(lower, "rh"))  flags |= (1 << 1); // right
        if (strstr(lower, "center") || strstr(lower, "centre") || strstr(lower, "ctr")) flags |= (1 << 2); // center
        if (strstr(lower, "aux"))                                                    flags |= (1 << 3); // aux
        if (strstr(lower, "tip"))                                                    flags |= (1 << 4); // tip
        if (strstr(lower, "main") || strstr(lower, "inboard") || strstr(lower, "inner")) flags |= (1 << 5); // main
        if (strstr(lower, "extern") || strstr(lower, "drop"))                       flags |= (1 << 6); // external
        if (strstr(lower, "trim"))                                                   flags |= (1 << 7); // trim
        if (strstr(lower, "header"))                                                 flags |= (1 << 8); // header

        return flags;
    }

    // Clear the cache (useful for cleanup or testing)
    inline void clear()
    {
        for (auto& name : station_names)
        {
            std::memset(name, 0, STATION_NAME_LENGTH);
        }
        for (auto& name : tank_names)
        {
            std::memset(name, 0, TANK_NAME_LENGTH);
        }
        loaded = false;
    }

} // namespace aircraft_config
