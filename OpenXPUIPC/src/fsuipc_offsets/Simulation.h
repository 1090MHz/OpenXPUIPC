// SPDX-License-Identifier: GPL-3.0-or-later
// fsuipc_offsets/Simulation.h — Production offset table
//
// 197 total offsets in this category
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

inline const std::vector<OffsetEntry> &fsuipc_offset_table_simulation()
{
  static const std::vector<OffsetEntry> table = {

//
//       // ===== Simulation =============================================
//
//       // Startup situation/flight — Path from FS folder is included.
//       {0x0024, 256,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0024");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 256);
//          dst[0] = 0;
//        },
//        nullptr,
//        "Startup situation/flight"},
//
//       // Log Book name [FS2002+] — Zero terminated ASCII string, but just
//       // 'logbook' by default. Length not actually determined -- probably
//       // less than 256 though.
//       {0x012C, 256,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Log Book name [FS2002+]"},
//
//       // Current flight plan [FSX] — Zero terminated ASCII string, giving the
//       // filepath to currently active flight plan (.PLN).
//       {0x0130, 256,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Current flight plan [FSX]"},
//
//       // Airline Traffic Density % — 0-100.
//       {0x0250, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0250");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0250");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Airline Traffic Density %"},
//
//       // General Aviation Traffic Density % — 0-100.
//       {0x0251, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0251");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0251");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "General Aviation Traffic Density %"},
//
//       // Ships & Ferries Traffic Density % — 0-100.
//       {0x0252, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0252");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0252");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Ships & Ferries Traffic Density %"},
//
//       // Cloud cover density setting 5-8 — 5 = MIN, 8 = MAX
//       {0x0254, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0254");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0254");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Cloud cover density setting 5-8"},
//
//       // Cloud simple/complex — 0 = Simple, 1 = Complex
//       {0x0255, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0255");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0255");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Cloud simple/complex"},
//
//       // Thermal visualisation — 0 = None, 1 = Natural, 2= Schematic
//       {0x0256, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0256");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Thermal visualisation"},
//
//       // Pause control — Write 1 to pause, 0 to unpause
//       {0x0262, 2,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0262");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Pause control"},

      // Pause flag — 0=Running, 1=Paused
      {0x0264, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h9 = XPLMFindDataRef("sim/time/paused");
         put<int16_t>(dst, static_cast<int16_t>((r_h9 ? XPLMGetDatai(r_h9) : 0)));
       },
       nullptr,
       "Paused"},
//
//       // Frame Rate
//       {0x0274, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0274");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Frame Rate"},
//
//       // Zoom factor (FS2002+) — 64=x1, 128=x2 et cetera. Read only, FS2002+
//       // only
//       {0x02B2, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x02B2");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Zoom factor (FS2002+)"},
//
//       // Control Timer 1 (FS2002+, see 0368) — Seconds and fractionals
//       {0x0310, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0310");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Control Timer 1 (FS2002+, see 0368)"},
//
//       // Plane in fuel box flag — Same as BGL variable 0288
//       {0x032C, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x032C");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Plane in fuel box flag"},
//
//       // Instrument: Com Freq inc. — 0=50 KHz, 1=25 KHz
//       {0x0358, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0358");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0358");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Instrument: Com Freq inc."},
//
//       // Instrument: Adf Freq inc. — 0=1.0 KHz, 1=0.1 KHz
//       {0x035C, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x035C");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x035C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Instrument: Adf Freq inc."},
//
//       // Control Timer 2 (FS2002, see 0310) — 32-bit FLOAT, control timing
//       // (eg inc/dec acceleration)
//       {0x0368, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Control Timer 2 (FS2002, see 0310)"},
//
//       // Reliabillity % — 0-100%
//       {0x0372, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0372");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0372");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Reliabillity %"},
//
//       // 1st FSUIPC Monitored value — In FLOAT32 form
//       {0x03A0, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03A0");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "1st FSUIPC Monitored value"},
//
//       // 2nd FSUIPC Monitored value — In FLOAT32 form
//       {0x03A4, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03A4");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "2nd FSUIPC Monitored value"},
//
//       // 3rd FSUIPC Monitored value — In FLOAT32 form
//       {0x03A8, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03A8");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "3rd FSUIPC Monitored value"},
//
//       // 4th FSUIPC Monitored value — In FLOAT32 form
//       {0x03AC, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03AC");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "4th FSUIPC Monitored value"},
//
//       // Button state, Joy #0 — Only valid if scanned by FSUIPC
//       {0x03C0, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03C0");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Button state, Joy #0"},
//
//       // Button state, Joy #1 — Only valid if scanned by FSUIPC
//       {0x03C4, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03C4");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Button state, Joy #1"},
//
//       // Button state, Joy #2 — Only valid if scanned by FSUIPC
//       {0x03C8, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03C8");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Button state, Joy #2"},
//
//       // Button state, Joy #3 — Only valid if scanned by FSUIPC
//       {0x03CC, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03CC");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Button state, Joy #3"},
//
//       // Button state, Joy #4 — Only valid if scanned by FSUIPC
//       {0x03D0, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03D0");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Button state, Joy #4"},
//
//       // Button state, Joy #5 — Only valid if scanned by FSUIPC
//       {0x03D4, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03D4");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Button state, Joy #5"},
//
//       // Button state, Joy #6 — Only valid if scanned by FSUIPC
//       {0x03D8, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03D8");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Button state, Joy #6"},
//
//       // Button state, Joy #7 — Only valid if scanned by FSUIPC
//       {0x03DC, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03DC");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Button state, Joy #7"},
//
//       // Button state, Joy #8 — Only valid if scanned by FSUIPC
//       {0x03E0, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03E0");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Button state, Joy #8"},
//
//       // Button state, Joy #9 — Only valid if scanned by FSUIPC
//       {0x03E4, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03E4");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Button state, Joy #9"},
//
//       // Button state, Joy #10 — Only valid if scanned by FSUIPC
//       {0x03E8, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03E8");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Button state, Joy #10"},
//
//       // Button state, Joy #11 — Only valid if scanned by FSUIPC
//       {0x03EC, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03EC");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Button state, Joy #11"},
//
//       // Button state, Joy #12 — Only valid if scanned by FSUIPC
//       {0x03F0, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03F0");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Button state, Joy #12"},
//
//       // Button state, Joy #13 — Only valid if scanned by FSUIPC
//       {0x03F4, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03F4");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Button state, Joy #13"},
//
//       // Button state, Joy #14 — Only valid if scanned by FSUIPC
//       {0x03F8, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03F8");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Button state, Joy #14"},
//
//       // Button state, Joy #15 — Only valid if scanned by FSUIPC
//       {0x03FC, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03FC");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Button state, Joy #15"},
//
//       // Name of last saved flight — ASCIIZ up to 128 bytes
//       {0x0400, 128,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0400");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 128);
//          dst[0] = 0;
//        },
//        nullptr,
//        "Name of last saved flight"},
//
//       // Elapsed time — Counts simiulated time, seconds. Accurate to
//       // fractions but only updated on a frame basis
//       {0x04A8, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x04A8");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Elapsed time"},
//
//       // Smoke system available (<= FS2000) — 0=No smoke available, 1=Smoke
//       // system fitted
//       {0x05D4, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05D4");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Smoke system available (<= FS2000)"},
//
//       // Slew Mode — 0=not slew mode, 1=slew mode
//       {0x05DC, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05DC");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05DC");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Slew Mode"},
//
//       // Slew control — Write non-zero value here at same time as changing
//       // 05DC above, and the Slew mode change includes the swapping of the
//       // assigned joystick axes. [ignored in FS2004 - the axes are swapped in
//       // any case. See offset 310B for control of axis connection in slew
//       // mode]
//       {0x05DE, 2,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05DE");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Slew control"},
//
//       // Slew roll rate — -ve roll right, +ve roll left. 192 gives a 360 roll
//       // in about 1 minute.
//       {0x05E4, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05E4");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05E4");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "Slew roll rate"},
//
//       // Slew yaw rate — Slew mode turns (rudder use in slew mode) can be
//       // read/written. +ve values are left, -ve are right, a value of 24
//       // takes about 1 minute to complete a 360.
//       {0x05E6, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05E6");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05E6");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "Slew yaw rate"},
//
//       // Slew vertical rate — 16384=no alt slew rate. 16383 to 0 increasing
//       // slew UP rates, 16385 to 32767 increasing slew DOWN rates
//       {0x05E8, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05E8");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05E8");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "Slew vertical rate"},
//
//       // Slew fwd/bwd rate — Slew fwd if-ve, bwd if +ve, 1=very slow ...
//       // 127=very fast, -128 fastest forward
//       {0x05EB, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05EB");
//          put<int8_t>(dst, static_cast<int8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05EB");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int8_t>(src)));
//        },
//        "Slew fwd/bwd rate"},
//
//       // Slew left/right rate — Slew left if -ve, right if +ve, 1=very slow
//       // ... 127=very fast, -128 fastest leftward
//       {0x05ED, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05ED");
//          put<int8_t>(dst, static_cast<int8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05ED");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int8_t>(src)));
//        },
//        "Slew left/right rate"},
//
//       // Slew pitch rate — 16384=no pitch slew. <16384 pitch up, >16384 pitch
//       // down, range 0-32767
//       {0x05EE, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05EE");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05EE");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "Slew pitch rate"},
//
//       // Slew mode display — 0=off, 1=coods/hdg/speed, 2=fps, 3=all
//       {0x05F4, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05F4");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05F4");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Slew mode display"},
//
//       // Flight mode display — 0=off, 1=coods/hdg/speed, 2=fps, 3=all
//       {0x05FC, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05FC");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x05FC");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Flight mode display"},
//
//       // Replay in action flag & control — 0=off, 1=on. See also 062C
//       {0x0628, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0628");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0628");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Replay in action flag & control"},
//
//       // Replay timer count-down — Instant replay time left in seconds.
//       // Whilst this is non-zero, 0628 controls the playback
//       {0x062C, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x062C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x062C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Replay timer count-down"},
//
//       // Video recording flag (FS2002+) — 0=off. 1=on
//       {0x0760, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0760");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Video recording flag (FS2002+)"},
//
//       // Crash detection — 0=Ignore Crash, 1=Detect Crash and restart,
//       // 2=Detect Crash and show Graph (last is not applicable to FS2002/4)
//       {0x0830, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0830");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0830");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Crash detection"},
//
//       // FSX Crash detection — 0=Ignore Crash, 1=Detect Crash
//       {0x0832, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0832");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FSX Crash detection"},
//
//       // FSX AI Crash detection — 0=Ignore Crash, 1=Detect Crash
//       {0x0833, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0833");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FSX AI Crash detection"},

      // Crashed — 0=Everything ok, 1=Crashed
      {0x0840, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel2/misc/has_crashed");
         put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
       },
       nullptr,
       "Crashed flag"},

      // Sound control — 0=Off, 1=On
      {0x0B20, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/sound/sound_on");
         put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/sound/sound_on");
         if (r)
           XPLMSetDatai(r, take<int16_t>(src) ? 1 : 0);
       },
       "Sound on/off control"},

      // Sound flag — 1=Sound enabled
      {0x0B24, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/sound/sound_on");
         put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
       },
       nullptr,
       "Sound on flag (read-only)"},
