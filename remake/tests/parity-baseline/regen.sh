#!/usr/bin/env bash
# =============================================================================
# regen.sh — Phase 0 DX9 parity-banking capture script.
#
# Drives remake/build/daybreak.exe under Wine+Xvfb with EXISTING binary flags
# only (no code changes; see README.md "gaps" for what existing flags cannot
# reach). Reuses remake/tests/visual/run.sh harness conventions (staging dir
# of symlinks, Xvfb, $GAME_DIR, DAYBREAK_CAMINFO=1) but does NOT share or
# modify run.sh / cases.txt: the case list here is the Phase 0 banking set.
#
# Usage:
#   ./regen.sh                 # full Phase 0 set (33 runs, ~6 min on this host)
#   ./regen.sh <substring>     # only cases whose name contains <substring>
#                              # (FILTERED runs rewrite manifest.tsv — always
#                              # finish with a full unfiltered run)
#   KEEP_FULL=1 ./regen.sh     # also keep full-res 800x600 PNGs in
#                              # captures-full/ (default keeps small only)
#   PARITY_DISP=:98 ./regen.sh # X display to use (default :97; override when
#                              # another run holds :97 — never run two regens
#                              # against this tree concurrently)
#
# Output (all under this dir):
#   logs/<name>.log            per-run console log (draw counts, cam probe,
#                              "main loop ended after N frames")
#   logs/dat-<nn>.log          `daybreak.exe -dat daybreak<nn>.dat -list`
#   logs/asset-*.log           `-asset-info` probes for the banked models
#   logs/host-input-devices.txt host gamepad evidence for the winebus override
#   captures/<name>.png        committed captures: 200x150 PNG8
#                              (framing/HUD-layout reference; whole set ≤ ~2 MB)
#   captures-full/<name>.png   full-res 800x600 PNGs (only with KEEP_FULL=1;
#                              always regenerable — rerun this script)
#   manifest.tsv               name, command, exit, frames, files, sha256
#                              (hashes cover the COMMITTED captures/ files)
#
# Prerequisites: built remake (build/daybreak.exe), Wine, ImageMagick
# (`convert`). Xvfb from remake/tools/xvfb or $PATH. Game .dats via $GAME_DIR
# (default <repo>/Higurashi-Daybreak). Nothing is copied; the staging dir
# is symlinks + per-run BMPs, removed on exit.
# =============================================================================
set -uo pipefail

PB="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "${PB}/../.." && pwd)"
REPO="$(cd "${ROOT}/.." && pwd)"
BUILD="${ROOT}/build/daybreak.exe"
GAME_DIR="${GAME_DIR:-${REPO}/Higurashi-Daybreak}"
VIS="${ROOT}/tests/visual"
OUT_CAP="${PB}/captures"
OUT_FULL="${PB}/captures-full"
OUT_LOG="${PB}/logs"
MANIFEST="${PB}/manifest.tsv"
KEEP_FULL="${KEEP_FULL:-0}"

[[ -x "${BUILD}" ]] || { echo "[parity] build first: ./remake/build.sh" >&2; exit 1; }
command -v wine >/dev/null || { echo "[parity] wine not found" >&2; exit 1; }
command -v convert >/dev/null || { echo "[parity] ImageMagick 'convert' not found" >&2; exit 1; }

mkdir -p "${OUT_CAP}" "${OUT_LOG}"
[[ "${KEEP_FULL}" == "1" ]] && mkdir -p "${OUT_FULL}"

# ---- .DAT inventory (no Xvfb/SDL needed: -dat mode never inits graphics) ----
export WINEPREFIX="${ROOT}/tools/wine-prefix"
export WINEDEBUG="-all"
DATWORK="$(mktemp -d /tmp/dbparity-dat.XXXXXX)"
for dat in "${GAME_DIR}"/daybreak0*.dat; do
    [[ -f "${dat}" ]] && ln -s "${dat}" "${DATWORK}/"
