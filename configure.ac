#Generated 2008-07-30 by G. B. then completed with a lot of stuff from wormux configure.ac
dnl *** NOT TESTED YET !!! *********

AC_INIT(linbound, 0.1)
AC_CONFIG_SRCDIR(src/main.cpp)
AM_INIT_AUTOMAKE(foreign)

dnl *** Check for gettext and friends ***************************************

AM_GNU_GETTEXT_VERSION(0.19)
AM_GNU_GETTEXT([external])

if test "x$USE_NLS" != "xyes"; then
  AC_MSG_WARN([gettext is disabled. If you want internationalisation, please install gettext package.])
fi

dnl **************************
dnl *** Usual tools needed ***
dnl **************************
AC_PROG_CC
AC_PROG_CXX
AC_PROG_CPP
AC_PROG_INSTALL

AC_CHECK_PROG(cxx_present, $CXX, "yes", "no")
if test "x$cxx_present" != "xyes"; then
  AC_MSG_ERROR([*** No C++ compiler can be found!])
fi

dnl *****************
dnl *** SDL check ***
dnl *****************

SDL_VERSION=2.0

AM_PATH_SDL2($SDL_VERSION,
            :,
            AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!]))
CXXFLAGS="$CXXFLAGS $SDL_CFLAGS"
CFLAGS="$CFLAGS $SDL_CFLAGS"
CPPFLAGS="$CPPFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"

dnl *** png check, used by SDL2_image ... is it really compulsory since sdl_image requests libpng as a dependency ???***

dnl *********************
dnl *** SDL2_gfx check ***
dnl *********************

AC_ARG_WITH(sdl2-gfx-prefix,
            [  --with-sdl2-gfx-prefix=DIR       specify where SDL2_gfx library is installed],
            [SDL_GFX_PREFIX="$withval"])
AC_SUBST(SDL_GFX_PREFIX)
if test "x$SDL_GFX_PREFIX" != "x"; then
  CPPFLAGS="$CPPFLAGS -I$SDL_GFX_PREFIX/include/SDL2"
  CXXFLAGS="$CXXFLAGS -I$SDL_GFX_PREFIX/include/SDL2"
  LIBS="-L$SDL_GFX_PREFIX/lib $LIBS"
fi
if test "$static" = yes; then
  LIBS="$LIBS -lm -ldl -lfreetype -lz"
fi
AC_CHECK_LIB(SDL2_gfx, rotozoomSurfaceXY,,check_sdl_gfx="no")
AC_CHECK_HEADERS(SDL_rotozoom.h,,check_sdl_gfx="no")

dnl ****** Check for pkg-config **************************************************

AC_PATH_PROGS([PACKAGE_CONFIG], [$host_alias-pkg-config pkg-config], [none])
if test "x$PACKAGE_CONFIG" = "xnone"; then
  AC_MSG_ERROR([*** pkg-config, needed to check for libxml2 existence has not been found.])
fi

dnl ****** Check for the whole SDL shabang ***************************************

AC_CHECK_LIB($PNG, png_error,,,)
AC_CHECK_LIB(SDL2_image, IMG_Load,,check_sdl_image="no")
AC_CHECK_LIB(SDL2_mixer, Mix_OpenAudio,,check_sdl_mixer="no")
AC_CHECK_LIB([SDL2_ttf], [TTF_OpenFont],,check_sdl_ttf="no")
AC_CHECK_LIB([SDL2_net], [SDLNet_Init],,check_sdl_net="no")
if test "${WIN32}" = "yes"; then LIBS="$LIBS -lwsock32 -lws2_32 -luser32"; fi

dnl *** Errors to display when missing ***********************************

if test \
     x${check_sdl_image} = xno \
  -o x${check_sdl_mixer} = xno \
  -o x${check_sdl_ttf} = xno \
  -o x${check_sdl_gfx} = xno \
  -o x${check_sdl_net} = xno \
  ; then
  AC_MSG_RESULT([])
  if test x${check_sdl_image} = xno; then
    AC_MSG_RESULT([ERROR: SDL2_image library required])
  fi
  if test x${check_sdl_mixer} = xno; then
    AC_MSG_RESULT([ERROR: SDL2_mixer library required])
  fi
  if test x${check_sdl_ttf} = xno; then
    AC_MSG_RESULT([ERROR: SDL2_ttf library required])
  fi
  if test x${check_sdl_gfx} = xno; then
    AC_MSG_RESULT([ERROR: SDL2_gfx library version >= 2.0.13 required])
  fi
  if test x${check_sdl_net} = xno; then
    AC_MSG_RESULT([ERROR: SDL2_net library required])
  fi
  exit 1
fi


AC_OUTPUT(Makefile po/Makefile.in src/Makefile)
