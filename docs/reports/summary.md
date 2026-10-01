# Findings summary — DaybreakDX.exe

> English executive summary. Full technical detail (Portuguese):
> `docs/archive/RELATORIO_COMPLETO.md`. Final executive report (PT):
> `docs/archive/RELATORIO_EXECUTIVO_FINAL.md`.

## Target

PE32 x86 (MSVC), image base `0x00400000`, ~2.86 MB, 4,092 functions,
39,002 symbols, 464 data types. `.text`/`rdata`/`data`/`rsrc` standard
layout (see `docs/archive/RELATORIO_COMPLETO.md` §2).

## Entry path

CRT `entry` (`0x0066c906`) → `FUN_0064d250` (`WinMain`: registers
`"HigurashiDaybreak"`, fixed 800×600) → `CommonInit` (`0x00543c70`:
D3D device, DirectInput, audio bootstrap) → `LoadNextScene`
(`0x00406310`), called indirectly via the pointer at `0x006a16c0`.

## Corrected hypothesis (phase 9)

`0x006a16c0` is **not** a scene-handler table — it is a
`SceneDispatcherConfig` struct (dispatcher pointer + UI layout floats +
asset path strings). Real dispatch: `switch(*(pGameState + 0x2e18))`
with cases title / character-select / VS-load / battle-init (→ scene 8).
13 scene-related callees mapped with confidence grades.

## Game systems identified

- **Graphics**: Direct3D 9 + D3DX (25 calls), `.x` meshes
  (`D3DXLoadMeshHierarchyFromXInMemory`), `D3DXIntersect` collision,
  10 embedded effects, fixed-function + sprite UI (`.bmp`/`.cnv`).
- **Input**: DirectInput 8 (keyboard/joystick globals at
  `0x006cae94…a0`).
- **Audio**: BGM as `.ogg` (`data/bgm/title.ogg` call site found);
  voice `.wav`; mixer init unconfirmed (DirectMusic vs Miles open).
- **Network**: DirectPlay 8, client/server/peer, 8 tick-counter slots,
  full menu-dispatcher map (10 cases), `config.dat` save/load found.
- **Assets**: 6 `daybreakXX.dat` bundles (+2 skipped indices);
  per-asset `.dat`, `env.dat` per stage, `.mpg` movies.

## Hygiene

No packing, no anti-debug, no debugger checks that matter (phase 12:
1 CRT false positive, 86 mostly-false-positive findings, 156
asset-related IOCs). Straightforward static analysis target.

## Limits / open work

- ~900 functions unreachable (thunks/externals/stubs).
- Review coverage is thin (single-digit `reviewed`/`locked`);
  the corpus is decompiled, not understood.
- Audio mixer init, effect↔mesh binding, and app-layer netcode
  protocol remain unmapped — the three highest-value RE targets left.
