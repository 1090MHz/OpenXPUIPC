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
#include "impl/aircraft_config.h" // Tank name parsing
#include <algorithm>      // std::clamp

// ===== Fuel Tank Role Mapper ================================================
// Dynamically maps FSUIPC positional tank roles to X-Plane tank array indices.
// Rebuilt when XPLM_MSG_PLANE_LOADED is received (via aircraft_config::reload()).
//
// Uses a hybrid approach:
//   1. PRIMARY: Parse tank names from ACF file (P acf/_tank_name/0-8) for keywords:
//      "left", "right", "center/centre", "aux", "tip", "main", "external", etc.
//   2. FALLBACK: If names are missing/unclear, classify by physical position:
//      |X| < 0.3 m  — centre tanks, sorted by Z ascending (most forward = centre)
//      X < -0.3 m   — left tanks,   sorted by |X| ascending (main, aux, tip)
//      X > +0.3 m   — right tanks,  sorted by |X| ascending (main, aux, tip)
//      overflow beyond 3rd per side — external1/2
//
// Tanks with acf_tank_rat == 0 are unused slots and are skipped.

enum FuelTankRole
{
  FTR_LEFT_MAIN = 0, FTR_LEFT_AUX,  FTR_LEFT_TIP,
  FTR_RIGHT_MAIN,    FTR_RIGHT_AUX, FTR_RIGHT_TIP,
  FTR_CENTRE,        FTR_CENTRE2,   FTR_CENTRE3,
  FTR_EXT1,          FTR_EXT2,
  FTR_COUNT
};

struct FuelTankMap
{
  int8_t idx[FTR_COUNT]; // X-Plane tank index for each role; -1 = not present

  struct Slot { int8_t xp_idx; float sortkey; };

  FuelTankMap() { for (int i = 0; i < FTR_COUNT; ++i) idx[i] = -1; }

