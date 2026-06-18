// SPDX-License-Identifier: GPL-3.0-or-later
// fsuipc_offsets/Controls.h — Production offset table
//
// 129 total offsets in this category
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

inline const std::vector<OffsetEntry> &fsuipc_offset_table_controls()
{
  static const std::vector<OffsetEntry> table = {

//       {0x0278, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0278");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0278");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "Auto-rudder"},
//
//       // Left aileron deflection — radians
//       {0x03B0, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03B0");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Left aileron deflection"},
//
//       // Right aileron deflection — radians
//       {0x03B8, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x03B8");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Right aileron deflection"},
//
//       // Aileron trim axis input from FSUIPC
//       {0x0480, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0480");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Aileron trim axis input from FSUIPC"},
//
//       // Rudder trim axis input from FSUIPC
//       {0x0488, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0488");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Rudder trim axis input from FSUIPC"},
//
//       // Aileron trim axis control to FSUIPC — Written if axis disconnected
//       // in 04A0
//       {0x0490, 8,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0490");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Aileron trim axis control to FSUIPC"},
//
//       // Rudder trim axis control to FSUIPC — Written if axis disconnected in
//       // 04A0
//       {0x0498, 8,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0498");
//          if (r)
//            XPLMSetDatad(r, static_cast<double>(take<double>(src)));
//        },
//        "Rudder trim axis control to FSUIPC"},
//
//       // Disconnection of trim axes — Set 2^0 to disconnect FSUIPC aileron
//       // trim, Set 2^1 to disconnect FSUIPC rudder trim
//       {0x04A0, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x04A0");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x04A0");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Disconnection of trim axes"},
//
//       // PM GC Controls parameter — See Project Magenta FSUIPC interface
//       // specification
//       {0x04F4, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x04F4");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x04F4");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "PM GC Controls parameter"},
//
//       // Rotor brake application (Robinson only) — 0-16384
//       {0x0822, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0822");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0822");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Rotor brake application (Robinson only)"},
//
//       // Rotor lateral trim (Robinson only) — 0-16384
//       {0x0824, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0824");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0824");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Rotor lateral trim (Robinson only)"},
//
//       // Rotor gov switch (Robinson only) — 0 = off, 1 = on
//       {0x0826, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0826");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0826");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Rotor gov switch (Robinson only)"},
//
//       // Rotor transmission temp — 64-bit double float, in degrees Rankine
//       {0x0828, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0828");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Rotor transmission temp"},
//
//       // Rotor clutch switch [FS2004]
//       {0x0889, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0889");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0889");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Rotor clutch switch [FS2004]"},
//
//       // Eng1 throttle, switchable input
//       {0x089A, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x089A");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x089A");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "Eng1 throttle, switchable input"},
//
//       // Eng2 throttle, switchable input
//       {0x0932, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0932");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0932");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "Eng2 throttle, switchable input"},
//
//       // Eng3 throttle, switchable input
//       {0x09CA, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09CA");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x09CA");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "Eng3 throttle, switchable input"},
//
//       // Eng4 throttle, switchable input
//       {0x0A62, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A62");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0A62");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "Eng4 throttle, switchable input"},
//
//       // Prop pitch system — 0=Fixed pitch propeller 1=Automatic 2=Manual.
//       // (FS2004: 0=fixed pitch, 1=constant speed).
//       {0x0AF0, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0AF0");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0AF0");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Prop pitch system"},

      // Elevator position control — -16383. to +16383
      {0x0BB2, 2, nullptr,
       // Read/Write: Read/Write
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         if (overrides().pitch)
         {
           static XPLMDataRef r_h81 = XPLMFindDataRef("sim/operation/override/override_joystick_pitch");
           if (r_h81)
             XPLMSetDatai(r_h81, 1);
           static XPLMDataRef r_h82 = XPLMFindDataRef("sim/joystick/yoke_pitch_ratio");
           if (r_h82)
             XPLMSetDataf(r_h82, take<int16_t>(src) / 16383.0f);
         }
         else
         {
           static XPLMDataRef r_h83 = XPLMFindDataRef("sim/operation/override/override_joystick_pitch");
           if (r_h83)
             XPLMSetDatai(r_h83, 0);
         }
       },
       "Pitch input (write)"},

      // Elevator indicator
      {0x0BB4, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h84 = XPLMFindDataRef("sim/flightmodel/controls/hstab1_elv1def");
         put<int16_t>(dst, static_cast<int16_t>((r_h84 ? XPLMGetDataf(r_h84) : 0.0f) * (-16363.0f / 15.0f)));
       },
       nullptr,
       "Elevator position indicator"},

      // Alieron position control — -16383 to +16383
      {0x0BB6, 2, nullptr,
       // Read/Write: Read/Write
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         if (overrides().roll)
         {
           static XPLMDataRef r_h85 = XPLMFindDataRef("sim/operation/override/override_joystick_roll");
           if (r_h85)
             XPLMSetDatai(r_h85, 1);
           static XPLMDataRef r_h86 = XPLMFindDataRef("sim/joystick/yoke_roll_ratio");
           if (r_h86)
             XPLMSetDataf(r_h86, take<int16_t>(src) / 16383.0f);
         }
         else
         {
           static XPLMDataRef r_h87 = XPLMFindDataRef("sim/operation/override/override_joystick_roll");
           if (r_h87)
             XPLMSetDatai(r_h87, 0);
         }
       },
       "Roll input (write)"},

      // Alieron indicator
      {0x0BB8, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h88 = XPLMFindDataRef("sim/flightmodel/controls/lail1def");
         put<int16_t>(dst, static_cast<int16_t>((r_h88 ? XPLMGetDataf(r_h88) : 0.0f) * -546.1f));
       },
       nullptr,
       "Aileron position indicator"},

      // Rudder position control — -16383 to +16383
      {0x0BBA, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/controls/yoke_heading_ratio");
         put<int16_t>(dst, static_cast<int16_t>((r ? XPLMGetDataf(r) : 0.0f) * 16383.0f));
       },
       nullptr,
       "Rudder control input"},

      // Rudder indicator
      {0x0BBC, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/controls/ldruddef");
         put<int16_t>(dst, static_cast<int16_t>((r ? XPLMGetDataf(r) : 0.0f) * 546.1f));
       },
       nullptr,
       "Rudder position indicator"},
