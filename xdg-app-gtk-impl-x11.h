#ifndef XDG_APP_GTK_X11_IMPL_H
#define XDG_APP_GTK_X11_IMPL_H

#include "xdg-app-gtk-impl.h"

#include <glib-object.h>

#define XDG_APP_GTK_TYPE_IMPL_X11 (xdg_app_gtk_impl_x11_get_type ())
G_DECLARE_FINAL_TYPE (XdgAppGtkImplX11, xdg_app_gtk_impl_x11,
                      XDG_APP_GTK, IMPL_X11,
                      XdgAppGtkImpl);

#endif /* XDG_APP_GTK_X11_IMPL_H */
