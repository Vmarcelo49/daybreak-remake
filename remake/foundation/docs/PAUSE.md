# Battle pause — the recovered freeze, and the port's menu

Issue #15. The input vocabulary and the binding screen already carried a `Pause` action
(keyboard W, pad Start by default, rebindable); nothing in the battle read it, and Escape
killed the process. This is what the pause is, what it freezes, and which runs may use it.

## What is recovered (cite, don't invent)

The original has a pause flag and a second toggle, both cleared by the battle reset:

| What | Where |
|---|---|
| pause flag `scene+0x4430`, second toggle `scene+0x4431` | cleared by `FUN_00634760` @0x634877 / @0x634881 |
| the toggle | `FUN_00634f60` @0x634fb3-0x635006 |
| offline-mode gate (`DAT_006cfdb0 == 0`) | @0x634fb3-0x634fbc |
| live-round gate (`scene+0x4a3c == 2`) | @0x634fc2-0x634fcc |
| the player's pause action (`[fighter+0x29c] == 1`) | @0x634fdf-0x634fe6 |
| the pause cue, system SE `0x11` (`FUN_0064aed0`) | @0x634fe8-0x634fef |
| the flag flip (`1 - (x != 0)`) | @0x634ff4-0x635006 |
| the prompt/banner switch: any of the fighter's 7 action slots flips `0x4431` | @0x63500c-0x635064 |
| **the freeze**: the frame counter `scene+0x1c` and the whole battle update are skipped | @0x635093-0x6350aa |
| the banner: the `PAUSE` cell of `data/object/system.cnv` (256,64,256,64) drawn at (400,300) | `FUN_0063a130` @0x63a08c-0x63a0b8 |

Two consequences worth stating: the original keeps **reading input while paused** (the
toggle sits before the gate), which is what lets a player resume; and it freezes everything
the gate wraps — fighter updates, the round machine `FUN_00635d40`, the balloon easing
`FUN_006430f0` and the camera/FX tail — not just the fighters.

## What is a port feature

The original's pause UI is the banner plus a もう一度挑戦しますか？ / はい / いいえ rematch
prompt from the same atlas. The **four-row readable menu** — Resume, Rematch, Return to
selection, Quit to desktop — and its captions are the port's own, because the issue asks for
readable, rebindable controls and the original has no return-to-selection row (leaving a
battle goes through its result scene there). The standalone `--match` harness has no
selection screen behind it, so its menu is three rows (Resume / Rematch / Quit).

The overlay's **size, spacing and backing panel are port decisions too**, and they live in
`ui/pause_layout.h` as one device-free rule (`tests/pause_overlay_layout_test.cpp` pins it):
the body glyph cell is 4.5 % of the target's shorter side, the title is 1.35x that and the
footer 0.8x, the line pitch is 1.5x the body size, and the panel is the measured text block
plus 0.7x the body size on every side. Nothing in that rule is recovered — the original has
no readable menu to measure — but *nothing in it is a constant either*, which is what issue
#50 defect 3 was: a fixed 16 px face at fixed pixel offsets drew a stamp in the middle of a
540-row frame and an unreadable one at 1080p. The overlay is one block over the whole target,
so a 4-view split reads at exactly the single-view size.

## Why the overlay owns a renderer (issue #50 defects 1 and 2)

`drawBattlePauseOverlay` batches into `App::pauseUi`, a second `SpriteRenderer`, and not into
the battle HUD's `app.uiRenderer`. That is not tidiness — it is the fix, and the mechanism is
worth writing down because it is a property of the sprite batch, not of this menu:

