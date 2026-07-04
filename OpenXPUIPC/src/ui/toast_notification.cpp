// OpenXPUIPC - Toast Notification Helper
// SPDX-License-Identifier: GPL-3.0-or-later

// Windows headers must come first to avoid conflicts
#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX  // Prevent Windows.h from defining min/max macros that conflict with std::min/max
#endif
#include <windows.h>
#include <GL/gl.h>
#endif

#include "ui/toast_notification.h"
#include <XPLMDisplay.h>
#include <XPLMGraphics.h>
#include <XPLMProcessing.h>
#include <XPlaneUtilities/XPlaneLog.h>

#include <algorithm>
#include <cmath>
#include <cstring>

// Static state
ToastNotification::State ToastNotification::s_state;
static XPLMFlightLoopID s_flight_loop = nullptr;

void ToastNotification::initialize()
{
    XPLANE_LOG_DEBUG("ToastNotification system initialized");
}

void ToastNotification::shutdown()
{
    dismiss();
    
    if (s_flight_loop)
    {
        XPLMDestroyFlightLoop(s_flight_loop);
        s_flight_loop = nullptr;
    }
    
    if (s_state.window_id)
    {
        XPLMDestroyWindow(s_state.window_id);
        s_state.window_id = nullptr;
    }
    
    XPLANE_LOG_DEBUG("ToastNotification system shut down");
}

void ToastNotification::show(const std::string& message, float duration_seconds, Type type)
{
    create_window_if_needed();
    
    s_state.current_message = message;
    s_state.current_type = type;
    s_state.show_time = std::chrono::steady_clock::now();
    s_state.duration = duration_seconds;
    s_state.is_active = true;
    
    // Make window visible
    XPLMSetWindowIsVisible(s_state.window_id, 1);
    
    // Position in top-right corner (20px margin from edges)
    int screen_left, screen_top, screen_right, screen_bottom;
    XPLMGetScreenBoundsGlobal(&screen_left, &screen_top, &screen_right, &screen_bottom);
    
    // Calculate notification size based on message length
    int char_width, char_height;
    XPLMGetFontDimensions(xplmFont_Proportional, &char_width, &char_height, nullptr);
    
    const int padding = 20;
    const int min_width = 250;
    const int max_width = 450;
    
    float message_width = XPLMMeasureString(xplmFont_Proportional, message.c_str(), static_cast<int>(message.length()));
    int window_width = static_cast<int>(message_width) + (padding * 2);
    window_width = std::max(min_width, std::min(window_width, max_width));
    
    // Store wrap width for drawing (actual text area width)
    s_state.wrap_width = window_width - (padding * 2);
    
    // Estimate number of lines needed for word-wrapped text
    // This is approximate: message_width / wrap_width gives rough line count
    int estimated_lines = std::max(1, static_cast<int>(std::ceil(message_width / s_state.wrap_width)));
    
    // Add extra line for safety margin and account for word boundaries
    if (estimated_lines > 1)
        estimated_lines += 1;
    
    int window_height = (char_height * estimated_lines) + (padding * 2);
    
    int margin = 20;
    int window_left = screen_right - window_width - margin;
    int window_bottom = screen_top - window_height - margin;
    int window_right = screen_right - margin;
    int window_top = screen_top - margin;
    
    XPLMSetWindowGeometry(s_state.window_id, window_left, window_top, window_right, window_bottom);
    
    XPLANE_LOG_DEBUG("Toast notification shown: '{}' ({}s)", message, duration_seconds);
}

bool ToastNotification::is_visible()
{
    return s_state.is_active;
}

void ToastNotification::dismiss()
{
    if (s_state.window_id)
    {
        XPLMSetWindowIsVisible(s_state.window_id, 0);
    }
    s_state.is_active = false;
}

void ToastNotification::create_window_if_needed()
{
    if (s_state.window_id)
        return; // Already created
    
    // Create flight loop for timeout management
    if (!s_flight_loop)
    {
        XPLMCreateFlightLoop_t fl{};
        fl.structSize = sizeof(fl);
        fl.phase = xplm_FlightLoop_Phase_BeforeFlightModel;
        fl.callbackFunc = flight_loop_callback;
        fl.refcon = nullptr;
        s_flight_loop = XPLMCreateFlightLoop(&fl);
        XPLMScheduleFlightLoop(s_flight_loop, -1.0f, 1); // Run every frame
    }
    
    // Create window in the Growl Notifications layer (always on top)
    XPLMCreateWindow_t params{};
    params.structSize = sizeof(params);
    params.left = 0;
    params.top = 100;
    params.right = 300;
    params.bottom = 0;
    params.visible = 0; // Initially hidden
    params.drawWindowFunc = draw_callback;
    params.handleMouseClickFunc = mouse_click_callback;
    params.handleRightClickFunc = mouse_click_callback; // Same handler for right-click
    params.handleKeyFunc = key_callback;
    params.handleCursorFunc = cursor_callback;
    params.handleMouseWheelFunc = mouse_wheel_callback;
    params.refcon = nullptr;
    params.decorateAsFloatingWindow = xplm_WindowDecorationNone; // No frame - we draw our own
    params.layer = xplm_WindowLayerGrowlNotifications; // Always on top, non-intrusive
    
    s_state.window_id = XPLMCreateWindowEx(&params);
    
    XPLANE_LOG_DEBUG("Toast notification window created (layer: GrowlNotifications)");
}

