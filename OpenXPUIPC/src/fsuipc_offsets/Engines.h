// SPDX-License-Identifier: GPL-3.0-or-later
// fsuipc_offsets/Engines.h — Production offset table
//
// 384 total offsets in this category
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

inline const std::vector<OffsetEntry> &fsuipc_offset_table_engines()
{
  static const std::vector<OffsetEntry> table = {

//
//       // ===== Engines ================================================
//
//       // Engine type — 0=Piston (and some Helos using the pistom model),
//       // 1=Jet, 2=Sailplane, 3=Helo, 4=Rocket, 5=Turboprop
//       {0x0609, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0609");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Engine type"},
//
//       // Has mixture control
//       {0x0780, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0780");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Has mixture control"},
//
//       // Has carb heat control
//       {0x0784, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0784");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Has carb heat control"},

      // ENG1 Throttle lever — -16384 (or max reverse, usually nearer -4096)
      // to +16384
      {0x088C, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h40 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_thro");
         float _fv40 = 0.0f;
         if (r_h40)
           XPLMGetDatavf(r_h40, &_fv40, 0, 1);
         put<int16_t>(dst, static_cast<int16_t>(_fv40 * 16384.0f));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         float v = take<int16_t>(src) / 16384.0f;
         static XPLMDataRef r_h41 = XPLMFindDataRef("sim/operation/override/override_throttles");
         if (r_h41)
           XPLMSetDatai(r_h41, 1);
         static XPLMDataRef r_h42 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_thro_use");
         {
           float _sv42 = v;
           if (r_h42)
             XPLMSetDatavf(r_h42, &_sv42, 0, 1);
         }
         static XPLMDataRef r_h43 = XPLMFindDataRef("sim/operation/override/override_throttles");
         if (r_h43)
           XPLMSetDatai(r_h43, 0);
       },
       "Engine 1 throttle"},
//
//       // ENG1 Prop lever — -16384 or max reverse, if reverse supported, else
//       // 0, to 16384
//       {0x088E, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x088E");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x088E");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "ENG1 Prop lever"},

      // ENG1 Mixture lever — 0-16384
      {0x0890, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/engine/ENGN_mixt");
         float v = 0.0f;
         if (r)
           XPLMGetDatavf(r, &v, 0, 1);
         put<int16_t>(dst, static_cast<int16_t>(v * 16384.0f));
       },
       nullptr,
       "Engine 1 mixture lever"},

      // ENG1 Starter switch pos — 0=Off, 1=Right or Strt, 2=Left or Gen,
      // 3=Both, 4=Start
      {0x0892, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Magneto/starter: 0=Off, 1=Right, 2=Left, 3=Both, 4=Start
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/engine/actuators/ignition_key");
         int v = 0;
         if (r)
           XPLMGetDatavi(r, &v, 0, 1);
         put<int16_t>(dst, static_cast<int16_t>(v));
       },
       nullptr,
       "Engine 1 starter/magnetos"},

      // ENG1 Combustion flag — 0=Eng not running, 1=running
      {0x0894, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Engine 1 combustion flag: TRUE (1) if engine is firing
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/engine/ENGN_running");
         int v = 0;
         if (r)
           XPLMGetDatavi(r, &v, 0, 1);
         put<int16_t>(dst, static_cast<int16_t>(v));
       },
       nullptr,
       "Engine 1 combustion flag"},
//
//       // ENG1 N2 — Percent*16384
//       {0x0896, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0896");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG1 N2"},

      // ENG1 N1 — Percent*16384
      {0x0898, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Engine 1 N1 (jet) or Prop RPM as 0–16384 (16384 = redline)
         // prop_speed_rpm is true RPM; acf_RSC_redline_prp is rad/s — convert to RPM via ×60/(2π)
         static XPLMDataRef r_rpm = XPLMFindDataRef("sim/cockpit2/engine/indicators/prop_speed_rpm");
         static XPLMDataRef r_n1 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_N1_");
         static XPLMDataRef r_max = XPLMFindDataRef("sim/aircraft/controls/acf_RSC_redline_prp");
         float rpm = 0.0f;
         if (r_rpm)
           XPLMGetDatavf(r_rpm, &rpm, 0, 1);
         if (rpm > 0.0f)
         {
           // Prop aircraft: scale by redline
           float redline_rads = r_max ? XPLMGetDataf(r_max) : 282.743f;
           if (redline_rads <= 0.0f)
             redline_rads = 282.743f;
           float redline_rpm = redline_rads * (60.0f / (2.0f * 3.14159265f)); // rad/s → RPM
           put<int16_t>(dst, static_cast<int16_t>(rpm / redline_rpm * 16384.0f));
         }
         else
         {
           // Jet aircraft: N1 %
           float n1 = 0.0f;
           if (r_n1)
             XPLMGetDatavf(r_n1, &n1, 0, 1);
           put<int16_t>(dst, static_cast<int16_t>(n1 / 100.0f * 16384.0f));
         }
       },
       nullptr,
       "Engine 1 N1/Prop RPM (0-16384)"},
//
//       // ENG1 Fuel Flow PPH SSL — Pounds Per Hour, Standardised for Sea
//       // Level. Units *128
//       {0x08A0, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x08A0");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG1 Fuel Flow PPH SSL"},

      // ENG1 Oil temp — 16384 = 140C. Degrees C obtained by calc shown.
      {0x08B8, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // oil_temperature_deg_C units vary by plane; use acf_oilT_is_C to normalise to Celsius
         // Clamp to 0: non-existent engines return 0°F which converts to -17.8°C
         static XPLMDataRef r_oilT = XPLMFindDataRef("sim/cockpit2/engine/indicators/oil_temperature_deg_C");
         static XPLMDataRef r_isC = XPLMFindDataRef("sim/aircraft/engine/acf_oilT_is_C");
         float raw = 0.0f;
         if (r_oilT)
           XPLMGetDatavf(r_oilT, &raw, 0, 1);
         float celsius = (r_isC && XPLMGetDatai(r_isC)) ? raw : (raw - 32.0f) / 1.8f;
         if (celsius < 0.0f)
           celsius = 0.0f;
         put<int16_t>(dst, static_cast<int16_t>(celsius / 140.0f * 16384.0f));
       },
       nullptr,
       "Engine 1 oil temp"},

      // ENG1 Oil pressure — 55 psi = 16384
      {0x08BA, 2,
       // Read/Write: Read (only)
       // aircraft  (the  B777)  this  can  exceed  the  16-bit  capacity  of  this
       // location. FSUIPC limits it to fit, i.e.65535 = 220 psi
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h45 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_oil_press_psi");
         float _fv45 = 0.0f;
         if (r_h45)
           XPLMGetDatavf(r_h45, &_fv45, 0, 1);
         // FSUIPC: 16384 = 55 psi (UINT16, clamped to 65535 = 220 psi)
         float scaled = _fv45 / 55.0f * 16384.0f;
         if (scaled > 65535.0f)
           scaled = 65535.0f;
         if (scaled < 0.0f)
           scaled = 0.0f;
         put<uint16_t>(dst, static_cast<uint16_t>(scaled));
       },
       nullptr,
       "Engine 1 oil pressure"},
//
//       // ENG1 Pressure Ratio (EPR) — 16384 = 1.60. Not always computed,
//       // depends on AIRcraft file
//       {0x08BC, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x08BC");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG1 Pressure Ratio (EPR)"},

      // ENG1 EGT — 16384 = 860 C. For props, in FS2004 get a more accurate
      // value in 3B70
      {0x08BE, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h46 = XPLMFindDataRef("sim/cockpit2/engine/indicators/EGT_deg_cel");
         float _fv46 = 0.0f;
         if (r_h46)
           XPLMGetDatavf(r_h46, &_fv46, 0, 1);
         put<int16_t>(dst, static_cast<int16_t>(_fv46 / 860.0f * 16384.0f));
       },
       nullptr,
       "Engine 1 EGT"},
//
//       // ENG1 Manifold Pressure — "Hg, 1024 = 1"
//       {0x08C0, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x08C0");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG1 Manifold Pressure"},
//
//       // ENG1 RPM scaler — Use this to calc Prop RPM from "N1" (or "N2")
//       // value. RPM = N1 x Scaler / 65536
//       {0x08C8, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x08C8");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG1 RPM scaler"},

      // ENG1 Oil Quantity — 16384 = 100%
      {0x08D0, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h47 = XPLMFindDataRef("sim/cockpit2/engine/indicators/oil_quantity_ratio");
         float _fv47 = 0.0f;
         if (r_h47)
           XPLMGetDatavf(r_h47, &_fv47, 0, 1);
         put<int32_t>(dst, static_cast<int32_t>(_fv47 * 16384.0f));
       },
       nullptr,
       "Engine 1 oil quantity"},
