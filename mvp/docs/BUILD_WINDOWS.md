# Build Instructions — daybreak_mvp (Windows)

## Option A: Visual Studio 2022 (recommended for beginners)

### 1. Install prerequisites

**Visual Studio 2022 Community** (free):
- Download: https://visualstudio.microsoft.com/downloads/
- During installation, select workload: **"Desktop development with C++"**
- This gives you MSVC, CMake, and the Windows SDK

**DirectX 9 SDK (June 2010)** — needed for `d3dx9.lib` (NOT included in modern Windows SDK):
- Download: https://www.microsoft.com/en-us/download/details.aspx?id=6812
- Install to default location: `C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\`
- Set environment variable `DXSDK_DIR` to that path (the installer usually does this)

### 2. Build

Open **"Developer Command Prompt for VS 2022"** (from Start menu):

```cmd
cd path\to\daybreak-decomp\mvp
cmake -B build -G "Visual Studio 17 2022" -A Win32
cmake --build build --config Release
```

### 3. Run

```cmd
build\Release\daybreak_mvp.exe
```

A 800x600 window titled "Higurashi Daybreak (MVP port)" should appear showing a slowly color-cycling screen. Press ESC to quit.

---

## Option B: MinGW-w64 (free, command-line only)

### 1. Install MSYS2

- Download: https://www.msys2.org/
- Follow installation instructions on the site

### 2. Install toolchain

Open **MSYS2 MINGW32** terminal (not the default MSYS2 terminal):

```bash
pacman -S --needed \
    mingw-w64-i686-gcc \
    mingw-w64-i686-cmake \
    mingw-w64-i686-directx-headers \
    make
```

### 3. Build

```bash
cd /c/path/to/daybreak-decomp/mvp
cmake -B build -G "MinGW Makefiles" \
    -DCMAKE_C_COMPILER=i686-w64-mingw32-gcc \
    -DCMAKE_MAKE_PROGRAM=mingw32-make
cmake --build build
```

### 4. Run

```bash
./build/daybreak_mvp.exe
```

**Note**: MinGW's `d3dx9` may not include the same version as Microsoft's DirectX SDK. If you get linker errors for `D3DXCreateEffect`, you may need to install the Microsoft DirectX 9 SDK separately and point CMake at it:

```bash
cmake -B build -G "MinGW Makefiles" \
    -DCMAKE_C_COMPILER=i686-w64-mingw32-gcc \
    -DDXSDK_DIR="C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)"
```

---

## Option C: CLion or other IDE

Any IDE that supports CMake should work. Open the `mvp/` directory as a CMake project. Set the toolchain to MSVC or MinGW as configured above.

---

## Common issues

### "d3d9.h not found"

You're missing the DirectX 9 SDK. Install it (see Option A step 1) and ensure `DXSDK_DIR` environment variable is set.

### "d3dx9.lib not found"

Same as above — `d3dx9` is part of the legacy DirectX SDK, not the modern Windows SDK.

### "Cannot find d3dx9_43.dll" at runtime

Install the **DirectX End-User Runtime Web Installer**:
- https://www.microsoft.com/en-us/download/details.aspx?id=35

This installs `d3dx9_43.dll` (and other DX9 DLLs) to `C:\Windows\System32\`.

### Window opens but immediately closes

Check the error MessageBox that appeared. Most likely D3D initialization failed. Common causes:
- DirectX 9 runtime not installed
- Graphics driver doesn't support DX9 (very old or very new hardware)
- Running in a VM without 3D acceleration

### Black screen (no color cycling)

The device was created but Present() is failing silently. Try:
1. Update graphics drivers
2. Force REF rasterizer by editing `d3d_init.c` and using only `CREATEFLAGS_REF`
3. Check if `d3d9.dll` is loaded (use Process Explorer)

### Color cycling is too fast/slow

Edit `render_loop.c` line in `RunMainLoop`:
```c
Sleep(16 - frame_time);  // 16ms = ~60 FPS
```
Change `16` to `33` for 30 FPS or `8` for 120 FPS.

---

## Verifying the build

After successful build, the executable should:
1. Open a window with title "Higurashi Daybreak (MVP port)"
2. Window size: 800x600 client area (slightly larger with title bar + borders)
3. Window should have a black background initially, then slowly cycle colors
4. Pressing ESC closes the window cleanly
5. Closing via X button also works cleanly

If all 5 work, the MVP is functional and you can proceed to `docs/TODO.md` Phase MVP+1.
