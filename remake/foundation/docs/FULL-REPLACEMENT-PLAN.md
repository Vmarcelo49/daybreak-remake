# Full replacement plan: drop DX9, WebGPU only

Status: **executing**. Phase 0 (parity banking + preconditions) passed
2026-10-02; Phase 1 (foundation-complete) passed 2026-10-02. Phases 2–5 not
started. Nothing below deletes or rewrites anything
until its phase gate passes. This plan exists because "replace DX9" is a
point of no return: after Phase 5 there is no DX9 build to compare against,
so every proof must be banked *before* the cutover.

## 0. Objective and definition of done

Replace the DirectX 9 + SDL2 stack in `remake/` with the SDL3 + WebGPU
foundation, then delete the DX9 code and retire the prototype folders.
Done means, on `main`:

- `remake/` builds for Linux, Windows and web with **no D3D9, D3DX, SDL2,
  or SDL_mixer references** outside `third_party/` (zero `grep` hits).
- A playable versus match runs on all three targets.
- `webgpu-mvp/` and `webgpu-spike/` are deleted.
- `remake/docs/decisions.md` D2, `AGENTS.md` rule 2, and the READMEs describe
  the WebGPU stack as current fact, not migration.
- This plan's per-phase gates all passed, in order.

Out of scope for the replacement itself (tracked separately, not blocking
the cutover): macOS execution (never tested by us), netplay (D6, design
first), story-mode video (stubbed by decision).

## 1. Rules of the migration

1. **Parity is banked before deletion, never after.** Phase 0 archives the
   DX9 reference outputs. Any claim of the form "X matches" must cite an
   archived artifact, never memory.
2. **No flag days inside a phase.** Gameplay code compiles throughout: the
   D3DXVECTOR3→glm swap (Phase 2a) is what unlocks compiling without D3D
   headers, and it lands before any render call is touched.
3. **One agent owns `remake/src` at a time.** Another agent is active there
   now (their `x_model_loader.cpp` is dirty). No cutover edit starts until
   the tree is coordinated: their work merged or paused, and the handoff
   recorded here.
4. **Prototypes die last.** `webgpu-mvp/` and `webgpu-spike/` are deleted in
   Phase 5 only, after the foundation demonstrably covers everything they
   proved.
5. **Toolchain payloads follow the code.** `remake/tools/{d3dx9,SDL2-2.30.10,
   SDL2_mixer-2.8.0}` die with the last DX9 reference. `mingw`, `xvfb`,
   `wine-prefix`, `python` stay (still used). `hook-tracer`, `asset-tools`,
   `debs` are audited before deciding.

## 2. Preconditions (all required before Phase 1)

- [x] `feat/webgpu-groundwork` reviewed and merged to `main`, or the
      replacement continues on the branch with `main` frozen for `remake/`.
      **Continues on the branch** (2026-10-02): `main` is at `37ed31d` and is
      an ancestor of the branch head; no `main` commit touches `remake/`.
- [x] Coordination with the other `remake/src` agent: clean tree or explicit
      handoff. Their `x_model_loader.cpp` work must land first or move.
      **Handoff recorded 2026-10-02**: that file stays uncommitted and dirty
      (`DAYBREAK_MESH_FLAGS` / `DAYBREAK_ANIM_DEBUG` probes gated behind env
      vars) and is untouched by this work — no commit here stages it. Standing
      split until they land or confirm a pause: **they own
      `remake/src/file_parser/`; this migration does not edit `remake/src` at
      all** (Phase 1–2 land in `remake/foundation/` first). Any edit needed on
      their side stops the phase and is reported, never worked around.
- [x] Tag `main` as `pre-webgpu-cutover` — the rollback point. Deletion
      without this tag is not permitted by this plan. Created 2026-10-02 on
      `37ed31d` (annotated; pushed with the branch).
