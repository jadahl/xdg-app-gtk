#include "config.h"

#include "xdg-app-gtk-imported.h"

#include <glib-object.h>

G_DEFINE_TYPE (XdgAppGtkImported, xdg_app_gtk_imported, G_TYPE_OBJECT);

void
xdg_app_gtk_imported_set_parent_of (XdgAppGtkImported *imported,
                                    GtkWindow *window)
{
  GdkWindow *gdk_window = gtk_widget_get_window (GTK_WIDGET (window));

  g_return_if_fail (gdk_window);
  g_return_if_fail ((gdk_window_get_type_hint (gdk_window) ==
                     GDK_WINDOW_TYPE_HINT_NORMAL) ||
                    (gdk_window_get_type_hint (gdk_window) ==
                     GDK_WINDOW_TYPE_HINT_DIALOG));

  XDG_APP_GTK_IMPORTED_GET_CLASS (imported)->set_parent_of (imported, window);
}

static void
xdg_app_gtk_imported_init (XdgAppGtkImported *imported)
{
}

static void
xdg_app_gtk_imported_class_init (XdgAppGtkImportedClass *klass)
{
}
