# Windows cross-build (MinGW-w64) and Wine verification

## Portable ZIP release

```sh
./scripts/package_windows.sh
```

The ZIP is written under `build/package/`. Extract its contents
directly into the original game folder, beside `DaybreakDX.exe`, and double-click
`DaybreakRemake.exe`. The ZIP includes SDL3, wgpu-native, both caption fonts and
license notices, with no scripts or original game data. The port's distinct name
avoids replacing an existing `daybreak.exe`.

The Windows executable uses its own directory for automatic game discovery,
independently of the working directory. Explicit `--install=` and
`DAYBREAK_INSTALL` still override it. Missing required bundles or fonts identify
the exact path, and interactive failures use a native error dialog. Settings use
the Windows application-data directory when no XDG override is supplied. The
release uses the Windows GUI subsystem, without an extra console window.

### Package verification — 2026-10-09

Wine 11.19 / RADV Vulkan, using a separately extracted package in a directory
containing spaces and Japanese characters:

- Direct executable startup from an unrelated working directory opened the title
  without `--install=`: `RESULT: ok`.
- The developer-only `windows_startup_smoke` target drove the real no-argument
  `SDL_AppInit`/frame/quit path twice, including opening playback and settings
  save/load/replace: both runs reported `errors=0`. It is not included in the ZIP.
- A 12,000-frame scripted frontend capture completed rounds on stage04 and
  stage06, returned through results/selection, and entered stage15: `RESULT: ok`.
  The local fixture changed the first timer adjustment to select 60 s from the
  corrected default of zero; the committed gate-script timing issue remains #63.
- Missing Japanese fallback font and missing `daybreak04.dat` both returned
  exit 1 with the exact missing filename. Headless checks suppressed the dialog.
- PE import checks found only the two bundled DLLs and Windows system libraries;
  the ZIP was checked for scripts and game-data files. Linux: 64/64 tests passed.

This establishes package startup and captured rematches under Wine. Actual
Windows hardware, physical controllers and a live Windows rematch still need
the recipient's test. The older issue #57 fault below is historical evidence,
not a result reproduced by these package checks.

### Packaging commit checks — 2026-10-12

Linux and Windows builds and the web cross-build passed. The ZIP packager's DLL
and file-exclusion checks passed. The rebuilt `windows_startup_smoke` ran twice
under Wine from a folder with spaces and Japanese characters, launched from an
unrelated working directory: opening/title and settings save/reload completed
with `errors=0`, exit 0. This smoke now passes only `--no-audio`; install and screen
selection remain automatic. The focused bundle/font/settings tests passed 3/3;
the full rebuilt Linux CTest suite passed 69/69 (205.52 s), with no failures or skips.
A separate title capture reached `RESULT: ok`, but its PPM output could not be
written to a Unicode path; Unicode screenshot export remains unverified.
Actual Windows hardware and live rematch verification remain pending.

```sh
# run from the repository root
./build.sh deps      # once
./build.sh windows   # configure + build + stage runtime DLLs
wine build/windows/daybreak.exe --frames=120
```

`--frames=N` counts N frames and exits; without it the demo runs until the
window is closed.

## What ends up in `build/windows/`

| file | comes from |
|---|---|
| `daybreak.exe` | the build, with the GCC runtime linked **statically** |
| `SDL3.dll` | copied by `build.sh windows` from the MinGW SDL3 payload |
| `wgpu_native.dll` | copied by `target_copy_webgpu_binaries()` |

Both DLLs have to sit next to the `.exe` — Wine resolves them from the
executable's own directory, so the demo runs from any working directory.

The GCC runtime is linked statically on purpose (`-static`,
`cmake/toolchains/mingw-w64-x86_64.cmake`). Dynamically it would drag in
`libgcc_s_seh-1.dll`, `libstdc++-6.dll` **and** `libwinpthread-1.dll`, none of
which are part of the SDL3/wgpu third-party payload, and Wine fails the load
with `status c0000135` if any of them is missing.

## Verified on this machine

wine-11.19, x86_64-w64-mingw32-g++ 16.2.0, no X display. Wine creates the
window through its own driver and wgpu-native picks Vulkan, so the demo gets the
real GPU:

```
$ wine build/windows/daybreak.exe --frames=120
=== Higurashi Daybreak Kai Fan Remake ===
video driver : windows
adapter      : AMD Radeon RX 9070 XT (RADV GFX1201) [Vulkan]
surface      : 960x540, 7 format(s), 3 present mode(s), fifo=yes
present mode : Fifo(vsync)

-- frame timing (variable delta, no fixed step) --
frames      : 120 in 0.656 s
delta avg   : 5.359 ms (186.6 fps)
delta min   : 0.606 ms
delta max   : 6.030 ms
RESULT: ok
```

That is the triangle: it proves the surface and the adapter request, not that the
game runs. **With the game install (issue #35)**, wine-11.19, run inside an
isolated headless KWin session:

```sh
wine build/windows/daybreak.exe --install=Z:/<abs>/Higurashi-Daybreak
```

reaches the title screen through the opening movie (issue #40's decoder, on this
target for the first time):

```
[install] game folder: Z:/.../Higurashi-Daybreak (from --install=)
[menu] scene: opening (tick 0)
movie        : data/movie/op.mpg (MPEG-1 system multiplex, 640x480, 29.97 fps, 22.79 s, MP2 44100 Hz stereo)
movie        : ended after 684 frames decoded/684 presented (22.789 s), audio 22.857 s
[menu] scene: title (tick 1485)
```

and with the release gate's own script

```sh
wine build/windows/daybreak.exe --install=Z:/<abs>/Higurashi-Daybreak \
  --screen=title --local-players=2 \
  --script=Z:/<abs>/tests/scripts/frontend-1v1-rematch.txt
```

the whole front end runs: `.dat` bundles (`assets: 6/6`), stage and characters,
VS, countdown, a live split-screen battle, a round decided on the time-up rule and
the result screen. `RELEASE-CHECKLIST.md` §5.2 has the full transcript, the canvas
captures and the honest ladder (compiled/launched/title/battle/played).

That older run found **a fault in round 2 of a rematch** — `wine: Unhandled page
fault on read access to ... at address 00000001400B3810`, inside
`gameplay::CharacterMoves::find(int) const` — while the identical Linux recipe
completes `RESULT: ok` (issue #57). Before the `cnv.h` fix in issue #35 the run
did not get that far at all: `std::filesystem::u8path` threw on a raw Shift-JIS
texture name and terminated the process.

With an X display present the adapter instead comes from Mesa's software path
(`llvmpipe [OpenGL]`, 5 formats, 2 present modes) and still ends in
`RESULT: ok` — useful as a fallback, since it needs no GPU:

```sh
remake/tools/xvfb/usr/bin/Xvfb :99 -screen 0 1280x800x24 &
DISPLAY=:99 wine build/windows/daybreak.exe --frames=120
```

The Xvfb fallback needs a local X server toolchain at `remake/tools/xvfb`
(local-only, not fetched by `build.sh deps`; `xvfb-run` must not wrap
agent-browser's own Xvfb) and `build/wine_frame.png` is a local capture, not a
committed reference — re-take it with the `DISPLAY=:99 wine ...` command above
rather than expecting it in the checkout; a re-taken capture shows the rotating
vertex-coloured triangle, i.e. the WebGPU pipeline really drawing.
