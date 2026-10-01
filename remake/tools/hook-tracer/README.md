# hook-tracer — launcher injector + file-access tracer (dev tool)

Verbatim copies from the frozen `mvp/hook/` (see `docs/decisions.md` D1 —
`mvp/` is read-only; if these need changes, change them **here**).

| File | Purpose |
|---|---|
| `daybreak_launcher.c` | **Working.** Injects a DLL into the original `DaybreakDX.exe` via `CreateProcess(SUSPENDED)` + `VirtualAllocEx` / `WriteProcessMemory` / `CreateRemoteThread(LoadLibraryA)`. Defaults overridable via argv. |
| `daybreak_hook.c` (v11) | **Tracer only — patches nothing.** IAT-hooks `CreateFileA` and logs opens of asset extensions (`.cnv/.bmp/.dat/.ogg/.wav/.x`, `data/`, `movie/`) with a reentrancy guard. Earlier versions (v1–v10) attempted inline `JMP rel32` patching for direct/archive/hybrid asset modes and crashed; v11 deliberately retreated to logging. |
| `CMakeLists.txt` | Builds `daybreak_hook.dll` (SHARED) + `daybreak_launcher.exe`. |

> Warning: `mvp/hook/README.md` describes Modes 0/1/2 hybrid patching —
> that design is **not in the code**. See `docs/decisions.md` D4. Do not
> plan runtime loose-file loading around this tool; it is for RE tracing
> (which files the original opens, in which order).

Build (from this dir):

```bash
cmake -B build -DCMAKE_TOOLCHAIN_FILE=../../cmake/toolchain-mingw-x86_64.cmake
cmake --build build
```

Note: the hook targets the 32-bit original exe; prefer the i686 toolchain
for the DLL. Anti-virus may flag the injector (standard DLL-injection
technique) — add an exclusion if needed.