  void rebuild()
  {
    for (int i = 0; i < FTR_COUNT; ++i) idx[i] = -1;

    static XPLMDataRef r_x   = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_X");
    static XPLMDataRef r_z   = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_Z");
    static XPLMDataRef r_rat = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
    if (!r_x || !r_rat) return;

    constexpr int N = 9;
    float tx[N] = {}, tz[N] = {}, rat[N] = {};
    XPLMGetDatavf(r_x,   tx,  0, N);
    if (r_z) XPLMGetDatavf(r_z, tz, 0, N);
    XPLMGetDatavf(r_rat, rat, 0, N);

    // === PHASE 1: Try name-based classification (primary method) ===
    int name_matched = 0;
    for (int i = 0; i < N; ++i)
    {
      if (rat[i] <= 0.0f) continue;
      
      const char* name = aircraft_config::get_tank_name(i);
      if (!name || name[0] == '\0') continue;
      
      uint16_t flags = aircraft_config::classify_tank_name(name);
      if (flags == 0) continue; // No recognizable keywords
      
      bool has_left = flags & (1 << 0);
      bool has_right = flags & (1 << 1);
      bool has_center = flags & (1 << 2);
      bool has_aux = flags & (1 << 3);
      bool has_tip = flags & (1 << 4);
      bool has_main = flags & (1 << 5);
      bool has_external = flags & (1 << 6);
      
      // Assign based on name keywords (prefer specific roles)
      if (has_left && has_tip && idx[FTR_LEFT_TIP] == -1) {
        idx[FTR_LEFT_TIP] = i; ++name_matched;
      } else if (has_left && has_aux && idx[FTR_LEFT_AUX] == -1) {
        idx[FTR_LEFT_AUX] = i; ++name_matched;
      } else if (has_left && (has_main || (!has_aux && !has_tip)) && idx[FTR_LEFT_MAIN] == -1) {
        idx[FTR_LEFT_MAIN] = i; ++name_matched;
      } else if (has_right && has_tip && idx[FTR_RIGHT_TIP] == -1) {
        idx[FTR_RIGHT_TIP] = i; ++name_matched;
      } else if (has_right && has_aux && idx[FTR_RIGHT_AUX] == -1) {
        idx[FTR_RIGHT_AUX] = i; ++name_matched;
      } else if (has_right && (has_main || (!has_aux && !has_tip)) && idx[FTR_RIGHT_MAIN] == -1) {
        idx[FTR_RIGHT_MAIN] = i; ++name_matched;
      } else if (has_center && idx[FTR_CENTRE] == -1) {
        idx[FTR_CENTRE] = i; ++name_matched;
      } else if (has_center && idx[FTR_CENTRE2] == -1) {
        idx[FTR_CENTRE2] = i; ++name_matched;
      } else if (has_center && idx[FTR_CENTRE3] == -1) {
        idx[FTR_CENTRE3] = i; ++name_matched;
      } else if (has_external && idx[FTR_EXT1] == -1) {
        idx[FTR_EXT1] = i; ++name_matched;
      } else if (has_external && idx[FTR_EXT2] == -1) {
        idx[FTR_EXT2] = i; ++name_matched;
      }
    }

    // === PHASE 2: Position-based fallback for unmapped tanks ===
    // Only use position heuristic if name-based didn't fully classify
    if (name_matched < N) // Some tanks remain unmapped
    {
      Slot left[N], right[N], centre[N];
      int nl = 0, nr = 0, nc = 0;
      constexpr float CTR_THRESH = 0.3f; // metres

      for (int i = 0; i < N; ++i)
      {
        if (rat[i] <= 0.0f) continue;
        
        // Skip if already assigned by name
        bool already_assigned = false;
        for (int r = 0; r < FTR_COUNT; ++r) {
          if (idx[r] == i) {
            already_assigned = true;
            break;
          }
        }
        if (already_assigned) continue;
        
        float x = tx[i];
        if      (x < -CTR_THRESH) left[nl++]   = {static_cast<int8_t>(i), -x};
        else if (x >  CTR_THRESH) right[nr++]  = {static_cast<int8_t>(i),  x};
        else                      centre[nc++] = {static_cast<int8_t>(i), tz[i]};
      }

      // Insertion-sort each group by sortkey ascending
      auto isort = [](Slot *a, int n) {
        for (int i = 1; i < n; ++i) {
          Slot k = a[i]; int j = i - 1;
          while (j >= 0 && a[j].sortkey > k.sortkey) { a[j + 1] = a[j]; --j; }
          a[j + 1] = k;
        }
      };
      isort(left, nl); isort(right, nr); isort(centre, nc);

      // Assign position-based fallback (only if slot not already filled by name)
      int li = 0, ri = 0, ci = 0;
      if (idx[FTR_LEFT_MAIN] == -1 && li < nl) idx[FTR_LEFT_MAIN] = left[li++].xp_idx;
      if (idx[FTR_LEFT_AUX] == -1 && li < nl)  idx[FTR_LEFT_AUX]  = left[li++].xp_idx;
      if (idx[FTR_LEFT_TIP] == -1 && li < nl)  idx[FTR_LEFT_TIP]  = left[li++].xp_idx;
      
      if (idx[FTR_RIGHT_MAIN] == -1 && ri < nr) idx[FTR_RIGHT_MAIN] = right[ri++].xp_idx;
      if (idx[FTR_RIGHT_AUX] == -1 && ri < nr)  idx[FTR_RIGHT_AUX]  = right[ri++].xp_idx;
      if (idx[FTR_RIGHT_TIP] == -1 && ri < nr)  idx[FTR_RIGHT_TIP]  = right[ri++].xp_idx;
      
      if (idx[FTR_CENTRE] == -1 && ci < nc)  idx[FTR_CENTRE]  = centre[ci++].xp_idx;
      if (idx[FTR_CENTRE2] == -1 && ci < nc) idx[FTR_CENTRE2] = centre[ci++].xp_idx;
      if (idx[FTR_CENTRE3] == -1 && ci < nc) idx[FTR_CENTRE3] = centre[ci++].xp_idx;

      // External tanks from position overflow
      if (idx[FTR_EXT1] == -1 && li < nl) idx[FTR_EXT1] = left[li++].xp_idx;
      else if (idx[FTR_EXT1] == -1 && ri < nr) idx[FTR_EXT1] = right[ri++].xp_idx;
      
      if (idx[FTR_EXT2] == -1 && li < nl) idx[FTR_EXT2] = left[li++].xp_idx;
      else if (idx[FTR_EXT2] == -1 && ri < nr) idx[FTR_EXT2] = right[ri++].xp_idx;
    }
  }
};