//
//       // ENG1 Vibration — 16384 = 5.0
//       {0x08D4, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x08D4");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG1 Vibration"},
//
//       // ENG1 Hydraulic pressure — 4 x psi
//       {0x08D8, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x08D8");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG1 Hydraulic pressure"},

      // ENG1 Hydraulic quantity — 16384 = 100%
      {0x08DC, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // hydraulic_quantity returns 0-1 ratio; 16384 = full
         static XPLMDataRef r_h48 = XPLMFindDataRef("sim/cockpit/misc/hydraulic_quantity");
         put<int32_t>(dst, static_cast<int32_t>((r_h48 ? XPLMGetDataf(r_h48) : 0.0f) * 16384.0f));
       },
       nullptr,
       "Engine 1 hydraulic qty"},

      // ENG1 CHT — Given in degrees F.
      {0x08E8, 8,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/engine/indicators/CHT_deg_cel");
         float c = 0.0f;
         if (r)
           XPLMGetDatavf(r, &c, 0, 1);
         put<double>(dst, c * 1.8 + 32.0);
       },
       nullptr,
       "Engine 1 CHT (deg F)"},
//
//       // ENG1 Turbine temp — Degrees C x 16384
//       {0x08F0, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x08F0");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG1 Turbine temp"},
//
//       // ENG1 Torque % — 16384 = 100%
//       {0x08F4, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x08F4");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG1 Torque %"},
//
//       // ENG1 Fuel pressure — psf, /144=psi
//       {0x08F8, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x08F8");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG1 Fuel pressure"},
//
//       // ENG1 Transmission pressure — psi * 16384
//       {0x0900, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0900");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG1 Transmission pressure"},
//
//       // ENG1 Transmission temp — Degrees C * 16384
//       {0x0904, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0904");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG1 Transmission temp"},
//
//       // ENG1 Rotor RPM % — 16384 = 100%
//       {0x0908, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0908");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG1 Rotor RPM %"},
//
//       // ENG1 Fuel Used — In pounds
//       {0x090C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x090C");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "ENG1 Fuel Used"},
//
//       // ENG1 Fuel elapsed time — In hours
//       {0x0910, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0910");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "ENG1 Fuel elapsed time"},

      // ENG1 Fuel Flow PPH
      {0x0918, 8,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h49 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_FF_");
         float _fv49 = 0.0f;
         if (r_h49)
           XPLMGetDatavf(r_h49, &_fv49, 0, 1);
         double ff = _fv49 * 3600.0 / 0.45359237;
         put<double>(dst, ff);
       },
       nullptr,
       "Engine 1 fuel flow (lbs/hr)"},

      // ENG2 Throttle lever — -16384 (or max reverse, usually nearer -4096)
      // to +16384
      {0x0924, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h51 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_thro");
         float _fv51 = 0.0f;
         if (r_h51)
           XPLMGetDatavf(r_h51, &_fv51, 1, 1);
         put<int16_t>(dst, static_cast<int16_t>(_fv51 * 16384.0f));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         float v = take<int16_t>(src) / 16384.0f;
         static XPLMDataRef r_h52 = XPLMFindDataRef("sim/operation/override/override_throttles");
         if (r_h52)
           XPLMSetDatai(r_h52, 1);
         static XPLMDataRef r_h53 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_thro_use");
         {
           float _sv53 = v;
           if (r_h53)
             XPLMSetDatavf(r_h53, &_sv53, 1, 1);
         }
         static XPLMDataRef r_h54 = XPLMFindDataRef("sim/operation/override/override_throttles");
         if (r_h54)
           XPLMSetDatai(r_h54, 0);
       },
       "Engine 2 throttle"},
//
//       // ENG2 Prop lever — -16384 or max reverse, if reverse supported, else
//       // 0, to 16384
//       {0x0926, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0926");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0926");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "ENG2 Prop lever"},

      // ENG2 Mixture lever — 0-16384
      {0x0928, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/engine/ENGN_mixt");
         float v = 0.0f;
         if (r)
           XPLMGetDatavf(r, &v, 1, 1);
         put<int16_t>(dst, static_cast<int16_t>(v * 16384.0f));
       },
       nullptr,
       "Engine 2 mixture lever"},

      // ENG2 Starter switch pos — 0=Off, 1=Right or Strt, 2=Left or Gen,
      // 3=Both, 4=Start
      {0x092A, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/engine/actuators/ignition_key");
         int v = 0;
         if (r)
           XPLMGetDatavi(r, &v, 1, 1);
         put<int16_t>(dst, static_cast<int16_t>(v));
       },
       nullptr,
       "Engine 2 starter/magnetos"},

      // ENG2 Combustion flag — 0=Eng not running, 1=running
      {0x092C, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Engine 2 combustion flag: TRUE (1) if engine is firing
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/engine/ENGN_running");
         int v = 0;
         if (r)
           XPLMGetDatavi(r, &v, 1, 1);
         put<int16_t>(dst, static_cast<int16_t>(v));
       },
       nullptr,
       "Engine 2 combustion flag"},
//
//       // ENG2 N2 — Percent*16384
//       {0x092E, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x092E");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG2 N2"},

      // ENG2 N1 — Percent*16384
      {0x0930, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Engine 2 N1 (jet) or Prop RPM as 0–16384 (16384 = redline)
         static XPLMDataRef r_rpm = XPLMFindDataRef("sim/cockpit2/engine/indicators/prop_speed_rpm");
         static XPLMDataRef r_n1 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_N1_");
         static XPLMDataRef r_max = XPLMFindDataRef("sim/aircraft/controls/acf_RSC_redline_prp");
         float rpm = 0.0f;
         if (r_rpm)
           XPLMGetDatavf(r_rpm, &rpm, 1, 1);
         if (rpm > 0.0f)
         {
           float redline_rads = r_max ? XPLMGetDataf(r_max) : 282.743f;
           if (redline_rads <= 0.0f)
             redline_rads = 282.743f;
           float redline_rpm = redline_rads * (60.0f / (2.0f * 3.14159265f)); // rad/s → RPM
           put<int16_t>(dst, static_cast<int16_t>(rpm / redline_rpm * 16384.0f));
         }
         else
         {
           float n1 = 0.0f;
           if (r_n1)
             XPLMGetDatavf(r_n1, &n1, 1, 1);
           put<int16_t>(dst, static_cast<int16_t>(n1 / 100.0f * 16384.0f));
         }
       },
       nullptr,
       "Engine 2 N1/Prop RPM (0-16384)"},
//
//       // ENG2 Fuel Flow PPH SSL — Pounds Per Hour, Standardised for Sea
//       // Level. Units *128 ??
//       {0x0938, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0938");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG2 Fuel Flow PPH SSL"},

      // ENG2 Oil temp — 16384 = 140C. Degrees C obtained by calc shown.
      {0x0950, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // oil_temperature_deg_C units vary by plane; use acf_oilT_is_C to normalise to Celsius
         // Clamp to 0: non-existent engines return 0°F which converts to -17.8°C
         static XPLMDataRef r_oilT = XPLMFindDataRef("sim/cockpit2/engine/indicators/oil_temperature_deg_C");
         static XPLMDataRef r_isC = XPLMFindDataRef("sim/aircraft/engine/acf_oilT_is_C");
         float raw = 0.0f;
         if (r_oilT)
           XPLMGetDatavf(r_oilT, &raw, 1, 1);
         float celsius = (r_isC && XPLMGetDatai(r_isC)) ? raw : (raw - 32.0f) / 1.8f;
         if (celsius < 0.0f)
           celsius = 0.0f;
         put<int16_t>(dst, static_cast<int16_t>(celsius / 140.0f * 16384.0f));
       },
       nullptr,
       "Engine 2 oil temp"},

      // ENG2 Oil pressure — 55 psi = 16384
      {0x0952, 2,
       // Read/Write: Read (only)
       // aircraft (the  B777) this can exceed the 16-bit capacity of this
       // location. FSUIPC limits it to fit, i.e.65535 = 220 psi
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h56 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_oil_press_psi");
         float _fv56 = 0.0f;
         if (r_h56)
           XPLMGetDatavf(r_h56, &_fv56, 1, 1);
         // FSUIPC: 16384 = 55 psi (UINT16, clamped to 65535 = 220 psi)
         float scaled = _fv56 / 55.0f * 16384.0f;
         if (scaled > 65535.0f)
           scaled = 65535.0f;
         if (scaled < 0.0f)
           scaled = 0.0f;
         put<uint16_t>(dst, static_cast<uint16_t>(scaled));
       },
       nullptr,
       "Engine 2 oil pressure"},
