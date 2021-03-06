AC_PREREQ([2.63])

AC_INIT([xdg-app-gtk],[0.0.1])

AC_PROG_CC
AM_PROG_CC_C_O
AC_DISABLE_STATIC

LT_PREREQ([2.2.6])
LT_INIT([disable-static])

AC_CONFIG_SRCDIR([xdg-app-gtk.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([1.11 no-define no-dist-gzip dist-bzip2 tar-ustar foreign])
AC_PROG_SED

# Enable silent rules is available
AM_SILENT_RULES([yes])
AM_MAINTAINER_MODE([enable])

if test "x$GCC" = "xyes"; then
  case " $CFLAGS " in
  *[[\ \	]]-Wall[[\ \	]]*) ;;
  *) CFLAGS="$CFLAGS -Wall" ;;
  esac
fi

PKG_PROG_PKG_CONFIG([0.24])

AC_ARG_WITH(dbus_service_dir,
        AS_HELP_STRING([--with-dbus-service-dir=PATH],[choose directory for dbus service files, [default=PREFIX/share/dbus-1/services]]),
        with_dbus_service_dir="$withval", with_dbus_service_dir=$datadir/dbus-1/services)
DBUS_SERVICE_DIR=$with_dbus_service_dir
AC_SUBST(DBUS_SERVICE_DIR)

AC_SUBST([XDG_APP_INTERFACES_DIR], [`$PKG_CONFIG --variable=interfaces_dir xdg-app`])
AC_SUBST([GDBUS_CODEGEN], [`$PKG_CONFIG --variable gdbus_codegen gio-2.0`])

PKG_CHECK_MODULES(WAYLAND, [wayland-client wayland-scanner wayland-protocols])
AC_SUBST(WAYLAND_PROTOCOLS_DATADIR, `$PKG_CONFIG --variable=pkgdatadir wayland-protocols`)
AC_PATH_PROG([WAYLAND_SCANNER],[wayland-scanner],[no])
AC_SUBST([WAYLAND_SCANNER])

PKG_CHECK_MODULES(GTK, [gtk+-3.0])
AC_SUBST(GTK_CFLAGS)
AC_SUBST(GTK_LIBS)

AC_CONFIG_FILES([
Makefile
])
AC_OUTPUT
