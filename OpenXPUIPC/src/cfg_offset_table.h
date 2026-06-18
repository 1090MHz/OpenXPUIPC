// Auto-generated from XPUIPCOffsets.cfg — DO NOT EDIT MANUALLY
// Re-generate with:  python generate_offsets.py <config> <output>
// 110 offset entries generated, 0 skipped
#pragma once

//#include "offset_table.h"   // OffsetEntry, put<>, take<>, DataRefCache
#include <cmath>             // std::pow, std::fmod, std::abs, std::round

inline const std::vector<OffsetEntry>& cfg_offset_table() {
    static const std::vector<OffsetEntry> table = {
    // 0x02CC FLOAT64 r  RPN: $CompassHdg
    { 0x02CC, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/gauges/indicators/compass_heading_deg_mag");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "CompassHdg" },

    // 0x02D8 SINT16 r  RPN: $Adf2Dir 360 / 65536 *
    { 0x02D8, 2,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit/radios/adf2_dir_degt");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          double v1 = (v0 / 360.0);
          double v2 = (v1 * 65536.0);
          put<int16_t>(dst, static_cast<int16_t>(v2));
      },
      nullptr,
      "Adf2Dir" },

    // 0x036D UINT8 r  RPN: $IAS $Vne >
    { 0x036D, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/flightmodel/position/indicated_airspeed");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          static XPLMDataRef r_v1 = XPLMFindDataRef("sim/aircraft/view/acf_Vne");
          double v1 = static_cast<double>(r_v1 ? XPLMGetDataf(r_v1) : 0.0f);
          double v2 = (v0 > v1) ? 1.0 : 0.0;
          put<uint8_t>(dst, static_cast<uint8_t>(v2));
      },
      nullptr,
      "IAS" },

    // 0x0378 UINT16 rw  RPN: $DmeSource 1 + >DmeSource @ 1 -
    { 0x0378, 2,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/radios/actuators/DME_slave_source");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          double v1 = (v0 + 1.0);
          put<uint16_t>(dst, static_cast<uint16_t>(v1));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint16_t>(src));
          double v0 = (written_val - 1.0);
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit2/radios/actuators/DME_slave_source");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(v0));
      },
      "DmeSource" },

    // 0x04E0 UINT8 rw  RPN: $rel_smoke_cpit >rel_smoke_cpit @
    { 0x04E0, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/operation/failures/rel_smoke_cpit");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint8_t>(dst, static_cast<uint8_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint8_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/operation/failures/rel_smoke_cpit");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "rel_smoke_cpit" },

    // 0x04E1 UINT8 rw  RPN: $aerobaskStarter_key >aerobaskStarter_key @
    { 0x04E1, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/engine/actuators/ignition_key");
          int _it_v0 = 0; if (r_v0) XPLMGetDatavi(r_v0, &_it_v0, 0, 1);
          double v0 = static_cast<double>(_it_v0);
          put<uint8_t>(dst, static_cast<uint8_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint8_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit2/engine/actuators/ignition_key");
          { int _sv = static_cast<int>(written_val); if (r_set0) XPLMSetDatavi(r_set0, &_sv, 0, 1); }
      },
      "aerobaskStarter_key" },

    // 0x04E2 UINT8 rw  RPN: $aerobaskEngine_master >aerobaskEngine_master @
    { 0x04E2, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("aerobask/dr401/engine_master");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint8_t>(dst, static_cast<uint8_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint8_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("aerobask/dr401/engine_master");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "aerobaskEngine_master" },

    // 0x04E4 UINT16 r  RPN: $MixtureControlPOSITION0 16384 *
    { 0x04E4, 2,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("simcoders/rep/engine/fuelline/commanded_mixture_ratio_0");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          double v1 = (v0 * 16384.0);
          put<uint16_t>(dst, static_cast<uint16_t>(v1));
      },
      nullptr,
      "MixtureControlPOSITION0" },

    // 0x04F0 UINT8 rw  RPN: $rel_engfir0 >rel_engfir0 @
    { 0x04F0, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/operation/failures/rel_engfir0");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint8_t>(dst, static_cast<uint8_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint8_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/operation/failures/rel_engfir0");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "rel_engfir0" },

    // 0x04F1 UINT8 rw  RPN: $rel_engfir1 >rel_engfir1 @
    { 0x04F1, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/operation/failures/rel_engfir1");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint8_t>(dst, static_cast<uint8_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint8_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/operation/failures/rel_engfir1");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "rel_engfir1" },

    // 0x04F2 UINT8 rw  RPN: $rel_engfir2 >rel_engfir2 @
    { 0x04F2, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/operation/failures/rel_engfir2");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint8_t>(dst, static_cast<uint8_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint8_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/operation/failures/rel_engfir2");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "rel_engfir2" },

    // 0x04F3 UINT8 rw  RPN: $rel_engfir3 >rel_engfir3 @
    { 0x04F3, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/operation/failures/rel_engfir3");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint8_t>(dst, static_cast<uint8_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint8_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/operation/failures/rel_engfir3");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "rel_engfir3" },

    // 0x04F4 UINT8 rw  RPN: $rel_bird_strike >rel_bird_strike @
    { 0x04F4, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/operation/failures/rel_bird_strike");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint8_t>(dst, static_cast<uint8_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint8_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/operation/failures/rel_bird_strike");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "rel_bird_strike" },

    // 0x088E SINT16 rw  RPN: $Prop1 $PropMaxRPM / 20480 * 4096 - >Prop1 @ 4096 + 20480 / $PropMaxRPM *
    { 0x088E, 2,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_prop");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 0, 1);
          double v0 = static_cast<double>(_ft_v0);
          static XPLMDataRef r_v1 = XPLMFindDataRef("sim/aircraft/controls/acf_RSC_redline_prp");
          double v1 = static_cast<double>(r_v1 ? XPLMGetDataf(r_v1) : 0.0f);
          double v2 = (v0 / v1);
          double v3 = (v2 * 20480.0);
          double v4 = (v3 - 4096.0);
          put<int16_t>(dst, static_cast<int16_t>(v4));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<int16_t>(src));
          double v0 = (written_val + 4096.0);
          double v1 = (v0 / 20480.0);
          static XPLMDataRef r_v2 = XPLMFindDataRef("sim/aircraft/controls/acf_RSC_redline_prp");
          double v2 = static_cast<double>(r_v2 ? XPLMGetDataf(r_v2) : 0.0f);
          double v3 = (v1 * v2);
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_prop");
          { float _sv = static_cast<float>(v3); if (r_set0) XPLMSetDatavf(r_set0, &_sv, 0, 1); }
      },
      "Prop1" },

    // 0x08B2 UINT16 rw  RPN: $ENGN_heat1 >ENGN_heat1 @
    { 0x08B2, 2,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/ice/ice_inlet_heat_on_per_engine");
          int _it_v0 = 0; if (r_v0) XPLMGetDatavi(r_v0, &_it_v0, 0, 1);
          double v0 = static_cast<double>(_it_v0);
          put<uint16_t>(dst, static_cast<uint16_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint16_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit2/ice/ice_inlet_heat_on_per_engine");
          { int _sv = static_cast<int>(written_val); if (r_set0) XPLMSetDatavi(r_set0, &_sv, 0, 1); }
      },
      "ENGN_heat1" },

    // 0x08C8 UINT16 r  RPN: $PropSpeed1 12000 * $N1_1 / PI /
    { 0x08C8, 2,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/flightmodel/engine/POINT_tacrad");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 0, 1);
          double v0 = static_cast<double>(_ft_v0);
          double v1 = (v0 * 12000.0);
          static XPLMDataRef r_v2 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_N1_");
          float _ft_v2 = 0.0f; if (r_v2) XPLMGetDatavf(r_v2, &_ft_v2, 0, 1);
          double v2 = static_cast<double>(_ft_v2);
          double v3 = (v1 / v2);
          double v4 = (v3 / 3.14159265358979323846);
          put<uint16_t>(dst, static_cast<uint16_t>(v4));
      },
      nullptr,
      "PropSpeed1" },

    // 0x08E8 FLOAT64 r  RPN: $CHT1 1.8 * 32 +
    { 0x08E8, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/engine/indicators/CHT_deg_cel");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 0, 1);
          double v0 = static_cast<double>(_ft_v0);
          double v1 = (v0 * 1.8);
          double v2 = (v1 + 32.0);
          put<double>(dst, static_cast<double>(v2));
      },
      nullptr,
      "CHT1" },

    // 0x0926 SINT16 rw  RPN: $Prop2 $PropMaxRPM / 20480 * 4096 - >Prop2 @ 4096 + 20480 / $PropMaxRPM *
    { 0x0926, 2,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_prop");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 1, 1);
          double v0 = static_cast<double>(_ft_v0);
          static XPLMDataRef r_v1 = XPLMFindDataRef("sim/aircraft/controls/acf_RSC_redline_prp");
          double v1 = static_cast<double>(r_v1 ? XPLMGetDataf(r_v1) : 0.0f);
          double v2 = (v0 / v1);
          double v3 = (v2 * 20480.0);
          double v4 = (v3 - 4096.0);
          put<int16_t>(dst, static_cast<int16_t>(v4));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<int16_t>(src));
          double v0 = (written_val + 4096.0);
          double v1 = (v0 / 20480.0);
          static XPLMDataRef r_v2 = XPLMFindDataRef("sim/aircraft/controls/acf_RSC_redline_prp");
          double v2 = static_cast<double>(r_v2 ? XPLMGetDataf(r_v2) : 0.0f);
          double v3 = (v1 * v2);
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_prop");
          { float _sv = static_cast<float>(v3); if (r_set0) XPLMSetDatavf(r_set0, &_sv, 1, 1); }
      },
      "Prop2" },

    // 0x094A UINT16 rw  RPN: $ENGN_heat2 >ENGN_heat2 @
    { 0x094A, 2,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/ice/ice_inlet_heat_on_per_engine");
          int _it_v0 = 0; if (r_v0) XPLMGetDatavi(r_v0, &_it_v0, 1, 1);
          double v0 = static_cast<double>(_it_v0);
          put<uint16_t>(dst, static_cast<uint16_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint16_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit2/ice/ice_inlet_heat_on_per_engine");
          { int _sv = static_cast<int>(written_val); if (r_set0) XPLMSetDatavi(r_set0, &_sv, 1, 1); }
      },
      "ENGN_heat2" },

    // 0x0960 UINT16 r  RPN: $PropSpeed2 12000 * $N1_2 / PI /
    { 0x0960, 2,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/flightmodel/engine/POINT_tacrad");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 1, 1);
          double v0 = static_cast<double>(_ft_v0);
          double v1 = (v0 * 12000.0);
          static XPLMDataRef r_v2 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_N1_");
          float _ft_v2 = 0.0f; if (r_v2) XPLMGetDatavf(r_v2, &_ft_v2, 1, 1);
          double v2 = static_cast<double>(_ft_v2);
          double v3 = (v1 / v2);
          double v4 = (v3 / 3.14159265358979323846);
          put<uint16_t>(dst, static_cast<uint16_t>(v4));
      },
      nullptr,
      "PropSpeed2" },

    // 0x0980 FLOAT64 r  RPN: $CHT2 1.8 * 32 +
    { 0x0980, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/engine/indicators/CHT_deg_cel");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 1, 1);
          double v0 = static_cast<double>(_ft_v0);
          double v1 = (v0 * 1.8);
          double v2 = (v1 + 32.0);
          put<double>(dst, static_cast<double>(v2));
      },
      nullptr,
      "CHT2" },

    // 0x09BE SINT16 rw  RPN: $Prop3 $PropMaxRPM / 20480 * 4096 - >Prop3 @ 4096 + 20480 / $PropMaxRPM *
    { 0x09BE, 2,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_prop");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 2, 1);
          double v0 = static_cast<double>(_ft_v0);
          static XPLMDataRef r_v1 = XPLMFindDataRef("sim/aircraft/controls/acf_RSC_redline_prp");
          double v1 = static_cast<double>(r_v1 ? XPLMGetDataf(r_v1) : 0.0f);
          double v2 = (v0 / v1);
          double v3 = (v2 * 20480.0);
          double v4 = (v3 - 4096.0);
          put<int16_t>(dst, static_cast<int16_t>(v4));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<int16_t>(src));
          double v0 = (written_val + 4096.0);
          double v1 = (v0 / 20480.0);
          static XPLMDataRef r_v2 = XPLMFindDataRef("sim/aircraft/controls/acf_RSC_redline_prp");
          double v2 = static_cast<double>(r_v2 ? XPLMGetDataf(r_v2) : 0.0f);
          double v3 = (v1 * v2);
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_prop");
          { float _sv = static_cast<float>(v3); if (r_set0) XPLMSetDatavf(r_set0, &_sv, 2, 1); }
      },
      "Prop3" },

    // 0x09E2 UINT16 rw  RPN: $ENGN_heat3 >ENGN_heat3 @
    { 0x09E2, 2,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/ice/ice_inlet_heat_on_per_engine");
          int _it_v0 = 0; if (r_v0) XPLMGetDatavi(r_v0, &_it_v0, 2, 1);
          double v0 = static_cast<double>(_it_v0);
          put<uint16_t>(dst, static_cast<uint16_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint16_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit2/ice/ice_inlet_heat_on_per_engine");
          { int _sv = static_cast<int>(written_val); if (r_set0) XPLMSetDatavi(r_set0, &_sv, 2, 1); }
      },
      "ENGN_heat3" },

    // 0x09F8 UINT16 r  RPN: $PropSpeed3 12000 * $N1_3 / PI /
    { 0x09F8, 2,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/flightmodel/engine/POINT_tacrad");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 2, 1);
          double v0 = static_cast<double>(_ft_v0);
          double v1 = (v0 * 12000.0);
          static XPLMDataRef r_v2 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_N1_");
          float _ft_v2 = 0.0f; if (r_v2) XPLMGetDatavf(r_v2, &_ft_v2, 2, 1);
          double v2 = static_cast<double>(_ft_v2);
          double v3 = (v1 / v2);
          double v4 = (v3 / 3.14159265358979323846);
          put<uint16_t>(dst, static_cast<uint16_t>(v4));
      },
      nullptr,
      "PropSpeed3" },

    // 0x0A18 FLOAT64 r  RPN: $CHT3 1.8 * 32 +
    { 0x0A18, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/engine/indicators/CHT_deg_cel");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 2, 1);
          double v0 = static_cast<double>(_ft_v0);
          double v1 = (v0 * 1.8);
          double v2 = (v1 + 32.0);
          put<double>(dst, static_cast<double>(v2));
      },
      nullptr,
      "CHT3" },

    // 0x0A56 SINT16 rw  RPN: $Prop4 $PropMaxRPM / 20480 * 4096 - >Prop4 @ 4096 + 20480 / $PropMaxRPM *
    { 0x0A56, 2,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_prop");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 3, 1);
          double v0 = static_cast<double>(_ft_v0);
          static XPLMDataRef r_v1 = XPLMFindDataRef("sim/aircraft/controls/acf_RSC_redline_prp");
          double v1 = static_cast<double>(r_v1 ? XPLMGetDataf(r_v1) : 0.0f);
          double v2 = (v0 / v1);
          double v3 = (v2 * 20480.0);
          double v4 = (v3 - 4096.0);
          put<int16_t>(dst, static_cast<int16_t>(v4));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<int16_t>(src));
          double v0 = (written_val + 4096.0);
          double v1 = (v0 / 20480.0);
          static XPLMDataRef r_v2 = XPLMFindDataRef("sim/aircraft/controls/acf_RSC_redline_prp");
          double v2 = static_cast<double>(r_v2 ? XPLMGetDataf(r_v2) : 0.0f);
          double v3 = (v1 * v2);
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_prop");
          { float _sv = static_cast<float>(v3); if (r_set0) XPLMSetDatavf(r_set0, &_sv, 3, 1); }
      },
      "Prop4" },

    // 0x0A7A UINT16 rw  RPN: $ENGN_heat4 >ENGN_heat4 @
    { 0x0A7A, 2,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/ice/ice_inlet_heat_on_per_engine");
          int _it_v0 = 0; if (r_v0) XPLMGetDatavi(r_v0, &_it_v0, 3, 1);
          double v0 = static_cast<double>(_it_v0);
          put<uint16_t>(dst, static_cast<uint16_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint16_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit2/ice/ice_inlet_heat_on_per_engine");
          { int _sv = static_cast<int>(written_val); if (r_set0) XPLMSetDatavi(r_set0, &_sv, 3, 1); }
      },
      "ENGN_heat4" },

    // 0x0A90 UINT16 r  RPN: $PropSpeed4 12000 * $N1_4 / PI /
    { 0x0A90, 2,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/flightmodel/engine/POINT_tacrad");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 3, 1);
          double v0 = static_cast<double>(_ft_v0);
          double v1 = (v0 * 12000.0);
          static XPLMDataRef r_v2 = XPLMFindDataRef("sim/flightmodel/engine/ENGN_N1_");
          float _ft_v2 = 0.0f; if (r_v2) XPLMGetDatavf(r_v2, &_ft_v2, 3, 1);
          double v2 = static_cast<double>(_ft_v2);
          double v3 = (v1 / v2);
          double v4 = (v3 / 3.14159265358979323846);
          put<uint16_t>(dst, static_cast<uint16_t>(v4));
      },
      nullptr,
      "PropSpeed4" },

    // 0x0AB0 FLOAT64 r  RPN: $CHT4 1.8 * 32 +
    { 0x0AB0, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/engine/indicators/CHT_deg_cel");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 3, 1);
          double v0 = static_cast<double>(_ft_v0);
          double v1 = (v0 * 1.8);
          double v2 = (v1 + 32.0);
          put<double>(dst, static_cast<double>(v2));
      },
      nullptr,
      "CHT4" },

    // 0x0B6D UINT8 rw  RPN: $rel_ss_dgy >rel_ss_dgy @
    { 0x0B6D, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/operation/failures/rel_ss_dgy");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint8_t>(dst, static_cast<uint8_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint8_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/operation/failures/rel_ss_dgy");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "rel_ss_dgy" },

    // 0x0B6E UINT8 rw  RPN: $rel_ss_vvi >rel_ss_vvi @
    { 0x0B6E, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/operation/failures/rel_ss_vvi");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint8_t>(dst, static_cast<uint8_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint8_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/operation/failures/rel_ss_vvi");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "rel_ss_vvi" },

    // 0x0B70 UINT8 rw  RPN: $rel_nav1 >rel_nav1 @
    { 0x0B70, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/operation/failures/rel_nav1");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint8_t>(dst, static_cast<uint8_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint8_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/operation/failures/rel_nav1");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "rel_nav1" },

    // 0x0B71 UINT8 rw  RPN: $rel_pitot >rel_pitot @
    { 0x0B71, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/operation/failures/rel_pitot");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint8_t>(dst, static_cast<uint8_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint8_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/operation/failures/rel_pitot");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "rel_pitot" },

    // 0x0B72 UINT8 rw  RPN: $rel_ss_tsi >rel_ss_tsi @
    { 0x0B72, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/operation/failures/rel_ss_tsi");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint8_t>(dst, static_cast<uint8_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint8_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/operation/failures/rel_ss_tsi");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "rel_ss_tsi" },

    // 0x0B73 UINT8 rw  RPN: $rel_vacuum >rel_vacuum @
    { 0x0B73, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/operation/failures/rel_vacuum");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint8_t>(dst, static_cast<uint8_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint8_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/operation/failures/rel_vacuum");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "rel_vacuum" },

    // 0x0C2E UINT8 r  RPN: $Nav1DmeSpeed 100 \ 48 +
    { 0x0C2E, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/radios/indicators/nav1_dme_speed_kts");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          double v1 = static_cast<double>(static_cast<int64_t>(v0) / static_cast<int64_t>(100.0));
          double v2 = (v1 + 48.0);
          put<uint8_t>(dst, static_cast<uint8_t>(v2));
      },
      nullptr,
      "Nav1DmeSpeed" },

    // 0x0C2F UINT8 r  RPN: $Nav1DmeSpeed 100 % 10 \ 48 +
    { 0x0C2F, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/radios/indicators/nav1_dme_speed_kts");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          double v1 = std::fmod(v0, 100.0);
          double v2 = static_cast<double>(static_cast<int64_t>(v1) / static_cast<int64_t>(10.0));
          double v3 = (v2 + 48.0);
          put<uint8_t>(dst, static_cast<uint8_t>(v3));
      },
      nullptr,
      "Nav1DmeSpeed" },

    // 0x0C30 UINT8 r  RPN: $Nav1DmeSpeed 10 % 48 +
    { 0x0C30, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/radios/indicators/nav1_dme_speed_kts");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          double v1 = std::fmod(v0, 10.0);
          double v2 = (v1 + 48.0);
          put<uint8_t>(dst, static_cast<uint8_t>(v2));
      },
      nullptr,
      "Nav1DmeSpeed" },

    // 0x0C31 UINT8 r  RPN: 0
    { 0x0C31, 1,
      [](uint8_t* dst, DataRefCache&) {
          put<uint8_t>(dst, static_cast<uint8_t>(0.0));
      },
      nullptr,
      "0x0C31" },

    // 0x0C38 UINT8 r  RPN: $Nav2DmeSpeed 100 \ 48 +
    { 0x0C38, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/radios/indicators/nav2_dme_speed_kts");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          double v1 = static_cast<double>(static_cast<int64_t>(v0) / static_cast<int64_t>(100.0));
          double v2 = (v1 + 48.0);
          put<uint8_t>(dst, static_cast<uint8_t>(v2));
      },
      nullptr,
      "Nav2DmeSpeed" },

    // 0x0C39 UINT8 r  RPN: $Nav2DmeSpeed 100 % 10 \ 48 +
    { 0x0C39, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/radios/indicators/nav2_dme_speed_kts");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          double v1 = std::fmod(v0, 100.0);
          double v2 = static_cast<double>(static_cast<int64_t>(v1) / static_cast<int64_t>(10.0));
          double v3 = (v2 + 48.0);
          put<uint8_t>(dst, static_cast<uint8_t>(v3));
      },
      nullptr,
      "Nav2DmeSpeed" },

    // 0x0C3A UINT8 r  RPN: $Nav2DmeSpeed 10 % 48 +
    { 0x0C3A, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/radios/indicators/nav2_dme_speed_kts");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          double v1 = std::fmod(v0, 10.0);
          double v2 = (v1 + 48.0);
          put<uint8_t>(dst, static_cast<uint8_t>(v2));
      },
      nullptr,
      "Nav2DmeSpeed" },

    // 0x0C3B UINT8 r  RPN: 0
    { 0x0C3B, 1,
      [](uint8_t* dst, DataRefCache&) {
          put<uint8_t>(dst, static_cast<uint8_t>(0.0));
      },
      nullptr,
      "0x0C3B" },

    // 0x0C3E SINT16 rw  RPN: $GyroDrift 360 / 65536 * >GyroDrift @ 360 * 65536 /
    { 0x0C3E, 2,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit/gyros/dg_drift_vac_deg");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          double v1 = (v0 / 360.0);
          double v2 = (v1 * 65536.0);
          put<int16_t>(dst, static_cast<int16_t>(v2));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<int16_t>(src));
          double v0 = (written_val * 360.0);
          double v1 = (v0 / 65536.0);
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit/gyros/dg_drift_vac_deg");
          if (r_set0) XPLMSetDataf(r_set0, static_cast<float>(v1));
      },
      "GyroDrift" },

    // 0x0C6A SINT16 r  RPN: $Adf1Dir 360 / 65536 *
    { 0x0C6A, 2,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit/radios/adf1_dir_degt");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          double v1 = (v0 / 360.0);
          double v2 = (v1 * 65536.0);
          put<int16_t>(dst, static_cast<int16_t>(v2));
      },
      nullptr,
      "Adf1Dir" },

    // 0x132C UINT32 rw  RPN: $HSISelect 2 == >HSISelect @ 2 *
    { 0x132C, 4,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit/switches/HSI_selector");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          double v1 = (v0 == 2.0) ? 1.0 : 0.0;
          put<uint32_t>(dst, static_cast<uint32_t>(v1));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint32_t>(src));
          double v0 = (written_val * 2.0);
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit/switches/HSI_selector");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(v0));
      },
      "HSISelect" },

    // 0x2022 UINT8 rw  RPN: $fd 128 * $ils 64 * + $tcas 16 * + $waypoints 8 * + $VORs 4 * + $NDBs 2 * + $airports 1 * + >fd @ 128 & 128 / >ils @ 64 & 64 / >tcas @ 16 & 16 / >waypoints @ 8 & 8 / >VORs @ 4 & 4 / >NDBs @ 2 & 2 / >airports @ 1 & 1 /
    { 0x2022, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/custom/xap/fcu/fd");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          double v1 = (v0 * 128.0);
          static XPLMDataRef r_v2 = XPLMFindDataRef("sim/custom/xap/fcu/ils");
          double v2 = static_cast<double>(r_v2 ? XPLMGetDatai(r_v2) : 0);
          double v3 = (v2 * 64.0);
          double v4 = (v1 + v3);
          static XPLMDataRef r_v5 = XPLMFindDataRef("sim/cockpit/switches/EFIS_shows_tcas");
          double v5 = static_cast<double>(r_v5 ? XPLMGetDatai(r_v5) : 0);
          double v6 = (v5 * 16.0);
          double v7 = (v4 + v6);
          static XPLMDataRef r_v8 = XPLMFindDataRef("sim/cockpit/switches/EFIS_shows_waypoints");
          double v8 = static_cast<double>(r_v8 ? XPLMGetDatai(r_v8) : 0);
          double v9 = (v8 * 8.0);
          double v10 = (v7 + v9);
          static XPLMDataRef r_v11 = XPLMFindDataRef("sim/cockpit/switches/EFIS_vor_on");
          double v11 = static_cast<double>(r_v11 ? XPLMGetDatai(r_v11) : 0);
          double v12 = (v11 * 4.0);
          double v13 = (v10 + v12);
          static XPLMDataRef r_v14 = XPLMFindDataRef("sim/cockpit/switches/EFIS_shows_NDBs");
          double v14 = static_cast<double>(r_v14 ? XPLMGetDatai(r_v14) : 0);
          double v15 = (v14 * 2.0);
          double v16 = (v13 + v15);
          static XPLMDataRef r_v17 = XPLMFindDataRef("sim/cockpit/switches/EFIS_shows_airports");
          double v17 = static_cast<double>(r_v17 ? XPLMGetDatai(r_v17) : 0);
          double v18 = (v17 * 1.0);
          double v19 = (v16 + v18);
          put<uint8_t>(dst, static_cast<uint8_t>(v19));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint8_t>(src));
          double v0 = static_cast<double>(static_cast<int64_t>(written_val) & static_cast<int64_t>(128.0));
          double v1 = (v0 / 128.0);
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/custom/xap/fcu/fd");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(v1));
          double v2 = static_cast<double>(static_cast<int64_t>(written_val) & static_cast<int64_t>(64.0));
          double v3 = (v2 / 64.0);
          static XPLMDataRef r_set1 = XPLMFindDataRef("sim/custom/xap/fcu/ils");
          if (r_set1) XPLMSetDatai(r_set1, static_cast<int>(v3));
          double v4 = static_cast<double>(static_cast<int64_t>(written_val) & static_cast<int64_t>(16.0));
          double v5 = (v4 / 16.0);
          static XPLMDataRef r_set2 = XPLMFindDataRef("sim/cockpit/switches/EFIS_shows_tcas");
          if (r_set2) XPLMSetDatai(r_set2, static_cast<int>(v5));
          double v6 = static_cast<double>(static_cast<int64_t>(written_val) & static_cast<int64_t>(8.0));
          double v7 = (v6 / 8.0);
          static XPLMDataRef r_set3 = XPLMFindDataRef("sim/cockpit/switches/EFIS_shows_waypoints");
          if (r_set3) XPLMSetDatai(r_set3, static_cast<int>(v7));
          double v8 = static_cast<double>(static_cast<int64_t>(written_val) & static_cast<int64_t>(4.0));
          double v9 = (v8 / 4.0);
          static XPLMDataRef r_set4 = XPLMFindDataRef("sim/cockpit/switches/EFIS_vor_on");
          if (r_set4) XPLMSetDatai(r_set4, static_cast<int>(v9));
          double v10 = static_cast<double>(static_cast<int64_t>(written_val) & static_cast<int64_t>(2.0));
          double v11 = (v10 / 2.0);
          static XPLMDataRef r_set5 = XPLMFindDataRef("sim/cockpit/switches/EFIS_shows_NDBs");
          if (r_set5) XPLMSetDatai(r_set5, static_cast<int>(v11));
          double v12 = static_cast<double>(static_cast<int64_t>(written_val) & static_cast<int64_t>(1.0));
          double v13 = (v12 / 1.0);
          static XPLMDataRef r_set6 = XPLMFindDataRef("sim/cockpit/switches/EFIS_shows_airports");
          if (r_set6) XPLMSetDatai(r_set6, static_cast<int>(v13));
      },
      "fd" },

    // 0x281C UINT32 rw  RPN: $BatteryMaster >BatteryMaster @
    { 0x281C, 4,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit/electrical/battery_on");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint32_t>(dst, static_cast<uint32_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint32_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit/electrical/battery_on");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "BatteryMaster" },

    // 0x282C FLOAT64 r  RPN: $Bat1Amps
    { 0x282C, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/electrical/battery_amps");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 0, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "Bat1Amps" },

    // 0x2834 FLOAT64 r  RPN: $Bat1Volt
    { 0x2834, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/electrical/battery_voltage_actual_volts");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 0, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "Bat1Volt" },

    // 0x2840 FLOAT64 r  RPN: $Bus1Volt
    { 0x2840, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/electrical/bus_volts");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 0, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "Bus1Volt" },

    // 0x2848 FLOAT64 r  RPN: $Bus1Amps
    { 0x2848, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/electrical/bus_load_amps");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 0, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "Bus1Amps" },

    // 0x2850 FLOAT64 r  RPN: $Bus2Volt
    { 0x2850, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/electrical/bus_volts");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 1, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "Bus2Volt" },

    // 0x2858 FLOAT64 r  RPN: $Bus2Amps
    { 0x2858, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/electrical/bus_load_amps");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 1, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "Bus2Amps" },

    // 0x2860 FLOAT64 r  RPN: $Bus3Volt
    { 0x2860, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/electrical/bus_volts");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 2, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "Bus3Volt" },

    // 0x2868 FLOAT64 r  RPN: $Bus3Amps
    { 0x2868, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/electrical/bus_load_amps");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 2, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "Bus3Amps" },

    // 0x2870 FLOAT64 r  RPN: $Bus4Volt
    { 0x2870, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/electrical/bus_volts");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 3, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "Bus4Volt" },

    // 0x2878 FLOAT64 r  RPN: $Bus4Amps
    { 0x2878, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/electrical/bus_load_amps");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 3, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "Bus4Amps" },

    // 0x2880 FLOAT64 r  RPN: $Bus1Volt
    { 0x2880, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/electrical/bus_volts");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 0, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "Bus1Volt" },

    // 0x2888 FLOAT64 r  RPN: $Gen1Amps
    { 0x2888, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/electrical/generator_amps");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 0, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "Gen1Amps" },

    // 0x2890 FLOAT64 r  RPN: $Bus2Volt
    { 0x2890, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/electrical/bus_volts");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 1, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "Bus2Volt" },

    // 0x2898 FLOAT64 r  RPN: $Gen2Amps
    { 0x2898, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/electrical/generator_amps");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 1, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "Gen2Amps" },

    // 0x28A0 FLOAT64 r  RPN: $Bus3Volt
    { 0x28A0, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/electrical/bus_volts");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 2, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "Bus3Volt" },

    // 0x28A8 FLOAT64 r  RPN: $Gen3Amps
    { 0x28A8, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/electrical/generator_amps");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 2, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "Gen3Amps" },

    // 0x28B0 FLOAT64 r  RPN: $Bus4Volt
    { 0x28B0, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/electrical/bus_volts");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 3, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "Bus4Volt" },

    // 0x28B8 FLOAT64 r  RPN: $Gen4Amps
    { 0x28B8, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/electrical/generator_amps");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 3, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      nullptr,
      "Gen4Amps" },

    // 0x2A90 UINT32 rw  RPN: $TailWheelLock >TailWheelLock @
    { 0x2A90, 4,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/flightmodel/controls/tail_lock_rat");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          put<uint32_t>(dst, static_cast<uint32_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint32_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/flightmodel/controls/tail_lock_rat");
          if (r_set0) XPLMSetDataf(r_set0, static_cast<float>(written_val));
      },
      "TailWheelLock" },

    // 0x2E80 UINT32 rw  RPN: $AvionicsMaster >AvionicsMaster @
    { 0x2E80, 4,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit/electrical/avionics_on");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint32_t>(dst, static_cast<uint32_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint32_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit/electrical/avionics_on");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "AvionicsMaster" },

    // 0x2EC8 UINT32 rw  RPN: $PropSync >PropSync @
    { 0x2EC8, 4,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit/switches/prop_sync_on");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint32_t>(dst, static_cast<uint32_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint32_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit/switches/prop_sync_on");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "PropSync" },

    // 0x3366 UINT8 rw  RPN: $rel_engfir0 6 == $rel_engfir1 6 == 2 * + $rel_engfir2 6 == 4 * + $rel_engfir3 6 == 8 * +
    { 0x3366, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/operation/failures/rel_engfir0");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          double v1 = (v0 == 6.0) ? 1.0 : 0.0;
          static XPLMDataRef r_v2 = XPLMFindDataRef("sim/operation/failures/rel_engfir1");
          double v2 = static_cast<double>(r_v2 ? XPLMGetDatai(r_v2) : 0);
          double v3 = (v2 == 6.0) ? 1.0 : 0.0;
          double v4 = (v3 * 2.0);
          double v5 = (v1 + v4);
          static XPLMDataRef r_v6 = XPLMFindDataRef("sim/operation/failures/rel_engfir2");
          double v6 = static_cast<double>(r_v6 ? XPLMGetDatai(r_v6) : 0);
          double v7 = (v6 == 6.0) ? 1.0 : 0.0;
          double v8 = (v7 * 4.0);
          double v9 = (v5 + v8);
          static XPLMDataRef r_v10 = XPLMFindDataRef("sim/operation/failures/rel_engfir3");
          double v10 = static_cast<double>(r_v10 ? XPLMGetDatai(r_v10) : 0);
          double v11 = (v10 == 6.0) ? 1.0 : 0.0;
          double v12 = (v11 * 8.0);
          double v13 = (v9 + v12);
          put<uint8_t>(dst, static_cast<uint8_t>(v13));
      },
      nullptr,
      "rel_engfir0" },

    // 0x337C UINT8 rw  RPN: $prop_heat1 1 == $prop_heat2 1 == 2 * + $prop_heat3 1 == 4 * + $prop_heat4 1 == 8 * +
    { 0x337C, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/ice/ice_prop_heat_on_per_engine");
          int _it_v0 = 0; if (r_v0) XPLMGetDatavi(r_v0, &_it_v0, 0, 1);
          double v0 = static_cast<double>(_it_v0);
          double v1 = (v0 == 1.0) ? 1.0 : 0.0;
          static XPLMDataRef r_v2 = XPLMFindDataRef("sim/cockpit2/ice/ice_prop_heat_on_per_engine");
          int _it_v2 = 0; if (r_v2) XPLMGetDatavi(r_v2, &_it_v2, 1, 1);
          double v2 = static_cast<double>(_it_v2);
          double v3 = (v2 == 1.0) ? 1.0 : 0.0;
          double v4 = (v3 * 2.0);
          double v5 = (v1 + v4);
          static XPLMDataRef r_v6 = XPLMFindDataRef("sim/cockpit2/ice/ice_prop_heat_on_per_engine");
          int _it_v6 = 0; if (r_v6) XPLMGetDatavi(r_v6, &_it_v6, 2, 1);
          double v6 = static_cast<double>(_it_v6);
          double v7 = (v6 == 1.0) ? 1.0 : 0.0;
          double v8 = (v7 * 4.0);
          double v9 = (v5 + v8);
          static XPLMDataRef r_v10 = XPLMFindDataRef("sim/cockpit2/ice/ice_prop_heat_on_per_engine");
          int _it_v10 = 0; if (r_v10) XPLMGetDatavi(r_v10, &_it_v10, 3, 1);
          double v10 = static_cast<double>(_it_v10);
          double v11 = (v10 == 1.0) ? 1.0 : 0.0;
          double v12 = (v11 * 8.0);
          double v13 = (v9 + v12);
          put<uint8_t>(dst, static_cast<uint8_t>(v13));
      },
      nullptr,
      "prop_heat1" },

    // 0x35B0 FLOAT64 rw  RPN: $CowlFlaps4 >CowlFlaps4 @
    { 0x35B0, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/engine/actuators/cowl_flap_ratio");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 3, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit2/engine/actuators/cowl_flap_ratio");
          { float _sv = static_cast<float>(written_val); if (r_set0) XPLMSetDatavf(r_set0, &_sv, 3, 1); }
      },
      "CowlFlaps4" },

    // 0x3670 FLOAT64 rw  RPN: $CowlFlaps3 >CowlFlaps3 @
    { 0x3670, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/engine/actuators/cowl_flap_ratio");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 2, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit2/engine/actuators/cowl_flap_ratio");
          { float _sv = static_cast<float>(written_val); if (r_set0) XPLMSetDatavf(r_set0, &_sv, 2, 1); }
      },
      "CowlFlaps3" },

    // 0x3730 FLOAT64 rw  RPN: $CowlFlaps2 >CowlFlaps2 @
    { 0x3730, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/engine/actuators/cowl_flap_ratio");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 1, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit2/engine/actuators/cowl_flap_ratio");
          { float _sv = static_cast<float>(written_val); if (r_set0) XPLMSetDatavf(r_set0, &_sv, 1, 1); }
      },
      "CowlFlaps2" },

    // 0x37C0 UINT32 rw  RPN: $fuel_tank_selector_right >fuel_tank_selector_right @
    { 0x37C0, 4,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/fuel/fuel_tank_selector_right");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint32_t>(dst, static_cast<uint32_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint32_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit2/fuel/fuel_tank_selector_right");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "fuel_tank_selector_right" },

    // 0x37F0 FLOAT64 rw  RPN: $CowlFlaps1 >CowlFlaps1 @
    { 0x37F0, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/engine/actuators/cowl_flap_ratio");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 0, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit2/engine/actuators/cowl_flap_ratio");
          { float _sv = static_cast<float>(written_val); if (r_set0) XPLMSetDatavf(r_set0, &_sv, 0, 1); }
      },
      "CowlFlaps1" },

    // 0x3858 FLOAT64 r  RPN: $CHT1 1.8 * 32 +
    { 0x3858, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/engine/indicators/CHT_deg_cel");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 0, 1);
          double v0 = static_cast<double>(_ft_v0);
          double v1 = (v0 * 1.8);
          double v2 = (v1 + 32.0);
          put<double>(dst, static_cast<double>(v2));
      },
      nullptr,
      "CHT1" },

    // 0x3880 UINT32 rw  RPN: $fuel_tank_selector_left >fuel_tank_selector_left @
    { 0x3880, 4,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/fuel/fuel_tank_selector_left");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint32_t>(dst, static_cast<uint32_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint32_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit2/fuel/fuel_tank_selector_left");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "fuel_tank_selector_left" },

    // 0x3930 FLOAT64 r  RPN: $EGT4 1.8 * 491.67 +
    { 0x3930, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/engine/indicators/EGT_deg_C");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 3, 1);
          double v0 = static_cast<double>(_ft_v0);
          double v1 = (v0 * 1.8);
          double v2 = (v1 + 491.67);
          put<double>(dst, static_cast<double>(v2));
      },
      nullptr,
      "EGT4" },

    // 0x3938 UINT32 rw  RPN: $Gen4On >Gen4On @
    { 0x3938, 4,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit/electrical/generator_on");
          int _it_v0 = 0; if (r_v0) XPLMGetDatavi(r_v0, &_it_v0, 3, 1);
          double v0 = static_cast<double>(_it_v0);
          put<uint32_t>(dst, static_cast<uint32_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint32_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit/electrical/generator_on");
          { int _sv = static_cast<int>(written_val); if (r_set0) XPLMSetDatavi(r_set0, &_sv, 3, 1); }
      },
      "Gen4On" },

    // 0x3958 UINT32 rw  RPN: $FuelPump4 >FuelPump4 @
    { 0x3958, 4,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit/engine/fuel_pump_on");
          int _it_v0 = 0; if (r_v0) XPLMGetDatavi(r_v0, &_it_v0, 3, 1);
          double v0 = static_cast<double>(_it_v0);
          put<uint32_t>(dst, static_cast<uint32_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint32_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit/engine/fuel_pump_on");
          { int _sv = static_cast<int>(written_val); if (r_set0) XPLMSetDatavi(r_set0, &_sv, 3, 1); }
      },
      "FuelPump4" },

    // 0x39F0 FLOAT64 r  RPN: $EGT3 1.8 * 491.67 +
    { 0x39F0, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/engine/indicators/EGT_deg_C");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 2, 1);
          double v0 = static_cast<double>(_ft_v0);
          double v1 = (v0 * 1.8);
          double v2 = (v1 + 491.67);
          put<double>(dst, static_cast<double>(v2));
      },
      nullptr,
      "EGT3" },

    // 0x39F8 UINT32 rw  RPN: $Gen3On >Gen3On @
    { 0x39F8, 4,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit/electrical/generator_on");
          int _it_v0 = 0; if (r_v0) XPLMGetDatavi(r_v0, &_it_v0, 2, 1);
          double v0 = static_cast<double>(_it_v0);
          put<uint32_t>(dst, static_cast<uint32_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint32_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit/electrical/generator_on");
          { int _sv = static_cast<int>(written_val); if (r_set0) XPLMSetDatavi(r_set0, &_sv, 2, 1); }
      },
      "Gen3On" },

    // 0x3A18 UINT32 rw  RPN: $FuelPump3 >FuelPump3 @
    { 0x3A18, 4,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit/engine/fuel_pump_on");
          int _it_v0 = 0; if (r_v0) XPLMGetDatavi(r_v0, &_it_v0, 2, 1);
          double v0 = static_cast<double>(_it_v0);
          put<uint32_t>(dst, static_cast<uint32_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint32_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit/engine/fuel_pump_on");
          { int _sv = static_cast<int>(written_val); if (r_set0) XPLMSetDatavi(r_set0, &_sv, 2, 1); }
      },
      "FuelPump3" },

    // 0x3AB0 FLOAT64 r  RPN: $EGT2 1.8 * 491.67 +
    { 0x3AB0, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/engine/indicators/EGT_deg_C");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 1, 1);
          double v0 = static_cast<double>(_ft_v0);
          double v1 = (v0 * 1.8);
          double v2 = (v1 + 491.67);
          put<double>(dst, static_cast<double>(v2));
      },
      nullptr,
      "EGT2" },

    // 0x3AB8 UINT32 rw  RPN: $Gen2On >Gen2On @
    { 0x3AB8, 4,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit/electrical/generator_on");
          int _it_v0 = 0; if (r_v0) XPLMGetDatavi(r_v0, &_it_v0, 1, 1);
          double v0 = static_cast<double>(_it_v0);
          put<uint32_t>(dst, static_cast<uint32_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint32_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit/electrical/generator_on");
          { int _sv = static_cast<int>(written_val); if (r_set0) XPLMSetDatavi(r_set0, &_sv, 1, 1); }
      },
      "Gen2On" },

    // 0x3AD8 UINT32 rw  RPN: $FuelPump2 >FuelPump2 @
    { 0x3AD8, 4,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit/engine/fuel_pump_on");
          int _it_v0 = 0; if (r_v0) XPLMGetDatavi(r_v0, &_it_v0, 1, 1);
          double v0 = static_cast<double>(_it_v0);
          put<uint32_t>(dst, static_cast<uint32_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint32_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit/engine/fuel_pump_on");
          { int _sv = static_cast<int>(written_val); if (r_set0) XPLMSetDatavi(r_set0, &_sv, 1, 1); }
      },
      "FuelPump2" },

    // 0x3B70 FLOAT64 r  RPN: $EGT1 1.8 * 491.67 +
    { 0x3B70, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit2/engine/indicators/EGT_deg_C");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 0, 1);
          double v0 = static_cast<double>(_ft_v0);
          double v1 = (v0 * 1.8);
          double v2 = (v1 + 491.67);
          put<double>(dst, static_cast<double>(v2));
      },
      nullptr,
      "EGT1" },

    // 0x3B78 UINT32 rw  RPN: $Gen1On >Gen1On @
    { 0x3B78, 4,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit/electrical/generator_on");
          int _it_v0 = 0; if (r_v0) XPLMGetDatavi(r_v0, &_it_v0, 0, 1);
          double v0 = static_cast<double>(_it_v0);
          put<uint32_t>(dst, static_cast<uint32_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint32_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit/electrical/generator_on");
          { int _sv = static_cast<int>(written_val); if (r_set0) XPLMSetDatavi(r_set0, &_sv, 0, 1); }
      },
      "Gen1On" },

    // 0x3B98 UINT32 rw  RPN: $FuelPump1 >FuelPump1 @
    { 0x3B98, 4,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/cockpit/engine/fuel_pump_on");
          int _it_v0 = 0; if (r_v0) XPLMGetDatavi(r_v0, &_it_v0, 0, 1);
          double v0 = static_cast<double>(_it_v0);
          put<uint32_t>(dst, static_cast<uint32_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint32_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/cockpit/engine/fuel_pump_on");
          { int _sv = static_cast<int>(written_val); if (r_set0) XPLMSetDatavi(r_set0, &_sv, 0, 1); }
      },
      "FuelPump1" },

    // 0x4000 FLOAT64 rw  RPN: $Flaps0 >Flaps0 @
    { 0x4000, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 0, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          { float _sv = static_cast<float>(written_val); if (r_set0) XPLMSetDatavf(r_set0, &_sv, 0, 1); }
      },
      "Flaps0" },

    // 0x4008 FLOAT64 rw  RPN: $Flaps1 >Flaps1 @
    { 0x4008, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 1, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          { float _sv = static_cast<float>(written_val); if (r_set0) XPLMSetDatavf(r_set0, &_sv, 1, 1); }
      },
      "Flaps1" },

    // 0x4010 FLOAT64 rw  RPN: $Flaps2 >Flaps2 @
    { 0x4010, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 2, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          { float _sv = static_cast<float>(written_val); if (r_set0) XPLMSetDatavf(r_set0, &_sv, 2, 1); }
      },
      "Flaps2" },

    // 0x4018 FLOAT64 rw  RPN: $Flaps3 >Flaps3 @
    { 0x4018, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 3, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          { float _sv = static_cast<float>(written_val); if (r_set0) XPLMSetDatavf(r_set0, &_sv, 3, 1); }
      },
      "Flaps3" },

    // 0x4020 FLOAT64 rw  RPN: $Flaps4 >Flaps4 @
    { 0x4020, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 4, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          { float _sv = static_cast<float>(written_val); if (r_set0) XPLMSetDatavf(r_set0, &_sv, 4, 1); }
      },
      "Flaps4" },

    // 0x4028 FLOAT64 rw  RPN: $Flaps5 >Flaps5 @
    { 0x4028, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 5, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          { float _sv = static_cast<float>(written_val); if (r_set0) XPLMSetDatavf(r_set0, &_sv, 5, 1); }
      },
      "Flaps5" },

    // 0x4030 FLOAT64 rw  RPN: $Flaps6 >Flaps6 @
    { 0x4030, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 6, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          { float _sv = static_cast<float>(written_val); if (r_set0) XPLMSetDatavf(r_set0, &_sv, 6, 1); }
      },
      "Flaps6" },

    // 0x4038 FLOAT64 rw  RPN: $Flaps7 >Flaps7 @
    { 0x4038, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 7, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          { float _sv = static_cast<float>(written_val); if (r_set0) XPLMSetDatavf(r_set0, &_sv, 7, 1); }
      },
      "Flaps7" },

    // 0x4040 FLOAT64 rw  RPN: $Flaps8 >Flaps8 @
    { 0x4040, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 8, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          { float _sv = static_cast<float>(written_val); if (r_set0) XPLMSetDatavf(r_set0, &_sv, 8, 1); }
      },
      "Flaps8" },

    // 0x4048 FLOAT64 rw  RPN: $Flaps9 >Flaps9 @
    { 0x4048, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          float _ft_v0 = 0.0f; if (r_v0) XPLMGetDatavf(r_v0, &_ft_v0, 9, 1);
          double v0 = static_cast<double>(_ft_v0);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_dn");
          { float _sv = static_cast<float>(written_val); if (r_set0) XPLMSetDatavf(r_set0, &_sv, 9, 1); }
      },
      "Flaps9" },

    // 0x4050 UINT8 rw  RPN: $GearIsRetractable >GearIsRetractable @
    { 0x4050, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/gear/acf_gear_retract");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint8_t>(dst, static_cast<uint8_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint8_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/gear/acf_gear_retract");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "GearIsRetractable" },

    // 0x4051 UINT8 rw  RPN: $FlapDetents >FlapDetents @
    { 0x4051, 1,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_detents");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDatai(r_v0) : 0);
          put<uint8_t>(dst, static_cast<uint8_t>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<uint8_t>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/controls/acf_flap_detents");
          if (r_set0) XPLMSetDatai(r_set0, static_cast<int>(written_val));
      },
      "FlapDetents" },

    // 0x4060 FLOAT64 rw  RPN: $Vso >Vso @
    { 0x4060, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/view/acf_Vso");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/view/acf_Vso");
          if (r_set0) XPLMSetDataf(r_set0, static_cast<float>(written_val));
      },
      "Vso" },

    // 0x4068 FLOAT64 rw  RPN: $Vs >Vs @
    { 0x4068, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/view/acf_Vs");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/view/acf_Vs");
          if (r_set0) XPLMSetDataf(r_set0, static_cast<float>(written_val));
      },
      "Vs" },

    // 0x4070 FLOAT64 rw  RPN: $Vfe >Vfe @
    { 0x4070, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/view/acf_Vfe");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/view/acf_Vfe");
          if (r_set0) XPLMSetDataf(r_set0, static_cast<float>(written_val));
      },
      "Vfe" },

    // 0x4078 FLOAT64 rw  RPN: $Vno >Vno @
    { 0x4078, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/view/acf_Vno");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/view/acf_Vno");
          if (r_set0) XPLMSetDataf(r_set0, static_cast<float>(written_val));
      },
      "Vno" },

    // 0x4080 FLOAT64 rw  RPN: $FSFSVne >FSFSVne @
    { 0x4080, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/view/acf_Vne");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/view/acf_Vne");
          if (r_set0) XPLMSetDataf(r_set0, static_cast<float>(written_val));
      },
      "FSFSVne" },

    // 0x4088 FLOAT64 rw  RPN: $Splr_up >Splr_up @
    { 0x4088, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/controls/acf_splr_up");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/controls/acf_splr_up");
          if (r_set0) XPLMSetDataf(r_set0, static_cast<float>(written_val));
      },
      "Splr_up" },

    // 0x4090 FLOAT64 rw  RPN: $Water_rud_area >Water_rud_area @
    { 0x4090, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/gear/acf_water_rud_area");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/gear/acf_water_rud_area");
          if (r_set0) XPLMSetDataf(r_set0, static_cast<float>(written_val));
      },
      "Water_rud_area" },

    // 0x4098 FLOAT64 rw  RPN: $Vle >Vle @
    { 0x4098, 8,
      [](uint8_t* dst, DataRefCache&) {
          static XPLMDataRef r_v0 = XPLMFindDataRef("sim/aircraft/overflow/acf_Vle");
          double v0 = static_cast<double>(r_v0 ? XPLMGetDataf(r_v0) : 0.0f);
          put<double>(dst, static_cast<double>(v0));
      },
      [](const uint8_t* src, uint32_t, DataRefCache&) {
          double written_val = static_cast<double>(take<double>(src));
          static XPLMDataRef r_set0 = XPLMFindDataRef("sim/aircraft/overflow/acf_Vle");
          if (r_set0) XPLMSetDataf(r_set0, static_cast<float>(written_val));
      },
      "Vle" },

    }; // end table

    return table;
}
