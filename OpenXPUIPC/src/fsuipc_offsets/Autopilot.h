// SPDX-License-Identifier: GPL-3.0-or-later
// fsuipc_offsets/Autopilot.h — Production offset table
//
// 46 total offsets in this category
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
#include "impl/autopilot.h"  // autopilot_state_bool(), autopilot:: constants

inline const std::vector<OffsetEntry> &fsuipc_offset_table_autopilot()
{
  static const std::vector<OffsetEntry> table = {

//       {0x04F0, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x04F0");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PM MCP lights"},
//
//       // Target pitch for elevator feedback control — For external autopilot
//       // implementation
//       {0x0700, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0700");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0700");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Target pitch for elevator feedback control"},
//
//       // Switch to enable/disable elevator feedback control — NZ for enabled,
//       // Zero else
//       {0x0708, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0708");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0708");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Switch to enable/disable elevator feedback control"},
//
//       // Target bank for aileron feedback control — For external autopilot
//       // implementation
//       {0x0718, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0718");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0718");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Target bank for aileron feedback control"},
//
//       // Switch to enable/disable aileron feedback control — NZ for enabled,
//       // Zero else
//       {0x0720, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0720");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0720");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Switch to enable/disable aileron feedback control"},
//
//       // Target speed for throttle feedback control — For external autopilot
//       // implementation
//       {0x0730, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0730");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0730");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Target speed for throttle feedback control"},
//
//       // Switch to enable/disable speed feedback control — NZ for enabled,
//       // Zero else
//       {0x0738, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0738");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0738");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Switch to enable/disable speed feedback control"},
//
//       // Target mach for throttle feedback control — For external
//       // autothrottle implementation
//       {0x0748, 8,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0748");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0748");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Target mach for throttle feedback control"},
//
//       // Switch to enable/disable mach feedback control — NZ for enabled,
//       // Zero else
//       {0x0750, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0750");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0750");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Switch to enable/disable mach feedback control"},
//
//       // Autopilot available — 0=no autopilot, 1=A/P available
//       {0x0764, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0764");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Autopilot available"},
//
//       // Fly by wire ELAC switch
//       {0x07B6, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x07B6");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x07B6");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Fly by wire ELAC switch"},
//
//       // Fly by wire ELAC comp fail flag
//       {0x07B7, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x07B7");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fly by wire ELAC comp fail flag"},
//
//       // Fly by wire FAC switch
//       {0x07B8, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x07B8");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x07B8");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Fly by wire FAC switch"},
//
//       // Fly by wire FAC comp fail flag
//       {0x07B9, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x07B9");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fly by wire FAC comp fail flag"},
//
//       // Fly by wire SEC switch
//       {0x07BA, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x07BA");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x07BA");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Fly by wire SEC switch"},
//
//       // Fly by wire SEC comp fail flag
//       {0x07BB, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x07BB");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Fly by wire SEC comp fail flag"},

      // AP Master Switch — 0=Off, 1=Active
      {0x07BC, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/autopilot/servos_on");
         put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
       },
       nullptr,
       "AP master switch"},

      // AP Wing LVL — 0=Off, 1=Active
      {0x07C0, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         put<uint32_t>(dst, autopilot_state_bool(autopilot::kRollHoldEngage));
       },
       nullptr,
       "AP wing leveller"},

      // AP Nav1 Hold — 0=off, 1=Active
      {0x07C4, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         put<uint32_t>(dst, autopilot_state_bool(autopilot::kNavArmed | autopilot::kNavEngaged));
       },
       nullptr,
       "AP NAV1 lock"},

      // AP Heading Hold — 0=Off, 1=Active
      {0x07C8, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         put<uint32_t>(dst, autopilot_state_bool(autopilot::kHeadingSelectEngage));
       },
       nullptr,
       "AP heading lock"},

      // AP Heading Value — 16384 = 90°
      {0x07CC, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // FSUIPC format: degrees * 65536 / 360
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/autopilot/heading_mag");
         float h = (r ? XPLMGetDataf(r) : 0.0f);
         put<uint16_t>(dst, static_cast<uint16_t>(h / 360.0f * 65536.0f));
       },
       nullptr,
       "AP heading value"},

      // AP Altitude Hold — 0=Off, 1=Active
      {0x07D0, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         put<uint32_t>(dst, legacy_altitude_lock_value());
       },
       nullptr,
       "AP altitude lock"},

      // AP Altitude Value — In metres*65536
      {0x07D4, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // FSUIPC format: metres * 65536
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/autopilot/altitude");
         float ft = (r ? XPLMGetDataf(r) : 0.0f);
         put<uint32_t>(dst, static_cast<uint32_t>(ft * 0.3048f * 65536.0f));
       },
       nullptr,
       "AP altitude value (m*65536)"},
