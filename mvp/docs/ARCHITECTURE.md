# Architecture — daybreak_mvp

## Overview

This MVP is a minimal Windows port of `DaybreakDX.exe` that:
- Creates the same window class `"HigurashiDaybreak"` at 800x600
- Initializes Direct3D 9 with the same 3-fallback chain (Hardware → Software → Reference)
- Loads the 10 D3DX effects embedded in the original binary
- Initializes DirectInput 8 keyboard
- Runs a render loop using BeginScene/EndScene/Present (same pattern as original)

## File-by-file mapping

| MVP file | Original function | Address | Original source |
|----------|-------------------|---------|-----------------|
| `src/main.c` | `WinMain` | `0x0064d250` | `decompiled/FUN_0064d250_entry_sub.c` |
| `src/engine_init.c` | `EngineInit` | `0x00657910` | `decompiled/FUN_00657910.c` |
| `src/d3d_init.c` | `InitD3D` | `0x00654b90` | `decompiled/FUN_00654b90.c` |
| `src/shader_load.c` | `CreateAllShaders` | `0x0064ff80` | `decompiled/FUN_0064ff80.c` |
| `src/input_init.c` | `InitDirectInput` + `InitKeyboard` | `0x00658260`, `0x00658410` | `decompiled/FUN_00658260.c`, `decompiled/FUN_00658410.c` |
| `src/render_loop.c` | `BeginScene` + `EndSceneAndPresent` + `ClearScreen` | `0x00650f70`, `0x00650fd0`, `0x00650d50` | `decompiled/FUN_00650f70.c`, etc. |

## What's different from original

### Simplifications (intentional)

1. **No DirectPlay** — multiplayer stubbed. Original has 48 functions for DirectPlay 8 (see `binary_data/network_analysis/`).
2. **No DirectMusic/audio** — audio stubbed. Original uses CoCreateInstance with custom IIDs (likely DirectMusic or Miles).
3. **No scene system** — only clear screen. Original has 10 scene renderers (see `binary_data/render_pipeline/FASE_RENDER_LOOP_REPORT.md`).
4. **No mesh loading** — `LoadMeshFromX` (FUN_0064d940) not ported. Original loads `.x` files via `D3DXLoadMeshHierarchyFromXInMemory`.
5. **No texture loading** — sprite textures (`.bmp` files) not loaded.
6. **No worker thread** — original creates a thread for audio mixing.
7. **No render sync event** — original creates an event for render thread sync.

### Additions (MVP-specific)

1. **Device lost recovery** — `AttemptDeviceRecovery()` in `render_loop.c`. Original sets a flag but doesn't recover (may be in unexplored code).
2. **Color-cycling clear screen** — to visually confirm the loop is running. Original always clears to black.
3. **Window proc ESC handler** — original checks ESC via DirectInput in MainGameLoop; MVP also checks via WindowProc for safety.

### Constants preserved exactly

| Constant | Value | From |
|----------|-------|------|
| Window class name | `"HigurashiDaybreak"` | `FUN_0064d250` |
| Window size | 800x600 | `FUN_0064d250` |
| D3D SDK version | `0x20` | `FUN_00654b90` |
| DirectInput version | `0x800` | `FUN_00658260` |
| CreateDevice flags HW | `0x44` | `FUN_00654b90` |
| CreateDevice flags SW | `0x24` | `FUN_00654b90` |
| CreateDevice flags REF | `0x22` | `FUN_00654b90` |
| Depth buffer format | `D3DFMT_D16` (0x50) | `FUN_00654b90` |
| Number of shaders | 10 | `FUN_0064ff80` |
| Keyboard cooperative level | `DISCL_NONEXCLUSIVE \| DISCL_FOREGROUND` (0x16) | `FUN_00658410` |

## Engine state struct

The `EngineState` struct in `include/engine.h` is a partial reconstruction of the original. Field offsets in comments are from analysis of `EngineInit` (`FUN_00657910`).

Known offsets from decompilation:
- `+0x00`: hwnd
- `+0x04`: hinstance
- `+0x08`: worker thread handle
- `+0x0c`: render sync event
- `+0x10`: thread ID
- `+0x14`: start_time (timeGetTime at init)
- `+0x17`: windowed flag
- `+0x1b`: scene_param (from config)
- `+0x1c`: IDirect3D9*
- `+0x20`: IDirect3DDevice9*
- `+0x24-0x5b`: D3DPRESENT_PARAMETERS (size 0x38)
- `+0x5c`: D3DCAPS9
- `+0x59`: device_lost flag
- `+0x68`: adapter format
- `+0x0e`: callback object pointer

Not all fields are used in MVP — only those needed for clear-screen rendering.

## Build dependencies

```
daybreak_mvp.exe
    ├─ d3d9.dll          (Windows built-in, DX9 runtime)
    ├─ d3dx9_43.dll      (from DirectX 9 June 2010 redistributable)
    ├─ dinput8.dll       (Windows built-in)
    ├─ winmm.dll         (Windows built-in)
    ├─ user32.dll        (Windows built-in)
    ├─ gdi32.dll         (Windows built-in)
    └─ ole32.dll         (Windows built-in, for CoInitialize)
```

End users need the **DirectX 9 June 2010 runtime** installed (specifically `d3dx9_43.dll`). Most Windows machines that have run any DX9 game already have this.

## Next steps after MVP runs

See `docs/TODO.md`.
