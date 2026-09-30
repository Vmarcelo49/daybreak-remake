#!/usr/bin/env bash
#
# launch_original.sh — open the original DaybreakDX.exe with the widescreen
# hook, for agent testing.
#
# What it does:
#   1. Resolves the game folder (GAME_DIR) and wideMod.exe (WIDEMOD).
#   2. Sanity-checks DaybreakDX.exe + config.dat (+ warns if DaybreakFixer.dll
#      is missing, the --launch injection would fail).
#   3. Runs `wideMod.exe --launch` under wine, pinned to CPU 0 on the host
#      (taskset, complements the in-guest affinity workaround).
#
# It BLOCKS while the game runs so interactive agents (computer-use, etc.)
# can drive the window; kill DaybreakDX.exe (or Ctrl-C here) to end the
# session. wideMod prints `game launched: pid=...` on start and
# `game exited: pid=... code=...` at the end.
#
# Usage:
#   tools/launch_original.sh [--resolution 1920x1080] [-- <extra wideMod args>]
#
# Env:
#   GAME_DIR  game install dir (default: <repo>/Higurashi-Daybreak)
#   WIDEMOD   wideMod.exe path (default: $GAME_DIR/wideMod.exe, then
#             ~/Projetos/daybreakWidescreen/wideMod.exe)
#   WINE      wine binary (default: wine)
#   WINEDLLOVERRIDES / WINEDEBUG  passthrough (defaults: "" / -all)
#
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
GAME_DIR="${GAME_DIR:-$REPO_ROOT/Higurashi-Daybreak}"
WINE="${WINE:-wine}"

pick_widemod() {
    if [[ -n "${WIDEMOD:-}" && -f "$WIDEMOD" ]]; then echo "$WIDEMOD"; return; fi
    # Prefer the source-built binary so agents always exercise the latest
    # --launch implementation; fall back to a copy inside the game dir.
    local sibling="$HOME/Projetos/daybreakWidescreen/wideMod.exe"
    if [[ -f "$sibling" ]]; then echo "$sibling"; return; fi
    if [[ -f "$GAME_DIR/wideMod.exe" ]]; then echo "$GAME_DIR/wideMod.exe"; return; fi
    echo "ERROR: wideMod.exe not found. Set WIDEMOD=/path/to/wideMod.exe" >&2
    exit 1
}

WIDEMOD_RESOLVED="$(pick_widemod)"

[[ -f "$GAME_DIR/DaybreakDX.exe" ]] || { echo "ERROR: $GAME_DIR/DaybreakDX.exe not found (set GAME_DIR)" >&2; exit 1; }
[[ -f "$GAME_DIR/config.dat" ]]     || { echo "ERROR: $GAME_DIR/config.dat not found (open config in the game once to generate it)" >&2; exit 1; }
[[ -f "$GAME_DIR/DaybreakFixer.dll" ]] || echo "WARN: DaybreakFixer.dll missing in $GAME_DIR — --launch injection will fail" >&2

# Optional resolution patch applied before launch: --resolution 1920x1080
EXTRA_ARGS=()
if [[ "${1:-}" == "--resolution" && -n "${2:-}" ]]; then
    EXTRA_ARGS+=(--resolution="$2")
    shift 2
fi
if [[ "${1:-}" == "--" ]]; then shift; fi
# Any remaining args are forwarded to wideMod.exe verbatim.

export WINEDEBUG="${WINEDEBUG:--all}"
[[ -n "${WINEDLLOVERRIDES:-}" ]] && export WINEDLLOVERRIDES

PIN=()
if command -v taskset >/dev/null 2>&1; then PIN=(taskset -c 0); fi

echo "=== launch_original ==="
echo "  game dir: $GAME_DIR"
echo "  wideMod:  $WIDEMOD_RESOLVED"
echo "  args:     --launch ${EXTRA_ARGS[*]:-} $*"
echo ""

cd "$GAME_DIR"
# shellcheck disable=SC2068
exec "${PIN[@]}" "$WINE" "$WIDEMOD_RESOLVED" --launch "${EXTRA_ARGS[@]}" $@
