# Groundwork spike — what was actually proven

Built and ran, not asserted. Every claim below has a command and an observed output behind it.

## What this spike is

One CMake project, one `main.cpp` written against **only `webgpu.h`**, building for native and
web. Nothing in it is Daybreak-specific: it creates a window, binds a WebGPU surface, asks for
an adapter and device, prints the surface's real capabilities, configures FIFO, renders frames,
and reports whether it worked.

```
webgpu-spike/
├── CMakeLists.txt              one file, both platforms
├── src/main.cpp                SDL3 + webgpu.h, no backend-specific calls except 2 documented #ifs
└── extern/
    ├── webgpu/                 eliemichel/WebGPU-distribution @ 17dcd42 (2025-09-03)
    └── sdl3webgpu/             eliemichel/sdl3webgpu @ 4fa9d70 (2025-05-01)
```

## Results

| Target | Implementation | Result |
|---|---|---|
| Linux, Wayland, real GPU | wgpu-native v24.0.3.1 | **works** — surface, caps, configure, 60/60 frames presented |
| Linux, Wayland, real GPU | Dawn `chromium/7187` (prebuilt) | **fails** — `Unsupported sType (SurfaceSourceWaylandSurface)` |
| Linux, X11 (Xvfb) | Dawn prebuilt | caps + configure OK; presentation did not complete headless |
| Linux, X11 (Xvfb) | wgpu-native | crash — `wgpuSurfaceConfigure: Invalid surface` |
| **Web** (Chromium, SwiftShader) | **emdawnwebgpu `v20250517.163311`** | **works** — `RESULT: ok`, browser presents |
| **Windows** (under Wine) | **Dawn prebuilt `chromium/7187`, MinGW-linked** | **links and runs** — `wgpuCreateInstance` returns an instance (exit 0) |
| macOS | Dawn prebuilt (x64 + aarch64) | not verifiable here — no Mac |

## The web build, in detail

```
SDL3 ready (emscripten canvas)
surface created
adapter:  |  | backend=WebGPU(browser) type=3
device + queue ready
surface formats (3): 18 23 34
present modes (1): Fifo(vsync)
FIFO (refresh-rate cap) available: yes
configured 640x360 format=18 presentMode=Fifo(vsync)
rendered 1/1 animation frames (the browser presents them)
RESULT: ok
```

Two things worth internalising:

- **Fifo is the only present mode on the web.** The browser owns pacing, so the "cap = display
  refresh rate" behaviour the original game has is not something the port has to arrange on
  web — it is the only thing it *can* have. Measured rAF cadence in the same browser:
  **60 frames in 972 ms = 61.7 fps.**
- **There is no explicit present on the web.** `wgpuSurfacePresent` aborts with
  *"unsupported (use requestAnimationFrame via html5.h instead)"*. The web frame loop is
  `emscripten_request_animation_frame_loop`, whose callback returns `bool` to keep running.
  Native code that presents explicitly therefore needs a second frame-loop shape, not just a
  different call.

## API differences found (the real cost of two implementations)

Each is one `#if`, exactly as the distribution's `WEBGPU_BACKEND_*` defines intend:

1. **`wgpuSurfacePresent`**: returns `WGPUStatus` in wgpu-native, `void` in the Dawn family
   (Dawn native *and* emdawnwebgpu). Key off `WEBGPU_BACKEND_WGPU`, not off Dawn alone.
2. **Surface acquire status**: both v24 and v29 spell it `SuccessOptimal` / `SuccessSuboptimal`.
   There is no bare `_Success` enumerator to test against.
3. **The web canvas source is emscripten-prefixed**:
   `WGPUEmscriptenSurfaceSourceCanvasHTMLSelector` /
   `WGPUSType_EmscriptenSurfaceSourceCanvasHTMLSelector`.
4. **v24 has no `WGPU_*_INIT` macros** (v29 does). Zero-initialise with `= {}` and the same
   source compiles against both.
5. **`wgpuInstanceProcessEvents` is required even on the web.** Waiting only on
   `emscripten_sleep(0)` hangs forever at the first adapter request: emdawnwebgpu dispatches
   `AllowProcessEvents` callbacks from that call. Both are needed — ProcessEvents to dispatch,
   `emscripten_sleep(0)` so the browser's own event loop runs (requires `-sASYNCIFY`).