//
//       // ENG2 Pressure Ratio (EPR) — 16384 = 1.60. Not always computed,
//       // depends on AIRcraft file
//       {0x0954, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0954");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG2 Pressure Ratio (EPR)"},

      // ENG2 EGT — 16384 = 860 C. For props, in FS2004 get a more accurate
      // value in 3AB0
      {0x0956, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // NOTE: Original bug preserved — reads engine 0 EGT for engine 2
         static XPLMDataRef r_h57 = XPLMFindDataRef("sim/cockpit2/engine/indicators/EGT_deg_cel");
         float _fv57 = 0.0f;
         if (r_h57)
           XPLMGetDatavf(r_h57, &_fv57, 0, 1);
         put<int16_t>(dst, static_cast<int16_t>(_fv57 / 860.0f * 16384.0f));
       },
       nullptr,
       "Engine 2 EGT (bug: reads eng0)"},
//
//       // ENG2 Manifold Pressure — "Hg, 1024 = 1"
//       {0x0958, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0958");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG2 Manifold Pressure"},
//
//       // ENG2 RPM scaler — Use this to calc Prop RPM from "N1" (or "N2")
//       // value. RPM = N1 x Scaler / 65536
//       {0x0960, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0960");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG2 RPM scaler"},

      // ENG2 Oil Quantity — 16384 = 100%
      {0x0968, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h58 = XPLMFindDataRef("sim/cockpit2/engine/indicators/oil_quantity_ratio");
         float _fv58 = 0.0f;
         if (r_h58)
           XPLMGetDatavf(r_h58, &_fv58, 1, 1);
         put<int32_t>(dst, static_cast<int32_t>(_fv58 * 16384.0f));
       },
       nullptr,
       "Engine 2 oil quantity"},
//
//       // ENG2 Vibration
//       {0x096C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x096C");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG2 Vibration"},
//
//       // ENG2 Hydraulic pressure — 4 x psi
//       {0x0970, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0970");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG2 Hydraulic pressure"},

      // ENG2 Hydraulic quantity — 16384 = 100%
      {0x0974, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // hydraulic_quantity2 returns 0-1 ratio; 16384 = full
         static XPLMDataRef r_h59 = XPLMFindDataRef("sim/cockpit/misc/hydraulic_quantity2");
         put<int32_t>(dst, static_cast<int32_t>((r_h59 ? XPLMGetDataf(r_h59) : 0.0f) * 16384.0f));
       },
       nullptr,
       "Engine 2 hydraulic qty"},

      // ENG2 CHT — Given in degrees F.
      {0x0980, 8,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/engine/indicators/CHT_deg_cel");
         float c = 0.0f;
         if (r)
           XPLMGetDatavf(r, &c, 1, 1);
         put<double>(dst, c * 1.8 + 32.0);
       },
       nullptr,
       "Engine 2 CHT (deg F)"},
//
//       // ENG2 Turbine temp — Degrees C x 16384
//       {0x0988, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0988");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG2 Turbine temp"},
//
//       // ENG2 Torque % — 16384 = 100%
//       {0x098C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x098C");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG2 Torque %"},
//
//       // ENG2 Fuel pressure — psf, /144=psi
//       {0x0990, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0990");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG2 Fuel pressure"},
//
//       // ENG2 Transmission pressure — psi * 16384
//       {0x0998, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0998");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG2 Transmission pressure"},
//
//       // ENG2 Transmission temp — Degrees C * 16384
//       {0x099C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x099C");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG2 Transmission temp"},
//
//       // ENG2 Rotor RPM % — 16384 = 100%
//       {0x09A0, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09A0");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG2 Rotor RPM %"},
//
//       // ENG2 Fuel Used — In pounds
//       {0x09A4, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09A4");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "ENG2 Fuel Used"},
//
//       // ENG2 Fuel elapsed time — In hours
//       {0x09A8, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09A8");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "ENG2 Fuel elapsed time"},

      // ENG2 Fuel Flow PPH
      {0x09B0, 8,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // NOTE: Original bug preserved — reads engine 0 fuel flow for engine 2
         static XPLMDataRef r_h60 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_FF_");
         float _fv60 = 0.0f;
         if (r_h60)
           XPLMGetDatavf(r_h60, &_fv60, 0, 1);
         double ff = _fv60 * 3600.0 / 0.45359237;
         put<double>(dst, ff);
       },
       nullptr,
       "Engine 2 fuel flow (bug: reads eng0)"},
//
//       // ENG3 Throttle lever — -16384 (or max reverse, usually nearer -4096)
//       // to +16384
//       {0x09BC, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09BC");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09BC");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "ENG3 Throttle lever"},
//
//       // ENG3 Prop lever — -16384 or max reverse, if reverse supported, else
//       // 0, to 16384
//       {0x09BE, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09BE");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09BE");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "ENG3 Prop lever"},
//
//       // ENG3 Mixture lever — 0-16384
//       {0x09C0, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09C0");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09C0");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "ENG3 Mixture lever"},
//
//       // ENG3 Starter switch pos — 0=Off, 1=Right or Strt, 2=Left or Gen,
//       // 3=Both, 4=Start
//       {0x09C2, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09C2");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09C2");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "ENG3 Starter switch pos"},
//
//       // ENG3 Combustion flag — 0=Eng not running, 1=running
//       {0x09C4, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09C4");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG3 Combustion flag"},
//
//       // ENG3 N2 — Percent*16384
//       {0x09C6, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09C6");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG3 N2"},

      // ENG3 N1 — Percent*16384
      {0x09C8, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/engine/ENGN_N1_");
         float v = 0.0f;
         if (r)
           XPLMGetDatavf(r, &v, 2, 1);
         put<uint16_t>(dst, static_cast<uint16_t>(v / 100.0f * 16384.0f));
       },
       nullptr,
       "Engine 3 Jet N1 (0-16384)"},
//
//       // ENG3 Fuel Flow PPH SSL — Pounds Per Hour, Standardised for Sea
//       // Level. Units *128 ??
//       {0x09D0, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09D0");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG3 Fuel Flow PPH SSL"},
//
//       // ENG3 Oil temp — 16384 = 140C. Degrees C obtained by calc shown.
//       {0x09E8, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09E8");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG3 Oil temp"},
//
//       // ENG3 Oil pressure — 55 psi = 16384
//       {0x09EA, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09EA");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG3 Oil pressure"},
//
//       // ENG3 Pressure Ratio (EPR) — 16384 = 1.60. Not always computed,
//       // depends on AIRcraft file
//       {0x09EC, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09EC");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG3 Pressure Ratio (EPR)"},
//
//       // ENG3 EGT — 16384 = 860 C. For props, in FS2004 get a more accurate
//       // value in 39F0
//       {0x09EE, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09EE");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG3 EGT"},
//
//       // ENG3 Manifold Pressure — "Hg, 1024 = 1"
//       {0x09F0, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09F0");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG3 Manifold Pressure"},
//
//       // ENG3 RPM scaler — Use this to calc Prop RPM from "N1" (or "N2")
//       // value. RPM = N1 x Scaler / 65536
//       {0x09F8, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09F8");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG3 RPM scaler"},
//
//       // ENG3 Oil Quantity — 16384 = 100%
//       {0x0A00, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A00");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG3 Oil Quantity"},
//
//       // ENG3 Vibration
//       {0x0A04, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A04");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG3 Vibration"},
//
//       // ENG3 Hydraulic pressure — 4 x psi
//       {0x0A08, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A08");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG3 Hydraulic pressure"},

      // ENG3 Hydraulic quantity — 16384 = 100%
      {0x0A0C, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/misc/hydraulic_quantity3");
         put<int32_t>(dst, static_cast<int32_t>((r ? XPLMGetDataf(r) : 0.0f) * 16384.0f));
       },
       nullptr,
       "Engine 3 hydraulic qty"},

      // ENG3 CHT — Given in degrees F.
      {0x0A18, 8,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/engine/indicators/CHT_deg_cel");
         float c = 0.0f;
         if (r)
           XPLMGetDatavf(r, &c, 2, 1);
         put<double>(dst, c * 1.8 + 32.0);
       },
       nullptr,
       "Engine 3 CHT (deg F)"},
