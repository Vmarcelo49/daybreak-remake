# Full replacement plan: drop DX9, WebGPU only

Status: **executed — cutover complete 2026-10-02.** Phase 0 (parity banking
+ preconditions) passed 2026-10-02; Phase 1 (foundation-complete) passed
2026-10-02; Phase 2 (gameplay port) passed 2026-10-02; Phase 3 (fidelity)
landed against the corrected target (§6a), with its remaining items tracked
rather than blocking; Phase 4 (netplay) is out of scope for the cutover (D6,
design first); **Phase 5 was executed 2026-10-02 and the DX9 tree is deleted**
(§8). This plan existed because "replace DX9" is a point of no return: every
proof was banked *before* the cutover, and the rollback point is the
`pre-webgpu-cutover` tag (`37ed31d`).

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

**Status 2026-10-02:** the zero-reference and deletion bullets hold; the
versus match is green on Linux and Wine; web and macOS execution are exactly
as recorded in §8.5 and `ROADMAP-PENDING.md` — not claimed beyond that.

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

- [x] **2a. Math-type swap.** `D3DXVECTOR3` → `glm::vec3` (already a
      foundation dep) across `gameplay/`, `physics/`, `maps/`, `core/`
      headers. Purely mechanical, compiles without D3D headers afterwards.
      Verify: full rebuild + unit-level spot checks (positions, matrices).
      **Done inside the port, not by editing `remake/src`**: the ported gameplay
      is glm-only and includes no D3D header, which is the item's actual goal,
      while `remake/src` stays untouched and buildable as the A/B reference
      (§1.2, and the Phase 3 gate requires DX9 to stay unchanged). The
      mechanical equivalence is pinned by the port's own tests — all 25
      `FighterConstants`, every enum value and every tuning row compared against
      the source, plus matrix checks (yaw 90° maps +Z to +X).
- [x] **2b. Fighter + projectile.** Port `fighter.cpp`/`projectile.cpp`
      logic onto foundation interfaces (`IFighterPose`, effect queue, HUD
      bridge, input actions, audio cues). Update/render split: `render()`
      methods lose their `IDirect3DDevice9*` and become data for the
      foundation renderer. Verify: scripted-playback matches (positions,
      HP, ammo over fixed input scripts, Linux vs Wine identical).
      **Landed `d88c55a`**: `Fighter` implements `game::IFighterPose` and
      exposes `modelMatrix()`; `render()` is deleted in both classes and its
      per-cube data (size/colour/fade) is exposed instead. Verified against the
      DX9 build itself: six scripted cases, 59 samples × 2 fighters, worst
      position delta **0 units**, animation states equal — including the
      2600-frame KO case (44 samples) and the dash displacement at frame 121.
      The KO console lines match byte for byte (modulo Wine's CRLF). Host tests:
      395 checks for the port, 5/5 under ctest.
- [x] **2c. Gameplay scene.** `scenes.cpp` gameplay path: match flow, live
      HUD values, effect spawning from combat, camera targets from live
      fighters. The versus vignette graduates here — same CLI shape, real
      state instead of scripted timeline. **Landed `d4612c0` + `d88c55a`**:
      `gameplay::Match` reproduces the reference's per-frame order (including
      its asymmetry), `MatchEconomy` the balloon/LIMIT/KO clock, and
      `fillHudValues` the HUD maths; the demo's `--match` drives them with a
      scripted or live P1 and a scripted-or-dummy P2, camera from the locked
      fighter's live pose with the reference's Guard+AttackB target switch, and
      combat hits push effect events. `--versus` stays as the deterministic
      capture vignette (it is banked evidence), which is why it was not deleted.
- [x] **2d. Stage/maps, manager, bootstrap, main.** Remaining flow + boot.
      `main.cpp` game boot replaces `d3d_init` with foundation init; dat
      tools and capture modes re-homed. **Partially done**: the match boot,
      stage/spawn/collision-channel loading, capture modes and the `--headless`
      path are in the foundation's `main.cpp`; the scene *manager* and the
      front-end/bootstrap flow are not ported, because D6 puts menus after
      versus and Phase 3 owns them. The dat tools stay in `remake/tools/`
      (Phase 5 audit).
