#include "config.h"

#include "xdg-app-gtk-importer.h"

#include <string.h>

#include "xdg-app-gtk-imported.h"

#ifdef GDK_WINDOWING_WAYLAND
#include "xdg-app-gtk-impl-wayland.h"
#endif
#ifdef GDK_WINDOWING_X11
#include "xdg-app-gtk-impl-x11.h"
#endif

struct _XdgAppGtkImporter
{
  GObject parent;

#ifdef GDK_WINDOWING_WAYLAND
  XdgAppGtkImpl *wayland_impl;
#endif
#ifdef GDK_WINDOWING_X11
  XdgAppGtkImpl *x11_impl;
#endif
};

G_DEFINE_TYPE (XdgAppGtkImporter, xdg_app_gtk_importer, G_TYPE_OBJECT);

XdgAppGtkImported *
xdg_app_gtk_importer_import (XdgAppGtkImporter *importer,
                             const char *handle)
{
  XdgAppGtkImpl *impl = NULL;

#ifdef GDK_WINDOWING_WAYLAND
  const char wayland_prefix[] = "wayland:";
  if (strncmp (handle, wayland_prefix, strlen (wayland_prefix)) == 0)
    impl = importer->wayland_impl;
#endif
#ifdef GDK_WINDOWING_X11
  const char x11_prefix[] = "x11:";
  if (strncmp (handle, x11_prefix, strlen (x11_prefix)) == 0)
    impl = importer->x11_impl;
#endif

  if (!impl)
    {
      g_warning ("Unsupported window handle '%s'", handle);
      return NULL;
    }

  return xdg_app_gtk_impl_import (impl, handle);
}

#ifdef GDK_WINDOWING_WAYLAND
static void
init_wayland_impl (XdgAppGtkImporter *importer)
{
  GdkDisplay *display;

  gdk_set_allowed_backends ("wayland");
  display = gdk_display_open (NULL);
  if (!display)
    {
      g_warning ("Failed to open Wayland display");
      return;
    }

  importer->wayland_impl = g_object_new (XDG_APP_GTK_TYPE_IMPL_WAYLAND,
                                         "display", display,
                                         NULL);
}
#endif

#ifdef GDK_WINDOWING_X11
static void
init_x11_impl (XdgAppGtkImporter *importer)
{
  GdkDisplay *display;

  gdk_set_allowed_backends ("x11");
  display = gdk_display_open (NULL);
  if (!display)
    {
      g_warning ("Failed to open X11 display");
      return;
    }

  importer->x11_impl = g_object_new (XDG_APP_GTK_TYPE_IMPL_X11,
                                         "display", display,
                                         NULL);
}
#endif

static void
xdg_app_gtk_importer_init (XdgAppGtkImporter *importer)
{
#ifdef GDK_WINDOWING_WAYLAND
  init_wayland_impl (importer);
#endif
#ifdef GDK_WINDOWING_X11
  init_x11_impl (importer);
#endif
}

static void
xdg_app_gtk_importer_class_init (XdgAppGtkImporterClass *klass)
{
}
