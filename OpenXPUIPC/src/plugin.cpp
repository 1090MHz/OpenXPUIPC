// OpenXPUIPC v1.0.0 — FSUIPC-compatible IPC bridge for X-Plane 12
// SPDX-License-Identifier: LGPL-3.0-or-later
//
// Provides two interfaces to external applications:
//   1. FSUIPC IPC (shared memory via UIPCMAIN window) — for FSUIPC-compatible clients
//   2. UDP server on port 5193 — for XConnect-style clients
//
// Both interfaces share the same Bridge (offset table + DataRef cache).

// Must come before any Windows SDK / XPLM header to avoid winsock.h vs winsock2.h conflict
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#endif

#include "bridge.h"
#include "udp_server.h"
#ifdef _WIN32
#include "ipc_server.h"
#endif

#include <XPLMPlugin.h>
#include <XPLMUtilities.h>
#include <XPLMMenus.h>
#include <XPLMProcessing.h>
#include <XPlaneUtilities/XPlaneLog.h>

#include <memory>

static std::unique_ptr<Bridge> bridge;
static std::unique_ptr<UdpServer> udp_server;
#ifdef _WIN32
static std::unique_ptr<IpcServer> ipc_server;
#endif

static XPLMMenuID menu_id = nullptr;
static int menu_container = -1;
static XPLMFlightLoopID bridge_loop = nullptr;

// ---------- Bridge update flight loop ----------
static float bridge_update_cb(float, float, int, void *)
{
    if (bridge)
        bridge->update();
    return 1.0f / 18.0f; // ~18 Hz — matches FSUIPC polling rate; no benefit updating faster
}

// ---------- Menu ----------
// In Release builds (NDEBUG defined) the menu shows status only.
// In Debug builds the log-level cycling item is also available.
#ifndef NDEBUG
enum MenuItems
{
    MENU_STATUS = 0,
    MENU_SEP,
    MENU_LOG_LEVEL
};
#else
enum MenuItems
{
    MENU_STATUS = 0
};
#endif

#ifndef NDEBUG
static void cycle_log_level()
{
    auto current = spdlog::get_level();
    spdlog::level::level_enum next;
    const char *label;
    switch (current)
    {
    case spdlog::level::info:
        next = spdlog::level::debug;
        label = "Log Level: DEBUG";
        break;
    case spdlog::level::debug:
        next = spdlog::level::trace;
        label = "Log Level: TRACE";
        break;
    default:
        next = spdlog::level::info;
        label = "Log Level: INFO";
        break;
    }
    spdlog::set_level(next);
    // Flush on every message during debug/trace so crash diagnostics survive
    spdlog::flush_on(next <= spdlog::level::debug ? spdlog::level::debug : spdlog::level::info);
    XPLMSetMenuItemName(menu_id, MENU_LOG_LEVEL, label, 0);
    XPLANE_LOG_INFO("Log level changed to {}", spdlog::level::to_string_view(next));
}
#endif

static void menu_handler(void *, void *item_ref)
{
    int id = static_cast<int>(reinterpret_cast<intptr_t>(item_ref));
    switch (id)
    {
#ifndef NDEBUG
    case MENU_LOG_LEVEL:
        cycle_log_level();
        break;
#endif
    default:
        break;
    }
}

static void create_menu()
{
    menu_container = XPLMAppendMenuItem(
        XPLMFindPluginsMenu(), "OpenXPUIPC", nullptr, 0);
    menu_id = XPLMCreateMenu(
        "OpenXPUIPC", XPLMFindPluginsMenu(), menu_container,
        menu_handler, nullptr);

    XPLMAppendMenuItem(menu_id, "Status: Running", (void *)MENU_STATUS, 0);
    XPLMEnableMenuItem(menu_id, MENU_STATUS, 0);

#ifndef NDEBUG
    // Debug builds: separator + log-level cycling item
    XPLMAppendMenuSeparator(menu_id);
    XPLMAppendMenuItem(menu_id, "Log Level: INFO", (void *)MENU_LOG_LEVEL, 0);
#endif
}

