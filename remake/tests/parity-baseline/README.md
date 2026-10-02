# Phase 0 — DX9 parity baseline (reference bank)

> Banked DX9 reference outputs for the WebGPU replacement
> (`remake/foundation/docs/FULL-REPLACEMENT-PLAN.md` Phase 0:
> "parity is banked before deletion, never after").
> Every later claim of the form "X matches DX9" must cite an artifact
> below, never memory.

Banked 2026-10-02 on `feat/webgpu-groundwork` @ `320a8263`
with `remake/build/daybreak.exe` sha256
`847c2f8405c8216bb2d6d5ba7059e394e302eb607b3004da367388ee6e7948d6`.
33 cases / 36 captures, all exit 0, zero duplicate hashes. **Verdict:
GREEN — DX9 reference banked** (see "Reproducibility" and "Gaps").

## Contents

- `regen.sh` — regenerates everything below. Only existing binary flags;
  no `remake/src` changes (see "Gaps" for what flags cannot reach).
- `manifest.tsv` — name, exact command, exit, frames, file, bytes, sha256.
  Hashes cover exactly the committed `captures/` files (verified:
  `awk -F'\t' 'NR>5{print $7"  "$5}' manifest.tsv | sha256sum -c`).
- `captures/` — 36 committed reference frames, 200x150 PNG8, total
  **530,149 bytes** (~518 KiB, ≤ ~2 MB budget). Framing/HUD-layout
  reference, not pixel-fidelity. No full-res or `-small` strays: the
  directory contains exactly the manifest set, with zero duplicate hashes
  (a `gameplay-yard` case duplicating `fighter-p1-rika` byte-for-byte was
  collapsed during banking — see case table).
- `captures-full/` — NOT committed (gitignored scratch). Full-res 800x600
  PNGs are regenerable: `KEEP_FULL=1 ./regen.sh` (proven 2026-10-02:
  reproduces 800x600 PNG, ~279 KB for title-100).
- `logs/<case>.log` — per-run console output (bundle load, draw counts,
  `DAYBREAK_CAMINFO` eye/fighter probe ~1/sec, `screenshot:`,
  `main loop ended after N frames`). 33 files.
- `logs/dat-<nn>.log` — `daybreak.exe -dat daybreak<nn>.dat -list`
  (00/01/02/04/05/06/07; there is no daybreak03.dat in the install).
  No SDL/D3D init in this mode.
- `logs/asset-*.log` — `-asset-info` index/offset/length + magic for
  `data/rika/01.X`, `data/takano/00.X`, `data/akane/00.X`, `data/rena/01.X`,
  `data/stage21/00.X`, `data/stage21/env.dat`. Log-only, no capture.
- `logs/host-input-devices.txt` — host `/dev/input` + bluetooth state at
  regen start: evidence for why the winebus gamepad override exists.
- `scripts/` — P1 input scripts new to this suite (`lock_p2.txt`,
  `heavy.txt`); combat scripts are symlinked from
  `remake/tests/visual/scripts/` at regen time (nothing copied).

## What each capture is

