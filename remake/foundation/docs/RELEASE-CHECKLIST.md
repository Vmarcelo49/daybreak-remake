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
> controllers with a deterministic synthetic pattern, and every command passes
> `--no-devices` (§3.0). A physical pad *was* attached to this machine — its
> owner was using it for another game while the gate ran — and no run here
> drives it: the flag exists because its live input reached these runs' menus.

## 0. What the gate demonstrates

| Acceptance item (issue #23) | Where it is proven |
|---|---|
| Two humans, title→selection→stage→VS/countdown→battle→results→selection | §3.1 |
| One human with COM | §3.2 |
| Four-fighter match, repeated rounds | §3.3 |
| Repeated rounds (rematch) for stability | §3.1–§3.3 (three rounds each), §6 (eight rounds) |
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
`launcher_test.sh` ends with `launcher_test: 30 checks, 0 failure(s)`; it drives
a sandbox package whose binary is a stub, so it needs no device, display or game
data. It is also registered in the host suite (`ctest -R launcher_test`).

## 2. Host suite (the CI job runs exactly this)

```bash
ctest --test-dir remake/foundation/build/linux --output-on-failure
```

* **With the game install present**: `100% tests passed out of 45`.
* **Without any game data** (the CI runner's state — no `Higurashi-Daybreak/`):
  `100% tests passed out of 45`, with `hud_cell_scale`, `toon_ramp`,
  `npr_experiments` and `npr_normals_test` reported as `Skipped` (exit 77) and
  `weapon_definition_test` skipping its fully-skipped sweep. CI needs no
  copyrighted data. (Both counts re-measured 2026-10-06, install present and
  install absent; the suite has grown from the 42 this document was written with.)

The workflow (`.github/workflows/build-foundation.yml`, Linux job) runs this
`ctest` step on every push to `main` that touches `remake/foundation/**` (issue
#28), so a broken test cannot sit on `main`. The same workflow's Windows and Web
jobs stay on the version-bump path: a `gate` job diffs the push and runs them when
`remake/foundation/VERSION` changed anywhere in it, or on a manual dispatch.

## 3. The acceptance runs (deterministic, real assets)

All three use the committed scripts under `tests/scripts/`, run from
`remake/foundation/`. They are **capture runs**: `--headless --out --frames`
steps one logic tick per rendered frame (the demo prints
`logic: N ticks, explicit capture cadence`), which is what makes the tap
ticks in the scripts exact and the run reproducible. Run them with a warm
page cache; each takes seconds to a minute.

### 3.0 Why every command carries `--no-devices`

SDL reports a connected controller whether or not the window has focus, so on a
machine where another application is using a pad, that pad's live input reaches
this port's menus and captures. It was measured on the gate machine (an 8BitDo
Ultimate 2C attached): with the owner playing another game, a
`--screen=title --local-players=2` run selected the title's *story* item instead
of *versus* because the pad's state moved the cursor first, and `hud_cell_scale`
failed because the pad changed the match the capture measured.

`--no-devices` makes the run own every input slot: the script drives controller
0 and `--local-players`' synthetic pads drive the rest. A normal player run does
not pass it. The host suite's demo-driving tools pass it too (`hud_cell_scale`,
`showcase`, `pin_viewpoint`), which is what keeps 42/42 green on a machine with
a pad in use. It is a verification instrument, not a feature.

### 3.1 Two humans, 1v1, three rounds

```bash
./build/linux/foundation_demo --install=<game-dir> --no-devices --screen=title \
  --local-players=2 --script=tests/scripts/frontend-1v1-rematch.txt \
  --headless --out=/tmp/rel-1v1.ppm --size=1280x720 --frames=15500
```

`--local-players=2` opens two local views: controller 0 is the keyboard,
driven by the script, and controller 1 is the synthetic pad that walks panel 2
and accepts the OK cell. What the transcript must show (quoted from the run):

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
[daybreak] match: round over, side 0 wins (time up) at frame 3600
[menu] scene: result (tick 9246)
[menu] scene: select (tick 9848)
[menu] scene: vs (tick 10174)                      <- round 3
[menu] battle: 2 fighters on data/stage15 (time 60s, health 50%, gauge 100%, balloon 40%/40%)
[daybreak] match: round over, side 1 wins (time up) at frame 3600
[menu] scene: result (tick 14110)
[menu] scene: select (tick 14712)
RESULT: ok
```

The `[split]` blocks prove who fought, in which view:

```
[split] layout=two views=2 target=1280x720 roster=2
[split]   p0 panel=0 team=0 1P Rena 0 role=owner ...
[split]   p1 panel=2 team=1 2P Keiichi 1 role=enemy ...
```

Every round keeps the same settings and ends at the 60 s time limit (match
frame 3600); the **stage is re-rolled per round** (`FrontendState::stage`
stays 0 = random), which is why the three rounds run on stage04/06/15.

### 3.2 One human with COM, three rounds

```bash
./build/linux/foundation_demo --install=<game-dir> --no-devices --screen=title \
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

`COM Chie 0` is the COM opponent the OK path rolled; the single view is the
one human's own camera.

### 3.3 Four fighters (2v2), three rounds

```bash
./build/linux/foundation_demo --install=<game-dir> --no-devices --screen=title \
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
[result] side 0 pair 0-2 grade 3 margin 0 script data/scenario/win/00-02-3.txt ...
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
is a character+weapon combo, never a bare fighter.

### 3.4 The scripts' own rules (read before editing them)

* Ticks are **front-end logic ticks**; the capture path runs exactly one per
  frame, so tap ticks are exact.
* Round 1 is the measured cycle of `tests/scripts/frontend-4p.txt`. A rematch
  round only walks the stage page to START: the settings carry over in
  `FrontendState`, and replaying the *value* taps would wrap them (measured:
  a rematch that replayed them played 240 s/175 % where round 1 had
  60 s/50 %).
* The synthetic pads stay neutral while the stage page is open, and their
  roster nudge only runs when their panel still has to be picked; both are
  what make a rematch round behave like the first one (see the commit that
  added these scripts).
* **A windowed (live) run is not the same clock.** The live loop steps the
  simulation at 64 Hz, while a capture steps once per rendered frame, so a round
  lasts 3840 ticks there and 3600 here: the rematch blocks above (whose offsets
  are measured in capture ticks) no longer line up after round 1. Use the
  capture path for round-by-round evidence; §5's windowed runs verify the window
  path itself (present, pacing, 64 Hz logic) and use the battle-screen script.

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
WEAPON_DEFINITION: ok (743 checks, 0 failed, 0 skipped)
```

Without an install the sweep skips itself and the test still passes
(`0 skipped` becomes the local-data count; CI's run is the skipped form).

### 4.2 Character × stage texture matrix (the G3 baseline)

```bash
python3 tests/showcase.py --check --out-dir /tmp/sweep
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
| 2 | Wayland, nested KWin, 60 Hz | `XDG_RUNTIME_DIR=<own> WAYLAND_DISPLAY=wayland-issue23 ./build/linux/foundation_demo --no-devices --screen=battle --local-players=2 --script=tests/scripts/split-two-human.txt --frames=1500` | `video driver : wayland`, `surface : 960x540 ... fifo=yes`, `present mode : Fifo(vsync)`, `frames : 1500 in 24.931 s`, `delta avg : 16.608 ms (60.2 fps)`, `logic : 1594 ticks, 64 Hz`, `RESULT: ok` |
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
  or the script. What would settle it: a real pad walking a panel and a
  battle, with the pad's own bindings.
* **Hardware audio listening** — the audio backend runs (dummy-device
  verification, combat voice/SE counts in the log), but nobody listened on
  real hardware.
* **Other distributions / older Mesa / other compositors** — only CachyOS +
  KWin 6.7.5 + Mesa RADV was exercised.
* **An interactive compositor-side window drag-resize** — resize was driven
  through the port's own Options resolution list; a mouse drag on the window
  edge was not simulated.
* **Windows, the web and macOS** — out of this issue's scope and not run for
  this checklist (their own docs carry their evidence).

## 6. Frame times, crashes and resource stability

Capture runs report wall-clock deltas but step one tick per frame, so their
`fps` number is not a pacing measurement; the windowed rows in §5 are. The
numbers to record per scenario (from the demo's own summary):

| Scenario | Command | Frames/ticks | Wall time | Peak live FX cards |
|---|---|---|---|---|
| 1v1, three rounds | §3.1 | 15500 ticks | 10.690 s | `peak=4/128`, `dropped=0`, `badEffectId=0` |
| COM, three rounds | §3.2 | 15500 ticks | 55.154 s | `peak=5/128`, `dropped=0` |
| 2v2, three rounds | §3.3 | 15500 ticks | 28.210 s | `peak=6/128`, `dropped=0` |
| 2v2, eight rounds | `--local-players=4 --script=<the §3.3 script extended to eight rematch rounds> --frames=40000` | 40000 ticks | 56.694 s | `peak=6/128`, `spawned=124`, `expired=123`, `dropped=0` |

(The wall times are from the demo's own summary on a shared machine — the
owner's game was running — so treat them as an upper bound on the capture cost,
not a benchmark. The `logic:` count is the reproducible number.)

The eight-round run is the prolonged-match stability check: eight
`match: round over` lines, `RESULT: ok`, no crash, and a bounded FX
population (`peak=6/128` live cards, `dropped=0`, `badEffectId=0`) — the
issue #17 acceptance number. Sampled `/proc/<pid>/status` during that run:
peak `VmRSS` ≈ 380 MB, peak thread count 14, no upward trend across rounds.

The COM scenario is ~5× slower per tick than the 1v1 on this machine
(52.8 s vs 10.3 s for the same 15500 ticks). It is well inside real time
(≈294 ticks/s against a 64 Hz clock) but it is a measured difference, not a
guess: the COM brain and its projectile load (`liveShots=2299` vs 1741) are
the places to look if it ever matters.

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
   `tests/select_menu_test.cpp`).

Two evidence gaps were closed as part of the same work: the `[menu] battle:`
line now prints the round's settings, and the display callbacks print what a
fullscreen/resolution request actually did.

## 8. Reproducing the whole gate

```bash
cd remake/foundation
./build.sh linux
ctest --test-dir build/linux --output-on-failure          # §2
./build/linux/weapon_definition_test                      # §4.1
python3 tests/showcase.py --check --out-dir /tmp/sweep    # §4.2
for p in 2 1 4; do                                        # §3
  case $p in 2) s=1v1;; 1) s=com;; 4) s=2v2;; esac
  ./build/linux/foundation_demo --install=<game-dir> --no-devices --screen=title \
    --local-players=$p --script=tests/scripts/frontend-$s-rematch.txt \
    --headless --out=/tmp/rel-$s.ppm --size=1280x720 --frames=15500
done
```

A run is green when it ends in `RESULT: ok`, every expected
`[menu] scene:`/`match: round over` line above is present, and the `[split]`
roster matches the scenario. A missing `[menu] scene: result`, a panic, or a
`RESULT:` other than `ok` is a gate failure — record the exact command and the
transcript rather than re-running until it passes.
