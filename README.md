# Higurashi Daybreak — Remake

An open-source remake and reverse-engineering project for **Higurashi Daybreak**, the 3D
arena fighting game developed by Twilight Frontier and 07th Expansion.

The goal is to bring the original game to modern platforms while preserving its gameplay,
characters, assets and overall identity. The product is written in **C++17** with **SDL3
and WebGPU**, and builds for Linux, Windows and the browser.

![Higurashi Daybreak remake screenshot](https://github.com/user-attachments/assets/64fe73d2-a2a7-4e61-aae6-7d9167c0c874)

## Project status

**Playable locally.** With your own copy of the game, you can play story and versus from the
title to the results.

Combat runs on a reconstructed simulation of the original. How closely it matches the original
at runtime has not been verified.

| Area | State |
|---|---|
| Combat, CPU, match rules | Run on the vendored reference core for all 46 character and weapon combos. |
| Story mode | Implemented: dialogue, ladder, retry, game over, endings and staff roll. |
| Language | Menus and HUD in English or Japanese. Story dialogue is still Japanese. |
| Texture packs | Optional PNG packs are read from beside the executable. No pack is published yet. |
| Linux, Windows | Build and package. CI builds both when `VERSION` changes. |
| Web | Battles run, but an uncaught exception ends them after about 31 s (issue #88). |
| Multiplayer | Local only. LAN and online are not implemented. |
| macOS | Not attempted. |

This is not an exhaustive bug list. The plan and its live state are
[`docs/DIRECTION.md`](docs/DIRECTION.md) (what is being done and why),
[`docs/DIRECTION-STATUS.md`](docs/DIRECTION-STATUS.md) (the task list and the work log),
[`docs/SCOREBOARD.md`](docs/SCOREBOARD.md) (the one metric) and
[`docs/QUESTIONS.md`](docs/QUESTIONS.md) (open owner decisions). Open bugs are the GitHub issues. Read
[`AGENTS.md`](AGENTS.md) before changing anything: it is the map and the enforcement point.

## Repository layout

```
src/            the product (C++17, SDL3 + WebGPU)
  app/          entry points, app state and the per-area blocks main.cpp is split into
  battle/       the simulation wrapper, its interface and the battle-side rules
  battle/core/  the vendored reference simulation, byte-pinned; changes are in PATCHES.md
  hud/          HUD composition, its value bridge and the pause overlay layout
  frontend/     screens, front-end state, launch and the result quote/title
  ui/           sprite batch, bitmap font, CJK text and captions
  camera/       the stateful arena camera and its pure view-projection math
  render/       scene rendering, debug primitives and the effect/shadow tables
  gpu/          webgpu.h only: instance, adapter, device, swapchain, buffers
  platform/     SDL3 only, plus the one surface seam between SDL and WebGPU
  assets/       .X / .cnv / .dat decoding and scene assembly
  audio/ input/ movie/ physics/ settings/ shaders/   as named
tests/          the host test suite (CTest), scripts and fixtures
tools/          harness, launch_original.sh, asset-tools, hook-tracer, audit tools
docs/           one documentation tree; closed plans in docs/archive/
research/       the reverse-engineering corpus; research/evidence/ holds the banks
cmake/ scripts/ package/ webdelivery/ assets/
CMakeLists.txt  build.sh  VERSION  README.md  AGENTS.md  LICENSE
```

`docs/PATHS.md` maps every path the reorganization moved. Start at
[`docs/overview.md`](docs/overview.md) for the research half and
[`docs/decisions.md`](docs/decisions.md) for the product's binding decisions.

## Build

Prerequisites: `cmake` (3.20+), `ninja`, `curl`, `unzip` and a C++17 compiler. Per target,
additionally: **Linux** — the SDL3 development package and a Vulkan driver; **Windows** —
`x86_64-w64-mingw32-g++` (SDL3 itself is fetched); **web** — the Emscripten SDK. SDL3 is the
only dependency that is not fetched for you, and only on Linux, where the distribution
package is normally the right one.

```bash
./build.sh deps      # once: pinned third-party sources (needs network)
./build.sh linux     # native Linux
./build.sh windows   # Windows x64 via MinGW-w64 (cross-compiled from Linux)
./build.sh web       # Emscripten (needs emsdk; EMSDK=... to override ~/emsdk)
./build.sh all
```

The game data is the user's own copy: the repository never ships the game's files.

```bash
./build/linux/daybreak --install=/path/to/Higurashi-Daybreak --screen=title
python3 -m http.server 8177 -d build/web     # then open http://127.0.0.1:8177/daybreak.html
```

With no asset argument the demo draws a spinning triangle. With one it loads the game's real
assets, and `--out` renders offscreen and writes a PPM, which is how it is verified without a
display:

```bash
./build/linux/daybreak --stage=<data/stageNN> --camera=player --out=stage.ppm --size=400
./build/linux/daybreak --character=<data/akane:0> --anim=2 --frames=30 --out=char.ppm
./build/linux/daybreak --weapon=<data/item/05.X> --out=weapon.ppm
./build/linux/daybreak --effect=<data/effect/01.X> --out=effect.ppm
./build/linux/daybreak --stage=<data/stage21> --camera=arena --out=arena.ppm
./build/linux/daybreak --character=<data/akane:0> --hud-test --out=hud.ppm
./build/linux/daybreak --audio-test
./build/linux/daybreak --input-test
./build/linux/daybreak --install=<game-dir> --screen=title --out=title.ppm --frames=30
./build/linux/daybreak --list                    # what a spec loads, then exit
```

Platform guides: [`docs/BUILD-linux.md`](docs/BUILD-linux.md),
[`docs/BUILD-windows.md`](docs/BUILD-windows.md), [`docs/BUILD-web.md`](docs/BUILD-web.md).

### Tests and verification

```bash
ctest --test-dir build/linux --output-on-failure
```

Read CTest's own summary rather than a count in a document. Tests that need the game install
skip themselves (exit 77) on a checkout without one; the release checklist is
[`docs/RELEASE-CHECKLIST.md`](docs/RELEASE-CHECKLIST.md), which also documents the full
command set and the current status.

All scripted, headless, capture and bounded `--frames` runs are silent by default. CTest also
forces SDL's dummy audio driver for its tests and their child processes. Use `--no-audio` on
any launch that should not make sound; `--with-audio` is only for an intentional listening
test, and neither flag changes saved volumes.

`tools/fingerprints.sh` prints the simulation and capture hashes to compare across a refactor.

### Continuous integration

Changing `VERSION` on `main` runs [`.github/workflows/build.yml`](.github/workflows/build.yml):
it builds Linux, Windows and web, runs the tests that need no game data, and keeps the packages
as workflow artifacts. Run it by hand with `gh workflow run build.yml`.

### The Linux release package

A user does not build anything: `scripts/package_linux.sh` stages and archives
`build/package/daybreak-<version>-linux-x86_64.tar.gz` through the install rules in
`CMakeLists.txt` — the executable, the two libraries it needs (wgpu-native, SDL3), the caption
fonts, the third-party notices, the `daybreak` launcher and
[`package/README-LINUX.md`](package/README-LINUX.md). The launcher finds the player's own game
folder (`--install=`, `$DAYBREAK_INSTALL`, the folder the binary remembered in its settings
file, then conventional locations) and boots the title screen; the binary remembers the folder
a run opens, so a direct run starts from the same place (issue #36,
[`docs/USER-SETTINGS.md`](docs/USER-SETTINGS.md)). The script also proves the two release
claims: nothing under a game-data path is in the artifact, and `ldd` resolves every library
inside the package or from the base system — never `third_party/` or the build tree.
`tests/launcher_test.sh` covers the launcher's search order, the choice it reads out of the
settings file, its one-time migration of a retired `install.conf` and its failure messages
without a device. The packaged binary is named `daybreak-bin` because the launcher owns the
name `daybreak`.

## Implementation notes

Two rules keep the graphics backend swappable, and they are the whole point of the split:

1. **`gpu/` includes nothing but `webgpu.h`.** No Dawn or wgpu-native header appears outside
   the build system, so choosing an implementation stays a build decision.
2. **`platform/` knows nothing about WebGPU**, except `src/platform/surface.{h,cpp}`, which exists
   to be the one place they meet.

`render/` is a deliberate third exception: building render pipelines is not something `gpu/`
wraps, so it includes `webgpu.h` and consumes the asset layer's `xm::DrawUniform` /
`xm::wgpuVertexLayout()` contract.

| Target | Implementation | Chosen by |
|---|---|---|
| Linux, Windows | wgpu-native (prebuilt) | `third_party/webgpu` |
| Web | emdawnwebgpu (official Dawn port) | switched automatically by `emcmake` |

Both are the same C API. The real differences live in `src/gpu/gpu.cpp` (wgpu-native returns a
present status, Dawn returns `void`) and in surface creation; the web has no present call at
all, because the browser composites the canvas on the next animation frame, which is exactly
when SDL3's iterate callback runs.

Live gameplay and the front end use **60 Hz** simulation ticks independent of render
frequency. The host samples devices once per render, queues input transitions (including taps
completed between polls) and consumes each edge once on a tick; catch-up is capped at eight
ticks per render. Deterministic `--out` captures deliberately keep one update per capture frame
and an explicit `--dt`, with interpolation disabled, so historical recipes stay byte-identical.
FIFO present pacing is selected whenever the platform offers it.

`.X`, `.cnv` and `.dat` are read through one seam (`src/assets/asset_source.*`): **the
install's `daybreakXX.dat` bundles first, the filesystem second**. An install is found from
whichever asset path the command line already carries, or named with `--install=<dir>`. The
original files are read as shipped; there is no asset conversion pipeline.

WGSL is embedded in the binary (`src/shaders/*_wgsl.h`) rather than loaded from a file, so
every target uses the same shader source.

## Playing a match

`--match` runs the real game on the vendored core: combat, the CPU, the match rules, the HUD
values and the camera all come from `src/battle/core/`.

```bash
./build/linux/daybreak --headless --match --install=<game-dir> \
  --stage=<game-dir>/data/stage21 \
  --sim-roster=<game-dir>/data/rika@0,<game-dir>/data/takano@0,<game-dir>/data/rena@0,<game-dir>/data/mion@0 \
  --script=research/evidence/parity-baseline/scripts/melee.txt --frames=150 --out=match.ppm --size=400
```

- `--script=<file>` drives P1 with the DX9 visual-suite format; without it P1 is live device
  input. `--script2=<file>` drives P2; without it P2 takes no input, which is what the DX9
  scene passes. The banked scripts are under `research/evidence/parity-baseline/scripts/`.
- `--spawn` / `--spawn2` override the stage's `env.dat` spawns.
- `DAYBREAK_CAMINFO=1` prints the trace the banked DX9 logs hold, field for field, so
  `tests/compare_match_traces.py` can diff a run against
  `research/evidence/parity-baseline/logs/`.
- `--headless` needs no display and still renders on the real GPU.

## The research half

The repository also holds the reverse-engineering corpus under `research/`: decompiled
functions, symbols, extraction phases and the evidence banks. Nothing there runs the game.
Start at [`docs/overview.md`](docs/overview.md) and [`docs/pipeline.md`](docs/pipeline.md);
`python3 research/tools/coverage_report.py` reports coverage, and `research/recomp/` is
generated output that is never hand-edited.

## License

See [`LICENSE`](LICENSE). The original game's engine, art, audio and story are the property of
Twilight Frontier and 07th Expansion; this project ships none of them.
