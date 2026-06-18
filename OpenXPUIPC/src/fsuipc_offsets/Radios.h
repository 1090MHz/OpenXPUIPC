// SPDX-License-Identifier: LGPL-3.0-or-later
// fsuipc_offsets/Radios.h — Production offset table
//
// 181 total offsets in this category
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
#include "impl/nav_station.h"  // find_nav_station(), NavStation

inline const std::vector<OffsetEntry> &fsuipc_offset_table_radios()
{
  static const std::vector<OffsetEntry> table = {

      {0x02D4, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h15 = XPLMFindDataRef("sim/cockpit/radios/adf2_freq_hz");
         put<int16_t>(dst, conv::to_bcd(r_h15 ? XPLMGetDatai(r_h15) : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h16 = XPLMFindDataRef("sim/cockpit/radios/adf2_freq_hz");
         if (r_h16)
           XPLMSetDatai(r_h16, from_bcd(take<uint16_t>(src)));
       },
       "ADF2 frequency (BCD)"},
//
//       // ADF2 Extended Freq (FS2004) — BCD, high byte=1000's digit, low
//       // byte=fraction digit
//       {0x02D6, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x02D6");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x02D6");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "ADF2 Extended Freq (FS2004)"},
//
//       // ADF2 Rel Bearing (FS2004)
//       {0x02D8, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x02D8");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ADF2 Rel Bearing (FS2004)"},

      // NDB2 identity (FS2004) — six byte character string including zero
      // terminator
      {0x02DC, 6,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         auto s = find_nav_station(dref, "sim/cockpit/radios/adf2_freq_hz", NAV_NDB);
         std::memcpy(dst, s.id, 6);
       },
       nullptr,
       "ADF2 station ID"},
//
//       // NDB2 name (FS2004) — 25 byte character string including zero
//       // terminator
//       {0x02E2, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x02E2");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "NDB2 name (FS2004)"},
//
//       // ADF2 ident sound switch (FS2004) — 1=enabled, 0=disabled
//       {0x02FB, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x02FB");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x02FB");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "ADF2 ident sound switch (FS2004)"},

      // VOR1 DME distance (tenths nm)
      {0x0300, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Despite the _m suffix, this dataref returns nautical miles.
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/nav1_dme_dist_m");
         float nm = r ? XPLMGetDataf(r) : 0.0f;
         put<int16_t>(dst, static_cast<int16_t>(nm * 10.0f));
       },
       nullptr,
       "VOR1 DME distance (nm * 10)"},

      // VOR1 DME speed (tenths kts)
      {0x0302, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/nav1_dme_speed_kts");
         float kts = r ? XPLMGetDataf(r) : 0.0f;
         put<int16_t>(dst, static_cast<int16_t>(kts * 10.0f));
       },
       nullptr,
       "VOR1 DME speed (kts * 10)"},

      // VOR1 DME time to stn (tenths secs)
      {0x0304, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/nav1_dme_time_secs");
         float s = r ? XPLMGetDataf(r) : 0.0f;
         put<int16_t>(dst, static_cast<int16_t>(s * 10.0f));
       },
       nullptr,
       "VOR1 DME time to station (secs * 10)"},

      // VOR2 DME distance (tenths nm)
      {0x0306, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/nav2_dme_dist_m");
         float nm = r ? XPLMGetDataf(r) : 0.0f;
         put<int16_t>(dst, static_cast<int16_t>(nm * 10.0f));
       },
       nullptr,
       "VOR2 DME distance (nm * 10)"},

      // VOR2 DME speed (tenths kts)
      {0x0308, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/nav2_dme_speed_kts");
         float kts = r ? XPLMGetDataf(r) : 0.0f;
         put<int16_t>(dst, static_cast<int16_t>(kts * 10.0f));
       },
       nullptr,
       "VOR2 DME speed (kts * 10)"},

      // VOR2 DME time to stn (tenths secs)
      {0x030A, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/nav2_dme_time_secs");
         float s = r ? XPLMGetDataf(r) : 0.0f;
         put<int16_t>(dst, static_cast<int16_t>(s * 10.0f));
       },
       nullptr,
       "VOR2 DME time to station (secs * 10)"},

      // ADF Freq — Frequency show as BCD (Binary Coded Decimal), 3 digits
      // (NNN). The thousandfs digit and the fractional parts are proovided
      // in the Extended ADF frequency location, 0356
      {0x034C, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h19 = XPLMFindDataRef("sim/cockpit/radios/adf1_freq_hz");
         put<int16_t>(dst, conv::to_bcd((r_h19 ? XPLMGetDatai(r_h19) : 0)));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h20 = XPLMFindDataRef("sim/cockpit/radios/adf1_freq_hz");
         if (r_h20)
           XPLMSetDatai(r_h20, from_bcd(take<uint16_t>(src)));
       },
       "ADF1 frequency (BCD)"},

      // COM Freq — Frequency show as BCD (Binary Coded Decimal), however the
      // prefixed "1" is removed
      {0x034E, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h21 = XPLMFindDataRef("sim/cockpit/radios/com1_freq_hz");
         put<int16_t>(dst, conv::to_bcd((r_h21 ? XPLMGetDatai(r_h21) : 0) - 10000));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h22 = XPLMFindDataRef("sim/cockpit/radios/com1_freq_hz");
         if (r_h22)
           XPLMSetDatai(r_h22, from_bcd(take<uint16_t>(src)) + 10000);
       },
       "COM1 frequency (BCD)"},

      // NAV1 Freq — Frequency show as BCD (Binary Coded Decimal), however
      // the prefixed "1" is removed
      {0x0350, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h23 = XPLMFindDataRef("sim/cockpit/radios/nav1_freq_hz");
         put<int16_t>(dst, conv::to_bcd((r_h23 ? XPLMGetDatai(r_h23) : 0) - 10000));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h24 = XPLMFindDataRef("sim/cockpit/radios/nav1_freq_hz");
         if (r_h24)
           XPLMSetDatai(r_h24, from_bcd(take<uint16_t>(src)) + 10000);
       },
       "NAV1 frequency (BCD)"},

      // NAV2 Freq — Frequency show as BCD (Binary Coded Decimal), however
      // the prefixed "1" is removed
      {0x0352, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h25 = XPLMFindDataRef("sim/cockpit/radios/nav2_freq_hz");
         put<int16_t>(dst, conv::to_bcd((r_h25 ? XPLMGetDatai(r_h25) : 0) - 10000));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h26 = XPLMFindDataRef("sim/cockpit/radios/nav2_freq_hz");
         if (r_h26)
           XPLMSetDatai(r_h26, from_bcd(take<uint16_t>(src)) + 10000);
       },
       "NAV2 frequency (BCD)"},

      // XPND - Transponser Freq. — Frequency show as BCD (Binary Coded
      // Decimal)
      {0x0354, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // FSUIPC encodes transponder code as BCD: decimal 7000 → 0x7000 (28672)
         static XPLMDataRef r_h27 = XPLMFindDataRef("sim/cockpit/radios/transponder_code");
         put<int16_t>(dst, conv::to_bcd(r_h27 ? XPLMGetDatai(r_h27) : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h28 = XPLMFindDataRef("sim/cockpit/radios/transponder_code");
         if (r_h28)
           XPLMSetDatai(r_h28, conv::from_bcd(take<int16_t>(src)));
       },
       "Transponder code"},
//
//       // ADF Extended Freq — Hi byte provides 1,000's digit, low byte
//       // provides fraction
//       {0x0356, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0356");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0356");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "ADF Extended Freq"},
//
//       // NAV1/2 Select — 256=Nav1, 512=Nav2
//       {0x0374, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0374");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0374");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "NAV1/2 Select"},
//
//       // DME1/2 Select — 1=DME1, 2=DME2
//       {0x0378, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0378");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0378");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "DME1/2 Select"},
//
//       // NAV & ADF activate (<= FS2000) — Send 2 to activate NAV radio(s),
//       // send 512 to activate ADF (514 for both). Not needed on FS2002/4
//       {0x0388, 2,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0388");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "NAV & ADF activate (<= FS2000)"},
//
//       // COM/ATIS activate (<= FS2000) — Send 1 to Activate COM radio (search
//       // for ATIS transmission). Not needed on FS2002/4
//       {0x038A, 2,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x038A");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "COM/ATIS activate (<= FS2000)"},

      // Has NAV1
      {0x07A0, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h139 = XPLMFindDataRef("sim/cockpit/radios/nav1_freq_hz");
         put<int32_t>(dst, r_h139 ? int32_t(1) : int32_t(0));
       },
       nullptr,
       "NAV1 available"},

      // Has NAV2
      {0x07A4, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h140 = XPLMFindDataRef("sim/cockpit/radios/nav2_freq_hz");
         put<int32_t>(dst, r_h140 ? int32_t(1) : int32_t(0));
       },
       nullptr,
       "NAV2 available"},