//
//       // Scenery Complexity — Complexity setting, 0-4 in FS98, 0-5 in later
//       // versions
//       {0x0B60, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0B60");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0B60");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Scenery Complexity"},
//
//       // International: Units — 0=US, 1=Metric, Alt in Feet, 2=Metric, Alt in
//       // Meters
//       {0x0C18, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C18");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C18");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "International: Units"},

      // Simulation rate — 256 = 1X. You can stop simulation by setting 0
      // here
      {0x0C1A, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h113 = XPLMFindDataRef("sim/time/sim_speed");
         put<int16_t>(dst, static_cast<int16_t>((r_h113 ? XPLMGetDatai(r_h113) : 1) * 256));
       },
       nullptr,
       "Simulation rate (*256)"},

      // Time String — Local Simulator time as an 9-byte character string in
      // the format:  hh:mm:ss with a zero string terminator.
      {0x0C20, 9,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &)
       {
         static XPLMDataRef r_hh = XPLMFindDataRef("sim/cockpit2/clock_timer/local_time_hours");
         static XPLMDataRef r_mm = XPLMFindDataRef("sim/cockpit2/clock_timer/local_time_minutes");
         static XPLMDataRef r_ss = XPLMFindDataRef("sim/cockpit2/clock_timer/local_time_seconds");
         int hh = r_hh ? XPLMGetDatai(r_hh) : 0;
         int mm = r_mm ? XPLMGetDatai(r_mm) : 0;
         int ss = r_ss ? XPLMGetDatai(r_ss) : 0;
         std::snprintf(reinterpret_cast<char *>(dst), 9, "%02d:%02d:%02d", hh, mm, ss);
       },
       nullptr,
       "Local time string (hh:mm:ss)"},
