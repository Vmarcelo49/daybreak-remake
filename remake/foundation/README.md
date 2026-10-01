# foundation — the multi-platform base

SDL3 + WebGPU (`webgpu.h`) in one CMake project that builds for **Linux, Windows
and the web**, and for macOS wherever the toolchain allows. This is the base the
renderer migration (decision D2) lands on: it is still not a game — no gameplay, no
HUD, no camera controller — but it now loads and draws Daybreak's real stages,
characters and weapons.

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
./build/linux/foundation_demo --list                    # what a spec loads, then exit
```

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
src/shaders/    WGSL, embedded in the binary
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

Variable delta, no fixed step, anywhere: `SDL_AppIterate` measures real elapsed
time and hands it to the game. Present pacing belongs to the swapchain — FIFO is
selected whenever the platform offers it, which is the original game's
cap-at-refresh behaviour. On the web FIFO is the *only* present mode there is.

## Shaders and assets

WGSL is embedded in the binary (`src/shaders/demo_wgsl.h`, `model_wgsl.h`) rather
than loaded from a file, because the web build has no filesystem.

`.X`, `.cnv` and `.dat` are read from disk. On native targets that is the extracted
game tree. On the web, the same code reads from Emscripten’s virtual filesystem,
so a local verification build can preload a small asset subset as `/assets`:

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

The asset path is verified the same way, offscreen, where it produces numbers
rather than a window: a stage at its spawn point, a character and a weapon each
report coverage and the luminance range of the frame, and `--no-textures` renders
the same scene untextured for comparison. Linux and Windows/Wine produce
byte-identical captures of the same asset, which is the point of the exercise —
one renderer, three targets. The two frames the reference implementation's own
captures were kept for (stage01 at the player camera, akane plus a weapon at the
front camera) come out pixel-identical here, so the port is not an approximation
of the shader and draw path it replaces.

New since the port landed, all verified the same way:

- `--camera=arena` drives the one-shot game camera from an env.dat spawn
  (stage21: eye-level fight frame, 96.55% coverage).
- `--effect=<file>` loads a card with the effect role, engaging the additive
  pass in-repo (`effect/01.X`: 11 effect draws, 17.95% coverage, no black quads).
- `--hud-test` composites a deterministic synthetic HUD into `--out` captures
  through the renderer's UI hook — the first in-engine HUD-over-3D frame.
- `foundation_ui` (sprite batch, bitmap font, HUD composer, diagnostics) is wired
  into the demo; `foundation_media` now carries the real SDL3 audio and input
  backends, verified in-engine with `--audio-test` (440 Hz tone through music +
  SFX paths, gains applied) and `--input-test` (canned 6-frame tap with exact
  edge output). Media backends run on Linux and Wine; the browser gesture path
  and audible checks remain open.

## Not here yet

Deliberately out of scope for the foundation: game code itself, video decoding
(explicit stub), BGM streaming/`.sfl` loops, and live-pad/browser-gesture
verification. Asset loading, depth-buffered 3D drawing, HUD compositing,
audio/input backends (including OGG Vorbis decode of all shipped BGM) and the
game camera path are in place; what is still missing before DX9 can be retired
(gate D2) is the frame having to *match* the original's, which needs
game-driven state (real HP, fighter positions, effect spawns) rather than test
rigs.
