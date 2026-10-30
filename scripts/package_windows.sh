#!/usr/bin/env bash
# Package the Windows x64 build without original game data.
# Usage: package_windows.sh [--no-build] [--out=<directory>]
set -euo pipefail
root=$(cd "$(dirname "$0")/.." && pwd)
out_dir="$root/build/package"
build=1
for arg in "$@"; do
    case "$arg" in
        --no-build) build=0 ;;
        --out=*) out_dir=${arg#--out=} ;;
        *) echo "Unknown option: $arg" >&2; exit 2 ;;
    esac
done
command -v zip >/dev/null
command -v x86_64-w64-mingw32-objdump >/dev/null
if [ "$build" = 1 ]; then "$root/build.sh" windows; fi
version=$(tr -d '[:space:]' < "$root/VERSION")
revision=$(git -C "$root" rev-parse --short HEAD)
if ! git -C "$root" diff --quiet || ! git -C "$root" diff --cached --quiet; then
    revision="$revision-dirty"
fi
name="daybreak-${version}-${revision}-windows-x86_64"
mkdir -p "$out_dir"
out_dir=$(cd "$out_dir" && pwd)
stage=$(mktemp -d "$out_dir/windows-stage.XXXXXX")
trap 'rm -rf "$stage"; rm -f "$stage.zip"' EXIT
for file in daybreak.exe SDL3.dll wgpu_native.dll; do
    test -s "$root/build/windows/$file"
done
cp "$root/build/windows/daybreak.exe" "$stage/DaybreakRemake.exe"
cp "$root/build/windows/SDL3.dll" "$root/build/windows/wgpu_native.dll" "$stage/"
mkdir -p "$stage/assets/fonts"
cp "$root/assets/fonts/gyrotrope-black.otf" "$stage/assets/fonts/"
cp "$root/third_party/fonts/NotoSansCJKjp-Regular.otf" "$stage/assets/fonts/"
cp "$root/package/README-WINDOWS.md" "$stage/"
cp -R "$root/package/LICENSES" "$stage/"
cp "$root/../../LICENSE" "$stage/LICENSES/daybreak-decomp.txt"
cat > "$stage/LICENSES/README.md" <<'NOTICES'
# Windows package notices

The port uses the Golden Witch License (daybreak-decomp.txt). SDL3 uses the zlib
license. wgpu-native and its distribution wrapper, GLM, stb and pl_mpeg use the
included MIT/public-domain notices. Gyrotrope Black and Noto Sans CJK JP use
SIL-OFL-1.1.txt. Fonts are redistributed without modification.

The MinGW GCC runtime is linked statically under GPL-3.0.txt with the permission
in GCC-Runtime-Library-Exception.txt. Windows system libraries are not bundled.
Original game data is not included.
NOTICES
printf 'Version: %s\nCode revision: %s\nTarget: Windows x64\n' "$version" "$revision" > "$stage/BUILD-INFO.txt"
for file in "$stage"/*.exe "$stage"/*.dll; do
    while IFS= read -r dependency; do
        case "${dependency,,}" in
            api-ms-*.dll|kernel32.dll|advapi32.dll|gdi32.dll|imm32.dll|msvcrt.dll|ole32.dll|oleaut32.dll|setupapi.dll|shell32.dll|user32.dll|version.dll|winmm.dll|d3dcompiler_47.dll|ntdll.dll|opengl32.dll|propsys.dll|userenv.dll|ws2_32.dll|bcryptprimitives.dll) ;;
            *) test -s "$stage/$dependency" || { echo "Missing runtime DLL: $dependency" >&2; exit 1; } ;;
        esac
    done < <(x86_64-w64-mingw32-objdump -p "$file" | sed -n 's/.*DLL Name: //p')
done
test -z "$(find "$stage" -type f \( -iname '*.dat' -o -iname '*.x' -o -iname '*.cnv' -o -iname '*.mpg' \) -print)"
test -z "$(find "$stage" -type f \( -iname '*.cmd' -o -iname '*.bat' -o -iname '*.ps1' -o -iname '*.sh' \) -print)"
(cd "$stage" && zip -q -r "$stage.zip" .)
mv "$stage.zip" "$out_dir/$name.zip"
sha256sum "$out_dir/$name.zip"
