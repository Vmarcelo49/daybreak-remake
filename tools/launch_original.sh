#!/usr/bin/env bash
#
# launch_original.sh — open DaybreakDX.exe with our DaybreakFixer injector,
# for agent testing. (wideMod support removed 2026-09-30: wideMod is not
# compatible with our DLL — game stays black under `wideMod --launch`.)
#
# What it does:
#   1. Resolves the game folder (GAME_DIR) and injector.exe (INJECTOR).
#   2. Sanity-checks DaybreakDX.exe + injector.exe (+ warns if
#      DaybreakFixer.dll / config.dat are missing).
#   3. Runs `injector.exe` under wine (Forwards CLI args). Our injector
#      exits after launching, so the script then BLOCKS while DaybreakDX.exe
#      lives, printing `game launched:` / `game exited:` lines.
#   4. No host-side CPU pin by default: pinning (taskset -c 0) causes
#      pathologically slow boot (black window for minutes) + system-wide
#      hitches under Wine (root cause 2026-09-30). Opt in with PIN_CPUS="0".
#
# It BLOCKS while the game runs so interactive agents (computer-use, etc.)
# can drive the window; kill DaybreakDX.exe (or Ctrl-C here) to end the
# session.
#
# Usage:
#   tools/launch_original.sh [--affinity] [--no-priority] [dll] [exe]
#   (args forwarded to injector.exe; resolution comes from widescreen.toml)
#
# Env:
#   GAME_DIR  game install dir (default: <repo>/Higurashi-Daybreak)
#   INJECTOR  injector.exe path (default: $GAME_DIR/injector.exe)
#   PIN_CPUS  opt-in host CPU pin, e.g. PIN_CPUS="0" (default: unset = no
#             pin; pinning causes black-screen boot + hitches under Wine)
#   WINE      wine binary (default: wine)
#   WINEDLLOVERRIDES / WINEDEBUG  passthrough (defaults: "" / -all)
#
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
GAME_DIR="${GAME_DIR:-$REPO_ROOT/Higurashi-Daybreak}"
INJECTOR="${INJECTOR:-$GAME_DIR/injector.exe}"
WINE="${WINE:-wine}"

[[ -f "$GAME_DIR/DaybreakDX.exe" ]] || { echo "ERROR: $GAME_DIR/DaybreakDX.exe not found (set GAME_DIR)" >&2; exit 1; }
[[ -f "$INJECTOR" ]] || { echo "ERROR: injector.exe not found at $INJECTOR (set INJECTOR)" >&2; exit 1; }
[[ -f "$GAME_DIR/DaybreakFixer.dll" ]] || echo "WARN: DaybreakFixer.dll missing in $GAME_DIR — injection will fail" >&2
[[ -f "$GAME_DIR/config.dat" ]]     || echo "WARN: no config.dat yet (fresh install) — open config in the game once to generate it" >&2

# Our injector reads resolution from widescreen.toml; fail fast instead of
# misparsing wideMod-style flags as [dll]/[exe] positionals.
if [[ "${1:-}" == "--resolution" ]]; then
    echo "ERROR: --resolution is a wideMod flag (unsupported). Edit widescreen.toml [display] instead." >&2
    exit 2
fi
if [[ "${1:-}" == "--launch" ]]; then
    echo "ERROR: --launch is a wideMod flag (unsupported). Our injector launches by default; drop the flag." >&2
    exit 2
fi
if [[ "${1:-}" == "--" ]]; then shift; fi

export WINEDEBUG="${WINEDEBUG:--all}"
[[ -n "${WINEDLLOVERRIDES:-}" ]] && export WINEDLLOVERRIDES

PIN=()
if [[ -n "${PIN_CPUS:-}" ]] && command -v taskset >/dev/null 2>&1; then PIN=(taskset -c "$PIN_CPUS"); fi

echo "=== launch_original ==="
echo "  game dir: $GAME_DIR"
echo "  injector: $INJECTOR"
if [[ ${#PIN[@]} -eq 0 ]]; then echo "  pin:      none (set PIN_CPUS=\"0\" to pin)"; else echo "  pin:      ${PIN[*]}"; fi
echo "  args:     $*"
echo ""

cd "$GAME_DIR"
# shellcheck disable=SC2068
"${PIN[@]}" "$WINE" "$INJECTOR" $@

# Our injector exits right after launching; block while the game lives so
# agents keep a stable window to drive. Wait up to 90s for boot, then
# poll until the process is gone (Ctrl-C / game quit ends the session).
echo "waiting for DaybreakDX.exe..."
for _ in $(seq 1 90); do
    if pgrep -f "DaybreakDX\.exe" >/dev/null; then break; fi
    sleep 1
done
GAME_PID="$(pgrep -f "DaybreakDX\.exe" | head -1 || true)"
if [[ -z "${GAME_PID:-}" ]]; then
    echo "ERROR: DaybreakDX.exe did not appear within 90s — check wine output above" >&2
    exit 1
fi
echo "game launched: pid=$GAME_PID exe=DaybreakDX.exe"
while kill -0 "$GAME_PID" 2>/dev/null; do sleep 2; done
echo "game exited: pid=$GAME_PID"
