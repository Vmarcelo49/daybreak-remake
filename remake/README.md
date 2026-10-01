# daybreak — Higurashi Daybreak remake (playable 2v2 arena fighter)

C++23 + SDL2 + Direct3D 9, cross-compiled from Linux to **Windows x64**
(MinGW-w64, CMake + Ninja). Boots straight into a versus match: two
fighters, stage meshes, lock-on camera, melee combat with HP/KO/balloon
economy, HUD, and BGM.

> **The renderer is migrating to SDL3 + WebGPU** — decision D2 in
> [`docs/decisions.md`](docs/decisions.md), reversed 2026-10-01. The stack
> described below is what the tree is today; DX9 stays buildable as the
> A/B reference until the WebGPU path renders a matching in-game frame.

Start here for context: [`docs/game-spec.md`](docs/game-spec.md) (what the
game is + build plan) · [`docs/decisions.md`](docs/decisions.md) (binding
scope/tech decisions) · [`docs/reference/README.md`](docs/reference/README.md)
(21 ground-truth captures) · [`docs/placeholders.md`](docs/placeholders.md)
(shipped stand-ins vs their targets) ·
[`docs/roadmap.md`](docs/roadmap.md) (PT roadmap).

## Quick start

```bash
./scripts/fetch_deps.sh   # one-time toolchain bootstrap (no sudo)
./build.sh                # produce build/daybreak.exe
./build.sh --clean        # wipe build/ first (needed after moving the tree)
```

Run on Windows (or Wine), from a directory containing the game bundles:

```
daybreak.exe              # boots Scene_Gameplay (rika vs takano, stage21)
```

Bundles auto-load from the working directory
(`daybreak00/02/04/05/06/07.dat`, tolerant of missing files), and
`assets/shaders/effect_*.bin` must sit next to the exe (strict load —
startup aborts loudly without them).

Under Wine (see `launch_daybreak.sh` for the full recipe):

```bash
WINEDLLOVERRIDES="d3dx9_43=native" WINEDEBUG=-all wine daybreak.exe
```

## Controls (P1 keyboard, verified against the original)

| Key | Battle | Menus |
|---|---|---|
| Arrows | Move | Navigate |
| Z | Jump (hold = fly) | Confirm |
| X | Melee | Cancel on filled slots |
| C | Shoot (hold = charge) | — |
| A | Target switch (hold = aim ally) | — |
| S / D | Special / Guard (hold) | — |
| Q / W | Tactics / Pause | — (ESC quits) |

