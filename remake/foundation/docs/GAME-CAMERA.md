# Game-side arena camera: smoothing + collision clamp

Owned files: `src/render/arena_camera.h` (ADDITIVE helpers only — the existing
one-shot `arenaViewProj` is untouched), new `src/game/fighter_pose.h` +
`src/game/camera_collision.h`. `src/main.cpp` untouched: no repo caller uses
the helpers yet, so no existing capture changes.

## Why this shape

`render::arenaViewProj()` answers "eye + viewProj for this target" in one
shot. The reference does two more things every frame that need caller state
(`remake/src/render/arena_camera.h`, RE section 14: `fcn.006507c0` +
`fcn.0042cb50`):

- spring the eye toward the desired eye at **0.1/frame**
  (`arena_camera.cpp:123-136` — `m_eye + (desiredEye - m_eye) * 0.1f`, noted
  there as "~10% per frame at 60fps → smooth follow");
- clamp the eye against `collision_camera.x`
  (`arena_camera.cpp:106-121` — raycast target→desired eye, clamp to
  `hit.dist - 20.0f`; stages without that file run unclamped, `stage.h:57`).

Smoothing needs the previous eye + frame delta (game-loop state); the clamp
needs the physics raycast (gameplay/physics state). Both stay caller-side;
the helpers below are the math without the state. The 0.1 convention is
documented, not baked in: every helper takes its blend/margin explicitly, so
gameplay tuning never edits a shared render header.

## What was added

In `render::` (`src/render/arena_camera.h`, after `arenaViewProj`):

| Helper | Takes | Answers |
|---|---|---|
| `arenaSmoothEye(prev, desired, alpha)` | previous eye, desired eye, per-frame blend in [0,1] | one exponential-lerp step; clamps out-of-range alpha |
| `arenaFrameAlpha(alphaAt60fps, dt, refDt=1/60)` | reference blend (caller passes `0.1f`), real frame delta | delta-correct alpha: `1-(1-a)^(dt/refDt)`; at `dt == refDt` returns the input exactly |
| `arenaSmoothEyeDt(prev, desired, dt, alphaAt60fps)` | (previous eye, desired eye, delta) in one call | the lerp with the mapped alpha — the variable-delta loop entry point |
| `arenaClampEye(aim, desiredEye, hitDist, margin=20)` | aim, desired eye, physics hit distance, wall margin | eye pulled back along the segment on a hit, desired eye back on a miss, aim on a degenerate hit |

In `game::` (`src/game/camera_collision.h`): the query interface physics
implements — `ICameraCollision::queryClamp({aim, desiredEye})` returns
`{hit, hitDist}` against `collision_camera.x` ("no hit" where a stage ships
none). `clampHitDistance(result, segmentLength)` resolves a miss to the
pass-through value so callers never branch on `hit`. Live fighter positions
arrive via `src/game/fighter_pose.h` (`arenaTargetFrom`, see
`docs/GAME-INTERFACES.md`).

## Verification

Host unit test in `/tmp` (headers included straight from the repo, never
committed): convergence to <1% residual after 100 steps at 0.1, `alpha=0`
frozen / `alpha=1` snap, `arenaFrameAlpha(0.1, 1/60) == 0.1` with monotonic
dt scaling, `arenaSmoothEyeDt` agreeing with the manual two-step, clamp
pass-through on a miss / pull-back on a hit / collapse onto aim on a
degenerate hit — `GAME-CAMERA-TEST: ok`.

## Parent-owned integration (proposed, not landed)

Per-frame, in the game loop that owns `prevEye` (replacing the one-shot seam
in the `--camera=arena` block, `src/main.cpp:501-508`):

```cpp
// Game state the foundation does not own:
game::FighterPose  pose = fighter.pose();              // live position/facing
float              dt   = /* real frame delta, s */;

render::ArenaTarget tgt  = game::arenaTargetFrom(pose);
render::ArenaFrame  want = render::arenaViewProj(tgt, params, aspect);

// Collision clamp against collision_camera.x (physics lives game-side):
game::CameraClampResult cr = collision->queryClamp({want.aim, want.eye});
const float seg = glm::length(want.eye - want.aim);
glm::vec3 clamped = render::arenaClampEye(
    want.aim, want.eye, game::clampHitDistance(cr, seg));

// 0.1/frame spring from the reference (arena_camera.cpp:123-136),
// mapped to the real delta so convergence is frame-rate independent:
glm::vec3 eye = render::arenaSmoothEyeDt(prevEye, clamped, dt, 0.1f);
prevEye = eye;
```

Needs a physics `ICameraCollision` backed by the stage's
`collision_camera.x` mesh before the clamp line does anything; until then
the query returns "no hit" and the path degrades to smoothing only.
