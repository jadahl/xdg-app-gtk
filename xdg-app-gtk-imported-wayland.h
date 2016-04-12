#ifndef XDG_APP_GTK_IMPORTED_WAYLAND_H
#define XDG_APP_GTK_IMPORTED_WAYLAND_H

#include <glib-object.h>

#include "xdg-app-gtk-imported.h"

#include "xdg-app-gtk-impl.h"

#include "xdg-foreign-unstable-v1-client-protocol.h"

#define XDG_APP_GTK_TYPE_IMPORTED_WAYLAND (xdg_app_gtk_imported_wayland_get_type ())
G_DECLARE_FINAL_TYPE (XdgAppGtkImportedWayland, xdg_app_gtk_imported_wayland,
                      XDG_APP_GTK, IMPORTED_WAYLAND,
                      XdgAppGtkImported);


XdgAppGtkImported * xdg_app_gtk_imported_wayland_new (XdgAppGtkImpl *impl,
                                                      struct zxdg_imported_v1 *imported);

#endif /* XDG_APP_GTK_IMPORTED_WAYLAND_H */
