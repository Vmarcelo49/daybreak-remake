# foundation — the multi-platform base

SDL3 + WebGPU (`webgpu.h`) in one CMake project that builds for **Linux, Windows
(MinGW cross-compile) and the web (Emscripten)**: `./build.sh deps` once, then
`./build.sh linux|windows|web`. macOS is not attempted — no Mac available (see the
table below). This is the product after the renderer migration (decision D2):
it is a playable front end and match as well as a viewer — `--match` runs the ported
fighter/projectile simulation with the live match economy and HUD values
(`src/gameplay/match.cpp`), `--versus` keeps the scripted capture vignette, and
`--camera=arena` follows the ported arena camera (`src/gameplay/arena_camera.cpp`).
It loads and draws Daybreak's real stages, characters and weapons.

## Build

Prerequisites: `cmake` (3.20+), `ninja`, `curl`, `unzip`, and a C++17 compiler.
Per target, additionally: **Linux** — SDL3 development package and a Vulkan
driver; **Windows** — `x86_64-w64-mingw32-g++` (SDL3 itself is fetched);
**web** — the Emscripten SDK. SDL3 is the only dependency that is not fetched for
you, and only on Linux, where the distribution package is normally the right one.

```bash
./build.sh deps      # once: pinned third-party sources (needs network)
./build.sh linux     # native Linux
./build.sh windows   # Windows x64 via MinGW-w64 (cross-compiled from Linux)
./build.sh web       # Emscripten (needs emsdk; EMSDK=... to override ~/emsdk)
./build.sh all
```

Run the demo:

```bash
./build/linux/foundation_demo --frames=300   # 0 or omitted = until the window closes
python3 -m http.server 8177 -d build/web     # then open foundation_demo.html
```

### The Linux release package

A user does not build anything: `scripts/package_linux.sh` stages and archives
`build/package/daybreak-<version>-linux-x86_64.tar.gz` through the install rules in
`CMakeLists.txt` — the executable, the two libraries it needs (wgpu-native, SDL3), the
caption fonts, the third-party notices, the `daybreak` launcher and
[`package/README-LINUX.md`](package/README-LINUX.md). The launcher finds the player's own
game folder (`--install=`, `$DAYBREAK_INSTALL`, the saved choice in the XDG config
directory, then conventional locations), remembers it and boots the title screen; the
guide documents the search order, the controls and what is not supported yet. The script
also proves the two release claims: nothing under a game-data path is in the artifact, and
`ldd` resolves every library inside the package or from the base system — never
`third_party/` or the build tree. `tests/launcher_test.sh` covers the launcher's search
order, persistence and failure messages without a device.

With no asset argument it draws the spinning triangle. With one it loads the game's
real assets and draws them (depth buffer, textures, per-draw uniforms, camera, stage
fog), and `--out` renders offscreen and writes a PPM, which is how it gets verified
without a display:

```bash
./build/linux/foundation_demo --stage=<data/stageNN> --camera=player --out=stage.ppm --size=400
./build/linux/foundation_demo --character=<data/akane:0> --anim=2 --frames=30 --out=char.ppm
./build/linux/foundation_demo --weapon=<data/item/05.X> --out=weapon.ppm
./build/linux/foundation_demo --effect=<data/effect/01.X> --out=effect.ppm
./build/linux/foundation_demo --stage=<data/stage21> --camera=arena --out=arena.ppm
./build/linux/foundation_demo --character=<data/akane:0> --hud-test --out=hud.ppm
./build/linux/foundation_demo --audio-test
./build/linux/foundation_demo --input-test
./build/linux/foundation_demo --install=<game-dir> --screen=title  # playable front end
./build/linux/foundation_demo --install=<game-dir> --screen=title --out=title.ppm --frames=30
./build/linux/foundation_demo --list                    # what a spec loads, then exit
```

`--camera` takes `auto|player|front|top|bounds|arena`. `--no-anim` binds no
animation set (bind pose, like the banked frames) and `--fog` is opt-in: the
reference never enables `FOGENABLE` (`FUN_00650a30` writes the parameters but never
the state), so a fogged frame cannot match a banked one — leave both off for a gate
capture.

