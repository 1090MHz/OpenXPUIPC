// SPDX-License-Identifier: GPL-3.0-or-later
// fsuipc_offsets/Plane.h — Production offset table
//
// 43 total offsets in this category
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

inline const std::vector<OffsetEntry> &fsuipc_offset_table_plane()
{
  static const std::vector<OffsetEntry> table = {

//
//       // ===== Plane ==================================================
//
//       // Design speed VS0 — Stall speed full flaps, in ft/sec
//       {0x0538, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0538");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Design speed VS0"},
//
//       // Design speed VS1 — Stall speed clean, in ft/sec
//       {0x0540, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0540");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Design speed VS1"},
//
//       // Design speed VC — Cruise speed, in ft/sec
//       {0x0548, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0548");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Design speed VC"},
//
//       // Minimum drage velocity — ft/sec
//       {0x0550, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0550");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Minimum drage velocity"},
//
//       // Smoke System control — 0=Off, 1=On, if smoke available
//       {0x05D8, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05D8");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05D8");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Smoke System control"},
//
//       // Gear type (<= FS2000) — 0=Gear is fixed, 1=Gear is reractable,
//       // 2=Gear is slides, ...?
//       {0x060C, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x060C");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Gear type (<= FS2000)"},
//
//       // Retractable gear
//       {0x060E, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x060E");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Retractable gear"},
//
//       // Retractable left float extension — 0=fully retracted, 16384=fully
//       // extended
//       {0x0614, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0614");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Retractable left float extension"},
//
//       // Retractable right float extension — 0=fully retracted, 16384=fully
//       // extended
//       {0x0616, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0616");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Retractable right float extension"},
//
//       // Flap Fitted — 0=Has no flaps. 1=Has flaps
//       {0x0778, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0778");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Flap Fitted"},
//
//       // Has stall horn — not FS2004?
//       {0x077C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x077C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Has stall horn"},
//
//       // Has spoilers
//       {0x078C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x078C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Has spoilers"},
//
//       // Aircraft is tail dragger
//       {0x0790, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0790");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Aircraft is tail dragger"},
//
//       // Has strobes
//       {0x0794, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0794");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Has strobes"},
//
//       // Has toe brakes
//       {0x079C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x079C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Has toe brakes"},
//
//       // Electrical load (helos) [FS2004]
//       {0x08FC, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Electrical load (helos) [FS2004]"},

      // Number of engines
      {0x0AEC, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h141 = XPLMFindDataRef("sim/aircraft/engine/acf_num_engines");
         put<int16_t>(dst, static_cast<int16_t>(r_h141 ? XPLMGetDatai(r_h141) : 0));
       },
       nullptr,
       "Number of engines"},
//
//       // Throttle low limit % — For aircraft with reverse thrust this will be
//       // negative, e.g. -4096=25%. This is the lowest working value for the
//       // Throttle Controls listed earlier.
//       {0x0B00, 2,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Throttle low limit %"},
//
//       // Mach maximum operating — Not FS2004
//       {0x0B0C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0B0C");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Mach maximum operating"},

      // Payload station count (FS2004) — Up to 61 station details follow,
      // all with the same 48-byte structure
      {0x13FC, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Count non-zero payload stations from acf_m_station_max array (9 stations max in X-Plane)
         static XPLMDataRef r = XPLMFindDataRef("sim/aircraft/weight/acf_m_station_max");
         uint32_t count = 0;
         if (r) {
           float stations[9] = {0};
           int num_values = XPLMGetDatavf(r, stations, 0, 9);
           for (int i = 0; i < num_values; i++) {
             if (stations[i] > 0.0f) {
               count++;
             }
           }
         }
         put<uint32_t>(dst, count);
       },
       nullptr,
       "Payload station count"},

