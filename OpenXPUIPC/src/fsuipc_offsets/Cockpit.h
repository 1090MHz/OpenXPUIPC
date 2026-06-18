// SPDX-License-Identifier: LGPL-3.0-or-later
// fsuipc_offsets/Cockpit.h — Production offset table
//
// 79 total offsets in this category
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

inline const std::vector<OffsetEntry> &fsuipc_offset_table_cockpit()
{
  static const std::vector<OffsetEntry> table = {

      {0x0280, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/switches/navigation_lights_on");
         put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/switches/navigation_lights_on");
         if (r)
           XPLMSetDatai(r, take<uint8_t>(src) ? 1 : 0);
       },
       "Navigation lights switch"},

      // Strobe/Beacon Lights — Operates Strobe and Beacon Lights. See $0D0C
      // for more control
      {0x0281, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_strb = XPLMFindDataRef("sim/cockpit/electrical/strobe_lights_on");
         static XPLMDataRef r_bcn = XPLMFindDataRef("sim/cockpit2/switches/beacon_on");
         int v = (r_strb ? XPLMGetDatai(r_strb) : 0) | (r_bcn ? XPLMGetDatai(r_bcn) : 0);
         put<uint8_t>(dst, static_cast<uint8_t>(v ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         const int v = take<uint8_t>(src) ? 1 : 0;
         static XPLMDataRef r_strb = XPLMFindDataRef("sim/cockpit/electrical/strobe_lights_on");
         static XPLMDataRef r_bcn = XPLMFindDataRef("sim/cockpit2/switches/beacon_on");
         if (r_strb)
           XPLMSetDatai(r_strb, v);
         if (r_bcn)
           XPLMSetDatai(r_bcn, v);
       },
       "Beacon and strobe lights"},

      // Landing Lights — Operates Landing Lights. See $0D0C
      {0x028C, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/switches/landing_lights_on");
         put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
       },
       nullptr,
       "Landing lights switch"},
//
//       // Alternate static air source — 0=alternate not selected 1=alternate
//       // selected
//       {0x029B, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x029B");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x029B");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Alternate static air source"},

      // Pitot heat — 0=Off, 1=On
      {0x029C, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/switches/pitot_heat_on");
         put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
       },
       nullptr,
       "Pitot heat switch"},

      // Altimeter setting (mb) — millibars (hPa) * 16, this is the
      // "Kollsman" window setting on the altimeter
      {0x0330, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h17 = XPLMFindDataRef("sim/cockpit/misc/barometer_setting");
         float alt = (r_h17 ? XPLMGetDataf(r_h17) : 0.0f);
         put<int16_t>(dst, static_cast<int16_t>(conv::inch_to_hpa(alt)) * 16);
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         int16_t val = take<int16_t>(src);
         static XPLMDataRef r_h18 = XPLMFindDataRef("sim/cockpit/misc/barometer_setting");
         if (r_h18)
           XPLMSetDataf(r_h18, conv::hpa_to_inch(val / 16.0f));
       },
       "QNH / altimeter setting"},
//
//       // G1000 altimeter setting (mb) — millibars (hPa) * 16, this is the
//       // "Kollsman" window setting on the G1000 altimeter
//       {0x0332, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0332");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0332");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "G1000 altimeter setting (mb)"},

      // Turn coordinator ball — -128 to +127, turn coordinator ball
      // position, +to right, - to left, 0 balanced
      {0x036E, 1,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/misc/slip");
         float slip = r ? XPLMGetDataf(r) : 0.0f;
         put<int8_t>(dst, static_cast<int8_t>((std::max)(-128.0f, (std::min)(127.0f, slip * 12.7f))));
       },
       nullptr,
       "Slip indicator (ball, -128=left, 127=right)"},

      // Turn Rate — Signed turn rate for coordinator needle. -512=2minute
      // Left, +512=2minute Right.
      {0x037C, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/gauges/indicators/turn_rate_heading_deg_pilot");
         float rate = r ? XPLMGetDataf(r) : 0.0f;
         put<int16_t>(dst, static_cast<int16_t>(rate * 512.0f / 3.0f));
       },
       nullptr,
       "Turn rate (0=level, +-512=2min turn)"},
