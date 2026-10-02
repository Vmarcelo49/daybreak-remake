# Port plan: mvp → remake

> Status HISTORY (Phase 5 cutover 2026-10-02): this plan ported the
> retired `mvp/` tree into the DX9 `remake/src/` tree (deleted). P0
> survives as relocated tooling; P1–P4 as ported behaviour now
> re-implemented in `remake/foundation/` (SDL3 + WebGPU, C++17).
> Remaining work is the foundation roadmap, not just P3.1-bind. Build
> is `remake/foundation/build.sh {deps,linux,windows,web}` (see
> `foundation/build.sh:3-7`); host suite is 13 ctest tests
> (`foundation/CMakeLists.txt:165-267`: debug_prims_geometry,
> raycast_analytic, dat_bundle_bytes, match_economy_test,
> fighter_script_test, arena_camera_test, animation_pose_test,
> lighting_test, text_test, hud_sprite_table, hud_text_test,
> unlit_cube_geometry, screen_stack_test).

Source: the retired `mvp/` tree (deleted 2026-10-01 after this
plan was implemented — do not look for it; decomp provenance lives
in `research/decompiled/`, `research/binary_data/`, with reviewed
truth in `research/symbols/`).
Target: `remake/foundation/` (C++17, SDL3 + WebGPU; entry
`remake/foundation/build.sh`, binary `build/linux/foundation_demo`;
visual target is the original's prints in
`remake/docs/reference/*.webp`, DX9 frames in
`remake/tests/parity-baseline/` are a behavioural oracle only).

Derived from full audits of both trees (2026-10-01). Items mvp genuinely
owns that the remake lacks; everything else the remake already supersedes.

## P0 — Relocate dev tooling (no code changes, do first)

Copy — do not move, do not modify mvp — into remake-side homes:

| mvp source | remake destination (suggested) | Notes |
|---|---|---|
| `hook/extract_dat.py`, `dat_packer.py`, `cnv_convert.py`, `cnv_pack.py` | `tools/asset-tools/` (new) | Offline `.dat` extract/repack + `.cnv`↔`.bmp/.wav`. Real, working. |
| `shaders/effect_0..9.bin` | `assets/shaders/` | 10 D3DX effect blobs (21220 B total). Note: `effect_0` and `effect_7` share size 3436 but differ in content (different hashes) — keep both slots; see `remake/assets/shaders/README.md`. |
| `hook/src/daybreak_launcher.c` | `tools/hook-tracer/` (new) | Working injector (`CreateProcess SUSPENDED` + `CreateRemoteThread(LoadLibraryA)`). Keep as-is (C, Win32). |
| `hook/src/daybreak_hook.c` (v11) | same | **Tracer only** — logs `CreateFileA` for asset extensions, patches nothing. Useful for RE; see D4. |
| `include/scene_defs.h`, `include/engine.h` offsets | comments only (P2.1) | No code to port; constants as documentation. |

Acceptance: remake builds/runs identically; new dirs contain verbatim
copies (+ a `README.md` each stating origin + "mvp frozen" pointer).

## P1 — Engine hardening (small, high value)

- **P1.1 Multi-archive bootstrap (HISTORY — order corrected by RE).**
  Done, with the plan's 00-first order superseded:
  `fnd::assets::DatBundleSet` opens six bundles tolerant of absents
  and resolves first-match-wins in exe registration order 07, 04, 00,
  05, 02, 06 (`foundation/src/assets/dat_bundle.cpp:278-281`; why in
  `:259-276` — resolving `data/object/P01.cnv` to 00 drew the wrong
  fan, `battle-hud.webp` matches 04). Wired via
  `AssetSource::openInstall`
  (`foundation/src/assets/asset_source.cpp:76`,
  `foundation/src/main.cpp:1230-1247`), which logs `%zu/%zu .dat
  bundle(s)`. No `Scene_Bootstrap` — that was the DX9 tree's seam.
- **P1.2 Device-lost recovery (HISTORY — D3D9-only, not applicable).**
  `TestCooperativeLevel → Reset` belonged to the deleted DX9 main
  loop. The WebGPU foundation (`foundation/src/gpu/gpu.cpp`,
  `foundation/src/main.cpp:1488-1500` teardown) has no Reset seam;
  surface loss is handled by re-creating the surface/swapchain, not by
  porting the mvp pattern. Alt-tab survival is verified at the
  SDL3/WebGPU level instead.
- **P1.3 Frame pacing + shutdown order (HISTORY — DX9 shape deleted).**
  The mvp `Sleep` throttle and shaders→scenes→archives→device teardown
  belonged to the DX9 loop. The foundation paces via `--frames/--dt`
  scripted timelines and `SDL_AppIterate`
  (`foundation/src/main.cpp:84-87,1176,1370`) and tears down ui →
  debug prims → renderer → WebGPU objects → surface → context → window
  (`:1488-1500`). Steady-60 and leak-warning acceptance no longer
  apply; capture determinism is covered by the parity-baseline bank.

## P2 — Scene-flow parity (data, not code)

