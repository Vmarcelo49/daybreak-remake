# Animation-system work handoff — 2026-10-07

## Update — urgent items 1–3 are now implemented (same day)

The four urgent discoveries below were verified against the original and three of them are
fixed in the working tree, together with the attachment model, the ribbon and new
regressions. Read this block first; the rest of the document is the earlier checkpoint.

- **Item 1 (phase placement) is confirmed and fixed.** `FUN_0043ffc0` reads phase at
  `this+0xadf4` and tick at `this+0xae04`; the earlier reading of `param_1[0x2b7d]`/
  `[0x2b81]` as `0xadf8`/`0xae08` was wrong. 360/370's hold is phase 2 tick 13 and 402's
  launch is tick 13, both now in `kRenaRules`.
- **Item 2 (air tap timing) is fixed**, and the "turns toward target at 15 degrees" half of
  it was **misdiagnosed**: `FUN_0042dc20`/`FUN_0042db10` converge the *bank/lean* field
  `this+0x64` toward an absolute 0-degree target while counter-rotating `this+0x60`. What
  those two fields drive in the model transform is not established, so **no rule was
  invented for them** — they are recorded as open in the audit §11. Landing transitions
  (402→403, 460→469, 370→469) also remain unimplemented; 460 is additionally unreachable
  with Rena 0 because her chargeMax needs 0.9375 s and the leap is shorter.
- **Item 3 (ribbon) is fixed**: the history shift is change-gated and decay stays outside
  that branch. A stationary-tip regression exists.
- **Item 4 (attachments) is implemented against a corrected model.** There is no visibility
  boolean: `FUN_00434a70(slot, propId)` binds an id and `-1` clears it, the executor
  re-binds slot0←prop0 / slot1←prop1 and deactivates both every frame, and only states 400
  (tick>11) and 402 (tick>12) among the moves this port runs hide anything. Items now load
  **all** non-empty attachment props with their own ids and anchors; `FUN_00435000`'s muzzle
  anchor replaces the fixed bone origin; and the renderer has a per-model draw gate
  (`setModelVisibility`) that survives `setEffectInstances` rebuilds.
- **Verification:** Linux/Windows/web builds all succeed; the native suite is **64/64** and
  `animation_data_test` reports **83,398 checks, 0 failures**; a 700-frame headless
  Rena 0 vs Keiichi 0 capture runs with all four shots releasing their bound models.
- **Still true from the original report:** the other 45 combat handlers, the full input
  selector, jump/dash port constants, billboard `0x1000`, projectile reflection `0x100`, the
  remaining combat columns and the extra-`.X` metadata are all still open. Do not describe
  this as a complete fix of the five issues.
- **No commit was made.** The tree is dirty by design; see the review items at the end of
  this document, most of which are now done.

## Read this first

The work is **unfinished and uncommitted**. Continue from the dirty checkout;
do not reset it or reimplement the changes from scratch. The starting commit was
`db6a083` (`Merge branch 'refactor/refactor-render'`). The checkout was clean when
this investigation began. No commits, pushes, issue closures, research edits,
subagents, or persistent goals were created.

The human requested a root-cause fix for **#52, #53, #54, #31 and #26**, then
authorized proceeding. Their latest request was to write this handoff because
they are switching agents. This document is a checkpoint, **not a completion
report**. Do not tell the human that all five issues or all roster attacks are
fixed: substantial compatibility behavior remains.

Read repository `AGENTS.md`, `remake/foundation/README.md`, and decisions D1–D9
in `remake/docs/decisions.md` before continuing. All new game code belongs in
`remake/`; never hand-edit `research/recomp/`. Preserve original `.X` assets.
Every gameplay test/run must bind a **character AND weapon**. Labels use the
weapon slot: `Rena 0` is item 001; `Rena 1` is her second weapon, not item 001.
Use `apply_patch` for edits. Before any commit, read **both** `git diff` and
`git diff --cached`, reviewing every changed file for dead code, temporary
debugging, repetition, and stale/verbose comments. This review is not finished.