- [x] **2e. Input/audio wiring.** Tables and backends exist; wire live
      mapping, BGM selection per scene, SFX triggers from combat events.
      **Mostly done**: P1 is live device input with the DX9 script override
      (`--script`), P2 a script (`--script2`) or the reference's dummy, and the
      match plays the reference's BGM (`data/bgm/01.ogg` + `.sfl`, 153,600
      frames pushed over 150 frames). **Combat SFX triggers are not wired** —
      the DX9 gameplay scene plays none (only BGM), so this is a fidelity item
      for Phase 3 against the original, not a parity gap.

Gate: playable versus match (two fighters, HP, KO, stage, BGM) on Linux
and Wine, captures + console numbers recorded. This gate *is* D2's spirit.
**PASSED 2026-10-02.** Evidence: the six-case trace parity above; Linux and
Wine headless runs of the same match producing **byte-identical** captures
(480,015 B each, coverage 156,633/160,000 = 97.90%, luminance 0.025..1.000)
with live HUD, animated fighters and the ported economy; and the console
numbers recorded in `d88c55a` (150 frames, hp1=100 hp2=100, balloon 0%/0%,
LIMIT 100%, bgm pushed 153,600 frames, 0 wraps).

**Open from Phase 2, carried forward (not blockers):**
1. **Guard has no input-driven exit** in the DX9 remake's state machine — a
   one-way state that drains stamina until damage or reset, while the same
   file's header documents "Idle/Walk → Guard → Idle (block key held)". The
   port keeps parity and its test pins the quirk, so a fix will show up as a
   test failure; fixing it is a product decision (it changes behaviour vs the
   DX9 reference and vs the banked `action-guard` capture, which holds the
   button and so is unaffected).
2. **Unreachable constants**: `kJumpSpeed` (380) is overwritten by the 40 u/s
   fly rise on the same frame, and `kFlyMaxAlt` (420) is never reached (peak
   49.25). Kakera's HP drain rounds to 0 at 60 Hz.
3. **Animation lookup differs from the DX9 remake on purpose**: the port
   matches set names case-insensitively (the original's `lstrcmpiA`), while
   the DX9 loader compares with `==`. The DX9 build also binds 0 sets for
   shipped characters, so its fighters never animate; the foundation's do.
   This is the one expected divergence in a trace A/B (it does not affect the
   state names the traces compare).
4. **Side 1's HUD block** has no destination in `GameHudValues`/`ui::HudState`
   (the DX9 layout draws only `fighters[0]` outside the two balloon corners).
5. **The match camera clamps** (Phase 1's `collision_camera` clamp) where the
   DX9 remake's is unclamped — deliberate, and the reason `--no-camera-clamp`
   exists for A/B.

## 6. Phase 3 — fidelity (RE + assets as needed)

**Landed so far (`275212d`, `47875f0`, `de4057e`):** camera parity with the DX9
reference (trace-exact, including frame 1), solid cubes for shots/sparks/auras,
`--size=WxH` so a foundation frame can be 800x600 like a banked one,
`tests/compare_frames.py` as the gate's instrument, the CJK text layer (500
checks) with a regenerated full-CP932 table, and fixed-function lighting parity
(RMSE 0.324 → 0.085 on three cases, exposure matched to ±0.003).

## 6a. Fidelity target, corrected 2026-10-03 (owner)

**The visual target is the original game's screens, not the DX9 remake's
frames.** `remake/docs/reference/*.webp` holds 23 prints of the running
original — one per screen: `title-menu` (the shrine main menu), `team-select`,
`char-select-rena`, `weapon-select-rena`, `stage-select-*`,
`hypermode-select`, `controller-select`/`-setup`, `option-screen`,
`vs-intro`, `battle-hud`, `battle-stamina`, `ko-moment`, `ready-confirm`,
`result-*`, `netplay-*`, `soft-keyboard`, `opening-frame-01`, `ammo-bar`.
Those are the specification for what the game looks like. The DX9 remake is
**not**: it is itself unfinished (its fighters never animate, its VFX are
untextured cube stand-ins, its HUD is a text-only sketch of the original's
art, and it carries a debug marker), so matching it pixel-for-pixel means
matching a stand-in and calling it done.

The two oracles therefore have different jobs, and claims must name which one
they used:

| oracle | what it can still settle |
|---|---|
| DX9 remake frames (`tests/visual/out/`, `tests/parity-baseline/`) | behaviour: positions, states, economy, trace equality (`compare_match_traces.py`). Still exact, still valuable. |
| the 23 prints (`docs/reference/`) | appearance: camera framing, HUD layout and art, VFX, stage look, and every screen the foundation does not have yet |

Consequences already visible, measured 2026-10-03 against `battle-hud.webp`:

* **Framing**: the print's player character is ~3x larger and stands with her
  feet at the HUD line; the foundation's is mid-frame and small. The arena
  camera currently ported is the *remake's* (height 300, distance 800), which
  is not the original's framing — the remake is closer to the original here
  than the foundation is. This supersedes the "camera parity" claim: it is
  parity with the remake, not with the game.
* **HUD**: the print's HUD is art — a fan-shaped OYASHIRO gauge, a boxed 適当
  label, shaped bars/panels, a "com" bar, an alert balloon, targeting
  brackets, a counter. The remake draws plain Arial text and flat bars, which
  is what the foundation reproduced. The gap is art and layout, not metrics.
* **Brightness**: the print's mean luminance is 0.621 against the
  foundation's 0.492 (and the DX9 remake's 0.490) — the original is brighter
  than both.