//
//       // Realism 0-100% — 0-100
//       {0x0C44, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C44");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C44");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Realism 0-100%"},
//
//       // Texture Quality — 0-3, as per slider in Display Quality (FS2k)
//       {0x0C92, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C92");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C92");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Texture Quality"},
//
//       // Macro or Lua String Parameter
//       {0x0D6C, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0D6C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0D6C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Macro or Lua String Parameter"},
//
//       // Macro or Lua String — Write macro command or lua control here
//       {0x0D70, 40,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0D70");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 40);
//          dst[0] = 0;
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0D70");
//          // TODO: string — XPLMSetDatab(r, (void*)src, 0, (int)sz);
//        },
//        "Macro or Lua String"},
//
//       // International: North/South — 2=North, 3=South
//       {0x0D98, 2,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "International: North/South"},
//
//       // International: West/East — 1=West, 0=East
//       {0x0D9C, 2,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "International: West/East"},
//
//       // Scenery variable USRVAR (0312h) — Scenery BGL variable "usrvar"
//       // (originally 0312h in BGL) (*In FS2004 this is moved to globals by
//       // FSUIPC unless 'MoveBGLvariables=No')
//       {0x0DD6, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DD6");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DD6");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Scenery variable USRVAR (0312h)"},
//
//       // Scenery variable USRVR2 (0314h) — Scenery BGL variable "usrvr2"
//       // (originally 0314h in BGL) (*In FS2004 this is moved to globals by
//       // FSUIPC unless 'MoveBGLvariables=No')
//       {0x0DD8, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DD8");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DD8");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Scenery variable USRVR2 (0314h)"},
//
//       // Scenery variable USRVR3 (0316h) — Scenery BGL variable "usrvr3"
//       // (originally 0316h in BGL) (*In FS2004 this is moved to globals by
//       // FSUIPC unless 'MoveBGLvariables=No')
//       {0x0DDA, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DDA");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DDA");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Scenery variable USRVR3 (0316h)"},
//
//       // Scenery variable USRVR4 (0318h) — Scenery BGL variable "usrvr4"
//       // (originally 0318h in BGL) (*In FS2004 this is moved to globals by
//       // FSUIPC unless 'MoveBGLvariables=No')
//       {0x0DDC, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DDC");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DDC");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Scenery variable USRVR4 (0318h)"},
//
//       // Scenery variable USRVR5 (031Ah) — Scenery BGL variable "usrvr5"
//       // (originally 031Ah in BGL) (*In FS2004 this is moved to globals by
//       // FSUIPC unless 'MoveBGLvariables=No')
//       {0x0DDE, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DDE");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DDE");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Scenery variable USRVR5 (031Ah)"},
//
//       // Scenery variable SPAR10 (031Eh) (not FS2004) — Scenery BGL variable
//       // "spar10" (originally 031Eh in BGL) (doesn't appear to be supported
//       // at all in FS2004)
//       {0x0DE2, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DE2");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DE2");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Scenery variable SPAR10 (031Eh) (not FS2004)"},
//
//       // Scenery variable SPAR11 (0320h) (not FS2004) — Scenery BGL variable
//       // "spar11" (originally 0320h in BGL) (doesn't appear to be supported
//       // at all in FS2004)
//       {0x0DE4, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DE4");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DE4");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Scenery variable SPAR11 (0320h) (not FS2004)"},
//
//       // Scenery variable SPAR12 (0322h) (not FS2004) — Scenery BGL variable
//       // "spar12" (originally 0322h in BGL) (doesn't appear to be supported
//       // at all in FS2004)
//       {0x0DE6, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DE6");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DE6");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Scenery variable SPAR12 (0322h) (not FS2004)"},
//
//       // Scenery variable SPAR13 (0324h) (not FS2004) — Scenery BGL variable
//       // "spar13" (originally 0324h in BGL) (doesn't appear to be supported
//       // at all in FS2004)
//       {0x0DE8, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DE8");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DE8");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Scenery variable SPAR13 (0324h) (not FS2004)"},
//
//       // Scenery variable SPAR14 (0326h) (not FS2004) — Scenery BGL variable
//       // "spar14" (originally 0326h in BGL) (doesn't appear to be supported
//       // at all in FS2004)
//       {0x0DEA, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DEA");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DEA");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Scenery variable SPAR14 (0326h) (not FS2004)"},
//
//       // Scenery variable SPAR15 (0328h) (not FS2004) — Scenery BGL variable
//       // "spar15" (originally 0328h in BGL) (doesn't appear to be supported
//       // at all in FS2004)
//       {0x0DEC, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DEC");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DEC");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Scenery variable SPAR15 (0328h) (not FS2004)"},
//
//       // Scenery variable SPAR16 (032Ah) (not FS2004) — Scenery BGL variable
//       // "spar16" (originally 032Ah in BGL) (doesn't appear to be supported
//       // at all in FS2004)
//       {0x0DEE, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DEE");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DEE");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Scenery variable SPAR16 (032Ah) (not FS2004)"},
//
//       // Scenery variable SPAR17 (032Ch) (not FS2004) — Scenery BGL variable
//       // "spar17" (originally 032Ch in BGL) (doesn't appear to be supported
//       // at all in FS2004)
//       {0x0DF0, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DF0");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DF0");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Scenery variable SPAR17 (032Ch) (not FS2004)"},
//
//       // Scenery variable SPAR18 (032Eh) (not FS2004) — Scenery BGL variable
//       // "spar18" (originally 032Eh in BGL) (doesn't appear to be supported
//       // at all in FS2004)
//       {0x0DF2, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DF2");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0DF2");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Scenery variable SPAR18 (032Eh) (not FS2004)"},
//
//       // Path read signature / flag — To action command in 0FF4 write non-
//       // zero signature here. If it reads Non-Zero, feature is in use
//       {0x0FF0, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0FF0");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0FF0");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Path read signature / flag"},
//
//       // Path read command — 1 = read default Flight folder, 2 = read AI
//       // traffic filepath (FS2004)
//       {0x0FF4, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0FF4");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0FF4");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Path read command"},
//
//       // Path read options — Flags modifying the Path Read command. Only one
//       // at preset: 1 = provide UNC path if not within FS main path.
//       {0x0FF6, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0FF6");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0FF6");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Path read options"},
//
//       // Path read parameter — Gives AI aircraft ID number for Path Read
//       // command #2
//       {0x0FF8, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0FF8");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0FF8");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int32_t>(src)));
//        },
//        "Path read parameter"},
//
//       // Path read timestamp — Timestamp to show when path is set
//       {0x0FFC, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0FFC");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Path read timestamp"},
//
//       // Path area (256 bytes) -- FLT path on FSX — On FSX this is the path
//       // (in UNC format if possible) to the folder where Flights are saved by
//       // default.
//       {0x1000, 256,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1000");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 256);
//          dst[0] = 0;
//        },
//        nullptr,
//        "Path area (256 bytes) -- FLT path on FSX"},
//
//       // Aircraft shadows
//       {0x11A4, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x11A4");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x11A4");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Aircraft shadows"},

      // G-Force
      {0x11BA, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Gload_normal_g returns 1.0 in level/1G flight, matching legacy FSUIPC (625 = 1G).
         // local_ay (kinematic acceleration) was ≈0 in level flight, giving wrong 0 result.
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/gauges/indicators/Gload_normal_g");
         float g = r ? XPLMGetDataf(r) : 1.0f;
         put<int16_t>(dst, static_cast<int16_t>(g * 625.0f));
       },
       nullptr,
       "G force (raw * 625)"},
