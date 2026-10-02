#!/usr/bin/env bash
# fetch_deps.sh — fetch the two things this folder needs, into third_party/.
#
#   ./tools/fetch_deps.sh              # host (Linux) wgpu-native + glm
#   ./tools/fetch_deps.sh windows      # Windows (MinGW) wgpu-native + glm
#   ./tools/fetch_deps.sh windows linux
#
# Both are permissively licensed and header/lib only; nothing here is committed.
set -euo pipefail

WGPU_VERSION="v29.0.1.1"
WGPU_BASE="https://github.com/gfx-rs/wgpu-native/releases/download/${WGPU_VERSION}"
GLM_REF="1.0.1"
GLM_URL="https://github.com/g-truc/glm/archive/refs/tags/${GLM_REF}.tar.gz"

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
dest="${root}/third_party"
mkdir -p "${dest}"

want=("$@")
if [ ${#want[@]} -eq 0 ]; then
    want=("linux")
    # Cross-building for Windows is this project's normal case, so grab that too when
    # the host can actually link it.
    if command -v x86_64-w64-mingw32-g++ >/dev/null 2>&1; then want+=("windows"); fi
fi

fetch() {  # fetch <url> <outfile>
    local url="$1" out="$2"
    if [ -s "${out}" ]; then
        echo "  have $(basename "${out}")"
        return
    fi
    echo "  fetching $(basename "${out}") ..."
    if command -v curl >/dev/null 2>&1; then
        curl -fL --retry 3 -o "${out}.part" "${url}"
    else
        wget -O "${out}.part" "${url}"
    fi
    mv "${out}.part" "${out}"
}

for target in "${want[@]}"; do
    case "${target}" in
        linux)
            zip="wgpu-linux-x86_64-release.zip"
            out="${dest}/wgpu-linux"
            echo "wgpu-native (linux x86_64, ${WGPU_VERSION})"
            fetch "${WGPU_BASE}/${zip}" "${dest}/${zip}"
            rm -rf "${out}"; mkdir -p "${out}"
            unzip -q -o "${dest}/${zip}" -d "${out}"
            ;;
        windows)
            zip="wgpu-windows-x86_64-gnu-release.zip"
            out="${dest}/wgpu-windows"
            echo "wgpu-native (windows x86_64 gnu, ${WGPU_VERSION})"
            fetch "${WGPU_BASE}/${zip}" "${dest}/${zip}"
            rm -rf "${out}"; mkdir -p "${out}"
            unzip -q -o "${dest}/${zip}" -d "${out}"
            ;;
        *)
            echo "unknown target '${target}' (expected: linux, windows)" >&2
            exit 2
            ;;
    esac
done

# GLM is header-only. Prefer the system copy, but vendor one for MinGW cross builds,
# where /usr/include/glm would drag glibc headers into the Windows compile.
if [ ! -d "${dest}/glm/glm" ]; then
    if [ -d /usr/include/glm ] && [ ! -d "${dest}/glm" ]; then
        echo "glm: copying the system copy into third_party/ for cross builds"
        mkdir -p "${dest}/glm"
        cp -r /usr/include/glm "${dest}/glm/"
    else
        echo "glm ${GLM_REF}: downloading"
        fetch "${GLM_URL}" "${dest}/glm.tar.gz"
        tar -xzf "${dest}/glm.tar.gz" -C "${dest}"
        mv "${dest}/glm-${GLM_REF}" "${dest}/glm-src"
        mkdir -p "${dest}/glm"
        cp -r "${dest}/glm-src/glm" "${dest}/glm/"
    fi
fi

echo
echo "third_party/ ready:"
ls -1 "${dest}" | sed 's/^/  /'
echo
echo "next: ./build.sh"
