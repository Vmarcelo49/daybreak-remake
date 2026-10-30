# Windows x64 via MinGW-w64, cross-compiled from Linux — the same pipeline the
# rest of the project uses.
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)
set(CMAKE_C_COMPILER   ${TOOLCHAIN_PREFIX}-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
set(CMAKE_RC_COMPILER  ${TOOLCHAIN_PREFIX}-windres)

# Pull the GCC runtime in statically. Otherwise every .exe needs libgcc_s_seh-1.dll,
# libstdc++-6.dll and libwinpthread-1.dll beside it, and those live in the MinGW
# sysroot, not in the SDL3/wgpu payload the build copies next to the binary.
set(CMAKE_EXE_LINKER_FLAGS_INIT "-static")

set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