//
//       // Helicopter pitch trim — -16383. to +16383
//       {0x0BBE, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0BBE");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0BBE");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "Helicopter pitch trim"},

      // Trim position control — -16383 to +16383
      {0x0BC0, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/controls/elv_trim");
         put<int16_t>(dst, static_cast<int16_t>((r ? XPLMGetDataf(r) : 0.0f) * 16383.0f));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/controls/elv_trim");
         if (r)
           XPLMSetDataf(r, take<int16_t>(src) / 16383.0f);
       },
       "Elevator trim input (-16383..+16383)"},
//
//       // Trim indicator
//       {0x0BC2, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0BC2");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Trim indicator"},

      // Brake actual (left) — 0...16383, write to apply a fixed pressure
      // till changed. Use 0C01 to emulate a keypress though.
      {0x0BC4, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/controls/l_brake_add");
         put<int16_t>(dst, static_cast<int16_t>((r ? XPLMGetDataf(r) : 0.0f) * 16383.0f));
       },
       nullptr,
       "Left brake (0-16383)"},

      // Brake actual (right) — 0...16383, write to apply a fixed pressure
      // till changed. Use 0C00 to emulate a keypress though.
      {0x0BC6, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/controls/r_brake_add");
         put<int16_t>(dst, static_cast<int16_t>((r ? XPLMGetDataf(r) : 0.0f) * 16383.0f));
       },
       nullptr,
       "Right brake (0-16383)"},

      // Brake parking — 0=Off, 32768=Set. Setting the parking brake to 32767
      // will set: Brake commanded, and left/right actual brake to 16383
      {0x0BC8, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h142 = XPLMFindDataRef("sim/flightmodel/controls/parkbrake");
         put<int16_t>(dst, static_cast<int16_t>((r_h142 ? XPLMGetDataf(r_h142) : 0.0f) * 32767.0f));
       },
       nullptr,
       "Parking brake (0=off, 32767=on)"},

      // Brake Commanded — Braking indicator 0 = off, 16383 = applied.
      // Probably analogue operation is possible, but not by writing here (at
      // least in FS2000)
      {0x0BCA, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_lb = XPLMFindDataRef("sim/flightmodel/controls/l_brake_add");
         static XPLMDataRef r_rb = XPLMFindDataRef("sim/flightmodel/controls/r_brake_add");
         float lb = r_lb ? XPLMGetDataf(r_lb) : 0.0f;
         float rb = r_rb ? XPLMGetDataf(r_rb) : 0.0f;
         float mx = lb > rb ? lb : rb;
         put<int16_t>(dst, static_cast<int16_t>(mx * 16383.0f));
       },
       nullptr,
       "Braking indicator (max brake, 0-16383)"},

      // Spoiler control — 0=off, 16383=full spoilers deployed
      {0x0BD0, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/controls/sbrkrqst");
         put<int32_t>(dst, static_cast<int32_t>((r ? XPLMGetDataf(r) : 0.0f) * 16383.0f));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/controls/sbrkrqst");
         if (r)
           XPLMSetDataf(r, static_cast<float>(take<int32_t>(src)) / 16383.0f);
       },
       "Spoilers control (0-16383)"},

      // Spolier actual (left) — 0-16383
      {0x0BD4, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/controls/sbrkrat");
         put<int32_t>(dst, static_cast<int32_t>((r ? XPLMGetDataf(r) : 0.0f) * 16383.0f));
       },
       nullptr,
       "Spoiler left position (0-16383)"},

      // Spoiler actual (right) — 0-16383
      {0x0BD8, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/controls/sbrkrat");
         put<int32_t>(dst, static_cast<int32_t>((r ? XPLMGetDataf(r) : 0.0f) * 16383.0f));
       },
       nullptr,
       "Spoiler right position (0-16383)"},

      // Flaps control — 0=Retracted, 16383=fully extended. Values in-between
      // depend only on the NUMBER of positions defined for specific
      // aircraft. Just divide the range from 0-16383 evenly (inc =
      // 16383/(no. of position-1)(
      {0x0BDC, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Actual flap deployment ratio (0=retracted, 1=fully extended), accounts for slow deployment
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/controls/flap_system_deploy_ratio");
         put<int32_t>(dst, static_cast<int32_t>((r ? XPLMGetDataf(r) : 0.0f) * 16383.0f));
       },
       nullptr,
       "Flap actual deployment (INT32, 0=up, 16383=full)"},

      // Flaps indicator (Left) — For FS2002/4 see also 30E0-30FF
      {0x0BE0, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Left flap surface. Left and right (0x0BE4) always work in unison.
         static XPLMDataRef r_h89 = XPLMFindDataRef("sim/cockpit2/controls/flap_system_deploy_ratio");
         put<int32_t>(dst, static_cast<int32_t>((r_h89 ? XPLMGetDataf(r_h89) : 0.0f) * 16383.0f));
       },
       nullptr,
       "Flaps position indicator (left)"},

      // Flaps indicator (right) — For FS2002/4 see also 30E0-30FF
      {0x0BE4, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Right flap surface. Left and right (0x0BE0) always work in unison.
         static XPLMDataRef r_h90 = XPLMFindDataRef("sim/cockpit2/controls/flap_system_deploy_ratio");
         put<int32_t>(dst, static_cast<int32_t>((r_h90 ? XPLMGetDataf(r_h90) : 0.0f) * 16383.0f));
       },
       nullptr,
       "Flaps position indicator (right)"},

      // Gear Commanded — 0=Gear up, 16383=Gear down
      {0x0BE8, 4,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Gear lever: 0 = up, 16383 = down
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/controls/gear_handle_down");
         int v = r ? XPLMGetDatai(r) : 1; // default down for fixed-gear
         put<int32_t>(dst, static_cast<int32_t>(v ? 16383 : 0));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/controls/gear_handle_down");
         if (r)
           XPLMSetDatai(r, take<int32_t>(src) > 8191 ? 1 : 0);
       },
       "Gear lever (0=up, 16383=down)"},

      // Gear actual (nose) — 0=up, 16383=down, other=off
      {0x0BEC, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Gear actual position (main gear, index 1): 0 = retracted, 16383 = extended
         // For fixed-gear aircraft sim/aircraft/gear/acf_gear_retract == 0 and deploy_ratio is always 1.0
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel2/gear/deploy_ratio");
         float v = 1.0f; // default fully extended
         if (r)
           XPLMGetDatavf(r, &v, 1, 1);
         put<int32_t>(dst, static_cast<int32_t>(v * 16383.0f));
       },
       nullptr,
       "Gear actual position (0=up, 16383=down)"},

      // Gear actual (right) — 0=up, 16383=down, other=off
      {0x0BF0, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel2/gear/deploy_ratio");
         float v = 1.0f;
         if (r)
           XPLMGetDatavf(r, &v, 2, 1);
         put<int32_t>(dst, static_cast<int32_t>(v * 16383.0f));
       },
       nullptr,
       "Gear position right (0=up, 16383=down)"},

      // Gear actual (left) — 0=up, 16383=down, other=off
      {0x0BF4, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel2/gear/deploy_ratio");
         float v = 1.0f;
         if (r)
           XPLMGetDatavf(r, &v, 1, 1);
         put<int32_t>(dst, static_cast<int32_t>(v * 16383.0f));
       },
       nullptr,
       "Gear position left (0=up, 16383=down)"},
