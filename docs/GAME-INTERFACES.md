# Game-facing interfaces: fighter pose, effect events, HUD bridge

These interfaces are implemented and integrated, rather than pending proposals.
`src/game/` defines the pose, effect-event, HUD-value, and camera-collision
contracts; `foundation_game` and `foundation_gameplay` are linked into
`daybreak` (`CMakeLists.txt:160-198`). `gameplay::Fighter` implements
`game::IFighterPose` (`src/gameplay/fighter.h:321,361-363`); `src/main.cpp`
drives the camera, effect-event, and HUD paths (`main.cpp:2767-2786,3152-3163,
3526-3547`), and `syntheticHudState()` forwards to the tested game-side
implementation (`main.cpp:5517-5521`). This document describes current
interfaces and provenance, not unimplemented work.

## Layering contract

`src/game/` holds headers + minimal logic, NO gameplay logic itself. It may
depend on glm + std only — no WebGPU, no SDL — with exactly two seam
exceptions, both documented at their use site:

- `game/fighter_pose.h` includes `render/arena_camera.h` for the
  `ArenaTarget` converter (that header is glm-only, so the "no WebGPU" rule
  still holds);
- `game/hud_bridge.h` includes `ui/hud.h` (which reaches `webgpu.h` via
  `sprite.h`). The game side of the bridge — `hud_values.h` — is the
  dependency-light contract; this header is the render-side seam and the only
  `game/` TU needing ui.

## IFighterPose (`src/game/fighter_pose.h`)

`FighterPose` carries position (Y-up game units), facing yaw about Y per
`FUN_00420b30`, animation time, and alive state behind `IFighterPose::pose()`.
`gameplay::Fighter` implements the interface. `arenaTargetFrom(pose)` maps the
live pose onto `render::ArenaTarget` (position + yaw); aim height is owned by
the selected arena-camera preset. The contract preserves the original lock-on
skip-dead behavior (`cycle_target`).

## IEffectEvents (`src/game/effect_events.h`)

The event queue carries spawn/kill events from gameplay into the live effect-card
set. `EffectEvent{Spawn{id, position, asset, ttl}}` / `{Kill{id}}` uses an asset
index, not a path; `EffectEventQueue` preserves FIFO order and transfers pending
events on `drain()`. The app drains it and applies its bounded live-card policy
in `src/main.cpp:3152-3163`; combat and the scripted versus path enqueue effects
there (`main.cpp:3866-3906,4095-4099`). This is integrated gameplay/rendering,
not merely a proposed renderer seam.

## HudState bridge (`src/game/hud_values.h` + `hud_bridge.h`)

`GameHudValues` is the game-units struct gameplay fills (fractions 0..1, hp /
balloon / limit as percentages — the units the HUD composer formats and
bars). It mirrors `ui::HudState` field-for-field except where gameplay must
not name pixels: charge-hold colour becomes `HoldTier{Idle,Yellow,Red}`
(RE provenance: DX9 picks from `ShotTier`) and the hyper aura becomes
a plain `GameRgb` (RE provenance: DX9 passes the mode aura `D3DCOLOR`
straight in). `makeHudState(v)` maps the two, resolving the tier
colours to the surveyed `kHudTier*` values; it reads nothing but its argument,
keeping HUD output a pure function of game state like `HudComposer` assumes.
`syntheticHudValues()` / `syntheticHudState()` define the `--hud-test` values
at the game-side seam. `src/main.cpp:5517-5521` forwards to that implementation;
the host test records the equality contract.

## Verification

Host unit test in `/tmp` (headers included straight from the repo, never
committed): FIFO drain ordering incl. kill-after-spawn and empty second
drain, `arenaTargetFrom` field mapping, `holdColorFor` tier mapping,
`syntheticHudState()` byte-equal to `main.cpp`'s `syntheticHudState()`
field-by-field, plus a custom-values mapping spot check —
`GAME-INTERFACES-TEST: ok`.

## Integrated call shape (abridged)

The active app composes these concerns per frame. Match cameras are built from
live fighters and updated with their camera-collision query
(`src/main.cpp:2767-2786,3526-3532`); effect events are drained into the renderer
(`main.cpp:3152-3180`); per-view HUD state is filled from gameplay and projected
through each view (`main.cpp:3541-3547` and the match HUD pass). The --hud-test
path uses `game::syntheticHudState()` (`main.cpp:5517-5521`). These existing
call sites are the integration reference; the sketch below is conceptual, not a
remaining-work list.
