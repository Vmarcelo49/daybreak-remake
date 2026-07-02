# daybreak_hook — DLL Hook for DaybreakDX.exe

> Enables **direct file mode** in the original `DaybreakDX.exe`, so the game loads assets from the `data/` folder instead of from `daybreakXX.dat` archives. Supports **hybrid mode** that tries direct file first, then falls back to archive.

## What this does

The original `DaybreakDX.exe` has an internal flag that controls whether to use archive mode (`1`) or direct file mode (`0`):

- `FUN_0064d760` (at `0x0064d760`) — sets the flag to `1` (enable archive mode)
- `FUN_00699fc0` (at `0x00699fc0`) — reads the flag
- `FUN_00653540` (at `0x00653540`) — checks the flag:
  - If `flag == 0` → `CreateFileA(filename)` (direct file mode)
  - If `flag != 0` → archive lookup in `daybreakXX.dat`

At startup, `WinMain` calls `FUN_0064d760()` which sets the flag to `1`, forcing archive mode. The "direct file mode" code path exists in the binary but is **never activated** in normal operation.

This DLL hooks those functions to:

1. **Mode 0 (Direct only)**: Never set the flag — game always uses direct file mode
2. **Mode 1 (Archive only)**: Don't hook anything — game uses archives (default)
3. **Mode 2 (Hybrid)**: Try direct file first; if not found, fall back to archive

## Usage

### Quick start

1. Build the hook (see below)
2. Copy `daybreak_hook.dll` and `daybreak_launcher.exe` to your Higurashi Daybreak folder (next to `DaybreakDX.exe`)
3. Run `daybreak_launcher.exe` instead of `DaybreakDX.exe`
4. The launcher injects the DLL and starts the game with hooks active

### Mode selection

Set the `DAYBREAK_HOOK_MODE` environment variable before running the launcher:

```cmd
:: Mode 0 = Direct file only (assets loaded from data/ folder)
set DAYBREAK_HOOK_MODE=0
daybreak_launcher.exe

:: Mode 1 = Archive only (original behavior — use daybreakXX.dat)
set DAYBREAK_HOOK_MODE=1
daybreak_launcher.exe

:: Mode 2 = Hybrid (try direct first, then archive) — DEFAULT
set DAYBREAK_HOOK_MODE=2
daybreak_launcher.exe
```

If `DAYBREAK_HOOK_MODE` is not set, defaults to **Mode 2 (Hybrid)**.

### What you'll see

When the DLL loads, a MessageBox appears:
```
daybreak_hook loaded!

Mode: 2 (Hybrid (direct + archive fallback))
Image base: 0x00400000
Hooks installed: Yes
```

Click OK and the game starts. The game now:
- First tries to load `data/title/back00.bmp` from disk
- If not found, looks inside `daybreak00.dat` (or whichever archive contains it)
- Same for all other assets (BMPs, OGGs, .x meshes, etc.)

## How to add custom assets

1. Create a `data/` folder next to `DaybreakDX.exe`
2. Place your modified BMPs/OGGs/.x files there, mirroring the original paths:
   ```
   data/
   ├── title/
   │   ├── back00.bmp    ← your custom background
   │   ├── logo.bmp
   │   └── title.bmp
   ├── bgm/
   │   └── title.ogg     ← your custom music
   ├── select/
   │   └── p00.bmp       ← your custom character portrait
   └── ...
   ```
3. Run `daybreak_launcher.exe` (with `DAYBREAK_HOOK_MODE=2` or `0`)
4. The game uses your custom files instead of the archived originals

## Build

### Linux cross-compile (LLVM-MinGW)

```bash
cd mvp/hook
cmake -B build -DCMAKE_TOOLCHAIN_FILE=../cmake/i686-w64-mingw32.cmake
cmake --build build
# Outputs: build/daybreak_hook.dll + build/daybreak_launcher.exe
```

### Windows native (MSVC)