//
//       // Flaps index — 0 = full up
//       {0x0BFC, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0BFC");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0BFC");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Flaps index"},
//
//       // Right Brake Timer — Toe brake action: value from 0-200 here gives
//       // variable breaking, and decreasing braking proportionally with time.
//       {0x0C00, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C00");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C00");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Right Brake Timer"},
//
//       // Left Brake Timer — Toe brake action: value from 0-200 here gives
//       // variable breaking, and decreasing braking proportionally with time.
//       {0x0C01, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C01");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C01");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Left Brake Timer"},

      // Aileron Trim position/control — -16383 to +16383
      {0x0C02, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/controls/aileron_trim");
         put<int16_t>(dst, static_cast<int16_t>((r ? XPLMGetDataf(r) : 0.0f) * 16383.0f));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/controls/aileron_trim");
         if (r)
           XPLMSetDataf(r, take<int16_t>(src) / 16383.0f);
       },
       "Aileron trim (-16383..+16383)"},

      // Rudder Trim position/control — -16383 to +16383
      {0x0C04, 2,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/controls/rudder_trim");
         put<int16_t>(dst, static_cast<int16_t>((r ? XPLMGetDataf(r) : 0.0f) * 16383.0f));
       },
       [](const uint8_t *src, uint32_t, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/controls/rudder_trim");
         if (r)
           XPLMSetDataf(r, take<int16_t>(src) / 16383.0f);
       },
       "Rudder trim (-16383..+16383)"},
