cmake_minimum_required(VERSION 3.20)
project(daybreak_foundation LANGUAGES C CXX)

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
    add_link_options(-sUSE_SDL=3 -sASYNCIFY=1 -sALLOW_MEMORY_GROWTH=1 -sSTACK_SIZE=1048576)
else()
    find_package(SDL3 REQUIRED)
    add_subdirectory(third_party/sdl3webgpu)
endif()

add_library(foundation STATIC
    src/platform/platform.cpp
    src/platform/surface.cpp
    src/gpu/gpu.cpp)
target_include_directories(foundation PUBLIC src)
target_link_libraries(foundation PUBLIC webgpu)

if(NOT EMSCRIPTEN)
    target_link_libraries(foundation PUBLIC SDL3::SDL3 sdl3webgpu)
endif()

add_executable(foundation_demo src/main.cpp)
target_link_libraries(foundation_demo PRIVATE foundation)

if(EMSCRIPTEN)
    set_target_properties(foundation_demo PROPERTIES SUFFIX ".html")
else()
    target_copy_webgpu_binaries(foundation_demo)
endif()