P2–P4 use gamepads (provisional map) or fallback keys — see
`src/input/input_manager.h`. F2 toggles animation debug (LEFT/RIGHT
cycles sets on P1's model).

## CLI tools (same exe, no window)

```
daybreak.exe -dat <file.dat> -list                              # list entries
daybreak.exe -dat <file.dat> -extract <outdir>                   # extract all
daybreak.exe -dat <file.dat> -extract-file <index> -out <path>   # extract one
daybreak.exe -asset-info <bundle.dat>[:...] <asset-name>         # locate + inspect
```

Built `-mwindows`, so `-dat`/`-asset-info` reattach to the parent console
on Windows. `tests/test_bundle.dat` (synthetic, regenerable via
`tests/gen_test_dat.py`) covers the read path in tests.

## How assets load (production path)

```
daybreakXX.dat --open--> DatBundle --register--> AssetManager
      --read/decrypt--> bytes --XModel::load_from_memory--> GPU
                                  \--UIImage / load_texture--> textures
```

- `AssetManager` scans registered bundles in order, first match wins,
  caches by name. Textures decode through `UIImage` (CNV auto-detect +
  D3DX for standard formats).
- `.x` files go straight from bundle bytes into
  `D3DXLoadMeshHierarchyFromXInMemory` — no temp files, no conversion
  pipeline (binding decision D3).

## Project layout

```
remake/
├── CMakeLists.txt / build.sh / cmake/toolchain-mingw-x86_64.cmake
├── scripts/fetch_deps.sh            # toolchain bootstrap
├── launch_daybreak.sh               # Wine run recipe (game + bundles)
├── src/
│   ├── main.cpp                     # SDL2+D3D9 boot, 6-bundle autoload,
│   │                                # strict effects, device-lost recovery,
│   │                                # 60fps loop → SceneManager
│   ├── core/      scene.h           # Scene base + SceneContext
│   │             scene_manager.*     # active scene, transitions, reset_current
│   │             scenes.*            # Bootstrap/Opening/Title/ModeSelect/
│   │                                 # CharacterSelect/Gameplay (+HUD wiring)
│   ├── render/    x_model_renderer.* # orbit-cam legacy helper
│   │             arena_camera.*      # lock-on camera + collision spring
│   │             ui_image.*          # BMP/CNV → texture + quad blits
│   │             video_player.*      # pl_mpeg OP-movie playback + skip
│   │             effect_system.*     # 10 D3DX effects, strict load
│   │             hud.*               # font/sprite HUD (balloon, HP, ammo…)
│   ├── file_parser/ dat_bundle.*    # .DAT reader (bit-exact vs original)
│   │               dat_crypto.*      # table + payload XOR primitives
│   │               text_codec.*      # Shift-JIS → UTF-8 filenames
│   │               x_file_preprocessor.*  # skin-template injection
│   │               x_model_loader.*  # hierarchy + skinning + 2-track anims
│   ├── gameplay/  fighter.*         # state machine, melee hits, HP/KO
│   ├── physics/   raycast.*         # D3DXIntersect frame-tree raycasts
│   ├── maps/      stage.*           # visible + 3 collision meshes
│   ├── input/     input_manager.*   # 4 players × 13 actions, edges/timers
│   ├── audio/     audio_engine.*    # SDL2_mixer SFX + streaming BGM
│   └── assets/    asset_manager.*   # bundle registry, model/texture cache
├── assets/shaders/                  # 10 extracted D3DX effects
├── tools/asset-tools/               # offline .dat/.cnv converters
├── tools/hook-tracer/               # original-exe injector + file tracer
├── tests/                           # .x fixtures + synthetic .dat
└── docs/                            # spec, decisions, roadmap, RE, reference
```

## .DAT file format

```
offset 0:  uint16  numFiles
offset 2:  uint8   fileTable[numFiles * 268]   (XOR-encrypted, see dat_crypto)

each 268-byte table entry (after decryption):
  [0:260]   char    filename[260]   (Shift-JIS, null-padded)
  [260:264] uint32  length          (file size in bytes)
  [264:268] uint32  offset          (absolute offset in the .DAT)

file payloads: single-byte XOR with key = ((offset >> 1) & 0xff) | 0x08
```

Table cipher is a stateful XOR stream (initial key/counter 100, `+77`
per byte). Bit-exact against the original's reader — validated against
the real 1.43 GB `daybreak00.dat` (7,677 entries). Read-only by design.

## How the .x loader works

```
bundle bytes
    ↓  XFilePreprocessor (idempotent skin-template injection, text .x only)
    ↓  D3DXLoadMeshHierarchyFromXInMemory (flags 0x220, Wine fallback to FromXA)
D3DXFRAME tree  +  ID3DXAnimationController (up to 2 tracks bound at load)
    ↓  per frame:
AdvanceTime(dt)  →  UpdateFrameMatrices  →  UpdateSkinnedMeshes  →  DrawSubset
```

Direction taken from [X2Blend](https://github.com/Vmarcelo49/X2Blend)'s
runtime side (their pipeline is export-only; ours renders live).
`XModel` facade: `load(device, path)` → `load_from_memory(…)` →
`update(dt)` (clamped to 0.1 s) → `render(device)` → `unload()`, with
`switch_to_animation(i|name)` (case-insensitive, track-0 fallback).

## Required runtime DLLs (next to daybreak.exe)

| DLL            | Source                                                   |
|----------------|----------------------------------------------------------|
| `SDL2.dll`, `SDL2_mixer.dll` | copied automatically by `build.sh`        |
| `d3dx9_43.dll` | `tools/d3dx9/` if fetched; else [DirectX End-User Runtime (June 2010)](https://www.microsoft.com/en-us/download/details.aspx?id=8109) |
| `d3d9.dll`     | ships with Windows                                        |

`winpthread` is statically linked, so there is no MinGW runtime
dependency. The `.x` runtime dep on `d3dx9_43.dll` is intentional (D3DX
does template parsing, frame trees, key interpolation, skinning).

## Build variants

```bash
./build.sh                              # Release
./build.sh Debug                        # Debug
BUILD_TYPE=RelWithDebInfo ./build.sh
```

`NOMINMAX`, `WIN32_LEAN_AND_MEAN`, `UNICODE`/`_UNICODE` are defined
project-wide; `libSDL2main.a` links `--whole-archive` for the
`WinMain`/CRT contract.
