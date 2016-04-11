#include "config.h"

#include "xdg-app-gtk-wayland.h"

#include <glib-object.h>
#include <gdk/gdkwayland.h>
#include <string.h>

#include "xdg-app-gtk-imported-wayland.h"

#include "xdg-foreign-unstable-v1-client-protocol.h"

struct _XdgAppGtkImplWayland
{
  XdgAppGtkImpl parent;

  struct zxdg_importer_v1 *importer;
};

G_DEFINE_TYPE (XdgAppGtkImplWayland, xdg_app_gtk_impl_wayland, XDG_APP_GTK_TYPE_IMPL);

static XdgAppGtkImported *
xdg_app_gtk_impl_wayland_import (XdgAppGtkImpl *impl,
                                 const char *handle)
{
  XdgAppGtkImplWayland *impl_wayland = XDG_APP_GTK_IMPL_WAYLAND (impl);
  const char prefix[] = "wayland:";
  g_autofree char *xdg_foreign_handle = NULL;
  struct zxdg_imported_v1 *imported;

  if (!impl_wayland->importer)
    {
      g_warning ("Wayland server doesn't have the xdg_importer interface");
      return NULL;
    }

  if (strncmp (handle, prefix, strlen (prefix)) != 0)
    {
      g_warning ("Not a Wayland surface handle");
      return NULL;
    }

  xdg_foreign_handle = g_strdup (handle + strlen (prefix));
  imported = zxdg_importer_v1_import (impl_wayland->importer,
                                      xdg_foreign_handle);

  return xdg_app_gtk_imported_wayland_new (impl, imported);
}

static void
registry_handle_global (void *data,
                        struct wl_registry *registry,
                        uint32_t name,
                        const char *interface,
                        uint32_t version)
{
  XdgAppGtkImpl *impl = data;
  XdgAppGtkImplWayland *impl_wayland = XDG_APP_GTK_IMPL_WAYLAND (impl);

  if (strcmp (interface, "zxdg_importer_v1") == 0)
    {
      impl_wayland->importer = wl_registry_bind (registry,
                                                 name,
                                                 &zxdg_importer_v1_interface,
                                                 1);
    }
}

static void
registry_handle_global_remove (void *data,
                               struct wl_registry *registry,
                               uint32_t name)
{
}

static const struct wl_registry_listener registry_listener = {
  registry_handle_global,
  registry_handle_global_remove
};

static void
xdg_app_gtk_impl_wayland_constructed (GObject *object)
{
  XdgAppGtkImpl *impl = XDG_APP_GTK_IMPL (object);
  GdkDisplay *display = xdg_app_gtk_impl_get_display (impl);
  struct wl_display *wl_display = gdk_wayland_display_get_wl_display (display);
  struct wl_registry *registry;

  registry = wl_display_get_registry (wl_display);
  wl_registry_add_listener (registry, &registry_listener, impl);
  wl_display_roundtrip (wl_display);
}

static void
xdg_app_gtk_impl_wayland_init (XdgAppGtkImplWayland *impl_wayland)
{
}

static void
xdg_app_gtk_impl_wayland_class_init (XdgAppGtkImplWaylandClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  XdgAppGtkImplClass *impl_class = XDG_APP_GTK_IMPL_CLASS (klass);

  object_class->constructed = xdg_app_gtk_impl_wayland_constructed;

  impl_class->import = xdg_app_gtk_impl_wayland_import;
}