* RMSE against the print is 0.298 versus 0.064 against the remake's frame.
  The 0.064 was a real result against the wrong target.
* **Wrong stage variant** (owner's catch, verified 2026-10-03). The school
  stage ships as a scene with day and night variants, and every comparison so
  far used `stage21` — the DX9 remake hardcodes it
  (`remake/src/core/scenes.cpp:481-489`) — which is the **night** variant
  (env.dat fog `rgb(0.06 0.08 0.20)`, the darkest of all 13 stages at max
  luminance 0.659). `stage-select-school.webp` names the stage the prints
  show: **雛見沢分校 校庭 (schoolyard) — 昼 (day)**. Searching the install for
  the CP932 bytes of 校庭 locates the scene in `stage01`, `stage02`,
  `stage11`, `stage12` and `stage21`, which the fog colours then sort into
  day (`01`: 0.30/0.39/0.47, `02`: 0.28/0.34/0.36), warm/sunset (`12`:
  0.35/0.20/0.18) and night (`21`). So the brightness gap in the row above is
  mostly the variant, not the lighting: comparisons against the prints must
  use `stage01`/`stage02` (whichever the print's wall/ground textures identify
  — a framing-independent question, being settled by the camera track). The
  DX9 frames stay valid for *behaviour* on whatever stage they used.
* The stage-select print also specs a whole front-end screen: `STAGE SELECT`
  with the stage name + time of day, a thumbnail, and `BATTLE SETTING` rows
  (制限時間, 体力値, ゲージ増加量, 青チーム風船サイズ, 赤チーム風船サイズ) over
  `戦闘開始` / `戻る` — the level of detail the front-end tracks can work
  from.

**Spawn question, reframed 2026-10-03 (an earlier note here called it a loader bug; that was
wrong).** The foundation's `env.dat` read matches the original's own reader —
`FUN_004011f0` takes four header ints at 0x14-0x20 and then four triples at 0x24, stride
12, in stored order, which is exactly `readEnv` in `src/assets/scene.h`. There is no DX9
loader to compare against either: the DX9 side hardcoded its spawns (see
`pre-webgpu-cutover:remake/src/core/scenes.cpp:527-535`), which is *why* the trace had to
pass `--spawn2` explicitly. So the open question is not the parse but the *consumer*: which
of the four stored points a versus match uses, and in what order. Next step is to read the
consumer of `param_1[0x11..0x1c]` (offsets 0x44-0x70) rather than the parser. See
`docs/ROADMAP-PENDING.md` item A1.

**Where the gate frame stands (2026-10-03, against the DX9 remake).** Against the three banked DX9
frames at 800x600, after camera parity, lighting parity, the animation-set fix
and the HUD text metrics: overall RMSE 0.063988 / 0.063431 / 0.056068 on
tapshot f110 / dash f95 / school f110, with luminance means within 0.002-0.004
of the reference. What is left, in measured order:

1. **Stage/sky detail** — RMSE ~0.061 over 74% of the pixels. This was
   attributed here to the reference filtering LINEAR **with mips** while the
   foundation had none. **Corrected 2026-10-03: that attribution was wrong.**
   The *original* does filter with mips — sampler 0 sets MAG/MIN/MIP all
   D3DTEXF_LINEAR (`FUN_00654f00.c:45-47`) and the mips are shipped art
   (`X.cnv` + `X_1.cnv` + `X_2.cnv`, only for the stage dirs) — but the **DX9
   remake does not**: it creates textures with MipLevels=1
   (`remake/src/render/ui_image.cpp:61`) and sets only MIN/MAG
   (`remake/src/core/scenes.cpp:760-761`), leaving D3D9's default
   MIPFILTER=NONE. So mips genuinely fix the foundation against the *prints*,
   and they *widen* any residual measured against the DX9 frames. The three
   banked gate numbers above therefore need re-banking before they are quoted
   again, and a DX9-frame comparison is no longer the right instrument for
   this item — the prints are.
   Mips are implemented (stage-role textures only, matching the shipped-art
   coverage; box filter; level 0 byte-identical by construction), measured
   0.255956 -> 0.254041 against `battle-hud.webp`, with every masked scene band
   improving and the minified-band gradient ratio falling from 1.25-1.78x the
   print's to 0.52-0.68x.
2. **Text rasterizer weight** — the HUD's residual is now purely that
   `stb_truetype` has no hinter, so a stem GDI snaps to one full column spreads
   over two half-covered ones. Positional error is gone: every HUD label's best
   integer shift is (0,0).
3. **Open items from the tracks, recorded rather than smuggled in:**
   * The KO sting is misplaced in the port: the reference centres it at
     `rect.top + 39` (DrawText DT_CENTER|DT_VCENTER in a 100 px box) while
     `computeHudLayout` puts `koY` at the band top, 39 px high. It needs the KO
     capture case, which is why it was not changed with the HUD metrics.
   * The corner marker the reference draws at (4,4) is reproduced as the
     remake's unlabelled yellow "0" (`scenes.cpp:829`). The *original's*
     battle-hud reference has a yellow marker in that corner, so the real fix is
     to draw the original's art there instead of a digit.
   * The reference's rasterizer places glyphs 1 px left of the pen — that is
     Wine's builtin `d3dx9_43`, the DLL the visual suite ships (the Microsoft
     redist is 1 px right and 1 px lower). The constant flips to 0 if the frames
     are ever re-banked against the redist.
   * Historical state at the DX9 cutover: `state_to_anim_name`'s "idle"/"walk"
     labels did not match the `.X` sets named "Anim-N". The current foundation
     resolves supported states from each fighter's `NN.dat`; the remaining
     selector limits and corrected voice-key finding are tracked in
     `ANIMATION-SETS.md` and `remake/docs/placeholders.md` §5.

