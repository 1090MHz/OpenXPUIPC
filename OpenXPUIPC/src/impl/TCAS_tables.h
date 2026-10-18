// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

#include "offset_types.h"

#include <XPLMProcessing.h>
#include <XPlaneUtilities/XPlaneLog.h>

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

namespace tcas_tables
{
  constexpr int kSlots = 96;
  constexpr uint32_t kSlotSize = 40;
  constexpr uint32_t kExtraSize = 20;
  constexpr int kTargets = 64;
  constexpr float kMetresToFeet = 3.28084f;
  constexpr float kMsToKnots = 1.943844f;
  constexpr float kMsToFpm = 196.85f;
  constexpr float kMetresPerNm = 1852.0f;
  constexpr float kDegToU16 = 65536.0f / 360.0f;
  constexpr uint8_t kStateEnroute = 0x8C;
  constexpr uint8_t kStateTaxiing = 0x88;
  constexpr uint8_t kStateParked = 0x81;

  struct Config
  {
    uint8_t ground_range_user_in_air = 0;
    uint8_t ground_range_user_on_ground = 0;
    uint8_t ground_id_option = 0;
    uint8_t active_traffic_preferred = 0;
    uint8_t air_range = 0;
    uint8_t air_id_option = 0;
  };

  inline Config &config()
  {
    static Config c;
    return c;
  }

  struct Entry
  {
    int32_t id = 0;
    float lat = 0, lon = 0, alt_ft = 0;
    uint16_t heading = 0, ground_speed = 0;
    int16_t vertical_speed = 0;
    int16_t pitch = 0, bank = 0;
    uint8_t state = 0;
    float distance_m = 0;
    char atc_id[15] = {};
  };

  struct Table
  {
    std::array<std::array<uint8_t, kSlotSize>, kSlots> bytes{};
    std::array<std::array<uint8_t, kExtraSize>, kSlots> extra{};
    std::array<uint8_t, kSlots> changed{};
    std::array<int32_t, kSlots> id{};
    uint16_t used = 0;
    uint16_t counter = 0;
    uint16_t nearest = 0;
  };

  struct State
  {
    Table tables[2];
    int cycle = -1;
    int logged_ground = -1, logged_air = -1;
  };

  inline State &state()
  {
    static State s;
    return s;
  }

  inline void build_atc_id(char (&out)[15], int option, const char *flight, const char *type, int32_t id)
  {
    char buf[32];
    if (option == 4 && type[0])
      std::snprintf(buf, sizeof(buf), "%s %s", type, flight);
    else if ((option == 2 || option == 5) && type[0])
      std::snprintf(buf, sizeof(buf), "%s", type);
    else if (flight[0])
      std::snprintf(buf, sizeof(buf), "%s", flight);
    else
      std::snprintf(buf, sizeof(buf), "%06X", static_cast<unsigned>(id));
    std::memset(out, 0, sizeof(out));
    std::memcpy(out, buf, (std::min<size_t>)(std::strlen(buf), sizeof(out) - 1));
  }

