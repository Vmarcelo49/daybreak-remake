# Windows cross-build (MinGW-w64) and Wine verification

```sh
cd remake/foundation
./build.sh deps      # once
./build.sh windows   # configure + build + stage runtime DLLs
wine build/windows/foundation_demo.exe --frames=120
```

`--frames=N` counts N frames and exits; without it the demo runs until the
window is closed.

## What ends up in `build/windows/`

| file | comes from |
|---|---|
| `foundation_demo.exe` | the build, with the GCC runtime linked **statically** |
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
$ wine build/windows/foundation_demo.exe --frames=120
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
wine build/windows/foundation_demo.exe --install=Z:/<abs>/Higurashi-Daybreak --no-devices
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
wine build/windows/foundation_demo.exe --install=Z:/<abs>/Higurashi-Daybreak \
  --screen=title --local-players=2 --no-devices \
  --script=Z:/<abs>/remake/foundation/tests/scripts/frontend-1v1-rematch.txt
```

the whole front end runs: `.dat` bundles (`assets: 6/6`), stage and characters,
VS, countdown, a live split-screen battle, a round decided on the time-up rule and
the result screen. `RELEASE-CHECKLIST.md` §5.2 has the full transcript, the canvas
captures and the honest ladder (compiled/launched/title/battle/played).

What does not work yet: **round 2 of a rematch faults** — `wine: Unhandled page
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
DISPLAY=:99 wine build/windows/foundation_demo.exe --frames=120
```

The Xvfb fallback needs a local X server toolchain at `remake/tools/xvfb`
(local-only, not fetched by `build.sh deps`; `xvfb-run` must not wrap
agent-browser's own Xvfb) and `build/wine_frame.png` is a local capture, not a
committed reference — re-take it with the `DISPLAY=:99 wine ...` command above
rather than expecting it in the checkout; a re-taken capture shows the rotating
vertex-coloured triangle, i.e. the WebGPU pipeline really drawing.
