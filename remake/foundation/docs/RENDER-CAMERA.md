# R5 game/arena camera path — isolated, framing heuristic preserved

Owned file added: `src/render/arena_camera.h` (pure glm, no WebGPU includes —
render stays the permitted consumer, nothing new for `gpu/` or `platform/`).
The helpers are live in `src/main.cpp`: the arena framing block seeds the
desired eye via `render::arenaViewProj`, and the iterate path smooths and
clamps it per frame (see Parent-owned integration below).

## What was added and why it is shaped this way

The demo frames captures from mesh bounds + env.dat spawn points — a verification
convenience. The game follows fighters with a target-locked arena camera
(`src/gameplay/arena_camera.h`, RE section 14: `fcn.006507c0` +
`fcn.0042cb50`; history: the earlier `remake/src/render/arena_camera.h`
reference tree is deleted — the live citations are the banked oracle
`remake/tests/parity-baseline/` plus the original's prints in
`remake/docs/reference/`). `render::arenaViewProj()` is the foundation side of that path:
desired eye + aim + view-projection from one target, term-by-term mirroring of
`ArenaCamera::compute_desired_eye/update/proj_matrix`:

- eye directly behind the facing (baseline orbit 0): `dx = −sin·dist`,
  `dz = −cos·dist`, `dy = height` — the match camera is
  `ArenaCameraPreset::original()` with height 211 / distance 289
  (`src/gameplay/arena_camera.h:76-82`, pinned by
  `tests/arena_camera_test.cpp:600-608`). The old 800 / 300 pair
  (`0x6a4928` / `0x6a1720`) are not height/distance: they are the near/far
  offsets of a different camera-node projection
  (`src/gameplay/arena_camera.h:102-112`); the render helper defaults at
  `src/render/arena_camera.h:34-43` still carry the remake oracle values and
  are overridden by the preset;
- aim = fighter position + aimHeight — 138 for the original
  (`src/gameplay/arena_camera.cpp:85`,
  `tests/arena_camera_test.cpp:642-643`); the +50 is the remake oracle
  (`src/gameplay/arena_camera.h:131-141`) and the raw render default
  (`src/render/arena_camera.h:65`). Y-up, LH `lookAt` + `perspectiveLH_ZO`,
  NDC passed through unchanged (the renderer's WebGPU convention);
- fovY/near/far are not fitted: fov π/4, near 50, far 150000, read from the
  original camera setup (`src/gameplay/arena_camera.h:102-108`). Near 1 /
  far 100000 is the DX9 remake oracle framing `referenceRemake()`, kept only
  as the behavioural oracle. Match frames project with the preset via
  `gameplay::ArenaCamera::proj_matrix`; the demo framing helper in the main
  file (which maxes far with the scene reach for sky domes) is a separate
  verification convenience.

The one-shot `arenaViewProj` stays, but the spring and clamp math now live
beside it as pure helpers with no baked tuning
(`src/render/arena_camera.h:87-134`): smoothing still needs the previous eye
+ frame delta (game-loop state), and the `collision_camera.x` clamp still
needs the physics query — both caller-side. State — retained eye, target
pool, orbit nudge, blocked/unblocked rule — lives in
`gameplay::ArenaCamera` (`src/gameplay/arena_camera.h`,
`src/gameplay/arena_camera.cpp:75-118`) and is composed per frame in the
main file (`src/main.cpp:2027-2053`).

Env.dat note (checked, not assumed): the helper takes fighter positions, not env
triples, but the spawn mapping was verified — `src/assets/scene.h:269-271`
reads triples as `(x, y, z)` with y ≈ 200 height, and stage21's
`pt0 = (−463, 200, −2200)` lands on the playfield only under that order (it is
also the exact eye the demo's `--camera=player` uses). History: an earlier
revision also cited `remake/src/core/scenes.cpp`'s `(x, z, y)` reading, but
that tree is deleted, so the second half of that comparison is unverifiable
and dropped — flagged for the parent, not resolved here.

## Verification

- Host unit test (`/tmp`, header included straight from the repo): eye/aim match
  hand-computed values for stage21 spawn at facing 0 and π/2; orbit-nudge ≡
  facing rotation; aim projects to NDC center; height/distance overrides honored
  — `ARENA-TEST: ok`.
- In-game frame via the `/tmp`-only shim (`--arena`, env spawn as the target,
  facing 0): stage21 renders eye-level from the spawn — ground plane, guardrail,
  trees, buildings under night fog, 96.55% coverage — the fight-frame look,
  unrecognizable from (and complementary to) the bounds-framed overview. The
  helper is live in the main file (arena framing block plus the iterate
  spring/clamp, and match mode's owned camera — see below), so arena and
  match captures move with it.

## Parent-owned integration (landed)

Landed as `--camera=arena`: env.dat spawn as the locked-on fighter, one-shot
desired eye via `render::arenaViewProj()` in the framing block
(`src/main.cpp:1374-1378`), keeping `auto/player/front/top/bounds` exactly as
they are — and per frame in the iterate path, which clamps the desired eye
against `collision_camera.x` via `render::arenaClampEye` and smooths it with
the dt-correct spring `render::arenaSmoothEyeDt` before `setCamera`
(`src/main.cpp:2027-2053`). Match mode owns a `gameplay::ArenaCamera` fed
from live fighters (`src/main.cpp:908`, `:986-1006`) and projects with its
matrices (`:2060-2061`). Nothing in `render/` changed for this.