//
//       // VOR2 DME Lat (FS2002+)
//       {0x0834, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0834");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "VOR2 DME Lat (FS2002+)"},
//
//       // VOR2 DME Long (FS2002+)
//       {0x0838, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0838");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "VOR2 DME Long (FS2002+)"},
//
//       // VOR2 DME Elevation (FS2002+]
//       {0x083C, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "VOR2 DME Elevation (FS2002+]"},

      // VOR2 Loc Heading (True) (FS2002+) — 180 degrees different to
      // aircraft direction to follow the localiser
      {0x0844, 2,
       // Read/Write: Read (only)
       // Convert to degrees by *360/65536. This is 180 degrees different
       // to the direction of flight to follow the localiser. [FS2002+]
       [](uint8_t *dst, DataRefCache &dref)
       {
         // Only meaningful when NAV2 is tuned to an ILS/LOC; return 0 for plain VOR
         auto s = find_nav_station(dref, "sim/cockpit/radios/nav2_freq_hz", NAV_ILS_LOC);
         if (!s.found)
         {
           put<uint16_t>(dst, 0);
           return;
         }
         static XPLMDataRef r_h38 = XPLMFindDataRef("sim/cockpit/radios/nav2_course_degm");
         float c = conv::wrap_heading((r_h38 ? XPLMGetDataf(r_h38) : 0.0f) + 180.0f);
         put<uint16_t>(dst, static_cast<uint16_t>(c / 360.0f * 65536.0f));
       },
       nullptr,
       "NAV2 ILS inverse runway heading"},
//
//       // VOR2 GS angle (FS2002+)
//       {0x0846, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0846");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "VOR2 GS angle (FS2002+)"},
//
//       // VOR2 LOC Lat (FS2002+)
//       {0x084C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x084C");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "VOR2 LOC Lat (FS2002+)"},
//
//       // VOR2 LOC Long (FS2002+)
//       {0x0850, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0850");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "VOR2 LOC Long (FS2002+)"},
//
//       // VOR2 LOC Elevation (FS2002+)
//       {0x0854, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0854");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "VOR2 LOC Elevation (FS2002+)"},

      // VOR2 or GS Lat (FS2002+)
      {0x0858, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         auto s = find_nav_station(dref, "sim/cockpit/radios/nav2_freq_hz", NAV_VOR_ILS_DME);
         put<int32_t>(dst, static_cast<int32_t>(s.lat / 90.0f * 10001750.0f));
       },
       nullptr,
       "NAV2 station latitude"},

      // VOR1 or GS Lat
      {0x085C, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         auto s = find_nav_station(dref, "sim/cockpit/radios/nav1_freq_hz", NAV_VOR_ILS_DME);
         put<int32_t>(dst, static_cast<int32_t>(s.lat / 90.0f * 10001750.0f));
       },
       nullptr,
       "NAV1 station latitude"},

      // VOR2 or GS Long (FS2002+)
      {0x0860, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         auto s = find_nav_station(dref, "sim/cockpit/radios/nav2_freq_hz", NAV_VOR_ILS_DME);
         put<int32_t>(dst, static_cast<int32_t>(s.lon / 360.0 * conv::FSUIPC_360_32));
       },
       nullptr,
       "NAV2 station longitude"},

      // VOR1 or GS Long
      {0x0864, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         auto s = find_nav_station(dref, "sim/cockpit/radios/nav1_freq_hz", NAV_VOR_ILS_DME);
         put<int32_t>(dst, static_cast<int32_t>(s.lon / 360.0 * conv::FSUIPC_360_32));
       },
       nullptr,
       "NAV1 station longitude"},