//
//       // Helo bank trim control — -16383 to +16383
//       {0x0C06, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C06");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C06");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<int16_t>(src)));
//        },
//        "Helo bank trim control"},
//
//       // Steering tiller calibrated value — -16383 to +16383
//       {0x0C08, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C08");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Steering tiller calibrated value"},
//
//       // Rudder calibrated value — -16383 to +16383
//       {0x0C0A, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x0C0A");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Rudder calibrated value"},
//
//       // Water rudder left extended
//       {0x2A78, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Water rudder left extended"},
//
//       // Water rudder right extended
//       {0x2A80, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Water rudder right extended"},
//
//       // Water rudder handle position — 16384 = 100%
//       {0x2A88, 2,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Water rudder handle position"},
//
//       // Tail wheel lock (FSX) — 0 = unlocked, 1 = locked
//       {0x2A90, 4,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Tail wheel lock (FSX)"},

      // Elevator Deflection — Radians (up +ve, down -ve)
      {0x2E98, 8,
       // Read/Write: Unknown
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // hstab1_elv1def is actual elevator deflection in degrees; elv_trim was the trim ratio (wrong).
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/controls/hstab1_elv1def");
         put<double>(dst, static_cast<double>(r ? XPLMGetDataf(r) : 0.0f) * (3.14159265358979 / 180.0));
       },
       nullptr,
       "Elevator deflection (double)"},
