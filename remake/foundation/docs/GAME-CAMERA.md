# Game-side arena camera: smoothing + collision clamp

This note records the helper split and verification history. The current match
path is implemented: `gameplay::ArenaCamera` owns follow state, projection, and
action animation; `game::physics::CameraCollision` provides the stage query. The
standalone `--camera=arena` viewer composes `render::arenaViewProj` with the
render-layer clamp/spring helpers. Live ownership and paths are summarized
below; the old DX9 `remake/src/` implementation was removed in Phase 5.

## Current status and ownership

Live match views follow their own fighter's position, but their normal orbit
orientation follows the bearing to that fighter's combat target (including an
ally hold). Without a selected living target, the hostile fallback supplies the
bearing. The body's movement turn (`FUN_00421780` / `FUN_0042db10`) does not rotate
the camera: holding Back turns the character away while the view remains oriented
toward the opponent. The asset-backed `controller_scene_lifetime_test` checks
this separation with Rena 0, including the resulting live camera direction.
Historical standalone match captures retain their banked actor-yaw orbit.
This corrects [issue #52](https://github.com/Vmarcelo49/daybreak-decomp/issues/52)
acceptance criterion 5: a movement turn must not swing the live camera with the
body. The target bearing remains the view and control reference.

LockSwitch selects the next enemy on the press edge. Selecting an ally requires
16 continuously held logic ticks, including the press tick: 250 ms at 64 Hz.
This duration is a port rule; the recovered 180-tick ally dwell is separate from
the input gesture. Releasing resets the gesture clock, so tapping again after
an ally selection stays on an enemy until a new full hold. The product-path
`lock_switch_camera_test` checks the threshold and taps lasting 1, 3, 6 and 15 ticks.

This note records the original helper split; it is implemented in the current
match path, not a future seam. `gameplay::ArenaCamera` owns the retained eye,
follow/retarget state, projection, and camera action animation
(`src/gameplay/arena_camera.{h,cpp}`); its `CollisionQuery` uses the live
`game::physics::CameraCollision` implementation in `src/physics/raycast.h`.
`src/main.cpp:2767-2786,3526-3532` supplies targets and updates each match view.
The separate `render::arenaViewProj` + dt-correct clamp/spring path is used by
the standalone `--camera=arena` viewer (`main.cpp:6219-6245`). The earlier
DX9 `remake/src/` implementation was deleted in Phase 5; RE provenance and the
banked comparison records remain in the docs and parity baseline.

`render::arenaViewProj()` answers “eye + viewProj for this target” in one
shot. The reference does two more things every frame that need caller state
(RE section 14: `fcn.006507c0` + `fcn.0042cb50`):

- spring the eye toward the desired eye at **0.1/frame**
  (`src/gameplay/arena_camera.cpp:75-118` — `m_eye + (desiredEye - m_eye) * 0.1f`, noted
  there as "~10% per frame at 60fps → smooth follow");
- clamp the eye against `collision_camera.x`
  (`src/gameplay/arena_camera.cpp:75-118` — raycast target→desired eye, clamp to
  `hit.dist - 20.0f`; stages without that file run unclamped).

For the standalone viewer, smoothing uses retained eye + frame delta in the
app loop and the clamp calls the physics query; the helpers below remain pure
math without this state. The match camera has its own ported per-call follow
rule and collision query. The 0.1 convention is documented, not baked into the
render helper.

## What was added

In `render::` (`src/render/arena_camera.h`, after `arenaViewProj`):

| Helper | Takes | Answers |
|---|---|---|
| `arenaSmoothEye(prev, desired, alpha)` | previous eye, desired eye, per-frame blend in [0,1] | one exponential-lerp step; clamps out-of-range alpha |
| `arenaFrameAlpha(alphaAt60fps, dt, refDt=1/60)` | reference blend (caller passes `0.1f`), real frame delta | delta-correct alpha: `1-(1-a)^(dt/refDt)`; at `dt == refDt` returns the input exactly |
| `arenaSmoothEyeDt(prev, desired, dt, alphaAt60fps)` | (previous eye, desired eye, delta) in one call | the lerp with the mapped alpha — the variable-delta loop entry point |
| `arenaClampEye(aim, desiredEye, hitDist, margin=20)` | aim, desired eye, physics hit distance, wall margin | eye pulled back along the segment on a hit, desired eye back on a miss, aim on a degenerate hit |

The current query interface is `game::ICameraCollision::queryClamp({aim,
desiredEye})`; the foundation physics implementation is
`game::physics::CameraCollision` (`src/physics/raycast.h`). The active original
preset aims at position + 138 (`src/gameplay/arena_camera.cpp:95`); the old
render helper's raw default still uses +50, while the match preset overrides it.
A miss resolves to the full segment length and passes through unclamped.

## Verification

Host unit test in `/tmp` (headers included straight from the repo, never
committed): convergence to <1% residual after 100 steps at 0.1, `alpha=0`
frozen / `alpha=1` snap, `arenaFrameAlpha(0.1, 1/60) == 0.1` with monotonic
dt scaling, `arenaSmoothEyeDt` agreeing with the manual two-step, clamp
pass-through on a miss / pull-back on a hit / collapse onto aim on a
degenerate hit — `GAME-CAMERA-TEST: ok`.

## Current integration references

- Match views build a target pool from the live fighter roster and initialize
  `gameplay::ArenaCamera` (`src/main.cpp:2767-2786`). Per tick, live fighter
  pose refresh and camera update happen at `main.cpp:3464-3532`; the camera query
  uses `game::physics::CameraCollision`.
- The stage loader sets that query's mesh from the `Camera` collision role
  (`src/main.cpp:4222-4244`). Empty/missing geometry reports no hit.
- The standalone `--camera=arena` path uses `render::arenaViewProj` then applies
  the optional camera clamp and dt-correct smoothing in `main.cpp:6219-6245`.

The original proposal sketched a generic `FighterPose`/clamp composition before
the match camera class and caller paths landed. That sample is omitted here to
avoid presenting a second, non-authoritative implementation; see `GAME-INTERFACES.md`
for the current contract overview.