//
//       // VOR2 or GS Elevation (FS2002+)
//       {0x0868, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0868");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "VOR2 or GS Elevation (FS2002+)"},
//
//       // VOR1 or GS Elevation
//       {0x086C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x086C");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "VOR1 or GS Elevation"},

      // VOR1 Loc Heading (True) — 180 degrees different to aircraft
      // direction to follow the localiser
      {0x0870, 2,
       // Read/Write: Read (only)
       // Convert to degrees by *360/65536. This is 180 degrees different
       // to the direction of flight to follow the localiser.
       [](uint8_t *dst, DataRefCache &dref)
       {
         // Only meaningful when NAV1 is tuned to an ILS/LOC; return 0 for plain VOR
         auto s = find_nav_station(dref, "sim/cockpit/radios/nav1_freq_hz", NAV_ILS_LOC);
         if (!s.found)
         {
           put<uint16_t>(dst, 0);
           return;
         }
         static XPLMDataRef r_h39 = XPLMFindDataRef("sim/cockpit/radios/nav1_course_degm");
         float c = conv::wrap_heading((r_h39 ? XPLMGetDataf(r_h39) : 0.0f) + 180.0f);
         put<uint16_t>(dst, static_cast<uint16_t>(c / 360.0f * 65536.0f));
       },
       nullptr,
       "NAV1 ILS inverse runway heading"},
//
//       // VOR1 GS angle
//       {0x0872, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0872");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "VOR1 GS angle"},
//
//       // VOR1 LOC Lat (FS2002+)
//       {0x0874, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0874");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "VOR1 LOC Lat (FS2002+)"},
//
//       // VOR1 LOC Long (FS2002+)
//       {0x0878, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0878");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "VOR1 LOC Long (FS2002+)"},
//
//       // VOR1 LOC Elevation (FS2002+)
//       {0x087C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x087C");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "VOR1 LOC Elevation (FS2002+)"},
//
//       // VOR1 DME Lat (FS2002+)
//       {0x0880, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0880");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "VOR1 DME Lat (FS2002+)"},
//
//       // VOR1 DME Long (FS2002+)
//       {0x0884, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0884");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "VOR1 DME Long (FS2002+)"},
//
//       // VOR1 DME Elevation (FS2002+]
//       {0x088A, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x088A");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "VOR1 DME Elevation (FS2002+]"},

      // Inner Marker
      {0x0BAC, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/misc/over_inner_marker");
         put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
       },
       nullptr,
       "Inner marker"},

      // Middle Marker
      {0x0BAE, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/misc/over_middle_marker");
         put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
       },
       nullptr,
       "Middle marker"},

      // Outer Marker
      {0x0BB0, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/misc/over_outer_marker");
         put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
       },
       nullptr,
       "Outer marker"},
//
//       // ADF2 signal strength
//       {0x0C14, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C14");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ADF2 signal strength"},
//
//       // ADF1 signal strength
//       {0x0C1C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C1C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ADF1 signal strength"},

      // VOR 1 DMEdistance string — String is either "nn.n" followed by space
      // or zero, or "nnn." followed by space or zero. Units are nm.
      {0x0C29, 5,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // static XPLMDataRef r_h91 = XPLMFindDataRef("sim/cockpit2/radios/indicators/nav1_dme_distance_nm");
         static XPLMDataRef r_h91 = XPLMFindDataRef("sim/cockpit/radios/nav1_dme_dist_m"); // despite _m suffix, returns nautical miles
         float dist = (r_h91 ? XPLMGetDataf(r_h91) : 0.0f);
         char buf[6];
         std::snprintf(buf, sizeof(buf), "%04.1f", dist); // "nn.n"; >99.9 produces "nnn.d" truncated to "nnn." below
         buf[4] = '\0';
         std::memcpy(dst, buf, 5);
       },
       nullptr,
       "DME1 distance (string)"},
//
//       // VOR 1 DME Speed  string — String is "nnn" in knots, followed by
//       // space then zero or just zero.
//       {0x0C2E, 5,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C2E");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 5);
//          dst[0] = 0;
//        },
//        nullptr,
//        "VOR 1 DME Speed  string"},

      // VOR 2 DMEdistance string — String is either "nn.n" followed by space
      // or zero, or "nnn." followed by space or zero. Units are nm.
      {0x0C33, 5,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // static XPLMDataRef r_h92 = XPLMFindDataRef("sim/cockpit2/radios/indicators/nav2_dme_distance_nm");
         static XPLMDataRef r_h92 = XPLMFindDataRef("sim/cockpit/radios/nav2_dme_dist_m"); // despite _m suffix, returns nautical miles
         float dist = (r_h92 ? XPLMGetDataf(r_h92) : 0.0f);
         char buf[6];
         std::snprintf(buf, sizeof(buf), "%04.1f", dist); // "nn.n"; >99.9 produces "nnn.d" truncated to "nnn." below
         buf[4] = '\0';
         std::memcpy(dst, buf, 5);
       },
       nullptr,
       "DME2 distance (string)"},
//
//       // VOR 2 DME Speed string — String is "nnn" in knots, followed by space
//       // then zero or just zero.
//       {0x0C38, 5,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C38");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 5);
//          dst[0] = 0;
//        },
//        nullptr,
//        "VOR 2 DME Speed string"},

      // NAV1 Loc Needle — -127 left to +127 right
      {0x0C48, 1,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h93 = XPLMFindDataRef("sim/cockpit2/radios/indicators/nav1_hdef_dots_pilot");
         put<int8_t>(dst, static_cast<int8_t>((r_h93 ? XPLMGetDataf(r_h93) : 0.0f) / 2.5f * 127.0f));
       },
       nullptr,
       "NAV1 lateral deflection"},

      // NAV1 GS  Needle — -127 up to +127 down
      {0x0C49, 1,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h94 = XPLMFindDataRef("sim/cockpit2/radios/indicators/nav1_vdef_dots_pilot");
         put<int8_t>(dst, static_cast<int8_t>((r_h94 ? XPLMGetDataf(r_h94) : 0.0f) / 2.5f * 127.0f));
       },
       nullptr,
       "NAV1 glideslope"},
