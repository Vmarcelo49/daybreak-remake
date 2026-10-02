cmake_minimum_required(VERSION 3.20)
project(webgpu_spike LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# ---------------------------------------------------------------------------------------
# Spike: does the proposed groundwork actually build and run on every target?
#
#   WEBGPU_BACKEND  WGPU (native default) | DAWN | EMSCRIPTEN | EMDAWNWEBGPU
#   WGPU_VERSION    override the distribution's pin — set below, see SPIKE_WGPU_VERSION
#
# The distribution enforces its own backend/compiler rules (it errors out if you ask for
# WGPU while cross-compiling with emscripten, and vice versa), so the same CMakeLists
# serves both native and web.
# ---------------------------------------------------------------------------------------

# The distribution @ main pins wgpu-native v24; set this to compare against a newer one.
set(SPIKE_WGPU_VERSION "" CACHE STRING "Override pinned wgpu-native version")
if(SPIKE_WGPU_VERSION)
    set(WGPU_VERSION "${SPIKE_WGPU_VERSION}" CACHE STRING "" FORCE)
endif()

if(NOT WEBGPU_BACKEND)
    if(EMSCRIPTEN)
        set(WEBGPU_BACKEND EMDAWNWEBGPU)
    else()
        set(WEBGPU_BACKEND WGPU)
    endif()
endif()

add_subdirectory(extern/webgpu)

if(EMSCRIPTEN)
    # The emscripten SDL3 port supplies the window/canvas and the event loop.
    add_compile_options(-sUSE_SDL=3)
    add_link_options(-sUSE_SDL=3)
else()
    find_package(SDL3 REQUIRED)
    add_subdirectory(extern/sdl3webgpu)
endif()

add_executable(spike src/main.cpp)

if(EMSCRIPTEN)
    target_link_libraries(spike PRIVATE webgpu)
    # Shell file + a canvas to render into; the port supplies the WebGPU bindings.
    # Asyncify lets the same blocking init code run in the browser: awaiting the adapter
    # and device yields to the JS event loop (see waitFor in main.cpp).
    set_target_properties(spike PROPERTIES
        SUFFIX ".html"
        LINK_FLAGS "-sASYNCIFY=1 -sALLOW_MEMORY_GROWTH=1 -sEXPORTED_RUNTIME_METHODS=['ccall','cwrap'] -sSTACK_SIZE=1048576")
else()
    target_link_libraries(spike PRIVATE webgpu SDL3::SDL3 sdl3webgpu)
    target_copy_webgpu_binaries(spike)
endif()

message(STATUS "spike: backend=${WEBGPU_BACKEND} emscripten=${EMSCRIPTEN}")
