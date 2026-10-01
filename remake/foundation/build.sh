#!/usr/bin/env bash
# Build the foundation for one target.
#   ./build.sh deps     fetch pinned third-party sources (once)
#   ./build.sh linux    native Linux
#   ./build.sh windows  Windows x64 via MinGW-w64
#   ./build.sh web      Emscripten (needs emsdk; set EMSDK to override ~/emsdk)
#   ./build.sh all      deps + all three
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
target=${1:-linux}; shift || true

case "$target" in
deps)    "$here/scripts/fetch_deps.sh" ;;
linux)   cmake -S "$here" -B "$here/build/linux" -GNinja -DCMAKE_BUILD_TYPE=Release "$@"
         cmake --build "$here/build/linux" ;;
windows) sdl3_dir="$here/third_party/SDL3-mingw/x86_64-w64-mingw32"
         cmake -S "$here" -B "$here/build/windows" -GNinja \
             -DCMAKE_TOOLCHAIN_FILE="$here/cmake/toolchains/mingw-w64-x86_64.cmake" \
             -DSDL3_DIR="$sdl3_dir/lib/cmake/SDL3" "$@"
         cmake --build "$here/build/windows"
         # SDL3 is a DLL on Windows, so like the wgpu runtime it has to sit next
         # to the .exe. The GCC runtime is linked statically (toolchain file).
         cmake -E copy_if_different "$sdl3_dir/bin/SDL3.dll" "$here/build/windows/SDL3.dll" ;;
web)     # shellcheck disable=SC1090
         source "${EMSDK:-$HOME/emsdk}/emsdk_env.sh" >/dev/null
         emcmake cmake -S "$here" -B "$here/build/web" -GNinja "$@"
         cmake --build "$here/build/web" ;;
all)     "$0" deps; "$0" linux; "$0" windows; "$0" web ;;
*)       echo "usage: $0 [deps|linux|windows|web|all]" >&2; exit 2 ;;
esac