//
//       // NAV1 BC flags — Flags indicating VOR1 aspects as follows: (bit 0 =
//       // least sig) 0 = Back Course available 1 = Localiser tuned in 2 = On
//       // Back Course 7 = Station is active (set even if no BC available)
//       {0x0C4A, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C4A");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "NAV1 BC flags"},

      // NAV1 To/From Flag — 0=not active, 1=to, 2=from
      {0x0C4B, 1,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h95 = XPLMFindDataRef("sim/cockpit/radios/nav1_fromto");
         put<int8_t>(dst, static_cast<int8_t>((r_h95 ? XPLMGetDatai(r_h95) : 0)));
       },
       nullptr,
       "NAV1 from/to flag"},

      // NAV1 GS Active — 1=GS being received
      {0x0C4C, 1,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h96 = XPLMFindDataRef("sim/cockpit/radios/nav1_CDI");
         put<int8_t>(dst, static_cast<int8_t>((r_h96 ? XPLMGetDatai(r_h96) : 0)));
       },
       nullptr,
       "NAV1 CDI flag"},
//
//       // NAV1 code — Bits used as follows: 0     DME available 1 TACAN 2
//       // Voice available 3       No signal available 4   DME transmitter at
//       // GS transmitter 5     No back course 6        GS available 7  This is
//       // a localiser (else it's a VOR)
//       {0x0C4D, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C4D");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "NAV1 code"},

      // NAV1 OBS (CRS) — In degrees
      {0x0C4E, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h97 = XPLMFindDataRef("sim/cockpit/radios/nav1_obs_degm");
         put<int16_t>(dst, static_cast<int16_t>((r_h97 ? XPLMGetDataf(r_h97) : 0.0f)));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h98 = XPLMFindDataRef("sim/cockpit/radios/nav1_obs_degm");
         if (r_h98)
           XPLMSetDataf(r_h98, static_cast<float>(take<int16_t>(src)));
       },
       "NAV1 OBS"},

      // NAV1 Radial
      {0x0C50, 2,
       // Read/Write: Read (only)
       // degrees Magnetic for a VOR, but TRUE for an ILS LOC.
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h99 = XPLMFindDataRef("sim/cockpit2/radios/indicators/nav1_bearing_deg_mag");
         float b = conv::wrap_heading((r_h99 ? XPLMGetDataf(r_h99) : 0.0f) - 180.0f);
         put<uint16_t>(dst, static_cast<uint16_t>(b / 360.0f * 65536.0f));
       },
       nullptr,
       "NAV1 radial"},
//
//       // NAV1 signal strength — For Localisers, seems to be either 0 or 256
//       // For VORs varies from 0 to over 1,000,000 when really close!
//       {0x0C52, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C52");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "NAV1 signal strength"},

      // NAV1 bearing to VOR — In degrees (0-359), relative bearing
      {0x0C56, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/nav1_dir_degt");
         put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDataf(r) : 0.0f));
       },
       nullptr,
       "NAV1 relative bearing (deg)"},

      // NAV2 Loc Needle — -127 left to +127 right
      {0x0C59, 1,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h100 = XPLMFindDataRef("sim/cockpit2/radios/indicators/nav2_hdef_dots_pilot");
         put<int8_t>(dst, static_cast<int8_t>((r_h100 ? XPLMGetDataf(r_h100) : 0.0f) / 2.5f * 127.0f));
       },
       nullptr,
       "NAV2 lateral deflection"},
//
//       // NAV2 BC flags — Flags indicating VOR2 aspects as follows: (bit 0 =
//       // least sig) 0 = Back Course available 1 = Localiser tuned in 2 = On
//       // Back Course 7 = Station is active (set even if no BC available)
//       {0x0C5A, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C5A");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "NAV2 BC flags"},

      // NAV2 To/From Flag — 0=not active, 1=To, 2=From
      {0x0C5B, 1,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h101 = XPLMFindDataRef("sim/cockpit/radios/nav2_fromto");
         put<int8_t>(dst, static_cast<int8_t>((r_h101 ? XPLMGetDatai(r_h101) : 0)));
       },
       nullptr,
       "NAV2 from/to flag"},

      // NAV2 bearing to VOR — In degrees (0-359), relative bearing
      {0x0C5C, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/nav2_dir_degt");
         put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDataf(r) : 0.0f));
       },
       nullptr,
       "NAV2 relative bearing (deg)"},

      // NAV2 OBS (CRS) — In degrees
      {0x0C5E, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h102 = XPLMFindDataRef("sim/cockpit/radios/nav2_obs_degm");
         put<int16_t>(dst, static_cast<int16_t>((r_h102 ? XPLMGetDataf(r_h102) : 0.0f)));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h103 = XPLMFindDataRef("sim/cockpit/radios/nav2_obs_degm");
         if (r_h103)
           XPLMSetDataf(r_h103, static_cast<float>(take<int16_t>(src)));
       },
       "NAV2 OBS"},

      // NAV2 Radial
      {0x0C60, 2,
       // Read/Write: Read (only)
       // degrees Magnetic for a VOR, but TRUE for an ILS LOC.
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h104 = XPLMFindDataRef("sim/cockpit2/radios/indicators/nav2_bearing_deg_mag");
         float b = conv::wrap_heading((r_h104 ? XPLMGetDataf(r_h104) : 0.0f) - 180.0f);
         put<uint16_t>(dst, static_cast<uint16_t>(b / 360.0f * 65536.0f));
       },
       nullptr,
       "NAV2 radial"},
//
//       // NAV2 signal strength — For Localisers, seems to be either 0 or 256
//       // For VORs varies from 0 to over 1,000,000 when really close!
//       {0x0C62, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C62");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "NAV2 signal strength"},
//
//       // ADF Relative Bearing — Bearing to NDB realtive to heading (-ve left,
//       // +ve right)
//       {0x0C6A, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C6A");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ADF Relative Bearing"},
//
//       // ADF dial heading — Degrees 1-360
//       {0x0C6C, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C6C");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C6C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "ADF dial heading"},

      // NAV2 GS Needle (FS2002+) — -127 up to +127 down
      {0x0C6E, 1,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h105 = XPLMFindDataRef("sim/cockpit2/radios/indicators/nav2_vdef_dots_pilot");
         put<int8_t>(dst, static_cast<int8_t>((r_h105 ? XPLMGetDataf(r_h105) : 0.0f) / 2.5f * 127.0f));
       },
       nullptr,
       "NAV2 glideslope"},

      // NAV2 GS Active (FS2002+) — 1=GS being received
      {0x0C6F, 1,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h106 = XPLMFindDataRef("sim/cockpit/radios/nav2_CDI");
         put<int8_t>(dst, static_cast<int8_t>((r_h106 ? XPLMGetDatai(r_h106) : 0)));
       },
       nullptr,
       "NAV2 CDI flag"},
