# ============================================================================
#  daybreak - old-game port skeleton
#  Cross-compiled from Linux to Windows x64 with MinGW-w64 + CMake + Ninja.
# ============================================================================
cmake_minimum_required(VERSION 3.22)

project(daybreak
    VERSION     0.2.0
    DESCRIPTION "daybreak - old-game port"
    LANGUAGES   CXX)

# ---- C++23 -----------------------------------------------------------------
set(CMAKE_CXX_STANDARD          23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# ---- Global compile options -------------------------------------------------
add_compile_options(
    -Wall -Wextra -Wpedantic
    -Wno-unknown-pragmas
    -Wno-unused-parameter
    -fdiagnostics-color=always)

# Avoid the classic Win32 min/max macro pollution
add_compile_definitions(
    NOMINMAX
    WIN32_LEAN_AND_MEAN
    _CRT_SECURE_NO_WARNINGS
    UNICODE _UNICODE)

# ----------------------------------------------------------------------------
# Resolve tools/ directory (set by toolchain file, or override by caller)
# ----------------------------------------------------------------------------
if(NOT DEFINED DAYBREAK_TOOLS_DIR)
    get_filename_component(_PROJECT_DIR "${CMAKE_SOURCE_DIR}" ABSOLUTE)
    set(DAYBREAK_TOOLS_DIR "${_PROJECT_DIR}/tools")
endif()

# ----------------------------------------------------------------------------
# SDL2 (MinGW dev package)
# ----------------------------------------------------------------------------
if(NOT DEFINED DAYBREAK_SDL2_ROOT)
    set(DAYBREAK_SDL2_ROOT ${DAYBREAK_TOOLS_DIR}/SDL2-2.30.10/x86_64-w64-mingw32)
endif()

set(SDL2_INCLUDE_DIR  ${DAYBREAK_SDL2_ROOT}/include/SDL2)
set(SDL2_LIBRARY      ${DAYBREAK_SDL2_ROOT}/lib/libSDL2.dll.a)
set(SDL2_MAIN_LIBRARY ${DAYBREAK_SDL2_ROOT}/lib/libSDL2main.a)
set(SDL2_RUNTIME_DLL  ${DAYBREAK_SDL2_ROOT}/bin/SDL2.dll)

if(NOT EXISTS ${SDL2_INCLUDE_DIR}/SDL.h)
    message(FATAL_ERROR "SDL2 headers not found at ${SDL2_INCLUDE_DIR} — run scripts/fetch_deps.sh")
endif()

add_library(daybreak_sdl2 INTERFACE)
target_include_directories(daybreak_sdl2 INTERFACE ${SDL2_INCLUDE_DIR})
# Use --whole-archive around libSDL2main.a so its WinMain symbol is always
# pulled in (the mingw32 CRT references WinMain late in the link).
target_link_libraries(daybreak_sdl2 INTERFACE
    "-Wl,--whole-archive"
    ${SDL2_MAIN_LIBRARY}
    "-Wl,--no-whole-archive"
    ${SDL2_LIBRARY})

# SDL2 on Windows needs Win32 libs in this order (SDL2main first)
target_link_libraries(daybreak_sdl2 INTERFACE
    user32 gdi32 winmm imm32 ole32 oleaut32 version shell32
    setupapi advapi32 dinput8 dwmapi)


# ----------------------------------------------------------------------------
# SDL2_mixer (audio — WAV/OGG/MP3 playback + mixing)
# ----------------------------------------------------------------------------
if(NOT DEFINED DAYBREAK_SDL2_MIXER_ROOT)
    set(DAYBREAK_SDL2_MIXER_ROOT ${DAYBREAK_TOOLS_DIR}/SDL2_mixer-2.8.0/x86_64-w64-mingw32)
endif()
set(SDL2_MIXER_INCLUDE_DIR ${DAYBREAK_SDL2_MIXER_ROOT}/include/SDL2)
set(SDL2_MIXER_LIBRARY     ${DAYBREAK_SDL2_MIXER_ROOT}/lib/libSDL2_mixer.dll.a)
set(SDL2_MIXER_RUNTIME_DLL ${DAYBREAK_SDL2_MIXER_ROOT}/bin/SDL2_mixer.dll)

if(NOT EXISTS ${SDL2_MIXER_INCLUDE_DIR}/SDL_mixer.h)
    message(FATAL_ERROR "SDL2_mixer headers not found at ${SDL2_MIXER_INCLUDE_DIR} — run scripts/fetch_deps.sh")
endif()

add_library(daybreak_sdl2_mixer INTERFACE)
target_include_directories(daybreak_sdl2_mixer INTERFACE ${SDL2_MIXER_INCLUDE_DIR})
target_link_libraries(daybreak_sdl2_mixer INTERFACE ${SDL2_MIXER_LIBRARY})
# ----------------------------------------------------------------------------
# Project sources — organized by subsystem (see README.md for the layout).
# Each subfolder under src/ corresponds to a major engine subsystem.
# ----------------------------------------------------------------------------
set(DAYBREAK_SOURCES
    src/main.cpp
    src/assets/asset_manager.cpp
    src/audio/audio_engine.cpp
    src/core/scene_manager.cpp
    src/core/scenes.cpp
    src/gameplay/fighter.cpp
    src/input/input_manager.cpp
    src/file_parser/dat_crypto.cpp
    src/file_parser/dat_bundle.cpp
    src/file_parser/text_codec.cpp
    src/file_parser/x_file_preprocessor.cpp
    src/file_parser/x_model_loader.cpp
    src/maps/stage.cpp
    src/physics/raycast.cpp
    src/render/arena_camera.cpp
    src/render/effect_system.cpp
    src/render/hud.cpp
    src/render/ui_image.cpp
    src/render/video_player.cpp
    src/render/x_model_renderer.cpp)

set(DAYBREAK_HEADERS
    src/assets/asset_manager.h
    src/audio/audio_engine.h
    src/core/scene.h
    src/core/scene_manager.h
    src/core/scenes.h
    src/gameplay/fighter.h
    src/input/input_manager.h
    src/file_parser/dat_crypto.h
    src/file_parser/dat_bundle.h
    src/file_parser/text_codec.h
    src/file_parser/x_file_preprocessor.h
    src/file_parser/x_model_loader.h
    src/maps/stage.h
    src/physics/raycast.h
    src/render/arena_camera.h
    src/render/effect_system.h
    src/render/hud.h
    src/render/ui_image.h
    src/render/video_player.h
    src/render/x_model_renderer.h)

# ----------------------------------------------------------------------------
# Main executable
# ----------------------------------------------------------------------------
add_executable(daybreak WIN32
    ${DAYBREAK_SOURCES}
    ${DAYBREAK_HEADERS})

target_compile_features(daybreak PRIVATE cxx_std_23)

# Make src/ the include root so includes look like
#   #include "file_parser/x_model_loader.h"
#   #include "render/x_model_renderer.h"
target_include_directories(daybreak PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# audio_engine.cpp directly.  Just expose the directory.

# Vendored single-file libraries under src/third_party/ (pl_mpeg).
target_include_directories(daybreak PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/third_party)

target_link_libraries(daybreak PRIVATE daybreak_sdl2 daybreak_sdl2_mixer)

# Direct3D 9 + D3DX (mesh hierarchy, animation controller, skinning)
# headers + libs ship with MinGW-w64 sysroot; d3dx9_43.dll is a runtime dep.
target_link_libraries(daybreak PRIVATE d3d9 d3dx9 dxguid)

# Win32 subsystem entry point (no console window)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_options(daybreak PRIVATE -mwindows)
endif()

# ----------------------------------------------------------------------------
# Post-build: copy SDL2.dll next to the .exe so it runs on Windows
# ----------------------------------------------------------------------------
add_custom_command(TARGET daybreak POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL2_RUNTIME_DLL}
        $<TARGET_FILE_DIR:daybreak>/SDL2.dll
    COMMENT "Copying SDL2.dll next to daybreak.exe")


# Copy SDL2_mixer.dll next to the .exe
add_custom_command(TARGET daybreak POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL2_MIXER_RUNTIME_DLL}
        $<TARGET_FILE_DIR:daybreak>/SDL2_mixer.dll
    COMMENT "Copying SDL2_mixer.dll next to daybreak.exe")

# ----------------------------------------------------------------------------
# Post-build: copy d3dx9_43.dll if fetch_deps.sh managed to grab it
# ----------------------------------------------------------------------------
set(D3DX9_DLL ${DAYBREAK_TOOLS_DIR}/d3dx9/d3dx9_43.dll)
if(EXISTS ${D3DX9_DLL})
    add_custom_command(TARGET daybreak POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${D3DX9_DLL}
            $<TARGET_FILE_DIR:daybreak>/d3dx9_43.dll
        COMMENT "Copying d3dx9_43.dll next to daybreak.exe")
else()
    add_custom_command(TARGET daybreak POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo
            "NOTE: d3dx9_43.dll not in ${DAYBREAK_TOOLS_DIR}/d3dx9/ — runtime .x loading will fail until it is provided."
        COMMENT "Checking for d3dx9_43.dll (optional, runtime only)")
endif()
