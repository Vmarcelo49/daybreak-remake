# Split-screen: per-controller cameras and HUDs (issue #12)

Status 2026-10-04. Local versus renders one view per **human controller**, each with its own
camera, its own cell on the render target and its own HUD values, while the match itself is
stepped exactly once. This file records what was recovered, what is a port policy, and what
was verified.

## What the original does (recovered)

`FUN_006396f0` @ `0x006396f0` is the original's frame dispatcher and the whole layout lives
in it. Nothing here is inferred from genre convention.

| Fact | Evidence |
|---|---|
| Views are keyed by **controller slot**, not by fighter | The view loop writes the view's controller to `game+0x44b4` (`FUN_006396f0.c:110`) and uses `game + 0x454e + controller*0x160` as that view's context (`:112`) — four `0x160`-byte contexts from `game+0x454c`, whose first byte is the per-view "hide HUD" flag read by `FUN_0063a130.c:53`. The same controller index plus the cell origin is handed to the HUD drawer (`FUN_0063a130(game, controller, rect.left, rect.top)`, `FUN_006396f0.c:185-186`). |
| The human count selects the layout | `DAT_006cfba0` is the number of human controllers: `FUN_0040d130` @ `0x0040d130:105-111` counts slots whose `DAT_006cfaf8[slot]` is a real fighter index (`4` is the unassigned/COM marker), and `:115-119` forces that count to 1 on slot 0 when there is no human at all. `FUN_006396f0:48` switches on it. |
| 1 human = the whole 800×600 frame | `FUN_006396f0.c:49-53` — `SetRect(0,0,800,600)`, `DAT_006cfd00 = 1`. |
| 2 humans = two 400×300 views, top-left and bottom-right | `FUN_006396f0.c:63-64` — cells `(0,0,400,300)` then `(400,300,800,600)`, `DAT_006cfd00 = 0`; the two slots come from `DAT_006cfba4`/`DAT_006cfba8` (`:59-60`), filled in ascending slot order. |
| 3 humans = the **four**-cell grid with the human-less cell skipped | `FUN_006396f0.c:74-81` marks a slot with no human `-1`, `:109` skips that cell, and `:82-85` gives the four cells in order TL, BL, TR, BR. There is no three-cell layout. |
| 4 humans = the same four cells, view *i* = controller *i* | `FUN_006396f0.c:90-96`. |
| Each view gets its own D3D viewport | `FUN_00650ab0` @ `0x00650ab0` stores X/Y/Width/Height and calls `SetViewport`; `FUN_006396f0.c:121-122` calls it with the cell rect before each view draws. |
| A split-screen view's HUD is drawn at half scale, offset by its cell | `FUN_0063a130.c:49-51` selects `local_8 = 0.5` whenever `DAT_006cfba0 != 1`; `FUN_006396f0.c:185-186` passes `rect.left`/`rect.top` into the HUD call. |
| More than one view draws a black cross over the whole frame | `FUN_006396f0.c:191-195` — vertical bar `x 399..400`, horizontal bar `y 299..300`, after the view loop. |
| A human-less cell only gets a centre placeholder | `FUN_006396f0.c:196-201` draws at `(cell.left + 200, cell.top + 150)` for each `-1` slot. |