// Get the static fuel tank map (rebuilt on aircraft load via aircraft_config::reload())
inline FuelTankMap &fuel_tank_map()
{
  static FuelTankMap map;
  return map;
}

// Provide rebuild function for aircraft_config::detail to call
namespace aircraft_config::detail {
  inline void rebuild_fuel_tank_map()
  {
    ::fuel_tank_map().rebuild();
  }
}

inline const std::vector<OffsetEntry> &fsuipc_offset_table_fuel()
{
  static const std::vector<OffsetEntry> table = {


      // ===== Fuel ===================================================

      // Fuel weight — 256 * Lbs / Gal
      // Note: this means fuel weight per gallon — Weight of one gallon of fuel (256 * Lbs / Gal)
      // This is fuel density, NOT total fuel weight
      {0x0AF4, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Get fuel density based on engine type:
         // - Piston engines (recip carb/injected) use AvGas: 6.0 lbs/gal
         // - Jet/turbine engines use Jet-A: 6.699219 lbs/gal
         float density = conv::get_fuel_density_lbs_per_gallon();
         int16_t fsuipc_value = static_cast<int16_t>(density * 256.0f);
         put<int16_t>(dst, fsuipc_value);
       },
       nullptr,
       "Fuel density (lbs/gal * 256)"},

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
         float cap = ratio * total; // acf_m_fuel_tot is in kg, same units as m_fuel
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
         float total = (r_h67 ? XPLMGetDataf(r_h67) : 0.0f); // acf_m_fuel_tot is in kg
         put<int32_t>(dst, static_cast<int32_t>(conv::kg_to_gallons(ratio * total)));
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
         float cap = ratio * total; // acf_m_fuel_tot is in kg, same units as m_fuel
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
         float total = (r_h72 ? XPLMGetDataf(r_h72) : 0.0f); // acf_m_fuel_tot is in kg
         put<int32_t>(dst, static_cast<int32_t>(conv::kg_to_gallons(ratio * total)));
       },
       nullptr,
       "Left tank fuel capacity"},

      // Fuel Left Aux Level (%) — 100% = 128 x 65536
      {0x0B84, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_LEFT_AUX];
         if (ti < 0) { put<int32_t>(dst, 0); return; }
         static XPLMDataRef r_rat  = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot  = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         static XPLMDataRef r_fuel = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         float cap   = ratio * total;
         if (cap <= 0.0f) { put<int32_t>(dst, 0); return; }
         float wt = 0.0f;
         if (r_fuel) XPLMGetDatavf(r_fuel, &wt, ti, 1);
         put<int32_t>(dst, static_cast<int32_t>(wt / cap * 128.0f * 65536.0f));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_LEFT_AUX];
         if (ti < 0) return;
         static XPLMDataRef r_rat  = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot  = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         static XPLMDataRef r_fuel = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         float cap   = ratio * total;
         if (cap <= 0.0f) return;
         float level = take<int32_t>(src) / (128.0f * 65536.0f);
         level = std::clamp(level, 0.0f, 1.0f);
         float wt = level * cap;
         if (r_fuel) XPLMSetDatavf(r_fuel, &wt, ti, 1);
       },
       "Left aux tank fuel level"},

      // Fuel Left Aux Capacity — US Gallons
      {0x0B88, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_LEFT_AUX];
         if (ti < 0) { put<int32_t>(dst, 0); return; }
         static XPLMDataRef r_rat = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         put<int32_t>(dst, static_cast<int32_t>(conv::kg_to_gallons(ratio * total)));
       },
       nullptr,
       "Fuel Left Aux Capacity"},

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
         float cap = ratio * total; // acf_m_fuel_tot is in kg, same units as m_fuel
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
         float total = (r_h74 ? XPLMGetDataf(r_h74) : 0.0f);
         float cap = ratio * total; // acf_m_fuel_tot is in kg, same units as m_fuel
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

      // Fuel Left Tip Capacity — US Gallons
      {0x0B90, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_LEFT_TIP];
         if (ti < 0) { put<int32_t>(dst, 0); return; }
         static XPLMDataRef r_rat = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         put<int32_t>(dst, static_cast<int32_t>(conv::kg_to_gallons(ratio * total)));
       },
       nullptr,
       "Fuel Left Tip Capacity"},

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
         float cap = ratio * total; // acf_m_fuel_tot is in kg, same units as m_fuel
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
         float total = (r_h80 ? XPLMGetDataf(r_h80) : 0.0f); // acf_m_fuel_tot is in kg
         put<int32_t>(dst, static_cast<int32_t>(conv::kg_to_gallons(ratio * total)));
       },
       nullptr,
       "Right tank fuel capacity"},

      // Fuel Right Aux Level (%) — 100% = 128 x 65536
      {0x0B9C, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_RIGHT_AUX];
         if (ti < 0) { put<int32_t>(dst, 0); return; }
         static XPLMDataRef r_rat  = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot  = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         static XPLMDataRef r_fuel = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         float cap   = ratio * total;
         if (cap <= 0.0f) { put<int32_t>(dst, 0); return; }
         float wt = 0.0f;
         if (r_fuel) XPLMGetDatavf(r_fuel, &wt, ti, 1);
         put<int32_t>(dst, static_cast<int32_t>(wt / cap * 128.0f * 65536.0f));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_RIGHT_AUX];
         if (ti < 0) return;
         static XPLMDataRef r_rat  = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot  = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         static XPLMDataRef r_fuel = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         float cap   = ratio * total;
         if (cap <= 0.0f) return;
         float level = take<int32_t>(src) / (128.0f * 65536.0f);
         level = std::clamp(level, 0.0f, 1.0f);
         float wt = level * cap;
         if (r_fuel) XPLMSetDatavf(r_fuel, &wt, ti, 1);
       },
       "Right aux tank fuel level"},

      // Fuel Right Aux Capacity — US Gallons
      {0x0BA0, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_RIGHT_AUX];
         if (ti < 0) { put<int32_t>(dst, 0); return; }
         static XPLMDataRef r_rat = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         put<int32_t>(dst, static_cast<int32_t>(conv::kg_to_gallons(ratio * total)));
       },
       nullptr,
       "Right aux tank fuel capacity"},

      // Fuel Right Tip Level (%) — 100% = 128 x 65536
      {0x0BA4, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_RIGHT_TIP];
         if (ti < 0) { put<int32_t>(dst, 0); return; }
         static XPLMDataRef r_rat  = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot  = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         static XPLMDataRef r_fuel = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         float cap   = ratio * total;
         if (cap <= 0.0f) { put<int32_t>(dst, 0); return; }
         float wt = 0.0f;
         if (r_fuel) XPLMGetDatavf(r_fuel, &wt, ti, 1);
         put<int32_t>(dst, static_cast<int32_t>(wt / cap * 128.0f * 65536.0f));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_RIGHT_TIP];
         if (ti < 0) return;
         static XPLMDataRef r_rat  = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot  = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         static XPLMDataRef r_fuel = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         float cap   = ratio * total;
         if (cap <= 0.0f) return;
         float level = take<int32_t>(src) / (128.0f * 65536.0f);
         level = std::clamp(level, 0.0f, 1.0f);
         float wt = level * cap;
         if (r_fuel) XPLMSetDatavf(r_fuel, &wt, ti, 1);
       },
       "Right tip tank fuel level"},

      // Fuel Right Tip Capacity — US Gallons
      {0x0BA8, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_RIGHT_TIP];
         if (ti < 0) { put<int32_t>(dst, 0); return; }
         static XPLMDataRef r_rat = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         put<int32_t>(dst, static_cast<int32_t>(conv::kg_to_gallons(ratio * total)));
       },
       nullptr,
       "Right tip tank fuel capacity"},
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

      // Fuel centre2 level (%) (FS2000+)
      {0x1244, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_CENTRE2];
         if (ti < 0) { put<int32_t>(dst, 0); return; }
         static XPLMDataRef r_rat  = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot  = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         static XPLMDataRef r_fuel = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         float cap   = ratio * total;
         if (cap <= 0.0f) { put<int32_t>(dst, 0); return; }
         float wt = 0.0f;
         if (r_fuel) XPLMGetDatavf(r_fuel, &wt, ti, 1);
         put<int32_t>(dst, static_cast<int32_t>(wt / cap * 128.0f * 65536.0f));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_CENTRE2];
         if (ti < 0) return;
         static XPLMDataRef r_rat  = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot  = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         static XPLMDataRef r_fuel = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         float cap   = ratio * total;
         if (cap <= 0.0f) return;
         float level = take<int32_t>(src) / (128.0f * 65536.0f);
         level = std::clamp(level, 0.0f, 1.0f);
         float wt = level * cap;
         if (r_fuel) XPLMSetDatavf(r_fuel, &wt, ti, 1);
       },
       "Centre2 tank fuel level"},

      // Fuel centre2 capacity (FS2000+) — US Gallons
      {0x1248, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_CENTRE2];
         if (ti < 0) { put<int32_t>(dst, 0); return; }
         static XPLMDataRef r_rat = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         put<int32_t>(dst, static_cast<int32_t>(conv::kg_to_gallons(ratio * total)));
       },
       nullptr,
       "Centre2 tank fuel capacity"},

      // Fuel centre3 level (%) (FS2000+)
      {0x124C, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_CENTRE3];
         if (ti < 0) { put<int32_t>(dst, 0); return; }
         static XPLMDataRef r_rat  = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot  = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         static XPLMDataRef r_fuel = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         float cap   = ratio * total;
         if (cap <= 0.0f) { put<int32_t>(dst, 0); return; }
         float wt = 0.0f;
         if (r_fuel) XPLMGetDatavf(r_fuel, &wt, ti, 1);
         put<int32_t>(dst, static_cast<int32_t>(wt / cap * 128.0f * 65536.0f));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_CENTRE3];
         if (ti < 0) return;
         static XPLMDataRef r_rat  = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot  = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         static XPLMDataRef r_fuel = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         float cap   = ratio * total;
         if (cap <= 0.0f) return;
         float level = take<int32_t>(src) / (128.0f * 65536.0f);
         level = std::clamp(level, 0.0f, 1.0f);
         float wt = level * cap;
         if (r_fuel) XPLMSetDatavf(r_fuel, &wt, ti, 1);
       },
       "Centre3 tank fuel level"},

      // Fuel centre3 capacity (FS2000+) — US Gallons
      {0x1250, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_CENTRE3];
         if (ti < 0) { put<int32_t>(dst, 0); return; }
         static XPLMDataRef r_rat = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         put<int32_t>(dst, static_cast<int32_t>(conv::kg_to_gallons(ratio * total)));
       },
       nullptr,
       "Centre3 tank fuel capacity"},

      // Fuel external1 level (%) (FS2000+)
      {0x1254, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_EXT1];
         if (ti < 0) { put<int32_t>(dst, 0); return; }
         static XPLMDataRef r_rat  = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot  = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         static XPLMDataRef r_fuel = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         float cap   = ratio * total;
         if (cap <= 0.0f) { put<int32_t>(dst, 0); return; }
         float wt = 0.0f;
         if (r_fuel) XPLMGetDatavf(r_fuel, &wt, ti, 1);
         put<int32_t>(dst, static_cast<int32_t>(wt / cap * 128.0f * 65536.0f));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_EXT1];
         if (ti < 0) return;
         static XPLMDataRef r_rat  = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot  = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         static XPLMDataRef r_fuel = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         float cap   = ratio * total;
         if (cap <= 0.0f) return;
         float level = take<int32_t>(src) / (128.0f * 65536.0f);
         level = std::clamp(level, 0.0f, 1.0f);
         float wt = level * cap;
         if (r_fuel) XPLMSetDatavf(r_fuel, &wt, ti, 1);
       },
       "External1 tank fuel level"},

      // Fuel external1 capacity (FS2000+) — US Gallons
      {0x1258, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_EXT1];
         if (ti < 0) { put<int32_t>(dst, 0); return; }
         static XPLMDataRef r_rat = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         put<int32_t>(dst, static_cast<int32_t>(conv::kg_to_gallons(ratio * total)));
       },
       nullptr,
       "External1 tank fuel capacity"},

      // Fuel external2 level (%) (FS2000+)
      {0x125C, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_EXT2];
         if (ti < 0) { put<int32_t>(dst, 0); return; }
         static XPLMDataRef r_rat  = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot  = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         static XPLMDataRef r_fuel = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         float cap   = ratio * total;
         if (cap <= 0.0f) { put<int32_t>(dst, 0); return; }
         float wt = 0.0f;
         if (r_fuel) XPLMGetDatavf(r_fuel, &wt, ti, 1);
         put<int32_t>(dst, static_cast<int32_t>(wt / cap * 128.0f * 65536.0f));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_EXT2];
         if (ti < 0) return;
         static XPLMDataRef r_rat  = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot  = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         static XPLMDataRef r_fuel = XPLMFindDataRef("sim/flightmodel/weight/m_fuel");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         float cap   = ratio * total;
         if (cap <= 0.0f) return;
         float level = take<int32_t>(src) / (128.0f * 65536.0f);
         level = std::clamp(level, 0.0f, 1.0f);
         float wt = level * cap;
         if (r_fuel) XPLMSetDatavf(r_fuel, &wt, ti, 1);
       },
       "External2 tank fuel level"},

      // Fuel external2 capacity (FS2000+) — US Gallons
      {0x1260, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         const int8_t ti = fuel_tank_map().idx[FTR_EXT2];
         if (ti < 0) { put<int32_t>(dst, 0); return; }
         static XPLMDataRef r_rat = XPLMFindDataRef("sim/aircraft/overflow/acf_tank_rat");
         static XPLMDataRef r_tot = XPLMFindDataRef("sim/aircraft/weight/acf_m_fuel_tot");
         float ratio = 0.0f;
         if (r_rat) XPLMGetDatavf(r_rat, &ratio, ti, 1);
         float total = r_tot ? XPLMGetDataf(r_tot) : 0.0f;
         put<int32_t>(dst, static_cast<int32_t>(conv::kg_to_gallons(ratio * total)));
       },
       nullptr,
       "External2 tank fuel capacity"},

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

      // Empty weight (FSX) — Aircraft weight without payload or fuel. In
      // pounds * 256
      {0x1330, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Empty weight: aircraft without fuel or payload
         static XPLMDataRef r = XPLMFindDataRef("sim/aircraft/weight/acf_m_empty");
         float kg = r ? XPLMGetDataf(r) : 0.0f;
         put<int32_t>(dst, static_cast<int32_t>(kg * 2.20462f * 256.0f));
       },
       nullptr,
       "Empty weight (lbs*256)"},

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
