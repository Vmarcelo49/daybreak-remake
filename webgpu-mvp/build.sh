#!/usr/bin/env bash
# build.sh — build the loader tool and the WebGPU render test.
#
#   ./build.sh                 # host build (needs: ./tools/fetch_deps.sh linux)
#   ./build.sh windows         # MinGW cross build (needs: ./tools/fetch_deps.sh windows)
#   ./build.sh both
#
# The loader (tools/xmodel_tool) needs nothing but GLM. The render test
# (tools/wgpu_smoke) additionally needs wgpu-native, and must run with model.wgsl
# reachable from the working directory.
set -euo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${root}"
mkdir -p build

mode="${1:-host}"
CXXFLAGS="-std=c++17 -O2 -Wall -Wextra -Wno-unused-parameter"
glm_inc="third_party/glm"

build_host() {
    local inc="${glm_inc}"
    [ -d "${inc}" ] || inc="/usr/include"
    echo "[host] xmodel_tool"
    g++ ${CXXFLAGS} -I"${inc}" tools/xmodel_tool.cpp -o build/xmodel_tool
    echo "[host] verify_textures"
    g++ ${CXXFLAGS} -I"${inc}" tools/verify_textures.cpp -o build/verify_textures

    if [ -d third_party/wgpu-linux/include ]; then
        echo "[host] wgpu_smoke (+ wgpu-native)"
        g++ ${CXXFLAGS} -I"${inc}" -Ithird_party/wgpu-linux/include \
            tools/wgpu_smoke.cpp -o build/wgpu_smoke \
            -Lthird_party/wgpu-linux/lib -lwgpu_native \
            -Wl,-rpath,"${root}/third_party/wgpu-linux/lib"
    else
        echo "[host] skipping wgpu_smoke (run: ./tools/fetch_deps.sh linux)"
    fi
}

build_windows() {
    local cxx=x86_64-w64-mingw32-g++
    command -v "${cxx}" >/dev/null 2>&1 || { echo "no ${cxx}; skipping"; return; }
    local inc="${glm_inc}"
    [ -d "${inc}" ] || inc="/usr/include"
    echo "[windows] xmodel_tool.exe"
    # -static: the MinGW posix threading model otherwise wants libwinpthread-1.dll
    # at runtime, which is not present on a plain Windows box.
    "${cxx}" ${CXXFLAGS} -I"${inc}" tools/xmodel_tool.cpp -o build/xmodel_tool.exe -static
    echo "[windows] verify_textures.exe"
    "${cxx}" ${CXXFLAGS} -I"${inc}" tools/verify_textures.cpp -o build/verify_textures.exe -static

    if [ -d third_party/wgpu-windows/include ]; then
        echo "[windows] wgpu_smoke.exe (+ wgpu_native.dll)"
        # Link the import library, not libwgpu_native.a: the static Rust archive
        # needs a pile of Windows system libs and bloats the exe by ~37 MB.
        "${cxx}" ${CXXFLAGS} -I"${inc}" -Ithird_party/wgpu-windows/include \
            tools/wgpu_smoke.cpp -o build/wgpu_smoke.exe \
            third_party/wgpu-windows/lib/libwgpu_native.dll.a -static
        cp -f third_party/wgpu-windows/lib/wgpu_native.dll build/
    else
        echo "[windows] skipping wgpu_smoke.exe (run: ./tools/fetch_deps.sh windows)"
    fi
}

case "${mode}" in
    host)    build_host ;;
    windows) build_windows ;;
    both)    build_host; build_windows ;;
    *) echo "usage: ./build.sh [host|windows|both]" >&2; exit 2 ;;
esac

echo
echo "built:"
ls -1 build/ 2>/dev/null | sed 's/^/  /' || true
echo
echo "try:  ./build/xmodel_tool stats <model.x>"
echo "      ./build/xmodel_tool sceneall <assetRoot>            # stage/character/weapon assembly"
echo "      ./build/xmodel_tool dtcheck <model.x> [anim]        # frame-rate independence"
echo "      ./build/verify_textures <assetRoot>                 # every .cnv decodes, refs resolve"
echo "      ./build/wgpu_smoke --character=<base>/<name>:<c> --out=/tmp/frame.ppm"
echo "      ./build/wgpu_smoke --stage=<stageDir> --camera=player --out=/tmp/frame.ppm"
echo "      (wgpu_smoke needs model.wgsl in the working directory)"
