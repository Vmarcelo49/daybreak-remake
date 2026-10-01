#!/usr/bin/env bash
# =============================================================================
#  run.sh — visual A/B runner: boots the remake headless (Xvfb + Wine),
#  plays scripted inputs, captures frames, and builds a side-by-side HTML
#  report against the ground-truth captures in remake/docs/reference/.
#
#  Usage:
#    ./run.sh                 # all cases in cases.txt
#    ./run.sh gameplay-yard   # one case (substring match)
#
#  Prerequisites: remake built (build/daybreak.exe), Wine, ImageMagick.
#  Xvfb comes from remake/tools/xvfb (user-local vendor) or $PATH.
#  Game .dats resolve via $GAME_DIR (default: <repo>/Higurashi-Daybreak).
#  Output lands in tests/visual/out/ (gitignored, regenerated each run).
# =============================================================================
set -euo pipefail

VIS="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$(cd "${VIS}/../.." && pwd)"
REPO="$(cd "${ROOT}/.." && pwd)"
REF="${ROOT}/docs/reference"
BUILD="${ROOT}/build/daybreak.exe"
GAME_DIR="${GAME_DIR:-${REPO}/Higurashi-Daybreak}"
OUT="${VIS}/out"
CASES="${VIS}/cases.txt"

[[ -x "${BUILD}" ]] || { echo "[visual] build first: ./remake/build.sh" >&2; exit 1; }
command -v wine >/dev/null || { echo "[visual] wine not found" >&2; exit 1; }
command -v convert >/dev/null || { echo "[visual] ImageMagick 'convert' not found" >&2; exit 1; }
command -v compare >/dev/null || { echo "[visual] ImageMagick 'compare' not found" >&2; exit 1; }

# ---- Xvfb ------------------------------------------------------------------
if [[ -x "${ROOT}/tools/xvfb/usr/bin/Xvfb" ]]; then
    XVFB="${ROOT}/tools/xvfb/usr/bin/Xvfb"
elif command -v Xvfb >/dev/null; then
    XVFB="Xvfb"
else
    echo "[visual] no Xvfb (run a fetch into remake/tools/xvfb or install it)" >&2
    exit 1
fi
DISP=":99"
if [[ -e "/tmp/.X11-unix/X${DISP#:}" ]]; then
    echo "[visual] display ${DISP} busy (single run at a time)" >&2
    exit 1
fi
"${XVFB}" "${DISP}" -screen 0 800x600x24 >/tmp/dbvis-xvfb.log 2>&1 &
XVFB_PID=$!
trap 'kill ${XVFB_PID} 2>/dev/null || true' EXIT
sleep 2

export DISPLAY="${DISP}"
export WINEPREFIX="${ROOT}/tools/wine-prefix"
export WINEDEBUG="-all"
export SDL_AUDIODRIVER="dummy"
export DAYBREAK_CAMINFO=1  # eye/fighter positions in per-case logs

# ---- staging (symlinks; nothing is copied) ----------------------------------
WORK="$(mktemp -d /tmp/dbvis.XXXXXX)"
trap 'kill ${XVFB_PID} 2>/dev/null || true; rm -rf "${WORK}"' EXIT
ln -s "${BUILD}" "${WORK}/daybreak.exe"
ln -s "${BUILD%/*}/SDL2.dll" "${WORK}/" 2>/dev/null || true
ln -s "${BUILD%/*}/SDL2_mixer.dll" "${WORK}/" 2>/dev/null || true
for dat in "${GAME_DIR}"/daybreak0*.dat; do
    [[ -f "${dat}" ]] && ln -s "${dat}" "${WORK}/"
done
ln -s "${ROOT}/assets" "${WORK}/assets"
ln -s "${VIS}/scripts" "${WORK}/scripts"
mkdir -p "${OUT}"

# ---- report helpers ---------------------------------------------------------
shot_png() { # $1 = staging bmp path (relative), prints out png path
    local bmp="${WORK}/$1" png="${OUT}/$1"
    png="${png%.bmp}.png"
    convert "${bmp}" "${png}"
    echo "${png}"
}

rmse_against() { # $1 = remake png, $2 = ref webp (or empty); prints score or "-"
    [[ -z "${2:-}" ]] && { echo "-"; return; }
    local ref="${REF}/$2" refpng="${WORK}/ref_$(basename "$2" .webp).png"
    [[ -f "${ref}" ]] || { echo "ref-missing"; return; }
    [[ -f "${refpng}" ]] || convert "${ref}" -resize '800x600!' "${refpng}"
    local score
    score=$(compare -metric RMSE "${refpng}" "$1" null: 2>&1 || true)
    echo "${score}" | grep -oE '\([0-9.]+\)' | tr -d '()' || echo "?"
}

# ---- run cases ---------------------------------------------------------------
FILTER="${1:-}"
REPORT="${OUT}/report.html"
{
echo '<!doctype html><html><head><meta charset="utf-8">'
echo '<title>daybreak visual A/B</title>'
echo '<style>body{font-family:sans-serif;background:#111;color:#ddd}'
echo 'table{border-collapse:collapse}td,th{border:1px solid #444;padding:8px;vertical-align:top}'
echo 'img{width:400px}.rmse{font-family:monospace}</style></head><body>'
echo '<h1>daybreak visual A/B</h1>'
echo '<p>RMSE is informational (untextured build vs finished game reads far from zero). '
echo 'Judge layout/framing/HUD by eye.</p>'
echo '<table><tr><th>case</th><th>remake</th><th>reference</th><th>RMSE</th><th>log</th></tr>'
} > "${REPORT}"

PASS=0; FAIL=0
while IFS='|' read -r name ref timeout args; do
    [[ "${name}" =~ ^#.*$ || -z "${name}" ]] && continue
    if [[ -n "${FILTER}" && "${name}" != *"${FILTER}"* ]]; then continue; fi
    echo "[visual] case ${name}"
    # shellcheck disable=SC2086
    if ! (cd "${WORK}" && timeout "${timeout}" wine daybreak.exe ${args} >"${OUT}/${name}.log" 2>&1); then
        echo "[visual]   FAILED (exit/timeout) — see out/${name}.log"
        FAIL=$((FAIL + 1))
        echo "<tr><td>${name}</td><td colspan=3>run failed</td><td><a href=\"${name}.log\">log</a></td></tr>" >> "${REPORT}"
        wineserver -k 2>/dev/null || true
        continue
    fi
    PASS=$((PASS + 1))
    wineserver -k 2>/dev/null || true
    for bmp in "${WORK}/${name}"*.bmp; do
        [[ -f "${bmp}" ]] || continue
        rel="$(basename "${bmp}")"
        png="$(shot_png "${rel}")"
        score="$(rmse_against "${png}" "${ref}")"
        refimg="(no ground truth)"
        if [[ -n "${ref}" && -f "${REF}/${ref}" ]]; then
            refimg="<a href=\"file://${REF}/${ref}\"><img src=\"file://${REF}/${ref}\"></a><br>${ref}"
        fi
        echo "<tr><td>${name}<br>${rel}</td><td><img src=\"$(basename "${png}")\">" >> "${REPORT}"
        echo "</td><td>${refimg}</td><td class=rmse>${score}</td>" >> "${REPORT}"
        echo "<td><a href=\"${name}.log\">log</a></td></tr>" >> "${REPORT}"
    done
done < "${CASES}"

echo '</table>' >> "${REPORT}"
echo "<p>${PASS} passed, ${FAIL} failed. Full logs in out/*.log.</p></body></html>" >> "${REPORT}"
echo "[visual] ${PASS} passed, ${FAIL} failed → ${REPORT}"