Per-fighter targeting is already per fighter (`gameplay/target_lock.h`, issue #8), and the
original's LockSwitch walk (`FUN_00421e30`/`FUN_00421f30`) moves the followed player and the
viewer's own combat target — so one camera per view is the right unit.

## What the port does

- `src/game/view_layout.h` — the recovered geometry and the controller-keyed assignment:
  `buildHumanViews` (slot order, COM slots allocate nothing, no-human fallback to one view on
  controller 0), `splitLayoutFor` (1 → single, 2 → two, 3 and 4 → the four-cell grid),
  `viewCell` (TL/BR for two; TL/BL/TR/BR for four, exact tiling at odd sizes) and
  `separatorRect`.
- `src/game/match_view.h` — one `MatchView` per human controller: its camera, the fighter it
  follows, its LockSwitch bookkeeping and its `ui::HudState`. No simulation state lives here.
- `src/render/scene_renderer.{h,cpp}` — `renderViews()` draws the scene once per view in one
  render pass: colour and depth clear once, then each view sets `SetViewport` **and**
  `SetScissorRect` to its cell, binds its own camera uniform and draws. Cells are disjoint, so
  a shared depth buffer cannot leak between views. `views.size() <= 1` defers to `render()`,
  which is the untouched single-view path.
- `src/render/debug_prims.*` — the overlay passes take the view's cell as `Options::viewport`
  (empty = whole target), so cubes and lines land in their own view.
- `src/ui/sprite.*` — `UiViewport` gained an origin; a batch draws its quads into that cell
  and clips its scissor runs to it. `x/y = 0` for every single-view surface.
- `src/main.cpp` — builds the views in `initMatch`, runs the per-view camera + HUD loop in
  `tickMatch` (one HUD fill per view through the existing `gameplay::hudStateFor`), and renders
  one pass per view plus the separator cross. Per-view HUD marker projection uses each view's
  own view-projection (D8). `app.eye`/`app.target` stay on the primary view so the banked
  `DAYBREAK_CAMINFO` trace and the debug overlay are unchanged.

## Port policies (explicit, not recovered)

1. **Per-view aspect is automatic (D8).** The original's cells were always 400×300 in an
   800×600 frame, i.e. 4:3. The port keeps the *cells* (halves of the target) and gives each
   view the aspect of its own cell, so a 16:9 window gets 16:9 views and an ultrawide window
   gets ultrawide views. **Provisional**: this is D8's rule applied per view, not something the
   original could express; a future decision could letterbox each view to 4:3 instead.
2. **Separator thickness scales with the frame.** The original's bars are one pixel of its
   800×600 frame; the port draws `round(min(w/800, h/600))`, at least one pixel, centred on the
   cell boundary (1 px at 800×600, 2 px at 1920×1080 and 3440×1440).
3. **A human-less cell stays at the scene clear colour.** The placeholder sprite
   `FUN_006396f0.c:198` draws was not identified, so the port draws nothing there rather than
   inventing art. The cross still delineates the empty cell, as the original's does.
4. **The FPS counter is drawn in the first view only.** The original draws it once, outside its
   view loop (`FUN_006396f0.c:203-210`); the port keeps the existing per-view HUD counter but
   gates it to view 0 (`ui::HudState::showFps`).
5. **`--local-players=N` is a verification instrument, not a feature.** It assigns controllers
   `0..N-1` to battle panels (1–2 humans: the 1v1 panel pair; 3–4: all four panels as a 2v2)
   and fills a pad-less controller's tick input from `src/input/synthetic_pad.h`, a pure
   `(controller, tick)` pattern. It is **synthetic input**: no physical controller was
   exercised, and controller 0 (the keyboard) is never overridden. Without the flag nothing
   changes.

## Verification (2026-10-04, Linux, RADV, headless captures)

- Host suite: `ctest --test-dir remake/foundation/build/linux --output-on-failure` —
  **30/30 pass** (29 before this change + `view_layout_test`).
- `view_layout_test` pins the cell geometry at 800×600, 1920×1080, 3440×1440, 1080×1920 and
  1373×777 (inside, disjoint, exact tiling, 1-px bars at 800×600), the controller-keyed
  assignment (COM allocates no view, no-human fallback, slot order), per-view projection into
  each view's own aspect, the synthetic pad pattern, and the acceptance guard: a real `Match`
  stepped once per tick with 1 view and with 4 views ends in identical fighter/economy state
  with identical tick and audio counts.
- `hud_layout_test` covers per-view HUD layout (400×300 quadrant = exactly the original's 0.5
  scale, 960×540, 1720×720, 540×960, odd sizes): anchors stay inside the view, centre anchors
  are the view's centre, edge anchors are the view's edges.
- `arena_camera_test` §7 covers per-view cameras: two views follow different fighters, cycling
  one view's lock leaves the other's index and eye untouched, and each projects its own cell
  aspect.
- Single-view parity (pristine `HEAD` build in `/tmp` vs this branch, `cmp` on the PPMs):
  `--match` scripted capture, `--versus` vignette, `--screen=battle` at 800×600 and 1920×1080,
  and `--hud-test` are all **byte-identical**.
- Asset-backed split-screen runs (`--headless`, real install, real stage/characters):
  - two humans, 800×600: two 400×300 views at TL and BR, separate HUD values
    (`main=6/charge=2` vs `main=30/charge=4`), cross separators, 7 shots;
  - three humans, 800×600: the four-cell grid with controller 3's (COM) cell left empty;
  - four humans, 1920×1080: four 960×540 views, 142 melee hits / 105 shots over 10 610 ticks,
    one KO credited (`balloon 21%/0%`), round over at frame 10 800 (time limit, side 0), and the
    front end advanced to the result/quote screen — the 2v2 loop completes;
  - ultrawide 3440×1440 (two and four views) and odd 1373×777 (two views): cells
    `1720×720` / `686×388`+`687×389`, each view with its own camera and HUD;
  - one windowed Wayland run (`--local-players=2`, 960×540 window) to exercise the window path:
    two 480×270 views with independent HUD values, 64 Hz logic ticks independent of the 1500
    renders.
- Not verified: physical gamepads (none attached — the runs above are synthetic input), an
  interactive window resize/fullscreen toggle, and any non-Linux target execution.

## Commands used

```bash
# host suite
ctest --test-dir remake/foundation/build/linux --output-on-failure

# two humans, 800x600, capture at frame 900 (180 of them are the countdown)
./build/linux/foundation_demo --headless --install=<game-dir> --screen=battle \
  --local-players=2 --script=tests/scripts/split-two-human.txt \
  --frames=900 --out=/tmp/two.ppm --size=800x600

# four humans, 2v2, 1920x1080
./build/linux/foundation_demo --headless --install=<game-dir> --screen=battle \
  --local-players=4 --frames=3200 --out=/tmp/four.ppm --size=1920x1080

# the same with a window instead of a capture
./build/linux/foundation_demo --install=<game-dir> --screen=battle \
  --local-players=2 --script=tests/scripts/split-two-human.txt --frames=1500
```

The per-view evidence is the `[split]` block the host prints every 128 match ticks and on the
capture frame: layout, view count, target size, then each view's controller, fighter, cell,
HP, MAIN/CHARGE stocks, stamina, hyper name/gauge and target/ring-pulse flags.
