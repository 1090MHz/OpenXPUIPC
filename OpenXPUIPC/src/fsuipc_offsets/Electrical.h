// SPDX-License-Identifier: GPL-3.0-or-later
// fsuipc_offsets/Electrical.h — Production offset table
//
// 20 total offsets in this category
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

inline const std::vector<OffsetEntry> &fsuipc_offset_table_electrical()
{
  static const std::vector<OffsetEntry> table = {

//       {0x281C, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Master Battery Switch"},
//
//       // Total load Amps
//       {0x2824, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Total load Amps"},
//
//       // Battery Load
//       {0x282C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Battery Load"},
//
//       // Battery Volt.
//       {0x2834, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Battery Volt."},
//
//       // Main Bus Volt.
//       {0x2840, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Main Bus Volt."},
//
//       // Main Bus Amps
//       {0x2848, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Main Bus Amps"},
//
//       // Avionics Bus Volt.
//       {0x2850, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Avionics Bus Volt."},
//
//       // Avionics Bus Amps
//       {0x2858, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Avionics Bus Amps"},
//
//       // Hot Battery Bus Volt.
//       {0x2860, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Hot Battery Bus Volt."},
//
//       // Hot Battery Bus Amps
//       {0x2868, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Hot Battery Bus Amps"},
//
//       // Battery Bus Volt.
//       {0x2870, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Battery Bus Volt."},
//
//       // Battery Bus Amps
//       {0x2878, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Battery Bus Amps"},
//
//       // Generator Alternator 1 Bus Volt.
//       {0x2880, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Generator Alternator 1 Bus Volt."},
//
//       // Generator Alternator 1 Bus Amps
//       {0x2888, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Generator Alternator 1 Bus Amps"},
//
//       // Generator Alternator 2 Bus Volt.
//       {0x2890, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Generator Alternator 2 Bus Volt."},
//
//       // Generator Alternator 2 Bus Amps
//       {0x2898, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Generator Alternator 2 Bus Amps"},
//
//       // Generator Alternator 3 Bus Volt.
//       {0x28A0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Generator Alternator 3 Bus Volt."},
//
//       // Generator Alternator 3 Bus Amps
//       {0x28A8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Generator Alternator 3 Bus Amps"},
//
//       // Generator Alternator 4 Bus Volt.
//       {0x28B0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Generator Alternator 4 Bus Volt."},
//
//       // Generator Alternator 4 Bus Amps
//       {0x28B8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Generator Alternator 4 Bus Amps"},

  }; // end table
  return table;
}