  inline void place(Table &t, const std::vector<Entry> &entries, uint16_t slot_base)
  {
    bool any_changed = false;

    for (int slot = 0; slot < kSlots; ++slot)
    {
      if (t.id[slot] == 0)
        continue;
      const bool present = std::any_of(entries.begin(), entries.end(),
                                       [&](const Entry &entry) { return entry.id == t.id[slot]; });
      if (!present)
      {
        t.id[slot] = 0;
        t.bytes[slot].fill(0);
        t.extra[slot].fill(0);
        ++t.changed[slot];
        any_changed = true;
      }
    }

    float nearest_m = 0.0f;
    t.nearest = 0;

    for (const Entry &entry : entries)
    {
      int slot = -1;
      for (int i = 0; i < kSlots && slot < 0; ++i)
        if (t.id[i] == entry.id)
          slot = i;
      for (int i = 0; i < kSlots && slot < 0; ++i)
        if (t.id[i] == 0)
          slot = i;
      if (slot < 0)
        continue;
      t.id[slot] = entry.id;

      std::array<uint8_t, kSlotSize> bytes{};
      uint8_t *p = bytes.data();
      put<int32_t>(p + 0x00, entry.id);
      put<float>(p + 0x04, entry.lat);
      put<float>(p + 0x08, entry.lon);
      put<float>(p + 0x0C, entry.alt_ft);
      put<uint16_t>(p + 0x10, entry.heading);
      put<uint16_t>(p + 0x12, entry.ground_speed);
      put<int16_t>(p + 0x14, entry.vertical_speed);
      std::memcpy(p + 0x16, entry.atc_id, sizeof(entry.atc_id));
      p[0x25] = entry.state;

      std::array<uint8_t, kExtraSize> extra{};
      put<int32_t>(extra.data() + 0x00, entry.id);
      put<int16_t>(extra.data() + 0x06, entry.pitch);
      put<int16_t>(extra.data() + 0x12, entry.bank);

      if (bytes != t.bytes[slot] || extra != t.extra[slot])
      {
        t.bytes[slot] = bytes;
        t.extra[slot] = extra;
        ++t.changed[slot];
        any_changed = true;
      }
      t.used = (std::max<uint16_t>)(t.used, static_cast<uint16_t>(slot + 1));

      if (t.nearest == 0 || entry.distance_m < nearest_m)
      {
        nearest_m = entry.distance_m;
        t.nearest = static_cast<uint16_t>(slot_base + slot * kSlotSize);
      }
    }

    if (any_changed)
      ++t.counter;
  }

  inline void refresh(DataRefCache &dref)
  {
    State &current = state();
    const int cycle = XPLMGetCycleNumber();
    if (cycle == current.cycle)
      return;
    current.cycle = cycle;

    int mode_s[kTargets] = {}, on_wheels[kTargets] = {};
    float lat[kTargets] = {}, lon[kTargets] = {}, ele[kTargets] = {}, vert[kTargets] = {};
    float psi[kTargets] = {}, vx[kTargets] = {}, vz[kTargets] = {}, dist[kTargets] = {};
    float pitch[kTargets] = {}, bank[kTargets] = {};
    char flight[kTargets * 8] = {}, type[kTargets * 8] = {};

    auto get_i = [&](const char *path, int *out)
    {
      if (XPLMDataRef ref = dref.find(path))
        XPLMGetDatavi(ref, out, 0, kTargets);
    };
    auto get_f = [&](const char *path, float *out)
    {
      if (XPLMDataRef ref = dref.find(path))
        XPLMGetDatavf(ref, out, 0, kTargets);
    };
    auto get_s = [&](const char *path, char *out)
    {
      if (XPLMDataRef ref = dref.find(path))
        XPLMGetDatab(ref, out, 0, kTargets * 8);
    };

    get_i("sim/cockpit2/tcas/targets/modeS_id", mode_s);
    get_i("sim/cockpit2/tcas/targets/position/weight_on_wheels", on_wheels);
    get_f("sim/cockpit2/tcas/targets/position/lat", lat);
    get_f("sim/cockpit2/tcas/targets/position/lon", lon);
    get_f("sim/cockpit2/tcas/targets/position/ele", ele);
    get_f("sim/cockpit2/tcas/targets/position/vertical_speed", vert);
    get_f("sim/cockpit2/tcas/targets/position/psi", psi);
    get_f("sim/cockpit2/tcas/targets/position/the", pitch);
    get_f("sim/cockpit2/tcas/targets/position/phi", bank);
    get_f("sim/cockpit2/tcas/targets/position/vx", vx);
    get_f("sim/cockpit2/tcas/targets/position/vz", vz);
    get_f("sim/cockpit2/tcas/indicators/relative_distance_mtrs", dist);
    get_s("sim/cockpit2/tcas/targets/flight_id", flight);
    get_s("sim/cockpit2/tcas/targets/icao_type", type);

    const bool user_on_ground = dref.get_i("sim/flightmodel/failures/onground_any") != 0;
    const Config &settings = config();

    std::vector<Entry> ground, air;
    for (int i = 1; i < kTargets; ++i)
    {
      const int32_t id = mode_s[i] & 0x00FFFFFF;
      if (id == 0)
        continue;

      const bool is_ground = on_wheels[i] != 0;
      const uint8_t range = is_ground ? (user_on_ground ? settings.ground_range_user_on_ground
                                                        : settings.ground_range_user_in_air)
                                      : settings.air_range;
      if (range != 0 && dist[i] / kMetresPerNm > range)
        continue;

      Entry entry;
      entry.id = id;
      entry.lat = lat[i];
      entry.lon = lon[i];
      entry.alt_ft = ele[i] * kMetresToFeet;

      float heading = std::fmod(psi[i], 360.0f);
      if (heading < 0.0f)
        heading += 360.0f;
      entry.heading = static_cast<uint16_t>((std::min)(heading / 360.0f * 65536.0f, 65535.0f));

      const float gs = std::sqrt(vx[i] * vx[i] + vz[i] * vz[i]) * kMsToKnots;
      entry.ground_speed = static_cast<uint16_t>((std::min)(gs, 65535.0f));
      entry.vertical_speed = static_cast<int16_t>((std::max)(-32768.0f, (std::min)(vert[i], 32767.0f)));
      entry.pitch = static_cast<int16_t>((std::max)(-32768.0f, (std::min)(pitch[i] * kDegToU16, 32767.0f)));
      entry.bank = static_cast<int16_t>((std::max)(-32768.0f, (std::min)(bank[i] * kDegToU16, 32767.0f)));
      entry.distance_m = dist[i];
      entry.state = !is_ground ? kStateEnroute : (gs > 2.0f ? kStateTaxiing : kStateParked);

      flight[i * 8 + 7] = 0;
      type[i * 8 + 7] = 0;
      build_atc_id(entry.atc_id, is_ground ? settings.ground_id_option : settings.air_id_option,
                   &flight[i * 8], &type[i * 8], id);
      (is_ground ? ground : air).push_back(entry);
    }

    place(current.tables[0], ground, 0xE080);
    place(current.tables[1], air, 0xF080);

    if (static_cast<int>(ground.size()) != current.logged_ground ||
        static_cast<int>(air.size()) != current.logged_air)
    {
      current.logged_ground = static_cast<int>(ground.size());
      current.logged_air = static_cast<int>(air.size());
      XPLANE_LOG_DEBUG("TCAS tables: {} airborne, {} ground (slots used: {} airborne, {} ground)",
                       air.size(), ground.size(), current.tables[1].used, current.tables[0].used);
    }
  }

