MAINTAINERCLEANFILES = Makefile.in

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

eet_la_SOURCES      = loader_eet.c common.h image.h
eet_la_CPPFLAGS     = @EET_CFLAGS@
eet_la_LDFLAGS      = -module -avoid-version
eet_la_LIBADD       = @EET_LIBS@
eet_la_LIBTOOLFLAGS = --tag=disable-static

xcf_la_SOURCES      = loader_xcf.c loader_xcf_pixelfuncs.c image.h common.h color_values.h
xcf_la_LDFLAGS      = -module -avoid-version
xcf_la_LIBADD       =
xcf_la_LIBTOOLFLAGS = --tag=disable-static

ico_la_SOURCES      = loader_ico.c common.h image.h
ico_la_LDFLAGS      = -module -avoid-version
ico_la_LIBADD       =
ico_la_LIBTOOLFLAGS = --tag=disable-static

ani_la_SOURCES      = loader_ani.c common.h image.h
ani_la_LDFLAGS      = -module -avoid-version
ani_la_LIBADD       =
ani_la_LIBTOOLFLAGS = --tag=disable-static
