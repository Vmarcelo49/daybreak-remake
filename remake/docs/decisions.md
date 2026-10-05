# Project decisions (binding)

Recorded 2026-10-01. These override any conflicting notes elsewhere in
`docs/` or roadmaps. Update this file — not scattered
comments — when a decision changes.

## D1 — `mvp/` retired; `remake/` is the only codebase

- The old `mvp/` tree (`<project>/mvp/`) was frozen, ported per
  `docs/port-from-mvp-plan.md`, then **deleted** (2026-10-01). All new
  code is written in `remake/foundation/` (`src/`, `tests/`, `scripts/`) —
  the DX9 `remake/src/` was deleted in the Phase 5 cutover (D2 reversal).
  `remake/{scripts,tools,assets,docs}/` keep the surviving tooling and
  evidence.
- What survives from `mvp/`: the relocated tooling
  (`tools/asset-tools/`, `tools/hook-tracer/`, `assets/shaders/`),
  the ported engine/scene/texture work, and the RE constants now
  cited in code comments. The decomp translations themselves live on
  in `research/decompiled/` and `research/binary_data/` — consult those,
  not `mvp/`, for `FUN_xxxxxx` provenance.
- Rationale: two active codebases split effort and drift; the remake
  (real gameplay stack) is the strictly better foundation
  (see comparison notes in chat, 2026-10-01).

## D2 — The renderer migrated to WebGPU; DX9 was the reference until parity (reversed 2026-10-02 — see the reversal below)

