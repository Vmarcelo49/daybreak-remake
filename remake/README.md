# daybreak

Old-game port — stage 2 skeleton.

Cross-compiled from Linux (Debian 13) to **Windows x64** with **MinGW-w64 (GCC 14, POSIX threads)**, **CMake 4.4** and **Ninja**, using **C++23**, **SDL2 2.30.10** and **Direct3D 9 + D3DX (June 2010)**.

## Stage 2 deliverables

- [x] `scripts/fetch_deps.sh` — anyone can bootstrap the toolchain (MinGW + CMake + Ninja + SDL2 + d3dx9_43.dll)
- [x] `build.sh` — one-shot configure + build
- [x] `.x` loader (`src/x_model_loader.{h,cpp}`) — ported from [X2Blend](https://github.com/Vmarcelo49/X2Blend)'s `viewer.cpp` runtime side
- [x] `.x` preprocessor with idempotent template injection (`src/x_file_preprocessor.{h,cpp}`)
- [x] Animation playback via `ID3DXAnimationController::AdvanceTime(deltaTime, …)` — driven by **delta time**
- [x] Skinned-mesh CPU skinning via `ID3DXSkinInfo::UpdateSkinnedMesh`
- [x] Orbit camera (mouse drag + scroll)
- [x] Animation set switching (SPACE / LEFT / RIGHT)
- [x] Compiles cleanly with `-Wall -Wextra -Wpedantic` under C++23

## Project layout

```
daybreak/
├── CMakeLists.txt
├── README.md
├── build.sh                              # configure + build
├── .gitignore
├── cmake/
│   └── toolchain-mingw-x86_64.cmake      # Linux → Windows x64 cross-compile
├── scripts/
│   └── fetch_deps.sh                     # bootstrap toolchain (no sudo)
├── src/
│   ├── main.cpp                          # SDL2 + DX9 + delta-time loop (entry point)
│   │
│   ├── core/         [placeholder]       # math, log, types, timer
│   ├── render/                           # D3D9 rendering subsystem
│   │   ├── x_model_renderer.h / .cpp     # camera + light + render states
│   │   └── (future: device, mesh, material, texture, shader/)
│   ├── file_parser/                      # file format parsers (no D3D dependency)
│   │   ├── dat_bundle.h / .cpp           # .DAT bundle reader (Higurashi Daybreak archive)
│   │   ├── dat_crypto.h / .cpp           # .DAT XOR-encryption primitives
│   │   ├── text_codec.h / .cpp           # Shift-JIS → UTF-8 filename conversion
│   │   ├── x_file_preprocessor.h / .cpp  # .x template-injection preprocessor
│   │   ├── x_model_loader.h / .cpp       # .x loader + animation playback (D3D-coupled)
│   │   └── (future: script_parser, archive_parser, …)
│   ├── gameplay/     [placeholder]       # arena-fighter logic: fighter, state machine,
│   │                                     #   combo system, AI controller, arena rules
│   ├── physics/      [placeholder]       # collision world, colliders, rigid body,
│   │                                     #   hitbox/hurtbox for combat
│   ├── maps/         [placeholder]       # stage representation, stage loader, stage data
│   ├── audio/        [placeholder]       # audio engine, sound, music streaming
│   ├── input/        [placeholder]       # input manager, key/button bindings
│   └── assets/       [placeholder]       # asset manager, asset handles
├── tests/
│   ├── test_triangle.x                   # static quad (no anim)
│   └── test_animated_cube.x              # cube + rotation animation
└── build/                                # generated; daybreak.exe + DLLs
```

### Subsystem layout rationale

The structure is organized around the major subsystems an arena fighter
(à la *Naruto Storm*) will need.  Each subfolder under `src/` owns one
subsystem and is intended to be largely independent of the others:

| Subfolder      | Owns                                              | Depends on        |
|----------------|---------------------------------------------------|-------------------|
| `core/`        | math primitives, logging, types, frame timer      | (none)            |
| `file_parser/` | file-format parsers (no D3D dependency)           | `core/`           |
| `render/`      | D3D9 device, renderable objects, shaders          | `core/`, D3D9/D3DX|
| `assets/`      | asset registry, handles, lifecycle                | `file_parser/`, `render/` |
| `physics/`     | broadphase collision, hitbox/hurtbox, rigid body  | `core/`           |
| `input/`       | input polling, key/button bindings                | `core/`           |
| `gameplay/`    | fighter, state machine, combos, AI, arena rules   | `physics/`, `assets/`, `input/` |
| `maps/`        | stage representation, stage loader                | `assets/`, `render/`, `physics/` |
| `audio/`       | audio device, sound playback, BGM streaming       | `core/`           |

Placeholder folders (currently containing only `.gitkeep`) are the
planned homes for subsystems we haven't implemented yet.  They'll be
filled in as the port progresses.

## Quick start

```bash
./scripts/fetch_deps.sh   # one-time; downloads MinGW, CMake, Ninja, SDL2, d3dx9_43.dll
./build.sh                # produce build/daybreak.exe
```

Run on Windows (or Wine):
```
daybreak.exe                              # stage-1 triangle fallback
daybreak.exe tests\test_triangle.x        # load static .x
daybreak.exe tests\test_animated_cube.x   # load animated .x (SPACE to cycle anims)
daybreak.exe -asset daybreak00.dat data/rika/01.X   # load .X from .DAT bundle (M1)
```

### Asset-loading modes (3 ways to get a model on screen)

| Invocation | What it does | When to use |
|---|---|---|
| `daybreak.exe` | Triangle fallback (stage 1) | Sanity check |
| `daybreak.exe <path/to/model.x>` | `XModel::load` reads from disk | Debugging a single `.X` file |
| `daybreak.exe -asset <bundle.dat>[:<bundle2.dat>...] <asset-name>` | `AssetManager` extracts from `.DAT` and feeds bytes to `XModel::load_from_memory` | **Production path** — this is how the game loads assets at runtime |

The `-asset` mode opens one or more `.DAT` bundles, registers them with
the `AssetManager`, then asks for an asset by name (e.g. `data/rika/01.X`).
The asset manager:

1. Looks up the name in each registered bundle (first match wins).
2. Reads + decrypts the payload into a memory buffer.
3. Calls `XModel::load_from_memory` which feeds the bytes straight to
   `D3DXLoadMeshHierarchyFromXInMemory` (no temp files, no disk I/O
   beyond the initial bundle open).

Textures are not loaded yet (the AssetManager passes an empty
texture_search_dir for now — M8 will add a texture provider that pulls
texture payloads from the same bundle).

### .DAT archive CLI mode

The same `daybreak.exe` doubles as a `.DAT` bundle inspector/extractor (no
SDL/D3D needed — it returns before the GUI loop starts). Mirrors the CLI
of the [Go reference](https://github.com/Vmarcelo49/higurashi-daybreak-in-go)
but only the read-side operations:

```
daybreak.exe -dat <file.dat> -list                                 # list all entries
daybreak.exe -dat <file.dat> -extract <outdir>                     # extract everything
daybreak.exe -dat <file.dat> -extract-file <index> -out <path>     # extract one by index
```

The `.exe` is built with `-mwindows` (GUI subsystem), so by default it has
no console attached.  When invoked with `-dat` from cmd.exe or PowerShell,
it calls `AttachConsole(ATTACH_PARENT_PROCESS)` and reopens stdin/stdout/
stderr against the parent's console so output shows up normally.

A synthetic test bundle (4 entries, including a Shift-JIS Japanese
filename and a subdirectory path) lives at `tests/test_bundle.dat` and can
be regenerated with `python3 tests/gen_test_dat.py`.

## .DAT file format

Ported from the [Go reference](https://github.com/Vmarcelo49/higurashi-daybreak-in-go). Read-only on the C++ side; the Go tool's patch/update operations are intentionally not ported (daybreak doesn't need to write back to the original game's archives).

```
offset 0:  uint16  numFiles
offset 2:  uint8   fileTable[numFiles * 268]   (XOR-encrypted, see dat_crypto)

each 268-byte table entry (after decryption):
  [0:260]   char    filename[260]   (Shift-JIS, null-padded)
  [260:264] uint32  length          (file size in bytes)
  [264:268] uint32  offset          (absolute offset in the .DAT)

file payloads: single-byte XOR with key = ((offset >> 1) & 0xff) | 0x08
```

The table block uses a stateful XOR stream keyed by a 9-bit index (always 0
in practice).  Filename decoding is Shift-JIS (CP932) → UTF-8 via Win32
`MultiByteToWideChar` / `WideCharToMultiByte`.

## Required runtime DLLs (next to daybreak.exe)

| DLL           | Source                                                                |
|---------------|----------------------------------------------------------------------|
| `SDL2.dll`    | copied automatically by `build.sh`                                   |
| `d3dx9_43.dll`| from `tools/d3dx9/` (auto-fetched by `fetch_deps.sh`); or install the [DirectX End-User Runtime (June 2010)](https://www.microsoft.com/en-us/download/details.aspx?id=8109) |
| `d3d9.dll`    | ships with Windows                                                   |

## Toolchain (one-time setup)

Run `./scripts/fetch_deps.sh`. It downloads into `tools/`:

| Component         | Source                                                  |
|-------------------|---------------------------------------------------------|
| CMake 4.4 / Ninja | pip wheels, into `tools/python/`                        |
| MinGW-w64 GCC 14  | Debian packages `g++-mingw-w64-x86-64-posix` + runtime  |
| DX9 headers/libs  | ship with MinGW-w64 (`d3d9.h`, `libd3d9.a`, `libd3dx9.a`) |
| SDL2 2.30.10      | official MinGW dev zip from libsdl.org                  |
| d3dx9_43.dll      | runtime DLL (downloaded; or copy from a Windows box)    |

The toolchain file resolves `tools/` relative to its own location, so it works from any CWD. Override with `-DDAYBREAK_TOOLS_DIR=/path`.

## How the .x loader works

Direction taken from [X2Blend](https://github.com/Vmarcelo49/X2Blend) (which uses `D3DXLoadMeshHierarchyFromXA` + a custom `ID3DXAllocateHierarchy`). X2Blend's pipeline is **export-only** (bakes animation to JSON for Blender import); daybreak uses the **runtime** side (renders the mesh + plays animations live).

```
.x file
   ↓  XFilePreprocessor (idempotent template injection)
preprocessed .x text
   ↓  D3DXLoadMeshHierarchyFromXA(device, …)
D3DXFRAME tree  +  ID3DXAnimationController
   ↓  per frame:
AdvanceTime(dt)  →  UpdateFrameMatrices  →  UpdateSkinnedMeshes  →  DrawSubset
```

Key classes:
- `daybreak::XFrame` — extends `D3DXFRAME` with `worldMatrix` (recomputed every frame).
- `daybreak::XMeshContainer` — extends `D3DXMESHCONTAINER` with materials vector, textures vector, and a CPU-skinned mesh clone.
- `daybreak::XModelAllocator` — `ID3DXAllocateHierarchy` implementation that delegates to `XModel`'s private `create_frame` / `create_mesh_container` / `destroy_*` methods.
- `daybreak::XModel` — public facade; `load(device, path)` → `update(dt)` → `render(device)` → `unload()`.

Animation control:
- `num_animation_sets()`, `animation_set_name(i)`, `switch_to_animation(i|name)`.
- `update(deltaTime)` clamps `deltaTime` to 0.1 s (avoid jumps after a stall) and calls `m_animController->AdvanceTime(deltaTime, nullptr)`.

## Build

```bash
./build.sh                              # Release
./build.sh Debug                        # Debug
./build.sh --clean                      # wipe build/ first
BUILD_TYPE=RelWithDebInfo ./build.sh
```

## Notes for future stages

- `winpthread` is statically linked (`-static-libgcc -static-libstdc++ -static`); the .exe has no MinGW runtime dependency.
- `libSDL2main.a` is linked with `--whole-archive` so its `WinMain` is always resolved against the mingw32 CRT.
- `main()` is rewritten to `SDL_main` via `SDL_main.h` — that's the SDL2 main-entry contract on Windows.
- `NOMINMAX`, `WIN32_LEAN_AND_MEAN`, `_CRT_SECURE_NO_WARNINGS`, `UNICODE`/`_UNICODE` are defined project-wide.
- The `.x` runtime dep on `d3dx9_43.dll` is intentional — D3DX's mesh-hierarchy + animation-controller API does the heavy lifting (template parsing, frame-tree construction, key interpolation, skinning). Writing a from-scratch `.x` parser would be a separate sub-project.
- Stage 3 candidates: input remapping, multi-mesh scene loading, model transforms (translate/rotate/scale), basic asset manifest.
