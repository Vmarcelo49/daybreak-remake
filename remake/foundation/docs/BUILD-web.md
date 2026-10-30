# Web (Emscripten)

> **Since M5 (2026-10-30) the web build compiles but cannot run a battle.** The core reads `daybreak*.dat` directly and the web build streams single assets, so a battle fails at launch until the core gets an asset seam (M6). The menus are unaffected. The `--character`/`--enemy` match recipes below are history; the last revision with a working web battle is `e9347627`.

```bash
cd remake/foundation   # all paths below are relative to here
./build.sh deps     # once (populates third_party/, CMakeLists.txt:27-29)
./build.sh web      # sources ~/emsdk/emsdk_env.sh (EMSDK= overrides)
python3 -m http.server 8177 -d build/web
# open http://127.0.0.1:8177/foundation_demo.html
```

The page needs a WebGPU-capable browser and, because wasm is fetched with
`fetch()`, an HTTP origin — `file://` does not work.

Verified with emcc 6.0.10, the Emscripten port of SDL3 3.4.2, and emdawnwebgpu
(Dawn v20250517.163311). `scripts/fetch_deps.sh` (via `build.sh deps`) fetches
the pinned WebGPU-distribution sources into `third_party/webgpu`, and that CMake
project downloads the prebuilt runtime at configure time — emdawnwebgpu on the
web (`third_party/webgpu/emdawnwebgpu/CMakeLists.txt:35`). Nothing in this
project selects Dawn: the WebGPU-distribution CMake project switches to the
Emscripten port on its own as soon as it is configured through `emcmake`.

## Reading the result

