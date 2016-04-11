#include "config.h"

#include "xdg-app-gtk-imported-x11.h"

#include <gdk/gdkx.h>

#include "xdg-app-gtk.h"
#include "xdg-app-gtk-imported.h"

struct _XdgAppGtkImportedX11
{
  XdgAppGtkImported parent;

  GdkWindow *imported_window;
};

G_DEFINE_TYPE (XdgAppGtkImportedX11, xdg_app_gtk_imported_x11,
               XDG_APP_GTK_TYPE_IMPORTED);

XdgAppGtkImported *
xdg_app_gtk_imported_x11_new (XdgAppGtkImpl *impl,
                              int xid)
{
  GdkDisplay *display;
  XdgAppGtkImportedX11 *imported_x11;

  imported_x11 = g_object_new (XDG_APP_GTK_TYPE_IMPORTED_X11, NULL);

  display = xdg_app_gtk_impl_get_display (impl);
  imported_x11->imported_window =
    gdk_x11_window_foreign_new_for_display (display, xid);

  return XDG_APP_GTK_IMPORTED (imported_x11);
}

static void
xdg_app_gtk_imported_x11_set_parent_of (XdgAppGtkImported *imported,
                                        GtkWindow *window)
{
  XdgAppGtkImportedX11 *imported_x11 = XDG_APP_GTK_IMPORTED_X11 (imported);
  GdkWindow *gdk_window = gtk_widget_get_window (GTK_WIDGET (window));

  gdk_window_set_transient_for (gdk_window, imported_x11->imported_window);
}

static void
xdg_app_gtk_imported_x11_init (XdgAppGtkImportedX11 *imported_x11)
{
}

static void
xdg_app_gtk_imported_x11_class_init (XdgAppGtkImportedX11Class *klass)
{
  XdgAppGtkImportedClass *imported_class = XDG_APP_GTK_IMPORTED_CLASS (klass);

  imported_class->set_parent_of = xdg_app_gtk_imported_x11_set_parent_of;
}
