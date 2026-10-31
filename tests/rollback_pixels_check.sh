#!/usr/bin/env bash
# Online rollback (docs/ONLINE-PLAN.md, step 2): forcing rollbacks must not change what is drawn.
set -u
daybreak=$1
install=$2
[ -f "$install/daybreak00.dat" ] || { echo "SKIP: no install"; exit 77; }
out=$(mktemp -d)
trap 'rm -rf "$out"' EXIT

failed=0
for frames in 400 1500 3000; do
    for stress in 0 8; do
        if ! "$daybreak" --headless --no-audio --install="$install" --screen=battle --frames="$frames" --size=640x360 \
            --rollback-stress="$stress" --out="$out/$stress.ppm" >/dev/null 2>&1; then
            echo "FAIL: the run at $frames frames, stress $stress"
            exit 1
        fi
    done
    if cmp -s "$out/0.ppm" "$out/8.ppm"; then
        echo "frame $frames: the same pixels"
    else
        echo "FAIL: frame $frames differs with rollbacks forced"
        failed=1
    fi
done
exit "$failed"