//
//       // NAV2 code — Bits used as follows: 0     DME available 1 TACAN 2
//       // Voice available 3       No signal available 4   DME transmitter at
//       // GS transmitter 5     No back course 6        GS available 7  This is
//       // a localiser (else it's a VOR)
//       {0x0C70, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C70");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "NAV2 code"},
//
//       // Inner Mkr Lat (FSX)
//       {0x1100, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1100");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Inner Mkr Lat (FSX)"},
//
//       // Inner Mkr Long (FSX)
//       {0x1104, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1104");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Inner Mkr Long (FSX)"},
//
//       // Inner Mkr Elevation (FSX)
//       {0x1108, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1108");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Inner Mkr Elevation (FSX)"},
//
//       // Middle Mkr Lat (FSX)
//       {0x110C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x110C");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Middle Mkr Lat (FSX)"},
//
//       // Middle Mkr Long (FSX)
//       {0x1110, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1110");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Middle Mkr Long (FSX)"},
//
//       // Middle Mkr Elevation (FSX)
//       {0x1114, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1114");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Middle Mkr Elevation (FSX)"},
//
//       // Outer Mkr Lat (FSX)
//       {0x1118, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1118");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Outer Mkr Lat (FSX)"},
//
//       // Outer Mkr Long (FSX)
//       {0x111C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x111C");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Outer Mkr Long (FSX)"},
//
//       // Outer Mkr Elevation (FSX)
//       {0x1120, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1120");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Outer Mkr Elevation (FSX)"},
//
//       // ADF1 Lat (FSX)
//       {0x1124, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1124");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ADF1 Lat (FSX)"},
//
//       // ADF1 Long (FSX)
//       {0x1128, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1128");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ADF1 Long (FSX)"},
//
//       // ADF1 Elevation (FSX)
//       {0x112C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x112C");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ADF1 Elevation (FSX)"},
//
//       // ADF2 Lat (FSX)
//       {0x1130, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1130");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ADF2 Lat (FSX)"},
//
//       // ADF2 Long (FSX)
//       {0x1134, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1134");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ADF2 Long (FSX)"},
//
//       // ADF2 Elevation (FSX)
//       {0x1138, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1138");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ADF2 Elevation (FSX)"},
//
//       // GPS/NAV switch [FS2000+] — =0 NAV, =1 GPS
//       {0x132C, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x132C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x132C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "GPS/NAV switch [FS2000+]"},

      // VOR1 Localiser needle
      {0x2AAC, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/nav1_hdef_dot");
         float dots = r ? XPLMGetDataf(r) : 0.0f;
         put<float>(dst, dots / 2.5f * 127.0f);
       },
       nullptr,
       "NAV1 CDI (float, -127..+127)"},

      // VOR1 Glideslope needle
      {0x2AB0, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/nav1_vdef_dot");
         float dots = r ? XPLMGetDataf(r) : 0.0f;
         put<float>(dst, dots / 2.5f * 127.0f);
       },
       nullptr,
       "NAV1 GS (float, -127..+127)"},

      // VOR2 Localiser needle
      {0x2AB4, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/nav2_hdef_dot");
         float dots = r ? XPLMGetDataf(r) : 0.0f;
         put<float>(dst, dots / 2.5f * 127.0f);
       },
       nullptr,
       "NAV2 CDI (float, -127..+127)"},

      // VOR2 Glideslope needle
      {0x2AB8, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/nav2_vdef_dot");
         float dots = r ? XPLMGetDataf(r) : 0.0f;
         put<float>(dst, dots / 2.5f * 127.0f);
       },
       nullptr,
       "NAV2 GS (float, -127..+127)"},
//
//       // HSI CDI needle — The HSI CDI needle deflection, range -127.0 to
//       // +127.0, corresponding to -10 to +10 degrees for a VOR, -2.5 to +2.5
//       // for a LOC.
//       {0x2F88, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2F88");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "HSI CDI needle"},
//
//       // HSI GSI needle — The HSI CDI needle deflection, range -119.0 to
//       // +119.0, corresponding to -0.7 to +0.7 degrees
//       {0x2F90, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2F90");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "HSI GSI needle"},
//
//       // HSI speed indication (metres/sec) — -1 if invalid
//       {0x2F98, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2F98");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "HSI speed indication (metres/sec)"},
//
//       // HSI distance indication (metres) — -1 if invalid
//       {0x2FA0, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2FA0");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "HSI distance indication (metres)"},
//
//       // HSI bearing (degrees 0-360)
//       {0x2FA8, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2FA8");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "HSI bearing (degrees 0-360)"},
//
//       // HSI CDI valid flag
//       {0x2FAA, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2FAA");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "HSI CDI valid flag"},
//
//       // HSI GSI valid flag
//       {0x2FAB, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2FAB");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "HSI GSI valid flag"},
//
//       // HSI bearing valid flag
//       {0x2FAC, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2FAC");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "HSI bearing valid flag"},
//
//       // HSI To/From flag — 0=off, 1=to, 2 = from
//       {0x2FAD, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2FAD");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "HSI To/From flag"},
//
//       // HSI has LOC flag
//       {0x2FAE, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2FAE");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "HSI has LOC flag"},
//
//       // HSI station ID
//       {0x2FB0, 6,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2FB0");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 6);
//          dst[0] = 0;
//        },
//        nullptr,
//        "HSI station ID"},
//
//       // Modules/Add-ons menu, app's item string — 32-byte area for app's to
//       // supply text for Modules menu entry (Add-ons menu in FSX).
//       {0x2FE0, 1,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2FE0");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Modules/Add-ons menu, app's item string"},

      // VOR1 identity — ID string, up to 6 chars incl zero terminator
      {0x3000, 6,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         auto s = find_nav_station(dref, "sim/cockpit/radios/nav1_freq_hz", NAV_VOR_ILS_DME);
         std::memcpy(dst, s.id, 6);
       },
       nullptr,
       "NAV1 station ID"},

      // VOR1 name — Name string, up to 25 chars incl zero terminator
      {0x3006, 25,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         auto s = find_nav_station(dref, "sim/cockpit/radios/nav1_freq_hz", NAV_VOR_ILS_DME);
         write_cstr(dst, 25, s.name);
       },
       nullptr,
       "NAV1 station name"},

      // VOR2 identity — ID string, up to 6 chars incl zero terminator
      {0x301F, 6,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         auto s = find_nav_station(dref, "sim/cockpit/radios/nav2_freq_hz", NAV_VOR_ILS_DME);
         std::memcpy(dst, s.id, 6);
       },
       nullptr,
       "NAV2 station ID"},

      // VOR2 name — Name string, up to 25 chars incl zero terminator
      {0x3025, 25,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         auto s = find_nav_station(dref, "sim/cockpit/radios/nav2_freq_hz", NAV_VOR_ILS_DME);
         write_cstr(dst, 25, s.name);
       },
       nullptr,
       "NAV2 station name"},

      // NDB identity — ID string, up to 6 chars incl zero terminator
      {0x303E, 6,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         auto s = find_nav_station(dref, "sim/cockpit/radios/adf1_freq_hz", NAV_NDB);
         std::memcpy(dst, s.id, 6);
       },
       nullptr,
       "ADF1 station ID"},

      // NDB name — Name string, up to 25 chars incl zero terminator
      {0x3044, 25,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         auto s = find_nav_station(dref, "sim/cockpit/radios/adf1_freq_hz", NAV_NDB);
         write_cstr(dst, 25, s.name);
       },
       nullptr,
       "ADF1 station name"},
