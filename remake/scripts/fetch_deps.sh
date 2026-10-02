#!/usr/bin/env bash
# =============================================================================
#  fetch_deps.sh — host toolchain and fonts for the SDL3 + WebGPU foundation.
#
#  No sudo / root required. Downloads and extracts (into tools/):
#     - CMake 4.x  + Ninja           (pip wheels, into tools/python)
#     - MinGW-w64 GCC 14 (posix)     (Debian .deb packages, into tools/mingw)
#     - radare2 5.9.8 + runtime libs (optional: RE of the original binary)
#  plus the two font files the foundation's text layer pins (into
#  foundation/third_party/fonts).
#
#  The foundation's own third-party sources (glm, stb, WebGPU-distribution,
#  sdl3webgpu, SDL3 for MinGW) come from foundation/scripts/fetch_deps.sh.
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

mkdir -p "${TOOLS}/debs" "${TOOLS}/mingw"

log()  { printf "\033[1;34m[fetch_deps]\033[0m %s\n" "$*"; }
ok()   { printf "\033[1;32m[fetch_deps]\033[0m %s\n" "$*"; }
warn() { printf "\033[1;33m[fetch_deps]\033[0m %s\n" "$*" >&2; }
die()  { printf "\033[1;31m[fetch_deps]\033[0m %s\n" "$*" >&2; exit 1; }

# ----------------------------------------------------------------------------
# 1) CMake + Ninja via a self-contained venv (no system Python pollution)
#    A system cmake/ninja works too — foundation/build.sh uses whatever is on
#    PATH — so this venv is the pinned fallback rather than a requirement.
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
#    The foundation's Windows target
#    (foundation/cmake/toolchains/mingw-w64-x86_64.cmake) resolves these
#    compilers from PATH, so add ${TOOLS}/mingw/usr/bin to it before building.
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

# ----------------------------------------------------------------------------
# 3) radare2 (for reverse-engineering the original DaybreakDX.exe)
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
# 4) Video: no external dependency. Story-mode video is out of scope by
#    decision (foundation/src/audio/video.h is an explicit stub), so no MPEG
#    decoder is vendored and nothing is fetched here.
# ----------------------------------------------------------------------------

# ----------------------------------------------------------------------------
# 5) CJK text: one OFL Japanese font for the foundation's in-process rasterizer.
#     docs/CJK-TEXT.md decided this (option B): the HUD and the menus need Japanese,
#     the DX9 font path is gone, and the embedded 5x7 ASCII atlas cannot draw it.
#     stb_truetype (vendored, public domain, third_party/stb/stb_truetype.h) rasterizes
#     it at run time, so the only external artefact is the font file itself, and that is
#     fetched here rather than committed: the repo never carries the game's assets, and
#     a 16 MB OFL font is not an exception.
#     The sha256 is pinned because the rasterizer's output is only reproducible against
#     a known font file (src/ui/text.h states the determinism contract, and
#     tests/text_test.cpp hashes the atlas it produces).
# ----------------------------------------------------------------------------
# Under the foundation tree: that is where the demo and tests look for it.
CJK_DIR="${ROOT}/foundation/third_party/fonts"
CJK_FONT="${CJK_DIR}/NotoSansCJKjp-Regular.otf"
CJK_URL="https://github.com/notofonts/noto-cjk/raw/main/Sans/OTF/Japanese/NotoSansCJKjp-Regular.otf"
# sha256 of the file this URL served on 2026-10-02 (Noto CJK Sans JP Regular, OFL 1.1).
CJK_SHA256="68a3fc98800b2a27b371f2fb79991daf3633bd89309d4ffaa6946fd587f375b5"
mkdir -p "${CJK_DIR}"
if [[ ${FORCE} -eq 1 ]] && [[ -f "${CJK_FONT}" ]]; then rm -f "${CJK_FONT}"; fi
if [[ ! -f "${CJK_FONT}" ]]; then
    log "fetching Noto Sans CJK JP (OFL, ~16 MB) for the CJK text layer"
    curl -fL --retry 3 -o "${CJK_FONT}.tmp" "${CJK_URL}" || die "CJK font download failed"
    mv "${CJK_FONT}.tmp" "${CJK_FONT}"
else
    ok "CJK font already present"
