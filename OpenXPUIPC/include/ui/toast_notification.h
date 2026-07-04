// OpenXPUIPC - Toast Notification Helper
// SPDX-License-Identifier: GPL-3.0-or-later
//
// Provides simple toast-style notifications that auto-dismiss after a timeout.
// Uses the X-Plane SDK's native "Growl Notifications" window layer for
// non-intrusive, always-on-top messages.

#pragma once

#include <string>
#include <chrono>

// Forward declarations
typedef void* XPLMWindowID;

/// @brief Toast notification helper for displaying temporary messages in X-Plane
///
/// Usage:
///   ToastNotification::show("IPC Server started", 3.0f);
///   ToastNotification::show("UDP connection failed!", 5.0f, ToastNotification::Type::Error);
class ToastNotification
{
public:
    /// Notification type (affects appearance)
    enum class Type
    {
        Info,    // Blue/neutral
        Success, // Green
        Warning, // Yellow/orange
        Error    // Red
    };

    /// @brief Display a toast notification
    /// @param message Text to display
    /// @param duration_seconds How long to show the notification (default: 3 seconds)
    /// @param type Notification type affecting color (default: Info)
    static void show(const std::string& message, 
                     float duration_seconds = 3.0f,
                     Type type = Type::Info);

    /// @brief Check if a notification is currently visible
    static bool is_visible();

    /// @brief Manually dismiss the current notification (if any)
    static void dismiss();

    /// @brief Initialize the toast notification system
    /// Call once during plugin startup (XPluginEnable)
    static void initialize();

    /// @brief Shutdown the toast notification system
    /// Call during plugin shutdown (XPluginDisable)
    static void shutdown();

private:
    ToastNotification() = delete;
    
    // Internal state
    struct State
    {
        XPLMWindowID window_id = nullptr;
        std::string current_message;
        Type current_type = Type::Info;
        std::chrono::steady_clock::time_point show_time;
        float duration = 0.0f;
        bool is_active = false;
        int wrap_width = 0;  // Text wrapping width for multi-line messages
    };
    
    static State s_state;
    
    // Callbacks for X-Plane window system
    static void draw_callback(XPLMWindowID window_id, void* refcon);
    static int mouse_click_callback(XPLMWindowID window_id, int x, int y, int mouse_status, void* refcon);
    static int mouse_wheel_callback(XPLMWindowID window_id, int x, int y, int wheel, int clicks, void* refcon);
    static int cursor_callback(XPLMWindowID window_id, int x, int y, void* refcon);
    static void key_callback(XPLMWindowID window_id, char key, int flags, char virtual_key, void* refcon, int losing_focus);
    
    // Helper to get color based on type
    static void get_color(Type type, float& r, float& g, float& b);
    
    // Create the window on first use
    static void create_window_if_needed();
    
    // Update visibility based on timeout
    static void update_visibility();
    
    // Flight loop callback for timeout management
    static float flight_loop_callback(float elapsed_since_last_call, float elapsed_time_since_last_loop, int counter, void* refcon);
};
