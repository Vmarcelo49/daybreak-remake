# Self-hosted web asset delivery plan

Status: implementation plan, 2026-10-04. This plan describes the target for
the self-hosted web version; the current manifest-based pack loader remains the
verification path until the replacement is implemented.

## Goal

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

For the current playable 1v1 flow, generate this set for the active fighter
slots 0 (blue) and 2 (red). Expand the dependency rules when four-fighter
launch is implemented.

The VS transition is a readiness barrier: keep its animation or show progress
while assets download, verify, decode, and upload. Do not start the battle
until every required resource is ready. The existing 109-update transition is
not a fixed network timeout; it may need to wait longer on a slow connection.

## Implementation steps

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
path resolves the same bytes as native `AssetSource` ([asset source](/home/marcelo/Projetos/daybreak-decomp/remake/foundation/src/assets/asset_source.h),
[bundle ordering](/home/marcelo/Projetos/daybreak-decomp/remake/foundation/src/assets/dat_bundle.cpp)).

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
