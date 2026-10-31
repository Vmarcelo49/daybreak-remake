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
    for mode in rollback-stress=0 rollback-stress=8 net-stress=8; do
        if ! "$daybreak" --headless --no-audio --install="$install" --screen=battle --frames="$frames" --size=640x360 \
            --"$mode" --out="$out/$mode.ppm" >"$out/log" 2>&1; then
            echo "FAIL: the run at $frames frames, $mode"
            exit 1
        fi
        case $mode in net-stress*)
            grep -q ' 0 desyncs' "$out/log" || { echo "FAIL: $mode at $frames frames: $(grep '\[net\]' "$out/log")"; failed=1; }
        esac
    done
    for mode in rollback-stress=8 net-stress=8; do
        if cmp -s "$out/rollback-stress=0.ppm" "$out/$mode.ppm"; then
            echo "frame $frames, $mode: the same pixels"
        else
            echo "FAIL: frame $frames differs with $mode"
            failed=1
        fi
    done
done
exit "$failed"
