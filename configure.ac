#Started 2008-07-30 by G. B. then completed with a lot of stuff from wormux configure.ac

AC_INIT(linbound, 0.1)
AC_CONFIG_SRCDIR(src/main.cpp)
AM_INIT_AUTOMAKE([foreign])

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

SDL_VERSION=2.0.0

AM_PATH_SDL2($SDL_VERSION,
            :,
            AC_MSG_ERROR([*** SDL2 version $SDL_VERSION not found!]))
CXXFLAGS="$CXXFLAGS $SDL_CFLAGS -std=c++11"
CFLAGS="$CFLAGS $SDL_CFLAGS"
CPPFLAGS="$CPPFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS"

dnl *********************
dnl *** SDL2_gfx check **
dnl *********************

AC_ARG_WITH(sdl2-gfx-prefix,
            [  --with-sdl2-gfx-prefix=DIR       specify where SDL2_gfx library is installed],
            [SDL2_GFX_PREFIX="$withval"])
AC_SUBST(SDL2_GFX_PREFIX)
if test "x$SDL2_GFX_PREFIX" != "x"; then
  CPPFLAGS="$CPPFLAGS -I$SDL2_GFX_PREFIX/include/SDL2"
  CXXFLAGS="$CXXFLAGS -I$SDL2_GFX_PREFIX/include/SDL2"
  LIBS="-L$SDL2_GFX_PREFIX/lib $LIBS"
fi
if test "$static" = yes; then
  LIBS="$LIBS -lm -ldl -lfreetype -lz"
fi
AC_CHECK_LIB(SDL2_gfx, rotozoomSurfaceXY,,check_sdl_gfx="no")
AC_CHECK_HEADERS([SDL2/SDL2_rotozoom.h],,check_sdl_gfx="no")

dnl ****** Check for pkg-config **************************************************

PKG_PROG_PKG_CONFIG()
PKG_CHECK_MODULES(GUISAN, guisan, [], [AC_MSG_FAILURE([guisan not found, see https://github/gbaudic/guisan])])
PKG_CHECK_MODULES(TINYXML2, tinyxml2, [], [AC_MSG_FAILURE([tinyxml2 not found])])
CFLAGS="$CFLAGS $GUISAN_CFLAGS $TINYXML2_CFLAGS"
CPPFLAGS="$CPPFLAGS $GUISAN_CFLAGS $TINYXML2_CFLAGS"
CXXFLAGS="$CXXFLAGS $GUISAN_CFLAGS $TINYXML2_CFLAGS"
LIBS="$LIBS $GUISAN_LIBS $TINYXML2_LIBS"

dnl ****** Check for the whole SDL shabang ***************************************

AC_CHECK_LIB(SDL2_image, IMG_Load,,check_sdl_image="no")
AC_CHECK_LIB(SDL2_mixer, Mix_OpenAudio,,check_sdl_mixer="no")
AC_CHECK_LIB([SDL2_ttf], [TTF_OpenFont],,check_sdl_ttf="no")
AC_CHECK_LIB([SDL2_net], [SDLNet_Init],,check_sdl_net="no")
AC_CHECK_LIB(sqlite3, sqlite3_open,,check_sqlite3="no")
if test "${WIN32}" = "yes"; then LIBS="$LIBS -lwsock32 -lws2_32 -luser32"; fi

dnl *** Errors to display when missing ***********************************

if test \
     x${check_sdl_image} = xno \
  -o x${check_sdl_mixer} = xno \
  -o x${check_sdl_ttf} = xno \
  -o x${check_sdl_gfx} = xno \
  -o x${check_sdl_net} = xno \
  -o x${check_sqlite3} = xno \
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
    AC_MSG_RESULT([ERROR: SDL2_gfx library version >= 1.0.0 required])
  fi
  if test x${check_sdl_net} = xno; then
    AC_MSG_RESULT([ERROR: SDL2_net library required])
  fi
  if test x${check_sqlite3} = xno; then
    AC_MSG_RESULT([ERROR: sqlite3 library required])
  fi
  exit 1
fi


AC_OUTPUT(Makefile po/Makefile.in src/Makefile res/Makefile)

echo "Configuration of linbound done. "
echo "Now type make to compile then sudo make install to install."
