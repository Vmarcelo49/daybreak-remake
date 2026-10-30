# Performance and system requirements

**Measured 2026-10-06 on one machine** — CachyOS, KWin 6.7.5 Wayland, Mesa RADV, AMD Radeon
RX 9070 XT (16 GB), Ryzen host. The numbers below are a **footprint measurement, not a
benchmark**: they say what the port allocates and how much CPU it burns, which is what a
minimum-requirements claim needs. Where a figure is an inference rather than a measurement it
says so.

## What was measured, and how

- **RAM** — `VmRSS` from `/proc/<pid>/status`, sampled every few seconds.
- **GPU memory** — the kernel's per-process DRM accounting, `/proc/<pid>/fdinfo/*`:
  `drm-memory-vram` (dedicated video memory) and `drm-memory-gtt` (GPU-accessible system
  memory). On an integrated GPU everything lands in GTT, which is why both are reported.
- **CPU** — `utime+stime` from `/proc/<pid>/stat` over a fixed window.
- **Runs** — **windowed** (`WAYLAND_DISPLAY` set, no `--headless`), because the headless
  capture path renders offscreen and runs a 30 000-frame match in about two seconds. It is not
  a gameplay measurement and its figures are excluded below.

## The footprint

| state | RAM (RSS) | VRAM | GTT |
|---|---|---|---|
| front end (title) | **84 MB** | 112 MB | 138 MB |
| 1v1 battle | **204 MB** | 97 MB | 138 MB |
| 4-view battle | **261–280 MB** | 102–149 MB | 138 MB |

**CPU: ~32 % of one core** for a 4-view battle at FIFO vsync. The port is not CPU-bound on any
hardware of the last decade; the COM brain's per-tick cost was the one real CPU concern and
issue #30 cut it by 4.5×.

**The 138 MB GTT is a floor, not a peak** — it is present at the title screen, before any
stage is loaded (surface, swapchain and wgpu-native's own allocations). It is why the GPU
total barely moves with resolution: the per-frame render targets are small next to it.

**Worst case measured: ~300 MB of RAM and ~290 MB of GPU memory** (VRAM + GTT), for a
four-view 2v2 battle.

## Minimum requirements (estimate)

The port creates its WebGPU device with **no required features and no required limits**
(`src/gpu/gpu.cpp` — the device descriptor carries only an error callback), and on Linux it
requests the **Vulkan** backend by name (issue #37: with no Vulkan driver it reports "no usable
GPU adapter" instead of panicking inside wgpu-hal's GLES fallback). So the GPU bar is exactly
"a conformant Vulkan 1.0 driver", and nothing above it.

| | minimum | comfortable |
|---|---|---|
| GPU | any Vulkan-capable: NVIDIA **Kepler+** (GTX 600/700), AMD **GCN 1st gen+** (HD 7000), Intel **HD 4000+** (3rd-gen Core) | any discrete GPU of the last decade |
| GPU memory | **256 MB** shared or dedicated | 512 MB+ |
| System RAM | **1 GB** (tight) | 2 GB+ |
| CPU | x86-64 dual-core | anything modern |
| Disk | **~7 GB** for the game install (4.4 GB of `.dat` bundles + 2.6 GB loose), plus ~10 MB for the port | — |
| OS | 64-bit Linux with a Vulkan driver, Wayland or X11 | — |

Vulkan generation floors per [Vulkan hardware
requirements](https://app.studyraid.com/en/read/14981/517278/hardware-requirements-for-vulkan-development)
and [a compatibility
summary](https://totaltech.blog/does-my-graphics-card-support-vulkan); the WebGPU
specification's own [system
requirements](https://github.com/gpuweb/gpuweb/wiki/System-Requirements) page is the reference
for the browser target.

## What this does NOT establish

1. **The GPU figures are from one 16 GB card.** Nothing here ever had to spill, so a 512 MB
   card's behaviour under the same load is an **inference from the allocation sizes**, not a
   measurement. Verifying it honestly means capping VRAM or testing on a small integrated GPU.
2. **The numbers are noisy at the margins.** A 1080p windowed run measured *less* VRAM (102 MB)
   than the default window (149 MB), which cannot be right — either the window size did not
   apply or the samples caught different moments. Treat the table as **order of magnitude**.
3. **The browser build has no GPU floor at all.** Issue #35 ran it on **SwiftShader** (software
   WebGPU), which is the opposite end: it works, and it is slow. Nothing here bounds browser
   performance.
4. **No frame-time or frame-pacing data.** The `--bench` cost path (issue #25) measures that,
   and this document deliberately does not repeat it.

## Reproducing

```bash
# RAM and per-process GPU memory while a windowed battle runs
./build/linux/daybreak --install=Higurashi-Daybreak \
    --screen=battle --local-players=4 --frames=3000 &
PID=$!
for n in /proc/$PID/fdinfo/*; do
    grep -H "drm-memory-vram\|drm-memory-gtt" "$n" 2>/dev/null
done
awk '/VmRSS/' /proc/$PID/status
```

`--local-players=4` is the heaviest configuration the port renders (four views, four fighters,
one stage). Drop it for the 1v1 row and use `--screen=title` for the front-end row.
