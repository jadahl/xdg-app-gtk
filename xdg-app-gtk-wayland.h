#ifndef XDG_APP_GTK_WAYLAND_H
#define XDG_APP_GTK_WAYLAND_H

#include "xdg-app-gtk.h"

#include <glib-object.h>

#define XDG_APP_GTK_TYPE_IMPL_WAYLAND (xdg_app_gtk_impl_wayland_get_type ())
G_DECLARE_FINAL_TYPE (XdgAppGtkImplWayland, xdg_app_gtk_impl_wayland,
                      XDG_APP_GTK, IMPL_WAYLAND,
                      XdgAppGtkImpl);

#endif /* XDG_APP_GTK_WAYLAND_H */
