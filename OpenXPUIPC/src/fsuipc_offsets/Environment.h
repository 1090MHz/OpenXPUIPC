// SPDX-License-Identifier: LGPL-3.0-or-later
// fsuipc_offsets/Environment.h — Production offset table
//
// 34 total offsets in this category
// (TODO entries are commented out with implementation instructions)
//
// TO IMPLEMENT A NEW OFFSET:
//   1. Find the commented-out entry below
//   2. Uncomment it
//   3. Replace TODO dataref with real X-Plane DataRef logic
//   4. Test and verify
//
#pragma once

#include "offset_types.h" // OffsetEntry, put<>, take<>, DataRefCache, conv::

inline const std::vector<OffsetEntry> &fsuipc_offset_table_environment()
{
  static const std::vector<OffsetEntry> table = {

      {0x0238, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h2 = XPLMFindDataRef("sim/cockpit2/clock_timer/local_time_hours");
         put<int8_t>(dst, static_cast<int8_t>((r_h2 ? XPLMGetDatai(r_h2) : 0)));
       },
       nullptr,
       "Local hours"},

      // Clock Min — 0-59
      {0x0239, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h3 = XPLMFindDataRef("sim/cockpit2/clock_timer/local_time_minutes");
         put<int8_t>(dst, static_cast<int8_t>((r_h3 ? XPLMGetDatai(r_h3) : 0)));
       },
       nullptr,
       "Local minutes"},

      // Clock Sec — 0-59
      {0x023A, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h4 = XPLMFindDataRef("sim/cockpit2/clock_timer/local_time_seconds");
         put<int8_t>(dst, static_cast<int8_t>((r_h4 ? XPLMGetDatai(r_h4) : 0)));
       },
       nullptr,
       "Local seconds"},

      // Zulu Hour — 0-23. Also known as UTC or GMT
      {0x023B, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h5 = XPLMFindDataRef("sim/cockpit2/clock_timer/zulu_time_hours");
         put<int8_t>(dst, static_cast<int8_t>((r_h5 ? XPLMGetDatai(r_h5) : 0)));
       },
       nullptr,
       "Zulu hours"},

      // Zulu Min — 0-59
      {0x023C, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h6 = XPLMFindDataRef("sim/cockpit2/clock_timer/zulu_time_minutes");
         put<int8_t>(dst, static_cast<int8_t>((r_h6 ? XPLMGetDatai(r_h6) : 0)));
       },
       nullptr,
       "Zulu minutes"},
//
//       // Zulu day of month (FSX only) — Counts from 1, not 0
//       {0x023D, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x023D");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Zulu day of month (FSX only)"},

      // Day of Year — Counts from 1, not 0
      {0x023E, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h7 = XPLMFindDataRef("sim/time/local_date_days");
         put<int16_t>(dst, static_cast<int16_t>((r_h7 ? XPLMGetDatai(r_h7) : 0)));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h8 = XPLMFindDataRef("sim/time/local_date_days");
         if (r_h8)
           XPLMSetDatai(r_h8, take<int16_t>(src));
       },
       "Day of year"},

      // Zulu Year
      {0x0240, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &)
       {
         std::time_t t = std::time(nullptr);
         std::tm tm = {};
         gmtime_s(&tm, &t);
         put<uint16_t>(dst, static_cast<uint16_t>(tm.tm_year + 1900));
       },
       nullptr,
       "Zulu year"},

      // Zulu month of year (FSX only)
      {0x0242, 1,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &)
       {
         std::time_t t = std::time(nullptr);
         std::tm tm = {};
         gmtime_s(&tm, &t);
         put<uint8_t>(dst, static_cast<uint8_t>(tm.tm_mon + 1));
       },
       nullptr,
       "Zulu month of year"},
//
//       // Zulu day of week (FSX only)
//       {0x0243, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0243");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Zulu day of week (FSX only)"},

      // Local month of year (FSX only)
      {0x0244, 1,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &)
       {
         std::time_t t = std::time(nullptr);
         std::tm tm = {};
         localtime_s(&tm, &t);
         put<uint8_t>(dst, static_cast<uint8_t>(tm.tm_mon + 1));
       },
       nullptr,
       "Local month of year"},