## What the human required

1. Read all five issues first, extracting symptoms, repros and characters.
2. Audit each character-file field against the original engine and both parser
   and runtime consumers before edits; investigate widths, offsets, indices,
   lookup tables and ignored events.
3. Inventory hardcoded walk/dash/other supposedly working behavior.
4. Report findings and ambiguities **before implementing**, without guessing.
5. Fix shared parser/data execution, effects, attack transforms and projectiles;
   do not add per-character symptom patches.
6. Replace workarounds and verify walking and forward dash.

Steps 1–4 were performed and reported. New discoveries were also reported before
the related edits. The full preimplementation report is
`remake/foundation/docs/ANIMATION-DATA-AUDIT.md`. Read it, but note that it still
needs a postimplementation ledger and some corrections listed below.

The hypothesis is **partly** confirmed. NN.dat was misread and execution was
flattened, but the original also contains executable character/weapon handlers.
The files do NOT contain every speed, firing row, trail toggle or input selector.
The human authorized recovering those executable rules as declarative behavior
data after the audit. A verified constructor-bound rule table is legitimate;
inventing a rule because it makes a symptom disappear is not.

## Issue observations already gathered

| Issue | Concrete scope |
|---|---|
| #52 | Input-driven shortest-arc facing in all eight directions; holding back must turn away rather than continuously face the opponent; camera follows facing. Includes human and COM. |
| #53 | Rena 0 melee too fast, no forward travel, no slice ribbon; second and third presses must chain; second hit/block enables sideways action camera. |
| #54 | Rena 0 tap / first charge / second charge should throw one nata / one grenade / two natas with matching poses. Comments also mention Rika syringe `bullet/007/50.X` and +X-authored projectile axes. |
| #31 | Rena 0 aerial move 340/set 88 had become presentation set 0 in older code. Current baseline already preserves the selector. A grounded dummy 40 units away can legitimately miss a 3D aerial sphere. |
| #26 | Old Walk→13 / Run→54 / Attack→2 guesses and bare-character attacks are invalid. NN slot+weapon join is mandatory. The issue's newer claim that vtable+0x20 generates hit geometry was disproved. |

All issue bodies **and comments** were read. Re-read if context is needed, but do
not assume issue assertions are correct; several were corrected by original RE.

## Source access and essential evidence

The Ghidra bridge is open on `http://localhost:8089`. No dedicated bridge tool
was found; shell `curl` works:

```bash
curl -s 'http://localhost:8089/decompile_function?address=0x43ffc0&program=DaybreakDX.exe'
curl -s 'http://localhost:8089/read_memory?address=0x6a2434&length=4&program=DaybreakDX.exe'
```

The memory endpoint returns JSON data/hex. Treat decompiler output as evidence,
not perfect C: missing arguments, implicit ECX, floating-point conversions and
assembly omissions have already caused important misleading conclusions.
The offline `research/decompiled` corpus is from a **patched executable**. Its
apparent absences do not establish absence in the original loaded in Ghidra.

Useful local-only investigation files, if still present:

- `/tmp/daybreak-animation-handler.c`: original `FUN_0043ffc0`, Rena 0 executor.
- `/tmp/daybreak-nata-projectile.c`: original `FUN_005f91c0`, item 001 projectile executor.
- `/tmp/fxdis/`: existing Wine/D3DX shader disassembly helper and blobs; its
  `extract.py` uses an old tree path, so do not blindly run it.

Important addresses and verified semantics:

- `FUN_0041e180`: NN.dat loader; `0x41e834–0x41e84a` obtains animation period,
  divides by float at `0x6a2434` (`6f 12 83 3c` = **0.016f**), rounds with x87
  helper. Period is `round(GetPeriod()/0.016)`, not rounded seconds.
