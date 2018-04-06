# get rid of that stupid cache mechanism
rm -f config.cache

AC_INIT([imlib2_loaders],[1.5.1],[enlightenment-devel@lists.sourceforge.net])
AC_CONFIG_SRCDIR(configure.ac)
AC_CONFIG_MACRO_DIR([m4])
AC_CANONICAL_BUILD
AC_CANONICAL_HOST

AM_INIT_AUTOMAKE(1.6 dist-bzip2)
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_C_BIGENDIAN
AC_PROG_CC

AC_HEADER_STDC
AC_C_CONST

dnl Next two lines is a hack to prevent libtool checking for CXX/F77
define([AC_LIBTOOL_LANG_CXX_CONFIG], [:])dnl
define([AC_LIBTOOL_LANG_F77_CONFIG], [:])dnl
LT_INIT

PKG_PROG_PKG_CONFIG

ani=yes
ico=yes

eet=auto
AC_ARG_ENABLE(eet,
[  --disable-eet           disable building the eet loader],
[
 if test x$enableval = xno; then
   eet=no
 else
   eet=yes
 fi
])

xcf=yes
AC_ARG_ENABLE(xcf,
[  --disable-xcf           disable building the xcf loader],
[
 if test x$enableval = xno; then
   xcf=no
 else
   xcf=yes
 fi
])


dnl PKG_CHECK_MODULES(IMLIB2, imlib2)

found_eet=no
if test "x$eet" != "xno" ; then
        PKG_CHECK_MODULES(EET, eet, found_eet=yes, found_eet=no)
fi
if test "x$eet$found_eet" = "xyesno" ; then
	AC_MSG_ERROR(Eet support was requested but not found)
elif test "x$found_eet" = "xno" ; then
	eet=no
fi

AM_CONDITIONAL(BUILD_ANI_LOADER, test x$ani != xno)
AM_CONDITIONAL(BUILD_EET_LOADER, test x$eet != xno)
AM_CONDITIONAL(BUILD_ICO_LOADER, test x$ico != xno)
AM_CONDITIONAL(BUILD_XCF_LOADER, test x$xcf != xno)

EC_C_WARNINGS()

AC_CONFIG_HEADERS(config.h)
AC_CONFIG_FILES([
Makefile
src/Makefile
src/modules/Makefile
src/modules/loaders/Makefile
README
imlib2_loaders.spec
])
AC_CONFIG_COMMANDS([default],[
],[])
AC_OUTPUT

#####################################################################
## Info
echo
echo
echo "------------------------------------------------------------------------"
echo "$PACKAGE $VERSION"
echo "------------------------------------------------------------------------"
echo
echo "Configuration Options Summary:"
echo
echo "Image loaders:"
echo "  ANI.....................: $ani"
echo "  EET.....................: $eet"
echo "  ICO.....................: $ico"
echo "  XCF.....................: $xcf"
echo
echo "Installation path.........: $prefix"
echo
