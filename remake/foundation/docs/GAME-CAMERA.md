# Game-side arena camera: smoothing + collision clamp

Owned files: `src/render/arena_camera.h` (ADDITIVE helpers only — the existing
one-shot `arenaViewProj` is untouched), new `src/game/fighter_pose.h` +
`src/game/camera_collision.h`. The helpers are live in `src/main.cpp`: the
arena framing block seeds the desired eye via `render::arenaViewProj`, the
iterate path smooths and clamps it per frame, and match mode steps
`gameplay::ArenaCamera` — so arena and match captures move with them (see
Parent-owned integration below).

## Why this shape

`render::arenaViewProj()` answers "eye + viewProj for this target" in one
shot. The reference does two more things every frame that need caller state
(RE section 14: `fcn.006507c0` + `fcn.0042cb50`; history: the earlier
`remake/src/render/arena_camera.h` reference tree is deleted — the ported
rules now live in `src/gameplay/arena_camera.{h,cpp}` and the banked oracle
in `remake/tests/parity-baseline/`):

- spring the eye toward the desired eye at **0.1/frame**
  (`src/gameplay/arena_camera.cpp:75-118` — `m_eye + (desiredEye - m_eye) * 0.1f`, noted
  there as "~10% per frame at 60fps → smooth follow");
- clamp the eye against `collision_camera.x`
  (`src/gameplay/arena_camera.cpp:75-118` — raycast target→desired eye, clamp to
  `hit.dist - 20.0f`; stages without that file run unclamped).

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
none). Read the query segment as aim→desiredEye for the active preset, not
as a fixed +50: the original aims at position + 138
(`src/gameplay/arena_camera.cpp:85`) while the remake oracle and the raw
render default still use +50 (`src/gameplay/arena_camera.h:131-141`,
`src/render/arena_camera.h:65`) — the `+ 50y` wording in the query comment
at `src/game/camera_collision.h:17-18` is parent-owned staleness.
`clampHitDistance(result, segmentLength)` resolves a miss to the
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

## Parent-owned integration (landed)

Integration landed: match mode owns a `gameplay::ArenaCamera` constructed
with the target pool (`src/main.cpp:908`), refreshed from live fighters and
updated per match frame (`src/main.cpp:986-1006`), projecting with its
matrices (`:2060-2061`); the arena capture path composes the physics clamp
with the dt-correct spring before `setCamera` (`src/main.cpp:2027-2053`).
History: the earlier proposal below named the one-shot seam at
`src/main.cpp:501-508` — those lines no longer point at the arena block (now
around `:1365-1378` and `:2027-2053`), so the line reference is retired; read
the arena framing block and the iterate spring instead:

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

// 0.1/frame spring from the reference (src/gameplay/arena_camera.cpp:75-118),
// mapped to the real delta so convergence is frame-rate independent:
glm::vec3 eye = render::arenaSmoothEyeDt(prevEye, clamped, dt, 0.1f);
prevEye = eye;
```

Needs a physics `ICameraCollision` backed by the stage's
`collision_camera.x` mesh before the clamp line does anything; until then
the query returns "no hit" and the path degrades to smoothing only.