| capture | command essence | shows |
|---|---|---|
| `title-100.png` | `-scene title -frames 120 -shot 100` | title screen, frame 100 |
| `gameplay-default.png` | `-frames 150 -shot 120` | versus idle, default env.dat spawns |
| `gameplay-school.png` | `-spawn 2800,200,-800` | versus idle, school-building viewpoint |
| `fighter-p1-<rika,takano,akane,rena>.png` | `-p1 N -p2 M -spawn 0,200,0` | each of the 4 reachable fighters as P1, player camera |
| `fighter-p2-<...>.png` | pairs swapped + `-spawn2 0,200,0` + `scripts/lock_p2.txt` | same 4 fighters as **P2, camera switched onto P2** (Guard+HEAVY target switch, frame 41; ~80 frames to converge). Without the switch these would duplicate the p1 set — verified distinct (p2-rika vs p1-rika RMSE 0.156). P2 stands at the default open spawn: P2 at 420,200,-120 parks the camera inside school geometry (probed 2026-10-02, rejected). |
| `fighter-bind.png` | `-frames 10 -shot 2` + `DAYBREAK_MESHINFO=1` | bind pose + vertex/texture survey in the log |
| `camera-alt.png` | `DAYBREAK_CAMH=600 DAYBREAK_CAMD=1400` | proves the camera height/distance override path |
| `stage-part-00..06.png` | `DAYBREAK_ONLY=0N.X` | each of the 7 stage21 parts isolated |
| `hud-dash.png` | `scripts/dash.txt` (double-tap UP), shot 95 | mid-dash + stamina bar |
| `hud-tapshot.png` | `scripts/tapshot.txt`, shot 110 | tap-tier shot + MAIN stock |
| `hud-charge-hold/release.png` | `scripts/charge.txt`, shots 160/185 | red-tier hold + release |
| `hud-hyper-charge.png` | `scripts/hyper_charge.txt` (4 taps, 500f) | Friendship bar filling from damage dealt |
| `hud-hyper-active.png` | `-gauge 1,0` + `scripts/hyper_activate.txt` | Friendship hypermode active (aura, timer, emptied bar) |
| `hud-hyper-oyashiro.png` | `-p1 1 -p2 0 -hyper 1,0 -gauge 1,0` + same script | Oyashiro hypermode active (mode-specific params) |
| `hud-hp-low.png` | `-hp 12,100` | low-HP HUD state |
| `hud-kakera.png` | `-hyper 0,2 -gauge 0,1 -hp 100,3` + `scripts/hyper_lethal.txt` | Kakera death-save instead of KO |
| `hud-ko-a/b/c.png` | `scripts/ko.txt`, 2600f, shots 2290/2330/2450 | KO sequence (25x4dmg): moment, banner, aftermath |
| `action-melee.png` | `scripts/melee.txt` (MELEE tap f80), shot 82 | AttackA swing state, whiffed (P2 out of range) |
| `action-heavy.png` | `scripts/heavy.txt` (HEAVY tap f80), P2 at 120 (< kMeleeRange 160), shot 95 | AttackB HIT: `took 12 damage → HP=88`, stun + knockback + gauge credit (RMSE 0.107 vs melee — genuinely different) |
| `action-jump.png` | `scripts/jump.txt` (JUMP tap f80), shot 92 | airborne + stamina cost |
| `action-guard.png` | `scripts/guard.txt` (GUARD hold f80), shot 100 | blocking + contextual stamina bar |

Fighter model map (`-p1`/`-p2`, clamped 0..3 in `main.cpp`):
0=`data/rika/01.X`, 1=`data/takano/00.X`, 2=`data/akane/00.X`, 3=`data/rena/01.X`.
`-hyper`: 0 Friendship, 1 Oyashiro, 2 Kakera. Frames are the 1-based
main-loop render index everywhere (scripts, `-shot`); logic is fixed 1/60.

## Regen (exact commands)

```bash
./remake/build.sh                         # build first
cd remake/tests/parity-baseline
./regen.sh                                # full set: 33 runs, ~6 min on this host
./regen.sh <substring>                    # subset — REWRITES manifest.tsv with
                                          # only matching rows; always finish
                                          # with a full unfiltered run
KEEP_FULL=1 ./regen.sh                    # also keep 800x600 PNGs in
                                          # captures-full/ (scratch, uncommitted)
PARITY_DISP=:98 ./regen.sh                # X display (default :97).
                                          # Never run two regens on this tree
                                          # concurrently — they share
                                          # captures/logs/manifest.tsv.
```

Prerequisites: `remake/build/daybreak.exe`, Wine, ImageMagick `convert`,
Xvfb (`remake/tools/xvfb/usr/bin/Xvfb` or `$PATH`), game `.dats` via
`$GAME_DIR` (default `<repo>/Higurashi-Daybreak`, gitignored install —
symlinked into a staging dir, never copied).
`WINEDLLOVERRIDES=winebus.sys=d` hides the host gamepad (this host has an
8BitDo whose resting stick exceeds the 8000 deadzone and would steer P1);
regen fails any run where `N gamepad(s), N≥1` reaches SDL
(`GAMEPAD-LEAK`, exit 99). `bluetoothctl` probe is `timeout 5`-guarded:
with no BT daemon it hangs forever (wedged a full regen 2026-10-02).

## Reproducibility (2026-10-02, same binary)

Re-ran subset `title-100`, `fighter-p1-rika` (fighter), `hud-dash` (hud)
after the final full pass; sha256 vs `manifest.tsv`:

- `title-100` MATCH `798b2c92…84fdd`
- `fighter-p1-rika` MATCH `e7777af1…f41063`
- `hud-dash` MATCH `5703c8d5…109f8675`

3/3 MATCH at the byte level. (First attempt mismatched on bytes with
pixels RMSE 0 — root cause: `convert` embeds `date:create/modify` PNG
chunks. Fixed with `-strip` on both convert lines; re-ran full set, then
3/3 MATCH. Lesson recorded in `regen.sh` comment.)

## Bayeux count (must reach zero by Phase 5)