//
//       // ENG3 Turbine temp — Degrees C x 16384
//       {0x0A20, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A20");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG3 Turbine temp"},
//
//       // ENG3 Torque % — 16384 = 100%
//       {0x0A24, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A24");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG3 Torque %"},
//
//       // ENG3 Fuel pressure — psf, /144=psi
//       {0x0A28, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A28");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG3 Fuel pressure"},
//
//       // ENG3 Transmission pressure — psi * 16384
//       {0x0A30, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A30");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG3 Transmission pressure"},
//
//       // ENG3 Transmission temp — Degrees C * 16384
//       {0x0A34, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A34");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG3 Transmission temp"},
//
//       // ENG3 Rotor RPM % — 16384 = 100%
//       {0x0A38, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A38");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG3 Rotor RPM %"},
//
//       // ENG3 Fuel Used — In pounds
//       {0x0A3C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A3C");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "ENG3 Fuel Used"},
//
//       // ENG3 Fuel elapsed time — In hours
//       {0x0A40, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A40");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "ENG3 Fuel elapsed time"},
//
//       // ENG3 Fuel Flow PPH
//       {0x0A48, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A48");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "ENG3 Fuel Flow PPH"},
//
//       // ENG4 Throttle lever — -16384 (or max reverse, usually nearer -4096)
//       // to +16384
//       {0x0A54, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A54");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A54");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "ENG4 Throttle lever"},
//
//       // ENG4 Prop lever — -16384 or max reverse, if reverse supported, else
//       // 0, to 16384
//       {0x0A56, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A56");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A56");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "ENG4 Prop lever"},
//
//       // ENG4 Mixture lever — 0-16384
//       {0x0A58, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A58");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A58");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "ENG4 Mixture lever"},
//
//       // ENG4 Starter switch pos — 0=Off, 1=Right or Strt, 2=Left or Gen,
//       // 3=Both, 4=Start
//       {0x0A5A, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A5A");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A5A");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "ENG4 Starter switch pos"},
//
//       // ENG4 Combustion flag — 0=Eng not running, 1=running
//       {0x0A5C, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A5C");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 Combustion flag"},
//
//       // ENG4 N2 — Percent*16384
//       {0x0A5E, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A5E");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 N2"},

      // ENG4 N1 — Percent*16384
      {0x0A60, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/engine/ENGN_N1_");
         float v = 0.0f;
         if (r)
           XPLMGetDatavf(r, &v, 3, 1);
         put<uint16_t>(dst, static_cast<uint16_t>(v / 100.0f * 16384.0f));
       },
       nullptr,
       "Engine 4 Jet N1 (0-16384)"},
//
//       // ENG4 Fuel Flow PPH SSL — Pounds Per Hour, Standardised for Sea
//       // Level. Units *128 ??
//       {0x0A68, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A68");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 Fuel Flow PPH SSL"},
//
//       // ENG4 Oil temp — 16384 = 140C. Degrees C obtained by calc shown.
//       {0x0A80, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A80");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 Oil temp"},
//
//       // ENG4 Oil pressure — 55 psi = 16384
//       {0x0A82, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A82");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 Oil pressure"},
//
//       // ENG4 Pressure Ratio (EPR) — 16384 = 1.60. Not always computed,
//       // depends on AIRcraft file
//       {0x0A84, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A84");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 Pressure Ratio (EPR)"},
//
//       // ENG4 EGT — 16384 = 860 C. For props, in FS2004 get a more accurate
//       // value in 3930
//       {0x0A86, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A86");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 EGT"},
//
//       // ENG4 Manifold Pressure — "Hg, 1024 = 1"
//       {0x0A88, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A88");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 Manifold Pressure"},
//
//       // ENG4 RPM scaler — Use this to calc Prop RPM from "N1" (or "N2")
//       // value. RPM = N1 x Scaler / 65536
//       {0x0A90, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A90");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 RPM scaler"},
//
//       // ENG4 Oil Quantity — 16384 = 100%
//       {0x0A98, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A98");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 Oil Quantity"},
//
//       // ENG4 Vibration
//       {0x0A9C, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A9C");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 Vibration"},
//
//       // ENG4 Hydraulic pressure — 4 x psi
//       {0x0AA0, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0AA0");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 Hydraulic pressure"},
//
//       // ENG4 Hydraulic quantity — 16384 = 100%
//       {0x0AA4, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0AA4");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 Hydraulic quantity"},

      // ENG4 CHT — Given in degrees F.
      {0x0AB0, 8,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/engine/indicators/CHT_deg_cel");
         float c = 0.0f;
         if (r)
           XPLMGetDatavf(r, &c, 3, 1);
         put<double>(dst, c * 1.8 + 32.0);
       },
       nullptr,
       "Engine 4 CHT (deg F)"},
//
//       // ENG4 Turbine temp — Degrees C x 16384
//       {0x0AB8, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0AB8");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 Turbine temp"},
//
//       // ENG4 Torque % — 16384 = 100%
//       {0x0ABC, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0ABC");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 Torque %"},
//
//       // ENG4 Fuel pressure — psf, /144=psi
//       {0x0AC0, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0AC0");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 Fuel pressure"},
//
//       // ENG4 Transmission pressure — psi * 16384
//       {0x0AC8, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0AC8");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 Transmission pressure"},
//
//       // ENG4 Transmission temp — Degrees C * 16384
//       {0x0ACC, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0ACC");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 Transmission temp"},
//
//       // ENG4 Rotor RPM % — 16384 = 100%
//       {0x0AD0, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0AD0");
//          put<int32_t>(dst, static_cast<int32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "ENG4 Rotor RPM %"},
//
//       // ENG4 Fuel Used — In pounds
//       {0x0AD4, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0AD4");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "ENG4 Fuel Used"},
//
//       // ENG4 Fuel elapsed time — In hours
//       {0x0AD8, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0AD8");
//          put<float>(dst, static_cast<float>(r ? XPLMGetDataf(r) : 0.0f));
//        },
//        nullptr,
//        "ENG4 Fuel elapsed time"},
//
//       // ENG4 Fuel Flow PPH
//       {0x0AE0, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0AE0");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "ENG4 Fuel Flow PPH"},

      // Turb. ENG1 N1 %
      {0x2000, 8,
       // Read/Write: Unknown
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h117 = XPLMFindDataRef("sim/cockpit2/engine/indicators/N1_percent");
         float _fv117 = 0.0f;
         if (r_h117)
           XPLMGetDatavf(r_h117, &_fv117, 0, 1);
         put<double>(dst, static_cast<double>(_fv117));
       },
       nullptr,
       "Engine 1 N1 %"},
//
//       // Turb. ENG1 N2 %
//       {0x2008, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG1 N2 %"},
//
//       // Turb. ENG1 Corrected N1 % — Jets and turbos only. The corrected
//       // value is the actual N1 after correction for low temperatures at
//       // cruise altitudes.
//       {0x2010, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG1 Corrected N1 %"},

      // Turb. ENG1 Corrected N2 % — Jets and turbos only. The corrected
      // value is the actual N2 after correction for low temperatures at
      // cruise altitudes.
      {0x2018, 8,
       // Read/Write: Unknown
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h118 = XPLMFindDataRef("sim/cockpit2/engine/indicators/N2_percent");
         float _fv118 = 0.0f;
         if (r_h118)
           XPLMGetDatavf(r_h118, &_fv118, 0, 1);
         put<double>(dst, static_cast<double>(_fv118));
       },
       nullptr,
       "Engine 1 N2 %"},