> **Reversed 2026-10-02.** The gate passed against the corrected visual
> target (the original's prints, plan §6a) and DX9 was dropped in the
> Phase 5 cutover; the reversal, with measured evidence, is at the end of
> this section. The text below is the decision as taken, kept as the
> record.

- **Supersedes the 2026-10-01 text** that read "DirectX 9 stays. No
  renderer migration." and claimed dropping DX9 was *not possible*. That
  claim was tested and disproven (evidence below), so the direction is
  now the opposite one.
- Target: **SDL3 + `webgpu.h`**, with the backend chosen per platform —
  **wgpu-native** on native targets, **emdawnwebgpu** on the web
  (`foundation/CMakeLists.txt:17`). One `CMakeLists.txt` serves all three
  targets; the web/native split is confined to the platform layer and the
  frame loop (`foundation/src/platform/{surface,web_pack}.cpp`,
  `foundation/src/gpu/gpu.cpp`, plus the web asset bootstrap in
  `foundation/src/main.cpp:1732`).
- **Record — superseded 2026-10-02 (reversal below).** The pre-cutover
  text read: "DX9 is not deleted … until it passes, DX9 is the shipping
  renderer." No longer true: the cutover deleted `remake/src/`,
  `remake/CMakeLists.txt`, `remake/build.sh` and `remake/cmake/`
  (`foundation/docs/FULL-REPLACEMENT-PLAN.md` §8), and the A/B reference
  is the frozen `tests/parity-baseline/` bank plus the original's prints.
- Evidence, as recorded at decision time in the now-deleted prototype
  (`webgpu-spike/FINDINGS.md`, archived in `3fea431`, deleted in `5a63db3`
  — read it with `git show 3fea431:webgpu-spike/FINDINGS.md`):
  - Linux/Wayland, real GPU, wgpu-native: surface, capabilities,
    configure, 60/60 frames presented, FIFO available.
  - Web (Emscripten + emdawnwebgpu): `RESULT: ok` in Chromium; the
    browser presents, and FIFO is the only present mode it offers.
  - Windows: Dawn linked from MinGW and ran; wgpu-native cross-compiled
    earlier the same day rendered under Wine byte-identically to Linux.
  - macOS: **unverified** — no Mac available. Dawn ships macos x64 and
    aarch64 prebuilts and `sdl3webgpu` has the Metal path, but nothing
    has been executed. Do not claim it works.
- Spike-era finding, kept in the record: Dawn (at least the
  `chromium/7187` prebuilt) rejects `WGPUSurfaceSourceWaylandSurface`, so
  it was a poor native backend on a Wayland desktop; wgpu-native handles
  Wayland and is the native backend (`foundation/CMakeLists.txt:17`). Not
  a live constraint — Dawn is only the web backend now.
- Rationale: D3DX9 is deprecated, drags `d3dx9_43.dll` and Wine-specific
  behaviour, and blocks the Linux/macOS/web targets this port exists to
  reach.

### D2 reversal — 2026-10-02: the gate has passed, DX9 is dropped

- **Why now.** The gate D2 named was "a matching in-game frame", and the
  visual target was corrected (plan §6a, owner) to the **original's own
  screens**, not the unfinished DX9 remake's frames. The WebGPU path now
  renders those:
  - title screen **RMSE 0.015970** against `docs/reference/title-menu.webp`
    (ink IoU 0.975 items / 0.980 logo / 0.974 selected row — the print is
    itself a capture at (+1,+5), `tests/title_bands.py:9-12`, and the masks
    land at (0,0) after that correction; residual is the print's own ~2%
    darkening plus webp ringing);
  - battle frame with the camera fitted from the prints: player pixel
    height **314 vs the print's 313** (0.997 of target), residuals 0.0 px on
    the four measured rows that over-determine the geometry;
  - HUD element bands **0.33–0.40 → 0.09–0.19** against
    `battle-hud.webp` (hp 0.3604 → 0.1118, main 0.3788 → 0.0951, charge
    0.4038 → 0.0944, fan gauge 0.3867 → 0.1910, every band now better than
    the 0.2755 scene-only floor).
- **What was dropped.** The DX9 tree and its build: `remake/src/`,
  `remake/CMakeLists.txt`, `remake/build.sh`, `remake/launch_daybreak.sh`,
  `remake/cmake/`, the DX9 visual-suite fixtures under `remake/tests/`, and
  the `webgpu-mvp/` / `webgpu-spike/` prototypes. Full list and what was
  deliberately kept: `foundation/docs/FULL-REPLACEMENT-PLAN.md` §8.
- **What replaces the A/B reference.** (a) The **banked reference bank**
  `tests/parity-baseline/` (33 cases / 36 captures, 47 logs, manifest +
  hashes) — now a **frozen archive**: `regen.sh` needs the deleted
  `build/daybreak.exe`, so it documents provenance, it does not regenerate;
  and (b) the original's **23 prints** in `docs/reference/`, which are the
  appearance target.
- **The DX9 behavioural oracle's role is retained as records.** The
  gameplay trace A/B (`compare_match_traces.py`) still runs against the
  banked DX9 logs, and the DX9 remake's quirks the port deliberately pins
  stay documented in the bank. The one-way Guard defect was corrected
  for playable updates in issue #6; the unclamped camera A/B remains tested.
  What ends is the ability to produce *new* DX9 frames: any new
  behavioural claim now has to come from the original.
- Rollback point: tag `pre-webgpu-cutover` (`37ed31d`), kept until the
  release after the cutover. This supersedes the "DX9 is not deleted"
  bullet above; everything else D2 records (backend choice, per-platform
  verification state, macOS unverified) still stands.

## D3 — Original `.X` files are used directly. No conversion pipeline.

- **Unchanged by D2.** The asset *layer* is the same on every backend:
  `loadStage`/`loadCharacter`/`loadWeapon` consume the originals as
  shipped — the foundation decodes all 728 `.X` files (three encodings),
  the `.cnv` images and the Shift-JIS texture references with no
  conversion step (`foundation/src/assets/xmodel.h`, `cnv.h:61`; the
  corpus proof — 728/728 `.X`, 5051/5051 `.cnv` — is archived in
  `3fea431:webgpu-mvp/README.md`, and `.X` is re-measured in
  `foundation/docs/RENDER-MATERIALS.md:36,43`), for exactly the reasons
  below. Delivery differs — native reads the `.dat` bundles/disk, the web
  build fetches per-pack files from an extracted tree
  (`foundation/src/platform/web_pack.cpp`, `foundation/scripts/make_pack.py`)
  — and Chromium software WebGPU has now executed the original stage01,
  Rena and Mion assets in scripted versus and live match (`foundation/docs/BUILD-web.md`,
  game-data verification 2026-10-03). Browser visual parity and hardware adapters
  remain unverified.
- Character/stage/collision meshes ship as `.X` in three encodings
  (`0302txt`, `0303bin`, `0303bzip`); the semantics to reproduce are the
  original loader's (`D3DXLoadMeshHierarchyFromXInMemory` frame trees,
  `ID3DXAnimationController` sets, skin weights, Biped rigs —
  `FUN_0064d940`), and the foundation's own parser and controller subset
  do that with no D3DX linked (`foundation/src/assets/xmodel.h:205-226`).