//
//       // Turn coordinator ball position — More precise version of 036E, range
//       // -1.0 to +1.0
//       {0x0380, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0380");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "Turn coordinator ball position"},
//
//       // Turn rate — More precise version of 037C, the range -3.0 to +3.0 is
//       // equivalent to the 2 mins left/right range.
//       {0x0384, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0384");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "Turn rate"},
//
//       // Display IAS (<= FS2000)
//       {0x0612, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0612");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0612");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Display IAS (<= FS2000)"},
//
//       // Active Engine bit-pattern — bit 0=Eng1, 1=Eng2, 2=Eng3, 3=eng4, so
//       // value 15=all 4 engines selected
//       {0x0888, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0888");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0888");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Active Engine bit-pattern"},
//
//       // ENG1 Ant-Ice / Carb heat — 0=Off, 1=On
//       {0x08B2, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x08B2");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x08B2");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "ENG1 Ant-Ice / Carb heat"},

      // ENG2 Ant-Ice / Carb heat — 0=Off, 1=On
      {0x094A, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h50 = XPLMFindDataRef("sim/cockpit2/ice/ice_inlet_heat_on_per_engine");
         int _iv50 = 0;
         if (r_h50)
           XPLMGetDatavi(r_h50, &_iv50, 1, 1);
         put<int16_t>(dst, static_cast<int16_t>(_iv50));
       },
       nullptr,
       "Engine 2 anti-ice / carb heat"},

      // ENG3 Ant-Ice / Carb heat — 0=Off, 1=On
      {0x09E2, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h61 = XPLMFindDataRef("sim/cockpit2/ice/ice_inlet_heat_on_per_engine");
         int _iv61 = 0;
         if (r_h61)
           XPLMGetDatavi(r_h61, &_iv61, 2, 1);
         put<int16_t>(dst, static_cast<int16_t>(_iv61));
       },
       nullptr,
       "Engine 3 anti-ice / carb heat"},

      // ENG4 Ant-Ice / Carb heat — 0=Off, 1=On
      {0x0A7A, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h62 = XPLMFindDataRef("sim/cockpit2/ice/ice_inlet_heat_on_per_engine");
         int _iv62 = 0;
         if (r_h62)
           XPLMGetDatavi(r_h62, &_iv62, 3, 1);
         put<int16_t>(dst, static_cast<int16_t>(_iv62));
       },
       nullptr,
       "Engine 4 anti-ice / carb heat"},

      // Suction pressure — Gyro suction in " of Hg [FS2k?]
      {0x0B18, 8,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/misc/vacuum");
         // Despite JSON describing this as a ratio, empirical values align with suction-gauge units.
         put<double>(dst, static_cast<double>(r ? XPLMGetDataf(r) : 0.0f));
       },
       nullptr,
       "Gyro vacuum (inHg, double)"},