//
//       // Turb. ENG1 Corrected Fuel Flow — Pounds per hour, jets and turbos
//       // only
//       {0x2020, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG1 Corrected Fuel Flow"},
//
//       // Turb. ENG1 Max Torque fraction
//       {0x2028, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG1 Max Torque fraction"},
//
//       // Turb. ENG1 EPR — Jets and turbos only
//       {0x2030, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG1 EPR"},
//
//       // Turb. ENG1 ITT — Jets and turbos only
//       {0x2038, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG1 ITT"},
//
//       // Turb. ENG1 Afterburner
//       {0x2048, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG1 Afterburner"},
//
//       // Turb. ENG1 JET Thrust — Pounds of jet thrust (turboprops also have
//       // prop thrust, see 2410)
//       {0x204C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG1 JET Thrust"},
//
//       // Turb. ENG1 Tank Selector
//       {0x2054, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG1 Tank Selector"},
//
//       // Turb. ENG1 Tank used
//       {0x2058, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG1 Tank used"},
//
//       // Turb. ENG1 number Tanks
//       {0x205C, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG1 number Tanks"},
//
//       // Turb. ENG1 FuelFlow PPH — Jets and turbos only
//       {0x2060, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG1 FuelFlow PPH"},
//
//       // Turb. ENG1 Fuel available
//       {0x2068, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG1 Fuel available"},
//
//       // Turb. ENG1 Bleed air PSI — Jets and turbos only
//       {0x206C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG1 Bleed air PSI"},
//
//       // Turb. ENG1 Pct. Area
//       {0x2074, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG1 Pct. Area"},
//
//       // Turb. ENG1 Reverser fraction — Proportion (0.0-1.0) of full thrust
//       // available for reverse
//       {0x207C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG1 Reverser fraction"},
//
//       // Turb. ENG1 Vibration
//       {0x2084, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG1 Vibration"},
//
//       // Turb. ENG1 Ignition Switch — 1 = On, 0 = Off
//       {0x208C, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x208C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x208C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Turb. ENG1 Ignition Switch"},

      // Turb. ENG2 N1 %
      {0x2100, 8,
       // Read/Write: Unknown
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h119 = XPLMFindDataRef("sim/cockpit2/engine/indicators/N1_percent");
         float _fv119 = 0.0f;
         if (r_h119)
           XPLMGetDatavf(r_h119, &_fv119, 1, 1);
         put<double>(dst, static_cast<double>(_fv119));
       },
       nullptr,
       "Engine 2 N1 %"},
//
//       // Turb. ENG2 N2 %
//       {0x2108, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG2 N2 %"},
//
//       // Turb. ENG2 Corrected N1 % — Jets and turbos only. The corrected
//       // value is the actual N1 after correction for low temperatures at
//       // cruise altitudes.
//       {0x2110, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG2 Corrected N1 %"},

      // Turb. ENG2 Corrected N2 % — Jets and turbos only. The corrected
      // value is the actual N2 after correction for low temperatures at
      // cruise altitudes.
      {0x2118, 8,
       // Read/Write: Unknown
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h120 = XPLMFindDataRef("sim/cockpit2/engine/indicators/N2_percent");
         float _fv120 = 0.0f;
         if (r_h120)
           XPLMGetDatavf(r_h120, &_fv120, 1, 1);
         put<double>(dst, static_cast<double>(_fv120));
       },
       nullptr,
       "Engine 2 N2 %"},
//
//       // Turb. ENG2 Corrected FF — Pounds per hour, jets and turbos only
//       {0x2120, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG2 Corrected FF"},
//
//       // Turb. ENG2 Max Torque fraction
//       {0x2128, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG2 Max Torque fraction"},
//
//       // Turb. ENG2  EPR — Jets and turbos only
//       {0x2130, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG2  EPR"},
//
//       // Turb. ENG2  ITT — Jets and turbos only
//       {0x2138, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG2  ITT"},
//
//       // Turb. ENG2 Afterburner
//       {0x2148, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG2 Afterburner"},
//
//       // Turb. ENG2 Jet Thrust — Pounds of jet thrust (turboprops also have
//       // prop thrust, see 2510)
//       {0x214C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG2 Jet Thrust"},
//
//       // Turb. ENG2 Tank Slector
//       {0x2154, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG2 Tank Slector"},
//
//       // Turb. ENG2 Tank used
//       {0x2158, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG2 Tank used"},
//
//       // Turb. ENG2 number Tanks
//       {0x215C, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG2 number Tanks"},
//
//       // Turb. ENG2 FuelFlow PPH — Jets and turbos only
//       {0x2160, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG2 FuelFlow PPH"},
//
//       // Turb. ENG2 Fuel available
//       {0x2168, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG2 Fuel available"},
//
//       // Turb. ENG2 Bleed air PSI — Jets and turbos only
//       {0x216C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG2 Bleed air PSI"},
//
//       // Turb. ENG2 Pct. Area
//       {0x2174, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG2 Pct. Area"},
//
//       // Turb. ENG2 Reverser fraction — Proportion (0.0-1.0) of full thrust
//       // available for reverse
//       {0x217C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG2 Reverser fraction"},
//
//       // Turb. ENG2 Vibration
//       {0x2184, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG2 Vibration"},
//
//       // Turb. ENG2 Ignition Switch — 1 = On, 0 = Off
//       {0x218C, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x218C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x218C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Turb. ENG2 Ignition Switch"},
//
//       // Turb. ENG3 N1 %
//       {0x2200, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3 N1 %"},
//
//       // Turb. ENG3 N2 %
//       {0x2208, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3 N2 %"},
//
//       // Turb. ENG3 Corrected N1 % — Jets and turbos only. The corrected
//       // value is the actual N1 after correction for low temperatures at
//       // cruise altitudes.
//       {0x2210, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3 Corrected N1 %"},
//
//       // Turb. ENG3 Corrected N2 % — Jets and turbos only. The corrected
//       // value is the actual N2 after correction for low temperatures at
//       // cruise altitudes.
//       {0x2218, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3 Corrected N2 %"},
//
//       // Turb. ENG3 Corrected FF — Pounds per hour, jets and turbos only
//       {0x2220, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3 Corrected FF"},
//
//       // Turb. ENG3 Max Torque fraction
//       {0x2228, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3 Max Torque fraction"},
//
//       // Turb. ENG3  EPR — Jets and turbos only
//       {0x2230, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3  EPR"},
//
//       // Turb. ENG3  ITT — Jets and turbos only
//       {0x2238, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3  ITT"},
//
//       // Turb. ENG3 Afterburner
//       {0x2248, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3 Afterburner"},
//
//       // Turb. ENG3 Jet Thrust — Pounds of jet thrust (turboprops also have
//       // prop thrust, see 2610)
//       {0x224C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3 Jet Thrust"},
//
//       // Turb. ENG3 Tank Slector
//       {0x2254, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3 Tank Slector"},
//
//       // Turb. ENG3 Tank used
//       {0x2258, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3 Tank used"},
//
//       // Turb. ENG3 number Tanks
//       {0x225C, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3 number Tanks"},
//
//       // Turb. ENG3 FuelFlow PPH — Jets and turbos only
//       {0x2260, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3 FuelFlow PPH"},
//
//       // Turb. ENG3 Fuel available
//       {0x2268, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3 Fuel available"},
//
//       // Turb. ENG3 Bleed air PSI — Jets and turbos only
//       {0x226C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3 Bleed air PSI"},
//
//       // Turb. ENG3 Pct. Area
//       {0x2274, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3 Pct. Area"},
//
//       // Turb. ENG3 Reverser fraction — Proportion (0.0-1.0) of full thrust
//       // available for reverse
//       {0x227C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3 Reverser fraction"},
//
//       // Turb. ENG3 Vibration
//       {0x2284, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG3 Vibration"},
//
//       // Turb. ENG3 Ignition Switch — 1 = On, 0 = Off
//       {0x228C, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x228C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x228C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Turb. ENG3 Ignition Switch"},
//
//       // Turb. ENG4 N1 %
//       {0x2300, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4 N1 %"},
//
//       // Turb. ENG4 N2 %
//       {0x2308, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4 N2 %"},
//
//       // Turb. ENG4 Corrected N1 % — Jets and turbos only. The corrected
//       // value is the actual N1 after correction for low temperatures at
//       // cruise altitudes.
//       {0x2310, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4 Corrected N1 %"},
//
//       // Turb. ENG4 Corrected N2 % — Jets and turbos only. The corrected
//       // value is the actual N2 after correction for low temperatures at
//       // cruise altitudes.
//       {0x2318, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4 Corrected N2 %"},
//
//       // Turb. ENG4 Corrected FF — Pounds per hour, jets and turbos only
//       {0x2320, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4 Corrected FF"},
//
//       // Turb. ENG4 Max Torque fraction
//       {0x2328, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4 Max Torque fraction"},
//
//       // Turb. ENG4  EPR — Jets and turbos only
//       {0x2330, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4  EPR"},
//
//       // Turb. ENG4  ITT — Jets and turbos only
//       {0x2338, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4  ITT"},
//
//       // Turb. ENG4 Afterburner
//       {0x2348, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4 Afterburner"},
//
//       // Turb. ENG4 Jet Thrust — Pounds of jet thrust (turboprops also have
//       // prop thrust, see 2710)
//       {0x234C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4 Jet Thrust"},
//
//       // Turb. ENG4 Tank Slector
//       {0x2354, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4 Tank Slector"},
//
//       // Turb. ENG4 Tank used
//       {0x2358, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4 Tank used"},
//
//       // Turb. ENG4 number Tanks
//       {0x235C, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4 number Tanks"},
//
//       // Turb. ENG4 FuelFlow PPH — Jets and turbos only
//       {0x2360, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4 FuelFlow PPH"},
//
//       // Turb. ENG4 Fuel available
//       {0x2368, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4 Fuel available"},
//
//       // Turb. ENG4 Bleed air PSI — Jets and turbos only
//       {0x236C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4 Bleed air PSI"},
//
//       // Turb. ENG4 Pct. Area
//       {0x2374, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4 Pct. Area"},
//
//       // Turb. ENG4 Reverser fraction — Proportion (0.0-1.0) of full thrust
//       // available for reverse
//       {0x237C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4 Reverser fraction"},
//
//       // Turb. ENG4 Vibrattion
//       {0x2384, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Turb. ENG4 Vibrattion"},
//
//       // Turb. ENG4 Ignition Switch — 1 = On, 0 = Off
//       {0x238C, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x238C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x238C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Turb. ENG4 Ignition Switch"},
//
//       // Prop1 RPM — For props and turboprops
//       {0x2400, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop1 RPM"},

      // Prop1 RPM fraction — RPM as a fraction of the maximim. For props and
      // turboprops
      {0x2408, 8,
       // Read/Write: Unknown
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/aircraft/engine/acf_RSC_redline_eng_per_engine");
         float v = 0.0f;
         if (r)
           XPLMGetDatavf(r, &v, 0, 1);
         put<double>(dst, static_cast<double>(v));
       },
       nullptr,
       "Prop 1 RPM redline (rad/s, double)"},