- The single production asset path is:
  `bundle → decrypt → xm::loadMemory → live animation`
  (`foundation/src/assets/xmodel.h:267`, `dat_bundle.cpp`).
  There is **no conversion step** (no glTF/FBX export into the build):
  converters bake down animation blending/track setup the game relies on
  and would cost more effort than using the originals.
- Loader parity targets (semantics of the original's loader
  `FUN_0064d940`, `docs/reverse-engineering.md:195`; its flag table at
  :229/:413 is superseded here): InMemory variant, mesh flags `0x220`,
  up to 2 anim tracks bound at load. (Note: `0x220` is
  `D3DXMESH_VB_MANAGED | D3DXMESH_IB_MANAGED` per `d3dx9mesh.h` —
  0x020 / 0x200 — not the `32BIT | NPATCHES` that
  `reverse-engineering.md` still claims; no NPatch templates exist in the
  shipped assets.)

## D4 — mvp hook status (do not plan around the README)

- `tools/hook-tracer/README.md` (the preserved copy of the deleted
  `mvp/hook/README.md`) describes inline patching with direct/archive/
  hybrid modes. The shipped `daybreak_hook.c` (v11) **patches nothing** —
  it is a `CreateFileA` tracer + log (`tools/hook-tracer/daybreak_hook.c:105`).
  The `daybreak_launcher.exe` injector itself works.
- Treat the hook as a **dev/RE tracing tool**, not a runtime asset
  feature. If runtime loose-file loading is ever needed, it will be
  re-implemented in the foundation — not revived in the retired `mvp/`.

## D5 — Comment/code-quality policy (remake)

- Comments must explain **why** or cite RE provenance
  (`FUN_xxxxxx`, binary address, `docs/reverse-engineering.md` section).
- Delete comments that restate the code, dead-code blocks kept
  "just in case", and stale milestone chatter. No behavior changes
  while cleaning (standing policy: `AGENTS.md` rule 4).

## D6 — Scope: versus + LAN netplay first (2026-10-01)

- The focus is **offline versus** (split-screen, bots) and **LAN
  netplay**. Full spec: `docs/game-spec.md`.
- This supersedes the old roadmap's blanket "no online/netcode" ban:
  DirectPlay 8 is still replaced, not ported, but a LAN-first netcode
  (deterministic lockstep over UDP) is in scope.
- Story mode is **not built**: the ids are registered
  (`Prologue`/`StoryTeam`/`StoryAdv`, `foundation/src/ui/screen.h:43-47`)
  but their builders remain absent. The front end now builds title, selection,
  stage settings, options/key config, VS intro and result screens; its playable
  battle path now supports up to four selected fighters, and the Linux build
  and host tests pass. An asset-backed four-fighter run remains unverified.
  The VS/result presentation and extra HUD bars still use
  two-fighter layouts; result earned titles and three renderer options remain
  pending. Story-mode video stays stubbed
  (`foundation/docs/ROADMAP-PENDING.md` §H). No
  branching, saves, or localization is planned. Non-goals listed in
  `game-spec.md` §5 stand.

## D7 — Runtime captions use Gyrotrope Black (2026-10-04)

- Use the user-selected `foundation/assets/fonts/gyrotrope-black.otf` for
  runtime text, including HUD fallback captions, options, result text and
  diagnostics. Future captions use the shared `ui::CaptionText` /
  `ui::loadCaptionFont` path. Image-based labels and numerals retain their
  original art.
- Gyrotrope has no Japanese glyphs; Noto Sans CJK JP supplies Japanese
  through font linking. Native builds package available fonts beside the
  executable; web builds preload them. The embedded bitmap face remains
  the fallback when a font or glyph is unavailable. Historical DX9 metric
  tests retain their explicit reference face.
- Rationale: the selected face matches the combat captions more closely
  and gives future runtime text one consistent visual identity.

## D8 — Automatic battle aspect; 4:3 menus; native resolution selection (2026-10-04)

- Aspect is automatic: use the current render viewport for the battle
  camera, including 4:3, 16:9, ultrawide and arbitrary window sizes. No
  separate aspect selector is exposed; automatic handling fulfills the
  user's preferred behavior without another setting to keep in sync.
- Preserve the HUD art's proportions with uniform scaling based on the
  smaller of `viewportWidth / 800` and `viewportHeight / 600`. Derive HUD
  groups from edge margins and center offsets in the resulting logical
  viewport; 800×600 remains the reference layout, not a fixed render size.
  Project fighter rings and bars with the same view-projection matrix as
  the scene, then map them into this logical viewport.
