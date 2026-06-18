// SPDX-License-Identifier: LGPL-3.0-or-later
// fsuipc_offsets/Pos./Attitude.h — Production offset table
//
// 65 total offsets in this category
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

inline const std::vector<OffsetEntry> &fsuipc_offset_table_pos_attitude()
{
  static const std::vector<OffsetEntry> table = {

      {0x0020, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h0 = XPLMFindDataRef("sim/flightmodel/position/elevation");
         double msl = (r_h0 ? XPLMGetDatad(r_h0) : 0.0);
         static XPLMDataRef r_h1 = XPLMFindDataRef("sim/flightmodel/position/y_agl");
         float agl = (r_h1 ? XPLMGetDataf(r_h1) : 0.0f);
         put<int32_t>(dst, static_cast<int32_t>((msl - agl) * 256.0f));
       },
       nullptr,
       "Ground elevation (m*256)"},

      // MagVar — -ve is West, +ve East. Convert Mag to True by adding this,
      // True to Mag by subracting it.
      {0x02A0, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h10 = XPLMFindDataRef("sim/flightmodel/position/magnetic_variation");
         float mv = (r_h10 ? XPLMGetDataf(r_h10) : 0.0f);
         put<int16_t>(dst, static_cast<int16_t>(-(mv / 360.0f * 65536.0f)));
       },
       nullptr,
       "Magnetic variation"},

      // Ground Speed — (Metres/sec) * 65536. Not valid in Slew mode!
      {0x02B4, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h11 = XPLMFindDataRef("sim/flightmodel/position/groundspeed");
         put<uint32_t>(dst, static_cast<uint32_t>((r_h11 ? XPLMGetDataf(r_h11) : 0.0f) * 65536.0f));
       },
       nullptr,
       "Ground speed (m/s*65536)"},

      // True Air Speed — Knots * 128
      {0x02B8, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h12 = XPLMFindDataRef("sim/flightmodel/position/true_airspeed");
         float tas = conv::meters_to_knots((r_h12 ? XPLMGetDataf(r_h12) : 0.0f)) * 128.0f;
         put<uint32_t>(dst, static_cast<uint32_t>(tas));
       },
       nullptr,
       "True airspeed (kts*128)"},

      // Indicated Air Speed — Knots * 128
      {0x02BC, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h13 = XPLMFindDataRef("sim/flightmodel/position/indicated_airspeed");
         put<int32_t>(dst, static_cast<int32_t>((r_h13 ? XPLMGetDataf(r_h13) : 0.0f) * 128.0f));
       },
       nullptr,
       "Indicated airspeed (kts*128)"},

      // Barber pole airspeed — Knots * 128
      {0x02C4, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/aircraft/view/acf_Vne");
         put<int32_t>(dst, static_cast<int32_t>((r ? XPLMGetDataf(r) : 0.0f) * 128.0f));
       },
       nullptr,
       "Barber pole airspeed (kts*128)"},

      // Vertical speed — VSI / 256 = VS per sec (in meters)
      {0x02C8, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h14 = XPLMFindDataRef("sim/cockpit2/gauges/indicators/vvi_fpm_pilot");
         float vs = (r_h14 ? XPLMGetDataf(r_h14) : 0.0f);
         put<int32_t>(dst, static_cast<int32_t>(vs / 60.0f / 3.28084f * 256.0f));
       },
       nullptr,
       "Vertical speed"},
//
//       // Whiskey Compass — Degrees
//       {0x02CC, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x02CC");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Whiskey Compass"},
//
//       // Vertical speed at touchdown — VSI / 256 = VS per sec (in meters)
//       {0x030C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x030C");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Vertical speed at touchdown"},

      // Plane on ground — 0=Airborne, 1=On Ground (NB not changed in Slew
      // mode)
      {0x0366, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h29 = XPLMFindDataRef("sim/flightmodel/failures/onground_any");
         put<int16_t>(dst, r_h29 ? static_cast<int16_t>(XPLMGetDatai(r_h29)) : int16_t(0));
       },
       nullptr,
       "On ground flag (any gear)"},

      // Stall Warning — 0=Inactive, 1=Stalling
      {0x036C, 1,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/failures/stallwarning");
         put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
       },
       nullptr,
       "Stall warning"},