//
//       // Prop1 Thrust — In pounds. For props and turboprops
//       {0x2410, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop1 Thrust"},
//
//       // Prop1 Beta — Beta blade angle in radians.  For props and turboprops
//       {0x2418, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop1 Beta"},
//
//       // Prop1 Feathering Inhibit
//       {0x2420, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop1 Feathering Inhibit"},
//
//       // Prop1 Feathered
//       {0x2424, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop1 Feathered"},
//
//       // Prop1 Sync Delta Lever
//       {0x2428, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop1 Sync Delta Lever"},
//
//       // Prop1 Autofeather armed
//       {0x2430, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop1 Autofeather armed"},
//
//       // Prop2 RPM — For props and turboprops
//       {0x2500, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop2 RPM"},

      // Prop2 RPM fraction — RPM as a fraction of the maximim. For props and
      // turboprops
      {0x2508, 8,
       // Read/Write: Unknown
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/aircraft/engine/acf_RSC_redline_eng_per_engine");
         float v = 0.0f;
         if (r)
           XPLMGetDatavf(r, &v, 1, 1);
         put<double>(dst, static_cast<double>(v));
       },
       nullptr,
       "Prop 2 RPM redline (rad/s, double)"},
//
//       // Prop2 Thrust — In pounds. For props and turboprops
//       {0x2510, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop2 Thrust"},
//
//       // Prop2 Beta — Beta blade angle in radians.  For props and turboprops
//       {0x2518, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop2 Beta"},
//
//       // Prop2 Feathering Inhibit
//       {0x2520, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop2 Feathering Inhibit"},
//
//       // Prop2 Feathered
//       {0x2524, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop2 Feathered"},
//
//       // Prop2 Sync Delta Lever
//       {0x2528, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop2 Sync Delta Lever"},
//
//       // Prop2 Autofeather armed
//       {0x2530, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop2 Autofeather armed"},
//
//       // Prop3 RPM — For props and turboprops
//       {0x2600, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop3 RPM"},
//
//       // Prop3 RPM fraction — RPM as a fraction of the maximim. For props and
//       // turboprops
//       {0x2608, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop3 RPM fraction"},
//
//       // Prop3 Thrust — In pounds. For props and turboprops
//       {0x2610, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop3 Thrust"},
//
//       // Prop3 Beta — Beta blade angle in radians.  For props and turboprops
//       {0x2618, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop3 Beta"},
//
//       // Prop3 Feathering Inhibit
//       {0x2620, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop3 Feathering Inhibit"},
//
//       // Prop3 Feathered
//       {0x2624, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop3 Feathered"},
//
//       // Prop3 Sync Delta Lever
//       {0x2628, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop3 Sync Delta Lever"},
//
//       // Prop3 Autofeather armed
//       {0x2630, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop3 Autofeather armed"},
//
//       // Prop4 RPM — For props and turboprops
//       {0x2700, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop4 RPM"},
//
//       // Prop4 RPM fraction — RPM as a fraction of the maximim. For props and
//       // turboprops
//       {0x2708, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop4 RPM fraction"},
//
//       // Prop4 Thrust — In pounds. For props and turboprops
//       {0x2710, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop4 Thrust"},
//
//       // Prop4 Beta — Beta blade angle in radians.  For props and turboprops
//       {0x2718, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop4 Beta"},
//
//       // Prop4 Feathering Inhibit
//       {0x2720, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop4 Feathering Inhibit"},
//
//       // Prop4 Feathered
//       {0x2724, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop4 Feathered"},
//
//       // Prop4 Sync Delta Lever
//       {0x2728, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop4 Sync Delta Lever"},
//
//       // Prop4 Autofeather armed
//       {0x2730, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Prop4 Autofeather armed"},
//
//       // Engine Fire Flags — Bit 0=Engine 1, ... Bit 3=Engine 4, on fire if
//       // set
//       {0x3366, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3366");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3366");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Engine Fire Flags"},
//
//       // Recip. ENG4 Manif. Press. — ibs/sqft
//       {0x35A8, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x35A8");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Recip. ENG4 Manif. Press."},
//
//       // Recip. ENG4 Cowl Flap Pos — 0.0=closed, 1.0=open
//       {0x35B0, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x35B0");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x35B0");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Recip. ENG4 Cowl Flap Pos"},
//
//       // Recip. ENG4 Carb Heat Pos
//       {0x35B8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG4 Carb Heat Pos"},
//
//       // Recip. ENG4 Alt. Air Pos
//       {0x35C0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG4 Alt. Air Pos"},
//
//       // Recip. ENG4 Coolant Reservoir Pct.
//       {0x35C8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG4 Coolant Reservoir Pct."},
//
//       // Recip. ENG4 Left Mag Select
//       {0x35D0, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x35D0");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x35D0");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Recip. ENG4 Left Mag Select"},
//
//       // Recip. ENG4 Right Mag Select
//       {0x35D4, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x35D4");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x35D4");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Recip. ENG4 Right Mag Select"},
//
//       // Recip. ENG4 fuel/air mass ratio
//       {0x35D8, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x35D8");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Recip. ENG4 fuel/air mass ratio"},
//
//       // Recip. ENG4 Brake Power — ft-lbs
//       {0x35E0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG4 Brake Power"},
//
//       // Recip ENG4 Carb temp [FS2002+] — In degrees Rankine. [FSUIPC >=
//       // 3.401]
//       {0x35E8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip ENG4 Carb temp [FS2002+]"},
//
//       // Recip. ENG4 Starter Torque
//       {0x35F0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG4 Starter Torque"},
//
//       // Recip. ENG4 Turbocharger Failed
//       {0x35F8, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG4 Turbocharger Failed"},
//
//       // Recip. ENG4 Emergency Boost Active
//       {0x35FC, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG4 Emergency Boost Active"},
//
//       // Recip. ENG4 Emergency Boost Elapsed Time
//       {0x3600, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG4 Emergency Boost Elapsed Time"},
//
//       // Recip. ENG4 Wastegate Pos
//       {0x3608, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG4 Wastegate Pos"},
//
//       // Recip. ENG4 TIT Degr.
//       {0x3610, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG4 TIT Degr."},
//
//       // Recip. ENG4 CHT Degr.
//       {0x3618, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG4 CHT Degr."},
//
//       // Recip. ENG4 Radiator Degr.
//       {0x3620, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG4 Radiator Degr."},
//
//       // Recip. ENG4 Fuel Pressure PSF
//       {0x3628, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG4 Fuel Pressure PSF"},
//
//       // Recip. ENG4 Tank Selector
//       {0x3640, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG4 Tank Selector"},
//
//       // Recip. ENG4 Tanks used
//       {0x3644, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG4 Tanks used"},
//
//       // Recip. ENG4 Number of Tanks used
//       {0x3648, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG4 Number of Tanks used"},
//
//       // Recip. ENG4 FuelFlow PPH
//       {0x364C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG4 FuelFlow PPH"},
//
//       // Recip. ENG4 Fuel available
//       {0x3654, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG4 Fuel available"},
//
//       // Recip. ENG3 Engine RPM
//       {0x3660, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Engine RPM"},
//
//       // Recip. ENG3 Mainf. Press. — ibs/sqft
//       {0x3668, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Mainf. Press."},
//
//       // Recip. ENG3 Cowl Flap Pos — 0.0=closed, 1.0=open
//       {0x3670, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Cowl Flap Pos"},
//
//       // Recip. ENG3 Carb Heat Pos
//       {0x3678, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Carb Heat Pos"},
//
//       // Recip. ENG3 Alt. Air Pos
//       {0x3680, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Alt. Air Pos"},
//
//       // Recip. ENG3 Coolant Reservoir Pct.
//       {0x3688, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Coolant Reservoir Pct."},
//
//       // Recip. ENG3 Left Mag Select
//       {0x3690, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Left Mag Select"},
//
//       // Recip. ENG3 Right Mag Select
//       {0x3694, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Right Mag Select"},
//
//       // Recip. ENG3 fuel/air mass ratio
//       {0x3698, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 fuel/air mass ratio"},
//
//       // Recip. ENG3 Brake Power — ft-lbs
//       {0x36A0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Brake Power"},
//
//       // Recip. ENG3 Carb Temp [FS2002+] — In degrees Rankine. [FSUIPC >=
//       // 3.401]
//       {0x36A8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Carb Temp [FS2002+]"},
//
//       // Recip. ENG3 Starter Torque
//       {0x36B0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Starter Torque"},
//
//       // Recip. ENG3 Turbocharger Failed
//       {0x36B8, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Turbocharger Failed"},
//
//       // Recip. ENG3 Emergency Boost Active
//       {0x36BC, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Emergency Boost Active"},
//
//       // Recip. ENG3 Emergency Boost Elapsed time
//       {0x36C0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Emergency Boost Elapsed time"},
//
//       // Recip. ENG3 Wastegate Pos
//       {0x36C8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Wastegate Pos"},
//
//       // Recip. ENG3 TIT Degr.
//       {0x36D0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 TIT Degr."},
//
//       // Recip. ENG3 CHT Degr.
//       {0x36D8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 CHT Degr."},
//
//       // Recip. ENG3 Radiator Degr.
//       {0x36E0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Radiator Degr."},
//
//       // Recip. ENG3 Fuel Pressure PSF
//       {0x36E8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Fuel Pressure PSF"},
//
//       // Recip. ENG3 Tank Selector
//       {0x3700, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Tank Selector"},
//
//       // Recip. ENG3 Tanks used
//       {0x3704, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Tanks used"},
//
//       // Recip. ENG3 Number of Tanks user
//       {0x3708, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Number of Tanks user"},
//
//       // Recip. ENG3 FuelFlow PPH
//       {0x370C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 FuelFlow PPH"},
//
//       // Recip. ENG3 Fuel Available
//       {0x3714, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG3 Fuel Available"},
//
//       // Recip. ENG2 Engine RPM
//       {0x3720, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Engine RPM"},
//
//       // Recip. ENG2 Manif. Press. — ibs/sqft
//       {0x3728, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Manif. Press."},
//
//       // Recip. ENG2 Cowl Flap Pos — 0.0=closed, 1.0=open
//       {0x3730, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Cowl Flap Pos"},
//
//       // Recip. ENG2 Carb Heat Pos
//       {0x3738, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Carb Heat Pos"},
//
//       // Recip. ENG2 Alt. Air Pos
//       {0x3740, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Alt. Air Pos"},
//
//       // Recip. ENG2 Coolant Reservoir Pct
//       {0x3748, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Coolant Reservoir Pct"},
//
//       // Recip. ENG2 Left Mag Select
//       {0x3750, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Left Mag Select"},
//
//       // Recip. ENG2 Right Mag Select
//       {0x3754, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Right Mag Select"},
//
//       // Recip. ENG2 fuel/air mass ratio
//       {0x3758, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 fuel/air mass ratio"},
//
//       // Recip. ENG2 Brake Power — ft-lbs
//       {0x3760, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Brake Power"},
//
//       // Recip. ENG2 Carb temp [FS2002+] — In degrees Rankine. [FSUIPC >=
//       // 3.401]
//       {0x3768, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Carb temp [FS2002+]"},
//
//       // Recip. ENG2 Starter Torque
//       {0x3770, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Starter Torque"},
//
//       // Recip. ENG2 Turbocharger Failed
//       {0x3778, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Turbocharger Failed"},
//
//       // Recip. ENG2 Emergency Boost Active
//       {0x377C, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Emergency Boost Active"},
//
//       // Recip. ENG2 Emergency Boost Elapsed Time
//       {0x3780, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Emergency Boost Elapsed Time"},
//
//       // Recip. ENG2 Wastegate Pos
//       {0x3788, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Wastegate Pos"},
//
//       // Recip. ENG2 TIT Degr.
//       {0x3790, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 TIT Degr."},
//
//       // Recip. ENG2 CHT Degr.
//       {0x3798, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 CHT Degr."},
//
//       // Recip. ENG2 Radiator Degr,
//       {0x37A0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Radiator Degr,"},
//
//       // Recip. ENG2 Fuel Pressure PSF
//       {0x37A8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Fuel Pressure PSF"},
//
//       // Recip. ENG2 Tank Selector
//       {0x37C0, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Tank Selector"},
//
//       // Recip. ENG2 Tanks used
//       {0x37C4, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Tanks used"},
//
//       // Recip. ENG2 Number of Tanks used
//       {0x37C8, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Number of Tanks used"},
//
//       // Recip. ENG2 FuelFlow PPH
//       {0x37CC, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 FuelFlow PPH"},
//
//       // Recip. ENG2 Fuel Available
//       {0x37D4, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG2 Fuel Available"},
//
//       // Recip. ENG1 Engine RPM
//       {0x37E0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Engine RPM"},
//
//       // Recip. ENG1 Manif. Press. — ibs/sqft
//       {0x37E8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Manif. Press."},
//
//       // Recip. ENG1 Cowl Flap Pos — 0.0=closed, 1.0=open
//       {0x37F0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Cowl Flap Pos"},
//
//       // Recip. ENG1 Carb. Heat Pos
//       {0x37F8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Carb. Heat Pos"},
//
//       // Recip. ENG1 Alt. Air Pos
//       {0x3800, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Alt. Air Pos"},
//
//       // Recip. ENG1 Coolant Reservoir Pct.
//       {0x3808, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Coolant Reservoir Pct."},
//
//       // Recip. ENG1 Left Mag Select
//       {0x3810, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Left Mag Select"},
//
//       // Recip. ENG1 Right Mag Select
//       {0x3814, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Right Mag Select"},
//
//       // Recip. ENG1 fuel/air mass ratio
//       {0x3818, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 fuel/air mass ratio"},
//
//       // Recip. ENG1 Brake Power — ft-lbs
//       {0x3820, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Brake Power"},
//
//       // Recip. ENG1 Carb temp [FS2002+] — In degrees Rankine. [FSUIPC >=
//       // 3.401]
//       {0x3828, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Carb temp [FS2002+]"},
//
//       // Recip. ENG1 Starter Torque
//       {0x3830, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Starter Torque"},
//
//       // Recip. ENG1 Turbocharger Failed
//       {0x3838, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Turbocharger Failed"},
//
//       // Recip. ENG1 Emergency Boost Active
//       {0x383C, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Emergency Boost Active"},
//
//       // Recip. ENG1 Emergency Boost Elapsed Time
//       {0x3840, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Emergency Boost Elapsed Time"},
//
//       // Recip. ENG1 Wastgate Pos
//       {0x3848, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Wastgate Pos"},
//
//       // Recip. ENG1 TIT Degr.
//       {0x3850, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 TIT Degr."},
//
//       // Recip. ENG1 CHT Degr.
//       {0x3858, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 CHT Degr."},
//
//       // Recip. ENG1 Radiator Degr.
//       {0x3860, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Radiator Degr."},
//
//       // Recip. ENG1 Fuel Pressure PSF
//       {0x3868, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Fuel Pressure PSF"},
//
//       // Engine Primer ???
//       {0x3870, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Engine Primer ???"},
//
//       // Recip. ENG1 Tank Selector
//       {0x3880, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Tank Selector"},
//
//       // Recip. ENG1 Tanks used
//       {0x3884, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Tanks used"},
//
//       // Recip. ENG1 Number of Tanks used
//       {0x3888, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Number of Tanks used"},
//
//       // Recip. ENG1 FuelFlow PPH
//       {0x388C, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 FuelFlow PPH"},
//
//       // Recip. ENG1 Fuel Available
//       {0x3894, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Recip. ENG1 Fuel Available"},
//
//       // ENG4 General Failure
//       {0x38A0, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG4 General Failure"},
//
//       // ENG4 Recip. Combustion
//       {0x38A4, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG4 Recip. Combustion"},
//
//       // ENG4 (Recip./General) Throttle Lever Pos — 0.0=idle, 1.0=Max
//       {0x38A8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG4 (Recip./General) Throttle Lever Pos"},
//
//       // ENG4 (Recip./General) Mixture Lever Pos — 0.0=cutoff, 1.0=full rich
//       {0x38B0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG4 (Recip./General) Mixture Lever Pos"},
//
//       // ENG4 (Recip./General) Prop. Lever Pos
//       {0x38B8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG4 (Recip./General) Prop. Lever Pos"},
//
//       // ENG4 (Recip./General) Starter
//       {0x38C0, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG4 (Recip./General) Starter"},
//
//       // ENG4 (Recip./General) Oil Temp — degrees Rankine
//       {0x3918, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG4 (Recip./General) Oil Temp"},
//
//       // ENG4 (Recip./General) Oil Press. — ibs/sqft
//       {0x3920, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG4 (Recip./General) Oil Press."},
//
//       // ENG4 Recip. Oil leak
//       {0x3928, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG4 Recip. Oil leak"},
//
//       // ENG4 (Recip./General) EGT — degrees Rankine
//       {0x3930, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG4 (Recip./General) EGT"},
//
//       // ENG4 General Generator Active
//       {0x393C, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG4 General Generator Active"},
//
//       // ENG4 Recip. Damage Pct.
//       {0x3940, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG4 Recip. Damage Pct."},
//
//       // ENG4 Recip. Combustion Sound Pct.
//       {0x3948, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG4 Recip. Combustion Sound Pct."},
//
//       // ENG4 Recip. Fuel Pump Switch
//       {0x3958, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG4 Recip. Fuel Pump Switch"},
//
//       // ENG3 General Failure
//       {0x3960, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG3 General Failure"},
//
//       // ENG3 Recip. Combustion
//       {0x3964, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG3 Recip. Combustion"},
//
//       // ENG3 (Recip./General) Throttle Lever Pos — 0.0=idle, 1.0=Max
//       {0x3968, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG3 (Recip./General) Throttle Lever Pos"},
//
//       // ENG3 (Recip./General) Mixture Lever Pos — 0.0=cutoff, 1.0=full rich
//       {0x3970, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG3 (Recip./General) Mixture Lever Pos"},
//
//       // ENG3 (Recip./General) Prop. Lever Pos
//       {0x3978, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG3 (Recip./General) Prop. Lever Pos"},
//
//       // ENG3 (Recip./General) Starter
//       {0x3980, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG3 (Recip./General) Starter"},
//
//       // ENG3 (Recip./General) Oil Temp — degrees Rankine
//       {0x39D8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG3 (Recip./General) Oil Temp"},
//
//       // ENG3 (Recip./General) Oil Press. — ibs/sqft
//       {0x39E0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG3 (Recip./General) Oil Press."},
//
//       // ENG3 Recip. Oil leak
//       {0x39E8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG3 Recip. Oil leak"},
//
//       // ENG3 (Recip./General) EGT — degrees Rankine
//       {0x39F0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG3 (Recip./General) EGT"},
//
//       // ENG3 General Generator Active
//       {0x39FC, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG3 General Generator Active"},
//
//       // ENG3 Recip. Damage Pct.
//       {0x3A00, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG3 Recip. Damage Pct."},
//
//       // ENG3 Recip. Combustion Sound Pct.
//       {0x3A08, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG3 Recip. Combustion Sound Pct."},
//
//       // ENG3 Recip. Fuel Pump Switch
//       {0x3A18, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG3 Recip. Fuel Pump Switch"},
//
//       // ENG2 General Failure
//       {0x3A20, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG2 General Failure"},
//
//       // ENG2 Recip. Combustion
//       {0x3A24, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG2 Recip. Combustion"},
//
//       // ENG2 (Recip./General) Throttle Lever Pos — 0.0=idle, 1.0=Max
//       {0x3A28, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG2 (Recip./General) Throttle Lever Pos"},
//
//       // ENG2 (Recip./General) Mixture Lever Pos — 0.0=cutoff, 1.0=full rich
//       {0x3A30, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG2 (Recip./General) Mixture Lever Pos"},
//
//       // ENG2 (Recip./General) Prop. Lever Pos
//       {0x3A38, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG2 (Recip./General) Prop. Lever Pos"},
//
//       // ENG2 (Recip./General) Starter
//       {0x3A40, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG2 (Recip./General) Starter"},
//
//       // ENG2 (Recip./General) Oil Temp — degrees Rankine
//       {0x3A98, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG2 (Recip./General) Oil Temp"},
//
//       // ENG2 (Recip./General) Oil Press. — ibs/sqft
//       {0x3AA0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG2 (Recip./General) Oil Press."},
//
//       // ENG2 Recip. Oil leak
//       {0x3AA8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG2 Recip. Oil leak"},
//
//       // ENG2 (Recip./General) EGT — degrees Rankine
//       {0x3AB0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG2 (Recip./General) EGT"},
//
//       // ENG2 General Generator Active
//       {0x3ABC, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG2 General Generator Active"},
//
//       // ENG2 Recip. Damage Pct.
//       {0x3AC0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG2 Recip. Damage Pct."},
//
//       // ENG2 Recip. Combustion Sound Pct.
//       {0x3AC8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG2 Recip. Combustion Sound Pct."},
//
//       // ENG2 Recip. Fuel Pump Switch
//       {0x3AD8, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG2 Recip. Fuel Pump Switch"},
//
//       // ENG1 General Failure
//       {0x3AE0, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG1 General Failure"},
//
//       // ENG1 Recip. Combustion
//       {0x3AE4, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG1 Recip. Combustion"},
//
//       // ENG1 (Recip./General) Throttle Lever Pos — 0.0=idle, 1.0=Max
//       {0x3AE8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG1 (Recip./General) Throttle Lever Pos"},
//
//       // ENG1 (Recip./General) Mixture Lever Pos — 0.0=cutoff, 1.0=full rich
//       {0x3AF0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG1 (Recip./General) Mixture Lever Pos"},
//
//       // ENG1 (Recip./General) Prop. Lever Pos
//       {0x3AF8, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG1 (Recip./General) Prop. Lever Pos"},
//
//       // ENG1 (Recip./General) Starter
//       {0x3B00, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG1 (Recip./General) Starter"},
//
//       // ENG1 (Recip./General) Oil Temp — degrees Rankine
//       {0x3B58, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG1 (Recip./General) Oil Temp"},
//
//       // ENG1 (Recip./General) Oil Press. — ibs/sqft
//       {0x3B60, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG1 (Recip./General) Oil Press."},
//
//       // ENG1 Recip. Oil leak
//       {0x3B68, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG1 Recip. Oil leak"},
//
//       // ENG1 (Recip./General) EGT — degrees Rankine
//       {0x3B70, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG1 (Recip./General) EGT"},
//
//       // ENG1 General Generator Active
//       {0x3B7C, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG1 General Generator Active"},
//
//       // ENG1 Recip. Damage Pct.
//       {0x3B80, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG1 Recip. Damage Pct."},
//
//       // ENG1 Recip. Combustion Sound Pct.
//       {0x3B88, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG1 Recip. Combustion Sound Pct."},
//
//       // ENG1 Recip. Fuel Pump Switch
//       {0x3B98, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "ENG1 Recip. Fuel Pump Switch"},

  }; // end table
  return table;
}