//
//       // Local day of month (FSX only)
//       {0x0245, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0245");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Local day of month (FSX only)"},

      // Time Zone offset to Zulu (minutes) — Determines local time from Zulu
      // and aircraft position (+ve=behind Zulu, -ve=ahead)
      {0x0246, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &)
       {
         // Derive from X-Plane's own datarefs so the value tracks sim time, not
         // the real-world wall clock (they differ when the user sets a custom time).
         static XPLMDataRef r_lh = XPLMFindDataRef("sim/cockpit2/clock_timer/local_time_hours");
         static XPLMDataRef r_lm = XPLMFindDataRef("sim/cockpit2/clock_timer/local_time_minutes");
         static XPLMDataRef r_zh = XPLMFindDataRef("sim/cockpit2/clock_timer/zulu_time_hours");
         static XPLMDataRef r_zm = XPLMFindDataRef("sim/cockpit2/clock_timer/zulu_time_minutes");
         int lh = r_lh ? XPLMGetDatai(r_lh) : 0;
         int lm = r_lm ? XPLMGetDatai(r_lm) : 0;
         int zh = r_zh ? XPLMGetDatai(r_zh) : 0;
         int zm = r_zm ? XPLMGetDatai(r_zm) : 0;
         int diff = (zh * 60 + zm) - (lh * 60 + lm); // +ve = behind Zulu (FSUIPC convention)
         if (diff > 720)
           diff -= 1440;
         if (diff < -720)
           diff += 1440;
         put<int16_t>(dst, static_cast<int16_t>(diff));
       },
       nullptr,
       "Time zone offset (minutes)"},
//
//       // Season — 0=winter, 1=spring, 2=summer, 3=fall
//       {0x0248, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0248");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0248");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Season"},

      // Local Year
      {0x024A, 2,

       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &)
       {
         std::time_t t = std::time(nullptr);
         std::tm tm = {};
         localtime_s(&tm, &t);
         put<uint16_t>(dst, static_cast<uint16_t>(tm.tm_year + 1900));
       },
       nullptr,
       "Local year"},
//
//       // Nearest Airport ICAO id — 3 or 4 ASCII characters set in one 32 bit
//       // DWORD.
//       {0x0658, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0658");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Nearest Airport ICAO id"},
//
//       // Nearest Airport Latitude — The nearest 6 airports are listed in
//       // order
//       {0x065C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x065C");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "Nearest Airport Latitude"},
//
//       // Nearest Airport Longitude — The nearest 6 airports are listed in
//       // order
//       {0x0660, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0660");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "Nearest Airport Longitude"},
//
//       // Nearest Airport Altitude (feet) — The nearest 6 airports are listed
//       // in order
//       {0x0664, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0664");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "Nearest Airport Altitude (feet)"},
//
//       // Nearest Airport distance (nm) — The nearest 6 airports are listed in
//       // order
//       {0x0668, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0668");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "Nearest Airport distance (nm)"},
//
//       // Unlimited Visibility value — 1600 x range in statute miles. It is
//       // set by the slider in Display Quality.
//       {0x0BF8, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0BF8");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0BF8");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int32_t>(src)));
//        },
//        "Unlimited Visibility value"},
//
//       // NAV1 mag var — *360/65536 for degrees
//       {0x0C40, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C40");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "NAV1 mag var"},
//
//       // NAV2 mag var — *360/65536 for degrees
//       {0x0C42, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C42");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "NAV2 mag var"},
//
//       // Tower Latitude
//       {0x0D50, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0D50");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0D50");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Tower Latitude"},
//
//       // Tower Longitude
//       {0x0D58, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0D58");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0D58");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Tower Longitude"},
//
//       // Tower Elevation
//       {0x0D60, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0D60");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0D60");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Tower Elevation"},
//
//       // ICAO id of nearest Wx station
//       {0x0E80, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E80");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 4);
//          dst[0] = 0;
//        },
//        nullptr,
//        "ICAO id of nearest Wx station"},
//
//       // Time of Day Indicator — 1=Day, 2=Dusk/Dawn, 4=Night
//       {0x115E, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x115E");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Time of Day Indicator"},
//
//       // Ground scenery shadows — 0=off, 1=on
//       {0x11A2, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x11A2");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x11A2");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Ground scenery shadows"},
//
//       // Aircraft reflections — 1=off, 2=on
//       {0x11B6, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x11B6");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x11B6");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Aircraft reflections"},
//
//       // Dynamic pressure [FS2000+] — FS2k/CFS2/FS2002 only. Pressure in
//       // lbs/sq ft
//       {0x30D8, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x30D8");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Dynamic pressure [FS2000+]"},
//
//       // Surface type (FS2002)
//       {0x31E8, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31E8");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Surface type (FS2002)"},
//
//       // Surface condition (FS2002)
//       {0x31EC, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31EC");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Surface condition (FS2002)"},
//
//       // Slot offset of nearest ground AI traffic
//       {0xE07E, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE07E");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Slot offset of nearest ground AI traffic"},

  }; // end table
  return table;
}