The demo prints which adapter and backend it got, the surface's formats and
present modes, what the asset layer loaded and how many textures resolved, and a
frame-timing summary, then `RESULT: ok`.

## Layout

```
src/platform/   SDL3 only — window, timing, video driver. Knows nothing of WebGPU.
src/platform/surface.{h,cpp}   the single SDL<->WebGPU seam (native / web canvas)
src/gpu/        webgpu.h only — instance, adapter, device, swapchain, frame, buffers
src/assets/     the Daybreak asset layer: .X meshes/animation, .cnv textures,
                Shift-JIS name resolution, stage/character/weapon scene assembly
src/render/     draws an xm::Scene — depth buffer, pipelines, per-draw uniforms,
                camera and fog
src/shaders/    WGSL, embedded in the binary (demo, model, ui, debug_line)
src/gameplay/   the ported simulation and match loop (fighter, projectile, match,
                match economy, hud_fill) — what --match/--versus run
src/game/       interfaces (fighter pose, HUD values, camera collision, effect events)
src/ui/         sprite/font/HUD/screens (--hud-test, --screen=title)
src/audio/ + src/input/   backends (--audio-test, --input-test)
src/physics/raycast.*     the D3DXIntersect replacement (Möller–Trumbore)
src/main.cpp    the app: SDL3 main callbacks, one code path for native and web
```

Two rules keep the backend swappable, and they are the whole point of the split:

1. **`gpu/` includes nothing but `webgpu.h`.** No Dawn or wgpu-native header ever
   appears outside the build system, so choosing an implementation stays a build
   decision rather than a code change.
2. **`platform/` knows nothing about WebGPU**, except `surface.{h,cpp}`, which
   exists precisely to be the one place they meet.

`render/` is a deliberate third exception: building render pipelines is not
something `gpu/` wraps, so it includes `webgpu.h` and consumes the asset layer's
`xm::DrawUniform` / `xm::wgpuVertexLayout()` — the contract between the two.

## Implementation per target

| Target | Implementation | Chosen by |
|---|---|---|
| Linux, Windows, macOS | wgpu-native (prebuilt) | `third_party/webgpu` |
| Web | emdawnwebgpu (official Dawn port) | switched automatically by `emcmake` |

Both are the same C API. The differences that are real, and where they live:

- `wgpuSurfacePresent` returns a status in wgpu-native and `void` in the Dawn
  family — one `#if` in `gpu.cpp`.
- The web has **no present call at all**: the browser composites the canvas on the
  next animation frame, which is exactly when SDL3's iterate callback runs. So the
  web "present" is a no-op and the frame loop needs no special case.
- Surface creation is per-target by nature, and is the only code in `platform/`
  that mentions WebGPU.

## Frame model

Live gameplay and frontend updates use **64 Hz** simulation ticks, independent
of render frequency. The host samples devices once per render, queues input
transitions (including taps completed between polls), and consumes each edge
once on a tick. Catch-up is capped at eight ticks per render; excess whole-tick
wall time is discarded after long stalls, retaining the fractional phase. Fighter
positions/yaw and the battle camera interpolate for rendering without changing
simulation state. The round-start countdown remains three seconds.

Deterministic `--out` captures deliberately keep one update per capture frame
and explicit `--dt` (default 1/60 s), with interpolation disabled. Standalone
match scripts use match ticks; frontend scripts use global logic ticks. This
preserves historical capture recipes rather than claiming they test live 64 Hz
pacing. Integer move/reload windows retain their tick counts at the chosen port
cadence. Standalone asset viewers and the scripted `--versus` vignette retain
their existing presentation clocks.
Present pacing belongs to the swapchain — FIFO is
selected whenever the platform offers it, which is the original game's
cap-at-refresh behaviour. On the web FIFO is the *only* present mode there is.

## Shaders and assets

WGSL is embedded in the binary (`src/shaders/demo_wgsl.h`, `model_wgsl.h`,
`ui_wgsl.h`, `debug_line_wgsl.h`) rather than loaded from a file, so every target
uses the same shader source without runtime shader-file reads.

