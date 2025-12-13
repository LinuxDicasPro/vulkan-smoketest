/*
 * Copyright (C) 2016 Google, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SHELL_WAYLAND_H
#define SHELL_WAYLAND_H

#include "Shell.h"
#include <wayland-client.h>
#include "xdg-shell-client-protocol.h"
#include "zxdg-decoration-client-protocol.h"

class ShellWayland : public Shell {
public:
    explicit ShellWayland(Game &game);

    ~ShellWayland() override;

    void run() override;

    void quit() override { quit_ = true; }

private:
    void init_connection();

    PFN_vkGetInstanceProcAddr load_vk() override;

    bool can_present(VkPhysicalDevice phy, uint32_t queue_family) override;

    void create_window();

    VkSurfaceKHR create_surface(VkInstance instance) override;

    void loop_wait();

    void loop_poll();

    void *lib_handle_{};
    bool quit_{};

    wl_display *display_{};
    wl_registry *registry_{};
    wl_compositor *compositor_{};

    // Objects XDG Shell
    struct xdg_wm_base *wm_base_{};
    wl_surface *surface_{};
    struct xdg_surface *xdg_surface_{};
    struct xdg_toplevel *xdg_toplevel_{};

    // Objects XDG Decoration
    struct zxdg_decoration_manager_v1 *decoration_manager_{};
    struct zxdg_toplevel_decoration_v1 *toplevel_decoration_{};

    wl_seat *seat_{};
    wl_pointer *pointer_{};
    wl_keyboard *keyboard_{};

    // XDG Shell Listeners
    static void handle_xdg_wm_base_ping(void *data, struct xdg_wm_base *xdg_wm_base, uint32_t serial);

    static const struct xdg_wm_base_listener wm_base_listener;

    static void handle_xdg_surface_configure(void *data, struct xdg_surface *xdg_surface, uint32_t serial);

    static const struct xdg_surface_listener xdg_surface_listener;

    static void handle_xdg_toplevel_configure(void *data, struct xdg_toplevel *xdg_toplevel,
                                              int32_t width, int32_t height, struct wl_array *states);

    static void handle_xdg_toplevel_close(void *data, struct xdg_toplevel *xdg_toplevel);

    static const struct xdg_toplevel_listener xdg_toplevel_listener;

    // Standard input listeners
    static void
    pointer_handle_enter(void *data, struct wl_pointer *pointer, uint32_t serial, struct wl_surface *surface,
                         wl_fixed_t sx, wl_fixed_t sy);

    static void
    pointer_handle_leave(void *data, struct wl_pointer *pointer, uint32_t serial, struct wl_surface *surface);

    static void
    pointer_handle_motion(void *data, struct wl_pointer *pointer, uint32_t time, wl_fixed_t sx, wl_fixed_t sy);

    static void
    pointer_handle_button(void *data, struct wl_pointer *wl_pointer, uint32_t serial, uint32_t time, uint32_t button,
                          uint32_t state);

    static void
    pointer_handle_axis(void *data, struct wl_pointer *wl_pointer, uint32_t time, uint32_t axis, wl_fixed_t value);

    static const wl_pointer_listener pointer_listener;

    static void
    keyboard_handle_keymap(void *data, struct wl_keyboard *keyboard, uint32_t format, int fd, uint32_t size);

    static void
    keyboard_handle_enter(void *data, struct wl_keyboard *keyboard, uint32_t serial, struct wl_surface *surface,
                          struct wl_array *keys);

    static void
    keyboard_handle_leave(void *data, struct wl_keyboard *keyboard, uint32_t serial, struct wl_surface *surface);

    static void
    keyboard_handle_key(void *data, struct wl_keyboard *keyboard, uint32_t serial, uint32_t time, uint32_t key,
                        uint32_t state);

    static void keyboard_handle_modifiers(void *data, wl_keyboard *keyboard, uint32_t serial, uint32_t mods_depressed,
                                          uint32_t mods_latched, uint32_t mods_locked, uint32_t group);

    static const wl_keyboard_listener keyboard_listener;

    static void seat_handle_capabilities(void *data, wl_seat *seat, uint32_t caps);

    static const wl_seat_listener seat_listener;

    static void
    registry_handle_global(void *data, wl_registry *registry, uint32_t id, const char *interface, uint32_t version);

    static const wl_registry_listener registry_listener;
};

#endif  // SHELL_WAYLAND_H