//
//       // SIM1 data — For internal module use only, used to point ot
//       // SIM1.SIM's export table
//       {0x11D4, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x11D4");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "SIM1 data"},
//
//       // Text display mode [FS2000+] — =0 for static line, =1 for scrolling
//       // line (FS2.. Try 1254 for this on FS98)
//       {0x1274, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1274");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1274");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Text display mode [FS2000+]"},
//
//       // AI traffic ID for control — Part of 12 byte AI control area provided
//       // for FS2004. This identifies the AI aircraft
//       {0x2900, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2900");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "AI traffic ID for control"},
//
//       // AI traffic control number — FS control number to be sent to
//       // Identified AI aircraft (FS2004)
//       {0x2904, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2904");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "AI traffic control number"},
//
//       // AI traffic control parameter — FS control parameter for AI contorl,
//       // if applicable. (FS2004)
//       {0x2908, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2908");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int32_t>(src)));
//        },
//        "AI traffic control parameter"},
//
//       // Hot buttons: # of slots — No. of FSUIPC Hot joystick button slots
//       // following
//       {0x290C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x290C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Hot buttons: # of slots"},
//
//       // Hot Button Joystick + 128 — Joystick number 0-15 plus 128. 0 if slot
//       // free
//       {0x2910, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2910");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2910");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Hot Button Joystick + 128"},
//
//       // Hot Button number 0-39 — Buttons 0-31 are normal, 32-39 are the hat
//       // positons or "points of view".
//       {0x2911, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2911");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2911");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Hot Button number 0-39"},
//
//       // Hot Button change required — This byte indicates which change is to
//       // be notified: = 0 for Off to On = 1 for On to Off = 2 for both Off to
//       // On and On to Off = 3 for Off to On but repeating about 6 times per
//       // second whilst it is on.
//       {0x2912, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2912");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2912");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Hot Button change required"},
//
//       // Hot Button result — Flags from FSUIPC.
//       {0x2913, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2913");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2913");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Hot Button result"},
//
//       // Autotune ADF1 disable — Write 1 to disable FSUIPC auto-tuning ADF1,
//       // if enabled in the INI
//       {0x3108, 1,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3108");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Autotune ADF1 disable"},
//
//       // Axis calibration disable — Write 1 to disable FSUIPC axis
//       // calibration, if enabled in the INI
//       {0x3109, 1,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3109");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Axis calibration disable"},

      // Joystick axis disable flags — Set bits here to prevent joystick axes
      // interfering with programmatic control. Bits are 2^0=Elevator,
      // 2^1=Aileron, 2^2=Rudder, 2^3=Throttles(all), 2^5=ElevTrim,
      // 2^6=Throttle 1, 2^7=Throttle 2.
      {0x310A, 1,
       // Read/Write: Read/Write
       nullptr,
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         uint8_t val = *src;
         auto &ov = overrides();
         ov.pitch = (val & 1) != 0;
         ov.roll = (val & 2) != 0;
         ov.throttle1 = (val & 8) != 0 || (val & 64) != 0;
         ov.throttle2 = (val & 8) != 0 || (val & 128) != 0;

         static XPLMDataRef r_h_ov_thro = XPLMFindDataRef("sim/operation/override/override_throttles");
         if (r_h_ov_thro)
           XPLMSetDatai(r_h_ov_thro, (ov.throttle1 || ov.throttle2) ? 1 : 0);
         static XPLMDataRef r_h134 = XPLMFindDataRef("sim/operation/override/override_joystick_pitch");
         if (r_h134)
           XPLMSetDatai(r_h134, ov.pitch ? 1 : 0);
         static XPLMDataRef r_h135 = XPLMFindDataRef("sim/operation/override/override_joystick_roll");
         if (r_h135)
           XPLMSetDatai(r_h135, ov.roll ? 1 : 0);
       },
       "Override disconnect flags"},
