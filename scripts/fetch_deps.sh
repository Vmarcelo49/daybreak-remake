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
PL_MPEG_COMMIT=c871f2be022ece7ef4f64230b4fb8e1fb9eb6023   # phoboslab/pl_mpeg master, 2025-12-30

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

# pl_mpeg (issue #40): MPEG-1 video + MP2 audio + MPEG-PS demux in one MIT header, the
# decoder behind the opening/staff-roll movies. Same single-raw-blob pattern as stb above;
# the upstream repository has no tags, so the pin is the commit the file's own README
# revision matched when this was written. Only the header is fetched — pl_mpeg.c is the
# same file with PL_MPEG_IMPLEMENTATION defined, and src/movie/movie_player.cpp is the one
# translation unit in this tree that defines it.
if [ ! -e "$tp/pl_mpeg/pl_mpeg.h" ]; then
    echo "  pl_mpeg.h (pinned ${PL_MPEG_COMMIT}): fetching"
    mkdir -p "$tp/pl_mpeg"
    curl -fsSL "https://raw.githubusercontent.com/phoboslab/pl_mpeg/${PL_MPEG_COMMIT}/pl_mpeg.h" \
        -o "$tp/pl_mpeg/pl_mpeg.h"
fi
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

# The fonts are fetched rather than committed, and their hashes are pinned because the
# rasterizer's output is only reproducible against a known file (src/ui/text.h).
verify_sha256() {  # file expected
    [ "$(sha256sum "$1" | cut -d' ' -f1)" = "$2" ] || { echo "sha256 mismatch: $1" >&2; exit 1; }
}
mkdir -p "$tp/fonts"

# Noto Sans CJK JP (OFL 1.1): the Japanese fallback of the caption chain (D7).
CJK_FONT="$tp/fonts/NotoSansCJKjp-Regular.otf"
CJK_SHA256=68a3fc98800b2a27b371f2fb79991daf3633bd89309d4ffaa6946fd587f375b5
if [ ! -e "$CJK_FONT" ]; then
    echo "  Noto Sans CJK JP: fetching"
    curl -fsSL --retry 3 -o "$CJK_FONT.tmp" \
        "https://github.com/notofonts/noto-cjk/raw/main/Sans/OTF/Japanese/NotoSansCJKjp-Regular.otf"
    mv "$CJK_FONT.tmp" "$CJK_FONT"
fi
verify_sha256 "$CJK_FONT" "$CJK_SHA256"

# Noto Sans CJK JP Bold (OFL 1.1): the story dialogue's stand-in for ＭＳ ゴシック bold.
STORY_FONT="$tp/fonts/NotoSansCJKjp-Bold.otf"
STORY_SHA256=e53dcb0dcb2922e45d01aae1ebd2f382bb81d4229b18b6b883bd170678af1f76
if [ ! -e "$STORY_FONT" ]; then
    echo "  Noto Sans CJK JP Bold: fetching"
    curl -fsSL --retry 3 -o "$STORY_FONT.tmp" \
        "https://github.com/notofonts/noto-cjk/raw/main/Sans/OTF/Japanese/NotoSansCJKjp-Bold.otf"
    mv "$STORY_FONT.tmp" "$STORY_FONT"
fi
verify_sha256 "$STORY_FONT" "$STORY_SHA256"

# Liberation Sans Bold (OFL 1.1): the Arial substitute tests/hud_text_test.cpp pins against
# the banked DX9 frames. The upstream release has no binary asset, so it comes from the .deb.
LATIN_FONT="$tp/fonts/LiberationSans-Bold.ttf"
LATIN_DEB_SHA256=3d5c47480067b9615f6bf9b0eda6eefcab9d837af609827015445e8e759b5b8c
LATIN_SHA256=1b5f2da6f4cadce4c05b9ecebe3a6fcd374eb95ae443605e799f4c3287978939
if [ ! -e "$LATIN_FONT" ]; then
    echo "  Liberation Sans Bold: fetching"
    tmp=$(mktemp -d)
    curl -fsSL --retry 3 -o "$tmp/lib.deb" \
        "https://deb.debian.org/debian/pool/main/f/fonts-liberation/fonts-liberation_2.1.5-3_all.deb"
    verify_sha256 "$tmp/lib.deb" "$LATIN_DEB_SHA256"
    (cd "$tmp" && ar x lib.deb data.tar.xz \
        && tar xJf data.tar.xz ./usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf)
    mv "$tmp/usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf" "$LATIN_FONT"
    rm -rf "$tmp"
fi
verify_sha256 "$LATIN_FONT" "$LATIN_SHA256"

echo "deps ready in $tp"
