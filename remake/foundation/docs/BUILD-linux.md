# Linux (native)

```bash
cd remake/foundation   # all paths below are relative to here
./build.sh deps        # once
./build.sh linux
./build/linux/foundation_demo --frames=180
```

Release artifact: `./scripts/package_linux.sh` builds and stages
`build/package/daybreak-<version>-linux-x86_64.tar.gz` — the executable, the wgpu-native
and SDL3 libraries it needs, the caption fonts, the third-party notices and the `daybreak`
launcher, which finds the player's game folder and boots the title screen. The script
verifies that no game data is inside the artifact and that `ldd` resolves nothing into
`third_party/` or the build tree; the player-facing guide is `package/README-LINUX.md`.

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
those two tests SKIP (they print where they looked); the remaining tests continue to run.
The suite now registers 63 tests (see `RELEASE-CHECKLIST.md` §2); use `ctest`'s own summary
for the current count. `FOUNDATION_CJK_FONT` (resp. `FOUNDATION_LATIN_FONT`) or argv[1]
overrides the search.

Observed (Arch, Mesa 26.2.3, RADV, Wayland session):

```
=== Higurashi Daybreak Kai Fan Remake ===
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

The log above is an earlier triangle/render benchmark. Its variable render
intervals do not describe current gameplay timing: live gameplay and frontend
updates now use the 64 Hz accumulator described in decision D9. Render pacing
remains the swapchain's job (FIFO); rendering may run faster than the display
under a compositor without real vsync.

## Implementation notes

- Backend: wgpu-native → Vulkan.
- Present modes offered: Mailbox, Fifo, Immediate. FIFO is selected.
- Wayland works through `SDL_GetWGPUSurface` (`src/platform/surface.cpp:18`),
  which is also the X11 route — one native path, not two. A headless Xvfb server
  crashed the wgpu-native prebuilt during bring-up; that is a test-environment
  artifact, not a desktop X11 result.


## Fixed-tick verification — 2026-10-04

- All 25 Linux CTest tests pass. `fixed_step_test` pins simulation to 64 Hz
  and compares two- and four-fighter input replays at 30/60/144 Hz rendering,
  including movement, shots, KO/respawn, economy and camera state. Input tests
  cover taps completed between polls and single-consumption during catch-up.
- A native Wayland/RADV stage21 match rendered 180 frames in 1.003 seconds,
  executing 63 logic ticks with the 64 Hz clock; its fractional remainder and
  first setup sample account for the partial final tick. It returned `RESULT: ok`.
  Audio used the dummy device; this is not a hardware listening check.
- The 4,700-frame real-asset frontend smoke recipe in `ROADMAP-PENDING.md`
  reached battle, result voice/report and selection again with `RESULT: ok`.
- The 150-frame stage21 Rika/Takano melee capture at 400×400, with explicit
  spawns `(0,200,0)` / `(-2200,200,-1363)`, was byte-identical to a capture
  saved before the fixed-tick changes. This checks the deliberate legacy
  1/60 capture path, not live 64 Hz timing.
- Linux, Windows cross-build and web builds succeed. These builds do not
  establish cross-platform deterministic rollback; issue #3 still requires
  snapshots, save/restore, state hashes and resimulation evidence.
