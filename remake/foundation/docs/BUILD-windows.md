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

wine-11.18, x86_64-w64-mingw32-g++ 16.2.0, no X display. Wine creates the
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
