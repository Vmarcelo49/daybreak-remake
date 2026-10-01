#!/usr/bin/env bash
# =============================================================================
#  fetch_deps.sh — bootstrap the daybreak cross-compile toolchain on Linux.
#
#  No sudo / root required. Downloads and extracts (into tools/):
#     - CMake 4.x  + Ninja           (pip wheels, into tools/python)
#     - MinGW-w64 GCC 14 (posix)     (Debian .deb packages, into tools/mingw)
#     - SDL2 2.30.10 MinGW dev zip   (into tools/SDL2-2.30.10)
#     - d3dx9_43.dll x64             (from a mirror, into tools/d3dx9)
#
#  Usage:
#     ./scripts/fetch_deps.sh            # download everything missing
#     ./scripts/fetch_deps.sh --force    # re-download even if present
#
#  Re-runnable: skips components that are already present.
# =============================================================================
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
TOOLS="${ROOT}/tools"
FORCE=0
if [[ "${1:-}" == "--force" || "${1:-}" == "-f" ]]; then FORCE=1; fi

mkdir -p "${TOOLS}/debs" "${TOOLS}/mingw" "${TOOLS}/d3dx9"
mkdir -p "${ROOT}/third_party"

log()  { printf "\033[1;34m[fetch_deps]\033[0m %s\n" "$*"; }
ok()   { printf "\033[1;32m[fetch_deps]\033[0m %s\n" "$*"; }
warn() { printf "\033[1;33m[fetch_deps]\033[0m %s\n" "$*" >&2; }
die()  { printf "\033[1;31m[fetch_deps]\033[0m %s\n" "$*" >&2; exit 1; }

have() { [[ -e "$1" ]]; }

# ----------------------------------------------------------------------------
# 1) CMake + Ninja via a self-contained venv (no system Python pollution)
# ----------------------------------------------------------------------------
VENV="${TOOLS}/python"
if [[ ${FORCE} -eq 1 ]] && [[ -d "${VENV}" ]]; then rm -rf "${VENV}"; fi

if [[ ! -d "${VENV}" ]]; then
    log "creating local Python venv at ${VENV}"
    python3 -m venv "${VENV}"
    "${VENV}/bin/pip" install --quiet --upgrade pip
    "${VENV}/bin/pip" install --quiet cmake ninja
else
    if ! "${VENV}/bin/cmake" --version >/dev/null 2>&1; then
        log "venv exists but cmake missing — installing"
        "${VENV}/bin/pip" install --quiet cmake ninja
    fi
fi
ok "cmake:  $(${VENV}/bin/cmake --version | head -1)"
ok "ninja:  $(${VENV}/bin/ninja --version)"

# ----------------------------------------------------------------------------
# 2) MinGW-w64 GCC 14 (POSIX, x86-64) from Debian packages
# ----------------------------------------------------------------------------
MINGW_BIN="${TOOLS}/mingw/usr/bin/x86_64-w64-mingw32-g++-posix"
if [[ ${FORCE} -eq 1 ]] && [[ -d "${TOOLS}/mingw/usr" ]]; then rm -rf "${TOOLS}/mingw/usr"; fi

if [[ ! -x "${MINGW_BIN}" ]]; then
    log "downloading MinGW-w64 .deb packages"
    cd "${TOOLS}/debs"
    apt-get download \
        binutils-mingw-w64-x86-64 \
        gcc-mingw-w64-base \
        gcc-mingw-w64-x86-64-posix \
        gcc-mingw-w64-x86-64-posix-runtime \
        g++-mingw-w64-x86-64-posix \
        mingw-w64-common \
        mingw-w64-x86-64-dev \
        mingw-w64-tools \
        libz-mingw-w64 || die "apt-get download failed (need network + apt-cache populated)"

    log "extracting MinGW-w64 into ${TOOLS}/mingw"
    for deb in *.deb; do dpkg -x "$deb" "${TOOLS}/mingw"; done
    cd "${ROOT}"
else
    ok "MinGW-w64 already present"
fi
ok "mingw:  $(${MINGW_BIN} --version | head -1)"

# Sanity: confirm DX9 headers + libs ship with MinGW sysroot
SYSROOT="${TOOLS}/mingw/usr/x86_64-w64-mingw32"
[[ -f "${SYSROOT}/include/d3d9.h"   ]] || die "d3d9.h missing in MinGW sysroot"
[[ -f "${SYSROOT}/lib/libd3d9.a"   ]] || die "libd3d9.a missing"
[[ -f "${SYSROOT}/lib/libd3dx9.a"  ]] || die "libd3dx9.a missing"
ok "dx9:    headers + libs OK"

# ----------------------------------------------------------------------------
# 3) SDL2 2.30.10 MinGW dev package (official release)
# ----------------------------------------------------------------------------
SDL2_VER="2.30.10"
SDL2_ROOT="${TOOLS}/SDL2-${SDL2_VER}"
SDL2_ZIP="${TOOLS}/SDL2-devel-${SDL2_VER}-mingw.zip"
SDL2_URL="https://github.com/libsdl-org/SDL/releases/download/release-${SDL2_VER}/SDL2-devel-${SDL2_VER}-mingw.zip"