//
//       // Elevator Trim — Radians (up +ve, down -ve)
//       {0x2EA0, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Elevator Trim"},

      // Aileron Deflection — Radians (right turn +ve, left turn -ve)
      {0x2EA8, 8,
       // Read/Write: Unknown
       // turn positive, left turn negative.
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // lail1def is in degrees; FSUIPC expects radians.
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/controls/lail1def");
         put<double>(dst, static_cast<double>(r ? -XPLMGetDataf(r) : 0.0f) * (3.14159265358979 / 180.0));
       },
       nullptr,
       "Aileron deflection (double)"},

      // Aileron Trim — Radians (right turn +ve, left turn -ve)
      {0x2EB0, 8,
       // Read/Write: Unknown
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/controls/ail_trim");
         put<double>(dst, static_cast<double>(r ? XPLMGetDataf(r) : 0.0f));
       },
       nullptr,
       "Aileron trim (double)"},

      // Rudder Deflection — Radians
      {0x2EB8, 8,
       // Read/Write: Unknown
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // ldruddef is in degrees; FSUIPC expects radians.
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/controls/ldruddef");
         put<double>(dst, static_cast<double>(r ? XPLMGetDataf(r) : 0.0f) * (3.14159265358979 / 180.0));
       },
       nullptr,
       "Rudder deflection (double)"},

      // Rudder Trim — Radians
      {0x2EC0, 8,
       // Read/Write: Unknown
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/controls/rud_trim");
         put<double>(dst, static_cast<double>(r ? XPLMGetDataf(r) : 0.0f));
       },
       nullptr,
       "Rudder trim (double)"},
//
//       // Concorde Visor Pos. Pct.
//       {0x2F28, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Concorde Visor Pos. Pct."},
//
//       // Concorde Nose Angle
//       {0x2F30, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Concorde Nose Angle"},
//
//       // Gear Pos Tail
//       {0x2F38, 8,
//        // Read/Write: Unknown
//        nullptr,
//        nullptr,
//        "Gear Pos Tail"},

      // Trailing edge flaps left inboard % — FS2002 and FS2004 only,
      // 16383=100%, max flap angle
      {0x30E0, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Trailing edge left inboard flap extension (% * 16383)
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/controls/flap_system_deploy_ratio");
         put<int16_t>(dst, static_cast<int16_t>((r ? XPLMGetDataf(r) : 0.0f) * 16383.0f));
       },
       nullptr,
       "TE flap left inboard % (INT16, 0=up, 16383=full)"},

      // Trailing edge flaps left outboard % — FS2002 and FS2004 only,
      // 16383=100%, max flap angle
      {0x30E2, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Trailing edge left outboard flap extension (% * 16383)
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/controls/flap_system_deploy_ratio");
         put<int16_t>(dst, static_cast<int16_t>((r ? XPLMGetDataf(r) : 0.0f) * 16383.0f));
       },
       nullptr,
       "TE flap left outboard % (INT16, 0=up, 16383=full)"},

      // Trailing edge flaps right inboard % — FS2002 and FS2004 only,
      // 16383=100%, max flap angle
      {0x30E4, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Trailing edge right inboard flap extension (% * 16383)
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/controls/flap_system_deploy_ratio");
         put<int16_t>(dst, static_cast<int16_t>((r ? XPLMGetDataf(r) : 0.0f) * 16383.0f));
       },
       nullptr,
       "TE flap right inboard % (INT16, 0=up, 16383=full)"},

      // Trailing edge flaps right outboard % — FS2002 and FS2004 only,
      // 16383=100%, max flap angle
      {0x30E6, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         // Trailing edge right outboard flap extension (% * 16383)
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit2/controls/flap_system_deploy_ratio");
         put<int16_t>(dst, static_cast<int16_t>((r ? XPLMGetDataf(r) : 0.0f) * 16383.0f));
       },
       nullptr,
       "TE flap right outboard % (INT16, 0=up, 16383=full)"},

      // Leading edge flaps left inboard % — FS2002 and FS2004 only,
      // 16383=100%, max flap angle
      {0x30E8, 2,
       // Read/Write: Read (only)
       // percentage, as a fraction of 65536 (16383 = 25% extension)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel2/controls/slat1_deploy_ratio");
         put<uint16_t>(dst, static_cast<uint16_t>((r ? XPLMGetDataf(r) : 0.0f) * 65536.0f));
       },
       nullptr,
       "Slat/LE flap deploy ratio (0-65535)"},