- Menus use a centered, uniformly scaled 800×600 canvas, clipped to its
  bounds with opaque black bars outside it. Their shipped backgrounds
  remain 4:3 until replacement art is available. Apply the same transform
  to text, sprite destinations, rotation anchors and clips.
- Native Options exposes Resolution with Desktop, common window sizes
  and available display modes. Windowed sizes are expressed in physical
  pixels with pixel-density conversion; fullscreen cycles skip unsupported
  exact sizes. Resize events reconfigure the swapchain. Desktop dimensions
  refresh when the window moves to another display.
- Browser resolution follows the canvas and fixed headless captures use
  `--size`; their resolution row indicates external control. Display and
  other frontend settings persist (D10).
- Verification: 24 Linux tests pass; Linux, Windows cross-build and web
  builds succeed. Native Wayland checks exercised resolution changes,
  fullscreen on/off and fullscreen resolution changes. Real-asset battle
  captures were inspected at 1920×1080 and 3440×1440; menus were checked at
  3440×1440 and 1373×777, including black-bar pixels. The complete frontend
  loop returned from battle/results to selection at 1920×1080.
- Rationale: battle uses the available display area while preserved menu
  art keeps its intended proportions. Anchor math supports future HUD
  additions without resolution-specific coordinate tables.

## D9 — Live simulation is fixed at 64 Hz (2026-10-04)

- The owner selected **64 Hz** for the playable port and its simulation tests.
  `foundation/src/gameplay/fixed_step.h` is the shared rate/accumulator contract.
  Rendering remains independently paced by the swapchain. Gameplay, bots, menu
  updates and frame-counted timers advance on logic ticks rather than presents.
- Device polling happens once per render. Keyboard/gamepad button events and
  sampled held states queue into tick inputs so a short tap survives a render
  stall or a render with no simulation tick. Each edge is consumed once;
  catch-up ticks keep held input without repeating edges.
- Catch-up is bounded to eight ticks per render. Excess whole-tick wall time is
  discarded after long stalls; simulation time advances only by executed ticks.
  This is an offline overload policy, not a completed network clock protocol.
- Fighter position/yaw, attachments, aura placement, camera and HUD marker
  projection use interpolated presentation transforms. Authoritative gameplay
  state remains tick-based. The round-start countdown stays three seconds;
  existing integer combat windows otherwise retain their tick counts at 64 Hz.
- Historical `--out` recipes intentionally bypass the live accumulator: one
  capture update per frame with explicit `--dt` (default 1/60 s), no presentation
  interpolation. Their script numbering and banked visual evidence stay usable.
  Standalone viewers and `--versus` retain their prior presentation clocks.
