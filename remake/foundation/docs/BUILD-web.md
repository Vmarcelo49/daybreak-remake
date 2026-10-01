# Web (Emscripten)

```bash
./build.sh web                                  # sources ~/emsdk/emsdk_env.sh (EMSDK= overrides)
python3 -m http.server 8177 -d build/web
# open http://127.0.0.1:8177/foundation_demo.html
```

The page needs a WebGPU-capable browser and, because wasm is fetched with
`fetch()`, an HTTP origin — `file://` does not work.

Verified with emcc 6.0.10, the Emscripten port of SDL3 3.4.2, and emdawnwebgpu
(Dawn v20250517.163311) as fetched by `third_party/webgpu`. Nothing in this
project selects Dawn: the WebGPU-distribution CMake project switches to the
Emscripten port on its own as soon as it is configured through `emcmake`.

## Reading the result

Diagnostics go to the browser console. There is no argv on the web, so
`--frames=N` never arrives and the demo renders until the app exits — which is
the intent for a browser demo. **Press Escape in the page** (the demo's own quit
path) to reach `SDL_AppQuit`, which is what prints the timing summary and
`RESULT: ok`:

```bash
export AGENT_BROWSER_SESSION="$(agent-browser session id --scope worktree --prefix webgpu-foundation)"
agent-browser --webgpu open "http://127.0.0.1:8177/foundation_demo.html"   # --webgpu = SwiftShader
agent-browser focus "#canvas" && agent-browser press Escape
agent-browser console
```

Observed (Chrome for Testing 152, headless, SwiftShader):

```
=== daybreak foundation ===
video driver : emscripten
adapter      : google swiftshader [WebGPU(browser)]
surface      : 960x540, 3 format(s), 1 present mode(s), fifo=yes
present mode : Fifo(vsync)

-- frame timing (variable delta, no fixed step) --
frames      : 845 in 14.085 s
delta avg   : 16.646 ms (60.1 fps)
delta min   : 16.100 ms
delta max   : 17.400 ms
RESULT: ok
```

On quit the runtime also logs `program exited (with status: 0), but
keepRuntimeAlive() is set ... due to an async operation`. It is an ASYNCIFY
side effect of the main loop, not a failure: the exit status is 0 and the report
above has already been printed.

## Implementation notes

- **No present call.** The browser composites the canvas on the next animation
  frame, which is the very frame SDL3 drives `SDL_AppIterate` from, so the web
  "present" is a no-op. This is not merely redundant on the web: emdawnwebgpu's
  `wgpuSurfacePresent` is a JS stub that calls `abort()`, so `gpu.cpp` must not
  reach it. Native wgpu-native keeps using it, and there it returns a status.
- **The canvas is not created by us.** The Emscripten shell ships
  `<canvas id="canvas">`, SDL3 binds its window to it, and
  `platform/surface.cpp` selects the same element by CSS selector via
  `WGPUEmscriptenSurfaceSourceCanvasHTMLSelector`. All three have to agree on
  the id, which is why no custom shell file is needed.
- **Adapter info is redacted.** Chrome deliberately reports empty `device` and
  `description` strings, leaving only `vendor` and `architecture` (`google
  swiftshader` under `--webgpu`), `createContext` falls back to those two, so the
  `adapter` line still names something instead of printing blank. `backendType` is
  populated, which is where `WebGPU(browser)` comes from — the adapter request
  itself succeeded.
- **Frame timing needed a better clock on the web.** SDL3's Emscripten build
  leaves `SDL_CLOCK_GETTIME` off (its default is `ON` only for `UNIX_SYS`), so
  `SDL_GetPerformanceCounter()` takes the `gettimeofday()` fallback over
  `Date.now()` and quantises deltas to whole milliseconds — at 60 fps that snaps
  every frame between 16 and 17 ms, which a variable-delta loop cannot afford.
  `plat::now()` therefore uses `std::chrono::steady_clock`, which is sub-millisecond
  on every target; the deltas above (16.100 / 17.400) are the result.
- **Awaiting the adapter needs both halves.** `wgpuInstanceProcessEvents` runs
  the WebGPU callbacks, but only a yield to the browser event loop lets the
  promise behind them settle, which is `emscripten_sleep(0)` at `-sASYNCIFY=1`.
- **One present mode.** FIFO is the only one the browser offers, which is
  already the demo's preference everywhere.

## Not verified

- **Canvas screenshot.** Headless Chromium screenshots of a WebGPU canvas come
  back black on this platform. `--headed` is the documented workaround, but it
  needs an X server that outlives the command (agent-browser starts its own
  Xvfb; `xvfb-run` must not be used), and no Xvfb is installed here. Console
  output is the evidence instead.
- **Real GPU.** Only SwiftShader software Vulkan has been exercised. Behaviour
  on a hardware adapter, and on a real vsync rather than SwiftShader's, is
  untested.
