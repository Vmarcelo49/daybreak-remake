#!/usr/bin/env bash
# Prints the simulation hashes and capture hashes that must not change across a refactor.
# Compare the output of two revisions; a difference means behaviour moved.
#
#   usage: tools/fingerprints.sh <simctl> <daybreak> <outdir> [tests/scripts dir]
#
# Run it from the repository root, with the game install at Higurashi-Daybreak. Each case runs
# twice, and a case whose two runs differ is reported as UNSTABLE instead of being compared.
# The filter keeps a connected pad out of the runs. With it, frontend-4p.txt ends after one
# round, because the gate scripts were calibrated with a pad attached (issue #63).
set -u
export SDL_GAMECONTROLLER_IGNORE_DEVICES_EXCEPT=0x0000/0x0000

simctl=${1:?simctl path}
demo=${2:?daybreak path}
out=${3:?outdir}
scripts=${4:-tests/scripts}
mkdir -p "$out"
fail=0

sim_case() { # sim_case <name> <roster...>
    local name=$1; shift
    local a b
    a=$("$simctl" --roster "$@" --ticks 3600 2>/dev/null | sed -n 's/.*"hash":"\([0-9a-f]*\)".*/\1/p')
    b=$("$simctl" --roster "$@" --ticks 3600 2>/dev/null | sed -n 's/.*"hash":"\([0-9a-f]*\)".*/\1/p')
    if [ -z "$a" ]; then
        echo "SIM  $name: NO HASH"; fail=1; return
    fi
    if [ "$a" != "$b" ]; then
        echo "SIM  $name: UNSTABLE a=$a b=$b"; return
    fi
    echo "SIM  $name: $a"
}

pix_case() { # pix_case <name> <extra args...>
    local name=$1; shift
    local p1="$out/$name-1.ppm" p2="$out/$name-2.ppm"
    if ! "$demo" --headless --no-audio --install=Higurashi-Daybreak "$@" --out="$p1" >/dev/null 2>&1 ||
       ! "$demo" --headless --no-audio --install=Higurashi-Daybreak "$@" --out="$p2" >/dev/null 2>&1; then
        echo "PIX  $name: RUN FAILED"; fail=1; return
    fi
    local h1 h2
    h1=$(sha256sum "$p1" | cut -d' ' -f1)
    h2=$(sha256sum "$p2" | cut -d' ' -f1)
    if [ "$h1" != "$h2" ]; then
        echo "PIX  $name: UNSTABLE $h1 vs $h2"; return
    fi
    echo "PIX  $name: $h1"
}

sim_case rena-mion-keiichi-satoko rena:0:human mion:0 keiichi:0 satoko:0
sim_case chie-rika-irie-hanyu chie:1 rika:2 irie:0 hanyu:1
sim_case akasaka-natumi-tomitake-shion akasaka:2 natumi:0 tomitake:1 shion:2

pix_case battle640 --screen=battle --frames=400 --size=640x360
pix_case title720 --screen=title --frames=200 --size=1280x720
pix_case title4p --screen=title --local-players=4 --script="$scripts/frontend-4p.txt" --frames=3500 --size=640x360

exit $fail