`.X`, `.cnv` and `.dat` are read through one seam (`src/assets/asset_source.*`):
**the install's `daybreakXX.dat` bundles first, the filesystem second**. An install is
found from whichever asset path the command line already carries, or named with
`--install=<dir>`; with an extracted tree and no bundles, every read falls through to
the filesystem exactly as before. The bundle path is the game's own: first match in
`daybreak07/04/00/05/02/06` registration order, resolving case like the exe's
`__stricmp`. The first three registrations are recovered; the remaining tail
is untested because no shipped duplicate is known to depend on its order.

The two sources are *not* interchangeable, which is why the order matters: 983 names
ship in more than one bundle and 445 groups differ in bytes. `extract_dat.py` leaves the
last copy in a tree while the game reads the first, so `data/rika/01.X` is 9,675,158
bytes from the bundles (what DX9 loads — `remake/tests/parity-baseline/logs/asset-*.log`,
index 6017) and 9,893,738 from the extracted tree. `--list` prints each model's byte
count so the loaded copy is visible.

A verification run needs no tree at all:

```bash
mkdir -p /tmp/install-only && ln -s "<game-dir>"/daybreak0*.dat /tmp/install-only/
./build/linux/foundation_demo --install=/tmp/install-only \
  --stage=/tmp/install-only/data/stage21 --character=/tmp/install-only/data/akane:0 --list
```

On the web, the same code reads from Emscripten’s virtual filesystem, so a local
verification build can preload a small asset subset as `/assets`:

```bash
mkdir -p /tmp/foundation-web-assets
cp -a <game-data>/akane /tmp/foundation-web-assets/
emcmake cmake -S . -B build/web-assets -GNinja \
  -DFOUNDATION_WEB_ASSETS=/tmp/foundation-web-assets \
  "-DFOUNDATION_WEB_ASSET=--character=/assets/akane:0"
cmake --build build/web-assets
```

The game data itself is never committed and generated packages stay under the
ignored `build/` directory. Beyond preload, the web build now also fetches
per-pack assets at runtime: `scripts/make_pack.py` writes a manifest from an
extracted tree, and `?pack=<manifest-url>` loads it into `/packs/` in the
browser (verified: Akane, 18 files, 4,216 frames at 60 fps, `RESULT: ok`).
Browser-side persistence (IndexedDB/OPFS) is the remaining open half; see
`docs/WEB-ASSETS-RUNTIME.md`.

## Playing a match

`--match` runs the real game: the fighter/projectile simulation, the match economy
(balloon / LIMIT / KO clock) and the live HUD values live in `src/gameplay/`
(`fighter.cpp`, `projectile.cpp`, `match.cpp`, `match_economy.cpp`, `hud_fill.cpp`),
ported from the deleted DX9 tree (`pre-webgpu-cutover` tag), and drive the frame,
instead of the versus vignette's frame-index script.

```bash
./build/linux/foundation_demo --headless --match --install=<game-dir> \
  --stage=<game-dir>/data/stage21 --character=<game-dir>/data/rika:0 \
  --enemy=<game-dir>/data/takano:0 --spawn=0,200,0 --spawn2=-2200,200,-1363 \
  --script=../tests/parity-baseline/scripts/melee.txt --frames=150 --out=match.ppm --size=400
```

- `--script=<file>` drives P1 with the DX9 visual-suite format; without it P1 is live
  device input. `--script2=<file>` drives P2; without it P2 takes no input, which is
  exactly what the DX9 scene passes. Scripts live at `../tests/parity-baseline/scripts/`
  (`melee.txt` is one MELEE tap at frame 80; also `guard.txt`, `heavy.txt`, `jump.txt`,
  `lock_p2.txt`) — one `<frame> TOKEN` per line (`src/input/input.h:85`).
- `--spawn` / `--spawn2` override the stage's `env.dat` spawns (the match uses
  `env.dat`, not the DX9 remake's hardcoded pair, which its comment misdescribes).
