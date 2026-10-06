# NPR evidence, issue #27 — what is here and how to re-render it

Issue #25 delivered the `--npr` harness and a recommendation; issue #27 rejected the
**evidence** behind it (prints that look identical at a glance, one resolution tested, "N
pixels changed" standing in for "reads differently"). This directory is the re-run. The
review, the verdicts and the recommendation are in
`remake/foundation/docs/NPR-EXPERIMENTS.md` **§8** — start there; this file is the map.

## Layout

```
issue-27/
├── captures/
│   ├── HOWTO-scene-and-regions.png   the scene, the metric regions, the definitions
│   ├── close-<arm>.png               10 contact sheets: one per technique, three
│   │                                 resolutions off/on side by side + face/hair/torso
│   │                                 crops + the metric regions + a difference locator
│   ├── sanity-<param>.png            10 sweeps: one parameter at a time at its extremes,
│   │                                 with the control frame beside every step
│   ├── gameplay-<arm>.png            6 fight-distance frames (kept arms; E included as
│   │                                 the counter-example that is byte-identical there)
│   ├── reach-versus.png              which arms reach a fight scene at all
│   └── fourview-2v2.png              the 4-view 2v2 split screen, off/on, cells at 2x
├── logs/                             the demo's own output for every capture, with the
│                                     command line as its first line
├── metrics.json                      every number, the recipes (`commands`) and the
│                                     sha256 of every frame
└── metrics.md                        the same numbers as tables
```

**Size: 15 MB** (captures 14.4 MB in 29 PNGs, logs 0.6 MB in 151 files). The raw PPMs are
not committed: every sheet contains its frames at native scale, and `metrics.json` carries
the command line that re-renders any of them.

## The scene every close-up sheet uses

| | |
|---|---|
| combo | **Rena 0** — 竜宮レナ + 愛用の鉈 (`data/rena/00.x` + `data/item/01.x`, item id 001) |
| pose, stage | bind pose (`--no-anim`), no stage — the background is the pass's clear colour, so the character mask is exact |
| camera | `--camera=bounds` (see below) |
| sizes | 640x360, 960x540, 1920x1080 — 16:9 and exact multiples of one world camera |
| capture | `--headless --frames=3 --out=<file.ppm>` |

```bash
cd remake/foundation/build/linux
I=../../Higurashi-Daybreak
./foundation_demo --headless --install=$I \
  --character=$I/data/rena:0 --weapon=$I/data/item/01.x \
  --no-anim --camera=bounds --frames=3 --size=1920x1080 \
  --npr=<arm> --out=/tmp/npr-evidence.ppm
```

`--camera=bounds` and not `auto` because auto framing (distance = 2 x the bounds radius,
fovY 45 degrees) clips the top of a weaponed fighter at 16:9 — 333 px of hair sit on row 0
of the 1080p capture. The #25 captures all used `auto`; that is one reason they read so
alike.

Fight-distance sheets are `--versus --camera=arena` on stage01 with **Rena 0 vs Mion 0**
(Mion 0 = コテ拳銃, `data/item/04.x`), 300 frames at 960x540; the 4-view sheet is
`--screen=battle --local-players=4` on stage03, whose front-end roster is Rena 0, Mion 0,
Mion 0, Rika 0.

## How to re-render

```bash
python3 remake/foundation/tests/npr_evidence.py \
  --demo remake/foundation/build/linux/foundation_demo \
  --install Higurashi-Daybreak \
  --outdir remake/tests/npr-evidence/issue-27 \
  --workdir /tmp/npr-evidence-work
```

`--only <id,id>` re-renders a subset (the report on disk is merged, so the other sections
survive) and `--quick` skips the fight scenes. Roughly two minutes for everything on the
machine that produced this.

The measurements themselves are not a judgement: `metrics.md` prints the numbers with the
thresholds the review declared (a port-side evidence rule, not a renderer constant), and
the sheets are what a human decides on. `tests/npr_experiments.py` is the gate that stays
in `ctest`: it pins OFF as the default byte for byte, each technique's stated property, and
— since issue #27 — that no arm's parameter is *silently* inert (the arms that are inert
today are named there with this issue's number, and a fix fails the test until the list
shrinks).