//
//       // Slew axis (plus thr 3/4) disable flags — Set bits here to stop slew
//       // axes being operated from joysticks. Also two normal throttles. Bits
//       // are 2^0=Ahead, 2^1=Side, 2^2=Heading, 2^3=Altitude, 2^4=Bank,
//       // 2^5=Pitch, 2^6=Throttle 3, 2^7=Throttle 4. FSUIPC clears this byte
//       // after 10 seconds since the last write, so you need to write it
//       // regularly to keep slew axes disabled.
//       {0x310B, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x310B");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x310B");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Slew axis (plus thr 3/4) disable flags"},
//
//       // PFC switch code input simulation — For PFC.DLL testing only
//       {0x310C, 2,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x310C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "PFC switch code input simulation"},
//
//       // FS Control to be executed — Exceutes the FS CFG type control, by
//       // number. If needed, set the parameter value in 3114 first, then write
//       // the control number (see FS controls lists) here. Better, write all 8
//       // bytes together.
//       {0x3110, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3110");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "FS Control to be executed"},
//
//       // FS Control parameter value — Parameter for axis and 'SET' controls
//       // executed by writing to 3110 above.
//       {0x3114, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3114");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int32_t>(src)));
//        },
//        "FS Control parameter value"},
//
//       // View control — Operates views: 0=FORWARD, 1=FORWARD_RIGHT, etc. to
//       // 7, then 8=DOWN, 9=UP, 10-17=FORWARD_UP and so on, clockwise. All
//       // other values=RESET. Reading does NOT tell you current view!
//       {0x3126, 1,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3126");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "View control"},
//
//       // FSUIPC Option Control Timer — Set NZ to make FSUIPC apply the option
//       // settings in 3128/312C. This byte needs writing regularly -- it is
//       // decremented by 1 every 50 mSecs or so. When it reaches 0 FSUIPC
//       // restores user settings
//       {0x3127, 1,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3127");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "FSUIPC Option Control Timer"},
//
//       // FSUIPC Option Mask — FSUIPC option bits -- only those with bits set
//       // herer are changed by 312C when 3127 is written non-zero
//       {0x3128, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3128");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "FSUIPC Option Mask"},
//
//       // FSUIPC Option Settings — FSUIPC option bits -- those positions set
//       // in the mask (3128) are altered to these values when 3127 is written
//       // non-zero (see FSUIPC doc for bit assignments)
//       {0x312C, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x312C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "FSUIPC Option Settings"},
//
//       // Pushback State (FS2002+] — 3=off, 0=pushing back, 1=pushing back,
//       // tail to left, 2=pushing back, tail to right
//       {0x31F0, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31F0");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Pushback State (FS2002+]"},
//
//       // Pushback Control [FS2002+] — Write 0=start, 1=tail left, 2=tail
//       // right, 3=stop
//       {0x31F4, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31F4");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Pushback Control [FS2002+]"},
//
//       // Tug heading [FS2002+] for gliders? — Degrees True
//       {0x31F8, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31F8");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Tug heading [FS2002+] for gliders?"},
//
//       // Tug speed [FS2002+] for gliders? — Feet/Sec
//       {0x31FC, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31FC");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Tug speed [FS2002+] for gliders?"},
//
//       // Key press to FS — 3 32-bit words giving Message (WM_LKEYUP or
//       // WM_KEYDOWN), then wParam and lParam, to send keystrokes to FS.
//       {0x3200, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3200");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Key press to FS"},
//
//       // Hot keys: # of slots — Number of FSUIPC hot key slots following
//       {0x320C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x320C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Hot keys: # of slots"},
//
//       // Hot Key keycode — Virtual keycode for hotkey
//       {0x3210, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3210");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3210");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Hot Key keycode"},
//
//       // Hot Key shift states — Shift state indicator
//       {0x3211, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3211");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3211");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Hot Key shift states"},
//
//       // Hot Key App flags — Flags from application.
//       {0x3212, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3212");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3212");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Hot Key App flags"},
//
//       // Hot Key result — This byte needs to be cleared by the application so
//       // that it can detect when the Hot Key occurs. There is no queuing. If
//       // the Hot Key alone is seen, this byte is set to 1. If bit 3 was set
//       // in Byte 1 above and another key was pressed before the hotkey was
//       // released, then the virtual keycode for the extra key (2-255) is
//       // provided here.
//       {0x3213, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3213");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3213");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Hot Key result"},
//
//       // FSUIPC tech opts inhibits (if user allows) — Write selected bits
//       // regularly (eg every 5 secs) to keep options inhibited
//       {0x32F6, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x32F6");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x32F6");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "FSUIPC tech opts inhibits (if user allows)"},
//
//       // Assorted facility inhibits — 2^0=no flap changes, 2^1=no spoiler
//       // changes etc (see docs)
//       {0x32F8, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x32F8");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x32F8");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Assorted facility inhibits"},
//
//       // Text display control — Writes to here makes FSUIPC display the last
//       // string written to 3380. The value written here is the Delay time, in
//       // seconds, till the message is cleared (0=leave till replaced), or -1
//       // for scrolling (if that option is set in FS).
//       {0x32FA, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x32FA");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x32FA");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "Text display control"},
//
//       // AIR file change counter — Incremented by 1 when AIR file pathname at
//       // 3C00 changes
//       {0x32FC, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x32FC");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x32FC");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "AIR file change counter"},
//
//       // Hot Key flags changed counter — Counter changed every time FSUIPC
//       // changes a flag in the Hot Key table. Applications can read this
//       // instead of scanning all the entries in which they have an interest.
//       {0x32FE, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x32FE");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Hot Key flags changed counter"},
//
//       // Hot Buttons changed counter — Counter changed every time FSUIPC
//       // changes a flag in the Hot Buttons table. Applications can read this
//       // instead of scanning all the entries in which they have an interest.
//       {0x32FF, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x32FF");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Hot Buttons changed counter"},

      // FSUIPC interim version Id — 0=none, 1-26 = a-z
      {0x3304, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &)
       {
         put<int32_t>(dst, 0x50000006);
       },
       nullptr,
       "FS version"},
//
//       // FSUIPC version — BCD. e.g. 0x1998 = version 1.998
//       {0x3306, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3306");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FSUIPC version"},

      // FS version — 1=FS98, 2=FS2K, 3=CFS2, 4=CFS1, 5=reserved, 6=FS2002,
      // 7=FS2004, 8=FSX, 9=ESP, 10=P3D
      {0x3308, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &)
       {
         put<int32_t>(dst, static_cast<int32_t>(0xFADE0008));
       },
       nullptr,
       "FSUIPC lib version"},