**A verification invariant this phase had to be corrected about, recorded
2026-10-03 because it invalidates a general claim Phase 2 made.** Linux-native
and Wine captures are byte-identical only when no animation is evaluated:

| content | Linux vs Wine |
|---|---|
| bare stage, no characters | **byte-identical** |
| one character, bind pose (no animation bound) | **byte-identical** |
| any frame with an animation evaluated | differs, from **1 byte at frame 1** to 8,124 bytes at frame 110 (tapshot, 800x600) |

The divergence is in the pose path, not the renderer: `slerp`/`normalize`/trig
in the animation evaluator land 1 ULP apart between MinGW and glibc, and a
vertex that moves by 1 ULP pushes a few pixels across an 8-bit bucket boundary
(bright shading makes more pixels cross, which is why the lighting fix widened
a pre-existing gap rather than creating one). Consequences, stated plainly:

* Phase 2's byte-identical match pairs (dash frame 150, KO frame 2600) remain
  true *measurements* — those frames were insensitive — but they are not a
  general invariant and must not be cited as one.
* The Phase 3 gate therefore compares frames with `compare_frames.py`'s RMSE /
  coverage / luminance, not with `cmp`, and the exact-integer oracle for
  gameplay behaviour stays the `DAYBREAK_CAMINFO` trace (positions and states,
  which still match to the unit across both implementations and both targets).
