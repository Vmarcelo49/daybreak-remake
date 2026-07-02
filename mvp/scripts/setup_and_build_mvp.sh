#!/usr/bin/env bash
# ============================================================
# setup_and_build_mvp.sh — Setup cross-compile environment and build the MVP
#
# This script is idempotent and safe to re-run. It:
#   1. Installs CMake (via pip) if missing
#   2. Downloads + extracts LLVM-MinGW cross-compiler (Linux → Win32) if missing
#   3. Configures CMake with the cross-compile toolchain
#   4. Builds daybreak_mvp.exe
#   5. Verifies the output is a valid PE32 executable
#
# Usage:
#   bash /home/z/my-project/scripts/setup_and_build_mvp.sh
#
# Or with custom paths:
#   LLVM_MINGW_ROOT=/custom/path bash setup_and_build_mvp.sh
#
# Output:
#   /home/z/my-project/FileVault/shared/daybreakdx-re/mvp/build/daybreak_mvp.exe
# ============================================================

set -euo pipefail

# ============================================================
# Configuration (override via env vars)
# ============================================================

PROJECT_ROOT="/home/z/my-project"
MVP_DIR="${PROJECT_ROOT}/FileVault/shared/daybreakdx-re/mvp"
LLVM_MINGW_ROOT="${LLVM_MINGW_ROOT:-${HOME}/mingw86/llvm-mingw}"
LLVM_MINGW_VERSION="20231017"
LLVM_MINGW_URL="https://github.com/mstorsjo/llvm-mingw/releases/download/${LLVM_MINGW_VERSION}/llvm-mingw-${LLVM_MINGW_VERSION}-ucrt-ubuntu-20.04-x86_64.tar.xz"
TOOLCHAIN_FILE="${MVP_DIR}/cmake/i686-w64-mingw32.cmake"
BUILD_DIR="${MVP_DIR}/build"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

log() { echo -e "${BLUE}[$(date +%H:%M:%S)]${NC} $*"; }
ok()  { echo -e "${GREEN}[$(date +%H:%M:%S)] ✅${NC} $*"; }
warn(){ echo -e "${YELLOW}[$(date +%H:%M:%S)] ⚠️${NC} $*"; }
err() { echo -e "${RED}[$(date +%H:%M:%S)] ❌${NC} $*" >&2; }

# ============================================================
# Step 1: Check prerequisites
# ============================================================

log "Step 1: Checking prerequisites..."

if [[ ! -d "$MVP_DIR" ]]; then
    err "MVP directory not found: $MVP_DIR"
    err "Make sure the daybreak-decomp repo is cloned at:"
    err "  ${PROJECT_ROOT}/FileVault/shared/daybreakdx-re/"
    exit 1
fi

if [[ ! -f "${MVP_DIR}/CMakeLists.txt" ]]; then
    err "CMakeLists.txt not found in $MVP_DIR"
    exit 1
fi

# Check basic tools
for tool in curl tar; do
    if ! command -v $tool &> /dev/null; then
        err "Required tool '$tool' not found. Install it first."
        exit 1
    fi
done

ok "Prerequisites OK"

# ============================================================
# Step 2: Install CMake via pip if missing
# ============================================================

log "Step 2: Checking CMake..."

if ! command -v cmake &> /dev/null; then
    log "CMake not found. Installing via pip..."
    pip3 install cmake --quiet 2>&1 || {
        err "Failed to install cmake via pip"
        exit 1
    }
    # Ensure pip-installed cmake is in PATH
    export PATH="${HOME}/.venv/bin:${PATH}"
fi

CMAKE_VERSION=$(cmake --version 2>&1 | head -1 | awk '{print $3}')
ok "CMake ${CMAKE_VERSION} available"

# ============================================================
# Step 3: Install LLVM-MinGW if missing
# ============================================================

log "Step 3: Checking LLVM-MinGW cross-compiler..."

GCC_BIN="${LLVM_MINGW_ROOT}/bin/i686-w64-mingw32-gcc"

if [[ -x "$GCC_BIN" ]]; then
    GCC_VERSION=$("$GCC_BIN" --version 2>&1 | head -1)
    ok "LLVM-MinGW already installed: ${GCC_VERSION}"
