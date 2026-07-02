# MVP Scripts

## `setup_and_build_mvp.sh` — Build the MVP

**Purpose**: Setup cross-compile environment (LLVM-MinGW + CMake) and build `daybreak_mvp.exe` from any agent environment.

**Idempotent**: safe to re-run. Skips already-installed components.

### Usage

```bash
# From any agent environment
bash mvp/scripts/setup_and_build_mvp.sh

# Custom LLVM-MinGW location
LLVM_MINGW_ROOT=/custom/path bash mvp/scripts/setup_and_build_mvp.sh
```

### What it does

1. Verifies prerequisites (curl, tar, MVP directory)
2. Installs CMake via pip if not present
3. Downloads + extracts LLVM-MinGW (71MB, one-time) if not present
4. Configures CMake with cross-compile toolchain
5. Builds `daybreak_mvp.exe` (~234 KB PE32)
6. Verifies the output is a valid PE32 executable

### Output

```
mvp/build/daybreak_mvp.exe
```

- PE32 executable for Windows, Intel i386
- ~234 KB
- Links against: d3d9.dll, d3dx9_43.dll, dinput8.dll, winmm.dll, user32.dll, gdi32.dll, ole32.dll

### Time estimates

- First run: ~3-5 min (downloads LLVM-MinGW)
- Subsequent runs: ~10 sec (cached, just rebuilds)

### Rebuild after code changes

```bash
# Fast rebuild
cmake --build mvp/build

# Or clean rebuild
rm -rf mvp/build && bash mvp/scripts/setup_and_build_mvp.sh
```

### Common issues

**"Download failed"**: GitHub may be slow. Script uses `curl -C -` for resume — just re-run.

**"CMake configuration failed"**: Clean state — `rm -rf mvp/build` and retry.

### Files modified

- `${HOME}/mingw86/llvm-mingw/` — LLVM-MinGW installation (71MB, persistent across runs)
- `${HOME}/.venv/bin/cmake` — CMake (if installed via pip)
- `mvp/build/` — Build output (gitignored)

Nothing outside these locations is touched.