static void destroy_menu()
{
    if (menu_id)
    {
        XPLMDestroyMenu(menu_id);
        menu_id = nullptr;
    }
    if (menu_container >= 0)
    {
        XPLMRemoveMenuItem(XPLMFindPluginsMenu(), menu_container);
        menu_container = -1;
    }
}

static void update_status(bool ipc_ok, bool udp_ok)
{
    if (!menu_id)
        return;
    char text[128];
    snprintf(text, sizeof(text), "Status: IPC %s, UDP %s",
             ipc_ok ? "OK" : "FAIL",
             udp_ok ? "OK (5193)" : "FAIL");
    XPLMSetMenuItemName(menu_id, MENU_STATUS, text, 0);
}

// ---------- Plugin lifecycle ----------
PLUGIN_API int XPluginStart(char *name, char *sig, char *desc)
{
    std::strcpy(name, "OpenXPUIPC");
    std::strcpy(sig, "GitHub.1090MHz.OpenXPUIPC");
    std::strcpy(desc, "FSUIPC-compatible IPC bridge for X-Plane 12 (v1.0.0)");

    XPlaneLog::init("OpenXPUIPC");
#ifdef NDEBUG
    spdlog::set_level(spdlog::level::info);
    spdlog::flush_on(spdlog::level::warn);
#else
    spdlog::set_level(spdlog::level::debug);
    spdlog::flush_on(spdlog::level::debug);
#endif
    XPLANE_LOG_INFO("OpenXPUIPC v1.0.0 starting");

    bridge = std::make_unique<Bridge>();
    udp_server = std::make_unique<UdpServer>();
#ifdef _WIN32
    ipc_server = std::make_unique<IpcServer>();
#endif

    create_menu();
    return 1;
}

PLUGIN_API int XPluginEnable()
{
    bool ipc_ok = false;
    bool udp_ok = false;

    // Bridge update loop — refreshes DataRefs into shadow buffer.
    // Must run BEFORE IPC server so the buffer is populated on first request.
    XPLMCreateFlightLoop_t fl{};
    fl.structSize = sizeof(fl);
    fl.phase = xplm_FlightLoop_Phase_BeforeFlightModel;
    fl.callbackFunc = bridge_update_cb;
    fl.refcon = nullptr;
    bridge_loop = XPLMCreateFlightLoop(&fl);
    XPLMScheduleFlightLoop(bridge_loop, -1.0f, 1);

    // Seed the buffer NOW — the flight loop is only scheduled, not yet fired.
    // Without this, the first client read returns all zeros, and the second read
    // returns real lat/lon/alt/speed values, which can trigger client-side
    // outlier/discontinuity detection and some clients may disconnects due to
    // these unexpected sudden changes.
    bridge->update();

#ifdef _WIN32
    ipc_ok = ipc_server->start(bridge.get());
#endif
    udp_ok = udp_server->start(bridge.get());

    update_status(ipc_ok, udp_ok);
    XPLANE_LOG_INFO("IPC: {}, UDP: {}", ipc_ok ? "OK" : "FAIL", udp_ok ? "OK" : "FAIL");

    // Succeed if at least one interface started
    return (ipc_ok || udp_ok) ? 1 : 0;
}

PLUGIN_API void XPluginDisable()
{
#ifdef _WIN32
    ipc_server->stop();
#endif
    udp_server->stop();
    if (bridge_loop)
    {
        XPLMDestroyFlightLoop(bridge_loop);
        bridge_loop = nullptr;
    }
    update_status(false, false);
    XPLANE_LOG_INFO("OpenXPUIPC disabled");
}

PLUGIN_API void XPluginStop()
{
    destroy_menu();
#ifdef _WIN32
    ipc_server.reset();
#endif
    udp_server.reset();
    bridge.reset();
    XPLANE_LOG_INFO("OpenXPUIPC stopped");
    XPlaneLog::shutdown();
}

PLUGIN_API void XPluginReceiveMessage(XPLMPluginID, int, void *)
{
}
