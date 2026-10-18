// SPDX-License-Identifier: GPL-3.0-or-later
// FSUIPC "New Weather locations" read protocol (0xCC00-0xCFFF + METAR at 0xB800).
//
// Client writes ICAO ("GLOB" = global, spaces = use lat/lon) and a non-zero
// signature at 0xCC04, then polls the timestamp at 0xCC24 for a change and
// reads the block. note_write() is wndproc-safe (no XPLM calls); process()
// must run from the pre-flight-model flight loop (XPLMGetWeatherAtLocation
// requirement).
#pragma once

#include <XPLMDataAccess.h>
#include <XPLMDefs.h>
#include <XPLMNavigation.h>
#include <XPLMProcessing.h>
#include <XPLMUtilities.h>
#include <XPLMWeather.h>
#include <XPlaneUtilities/XPlaneLog.h>
#include <algorithm>
#include <atomic>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <cstddef>
#include <vector>

class WeatherReadService {
public:
    static constexpr uint32_t OFF_BLOCK   = 0xCC00;
    static constexpr uint32_t OFF_SIG     = 0xCC04;
    static constexpr uint32_t OFF_ICAO    = 0xCC08;
    static constexpr uint32_t OFF_LAT     = 0xCC10;
    static constexpr uint32_t OFF_LON     = 0xCC18;
    static constexpr uint32_t OFF_ELEV    = 0xCC20;
    static constexpr uint32_t OFF_STAMP   = 0xCC24;
    static constexpr uint32_t OFF_QNH     = 0xCC28;
    static constexpr uint32_t OFF_VIS     = 0xCC2C;
    static constexpr uint32_t OFF_TEMP_N  = 0xCC34;
    static constexpr uint32_t OFF_TEMP    = 0xCC38;  // 8 bytes each
    static constexpr uint32_t OFF_WIND_N  = 0xCCF8;
    static constexpr uint32_t OFF_WIND    = 0xCCFC;  // 16 bytes each
    static constexpr uint32_t OFF_CLOUD_N = 0xCE7C;
    static constexpr uint32_t OFF_CLOUD   = 0xCE80;  // 16 bytes each
    static constexpr uint32_t OFF_END     = 0xD000;
    static constexpr uint32_t OFF_METAR   = 0xB800;
    static constexpr uint32_t METAR_SIZE  = 2048;    // Plan-G reads 2048, FSUIPC documents 2000
    static constexpr int MAX_LAYERS = 24;

    // Wndproc-safe: latch a request when the signature dword is written non-zero.
    void note_write(uint32_t offset, uint32_t size, const uint8_t* buf) {
        if (offset <= OFF_SIG && OFF_SIG + 4 <= offset + size) {
            // TODO: validate against the real FSUIPC signature value once confirmed from a live Plan-G trace.
            uint32_t sig; std::memcpy(&sig, buf + OFF_SIG, 4);
            if (sig != 0) pending_.store(true);
        }
    }