if [[ ${FORCE} -eq 1 ]] && [[ -d "${SDL2_ROOT}" ]]; then rm -rf "${SDL2_ROOT}"; fi
if [[ ! -d "${SDL2_ROOT}" ]]; then
    if [[ ! -f "${SDL2_ZIP}" ]]; then
        log "downloading SDL2 ${SDL2_VER} MinGW dev"
        curl -fL --retry 3 -o "${SDL2_ZIP}" "${SDL2_URL}" || die "SDL2 download failed"
    fi
    log "extracting SDL2"
    (cd "${TOOLS}" && unzip -q -o "$(basename "${SDL2_ZIP}")")
fi
[[ -f "${SDL2_ROOT}/x86_64-w64-mingw32/include/SDL2/SDL.h" ]] || die "SDL2 headers missing"
ok "sdl2:   ${SDL2_ROOT}"

# ----------------------------------------------------------------------------
# 4) d3dx9_43.dll (x64) — required at RUNTIME for D3DXLoadMeshHierarchyFromX.
#    The MinGW sysroot ships the import lib (libd3dx9.a), but not the DLL.
#    We pull it from a known mirror; if every mirror fails, instruct the
#    user to install the DirectX End-User Runtime (June 2010).
# ----------------------------------------------------------------------------
D3DX9_DLL="${TOOLS}/d3dx9/d3dx9_43.dll"
if [[ ${FORCE} -eq 1 ]] && [[ -f "${D3DX9_DLL}" ]]; then rm -f "${D3DX9_DLL}"; fi

if [[ ! -f "${D3DX9_DLL}" ]]; then
    log "fetching d3dx9_43.dll (x64) — runtime dep for .x loader"

    # Mirror 1: DirectX redist DLLs hosted on a public GitHub release.
    D3DX9_URLS=(
        "https://github.com/sneha-belur/d3dx9/releases/download/v0.1/d3dx9_43_x64.dll"
        "https://raw.githubusercontent.com/MichaelMoroz/CppD3D11Tutorial/main/redist/d3dx9_43_x64.dll"
    )
    fetched=0
    for url in "${D3DX9_URLS[@]}"; do
        if curl -fL --retry 2 -o "${D3DX9_DLL}.tmp" "${url}" 2>/dev/null; then
            mv "${D3DX9_DLL}.tmp" "${D3DX9_DLL}"
            fetched=1
            break
        fi
    done

    if [[ ${fetched} -eq 0 ]]; then
        warn "Could not auto-fetch d3dx9_43.dll from a mirror."
        warn "On a Windows machine, install the DirectX End-User Runtime (June 2010)"
        warn "  → https://www.microsoft.com/en-us/download/details.aspx?id=8109"
        warn "or copy d3dx9_43.dll (x64) into ${TOOLS}/d3dx9/ manually."
        warn "The build will still succeed; only the runtime needs the DLL."
    else
        ok "d3dx9:  ${D3DX9_DLL}"
    fi
else
    ok "d3dx9 already present: ${D3DX9_DLL}"
fi

# ----------------------------------------------------------------------------
# 5) radare2 (for reverse-engineering the original DaybreakDX.exe)
#    Optional — only needed when analyzing the original binary.  Installed
#    from the Ubuntu archive (Debian trixie doesn't ship radare2) plus the
#    runtime libs (libcapstone5, libzip5, libmagic1t64, libxxhash0, liblz4-1).
# ----------------------------------------------------------------------------
R2_BIN="${TOOLS}/r2/usr/bin/r2"
if [[ ${FORCE} -eq 1 ]] && [[ -d "${TOOLS}/r2/usr" ]]; then rm -rf "${TOOLS}/r2/usr"; fi

if [[ ! -x "${R2_BIN}" ]]; then
    log "downloading radare2 5.9.8 (Ubuntu archive) + runtime deps"
    R2_DEB_DIR="${TOOLS}/.r2-debs"
    mkdir -p "${R2_DEB_DIR}"
    cd "${R2_DEB_DIR}"
    curl -fsSL -o r2.deb      "http://archive.ubuntu.com/ubuntu/pool/universe/r/radare2/radare2_5.9.8+dfsg-2_amd64.deb"
    curl -fsSL -o libr2.deb   "http://archive.ubuntu.com/ubuntu/pool/universe/r/radare2/libradare2-5.0.0t64_5.9.8+dfsg-2_amd64.deb"
    curl -fsSL -o r2-common.deb "http://archive.ubuntu.com/ubuntu/pool/universe/r/radare2/libradare2-common_5.9.8+dfsg-2_all.deb"
    apt-get download libcapstone5 libzip5 libmagic1t64 libmagic-mgc libxxhash0 liblz4-1 2>/dev/null
    log "extracting radare2 into ${TOOLS}/r2"
    mkdir -p "${TOOLS}/r2"
    for d in *.deb; do dpkg -x "$d" "${TOOLS}/r2"; done
    cd "${ROOT}"

    # Create unversioned .so symlinks (r2 needs libr_*.so, packages ship only .so.5)
    R2_LIB="${TOOLS}/r2/usr/lib/x86_64-linux-gnu"
    for f in "${R2_LIB}"/libr_*.so.5; do
        base="${f%.so.*}"
        [[ ! -e "${base}.so" ]] && ln -sf "$(basename "$f")" "${base}.so"
    done
