// SPDX-License-Identifier: GPL-3.0-or-later
// fsuipc_offsets/Misc.h — Production offset table
//
// 19 total offsets in this category
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

inline const std::vector<OffsetEntry> &fsuipc_offset_table_misc()
{
  static const std::vector<OffsetEntry> table = {

//       {0x0B50, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0B50");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0B50");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Bleed air source control"},

      // APU generator switch
      {0x0B51, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/engine/APU_switch"); // Legacy dataref
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/electrical/APU_starter_switch");
         // sim/cockpit2/electrical/APU_starter_switch: 0=off, 1=start, 2=on
         // FSUIPC client expects Boolean (0/1), so collapse any non-zero to 1
         put<uint8_t>(dst, static_cast<uint8_t>(r ? (XPLMGetDatai(r) > 0) : 0));
       },
       nullptr,
       "APU generator switch"},

      // APU generator active flag
      {0x0B52, 1,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // static XPLMDataRef r_apu = XPLMFindDataRef("sim/cockpit/electrical/generator_apu_on"); // Legacy dataref
         static XPLMDataRef r_gen = XPLMFindDataRef("sim/cockpit2/electrical/APU_generator_on");
         // int v = (r_apu ? XPLMGetDatai(r_apu) : 0) | (r_gen ? XPLMGetDatai(r_gen) : 0);
         int v = (r_gen ? XPLMGetDatai(r_gen) : 0);
         put<uint8_t>(dst, static_cast<uint8_t>(v ? 1 : 0));
       },
       nullptr,
       "APU generator active flag"},
//
//       // APU on fire flag
//       {0x0B53, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0B53");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "APU on fire flag"},
//
//       // APU RPM percent — percentage of max
//       {0x0B54, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0B54");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "APU RPM percent"},

      // APU starter percent — FSUIPC4 interprets writes here as start /stop
      // APU requests. Just write any Non-Zero value to start, or all zero to
      // stop.
      {0x0B58, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/electrical/APU_N1_percent");
         put<int32_t>(dst, r ? XPLMGetDatai(r) : 0);
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_sw = XPLMFindDataRef("sim/cockpit2/electrical/APU_N1_percent");
         if (r_sw)
           XPLMSetDatai(r_sw, take<int32_t>(src) ? 1 : 0);
       },
       "APU starter percent"},
//
//       // APU generator voltage
//       {0x0B5C, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0B5C");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0B5C");
//          if (r)
//            XPLMSetDataf(r, static_cast<float>(take<float>(src)));
//        },
//        "APU generator voltage"},
//
//       // Virtual button control word — Write here as an easier way of
//       // toggling, setting or clearing one of the virtual buttons at offsets
//       // 3340 ff.
//       {0x29F0, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x29F0");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x29F0");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Virtual button control word"},
//
//       // Heli Beep
//       {0x2DC6, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2DC6");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2DC6");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Heli Beep"},

      // ATC flight no. [FS2002+] — String, up to 12 chars inclusing zero
      // terminator
      {0x3130, 12,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         std::memset(dst, 0, 12);
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/radios/actuators/flight_id");
         if (r)
           XPLMGetDatab(r, dst, 0, 11);
         dst[11] = 0;
       },
       nullptr,
       "ATC flight number / callsign (12 chars)"},

      // ATC id (tail no.) [FS2002+] — String, up to 12 chars inclusing zero
      // terminator
      {0x313C, 12,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         std::memset(dst, 0, 12);
         static XPLMDataRef r = XPLMFindDataRef("sim/aircraft/view/acf_tailnum");
         if (r)
           XPLMGetDatab(r, dst, 0, 11);
         dst[11] = 0;
       },
       nullptr,
       "Aircraft registration / tail number (12 chars)"},

      // ATC airline [FS2002+] — String, up to 24 chars inclusing zero
      // terminator
      {0x3148, 24,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         std::memset(dst, 0, 24);
         static XPLMDataRef r = XPLMFindDataRef("sim/aircraft/view/acf_manufacturer");
         if (r)
           XPLMGetDatab(r, dst, 0, 23);
         dst[23] = 0;
       },
       nullptr,
       "Airline / manufacturer (24 chars)"},

      // ATC airxraft type [FS2002+] — String, up to 24 chars inclusing zero
      // terminator
      {0x3160, 24,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         std::memset(dst, 0, 24);
         static XPLMDataRef r = XPLMFindDataRef("sim/aircraft/view/acf_descrip");
         if (r)
           XPLMGetDatab(r, dst, 0, 23);
         dst[23] = 0;
       },
       nullptr,
       "Aircraft model name (24 chars)"},
//
//       // Protected Options control
//       {0x32F0, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x32F0");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Protected Options control"},
//
//       // Last Menu item accessed
//       {0x32F4, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x32F4");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Last Menu item accessed"},
//
//       // FSUIPC option flags — 0=non-scrolling messages to be white,
//       // 1=MakeItVersionFS2002 is being used in FS2004
//       {0x3302, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3302");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FSUIPC option flags"},
//
//       // WideFS Shutdown Option — WideFS option "AllowShutdown=Yes" is
//       // activated by writing 0xABCD to this location (needs WideFS 4.43
//       {0x3320, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3320");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3320");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "WideFS Shutdown Option"},
//
//       // WideServer version — WideServer version, if running and if 5.00 or
//       // later (in hex BCD x 1000)
//       {0x3322, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3322");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "WideServer version"},
//
//       // Tailhook position — 0.0=retracted, 1.0=lowered
//       {0x3BA0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Tailhook position"},

  }; // end table
  return table;
}
