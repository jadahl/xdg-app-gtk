#ifndef XDG_APP_GTK_IMPORTED_X11_H
#define XDG_APP_GTK_IMPORTED_X11_H

#include <glib-object.h>

#include "xdg-app-gtk-imported.h"

#define XDG_APP_GTK_TYPE_IMPORTED_X11 (xdg_app_gtk_imported_x11_get_type ())
G_DECLARE_FINAL_TYPE (XdgAppGtkImportedX11, xdg_app_gtk_imported_x11,
                      XDG_APP_GTK, IMPORTED_X11,
                      XdgAppGtkImported);

XdgAppGtkImported * xdg_app_gtk_imported_x11_new (XdgAppGtkImpl *impl,
                                                  int xid);

#endif /* XDG_APP_GTK_IMPORTED_X11_H */