//
//       // AP Attitude Hold
//       {0x07D8, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x07D8");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x07D8");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "AP Attitude Hold"},

      // AP Air Speed Hold
      {0x07DC, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/autopilot/speed_status");
         put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
       },
       nullptr,
       "AP airspeed hold"},

      // AP Air Speed Value — Knots
      {0x07E2, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/autopilot/airspeed");
         put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDataf(r) : 0.0f));
       },
       nullptr,
       "AP airspeed value (kts)"},

      // AP Mach Hold
      {0x07E4, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/autopilot/airspeed_is_mach");
         put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
       },
       nullptr,
       "AP mach hold"},
//
//       // AP Mach Value — Mach speed * 65536
//       {0x07E8, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x07E8");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x07E8");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "AP Mach Value"},

      // AP V/S Hold — Doesn't seem to be connected in FS2002 or FS2004. V/S
      // operates with a target altitude
      {0x07EC, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         put<uint32_t>(dst, autopilot_state_bool(autopilot::kVerticalSpeedEngage));
       },
       nullptr,
       "AP VS hold"},

      // AP V/S Value — ft/min
      {0x07F2, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/autopilot/vertical_velocity");
         put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDataf(r) : 0.0f));
       },
       nullptr,
       "AP VS value (ft/min)"},

      // AP RPM (N1) Hold
      {0x07F4, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         put<uint32_t>(dst, 0u);
       },
       nullptr,
       "AP RPM hold (not supported)"},
//
//       // AP RPM (N1) Value — 16384 = 100% N1. Writing rounds to the nearest
//       // whole %
//       {0x07F8, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x07F8");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x07F8");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "AP RPM (N1) Value"},
//
//       // AP GS Hold — Linked to 0800, approach hold
//       {0x07FC, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x07FC");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x07FC");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "AP GS Hold"},

      // AP Approach Hold — 0=Off, 1=Active
      {0x0800, 4,
       // Read/Write: Read/Write
       // approach_status: 0=off, 1=armed, 2=captured. Map both armed and captured -> 1.
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/autopilot/approach_status");
         const int status = r ? XPLMGetDatai(r) : 0;
         put<uint32_t>(dst, static_cast<uint32_t>(status > 0 ? 1 : 0));
       },
       nullptr,
       "AP approach hold"},

      // AP BackCourse Hold — 0=Off, 1=Active
      {0x0804, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/autopilot/backcourse_status");
         const int status = r ? XPLMGetDatai(r) : 0;
         put<uint32_t>(dst, static_cast<uint32_t>(status == 2 ? 1 : 0));
       },
       nullptr,
       "AP back course hold"},

      // AP Yaw damper — 0=Off, 1=Active
      {0x0808, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/switches/yaw_damper_on");
         put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
       },
       nullptr,
       "Yaw damper"},
//
//       // AP TO/GA — 0=Off, 1=Active (Take-Off / Go - Around)
//       {0x080C, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x080C");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x080C");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "AP TO/GA"},

      // AP Auto-Throttle ARM — 0=Off, 1=Active (Armed)
      {0x0810, 4,
       // Read/Write: Read/Write
       // autothrottle_enabled: -1=hard off, 0=arm/hold, 1+=engaged mode.
       // Stored as uint32_t so -1 → 0xFFFFFFFF, matching original XPUIPC and
       // the FSUIPC convention where non-zero = armed/engaged.
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/autopilot/autothrottle_enabled");
         put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
       },
       nullptr,
       "Autothrottle arm"},
//
//       // Autopilot max bank (FSX) — Autopilot max bank … degrees. Works for
//       // the default FSX 737.
//       {0x2E04, 4,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2E04");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x2E04");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint32_t>(src)));
//        },
//        "Autopilot max bank (FSX)"},

      // Flight Director Active
      {0x2EE0, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/autopilot/flight_director_mode");
         put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
       },
       nullptr,
       "Flight director active"},

      // Flight Director Pitch — degrees, only when FSD is active
      {0x2EE8, 8,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/autopilot/flight_director_pitch");
         put<double>(dst, static_cast<double>(r ? -XPLMGetDataf(r) : 0.0f));
       },
       nullptr,
       "Flight director pitch (deg, double)"},

      // Flight Director Bank — degrees. Right -ve, Left +ve
      {0x2EF0, 8,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/autopilot/flight_director_roll");
         put<double>(dst, static_cast<double>(r ? -XPLMGetDataf(r) : 0.0f));
       },
       nullptr,
       "Flight director roll (deg, double)"},
//
//       // AutoPilot Max Speed
//       {0x2F40, 2,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "AutoPilot Max Speed"},
//
//       // AutoPilot Cruise Speed
//       {0x2F48, 2,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "AutoPilot Cruise Speed"},
//
//       // Panel Autopilot Speed Setting
//       {0x3458, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Panel Autopilot Speed Setting"},
//
//       // Autopilot Airspeed Hold Current
//       {0x3460, 2,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Autopilot Airspeed Hold Current"},

  }; // end table
  return table;
}
