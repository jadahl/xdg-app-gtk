NULL =

libexec_PROGRAMS = \
	xdg-app-gtk-portal \
	$(NULL)

portaldir = $(datadir)/xdg-app/portals
portal_DATA = gtk.portal

dbus_built_sources = xdg-app-portal-dbus.c xdg-app-portal-dbus.h
BUILT_SOURCES = $(dbus_built_sources)

$(dbus_built_sources): Makefile.am
	$(AM_V_GEN) $(GDBUS_CODEGEN)			\
	--interface-prefix org.freedesktop.portal.	\
	--c-namespace XdgAppDesktop			\
	--generate-c-code xdg-app-portal-dbus		\
	 $(XDG_APP_INTERFACES_DIR)/org.freedesktop.portal.FileChooserBackend.xml \
	$(NULL)

%.service: %.service.in config.log
	$(AM_V_GEN) $(SED) -e "s|\@libexecdir\@|$(libexecdir)|" $< > $@

servicedir = $(DBUS_SERVICE_DIR)
service_in_files = org.freedesktop.portal_backend.desktop.gtk.service.in
service_DATA = org.freedesktop.portal_backend.desktop.gtk.service

wayland_built_sources = \
	xdg-foreign-unstable-v1-client-protocol.h \
	xdg-foreign-unstable-v1-protocol.c
BUILT_SOURCES += $(wayland_built_sources)

.SECONDEXPANSION:

define protostability
$(shell echo $1 | sed 's/.*\(\<unstable\>\|\<stable\>\).*/\1/')
endef

define protoname
$(shell echo $1 | sed 's/\([a-z\-]\+\)-[a-z]\+-v[0-9]\+/\1/')
endef

%-protocol.c : $(WAYLAND_PROTOCOLS_DATADIR)/$$(call protostability,$$*)/$$(call protoname,$$*)/$$*.xml
	$(AM_V_GEN)$(WAYLAND_SCANNER) code < $< > $@
	$(AM_V_GEN)$(SED) -i -e 's/WL_EXPORT //' $@
%-client-protocol.h : $(WAYLAND_PROTOCOLS_DATADIR)/$$(call protostability,$$*)/$$(call protoname,$$*)/$$*.xml
	$(AM_V_GEN)$(WAYLAND_SCANNER) client-header < $< > $@

xdg_app_gtk_portal_SOURCES = \
	xdg-app-gtk.c		\
	xdg-app-gtk.h		\
	xdg-app-gtk-imported.c	\
	xdg-app-gtk-imported.h	\
	xdg-app-gtk-imported-wayland.c	\
	xdg-app-gtk-imported-wayland.h	\
	xdg-app-gtk-imported-x11.c	\
	xdg-app-gtk-imported-x11.h	\
	xdg-app-gtk-impl.c	\
	xdg-app-gtk-impl.h	\
	xdg-app-gtk-impl-wayland.c	\
	xdg-app-gtk-impl-wayland.h	\
	xdg-app-gtk-impl-x11.c	\
	xdg-app-gtk-impl-x11.h	\
	$(dbus_built_sources)	\
	$(wayland_built_sources)	\
	$(NULL)

xdg_app_gtk_portal_LDADD = $(BASE_LIBS) $(GTK_LIBS)
xdg_app_gtk_portal_CFLAGS = $(BASE_CFLAGS) $(GTK_CFLAGS)