Diagnostics go to the browser console. Browser arguments come from `?delivery=`
(the self-hosted per-asset API, below), `?asset=` (a single CLI arg), `?pack=`
(manifest URL fetched into `/packs/`, `asset=` line wins), then the configure-time
`FOUNDATION_WEB_ASSET`. Additional flags go in
`?args=`, separated by `|`, including `--frames=N`, `--match` and the other
asset paths (`src/main.cpp`, web argument bootstrap). Percent-encode query values
when paths contain URL punctuation. **Press Escape in the page** (the demo's own quit
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
=== Higurashi Daybreak Kai Fan Remake ===
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

## Self-hosted delivery (issue #4)

The production shape is the same-origin service in
[`webdelivery/`](../webdelivery/README.md): a host mounts their own install, the
server prepares and catalogs it once, and the browser fetches individual assets.

```bash
python3 -m daybreak_web prepare --install /path/to/Higurashi-Daybreak --out /tmp/web-data
python3 -m daybreak_web serve --out /tmp/web-data --client build/web --port 8177
# open http://127.0.0.1:8177/ and follow "Start the client"
```

`?delivery=1` means "this origin"; `?delivery=<origin>` names another one. The
client fetches the startup manifest, validates every asset against the catalog's
sha256, materialises it at the path the port's own asset layer reads (`data/...`,
`movie/...` — which is what issue #58 records the `?pack=` path cannot do), caches
each asset independently by its content hash, and reports progress. A standalone
recipe works too, and requests its own match group from the arguments:

```bash
# note the /data/... paths: the delivered tree is the MEMFS root
foundation_demo.html?delivery=1&args=--stage=/data/stage21|--character=/data/rena:0|--enemy=/data/mion:0|--match|--frames=300
```

The startup gate (the assets the first usable screen needs) holds `SDL_AppInit`;
optional startup assets (the movie, BGM) keep loading from `SDL_AppIterate`, and a
front-end match requests its group when the VS screen appears and waits for it in
`enterFrontendBattle`.

## Local asset preload for renderer verification

The ordinary web build has no game data. For a local check, mount a small subset
at `/assets` in a separate build directory and inject one asset argument (the
plain build is untouched):

```bash
mkdir -p /tmp/foundation-web-assets
cp -a <game-data>/akane /tmp/foundation-web-assets/
emcmake cmake -S . -B build/web-assets -GNinja \
  -DFOUNDATION_WEB_ASSETS=/tmp/foundation-web-assets \
  "-DFOUNDATION_WEB_ASSET=--character=/assets/akane:0"
cmake --build build/web-assets
python3 -m http.server 8178 -d build/web-assets
# open http://127.0.0.1:8178/foundation_demo.html
```

For a quick local check, `?asset=--character=/assets/akane:0` in the page URL
beats rebuilding with `-DFOUNDATION_WEB_ASSET` (see the `?asset=` / `?pack=`
query paths above).

The expected console evidence is the same shape as native asset runs: the loaded
model/mesh/vertex counts, resolved texture counts, generated draws and GPU
textures, followed by the frame report and `RESULT: ok`. Game data and the
generated `.data` package stay out of the repository.

## Verified with game data (2026-10-06, issue #35)

The 2026-10-03 section below is superseded on one point and confirmed on others.
Re-run on Chrome for Testing 152 through `agent-browser --webgpu` (headless,
**software WebGPU: `google swiftshader [WebGPU(browser)]`** — this box's RADV
device is not what Chromium's WebGPU used), with a `/data` preload rig built as
in `RELEASE-CHECKLIST.md` §5.2:

* **The title screen runs.** An interactive launch passes the front-end data gate
  (`[install] no --install= and no DAYBREAK_INSTALL: reading data/ from the
  current directory`), boots the opening scene and lands on the title with its art
  and Japanese text drawn. Canvas readback (`canvas.toDataURL`) is a real frame;
  the compositor screenshot is still black.
* **A live match runs.** `--stage=/data/stage01 --character=/data/rena:0
  --enemy=/data/mion:0 --match`: stage textures 168 resolved / 0 missed, both
  fighters geared as combos (item 001/item 002), 122/134 moves loaded, 195 draws
  (168 textured, 4 decals, 27 outlines), 143 GPU textures, and the readback shows
  Rena with her weapon facing Mion on the schoolyard with the HUD up.
* **Issue #40's web movie stub, exercised for the first time.** It logs
  `[movie] the web build does not decode movies in wasm: the browser must play
  them (HTMLVideoElement/WebCodecs)` and the switcher moves to the title
  (`opening (tick 0)` → `title (tick 25)`). Deliberate, reported, not a crash.
* **Exceptions must be enabled for any of this to survive a missing asset.**
  emcc disables C++ exception catching by default, which made the asset layer's
  own `try`/`catch` inert and every `throw` fatal: the run aborted with
  `Aborted(Assertion failed: Exception thrown, but exception catching is not
  enabled ...)` on the first missing candidate asset (a `data/aura/00.x` the tree
  ships as `00.X`). `CMakeLists.txt` now passes `-fexceptions`; wasm grows
  6,249,962 → 8,186,870 bytes (+31%).
* **The `?pack=` runtime path still cannot drive the front end.** The fetch half
  works (`[pack] 766 files, 84.5 MB -> /packs/`), but the front end and the
  fighter weapon join read install-relative `data/...` paths that `/packs/` does
  not satisfy; the run now reports it instead of aborting
  (`RESULT: load failed: P1 /packs/data/rena:0 has no weapon: slot-0 item 1
  unreadable — roster fighters must gear up`). Issue #58.
* **`--preload-file …@/assets` (the recipe above) no longer works** for a match:
  its subset has no `item/`, so the launch guard fails. Mount the subset at
  `/data` instead.
* **A scripted front-end run does not leave the selection screen** in the browser
  (issue #59), and a missing candidate asset is logged once per frame (issue #60).

## Game-data run verified (2026-10-03)

A separate `build/web-roadmap` build preloaded the original extracted `stage01`,
`rena`, `mion`, `aura`, `effect` and `object` folders at `/assets`, plus the font
folder at `/third_party/fonts`. From the foundation directory:

```bash
source "${EMSDK:-$HOME/emsdk}/emsdk_env.sh"
emcmake cmake -S . -B build/web-roadmap -GNinja \
  -DFOUNDATION_WEB_ASSETS=/tmp/daybreak-web-assets \
  "-DCMAKE_EXE_LINKER_FLAGS=--preload-file $PWD/third_party/fonts@/third_party/fonts"
cmake --build build/web-roadmap
python3 -m http.server 8179 -d build/web-roadmap
# foundation_demo.html?args=--stage=/assets/stage01|--character=/assets/rena:0|--enemy=/assets/mion:0|--versus|--camera=arena|--frames=300
```

Chromium with `agent-browser --webgpu` used `google swiftshader
[WebGPU(browser)]`, a 960×540 FIFO surface, and resolved all 167 stage textures
with zero misses. The scripted versus run produced 175 draws and 114 GPU
textures, completed 300 frames in 4.993 seconds (60.2 fps), and printed
`RESULT: ok`.

Replacing `--versus|--frames=300` with `--match` exercised the live match with
Rena and Mion, loaded projectile assets, and produced 177 draws and 116 GPU
textures. Escape closed it after 411 frames in 6.876 seconds (60.1 fps), also
with `RESULT: ok`. BGM was unavailable because this local subset omitted `bgm`;
the match continued silently. This verifies game-data loading, draw submission
and match execution on software WebGPU. Screenshots still captured a black
canvas, so visual parity and hardware browser rendering remain unverified.

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
