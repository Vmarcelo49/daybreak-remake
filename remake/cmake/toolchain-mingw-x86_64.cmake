# ----------------------------------------------------------------------------
# Toolchain file: cross-compile from Linux to Windows x64 using MinGW-w64
# (POSIX threads model, GCC 14, supports C++23).
#
# Usage:
#   cmake -S . -B build -G Ninja \
#         -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-mingw-x86_64.cmake \
#         -DCMAKE_BUILD_TYPE=Release
#
#  Expects ./scripts/fetch_deps.sh to have populated tools/ in the project
#  root.  You can override the location with -DDAYBREAK_TOOLS_DIR=/path.
# ----------------------------------------------------------------------------

set(CMAKE_SYSTEM_NAME       Windows)
set(CMAKE_SYSTEM_PROCESSOR  x86_64)

# Toolchain binaries (POSIX thread model so std::thread / std::jthread work)
set(_MINGW_PREFIX x86_64-w64-mingw32)
set(CMAKE_C_COMPILER        ${_MINGW_PREFIX}-gcc-posix)
set(CMAKE_CXX_COMPILER      ${_MINGW_PREFIX}-g++-posix)
set(CMAKE_RC_COMPILER       ${_MINGW_PREFIX}-windres)
set(CMAKE_AR                ${_MINGW_PREFIX}-ar        CACHE FILEPATH "")
set(CMAKE_RANLIB            ${_MINGW_PREFIX}-ranlib    CACHE FILEPATH "")
set(CMAKE_STRIP             ${_MINGW_PREFIX}-strip     CACHE FILEPATH "")

# Resolve tools/ relative to this file (so it works from any CWD), unless
# the caller overrides DAYBREAK_TOOLS_DIR explicitly.
if(NOT DEFINED DAYBREAK_TOOLS_DIR)
    get_filename_component(_THIS_DIR "${CMAKE_CURRENT_LIST_FILE}" DIRECTORY)
    get_filename_component(_PROJECT_DIR "${_THIS_DIR}/.." ABSOLUTE)
    set(DAYBREAK_TOOLS_DIR "${_PROJECT_DIR}/tools")
endif()

# Sysroot where MinGW headers + libs live (extracted from Debian mingw debs)
set(_MINGW_SYSROOT ${DAYBREAK_TOOLS_DIR}/mingw/usr/${_MINGW_PREFIX})
set(CMAKE_FIND_ROOT_PATH ${_MINGW_SYSROOT})

# SDL2 MinGW dev package install location
set(DAYBREAK_SDL2_ROOT ${DAYBREAK_TOOLS_DIR}/SDL2-2.30.10/x86_64-w64-mingw32)

# Search behavior under cross-compile
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)   # host tools (cmake, ninja) from host
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)   # libs only from sysroot
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)   # headers only from sysroot
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Static-link the winpthread runtime so the .exe doesn't need libwinpthread-1.dll
set(CMAKE_EXE_LINKER_FLAGS_INIT "-static -static-libgcc -static-libstdc++")
