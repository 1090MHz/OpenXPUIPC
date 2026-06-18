// SPDX-License-Identifier: LGPL-3.0-or-later
// fsuipc_offsets/AI-Traffic / TCAS.h — Production offset table
//
// 64 total offsets in this category
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

inline const std::vector<OffsetEntry> &fsuipc_offset_table_ai_traffic_tcas()
{
  static const std::vector<OffsetEntry> table = {

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
//       // AI ground traffic flight key (per file) — Unique identifier for this
//       // flight within the traffic file identified in next field
//       {0xD040, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD040");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI ground traffic flight key (per file)"},
//
//       // AI ground traffic file ID — Traffic IDs and their relationship to
//       // actual BGLs are logged in FSUIPC's log file and can be read via the
//       // facilities at offset 0FF0 and following.
//       {0xD044, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD044");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI ground traffic file ID"},
//
//       // AI ground traffic: aircraft pitch
//       {0xD046, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD046");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI ground traffic: aircraft pitch"},
//
//       // AI ground traffic Dep ICAO
//       {0xD048, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD048");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 4);
//          dst[0] = 0;
//        },
//        nullptr,
//        "AI ground traffic Dep ICAO"},
//
//       // AI ground traffic Arr ICAO
//       {0xD04C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD04C");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 4);
//          dst[0] = 0;
//        },
//        nullptr,
//        "AI ground traffic Arr ICAO"},
//
//       // AI ground traffic runway num — 0 if not assigned for take-off or
//       // landing. Else 1-36, or one of 37=N, 38=NE, 39=E, 40=SE, 41=S, 42=SW,
//       // 43=W, 44=NW
//       {0xD050, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD050");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI ground traffic runway num"},
//
//       // AI ground traffic runway desig — 0 or runway designator: 1=L, 2=R,
//       // 3=C, 4=W (water)
//       {0xD051, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD051");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI ground traffic runway desig"},
//
//       // AI ground traffic: aircraft bank
//       {0xD052, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD052");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI ground traffic: aircraft bank "},
//
//       // AI airborne traffic flght key (per file) — Unique identifier for
//       // this flight within the traffic file identified in next field
//       {0xD840, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD840");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI airborne traffic flght key (per file)"},
//
//       // AI airborne traffic file ID — Traffic IDs and their relationship to
//       // actual BGLs are logged in FSUIPC's log file and can be read via the
//       // facilities at offset 0FF0 and following.
//       {0xD844, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD844");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI airborne traffic file ID"},
//
//       // AI airborne traffic: aircraft pitch
//       {0xD846, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD846");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI airborne traffic: aircraft pitch"},
//
//       // AI airborne traffic Dep ICAO
//       {0xD848, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD848");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 4);
//          dst[0] = 0;
//        },
//        nullptr,
//        "AI airborne traffic Dep ICAO"},
//
//       // AI airborne traffic Arr ICAO
//       {0xD84C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD84C");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 4);
//          dst[0] = 0;
//        },
//        nullptr,
//        "AI airborne traffic Arr ICAO"},
//
//       // AI airborne traffic runway num — 0 if not assigned for take-off or
//       // landing. Else 1-36, or one of 37=N, 38=NE, 39=E, 40=SE, 41=S, 42=SW,
//       // 43=W, 44=NW
//       {0xD850, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD850");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI airborne traffic runway num"},
//
//       // AI airborne traffic runway desig — 0 or runway designator: 1=L, 2=R,
//       // 3=C, 4=W (water)
//       {0xD851, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD851");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI airborne traffic runway desig"},
//
//       // AI airborne traffic: aircraft bank
//       {0xD852, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xD852");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI airborne traffic: aircraft bank"},
//
//       // AI ground traffic slot size — = 40 at present. Not likely to change!
//       {0xE000, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE000");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI ground traffic slot size"},
//
//       // AI ground traffic slot count — = 96. Not likely to change
//       {0xE002, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE002");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI ground traffic slot count"},
//
//       // AI ground traffic slots used so far
//       {0xE004, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE004");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI ground traffic slots used so far"},
//
//       // AI ground traffic changes counter
//       {0xE006, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE006");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI ground traffic changes counter"},
//
//       // AI ground traffic slot changed ctr
//       {0xE008, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE008");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI ground traffic slot changed ctr"},
//
//       // AI ground traffic id (0=empty slot)
//       {0xE080, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE080");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI ground traffic id (0=empty slot)"},
//
//       // AI ground traffic Latitude
//       {0xE084, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE084");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "AI ground traffic Latitude"},
//
//       // AI ground traffic Longitude
//       {0xE088, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE088");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "AI ground traffic Longitude"},
//
//       // AI ground traffic Altitude
//       {0xE08C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE08C");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "AI ground traffic Altitude"},
//
//       // AI ground traffic Heading (True)
//       {0xE090, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE090");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI ground traffic Heading (True)"},
//
//       // AI ground traffic GS (k)
//       {0xE092, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE092");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI ground traffic GS (k)"},
//
//       // AI ground traffic VS (fpm)
//       {0xE094, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE094");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI ground traffic VS (fpm)"},
//
//       // AI ground traffic ATC id
//       {0xE096, 15,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE096");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 15);
//          dst[0] = 0;
//        },
//        nullptr,
//        "AI ground traffic ATC id"},
//
//       // AI ground traffic state (FS2004) — Zero on FS2002. On FS2004, one
//       // of:
//       {0xE0A5, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE0A5");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI ground traffic state (FS2004)"},
//
//       // AI ground traffic COM1 freq — The COM1 frequency set in the AI
//       // aircraft's radio. (0Xaabb as in 1aa.bb)
//       {0xE0A6, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xE0A6");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "AI ground traffic COM1 freq"},
//
//       // TCAS traffic slot size — = 40 at present. Not likely to change!
//       {0xF000, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF000");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "TCAS traffic slot size"},
//
//       // TCAS traffic slot count — = 96. Not likely to change
//       {0xF002, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF002");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "TCAS traffic slot count"},
//
//       // TCAS traffic slots used so far
//       {0xF004, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF004");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "TCAS traffic slots used so far"},
//
//       // TCAS traffic changes counter
//       {0xF006, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF006");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "TCAS traffic changes counter"},
//
//       // TCAS traffic slot changed ctr
//       {0xF008, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF008");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "TCAS traffic slot changed ctr"},
//
//       // TCAS traffic id (0=empty slot)
//       {0xF080, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF080");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "TCAS traffic id (0=empty slot)"},
//
//       // TCAS traffic Latitude
//       {0xF084, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF084");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "TCAS traffic Latitude"},
//
//       // TCAS traffic Longitude
//       {0xF088, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF088");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "TCAS traffic Longitude"},
//
//       // TCAS traffic Altitude
//       {0xF08C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF08C");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "TCAS traffic Altitude"},
//
//       // TCAS traffic Heading (True)
//       {0xF090, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF090");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "TCAS traffic Heading (True)"},
//
//       // TCAS traffic GS (k)
//       {0xF092, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF092");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "TCAS traffic GS (k)"},
//
//       // TCAS traffic VS (fpm)
//       {0xF094, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF094");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "TCAS traffic VS (fpm)"},
//
//       // TCAS traffic ATC id
//       {0xF096, 15,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF096");
//          // TODO: string — XPLMGetDatab(r, (char*)dst, 0, 15);
//          dst[0] = 0;
//        },
//        nullptr,
//        "TCAS traffic ATC id"},
//
//       // TCAS traffic state (FS2004) — Zero on FS2002. On FS2004, one of:
//       {0xF0A5, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF0A5");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "TCAS traffic state (FS2004)"},
//
//       // TCAS traffic COM1 freq — The COM1 frequency set in the AI aircraft's
//       // radio. (0Xaabb as in 1aa.bb)
//       {0xF0A6, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0xF0A6");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "TCAS traffic COM1 freq"},

  }; // end table
  return table;
}
