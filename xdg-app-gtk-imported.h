#ifndef XDG_APP_GTK_IMPORTED_H
#define XDG_APP_GTK_IMPORTED_H

#include <glib-object.h>
#include <gtk/gtk.h>

#define XDG_APP_GTK_TYPE_IMPORTED (xdg_app_gtk_imported_get_type ())
G_DECLARE_DERIVABLE_TYPE (XdgAppGtkImported, xdg_app_gtk_imported,
                          XDG_APP_GTK, IMPORTED,
                          GObject);

struct _XdgAppGtkImportedClass
{
  GObjectClass parent_class;

  void (*set_parent_of) (XdgAppGtkImported *imported,
                         GtkWindow *window);
};

void xdg_app_gtk_imported_set_parent_of (XdgAppGtkImported *imported,
                                         GtkWindow *window);

#endif /* XDG_APP_GTK_IMPORTED_H*/