6. **`argv` is not forwarded to wasm** by default, so `--frames=N` reached native but not web.

## What the distribution does for you

- Native: fetches prebuilt binaries. `webgpu-native` from the official gfx-rs release;
  Dawn from `eliemichel/dawn-prebuilt`. No compiler toolchain, no Chromium checkout.
- Web: fetches the **official** `emdawnwebgpu` port from `github.com/google/dawn/releases` and
  switches automatically under `emcmake`. Dawn releases support **SHARED linking only** —
  `WEBGPU_LINK_TYPE=STATIC` with Dawn is a hard `FATAL_ERROR`.
- Dawn prebuilts exist for Windows x64, Linux x64, macOS x64 and macOS aarch64.

## Not verified, and why

- **macOS.** No Mac available. The stack supports it on paper — Dawn ships macos x64/aarch64
  prebuilts, and `sdl3webgpu` has a Metal path with the Cocoa/CoreVideo/IOKit/QuartzCore link
  lines already in its `CMakeLists.txt` — but nothing here was executed. Treat it as unproven.
- **Windows via MinGW in this CMake groundwork.** What *was* proven: wgpu-native +
  MinGW works at the render level (earlier in this session, a cross-compiled
  `wgpu_smoke.exe` ran under Wine producing output byte-identical to the Linux build), and Dawn
  is now linked and run under MinGW too — see below. What was *not* done: driving this
  CMakeLists with a MinGW toolchain file, which additionally needs an SDL3 MinGW package.
- **The X11 rows in the table.** Xvfb is a headless X server with no real presentation path, so
  both failures there are likely artifacts of the test environment rather than properties of
  the implementations. Only the Wayland result — a hard "unsupported sType" from Dawn — is a
  real implementation limitation.

## Windows / MinGW + Dawn (tested)

Dawn's Windows prebuilt ships `bin/webgpu_dawn.dll` plus `lib/webgpu_dawn.lib`, an **MSVC**
import library. Two questions mattered, and both came back positive:

```bash
# 1. Can MinGW's ld read the MSVC import library directly?
x86_64-w64-mingw32-gcc t.c -Iinclude lib/webgpu_dawn.lib -o t2.exe   # -> links, runs (exit 0)

# 2. If not, can an import library be generated from the DLL?
gendef - bin/webgpu_dawn.dll > webgpu_dawn.def          # 359 symbols
x86_64-w64-mingw32-dlltool -d webgpu_dawn.def -l libwebgpu_dawn.dll.a
x86_64-w64-mingw32-gcc t.c -Iinclude -L. -lwebgpu_dawn -o t3.exe     # -> links, runs (exit 0)
```

Both paths work; binutils reads the `.lib` directly, and `gendef`+`dlltool` is a fallback.
Each binary was run under Wine and returned 0, meaning `wgpuCreateInstance` produced an
instance. **Caveat:** that proves linking and instance creation on Windows, not a working GPU
backend — an adapter was not requested in this test, and Dawn under Wine would need D3D12
(vkd3d) or Vulkan to go further. Treat the backend as unproven on Windows.

## Reproducing

```bash
# Linux (wgpu-native)
cmake -B build/linux -GNinja -DCMAKE_BUILD_TYPE=Release && cmake --build build/linux
LD_LIBRARY_PATH=$PWD/build/linux ./build/linux/spike --frames=60

# Linux (Dawn)
cmake -B build/linux-dawn -GNinja -DWEBGPU_BACKEND=DAWN && cmake --build build/linux-dawn

# Web
source ~/emsdk/emsdk_env.sh
emcmake cmake -B build/web -GNinja && cmake --build build/web
python3 -m http.server 8177 -d build/web      # then open spike.html in a WebGPU-capable browser
```

## Conclusion for the decision

The groundwork is viable, and the recommended split is what the distribution already defaults
to: **wgpu-native on native targets, emdawnwebgpu on the web.** Dawn works, but its Wayland gap
(`SurfaceSourceWaylandSurface` unsupported in `chromium/7187`) makes it a poor native choice on
a Wayland development machine, which is the common Linux desktop today.

The portability tax is small and enumerable: **six** differences, five of them one-liners, all
confined to the platform/presentation layer. None of them touch the asset or scene code that
already works.