//
//       // Spoiler arm — 0=Off, 1=Active (Arm spoiler for auto-deployment)
//       {0x0BCC, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0BCC");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0BCC");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int32_t>(src)));
//        },
//        "Spoiler arm"},
//
//       // Gyro Drift
//       {0x0C3E, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C3E");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C3E");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "Gyro Drift"},

      // Lights [FS2000+) — 1=Nav, 2=Bcn, 4=Land, 8=Taxi, 16=Strobe,
      // 32=Panel, 64=Recognition, 128=Wing, 256=Logo, 512=Cabin (see also
      // $0280, $0281 and $028C)
      {0x0D0C, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_nav = XPLMFindDataRef("sim/cockpit2/switches/navigation_lights_on");
         static XPLMDataRef r_bcn = XPLMFindDataRef("sim/cockpit2/switches/beacon_on");
         static XPLMDataRef r_land = XPLMFindDataRef("sim/cockpit2/switches/landing_lights_on");
         static XPLMDataRef r_taxi = XPLMFindDataRef("sim/cockpit2/switches/taxi_light_on");
         static XPLMDataRef r_strb = XPLMFindDataRef("sim/cockpit2/switches/strobe_lights_on");
         static XPLMDataRef r_flood = XPLMFindDataRef("sim/cockpit2/switches/panel_brightness_ratio");
         int16_t flags = 0;
         if (r_nav && XPLMGetDatai(r_nav))
           flags |= 1;
         if (r_bcn && XPLMGetDatai(r_bcn))
           flags |= 2;
         if (r_land && XPLMGetDatai(r_land))
           flags |= 4;
         if (r_taxi && XPLMGetDatai(r_taxi))
           flags |= 8;
         if (r_strb && XPLMGetDatai(r_strb))
           flags |= 16;
         if (r_flood)
         {
           float v = 0.0f;
           XPLMGetDatavf(r_flood, &v, 0, 1);
           if (v >= 0.5f)
             flags |= 32;
         }
         put<int16_t>(dst, flags);
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         int16_t flags = take<int16_t>(src);
         static XPLMDataRef r_nav = XPLMFindDataRef("sim/cockpit2/switches/navigation_lights_on");
         static XPLMDataRef r_bcn = XPLMFindDataRef("sim/cockpit2/switches/beacon_on");
         static XPLMDataRef r_land = XPLMFindDataRef("sim/cockpit2/switches/landing_lights_on");
         static XPLMDataRef r_taxi = XPLMFindDataRef("sim/cockpit2/switches/taxi_light_on");
         static XPLMDataRef r_strb = XPLMFindDataRef("sim/cockpit2/switches/strobe_lights_on");
         static XPLMDataRef r_flood = XPLMFindDataRef("sim/cockpit2/switches/panel_brightness_ratio");
         if (r_nav)
           XPLMSetDatai(r_nav, (flags & 1) ? 1 : 0);
         if (r_bcn)
           XPLMSetDatai(r_bcn, (flags & 2) ? 1 : 0);
         if (r_land)
           XPLMSetDatai(r_land, (flags & 4) ? 1 : 0);
         if (r_taxi)
           XPLMSetDatai(r_taxi, (flags & 8) ? 1 : 0);
         if (r_strb)
           XPLMSetDatai(r_strb, (flags & 16) ? 1 : 0);
         if (r_flood)
         {
           float v = (flags & 32) ? 1.0f : 0.0f;
           XPLMSetDatavf(r_flood, &v, 0, 1);
         }
       },
       "Light switches (nav/beacon/landing/taxi/strobe/flood)"},