//       // Payload weight lbs (FS2004) — Payload station 2-61 appear after
//       // these, 48 bytes each
//       {0x1400, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1400");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Payload weight lbs (FS2004)"},
//
//       // Payload lateral feet (FS2004)
//       {0x1408, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1408");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Payload lateral feet (FS2004)"},
//
//       // Payload vertical feet (FS2004)
//       {0x1410, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1410");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Payload vertical feet (FS2004)"},
//
//       // Payload longitudinal feet (FS2004)
//       {0x1418, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1418");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Payload longitudinal feet (FS2004)"},
//
//       // Payload name (16 ch ASCIIZ) (FS2004)
//       {0x1420, 16,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1420");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 16);
//          dst[0] = 0;
//        },
//        nullptr,
//        "Payload name (16 ch ASCIIZ) (FS2004)"},
//
//       // Left folding wing %
//       {0x2A48, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Left folding wing %"},
//
//       // Right folding wind %
//       {0x2A50, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Right folding wind %"},
//
//       // Canopy open
//       {0x2A70, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Canopy open"},

      // Current loaded weight [FS2000+] — In lbs
      {0x30C0, 8,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Total aircraft weight in pounds (kg * 2.20462)
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/weight/m_total");
         float kg = r ? XPLMGetDataf(r) : 0.0f;
         put<double>(dst, static_cast<double>(kg * 2.20462f));
       },
       nullptr,
       "Gross weight (lbs)"},
//
//       // Plane's mass [FS2000+] — Units are slugs (1 lb * G = 32.174 lbs
//       // mass)
//       {0x30C8, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x30C8");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Plane's mass [FS2000+]"},
//
//       // Doors open flags — FS2004: Bit 0 = Main Doors open (no others used
//       // at present).
//       {0x3367, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3367");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3367");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Doors open flags"},
//
//       // Toe brakes handled by FSUIPC — High byte=Right, lo byte=Left, NZ if
//       // FSUIPC is "set" to deal with toe brakes
//       {0x336E, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x336E");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Toe brakes handled by FSUIPC"},
//
//       // Prop De-ice switch [FS2002+] — Reflects anti-ice switch only?
//       {0x337C, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x337C");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x337C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Prop De-ice switch [FS2002+]"},
//
//       // Structural De-ice switch [FS2002+] — Not implemented, though
//       // documented in panels SDK?
//       {0x337D, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x337D");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x337D");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Structural De-ice switch [FS2002+]"},
//
//       // G-Force Maximum
//       {0x34D0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "G-Force Maximum"},
//
//       // G-Force Minimum
//       {0x34D8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "G-Force Minimum"},
//
//       // ENG1 Max RPM
//       {0x34E8, 2,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG1 Max RPM"},
//
//       // ENG2 Max RPM
//       {0x34EC, 2,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG2 Max RPM"},
//
//       // ENG3 Max RPM
//       {0x34F0, 2,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG3 Max RPM"},
//
//       // ENG4 Max RPM
//       {0x34F4, 2,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG4 Max RPM"},
//
//       // Airspeed Mach value
//       {0x35A0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Airspeed Mach value"},

      // No. of flap positions (not incl up)
      {0x3BF8, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Get number of flap detents, subtract 1 to exclude "up" position
         static XPLMDataRef r = XPLMFindDataRef("sim/aircraft/controls/acf_flap_detents");
         int detents = r ? XPLMGetDatai(r) : 1;
         put<uint16_t>(dst, static_cast<uint16_t>(detents > 0 ? detents - 1 : 0));
       },
       nullptr,
       "No. of flap positions (not incl up)"},

      // Zero Fuel Weight — lbs * 256
      {0x3BFC, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_total = XPLMFindDataRef("sim/flightmodel/weight/m_total");
         static XPLMDataRef r_fuel = XPLMFindDataRef("sim/flightmodel/weight/m_fuel_total");
         float kg = (r_total ? XPLMGetDataf(r_total) : 0.0f) - (r_fuel ? XPLMGetDataf(r_fuel) : 0.0f);
         put<int32_t>(dst, static_cast<int32_t>(kg * 2.20462f * 256.0f));
       },
       nullptr,
       "Zero fuel weight (lbs*256)"},

  }; // end table
  return table;
}
