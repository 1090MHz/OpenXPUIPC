// SPDX-License-Identifier: LGPL-3.0-or-later
// fsuipc_offsets/Unknown.h — Production offset table
//
// 40 total offsets in this category
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

inline const std::vector<OffsetEntry> &fsuipc_offset_table_unknown()
{
  static const std::vector<OffsetEntry> table = {

      {0x0318, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/pressure/cabin_altitude_actual_ft");
         put<int32_t>(dst, r ? static_cast<int32_t>(XPLMGetDataf(r)) : 0);
       },
       nullptr,
       "Cabin altitude actual (ft MSL)"},

      // Pressurisation: cabin altitude target — In feet
      {0x031C, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/pressure/cabin_altitude_set_ft");
         put<int32_t>(dst, r ? static_cast<int32_t>(XPLMGetDataf(r)) : 0);
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/pressure/cabin_altitude_set_ft");
         if (r)
           XPLMSetDataf(r, static_cast<float>(take<int32_t>(src)));
       },
       "Cabin altitude set (ft MSL)"},

      // Pressurisation: cabin alt change set — feet/sec (FLOAT32)
      {0x0320, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/pressure/cabin_vvi_set_m_msec");
         put<float>(dst, r ? XPLMGetDataf(r) : 0.0f);
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/pressure/cabin_vvi_set_m_msec");
         if (r)
           XPLMSetDataf(r, take<float>(src));
       },
       "Cabin VVI set (m/sec)"},
//
//       // Pressurisation: cabin press diff — lb/sqft (FLOAT32)
//       {0x0324, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0324");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "Pressurisation: cabin press diff"},
//
//       // Pressurisation:dump switch — 1 = open, 0 = closed
//       {0x0328, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0328");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0328");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Pressurisation:dump switch"},
//
//       // Pushback angle — radians
//       {0x0334, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0334");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "Pushback angle"},
//
//       // Pushback X contact — feet
//       {0x0338, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0338");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "Pushback X contact"},
//
//       // Pushback Y contact — feet
//       {0x033C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x033C");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "Pushback Y contact"},
//
//       // Pushback Z contact — feet
//       {0x0340, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0340");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "Pushback Z contact"},
//
//       // Pushback wait flag
//       {0x0344, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0344");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Pushback wait flag"},
//
//       // Surface condition — 0 normal, 1 wet, 2 icy, 3 snow
//       {0x0346, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0346");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Surface condition"},
//
//       // Surface condition valid flag — not working?
//       {0x0347, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0347");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Surface condition valid flag"},
//
//       // Structural ice quantity — 0 none - 16384 100%
//       {0x0348, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0348");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Structural ice quantity"},
//
//       // Pitot ice quantity — 0 none - 16384 100%
//       {0x034A, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x034A");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Pitot ice quantity"},
//
//       // Fuel tank select — 0=Off, 1=All, 2=Left, 3=Right, 4=LeftAux,
//       // 5=RightAux, 6=Center, 7=Centre2, 8=Centre3, 9=Ext1, 10=Ext2,
//       // 11=RtTip, 12=LftTip, 14=CrossFeed Left to Right, 15=CrossFeed Right
//       // to Left
//       {0x0AF8, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0AF8");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0AF8");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "Fuel tank select"},
//
//       // Ground Altitude — Metres, *3.28084 for feet. See 0020 for more
//       // accuracy
//       {0x0B4C, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0B4C");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Ground Altitude"},
//
//       // Cloud type at aircraft
//       {0x0E84, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E84");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Cloud type at aircraft"},
//
//       // Cloud cover at aircraft
//       {0x0E85, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E85");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Cloud cover at aircraft"},
//
//       // Cloud icing at aircraft
//       {0x0E86, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E86");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Cloud icing at aircraft"},
//
//       // Cloud turbulence at aircraft
//       {0x0E88, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E88");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Cloud turbulence at aircraft"},
//
//       // Wind gusting at aircraft
//       {0x0E94, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E94");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Wind gusting at aircraft"},
//
//       // Wind variance at aircraft
//       {0x0E96, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E96");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Wind variance at aircraft"},
//
//       // Wind turbulence at aircraft
//       {0x0E98, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E98");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Wind turbulence at aircraft"},
//
//       // CG % lateral (FFSX) — CG percent laterally, as a double (FLOAT64).
//       // This is the position of the actual CoG as a fraction (%/100)  of
//       // MAC (Mean Aerodynamic Chord).
//       {0x2E78, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2E78");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "CG % lateral (FFSX)"},
//
//       // Incidence Alpha — Radians. Aircraft body AofA
//       {0x2ED0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Incidence Alpha"},
//
//       // Incidence Beta — Radians, side slip angle
//       {0x2ED8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Incidence Beta"},

      // CG % — probably position of actual CG as % of MAC
      {0x2EF8, 8,
       // Read/Write: Unknown
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/misc/cgz_ref_to_default");
         put<double>(dst, static_cast<double>(r ? XPLMGetDataf(r) : 0.0f));
       },
       nullptr,
       "CG position (m from design CG, double)"},
//
//       // CG AFT Limit
//       {0x2F00, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "CG AFT Limit"},
//
//       // CG FWD Limit
//       {0x2F08, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "CG FWD Limit"},
//
//       // CG Max MACH
//       {0x2F10, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "CG Max MACH"},
//
//       // CG Min MACH
//       {0x2F18, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "CG Min MACH"},

      // Validity pattern FADE — If this is not "0xFADE" then the above
      // Version information is not trustworthy!
      {0x330A, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &)
       {
         put<int16_t>(dst, static_cast<int16_t>(0xFADE)); // fixed magic pattern
       },
       nullptr,
       "FSUIPC magic (0xFADE)"},
//
//       // Assorted FSUIPC status flags — Bit 1 = full IPC access allowed Bit 2
//       // = FSUIPC is user registered Bit 4 = Throttle Sync (hot key) enabled
//       {0x330C, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x330C");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Assorted FSUIPC status flags"},
//
//       // Sound player command/busy
//       {0x4200, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x4200");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x4200");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Sound player command/busy"},
//
//       // Sound player options
//       {0x4201, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x4201");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x4201");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Sound player options"},
//
//       // Sound player status
//       {0x4202, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x4202");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Sound player status"},
//
//       // Sound player reference
//       {0x4204, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x4204");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x4204");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Sound player reference"},
//
//       // Sound player WAV file pathname
//       {0x4208, 247,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x4208");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 247);
//          dst[0] = 0;
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x4208");
//          // TODO: string — XPLMSetDatab(r, (void*)src, 0, (int)sz);
//        },
//        "Sound player WAV file pathname"},
//
//       // Aerosoft EICAS/EFIS switch command
//       {0x5280, 1,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Aerosoft EICAS/EFIS switch command"},
//
//       // Aerosoft EICAS/EFIS switch data
//       {0x5281, 1,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Aerosoft EICAS/EFIS switch data"},

  }; // end table
  return table;
}
