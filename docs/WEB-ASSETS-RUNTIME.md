# Web runtime assets: delivery history and browser evidence (Track W)

Scope: PORT-PLAN.md Track W (W1/W2/W3). Verification-only; no game data in git.
Local paths below are machine-local and gitignored, never committed.

## Current production path (issue #4)

The active browser delivery path is the same-origin, per-asset client: open the
web build with `?delivery=1` (or a delivery origin), fetch startup/match assets
as requested, validate each response against the catalog SHA-256, and cache by
content hash in IndexedDB when available. Assets are materialized at the
install-relative MEMFS paths the native asset layer expects. The service,
container quick-start and current routes are documented in
[`webdelivery/README.md`](../webdelivery/README.md); the runnable browser recipe
and execution limits are in [`BUILD-web.md`](BUILD-web.md).

The older `?pack=<manifest-url>` + `/packs/` + IDBFS experiment below is retained
as historical verification evidence, not the production design. It fetched a
whole manifest into a separate mount, which did not satisfy the front end's
`data/...` paths. Emscripten `--preload-file` remains a local verification rig;
no game data is distributed by the web release.

## Historical design notes (before issue #4)

The original Track W proposal compared embedded assets, Emscripten preload,
and runtime fetch/persistence. Its scale and data-handling constraints remain
useful, but the proposed per-pack mount, `/packs/` cache protocol and future-work
recommendations below were superseded by the per-asset `?delivery=` client.

## 2. Constraints (W3)

- **Size/memory.** Extracted tree (`Higurashi-Daybreak/data`) is 2.6 GB;
  the `.dat` bundles total ~4.4 GB (`daybreak00.dat` 1.5 GB, `daybreak02.dat`
  1.2 GB, `daybreak04.dat` 1.3 GB, `daybreak06.dat` 440 MB). One character
  (`akane/`) is 12 MB → 12.4 MB `.data` package. Full-tree preload is not
  possible in a browser tab (download time, wasm heap, mobile memory). Build
  flags already assume growth (`-sALLOW_MEMORY_GROWTH=1`, 1 MB stack); packs
  keep peak working set to one arena + its cast.
- **Subset strategy.** Pack per load unit the game actually loads: one
  character dir (+costume siblings), one stage dir, `item/` weapons on demand,
  `bgm/` streamed. Verification subset stays minimal: `akane:0` proves the
  textured skinned path; one stage proves fog/spawn camera; weapons prove
  bone attachment. Nothing else needs to ship for renderer verification.
- **CORS/HTTPS/localhost.** `wasm` is loaded with `fetch()`, so `file://`
  never works — HTTP origin required (verified via `python3 -m http.server`).
  WebGPU needs a secure context: `https://` in production, `http://localhost`
  accepted locally. Cross-origin pack hosts need `Access-Control-Allow-Origin`;
  same-origin hosting avoids the issue entirely. No COOP/COEP headers are
  needed: the build is single-threaded (`-sASYNCIFY=1`, no pthreads), so no
  `SharedArrayBuffer` requirement.
- **Licensing/data handling.** Game data is commercial (Twilight Frontier /
  07th Expansion). No `.X`/`.cnv`/`.dat`/extracted file may enter the repo,
  any pack, or any cache checked into the project. The release must load
  user-provided data at runtime; verification data lives only in gitignored
  dirs (`Higurashi-Daybreak/`, `/tmp/foundation-web-assets/`, `build/`).
