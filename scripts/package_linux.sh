#!/usr/bin/env bash
# Build the Linux release package (issue #22).
#
#   ./scripts/package_linux.sh [--no-build] [--out=<dir>]
#
# Produces build/package/daybreak-<version>-linux-x86_64.tar.gz: the executable, the two
# runtime libraries it actually needs (wgpu-native and SDL3), the caption fonts, the
# third-party notices, the launcher and the startup/controls guide. It contains no
# original game data — the game's files are copyrighted and are never release artifacts.
#
# The staging itself is CMake's install rules (CMakeLists.txt), so the file list is a
# build-system fact; this script builds, stages, verifies and archives:
#   * every required file is present, and the launcher is executable;
#   * nothing under a game-data path (daybreakXX.dat, data/, movie/, .X/.cnv) is in the
#     artifact, and the archive's table of contents is printed so the claim is checkable;
#   * `ldd` on the packaged executable resolves every library inside the package or from
#     the base system — never third_party/, the build tree or any other developer path;
#   * the tarball is deterministic (sorted names, fixed mtimes, gzip without a timestamp),
#     so two runs of this script produce the same sha256.
#
# The package is written under the gitignored build/ directory. It is never committed.
set -euo pipefail

here=$(cd "$(dirname "$0")" && pwd)
root=$(cd "$here/.." && pwd)          # the repository root
version=$(tr -d '[:space:]' < "$root/VERSION")
name="daybreak-${version}-linux-x86_64"
out_dir="$root/build/package"
build=1

usage() {
    sed -n '2,20p' "$0" | sed 's/^# \{0,1\}//'
}

while [ $# -gt 0 ]; do
    case $1 in
        --no-build) build=0 ;;
        --out=*)    out_dir=${1#--out=} ;;
        -h|--help)  usage; exit 0 ;;
        *)          echo "package_linux.sh: unknown option $1" >&2; exit 2 ;;
    esac
    shift
done

fail() { echo "package_linux.sh: $*" >&2; exit 1; }

command -v tar >/dev/null || fail "tar is required"
tar --version | grep -q GNU || fail "GNU tar is required (--sort/--mtime/--owner)"

if [ "$build" = 1 ]; then
    echo "== building =="
    "$root/build.sh" linux
fi
[ -f "$root/build/linux/daybreak" ] \
    || fail "no build in $root/build/linux — run ./build.sh linux first (or drop --no-build)"
[ -f "$root/third_party/fonts/NotoSansCJKjp-Regular.otf" ] \
    || fail "third_party/fonts/NotoSansCJKjp-Regular.otf is missing — run ./build.sh deps (D7 needs the Japanese fallback in the package)"

stage="$out_dir/$name"
echo "== staging $stage =="
rm -rf "$stage"
mkdir -p "$out_dir"
cmake --install "$root/build/linux" --prefix "$stage" >/dev/null

echo "== required files =="
required=(
    daybreak-bin daybreak README-LINUX.md VERSION
    assets/fonts/gyrotrope-black.otf assets/fonts/NotoSansCJKjp-Regular.otf
    lib/libwgpu_native.so lib/libSDL3.so.0
    LICENSES/README.md LICENSES/SDL3.txt LICENSES/wgpu-native-MIT.txt
    LICENSES/SIL-OFL-1.1.txt LICENSES/glm-MIT.txt LICENSES/stb.txt
    LICENSES/daybreak-decomp.txt
)
for f in "${required[@]}"; do
    [ -e "$stage/$f" ] || fail "the staged package is missing $f"
done
[ -x "$stage/daybreak" ] || fail "the launcher is not executable in the package"
[ -x "$stage/daybreak-bin" ] || fail "the executable is not executable in the package"

echo "== no game data =="
# Both routes the port reads are game data: the shipped .dat bundles and an extracted
# tree (data/, movie/). Any hit fails the package — release artifacts never ship
# copyrighted files.
[ ! -e "$stage/data" ] || fail "the staged package contains a data/ tree (game data)"
[ ! -e "$stage/movie" ] || fail "the staged package contains a movie/ tree (game data)"
game_files=$(find "$stage" -type f \
    \( -iname 'daybreak[0-9][0-9].dat' -o -iname '*.X' -o -iname '*.cnv' \
       -o -iname '*.dat' -o -iname '*.ogg' -o -iname '*.sfl' \) -print)
[ -z "$game_files" ] || fail "the staged package contains game data:
$game_files"
echo "no daybreakXX.dat, data/, movie/, .X, .cnv, .dat, .ogg or .sfl file in the artifact"

echo "== runtime libraries (ldd) =="
ldd_out=$(ldd "$stage/daybreak-bin")
printf '%s\n' "$ldd_out"
printf '%s\n' "$ldd_out" | grep -q 'not found' \
    && fail "a library does not resolve — the package would not start on a machine without the build tree"
# Every resolved path must be the package's own lib/ or a base-system library; anything
# else is a developer path (third_party/, the build tree, _deps) that does not exist on a
# user's machine. The package's own path is exempt because it is staged under build/.
stray=$(printf '%s\n' "$ldd_out" | awk '{print $3}' | grep -v '^$' \
        | grep -vF "$stage/" | grep -Ev '^/(usr/)?lib' || true)
[ -z "$stray" ] || fail "a library resolves outside the package and the base system:
$stray"
printf '%s\n' "$ldd_out" | grep -qF "$stage/lib/libwgpu_native.so" \
    || fail "libwgpu_native.so does not resolve inside the package"
printf '%s\n' "$ldd_out" | grep -qF "$stage/lib/libSDL3.so.0" \
    || fail "libSDL3.so.0 does not resolve inside the package"

echo "== archive =="
tarball="$out_dir/$name.tar.gz"
rm -f "$tarball" "$tarball.sha256"
# Deterministic: sorted entries, fixed ownership and mtime, gzip without its own
# timestamp — two runs give the same sha256 (verified in the issue's report).
tar -C "$out_dir" --sort=name --owner=0 --group=0 --numeric-owner --mtime=@0 \
    -cf - "$name" | gzip -9n > "$tarball"
sha256sum "$tarball" > "$tarball.sha256"
cat "$tarball.sha256"

echo "== artifact contents =="
tar -tzf "$tarball" | sed 's/^/  /'
echo
echo "package : $tarball ($(du -h "$tarball" | cut -f1))"
echo "sha256  : $(cut -d' ' -f1 "$tarball.sha256")"
echo "unpack  : tar -xzf $(basename "$tarball") && cd $name && ./daybreak --install=\"/path/to/Higurashi-Daybreak\""
