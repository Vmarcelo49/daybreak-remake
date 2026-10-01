cmake_minimum_required(VERSION 3.20)

# The version lives in VERSION so that bumping it is a one-line act — and the only
# thing that triggers the multi-target CI build (see .github/workflows).
file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" FOUNDATION_VERSION)
string(STRIP "${FOUNDATION_VERSION}" FOUNDATION_VERSION)
project(daybreak_foundation VERSION ${FOUNDATION_VERSION} LANGUAGES C CXX)

# Multi-platform foundation: SDL3 + WebGPU (webgpu.h), built for Linux, Windows
# (MinGW cross-compile) and the web (Emscripten) from this one file.
#
#   linux    cmake -B build/linux   -GNinja
#   windows  cmake -B build/windows -GNinja -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/mingw-w64-x86_64.cmake
#   web      emcmake cmake -B build/web -GNinja
#
# The WebGPU implementation is picked per target by third_party/webgpu (the
# WebGPU-distribution project): wgpu-native natively, emdawnwebgpu on the web.

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE AND NOT EMSCRIPTEN)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif()

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/third_party/webgpu/CMakeLists.txt")
    message(FATAL_ERROR "third_party/ is empty — run scripts/fetch_deps.sh first")
endif()
add_subdirectory(third_party/webgpu)

if(EMSCRIPTEN)
    # SDL3 is supplied by the Emscripten port; it also owns the <canvas>.
    add_compile_options(-sUSE_SDL=3)
    add_link_options(-sUSE_SDL=3 -sASYNCIFY=1 -sALLOW_MEMORY_GROWTH=1 -sSTACK_SIZE=1048576 -sFETCH=1)
    # Local game data can be mounted at /assets for browser verification. Both stay
    # local-only: the data is copyrighted and build/ is ignored, so this never changes
    # what the plain web build contains.
    set(FOUNDATION_WEB_ASSETS "" CACHE PATH "Local directory preloaded as /assets in the web build")
    set(FOUNDATION_WEB_ASSET "" CACHE STRING "Single asset argument injected on web, e.g. --character=/assets/akane:0")
    if(FOUNDATION_WEB_ASSETS)
        add_link_options("SHELL:--preload-file ${FOUNDATION_WEB_ASSETS}@/assets")
    endif()
else()
    find_package(SDL3 REQUIRED)
    add_subdirectory(third_party/sdl3webgpu)
endif()

# glm is the asset layer's only third-party dependency (xmodel.h works in mat4/vec3).
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/third_party/glm")

# The Daybreak asset layer: .X/.cnv decoding and scene assembly, unchanged from the
# backend it was proved on.
add_library(foundation_assets STATIC src/assets/assets.cpp)
target_include_directories(foundation_assets PUBLIC src/assets)
target_link_libraries(foundation_assets PUBLIC glm)

add_library(foundation STATIC
    src/platform/platform.cpp
    src/platform/surface.cpp
    src/platform/web_pack.cpp
    src/gpu/gpu.cpp)
target_include_directories(foundation PUBLIC src)
target_link_libraries(foundation PUBLIC webgpu)

if(NOT EMSCRIPTEN)
    target_link_libraries(foundation PUBLIC SDL3::SDL3 sdl3webgpu)
endif()

# The scene renderer is the one layer above gpu/ that also needs the asset layer: it
# builds the pipelines raw WebGPU requires and consumes xm::Vertex / xm::DrawUniform.
add_library(foundation_render STATIC src/render/scene_renderer.cpp)
target_link_libraries(foundation_render PUBLIC foundation foundation_assets)

# The 2D/UI layer: sprite batch, bitmap font, HUD composition, diagnostics. Same
# shape as foundation_render; verified headless before wiring (docs/UI-VERIFY.md).
add_library(foundation_ui STATIC
    src/ui/sprite.cpp
    src/ui/font.cpp
    src/ui/hud.cpp
    src/ui/fallback.cpp)
target_include_directories(foundation_ui PUBLIC src)
target_link_libraries(foundation_ui PUBLIC foundation)

# Media/input contracts and tables. Header-only by design (they unit-test
# anywhere), so this library is one TU of static_asserts against the real SDL3
# headers: the tables cannot drift from SDL3 without failing every target build.
add_library(foundation_media STATIC src/input/pin_tables.cpp src/audio/audio_engine.cpp
                          src/input/input_backend.cpp)
target_include_directories(foundation_media PUBLIC src)
target_include_directories(foundation_media PRIVATE third_party/stb)
if(NOT EMSCRIPTEN)
    target_link_libraries(foundation_media PUBLIC SDL3::SDL3)
endif()

# Game-facing interfaces: header-only (glm+std, plus hud_bridge.h over ui/), so
# this library is a check TU that forces every target to compile them — the
# same rationale as the pin TU above.
add_library(foundation_game STATIC src/game/game_check.cpp)
target_include_directories(foundation_game PUBLIC src)
target_link_libraries(foundation_game PUBLIC foundation_ui glm)

add_executable(foundation_demo src/main.cpp)
target_link_libraries(foundation_demo PRIVATE foundation_render foundation_ui foundation_media foundation_game)

if(EMSCRIPTEN)
    set_target_properties(foundation_demo PROPERTIES SUFFIX ".html")
    # argv never reaches wasm, so a local verification build can name its one asset here.
    # The plain web build leaves this empty and keeps the triangle demo.
    if(FOUNDATION_WEB_ASSET)
        target_compile_definitions(foundation_demo PRIVATE "FOUNDATION_WEB_ASSET=\"${FOUNDATION_WEB_ASSET}\"")
    endif()
else()
    target_copy_webgpu_binaries(foundation_demo)
endif()
