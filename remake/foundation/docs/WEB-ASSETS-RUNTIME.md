# Web runtime assets: production path + browser evidence (Track W)

Scope: PORT-PLAN.md Track W (W1/W2/W3). Verification-only; no game data in git.
Local paths below are machine-local and gitignored, never committed.

## 1. Recommendation (W1)

**Production path: plain web build + HTTP fetch/streaming of per-pack assets,
cached in the browser (IndexedDB/OPFS), with Emscripten preload kept only for
local renderer verification.** Both halves of this are now implemented:
the fetch half (`src/platform/web_pack.{h,cpp}` + `scripts/make_pack.py`)
and the IDBFS persistence half (`fetchWebPack` mount + sync with
hash-pinned cache skip) — see the Runtime-fetch and Persistence sections,
both green.

- The engine (`foundation_demo.wasm` 3.67 MB + `.js` 0.48 MB + `.html` 22 KB)
  ships with **no assets**. At startup it fetches named asset packs
  (character ~12 MB, stage ~20 MB, see §3) over HTTP into the Emscripten
  virtual filesystem, then runs the unchanged asset layer (`xm::loadStage` /
  `loadCharacter` / `loadWeapon`).
- Packs are manifest-addressed, not content-addressed:
  `scripts/make_pack.py` lists plain relative paths (the game's
  Shift-JIS-derived UTF-8 names, percent-encoded), and
  `src/platform/web_pack.cpp:170-186` validates the cache by
  manifest-text hash (FNV-1a) plus file presence, refetching everything on
  mismatch. Per-file content hashes in URLs would be a future manifest
  revision. BGM (49 MB) and movie audio are **streamed, never preloaded**.
- The user supplies the data: a local folder picker, a self-hosted pack URL,
  or a first-run importer that reads their own install. The web release
  **never redistributes game files** (commercial data, §4).
- Emscripten `--preload-file` (`FOUNDATION_WEB_ASSETS`, `/assets` mount)
  stays exactly what it is: the local renderer-verification rig. It is the
  wrong production shape because it bundles the whole subset into one
  `foundation_demo.data` (12.4 MB for a single character) that must fully
  download before `main()` runs, with no caching across builds and no
  per-stage/character granularity.

Why not the alternatives:

| Path | Verdict |
|---|---|
| Embedded subset (compiled into wasm, e.g. `xxd`/`incbin` of `.X`/`.cnv`) | Rejected. Bloats the wasm (one character ≈ 12 MB → 3.7 MB wasm becomes ~16 MB), forces a rebuild per asset change, keeps everything resident, and still redistributes data. WGSL stays embedded (it is ours); game data must not be. |
| Emscripten preload (`--preload-file …@/assets`) | Verification-only (current rig). Single monolithic `.data`, all-or-nothing download before startup, no cross-version cache, every subset change rebuilds the package. Fine for a 12 MB local check, unusable at 2.6 GB. |
| HTTP fetch/streaming + IndexedDB/OPFS cache | **Recommended.** Lazy per-pack download, browser-managed persistence, range requests for large packs, streaming decode for audio. Only new code is a small fetch→MEMFS/IDBFS bridge; the asset layer is untouched. |
| IndexedDB/cache alone (without HTTP packs) | A cache is not a source. IDBFS/OPFS is the persistence half of the recommended path, not a delivery path by itself. |

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
- **What still cannot run in-browser.** Anything not yet ported anywhere
  (effects techniques, 2D/HUD, audio, game camera — see PORT-PLAN checkpoint)
  is equally absent on web. No web-only stubs: the web runs the same
  `main.cpp` code path as native (§5).

## Runtime fetch, verified end-to-end (W2 follow-through)

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

## Persistence, verified (IndexedDB via IDBFS)

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
agent-browser --webgpu open "http://127.0.0.1:8178/foundation_demo.html"   # web-assets build, --character=/assets/akane:0
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
  `build/linux/foundation_demo --character=Higurashi-Daybreak/data/akane:0
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

## 4. Proposed integration patch (parent-owned files — NOT applied)

Track W may not touch `CMakeLists.txt` / `src/main.cpp`; the following is the
proposal for the parent. Goal: make the web build self-reporting — one
offscreen capture through the existing `SceneRenderer::capture()` path
(which is already web-safe: `gpu::readBuffer` pumps `wgpuInstanceProcessEvents`
+ `emscripten_sleep`), with coverage/luminance printed to the console where the
browser harness can read it. No new asset mechanism, no layering change.

```diff
--- a/remake/foundation/CMakeLists.txt
+++ b/remake/foundation/CMakeLists.txt
@@ if(EMSCRIPTEN)
     set(FOUNDATION_WEB_ASSETS "" CACHE PATH "Local directory preloaded as /assets in the web build")
     set(FOUNDATION_WEB_ASSET "" CACHE STRING "Single asset argument injected on web, e.g. --character=/assets/akane:0")
+    set(FOUNDATION_WEB_CAPTURE "" CACHE STRING "If set with FOUNDATION_WEB_ASSET, capture one offscreen frame on web and report coverage (e.g. 256)")
     if(FOUNDATION_WEB_ASSETS)
         add_link_options("SHELL:--preload-file ${FOUNDATION_WEB_ASSETS}@/assets")
     endif()
@@ if(EMSCRIPTEN)
     if(FOUNDATION_WEB_ASSET)
         target_compile_definitions(foundation_demo PRIVATE "FOUNDATION_WEB_ASSET=\"${FOUNDATION_WEB_ASSET}\"")
     endif()
+    if(FOUNDATION_WEB_CAPTURE)
+        target_compile_definitions(foundation_demo PRIVATE "FOUNDATION_WEB_CAPTURE=${FOUNDATION_WEB_CAPTURE}")
+    endif()
--- a/remake/foundation/src/main.cpp
+++ b/remake/foundation/src/main.cpp
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

Follow-up (landed): the fetch→`/packs/` loader behind the same
`FOUNDATION_WEB_ASSET` injection point is implemented
(`src/platform/web_pack.cpp`, manifests via `scripts/make_pack.py` with
`asset=`/`base=`/paths, `?pack=` handling at `src/main.cpp:1734-1741`)
with IDBFS caching — the 'future decision' framing above is closed.

## 5. Not verified

- `FOUNDATION_WEB_CAPTURE` patch above: proposed only, never compiled or run.
- `toDataURL()` on a hardware adapter / real vsync (SwiftShader only here).
- `toDataURL()` blank-frame race under load; headed-Chromium screenshot path
  (no Xvfb here, per BUILD-web.md).
- OPFS alternative, range requests, BGM/movie streaming, hardware-adapter
  runs: still open (fetch + IDBFS persistence are implemented, per §§1–2).
- macOS anything (out of scope per PORT-PLAN).
- Full-tree or multi-pack web load (only `akane:0`, 12 MB, exercised).
