// SPDX-License-Identifier: GPL-3.0-or-later
// fsuipc_offsets/Hydraulics.h — Production offset table
//
// 1 total offsets in this category
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

inline const std::vector<OffsetEntry> &fsuipc_offset_table_hydraulics()
{
  static const std::vector<OffsetEntry> table = {

//
//       // ===== Hydraulics =============================================
//
//       // Hydraulic pump switches — Bit 0 (2^0) = pump 1 Bit 1 (2^1) = pump 2
//       // Bit 2 (2^2) = pump 3 Bit 3 (2^3) = pump 4
//       {0x341E, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x341E");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x341E");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Hydraulic pump switches"},

  }; // end table
  return table;
}