//
//       // ND scale (738/A321 EFIS) — Default 738 and A321 EFIS: ND scale: 738:
//       // 0=5nm up to 7=640nm A321: 0=10nm up to 5=320nm
//       {0x0E00, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E00");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E00");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "ND scale (738/A321 EFIS)"},
//
//       // ND mode (738 EFIS) — Default 738 EFIS: ND mode: 0=APP, 1=VOR, 2=MAP
//       {0x0E02, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E02");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E02");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "ND mode (738 EFIS)"},
//
//       // ND map items (738 / A321 EFIS) — Default 738 and A321 EFIS: ND map
//       // items shown: 738: 0=WPT, 1=APT, 2=NDB, 3=VOR A321: 0=WPT, 1=VOR,
//       // 2=NDB, 3=APT
//       {0x0E04, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E04");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E04");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "ND map items (738 / A321 EFIS)"},
//
//       // ND rad1 select (738 EFIS) — Default 738 EFIS: ND VOR/ADF1 switch:
//       // 0=VOR, 1=OFF, 2=ADF
//       {0x0E06, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E06");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E06");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "ND rad1 select (738 EFIS)"},
//
//       // ND rad2 select (738 EFIS) — Default 738 EFIS: ND VOR/ADF2 switch:
//       // 0=VOR, 1=OFF, 2=ADF
//       {0x0E08, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E08");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E08");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "ND rad2 select (738 EFIS)"},
//
//       // ND arc/ctr (738 EFIS) — Default 738 EFIS: ND arc=0, centred=1
//       {0x0E0A, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E0A");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E0A");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "ND arc/ctr (738 EFIS)"},
//
//       // AP C/O (738) — Default 738 EFIS: AP speed/mach C/O button (pressed
//       // if 1, not pressed if 0).
//       {0x0E0C, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E0C");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AP C/O (738)"},
//
//       // ND mode (A321 EFIS) — Default A321 EFIS: ND mode: 0=ILS, 1=VOR,
//       // 2=NAV, 3=ARC
//       {0x0E0E, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E0E");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E0E");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "ND mode (A321 EFIS)"},
//
//       // ND rad1 select (A321 EFIS) — Default A321 EFIS: ND VOR/ADF1 switch:
//       // 0=VOR, 1=OFF, 2=ADF
//       {0x0E10, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E10");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E10");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "ND rad1 select (A321 EFIS)"},
//
//       // ND rad2 select (A321 EFIS) — Default A321 EFIS: ND VOR/ADF2 switch:
//       // 0=VOR, 1=OFF, 2=ADF
//       {0x0E12, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E12");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E12");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "ND rad2 select (A321 EFIS)"},
//
//       // ND Ins/hPA select (A321 EFIS) — Default A321 EFIS: ND InHg/hPA
//       // switch, 0=InHg, 1=hPA
//       {0x0E14, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E14");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E14");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "ND Ins/hPA select (A321 EFIS)"},
//
//       // ND ILS mode (A321 EFIS) — Default A321 EFIS: ND ILS mode button, 0 =
//       // off, 1=onA
//       {0x0E16, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E16");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E16");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "ND ILS mode (A321 EFIS)"},
//
//       // AP C/O (A321) — Default A321 EFIS: AP speed/mach C/O button (pressed
//       // if 1, not pressed if 0).
//       {0x0E18, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E18");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AP C/O (A321)"},
//
//       // Alt change rate (A321 EFIS) — Default A321 EFIS: Altitude change
//       // rate switch (0 = 100, 1=1000)
//       {0x0E1A, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E1A");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0E1A");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Alt change rate (A321 EFIS)"},
//
//       // Elevon 1 Deflector
//       {0x2A00, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Elevon 1 Deflector"},
//
//       // Elevon 2 Deflector
//       {0x2A08, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Elevon 2 Deflector"},
//
//       // Elevon 3 Deflector
//       {0x2A10, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Elevon 3 Deflector"},
//
//       // Elevon 4 Deflector
//       {0x2A18, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Elevon 4 Deflector"},
//
//       // Elevon 5 Deflector
//       {0x2A20, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Elevon 5 Deflector"},
//
//       // Elevon 6 Deflector
//       {0x2A28, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Elevon 6 Deflector"},
//
//       // Elevon 7 Deflector
//       {0x2A30, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Elevon 7 Deflector"},
//
//       // Elevon 8 Deflector
//       {0x2A38, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Elevon 8 Deflector"},
//
//       // Gyro compass heading (mag) — Includes drift
//       {0x2B00, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Gyro compass heading (mag)"},
//
//       // Hyd. 1 Press. PSF
//       {0x2B08, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Hyd. 1 Press. PSF"},
//
//       // Hyd. 1 Reservoir Pct.
//       {0x2B1C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Hyd. 1 Reservoir Pct."},
//
//       // Hyd. 2 Press. PSF
//       {0x2C08, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Hyd. 2 Press. PSF"},
//
//       // Hyd. 2 Reservoir Pct.
//       {0x2C1C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Hyd. 2 Reservoir Pct."},
//
//       // Hyd. 3 Press. PSF
//       {0x2D08, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Hyd. 3 Press. PSF"},
//
//       // Hyd. 3 Reservoir Pct.
//       {0x2D1C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Hyd. 3 Reservoir Pct."},
//
//       // Hyd. 4 Press. PSF
//       {0x2E08, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Hyd. 4 Press. PSF"},
//
//       // Hyd. 4 Reservoir Pct.
//       {0x2E1C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Hyd. 4 Reservoir Pct."},
//
//       // Avionics Master Switch
//       {0x2E80, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2E80");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2E80");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Avionics Master Switch"},
//
//       // Panel Autofeather Switch
//       {0x2E88, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2E88");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2E88");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Panel Autofeather Switch"},
//
//       // Standby Vacuum Circuit On
//       {0x2E90, 2,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Standby Vacuum Circuit On"},
//
//       // Prop.sync Active
//       {0x2EC8, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2EC8");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2EC8");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Prop.sync Active"},
//
//       // Concorde Visor Nose Handle
//       {0x2F20, 2,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Concorde Visor Nose Handle"},
//
//       // Barbers Pole Mach
//       {0x2F50, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Barbers Pole Mach"},
//
//       // Select Fuel Transfer Mode
//       {0x2F58, 2,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Select Fuel Transfer Mode"},
//
//       // Attitude Cage Button
//       {0x2F68, 2,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Attitude Cage Button"},

      // Attitude Indicator Pitch — degrees
      {0x2F70, 8,
       // Read/Write: Unknown
       // FSUIPC sign convention: negative = nose-up (same as 0x0578 float version)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/position/theta");
         put<double>(dst, -static_cast<double>(r ? XPLMGetDataf(r) : 0.0f));
       },
       nullptr,
       "Pitch angle (deg, double)"},

      // Attitude Indicator Bank — degrees
      {0x2F78, 8,
       // Read/Write: Unknown
       // FSUIPC sign convention: negative = right-bank-down (same as 0x057C float version)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/position/phi");
         put<double>(dst, -static_cast<double>(r ? XPLMGetDataf(r) : 0.0f));
       },
       nullptr,
       "Bank angle (deg, double)"},

      // Panel Autobrake Switch — 0=RTO, 1=off, 2=brake1, 3=brake2, 4=brake3,
      // 5=max
      {0x2F80, 1,
       // Read/Write: Read/Write
       // Use switch position (matches legacy XPUIPC: sim/cockpit/switches/auto_brake_settings)
       // 0=off, 1=RTO, 2=1, 3=2, 4=3, 5=max
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/switches/auto_brake_settings");
         put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
       },
       nullptr,
       "Panel autobrake switch"},