    // XPLM context only. Fills the shadow buffer; the timestamp is written last.
    void process(uint8_t* buf) {
        if (!pending_.exchange(false)) return;

        char icao[5] = {};
        std::memcpy(icao, buf + OFF_ICAO, 4);
        for (int i = 3; i >= 0 && (icao[i] == ' ' || icao[i] == 0); --i) icao[i] = 0;

        double lat = 0, lon = 0, elev = 0;
        bool valid_id = std::strlen(icao) >= 3;
        for (const char* p = icao; *p; ++p) valid_id = valid_id && std::isalnum(static_cast<unsigned char>(*p));
        double req_lat, req_lon;
        std::memcpy(&req_lat, buf + OFF_LAT, 8);
        std::memcpy(&req_lon, buf + OFF_LON, 8);
        // Plan-G sends a placeholder like "<??>" with no lat/lon; serve the aircraft position then.
        // The shadow buffer keeps lat/lon from our previous reply, so a re-request still has non-zero lat/lon; "<" alone marks the placeholder.
        const bool placeholder = !valid_id && icao[0] == '<';
        const bool global = std::strcmp(icao, "GLOB") == 0 || placeholder || (!valid_id && req_lat == 0.0 && req_lon == 0.0);
        const bool by_icao = !global && valid_id;
        const bool nearest = global && std::strcmp(icao, "GLOB") != 0;

        if (global) {
            // TODO: GLOB should be the sim's global weather, not aircraft-local; X-Plane has no equivalent.
            static XPLMDataRef rlat = XPLMFindDataRef("sim/flightmodel/position/latitude");
            static XPLMDataRef rlon = XPLMFindDataRef("sim/flightmodel/position/longitude");
            static XPLMDataRef rel  = XPLMFindDataRef("sim/flightmodel/position/elevation");
            lat = rlat ? XPLMGetDatad(rlat) : 0.0;
            lon = rlon ? XPLMGetDatad(rlon) : 0.0;
            elev = rel ? XPLMGetDatad(rel) : 0.0;
            std::memcpy(buf + OFF_LAT, &lat, 8);
            std::memcpy(buf + OFF_LON, &lon, 8);
            if (nearest) {
                // Plan-G's "<??>" means "nearest station": reply with the nearest airport that has a METAR.
                nearest_airport_with_metar(lat, lon, icao);
                if (icao[0]) {
                    std::memset(buf + OFF_ICAO, 0, 5);
                    std::memcpy(buf + OFF_ICAO, icao, std::strlen(icao));
                }
            }
        } else if (by_icao) {
            XPLMNavRef ref = XPLMFindNavAid(nullptr, icao, nullptr, nullptr, nullptr, xplm_Nav_Airport);
            char id[32] = {};
            float flat = 0, flon = 0, fh = 0;
            if (ref != XPLM_NAV_NOT_FOUND)
                XPLMGetNavAidInfo(ref, nullptr, &flat, &flon, &fh, nullptr, nullptr, id, nullptr, nullptr);
            // XPLMFindNavAid matches ID fragments; require an exact match.
            if (ref == XPLM_NAV_NOT_FOUND || std::strcmp(id, icao) != 0) {
                // No reply: leaving the timestamp unchanged lets the client time out rather than trust the wrong station.
                XPLANE_LOG_DEBUG("Weather read: unknown ICAO '{}'", icao);
                std::memset(buf + OFF_SIG, 0, 4);
                return;
            }
            lat = flat; lon = flon; elev = fh;
            std::memcpy(buf + OFF_LAT, &lat, 8);
            std::memcpy(buf + OFF_LON, &lon, 8);
        } else {
            std::memcpy(&lat, buf + OFF_LAT, 8);
            std::memcpy(&lon, buf + OFF_LON, 8);
            // TODO: sample terrain elevation (XPLMProbeTerrainXYZ) instead of assuming sea level.
            elev = 0;
        }

        std::memset(buf + OFF_SIG, 0, 4);  // signature accepted
        std::memset(buf + OFF_ELEV, 0, OFF_END - OFF_ELEV);
        std::memset(buf + OFF_METAR, 0, METAR_SIZE);

        XPLMWeatherInfo_t wx{};
        // v1 layout: v2 fields (temp/dewpoint layers) are absent on older X-Plane 12 builds.
        wx.structSize = static_cast<int>(offsetof(XPLMWeatherInfo_t, temp_layers));
        const double sample_alt = elev;
        XPLMGetWeatherAtLocation(lat, lon, sample_alt, &wx);

        put32(buf, OFF_ELEV, static_cast<int32_t>(elev));
        fill_surface(buf, wx);
        fill_temps(buf, lat, lon, sample_alt);
        fill_winds(buf, wx);
        fill_clouds(buf, wx);

        if (by_icao || (nearest && icao[0])) {
            XPLMFixedString150_t metar{};
            XPLMGetMETARForAirport(icao, &metar);
            // TODO: synthesise a METAR from XPLMWeatherInfo_t when empty (not in real-weather mode) or for GLOB/lat-lon requests.
            // TODO: pull METAR from an external provider (e.g. aviationweather.gov) for stations X-Plane has not downloaded.
            std::strncpy(reinterpret_cast<char*>(buf + OFF_METAR), metar.buffer, sizeof(metar.buffer) - 1);
        }

        uint32_t stamp = static_cast<uint32_t>(XPLMGetElapsedTime() * 1000.0f);
        uint32_t prev; std::memcpy(&prev, buf + OFF_STAMP, 4);
        if (stamp == prev) ++stamp;  // client detects completion by change
        put32(buf, OFF_STAMP, static_cast<int32_t>(stamp));

        int32_t nt, nw, nc; uint16_t qnh, w0spd, w0dir;
        std::memcpy(&nt, buf + OFF_TEMP_N, 4);
        std::memcpy(&nw, buf + OFF_WIND_N, 4);
        std::memcpy(&nc, buf + OFF_CLOUD_N, 4);
        std::memcpy(&qnh, buf + OFF_QNH, 2);
        std::memcpy(&w0spd, buf + OFF_WIND + 2, 2);
        std::memcpy(&w0dir, buf + OFF_WIND + 6, 2);
        XPLANE_LOG_DEBUG("Weather read: id='{}' lat={:.4f} lon={:.4f} elev={:.0f} stamp={} qnh={:.1f}hPa temps={} winds={} (w0 {}kt {:.0f}deg) clouds={} metar='{}'",
            icao, lat, lon, elev, stamp, qnh / 16.0, nt, nw, w0spd, w0dir * 360.0 / 65536.0, nc,
            reinterpret_cast<const char*>(buf + OFF_METAR));
    }

private:
    std::atomic<bool> pending_{false};