void ToastNotification::draw_callback(XPLMWindowID window_id, void* refcon)
{
    (void)refcon;
    
    // Get window bounds
    int left, top, right, bottom;
    XPLMGetWindowGeometry(window_id, &left, &top, &right, &bottom);
    
    // Set up OpenGL for 2D drawing
    XPLMSetGraphicsState(
        0,  // No fog
        0,  // No texturing
        0,  // No lighting
        0,  // No alpha testing
        1,  // Enable alpha blending
        1,  // Enable depth testing
        0); // No depth writing
    
    // Get color based on notification type
    float r, g, b;
    get_color(s_state.current_type, r, g, b);
    
    // Draw dark opaque background first for text readability
    // Use X-Plane's built-in translucent dark box (same as text file viewer)
    XPLMDrawTranslucentDarkBox(left, top, right, bottom);
    
    // Draw colored overlay to indicate notification type (subtle tint)
    XPLMSetGraphicsState(
        0,  // No fog
        0,  // No texturing
        0,  // No lighting
        0,  // No alpha testing
        1,  // Enable alpha blending
        1,  // Enable depth testing
        0); // No depth writing
    
    // Semi-transparent colored overlay on top of dark background
    glColor4f(r, g, b, 0.15f); // Very subtle color tint
    glBegin(GL_QUADS);
    glVertex2i(left, top);
    glVertex2i(left, bottom);
    glVertex2i(right, bottom);
    glVertex2i(right, top);
    glEnd();
    
    // Draw colored border (more prominent)
    glColor4f(r, g, b, 0.9f); // Bright, mostly opaque
    glLineWidth(3.0f);  // Thicker border for better visibility
    glBegin(GL_LINE_LOOP);
    glVertex2i(left, top);
    glVertex2i(left, bottom);
    glVertex2i(right, bottom);
    glVertex2i(right, top);
    glEnd();
    
    // Draw text
    float text_color[] = {1.0f, 1.0f, 1.0f}; // White text
    
    int char_width, char_height;
    XPLMGetFontDimensions(xplmFont_Proportional, &char_width, &char_height, nullptr);
    
    int padding = 20;
    int text_x = left + padding;
    // Position text near bottom with small margin, XPLMDrawString draws upward from this point
    int text_y = bottom + padding;
    
    // Enable word wrapping to prevent text from overflowing the window
    int wrap_width = s_state.wrap_width;
    XPLMDrawString(text_color, text_x, text_y, 
                   const_cast<char*>(s_state.current_message.c_str()),
                   &wrap_width, xplmFont_Proportional);
}

int ToastNotification::mouse_click_callback(XPLMWindowID window_id, int x, int y, int mouse_status, void* refcon)
{
    (void)window_id;
    (void)x;
    (void)y;
    (void)refcon;
    
    // Click to dismiss
    if (mouse_status == xplm_MouseDown)
    {
        dismiss();
    }
    
    return 1; // Consume the click
}

int ToastNotification::mouse_wheel_callback(XPLMWindowID window_id, int x, int y, int wheel, int clicks, void* refcon)
{
    (void)window_id;
    (void)x;
    (void)y;
    (void)wheel;
    (void)clicks;
    (void)refcon;
    
    return 1; // Consume the event
}

int ToastNotification::cursor_callback(XPLMWindowID window_id, int x, int y, void* refcon)
{
    (void)window_id;
    (void)x;
    (void)y;
    (void)refcon;
    
    return xplm_CursorDefault;
}

void ToastNotification::key_callback(XPLMWindowID window_id, char key, int flags, char virtual_key, void* refcon, int losing_focus)
{
    (void)window_id;
    (void)key;
    (void)flags;
    (void)virtual_key;
    (void)refcon;
    (void)losing_focus;
    
    // No keyboard handling needed for toast notifications
}

void ToastNotification::get_color(Type type, float& r, float& g, float& b)
{
    switch (type)
    {
    case Type::Info:
        r = 0.3f; g = 0.6f; b = 1.0f; // Blue
        break;
    case Type::Success:
        r = 0.2f; g = 0.8f; b = 0.3f; // Green
        break;
    case Type::Warning:
        r = 1.0f; g = 0.7f; b = 0.2f; // Orange
        break;
    case Type::Error:
        r = 1.0f; g = 0.2f; b = 0.2f; // Red
        break;
    }
}

float ToastNotification::flight_loop_callback(float elapsed_since_last_call, float elapsed_time_since_last_loop, int counter, void* refcon)
{
    (void)elapsed_since_last_call;
    (void)elapsed_time_since_last_loop;
    (void)counter;
    (void)refcon;
    
    // Check if notification has timed out
    if (s_state.is_active)
    {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - s_state.show_time).count() / 1000.0f;
        
        if (elapsed >= s_state.duration)
        {
            dismiss();
        }
    }
    
    return -1.0f; // Run every frame
}