//
//       // electric always available (FS2002 only) — Copy of FS2002's "electric
//       // always available" flag, can be changed too.
//       {0x3124, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3124");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3124");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "electric always available (FS2002 only)"},
//
//       // No smoking switch — 0 off, 1 on
//       {0x341C, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x341C");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x341C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "No smoking switch"},
//
//       // Seat belt switch — 0 off, 1 on
//       {0x341D, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x341D");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x341D");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Seat belt switch"},
//
//       // Rad Ind Switch
//       {0x3420, 2,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Rad Ind Switch"},
//
//       // Low Height Warning
//       {0x3424, 2,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Low Height Warning"},
//
//       // ENG1 FuelFlow Bug Position
//       {0x3438, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG1 FuelFlow Bug Position"},
//
//       // ENG2 FuelFlow Bug Position
//       {0x3440, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG2 FuelFlow Bug Position"},
//
//       // ENG3 FuelFlow Bug Position
//       {0x3448, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG3 FuelFlow Bug Position"},
//
//       // ENG4 FuelFlow Bug Position
//       {0x3450, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG4 FuelFlow Bug Position"},

      // Standby altimeter pressure setting (mb x 16) — Used by FSUIPC to
      // maintain 3544
      {0x3542, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h136 = XPLMFindDataRef("sim/cockpit/misc/barometer_setting2");
         float alt = (r_h136 ? XPLMGetDataf(r_h136) : 0.0f);
         put<int16_t>(dst, static_cast<int16_t>(conv::inch_to_hpa(alt)) * 16);
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         int16_t val = take<int16_t>(src);
         static XPLMDataRef r_h137 = XPLMFindDataRef("sim/cockpit/misc/barometer_setting2");
         if (r_h137)
           XPLMSetDataf(r_h137, conv::hpa_to_inch(val / 16.0f));
       },
       "Standby QNH"},

      // Standby altimeter altitude reading — Feet or Metres depending on
      // 0C18
      {0x3544, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h138 = XPLMFindDataRef("sim/flightmodel/misc/h_ind_copilot2");
         put<int32_t>(dst, static_cast<int32_t>((r_h138 ? XPLMGetDataf(r_h138) : 0.0f)));
       },
       nullptr,
       "Standby altitude"},
//
//       // Horizon Bar / Attitude Bars — Percent of max, -100 (down) to +100
//       // (up), 100% in Cessna is 10 degrees
//       {0x3548, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3548");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Horizon Bar / Attitude Bars"},
//
//       // ENG4 General Generator Switch
//       {0x3938, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG4 General Generator Switch"},
//
//       // ENG3 General Generator Switch
//       {0x39F8, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG3 General Generator Switch"},
//
//       // ENG2 General Generator Switch
//       {0x3AB8, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG2 General Generator Switch"},
//
//       // ENG1 General Generator Switch
//       {0x3B78, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG1 General Generator Switch"},

  }; // end table
  return table;
}