- [x] The versus vignette (`--versus`) runs green on Linux and Wine from a
      clean checkout, so Phase 1 starts from a verified base. Verified
      2026-10-02: both targets `RESULT: ok`, PPMs byte-identical (480,015 B),
      coverage 150,160/160,000 px (93.85%), draws 167, and the strict pair
      (P1 = P2 = `akane/00.X`, same asset bytes both targets) is bit-for-bit
      equal including camera smoothing, animation, HUD and audio counts.

## 3. Phase 0 — parity banking (before any deletion)

Bank the DX9 reference outputs that all later "matches" claims cite:

- [x] Full capture suite from the DX9 build: every stage at player camera,
      every fighter/costume (front + bind pose + one animation frame),
      weapons, effects, HUD states. Command lines + PPMs archived under
      `remake/tests/parity-baseline/` (new, committed — small sizes only;
      large sets stay as scripts that regenerate them). **Banked 2026-10-02 in
      `cd82bd6`**: 33 cases / 36 captures (200x150 PNG8, 530,149 B total), all
      exit 0, zero duplicate hashes, `regen.sh` regenerates the set. A full
      replay reproduced **36/36 sha256 identical**. The plan's item list is
      wider than what the DX9 binary's flags can reach — see the deviation
      note below.
- [x] Console-output logs for the same runs (draw counts, texture
      resolution, timing summaries). 47 logs committed (`logs/`), plus
      `-dat -list` inventories and `-asset-info` probes.
- [x] `git grep -E "d3d9|D3D9|D3DX|SDL2|SDL_mixer|DirectX|Direct3D|DirectInput|DirectPlay|DirectSound" remake/src --include='*.cpp' --include='*.h' | grep -v third_party`
      recorded as the Bayeux count: **29 files** at plan time. Phase 5 ends
      at zero. **Re-measured 2026-10-02: 35 files** (list in the baseline
      README) — the plan-time number was an undercount, not a regression. The
      Phase 5 target is unchanged: zero.

**Deviation (recorded, not silently dropped):** "every stage", "every
costume", weapons and effect isolation are *not* bankable from the current
DX9 binary — it has no `-stage` flag (stage21 is hardcoded), `-p1`/`-p2`
clamp to four indices with one fixed `.X` each, there are no weapon models in
the remake at all, loaded models bind 0 animation sets, and effects spawn only
from combat. Producing those captures would mean adding flags to DX9 code that
Phase 5 deletes, while §2 forbids editing `remake/src` under the standing
handoff. The baseline therefore banks what the shipped flags reach and lists
the remaining 10 gaps explicitly (flag + what is missing) in
`remake/tests/parity-baseline/README.md`. Consequence to keep in mind: for an
asset class with no banked DX9 capture (other stages, costumes, weapons),
"matches the original" is not a claim this baseline can support.

## 4. Phase 1 — foundation-complete (parallelizable)

Independent pieces, subagent-suitable, each with its own verification:

- [x] **Bundle support.** Port `dat_bundle` + `dat_crypto` (XOR, tiny) +
      `asset_manager` resolution; foundation reads `daybreakXX.dat` from an
      install, no extracted tree needed. Verify: same bytes as `extract_dat.py`
      output, then byte-identical captures from bundle vs tree. **Landed
      `03eb045` + `edcb53c`**: 12,345/12,345 entries match the oracle, 0
      structural mismatches. The second half of the verification does not hold
      as written — the tree is not the same data (see the finding below) — so it
      was replaced by the check that matters: an install-only run (nothing but
      `daybreak0*.dat` reachable) renders the full vignette green on Linux and
      Wine with byte-identical captures, 12 models / 54 meshes / 55,095
      vertices, 166 draws, coverage 150,052 px (93.78%).
