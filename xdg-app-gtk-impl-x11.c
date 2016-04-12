#include "config.h"

#include "xdg-app-gtk-impl-x11.h"

#include <glib-object.h>
#include <stdio.h>

#include "xdg-app-gtk-imported-x11.h"

struct _XdgAppGtkImplX11
{
  XdgAppGtkImpl parent;
};

G_DEFINE_TYPE (XdgAppGtkImplX11, xdg_app_gtk_impl_x11, XDG_APP_GTK_TYPE_IMPL);

static XdgAppGtkImported *
xdg_app_gtk_impl_x11_import (XdgAppGtkImpl *impl,
                             const char *handle)
{
  int xid;

  if (sscanf (handle, "x11:%x", &xid) != 1)
    {
      g_warning ("Not an X11 window handle or invalid xid");
      return NULL;
    }

  return xdg_app_gtk_imported_x11_new (impl, xid);
}

static void
xdg_app_gtk_impl_x11_init (XdgAppGtkImplX11 *impl_x11)
{
}

static void
xdg_app_gtk_impl_x11_class_init (XdgAppGtkImplX11Class *klass)
{
  XdgAppGtkImplClass *impl_class = XDG_APP_GTK_IMPL_CLASS (klass);

  impl_class->import = xdg_app_gtk_impl_x11_import;
}
