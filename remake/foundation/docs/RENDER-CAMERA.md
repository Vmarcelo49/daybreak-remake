# R5 game/arena camera path — isolated, framing heuristic preserved

Owned file added: `src/render/arena_camera.h` (pure glm, no WebGPU includes —
render stays the permitted consumer, nothing new for `gpu/` or `platform/`).
`src/main.cpp` untouched: the framing heuristic still drives every in-repo
capture.

## What was added and why it is shaped this way

The demo frames captures from mesh bounds + env.dat spawn points — a verification
convenience. The game follows fighters with a target-locked arena camera
(`remake/src/render/arena_camera.h`, RE section 14: `fcn.006507c0` +
`fcn.0042cb50`). `render::arenaViewProj()` is the foundation side of that path:
desired eye + aim + view-projection from one target, term-by-term mirroring of
`ArenaCamera::compute_desired_eye/update/proj_matrix`:

- eye 45° (π/4, `0x6aac70`) to the side of the facing: `dx = −sin·dist`,
  `dz = −cos·dist`, `dy = height` (defaults 800 / 300, `0x6a4928` / `0x6a1720`);
- aim = fighter position + 50y; Y-up, LH `lookAt` + `perspectiveLH_ZO`, NDC
  passed through unchanged (the renderer's WebGPU convention);
- FOV π/4 kept **marked as a guess** (the reference header says so too);
  near 1 / far 100000 (`0x461c4000`); caller maxes far with the scene reach for
  sky domes, exactly as the framing path does.

Deliberately one-shot (no spring lerp, no retained eye, no collision raycast):
smoothing needs the previous eye + frame delta (game-loop state), and the
`collision_camera.x` clamp needs the physics query — both caller-side. The
helper answers "eye + viewProj for this target" and nothing else.

Env.dat note (checked, not assumed): the helper takes fighter positions, not env
triples, but the spawn mapping was verified — `scene.h` reads triples as
`(x, y, z)` with y ≈ 200 height, and stage21's `pt0 = (−463, 200, −2200)` lands on
the playfield only under that order (it is also the exact eye the demo's
`--camera=player` uses). `remake/src/core/scenes.cpp` describes the same triples
as `(x, z, y)`; if both readings are live, one of them is compensating
elsewhere — flagged for the parent, not resolved here.

## Verification

- Host unit test (`/tmp`, header included straight from the repo): eye/aim match
  hand-computed values for stage21 spawn at facing 0 and π/2; orbit-nudge ≡
  facing rotation; aim projects to NDC center; height/distance overrides honored
  — `ARENA-TEST: ok`.
- In-game frame via the `/tmp`-only shim (`--arena`, env spawn as the target,
  facing 0): stage21 renders eye-level from the spawn — ground plane, guardrail,
  trees, buildings under night fog, 96.55% coverage — the fight-frame look,
  unrecognizable from (and complementary to) the bounds-framed overview. No repo
  caller uses the helper yet, so no existing capture changes.

## Parent-owned integration (landed)

Landed as `--camera=arena`: env.dat spawn as the locked-on fighter, one-shot
desired eye via `render::arenaViewProj()` in the framing block, keeping
`auto/player/front/top/bounds` exactly as they are. Collision clamp against
`collision_camera.x` and the 0.1/frame eye spring stay game-side per the
reference. Nothing in `render/` changed for this — the seam was the one
`setCamera` call, now fed by the arena eye/aim instead.