//
//       // Leading edge flaps left outboard % — FS2002 and FS2004 only,
//       // 16383=100%, max flap angle
//       {0x30EA, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x30EA");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Leading edge flaps left outboard %"},
//
//       // Leading edge flaps right inboard % — FS2002 and FS2004 only,
//       // 16383=100%, max flap angle
//       {0x30EC, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x30EC");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Leading edge flaps right inboard %"},
//
//       // Leading edge flaps right outboard % — FS2002 and FS2004 only,
//       // 16383=100%, max flap angle
//       {0x30EE, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x30EE");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Leading edge flaps right outboard %"},

      // Trailing edge flaps left inboard angle — FS2002 and FS2004 only,
      // degrees * 256
      {0x30F0, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/controls/wing1l_fla1def");
         put<int16_t>(dst, static_cast<int16_t>((r ? XPLMGetDataf(r) : 0.0f) * 256.0f));
       },
       nullptr,
       "TE flap left inboard (deg*256)"},

      // Trailing edge flaps left outboard angle — FS2002 and FS2004 only,
      // degrees * 256
      {0x30F2, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/controls/wing2l_fla1def");
         put<int16_t>(dst, static_cast<int16_t>((r ? XPLMGetDataf(r) : 0.0f) * 256.0f));
       },
       nullptr,
       "TE flap left outboard (deg*256)"},

      // Trailing edge flaps right inboard angle — FS2002 and FS2004 only,
      // degrees * 256
      {0x30F4, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/controls/wing1r_fla1def");
         put<int16_t>(dst, static_cast<int16_t>((r ? XPLMGetDataf(r) : 0.0f) * 256.0f));
       },
       nullptr,
       "TE flap right inboard (deg*256)"},

      // Trailing edge flaps right outboard angle — FS2002 and FS2004 only,
      // degrees * 256
      {0x30F6, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/flightmodel/controls/wing2r_fla1def");
         put<int16_t>(dst, static_cast<int16_t>((r ? XPLMGetDataf(r) : 0.0f) * 256.0f));
       },
       nullptr,
       "TE flap right outboard (deg*256)"},
//
//       // Leading edge flaps left inboard angle — FS2002 and FS2004 only,
//       // degrees * 256
//       {0x30F8, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x30F8");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Leading edge flaps left inboard angle"},
//
//       // Leading edge flaps left outboard angle — FS2002 and FS2004 only,
//       // degrees * 256
//       {0x30FA, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x30FA");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Leading edge flaps left outboard angle"},
//
//       // Leading edge flaps right inboard angle — FS2002 and FS2004 only,
//       // degrees * 256
//       {0x30FC, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x30FC");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Leading edge flaps right inboard angle"},
//
//       // Leading edge flaps right outboard angle — FS2002 and FS2004 only,
//       // degrees * 256
//       {0x30FE, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x30FE");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Leading edge flaps right outboard angle"},
//
//       // Engine primer — One shot, write Non-Zero to operate primer
//       {0x3100, 1,
//        // Read/Write: Write (only)
//        nullptr,
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3100");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Engine primer"},

      // Master Alternator switch — 0=off, 1=on
      {0x3101, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/electrical/generator_on");
         int v = 0;
         if (r)
           XPLMGetDatavi(r, &v, 0, 1);
         put<uint8_t>(dst, static_cast<uint8_t>(v));
       },
       nullptr,
       "Alternator / generator 1"},

      // Master Battery switch — 0=off, 1=on
      {0x3102, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/electrical/battery_on");
         put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
       },
       nullptr,
       "Battery master switch"},

      // Avionics switch — 0=off, 1=on
      {0x3103, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/electrical/avionics_on");
         put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
       },
       nullptr,
       "Avionics master switch"},

      // Fuel pump swittch — 0=off, 1=on (see 3125 for separate switches on
      // FS2000/2002)
      {0x3104, 1,
       // Read/Write: Read/Write
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r = XPLMFindDataRef("sim/cockpit/engine/fuel_pump_on");
         int v = 0;
         if (r)
           XPLMGetDatavi(r, &v, 0, 1);
         put<uint8_t>(dst, static_cast<uint8_t>(v));
       },
       nullptr,
       "Fuel pump 1"},
