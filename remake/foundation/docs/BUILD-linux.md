# Linux (native)

```bash
./build.sh deps     # once
./build.sh linux
LD_LIBRARY_PATH=$PWD/build/linux ./build/linux/foundation_demo --frames=180
```

Requires SDL3 (the system package; verified with 3.4.16) and a Vulkan-capable
driver. `third_party/webgpu` fetches the prebuilt wgpu-native runtime and
`target_copy_webgpu_binaries` places `libwgpu_native.so` next to the executable,
which is why `LD_LIBRARY_PATH` is only needed when running from elsewhere.

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
- Wayland works through `SDL_GetWGPUSurface` (the X11 path is there too, but the
  wgpu-native prebuilt crashed on a headless Xvfb server during bring-up; that is
  a test-environment artifact, not a desktop X11 result).
