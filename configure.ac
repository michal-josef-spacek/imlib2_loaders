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
LT_INIT
PKG_PROG_PKG_CONFIG

if test "x${bindir}" = 'x${exec_prefix}/bin'; then
  if test "x${exec_prefix}" = "xNONE"; then
    if test "x${prefix}" = "xNONE"; then
      bindir="${ac_default_prefix}/bin";
    else
      bindir="${prefix}/bin";
    fi
  else
    if test "x${prefix}" = "xNONE"; then
      bindir="${ac_default_prefix}/bin";
    else
      bindir="${prefix}/bin";
    fi
  fi
fi

if test "x${libdir}" = 'x${exec_prefix}/lib'; then
  if test "x${exec_prefix}" = "xNONE"; then
    if test "x${prefix}" = "xNONE"; then
      libdir="${ac_default_prefix}/lib";
    else
      libdir="${prefix}/lib";
    fi
  else
    if test "x${prefix}" = "xNONE"; then
      libdir="${ac_default_prefix}/lib";
    else
      libdir="${prefix}/lib";
    fi
  fi
fi

dnl Set PACKAGE_BIN_DIR in config.h.
if test "x${bindir}" = 'xNONE'; then
  if test "x${prefix}" = "xNONE"; then
    AC_DEFINE_UNQUOTED(PACKAGE_BIN_DIR, "${ac_default_prefix}/bin", [Installation directory for user executables])
  else
    AC_DEFINE_UNQUOTED(PACKAGE_BIN_DIR, "${prefix}/bin", [Installation directory for user executables])
  fi
else
  AC_DEFINE_UNQUOTED(PACKAGE_BIN_DIR, "${bindir}", [Installation directory for user executables])
fi

dnl Set PACKAGE_LIB_DIR in config.h.
if test "x${libdir}" = 'xNONE'; then
  if test "x${prefix}" = "xNONE"; then
    AC_DEFINE_UNQUOTED(PACKAGE_LIB_DIR, "${ac_default_prefix}/lib", [Installation directory for libraries])
  else
    AC_DEFINE_UNQUOTED(PACKAGE_LIB_DIR, "${prefix}/lib", [Installation directory for libraries])
  fi
else
  AC_DEFINE_UNQUOTED(PACKAGE_LIB_DIR, "${libdir}", [Installation directory for libraries])
fi

dnl Set PACKAGE_DATA_DIR in config.h.
if test "x${prefix}" = "xNONE"; then
  AC_DEFINE_UNQUOTED(PACKAGE_DATA_DIR, "${ac_default_prefix}/share/${PACKAGE}", [Shared Data Directory])
else
  AC_DEFINE_UNQUOTED(PACKAGE_DATA_DIR, "${prefix}/share/${PACKAGE}", [Shared Data Directory])
fi

dnl Set PACKAGE_SOURCE_DIR in config.h.
packagesrcdir=`cd $srcdir && pwd`
AC_DEFINE_UNQUOTED(PACKAGE_SOURCE_DIR, "${packagesrcdir}", [Source code directory])


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

AC_ARG_ENABLE(xcf,
[  --disable-xcf           disable building the xcf loader],
[
 if test x$enableval = xno; then
   xcf=no;
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

AM_CONDITIONAL(BUILD_EET_LOADER, test x$eet != xno)
AM_CONDITIONAL(BUILD_XCF_LOADER, test x$xcf != xno)

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

echo -e "\nBuild summary:"
echo    "------------------------"
echo -n " EET: "
if test x$eet = xno ; then
  echo    "Disabled "
else
  echo    "Enabled "
fi
echo -n " XCF: "
if test x$xcf = xno ; then
  echo    "Disabled "
else
  echo    "Enabled "
fi
