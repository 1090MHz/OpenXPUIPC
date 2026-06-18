// SPDX-License-Identifier: GPL-3.0-or-later
// fsuipc_offsets/Fuel.h — Production offset table
//
// 38 total offsets in this category
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

inline const std::vector<OffsetEntry> &fsuipc_offset_table_fuel()
{
  static const std::vector<OffsetEntry> table = {

//       {0x0AF4, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0AF4");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fuel weight"},

      // Fuel Centre Level (%) — 100% = 128 x 65536
      {0x0B74, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h63 = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         float _fv63 = 0.0f;
         if (r_h63)
           XPLMGetDatavf(r_h63, &_fv63, 2, 1);
         float ratio = _fv63;
         static XPLMDataRef r_h64 = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         float total = (r_h64 ? XPLMGetDataf(r_h64) : 0.0f);
         float cap = conv::lbs_to_kg(ratio * total); // total is in lbs; cap in kg to match m_fuel
         if (cap <= 0.0f)
         {
           put<int32_t>(dst, 0);
           return;
         }
         static XPLMDataRef r_h65 = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         float _fv65 = 0.0f;
         if (r_h65)
           XPLMGetDatavf(r_h65, &_fv65, 2, 1);
         float wt = _fv65;
         put<int32_t>(dst, static_cast<int32_t>(wt / cap * 128.0f * 65536.0f));
       },
       nullptr,
       "Center tank fuel level"},

      // Fuel Centre Capacity — US Gallons
      {0x0B78, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h66 = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         float _fv66 = 0.0f;
         if (r_h66)
           XPLMGetDatavf(r_h66, &_fv66, 2, 1);
         float ratio = _fv66;
         static XPLMDataRef r_h67 = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         float total = (r_h67 ? XPLMGetDataf(r_h67) : 0.0f); // total is in lbs
         put<int32_t>(dst, static_cast<int32_t>(conv::lbs_to_gallons(ratio * total)));
       },
       nullptr,
       "Center tank fuel capacity"},

      // Fuel Left Main Level (%) — 100% = 128 x 65536
      {0x0B7C, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h68 = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         float _fv68 = 0.0f;
         if (r_h68)
           XPLMGetDatavf(r_h68, &_fv68, 0, 1);
         float ratio = _fv68;
         static XPLMDataRef r_h69 = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         float total = (r_h69 ? XPLMGetDataf(r_h69) : 0.0f);
         float cap = conv::lbs_to_kg(ratio * total); // total is in lbs; cap in kg to match m_fuel
         if (cap <= 0.0f)
         {
           put<int32_t>(dst, 0);
           return;
         }
         static XPLMDataRef r_h70 = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         float _fv70 = 0.0f;
         if (r_h70)
           XPLMGetDatavf(r_h70, &_fv70, 0, 1);
         float wt = _fv70;
         put<int32_t>(dst, static_cast<int32_t>(wt / cap * 128.0f * 65536.0f));
       },
       nullptr,
       "Left tank fuel level"},

      // Fuel Left Main Capacity — US Gallons
      {0x0B80, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h71 = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         float _fv71 = 0.0f;
         if (r_h71)
           XPLMGetDatavf(r_h71, &_fv71, 0, 1);
         float ratio = _fv71;
         static XPLMDataRef r_h72 = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         float total = (r_h72 ? XPLMGetDataf(r_h72) : 0.0f); // total is in lbs
         put<int32_t>(dst, static_cast<int32_t>(conv::lbs_to_gallons(ratio * total)));
       },
       nullptr,
       "Left tank fuel capacity"},