else
    ok "radare2 already present"
fi
# r2 needs LD_LIBRARY_PATH to find libr_*.so and friends; the wrapper
# script (scripts/r2.sh) sets it, but for the version probe here we set
# it inline.
R2_LIB_DIR="${TOOLS}/r2/usr/lib/x86_64-linux-gnu"
R2_VERSION="$(LD_LIBRARY_PATH="${R2_LIB_DIR}:${LD_LIBRARY_PATH:-}" "${R2_BIN}" -v 2>/dev/null | head -1)"
ok "radare2: ${R2_VERSION}"

# ----------------------------------------------------------------------------
# 6) SDL2_mixer + libvorbis (audio engine)
#    SDL2_mixer is SDL2's audio mixer — supports WAV, OGG (via libvorbis),
#    MP3, MOD.  We grab the MinGW dev package (matches our SDL2 2.30.10)
#    and the libvorbis + libogg runtime DLLs from xiph.org.
# ----------------------------------------------------------------------------
SDL_MIXER_VER="2.8.0"
SDL_MIXER_DIR="${TOOLS}/SDL2_mixer-${SDL_MIXER_VER}"
SDL_MIXER_ZIP="${TOOLS}/SDL2_mixer-devel-${SDL_MIXER_VER}-mingw.zip"
SDL_MIXER_URL="https://github.com/libsdl-org/SDL_mixer/releases/download/release-${SDL_MIXER_VER}/SDL2_mixer-devel-${SDL_MIXER_VER}-mingw.zip"

if [[ ! -d "${SDL_MIXER_DIR}" ]]; then
    log "downloading SDL2_mixer ${SDL_MIXER_VER} MinGW dev"
    curl -fsSL -o "${SDL_MIXER_ZIP}" "${SDL_MIXER_URL}" \
        || die "SDL2_mixer download failed"
    (cd "${TOOLS}" && unzip -q -o "$(basename "${SDL_MIXER_ZIP}")")
    rm -f "${SDL_MIXER_ZIP}"
else
    ok "SDL2_mixer already present"
fi
ok "sdl_mixer: ${SDL_MIXER_DIR}"

# libvorbis + libogg runtime DLLs (downloaded from xiph.org).
# SDL2_mixer dynamically loads these at runtime if they're in the PATH.
VORBIS_DIR="${TOOLS}/libvorbis-mingw"
mkdir -p "${VORBIS_DIR}/lib"
if [[ ! -f "${VORBIS_DIR}/lib/libvorbis-0.dll" ]]; then
    log "downloading libvorbis + libogg runtime DLLs (xiph.org)"
    curl -fsSL -o /tmp/libvorbis-win.zip \
        "https://downloads.xiph.org/releases/vorbis/libvorbis-1.3.7-win.zip" || true
    if [[ -f /tmp/libvorbis-win.zip ]]; then
        mkdir -p /tmp/libvorbis-extract
        (cd /tmp/libvorbis-extract && unzip -q -o /tmp/libvorbis-win.zip)
        find /tmp/libvorbis-extract -name "*.dll" -exec cp {} "${VORBIS_DIR}/lib/" \;
        rm -rf /tmp/libvorbis-extract /tmp/libvorbis-win.zip
    fi
    curl -fsSL -o /tmp/libogg-win.zip \
        "https://downloads.xiph.org/releases/ogg/libogg-1.3.5-win.zip" || true
    if [[ -f /tmp/libogg-win.zip ]]; then
        mkdir -p /tmp/libogg-extract
        (cd /tmp/libogg-extract && unzip -q -o /tmp/libogg-win.zip)
        find /tmp/libogg-extract -name "*.dll" -exec cp {} "${VORBIS_DIR}/lib/" \;
        rm -rf /tmp/libogg-extract /tmp/libogg-win.zip
    fi
else
    ok "libvorbis DLLs already present"
fi
ok "libvorbis: ${VORBIS_DIR}/lib/"

# ----------------------------------------------------------------------------
# 7) Video playback: no external dependency.
#    MPEG1/MP2 decoding is handled by pl_mpeg (MIT, single-file C library)
#    vendored at src/third_party/pl_mpeg.h. Previously this step downloaded
#    the FFmpeg shared build (~30 MB of DLLs); that is no longer needed.
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# 8) Summary
# ----------------------------------------------------------------------------
echo
ok "All dependencies ready under ${TOOLS}"
echo
echo "Next:"
echo "  ./build.sh                # configure + build daybreak.exe"
echo "  ls -lh build/daybreak.exe build/SDL2.dll build/d3dx9_43.dll"
echo "  ./scripts/r2.sh rabin2 -I path/to/DaybreakDX.exe   # reverse-engineering"
echo "  ls third_party/           # miniaudio.h + stb_vorbis.c"
echo "  ls src/third_party/       # pl_mpeg.h (video decoder)"