- This implements the fixed-clock/input prerequisite shared by
  [issue #5](https://github.com/Vmarcelo49/daybreak-decomp/issues/5) and
  [issue #3](https://github.com/Vmarcelo49/daybreak-decomp/issues/3).
  Save/restore, serializable RNG, authoritative snapshots/state hashes,
  resimulation and cross-platform determinism audits remain open under #3;
  neither rollback nor network transport is implemented by this decision.
## D10 — User settings live in the XDG config directory, versioned and atomic (2026-10-05)

- Display preferences, the four audio volumes and the keyboard/gamepad bindings
  persist in `$XDG_CONFIG_HOME/daybreak-decomp/settings.conf` (falling back to
  `~/.config/...`; only an absolute `$XDG_CONFIG_HOME` counts). The original keeps
  the same settings in a flat binary `config.dat` beside its executable
  (`FUN_006486c0` @0x6486c0 reads it, `FUN_006488d0` @0x6488d0 writes it); writing
  into the install tree is what the issue forbids, and an unversioned, unvalidated
  binary blob is what the port does not want.
- The format is the port's own versioned INI-style document (schema version 1). A
  file whose version is not the current one is ignored whole, never partially
  applied; unknown keys inside a known section are ignored with a warning so a
  newer schema cannot destroy older settings. Structure errors reject the whole
  document, value errors default the one key. Defaults equal a first launch, and
  deleting the file is the reset.
- Writes are atomic: temp file in the same directory, `fsync`, `rename`, directory
  `fsync`, mode 0600. A failure leaves the previous file untouched and reports once
  (then backs off), and nothing is ever written into the checkout or the game
  install.
- Bindings stay per **player** — the original's unit (`config.dat`'s 0xd0-byte block
  is four players x thirteen actions, and its key config has four player columns) —
  and the port adds the stable identity the original lacks: the SDL GUID of the pad
  that last used each slot, used to give a replugged pad back its player instead of
  the lowest free enumeration slot.
- Session state stays out: earned titles, result stats and match outcomes are not
  persisted (the issue requires this, and the original's session flags are session
  scoped). Adding such a key needs a scope decision, not a schema bump.
- Only a plain interactive frontend run reads or writes the file; `--match`,
  `--versus`, `--hud-test`, `--out`/`--headless` captures, the asset viewers and any
  `--frames` run ignore it, so the banked captures and parity recipes are unchanged
  by a user config.
- Browser persistence (IndexedDB/OPFS) remains open, as recorded in
  `foundation/docs/WEB-ASSETS-RUNTIME.md`; the web build keeps settings process-local.
- Verification: 34 native host tests (the new `user_settings_test` covers the
  parser, the validator, the atomic write and the controller policy); an isolated
  `XDG_CONFIG_HOME` run proves save → restart → load → apply, and garbage,
  `version = 99`, truncated, NUL-byte, unwritable, spaced-path and
  unavailable-resolution cases all keep the port starting. Format and policies:
  `foundation/docs/USER-SETTINGS.md`.
- Rationale: settings that vanish on every launch make the options screen a demo;
  a user config directory, a versioned schema and an atomic write are the smallest
  set that makes them real without touching the install tree.

## D11 — Battle pause freezes the authoritative step; the menu is a port feature (2026-10-05)

- The freeze is recovered: the original's pause flag `scene+0x4430` gates its whole battle
  update (`FUN_00634f60` @0x635093-0x6350aa skips the frame counter and every
  fighter/economy/camera step) and is toggled from the per-fighter pause action while the
  live round runs (@0x634fb3-0x635006, playing system SE 0x11). The port gates its
  authoritative step the same way (`Match::set_paused`), so a paused step touches nothing
  and drops `dt` instead of accumulating it: paused wall time cannot become catch-up ticks.
- The readable four-row menu (Resume / Rematch / Return to selection / Quit to desktop), its
  captions on the shared D7 path and its key hints read from the current bindings are a
  **port feature**, labelled as such: the original's recovered pause UI is the "PAUSE" cell
  of `data/object/system.cnv` plus a もう一度挑戦しますか？ rematch prompt, and it has no
  return-to-selection row. The standalone `--match` harness has no selection screen behind
  it, so its menu is three rows.
- Input: the paused ticks keep draining the device queues, so a button held across the pause
  has no edge to fire on resume while a fresh press still works. Escape opens the pause in a
  live battle instead of quitting the process. Focus loss drops held keys (#6) and pauses a
  live battle; a disconnected pad already reads as released (#6's backend path) and the
  keyboard can always reach the menu. A scripted run is exempt from the focus-loss auto-pause
  so a stray focus event cannot make a recipe non-deterministic.
- Audio: gameplay SFX (bus Sfx) are stopped on pause, BGM keeps playing (the original's pause
  path never touches the music stream), and the recovered SE 0x11 plays on the UI bus. The
  expectation is published to the #16 combat-audio work, which owns no pause policy.
- Only a live offline battle that is not a capture or bounded run may pause (`--match`,
  `--versus`, `--hud-test`, `--screen=battle` captures, `--out`/`--headless` and any
  `--frames` run are excluded), so every parity recipe is byte-identical with the pause
  unused. A scripted standalone run gets `App::pauseScriptAdvance` so its match-frame-indexed
  script clock stays monotonic across a pause; it is zero for every run that never pauses.
- Verification: 36 native host tests including the device-free `battle_pause_test` (frozen
  economy/KO/respawn clocks, the held-button rule, the menu); asset-backed runs for pause
  mid-attack, rematch twice (same stage, identical scene/asset counts each cycle), return to
  selection and quit; and a mid-respawn run where 600 paused ticks (three times the 3 s
  window) produce no respawn and the respawn follows the resume. Linux, Windows cross-build
  and web builds succeed. Policy and provenance: `foundation/docs/PAUSE.md`.
- Rationale: a P1 offline release needs a way out of a battle that is not "kill the
  process", and the freeze has to be the authoritative step rather than a rendering trick,
  or timers keep running behind a still picture.

