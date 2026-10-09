# Linux release checklist — the offline versus gate (issue #23)

> What this is: the reproducible evidence that the Linux playable release is
> releasable, plus the honest list of what this machine could **not** verify.
> A second person should be able to follow it top to bottom and get the same
> numbers; every command below was run on 2026-10-05 for this document, and
> the decisive lines of each transcript are quoted with the result.
>
> The release package itself (the `daybreak` launcher, the archive and its
> contents) is issue #22 and is documented in
> [`package/README-LINUX.md`](../package/README-LINUX.md). This checklist
> gates the *playable* claim: the front end, the matches, the assets and the
> environments.
>
> **Synthetic input is not physical-controller evidence.** Every run here is
> driven by a script file plus `--local-players`, which fills the pad-less
> controllers with a deterministic synthetic pattern. A physical pad *was*
> attached to this machine — its owner was using it for another game while the
> gate ran — and no run here drives it: issue #29 made a verification run ignore
> physical devices by default (§3.0), which is why the commands below no longer
> carry `--no-devices`.

## 0. What the gate demonstrates

| Acceptance item (issue #23) | Where it is proven |
|---|---|
| Two humans, title→selection→stage→VS/countdown→battle→results→selection | §3.1 |
| One human with COM | §3.2 |
| Four-fighter match, repeated rounds | §3.3 |
| Repeated rounds (rematch) for stability | §3.1–§3.3 (three rounds each), §6 (five rounds) |
| CI passes host tests | §2 |
| All legal character/weapon choices swept | §4 |
| Stages swept, texture baseline retained | §4 |
| Wayland / X11, pacing, resize/fullscreen | §5 |
| Frame times, crash and resource stability | §6 |
| Documented environments match the evidence | §7 |

## 1. Build and package

```bash
./remake/foundation/build.sh deps          # once; pinned third-party sources
./remake/foundation/build.sh linux         # the warm build used below
```

Expected: the build ends with `Linking CXX executable foundation_demo`, exit 0.
`build.sh linux` also builds every host test binary (`build/linux/*_test`).

The release archive (issue #22) and its launcher:

```bash
./remake/foundation/scripts/package_linux.sh
./remake/foundation/tests/launcher_test.sh ./remake/foundation/package/daybreak
```

Expected: the packaging script stages `build/package/daybreak-<version>-linux-x86_64/`
and the tarball (measured: `daybreak-0.1.0-linux-x86_64.tar.gz`, 19M,
sha256 `769d9b7bfdd350d5b6608dc49278f21e2a43a2e56333b27a81dd89bbc11e3cf5`),
and proves both release claims (no game data in the artifact; `ldd` resolves
every library inside the package or from the base system).
`launcher_test.sh` ends with `launcher_test: 38 checks, 0 failure(s)`; it drives
a sandbox package whose binary is a stub, so it needs no device, display or game
data. It is also registered in the host suite (`ctest -R launcher_test`). (Issue #36
extended this suite and `user_settings_test` — no suite was added, which is why the
§2 count below is unchanged.)

## 2. Host suite (the CI job runs exactly this)

```bash
ctest --test-dir remake/foundation/build/linux --output-on-failure
```

* **With the game install present**: `100% tests passed out of 65`
  (re-measured 2026-10-09; 63 was the 2026-10-06 measurement: 61 came from issue #4's three
  delivery suites, 58 from issue #56's `hud_view_geometry`, 57 from issue #50's
  `pause_overlay_layout_test` and `pause_overlay_panel`, 55 from issue #39's
  `live_camera_smoothness_test`, 54 from issue #48's `debug_keys_test`, 53 from issue
  #47's `countdown_overlay_test`, and 52 from issue #51's `lock_switch_camera_test`;
  issue #21 row 1 adds `shadow_map_test` and `character_shadow`). The Ginkiha port's
  `ginkiha_tables_test` (docs/reports/ginkiha-port-plan.md §1, Fase 0) is the 65th:
  device-free AND data-free, so it neither skips without an install nor changes which
  tests skip, and it pins the generated `ginkiha_tables.h` against the bundle.
* **Without any game data** (the CI runner's state — no `Higurashi-Daybreak/`):
  the same six tests go `Skipped` (exit 77) — `hud_cell_scale`, `toon_ramp`,
  `npr_experiments`, `npr_normals_test`, `controller_scene_lifetime_test` and
  `device_isolation_test` — plus issue #50's `pause_overlay_panel`, which renders a real
  paused battle, and issue #56's `hud_view_geometry`, which renders a real four-view
  battle, so both skip themselves with those six, making eight; with
  `weapon_definition_test` skipping its
  fully-skipped sweep, which was the measured 50-test shape of 2026-10-06.
  #43's `select_row_slidein_test` is device-free AND data-free (no install, no
  adapter, no screen), so it neither skips nor changes which tests skip: the
  no-data count is that measurement plus one, 51 — not re-measured here, because
  the shared install symlink must not be hidden to produce it. CI needs no
  copyrighted data. #51's `lock_switch_camera_test` and #47's `countdown_overlay_test` are
  in that same class (the first compiles `src/main.cpp` and drives `tickMatch` with a
  hand-built match; the second draws the real countdown screen through a device-less
  `SpriteRenderer` and asserts on the pushed batch), so neither skips nor changes which
  tests skip: each adds one to both counts, which is how 51 became 53, and the six
  skipping tests are unchanged through #39's `live_camera_smoothness_test` (55 registered,
  the same 55 with six Skipped without data). #50's `pause_overlay_layout_test` is in that
  same device-free class (it calls `ui::computePauseOverlayLayout` and nothing else), so it
  adds one to both counts; its `pause_overlay_panel` needs the install and joins the skip
  list above. #56's `hud_view_geometry` is the same capture class as `hud_cell_scale` (it
  renders a real four-view battle and reads the frame), so it too needs the install and
  joins that list. Issue #4 added three suites and no skips: `web_delivery_test` (the
  self-hosted service — prepare, catalog, verify and the same-origin HTTP surface, all
  against synthetic `.DAT` bundles the test writes itself), `web_assets_test` (the
  host-testable half of the web asset client) and `web_catalog_order` (the archive
  ordering compared against the native reader; its hermetic half needs no game data and
  its install half skips itself with the others). Issue #21 row 1 then added
  `shadow_map_test`, which is device-free AND data-free (it links glm and nothing else) and
  so adds one to both counts, and `character_shadow`, which renders frames like `toon_ramp`
  and joins the skip list above. The merged count is therefore **63 registered**, with
  **eight** Skipped in a data-free tree.
  The denominator is the number of *registered* tests and grows whenever a suite is
  added (42 when this document was written, 45 when #28 re-measured it, 50 after
  #42's `bgm_loop_test`, #45's `frontend_lifecycle_test` and #46's
  `controller_scene_lifetime_test`, 49 after #29's `device_isolation_test`, 51 after
  #43's `select_row_slidein_test`, 52 after #51's `lock_switch_camera_test`, 53 after
  #47's `countdown_overlay_test`, 54 after #48's `debug_keys_test`, 55 after #39's
  # `live_camera_smoothness_test`, 57 after #50's two pause-overlay suites, 58 after
  # #56's `hud_view_geometry`, 61 after #4's three delivery suites, 63 after #21 row 1's
  # `shadow_map_test` and `character_shadow`), so
  read the command's own summary rather than this line when the two disagree —
  the invariant to check is *100% passed* with the asset-dependent tests Skipped
  and none Failed. Issue #40 added no suite: its device-free half (the recovered
  movie-skip key set and the opening scene's host seam) is 12 more checks inside
  the existing `screen_stack_test`, so the denominator is unchanged and the
  movie itself needs the install — its evidence is a local run
  (`docs/MEDIA-INPUT.md` §3.1). Issue #32 added no suite either: the recovered shot visual
  is 7 more checks inside the existing `effect_catalog_test` (126 with the install) and 4
  inside the existing `weapon_definition_test` (747 with the install, including its new
  asset-backed sweep), so the denominator is unchanged at 57 and the with-install count
  above is re-measured.

The workflow (`.github/workflows/build-foundation.yml`, Linux job) runs this
`ctest` step on every push to `main` that touches `remake/foundation/**` (issue
#28), so a broken test cannot sit on `main`. The same workflow's Windows and Web
jobs stay on the version-bump path: a `gate` job diffs the push and runs them when
`remake/foundation/VERSION` changed anywhere in it, or on a manual dispatch.

## 3. The acceptance runs (deterministic, real assets)

All four use the committed scripts under `tests/scripts/`, run from
`remake/foundation/`. They are **capture runs**: `--headless --out --frames`
steps one logic tick per rendered frame (the demo prints
`logic: N ticks, explicit capture cadence`), which is what makes the tap
ticks in the scripts exact and the run reproducible. Run them with a warm
page cache; each takes seconds to a minute.

> **These four recipes DO NOT REPRODUCE as written (issue #63).** `75e69c3` corrected the stage
> page's time-limit default from a port-chosen 180 to the original's **0 = infinite**, and the
> scripts' stage-page taps are relative to that default: the 1v1 script's two LEFT presses used
> to reach 60 s and now reach 180 s. Every gate's round is therefore longer, ends by balloon
> burst instead of time up, and the 4p gate's `--frames=9600` no longer lands on a capturable
> frame (it prints `RESULT: ok` and writes no PPM). **The ladders and digests below are the
> PRE-fix values, kept because they are what the gate is meant to return once issue #63
> re-calibrates the scripts** — do not re-record them to match the current behaviour, which is
> the fix's side effect and not the gate's contract.

The four are §3.1 (§3.1's 1v1), §3.2 (com), §3.3 (2v2) and the four-player
loop, whose command is:
```bash
./build/linux/foundation_demo --install=<game-dir> --screen=title \
  --local-players=4 --script=tests/scripts/frontend-4p.txt \
  --headless --out=/tmp/rel-4p.ppm --size=1280x720 --frames=9600
```

**`<game-dir>` has a working form, and copying the recipes literally does not
give it.** Run from `remake/foundation/`, the install is at the *worktree root*,
so the path is `--install=../../Higurashi-Daybreak` (or an absolute path).
`--install=Higurashi-Daybreak` exits 1 with `no game data in
"Higurashi-Daybreak"` — the bare name only resolves when the working directory
is the repo or worktree root.

**Do not elide `--headless` when repeating a recipe.** §3.4's own warning
applies: a windowed run steps at the real 64 Hz clock instead of one logic tick
per rendered frame, so it still prints `RESULT: ok` on a *different* ladder and
the tick numbers below no longer mean anything. The shorthand in §3.1-§3.3
("same with …") assumes every flag above it is carried.

**Hashes quoted for these runs are the first eight hex digits of `sha256sum` of
the written PPM.** An `md5sum` prefix of the same file is different — for the
1v1 and 2v2 gates, sha256 `8cc49e6c` against md5 `3e4e892a` — so never compare
one against the other. (This convention was implicit until it cost two readers
an afternoon; the two digest families were being mixed with only the md5 ones
labelled.)

### 3.0 Why a verification run ignores the physical devices (and when to ask for them)

SDL reports a connected controller whether or not the window has focus, so on a
machine where another application is using a pad, that pad's live input reaches
this port's menus and captures. It was measured on the gate machine (an 8BitDo
Ultimate 2C attached): with the owner playing another game, a
`--screen=title --local-players=2` run selected the title's *story* item instead
of *versus* because the pad's state moved the cursor first, and `hud_cell_scale`
failed because the pad changed the match the capture measured.

**A verification run owns every input slot by default** (issue #29; a port rule,
not recovered behaviour — the original has one focused window and reads whatever
the OS reports). A run is a verification run when it produces evidence rather
than being played: `--headless`, any `--out=` capture, `--script=`/`--script2=`,
`--match`, `--versus`, `--hud-test`, `--bench=` or `--list`. In such a run the
keyboard and every gamepad are ignored — the polled device state, the key/pad
events the app forwards, and the SDL event queue the backend harvests alike — so
the script drives controller 0 and `--local-players`' synthetic pads drive the
rest. `--devices` asks for the physical devices back in one of those runs, and is
then the only way a capture can be driven from real hardware.

`--no-devices` still works and still means the same thing. It is redundant inside
the set above and meaningful outside it: a **player** run (a plain `--screen=`
run, the asset viewers, or `--local-players=N` without a capture or a script)
reads the devices it is played with, and `--no-devices` silences one of those.
Passing both flags is rejected.

**An unfocused window also accepts no input** (the same issue): while the window
is unfocused every device reads as released, and input re-arms on
`SDL_EVENT_WINDOW_FOCUS_GAINED`. Focus starts as *focused*, so a compositor that
never delivers a focus event — or a `--headless` run with no window at all —
cannot leave the game unresponsive. The device itself is never relinquished: an
unfocused pad keeps its slot, because a slot reported empty would be handed to a
synthetic pad and the game would play itself.

The commands below therefore do not pass `--no-devices`: the capture flags imply
it (the flag is still accepted, and the transcripts quoted in §3.1–§3.3 are the
ones those gate runs produced). The regression test is
`tests/device_isolation_test.cpp`: it drives the demo's own SDL entry points,
injects device events into a headless capture through `Backend::note_key` /
`note_gamepad_button`, a pushed `SDL_EVENT_KEY_DOWN` and a real SDL virtual
gamepad, and asserts the frame hash and the scene ladder did not move — while a
`--devices` row proves the same injection does move them. The host suite's
demo-driving tools (`hud_cell_scale`, `showcase`, `pin_viewpoint`) still pass
`--no-devices` explicitly, which is what keeps them green on a machine with a pad
in use. It is a verification instrument, not a feature.

### 3.1 Two humans, 1v1, three rounds

```bash
./build/linux/foundation_demo --install=<game-dir> --screen=title \
  --local-players=2 --script=tests/scripts/frontend-1v1-rematch.txt \
  --headless --out=/tmp/rel-1v1.ppm --size=1280x720 --frames=15500
```

`--local-players=2` opens two local views: controller 0 is the keyboard,
driven by the script, and controller 1 is the synthetic pad that reaches the OK
cell and keeps the stage-page timing. What the transcript must show (quoted from
the run):

```
[menu] scene: title (tick 0)
[menu] scene: select (tick 34)
[menu] scene: vs (tick 446)
[menu] battle: 2 fighters on data/stage04 (time 60s, health 50%, gauge 100%, balloon 40%/40%)
[daybreak] match: round over, side 1 wins (time up) at frame 3600
[result] side 1 pair 2-2 grade 3 margin 0 script data/scenario/win/02-02-3.txt persona 0/0 voice W02-02-7.wav
[menu] scene: result (tick 4382)
[menu] scene: select (tick 4984)
[menu] scene: vs (tick 5310)                       <- round 2 (rematch)
[menu] battle: 2 fighters on data/stage06 (time 60s, health 50%, gauge 100%, balloon 40%/40%)
[daybreak] match: round over, side 1 wins (time up) at frame 3600
[result] side 1 pair 12-12 grade 3 margin 0 script data/scenario/win/12-12-3.txt persona 0/0 voice W12-12-7.wav
[menu] scene: result (tick 9246)
[menu] scene: select (tick 9848)
[menu] scene: vs (tick 10174)                      <- round 3
[menu] battle: 2 fighters on data/stage15 (time 60s, health 50%, gauge 100%, balloon 40%/40%)
[daybreak] match: round over, side 1 wins (time up) at frame 3600
[result] side 1 pair 11-11 grade 3 margin 0 script data/scenario/win/11-11-3.txt persona 0/0 voice W11-11-7.wav
[menu] scene: result (tick 14110)
[menu] scene: select (tick 14712)
RESULT: ok
```

> The tick ladder, the stages and every round's settings are stable, and those are
> what this section checks. The **outcome lines are not**: rounds 2 and 3 were
> re-measured on 2026-10-06 (the block previously quoted `side 0 wins` for round 2
> and carried no result line for either). Side 1 wins all three here because the
> red fighter is the OK path's random COM roll and the script only drives P1 — a
> different roll changes the winner, the `pair`, the `script` and the `voice`
> together, by design. Read the ladder, not the winner.

The `[split]` blocks prove who fought, in which view:

```
[split] layout=two views=2 target=1280x720 roster=2
[split]   p0 panel=0 team=0 1P Rena 0 role=owner ...
[split]   p1 panel=2 team=1 2P Keiichi 1 role=enemy ...
```

Every round keeps the same *settings* and ends at the 60 s time limit (match
frame 3600); the **stage is re-rolled per round** (entering the select scene
resets `FrontendState::stage` to 0 = random), which is why the three rounds run
on stage04/06/15. The **selection is re-made per round**: entering the select
scene starts an empty selection (issue #45, `FUN_00408330:143-158`), so a
rematch round replays the panel taps before it walks the stage page (§3.4).

The red fighter is the OK path's first random COM roll, not the synthetic pad's
pick: the pad's own select panel is the grid's start cell (panel 1 for
controller 1, `syntheticMenuStartPanel`), which the duel pair {0,2} discards in
`enterFrontendBattle`, so panel 2 is filled by `FUN_0040d130`'s COM roll —
measured `Keiichi 1` = character 2 / weapon 1, exactly the first draw of
`FrontendState::nextRandom` from its seed. It is re-rolled on every fresh
selection (measured `Kasai 0`, then `Chie 1`); the pad's job in this gate is the
OK cell and the stage-page timing.

### 3.2 One human with COM, three rounds

```bash
./build/linux/foundation_demo --install=<game-dir> --screen=title \
  --local-players=1 --script=tests/scripts/frontend-com-rematch.txt \
  --headless --out=/tmp/rel-com.ppm --size=1280x720 --frames=15500
```

There is no synthetic pad here, so the script walks P0's own panel, steers to
the OK cell and confirms; the OK path fills the panels no human walked with
the original's random COM picks (`screen_select.cpp`, `FUN_0040d130`). The
transcript shows the same tick ladder as §3.1 (`34/446/4382/4984`, then
`5310/9246/9848`, then `10174/14110/14712`) with:

```
[menu] battle: 2 fighters on data/stage04 (time 60s, health 50%, gauge 100%, balloon 40%/40%)
[daybreak] match: round over, side 1 wins (time up) at frame 3600
[result] side 1 pair 11-11 grade 3 margin 21 script data/scenario/win/11-11-3.txt ...
[split] layout=single views=1 target=1280x720 roster=2
[split]   p0 panel=0 team=0 1P Rena 0 role=owner ...
[split]   p1 panel=2 team=1 COM Chie 0 role=enemy ...
```

`COM Chie 0` is the COM opponent the OK path rolled for round 1; the single view
is the one human's own camera. Every round re-enters an empty selection, so the
OK path rolls again (`Chie 1`, then `Irie 2` measured) — the COM opponent, like
the stage, is per round.

### 3.3 Four fighters (2v2), three rounds

```bash
./build/linux/foundation_demo --install=<game-dir> --screen=title \
  --local-players=4 --script=tests/scripts/frontend-2v2-rematch.txt \
  --headless --out=/tmp/rel-2v2.ppm --size=1280x720 --frames=15500
```

Four synthetic pads walk panels 1–3 while the script walks panel 0. The
roster, the four views and the per-round loop:

```
[menu] battle: 4 fighters on data/stage04 (time 60s, health 50%, gauge 100%, balloon 40%/40%)
[split] layout=four views=4 target=1280x720 roster=4
[split]   p0 panel=0 team=0 1P Rena 0 role=owner ...
[split]   p1 panel=1 team=0 2P Keiichi 0 role=ally ...
[split]   p2 panel=2 team=1 3P Rika 0 role=enemy ...
[split]   p3 panel=3 team=1 4P Mion 0 role=enemy ...
[daybreak] match: round over, side 0 wins (time up) at frame 3600
[result] side 0 pair 0-2 grade 4 margin 21 script data/scenario/win/00-02-4.txt ...
[menu] scene: result (tick 4382)
[menu] scene: select (tick 4984)
[menu] scene: vs (tick 5310)                       <- round 2 (rematch)
[menu] battle: 4 fighters on data/stage06 (time 60s, health 50%, gauge 100%, balloon 40%/40%)
[daybreak] match: round over, side 1 wins (time up) at frame 3600
[result] side 1 pair 1-4 grade 3 margin 1 script data/scenario/win/01-04-3.txt ...
[menu] scene: result (tick 9246)
[menu] scene: select (tick 9848)
[menu] scene: vs (tick 10174)                      <- round 3
[menu] scene: select (tick 14712)
RESULT: ok
```

The four picks are the pattern's documented distinct roster entries
(`0/2/4/1` = Rena/Keiichi/Rika/Mion), each with weapon slot 0 — every fighter
is a character+weapon combo, never a bare fighter. The pads re-pick exactly
those four in every round, because a rematch round's selection starts empty.

### 3.4 The scripts' own rules (read before editing them)

* Ticks are **front-end logic ticks**; the capture path runs exactly one per
  frame, so tap ticks are exact.
* Round 1 is the measured cycle of `tests/scripts/frontend-4p.txt`. A rematch
  round re-picks its panels first — entering the select scene starts an empty
  selection (issue #45, `FUN_00408330:143-158`) — and then walks the stage page
  to START. Only the *value* taps are left out: the stage page's settings live
  in the original's process globals (`DAT_006cf3c0` / `3b8` / `3bc` / `3b0` /
  `3b4`) and persist across entries, so replaying them would wrap them
  (measured: a rematch that replayed them played 240 s/175 % where round 1 had
  60 s/50 %).
* The taps that re-pick a panel open with an explicit release: the previous
  round's battle taps leave Jump held into the selection screen, and a held
  button is not a press edge.
* The synthetic pads stay neutral while the stage page is open, and they walk
  their own panels on every entry (a fresh selection always has one to pick).
  An extended run (the prolonged row of §6, `frontend-2v2-longrun.txt`) repeats that
  block per round; it reaches five rounds, not eight -- see that row.
* **A windowed (live) run is not the same clock.** The live loop steps the
  simulation at 64 Hz, while a capture steps once per rendered frame, so a round
  lasts 3840 ticks there and 3600 here: the rematch blocks above (whose offsets
  are measured in capture ticks) no longer line up after round 1. Use the
  capture path for round-by-round evidence; §5's windowed runs verify the window
  path itself (present, pacing, 64 Hz logic) and use the battle-screen script.

### 3.5 The live path (issue #39): what a capture cannot see

**A capture is not a live run, and the difference hid a real defect.** The camera
defect fixed in `92b6d70` survived twenty-odd issues of verification — every
capture below, this whole host suite and the owner's own measurements — because
the capture path renders with `app.matchAlpha = 1` (D9's one-update-per-frame
recipes) while `buildFrameViews` draws `glm::mix(previousEye, camera.eye(),
matchAlpha)`. At alpha 1 that mix returns the current camera unchanged, so a
capture was byte-perfect while a *played* battle swept the camera between the
match's opening pose and the converged one on every frame (measured live: 19-938
units/frame, median 387; after the fix ~4.2 units/frame). Anything that lives in
presentation-time interpolation, per-frame smoothing, alpha blending or
input-driven per-frame state is invisible to a capture for the same reason.

Two things now cover it, and the first is the gate:

```bash
./build/linux/live_camera_smoothness_test
```

`tests/live_camera_smoothness_test.cpp` compiles `src/main.cpp` into its own TU
and composes frames the way the frame loop does — `gameplay::FixedStep` decides
the tick count and the presentation fraction, `tickMatch` steps the match,
`buildFrameViews` builds the frame — then asserts on `FrameView::camera.eye`,
the frame-view state the renderer consumes, not on pixels. Device-free,
window-free and data-free (the fighters carry a synthetic Rena 1 combo). With the
camera settled on a stationary, non-turning followed fighter, consecutive live
frames must not move the rendered eye by more than **5 units**:

```
  measured 1v1, two views, 60 Hz ...: 399 frames x 2 view(s), alpha 0.000..0.933, ticks/frame 0 zero / 26 multi
             rendered eye max step 0.0000 units, camera eye max step 0.0000, fighter drift 0.0000 (facing 0.0000 rad)
  consecutive rendered frames do not sweep the camera eye          ok  (measured 0.000, limit 5.000)
  ... the same at 144 Hz (frames with no tick) and 30 Hz 2v2 (two ticks per frame)
```

The check fires on the real defect: with `92b6d70`'s `previousEye` advance
reverted on a scratch copy, the same binary run reports
`rendered eye max step 1282.8557 units` at 60 Hz (763.6 at 144 Hz, 1228.3 for the
4-view 2v2) and exits 1 — while the camera's own eye and the followed fighter are
still exactly static, which is the defect's signature and nobody's else's.

The second is the mode a capture can use. `--match-alpha=<0..1>` renders every
headless frame at a fixed presentation fraction instead of pinning it to 1, so a
capture sees the interpolation the live path sees:

```bash
./build/linux/foundation_demo --install=<game-dir> --headless --match \
  --stage=data/stage21 --character=data/rena --enemy=data/mion \
  --frames=3 --size=400x400 --match-alpha=0.5 --out=/tmp/live-alpha.ppm
```

Measured on that recipe: `--match-alpha=0.5` moves 74% of the pixels against the
same command without it (mean |dRGB| 21.3 — the camera moved), `--match-alpha=1`
is byte-identical to no flag at all (`f80d0368`), and a value outside `[0,1]` is
rejected with `RESULT: --match-alpha takes a fraction in [0,1]`. **With the flag
absent nothing changes**: the four §3 gates re-run after this landed produced the
same `RESULT: ok` ladders and byte-identical final captures (4p `14305bc9`, com
`b813155d`, and 1v1/2v2 share `8cc49e6c`). The sharing is real but the obvious
reason for it is not: 1v1 and 2v2 are byte-identical because both end on the
**stage-select page** of the selection screen, while com's one-player run ends
on the **character-panel page** (74.8 % of pixels differ between the two) and
the 4p gate ends on the **result screen** at tick 9520. Why a one-player run
lands on a different page was not chased — the observation is verified, the
causal clause is not.

**The manual floor stays.** The test drives the product's own live composition,
but it is not a window: no compositor, no real frame pacing, no physical device
and no user input. The step that covers those is still a played battle — run
`--screen=battle --local-players=2` for 30 s and confirm the camera settles
behind the fighter instead of sweeping, then take a hit and confirm it stays
settled. That is the only part of this class a headless run cannot own.

### 3.6 Which baselines the random-character pick moved (the four-player gate)

The character select's off-diamond cursor now **rolls a random character** instead of leaving
the panel unset (`src/ui/screen_select.cpp`, the original's random pick at
`FUN_00409340:305-317`), so any script whose taps take a cursor off the grid picks a different
roster and its final frame moves. **The four-player gate is the only one affected**:

| recipe | before | after |
|---|---|---|
| 4p `frontend-4p.txt` | `2483c3aa…` | **`14305bc9…`** |
| 1v1 / 2v2 `frontend-1v1-rematch.txt`, `frontend-2v2-rematch.txt` | `8cc49e6c…` | unchanged |
| com `frontend-com-rematch.txt` | `b813155d…` | unchanged |

**One gate moves, because its script takes a cursor off the diamond**: the roll consumes RNG, so
the roster the script settles on differs and so does the frame. Its ladder and roster are
unchanged and the new digest is deterministic (reproduced twice).

**The com gate moved and came back, which is worth recording as a lesson.** While the roll's
display field was value-initialised to 0 — a real character, Rena — every panel with no pick
drew Rena's portrait from the moment the screen opened, and com's frame moved to `57044cfb`.
Fixing that initialisation to `-1` restored `b813155d` exactly. **A digest that moves is
evidence about the change, not noise to be re-recorded**: re-measuring the baseline is the last
step, not the first, and here it would have written a bug into the gate.

The 4p **ladder and roster are unchanged** (`0/34/446/4382/4984/5584/9520`; `round over, side 0
wins (time up) at frame 3600`, then `side 1 balloon burst`), and the new digest is
**deterministic** — reproduced twice. Only the frame differs, because the roster the script
settles on differs. The three gates that never leave the diamond are byte-identical, which is
the useful half of this table: it shows the change is confined to panels that actually go
off-grid.

### 3.7 Which baselines the sprite batch's per-pass vertices moved (issue #56)

`SpriteRenderer` gave every pass in a frame the same vertex buffer, written at offset 0 by
each `render()` call, and a frame's queue writes all land before its single submission — so
a pass read the last pass's geometry plus the tail of the longest earlier one. The fix gives
each `render()` call its own region, addressed by binding the vertex buffer at that region's
byte offset (the uniform path's own rule, `src/ui/sprite.h`). The unpaused **single-view**
path writes and binds region 0 exactly as it wrote and bound the whole buffer, so it is
**byte-identical**; **multi-view** frames deliberately move, because they were reading
another view's geometry before.

| recipe (from `remake/foundation/`, install via `--install=`) | before | after |
|---|---|---|
| `--screen=battle --local-players=1 --frames=300 --size=960x540` | `db392ca6` | `db392ca6` (identical) |
| `--match --stage=data/stage03 --character=data/rena --enemy=data/mion --frames=300 --size=800x600` | `10f6cbbd` | `10f6cbbd` (identical) |
| `--screen=title --frames=200 --size=1280x720` | `a88d4de4` | `a88d4de4` (identical) |
| `--screen=battle --hud-test --frames=5 --size=800x600` | `e9c61969` | `e9c61969` (identical) |
| `--screen=battle --pause-overlay=300 --frames=481 --size=960x540` (#50's overlay) | `ea373b57` | `ea373b57` (identical) |
| `--versus --stage=data/stage03 --character=data/rena --enemy=data/mion --frames=200 --size=800x600` | `0d0e8dd9` | `0d0e8dd9` (identical) |
| `--screen=battle --local-players=2 --frames=300 --size=960x540` | `cf7983a7` | `60ce8237` (**moves**) |
| `--screen=battle --local-players=4 --frames=300 --size=960x540` | `e3e9c445` | `0f30fad5` (**moves**) |
| `--screen=battle --local-players=4 --frames=300 --size=1280x720` | `afba09df` | `09f0da41` (**moves**) |
| `--screen=battle --local-players=4 --pause-overlay=300 --frames=481 --size=960x540` | `6162d455` | `6e27d5ac` (**moves**: the frozen HUD under the overlay) |

Hashes are the first eight hex digits of `sha256sum` of the written PPM. The four §3 gates
end on a single-view frame (the result or the selection screen), so all four keep their
documented final captures exactly — 4p `14305bc9`, 1v1 `8cc49e6c`, 2v2 `8cc49e6c`, com
`b813155d` — and their `[menu] scene` / `[split]` ladders are unchanged. §4.2's sweep is
`--match` without `--local-players`, so it is single-view and its problem counts cannot move
either.

What moved is the reticle: in the 960x540 four-view frame, 12,874 of 518,400 pixels (2.48%),
by cell 6,062 / 2,882 / 3,388 / 542 — the FIRST view loses the most because it was reading
the last view's geometry for everything but its two separator quads, and the LAST view loses
the least because it was reading its own. The test that pins it is
`tests/hud_view_geometry.py` (host suite, `ctest -R hud_view_geometry`): it asserts that
every participant's reticle is in the frame at **that view's own** ring anchor, printed by
the demo's own `[split]` line, and that the reticle at each cell's centre is within 8 px of
that cell's own fighter's anchor. Before the fix it fails on five anchors (0 red reticle
pixels at each, against 67-74 after) and on the centre reticle of the first view, whose
centroid sits 18.5 px from its own anchor and 0.6 px from the last view's. `hud_cell_scale`
cannot express this: it probes markers every pass pushes at identical coordinates.

Reticle correction (2026-10-09): the original gameplay prints and the owner's
report establish no reticle on the active player, green allies and red enemies.
The counter-rotating triangles belong only to a mutually targeted enemy. The
current geometry gate therefore measures eligible ally/enemy anchors in their
team color; the owner-centroid assertion above records the earlier issue #56
test and is retired. A host rule matrix checks owner suppression, both colors
and one-way versus mutual locks; the asset-backed scene test checks that mutual
targeting reaches the opponent's HUD entry through the product's view builder.

## 4. Asset sweep — every legal selection and every stage

### 4.1 All 46 character/weapon selections

```bash
./build/linux/weapon_definition_test            # with the install reachable
```

Expected tail:

```
  46 legal selections (14x3 + 2x2)                               ok
  every legal selection's item file parses                       ok
  all 46 legal selections ran a match                            ok
WEAPON_DEFINITION: ok (747 checks, 0 failed, 0 skipped)
```

Without an install the sweep skips itself and the test still passes
(`0 skipped` becomes the local-data count; CI's run is the skipped form).

### 4.2 Character × stage texture matrix (the G3 baseline)

```bash
python3 tests/showcase.py --check --allow-problems=43 --out-dir /tmp/sweep
```

Expected summary and the current baseline (re-measured for this checklist;
the tool passes `--no-devices` itself, §3.0):

```
asset check: 16 character(s) x 13 stage(s) -> 208 runs
165 pass, 43 problem(s)
```

The 43 are the **documented install gaps**, unchanged: stage05/stage15 miss 4
dust/particle textures per stage on all 15 other characters (30 cells), and
`kasai` misses its `g` texture on every stage (11 cells at 2 draws + 2 cells
at 6 draws where both gaps overlap). **Zero pipeline failures, and no new
untextured draw**: the loader is doing the right thing on data the install
does not ship. Any new cell in that list is a regression, not a data gap.

## 5. Environments, pacing, resize and fullscreen

Every run below is isolated from the user's desktop: an own
`XDG_RUNTIME_DIR` with a nested `kwin_wayland --virtual --xwayland` session,
plus `gamescope --backend wayland` inside it for the non-60 Hz rates. No
window ever appeared on the real session.

| # | Environment | Command shape | Result |
|---|---|---|---|
| 1 | Headless, Vulkan RADV | the §3 capture runs | `RESULT: ok`, real GPU, no window |
| 2 | Wayland, nested KWin, 60 Hz | `XDG_RUNTIME_DIR=<own> WAYLAND_DISPLAY=wayland-issue23 ./build/linux/foundation_demo --screen=battle --local-players=2 --script=tests/scripts/split-two-human.txt --frames=1500` | `video driver : wayland`, `surface : 960x540 ... fifo=yes`, `present mode : Fifo(vsync)`, `frames : 1500 in 24.931 s`, `delta avg : 16.608 ms (60.2 fps)`, `logic : 1594 ticks, 64 Hz`, `RESULT: ok` |
| 3 | X11, nested Xwayland `:1` | same with `DISPLAY=:1` | `video driver : x11`, `present mode : Fifo(vsync)`, `frames : 1500 in 24.935 s (60.2 fps)`, `logic : 1593 ticks, 64 Hz`, `RESULT: ok` |
| 4 | 30 Hz output | `gamescope --backend wayland -W 1280 -H 720 -r 30 -- <demo> --frames=300` | `frames : 300 in 9.885 s`, `delta avg : 32.927 ms (30.4 fps)`, `logic : 632 ticks, 64 Hz` → **2.11 logic ticks per frame** |
| 5 | High refresh (gamescope `-r 144`) | `... -r 144 -- <demo> --frames=1200` | `frames : 1200 in 6.743 s`, `delta avg : 5.616 ms (178.1 fps)`, `logic : 431 ticks, 64 Hz` → **0.36 ticks per frame** |
| 6 | Fullscreen + resolution change | `--screen=options --script=<options walk>` on Wayland and X11 | Wayland: `[display] requested 1280x720 fullscreen, window now 960x540`, `[display] fullscreen on, window 960x540`, then `[display] requested 640x480 fullscreen, window now 640x480` and `720x480`; X11: `[display] fullscreen on, window 960x540`, then `[display] requested 320x240 fullscreen, window now 320x200` |

Pacing conclusion, stated plainly: the **simulation is 64 Hz regardless of
the render rate** — at 30 fps two logic ticks share a frame, at ~181 fps
roughly one frame in three has none — and every windowed run above presented
with FIFO vsync (`present mode : Fifo(vsync)`), which is the original's
cap-at-refresh behaviour. The 30 Hz and high-refresh rows come from the
demo's own `--frames` summary (wall-clock deltas), not from a stopwatch.

### 5.1 Not verified on this machine (do not read as covered)

* **A second GPU vendor** (NVIDIA/Intel/AMDVLK) — this machine is one
  RADV adapter. What would settle it: the same §3.1 run on each adapter.
* **Physical controllers** — every run uses `--local-players` synthetic pads
  or the script, and no run drives the attached 8BitDo by hand. What would
  settle it: a real pad walking a panel and a battle, with the pad's own
  bindings — a run that asks for the devices (`--devices`, §3.0) plus the
  attached pad.
* **Hardware audio listening** — the audio backend runs (dummy-device
  verification, combat voice/SE counts in the log), but nobody listened on
  real hardware.
* **Other distributions / older Mesa / other compositors** — only CachyOS +
  KWin 6.7.5 + Mesa RADV was exercised. **A windowed run needs the recipe below,
  not a plain background launch**: `kwin_wayland` started naively dies silently
  while leaving its socket file behind, so "the socket exists" proves nothing.
  The working form (issue #24's audit) is a private runtime directory plus a
  session bus:
  ```bash
  export XDG_RUNTIME_DIR=$(mktemp -d)
  setsid dbus-run-session -- kwin_wayland --virtual --xwayland --socket dbd-test &
  export WAYLAND_DISPLAY=dbd-test
  ./build/linux/foundation_demo --install=../../Higurashi-Daybreak --screen=battle \
      --local-players=2 --frames=1500
  ```
  A healthy run prints `present mode : Fifo(vsync)` and `logic : N ticks, 64 Hz`
  and ends `RESULT: ok`; kill the session when done.
* **An interactive compositor-side window drag-resize** — resize was driven
  through the port's own Options resolution list; a mouse drag on the window
  edge was not simulated.
* **A played battle's live camera, by eye** — §3.5's device-free test asserts the
  live *composition* (the fixed-step clock, `tickMatch` and the interpolated
  frame view) and `--match-alpha` lets a capture render that interpolation, but
  neither is a window with a compositor, real pacing or a real device, and no run
  here measures or watches the camera settle in a played battle. What would
  settle it: the §3.5 manual step (30 s of `--screen=battle`, camera settles and
  stays settled through a hit) on a real session.
* **macOS** — nothing has been executed on Apple hardware. What would settle
  it: the §5.2 Windows recipe on a Mac (Dawn ships macos x64/aarch64 prebuilts).
* **Windows and the web** — run for the first time with game data in issue #35;
  §5.2 is that record and it is not a clean bill. Windows reached the title and a
  battle and then faulted in a rematch (issue #57); the web reached both only on
  a locally preloaded rig, and one web path (`?pack=`) still cannot (issue #58).
  Read §5.2 before quoting either target as verified.

## 5.2 Windows and the web, actually run (issue #35)

Every issue in this batch reported "Windows/web build green", and neither artifact
had ever been started with game data: a link-time success says nothing about
startup, asset lookup, fonts, the adapter request or the emscripten file-loading
path. This section is that run. It is a record of what the two targets *do*, and
"verified" below means exactly one rung of this ladder — never a higher one:

| rung | means |
|---|---|
| **compiled** | the cross-build linked |
| **launched** | the artifact started, created a surface and printed the adapter line |
| **title** | the front end loaded its own art/fonts and drew the title screen |
| **battle** | a live match ran: simulation ticks, HUD, camera, draws |
| **played** | a human drove a match with real devices, title to results |

Nothing here is rung 5, on any target. (Linux's §3 captures are rung 4 and its
§3.5 manual step is the rung-5 recipe.)

### Windows — rungs 3 and 4, then a fault

```bash
cd remake/foundation
./build.sh deps && ./build.sh windows
# a) interactive boot (movie -> title), no script: the #40 movie decodes on Windows
wine build/windows/foundation_demo.exe --install=Z:/<abs>/Higurashi-Daybreak --no-devices
# b) front end, three rounds, two humans; --no-devices so only the script drives it
wine build/windows/foundation_demo.exe --install=Z:/<abs>/Higurashi-Daybreak \
  --screen=title --local-players=2 --no-devices \
  --script=Z:/<abs>/remake/foundation/tests/scripts/frontend-1v1-rematch.txt
```

`wine --version` on this machine: **wine-11.19**. Run inside an isolated headless
KWin session (`computer-use`'s default), so no window ever reached the real
desktop. Wine picks its own Wayland driver; the log's own lines:

```
video driver : windows
adapter      : AMD Radeon RX 9070 XT (RADV GFX1201) [Vulkan]
surface      : 960x540, 7 format(s), 3 present mode(s), fifo=yes
[install] game folder: Z:/.../Higurashi-Daybreak (from --install=)
[menu] scene: opening (tick 0)
movie        : data/movie/op.mpg (MPEG-1 system multiplex, 640x480, 29.97 fps, 22.79 s, MP2 44100 Hz stereo)
movie        : ended after 684 frames decoded/684 presented (22.789 s), audio 22.857 s
[menu] scene: title (tick 1485)
[menu] scene: select (tick 34)   # run (b): the script's walk
[menu] scene: vs (tick 446)
[menu] battle: 2 fighters on data/stage04 (time 60s, health 50%, gauge 100%, balloon 40%/40%)
[daybreak] match: round over, side 1 wins (time up) at frame 3840
[menu] scene: result (tick 4634)
[menu] scene: select (tick 5020)
```

What worked: the install's `.dat` bundles load (`assets: 6/6`), the title screen
draws its Japanese text through the bundled Gyrotrope/CJK fonts, the selection,
VS, countdown, live split-screen battle and results screens all render, a round
completes on the time-up rule, and the movie decodes — issue #40's Windows half
had never been executed either.

What did **not** work, in the same run:

1. **Round 2 faulted.** `[moves] fighter 1 (Kasai 0)` is followed by
   `wine: Unhandled page fault on read access to 00007FFFF8483050 at address
   00000001400B3810` — inside `gameplay::CharacterMoves::find(int) const`
   (`x86_64-w64-mingw32-nm`/`addr2line` on the exe). It reproduces in the
   headless capture run (identical recipe, `round over` at tick 4382 then the
   fault at the round-2 rebuild) and in the windowed run, with a *different*
   roster each time; the same recipe, the same roster and the same rematch on
   Linux completes `RESULT: ok`. Filed as issue #57.
2. **The texture fallback killed the process before the first battle** —
   `std::filesystem::u8path` throws on a name that is not valid UTF-8, and raw
   Shift-JIS texture names reach it whenever the bundle lookup misses. Fixed in
   this change (`src/assets/cnv.h`); before the fix the run ended at
   `[moves] fighter 1 (Keiichi 1)` with `terminate called after throwing an
   instance of 'std::filesystem::filesystem_error'`.
3. BGM/voice/`sysse` load from the install and play through SDL3's dummy device;
   nothing listened to real hardware (same limit as §5.1).

### Web — rung 3 (title) and rung 4 (battle), on a local rig

Serving and browser: `python3 -m http.server` on the build directory, Chrome for
Testing 152 through `agent-browser --webgpu` (headless). Adapter, every run:

```
adapter      : google swiftshader [WebGPU(browser)]
surface      : 960x540, 3 format(s), 1 present mode(s), fifo=yes
present mode : Fifo(vsync)
```

**Software WebGPU, labelled as such**: this box has a RADV device, but headless
Chromium's WebGPU is SwiftShader here, so nothing below is hardware-adapter
evidence. Compositor screenshots of a WebGPU canvas are still black; the pixels
were read with `canvas.toDataURL('image/png')` (the §3.3 method) and are real
frames.

Three ways to get game data into the page were tried; only the third reached a
battle, and the first is a defect:

1. **`?pack=` runtime pack (the production delivery path) — no title, no battle.**
   The fetch and mirror half works: `[pack] 766 files, 84.5 MB -> /packs/ from
   http://127.0.0.1:8177/packs/manifest.txt`. But the front end and the fighter
   weapon join address assets as install-relative `data/...` paths, which the
   `/packs/` mount never satisfies, so the front-end gate reports
   `RESULT: no Higurashi Daybreak data found: ... has no data/title/back00.cnv`
   and the standalone match reports
   `RESULT: load failed: P1 /packs/data/rena:0 has no weapon: slot-0 item 1
   unreadable — roster fighters must gear up`. Cross-origin pack hosting also
   fails closed (`RESULT: fetch http://127.0.0.1:8178/...: HTTP 0`) unless the
   pack is same-origin — correct per `WEB-ASSETS-RUNTIME.md` §2, worth knowing
   when reproducing. Filed as issue #58.
2. **`--preload-file <subset>@/assets` (the recipe in `BUILD-web.md`) — now
   aborts.** With the tree's current guard, a roster fighter whose slot-0 item
   cannot be read throws; that recipe's subset has no `item/`, so the launch
   fails. The guard is right (rule 7); the recipe needs updating.
3. **`--preload-file <subset>@/data` — title and battle.** Mounting the subset
   where the port's own relative paths already look (`/data`) is what makes a
   browser run possible at all:

```bash
# once: a local subset (gitignored, never committed), the dirs a match touches
mkdir -p /tmp/dbd-web/rig && cd Higurashi-Daybreak/data
cp -a title select teamselect vs win talk trail scenario chat sysse keyconfig \
      camera config object directX item effect aura bullet/001 bullet/002 \
      stage01 rena mion /tmp/dbd-web/rig/
cp remake/foundation/tests/scripts/frontend-1v1-rematch.txt /tmp/dbd-web/rig/
cd remake/foundation && source ~/emsdk/emsdk_env.sh
emcmake cmake -S . -B build/web-data -GNinja \
  "-DCMAKE_EXE_LINKER_FLAGS=--preload-file /tmp/dbd-web/rig@/data"
cmake --build build/web-data
python3 -m http.server 8179 -d build/web-data
# interactive boot: title screen (and the movie stub, below)
#   http://127.0.0.1:8179/foundation_demo.html
# a live match, no front end:
#   ...?args=--stage=/data/stage01|--character=/data/rena:0|--enemy=/data/mion:0|--match|--frames=4000
```

The match ran: `[scene] /data/stage01: 13 model(s), ..., textures 168 resolved /
0 missed`, both fighters geared as combos (`[weapons] P1 Rena 0: item 001`,
`[weapons] P2 Mion 0: item 002`), `[moves] fighter 0 (Rena 0): /data/rena/00.dat
(122 moves)`, `[moves] fighter 1 (Mion 0): /data/mion/00.dat (134 moves)`, 195
draws (168 textured, 4 decals, 27 outlines) and 143 GPU textures, and the canvas
readback shows Rena with her weapon facing Mion on the schoolyard stage with the
HUD drawn. A 6000-frame scripted front-end run ended `RESULT: ok` (6763-6988
logic ticks at 64 Hz, 53-57 fps).

What did **not** work on the web:

* **The movie is still a stub — and it is a clean, deliberate hole.** Issue #40's
  `#if defined(__EMSCRIPTEN__)` path was compiled and run for the first time
  here. An interactive launch logs
  `[error] [movie] the web build does not decode movies in wasm: the browser must
  play them (HTMLVideoElement/WebCodecs); see remake/foundation/docs/MEDIA-INPUT.md`
  and moves on: `[menu] scene: opening (tick 0)` → `[menu] scene: title (tick 25)`.
  No crash, no silence, exactly the documented gap. It is a gap to close (issue
  #4's asset delivery), not a defect.
* **Exceptions had to be enabled to get this far.** emcc disables C++ exception
  *catching* by default, which made every `try` in the asset layer inert and every
  `throw` fatal: the first missing candidate asset aborted the module with
  `Aborted(Assertion failed: Exception thrown, but exception catching is not
  enabled ...)` where Linux and Wine log the miss and walk on. Fixed in this
  change (`CMakeLists.txt`, `-fexceptions`); cost measured on the same tree:
  `foundation_demo.wasm` 6,249,962 → 8,186,870 bytes (+31%).
* **A scripted front-end run does not leave the selection screen.** The same
  script, the same build settings and the same roster reach VS and a battle on
  Linux and under Wine, but in the browser the run sits on the select screen for
  6000 frames (`menu-audio: confirm=179 back=19 cursor=61 ready=2`): confirms
  arrive, panels rarely latch ready. The canvas readback confirms it frame after
  frame. Filed as issue #59.
* **Missing candidate assets are logged once per frame.** `data/select/p01.cnv`
  (the file ships in `data/teamselect/`) produced 97 error lines in ~2 s on the
  select screen — console spam, not a failure. Filed as issue #60.
* Hardware-adapter WebGPU, real vsync and visual parity remain unverified, as in
  `BUILD-web.md` §"Not verified".

### Cleanup

Every server, browser session and display started for this section was stopped:
the two KWin sessions (`session_stop`, no `wayland-mcp-*` process or socket left),
the `agent-browser` session, and all four `python3 -m http.server` instances.
No window ever appeared on the real desktop.

## 6. Frame times, crashes and resource stability

Capture runs report wall-clock deltas but step one tick per frame, so their
`fps` number is not a pacing measurement; the windowed rows in §5 are. The
numbers to record per scenario (from the demo's own summary):

| Scenario | Command | Frames/ticks | Wall time | Peak live FX cards |
|---|---|---|---|---|
| 1v1, three rounds | §3.1 | 15500 ticks | 10.690 s (pre-#30; **5.273 s** after it) | `peak=2/128`, `dropped=0`, `badEffectId=0` |
| COM, three rounds | §3.2 | 15500 ticks | 12.110 s | `peak=2/128`, `dropped=0` |
| 2v2, three rounds | §3.3 | 15500 ticks | 28.210 s | `peak=3/128` (`4/128` in rounds 2-3), `dropped=0` |
| 2v2, prolonged | `--local-players=4 --script=tests/scripts/frontend-2v2-longrun.txt --frames=40000` | 40000 ticks | 56.694 s | `peak=4/128`, `spawned=93`, `expired=93`, `dropped=0` (re-measured 2026-10-06 after #32) |

(The wall times are from the demo's own summary on a shared machine — the
owner's game was running — so treat them as an upper bound on the capture cost,
not a benchmark. The `logic:` count is the reproducible number.)

**Issue #32 moved the shot out of the card set.** An in-flight shot now draws the bullet's
own model as a direct renderer instance, so it no longer spawns, expires or counts as a live
card; the three rows above were re-measured after that change, and the live-card counters
drop by exactly the shot spawns (same tree, same recipes: 1v1 round 1 `spawned` 58 → 36 and
`peak` 4 → 2; COM round 1 `spawned` 104 → 66 and `peak` 5 → 2; 2v2 round 1 `spawned`
128 → 89 and `peak` 6 → 3). The shot placements themselves are unchanged and are now
reported as `shotModels` (1v1 round 1: 1741, exactly the old `liveShots` count). The
prolonged row was **re-measured** for #32 (it now reads `peak=4/128`, `spawned=93`,
`expired=93`, `dropped=0`) and its script is committed as `frontend-2v2-longrun.txt`, so
those counters are current rather than inherited. The bound it checks is unaffected by #32
in either direction — the same script's round 2 measured `spawned` 124 → 82, `peak` 6 → 4,
`dropped=0`, and the peak can only fall when the shot cards leave the set.

The prolonged run is the long-match stability check: repeated
`match: round over` lines, `RESULT: ok`, no crash, and a bounded FX
population (`dropped=0`, `badEffectId=0`) — the issue #17 acceptance number.

**It reaches FIVE rounds, not eight, and the script says so.** This row used to
name a script that was never committed ("the §3.3 script extended to eight
rematch rounds"), so its counters were unreproducible by anyone else. The
committed `frontend-2v2-longrun.txt` reaches five complete rounds in 40000
frames, with rounds 1-3 reproducing the §3.3 ladder exactly. **Eight is not
reachable by extending the taps**: the replay is provably right for rounds 1-3,
and from round 4 the selection screen stops advancing on time-shifted input
because the menu navigation is **state-dependent** — a fixed `5xJUMP + 6xDOWN +
JUMP` advances rounds 2 and 3 but not 4+. A true eight-round run needs per-round
menu handling in the synthetic pad, which is a follow-up rather than something
to fake here. Sampled `/proc/<pid>/status` during that run:
peak `VmRSS` ≈ 380 MB, peak thread count 14, no upward trend across rounds.

**The COM scenario's cost was measured, named and fixed (issue #30).** It used to
be ~5x slower per tick than the 1v1 (54.030 s vs 10.799 s, three-run means); it is
now **12.110 s vs 5.273 s, a 2.30x ratio**, and the 1v1 itself got 2.05x faster.

The cost was not the script, not the extra views and not the round count — it was
`BotBrain::probe_progress` -> `MovementCollision::move` -> `slideSegment` ->
`firstWallHit`, which walked **every triangle of the movement mesh once per ray**
with no spatial pruning: 39 rays per probe (13 ring samples x 3 body heights),
76,010 rays in one 15500-tick run, **987 faces scanned and 646 tested per ray** —
2.9e9 triangle visits. `setMeshes` now stores each movement triangle's AABB and
`firstWallHit` rejects on a slab predicate before touching the triangle
(`sweepReachesBounds`; a face the horizontal one-stride segment cannot reach holds
no point within it, with a 1e-5 parameter slack so an exact corner graze is kept —
see the note below). Faces per ray fell to **1.18** and intersections to **0.87**.

All 12 PPM captures of the two gate recipes and both `DAYBREAK_CAMINFO` traces are
sha256-identical before and after, so this is a pure cost change. The residual
2.30x is the **probe count** (0.53 probes/tick, ~6.8 ms each), not the query —
closing it would mean changing COM decisions, which are pinned by tests.

**The card counts in the table are lower than they were before issue #32**, which
made the in-flight shot a direct instance instead of an fx card: the shot no longer
occupies a card slot, so `peak`/`spawned` fell (1v1 58->36 spawned, 2v2 128->89)
while the placement tally — `shotModels`, renamed from `liveShots` — still counts
the same shots. The prolonged row's numbers were re-measured for #32, so they are not
inherited from before it.

## 7. What the gate found (and what it now claims)

Three release-blocking defects were found by these runs and fixed in this
issue; each has its own commit and, where a device-free test is possible, a
regression test:

1. **The 1v1 result screen never loaded** — issue #20's two-winner art made
   `loaded()` require both winner sheets, and a one-member winning side (the
   port's 1v1) only loads one. The screen refused, the switcher read the null
   scene as "no scene", and the run ended as a *successful* quit with no
   results screen (`scene: result` missing, `RESULT: ok`). Fixed in
   `src/ui/screen_result.cpp` (+ `winnerPortraitCount` in
   `src/ui/result_quote.h`, regression test in `tests/result_screen_test.cpp`).
2. **A rematch crashed the renderer** — `SceneRenderer::setScene` released the
   previous scene's buffers but kept its `drawTemplates_`/`baseDrawList_`, so
   the first live effect card after a rematch submitted a released vertex
   buffer: wgpu-native panicked with `Buffer[Id(...)] does not exist` and the
   process aborted (exit 134) a few seconds into round 2. Fixed in
   `src/render/scene_renderer.cpp`.
3. **Rematch rounds diverged from round 1** — the synthetic pads' menu clock
   was latched on the first selection screen (so a rematch could not reach the
   OK cell), their roster nudge then moved the *cursor* onto the Back cell
   (the run left to the title), and their directions moved the stage page's
   settings cursor (a rematch played 240 s/175 %). Fixed in `src/main.cpp`
   and `src/input/synthetic_pad.h` (regression test in
   `tests/select_menu_test.cpp`). Issue #45 then removed the nudge's condition
   altogether: a re-entered selection screen is empty
   (`FrontendState::beginSelection`), so the pads always walk their panels and
   the nudge is never a cursor move.

Two evidence gaps were closed as part of the same work: the `[menu] battle:`
line now prints the round's settings, and the display callbacks print what a
fullscreen/resolution request actually did.

## 8. Reproducing the whole gate

```bash
cd remake/foundation
./build.sh linux
ctest --test-dir build/linux --output-on-failure          # §2 (includes §3.5's live-path test)
./build/linux/weapon_definition_test                      # §4.1
python3 tests/showcase.py --check --allow-problems=43 --out-dir /tmp/sweep    # §4.2
for p in 2 1 4; do                                        # §3
  case $p in 2) s=1v1;; 1) s=com;; 4) s=2v2;; esac
  ./build/linux/foundation_demo --install=<game-dir> --screen=title \
    --local-players=$p --script=tests/scripts/frontend-$s-rematch.txt \
    --headless --out=/tmp/rel-$s.ppm --size=1280x720 --frames=15500
  sha256sum /tmp/rel-$s.ppm   # the digest §3 quotes (NOT md5sum)
done
```

`live_camera_smoothness_test` is the §3.5 gate and `ctest` runs it; a played
battle (§3.5's manual step) is still the only thing that covers the window path.

A run is green when it ends in `RESULT: ok`, every expected
`[menu] scene:`/`match: round over` line above is present, and the `[split]`
roster matches the scenario. A missing `[menu] scene: result`, a panic, or a
`RESULT:` other than `ok` is a gate failure — record the exact command and the
transcript rather than re-running until it passes.