//
//       // Fuel Left Aux Level (%) — 100% = 128 x 65536
//       {0x0B84, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0B84");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0B84");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int32_t>(src)));
//        },
//        "Fuel Left Aux Level (%)"},
//
//       // Fuel Left Aux Capacity — US Gallons
//       {0x0B88, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0B88");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fuel Left Aux Capacity"},

      // Fuel Left Tip Level (%) — 100% = 128 x 65536
      {0x0B8C, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h73 = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         float _fv73 = 0.0f;
         if (r_h73)
           XPLMGetDatavf(r_h73, &_fv73, 3, 1);
         float ratio = _fv73;
         static XPLMDataRef r_h74 = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         float total = (r_h74 ? XPLMGetDataf(r_h74) : 0.0f);
         float cap = conv::lbs_to_kg(ratio * total); // total is in lbs; cap in kg to match m_fuel
         if (cap <= 0.0f)
         {
           put<int32_t>(dst, 0);
           return;
         }
         static XPLMDataRef r_h75 = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         float _fv75 = 0.0f;
         if (r_h75)
           XPLMGetDatavf(r_h75, &_fv75, 3, 1);
         float wt = _fv75;
         put<int32_t>(dst, static_cast<int32_t>(wt / cap * 128.0f * 65536.0f));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h73 = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         float _fv73 = 0.0f;
         if (r_h73)
           XPLMGetDatavf(r_h73, &_fv73, 3, 1);
         float ratio = _fv73;
         static XPLMDataRef r_h74 = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         float total = (r_h74 ? XPLMGetDataf(r_h74) : 0.0f); // total is in lbs
         float cap = conv::lbs_to_kg(ratio * total);         // convert to kg to match m_fuel
         if (cap <= 0.0f)
         {
           return;
         }
         float level = take<int32_t>(src) / (128.0f * 65536.0f);
         level = std::clamp(level, 0.0f, 1.0f);
         static XPLMDataRef r_h75 = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         {
           float _sv75 = level * cap;
           if (r_h75)
             XPLMSetDatavf(r_h75, &_sv75, 3, 1);
         }
       },
       "Left tip tank fuel level (write)"},
//
//       // Fuel Left Tip Capacity — US Gallons
//       {0x0B90, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0B90");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fuel Left Tip Capacity"},

      // Fuel Right Main Level (%) — 100% = 128 x 65536
      {0x0B94, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h76 = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         float _fv76 = 0.0f;
         if (r_h76)
           XPLMGetDatavf(r_h76, &_fv76, 1, 1);
         float ratio = _fv76;
         static XPLMDataRef r_h77 = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         float total = (r_h77 ? XPLMGetDataf(r_h77) : 0.0f);
         float cap = conv::lbs_to_kg(ratio * total); // total is in lbs; cap in kg to match m_fuel
         if (cap <= 0.0f)
         {
           put<int32_t>(dst, 0);
           return;
         }
         static XPLMDataRef r_h78 = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         float _fv78 = 0.0f;
         if (r_h78)
           XPLMGetDatavf(r_h78, &_fv78, 1, 1);
         float wt = _fv78;
         put<int32_t>(dst, static_cast<int32_t>(wt / cap * 128.0f * 65536.0f));
       },
       nullptr,
       "Right tank fuel level"},

      // Fuel Right Main Capacity — US Gallons
      {0x0B98, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h79 = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         float _fv79 = 0.0f;
         if (r_h79)
           XPLMGetDatavf(r_h79, &_fv79, 1, 1);
         float ratio = _fv79;
         static XPLMDataRef r_h80 = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         float total = (r_h80 ? XPLMGetDataf(r_h80) : 0.0f); // total is in lbs
         put<int32_t>(dst, static_cast<int32_t>(conv::lbs_to_gallons(ratio * total)));
       },
       nullptr,
       "Right tank fuel capacity"},
