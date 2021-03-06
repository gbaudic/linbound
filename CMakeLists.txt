project(linbound)

cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 11)

# The version number.
set (Linbound_VERSION_MAJOR 0)
set (Linbound_VERSION_MINOR 1)
set (Linbound_VERSION_RELEASE 0)
set (ENABLE_SERVER FALSE)
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.hpp.in"
  "${PROJECT_SOURCE_DIR}/config.hpp"
  )

add_executable(${PROJECT_NAME} src/main.cpp)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2_IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2_TTF REQUIRED SDL2_ttf)
PKG_SEARCH_MODULE(SDL2_GFX REQUIRED SDL2_gfx)
PKG_SEARCH_MODULE(SDL2_MIXER REQUIRED SDL2_mixer)
PKG_SEARCH_MODULE(SDL2_NET REQUIRED SDL2_net)
PKG_SEARCH_MODULE(GUISAN REQUIRED guisan>=0.9.0)
#todo sqlite tinyxml + make sure errors are printed 
find_library(TINYXML2 REQUIRED libtinyxml2)
find_library(SQLITE3 REQUIRED libsqlite3)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} 
	${SDL2_IMAGE_INCLUDE_DIRS} 
	${SDL2_TTF_INCLUDE_DIRS}
	${SDL2_GFX_INCLUDE_DIRS}
	${SDL2_MIXER_INCLUDE_DIRS}
	${SDL2_NET_INCLUDE_DIRS}
	${GUISAN_INCLUDE_DIRS}
	${TINYXML2_INCLUDE_DIRS}
	${SQLITE3_INCLUDE_DIRS})
	
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} 
	${SDL2_IMAGE_LIBRARIES} 
	${SDL2_TTF_LIBRARIES}
	${SDL2_GFX_LIBRARIES}
	${SDL2_MIXER_LIBRARIES}
	${SDL2_NET_LIBRARIES}
	${GUISAN_LIBRARIES}
	${TINYXML2_LIBRARIES}
	${SQLITE3_LIBRARIES})
