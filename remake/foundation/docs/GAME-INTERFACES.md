# Game-facing interfaces: fighter pose, effect events, HUD bridge

Owned files: new `src/game/fighter_pose.h`, `src/game/effect_events.h`,
`src/game/hud_values.h`, `src/game/hud_bridge.h`,
`src/game/camera_collision.h` (query side documented in
`docs/GAME-CAMERA.md`). `game/` ships as `foundation_game` (check TU
`src/game/game_check.cpp`) plus `foundation_gameplay` (`src/gameplay/*`),
both linked into `foundation_demo` — no longer header-only or
host-test-only. The landed seam is `src/main.cpp:1833-1838`, which
forwards `syntheticHudState()` to `game::syntheticHudState()`.

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

What the game must supply so the camera (later: character rendering) follows
live fighters instead of env.dat spawn points: `FighterPose`
(position Y-up game units, facing yaw about Y per `FUN_00420b30`, animation
time in seconds, alive flag) behind `IFighterPose::pose()`. Mirrors the DX9
side's `Fighter::position()/facing_yaw()` + animation state
(`src/gameplay/fighter.h:199` `state_to_anim_name`, `:412-413`
`position()`/`facing_yaw()`, `FUN_00420b30` yaw convention) and the
lock-on skip-dead rule (`cycle_target`). `arenaTargetFrom(pose)` maps a pose
onto `render::ArenaTarget` (position + yaw; the +50y aim raise stays inside
`arenaViewProj`).

## IEffectEvents (`src/game/effect_events.h`)

Spawn/kill event queue the renderer drains. Combat decides (RE provenance:
`PendingShot` armed in `Fighter`, spawned via `m_shots.spawn/spawn_spark`
— the ported truth is `src/game/effect_events.h`: asset-as-index, FIFO
drain, no cap); this header only carries
the decision: `EffectEvent{Spawn{id, position, asset, ttl}}` /
`{Kill{id}}`, where `asset` indexes the renderer's effect-asset table, never
a path. `EffectEventQueue` is a dumb FIFO — `pushSpawn/pushKill`, one
`drain()` per frame that moves events out and clears (a second drain in the
same frame is empty by construction; same-frame kill-after-spawn order is
preserved). No cap: the per-frame drain bounds it, and a cap would drop hits
silently.

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
`syntheticHudValues()` / `syntheticHudState()` restate the `--hud-test`
numbers from `src/main.cpp:1833-1838` as the bridge's trivial implementation —
the parent can replace the hand-built state with that one-liner with zero
capture-pixel change (proven by the host test below).

## Verification

Host unit test in `/tmp` (headers included straight from the repo, never
committed): FIFO drain ordering incl. kill-after-spawn and empty second
drain, `arenaTargetFrom` field mapping, `holdColorFor` tier mapping,
`syntheticHudState()` byte-equal to `main.cpp`'s `syntheticHudState()`
field-by-field, plus a custom-values mapping spot check —
`GAME-INTERFACES-TEST: ok`.

## Parent-owned integration (landed)

```cpp
// Per frame, after the simulation steps:
// 1. camera target from the live locked-on fighter:
game::FighterPose pose = fighters[lockedOn].pose();
render::ArenaTarget tgt = game::arenaTargetFrom(pose);
// 2. effect cards: gameplay pushed spawns/kills during update...
for (const game::EffectEvent& e : effects.drain()) renderer.applyEffect(e);
// 3. HUD: gameplay fills plain values, the bridge maps them...
game::GameHudValues hv;
hv.hp = fighters[0].hp(); /* ... balloon, MAIN/CHARGE, hyper, stamina, KO ... */
ui::HudState st = game::makeHudState(hv);
hud.compose(batch, st, ui::computeHudLayout(w, h));
// --hud-test becomes: ui::HudState st = game::syntheticHudState();
```

Landed as: `src/main.cpp:1833-1838` forwards `syntheticHudState()` to
`game::syntheticHudState()`, and the versus/match path follows the
per-frame camera/effect/HUD sketch above.

Needs: a gameplay `IFighterPose` over the real `Fighter`, a renderer-side
effect-card set fed by `drain()`, and a `foundation_game` CMake target
— the first seam pieces are in (`foundation_game` from
`src/game/game_check.cpp`, `foundation_gameplay` from `src/gameplay/*`,
both linked into `foundation_demo`).