//
//       // Fuel Right Aux Level (%) — 100% = 128 x 65536
//       {0x0B9C, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0B9C");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0B9C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int32_t>(src)));
//        },
//        "Fuel Right Aux Level (%)"},
//
//       // Fuel Right Aux Capacify — US Gallons
//       {0x0BA0, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0BA0");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fuel Right Aux Capacify"},
//
//       // Fuel Right Tip Level (%) — 100% = 128 x 65536
//       {0x0BA4, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0BA4");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0BA4");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int32_t>(src)));
//        },
//        "Fuel Right Tip Level (%)"},
//
//       // Fuel Right Tip Capacity — US Gallons
//       {0x0BA8, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0BA8");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fuel Right Tip Capacity"},
//
//       // Fuel: no. of selectors (FSX)
//       {0x123E, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x123E");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fuel: no. of selectors (FSX)"},
//
//       // Fuel: unlimited fuel (FSX) — Fuel: unlimited fuel is set in
//       // "realism" if this is non-zero
//       {0x123F, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x123F");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fuel: unlimited fuel (FSX)"},
//
//       // Fuel: total capacity (FSX) — In U.S. Gallons
//       {0x1240, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1240");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fuel: total capacity (FSX)"},
//
//       // Fuel centre2 level (%) (FS2000+)
//       {0x1244, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1244");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1244");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int32_t>(src)));
//        },
//        "Fuel centre2 level (%) (FS2000+)"},
//
//       // Fuel centre2 capacity (FS2000+) — US Gallons
//       {0x1248, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1248");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fuel centre2 capacity (FS2000+)"},
//
//       // Fuel centre3 level (%) (FS2000+)
//       {0x124C, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x124C");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x124C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int32_t>(src)));
//        },
//        "Fuel centre3 level (%) (FS2000+)"},
//
//       // Fuel centre3 capacity (FS2000+) — US Gallons
//       {0x1250, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1250");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fuel centre3 capacity (FS2000+)"},
//
//       // Fuel external1 level (%) (FS2000+)
//       {0x1254, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1254");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1254");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int32_t>(src)));
//        },
//        "Fuel external1 level (%) (FS2000+)"},
//
//       // Fuel external1 capacity (FS2000+) — US Gallons
//       {0x1258, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1258");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fuel external1 capacity (FS2000+)"},
//
//       // Fuel external2 level (%) (FS2000+)
//       {0x125C, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x125C");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x125C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int32_t>(src)));
//        },
//        "Fuel external2 level (%) (FS2000+)"},
//
//       // Fuel external2 capacity (FS2000+) — US Gallons
//       {0x1260, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1260");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fuel external2 capacity (FS2000+)"},
//
//       // Fuel total quantity (FSX) — US Gallons
//       {0x1264, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1264");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fuel total quantity (FSX)"},
//
//       // Fuel selected quantity (FSX) — US Gallons
//       {0x1268, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1268");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fuel selected quantity (FSX)"},
//
//       // Fuel total weight (FSX) — Pounds
//       {0x126C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x126C");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fuel total weight (FSX)"},
//
//       // Fuel flow at cruise, est (FSX) — Pounds / hour
//       {0x1270, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1270");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fuel flow at cruise, est (FSX)"},
//
//       // Empty weight (FSX) — Aircraft weight without payload or fuel. In
//       // pounds * 256
//       {0x1330, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x1330");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Empty weight (FSX)"},

      // Max gross weight (FSX) — pounds * 256
      {0x1334, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/aircraft/weight/acf_m_max");
         float kg = r ? XPLMGetDataf(r) : 0.0f;
         put<int32_t>(dst, static_cast<int32_t>(kg * 2.20462f * 256.0f));
       },
       nullptr,
       "Max gross weight (lbs*256)"},
//
//       // Fuel pump switches (separate per engine)) — FS2000/FS2002 only.
//       // Separate bits for each fuel pump: 2^0=1, 2^1=2, 2^2=3, 2^3=4.
//       {0x3125, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3125");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3125");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Fuel pump switches (separate per engine))"},
//
//       // Fuel crossfeed switch
//       {0x341F, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x341F");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x341F");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Fuel crossfeed switch"},
//
//       // Engine 1 Fuel Valve [FS2002+] — BOOLEAN (1 = open, 0 = closed)
//       {0x3590, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3590");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3590");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Engine 1 Fuel Valve [FS2002+]"},
//
//       // Engine 2 Fuel Valve [FS2002+] — BOOLEAN (1 = open, 0 = closed]
//       {0x3594, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3594");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3594");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Engine 2 Fuel Valve [FS2002+]"},
//
//       // Engine 3 Fuel Valve [FS2002+] — BOOLEAN (1 = open, 0 = closed)
//       {0x3598, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3598");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3598");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Engine 3 Fuel Valve [FS2002+]"},
//
//       // Engine 4 Fuel Valve [FS2002+] — BOOLEAN (1 = open, 0 =closed)
//       {0x359C, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x359C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x359C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Engine 4 Fuel Valve [FS2002+]"},

  }; // end table
  return table;
}