    // Closest airport (within 150 km, by distance order) for which X-Plane has a METAR; icao is cleared if none.
    // Backup: literal nearest airport (may be a private strip with no METAR), kept for reference.
    //   float qlat = static_cast<float>(lat), qlon = static_cast<float>(lon);
    //   XPLMNavRef ref = XPLMFindNavAid(nullptr, nullptr, &qlat, &qlon, nullptr, xplm_Nav_Airport);
    //   char id[32] = {};
    //   if (ref != XPLM_NAV_NOT_FOUND) {
    //       XPLMGetNavAidInfo(ref, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, id, nullptr, nullptr);
    //       std::memset(icao, 0, sizeof(icao));
    //       std::strncpy(icao, id, 4);
    //   }
    static void nearest_airport_with_metar(double lat, double lon, char (&icao)[5]) {
        struct Cand { double d2; char id[8]; };
        std::vector<Cand> cands;
        const double coslat = std::cos(lat * 3.14159265358979 / 180.0);
        const XPLMNavRef last = XPLMFindLastNavAidOfType(xplm_Nav_Airport);
        for (XPLMNavRef r = XPLMFindFirstNavAidOfType(xplm_Nav_Airport); r != XPLM_NAV_NOT_FOUND;
             r = (r == last) ? XPLM_NAV_NOT_FOUND : XPLMGetNextNavAid(r)) {
            XPLMNavType type; float flat, flon; char id[32] = {};
            XPLMGetNavAidInfo(r, &type, &flat, &flon, nullptr, nullptr, nullptr, id, nullptr, nullptr);
            if (type != xplm_Nav_Airport) continue;
            const double dy = (flat - lat) * 111.2, dx = (flon - lon) * 111.2 * coslat;
            const double d2 = dx * dx + dy * dy;
            if (d2 > 150.0 * 150.0) continue;
            Cand c{d2, {}};
            std::strncpy(c.id, id, 7);
            cands.push_back(c);
        }
        std::sort(cands.begin(), cands.end(), [](const Cand& a, const Cand& b) { return a.d2 < b.d2; });
        for (const auto& c : cands) {
            XPLMFixedString150_t m{};
            XPLMGetMETARForAirport(c.id, &m);
            if (m.buffer[0]) { std::memset(icao, 0, sizeof(icao)); std::strncpy(icao, c.id, 4); return; }
        }
        std::memset(icao, 0, sizeof(icao));
    }

    static void put32(uint8_t* b, uint32_t off, int32_t v) { std::memcpy(b + off, &v, 4); }
    static void put16(uint8_t* b, uint32_t off, uint16_t v) { std::memcpy(b + off, &v, 2); }
    static uint16_t clamp_u16(double v) { return static_cast<uint16_t>(std::clamp(v + 0.5, 0.0, 65535.0)); }
    static int16_t clamp_s16(double v) { return static_cast<int16_t>(std::clamp(std::floor(v + 0.5), -32768.0, 32767.0)); }