//
//       // Overspeed Warning — 0=Inactive, 1=Overspeeding
//       {0x036D, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x036D");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Overspeed Warning"},
//
//       // Initial position with airSpeed [FSX] — Write airspeed here (together
//       // with the next fields for on-ground and
//       // Lat/Lon/Alt/Pitch/Bank/heading (LLAPBH) to set the user aircraft
//       // flying at that airspeed at that position.
//       {0x0558, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0558");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Initial position with airSpeed [FSX]"},
//
//       // Initial position set [FSX] — Write 0 or 1 here -- 0 for "in air" 1
//       // for "on ground" -- together with the next fields for
//       // Lat/Lon/Alt/Pitch/Bank/heading (LLAPBH) to set the user aircraft
//       // either on the ground with zero airspeed or flying with its current
//       // airspeed at that position.
//       {0x055C, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x055C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Initial position set [FSX]"},

      // Latitude of aircraft — -ve for South, +ve for North. See expression
      // for conversion.
      {0x0560, 8,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h30 = XPLMFindDataRef("sim/flightmodel/position/latitude");
         double lat = (r_h30 ? XPLMGetDatad(r_h30) : 0.0);
         put<int64_t>(dst, static_cast<int64_t>(lat * conv::FSUIPC_LAT_SCALE));
       },
       nullptr,
       "Latitude (64-bit FS units)"},

      // Longitude of aircraft — -ve for West, +ve for East. See expression
      // for conversion.
      {0x0568, 8,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h32 = XPLMFindDataRef("sim/flightmodel/position/longitude");
         double lon = (r_h32 ? XPLMGetDatad(r_h32) : 0.0);
         put<int64_t>(dst, static_cast<int64_t>(lon * conv::FSUIPC_LON_SCALE));
       },
       nullptr,
       "Longitude (64-bit FS units)"},

      // Altitude of aircraft — AGL. Can be written to move aircraft: in
      // FS2002 only in slew or pause states
      {0x0570, 8,
       // Read/Write: Read/Write
       // high 32-bit integer (at 0574) and the fractional part is in the low
       // 32-bit  integer  (at  0570).  [Can  be  written  to  move  aircraft:  in
       // FS2002 only in slew or pause states]
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h34 = XPLMFindDataRef("sim/flightmodel/position/elevation");
         double elev = (r_h34 ? XPLMGetDatad(r_h34) : 0.0);
         put<int64_t>(dst, static_cast<int64_t>(elev * conv::FSUIPC_360_32));
       },
       nullptr,
       "Altitude (m * 2^32)"},

      // Pitch — 0=level, -ve=pictch up, +ve=pitch down, degrees. (Only
      // settable in Slew mode except in FS2004)
      {0x0578, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h35 = XPLMFindDataRef("sim/flightmodel/position/theta");
         float p = (r_h35 ? XPLMGetDataf(r_h35) : 0.0f);
         put<int32_t>(dst, -static_cast<int32_t>(p / 360.0f * conv::FSUIPC_360_32));
       },
       nullptr,
       "Pitch angle"},

      // Bank — -ve right bank, +ve left bank. Only settable in slew mode
      // except in FS2004
      {0x057C, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h36 = XPLMFindDataRef("sim/flightmodel/position/phi");
         float b = (r_h36 ? XPLMGetDataf(r_h36) : 0.0f);
         put<int32_t>(dst, -static_cast<int32_t>(b / 360.0f * conv::FSUIPC_360_32));
       },
       nullptr,
       "Bank angle"},

      // Heading — Slew-mode needs to be active to set heading except in
      // FS2004
      {0x0580, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h37 = XPLMFindDataRef("sim/flightmodel/position/psi");
         double h = (r_h37 ? XPLMGetDataf(r_h37) : 0.0f);
         put<uint32_t>(dst, static_cast<uint32_t>(h / 360.0 * conv::FSUIPC_360_32));
       },
       nullptr,
       "Heading"},
//
//       // LLAPBH updated flags — Bits indicating which of LLAPBH (offsets
//       // 0560-0580) were changed at the time in offset 0588.
//       {0x0584, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0584");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "LLAPBH updated flags"},
//
//       // LLAPBH updated time — Elapsed time, in seconds, when LLAPBH last
//       // changed. See also offset 0584.
//       {0x0588, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0588");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "LLAPBH updated time"},
//
//       // Viewpoint Latitude — -ve for South, +ve for North. See expression
//       // for conversion.
//       {0x05B0, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05B0");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Viewpoint Latitude"},
//
//       // Viewpoint Longitude — -ve for West, +ve for East. See expression for
//       // conversion.
//       {0x05B8, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05B8");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Viewpoint Longitude"},
//
//       // Viewpoint Altitude — This is read only and seems to relate to the
//       // position of the viewer whether in cockpit, tower or spot views
//       {0x05C0, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05C0");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Viewpoint Altitude"},
//
//       // Viewpoint pitch — 0=level, -ve=pictch up, +ve=pitch down, degrees.
//       {0x05C8, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05C8");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Viewpoint pitch"},
//
//       // Viewpoint bank — 0=level, -ve=right, +ve=left, degrees.
//       {0x05CC, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05CC");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Viewpoint bank"},
//
//       // View direction (TRUE)
//       {0x05D0, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05D0");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "View direction (TRUE)"},

      // Vertical speed — Metres per minute, but -ve for up. Okay in slew
      // mode except in FS2002
      {0x0842, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Vertical speed in metres per minute, –ve for UP, +ve for DOWN
         static XPLMDataRef r_h112 = XPLMFindDataRef("sim/cockpit2/gauges/indicators/vvi_fpm_pilot");
         float vs_fpm = (r_h112 ? XPLMGetDataf(r_h112) : 0.0f);
         float vs_mpm = vs_fpm / 3.28084f;
         put<int16_t>(dst, static_cast<int16_t>(-vs_mpm));
       },
       nullptr,
       "Vertical speed (m/min, -ve=up)"},
