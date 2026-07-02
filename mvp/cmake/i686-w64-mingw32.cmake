# CMake toolchain file for cross-compiling from Linux to Windows (32-bit)
# using LLVM-MinGW (clang-based, includes DX9 headers).
#
# Usage:
#   cmake -B build -DCMAKE_TOOLCHAIN_FILE=cmake/i686-w64-mingw32.cmake
#   cmake --build build
#
# Install LLVM-MinGW: https://github.com/mstorsjo/llvm-mingw/releases

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86)

# Adjust this path to your LLVM-Mingw install location
set(LLVM_MINGW_ROOT "/home/z/mingw86/llvm-mingw"
    CACHE PATH "Path to LLVM-MinGW installation")

set(CMAKE_C_COMPILER   ${LLVM_MINGW_ROOT}/bin/i686-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER ${LLVM_MINGW_ROOT}/bin/i686-w64-mingw32-g++)
set(CMAKE_RC_COMPILER  ${LLVM_MINGW_ROOT}/bin/i686-w64-mingw32-windres)

set(CMAKE_FIND_ROOT_PATH ${LLVM_MINGW_ROOT}/i686-w64-mingw32)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