//
//       // Slew axis longitudinal axis input
//       {0x31D8, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31D8");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Slew axis longitudinal axis input"},
//
//       // Slew axis lateral axis input
//       {0x31DA, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31DA");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Slew axis lateral axis input"},
//
//       // Slew axis yaw axis input
//       {0x31DC, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31DC");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Slew axis yaw axis input"},
//
//       // Slew axis vertical axis input
//       {0x31DE, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31DE");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Slew axis vertical axis input"},
//
//       // Slew axis roll axis input
//       {0x31E0, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31E0");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Slew axis roll axis input"},
//
//       // Slew axis pitch axis input
//       {0x31E2, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x31E2");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Slew axis pitch axis input"},
//
//       // Brakes being used flag
//       {0x32F9, 1,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x32F9");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Brakes being used flag"},

      // Altimeter altitude in feet OR metres — Note tyhat metres are used if
      // 0C18 contains 2!
      {0x3324, 4,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h131 = XPLMFindDataRef("sim/flightmodel/misc/h_ind2");
         put<int32_t>(dst, static_cast<int32_t>((r_h131 ? XPLMGetDataf(r_h131) : 0.0f)));
       },
       nullptr,
       "Pressure altitude"},
//
//       // Elevator axis input — Post calibration, before delivery
//       {0x3328, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3328");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Elevator axis input"},
//
//       // Ailerons axis input — Post calibration, before delivery
//       {0x332A, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x332A");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Ailerons axis input"},
//
//       // Rudder axis input — Post calibration, before delivery
//       {0x332C, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x332C");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Rudder axis input"},
//
//       // Throttle (common) axis input — This throttle axis is applied to the
//       // Engines sel;ected by word at offset 0888. Post calibration, before
//       // delivery
//       {0x332E, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x332E");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Throttle (common) axis input"},

      // Throttle 1 axis input — Post calibration, before delivery
      {0x3330, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h132 = XPLMFindDataRef("sim/cockpit2/engine/actuators/throttle_ratio");
         float _fv132 = 0.0f;
         if (r_h132)
           XPLMGetDatavf(r_h132, &_fv132, 0, 1);
         put<int16_t>(dst, static_cast<int16_t>(_fv132 * 16384.0f));
       },
       nullptr,
       "Engine 1 throttle input"},

      // Throttle 2 axis input — Post calibration, before delivery
      {0x3332, 2,
       // Read/Write: Read (only)
       [](uint8_t *dst, DataRefCache &dref)
       {
         (void)dref;
         static XPLMDataRef r_h133 = XPLMFindDataRef("sim/cockpit2/engine/actuators/throttle_ratio");
         float _fv133 = 0.0f;
         if (r_h133)
           XPLMGetDatavf(r_h133, &_fv133, 1, 1);
         put<int16_t>(dst, static_cast<int16_t>(_fv133 * 16384.0f));
       },
       nullptr,
       "Engine 2 throttle input"},