- `DAYBREAK_CAMINFO=1` prints the trace the banked DX9 logs hold, field for field
  (`src/main.cpp:1087`), so `tests/compare_match_traces.py` diffs a foundation run
  against `../tests/parity-baseline/logs/`. The deleted DX9 tree is reachable only
  via the `pre-webgpu-cutover` tag. Six scripted cases currently agree exactly
  (worst position delta 0 units over 59 samples × 2 fighters).
- `--headless` needs no display at all and still renders on the real GPU. That matters
  for verification: Mesa's Vulkan WSI cannot present on Xvfb (no DRI3), so a windowed
  run there silently falls back to software GL while Wine gets RADV — two different
  rasterizers, which would make a Linux/Wine capture pair meaningless.
- Known behaviour quirks are kept from the reference and listed in
  `docs/FULL-REPLACEMENT-PLAN.md` §5 (a one-way Guard state, two unreachable
  constants, Kakera's no-op drain) rather than quietly fixed under a parity port.

## What is verified, and what is not

Verified by building and running; see `docs/BUILD-*.md` for per-target detail.

| Target | Built | Ran | Backend observed |
|---|---|---|---|
| Linux | yes | yes | wgpu-native → Vulkan (RADV), FIFO, 7 formats |
| Windows (Wine) | yes | yes | wgpu-native → Vulkan, same adapter as Linux |
| Web (Chromium) | yes | yes | emdawnwebgpu → browser WebGPU, 60 fps, FIFO only |
| macOS | not attempted | — | no Mac available; Dawn ships macos x64/aarch64 prebuilts and `sdl3webgpu` has the Metal path, but nothing has been executed |

Every "ran" row printed `RESULT: ok` with real frame timings; per-target commands
and outputs are in `docs/BUILD-linux.md`, `docs/BUILD-windows.md` and
`docs/BUILD-web.md`.

Host-side tests run without a GPU (`CMakeLists.txt`): the Linux suite has 37
tests covering geometry, raycasts, asset parsing/spawns, gameplay/economy,
animation/lighting, caption fonts/text, HUD/menu layouts, split-screen view
layout, the four-participant roster and screen geometry, the recovered result
rules (the victory-quote plan and the earned-title chain), the live combat audio
policy (event identity, per-fighter voice channels, cleanup) with an asset-backed
COM 2v2 over it, input/rebinding and frontend selection/VS/results. Asset-dependent checks skip when the install is
unavailable. Cross (Windows) and web targets do not build the host tests.

```bash
ctest --test-dir build/linux --output-on-failure
```

The asset path is verified the same way, offscreen, where it produces numbers
rather than a window: a stage at its spawn point, a character and a weapon each
report coverage and the luminance range of the frame, and `--no-textures` renders
the same scene untextured for comparison. Linux and Windows/Wine produce
byte-identical captures of the same asset, which is the point of the exercise —
one renderer, three targets. The two frames kept from the deleted DX9 tree's own
captures (stage01 at the player camera, akane plus a weapon at the front camera;
the tree itself is reachable only via the `pre-webgpu-cutover` tag) come out
pixel-identical here, so the port is not an approximation of the shader and draw
path it replaces.

New since the port landed, all verified the same way:

- `--camera=arena` drives the one-shot game camera from an env.dat spawn
  (stage21: eye-level fight frame, 96.55% coverage).
- `--effect=<file>` loads a card with the effect role, engaging the additive
  pass in-repo (`effect/01.X`: 11 effect draws, 17.95% coverage, no black quads).
- `--hud-test` composites a deterministic synthetic HUD into `--out` captures
  through the renderer's UI hook — the first in-engine HUD-over-3D frame.
- `--versus` runs a scripted two-fighter vignette (stage + P1 + P2, arena
  follow, timeline HUD, BGM loop, SFX cues, effect queue): P2 strafes on an
  integer triangle wave, weapons re-attach to live prop bones every frame, and
  every number is a pure function of the frame index — Linux vs Wine captures
  byte-identical, including camera smoothing, animation, and audio counts. Its
  scripted hits spawn the recovered hit card (`data/effect/000.dat` → `14.X`) with
  the lifetime that model animates for (0.250 s), so a capture has to land within
  ~15 frames of a hit: `--versus --frames=60` (the hits are at 30/55/80 % of
  `--frames`) shows one, and a longer run shows none.
- `--screen=title` boots the front end (`--script=` drives menus and `--out`
  captures them). Title → character/weapon/hypermode/controller selection →
  stage/battle settings → VS intro → live 1v1 battle → victory/quote/report →
  select is connected. Slots 0 (blue) and 2 (red) fight; VS and results show only
  those participants. Options apply fullscreen and four audio sliders; key config
  rebinds keyboard/gamepad actions. Both persist (issue #19).
  Runtime text uses the bundled Gyrotrope Black face with a Noto Japanese
  fallback; new captions share `ui/caption.h` (see `assets/fonts/README.md`). The soft keyboard is
  a reusable widget awaiting its netplay host. See `docs/FRONTEND-PLAN.md`.
- Menu cursor/confirm/back/ready sounds use the shipped system bank, and the
  result quote plays its shipped voice once. The report displays real KO, death
  and damage totals; original earned titles and four-fighter layouts remain open.
- Local split-screen: one view per human controller, each with its own camera,
  cell and HUD values, with the match still stepped once at 64 Hz. The layouts are
  the original's (`FUN_006396f0`): one full frame, two 400×300 views at top-left
  and bottom-right, or the four-cell TL/BL/TR/BR grid — three humans reuse the grid
  and leave the human-less cell empty. Each view sets both a viewport and a scissor
  so views cannot bleed into each other, and its markers project through its own
  camera. `--local-players=N` opens N local views for verification, filling
  pad-less controllers with synthetic input (not physical-pad evidence); in the
  front end they also walk their own selection panel, which is what makes a
  device-free four-participant run possible
  (`tests/scripts/frontend-4p.txt`). See
  [`docs/SPLIT-SCREEN.md`](docs/SPLIT-SCREEN.md).
- Result fidelity: the winning side's own pair script and voice answer the quote
  (both winners' portraits, the persona variant for Rena/Rika with weapon slot 2,
  the recovered 16/17 single-script fallback), and the report shows each
  participant's earned title from the game's own 41-entry table, read out of the
  installed exe. Titles whose conditions depend on fields this port has not
  recovered are flagged in the log rather than guessed. See
  `docs/ROADMAP-PENDING.md`'s E5 section.
- Four-fighter presentation: the four selection panels are one roster that VS,
  the countdown, the battle HUD and the results all read, so a 2v2 shows four
  portraits and nameplates, four per-view HUD markers (owner/ally/enemy/locked
  art plus off-screen edge markers) and four per-participant report rows with the
  winning team named. See `docs/ROADMAP-PENDING.md`'s issue #13 update.
- Chromium software WebGPU has executed real stage01/Rena/Mion assets in both
  scripted versus (300 frames, 60.2 fps) and live match (411 frames, 60.1 fps),
  with `RESULT: ok`. Visual browser parity and hardware rendering remain
  unverified; console evidence and the asset subset are in `docs/BUILD-web.md`.
- `foundation_ui` (sprite batch, bitmap font, HUD composer, diagnostics) is wired
  into the demo; `foundation_media` now carries the real SDL3 audio and input
  backends, verified in-engine with `--audio-test` (440 Hz tone through music +
  SFX paths, gains applied) and `--input-test` (canned 6-frame tap with exact
  edge output). Media backends run on Linux and Wine; the browser gesture path
  and audible checks remain open.

Phase 1 (reads installs, CPU raycast, debug prims):

- Bundles are the primary asset source (see "Shaders and assets" above). Run with
  only `daybreak0*.dat` symlinked into a scratch directory and every asset path
  pointing inside it — nothing on disk — and `--versus` runs green on Linux and
  Wine with byte-identical captures (480,015 B each): 12 models / 54 meshes /
  55,095 vertices, 166 draws, coverage 150,052 px (93.78%), and identical
  camera-smoothing, animation, HUD and audio counts. Wine reports the same
  composition as Linux here, where the extracted-tree runs diverged 13 vs 12
  models (a case-folding artifact this work fixed).
- `--debug-prims` draws a deterministic line overlay (play-area box, aim cross,
  desired-eye cross) as a second Load-preserving pass on the scene's encoder,
  depth-tested against the scene's own depth attachment (dashes where the stage
  occludes a line). Linux vs Wine captures are byte-identical at 1,080,015 B;
  15 lines / 30 vertices / 0 dropped / 1 pass; coverage 225,692 px (62.69%),
  luminance 0.046..0.928.
- `physics/raycast.*` replaces `D3DXIntersect` (Möller–Trumbore, the reference's
  two walkers and traversal order) and drives the arena eye clamp: the desired
  eye is clamped against the stage's `collision_camera` mesh before smoothing,
  with `--no-camera-clamp` as the A/B switch. Stages 04/14 ship a camera mesh
  that parses to zero triangles and take the documented no-clamp degradation;
  01/06/16/21 ship real geometry (180–628 triangles) and their shipped spawn
  segment is unblocked, so the clamp is inert there. Measured cost: 5.5 µs/ray
  on the largest shipped camera mesh — no BVH (201 µs/ray at 32,768 triangles is
  where one would start to pay).

## Display layout

Battle rendering uses the actual viewport aspect automatically, including
ultrawide and custom window sizes. HUD groups use scaled edge margins and center
offsets; fighter markers project through the same camera as the scene. Menu art
stays on a centered 4:3 canvas with black bars around it.

Options includes native window/fullscreen resolution selection, with Desktop,
common sizes and the display's available modes. Unsupported fullscreen modes
are skipped. Browser sizing follows its canvas; fixed captures retain `--size`.
Aspect is automatic, so there is no separate aspect selector. Volumes,
fullscreen, resolution and bindings persist in
`$XDG_CONFIG_HOME/daybreak-decomp/settings.conf` (default `~/.config/...`), loaded
and validated before the front end starts; delete the file to reset. See
`docs/USER-SETTINGS.md`.

## Not here yet

Story video decoding remains an explicit stub. Live-pad and browser-gesture
verification remain open: a pad attached to the gate machine perturbed runs
until device isolation existed (issue #29 — a verification run ignores physical
devices by default and an unfocused window takes no input), and no run drives
that attached pad by hand; the pad-facing runs use SDL's virtual pad. The
four-fighter battle path builds and passes the Linux test suite, and the release
gate's four-human 2v2 completes three consecutive rounds with its VS/result
presentation, per-view HUD markers and four-row report
([`docs/RELEASE-CHECKLIST.md`](docs/RELEASE-CHECKLIST.md) §3.3). An
opt-in 3v3/4v4 mode would be a new remake feature (six/eight fighters total);
its implementation handoff is in
[`docs/ROADMAP-PENDING.md`](docs/ROADMAP-PENDING.md#future-remake-only-experiment-3v3-and-4v4).
Renderer options (the first three options rows are marked unavailable) remain
pending (issue #21). Battle fidelity includes unresolved animation/VFX details;
LAN netplay awaits its own implementation. The Linux CTest suite has 50 tests (2026-10-06),
including frontend selection/configuration, VS/result timelines, HUD geometry and
the split-screen layout/assignment guards. The release gate — the checklist, the
sweeps, the environment matrix and the stability run — is
[`docs/RELEASE-CHECKLIST.md`](docs/RELEASE-CHECKLIST.md).
See `docs/ROADMAP-PENDING.md` for the remaining work.

Where to read next: plan and handoff in `docs/FULL-REPLACEMENT-PLAN.md` (§5 quirks,
§8 cutover) then `docs/ROADMAP-PENDING.md`; assets in `remake/docs/ASSET-CATALOG.md`;
HUD tables in `docs/BATTLE-HUD-SPEC.md`; screens in `docs/FRONTEND-PLAN.md`;
per-target build logs in `docs/BUILD-linux.md`, `docs/BUILD-windows.md` and
`docs/BUILD-web.md`.