else
    log "LLVM-MinGW not found at ${LLVM_MINGW_ROOT}"
    log "Downloading from: ${LLVM_MINGW_URL}"

    INSTALL_PARENT=$(dirname "$LLVM_MINGW_ROOT")
    mkdir -p "$INSTALL_PARENT"
    cd "$INSTALL_PARENT"

    ARCHIVE="llvm-mingw.tar.xz"

    # Download (resume-friendly with -C -)
    curl -L -C - -o "$ARCHIVE" --max-time 300 "$LLVM_MINGW_URL" 2>&1 | tail -3

    if [[ ! -s "$ARCHIVE" ]]; then
        err "Download failed or empty file"
        exit 1
    fi

    log "Extracting..."
    tar xf "$ARCHIVE"
    rm "$ARCHIVE"

    # The tar extracts to llvm-mingw-VERSION-...-x86_64/, rename to llvm-mingw
    EXTRACTED_DIR=$(ls -d llvm-mingw-* 2>/dev/null | head -1)
    if [[ -z "$EXTRACTED_DIR" ]]; then
        err "Extraction failed — no llvm-mingw-* directory found"
        exit 1
    fi

    if [[ "$EXTRACTED_DIR" != "llvm-mingw" ]]; then
        rm -rf llvm-mingw  # in case exists from previous run
        mv "$EXTRACTED_DIR" llvm-mingw
    fi

    if [[ ! -x "$GCC_BIN" ]]; then
        err "After extraction, gcc still not found at $GCC_BIN"
        err "Contents of ${LLVM_MINGW_ROOT}/bin/:"
        ls "${LLVM_MINGW_ROOT}/bin/" | head -10
        exit 1
    fi

    GCC_VERSION=$("$GCC_BIN" --version 2>&1 | head -1)
    ok "LLVM-MinGW installed: ${GCC_VERSION}"
fi

# Add to PATH for this session
export PATH="${LLVM_MINGW_ROOT}/bin:${PATH}"

# ============================================================
# Step 4: Configure CMake
# ============================================================

log "Step 4: Configuring CMake (cross-compile)..."

# Clean previous build (force fresh configuration)
rm -rf "$BUILD_DIR"

cmake -B "$BUILD_DIR" \
      -S "$MVP_DIR" \
      -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN_FILE" \
      -DLLVM_MINGW_ROOT="$LLVM_MINGW_ROOT" \
      2>&1 | tail -15

if [[ ${PIPESTATUS[0]} -ne 0 ]]; then
    err "CMake configuration failed"
    exit 1
fi

ok "CMake configured"

# ============================================================
# Step 5: Build
# ============================================================

log "Step 5: Building daybreak_mvp.exe..."

cmake --build "$BUILD_DIR" -- -j$(nproc) 2>&1 | tail -15

if [[ ${PIPESTATUS[0]} -ne 0 ]]; then
    err "Build failed"
    exit 1
fi

# ============================================================
# Step 6: Verify output
# ============================================================

log "Step 6: Verifying output..."

OUTPUT_EXE="${BUILD_DIR}/daybreak_mvp.exe"

if [[ ! -f "$OUTPUT_EXE" ]]; then
    err "Build output not found: $OUTPUT_EXE"
    exit 1
fi

# Use cross-compiler's `file` equivalent via objdump
OBJDUMP="${LLVM_MINGW_ROOT}/bin/i686-w64-mingw32-objdump"
if [[ -x "$OBJDUMP" ]]; then
    log "Executable info:"
    "$OBJDUMP" -f "$OUTPUT_EXE" 2>&1 | head -10
    echo ""
    log "DLL dependencies:"
    "$OBJDUMP" -p "$OUTPUT_EXE" 2>&1 | grep "DLL Name" | head -10
fi

# Get file size
SIZE=$(stat -c%s "$OUTPUT_EXE" 2>/dev/null || stat -f%z "$OUTPUT_EXE")
SIZE_KB=$((SIZE / 1024))

# ============================================================
# Done
# ============================================================

echo ""
echo "============================================================"
ok "BUILD COMPLETE"
echo "============================================================"
echo ""
echo "Output: ${OUTPUT_EXE}"
echo "Size:   ${SIZE_KB} KB (${SIZE} bytes)"
echo ""
echo "To run on Windows:"
echo "  1. Copy daybreak_mvp.exe to a Windows machine"
echo "  2. Ensure d3d9.dll, d3dx9_43.dll, dinput8.dll are available"
echo "     (DirectX 9 runtime: https://www.microsoft.com/en-us/download/details.aspx?id=35)"
echo "  3. Double-click daybreak_mvp.exe"
echo "  4. A 800x600 window should appear with slowly cycling colors"
echo "  5. Press ESC to quit"
echo ""
echo "To rebuild after code changes:"
echo "  cmake --build ${BUILD_DIR}"
echo ""
echo "To force a clean rebuild:"
echo "  rm -rf ${BUILD_DIR} && bash $0"
echo ""