- Anchor loader instructions `0x41e67d/69f/6c1/751/773/795` use **FILD**:
  signed integers converted numerically to float, not IEEE bits.
- `FUN_0064e6c0` is skeleton frame lookup via `D3DXFrameFind`.
- Rena 0 ctor `FUN_0064c840` installs vtable `0x6a4e10`: +0x18=`43ffc0`
  execution, +0x1c=`445ee0` selector, +0x20=`423310` **returns false** and
  controls blend permission through `421410`, not generated collision.
- `FUN_004212f0` selects phase-local timed records, retaining the current one
  until the next threshold; first record is selected at bind.
- Live `43ffc0` tail increments elapsed, selects records, then advances phase
  when **period < elapsed** and gate is zero. `FUN_004218c0` separately detects
  last-phase end using **period <= elapsed+1**. Do not replace live logic with
  replay counter clamping in `FUN_0063dad0`.
- `FUN_0041f580`: pose position is elapsed×0.016, plus texture intervals/blend.
- `FUN_00420880`: fighter collision transforms anchors through posed bone.
  `FUN_0063b470/4d0`: victim head/chest spheres vs attack sphere/capsule.
- `FUN_005f6710`: projectile collision uses velocity-aligned local anchors,
  **not the loaded bone**, visual own rotation or billboard flags.
- `FUN_005f75a0`: bullets select records from **first section only**, at TOTAL
  age. `5f60b0` samples controller track 0, not the section tag. `5f8510`
  appends **all** trailer texture intervals to one variant material vector.
- `FUN_005f60b0`: own Yaw/Pitch/Roll, then velocity pitch Z/yaw Y; `0x4000`
  suppresses aim alignment, `0x1000` requests camera billboard; combat column
  19 is render mode (0/1 normal depth alpha lit, 2 additive/no Z write,
  3 unlit opaque, 4 unlit additive).
- `FUN_0042fff0/430120/4303b0`: procedural weapon ribbon, twelve endpoint
  samples, nine spline spans with five subdivisions, anchored triangle fan.
  `FUN_0065d580` really uses t² in its second weight (`0x65d5d6` assembly);
  do not mathematically “correct” this odd literal without contrary evidence.
- `FUN_00435000`: launch at Prop1/Prop2 transformed item muzzle triple when
  selected attachment >=0; bone origin when hidden (-1). `435450` is the
  explicit-position launcher used for the two red natas.

## Data format conclusions

Detailed field tables are in the audit. Short version:

- NN header: tag i32, model name[260], six i32 words. Fourth header word at
  **file 0x114** is item id. Other known words are mode thresholds/durations;
  retain unresolved words. Then serialized move rows indexed by move ID,
  with repeated IDs **last writer wins**.
- Move row: ID, destination priority, cancel threshold, section count. Cancel
  threshold compares with a **destination row priority**, not elapsed frames.
  Sections carry controller animation index, entry count and timed records.
- Shared timed record is **154 bytes**: name[30], frame i32, first three
  signed integer anchors, radius i32, combat[20] i32, state flags i32,
  attack flags i32, shape i32, second three signed integer anchors.
- Name is a skeleton bone, not effect name. Shape 0 sphere, nonzero capsule.
  All combat fields retained. Treat the combat block as raw indexed fields; see
  `remake/foundation/docs/ANIMATION-DATA-AUDIT.md` §11.1 for the corrected resolver
  evidence. Older labels for columns 5–10, 13, and 17/18 in earlier handoff revisions
  are superseded: in particular, do not infer stun/reaction/release-offset semantics from
  current remake aliases or tests. The exact meaning of several columns remains unresolved.
- Trailer: set count; per-set blend metadata, counter gate, texture-event
  count; each interval is **132 bytes**: start/end/repeat and two names[60].
  Active interval `[start,end)`, modulo repeat when positive. These animate
  materials/eyes etc., not generic effect spawns.