* `SpriteRenderer::beginFrame` does clear the quad queue, so the overlay never "adopted" the
  HUD's *quads*. What it shared was the **vertex buffer**: every `render()` call in the frame
  wrote the same buffer at offset 0, and (per WebGPU's queue ordering) all of a frame's
  writes are performed before its single submission. The effective content of a frame was
  therefore the LAST write, with the tail of the longest earlier write left behind it.
* Measured on a paused single-view frame: the overlay's pass pushed 546 quads (its 55 % dim
  plus the caption's glyphs) and the HUD's pass 32 (its first quad being the first fighter's
  reticle cell — a 115x115 rotated quad). The HUD's shorter write overwrote the overlay's
  first 32 quads, so the overlay's pass drew the HUD's geometry with ITS OWN texture binds:
  the dim quad came out as the reticle's quad textured with the 1x1 white fallback — a solid
  white rotated block over a fighter, which is the human's "the white rectangle is the
  targeting image but the white should be transparency" — the rest ghosted the HUD's opening
  art under the real HUD (defect 2's "ghosted, doubled art and text"), and the overlay's own
  title (inside those first 32 quads) was not drawn at all.
* Controls that ruled out the issue's other candidates: with the reticle suppressed the white
  block disappears (so it IS that quad); `--no-toon` reproduces it byte-for-byte (so it is not
  #21's outline hull); and the run's own summary reports `fx events=0 … peak=0/128` for the
  frame (so it is not #17's effect cards).
* With the overlay in its own renderer, its pass and the HUD's passes cannot see each other's
  vertices at all, and **unpaused captures are unchanged** — the overlay is not drawn when the
  battle is not paused, so a single-view, 2-view or 4-view unpaused capture hashed identically
  before and after.

The aliasing itself is fixed as of issue #56, at the batch rather than per caller: each
`render()` call now writes and binds its OWN vertex region (`src/ui/sprite.h`, `kVertexSlots`,
the uniform path's rule), so no pass can read another's geometry. The second renderer stays:
it is how the overlay owns its batching (a different lifecycle from the HUD's per-view
passes), and #50's evidence and this document were measured with it. Removing it is a
follow-up, not a repair — with the batch fixed it would be tidiness, not a fix.

The defect that same aliasing caused *within* the battle HUD's own passes is what #56 fixed:
in a 4-view frame the separator pass was the last write, so every view's first two quads
(fighter 0's reticle circle and triangles) were replaced by the separator's thin bars and each
cell's remaining quads read whichever view wrote last. `hud_cell_scale.py` cannot see it —
every pass pushes its probe markers at identical coordinates — so #56 added
`tests/hud_view_geometry.py`, which asserts on each view's own reticle anchors, and recorded
the split-screen baselines that legitimately move in `RELEASE-CHECKLIST.md` §3.7.

## What freezes

`Match::set_paused` gates the authoritative step: a paused `Match::step` returns an empty
frame and touches nothing — no economy tick, no fighter tick, no respawn clock, no
projectile motion, no FX event — and `dt` is dropped rather than accumulated. The host also
skips its own per-tick work (`tickMatch`: the frame counter, COM decisions, HUD values,
camera update, animation clock), so the presented frame is frozen, and the fixed-step clock
is **not advanced at all** while paused: paused wall time can never become catch-up ticks.

Measured (temporary per-frame instrumentation, since removed): a live battle paused for
12 s of wall time printed `matchFrame=39 alpha=0.3728 eye=(0.00,176.47,-124.08)
target=(0.00,338.00,0.00)` identically on every sampled frame.

## Input

* The paused ticks keep draining the device queues at the same cadence they would during
  play. That is what makes a button held across the pause produce **no** edge on resume,
  while a fresh press still works.
* Menu keys: Up/Down choose, Jump confirms, AttackA backs out (Resume), Pause toggles back
  out — the same vocabulary the other menus use.
* The overlay's key hints are read from the **current bindings** (P1 keyboard plus the
  pausing player's pad), so a rebind shows up without a second table.
* Escape opens the pause in a live battle instead of quitting the process; inside the menu
  it resumes. Menu screens and every capture/replay path keep Escape's old behaviour.

## Focus loss and disconnected controllers

* Focus loss drops held keys (#6's Guard-safety fix) and **pauses a live offline battle**,
  so a match cannot keep running — and keep taking damage — while the player cannot see or
  control it. Regaining focus does not auto-resume; the player resumes deliberately. A
  *scripted* run is left alone: its script owns the pause state, and a stray focus event
  must not make a recipe non-deterministic.
* A disconnected pad already reads as released (`Backend::poll` clears a removed device's
  held state, so a mid-hold removal becomes one `just_released`, not a stuck hold), and the
  pause action is bound to the keyboard by default and is rebindable — so a player whose pad
  dies can always reach the menu.

## Audio

* Gameplay SFX (`SfxBus::Sfx`, channels 16..31) are stopped when the pause begins; no new
  cue can start because the match does not step, and a pause is not a mixer pause (one-shots
  do not resume).
* BGM keeps playing: the original's pause path plays SE 0x11 and never touches the music
  stream.
* The pause cue is the recovered system SE 0x11 (`data/sysse/017`), played on the UI bus.
* Voices are not cut (they are short, and the original does not touch them).
* The full expectation was handed to the #16 (combat audio) agent; it must not add pause
  policy of its own.

## Which runs may pause

Only a live offline battle that is not a capture or a bounded run:

```cpp
app.matchMode && app.opts.out.empty() && !app.opts.headless && app.opts.frames == 0
```

so `--match`, `--versus`, `--hud-test`, `--screen=battle` captures, `--out`/`--headless`
runs and every `--frames` run keep their historical behaviour and are byte-identical with
the pause unused (verified: the four parity recipes produce identical PPMs with and without
a user config and never mention the pause).

A scripted standalone `--match` run needs one extra piece: its script is indexed by the
match frame, which freezes with the pause, so the paused ticks advance
`App::pauseScriptAdvance`, which is added to that clock. It is zero for every run that never
pauses, so the banked traces keep their frame-for-frame script mapping.

## Verification

* `pause_overlay_layout_test` (device-free, no assets): the layout rule above — the size and
  the panel scale with the canvas (1080p is 2x 540p), the panel is the measured text plus its
  margin and stays inside the frame from 320x180 to 8K, and the shorter side fixes the size,
  so a 4-view split over the same target reads the same.
* `pause_overlay_panel` (rendered frame, skips without game data): runs `--pause-overlay=300`
  and measures the capture against a reference frame of the SAME match state one frame
  earlier. Pins: no solid-white block (the defect's quad was 158x157 px at 960x540, and the
  same capture made by the pre-fix draw path fails this check), a backing panel present with
  the text inside it and 5–6 drawn line bands, the title's ink 20 px at 960x540 and 41 px at
  1920x1080 (2.05x, panel width 2.04x), the 4-view split's panel identical to the single
  view's at that size, the panel mask empty on two unpaused frames, and a pause captured 60
  frames after it began byte-identical (the freeze, seen from the capture path).
* `--pause-overlay=N` is the instrument those captures use, and the only way a headless run
  can photograph the menu: it enters the battle pause on the tick `matchFrame` reaches N
  through the same `enterBattlePause` the player's key uses, so the captured frame is a real
  paused one, with the frozen clocks and the real menu rows. It is parsed only with `--out`
  and a live run rejects it, so no played or other capture path can reach it.
* `battle_pause_test` (device-free, 1276 checks): the frozen economy, KO and respawn clocks;
  a held button producing no shot or attack while paused and none on resume, while a fresh
  press still does; the `TickInput` drain rule; the menu's rows, wrap and choices.
* Asset-backed, `--screen=battle`: pause mid-attack → resume; pause → Rematch → VS → the
  **same stage** → a fresh battle; Rematch again; pause → Return to selection → the Select
  screen; quit through the menu with a clean exit (`RESULT: ok`). The scene/asset counts are
  identical every cycle (13 models, 63 meshes, 50006 vertices, 152 textures), i.e. repeated
  re-entry does not grow anything.
* Asset-backed, mid-respawn (needs the damage fix from `feat/fix-damage-scale`):
  `KO! side=1` → pause inside the 3 s window → **600 paused ticks (three times the window)
  with no respawn** → resume → `side 1 respawned` → quit. Log order is the evidence.
* Focus-loss auto-pause and the disconnected-pad path are policy plus the existing backend
  behaviour; a physical pad replug and real hardware audio were not exercised here.
