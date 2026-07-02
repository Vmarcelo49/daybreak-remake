# daybreak_mvp — Minimum Viable Port

> Goal: **compile and run on Windows**, showing the Higurashi Daybreak title screen.

## Status

✅ **Compiles** via LLVM-MinGW cross-compiler (Linux → Win32 PE32)
✅ **Title screen renders** with menu navigation
✅ **Shaders extracted** from original binary (10 D3DX effects, 20.7 KB)
✅ **Input works** (Up/Down/Enter/ESC via DirectInput 8)

## What the MVP does

1. Creates window class `"HigurashiDaybreak"` at 800x600 (from FUN_0064d250)
2. `EngineInit` (FUN_00657910) — orchestrates:
   - timeBeginPeriod(1) for 1ms timer
   - CoInitialize for COM
   - InitD3D with 3-fallback chain (HW→SW→REF, from FUN_00654b90)
   - CreateAllShaders — loads 10 D3DX effects from `shaders/*.bin` (FUN_0064ff80)
   - InitDirectInput + InitKeyboard (FUN_00658260, FUN_00658410)
3. `RunMainLoop` — 60 FPS loop that:
   - Updates current scene based on input
   - Renders current scene
   - Handles device lost (alt-tab recovery)
   - ESC quits cleanly

## Scenes implemented

| Scene | Status | Notes |
|-------|--------|-------|
| **Title** | ✅ Implemented | Menu with 9 items, Up/Down navigation, Enter to select |
| Select | ⏸️ Stub | Returns to title |
| VS | ⏸️ Stub | — |
| Battle | ⏸️ Stub | — |
| Network | ⏸️ Stub | Would require DirectPlay replacement |

## Title screen behavior

When you run the executable, you'll see:
- Dark blue background (or `data/title/back00.bmp` if available)
- "Higurashi Daybreak" text at top (white)
- 9-item menu at X=180, Y=128-384 (32px spacing — matches original positions)
- Selected item in yellow, others in light gray
- Bottom hint: "Up/Down: Navigate   Enter: Select   ESC: Quit"

## Quick build

```bash
# From any agent environment
bash mvp/scripts/setup_and_build_mvp.sh

# Or manually with CMake
cd mvp
cmake -B build -DCMAKE_TOOLCHAIN_FILE=cmake/i686-w64-mingw32.cmake
cmake --build build
```

Output: `build/daybreak_mvp.exe` (~243 KB PE32)

## Run on Windows

1. Copy `build/daybreak_mvp.exe` and `build/shaders/` to a Windows machine
2. Install DirectX 9 runtime if missing (for `d3dx9_43.dll`):
   https://www.microsoft.com/en-us/download/details.aspx?id=35
3. Optionally copy `data/title/back00.bmp` from original game for background
4. Double-click `daybreak_mvp.exe`

## Project structure

```
mvp/
├── README.md
├── CMakeLists.txt
├── cmake/i686-w64-mingw32.cmake      LLVM-MinGW toolchain
├── docs/                             Architecture + build + TODO
├── include/
│   ├── engine.h                      Types + function decls
│   ├── scene_defs.h                  Scene IDs + GameState offsets
│   └── d3d_utils.h                   COM release macros + colors
├── src/
│   ├── main.c                        WinMain + window class
│   ├── engine_init.c                 EngineInit (FUN_00657910)
│   ├── d3d_init.c                    InitD3D (FUN_00654b90)
│   ├── shader_load.c                 CreateAllShaders (FUN_0064ff80)
│   ├── input_init.c                  InitDirectInput + InitKeyboard
│   ├── render_loop.c                 Main loop + BeginScene/EndScene
│   └── scene_title.c                 Title screen (RenderTitle MVP+1)
├── scripts/
│   ├── README.md
│   └── setup_and_build_mvp.sh        Build script
└── shaders/                          10 D3DX effects extracted from original
    ├── effect_0.bin (3436 bytes)
    ├── effect_1.bin (3640 bytes)
    ├── ... (10 total, 20.7 KB)
    └── README.md
```

## Origin mapping

Each source file documents which function from `DaybreakDX.exe` it translates:

| File | Original | Address | Analysis ref |
|------|----------|---------|--------------|
| `main.c` | `WinMain` | `0x0064d250` | `RELATORIO_COMPLETO.md` §6.1 |
| `engine_init.c` | `EngineInit` | `0x00657910` | `binary_data/render_pipeline/FASE_D3D_REPORT.md` |
| `d3d_init.c` | `InitD3D` | `0x00654b90` | same |
| `shader_load.c` | `CreateAllShaders` | `0x0064ff80` | same |
| `input_init.c` | `InitDirectInput` + `InitKeyboard` | `0x00658260`, `0x00658410` | same |
| `render_loop.c` | `BeginScene` + `EndSceneAndPresent` + `ClearScreen` | `0x00650f70`, `0x00650fd0`, `0x00650d50` | `binary_data/render_pipeline/FASE_RENDER_LOOP_REPORT.md` |
| `scene_title.c` | `RenderTitle` (MVP+1 adaptation) | `0x00403470` | same |

## Next steps

See `docs/TODO.md` for the incremental roadmap. Highlights:
- MVP+2: Port `LoadNextScene` for scene state machine
- MVP+3: Asset loading (meshes `.x`, textures `.bmp`)
- MVP+5: Battle scene (the big one — 256 lines in original)

## License

Source code: MIT.
Embedded D3DX effects: copyright Twilight Frontier / 07th Expansion — used under fair use for interoperability.
