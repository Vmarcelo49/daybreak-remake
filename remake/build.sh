#!/usr/bin/env bash
# =============================================================================
#  build.sh — configure + build daybreak.exe (cross-compile Linux → Windows x64)
#
#  Prerequisites: ./scripts/fetch_deps.sh must have been run once.
#
#  Usage:
#     ./build.sh                 # Release build into build/
#     ./build.sh Debug           # Debug build
#     ./build.sh --clean         # wipe build/ first
#     BUILD_TYPE=RelWithDebInfo ./build.sh
# =============================================================================
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="${SCRIPT_DIR}"
TOOLS="${ROOT}/tools"
BUILD_DIR="${ROOT}/build"

# ---- build type ------------------------------------------------------------
BUILD_TYPE="${BUILD_TYPE:-Release}"
CLEAN=0
for arg in "$@"; do
    case "${arg}" in
        Debug|Release|RelWithDebInfo|MinSizeRel) BUILD_TYPE="${arg}" ;;
        --clean|-c) CLEAN=1 ;;
        *) ;;
    esac
done

# ---- venv (cmake + ninja) --------------------------------------------------
VENV="${TOOLS}/python"
if [[ ! -x "${VENV}/bin/cmake" ]]; then
    echo "[build] cmake not found — run ./scripts/fetch_deps.sh first" >&2
    exit 1
fi
export PATH="${VENV}/bin:${PATH}"

# ---- MinGW -----------------------------------------------------------------
MINGW_BIN="${TOOLS}/mingw/usr/bin"
if [[ ! -x "${MINGW_BIN}/x86_64-w64-mingw32-g++-posix" ]]; then
    echo "[build] MinGW not found — run ./scripts/fetch_deps.sh first" >&2
    exit 1
fi
export PATH="${MINGW_BIN}:${PATH}"

# ---- clean -----------------------------------------------------------------
if [[ ${CLEAN} -eq 1 ]] && [[ -d "${BUILD_DIR}" ]]; then
    echo "[build] cleaning ${BUILD_DIR}"
    rm -rf "${BUILD_DIR}"
fi

# ---- configure -------------------------------------------------------------
echo "[build] configure + build (${BUILD_TYPE})"
cmake -S "${ROOT}" -B "${BUILD_DIR}" -G Ninja \
    -DCMAKE_TOOLCHAIN_FILE="${ROOT}/cmake/toolchain-mingw-x86_64.cmake" \
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE}"

cmake --build "${BUILD_DIR}" --parallel

# ---- summary ---------------------------------------------------------------
echo
echo "[build] artifacts in ${BUILD_DIR}:"
ls -lh "${BUILD_DIR}/daybreak.exe" "${BUILD_DIR}/SDL2.dll"

if [[ -f "${TOOLS}/d3dx9/d3dx9_43.dll" ]]; then
    cp -f "${TOOLS}/d3dx9/d3dx9_43.dll" "${BUILD_DIR}/"
    echo "[build] copied d3dx9_43.dll"
else
    echo
    echo "[build] WARNING: d3dx9_43.dll not found."
    echo "        Runtime .x loading will fail until it is placed next to daybreak.exe."
    echo "        Get it via the DirectX End-User Runtime (June 2010):"
    echo "          https://www.microsoft.com/en-us/download/details.aspx?id=8109"
fi

# ---- package ---------------------------------------------------------------
# Creates a zip with the build output (daybreak.exe + all DLLs) AND the source
# code (without build artifacts, tools/, or .DAT files).
#
# Usage:
#   ./build.sh              # build only
#   ./build.sh --package    # build + zip
#   ./build.sh --clean --package
# ----------------------------------------------------------------------------
if [[ "${PACKAGE:-0}" == "1" ]] || [[ "$*" == *"--package"* ]] || [[ "$*" == *"-p"* ]]; then
    echo
    echo "[build] packaging..."

    STAGING="${ROOT}/.pkg-staging"
    PKG_NAME="daybreak-$(date +%Y%m%d-%H%M%S)"
    PKG_DIR="${STAGING}/${PKG_NAME}"
    rm -rf "${STAGING}"
    mkdir -p "${PKG_DIR}"

    # Copy source (no build artifacts, no tools, no .DAT, no .git).
    for item in CMakeLists.txt README.md build.sh .gitignore cmake scripts src tests docs; do
        if [[ -e "${ROOT}/${item}" ]]; then
            cp -r "${ROOT}/${item}" "${PKG_DIR}/"
        fi
    done

    # Remove heavy test assets (.DAT files — 2GB+).
    rm -rf "${PKG_DIR}/tests/real_assets"
    find "${PKG_DIR}" -name "*.dat" -delete 2>/dev/null || true

    # Copy build output (the runnable game).
    mkdir -p "${PKG_DIR}/build"
    cp "${BUILD_DIR}"/daybreak.exe "${PKG_DIR}/build/"
    for dll in "${BUILD_DIR}"/*.dll; do
        [[ -f "$dll" ]] && cp "$dll" "${PKG_DIR}/build/"
    done

    # Copy test .X files.
    cp "${ROOT}"/tests/*.x "${PKG_DIR}/tests/" 2>/dev/null || true

    # Zip it.
    ZIP_PATH="${ROOT}/daybreak-package.zip"
    (cd "${STAGING}" && zip -qr "${ZIP_PATH}" "${PKG_NAME}")
    rm -rf "${STAGING}"

    echo "[build] package: ${ZIP_PATH}"
    ls -lh "${ZIP_PATH}"
fi