    static void fill_surface(uint8_t* b, const XPLMWeatherInfo_t& wx) {
        put16(b, OFF_QNH, clamp_u16(wx.pressure_sl / 100.0 * 16.0));  // hPa x 16
        put16(b, OFF_VIS + 0, 65535);  // upper alt: X-Plane visibility is surface-only, apply to all altitudes
        b[OFF_VIS + 2] = 0;            // lower alt
        put16(b, OFF_VIS + 4, clamp_u16(wx.visibility / 1609.344 * 100.0));  // sm x 100
    }

    static void fill_temps(uint8_t* b, double lat, double lon, double base_alt) {
        // TODO: use XPLMWeatherInfo_t::temp_layers/dewp_layers where available (XPLM420) instead of re-sampling.
        static const double alts[] = {0, 1500, 3000, 6000, 9000, 12000};
        int n = 0;
        for (double a : alts) {
            XPLMWeatherInfo_t t{};
            t.structSize = static_cast<int>(offsetof(XPLMWeatherInfo_t, temp_layers));
            XPLMGetWeatherAtLocation(lat, lon, a + (a == 0 ? base_alt : 0), &t);
            uint32_t o = OFF_TEMP + n * 8;
            put16(b, o + 0, clamp_u16(a));
            put16(b, o + 2, static_cast<uint16_t>(clamp_s16(t.temperature_alt)));
            put16(b, o + 4, 0);  // day/night variation: not modelled by X-Plane
            put16(b, o + 6, static_cast<uint16_t>(clamp_s16(t.dewpoint_alt)));
            ++n;
        }
        put32(b, OFF_TEMP_N, n);
    }

    static void fill_winds(uint8_t* b, const XPLMWeatherInfo_t& wx) {
        constexpr double MS_TO_KT = 1.943844;
        int n = 0;
        for (const auto& w : wx.wind_layers) {
            if (n >= MAX_LAYERS || w.speed < 0.0f) continue;  // negative = undefined layer
            uint32_t o = OFF_WIND + n * 16;
            double kt = w.speed * MS_TO_KT;
            double gust = (std::max)(0.0, (w.gust_speed - w.speed) * MS_TO_KT);
            double dir = std::fmod(std::fmod(w.direction, 360.0) + 360.0, 360.0);
            put16(b, o + 0, clamp_u16(w.alt_msl));
            put16(b, o + 2, clamp_u16(kt));
            put16(b, o + 4, clamp_u16(gust));
            put16(b, o + 6, clamp_u16(dir * 65536.0 / 360.0) );
            b[o + 8] = static_cast<uint8_t>(std::clamp(std::lround(w.turbulence * 4.0), 0L, 4L));
            b[o + 9] = 0;  // TODO: map shear arc (degrees) to FSUIPC shear degree 0-3.
            put16(b, o + 10, clamp_u16(w.shear * 65536.0 / 360.0));  // direction variance
            put16(b, o + 12, static_cast<uint16_t>((kt - std::floor(kt)) * 65536.0));
            ++n;
        }
        put32(b, OFF_WIND_N, n);
    }

    static void fill_clouds(uint8_t* b, const XPLMWeatherInfo_t& wx) {
        int n = 0;
        for (const auto& c : wx.cloud_layers) {
            if (n >= MAX_LAYERS || c.coverage <= 0.0f) continue;
            uint32_t o = OFF_CLOUD + n * 16;
            put16(b, o + 0, clamp_u16(c.alt_top));
            put16(b, o + 2, clamp_u16(c.alt_base));
            put16(b, o + 4, 0);  // altitude deviation: not modelled by X-Plane
            b[o + 6] = static_cast<uint8_t>(std::clamp(std::lround(c.coverage * 8.0), 0L, 8L));  // oktas
            // X-Plane 0 Cirrus,1 Stratus,2 Cumulus,3 Cumulonimbus -> FS 1,8,9,10.
            // TODO: verify FS cumulonimbus code (10) against a real FSUIPC reading.
            static const uint8_t type_map[] = {1, 8, 9, 10};
            b[o + 7] = type_map[std::clamp(std::lround(c.cloud_type), 0L, 3L)];
            // TODO: turbulence/icing/precipitation per cloud layer from sim/weather/region/* datarefs.
            ++n;
        }
        put32(b, OFF_CLOUD_N, n);
    }
};