- **Current browser gaps.** Native audio, HUD, camera and gameplay paths exist;
  the web movie player remains a deliberate stub, front-end scripted navigation
  has an open issue (#59), and hardware-adapter/visual parity remain unverified.
  The web build shares the native `main.cpp` path apart from platform-specific
  services such as browser movie playback.

## Historical pack-loader run, verified end-to-end (W2 follow-through; superseded)

`?pack=<manifest-url>` fetches the manifest and every listed file into `/packs/`
(percent-encoding Shift-JIS-derived UTF-8 names), then `?asset=` — or the
manifest's own `asset=` line — selects the scene through the unchanged argument
parser. Observed in Chromium against a local pack server (Akane, 18 files,
11.8 MB):

```text
[pack] 18 files, 11.8 MB -> /packs/ from http://127.0.0.1:8179/packs/akane/manifest.txt
[scene] /packs/akane: 1 model(s), 8 meshes, 2195 vertices, textures 13 resolved / 0 missed
draws: 13 (13 textured, 0 untextured, 0 decals, 0 effects), 5 GPU textures
frames      : 4216 in 70.251 s
delta avg   : 16.659 ms (60.0 fps)
RESULT: ok
```

Three real bugs found on the way there, all fixed and documented in code:
query parsing never skipped the leading `?` (first parameter invisible); the
URL encoder mangled `:` in `http://`; and `emscripten_fetch_wait()` never
resolved in this setup (HTTP 0 every attempt), so completion goes through
`onsuccess`/`onerror` callbacks pumped by the same yield the adapter waits use.

## Historical `/packs/` persistence run (IndexedDB via IDBFS; superseded)

`/packs/` is an IDBFS mount: after a fetch, the manifest hash plus every file
syncs back, and the next boot populates from storage, compares the hash, and
skips all downloads on a match. The decisive test blocked every file download
at the network layer (`**/data/**` aborted, manifest allowed) and reloaded:
`cache hit: 18 files already in /packs/`, then the full scene — 13/13 textures,
13 draws — with zero pack bytes over the wire. An earlier green run turned out
to be confounded by the browser HTTP cache serving the files with no server
log lines; the abort-route test rules that out, because aborted requests reach
neither server nor cache. Sync/mount failures degrade to an uncached MEMFS
session rather than failing the run.

## 3. Browser evidence (W2)

All checks read-only against existing local artifacts; nothing was rebuilt.
Server on :8178 was already running (`build/web-assets`); :8179 served the
untouched plain `build/web` for the baseline check only.

### 3.1 Commands

```bash
export AGENT_BROWSER_SESSION="$(agent-browser session id --scope worktree --prefix webassets)"
agent-browser --webgpu open "http://127.0.0.1:8178/daybreak.html"   # web-assets build, --character=/assets/akane:0
agent-browser snapshot -i
agent-browser focus "#canvas" && agent-browser press Escape                # quit → timing summary + RESULT
agent-browser console
agent-browser screenshot /tmp/webassets-canvas2.png                        # compositor screenshot (expected black, §3.3)
agent-browser eval "(function(){return document.getElementById('canvas').toDataURL(); })()"   # pixel path (§3.3)
```

### 3.2 Console evidence (web-assets build, Chrome for Testing, SwiftShader)

```
[log] === Higurashi Daybreak Kai Fan Remake ===
[log] video driver : emscripten
[log] adapter      : google swiftshader [WebGPU(browser)]
[log] surface      : 960x540, 3 format(s), 1 present mode(s), fifo=yes
[log] present mode : Fifo(vsync)
[log] [scene] /assets/akane: 1 model(s), 8 meshes, 2195 vertices, textures 13 resolved / 0 missed
[log] scene /assets/akane: 1 model(s), 8 meshes, 2195 vertices, 51 palette matrices
[log] bounds [-50 0 -9] .. [50 153 39]  radius 94
[log] camera auto at [117 141 -119] looking at [0 77 15] (distance 189)
[log] far plane reach 270 units (sky dome included)
[log] draws: 13 (13 textured, 0 untextured, 0 decals), 5 GPU textures
[log] -- frame timing (variable delta, no fixed step) --
[log] frames      : 184 in 3.048 s
[log] delta avg   : 16.463 ms (60.7 fps)
[log] delta min   : 1.600 ms
[log] delta max   : 23.700 ms
[log] RESULT: ok
[error] program exited (with status: 0), but keepRuntimeAlive() is set … (ASYNCIFY side effect, exit status 0 — see BUILD-web.md)
```

Plain build (`build/web`, triangle, :8179) in the same session: 504 frames in
8.475 s, 59.7 fps average, `RESULT: ok`, and its canvas readback shows the
correct spinning vertex-colored triangle — the no-asset production baseline runs.

### 3.3 Pixel evidence: `canvas.toDataURL()` works where screenshots cannot

- **Compositor screenshots are black** (reproduced: 1280×577 capture shows
  page chrome + black canvas, `/tmp/webassets-canvas2.png`). This is the known
  headless-WebGPU limitation, not a render failure.
- **`canvas.toDataURL()` reads the live WebGPU frame.** Evaluated twice
  against the running `akane:0` scene, 5 s apart:
  both PNGs 960×540, 122223 bytes, **byte-identical**
  (`sha256 174e5bda…`; static bind pose, so determinism is expected, not luck).
  The frame shows the textured character (green hair, skin, black kimono) on the
  clear colour — 13/13 textured draws and 0 missed textures from §3.2 made
  visible. 3/3 `toDataURL()` evaluations across both builds returned real
  frames (no blank race observed, but see caveat below).
- **Pixel metrics** (same clear-colour threshold as `reportCoverage` in
  `main.cpp`): coverage **189211 px of 518400 (36.50%)**, luminance
  **0.022–1.000**.
- **Native cross-check** (read-only run, no rebuild):
  `build/linux/daybreak --character=Higurashi-Daybreak/data/akane:0
  --out=/tmp/native-akane.ppm --size=512` → identical scene stats (8 meshes,
  2195 vertices, 13 draws, 5 GPU textures), coverage 22.94% at 512×512,
  luminance 0.020–1.000. Coverage differs because the viewports differ
  (960×540 canvas vs 512×512 offscreen); luminance ranges agree. This is a
  consistency check, **not** a byte-compare claim.

Caveat: `toDataURL()` on a WebGPU canvas without `preserveDrawingBuffer` can
theoretically race a frame boundary and return a blank; mitigate by
re-reading until non-blank. For committed verification the deterministic route
is §5 (in-engine offscreen capture printed to the console), which removes the
browser compositor from the loop entirely.

## 4. Historical proposed integration patch (never applied)

Track W may not touch `CMakeLists.txt` / `src/main.cpp`; the following is the
proposal for the parent. Goal: make the web build self-reporting — one
offscreen capture through the existing `SceneRenderer::capture()` path
(which is already web-safe: `gpu::readBuffer` pumps `wgpuInstanceProcessEvents`
+ `emscripten_sleep`), with coverage/luminance printed to the console where the
browser harness can read it. No new asset mechanism, no layering change.

```diff
--- a/CMakeLists.txt
+++ b/CMakeLists.txt
@@ if(EMSCRIPTEN)
     set(FOUNDATION_WEB_ASSETS "" CACHE PATH "Local directory preloaded as /assets in the web build")
     set(FOUNDATION_WEB_ASSET "" CACHE STRING "Single asset argument injected on web, e.g. --character=/assets/akane:0")
+    set(FOUNDATION_WEB_CAPTURE "" CACHE STRING "If set with FOUNDATION_WEB_ASSET, capture one offscreen frame on web and report coverage (e.g. 256)")
     if(FOUNDATION_WEB_ASSETS)
         add_link_options("SHELL:--preload-file ${FOUNDATION_WEB_ASSETS}@/assets")
     endif()
@@ if(EMSCRIPTEN)
     if(FOUNDATION_WEB_ASSET)
         target_compile_definitions(daybreak PRIVATE "FOUNDATION_WEB_ASSET=\"${FOUNDATION_WEB_ASSET}\"")
     endif()
+    if(FOUNDATION_WEB_CAPTURE)
+        target_compile_definitions(daybreak PRIVATE "FOUNDATION_WEB_CAPTURE=${FOUNDATION_WEB_CAPTURE}")
+    endif()
--- a/src/main.cpp
+++ b/src/main.cpp
@@ SDL_AppResult SDL_AppIterate(void* appstate) {
     // The whole frame model, in three lines ...
+#if defined(__EMSCRIPTEN__) && defined(FOUNDATION_WEB_ASSET) && defined(FOUNDATION_WEB_CAPTURE)
+    // Verification-only: one in-engine offscreen capture reported to the console,
+    // so browser checks get pixel numbers without canvas screenshots.
+    static bool webCaptured = false;
+    if (!webCaptured && hasAsset(app->opts) && app->frames >= 5) {
+        webCaptured = true;
+        std::vector<uint8_t> rgba;
+        if (app->renderer.capture((uint32_t)FOUNDATION_WEB_CAPTURE, rgba, app->error)) {
+            reportCoverage(rgba, (int)FOUNDATION_WEB_CAPTURE);
+        } else {
+            std::fprintf(stderr, "web capture failed: %s\n", app->error.c_str());
+        }
+    }
+#endif
      const double now = plat::now();
```

Historical follow-up: the `?pack=` loader and IDBFS cache were implemented
for the experiment described above. Issue #4 replaced them as the production
path with `?delivery=` and per-asset cache; see the current-path section at the
top and `BUILD-web.md`.

## 5. Not verified

- `toDataURL()` on a hardware adapter / real vsync (SwiftShader only here).
- `toDataURL()` blank-frame race under load; headed-Chromium screenshot path
  (no Xvfb here, per BUILD-web.md).
- OPFS alternative, range requests, hardware-adapter runs: not measured in this
  dated evidence pass. Current browser movie limitation and delivery verification
  are recorded in `BUILD-web.md`.
- macOS anything (out of scope per PORT-PLAN).
- Full-tree or multi-pack web load (only `akane:0`, 12 MB, exercised).
