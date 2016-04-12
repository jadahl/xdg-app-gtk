#ifndef XDG_APP_GTK_IMPORTER_H
#define XDG_APP_GTK_IMPORTER_H

#include <glib-object.h>

#include "xdg-app-gtk-imported.h"

#define XDG_APP_GTK_TYPE_IMPORTER (xdg_app_gtk_importer_get_type ())
G_DECLARE_FINAL_TYPE (XdgAppGtkImporter, xdg_app_gtk_importer,
                      XDG_APP_GTK, IMPORTER,
                      GObject);

XdgAppGtkImported * xdg_app_gtk_importer_import (XdgAppGtkImporter *importer,
                                                 const char *handle);

#endif /* XDG_APP_GTK_IMPORTER_H */