//
//       // IPC application counter — Counts up to 255 only
//       {0x330E, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x330E");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "IPC application counter"},
//
//       // WideFS flags — From WideFS 5.50 only: 2^0=Using TCP (else SPX),
//       // 2^1=Have connections, Others to follow
//       {0x333C, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x333C");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "WideFS flags"},
//
//       // Virtual Buttons, Joy #64
//       {0x3340, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3340");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3340");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Virtual Buttons, Joy #64"},
//
//       // Virtual Buttons, Joy #65
//       {0x3344, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3344");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3344");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Virtual Buttons, Joy #65"},
//
//       // Virtual Buttons, Joy #66
//       {0x3348, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3348");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3348");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Virtual Buttons, Joy #66"},
//
//       // Virtual Buttons, Joy #67
//       {0x334C, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x334C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x334C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Virtual Buttons, Joy #67"},
//
//       // Virtual Buttons, Joy #68
//       {0x3350, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3350");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3350");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Virtual Buttons, Joy #68"},
//
//       // Virtual Buttons, Joy #69
//       {0x3354, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3354");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3354");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Virtual Buttons, Joy #69"},
//
//       // Virtual Buttons, Joy #70
//       {0x3358, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3358");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3358");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Virtual Buttons, Joy #70"},
//
//       // Virtual Buttons, Joy #71
//       {0x335C, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x335C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x335C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Virtual Buttons, Joy #71"},
//
//       // Virtual Buttons, Joy #72
//       {0x3360, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3360");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3360");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Virtual Buttons, Joy #72"},
//
//       // FS2004 ready to fly flag — FS2004, zero = ready to fly (always zero
//       // before FS2004)
//       {0x3364, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3364");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FS2004 ready to fly flag"},
//
//       // Paused in menu flag — NZ means FS is in a menu or frozen whilst a
//       // resulting amodal dialogue is used
//       {0x3365, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3365");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Paused in menu flag"},
//
//       // PFC MCP events flags — Flags for PFC's MCP buttons. See PFC.DLL docs
//       {0x3368, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3368");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PFC MCP events flags"},
//
//       // Frame rate entry counter — 16-bit counter incremented each time
//       // FSUIPC is entered by FS Frame Rate call
//       {0x336C, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x336C");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Frame rate entry counter"},
//
//       // PFC driver diagnostic area — See PFC.DLL documentation
//       {0x3370, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3370");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PFC driver diagnostic area"},
//
//       // Live millisecond expired counter, as in Logs
//       {0x3374, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3374");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Live millisecond expired counter, as in Logs"},
//
//       // Last log message time — Millisecond timestamp of last message sent
//       // to FSUIPC's Log file
//       {0x3378, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3378");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Last log message time"},
//
//       // FSUIPC activity counter — Keeps changing whilst FSUIPC (and
//       // therefore FS) is running. Can be used by wideFS clients to detect FS
//       // crashes
//       {0x337E, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x337E");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "FSUIPC activity counter"},
//
//       // Text display in FS — 128 byte area, containing messages intercepted
//       // by AdvDisplay (if running). Also, can write messages for display
//       // here, then set delay/scroll option in 32FA.
//       {0x3380, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3380");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3380");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Text display in FS"},
//
//       // FSUIPC logging control / indicators — Bits for each logging option -
//       // 0 = logging enabled (ignored, as logging is always enabled nowadays)
//       // 1 = weather 2 = IPC writes 3 = IPC reads 4 = Extras 5 = Extended,
//       // technical button and key logging 6 = VRI comms 7 = com HID 8 =
//       // L:Vars 9 = Axes 10 = Events 11 = Button/key standard logging 12 =
//       // Lua logging separate
//       {0x3400, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3400");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3400");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "FSUIPC logging control / indicators"},
//
//       // WideClient lowest version number if > 6441
//       {0x3520, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3520");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "WideClient lowest version number if > 6441"},
//
//       // Lat/Lon freeze timer — in ticks (55 mSecs). Keep it non-zero to keep
//       // the Lat/Lon of the aircraft fixed
//       {0x3541, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3541");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3541");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Lat/Lon freeze timer"},
//
//       // Count of FLT files saved
//       {0x3BD2, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BD2");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Count of FLT files saved"},

      // Panel failure ADF (FS2002+) Both on FS2004
      {0x3BD6, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r1 = XPLMFindDataRef("sim/operation/failures/rel_adf1");
         static XPLMDataRef r2 = XPLMFindDataRef("sim/operation/failures/rel_adf2");
         int v = (r1 ? XPLMGetDatai(r1) : 0) | (r2 ? XPLMGetDatai(r2) : 0);
         put<uint8_t>(dst, static_cast<uint8_t>(v != 0 ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         const int v = take<uint8_t>(src) ? 1 : 0;
         static XPLMDataRef r1 = XPLMFindDataRef("sim/operation/failures/rel_adf1");
         static XPLMDataRef r2 = XPLMFindDataRef("sim/operation/failures/rel_adf2");
         if (r1)
           XPLMSetDatai(r1, v);
         if (r2)
           XPLMSetDatai(r2, v);
       },
       "ADF failure (0=ok, 1=failed)"},

      // Panel failure ASI (FS2002+)
      {0x3BD7, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_g_asi");
         put<uint8_t>(dst, static_cast<uint8_t>((r ? XPLMGetDatai(r) : 0) != 0 ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_g_asi");
         if (r)
           XPLMSetDatai(r, take<uint8_t>(src) ? 1 : 0);
       },
       "Airspeed indicator failure (0=ok, 1=failed)"},

      // Panel failure Altimeter (FS2002+)
      {0x3BD8, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_ss_alt");
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_g_alt");
         put<uint8_t>(dst, static_cast<uint8_t>((r ? XPLMGetDatai(r) : 0) != 0 ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_g_alt");
         if (r)
           XPLMSetDatai(r, take<uint8_t>(src) ? 1 : 0);
       },
       "Altimeter failure (0=ok, 1=failed)"},

      // Panel failure AI (FS2002+)
      {0x3BD9, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_ss_ahz");
         put<uint8_t>(dst, static_cast<uint8_t>((r ? XPLMGetDatai(r) : 0) != 0 ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_ss_ahz");
         if (r)
           XPLMSetDatai(r, take<uint8_t>(src) ? 1 : 0);
       },
       "Attitude indicator failure (0=ok, 1=failed)"},

      // Panel failure COM1 (FS2002+)
      {0x3BDA, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_com1");
         put<uint8_t>(dst, static_cast<uint8_t>((r ? XPLMGetDatai(r) : 0) != 0 ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_com1");
         if (r)
           XPLMSetDatai(r, take<uint8_t>(src) ? 1 : 0);
       },
       "COM1 failure (0=ok, 1=failed)"},

      // Panel failure COM2 (FS2002+)
      {0x3BDB, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_com2");
         put<uint8_t>(dst, static_cast<uint8_t>((r ? XPLMGetDatai(r) : 0) != 0 ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_com2");
         if (r)
           XPLMSetDatai(r, take<uint8_t>(src) ? 1 : 0);
       },
       "COM2 failure (0=ok, 1=failed)"},

      // Panel failure Compass (FS2002+)
      {0x3BDC, 1,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_g_magmtr");
         put<uint8_t>(dst, static_cast<uint8_t>((r ? XPLMGetDatai(r) : 0) != 0 ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_g_magmtr");
         if (r)
           XPLMSetDatai(r, take<uint8_t>(src) ? 1 : 0);
       },
       "Compass failure (0=ok, 1=failed)"},

      // Panel failure ? unknown (FS2002+)
      {0x3BDD, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_gen_avio");
         put<uint8_t>(dst, static_cast<uint8_t>((r ? XPLMGetDatai(r) : 0) != 0 ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_gen_avio");
         if (r)
           XPLMSetDatai(r, take<uint8_t>(src) ? 1 : 0);
       },
       "Avionics bus failure (0=ok, 1=failed)"},

      // Panel failure Engine (FS2002+) — See 0B6B for separate engines
      {0x3BDE, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r1 = XPLMFindDataRef("sim/operation/failures/rel_engfai0");
         static XPLMDataRef r2 = XPLMFindDataRef("sim/operation/failures/rel_engfai1");
         static XPLMDataRef r3 = XPLMFindDataRef("sim/operation/failures/rel_engfai2");
         static XPLMDataRef r4 = XPLMFindDataRef("sim/operation/failures/rel_engfai3");
         int v = 0;
         v |= (r1 ? XPLMGetDatai(r1) : 0);
         v |= (r2 ? XPLMGetDatai(r2) : 0);
         v |= (r3 ? XPLMGetDatai(r3) : 0);
         v |= (r4 ? XPLMGetDatai(r4) : 0);
         put<uint8_t>(dst, static_cast<uint8_t>(v != 0 ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         const int v = take<uint8_t>(src) ? 1 : 0;
         static XPLMDataRef r1 = XPLMFindDataRef("sim/operation/failures/rel_engfai0");
         static XPLMDataRef r2 = XPLMFindDataRef("sim/operation/failures/rel_engfai1");
         static XPLMDataRef r3 = XPLMFindDataRef("sim/operation/failures/rel_engfai2");
         static XPLMDataRef r4 = XPLMFindDataRef("sim/operation/failures/rel_engfai3");
         if (r1)
           XPLMSetDatai(r1, v);
         if (r2)
           XPLMSetDatai(r2, v);
         if (r3)
           XPLMSetDatai(r3, v);
         if (r4)
           XPLMSetDatai(r4, v);
       },
       "Engine instruments failure (0=ok, 1=failed)"},

      // Panel failure Fuel ind (FS2002+)
      {0x3BDF, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_g_fuel");
         put<uint8_t>(dst, static_cast<uint8_t>((r ? XPLMGetDatai(r) : 0) != 0 ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_g_fuel");
         if (r)
           XPLMSetDatai(r, take<uint8_t>(src) ? 1 : 0);
       },
       "Fuel quantity indicator failure (0=ok, 1=failed)"},

      // Panel failure Heading ind (FS2002+)
      {0x3BE0, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_ss_dgy");
         put<uint8_t>(dst, static_cast<uint8_t>((r ? XPLMGetDatai(r) : 0) != 0 ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_ss_dgy");
         if (r)
           XPLMSetDatai(r, take<uint8_t>(src) ? 1 : 0);
       },
       "Heading indicator failure (0=ok, 1=failed)"},

      // Panel failure NAV1 (FS2002+)
      {0x3BE1, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_nav1");
         put<uint8_t>(dst, static_cast<uint8_t>((r ? XPLMGetDatai(r) : 0) != 0 ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_nav1");
         if (r)
           XPLMSetDatai(r, take<uint8_t>(src) ? 1 : 0);
       },
       "NAV1 failure (0=ok, 1=failed)"},

      // Panel failure NAV2 (FS2002+)
      {0x3BE2, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_nav2");
         put<uint8_t>(dst, static_cast<uint8_t>((r ? XPLMGetDatai(r) : 0) != 0 ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_nav2");
         if (r)
           XPLMSetDatai(r, take<uint8_t>(src) ? 1 : 0);
       },
       "NAV2 failure (0=ok, 1=failed)"},

      // Panel failure pitot heat (FS2002+)
      {0x3BE3, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r1 = XPLMFindDataRef("sim/operation/failures/rel_ice_pitot_heat1");
         static XPLMDataRef r2 = XPLMFindDataRef("sim/operation/failures/rel_ice_pitot_heat2");
         static XPLMDataRef r3 = XPLMFindDataRef("sim/operation/failures/rel_ice_pitot_heat_stby");
         int v = (r1 ? XPLMGetDatai(r1) : 0) | (r2 ? XPLMGetDatai(r2) : 0) | (r3 ? XPLMGetDatai(r3) : 0);
         put<uint8_t>(dst, static_cast<uint8_t>(v != 0 ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         const int v = take<uint8_t>(src) ? 1 : 0;
         static XPLMDataRef r1 = XPLMFindDataRef("sim/operation/failures/rel_ice_pitot_heat1");
         static XPLMDataRef r2 = XPLMFindDataRef("sim/operation/failures/rel_ice_pitot_heat2");
         static XPLMDataRef r3 = XPLMFindDataRef("sim/operation/failures/rel_ice_pitot_heat_stby");
         if (r1)
           XPLMSetDatai(r1, v);
         if (r2)
           XPLMSetDatai(r2, v);
         if (r3)
           XPLMSetDatai(r3, v);
       },
       "Pitot heat failure (0=ok, 1=failed)"},

      // Panel failure transponder (FS2002+)
      {0x3BE4, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_xpndr");
         put<uint8_t>(dst, static_cast<uint8_t>((r ? XPLMGetDatai(r) : 0) != 0 ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_xpndr");
         if (r)
           XPLMSetDatai(r, take<uint8_t>(src) ? 1 : 0);
       },
       "Transponder failure (0=ok, 1=failed)"},

      // Panel failure turn coord (FS2002+)
      {0x3BE5, 1,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r1 = XPLMFindDataRef("sim/operation/failures/rel_ss_tsi");
         static XPLMDataRef r2 = XPLMFindDataRef("sim/operation/failures/rel_cop_tsi");
         int v = (r1 ? XPLMGetDatai(r1) : 0) | (r2 ? XPLMGetDatai(r2) : 0);
         put<uint8_t>(dst, static_cast<uint8_t>(v != 0 ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         const int v = take<uint8_t>(src) ? 6 : 0;
         static XPLMDataRef r1 = XPLMFindDataRef("sim/operation/failures/rel_ss_tsi");
         static XPLMDataRef r2 = XPLMFindDataRef("sim/operation/failures/rel_cop_tsi");
         if (r1)
           XPLMSetDatai(r1, v);
         if (r2)
           XPLMSetDatai(r2, v);
       },
       "Turn co-ordinator failure (0=ok, 1=failed)"},

      // Panel failure vacuum (FS2002+)
      {0x3BE6, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r1 = XPLMFindDataRef("sim/operation/failures/rel_vacuum");
         static XPLMDataRef r2 = XPLMFindDataRef("sim/operation/failures/rel_vacuum2");
         static XPLMDataRef r3 = XPLMFindDataRef("sim/operation/failures/rel_vacuum_stby");
         int v = (r1 ? XPLMGetDatai(r1) : 0) | (r2 ? XPLMGetDatai(r2) : 0) | (r3 ? XPLMGetDatai(r3) : 0);
         put<uint8_t>(dst, static_cast<uint8_t>(v != 0 ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         const int v = take<uint8_t>(src) ? 1 : 0;
         static XPLMDataRef r1 = XPLMFindDataRef("sim/operation/failures/rel_vacuum");
         static XPLMDataRef r2 = XPLMFindDataRef("sim/operation/failures/rel_vacuum2");
         static XPLMDataRef r3 = XPLMFindDataRef("sim/operation/failures/rel_vacuum_stby");
         if (r1)
           XPLMSetDatai(r1, v);
         if (r2)
           XPLMSetDatai(r2, v);
         if (r3)
           XPLMSetDatai(r3, v);
       },
       "Vacuum failure (0=ok, 1=failed)"},

      // Panel failure VSI (FS2002+)
      {0x3BE7, 1,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_g_vvi");
         // static XPLMDataRef r1 = XPLMFindDataRef("sim/operation/failures/rel_ss_vvi");
         // static XPLMDataRef r2 = XPLMFindDataRef("sim/operation/failures/rel_cop_vvi");
         // int v = (r1 ? XPLMGetDatai(r1) : 0) | (r2 ? XPLMGetDatai(r2) : 0);
         int v = (r ? XPLMGetDatai(r) : 0);
         put<uint8_t>(dst, static_cast<uint8_t>(v != 0 ? 1 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         const int v = take<uint8_t>(src) ? 1 : 0;
         static XPLMDataRef r = XPLMFindDataRef("sim/operation/failures/rel_g_vvi");
         // static XPLMDataRef r1 = XPLMFindDataRef("sim/operation/failures/rel_ss_vvi");
         // static XPLMDataRef r2 = XPLMFindDataRef("sim/operation/failures/rel_cop_vvi");
         if (r)
           XPLMSetDatai(r, v);
         // if (r1) XPLMSetDatai(r1, v);
         // if (r2) XPLMSetDatai(r2, v);
       },
       "VSI failure (0=ok, 1=failed)"},
//
//       // SimConnect reconnection count
//       {0x3BF6, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BF6");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "SimConnect reconnection count"},

      // Current AIR file — String up to 256 bytes, zero terminated, giving
      // pathname of current AIR file, from "Aircraft\" .... to ..." .AIR".
      // Priovided by FSUIPC.
      {0x3C00, 256,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         char acfFile[256] = {};
         char acfDir[512] = {};
         XPLMGetNthAircraftModel(0, acfFile, acfDir);
         // In X-Plane 12, outPath (acfDir) already contains the full path including
         // the filename (e.g. "C:\X-Plane 12\Aircraft\...\Cessna_172SP.acf").
         write_cstr(dst, 256, acfDir);
       },
       nullptr,
       "Aircraft path (full)"},

      // Aircraft name string — String of up to 256 characters giving the
      // current aircraft name (in FS2k only).
      {0x3D00, 256,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         std::memset(dst, 0, 256);
         static XPLMDataRef r = XPLMFindDataRef("sim/aircraft/view/acf_descrip");
         if (r)
           XPLMGetDatab(r, dst, 0, 255);
         dst[255] = 0;
       },
       nullptr,
       "Aircraft title (256 chars)"},

      // Folder path to Flight Sim — Provides full path details to the main
      // FS folder, in UNC ("Iniversal Naming convention") format when the PC
      // is on a Windows Network, so remote applications can still find it.
      // (UNC form is \\pcname\ ....). The path ends in a '\' character and
      // zero terminator. (Max total length is 256)
      {0x3E00, 256,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &)
       {
         char buf[512] = {};
         XPLMGetSystemPath(buf);
         write_cstr(dst, 256, buf);
       },
       nullptr,
       "X-Plane install path (256 chars)"},
//
//       // Load/Save Flight Control — Set flight/situation filename to 3F04,
//       // then write 0 here to load, or 1 to save. Write 257 to save with a
//       // description (second string in 3F04). [FS98/FS2k)
//       {0x3F00, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3F00");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3F00");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Load/Save Flight Control"},
//
//       // Flight load count [FS2k] — Counter changes each time a flight is
//       // loaded in FS2k. The flight filepath can be read at 3F04.
//       {0x3F02, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3F02");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Flight load count [FS2k]"},
//
//       // Flight/situation name — FS2k only: read last loaded flight filepath
//       // (within FS's folder). 3F02 is incremented when a flight is loaded.
//       {0x3F04, 252,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3F04");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 252);
//          dst[0] = 0;
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3F04");
//          // TODO: string — XPLMSetDatab(r, (void*)src, 0, (int)sz);
//        },
//        "Flight/situation name"},
//
//       // PM / PFC cautions and warnings — See PM offsets documentation
//       {0x5530, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x5530");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x5530");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "PM / PFC cautions and warnings"},
//
//       // FSUIPC message window title — Only one window is supported, first
//       // title written here BEFORE any multi-line messages are sent, wins.
//       {0x6D60, 32,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x6D60");
//          // TODO: string — XPLMSetDatab(r, (void*)src, 0, (int)sz);
//        },
//        "FSUIPC message window title"},
//
//       // View: current view type — In Fs2004:
//       {0x8320, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x8320");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x8320");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "View: current view type"},
//
//       // View: Zoom settings — 64=x1, 128=x2 et cetera
//       {0x832C, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x832C");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x832C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "View: Zoom settings"},
//
//       // Spot view direction from user plane — Degrees TRUE, relative to user
//       // aircraft
//       {0x833C, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x833C");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x833C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Spot view direction from user plane"},
//
//       // Spot plane distance — distance from user aircraft
//       {0x8340, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x8340");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x8340");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Spot plane distance"},
//
//       // Spot plane transition — 0=gradual 1=direct
//       {0x8345, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x8345");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x8345");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Spot plane transition"},
//
//       // Spot plane altitude diff — Altitude relative to user aircraft
//       {0x8348, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x8348");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x8348");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Spot plane altitude diff"},
//
//       // AI runways or string data request signature — For runways-in-use
//       // datas, write the ICAO at D004 and a signature at the same time (one
//       // write of 8 bytes or else two in one FSUIPC_Process -- but the
//       // signature second).
//       {0xD000, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD000");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "AI runways or string data request signature"},
//
//       // TCAS ground range user in air — nm
//       {0xE068, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE068");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE068");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "TCAS ground range user in air"},
//
//       // TCAS ground range user on ground — nm
//       {0xE069, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE069");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE069");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "TCAS ground range user on ground"},
//
//       // TCAS ground id option — 0=tail, 1=airline+flt, 2=type, 3=title,
//       // 4=Type+tail, 5=model
//       {0xE06A, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE06A");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE06A");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "TCAS ground id option"},
//
//       // TCAS active traffic preference — 0=near ground preference, 1=active
//       // traffic preferred
//       {0xE06B, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE06B");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE06B");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "TCAS active traffic preference"},
//
//       // TCAS air range — nm
//       {0xF068, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF068");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF068");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "TCAS air range"},
//
//       // TCAS air id option — 0=tail, 1=airline+flt, 2=type, 3=title,
//       // 4=Type+tail, 5=model
//       {0xF06A, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF06A");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF06A");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "TCAS air id option"},

  }; // end table
  return table;
}