fi
# Verify, always: a moved URL or a rewritten upstream file must fail here rather than
# silently change every glyph the HUD draws.
if command -v sha256sum >/dev/null 2>&1; then
    actual="$(sha256sum "${CJK_FONT}" | cut -d' ' -f1)"
    if [[ "${actual}" != "${CJK_SHA256}" ]]; then
        die "CJK font sha256 mismatch: expected ${CJK_SHA256}, got ${actual}"
    fi
    ok "cjk font sha256 verified"
else
    warn "sha256sum unavailable; skipping the font hash check"
fi
ok "cjk font: ${CJK_FONT}"
echo "  note: the font is not committed; src/ui/text.h falls back to the ASCII atlas"
echo "        when it is absent, and tests/text_test.cpp SKIPs."

# ----------------------------------------------------------------------------
# 6) HUD text: the Latin face the DX9 reference actually rendered with.
#     The reference builds its HUD font with D3DXCreateFontA(device, 22, 0, FW_BOLD, ...,
#     "Arial", ...). Under the Wine prefix the parity baseline was banked in, fontconfig
#     resolves "Arial" to Liberation Sans and FW_BOLD selects the Bold face, so that is
#     the file the foundation's HUD has to reproduce: cell 22 -> em 20, and the integer
#     advance table only comes out of em 20 (foundation/tests/hud_text_test.cpp pins it
#     against the banked frames in tests/parity-baseline/). The .deb below is the
#     stablest direct URL for 2.1.5 — the pagure tarball stops at 2.00.1 and the
#     GitHub release carries no binary asset.
# ----------------------------------------------------------------------------
LATIN_FONT="${CJK_DIR}/LiberationSans-Bold.ttf"
LATIN_DEB_URL="https://deb.debian.org/debian/pool/main/f/fonts-liberation/fonts-liberation_2.1.5-3_all.deb"
LATIN_DEB_SHA256="3d5c47480067b9615f6bf9b0eda6eefcab9d837af609827015445e8e759b5b8c"
# sha256 of the TTF inside that .deb (upstream Liberation 2.1.5, SIL OFL 1.1).
LATIN_SHA256="1b5f2da6f4cadce4c05b9ecebe3a6fcd374eb95ae443605e799f4c3287978939"
if [[ ${FORCE} -eq 1 ]] && [[ -f "${LATIN_FONT}" ]]; then rm -f "${LATIN_FONT}"; fi
if [[ ! -f "${LATIN_FONT}" ]]; then
    command -v ar >/dev/null || die "ar (binutils) is needed to unpack the Liberation .deb"
    log "fetching Liberation Sans Bold (OFL, the reference's Arial substitute)"
    tmp="$(mktemp -d)"
    curl -fL --retry 3 -o "${tmp}/lib.deb" "${LATIN_DEB_URL}" || die "Liberation download failed"
    if command -v sha256sum >/dev/null 2>&1; then
        actual="$(sha256sum "${tmp}/lib.deb" | cut -d' ' -f1)"
        [[ "${actual}" == "${LATIN_DEB_SHA256}" ]] || die "Liberation .deb sha256 mismatch: expected ${LATIN_DEB_SHA256}, got ${actual}"
    fi
    ( cd "${tmp}" && ar x lib.deb data.tar.xz \
      && tar xJf data.tar.xz ./usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf ) \
        || die "unpacking the Liberation .deb failed"
    mv "${tmp}/usr/share/fonts/truetype/liberation/LiberationSans-Bold.ttf" "${LATIN_FONT}"
    rm -rf "${tmp}"
else
    ok "Liberation Sans Bold already present"
fi
if command -v sha256sum >/dev/null 2>&1; then
    actual="$(sha256sum "${LATIN_FONT}" | cut -d' ' -f1)"
    [[ "${actual}" == "${LATIN_SHA256}" ]] || die "Liberation font sha256 mismatch: expected ${LATIN_SHA256}, got ${actual}"
    ok "latin font sha256 verified"
fi
ok "latin font: ${LATIN_FONT}"

# ----------------------------------------------------------------------------
# 7) Summary
# ----------------------------------------------------------------------------
echo
ok "All dependencies ready under ${TOOLS}"
echo
echo "Next:"
echo "  PATH=\"${TOOLS}/mingw/usr/bin:\${PATH}\"   # for the foundation's Windows target"
echo "  foundation/scripts/fetch_deps.sh          # third-party sources (glm, stb, webgpu, SDL3)"
echo "  foundation/build.sh linux                 # configure + build + test"
echo "  ./scripts/r2.sh rabin2 -I path/to/DaybreakDX.exe   # reverse-engineering"