* Making the evaluator bit-reproducible across compilers would mean a
  deterministic math layer; not attempted, and not needed for the gate.

- [ ] Effect techniques completed (trails via `FUN_00633ca0`, per-effect
      factors, billboard yaw vs original).
- [x] CJK implementation from the Phase 1 decision. **Landed `47875f0`**:
      `ui::TextLayer` (stb_truetype, on-demand glyph cache, uploadable RGBA8
      atlas, `\c` colour runs, integer fixed-point advances), 500 checks,
      bitmap fallback bit-for-bit identical to `ui::measureText`. Not wired to
      the HUD yet on purpose — the gate frame's HUD is ASCII; the CJK strings
      (適当, the menu) belong to the menus item below. The same test found the
      shipped CP932 table was generated from texture filenames only and could
      not convert 15 code points used by menu text; regenerated full-CP932.
- [ ] Animation pose correctness. **The top open bug**: with any animation
      bound the skinned model tumbles (upright at frame 1, inverted by frame
      15). The DX9 A/B cannot catch it — it binds zero animation sets for
      shipped characters, so its captures are all bind pose. Also the reason
      Linux/Wine byte-identity stops at animated frames (see the table above).
- [ ] Video if D6 scope reaches it (pl_mpeg vendor + uploader; still
      stubbed until then).
- [ ] Menus/title/opening scenes after gameplay (D6 order: versus first).
      **Known trap, recorded 2026-10-02 (owner)**: the scene named `title` is a
      misnomer — `Scene_Title` draws only `data/select/bg00.cnv`, the shared
      *select-screen* panel background (the 青組/赤組 diamond layer of
      `docs/reference/team-select.webp`), with no portraits, labels or cursor.
      The real main menu is a **shrine** with six Japanese items (ストーリー /
      対戦 / 通信対戦 / 環境設定 / 操作設定 / 終了, `docs/reference/title-menu.webp`)
      and is not reachable from the CLI at all. Any capture or note labelled
      "title" today is therefore the select background — this mislabelling has
      already misled one reviewer, so the frontend port should rename the scene
      and treat the shrine menu as unimplemented rather than "placeholder art".
      Full inventory: `remake/docs/placeholders.md` §13.
- [ ] CJK implementation from the Phase 1 decision (decision recorded in
      `docs/CJK-TEXT.md`, no code yet). The menu text above is the strongest
      evidence that it is needed: the first screen the player sees is Japanese,
      and so is every item on it.

Gate: D2's letter — a complete in-game frame matching the banked DX9
reference. **Superseded 2026-10-02:** §6a corrected the visual target to the
original's prints, the match against those was measured (§6a, D2 reversal),
and the cutover (§8) executed with the remaining items tracked here and in
`ROADMAP-PENDING.md`. DX9 is no longer buildable, by design.

## 7. Phase 4 — netplay (design first, D6)

Greenfield deterministic lockstep over UDP. No code before a design doc
covering: input delay vs rollback, float-determinism discipline across
MSVC/MinGW/Emscripten toolchains, desync detection, and what "LAN-first"
excludes. Separate plan, separate review — listed here only so it is not
forgotten.

## 8. Phase 5 — cutover (**executed 2026-10-02**)

Executed in the order below; this section is now the record, not a to-do.
Steps are the original plan's, annotated with what actually happened.