//
//       // VOR1 morse ID switch — 0=off, 1=on
//       {0x3105, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3105");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3105");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "VOR1 morse ID switch"},
//
//       // VOR2 morse ID switch — 0=off, 1=on
//       {0x3106, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3106");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3106");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "VOR2 morse ID switch"},
//
//       // NDB morse ID switch — 0=off, 1=on
//       {0x3107, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3107");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3107");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "NDB morse ID switch"},

      // COM2 freq (FS2002+) — Frequency shown as BCD (Binary Coded Decimal),
      // however the prefixed "1" is removed
      {0x3118, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h121 = XPLMFindDataRef("sim/cockpit/radios/com2_freq_hz");
         put<int16_t>(dst, conv::to_bcd((r_h121 ? XPLMGetDatai(r_h121) : 0) - 10000));
       },
       nullptr,
       "COM2 frequency (BCD)"},

      // COM1 STBY freq (FS2002+) — Frequency shown as BCD (Binary Coded
      // Decimal), however the prefixed "1" is removed
      {0x311A, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/com1_stdby_freq_hz");
         put<int16_t>(dst, conv::to_bcd((r ? XPLMGetDatai(r) : 0) - 10000));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/com1_stdby_freq_hz");
         if (r)
           XPLMSetDatai(r, from_bcd(take<uint16_t>(src)) + 10000);
       },
       "COM1 standby frequency (BCD)"},

      // COM2 STBY freq (FS2002+) — Frequency shown as BCD (Binary Coded
      // Decimal), however the prefixed "1" is removed
      {0x311C, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/com2_stdby_freq_hz");
         put<int16_t>(dst, conv::to_bcd((r ? XPLMGetDatai(r) : 0) - 10000));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/com2_stdby_freq_hz");
         if (r)
           XPLMSetDatai(r, from_bcd(take<uint16_t>(src)) + 10000);
       },
       "COM2 standby frequency (BCD)"},

      // NAV1 STBY freq (FS2002+) — Frequency shown as BCD (Binary Coded
      // Decimal), however the prefixed "1" is removed
      {0x311E, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/nav1_stdby_freq_hz");
         put<int16_t>(dst, conv::to_bcd((r ? XPLMGetDatai(r) : 0) - 10000));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/nav1_stdby_freq_hz");
         if (r)
           XPLMSetDatai(r, from_bcd(take<uint16_t>(src)) + 10000);
       },
       "NAV1 standby frequency (BCD)"},

      // NAV2 STBY freq (FS2002+) — Frequency shown as BCD (Binary Coded
      // Decimal), however the prefixed "1" is removed
      {0x3120, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/nav2_stdby_freq_hz");
         put<int16_t>(dst, conv::to_bcd((r ? XPLMGetDatai(r) : 0) - 10000));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/radios/nav2_stdby_freq_hz");
         if (r)
           XPLMSetDatai(r, from_bcd(take<uint16_t>(src)) + 10000);
       },
       "NAV2 standby frequency (BCD)"},

      // Radio sound select switches (FS2002+) — Bits allocated as follows:
      {0x3122, 1,
       // Read/Write: Read/Write
       // 3=NAV2, 4=ADF1, 5=DME, 6=Marker
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_com1 = XPLMFindDataRef("sim/cockpit2/radios/actuators/audio_selection_com1");
         static XPLMDataRef r_com2 = XPLMFindDataRef("sim/cockpit2/radios/actuators/audio_selection_com2");
         static XPLMDataRef r_nav1 = XPLMFindDataRef("sim/cockpit2/radios/actuators/audio_selection_nav1");
         static XPLMDataRef r_nav2 = XPLMFindDataRef("sim/cockpit2/radios/actuators/audio_selection_nav2");
         static XPLMDataRef r_adf1 = XPLMFindDataRef("sim/cockpit2/radios/actuators/audio_selection_adf1");
         static XPLMDataRef r_dme = XPLMFindDataRef("sim/cockpit2/radios/actuators/audio_dme_enabled");
         static XPLMDataRef r_mkr = XPLMFindDataRef("sim/cockpit2/radios/actuators/audio_marker_enabled");
         uint8_t v = 0;
         if (r_com1 && XPLMGetDatai(r_com1))
           v |= (1 << 0);
         if (r_com2 && XPLMGetDatai(r_com2))
           v |= (1 << 1);
         if (r_nav1 && XPLMGetDatai(r_nav1))
           v |= (1 << 2);
         if (r_nav2 && XPLMGetDatai(r_nav2))
           v |= (1 << 3);
         if (r_adf1 && XPLMGetDatai(r_adf1))
           v |= (1 << 4);
         if (r_dme && XPLMGetDatai(r_dme))
           v |= (1 << 5);
         if (r_mkr && XPLMGetDatai(r_mkr))
           v |= (1 << 6);
         put<uint8_t>(dst, v);
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         const uint8_t v = take<uint8_t>(src);
         static XPLMDataRef r_com1 = XPLMFindDataRef("sim/cockpit2/radios/actuators/audio_selection_com1");
         static XPLMDataRef r_com2 = XPLMFindDataRef("sim/cockpit2/radios/actuators/audio_selection_com2");
         static XPLMDataRef r_nav1 = XPLMFindDataRef("sim/cockpit2/radios/actuators/audio_selection_nav1");
         static XPLMDataRef r_nav2 = XPLMFindDataRef("sim/cockpit2/radios/actuators/audio_selection_nav2");
         static XPLMDataRef r_adf1 = XPLMFindDataRef("sim/cockpit2/radios/actuators/audio_selection_adf1");
         static XPLMDataRef r_dme = XPLMFindDataRef("sim/cockpit2/radios/actuators/audio_dme_enabled");
         static XPLMDataRef r_mkr = XPLMFindDataRef("sim/cockpit2/radios/actuators/audio_marker_enabled");
         if (r_com1)
           XPLMSetDatai(r_com1, (v >> 0) & 1);
         if (r_com2)
           XPLMSetDatai(r_com2, (v >> 1) & 1);
         if (r_nav1)
           XPLMSetDatai(r_nav1, (v >> 2) & 1);
         if (r_nav2)
           XPLMSetDatai(r_nav2, (v >> 3) & 1);
         if (r_adf1)
           XPLMSetDatai(r_adf1, (v >> 4) & 1);
         if (r_dme)
           XPLMSetDatai(r_dme, (v >> 5) & 1);
         if (r_mkr)
           XPLMSetDatai(r_mkr, (v >> 6) & 1);
       },
       "Radio audio switches (bit 0=COM1..6=Marker)"},