- [x] **CPU raycast.** Replace `D3DXIntersect` (brute force first, BVH if
      profiles demand it). Verify against scripted rays; unblocks the arena
      camera clamp hook. **Landed `03eb045`, wired `edcb53c`**: Möller–Trumbore
      with the reference's two walkers and traversal order; 72 analytic checks,
      an independent float64 cross-check (0 hit/miss disagreements), real-asset
      invariants, and the clamp wired into the arena eye with an A/B switch.
      No D3DXIntersect parity is claimed and none is possible: the DX9 binary
      has no raycast probe (`main.cpp` includes `raycast.h`, never calls it).
      Measured 5.5 µs/ray on the largest shipped camera mesh (628 triangles) —
      brute force stays, a BVH only pays around 32k triangles (201 µs/ray).
- [x] **Debug prims.** Line drawing port (~100 lines). Verify visually once.
      **Landed `03eb045`**: the file the plan meant is a cube pass for un-RE'd
      VFX with no line primitive in it, so this was built (not ported) with the
      semantics that file does have; 111 geometry checks, wired as
      `--debug-prims`, verified visually and byte-identical Linux vs Wine
      (1,080,015 B). The cube capability it does have is *not* replaced by this
      and must be covered before Phase 5 deletes `debug_prim.*` (see §8).
- [x] **CJK decision.** ASCII bitmap cannot do HUD Japanese. Options: system
      fonts per platform, embedded CJK bitmap, SDF atlas. Decision first, code
      after. **Decided 2026-10-02 (user): in-process TrueType rasterization from
      one fetched OFL font**, ASCII bitmap as fallback; evidence and rejected
      options in `docs/CJK-TEXT.md`. Implementation is Phase 3.

Gate: foundation reads installs, raycast + prims verified, CJK path chosen.
**PASSED 2026-10-02.**

**Finding that changes an assumption above (asset source):** "byte-identical
captures from bundle vs tree" cannot hold, because the extracted tree is not
the same data as the install. 983 names ship in more than one bundle, 445
groups differ in bytes, and `extract_dat.py` writes the *last* copy into the
tree while the game reads the *first* (`FUN_00653540` order). The foundation
now reads bundles first, matching the game; the observable difference is real
and was measured (`data/rika/01.X`: 9,675,158 B from bundles — the DX9 side's
own number, `parity-baseline/logs/asset-*.log` index 6017 — versus 9,893,738 B
from the tree). Consequence for the record: the foundation captures verified
before this change rendered different rika/takano/akane/rena bytes than the DX9
reference they were being compared against, so any *cross-implementation*
comparison must be re-run bundle-first (the Linux-vs-Wine pairs remain valid,
since both sides read the same source). A second consequence, fixed here rather
than worked around: probing both spellings of a case-insensitive name loaded
one file twice, which is the "+1 model / +909 vertices on Wine" divergence
Phase 0 recorded; `AssetSource::resolve()` now returns a single path.

## 5. Phase 2 — gameplay port (supervised, mostly sequential)

The ~2.5k lines of game truth, translated file by file. Order matters:

- [ ] **2a. Math-type swap.** `D3DXVECTOR3` → `glm::vec3` (already a
      foundation dep) across `gameplay/`, `physics/`, `maps/`, `core/`
      headers. Purely mechanical, compiles without D3D headers afterwards.
      Verify: full rebuild + unit-level spot checks (positions, matrices).
- [ ] **2b. Fighter + projectile.** Port `fighter.cpp`/`projectile.cpp`
      logic onto foundation interfaces (`IFighterPose`, effect queue, HUD
      bridge, input actions, audio cues). Update/render split: `render()`
      methods lose their `IDirect3DDevice9*` and become data for the
      foundation renderer. Verify: scripted-playback matches (positions,
      HP, ammo over fixed input scripts, Linux vs Wine identical).
- [ ] **2c. Gameplay scene.** `scenes.cpp` gameplay path: match flow, live
      HUD values, effect spawning from combat, camera targets from live
      fighters. The versus vignette graduates here — same CLI shape, real
      state instead of scripted timeline.
- [ ] **2d. Stage/maps, manager, bootstrap, main.** Remaining flow + boot.
      `main.cpp` game boot replaces `d3d_init` with foundation init; dat
      tools and capture modes re-homed.