- Item slots: model[30], texture[30], nine numeric signed anchors:
  muzzle[0..2], ribbon root[3..5], tip[6..8]. Two magazine blocks follow.
- Item bullet row: magazine index, **live pool capacity**, file type, status.
  Row index is not `type*10+status`, effect id, animation index or volley count.
  Projectile speeds/launch rules come from executable handlers, not these rows.
- Winning asset-source bundle priority is **07/04/00/05/02/06**. Always use
  `AssetSource`, not extracted files that may have different winning copies.
- Across all46 NN files: 5847 winning moves, 5879 trailer rows, 7921 texture
  intervals. **Serialized** 9931 phases/12214 records; **winning after duplicate
  overwrite** 9903 phases/12161 records. Audit currently confuses these totals.
- Eight section tags 122/123 in Ohishi0/1/2 and Hanyu1 (including moves132/232)
  exceed their metadata count122 but are valid in `.X` with124 sets. Original
  missing-metadata initialization needs investigation, not invalid-index guesses.

## Implemented in the current dirty tree

All paths below are under `remake/foundation/` unless specified.

### Shared parsing and execution

- New `src/gameplay/combat_record.h`: one full record decoder, signed anchors,
  raw columns/flags, original tick constant. New `combat_volume.h`: 3D posed
  sphere/capsule collision with strict boundary.
- `character_moves.cpp/.h`: retained header/model/trailer texture fields, full
  phases/records, vector move storage, duplicate overwrite and exact EOF.
  **Renamed** `cancelWindow`/`cancel_window` to `cancelThreshold`/
  `cancel_threshold` in code; old docs may still use the misleading name.
- `weapon_definition.cpp/.h`: full selected bullet variant/sections/trailer,
  exact row identities, pool capacity naming. Scalar aliases retained for legacy
  preview APIs; runtime selects current records.
- `fighter.cpp/.h`: correct original phase/pose clock, current-record combat,
  posed head/chest anchors, full bone-local attack transforms, capsules,
  record state-bit/cancel-priority ordinary chain, data end for supported moves.
- `assets/scene.h` and `main.cpp`: rig scene selects **equipped NN slot**, not
  first usable file. Main loads/binds all bullet rows/models with stable borrowed
  pointers; scene model vector reserved before loading to avoid invalidation.

### Recovered executable behavior data

- New `move_behavior.h`: constructor/vtable-bound walk + forward dash profiles
  for **all46 base combos**. No shared420/900 substitution on this path.
  Dash uses startup/held/release phases, steer/drain/decay and hold lengths.
  Hanyu1 powered form has different speeds/drain; only base form implemented.
- Same header has partial **Rena0** (`43ffc0`) declarative move program:
  300→301→302 ordinary chain, attack displacement/turn, trail intervals,
  charged/ordinary launch rows and action camera. Other45 combat programs are
  **not recovered** and still use compatibility fallbacks.
- New `projectile_behavior.h`: item001 nine verified parameter identities
  0/10/20/30/110/120/150/160/170: own rotation, speeds, gravity, lifetimes,
  homing, wall/secondary exact-row emissions and contact policy.
- Tap row0→`03.X`, grenade row2→`05.X`, red rows11/12→`09.X`.
  Normal ground tap400 tick12; grenade450 tick13; red360/370 phase2 tick2.
  **Some current program timing is WRONG; see urgent next tasks.**