//
//       // Radio swap controls (FS2002+) — Write 1 to specific bits to swap
//       // use/standby frequencies:
//       {0x3123, 1,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3123");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Radio swap controls (FS2002+)"},

      // Navaid status flags — Bits set as follows: (bit 0 = Least SDig) 1 =
      // good NAV1 signal 2 = good NAV2 signal 3 = good ADF signal 4 = NAV1
      // has DME 5 = NAV2 has DME 6 = NAV1 is an ILS 7 = AP NAV1 radial
      // acquired 8 = AP ILS LOC acquired (see 10) 9 = AP ILS GS acquired
      // 10=LOC is BC 11=ADF2 signal ok, 12=NAV2 is ILS
      {0x3300, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         int16_t flags = 0;
         static XPLMDataRef r_h123 = XPLMFindDataRef("sim/cockpit/radios/nav_type");
         int _iv123 = 0;
         if (r_h123)
           XPLMGetDatavi(r_h123, &_iv123, 0, 1);
         if (_iv123 != 0)
           flags |= 2;
         static XPLMDataRef r_h124 = XPLMFindDataRef("sim/cockpit/radios/nav_type");
         int _iv124 = 0;
         if (r_h124)
           XPLMGetDatavi(r_h124, &_iv124, 1, 1);
         if (_iv124 != 0)
           flags |= 4;
         static XPLMDataRef r_h125 = XPLMFindDataRef("sim/cockpit/radios/nav_type");
         int _iv125 = 0;
         if (r_h125)
           XPLMGetDatavi(r_h125, &_iv125, 2, 1);
         if (_iv125 != 0)
           flags |= 8;
         static XPLMDataRef r_h126 = XPLMFindDataRef("sim/cockpit/radios/nav1_has_dme");
         if ((r_h126 ? XPLMGetDatai(r_h126) : 0) != 0)
           flags |= 16;
         static XPLMDataRef r_h127 = XPLMFindDataRef("sim/cockpit/radios/nav2_has_dme");
         if ((r_h127 ? XPLMGetDatai(r_h127) : 0) != 0)
           flags |= 32;
         static XPLMDataRef r_h128 = XPLMFindDataRef("sim/cockpit/radios/nav_type");
         int _iv128 = 0;
         if (r_h128)
           XPLMGetDatavi(r_h128, &_iv128, 0, 1);
         if (_iv128 == 4)
           flags |= 64;
         static XPLMDataRef r_h129 = XPLMFindDataRef("sim/cockpit/radios/nav_type");
         int _iv129 = 0;
         if (r_h129)
           XPLMGetDatavi(r_h129, &_iv129, 3, 1);
         if (_iv129 != 0)
           flags |= 2048;
         static XPLMDataRef r_h130 = XPLMFindDataRef("sim/cockpit/radios/nav_type");
         int _iv130 = 0;
         if (r_h130)
           XPLMGetDatavi(r_h130, &_iv130, 1, 1);
         if (_iv130 == 4)
           flags |= 4096;
         put<int16_t>(dst, flags);
       },
       nullptr,
       "Radio status flags"},