`git grep -l -E "d3d9|D3D9|D3DX|SDL2|SDL_mixer|DirectX|Direct3D|DirectInput|DirectPlay|DirectSound" -- remake/src | grep -v third_party`
→ **35 files** (plan estimated 29 at plan time; all `.cpp`/`.h`, no other
suffixes match):

- `remake/src/assets/asset_manager.cpp`, `.h`
- `remake/src/audio/audio_engine.cpp`, `.h`
- `remake/src/core/scene.h`, `scenes.cpp`, `scenes.h`
- `remake/src/file_parser/x_file_preprocessor.cpp`,
  `x_model_loader.cpp`, `x_model_loader.h`
- `remake/src/gameplay/fighter.cpp`, `fighter.h`,
  `projectile.cpp`, `projectile.h`
- `remake/src/input/input_manager.cpp`, `input_manager.h`
- `remake/src/main.cpp`
- `remake/src/maps/stage.cpp`, `stage.h`
- `remake/src/physics/raycast.cpp`, `raycast.h`
- `remake/src/render/arena_camera.cpp`, `arena_camera.h`,
  `debug_prim.cpp`, `debug_prim.h`, `effect_system.cpp`,
  `effect_system.h`, `hud.cpp`, `hud.h`, `ui_image.cpp`,
  `ui_image.h`, `video_player.cpp`, `video_player.h`,
  `x_model_renderer.cpp`, `x_model_renderer.h`

## Gaps — what existing flags cannot reach (flag + missing)

1. **No `-stage` flag** (`scenes.cpp` hardcodes `data/stage21/00–06.X` +
   `collision_tama.x`). Banked: stage21 only (7 parts via `DAYBREAK_ONLY`).
   Missing: stage01–06, 11–14 (all present in daybreak00.dat), stage
   select, per-stage env.dat spawns/BGM.
2. **`-p1`/`-p2` clamp 0..3, one fixed `.X` per index** (`main.cpp:557`).
   Missing fighters (all have models in daybreak00.dat): keiichi, mion
   (+`01.X` alt), shion, satoko (+`01.X` alt), chie, irie, kasai, ohishi,
   tomitake, akasaka. Missing costumes: `rika_B/01.X`, `rena_B/{00,01}.X`,
   `rena/00.X`. Versus weapon pick unwired (comment only, `scenes.h:155`).
   Max 2 fighters per run (camera supports a pool of 4; no flags for slots
   3–4) — no 2v2 banked.
3. **`-scene` only special-cases `title`** (anything else → gameplay).
   `Scene_Opening`, `Scene_ModeSelect`, `Scene_CharacterSelect`,
   `Scene_Bootstrap` exist but are unreachable via CLI.
4. **No effect/weapon spawn flags.** The 10 effects in `assets/shaders`
   spawn only via combat (projectile muzzle/trails visible in
   tapshot/charge/ko captures); no per-effect isolation possible. No
   weapon models exist in the remake at all.
5. **Animation:** loaded models bind **0 animation sets**
   (`XModel loaded: ... (animations=0, tracks bound=0)` in every log), so
   action captures are state poses, not animation frames. F2 anim-debug is
   physical-keyboard-only (scripts cannot synthesize `SDL_KEYDOWN`) —
   unreachable headless.
6. **Script tokens parsed but unwired:** `TACTICS` (no gameplay effect),
   `LOCK` (camera switch is Guard+AttackB, not the LOCK token), `PAUSE`.
   `LOCK_p2.txt` uses the working Guard+HEAVY combo instead.
7. **`-asset` boot variant not banked** (custom bundle list into the same
   gameplay path — no distinct content).
8. **`-hp`/`-gauge` continuous ranges sampled, not swept** (banked: 12/100,
   100/3, 1/0, 0/1). `DAYBREAK_CAMH/CAMD` sampled once (`camera-alt`).
   `DAYBREAK_MESHINFO` on for `fighter-bind` log only;
   `DAYBREAK_MESH_FLAGS`/`DAYBREAK_ANIM_DEBUG` are loader diagnostics,
   log-only.
9. **`daybreak01.dat` is not in the exe's 6-bundle list**
   (`00:02:04:05:06:07`); its 38-entry inventory is banked in
   `dat-01.log` but its contents never load in-game.
10. **Proxy caveat:** all evidence is Wine + RADV/Xvfb (llvmpipe-class
    GL), not real Windows + vendor drivers. Seek one real-Windows run
    before Phase 5. Host gamepad neutralized (see Regen); any future
    gamepad-visible log invalidates that run's captures.