//
//       // Throttle 3 axis input — Post calibration, before delivery
//       {0x3334, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3334");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Throttle 3 axis input"},
//
//       // Throttle 4 axis input — Post calibration, before delivery
//       {0x3336, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3336");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Throttle 4 axis input"},
//
//       // Elevator trim axis input — Post calibration, before delivery
//       {0x3338, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3338");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Elevator trim axis input"},
//
//       // Throttle reverse limit — FS2002 and later only
//       {0x333A, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x333A");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Throttle reverse limit"},
//
//       // Reverser indicators — Assorted indicator flags. These are the only
//       // ones currently set (bit numbers, bit 0 = 2^0): 4     Engine 1
//       // Reverser is set but inhibited* 5       Engine 2 Reverser is set but
//       // inhibited* 6       Engine 3 Reverser is set but inhibited* 7
//       // Engine 4 Reverser is set but inhibited* * Reverser inhibits are set
//       // in offset 32F8. Note that these flags will be cleared only when the
//       // inhibit is removed or the relevant throttle input goes positive
//       // (i.e. not just to idle).
//       {0x3410, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3410");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Reverser indicators"},
//
//       // Spoiler axis calibrated value
//       {0x3412, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3412");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Spoiler axis calibrated value"},
//
//       // Flaps axis calibrated value
//       {0x3414, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3414");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Flaps axis calibrated value"},
//
//       // Left brake axis calibrated value
//       {0x3416, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3416");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Left brake axis calibrated value"},
//
//       // Right brake axis calibrated value
//       {0x3418, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3418");
//          put<int16_t>(dst, static_cast<int16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Right brake axis calibrated value"},
//
//       // Ancillary axis disconnection — Bits control FSUIPC disconnection for
//       // the following axes:
//       {0x341A, 1,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x341A");
//          put<uint8_t>(dst, static_cast<uint8_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x341A");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint8_t>(src)));
//        },
//        "Ancillary axis disconnection"},
//
//       // PFC raw axis 0 (aileron)
//       {0x3BA8, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BA8");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PFC raw axis 0 (aileron)"},
//
//       // PFC raw axis 1 (elevator)
//       {0x3BAA, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BAA");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PFC raw axis 1 (elevator)"},
//
//       // PFC raw axis 2 (rudder)
//       {0x3BAC, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BAC");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PFC raw axis 2 (rudder)"},
//
//       // PFC raw axis 3 (quad #5)
//       {0x3BAE, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BAE");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PFC raw axis 3 (quad #5)"},
//
//       // PFC raw axis 4 (quad #3)
//       {0x3BB0, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BB0");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PFC raw axis 4 (quad #3)"},
//
//       // PFC raw axis 5 (quad #1)
//       {0x3BB2, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BB2");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PFC raw axis 5 (quad #1)"},
//
//       // PFC raw axis 6 (left brakes)
//       {0x3BB4, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BB4");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PFC raw axis 6 (left brakes)"},
//
//       // PFC raw axis 7 (quad #6)
//       {0x3BB6, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BB6");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PFC raw axis 7 (quad #6)"},
//
//       // PFC raw axis 8 (quad #4)
//       {0x3BB8, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BB8");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PFC raw axis 8 (quad #4)"},
//
//       // PFC raw axis 9 (quad #2)
//       {0x3BBA, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BBA");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PFC raw axis 9 (quad #2)"},
//
//       // PFC raw axis 10 (right brakes)
//       {0x3BBC, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BBC");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PFC raw axis 10 (right brakes)"},
//
//       // PFC raw axis 11 (elev trim)
//       {0x3BBE, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BBE");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PFC raw axis 11 (elev trim)"},
//
//       // PFC raw axis 12 (ail trim)
//       {0x3BC0, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BC0");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PFC raw axis 12 (ail trim)"},
//
//       // PFC raw axis 13 (rud trim)
//       {0x3BC2, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BC2");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PFC raw axis 13 (rud trim)"},
//
//       // PFC raw axis 14 (tiller)
//       {0x3BC4, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BC4");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PFC raw axis 14 (tiller)"},
//
//       // PFC raw axis 15 (unassigned))
//       {0x3BC6, 2,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BC6");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "PFC raw axis 15 (unassigned))"},
//
//       // PFC axis disconnect control — Set bit to disconnect equivalent PFC
//       // axis (bits 0-15 = axes 0-15)
//       {0x3BC8, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BC8");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BC8");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "PFC axis disconnect control"},
//
//       // Attitude Indicator failure timer [FS2000 only] — > 20.0 fails AI
//       {0x3BE8, 8,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BE8");
//          put<double>(dst, static_cast<double>(r ? XPLMGetDatad(r) : 0.0));
//        },
//        nullptr,
//        "Attitude Indicator failure timer [FS2000 only]"},
//
//       // Attitude Indicator Lock [FS2000 only]
//       {0x3BF0, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BF0");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Attitude Indicator Lock [FS2000 only]"},
//
//       // Low vacuum [FS2000 only]
//       {0x3BF4, 4,
//        // Read/Write: Read (only)
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BF4");
//          put<uint32_t>(dst, static_cast<uint32_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        nullptr,
//        "Low vacuum [FS2000 only]"},
//
//       // Flap detent increment [FS2000+] — [FS2k only] The full range of flap
//       // movement is 0-0x3FFF (16383). Each detent position or "notch" is
//       // spaced equidistant in this range, no matter what flap angle is
//       // represented -- a table in the AIR filegives those. To obtain the
//       // numvber of detents, divide this increment value into 16384 and add
//       // 1.
//       {0x3BFA, 2,
//        // Read/Write: Read/Write
//        [](uint8_t *dst, DataRefCache &dref)
//        {
//          (void)dref;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BFA");
//          put<uint16_t>(dst, static_cast<uint16_t>(r ? XPLMGetDatai(r) : 0));
//        },
//        [](const uint8_t *src, uint32_t sz, DataRefCache &dref)
//        {
//          (void)dref;
//          (void)sz;
//          static XPLMDataRef r = XPLMFindDataRef("TODO: sim/fsuipc_0x3BFA");
//          if (r)
//            XPLMSetDatai(r, static_cast<int>(take<uint16_t>(src)));
//        },
//        "Flap detent increment [FS2000+]"},

  }; // end table
  return table;
}
