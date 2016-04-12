#include "config.h"

#include "xdg-app-gtk-imported.h"

#include <glib-object.h>

#include "xdg-app-gtk-impl.h"

enum
{
  PROP_0,

  PROP_IMPL,
};

typedef struct _XdgAppGtkImportedPrivate
{
  XdgAppGtkImpl *impl;
} XdgAppGtkImportedPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (XdgAppGtkImported, xdg_app_gtk_imported,
                            G_TYPE_OBJECT);

GdkDisplay *
xdg_app_gtk_imported_get_display (XdgAppGtkImported *imported)
{
  XdgAppGtkImportedPrivate *priv =
    xdg_app_gtk_imported_get_instance_private (imported);

  return xdg_app_gtk_impl_get_display (priv->impl);
}

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
xdg_app_gtk_imported_set_property (GObject      *object,
                                   guint         prop_id,
                                   const GValue *value,
                                   GParamSpec   *pspec)
{
  XdgAppGtkImported *imported = XDG_APP_GTK_IMPORTED (object);
  XdgAppGtkImportedPrivate *priv = xdg_app_gtk_imported_get_instance_private (imported);

  switch (prop_id)
    {
    case PROP_IMPL:
      g_set_object (&priv->impl, g_value_get_object (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
xdg_app_gtk_imported_get_property (GObject    *object,
                                   guint       prop_id,
                                   GValue     *value,
                                   GParamSpec *pspec)
{
  XdgAppGtkImported *imported = XDG_APP_GTK_IMPORTED (object);
  XdgAppGtkImportedPrivate *priv = xdg_app_gtk_imported_get_instance_private (imported);

  switch (prop_id)
    {
    case PROP_IMPL:
      g_value_set_object (value, priv->impl);

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
xdg_app_gtk_imported_init (XdgAppGtkImported *imported)
{
}

static void
xdg_app_gtk_imported_class_init (XdgAppGtkImportedClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->get_property = xdg_app_gtk_imported_get_property;
  object_class->set_property = xdg_app_gtk_imported_set_property;

  g_object_class_install_property (object_class,
                                   PROP_IMPL,
                                   g_param_spec_object ("impl",
                                                        "XdgAppGtkImpl",
                                                        "The XdgAppGtkImpl instance",
                                                        XDG_APP_GTK_TYPE_IMPL,
                                                        G_PARAM_READWRITE |
                                                        G_PARAM_CONSTRUCT_ONLY |
                                                        G_PARAM_STATIC_STRINGS));
}