  template <int T> inline void rd_slot_size(uint8_t *dst, DataRefCache &) { put<uint16_t>(dst, kSlotSize); }
  template <int T> inline void rd_slot_count(uint8_t *dst, DataRefCache &) { put<uint16_t>(dst, kSlots); }
  template <int T> inline void rd_used(uint8_t *dst, DataRefCache &d)
  {
    refresh(d);
    put<uint16_t>(dst, state().tables[T].used);
  }
  template <int T> inline void rd_counter(uint8_t *dst, DataRefCache &d)
  {
    refresh(d);
    put<uint16_t>(dst, state().tables[T].counter);
  }
  template <int T> inline void rd_changed(uint8_t *dst, DataRefCache &d)
  {
    refresh(d);
    std::memcpy(dst, state().tables[T].changed.data(), kSlots);
  }
  template <int T> inline void rd_slots(uint8_t *dst, DataRefCache &d)
  {
    refresh(d);
    for (int slot = 0; slot < kSlots; ++slot)
      std::memcpy(dst + slot * kSlotSize, state().tables[T].bytes[slot].data(), kSlotSize);
  }
  template <int T> inline void rd_nearest(uint8_t *dst, DataRefCache &d)
  {
    refresh(d);
    put<uint16_t>(dst, state().tables[T].nearest);
  }
  template <int T> inline void rd_extra(uint8_t *dst, DataRefCache &d)
  {
    refresh(d);
    for (int slot = 0; slot < kSlots; ++slot)
      std::memcpy(dst + slot * kExtraSize, state().tables[T].extra[slot].data(), kExtraSize);
  }
} // namespace tcas_tables