done
ln -s "${BUILD}" "${DATWORK}/daybreak.exe"
# NOTE: the DLLs must be present even for -dat mode (exit 53 without them).
ln -s "${BUILD%/*}/SDL2.dll" "${DATWORK}/" 2>/dev/null || true
ln -s "${BUILD%/*}/SDL2_mixer.dll" "${DATWORK}/" 2>/dev/null || true
for nn in 00 01 02 04 05 06 07; do
    dat="daybreak${nn}.dat"
    if [[ -f "${DATWORK}/${dat}" ]]; then
        (cd "${DATWORK}" && wine daybreak.exe -dat "${dat}" -list >"${OUT_LOG}/dat-${nn}.log" 2>&1) || true
        echo "[parity] dat-${nn}: $(grep -c '' "${OUT_LOG}/dat-${nn}.log") log lines"
    else
        echo "[parity] dat-${nn}: MISSING from GAME_DIR" | tee "${OUT_LOG}/dat-${nn}.log"
    fi
done
# Asset probes (-asset-info): index/offset/length + magic for the Phase 0
# models. Log-only (no capture). Bundle order mirrors the exe's 6 canonical
# bundles (daybreak01.dat is NOT in the exe's list — see README gaps).
BUNDLES="daybreak00.dat:daybreak02.dat:daybreak04.dat:daybreak05.dat:daybreak06.dat:daybreak07.dat"
for asset in data/rika/01.X data/takano/00.X data/akane/00.X data/rena/01.X data/stage21/00.X data/stage21/env.dat; do
    safe="$(echo "${asset}" | tr '/.' '__')"
    (cd "${DATWORK}" && wine daybreak.exe -asset-info "${BUNDLES}" "${asset}" >"${OUT_LOG}/asset-${safe}.log" 2>&1)
    echo "[parity] asset-${safe}: exit=$? lines=$(grep -c '' "${OUT_LOG}/asset-${safe}.log")"
done

# ---- Xvfb -------------------------------------------------------------------
if [[ -x "${ROOT}/tools/xvfb/usr/bin/Xvfb" ]]; then
    XVFB="${ROOT}/tools/xvfb/usr/bin/Xvfb"
elif command -v Xvfb >/dev/null; then
    XVFB="Xvfb"
else
    echo "[parity] no Xvfb" >&2
    exit 1
fi
DISP="${PARITY_DISP:-:97}"
if [[ -e "/tmp/.X11-unix/X${DISP#:}" ]]; then
    echo "[parity] display ${DISP} busy (single run at a time)" >&2
    exit 1
fi
XVFB_LOG="/tmp/dbparity-xvfb-${DISP#:}.log"
"${XVFB}" "${DISP}" -screen 0 800x600x24 >"${XVFB_LOG}" 2>&1 &
XVFB_PID=$!
trap 'kill ${XVFB_PID} 2>/dev/null || true; rm -rf "${WORK:-}" "${DATWORK}"' EXIT
sleep 2

export DISPLAY="${DISP}"
export SDL_AUDIODRIVER="dummy"
export DAYBREAK_CAMINFO=1  # eye/fighter positions in per-case logs
# Hardware-input neutralization (harness-level, no binary change): this host
# has a physical gamepad (8BitDo) whose left stick rests outside the 8000
# deadzone, so unsuppressed runs inject random `walk` drift into P1 and every
# player-camera capture becomes non-reproducible. Disabling Wine's HID bus
# driver hides gamepads from SDL (log shows "0 gamepad(s) + keyboard") while
# keyboard/scripts (the only inputs the banking set uses) keep working.
export WINEDLLOVERRIDES="winebus.sys=d"

# ---- staging (symlinks; nothing is copied) ----------------------------------
WORK="$(mktemp -d /tmp/dbparity.XXXXXX)"
ln -s "${BUILD}" "${WORK}/daybreak.exe"
ln -s "${BUILD%/*}/SDL2.dll" "${WORK}/" 2>/dev/null || true
ln -s "${BUILD%/*}/SDL2_mixer.dll" "${WORK}/" 2>/dev/null || true
for dat in "${GAME_DIR}"/daybreak0*.dat; do
    [[ -f "${dat}" ]] && ln -s "${dat}" "${WORK}/"
