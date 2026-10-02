# Linux (native)

```bash
cd remake/foundation   # all paths below are relative to here
./build.sh deps        # once
./build.sh linux
./build/linux/foundation_demo --frames=180
```

Requires SDL3 (the system package; verified with 3.4.16) and a Vulkan-capable
driver. `scripts/fetch_deps.sh` (via `build.sh deps`) fetches the pinned
WebGPU-distribution sources into `third_party/webgpu`, and that CMake project
downloads the prebuilt wgpu-native runtime at configure time. The binary carries
a build-tree RUNPATH to its configure-time wgpu directory (confirm with
`readelf -d`), so in place it just runs; `target_copy_webgpu_binaries`
(`CMakeLists.txt:278`) still stages a `libwgpu_native.so` beside the executable
for anything that moves the binary away from that directory — point
`LD_LIBRARY_PATH` at the executable's own directory only in that case.

Native checks need two local-only faces in `third_party/fonts/` (gitignored;
fetched by `remake/scripts/fetch_deps.sh`, the host-toolchain-and-fonts script —
not by `build.sh deps`, which only fetches third-party sources): `NotoSansCJKjp-Regular.otf`, the CJK face
`text_test` looks for (`tests/text_test.cpp:406`), and
`LiberationSans-Bold.ttf`, the Latin face `hud_text_test` needs. Without them
those two tests SKIP (they print where they looked); everything else in the
13-test suite runs. `FOUNDATION_CJK_FONT` (resp. `FOUNDATION_LATIN_FONT`) or
argv[1] overrides the search.

Observed (Arch, Mesa 26.2.3, RADV, Wayland session):

```
=== daybreak foundation ===
video driver : wayland
adapter      : AMD Radeon RX 9070 XT (RADV GFX1201) [Vulkan]
surface      : 960x540, 7 format(s), 3 present mode(s), fifo=yes
present mode : Fifo(vsync)

-- frame timing (variable delta, no fixed step) --
frames      : 180 in 0.983 s
delta avg   : 5.428 ms (184.2 fps)
delta min   : 0.653 ms
delta max   : 9.498 ms
RESULT: ok
```

The spread between `delta min` and `delta max` is the point: the frame loop takes
real elapsed time and nothing imposes a fixed step. Frame *pacing* is the
swapchain's job (FIFO), not the loop's — note that under a compositor with no real
vsync the loop can run faster than the display, which is expected here and is not
a frame-rate claim.

## Implementation notes

- Backend: wgpu-native → Vulkan.
- Present modes offered: Mailbox, Fifo, Immediate. FIFO is selected.
- Wayland works through `SDL_GetWGPUSurface` (`src/platform/surface.cpp:18`),
  which is also the X11 route — one native path, not two. A headless Xvfb server
  crashed the wgpu-native prebuilt during bring-up; that is a test-environment
  artifact, not a desktop X11 result.
