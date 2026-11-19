#!/usr/bin/env bash
# Bounded, build-only coverage for the web target (issue #128). Compiles and links
# a fresh non-release tree, then checks that daybreak.html/js/wasm/data exist.
# It never starts a browser, loads game data, uploads an artifact, or changes the
# production `./build.sh web` build. The CI job's hard timeout also covers the
# SDK install and dependency fetch that happen before this script runs.
set -euo pipefail
here=$(cd -P "$(dirname "$0")/.." && pwd)
sdk=${EMSDK:-$HOME/emsdk}
pinned_sdk=6.0.10
timeout_s=${WEB_BUILD_TIMEOUT:-600}
# GNU timeout treats 0 as "no limit"; refuse it and anything non-numeric so the
# bounded contract cannot be turned off by a typo.
[[ "$timeout_s" =~ ^[1-9][0-9]*$ ]] || {
    echo "[web-check] WEB_BUILD_TIMEOUT must be positive integer seconds, got: $timeout_s" >&2
    exit 2
}

# The build root must be a real directory in the canonical checkout. mktemp then
# creates a brand-new tree: no recursive removal of a caller-supplied path.
build_root="$here/build"
mkdir -p "$build_root"
resolved_root=$(cd -P "$build_root" && pwd)
[ "$resolved_root" = "$build_root" ] || {
    echo "refusing symlinked build root: $build_root -> $resolved_root" >&2; exit 2
}

[ -f "$sdk/emsdk_env.sh" ] || { echo "[web-check] no emsdk at $sdk" >&2; exit 2; }
# emsdk_env.sh is not set -u clean; source it with nounset relaxed.
# shellcheck disable=SC1090
set +u
source "$sdk/emsdk_env.sh" >/dev/null
set -u
# emsdk_env.sh clears EM_CACHE, so set the cache only after sourcing it.
export EM_CACHE="${WEB_EM_CACHE:-$sdk/upstream/emscripten/cache}"

stamp() { date -u +%FT%TZ; }
emcc_version=$(emcc --version | head -1)
[[ "$emcc_version" == *" $pinned_sdk "* ]] || {
    echo "[web-check] expected emcc $pinned_sdk, got: $emcc_version" >&2; exit 2
}
printf '[web-check] %s emcc: %s\n' "$(stamp)" "$emcc_version"
printf '[web-check] %s cmake: %s\n' "$(stamp)" "$(cmake --version | head -1)"
printf '[web-check] %s cache: %s\n' "$(stamp)" "$EM_CACHE"

build_dir=$(mktemp -d "$build_root/web-check.XXXXXX")
printf '[web-check] %s fresh tree: %s\n' "$(stamp)" "$build_dir"
printf '[web-check] %s cap: %ss for configure + build (no build output is cached)\n' "$(stamp)" "$timeout_s"

# One timeout covers configure (including the emdawnwebgpu port fetch) and the
# verbose build, so the last printed ninja command is the final link if it stalls.
set +e
timeout --kill-after=30s "${timeout_s}s" bash -c '
    set -e
    emcmake cmake -S "$1" -B "$2" -GNinja -DCMAKE_BUILD_TYPE=Debug
    cmake --build "$2" --verbose
' web-check "$here" "$build_dir"
rc=$?
set -e
printf '[web-check] %s build end rc=%d\n' "$(stamp)" "$rc"
[ "$rc" -eq 0 ] || { echo '[web-check] build failed or hit its timeout' >&2; exit "$rc"; }

for name in daybreak.html daybreak.js daybreak.wasm daybreak.data; do
    [ -s "$build_dir/$name" ] || { echo "[web-check] missing or empty: $name" >&2; exit 1; }
done
wc -c "$build_dir"/daybreak.html "$build_dir"/daybreak.js \
      "$build_dir"/daybreak.wasm "$build_dir"/daybreak.data
printf '[web-check] %s RESULT: linked web build OK — build only, no browser, no game data, no release artifact\n' "$(stamp)"