1. **The default flipped — by deletion, not retargeting.** `remake/build.sh`
   was deleted outright instead of being repointed at the foundation: the
   foundation already has its own build
   (`remake/foundation/build.sh linux|windows|web|all`), so there is no
   `build-dx9.sh` and no second build to keep in step.
2. **Deleted** in the cutover change: `remake/src/` in full (core, render,
   file_parser, gameplay, physics, input, maps, audio, assets, `main.cpp`),
   `remake/CMakeLists.txt`, `remake/build.sh`, `remake/launch_daybreak.sh`,
   `remake/cmake/`, the DX9 test fixtures (`remake/tests/visual/`,
   `gen_test_dat.py`, `*.x`, `test_bundle.dat`), and the prototypes
   `webgpu-mvp/` + `webgpu-spike/`. The DX9 toolchain payloads
   `remake/tools/{d3dx9,SDL2-2.30.10,SDL2_mixer-2.8.0}` are local-only
   (gitignored) and go with the same cutover per §1.5 — they cannot appear in
   the commit, so their removal is a disk action, not a diff. The
   `debug_prim.*` precondition resolved
   the other way: the cube pass *was* a placeholder for un-RE'd VFX, the
   foundation carries the same cube capability in
   `foundation/src/render/debug_prims.*`, and the real effect path
   (trails/auras/billboards) is an open item in `ROADMAP-PENDING.md` rather
   than a silent loss of function.
3. **Deliberately kept.** `remake/tests/parity-baseline/` — the Phase 0 bank,
   now a **frozen archive** (`regen.sh` needs the deleted
   `remake/build/daybreak.exe`, so it documents provenance and cannot
   regenerate; the README says so); `remake/docs/` — `decisions.md` (D2
   reversed, in place), `game-spec.md`, the 23 original prints in
   `reference/`, and `roadmap.md`/`placeholders.md` as the DX9 record;
   `remake/tools/{asset-tools,hook-tracer}`, `remake/assets/shaders/`,
   `remake/scripts/` and the host toolchain, pending the §1.5 audit.
4. **Docs updated in the same change.** `decisions.md` D2 reversal (dated,
   with the measured evidence and what replaces the A/B), `AGENTS.md` rule 2 +
   halves table + map + commands, `remake/README.md` (foundation is the
   product; the DX9 body is marked as the record), `roadmap.md` and
   `placeholders.md` status plus the animation-key correction, and the new
   `foundation/docs/ROADMAP-PENDING.md` for everything still open.
5. **Verification — stated at its real strength.** The Phase 0
   D3D9/SDL2-family grep target is zero by construction: the tree that held
   all 35 files is gone. The foundation builds Linux/Windows/web and runs
   offscreen green on Linux and Wine; the **web** plain demo has been run in
   headless Chromium (SwiftShader) and printed `RESULT: ok`, but a browser run
   *with game assets in the versus scene* is still unverified, and **macOS
   execution remains unverified** (standing rule). "A playable versus match
   runs on all three targets" is therefore **not** claimed for web or macOS —
   both are carried in `ROADMAP-PENDING.md`.
6. **One correction made after the fact, recorded here so it is not lost
   (§6a's own mip attribution).** §6a originally blamed the DX9-frame residual
   on the reference filtering *with* mips. That was wrong: the DX9 remake
   builds textures with `MipLevels=1` (`remake/src/render/ui_image.cpp:61` —
   deleted in this cutover; see the `pre-webgpu-cutover` tag) and sets only
   MIN/MAG (`remake/src/core/scenes.cpp:760-761`), leaving D3D9's default
   `MIPFILTER=NONE`. So the three DX9 gate numbers in §6a (0.063988 / 0.063431
   / 0.056068) predate mips and **must be re-banked before being quoted
   again**; the original's prints are the right instrument, and against
   `battle-hud.webp` the stage band moved 0.255956 → 0.254041 with the shipped
   levels still to be wired (`ROADMAP-PENDING.md`).

Rollback: `pre-webgpu-cutover` tag (`37ed31d`) + this branch, kept until the
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