```cmd
cd mvp\hook
cmake -B build -G "Visual Studio 17 2022" -A Win32
cmake --build build --config Release
```

### Windows native (MinGW)

```bash
cd mvp/hook
cmake -B build -G "MinGW Makefiles"
cmake --build build
```

## How it works (technical)

### Inline hooking

The hook uses **inline patching** — it overwrites the first 5 bytes of each target function with a `JMP rel32` instruction that jumps to our detour function.

```
Original function (5 bytes):
  push ebp          ; 55
  mov ebp, esp      ; 8B EC
  push ecx          ; 51
  mov [ebp-4], ecx  ; 89 4D FC

After hook:
  jmp <detour>      ; E9 XX XX XX XX
```

The detour function can:
- Inspect/modify arguments
- Call the original function (via saved trampoline)
- Skip the original entirely
- Modify the return value

### Hooked functions

| Function | Address | Original behavior | Hook behavior (hybrid mode) |
|----------|---------|-------------------|-----------------------------|
| `FUN_0064d760` | `0x0064d760` | Sets flag to 1 (archive mode) | Does nothing (leaves flag at 0 = direct mode) |
| `FUN_00699fc0` | `0x00699fc0` | Returns flag value | Always returns 0 (direct mode) |
| `FUN_00653540` | `0x00653540` | If flag!=0: archive; else: CreateFileA | Try direct file; if fail, temporarily unhook and call original (archive lookup) |

### DLL injection

The launcher uses the classic `CreateRemoteThread + LoadLibraryA` technique:

1. `CreateProcess("DaybreakDX.exe", CREATE_SUSPENDED)` — start game frozen
2. `VirtualAllocEx` — allocate memory in game process for DLL path string
3. `WriteProcessMemory` — write `"daybreak_hook.dll"` into game process
4. `CreateRemoteThread(LoadLibraryA, remote_mem)` — game process loads our DLL
5. `ResumeThread` — game starts executing with hooks already installed

When `daybreak_hook.dll` loads, its `DllMain(DLL_PROCESS_ATTACH)` calls `InstallHooks()` which patches the three target functions.

## Limitations

1. **Anti-virus may flag the launcher** as suspicious (DLL injection is also used by malware). Add an exclusion if needed.

2. **Game updates break hooks**. If `DaybreakDX.exe` is updated, function addresses may change. The hook uses hardcoded addresses from the decompilation. To update, re-analyze the binary and update `ADDR_*` constants in `daybreak_hook.c`.

3. **No ASLR support for the hook addresses**. `DaybreakDX.exe` is 32-bit and typically loads at its preferred base `0x00400000`. If ASLR moves it, the hook calculates correct offsets from `GetModuleHandle(NULL)`.

4. **Hybrid mode has a small race condition**. When falling back to archive mode, the hook briefly removes the `get_flag` hook. In single-threaded game code this is fine, but if the game spawns threads before asset loading, there could be a window where another thread sees `flag=1`.

## Troubleshooting

### "DLL injection failed"

- Make sure `daybreak_hook.dll` is in the same folder as `daybreak_launcher.exe`
- Run the launcher as Administrator
- Check that `DaybreakDX.exe` is not already running
- Disable antivirus temporarily (DLL injection is flagged as suspicious)

### Game crashes on startup

- The hook addresses may be wrong (different game version). Check the MessageBox that appears when the DLL loads — it shows the image base. If it's not `0x00400000`, you need to update the `ADDR_*` constants.
- Try `DAYBREAK_HOOK_MODE=1` (archive only) to verify the launcher works without hooks.

### Game runs but assets still load from archive

- Make sure `DAYBREAK_HOOK_MODE=0` or `2` (not `1`)
- Check the MessageBox — it should say "Mode: 2 (Hybrid...)" or "Mode: 0 (Direct...)"
- Verify your `data/` folder structure matches the original game's paths

## License

MIT — this is original work based on reverse engineering of `DaybreakDX.exe` for interoperability purposes.
