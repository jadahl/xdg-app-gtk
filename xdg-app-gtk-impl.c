#include "config.h"

#include "xdg-app-gtk-impl.h"

#include <glib-object.h>

#include "xdg-app-gtk-imported.h"

enum
{
  PROP_0,

  PROP_DISPLAY,
};

typedef struct _XdgAppGtkImplPrivate
{
  GMainLoop *loop;
  GdkDisplay *display;
} XdgAppGtkImplPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (XdgAppGtkImpl, xdg_app_gtk_impl, G_TYPE_OBJECT);

XdgAppGtkImported *
xdg_app_gtk_impl_import (XdgAppGtkImpl *impl,
                         const char *handle)
{
  return XDG_APP_GTK_IMPL_GET_CLASS (impl)->import (impl, handle);
}

GdkDisplay *
xdg_app_gtk_impl_get_display (XdgAppGtkImpl *impl)
{
  XdgAppGtkImplPrivate *priv = xdg_app_gtk_impl_get_instance_private (impl);

  return priv->display;
}

static void
xdg_app_gtk_impl_dispose (GObject *object)
{
  XdgAppGtkImpl *impl = XDG_APP_GTK_IMPL (object);
  XdgAppGtkImplPrivate *priv = xdg_app_gtk_impl_get_instance_private (impl);

  g_clear_object (&priv->display);

  G_OBJECT_CLASS (xdg_app_gtk_impl_parent_class)->dispose (object);
}

static void
xdg_app_gtk_impl_set_property (GObject      *object,
                               guint         prop_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
  XdgAppGtkImpl *impl = XDG_APP_GTK_IMPL (object);
  XdgAppGtkImplPrivate *priv = xdg_app_gtk_impl_get_instance_private (impl);

  switch (prop_id)
    {
    case PROP_DISPLAY:
      g_set_object (&priv->display, g_value_get_object (value));
      break;

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
xdg_app_gtk_impl_get_property (GObject    *object,
                               guint       prop_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  XdgAppGtkImpl *impl = XDG_APP_GTK_IMPL (object);
  XdgAppGtkImplPrivate *priv = xdg_app_gtk_impl_get_instance_private (impl);

  switch (prop_id)
    {
    case PROP_DISPLAY:
      g_value_set_object (value, priv->display);

    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    }
}

static void
xdg_app_gtk_impl_init (XdgAppGtkImpl *impl)
{
}

static void
xdg_app_gtk_impl_class_init (XdgAppGtkImplClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->dispose = xdg_app_gtk_impl_dispose;
  object_class->get_property = xdg_app_gtk_impl_get_property;
  object_class->set_property = xdg_app_gtk_impl_set_property;

  g_object_class_install_property (object_class,
                                   PROP_DISPLAY,
                                   g_param_spec_object ("display",
                                                        "GdkDisplay",
                                                        "The GdkDisplay instance",
                                                        GDK_TYPE_DISPLAY,
                                                        G_PARAM_READWRITE |
                                                        G_PARAM_CONSTRUCT_ONLY |
                                                        G_PARAM_STATIC_STRINGS));
}