- `projectile.cpp/.h`: first-section total clock, per-instance controller,
  velocity-only collision anchors, current damage/effect record, row capacity,
  deferred secondary allocation (newborns don't update twice), per-victim masks
  and budgets. Tap persists on normal hit and stops on block. Red allows5 hits
  per victim, pauses first5 updates without advancing age/record cursor, resumes
  at speed60, clears contact masks (NOT budgets), subsequent pauses10 updates.
  Secondary row17 emits every2 updates, including before the pause return.
  Stationary secondary params150/160/170 have zero hit allowance.

### Presentation

- New `weapon_trail.h`, Fighter sampling, main procedural models and renderer
  dynamic mesh upload: two-hand textured ribbon production.
- Fixed trail texture-cache base to **`data/item/` with trailing separator**;
  missing separator produced giant white triangles. Textured native capture
  shows violet ribbon after fix, but exact original visual parity is unverified.
- `arena_camera.cpp/.h`, match integration: Rena0 contact chain action camera
  uses `01.X` clip2 Box01/Box02, local transform(1,0,0), elapsed×.016, original
  .2/.3 smoothing and distance snapping. Not every selector/camera mode recovered.
- Renderer: per-projectile palettes/poses (grown/appended safely), texture
  replacements and projectile record render-mode passes. `0x4000` implemented;
  full `0x1000` original billboard is **not** reproduced by current generic
  cylindrical card billboard.

### Tests and evidence tool

- New `tests/combo_fixture.h`: actual winning moves+item+rig+bullet rows and
  stable heap controllers. Existing fighter/melee/bot/damage tests adjusted to
  real combos rather than misleading bare/fixed-chest fixtures.
- New `animation_data_test.cpp` (registered in CMake): hermetic record-width,
  anchor/raw-field/truncation/texture/ribbon checks, all46 parser/rig joins and
  walk/forward-dash phase checks, Rena0 chain/displacement/camera/exact shots,
  bullet model/cursor/gravity/contact/pause behavior.
- `tests/scripts/animation-data.txt`: standalone Rena0 input edges, ordinary
  melee, all three shot tiers and forward dash.
- `tools/audit_move_handlers.py`: read-only evidence auditor, factory→ctor→
  vtable binding with PE immediate speed lookup; `--dash-details` prints decay,
  drain, steer and phase hold. It is NOT a general behavior generator.
- Large `melee_rules_test.cpp` diff removes obsolete first-record/chest-window
  fixtures and replaces them with posed/capsule/timing tests. Review this large
  deletion carefully; do not simply assume all removed coverage was invalid.

## Verification actually performed

- An earlier native full CTest run: **64/64 passed**, 55.25 seconds.
  This was **before** the newest projectile contact-policy and bone-ignore fixes.
- Expanded `animation_data_test`: **83,976 checks, zero failures** after the
  contact-policy, bone-ignore and ribbon-texture checks. Then test fixture
  deduplication and four more hermetic record checks were added; the test count
  will change. Do not treat 83,976 as the final-tree count.
- Linux, Windows and web builds all completed successfully. Most recent build
  sessions81411/87656/89941 were polled and exited0 in the handoff turn.
  They overlapped a final bullet scalar-alias relocation; **rebuild final tree**
  and run full tests after repairs. Windows/web link success is NOT runtime proof.
- Native AMD/Vulkan headless match captures with assets were run. Capture83:
  hp100/92, one hit/one effect; after texture-path fix151 textured/0 untextured
  draws, four effect draws,208 textures (before147/4,204). Capture83 showed a
  violet ribbon and no prior giant white geometry. No live-original parity claim.
- D9: capture pins presentation blend1. It is **not a live interpolation run**.

Local artifacts if still present:
`/tmp/animation-ribbon83.png` (before texture fix),
`/tmp/animation-ribbon-textured83.png` (after), corresponding PPMs;
`/tmp/animation-render-mode600.png` (earlier second-charge capture, not parity).

Reproduction/build commands (repo root):

```bash
./remake/foundation/build.sh linux
./remake/foundation/build.sh windows
./remake/foundation/build.sh web
ctest --test-dir remake/foundation/build/linux --output-on-failure
./remake/foundation/build/linux/animation_data_test
python3 remake/foundation/tools/audit_move_handlers.py Higurashi-Daybreak/DaybreakDX.exe --dash-details
./remake/foundation/build/linux/foundation_demo --headless --no-devices --install=Higurashi-Daybreak --stage=data/stage03 --character=data/rena:0 --enemy=data/keiichi:0 --match --script=remake/foundation/tests/scripts/animation-data.txt --spawn=-1200,200,0 --spawn2=-1200,200,500 --frames=83 --size=800x600 --out=/tmp/animation-handoff83.ppm
```

No known running build/test sessions remain. All work is visible on disk.

## Urgent discoveries NOT YET IMPLEMENTED

> **Superseded by the Update block at the top of this document.** Items 1–4 below are
> implemented in the tree as of the same day; the text is kept as the original evidence
> trail. Read the Update block for what actually landed and what is still open.

1. **Rena0 second-charge hold is in phase2, not phase0.** Current `kRenaRules`
   incorrectly holds360/370 at **phase0 tick13**. Original `43ffc0` cases0x168
   and0x172 place the ten-update return at **phase2 tick13**, after the phase2
   tick2 launches. Both cases turn toward target at15 degrees while phase<2;
   current table omits that turn. Current tests check rows but not exact hold
   placement, so they did not catch this. Add precise phase/clock tests.
2. **Airborne tap402 fires at tick13, not12.** Original case0x192 does row1
   launch at0xd, hides attachments only when elapsed>12, turns through tick12.
   Ground tap400 fires at12, hides attachments at elapsed>11, turns through11.
   Case402 transitions to403 on landing when elapsed>0. Current table puts402
   launch at12 and has no complete landing transition. Air grenade460 correctly
   launches at12 but lands into469 when grounded and vy<0; also not implemented.
3. **Ribbon growth requires moving tip.** Original42fff0 calls430670 to compare
   endpoint samples, shifts history and grows by5 only if different; inactive
   ribbon still decays by2. Current `WeaponTrail::step` shifts/grows every active
   call even with stationary tip. Add a stationary-tip regression. Handle first
   sample deliberately rather than guessing initialization semantics.
4. **Attachment visibility and muzzle selection are not implemented.** Rena0
   executor resets slots0/1 visible each update (`434a70(0,0),(1,1)`), then hides
   both at the above throw thresholds. Main currently draws first nonempty item
   mesh always; launch helper uses bone origin always except explicit red origins.
   `435000` uses item muzzle[0..2] only when selected attachment is visible.
   Consider generic attachment-selection operations in the recovered program,
   actual slot binding, and renderer visibility (including shadow caster pass),
   not zero-scale geometry or a move-id special case in rendering. Renderer has
   no model-visibility API yet; `setModelMatrices` alone is available. `SceneModel`
   stores `attachFrame`, but not item slot identity. Review first-nonempty loading
   and selected slot ownership across multiplayer before changing it.

The last commentary said air tap timing, attachment hiding and stationary ribbon
would be encoded; **no edits implementing them were made**.

## Other remaining work / risks

- Other45 combat handlers still fall back to immediate lowest-type-per-magazine
  shots,20-tick shoot state, first-combat melee preview,8 active/17 recovery
  defaults. Not a complete data-driven fix across the roster. Recover handlers
  from verified ctor/vtable bindings into declarative rules; don't extrapolate
  Rena0 behavior to all weapons. User's issue repros primarily target Rena0, but
  the task also explicitly asks to remove guessed working-animation behavior.
- Full Rena0 input selectors (directional branches/kicks/cancels), attack340
  gravity/contact branches, air370 launch recoil, hyper rows6/8 and EX remain
  incomplete. Jump, side/back/air dash and reload/charge conversions still have
  documented port constants. Header mode words are retained, not fully consumed.
- Rena0 base-air340 handler changes/ground gate need careful interpretation:
  do not add guessed attack gravity to the shared fighter merely to match a clip.
- Full billboard flag0x1000: `FUN_00661a20` returns implicit camera+0x40;
  `FUN_00661770` constructs camera orientation from aim−eye (`42dfd0` subtract
  wrapper), yaw from+X and pitch around(-z,0,x). Current geometry classification
  and cylindrical billboarding are not that original matrix.
- Projectile reflection0x100, accurate block flags/state, all combat column
  response consumers and full damage/gauge semantics remain incomplete.
- Generic FX blending differs from projectile render mode. Read
  `remake/docs/EFFECTS-BLEND.md` if changing this; do not apply projectile column19
  logic to generic effects without evidence. Shader8 MulColor is a uniform, not
  evidence for a vertex-color hack.
- Missing animation metadata for the valid extra `.X` sets needs base constructor
  `FUN_0041d870` initialization investigation (Rena ctor calls it). Current absent
  metadata returns-1 and can prevent generic phase progression.
- `has_combat()` currently requires radius>0 and baseDamage>0; consider non-HP
  effect/gauge attacks only after inspecting original consumers, not guessing.
- Current bullet collision selects a record only when a bullet model is bound;
  no-model legacy tests fall back to old XZ collision. Verify appropriate behavior
  for legitimately model-less shipped bullets rather than retaining a test seam
  as production truth.

## Diff-review cleanup still needed

- Remove extra blank line after bullet `phase.entries[...] = record` in
  `weapon_definition.cpp`. Last edit relocated scalar alias population to the
  **successful parse end**, using winning first-section record, so duplicate
  variants with empty winning first section don't retain stale first aliases.
  Add a duplicate-variant/empty-first-section regression for this exact case.
- Unify repeated move-runtime reset blocks in Fighter init/reset/respawn while
  preserving their different state/magazine semantics.
- Update stale comments: swing clock description should say legacy path;
  source-proven Rena0 selectors vs provisional others; dash12 drain comment
  now applies to varied profiles; `SceneModel` says nine offsets are position+
  rotations/unparsed (they are muzzle/ribbon triples, now parsed); projectile
  instance comments claim all shots opt out of billboard though flags control it.
- Main has stale bullet “level” comments and old claims NN↔weapon join is open.
- Check dt<=0 handling before newly introduced per-update speeds divide by dt
  in Fighter; ProjectilePool already returns early for nonpositive step.
- Shared combo fixture should reset cached fields on reuse if tests reuse it;
  currently typical tests load one combo per fixture.
- Correct audit serialized-vs-winning totals and append implementation status,
  including current limitations and new evidence. The audit is intentionally a
  historical **before fix** report; do not silently rewrite old observations into
  claims that the complete runtime now works.
- `ANIMATION-SETS.md`, `ROADMAP-PENDING.md` contain stale rounded-second timing
  / `cancelWindow` claims. Add accurate current cross-reference/corrections.

Full diff was partially read: CMake, scene/shot helpers, arena camera, match,
character parser, fighter.cpp and weapon parser received substantive review.
Still review complete fighter.h, projectile files, main, renderer, all modified
tests and all new files. `git diff --cached` was empty. **No commit review has
been certified**; perform the full mandatory review again before any commit.

## Suggested continuation order

1. Read this handoff and audit, inspect `git status`/diff, confirm bridge source.
2. Fix the four urgent verified discrepancies, with precise clock/attachment/
   stationary-tip regressions. Report additional discoveries before edits.
3. Finish original-handler recovery to the scope claimed; either remove the
   compatibility substitutes or explicitly document unimplemented coverage.
   Do not describe the shared parser fix as proof all46 attacks/shots are fixed.
4. Run hermetic tests and actual-asset all46 walk/dash regressions, then the full
   native suite; rebuild Windows/web and distinguish build from execution.
5. Capture supported Rena0 combos, then validate live behavior and original
   reference where possible; capture alone is not D9 live verification.
6. Update audit/roadmap, perform complete diff review, remove investigation junk,
   and hand over truthful results. No automatic commit/push is necessary.

## use sub agents to help you with

The human explicitly requested these delegation directives for continuation.
Use sub-agents for bounded, independent research or verification while the main
agent owns integration, user updates, and the final evidence-backed conclusions.
This does not authorize unrelated changes, commits, pushes, or issue closures.

### Research assignments

- **Original handler recovery:** assign one combo/handler or a small related
  family at a time. Have the agent verify constructor→vtable binding, recover
  exact move/phase/tick conditions, launch item rows, attachment selections,
  movement and trail operations. Require function addresses, relevant assembly
  or decompiler excerpts, units, and explicit uncertainties. Start with the
  urgent Rena0 discrepancies, then unrecovered weapon handlers.
- **Independent format audit:** ask an agent to cross-check record widths,
  signed conversions, duplicate overwrite, bullet variant selection and lookup
  namespaces against original loader consumers and winning bundle bytes.
  Retained fields are not proof that runtime consumers are correct.
- **Focused unresolved semantics:** delegate missing animation-metadata
  initialization, projectile billboard matrices, reflection/block flags, or
  combat-column consumers as separate read-only investigations. Ask for evidence
  that distinguishes competing interpretations; do not request a plausible guess.
- **Workaround audit:** have an agent enumerate remaining magic numbers and
  fallback paths with file/function locations, affected combos and whether the
  value is source-proven or a port substitute. Compare against this handoff.

### Testing assignments

- **Precise regression design:** ask an agent to propose or implement isolated
  tests for phase2 red-charge hold, airborne tap tick13, attachment visibility
  and muzzle anchors, stationary-tip ribbons, and duplicate bullet variants.
  Tests must detect the current wrong behavior, not merely assert the new code's
  own constants. Bind actual character+weapon combos for gameplay coverage.
- **Roster verification:** divide all46 legal combos into nonoverlapping groups
  for parser/rig/weapon joins and walk/forward-dash checks. Use the shared fixture
  and winning `AssetSource` bytes; report exact combo labels, observed clocks,
  movement and failures. Keep base and powered forms distinct.
- **Build and runtime checks:** delegate native tests, Windows build/runtime,
  and web build/runtime as separate bounded jobs where resources permit.
  Serialize jobs sharing a build directory or running memory-heavy suites.
  Report commands, checkout state tested, exit codes, test counts, asset-related
  skips and artifacts. A successful link is not successful execution.
- **Visual/live verification:** assign repeatable captures and live checks with
  explicit combo, stage, inputs and frame numbers. Compare with original-engine
  evidence when available. Distinguish rendered appearance, simulation events,
  and D9 live interpolation; do not call a capture a live run or exact parity.
- **Independent diff review:** ask a fresh agent to review changed code/tests
  for stale aliases, clock disagreements, pointer lifetime, multiplayer ownership,
  removed coverage and remaining hardcoded behavior. This supplements, never
  replaces, the main agent's mandatory full diff review before a commit.

### Coordination and acceptance rules

1. Give every agent this handoff, repository instructions, exact scope, expected
   deliverable and read-only versus edit permission. Agents share the checkout:
   preserve existing work and assign disjoint files if edits are permitted.
2. Keep shared parser/runtime integration with the main agent. Research agents
   should normally return findings first; the main agent reports new findings
   to the human before implementation, as the task requires.
3. Use only available concurrency slots and bounded tasks. Do not have multiple
   agents change the same files, rebuild the same target directory, or mutate
   the shared Ghidra program/session concurrently. Read-only queries are preferable.
4. Require each result to separate **observed evidence**, **inference**, and
   **unresolved questions**, with reproducible commands or original addresses.
   Sub-agents must not extrapolate Rena0 rules to other weapons or invent
   per-character symptom fixes.
5. Inspect returned diffs and verify important RE claims independently against
   the original. Re-run relevant tests after integration; a result from an older
   checkout does not certify the final tree.
6. Consolidate findings into the audit and handoff, remove duplicate work and
   temporary instrumentation, and give the human one accurate status report.
   Main-agent responsibility for correctness, limitations and completion remains.
