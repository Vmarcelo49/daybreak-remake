#!/usr/bin/env bash
set -euo pipefail
PROJECT_DIR="/home/marcelo/Projetos/daybreak-decomp/remake"
GAME_DIR="/mnt/disco1/Games-Windows/Higurashi Daybreak"
BUILD_DIR="$PROJECT_DIR/build"

if [[ ! -f "$BUILD_DIR/daybreak.exe" ]]; then
    echo "ERROR: daybreak.exe not found at $BUILD_DIR/daybreak.exe"
    exit 1
fi

BUNDLES=""
for dat in daybreak00 daybreak01 daybreak02 daybreak04 daybreak05 daybreak06 daybreak07; do
    f="$GAME_DIR/${dat}.dat"
    if [[ -f "$f" ]]; then
        if [[ -z "$BUNDLES" ]]; then BUNDLES="$f"
        else BUNDLES="$BUNDLES:$f"; fi
    fi
done

echo "=== daybreak launcher ==="
echo "  bundles: $(echo "$BUNDLES" | tr ':' '\n' | wc -l) files"
echo ""

cd "$BUILD_DIR"
# Use "native" for d3dx9_43 — wine's builtin doesn't parse .X binary animations correctly.
export WINEDLLOVERRIDES="d3dx9_43=native"
export WINEDEBUG=-all
exec wine daybreak.exe -asset "$BUNDLES" data/rika/01.X