- **P2.1 Scene ids as documentation (HISTORY — ids corrected by RE,
  new home).** The `scene_defs.h` values (TITLE=0, SELECT=1, VS_LOAD=2,
  BATTLE=3, …) are superseded — do not copy them. The proven ids live
  as `ui::ScreenId` in `foundation/src/ui/screen.h:39-56`
  (`FUN_004020a0` switch: Title 0x01, Select 0x03, VsIntro 0x09, Battle
  0x0a, …; 0x02/0x0e–0x13 unnamed per FRONTEND-PLAN §7.6).
  `src/core/scenes.h` never survived the Phase 5 cutover; future
  debugger notes go next to `screen.h`, citing `FUN_xxxxxx`.
- **P2.2 Title menu data** (from retired `mvp/src/scene_title.c`).
  ⚠️ SUPERSEDED by captures (`docs/reference/title-menu.webp`): the real
  title has **6 items at different positions** (y≈280, ~45px stride), not
  mvp's inferred 9 at X=180/Y=128+i*32 — do NOT implement those numbers.
  Kept for the record: Up/Down wrap + confirm/cancel grammar idea only.
- **P2.3 Stub-flow conventions (HISTORY — replaced by the RE'd
  switcher).** The 180-frame VS auto-advance and X-to-Title stub rules
  were mvp placeholders — do not implement. The foundation uses
  `ui::ScreenStack` (`foundation/src/ui/screen.h:93-131`): update
  returns the next id, 25-frame fade per `FUN_00657c80` (`kFadeFrames
  0x19`), factory `makeScreen`. Title wrap is `(i+1)%6` / `(i+5)%6`
  (`screen_title.h:12-13`); flow order follows
  `remake/docs/reference/README.md` (team first, then characters).

## P3 — Rendering assets (the real work)

- **P3.1 — Effect system (HISTORY — DX9 loader deleted; bytecode kept
  as evidence)**

  The DX9 `src/render/effect_system.*` strict loader (missing slot
  aborts startup, owned lifetime, raw accessors) shipped 2026-10-01 and
  was deleted in the Phase 5 cutover. The 10 blobs survive as evidence
  in `remake/assets/shaders/effect_0..9.bin` (`CreateAllShaders`
  `FUN_0064ff80`). Nothing in the product loads them yet;
  technique/pass binding per mesh category was never in mvp and remains
  fresh RE + new WebGPU pipeline code in
  `foundation/src/render/scene_renderer.cpp` +
  `foundation/src/gpu/gpu.cpp`.
- **P3.2 Texture provider (HISTORY — D3DX call deleted; runtime CNV
  path exists).** The `mvp/src/texture_loader.c` pattern
  (`D3DXCreateTextureFromFileInMemory` under an `AssetManager`) was the
  DX9 design and is gone with it. The foundation decodes CNV at runtime
  via `xm::decodeCnvImage` (`foundation/src/assets/cnv.h:61,154`),
  consumed e.g. by `foundation/src/ui/hud_atlas.cpp:37`. Offline
  `tools/asset-tools/cnv_convert.py` remains for inspection; it is no
  longer a prerequisite.

## P4 — Loader parity (HISTORY — DX9 implementation deleted in Phase 5; behaviour re-implemented in the foundation)

The DX9 `XModel::load_from_buffer_impl`
(`src/file_parser/x_model_loader.cpp`:
`D3DXLoadMeshHierarchyFromXInMemory` with `0x220`, Wine `FromXA`
fallback, 2-track 1.0/0.0 bind) was verified 2026-10-01 and then
deleted with `remake/src/`. The behaviour lives on as `xm::Model` +
`xm::Controller` in `foundation/src/assets/xmodel.h:10-13,208-236`
(header-only .X + skeletal animation for WebGPU; 2-track blend, track
0 weight 1.0). Do not look for the D3DX loader; extend `xmodel.h` and
its `animation_pose_test` instead.

## P5 — Explicitly NOT ported (HISTORY — closed with the DX9 tree)

- `input_init.c` (DirectInput) — superseded by the SDL3 backend
  (`foundation/src/input/input_backend.cpp:1-36`; bindings pinned in
  `input_sdl3.h`, authoritative table in
  `remake/docs/reference/README.md` controller-setup row: Z
  jump/confirm, X melee/cancel, C shoot, A lock, S special, D guard, Q
  tactics, W pause).
- mvp's lenient shader `MessageBox` and `scene_stubs.c` `DrawTextA`
  placeholders — deleted with the DX9 tree; no equivalent in the
  foundation.
- `SetupRenderStates (FUN_00654f00)` — was TODO in mvp too; remains an
  open RE gap, not a port item.
- Hook inline-patching — never existed in code (D4;
  `tools/hook-tracer/daybreak_hook.c:105` is a `CreateFileA` tracer);
  nothing was or will be ported.

## Suggested order (HISTORY — completed 2026-10-01; kept for the record)

P0 → P1 → P4 → P2 → P3.1(load) → P3.2 → P3.1(bind). P0–P2 took days;
P3.1-bind was the fresh-RE tail. The P0 homes are no longer '(new)' —
`remake/tools/asset-tools/`, `remake/tools/hook-tracer/`,
`remake/assets/shaders/` (each with a README stating origin + 'mvp
frozen' pointer). Later phases (front-end RE in
`foundation/src/ui/screen.h`, gameplay, HUD, LAN netplay per
decisions.md D6) lie outside this plan.
