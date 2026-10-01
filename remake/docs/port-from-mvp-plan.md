# Port plan: mvp → remake

> Status 2026-10-01: **P0–P4 all implemented** (P4 was already in the
> loader — verified, not re-done). Remaining future work is only the
> P3.1 technique/pass binding, which needs fresh RE. Build passes
> 17/17 (`./build.sh`, `-Wall -Wextra -Wpedantic` clean).

Source: the retired `<project>/mvp/` tree (deleted 2026-10-01 after this
plan was fully implemented — do not look for it; decomp provenance lives
in `<project>/decompiled/` and `binary_data/`).
Target: this repo (`remake/`).

Derived from full audits of both trees (2026-10-01). Items mvp genuinely
owns that the remake lacks; everything else the remake already supersedes.

## P0 — Relocate dev tooling (no code changes, do first)

Copy — do not move, do not modify mvp — into remake-side homes:

| mvp source | remake destination (suggested) | Notes |
|---|---|---|
| `hook/extract_dat.py`, `dat_packer.py`, `cnv_convert.py`, `cnv_pack.py` | `tools/asset-tools/` (new) | Offline `.dat` extract/repack + `.cnv`↔`.bmp/.wav`. Real, working. |
| `shaders/effect_0..9.bin` | `assets/shaders/` (new) | 10 D3DX effect blobs (~20.7 KB). Note: `effect_0` == `effect_7` byte-identical; keep both slots, flag the dup. |
| `hook/src/daybreak_launcher.c` | `tools/hook-tracer/` (new) | Working injector (`CreateProcess SUSPENDED` + `CreateRemoteThread(LoadLibraryA)`). Keep as-is (C, Win32). |
| `hook/src/daybreak_hook.c` (v11) | same | **Tracer only** — logs `CreateFileA` for asset extensions, patches nothing. Useful for RE; see D4. |
| `include/scene_defs.h`, `include/engine.h` offsets | comments only (P2.1) | No code to port; constants as documentation. |

Acceptance: remake builds/runs identically; new dirs contain verbatim
copies (+ a `README.md` each stating origin + "mvp frozen" pointer).

## P1 — Engine hardening (small, high value)

- **P1.1 Multi-archive bootstrap** (from `mvp/src/archive_init.c`).
  Register `daybreak00/02/04/05/06/07.dat` in that order, first-match-wins,
  tolerant when some are absent (log + continue). Wire into
  `Scene_Bootstrap` instead of today's manual/hard-skipped bundle setup.
  Acceptance: boots with any subset of bundles; log shows `N/6 loaded`.
- **P1.2 Device-lost recovery** (from `mvp/src/render_loop.c`:
  `TestCooperativeLevel` → `Reset`).
  Port into remake main loop. The original allegedly lacks it; mvp's
  version is proven pattern. Acceptance: alt-tab away/back survives.
- **P1.3 Frame pacing + shutdown order** (from `render_loop.c` / `main.c`).
  60 fps cap (`Sleep`-style throttle on top of dt loop) and deterministic
  teardown (shaders → scenes → archives → device). Acceptance: steady
  60 fps, clean exit, no device-leak warnings.

## P2 — Scene-flow parity (data, not code)

- **P2.1 Adopt original SceneId values + offsets as documentation.**
  `TITLE=0, SELECT=1, VS_LOAD=2, BATTLE=3, CONNECT=7, BATTLE_RUN=8`
  (`scene_defs.h`); `GameState` offsets `0x2e14/0x2e18/0x2e20…`; input
  globals `0x006cae94…a0`. Put them in `src/core/scenes.h` comments so
  future debugger sessions speak the same language. No behavior change.
- **P2.2 Title menu data** (from `mvp/src/scene_title.c`, a port of
  `RenderTitle FUN_00403470`).
  Merge into remake `Scene_Title`: 9 items at **X=180, Y=128+i*32**;
  Up/Down wraps; `Enter/Z` confirm, `X/Backspace` cancel; mapping
  `0→Select, 1→Connect, 3/4→Battle, 8→quit`, items 2/5/6/7 no-op.
  Keep remake's CNV backgrounds + SDL input; take only positions/map.
  Caveat: mvp's labels are **guessed from screenshots** (original used a
  bitmap-font glyph sheet) — treat as placeholder text.
- **P2.3 Stub-flow conventions** (from `scene_manager.c`).
  VS auto-advance after 180 frames (`VS→BATTLE`); `X` returns any stub
  scene to Title. Use for TeamSelect/Result/Config until real.

## P3 — Rendering assets (the real work)

- **P3.1 Effect system** (blobs in `assets/shaders/` + logic from `mvp/src/shader_load.c`).
  `src/render/effect_system.*` implemented 2026-10-01: strict load
  (any missing/failing slot aborts startup with a log line — the
  deliberate divergence from mvp's lenient MessageBox), lifetime owned,
  raw non-owning accessors. Still TODO: wiring into `App`/`SceneContext`
  + teardown order, and technique/pass binding per mesh category, which
  mvp never did — that half is fresh RE + new code.
- **P3.2 Texture provider** (pattern from `mvp/src/texture_loader.c`,
  the planned "M8 texture provider").
  `archive bytes → D3DXCreateTextureFromFileInMemory`, owned by
  `AssetManager`. Prerequisite: CNV-encoded payloads must go through the
  `cnv_convert` path first (offline via P0 tools, or runtime later).

## P4 — Loader parity (ALREADY IMPLEMENTED — verified 2026-10-01)

`XModel::load_from_buffer_impl` (`src/file_parser/x_model_loader.cpp`)
already does all three: `D3DXLoadMeshHierarchyFromXInMemory` first with
mesh flags `0x220` (`D3DXMESH_32BIT | D3DXMESH_NPATCHES`), Wine fallback
to file-based `...FromXA` when the InMemory loader returns no animation
controller, and up-to-2 track binding at load (track 0 weight 1.0, track
1 weight 0.0 — original uses 1.0/1.0; revisit only if blend looks wrong).
No work remaining.

## P5 — Explicitly NOT porting

- `input_init.c` (DirectInput keyboard) — SDL covers it; keep the
  `& 0x80` / `DIK_*` notes as comments for key-code cross-checks only.
- mvp's lenient shader `MessageBox` behavior (see P3.1).
- `scene_stubs.c` `DrawTextA` placeholders — remake scenes supersede.
- `SetupRenderStates (FUN_00654f00)` — TODO in mvp too; open RE gap.
- Hook inline-patching — **does not exist in code** (D4); nothing to port.

## Suggested order

P0 → P1 → P4 → P2 → P3.1(load) → P3.2 → P3.1(bind).
P0–P2 are days; P3.1-bind is the only item needing fresh RE.
