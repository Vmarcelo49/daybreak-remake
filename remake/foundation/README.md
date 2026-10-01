# foundation — the multi-platform base

SDL3 + WebGPU (`webgpu.h`) in one CMake project that builds for **Linux, Windows
and the web**, and for macOS wherever the toolchain allows. This is the platform
layer the renderer migration (decision D2) lands on: it is deliberately *not* a
game, and it knows nothing about Daybreak's assets.

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

The demo prints which adapter and backend it got, the surface's formats and
present modes, and a frame-timing summary, then `RESULT: ok`.

## Layout

```
src/platform/   SDL3 only — window, timing, video driver. Knows nothing of WebGPU.
src/platform/surface.{h,cpp}   the single SDL<->WebGPU seam (native / web canvas)
src/gpu/        webgpu.h only — instance, adapter, device, swapchain, frame, buffers
src/shaders/    WGSL, embedded in the binary
src/main.cpp    the app: SDL3 main callbacks, one code path for native and web
```

Two rules keep the backend swappable, and they are the whole point of the split:

1. **`gpu/` includes nothing but `webgpu.h`.** No Dawn or wgpu-native header ever
   appears outside the build system, so choosing an implementation stays a build
   decision rather than a code change.
2. **`platform/` knows nothing about WebGPU**, except `surface.{h,cpp}`, which
   exists precisely to be the one place they meet.

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

WGSL is embedded in the binary (`src/shaders/demo_wgsl.h`) rather than loaded from
a file, because the web build has no filesystem. Everything else that gets loaded
at runtime — `.X` meshes, `.cnv` textures, `.dat` bundles — will need the same
treatment (embedded or fetched over HTTP), which is a decision to make before the
asset layer is moved onto this base.

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

## Not here yet

Deliberately out of scope for the foundation: asset loading (the `.X`/`.cnv`
loader proved out in `webgpu-mvp/`), depth buffers, the 2D/HUD layer, effects,
audio, input mapping, and any game code. The next step that makes this a renderer
rather than a base is moving the asset layer onto it and drawing a real stage —
the gate D2 sets for retiring DX9.
