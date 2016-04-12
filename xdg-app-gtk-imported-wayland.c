#include "config.h"

#include "xdg-app-gtk-imported-wayland.h"

#include <gdk/gdk.h>
#include <gdk/gdkwayland.h>

#include "xdg-foreign-unstable-v1-client-protocol.h"

struct _XdgAppGtkImportedWayland
{
  XdgAppGtkImported parent;

  struct zxdg_imported_v1 *imported;
};

G_DEFINE_TYPE (XdgAppGtkImportedWayland, xdg_app_gtk_imported_wayland,
               XDG_APP_GTK_TYPE_IMPORTED);

static void
xdg_imported_destroyed (void *data,
                        struct zxdg_imported_v1 *zxdg_imported_v1)
{
  /* TODO: Send signal so xdg-app-gtk can hide its portal window. */
}

static const struct zxdg_imported_v1_listener xdg_imported_listener = {
  xdg_imported_destroyed,
};

XdgAppGtkImported *
xdg_app_gtk_imported_wayland_new (XdgAppGtkImpl *impl,
                                  struct zxdg_imported_v1 *imported)
{
  XdgAppGtkImportedWayland *imported_wayland;

  imported_wayland = g_object_new (XDG_APP_GTK_TYPE_IMPORTED_WAYLAND,
                                   "impl", impl,
                                   NULL);
  imported_wayland->imported = imported;
  zxdg_imported_v1_add_listener (imported, &xdg_imported_listener, imported);

  return XDG_APP_GTK_IMPORTED (imported_wayland);
}

static void
window_visible (GtkWidget *widget,
                GParamSpec *pspec,
                XdgAppGtkImported *imported)
{
  XdgAppGtkImportedWayland *imported_wayland =
    XDG_APP_GTK_IMPORTED_WAYLAND (imported);
  GdkWindow *gdk_window;
  struct wl_surface *surface;

  if (!gtk_widget_is_visible (widget))
    return;

  gdk_window = gtk_widget_get_window (widget);
  surface = gdk_wayland_window_get_wl_surface (gdk_window);
  zxdg_imported_v1_set_parent_of (imported_wayland->imported, surface);
}

static void
xdg_app_gtk_imported_wayland_set_parent_of (XdgAppGtkImported *imported,
                                            GtkWindow *window)
{
  XdgAppGtkImportedWayland *imported_wayland =
    XDG_APP_GTK_IMPORTED_WAYLAND (imported);
  GdkWindow *gdk_window = gtk_widget_get_window (GTK_WIDGET (window));
  struct wl_surface *surface;

  if (!gtk_widget_is_visible (GTK_WIDGET (window)))
    {
      g_signal_connect_object (window, "notify::visible",
                               G_CALLBACK (window_visible),
                               imported, 0);
      return;
    }

  surface = gdk_wayland_window_get_wl_surface (gdk_window);
  zxdg_imported_v1_set_parent_of (imported_wayland->imported, surface);
}

static void
xdg_app_gtk_imported_wayland_finalize (GObject *object)
{
  XdgAppGtkImportedWayland *imported_wayland =
    XDG_APP_GTK_IMPORTED_WAYLAND (object);

  zxdg_imported_v1_destroy (imported_wayland->imported);

  G_OBJECT_CLASS (xdg_app_gtk_imported_wayland_parent_class)->finalize (object);
}

static void
xdg_app_gtk_imported_wayland_init (XdgAppGtkImportedWayland *imported_wayland)
{
}

static void
xdg_app_gtk_imported_wayland_class_init (XdgAppGtkImportedWaylandClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  XdgAppGtkImportedClass *imported_class = XDG_APP_GTK_IMPORTED_CLASS (klass);

  object_class->finalize = xdg_app_gtk_imported_wayland_finalize;

  imported_class->set_parent_of = xdg_app_gtk_imported_wayland_set_parent_of;
}
