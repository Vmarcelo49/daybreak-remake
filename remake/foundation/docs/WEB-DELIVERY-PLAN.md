# Web asset delivery — implementation record and original plan

> **Current status: implemented (issue #4, 2026-10-06).** The service lives in
> [`webdelivery/`](../webdelivery/README.md) and the client in
> `src/platform/{web_assets,asset_client}.{h,cpp}`. This document preserves the
> original plan and its measured deviations; its numbered steps are historical,
> not outstanding work. Current routes and browser execution limits are in
> [`BUILD-web.md`](BUILD-web.md). The old `?pack=` flow remains only as a local
> verification rig: production uses `?delivery=` and per-asset requests at the
> install-relative paths expected by the frontend (`data/...`).

## Original goal (design record)

The steps below are the original proposal, retained as provenance for issue #4;
they are not a list of unimplemented work. Current delivery behavior and the
measurements against it are summarized in “Where this plan was stale” and
“Verified end to end.” The current 1v1/2v2 frontend requests all selected
participants, weapons, and stage resources at the VS readiness barrier.

A host supplies their own Higurashi Daybreak installation to a Dockerized web
server. The server prepares the game data once, then serves the web client and
individual assets from the same origin. Browsers fetch only the assets needed
for the current stage of play and cache them per asset where browser storage
allows.

The repository, Docker image, and release artifacts contain no game data. The
host's original install is mounted read-only. Prepared/extracted data and its
catalog live in a separate persistent volume.

## Loading groups

### 1. Startup group

Load the resources required to show and operate the front end:

- `movie/op.mpg` for the opening. Fetch it during startup, but decode/play it
  only while the opening screen is active. Allow any-button skip.
- Shared title, selection, stage-settings and options backgrounds, buttons,
  text assets, fonts, and other non-character UI art.
- Roster portraits, stage-select thumbnails, and weapon/menu icons needed to
  make the selection screens usable.
- Menu music and common menu sounds.
- Shared HUD and other non-character artwork used across screens, including
  the common battle HUD images.

Do not load full stage models, full fighter models, weapon models, or
match-specific sounds in this group. The selected stage and equipment are not
known yet. Full battle resources belong in the second group; small previews
needed by menus belong here.

### 2. Match group at the VS transition

After the player confirms the matchup and stage, request the dependency set for
that exact match:

- Selected stage models, textures, environment/collision data, and variation.
- Selected fighters, costumes, models, animations, and required textures.
- The selected weapons and their attached models.
- Stage-specific effects and shared battle objects, match music, and required
  battle sounds not already in the startup group.
- Any resources needed to render the VS screen itself; portraits and shared VS
  art should already be available from startup where practical.

Original proposal scope: 1v1 active fighter slots 0 (blue) and 2 (red). The
implemented frontend now builds the match request from every selected fighter
and weapon; four-fighter 2v2 is covered by the current product and the delivery
grouping test.

The VS transition is a readiness barrier: keep its animation or show progress
while assets download, verify, decode, and upload. Do not start the battle
until every required resource is ready. The existing 109-update transition is
not a fixed network timeout; it may need to wait longer on a slow connection.

## Original implementation plan (completed; retained as dated design record)

### Step 1 — Build a faithful prepared-data catalog

Add a host-side preparation command that reads the supplied game install,
unpacks the archives into a persistent web-data directory, and writes a
versioned catalog of logical asset names, sizes, hashes, and prepared paths.
Preparation should be repeatable and skip work when the source install has not
changed.

Preserve the game's archive lookup precedence and case-insensitive name
matching when resolving duplicates. Do not flatten archives by blindly
overwriting same-named files: the remake has measured assets whose bytes differ
between bundles. Preserve the winning bundle/source in the catalog so the web
path resolves the same bytes as native `AssetSource` ([asset source](../src/assets/asset_source.h),
[bundle ordering](../src/assets/dat_bundle.cpp)).

The prepared files should be ordinary decoded archive payloads in their game
formats. This removes archive lookup and the DAT payload XOR from requests; it
does not replace runtime decoding of formats such as `.cnv`.

**Acceptance:** prepare a real local install; compare representative duplicate
and non-duplicate asset bytes with `AssetSource`; verify a second preparation
reuses the existing output; keep all generated game data outside Git and the
Docker image.

### Step 2 — Package the self-hosted service

Create a Docker image containing the web client and a small same-origin web
server/API. Mount the original install read-only and the prepared data/catalog
as a persistent volume. Provide a one-time prepare/install command or a
first-start preparation step with visible progress; normal restarts should use
the prepared volume rather than unpacking again.

Serve the client and asset API from one origin. The API accepts catalogued
logical asset IDs/paths only, never arbitrary filesystem paths. Return clear
not-found and incompatible-install errors. Support cache validators such as
ETag using the prepared asset hash. Keep the initial deployment usable behind a
standard HTTPS reverse proxy.

**Acceptance:** a host can mount an existing game directory, prepare it, start
the container, and load the client without manually extracting files or
configuring cross-origin access.

### Step 3 — Replace pack-wide fetching with an asynchronous asset source

Add a web asset provider that requests one asset at a time from the service,
reports progress, validates the response against catalog metadata, and caches
assets independently in browser storage. Cache identity must include the
server's prepared-data version and the asset hash. Treat browser persistence as
best effort: handle eviction and quota failures by downloading again.

Connect this provider to a loading/state-machine boundary. Do not block the
browser's frame/input loop while a network request is outstanding. Keep the
existing synchronous native `AssetSource` path unchanged. Replace the current
web pack bootstrap only after the new provider can load the same real-asset
scenes; the existing pack flow can remain for local verification meanwhile.

**Acceptance:** a cold load requests only requested files; a warm load reuses
cached files; changing one asset invalidates only that asset; missing files,
server disconnects, and storage eviction produce recoverable errors and visible
progress.

### Step 4 — Implement and verify the startup group

Create a versioned startup dependency manifest from the loading-group list.
Fetch it when the web client starts and report total bytes and progress. Load
the opening video and menu assets, but start video/audio only under the existing
browser gesture rules. Keep menu interactions responsive while optional
startup assets finish; mark only assets required by the first usable screen as
the startup gate.

**Acceptance:** a cold browser session reaches the title/selection flow with
the declared startup assets only; skipping the opening stops playback cleanly;
the next visit reuses cached assets where the browser retained them.

### Step 5 — Load the selected match during VS

Build the match dependency manifest from the selected fighters, costumes,
weapons, stage, stage variation, and battle settings. Start fetching when the
match is confirmed and expose download/decode/upload progress on the VS
transition. Cache matching assets across later matches so only changed or
missing assets transfer.

**Acceptance:** verify at least two different fighter pairs and two stages;
confirm the requested assets match the native dependency set; verify the VS
screen waits through slow or failed requests without entering a partially
loaded battle; verify retry/cancel behavior.

### Step 6 — Measure compression before selecting a format

Record per-format source size, prepared size, transfer size, server preparation
time, browser decompression time, and existing asset decode time for
representative startup and match groups. Start with uncompressed payloads and
standard HTTP compression where it reduces transfer size. Avoid compressing
already-compressed video/audio and any other format that shows no useful gain.

Evaluate LZ4 only if the measurements show a meaningful benefit. Browsers do
not transparently accept LZ4 as an ordinary HTTP content encoding, so using it
requires an explicit per-asset wrapper and a browser/WASM decoder. If adopted,
use independent framed files with uncompressed size and checksum metadata so
assets remain individually cacheable and verifiable. ([LZ4 frame format](https://github.com/lz4/lz4/blob/dev/doc/lz4_Frame_format.md),
[HTTP content encoding](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Content-Encoding))

**Acceptance:** document measured cold-load bytes and time for startup and a
representative match. Adopt a codec only when its transfer savings outweigh
server preparation and browser decode costs on supported devices.

### Step 7 — Verify the complete hosted flow

Test the Docker deployment with a real owner-supplied install on Linux, then
verify the browser path using software WebGPU and a hardware adapter where
available. Cover HTTPS, audio unlock, opening playback/skip, startup progress,
match progress, cache reuse, missing/corrupt assets, and interrupted network
requests. Record cold and warm bytes transferred; use real sessions to validate
the estimated ~500 MB match-session transfer rather than treating it as a
fixed budget.

**Acceptance:** a new host can follow the documented mount/prepare/start steps;
the same-origin site completes startup, selection, VS loading, battle and
results; measured data use and unverified platform cases are recorded.

## Scope boundaries

- No game assets in Git, the public Docker image, or project-hosted downloads.
- No eager transfer of the complete install to each browser.
- No requirement that browser storage retain all assets permanently.
- No custom compression format until Step 6 demonstrates a clear benefit.
- Browser downloads necessarily deliver the requested game assets to that
  browser; self-hosting keeps the project from hosting the game data itself.

## Where this plan was stale

Written 2026-10-04, implemented 2026-10-06 against a tree that had moved. Each
item is a place the plan was followed in spirit rather than literally, with the
measurement or the code that decided it.

1. **The original plan's two loading groups are not two lists of names.** The plan lists
   assets ("shared title, selection … artwork", "selected stage models"). The
   loaders do not read names, they read **directories**: `xm::loadStage` walks one
   `data/stageNN/` (eight model slots, `collision*`, `env.dat`), `xm::loadCharacter`
   one `data/<char>` plus the costume siblings `_B.._F`, `xm::loadWeapon` one
   `data/bullet/%03d/` or a `data/item/` model (`src/assets/scene.h`). The groups
   are therefore expressed as those scopes (`webdelivery/daybreak_web/groups.py`),
   and the server expands each prefix from the catalog so a client never carries a
   file list.

2. **"Shared battle objects" is measurable, and the first guess was wrong.**
   `data/effect/` and `data/aura/` were initially classified as startup art. A live
   delivered match then asked for `data/aura/03.x` and the effect table reads
   `data/effect/%03d.dat` (`buildFxAssets`, `src/main.cpp`), so both moved to the
   match group — where the plan's own wording puts them. The grouping rules now
   carry a fingerprint that a prepared catalog records, so changing a rule
   invalidates the catalog instead of silently serving the old grouping.

3. **The startup gate is not the whole startup group.** The plan's Step 4 says to
   "mark only assets required by the first usable screen as the startup gate", but
   its group list also puts the opening movie and menu music in startup. The
   implementation fetches both and gates on neither: the movie is decoded by the
   browser rather than by wasm (the `#if defined(__EMSCRIPTEN__)` stub in
   `movie_player.cpp` — which, as the plan's own note suspected, had never been
   compiled and does not play anything yet), and BGM is streamed by the audio path
   instead of being decoded from memory. Dispatching gate assets before the
   optional ones is worth **44 MB** of time-to-title on a cold load (140.3 MB →
   96.3 MB measured).

4. **The `.mpg` asset path in the code does not match the archives.** The plan says
   the movie needs an asset path; `movie_player.h`'s `kOpeningMovie` is
   `data/movie/op.mpg` while the archives store **`movie/op.mpg`** (prepared and
   catalogued under that name). Nothing is broken today because the web build does
   not decode the movie at all, but whoever implements the browser-side
   `HTMLVideoElement`/WebCodecs path must use the archive spelling or the catalog
   needs an alias. Filed as an open item on issue #4.

5. **Step 1's acceptance said "compare representative duplicate and
   non-duplicate asset bytes with `AssetSource`".** A representative sample is
   weaker than the check that was actually possible: `tests/web_catalog_order.cpp`
   compares **every** resolved name — 11,261 on a real install, 983 of them
   duplicates — against the native `DatBundleSet`, and hashes the winners
   independently with `sha256sum`. Its hermetic half writes synthetic `.DAT`
   bundles with `dat_crypto`, so the ordering rule is tested with no game data at
   all. Measured agreement: 0 mismatches.

6. **Step 6's "evaluate LZ4 only if the measurements show a meaningful benefit"
   resolved to "no LZ4".** Measured on a real install: `.x` models compress to
   0.468 with gzip, while `.cnv` (186.9 MB), `.mpg` (1641.2 MB) and `.ogg`
   (50.3 MB) do not compress at all. Standard HTTP `Content-Encoding: gzip` on the
   compressible assets captures the win; a per-asset wrapper plus a browser decoder
   would buy nothing on top of it.

7. **"Preserve the winning bundle/source in the catalog" needed a second rule
   beside precedence.** The catalogued spelling is not the only spelling the port
   probes: the game's lookup folds ASCII case (`__stricmp`, 0x00663c20) and the
   native layer reproduces that through the bundle index, while a delivered tree is
   a plain filesystem that does not. Measured misses: `data/item/04.x` for a stored
   `04.X` (the weapon model) and the battle HUD's `P00`/`P02` atlases for a stored
   `p00.cnv`/`p02.cnv` (which silently fell back to the text HUD). Delivered assets
   now also answer the probe spellings the port uses, as symlinks
   (`webAssetCaseVariants`), and the host test pins them. This is a bounded set, not
   the case-equivalence class; resolving case-insensitively at lookup time is the
   general fix and is not implemented.

## Verified end to end (2026-10-06; dated software-WebGPU evidence)

Chromium (Chrome for Testing, headless) on **software WebGPU**
(`google swiftshader [WebGPU(browser)]`), against the Docker image serving the
full prepared install from the host's own read-only mount:

| What | Evidence |
|---|---|
| Cold startup gate | `494 request(s), 96.3 MB received`, then `screen: title (0x01)` |
| Warm reload | `network 1 request(s), 0.0 MB received`, all 539 startup assets from the per-asset cache |
| Match group | `756 assets, 131.9 MB`, `match group ready` before the battle started |
| Live match | `49 model(s), 150 meshes, 56730 vertices`; `draws: 197 (169 textured, 0 untextured, 4 decals, 0 effects, 28 outlines), 156 GPU textures`; `battle HUD atlases loaded (P00/P01/P02)`; `frames : 300`, `RESULT: ok` |

Those draw and texture counts are the **same numbers as the native capture** of the
same match. Not verified: a hardware browser adapter, the browser-side movie
playback (not implemented), selection→VS→battle driven by the front end in the
browser (issue #59), and HTTPS behind a reverse proxy.

