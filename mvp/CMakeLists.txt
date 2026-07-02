cmake_minimum_required(VERSION 3.16)
project(daybreak_mvp C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Sources
set(MVP_SOURCES
    src/main.c
    src/engine_init.c
    src/d3d_init.c
    src/shader_load.c
    src/input_init.c
    src/render_loop.c
    src/scene_title.c
    src/scene_manager.c
    src/scene_stubs.c
    src/dat_archive.c
    src/texture_loader.c
)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Detect toolchain
if(DEFINED CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
elseif(MINGW OR CMAKE_C_COMPILER MATCHES "mingw")
    message(STATUS "Detected MinGW compiler")
    set(MVP_USING_MINGW TRUE)
elseif(MSVC)
    message(STATUS "Detected MSVC compiler")
    set(MVP_USING_MSVC TRUE)
else()
    message(STATUS "Unknown compiler — assuming MinGW-compatible")
    set(MVP_USING_MINGW TRUE)
endif()

# Find DirectX 9 headers
set(DX9_SEARCH_PATHS
    "$ENV{DXSDK_DIR}/Include"
    "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include"
    "C:/Program Files/Microsoft DirectX SDK/Include"
    # MinGW ships with d3d9.h, d3dx9.h, dinput.h built-in
)

find_path(D3D9_INCLUDE_DIR d3d9.h PATHS ${DX9_SEARCH_PATHS})
find_path(D3DX9_INCLUDE_DIR d3dx9.h PATHS ${DX9_SEARCH_PATHS})
find_path(DINPUT_INCLUDE_DIR dinput.h PATHS ${DX9_SEARCH_PATHS})

if(NOT D3D9_INCLUDE_DIR)
    message(FATAL_ERROR
        "d3d9.h not found. Install DirectX 9 SDK or use MinGW (which includes it).")
endif()

message(STATUS "D3D9 headers: ${D3D9_INCLUDE_DIR}")
message(STATUS "D3DX9 headers: ${D3DX9_INCLUDE_DIR}")
message(STATUS "DInput headers: ${DINPUT_INCLUDE_DIR}")

include_directories(${D3D9_INCLUDE_DIR} ${D3DX9_INCLUDE_DIR} ${DINPUT_INCLUDE_DIR})

# Executable (Win32 GUI app)
add_executable(daybreak_mvp WIN32 ${MVP_SOURCES})

# Link libraries
if(MVP_USING_MSVC)
    set(DX9_LIB_PATHS
        "$ENV{DXSDK_DIR}/Lib/x86"
        "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86"
    )
    find_library(D3D9_LIB d3d9 PATHS ${DX9_LIB_PATHS})
    find_library(D3DX9_LIB d3dx9 PATHS ${DX9_LIB_PATHS})
    find_library(DINPUT8_LIB dinput8 PATHS ${DX9_LIB_PATHS})
    find_library(DXGUID_LIB dxguid PATHS ${DX9_LIB_PATHS})

    target_link_libraries(daybreak_mvp PRIVATE
        ${D3D9_LIB} ${D3DX9_LIB} ${DINPUT8_LIB} ${DXGUID_LIB}
        winmm user32 gdi32 ole32
    )
else()
    # MinGW: system libs (headers + libs bundled)
    target_link_libraries(daybreak_mvp PRIVATE
        d3d9 d3dx9 dinput8 dxguid
        winmm user32 gdi32 ole32
    )
endif()

# Copy shaders to build dir (if they exist)
add_custom_command(TARGET daybreak_mvp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:daybreak_mvp>/shaders
    || true  # ignore if shaders dir is empty
)

# Copy data assets to build dir (synthetic BMPs for testing)
add_custom_command(TARGET daybreak_mvp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:daybreak_mvp>/data
    || true  # ignore if data dir is empty
)

message(STATUS "")
message(STATUS "Configuration complete. Build with:")
message(STATUS "  cmake --build build")
message(STATUS "")
