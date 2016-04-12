#ifndef XDG_APP_GTK_IMPL_H
#define XDG_APP_GTK_IMPL_H

#include <gdk/gdk.h>
#include <glib-object.h>

typedef struct _XdgAppGtkImported XdgAppGtkImported;

#define XDG_APP_GTK_TYPE_IMPL (xdg_app_gtk_impl_get_type ())
G_DECLARE_DERIVABLE_TYPE (XdgAppGtkImpl, xdg_app_gtk_impl,
                          XDG_APP_GTK, IMPL,
                          GObject);

struct _XdgAppGtkImplClass
{
  GObjectClass parent_class;

  XdgAppGtkImported * (*import) (XdgAppGtkImpl *impl,
                                 const char *handle);
};

XdgAppGtkImported * xdg_app_gtk_impl_import (XdgAppGtkImpl *impl,
                                             const char *handle);

GdkDisplay * xdg_app_gtk_impl_get_display (XdgAppGtkImpl *impl);

#endif /* XDG_APP_GTK_IMPL_H */
