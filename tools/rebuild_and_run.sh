#!/usr/bin/env bash
#
# rebuild_and_run.sh — rebuild the foundation and launch a versus match.
#
# What it does:
#   1. Rebuilds remake/foundation/build/linux (ctest does NOT rebuild the
#      demo binary, so testing a fix without this step runs stale code).
#   2. Stops any already-running foundation_demo (a stale window hides the
#      new build behind the old behaviour).
#   3. Launches the demo detached with the standard versus flags, logging to
#      $LOG (default /tmp/win3.log), then reports instances + log tail.
#
# Usage:
#   ./tools/rebuild_and_run.sh
#   ./tools/rebuild_and_run.sh --character=data/mion --enemy=data/rika
#   STAGE=data/stage14 CHARACTER=data/mion ENEMY=data/rika LOG=/tmp/m.log \
#       ./tools/rebuild_and_run.sh --hitbox-debug
#
# Any extra arguments are forwarded to foundation_demo (they override the
# STAGE/CHARACTER/ENEMY defaults below only when they repeat those flags).
set -uo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD="$ROOT/remake/foundation/build/linux"
DEMO="$BUILD/foundation_demo"
LOG="${LOG:-/tmp/win3.log}"
STAGE="${STAGE:-data/stage21}"
CHARACTER="${CHARACTER:-data/rena}"
ENEMY="${ENEMY:-data/rena}"

echo "==> building $BUILD"
BUILD_LOG="$(cmake --build "$BUILD" 2>&1)"
BUILD_STATUS=$?
echo "$BUILD_LOG" | tail -n 2
if [ $BUILD_STATUS -ne 0 ]; then
    echo "$BUILD_LOG" | grep -E "error|FAILED" | head -n 20
    echo "ERROR: build failed" >&2
    exit 1
fi
if [ ! -x "$DEMO" ]; then
    echo "ERROR: $DEMO missing after build" >&2
    exit 1
fi

echo "==> stopping old instances"
pkill -f 'foundation_dem[o]' 2>/dev/null || true
sleep 1

echo "==> launching (log: $LOG)"
rm -f "$LOG"
cd "$ROOT"
setsid nohup env SDL_AUDIODRIVER=dummy "$DEMO" \
    --install=Higurashi-Daybreak --match \
    --stage="$STAGE" --character="$CHARACTER" --enemy="$ENEMY" \
    "$@" > "$LOG" 2>&1 < /dev/null &
disown
sleep 18
echo "instances: $(pgrep -c 'foundation_dem[o]')"
tail -3 "$LOG"
