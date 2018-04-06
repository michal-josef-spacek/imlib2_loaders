MAINTAINERCLEANFILES = Makefile.in

AM_CFLAGS            = $(CFLAGS_WARNINGS)

pkgdir               = $(libdir)/imlib2/loaders

if BUILD_ANI_LOADER
ANI_L                = ani.la
endif
if BUILD_EET_LOADER
EET_L                = eet.la
endif
if BUILD_ICO_LOADER
ICO_L                = ico.la
endif
if BUILD_XCF_LOADER
XCF_L                = xcf.la
endif

pkg_LTLIBRARIES      = \
$(ANI_L) \
$(EET_L) \
$(ICO_L) \
$(XCF_L)

EXTRA_DIST = color_values.h common.h image.h loader_common.h

eet_la_SOURCES      = loader_eet.c
eet_la_CPPFLAGS     = @EET_CFLAGS@
eet_la_LDFLAGS      = -module -avoid-version
eet_la_LIBADD       = @EET_LIBS@
eet_la_LIBTOOLFLAGS = --tag=disable-static

xcf_la_SOURCES      = loader_xcf.c loader_xcf_pixelfuncs.c loader_xcf.h
xcf_la_LDFLAGS      = -module -avoid-version
xcf_la_LIBADD       =
xcf_la_LIBTOOLFLAGS = --tag=disable-static

ico_la_SOURCES      = loader_ico.c
ico_la_LDFLAGS      = -module -avoid-version
ico_la_LIBADD       =
ico_la_LIBTOOLFLAGS = --tag=disable-static

ani_la_SOURCES      = loader_ani.c
ani_la_LDFLAGS      = -module -avoid-version
ani_la_LIBADD       =
ani_la_LIBTOOLFLAGS = --tag=disable-static
