// SPDX-License-Identifier: GPL-3.0-or-later
// fsuipc_offsets/AI_Traffic_TCAS.h — Legacy, unregistered TCAS stubs
// Implemented TCAS table offsets are registered from AI_Traffic_TCAS_tables.h.
//
// TO IMPLEMENT A NEW OFFSET:
//   1. Find the commented-out entry below
//   2. Uncomment it
//   3. Replace TODO dataref with real X-Plane DataRef logic
//   4. Test and verify
//
#pragma once

#include "offset_types.h" // OffsetEntry, put<>, take<>, DataRefCache, conv::

inline const std::vector<OffsetEntry> &fsuipc_offset_table_ai_traffic_tcas()
{
  static const std::vector<OffsetEntry> table = {

//
//       // ===== AI-Traffic / TCAS ======================================
//
//       // AI ground traffic ATC id
//       {0x0000, 15,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0000");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 15);
//          dst[0] = 0;
//        },
//        nullptr,
//        "AI ground traffic ATC id"},
//
//       // TCAS injection Id — Write a TCAS_DATA structure here to have it
//       // added to the TCAS table at F080.
//       {0x1F80, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1F80");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int32_t>(src)));
//        },
//        "TCAS injection Id"},
//
//       // TCAS injection Latitude
//       {0x1F84, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1F84");
//          if (r)
//            XPLMSetDataf(r, static_cast<float>(take<float>(src)));
//        },
//        "TCAS injection Latitude"},
//
//       // TCAS injection Longitude
//       {0x1F88, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1F88");
//          if (r)
//            XPLMSetDataf(r, static_cast<float>(take<float>(src)));
//        },
//        "TCAS injection Longitude"},
//
//       // TCAS injection Alt
//       {0x1F8C, 4,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1F8C");
//          if (r)
//            XPLMSetDataf(r, static_cast<float>(take<float>(src)));
//        },
//        "TCAS injection Alt"},
//
//       // TCAS injection Hdg True — 0-65535 ised for 0-359.9999 degrees
//       {0x1F90, 2,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1F90");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "TCAS injection Hdg True"},
//
//       // TCAS injection GS
//       {0x1F92, 2,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1F92");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "TCAS injection GS"},
//
//       // TCAS injection VS — fpm
//       {0x1F94, 2,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1F94");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "TCAS injection VS"},
//
//       // TCAS injection ATC ident string
//       {0x1F96, 15,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1F96");
//          // TODO: string — XPLMSetDatab(r, (void*)src, 0, (int)sz);
//        },
//        "TCAS injection ATC ident string"},
//
//       // TCAS injection state flag — Normally zero, but can be one of these
//       // to indicate state to any TCAS display programs:
//       {0x1FA5, 1,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1FA5");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "TCAS injection state flag"},
//
//       // TCAS injection COM1 freq — COM1 frequency set in the AI aircraft's
//       // radio. (0Xaabb as in 1aa.bb). Probably not relevant for injected
//       // aircraft data.
//       {0x1FA6, 2,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1FA6");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "TCAS injection COM1 freq"},
//
//       // AI runways request ICAO or string data command
//       {0xD004, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD004");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD004");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "AI runways request ICAO or string data command"},
//
//       // AI runways request timestamp
//       {0xD008, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD008");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI runways request timestamp"},
//
//       // AI runways request -- 1st Rwy Num — Runways are numbered 1-36, with
//       // special numbers as follows:
//       {0xD00C, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD00C");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI runways request -- 1st Rwy Num"},
//
//       // AI runways request -- 1st Rwy Desig — 0=none , 1=L, 2=R, 3=C, 4=W
//       {0xD00D, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD00D");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI runways request -- 1st Rwy Desig"},
//
//       // AI runways request -- 2nd Rwy Num — Runways are numbered 1-36, with
//       // special numbers as follows:
//       {0xD00E, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD00E");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI runways request -- 2nd Rwy Num"},
//
//       // AI runways request -- 2nd Rwy Desig — 0=none , 1=L, 2=R, 3=C, 4=W
//       {0xD00F, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD00F");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI runways request -- 2nd Rwy Desig"},
//
//       // AI string data read area
//       {0xD010, 48,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD010");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 48);
//          dst[0] = 0;
//        },
//        nullptr,
//        "AI string data read area"},
//
      // Ground extra fields are served in bulk at 0xD040 by
      // fsuipc_offset_table_ai_traffic_tcas_tables().

      // Airborne extra fields are served in bulk at 0xD840 by
      // fsuipc_offset_table_ai_traffic_tcas_tables().

      // Ground and airborne slot/config offsets are provided by the bulk
      // handlers in AI_Traffic_TCAS_tables.h.

  }; // end table
  return table;
}