//
//       // G-Force (FSX)
//       {0x1140, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1140");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "G-Force (FSX)"},
//
//       // AOA (Angle Of Attack) — Result is % of maximum AofA for this
//       // aircraft
//       {0x11BE, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x11BE");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AOA (Angle Of Attack)"},

      // Mach speed
      {0x11C6, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h114 = XPLMFindDataRef("sim/flightmodel/misc/machno");
         put<int16_t>(dst, static_cast<int16_t>((r_h114 ? XPLMGetDataf(r_h114) : 0.0f) * 20480.0f));
       },
       nullptr,
       "Mach number (*20480)"},
//
//       // X (Lateral) Acceleration [FS2000+] — Right/left relative to body
//       // axes, in ft/sec/sec
//       {0x3060, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3060");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3060");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "X (Lateral) Acceleration [FS2000+]"},
//
//       // Y (Vertical) Acceleration [FS2000+] — Up/down relative to body axes,
//       // in ft/sec/sec
//       {0x3068, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3068");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3068");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Y (Vertical) Acceleration [FS2000+]"},
//
//       // Z (Longitudinal) Acceleration [FS2000+] — Foward/backward relative
//       // to body axes, in ft/sec/sec
//       {0x3070, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3070");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3070");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Z (Longitudinal) Acceleration [FS2000+]"},
//
//       // Pitch Acceleration [FS2000+] — Relative to body axes, in
//       // rads/sec/sec
//       {0x3078, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3078");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3078");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Pitch Acceleration [FS2000+]"},
//
//       // Roll Acceleration [FS2000+] — Relative to body axes, in rads/sec/sec
//       {0x3080, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3080");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3080");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Roll Acceleration [FS2000+]"},
//
//       // Yaw Acceleration [FS2000+] — Relative to body axes, in rads/sec/sec
//       {0x3088, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3088");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3088");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Yaw Acceleration [FS2000+]"},
//
//       // Z (Longitudinal) GS-velocity [FS2000+] — Forward/backward relative
//       // to body axes, in ft/sec
//       {0x3090, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3090");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3090");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Z (Longitudinal) GS-velocity [FS2000+]"},
//
//       // X (Lateral) GS-velocity [FS2000+] — Right/left relative to body
//       // axes, in ft/sec
//       {0x3098, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3098");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3098");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "X (Lateral) GS-velocity [FS2000+]"},
//
//       // Y (Vertical) GS-velocity [FS2000+] — Up/down relative to body axes,
//       // in ft/sec
//       {0x30A0, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x30A0");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x30A0");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Y (Vertical) GS-velocity [FS2000+]"},

      // Pitch Velocity [FS2000+] — Relative to body axes, in rads/sec
      {0x30A8, 8,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/position/Qrad");
         put<double>(dst, static_cast<double>(r ? XPLMGetDataf(r) : 0.0f));
       },
       nullptr,
       "Pitch rate body (rad/sec, double)"},

      // Roll Velocity [FS2000+] — Relative to body axes, in rads/sec
      {0x30B0, 8,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/position/Prad");
         put<double>(dst, static_cast<double>(r ? XPLMGetDataf(r) : 0.0f));
       },
       nullptr,
       "Roll rate body (rad/sec, double)"},

      // Yaw Velocity [FS2000+] — Relative to body axes, in rads/sec
      {0x30B8, 8,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/position/Rrad");
         put<double>(dst, static_cast<double>(r ? XPLMGetDataf(r) : 0.0f));
       },
       nullptr,
       "Yaw rate body (rad/sec, double)"},
