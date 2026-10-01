# Visual A/B suite — headless captures vs ground-truth screenshots

> Drive the remake under Xvfb + Wine with scripted inputs, capture frames,
> and compare side-by-side against the original-game captures in
> [`docs/reference/`](../../docs/reference/) (21 ground-truth shots).
> This suite already paid for itself once: its first captures exposed a
> Y-up/Z-up axis mismatch (camera modeled Z-up in a Y-up world, fighters
> buried or floating) that no amount of code reading had caught.

## Quickstart

```bash
./remake/build.sh              # build first
./remake/tests/visual/run.sh   # all cases → tests/visual/out/report.html
./remake/tests/visual/run.sh gameplay-yard   # one case (substring match)
```

Prerequisites: Wine, ImageMagick (`convert`, `compare`, `montage`).
Xvfb resolves to `remake/tools/xvfb` (user-local vendor, gitignored) or
`$PATH`. Game `.dats` resolve via `$GAME_DIR` (default
`<repo>/Higurashi-Daybreak`, the gitignored local install). Output lands
in `tests/visual/out/` (gitignored) — BMPs, PNGs, per-case logs, report.

## How a case works

`cases.txt` lines are `name|reference|timeout(s)|wine args`:

- `-scene title|gameplay`, `-p1 N`, `-p2 N` pick the entry point.
- `-spawn x,y,z` overrides the P1 spawn (per-stage viewpoints; spawns
  come from `data/stageNN/env.dat` — stage21's holds both spawns verbatim).
- `-script scripts/<name>.txt` plays P1 inputs on main-loop frame numbers
  (`<frame> <TOKEN>...`, `-` releases; `#` comments). Tokens: `UP DOWN
  LEFT RIGHT MELEE HEAVY GUARD SHOOT JUMP SPECIAL TACTICS LOCK PAUSE`.
- `-shot <frame>=<name>.bmp` saves the backbuffer after that render.
  `F12` does the same interactively (`shot_f<frame>.bmp`).
- `-frames N` quits cleanly after N frames (exit 0, no window to close).

Frames are the 1-based main-loop render index everywhere (script lines,
`-shot`, F12 names), and game logic runs on a fixed 1/60 step — so frame N
is always game-time N/60s and script timings mean the same on every host.
Probes (all env-gated, off by default):

| Env | Effect |
|---|---|
| `DAYBREAK_CAMINFO=1` | eye + fighter positions ~1/sec in stdout |
| `DAYBREAK_CAMH/H`, `DAYBREAK_CAMD` | camera height/distance override |
| `DAYBREAK_MESHINFO=1` | vertex counts + bounding boxes per mesh at load |

`run.sh` stages a dir of symlinks (exe, DLLs, `.dat`s, `assets/`,
`scripts/`), runs each case headless, converts BMP→PNG, scores RMSE
against the reference (informational only — an untextured build reads
far from zero; judge layout/framing/HUD by eye), and writes the report.

## Case ↔ capture map (v1)

| Case | Reference | Exercises |
|---|---|---|
| `title-100` | `title-menu.webp` | Title bg + boot (no menu text yet) |
| `gameplay-120` | `battle-hud.webp` | Default-spawn framing, full HUD |
| `gameplay-yard` | `battle-hud.webp` | Arena-center framing, P1 mid-frame |
| `gameplay-dash` | `battle-stamina.webp` | Double-tap dash + contextual stamina bar |
| `gameplay-tapshot` | `battle-hud.webp` | Tap-tier projectile in flight |
| `gameplay-charge` | — (charge UI unpinned) | Charge meter while held + red release |
| `gameplay-ko` | `ko-moment.webp` | 28 taps vs P2 dummy → KO, sting, balloon +21% |

## Known deltas (suite-owned punchlist for future milestones)

- **D1 — Textured (bundle-backed resolve).** `.X` `TextureFilename`
  refs (`服.bmp`) map to same-dir `.cnv` in the bundle (Shift-JIS→UTF-8
  before lookup — the miss-everything encoding bug is fixed). Foliage
  cards alpha-cut via scene alpha test (bimodal CNV alpha); baked blob
  shadows (white card + dark blob/silhouette, opaque alpha) white-key
  exact-white texels to transparent at resolve time (cut by the same
  alpha test) and multiply the rest (white neutral, blob darkens).
  Decal verdict lives in one `MaterialResolver` predicate on the texture
  name — ASCII `shadow*` plus 影 (e.g. 校舎影02 school shadow, 手すり影
  handrail shadow) — provisional until effect-technique binding (P3.1)
  replaces name-matching with real technique assignment.
- **D2 — Bind pose.** Fighters load with 0 animation sets (character
  anims live in separate `data/<char>/NN.dat`, not yet loaded), so
  poses never change. F2 anim-debug lists the (empty) set table.
- **D3 — Gray arena background.** Eye-level views fill with flat gray —
  the stage21 skybox/far mesh interior, untextured (follows from D1).
- **D4 — Title.** No menu items render yet; `bg00.cnv` content reads as
  team-select art (blue/red halves + team kanji), which disagrees with
  the shrine-approach bg in `title-menu.webp` — open whether the asset
  pick or the CNV mip-decode is wrong.
- **D5 — Spawns.** P1/P2 spawns are stage01-era values; per-stage
  spawns (and spawn heights vs each arena floor) arrive with the
  versus-frontend milestone.
- **D6 — HUD gaps.** ASCII `KO!` (no kanji sting), static `OYASHIRO`
  label, no FPS counter / lock reticule / `com` tags / overhead HP —
  all visible in `battle-hud.webp`, none modeled yet.
- **D7 — Sting/inflate animation.** KO adds +21% instantly; the
  inflate sweep and floating `+N%` delta from `ko-moment.webp` are
  future work.

## Adding a case

1. Write `scripts/<name>.txt` if it needs inputs (frames start after
   the 60-frame BattleStart pose — inputs before that are ignored).
2. Append one `cases.txt` line with a timeout generous at ~35 fps
   under llvmpipe plus ~10 s Wine boot.
3. Run it, read `out/report.html`, and extend the delta list above —
   a case that only passes is a case that teaches nothing.