done
ln -s "${ROOT}/assets" "${WORK}/assets"
mkdir -p "${WORK}/scripts"
for s in "${VIS}"/scripts/*.txt; do ln -s "${s}" "${WORK}/scripts/"; done
for s in "${PB}"/scripts/*.txt; do ln -s "${s}" "${WORK}/scripts/"; done

# ---- case list --------------------------------------------------------------
# name|timeout(s)|extra-env|wine args. Shots land in staging, converted below.
# Fighter model map (-p1/-p2 index): 0=rika/01.X 1=takano/00.X 2=akane/00.X
# 3=rena/01.X. Stage is ALWAYS stage21 (hardcoded, no -stage flag — see gaps).
CASES=(
"title-100|90||-scene title -frames 120 -shot 100=title-100.bmp"
"gameplay-default|120||-frames 150 -shot 120=gameplay-default.bmp"
# NOTE: no `gameplay-yard`: `-spawn 0,200,0` with default -p1 0 -p2 1 is
# byte-identical to fighter-p1-rika (same pixels banked twice — removed
# 2026-10-02; the 0,200,0 open-spawn viewpoint stays covered by the
# fighter-p1-* set and the action-* cases).
"gameplay-school|120||-spawn 2800,200,-800 -frames 130 -shot 110=gameplay-school.bmp"
"fighter-p1-rika|120||-p1 0 -p2 1 -spawn 0,200,0 -frames 150 -shot 120=fighter-p1-rika.bmp"
"fighter-p1-takano|120||-p1 1 -p2 0 -spawn 0,200,0 -frames 150 -shot 120=fighter-p1-takano.bmp"
"fighter-p1-akane|120||-p1 2 -p2 0 -spawn 0,200,0 -frames 150 -shot 120=fighter-p1-akane.bmp"
"fighter-p1-rena|120||-p1 3 -p2 0 -spawn 0,200,0 -frames 150 -shot 120=fighter-p1-rena.bmp"
# fighter-p2-* use scripts/lock_p2.txt (Guard+HEAVY target switch at frame
# 41) so the camera frames P2 — without it they would duplicate the p1 set
# (same pair, same P1-locked camera). P2 stands at the default open spawn
# (-spawn2 0,200,0; P1 offset to 420,200,-120): verified 2026-10-02 that the
# P2-following camera lands in the open there, while P2 at 420,200,-120
# parks the camera inside school geometry (unusable framing).
"fighter-p2-rika|120||-p1 1 -p2 0 -spawn 420,200,-120 -spawn2 0,200,0 -script scripts/lock_p2.txt -frames 150 -shot 120=fighter-p2-rika.bmp"
"fighter-p2-takano|120||-p1 0 -p2 1 -spawn 420,200,-120 -spawn2 0,200,0 -script scripts/lock_p2.txt -frames 150 -shot 120=fighter-p2-takano.bmp"
"fighter-p2-akane|120||-p1 0 -p2 2 -spawn 420,200,-120 -spawn2 0,200,0 -script scripts/lock_p2.txt -frames 150 -shot 120=fighter-p2-akane.bmp"
"fighter-p2-rena|120||-p1 0 -p2 3 -spawn 420,200,-120 -spawn2 0,200,0 -script scripts/lock_p2.txt -frames 150 -shot 120=fighter-p2-rena.bmp"
"fighter-bind|60|DAYBREAK_MESHINFO=1|-p1 0 -p2 1 -spawn 0,200,0 -frames 10 -shot 2=fighter-bind.bmp"
"camera-alt|120|DAYBREAK_CAMH=600 DAYBREAK_CAMD=1400|-spawn 0,200,0 -frames 150 -shot 120=camera-alt.bmp"
"stage-part-00|120|DAYBREAK_ONLY=00.X|-spawn 0,200,0 -frames 150 -shot 120=stage-part-00.bmp"
"stage-part-01|120|DAYBREAK_ONLY=01.X|-spawn 0,200,0 -frames 150 -shot 120=stage-part-01.bmp"
"stage-part-02|120|DAYBREAK_ONLY=02.X|-spawn 0,200,0 -frames 150 -shot 120=stage-part-02.bmp"
"stage-part-03|120|DAYBREAK_ONLY=03.X|-spawn 0,200,0 -frames 150 -shot 120=stage-part-03.bmp"
"stage-part-04|120|DAYBREAK_ONLY=04.X|-spawn 0,200,0 -frames 150 -shot 120=stage-part-04.bmp"
"stage-part-05|120|DAYBREAK_ONLY=05.X|-spawn 0,200,0 -frames 150 -shot 120=stage-part-05.bmp"
"stage-part-06|120|DAYBREAK_ONLY=06.X|-spawn 0,200,0 -frames 150 -shot 120=stage-part-06.bmp"
"hud-dash|120||-spawn 0,200,0 -script scripts/dash.txt -frames 150 -shot 95=hud-dash.bmp"
"hud-tapshot|120||-spawn 0,200,0 -script scripts/tapshot.txt -frames 150 -shot 110=hud-tapshot.bmp"
"hud-charge|120||-spawn 0,200,0 -script scripts/charge.txt -frames 200 -shot 160=hud-charge-hold.bmp -shot 185=hud-charge-release.bmp"
"hud-hyper-charge|150||-spawn 0,200,0 -spawn2 420,200,-120 -script scripts/hyper_charge.txt -frames 500 -shot 470=hud-hyper-charge.bmp"
"hud-hyper-active|120||-spawn 0,200,0 -spawn2 420,200,-120 -gauge 1,0 -script scripts/hyper_activate.txt -frames 110 -shot 100=hud-hyper-active.bmp"
"hud-hyper-oyashiro|120||-p1 1 -p2 0 -spawn 0,200,0 -spawn2 420,200,-120 -hyper 1,0 -gauge 1,0 -script scripts/hyper_activate.txt -frames 110 -shot 100=hud-hyper-oyashiro.bmp"
"hud-hp-low|120||-spawn 0,200,0 -hp 12,100 -frames 150 -shot 120=hud-hp-low.bmp"
"hud-kakera|150||-spawn 0,200,0 -spawn2 420,200,-120 -hyper 0,2 -gauge 0,1 -hp 100,3 -script scripts/hyper_lethal.txt -frames 200 -shot 170=hud-kakera.bmp"
"hud-ko|300||-spawn -2000,200,-1200 -script scripts/ko.txt -frames 2600 -shot 2290=hud-ko-a.bmp -shot 2330=hud-ko-b.bmp -shot 2450=hud-ko-c.bmp"
"action-melee|120||-p1 0 -p2 1 -spawn 0,200,0 -spawn2 420,200,-120 -script scripts/melee.txt -frames 150 -shot 82=action-melee.bmp"
# action-heavy puts the P2 dummy INSIDE kMeleeRange (160): the HEAVY tap at
# frame 80 lands ~frame 85 for kHeavyDamage=12 → P2 HP 100→88, Hit stun,
# knockback displacement, gauge credit. (Melee stays a whiffed swing at 82 —
# P2 out of range — so the two document swing-state vs heavy-hit.)
"action-heavy|120||-p1 0 -p2 1 -spawn 0,200,0 -spawn2 120,200,0 -script scripts/heavy.txt -frames 150 -shot 95=action-heavy.bmp"
"action-jump|120||-p1 0 -p2 1 -spawn 0,200,0 -script scripts/jump.txt -frames 150 -shot 92=action-jump.bmp"
"action-guard|120||-p1 0 -p2 1 -spawn 0,200,0 -script scripts/guard.txt -frames 150 -shot 100=action-guard.bmp"
)

FILTER="${1:-}"
{
echo -e "# DX9 parity-banking manifest (generated by regen.sh — do not hand-edit)"
echo -e "# binary: $(sha256sum "${BUILD}" | cut -d' ' -f1)  ($(basename "${BUILD}"))"
echo -e "# git HEAD: $(git -C "${REPO}" rev-parse HEAD)  ($(git -C "${REPO}" branch --show-current))"
echo -e "# git dirty: $(git -C "${REPO}" status --short | tr '\n' ';')"
echo -e "name\tcommand\texit\tframes\tfile\tbytes\tsha256"
} > "${MANIFEST}"
# Host input-device evidence: proves what the winebus override had to hide
# (a wireless 8BitDo pad comes and goes; either way the per-case guard above
# fails any run where a gamepad reaches SDL).
{ echo "# host input devices at regen start ($(date -u +%Y-%m-%dT%H:%M:%SZ))";
  ls /dev/input/ 2>&1;
  echo "# bluetooth (8BitDo is wireless):";
  # NOTE: hcitool is absent on modern hosts; bluetoothctl with no daemon
  # HANGS forever (wedged a full regen 2026-10-02) — always guard it.
  hcitool dev 2>&1 || timeout 5 bluetoothctl devices 2>&1 || echo "(no bt query tool/timeout)";
} > "${OUT_LOG}/host-input-devices.txt" 2>&1

PASS=0; FAIL=0
for entry in "${CASES[@]}"; do
    IFS='|' read -r name timeout extraenv args <<< "${entry}"
    if [[ -n "${FILTER}" && "${name}" != *"${FILTER}"* ]]; then continue; fi
    echo "[parity] case ${name}"
    rm -f "${WORK}/${name}"*.bmp
    # shellcheck disable=SC2086
    if [[ -n "${extraenv}" ]]; then
        (cd "${WORK}" && env ${extraenv} timeout "${timeout}" wine daybreak.exe ${args} >"${OUT_LOG}/${name}.log" 2>&1)
        code=$?
        cmdfull="env ${extraenv} wine daybreak.exe ${args}"
    else
        (cd "${WORK}" && timeout "${timeout}" wine daybreak.exe ${args} >"${OUT_LOG}/${name}.log" 2>&1)
        code=$?
        cmdfull="wine daybreak.exe ${args}"
    fi
    wineserver -k 2>/dev/null || true
    frames="$(grep -oE 'main loop ended after [0-9]+ frames' "${OUT_LOG}/${name}.log" | grep -oE '[0-9]+' || echo 0)"
    if [[ "${code}" -ne 0 ]]; then
        echo "[parity]   FAILED exit=${code} — see logs/${name}.log"
        FAIL=$((FAIL + 1))
        printf "%s\t%s\t%d\t%s\t%s\t%s\t%s\n" "${name}" "${cmdfull}" "${code}" "${frames}" "MISSING" "0" "-" >> "${MANIFEST}"
        continue
    fi
    # Determinism guard: the banking set uses scripts only, so any visible
    # gamepad means the winebus override did not propagate and stick drift
    # may have steered P1 — fail loudly instead of banking a drifted frame.
    if grep -qE "[1-9][0-9]* gamepad\(s\)" "${OUT_LOG}/${name}.log"; then
        echo "[parity]   FAILED gamepad-leak — see logs/${name}.log"
        FAIL=$((FAIL + 1))
        printf "%s\t%s\t%d\t%s\t%s\t%s\t%s\n" "${name}" "${cmdfull}" "99" "${frames}" "GAMEPAD-LEAK" "0" "-" >> "${MANIFEST}"
        continue
    fi
    PASS=$((PASS + 1))
    for bmp in "${WORK}/${name}"*.bmp; do
        [[ -f "${bmp}" ]] || { printf "%s\t%s\t%d\t%s\t%s\t%s\t%s\n" "${name}" "${cmdfull}" "${code}" "${frames}" "MISSING-shot" "0" "-" >> "${MANIFEST}"; continue; }
        rel="$(basename "${bmp}")"
        base="${rel%.bmp}"
        # Committed capture: 200x150 PNG8 (plan's "small sizes only" rule;
        # -colors 256 keeps the banked set under ~2 MB total). -strip removes
        # the date:create/modify chunks `convert` would otherwise embed, so
        # identical frames hash identically across runs (reproducibility
        # check in README.md; found 2026-10-02: pixels RMSE 0, bytes
        # differed only in timestamps).
        convert "${bmp}" -resize '200x150!' -colors 256 -strip "${OUT_CAP}/${base}.png"
        if [[ "${KEEP_FULL}" == "1" ]]; then
            convert "${bmp}" -strip "${OUT_FULL}/${base}.png"
        fi
        bytes="$(stat -c%s "${OUT_CAP}/${base}.png")"
        sha="$(sha256sum "${OUT_CAP}/${base}.png" | cut -d' ' -f1)"
        printf "%s\t%s\t%d\t%s\t%s\t%s\t%s\n" "${name}" "${cmdfull}" "${code}" "${frames}" "captures/${base}.png" "${bytes}" "${sha}" >> "${MANIFEST}"
        rm -f "${bmp}"
    done
done

echo "[parity] ${PASS} passed, ${FAIL} failed → ${MANIFEST}"
echo "[parity] captures: $(du -sh "${OUT_CAP}" | cut -f1) in ${OUT_CAP} ($(ls "${OUT_CAP}" | wc -l) files)"
echo "[parity] logs: $(du -sh "${OUT_LOG}" | cut -f1) in ${OUT_LOG} ($(ls "${OUT_LOG}" | wc -l) files)"