//
//       // Vertical acceleration [FS2000 only] — FS2k only. Acceleration is in
//       // G's
//       {0x30D0, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x30D0");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Vertical acceleration [FS2000 only]"},
//
//       // Z (Longitudinal) TAS-vel body axes (FS2000+) — Body axes, ft/sec
//       {0x3178, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3178");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3178");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Z (Longitudinal) TAS-vel body axes (FS2000+)"},
//
//       // X (Lateral) TAS-vel body axes (FS2000+) — Body axes, ft/sec
//       {0x3180, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3180");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3180");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "X (Lateral) TAS-vel body axes (FS2000+)"},
//
//       // Y (Vertical) TAS-vel body axes (FS2000+) — Body axes, ft/sec
//       {0x3188, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3188");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3188");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Y (Vertical) TAS-vel body axes (FS2000+)"},
//
//       // Z (Longitudinal) GS-vel world axes (FS2000+) — World axes, ft/sec
//       {0x3190, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3190");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3190");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Z (Longitudinal) GS-vel world axes (FS2000+)"},
//
//       // X (Lateral) GS-vel world axes (FS2000+) — World axes, ft/sec
//       {0x3198, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3198");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3198");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "X (Lateral) GS-vel world axes (FS2000+)"},

      // Y (Vertical) GS-vel world axes (FS2000+) — World axes, ft/sec
      {0x31A0, 8,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/position/vh_ind_fpm");
         float fpm = r ? XPLMGetDataf(r) : 0.0f;
         put<double>(dst, static_cast<double>(fpm / 60.0f));
       },
       nullptr,
       "Vertical speed world (ft/sec, double)"},

      // Pitch vel world axes (FS2000+) — World axes, rads/sec
      {0x31A8, 8,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/position/Qrad");
         put<double>(dst, static_cast<double>(r ? XPLMGetDataf(r) : 0.0f));
       },
       nullptr,
       "Pitch rate world (rad/sec, double)"},

      // Roll vel world axes (FS2000+) — World axes, rads/sec
      {0x31B0, 8,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/position/Prad");
         put<double>(dst, static_cast<double>(r ? XPLMGetDataf(r) : 0.0f));
       },
       nullptr,
       "Roll rate world (rad/sec, double)"},
//
//       // Yaw vel world axes (FS2000+) — World axes, rads/sec
//       {0x31B8, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31B8");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31B8");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Yaw vel world axes (FS2000+)"},
//
//       // X (Lateral) Acceleration [FS2002+] — Right/left relative to world
//       // axes, in ft/sec/sec
//       {0x31C0, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31C0");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31C0");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "X (Lateral) Acceleration [FS2002+]"},
//
//       // Y (Vertical) Acceleration [FS2002+] — Up/down relative to world
//       // axes, in ft/sec/sec
//       {0x31C8, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31C8");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31C8");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Y (Vertical) Acceleration [FS2002+]"},
//
//       // Z (Longitudinal) Acceleration [FS2002+] — Foward/backward relative
//       // to world axes, in ft/sec/sec
//       {0x31D0, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31D0");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31D0");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Z (Longitudinal) Acceleration [FS2002+]"},

      // Radio altitude — Metres * 65536
      {0x31E4, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h122 = XPLMFindDataRef("sim/flightmodel/position/y_agl");
         put<int32_t>(dst, static_cast<int32_t>((r_h122 ? XPLMGetDataf(r_h122) : 0.0f) * 65536.0f));
       },
       nullptr,
       "Height AGL (m*65536)"},
//
//       // Total velocity ft/sec — This is the resultant velocity of the three
//       // X,Y,Z orthogonal velocities given in offsets 3178, 3180 and 3188.
//       {0x34C8, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x34C8");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Total velocity ft/sec"},
//
//       // Viewpoint Latitude — -ve for South, +ve for North. See expression
//       // for conversion.
//       {0x83BC, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x83BC");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Viewpoint Latitude"},
//
//       // Viewpoint Longitude — -ve for West, +ve for East. See expression for
//       // conversion.
//       {0x83C4, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x83C4");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Viewpoint Longitude"},
//
//       // Viewpoint Altitude — This is read only and seems to relate to the
//       // position of the viewer whether in cockpit, tower or spot views
//       {0x83CC, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x83CC");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Viewpoint Altitude"},
//
//       // Viewpoint Pitch — 0=level, -ve=pictch up, +ve=pitch down, degrees.
//       {0x83D4, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x83D4");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Viewpoint Pitch"},
//
//       // Viewpoint Bank — -ve right bank, +ve left bank.
//       {0x83D8, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x83D8");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Viewpoint Bank"},
//
//       // Viewpoint Heading — degrees TRUE
//       {0x83DC, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x83DC");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Viewpoint Heading"},

  }; // end table
  return table;
}
