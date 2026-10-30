#!/bin/sh
# docs/DIRECTION.md, M3: the product reads gameplay through game::BattleView. main.cpp may reach
# the legacy Match only at its named seams, and no other product code may name Fighter or Match.
# Growing the count below means a new read bypassed the view; shrink it as seams move.
src="$1"
status=0

allowed=12   # setup 5, debug keys 1, COM input 1, pilot 2 (before, after), live debug 3
seams=$(grep -c 'legacyBattle\.match()' "$src/main.cpp")
# The member's own comment names the seam.
seams=$((seams - 1))
if [ "$seams" -gt "$allowed" ]; then
    echo "FAIL: main.cpp reaches legacyBattle.match() $seams times, allowed $allowed"
    status=1
fi

if grep -nE 'gameplay::(Fighter|Match|Projectile|Spark)\b' "$src/main.cpp" | grep -v '^[0-9]*:[[:space:]]*//'; then
    echo "FAIL: main.cpp names a legacy simulation type"
    status=1
fi

for dir in render ui audio game; do
    if grep -rlE '#include "gameplay/(fighter|match|projectile|legacy_battle)\.h"' "$src/$dir"; then
        echo "FAIL: $dir includes the legacy simulation"
        status=1
    fi
done

[ "$status" -eq 0 ] && echo "BATTLE_SEAM: ok ($seams seams)"
exit "$status"