//
//       // FS2004 GPS data area -- see SDK
//       {0x6000, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6000");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS data area -- see SDK"},
//
//       // FS2004 GPS flags
//       {0x6004, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6004");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS flags"},
//
//       // FS2004 GPS unknown progress flags?
//       {0x6008, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6008");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS unknown progress flags?"},
//
//       // FS2004 GPS Zulu time in secs since midnight
//       {0x600C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x600C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Zulu time in secs since midnight"},
//
//       // FS2004 GPS Latitude in degrees — -ve = South
//       {0x6010, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6010");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Latitude in degrees"},
//
//       // FS2004 GPS Longitude in degrees — -ve = West
//       {0x6018, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6018");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Longitude in degrees"},
//
//       // FS2004 GPS Altitude — metres
//       {0x6020, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6020");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Altitude"},
//
//       // FS2004 GPS Mag Var — radians (subtract from True for Mag headings)
//       {0x6028, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6028");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Mag Var"},
//
//       // FS2004 GPS Ground Speed — metres/sec
//       {0x6030, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6030");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Ground Speed"},
//
//       // FS2004 GPS True Heading — radians
//       {0x6038, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6038");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS True Heading"},
//
//       // FS2004 GPS Mag Track — radians
//       {0x6040, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6040");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Mag Track"},
//
//       // FS2004 GPS Distance to next WP — metres
//       {0x6048, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6048");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Distance to next WP"},
//
//       // FS2004 GPS Mag bearing to next WP — radians
//       {0x6050, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6050");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Mag bearing to next WP"},
//
//       // FS2004 GPS Cross track error — metres
//       {0x6058, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6058");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Cross track error"},
//
//       // FS2004 GPS Required true heading — radians
//       {0x6060, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6060");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Required true heading"},
//
//       // FS2004 GPS Track error — radians
//       {0x6068, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6068");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Track error"},
//
//       // FS2004 GPS Vertical speed — ?
//       {0x6078, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6078");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Vertical speed"},
//
//       // FS2004 GPS Prev WP valid flag
//       {0x6080, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6080");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Prev WP valid flag"},
//
//       // FS2004 GPS Prev WP ID string — 6 characters?
//       {0x6081, 6,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6081");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 6);
//          dst[0] = 0;
//        },
//        nullptr,
//        "FS2004 GPS Prev WP ID string"},
//
//       // FS2004 GPS Prev WP latitude
//       {0x608C, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x608C");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Prev WP latitude"},
//
//       // FS2004 GPS Prev WP longitude
//       {0x6094, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6094");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Prev WP longitude"},
//
//       // FS2004 GPS Prev WP aircraft altitude — metres
//       {0x609C, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x609C");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Prev WP aircraft altitude"},
//
//       // FS2004 GPS Next WP ID string — 6 characters?
//       {0x60A4, 6,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x60A4");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 6);
//          dst[0] = 0;
//        },
//        nullptr,
//        "FS2004 GPS Next WP ID string"},
//
//       // FS2004 GPS Next WP latitude
//       {0x60AC, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x60AC");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Next WP latitude"},
//
//       // FS2004 GPS Next WP longitude
//       {0x60B4, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x60B4");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Next WP longitude"},
//
//       // FS2004 GPS Next WP aircraft altitude — metres
//       {0x60BC, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x60BC");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Next WP aircraft altitude"},
//
//       // FS2004 GPS Next WP ETE in secs
//       {0x60E4, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x60E4");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Next WP ETE in secs"},
//
//       // FS2004 GPS Next WP ETA in secs, local time?
//       {0x60E8, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x60E8");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Next WP ETA in secs, local time?"},
//
//       // FS2004 GPS Next WP distance — metres
//       {0x60EC, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x60EC");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Next WP distance"},
//
//       // FS2004 GPS Distance prev to next WP — metres
//       {0x60F4, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x60F4");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Distance prev to next WP"},
//
//       // FS2004 GPS Approach mode no. (?)
//       {0x60FC, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x60FC");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Approach mode no. (?)"},
//
//       // FS2004 GPS Approach WP type (?)
//       {0x6100, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6100");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Approach WP type (?)"},
//
//       // FS2004 GPS Approach Segment type (?)
//       {0x6104, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6104");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Approach Segment type (?)"},
//
//       // FS2004 GPS Approach mode flag — Indicates approaching WP is the
//       // runway (?)
//       {0x6108, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6108");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Approach mode flag"},
//
//       // FS2004 GPS Course to set (CTS) — radians
//       {0x610C, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x610C");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Course to set (CTS)"},
//
//       // FS2004 GPS Total no. of WPs in plan
//       {0x6120, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6120");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Total no. of WPs in plan"},
//
//       // FS2004 GPS Approach WP count (?)
//       {0x6128, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6128");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Approach WP count (?)"},
//
//       // FS2004 GPS Destination airport ID — 5 chars
//       {0x6137, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6137");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Destination airport ID"},
//
//       // FS2004 GPS Approach name string — 8 chars
//       {0x6140, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6140");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Approach name string"},
//
//       // FS2004 GPS Approach transition index (?) — -1 = invalid
//       {0x6150, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6150");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Approach transition index (?)"},
//
//       // FS2004 GPS Approach transition name — 8 chars
//       {0x6154, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6154");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Approach transition name"},
//
//       // FS2004 GPS Approach type (?)
//       {0x6160, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6160");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Approach type (?)"},
//
//       // FS2004 GPS Approach time zone deviation (?)
//       {0x6168, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6168");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Approach time zone deviation (?)"},
//
//       // FS2004 GPS Current WP index — counting from 1
//       {0x616C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x616C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Current WP index"},
//
//       // FS2004 GPS Approach current WP index (?)
//       {0x6170, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6170");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Approach current WP index (?)"},
//
//       // FS2004 GPS unknown
//       {0x6178, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6178");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS unknown"},
//
//       // FS2004 GPS unknown
//       {0x6180, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6180");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS unknown"},
//
//       // FS2004 GPS unknown
//       {0x6188, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6188");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS unknown"},
//
//       // FS2004 GPS Time last WP crossed — Seconds since Zulu midnight
//       {0x6190, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6190");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Time last WP crossed"},
//
//       // FS2004 GPS Dest ETE in secs
//       {0x6198, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6198");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Dest ETE in secs"},
//
//       // FS2004 GPS Dest ETA in secs, local time ?
//       {0x619C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x619C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Dest ETA in secs, local time ?"},
//
//       // FS2004 GPS Route total distance — metres
//       {0x61A0, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x61A0");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Route total distance"},
//
//       // FS2004 GPS Est fuel burn, US gals
//       {0x61A8, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x61A8");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "FS2004 GPS Est fuel burn, US gals"},
//
//       // FS2004 GPS Time of last upd to 61B8 — Seconds since Zulu midnight
//       {0x61B0, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x61B0");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Time of last upd to 61B8"},
//
//       // FS2004 GPS Count updated every 5 secs
//       {0x61B8, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x61B8");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 GPS Count updated every 5 secs"},

  }; // end table
  return table;
}
