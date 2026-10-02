#!/usr/bin/env bash
# Fetch the pinned third-party sources. Revisions are pinned deliberately: the
# WebGPU-distribution README asks for a tag or commit rather than a branch tip,
# and webgpu.h itself is not yet a frozen API.
set -euo pipefail
here=$(cd "$(dirname "$0")/.." && pwd)
tp="$here/third_party"
mkdir -p "$tp"

WEBGPU_DIST_COMMIT=17dcd42a7683355e7a40ac4e97e77f36dff5b5ab   # 2025-09-03
SDL3WEBGPU_COMMIT=4fa9d70935e41c075f664b231ee10a64262a8ac7      # 2025-05-01
SDL3_VERSION=3.4.16
GLM_VERSION=1.0.1
STB_COMMIT=2c980bb59875b0d32144a71867fbdebb2f77cd20   # nothings/stb master, v1.22 stb_vorbis

fetch_zip() {  # url destdir name
    local url=$1 dest=$2 name=$3 tmp
    [ -e "$dest" ] && { echo "  $name: already present"; return; }
    tmp=$(mktemp -d)
    echo "  $name: fetching"
    curl -fsSL "$url" -o "$tmp/a.zip"
    unzip -q "$tmp/a.zip" -d "$tmp"
    mv "$tmp"/*/ "$dest"
    rm -rf "$tmp"
}

fetch_zip "https://github.com/g-truc/glm/archive/refs/tags/${GLM_VERSION}.zip" "$tp/glm" "glm ${GLM_VERSION}"

# stb_vorbis.c and stb_truetype.h are single files, not zips: fetch the pinned raw blobs
# directly. stb_truetype.h is a hard requirement (ui/text.cpp includes it and CMake puts
# third_party/stb on the include path), and it used to be fetched by nothing: the build
# only succeeded where the header happened to already exist, so a fresh checkout failed.
for f in stb_vorbis.c stb_truetype.h; do
    if [ ! -e "$tp/stb/$f" ]; then
        echo "  $f (pinned ${STB_COMMIT}): fetching"
        mkdir -p "$tp/stb"
        curl -fsSL "https://raw.githubusercontent.com/nothings/stb/${STB_COMMIT}/$f" -o "$tp/stb/$f"
    fi
done
fetch_zip "https://github.com/eliemichel/WebGPU-distribution/archive/${WEBGPU_DIST_COMMIT}.zip" "$tp/webgpu" "WebGPU-distribution"
fetch_zip "https://github.com/eliemichel/sdl3webgpu/archive/${SDL3WEBGPU_COMMIT}.zip" "$tp/sdl3webgpu" "sdl3webgpu"

# SDL3 for the MinGW cross-build (the native Linux build uses the system SDL3).
if [ ! -e "$tp/SDL3-mingw" ]; then
    echo "  SDL3 $SDL3_VERSION (MinGW): fetching"
    tmp=$(mktemp -d)
    curl -fsSL "https://github.com/libsdl-org/SDL/releases/download/release-${SDL3_VERSION}/SDL3-devel-${SDL3_VERSION}-mingw.tar.gz" -o "$tmp/sdl3.tar.gz"
    tar -xzf "$tmp/sdl3.tar.gz" -C "$tmp"
    mv "$tmp"/SDL3-*/ "$tp/SDL3-mingw"
    rm -rf "$tmp"
fi
echo "deps ready in $tp"