- [ ] **2e. Input/audio wiring.** Tables and backends exist; wire live
      mapping, BGM selection per scene, SFX triggers from combat events.

Gate: playable versus match (two fighters, HP, KO, stage, BGM) on Linux
and Wine, captures + console numbers recorded. This gate *is* D2's spirit.

## 6. Phase 3 — fidelity (RE + assets as needed)

- [ ] Effect techniques completed (trails via `FUN_00633ca0`, per-effect
      factors, billboard yaw vs original).
- [ ] CJK implementation from the Phase 1 decision.
- [ ] Video if D6 scope reaches it (pl_mpeg vendor + uploader; still
      stubbed until then).
- [ ] Menus/title/opening scenes after gameplay (D6 order: versus first).

Gate: D2's letter — a complete in-game frame matching the banked DX9
reference. Until this passes, DX9 stays buildable (unchanged from today).

## 7. Phase 4 — netplay (design first, D6)

Greenfield deterministic lockstep over UDP. No code before a design doc
covering: input delay vs rollback, float-determinism discipline across
MSVC/MinGW/Emscripten toolchains, desync detection, and what "LAN-first"
excludes. Separate plan, separate review — listed here only so it is not
forgotten.

## 8. Phase 5 — cutover (the actual drop)

Only after Phases 0–3 gates (4 if in scope) have passed, in this order:

1. Flip the default: foundation build becomes *the* build (`remake/build.sh`
   targets it; DX9 build moves to `remake/build-dx9.sh` temporarily or is
   removed outright — decide at the time, default to remove).
2. Delete, in one reviewed commit: `remake/src/render/{x_model_renderer,
   hud,ui_image,video_player,effect_system,debug_prim,arena_camera}
   .{h,cpp}` as replaced (arena_camera math already lives in foundation),
   `remake/src/file_parser/*` as replaced, `remake/tools/{d3dx9,
   SDL2-2.30.10,SDL2_mixer-2.8.0}`, `webgpu-mvp/`, `webgpu-spike/`.
   Gameplay files (`fighter`, `projectile`, `scenes`, …) are *ported*, not
   deleted — they move adapted, never vanish. **Precondition for deleting
   `debug_prim.{h,cpp}`**: Phase 1 replaced the *plan's* idea of it (lines),
   not what it is — a placeholder unlit-cube pass for un-RE'd VFX. Confirm the
   effect path covers shots/sparks/aura before removing it, and if it does not,
   that coverage is a Phase 3 deliverable rather than a silent loss of
   function.
3. Update in the same commit: D2 to past tense ("DX9 removed <date>, WebGPU
   only"), AGENTS.md rule 2 + halves table, both READMEs, CI (retire DX9
   jobs; foundation matrix stays version-gated).
4. Verify: clean-checkout build of all three targets, versus match green,
   `grep` count from Phase 0 at **zero**.

Rollback: `pre-webgpu-cutover` tag + this branch, which is kept until the
release after the cutover.

## 9. Risk register

- **Active second agent in `remake/src`.** Highest collision risk in the
  whole plan. Mitigation: §2 precondition + file-level ownership while
  porting (they own loader/parser, we own render/gameplay or vice versa —
  agree in writing first).
- **CJK text.** Only item with no proven approach yet. Mitigation: decide
  in Phase 1, before HUD fidelity depends on it.
- **Netplay determinism across three toolchains.** Mitigation: design doc
  with a determinism test harness before any netcode.
- **Wine as verification proxy.** All Windows evidence is Wine + RADV, not
  real Windows + vendor drivers. Mitigation: note it on every claim (as
  today); seek one real-Windows run before Phase 5.
- **Scope creep into story mode.** D6 says versus first; title/opening/
  story stay minimal until Phase 3 at the earliest.

## 10. What this plan deliberately does not do

- No macOS execution (standing rule: never tested by us).
- No gameplay invented beyond the remake's RE-grounded logic; the
  foundation stays a renderer + platform, the game stays the game.
- No big-bang rewrite: every phase leaves a building, running tree.
