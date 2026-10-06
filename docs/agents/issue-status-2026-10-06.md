# Coordinator status — issue batch of 2026-10-06

> Owner: coordinator session. One line per issue, newest state wins. `main` is the
> coordinator's alone; workers commit on their branch and never push/rebase/merge.

Base commit for the whole batch: `main` @ `a35e36d`.

## Dispatch plan (revised from the human's suggested order)

| Wave | Issues | Why this order |
|---|---|---|
| 0a | #45, #42 | #45 re-baselines the front-end scripts and #42 is hypothesis 3 of the #46 crash; #46's repro is only clean once both have landed |
| 0b | #46, #28 | crash next (highest severity, blocked on 0a); CI cadence is one YAML file, disjoint |
| 0c | #29 | needs a human decision on the default (see Open decisions) |
| 1 | #26 → #18 → #52 → #53 → #54 (+#31) | one agent, sequential, shared set table |
| 2 | #41 → #44 → #43 → #47 (+#40 blocked) | after #45 |
| 3 | #51 | after animation (camera is facing-relative) |
| 4 | #49 → #50, #38 (blocked on human eye) | |
| 5 | #21 → #32 → #33 → #34 → #27 | |
| 6 | #35, #36, #37, #4 | #37 needs a human decision |
| 7 | #24, #3 | |

## Per-issue status

| Issue | Area | Branch / worktree | Worker | State | Hash |
|---|---|---|---|---|---|
| #45 | frontend | `fix/issue-45-frontend-state-lifecycle` | verified + merged | **MERGED** `850c95d` (worker `b91d329`) |
| #42 | audio | `fix/issue-42-vs-bgm-no-sfl` | verified + merged | **MERGED** `1e0005f` (worker `fa8f8b0`) |
| #46 | gameplay/crash | `fix/issue-46-match-start-crash` | verified + merged | **MERGED** `b1bde91` (worker `dd8473a`) |
| #28 | verification | `chore/issue-28-ci-cadence` | verified + merged | **MERGED** `006745b` (worker `ff3a194`) |
| #37 | platform | decision recorded | **CLOSED** — D13 in `remake/docs/decisions.md` | `4cb3694` |
| #18 (+#31) | animation | `feat/issue-18-guard-jump-sets` | verified + merged | **MERGED** `b49b22b` (worker `11215aa`/`cf88879`) |
| #29 | verification | `fix/issue-29-input-devices` | verified + merged | **MERGED** `6a0a99f` (worker `b1474cc`/`8c910a4`) |
| #41 | frontend | `fix/issue-41-select-free-cursor` | verified + merged | **MERGED** `c8e5245` (worker `d028c71`/`0c11e4b`) |
| — | infra | `fix/ci-linux-sdl-deps` | verified + merged | **MERGED** `2b76e2c` — CI green for the first time |
| #26 | animation | — | **re-scoped on GitHub** (per the human) | issue edited |
| #37 | platform | — | **CLOSED** — D13 | `4cb3694` |
| #38 | renderer | — | dropped (human: really low priority) | — |
| #40 | frontend | `feat/issue-40-opening-movie` @ `dbd-worktrees/issue-40` | dispatched (vendor pl_mpeg, simple) | in progress | — |
| #49 | hud | `fix/issue-49-ring-lock-state` @ `dbd-worktrees/issue-49` | dispatched | in progress | — |
| #43 | frontend | `feat/issue-43-select-row-slidein` @ `dbd-worktrees/issue-43` | dispatched | in progress | — |
| #43 | frontend | `feat/issue-43-select-row-slidein` | verified + merged | **MERGED** `86a8d2f` (worker `8587239`) — **issue premise was wrong** |
| #44, #50, #2, #21, #32, #33, #34, #27, #51, #48, #30, #35, #36, #4, #39, #24, #3 | — | — | queued | — |

`main` is at **48/48 ctest** with the install and **48/48 with five tests Skipped** in a checkout
with no game data at all (measured, not inferred — see below).

## Round 2 — four merges, verified myself

**#42** (also round 1) — see below.

**#45 frontend selection lifecycle.** I reproduced the human's exact bug before merging:
`/tmp/rt/frontend-roundtrip.txt` does title → select → pick Rika → Back to title → select → battle.
Pre-change the battle plays **`1P Rika 0`** (the first entry's pick survived the round trip); after
`b91d329` the same script plays **`1P Rena 0`** (the second entry's own pick). Stale `FrontendState`
is therefore **eliminated** as a hypothesis for #46 — the worker said so, and my run confirms it.
I also re-ran the 4p script and all three release-gate rematch scripts with their *documented*
player counts (1v1 `=2`, com `=1`, 2v2 `=4`; I first ran all three with `=2` and got 2-fighter 2v2
runs — the counts matter) and every one ends `RESULT: ok` on the documented ladder.

**#28 CI cadence.** Verified: the workflow's `gate` job diffs the push's whole `before..after` range,
so a `VERSION` bump counts wherever it sits (the tip-commit version silently skipped windows/web);
`92b6d70` → linux only; `a35e36d` → the workflow does not run. The worker also found and fixed a
prerequisite defect — **`npr_normals_test` never honoured its own exit-77 skip contract**
(`CMakeLists.txt:409-410` always passed the install path; `npr_normals_test.cpp:245` only checked
the argument was non-empty), so the first per-push run on a runner with no game data would have gone
red. I reproduced the abort myself (real exit **134**) without touching the shared install, and after
the fix a no-data tree is **48/48 with 5 Skipped** where it was 1 aborted.

**#46 crash — root cause, fix, and the #39 blind spot.** See the section above for the core-dump
forensics. The fix is an 11-line clear in `initScene` before the scene assignment
(`fd2e97f`/`dd8473a`). Verified by me: the windowed non-capturing recipe that aborted now exits 0
with `RESULT: ok`; the new `controller_scene_lifetime_test` fails **3 checks** with the fix reverted
and passes **12/12** with it; ctest 45 → 48 across the batch. And the sharpest result of the round:

> the **same** 5600-frame `--headless --out` capture is byte-identical before and after the fix
> (`sha256 dd23cc5c40df0c8474aac12c18255c1a815a10192e71838d20c8db167ecdfa05`), and the **pre-fix**
> binary completes it with `RESULT: ok` — while the windowed run of the same recipe dies.

So capture A/B cannot even *detect* scene-lifetime defects, not merely fail to reproduce them. That
belongs in #39's write-up.

**#37 platform.** The human delegated the choice and asked for the simpler option. Recorded as
**D13**: Linux keeps the Vulkan-only adapter request. The deciding fact is a verified negative —
`strings` over the shipped `libwgpu_native.so` finds **no `WGPU_*` environment variable at all**, so
a prefer-Vulkan-with-fallback retry could not be made safe and would re-enter the
`gles/egl.rs:899` abort it exists to avoid. The reach it costs is stated in D13, and the error
message (which names the driver to install) was verified unchanged.

**#26 re-scoped on GitHub** with the human's approval, to the only genuinely-open item: the
vtable-`0x20` per-character handler-family hits (40/41/42, 400-family). Title and body rewritten;
the original body is preserved in a collapsed `<details>` block for provenance.

**#29 decided by me** (the human had no preference): option (c), both (a) a device-free default for
headless/scripted/captured runs with an explicit `--devices` opt-in and (b) no input while the window
is unfocused, with the rule *unknown focus means focused* and the pitfall that `device()` must not
report `None` while unfocused (that would hand the slot to a synthetic pad and the game would play
itself).

## #26 is stale — verified by me before dispatching

The issue's headline ("the `state_to_anim_set` table in `src/gameplay/fighter.h` … is wrong in all
three of its anchors") no longer describes the tree:

- The table **does not exist**. `fighter.cpp:655-661` resolves `state_move_id()` →
  `CharacterMove::phase_set_index()`, with the comment "Resolve it only from this fighter's bound
  NN.dat; **there is no raw-set table**."
- The weapon dimension is present: `bind_animation_set` calls
  `has_recovered_animation_blend(character_index(), weapon_id(), currentSet, setIndex)`.
- The melee numbers are no longer port rules: `melee_rules.h:41-46` records that the 300-family
  phases read `hitRadius` (record `+0x24`), `hpDamage` (`combat[5]`), `defenderHitstun`
  (`combat[10]`) and the in-phase frame from the bound move table; only the recovery tail (17 ticks)
  and the attack-sphere centre remain port rules.
- The unarmed-attack finding was absorbed: `AttackB` was removed ("had no original justification"),
  and `AGENTS.md` rule 7 now carries the conclusion.
- `docs/ANIMATION-SETS.md` §4 documents all of the above.

So items 1–4 of #26's "To fix" are done. What genuinely remains is the 40/41/42 + 400-family hits
behind the vtable-slot-0x20 per-character handler, and the situation→move selector flags in
`FUN_0043ded0` — which is **#18's subject**. Recommendation: rewrite #26's body to that remainder and
let #18 carry it.

## #18 / #31 — the coordinator's measured baseline (main @ `1e0005f`)

The instrument already exists: `DAYBREAK_CAMINFO=1` enables `traceMatch` (`main.cpp:3286`), which
prints the port state and the set that actually plays every 60 match frames.

```sh
DAYBREAK_CAMINFO=1 ./remake/foundation/build/linux/foundation_demo \
  --install=Higurashi-Daybreak --screen=battle --local-players=1 --no-devices \
  --script=remake/foundation/tests/scripts/guard-lifecycle.txt \
  --headless --out=/tmp/g.ppm --size=64x64 --frames=900 2>&1 | grep 'daybreak] \(cam\|anim\)'
```

Deduplicated state → set correlation:

| port state | resolved set | verdict |
|---|---|---|
| `battlestart` | `43 Anim-81` | correct |
| `idle` | `0 Anim-124` | correct (idle *is* set 0) |
| **`guard`** | **`0 Anim-124 (fallback)`** | **#18's acceptance failure, measured** |

Also verified: #18's step 2 (phase progression) is **already implemented** —
`Fighter::advance_animation_phase` (`fighter.cpp:1030-1065`) does the elapsed counter, the
`animation_set_phase_gate` check, the `nearbyint(duration / ticksPerSecond)` period and the rebind,
citing `FUN_0041e180` / `FUN_00421100` / `FUN_004212f0`. #18's remaining work is the Guard/Jump
*selectors*, the blend-counter initialisation, and the roster sweep.

## #42 — verified by me, merged

Worker: `fa8f8b0`. Merged as `1e0005f`; `main` is at **46/46 ctest** and `--screen=vsintro` now
prints `menu-audio: ... bgm=47104 frames`.

I reproduced every load-bearing claim myself rather than trusting the report:

- **The causal link.** Reverting only the `loadBgmTrack` hunk while keeping the new counter gives
  `[menu] missing loop sheet data/bgm/vs.sfl` and **`bgm=0 frames`**; the committed tree gives no
  loop-sheet line and **`bgm=46080 frames`**. So the counter measures the fix, not itself.
- **No loop point moved.** `--audio-test --audio-file` over all 21 shipped tracks, before (`main`
  @ `a35e36d`) vs after: 20 `loop <start>..<end> ... 2 wraps` lines, `diff` says IDENTICAL.
- **vs.ogg**: after = `no loop sheet for ... vs.ogg, playing to EOF` + `streamed 206720/206720
  frames to EOF, 0 wraps`; before = no line at all (silently skipped).
- **Unparsable stays distinct**: a 12-byte truncated `vs.sfl` gives `unparsable loop sheet ... [port
  rule: reported, FUN_00668820 is silent]` and still streams 206720/206720 to EOF, `RESULT: ok`.
- `bgm_loop_test` passes, `ldd` shows zero SDL. Build + ctest clean on the merged tree.
- The RE chain (`FUN_00411ae0:34` → `FUN_0065b870` → `FUN_006683d0` → `FUN_00668820`) is confirmed in
  **both** corpora, as recorded above.

Accepted as port rules (the original is silent in both cases): the absent/unparsable diagnostic
split, the extension-based sibling-path rule, and the new `bgm=<n> frames` summary field (it is the
only positive playback evidence criterion 3 can have, and it mirrors the existing `menuSoundPlays` /
`versusBgmPushed` counters).

## #46 — the crash: root cause (coordinator's own work)

This is **not** a front-end or stale-`FrontendState` bug, and it is **not** the `.sfl`/audio path.
I recovered a symbolized backtrace from the core dump the reporter left
(`coredumpctl`, entry **563299**), which the issue did not have:

```
#8  xm::Controller::evalLocal(...)   foundation_demo + 0xddeb6
#9  xm::Controller::evalWorld(...)   foundation_demo + 0xe3873
#10 (anonymous namespace)::advanceAnimation(App&, double)   foundation_demo + 0x16e1f
#11 SDL_AppIterate
```

Then I read the faulting frame out of the core with gdb:

- the failing instruction is `evalLocal+129`, `call _Znwm@plt` — i.e. `operator new` from
  `main.cpp:2057`'s `pos.assign(nf, glm::vec3(0.f))`;
- the requested size, recovered from `[rsp+8]` where `+124` saved `%rcx`, is **6148914691325296640
  bytes = 0x5555555555555580**;
- `this` (a `Controller`) has `model_ = 0x55b404fb8428`;
- `model_->frames` reads as `{begin = 0, end = 0x3f800000, cap = 0}` → `end - begin = 0x3f800000`
  = 1065353216, i.e. **the IEEE-754 bit pattern of `1.0f`**, and the memory at `model_` is
  `0.0f/1.0f` float data, not a `Model`.

So the `bad_alloc` is a **stale `Controller::model_` pointer**, not an out-of-memory condition:
`model_->frames` is read out of recycled heap and `nf` comes back as 66584576.

**Mechanism, and it is a real code defect:**

- `Controller::bind()` stores a raw `const Model*` (`xmodel.h:238`), bound for the fighter rigs at
  `main.cpp:2260` as `anims[i] = &app.controllers[rigs[i]]` and `models[i] = &app.scene.models[rigs[i]].model`.
- `rigs[i]` is **the scene-model index of the i-th model whose `role == "character"`**
  (`main.cpp:2150-2152`), so the controller index a fighter uses depends on how many non-character
  models precede the characters in that stage's scene.
- `initScene` replaces the whole scene (`app.scene = loadScene(...)`, `main.cpp:3511`), then does
  `app.controllers.resize(app.scene.models.size())` (`main.cpp:3559`). **`resize` does not clear the
  surviving entries**, and the rebind loop at `main.cpp:3564` only rebinds when `opts.anim >= 0`.
  `initMatch` then rebinds only the *current* `rigs[]` (`main.cpp:2259-2261`).
- Therefore any controller bound by a **previous** match whose scene index is not a fighter rig in the
  new match keeps a pointer into the freed scene, and `advanceAnimation`
  (`main.cpp:3844-3845`) evaluates **every** controller with a non-null `model_`.

**Reproduced deterministically** (release build, `frontend-2v2-rematch.txt`, 4 fighters,
`--local-players=4 --no-devices`):

```
[dbg-stale] before rebind: scene.models=46 controllers=46 rigs=7,9,11,13 bound=4 stale=4
[dbg-stale] STALE controller 8  model=0x... after replace (scene.models=46)
[dbg-stale] STALE controller 10 model=0x... after replace (scene.models=46)
[dbg-stale] STALE controller 12 model=0x... after replace (scene.models=46)
[dbg-stale] STALE controller 14 model=0x... after replace (scene.models=46)
```

Match 1 (stage04) and match 2 (stage06) both use rigs `8,10,12,14`, so re-binding covers them;
match 3 (stage15) uses rigs `7,9,11,13`, so controllers **8, 10, 12 and 14 are left dangling** and
are then evaluated. The abort is allocator-dependent, which is exactly why the reporter hit it and
the scripted recipes do not.

**Why the existing recipes cannot see it:** with `--out=` the run is `capturing`
(`main.cpp:4932`), and `main.cpp:5007` is `if (!capturing) advanceAnimation(...)`. Every capture
recipe therefore **skips the crashing function entirely**. This is the same blind spot issue #39
describes, and it is worth folding into #39's write-up.

**Reproduced — the abort itself, on the live path** (not just the mechanism). Release build,
`frontend-2v2-rematch.txt`, 4 fighters, **no `--out=`** (a windowed run against
`XDG_RUNTIME_DIR=/run/user/1000 WAYLAND_DISPLAY=wayland-0`):

```
[dbg-stale] entering initScene: scene.models=18 controllers=47 bound=4 stale(before replace)=4
[dbg-stale] STALE controller 8  model=0x55983321d6e0 after replace (scene.models=49)
[dbg-stale] STALE controller 10 model=0x55983321da50 after replace (scene.models=49)
[dbg-stale] STALE controller 12 model=0x55983321ddc0 after replace (scene.models=49)
[dbg-stale] STALE controller 14 model=0x55983321e130 after replace (scene.models=49)
[dbg-stale] before rebind: scene.models=49 controllers=49 rigs=10,12,14,16 bound=4 stale=4
[dbg-dead]  controller 8 model=0x55983321d6e0 NOT in scene (49 models)
-> SIGSEGV, exit 139
```

Match 1 (stage04) and match 2 (stage06) both use rigs `8,10,12,14`, so rebinding covers them; match 3
(stage15) uses rigs `10,12,14,16`, so controllers **8** (and 10/12/14 before their rebind) are left
pointing into the freed scene and are then evaluated. `bad_alloc` vs `SIGSEGV` is allocator-dependent
— same defect, two faces, which is exactly why the reporter's core shows `bad_alloc` and my run
segfaults. The log shape also matches the reporter's: `[menu] missing loop sheet data/bgm/vs.sfl`,
then the scene swap, then `[scene] data/item/04.x: attachment frame 89 unusable` (theirs was
`data/item/58.x`, frame 87), then death.

**Why no existing recipe can see it:** `main.cpp:4932` is `const bool capturing = !app->opts.out.empty();`
and `main.cpp:5007` is `if (!capturing) advanceAnimation(...)`. **Every `--out=`/`--headless` capture
recipe skips the crashing function entirely.** That is issue #39's blind spot with a concrete body
count now — it should be folded into #39's write-up.

Fix dispatched to a worker with this brief; my diagnostic instrumentation was reverted from the
worktree before hand-off.

## BINARY PROVENANCE (told to me by the human, 2026-10-06) — applies to every citation

The Ghidra project currently has the **original (unpatched)** `DaybreakDX.exe` loaded. The
**first RE pass that produced `research/` ran on a patched copy**. Addresses, function boundaries
and names from the live bridge may therefore not match `research/decompiled/`,
`research/symbols/` or `research/recomp/` one-for-one.

- Live program `DaybreakDX.exe` = `Higurashi-Daybreak/DaybreakDX.exe`, md5
  `a136ddc01bd7ef355b759b88ac89e02c`, 2920448 bytes, **4267 functions**, 25456 symbols.
- A third program `DaybreakDX.exe-old` is open from `/mnt/disco1/Games-Windows/Higurashi Daybreak/`
  and is effectively unanalyzed (10 functions, 188 symbols) — **not** the corpus binary.
- Sampled agreement is good, not guaranteed: `FUN_00411ae0` and `FUN_00668820` agree at the same
  addresses in both corpora (only cosmetic local-variable names differ).
- **Rule given to every worker**: every address must name its source ("live original via bridge" vs
  "`research/decompiled/FUN_xxxxxx.c`, first pass"); cross-check in both where possible; if they
  disagree, say so and label the port behaviour a port rule; never rename in Ghidra.

## Coordinator-verified facts (reproduced by me, not taken from a report)

- Baseline `main` @ `a35e36d`: **45/45 ctest pass**, 56 s, in both the primary checkout and a fresh
  worktree. `ccache` present; a worktree pre-warm takes **~27 s**.
- Ghidra bridge: **tool endpoints are at the root path** (`/decompile_function?address=..`), not
  under `/mcp/`. `/mcp/health`, `/mcp/instance_info`, `/mcp/schema` are discovery only.
  `DaybreakDX.exe` is open (also `MBAA.exe`, `DaybreakDX.exe-old` — always pass `program=`).
- #42's RE, reproduced by me: `FUN_00411ae0:34` = `FUN_0065b870("data/bgm/vs.ogg")` (path only).
  `FUN_00668820` treats the `.sfl` as optional (`FUN_00653540` existence check) and leaves the loop
  fields at `_DAT_006a5630` = double `0.0` when it is missing → **no loop, play once to EOF**.
  `data/bgm/` = 21 `.ogg`, 20 `.sfl`; `vs.ogg` is the only one without a sheet.
- #45's stated cause is **wrong**: `src/ui/screen.cpp:70`'s static is reached only from
  `tests/screen_stack_test.cpp`. The live state is `App::frontend` (`src/main.cpp:819`), passed to
  the 4-arg `makeScreen` at `src/main.cpp:4286`. Correction passed to the worker.

## Open decisions for the human

1. **#29** — the issue's acceptance lists three options: (a) headless/scripted/captured runs ignore
   physical devices unless `--devices`; (b) ignore input while the window is unfocused; (c) both.
   Which default? (b) carries a Wayland/X11 risk: a missed `FOCUS_GAINED` would leave the game
   unresponsive, so it needs an "unknown focus = focused" rule.
2. **#38** — needs your eye on the toon/outline captures.
3. **#37** — keep the Vulkan-only adapter request, or fall back?
4. **#40** — the opening-movie decoder decision.

## Round 3 — three more merges, and CI green for the first time in the repo's history

`main` is at **50/50 ctest** with the install and **50/50 with six Skipped** in a checkout with no
game data at all. Everything below was reproduced by me before merging.

**#29 input devices.** Option (c), both halves. Verified: the release recipe is **byte-identical**
between *main + `--no-devices`* and *the branch with no flag* (`sha256 34a6d3a9…`), so making
verification runs device-free by default preserved behaviour exactly. `device_isolation_test` passes
44/44, and the design does the one thing that mattered — `device()` deliberately still *names* a pad
while unfocused, so a `--local-players` slot is never handed to a synthetic pad.

**#18 + #31 animation selectors.** Measured before/after with the trace I set up in round 1:
`guard` went from `set 0 (fallback)` to `set 0 (no selector)` — Guard binds no clip *in the source*
(`FUN_00637950`'s blocked branch calls no move bind), which is a recovered result, not a gap — and
the airborne attack now plays its resolved `set 88 Anim-36`. The worker also corrected my brief: a
capture *with* `--anim` does call `advanceAnimation`, so #39's claim needed narrowing to the match
tick. Its committed `air-attack.txt` recipe did **not** reproduce on the rebased tree (a lone leap is
interrupted by the COM), so I recalibrated it and re-measured 4 `set 88` samples in each of three
consecutive runs rather than shipping a recipe that lies.

**#41 free select cursor.** The recovered rule implemented faithfully, and the worker corrected the
issue's own premise with a BFS over the pre-change code: all 16 entries *were* reachable, but a press
jumped a whole cell with counter-icon landings (`rena: L→keiichi R→rika U→satoko`, `DOWN` a no-op on
`rena`). The real defect was the unslidable jump, not unreachability — worth knowing before anyone
re-tests by hand. All four gate scripts still select the same characters.

### CI: two pre-existing defects, both found by the new per-push trigger

The first push after #28 landed turned CI red, and it was right to:

1. The **linux job could never build SDL** — the runner has no X11/Wayland development libraries, so
   `configure` refused. The workflow had run **twice in its life, both failures**, and nobody saw it
   because it only ran on VERSION bumps. Fixed by installing SDL's own dependency set.
2. The **windows job's toolchain path was relative**, and CMake resolves `CMAKE_TOOLCHAIN_FILE`
   against the *build* directory — I reproduced it locally word for word, including the misleading
   "unable to find a build program corresponding to Ninja" cascade, and fixed it to the absolute form
   `build.sh` already used.

After both: `gate` ✓ `linux` ✓ `windows` ✓ `web` ✓ on a `workflow_dispatch`, and `gate` ✓ `linux` ✓
with `windows`/`web` **skipped** on an ordinary push to `main` — exactly the cadence #28 specified,
now verified against real GitHub Actions rather than modelled.

## Round 5 — coordinator's own verification while three workers run

**The 8-round 2v2 stability gate passes on the merged tree.** This is the checklist's own strongest
integration recipe (§6's row), and it is the first time it has run over everything merged in this
batch — #45's selection lifecycle, #41's free cursor, #29's device isolation and #46's controller
lifetime all working together:

```
--screen=title --local-players=4 --script=<8-round 2v2> --frames=40000
EXIT=0   8 battles   8 rounds over
fx cards : events=38029 spawned=124 dropped=0 expired=123 killed=0 peak=6/128,
           liveShots=5500 badEffectId=0
RESULT: ok
```

Those counters are exactly the ones `RELEASE-CHECKLIST.md` §6 quotes for that row
(`peak=6/128`, `spawned=124`, `expired=123`, `dropped=0`), so the quoted block is still true.

**§3.1's transcript was the only stale one.** A worker flagged that its quoted outcome lines no longer
reproduced. I re-measured all three gate transcripts myself: §3.1 quoted `side 0 wins` for round 2 and
carried no result line for either later round, while the run reports side 1 winning all three with
pairs `2-2 / 12-12 / 11-11`; §3.2 and §3.3 still match their quotes **exactly**, down to
`11-11 margin 21` and `1-4 margin 1`. Fixed §3.1 (`ec73b52`) and recorded which fields are stable —
the ladder, the stages and the settings — versus which follow the OK path's random COM roll.

**The CI path filter behaves as designed.** Pushes that touch only `docs/**` produce no workflow run
(verified: `a39ba7e` and `33ef9be` have none), while `52c0d88`'s touch of
`remake/foundation/docs/RELEASE-CHECKLIST.md` triggered one, green.

## Round 6 — #43 merged, and the issue's premise was wrong

**#43's body attributed the recovered `0.1`/`i+5` ramp to the weapon/hypermode/controller rows. It
is not that.** The ramp drives the **16 chibi icons' entry reveal** (`FUN_004090a0:24-26` /
`FUN_0041bae0:37-40` over the objects at `scene+0x150c+i*0xa0`, the `i%02d.bmp` chibis). The row
slide the human reported is a *different* recovered transition, `0x3cc4`: `FUN_00409340:589-595`
sets 300.0 on a phase change and steps 20.0/tick while > 0, and `FUN_0040b2b0:0x40c09f-0x40c0c4`
signs it by panel column and adds it to the header, the rows, the choice sprite and the arrow. The
worker implemented **both**, each with its own provenance, rather than the invented one — and the
question the issue said to pin first now has an answer.

**`+0x84`/`+0x88` are the sprite quad's x and y SCALE**, consumed by `FUN_00655830`
`@0x65583f-0x6558db` as `x0 = x - pivotX*sx`, `w = srcW*sx` (and the y pair likewise).
`FUN_0040da60` writes the pair; `FUN_00408250` writes one value into both, which is the uniform
case the port already modelled. So `(v, 2-v)` is a scale, **not** an x-offset.

**Verified by me before merging**: ctest 50 → **51**; `select_row_slidein_test` shows the stagger
directly (`slot 0` first step at tick 6, `slot 15` at tick 21); and the **settled select frame is
byte-identical** before and after (`sha256 367fade4197d82d7d0ba0eba77136fd2b4729f42c3a410f259ee8df207478b87`),
so the change only affects the transition window. I closed #43 with the correction rather than
rewriting its body.

**#44's premise is confirmed correct by that finding**: it said it shares the ramp with #43, and
the ramp *is* the chibi reveal — so #44 can reuse `ui::SelectReveal` as-is.

## Round 7 — #49 merged, and its issue's question answered

**#49's question ("does a fighter with no prior selection acquire a target automatically?") has a
definitive answer: no.** The auto-acquire was a port invention. From the live original:
`FUN_0041f580`'s maintenance branch clears `+0x304` at `0x421fecb` and then calls `FUN_00421e30`,
which clears it *again* at `0x421e96`; the only store that makes `+0x304` valid is `FUN_00421f30`'s
`0x421f65`, whose only callers are `FUN_0041f580` and the command dispatcher `FUN_0063c2a0` (command
`0x2b` = the LockSwitch tap). An exhaustive operand scan of `0x304` (31 instructions program-wide)
found no other writer, and the one automatic call is gated on `+0x28c == 0x1e`, which nothing in the
binary ever stores.

**Verified by me, not taken from the report.** Same recipe
(`--screen=battle --local-players=1 --frames=300 --size=800x600`), counting ring pixels at the art's
own colours:

| build | red px | green px |
|---|---|---|
| `main` before (auto-acquire) | **0** | 640 |
| after #49 | **427** | 315 |

Every ring green before — the human's exact report — and after, the human red and unlocked while the
COM is green from a lock its own brain requested.

**A documented rule was backwards.** `ROADMAP-PENDING.md` D2 read `local_31` as "this fighter is the
viewer's locked target"; the live disassembly (`0x6433b0-0x6433f7`) makes it
`(owner->0x300 == lookup(owner+0x2f0, 0)->0x300) && (owner->0x304 < 0)` — the drawn fighter is what
that container's element 0 faces **and has no lock of its own**. Nothing in the ring path reads
another fighter's `+0x304`. The human's "second reticle when both are aiming at each other" was a
misreading caused by the port's tick-1 auto-acquire, which meant the second copy never drew at all.
The doc is corrected; the drawing code already had the right condition.

## Round 8 — #40 merged (the opening movie)

**pl_mpeg vendored** exactly as the human asked ("vendor pl mpeg, simple"): a pinned commit
(`c871f2be…`) fetched as a single raw blob in `fetch_deps.sh` with the stb pattern, its MIT text in
`remake/foundation/package/LICENSES/pl_mpeg-MIT.txt` and a row in that directory's table, and **one**
player class (`src/movie/movie_player.{h,cpp}`) — decode → YCrCb→RGBA on the CPU → the HUD's existing
`updateTexture` → one quad. No thread, no shader path, no second screen.

**The skip was recovered, not invented**: `FUN_00404ff0`'s update tests `FUN_006586d0(0x1c)`, `0xb8`,
`0x38` — raw virtual-key **down** tests, so **Enter or either Alt, held, never an edge**. (The docs
had claimed "any controller button"; that was wrong and is corrected.) The pad half is recoverable as
offsets but not as button names, so it was deliberately left unimplemented rather than guessed.
`FUN_00408250(0x3fa00000)` = 1.25f is the sprite **scale**, i.e. the 640×480 movie drawn at exactly
800×600 — the port's own menu canvas.

**Verified by me on the merged tree**: `ended after 684 frames decoded/684 presented (22.789 s),
audio 22.857 s` → `[menu] scene: title (tick 1485)` → `RESULT: ok`; the same-run A/V drift is flat at
+0.26–0.28 s (the deliberate audio lead, not accumulating); and a `--screen=title` capture emits
**zero** `movie` lines, so no evidence run pays the 22.7 MB decode. `staffroll.mpg` runs through the
same player to `RESULT: ok`.

**One merge-time detail worth knowing**: `third_party/` is hardlinked per worktree, so the fetched
`pl_mpeg.h` existed only in the worker's tree. A fresh checkout needs `./remake/foundation/build.sh
deps` — which the coordinator ran in the primary before building the merge.

## Round 9 — dispatch, and what a successor needs to know

**Dispatched:** #44 (chibi reveal's white flash + the screen flash — the two things #43 deliberately
left), #47 (countdown over the loaded scene), #51 (the LockSwitch tap must not move the camera).

**#47's worker corrected its own issue, and the correction is the useful part.** The issue says "the
match is only loaded after the countdown"; it measured that the match is **already built** at the
VS→Battle hand-over (the baseline log prints `match : 2 fighters, movement/ground=loaded,
projectile=loaded` before `[menu] battle:` and ~180 ticks before the first countdown frame). The real
cause is that `screensMode` draws only the UI screen while `matchMode` stays false, so the arena is
never rendered. That turns the fix from "move the initialisation earlier" into "render the scene that
already exists" — smaller and safer. I asked for that to be prominent in the report rather than doing
the issue's item 1 for symmetry.

### How to continue this batch (for whoever picks it up)

- `main` is the coordinator's alone. Workers commit on their branch and never push, rebase or merge.
  The coordinator rebases onto `main`, re-runs the verification, merges, and pushes.
- Worktrees live in `../dbd-worktrees/<slug>`; `tools/wt-setup.sh <slug> <branch> [base]` creates one
  with `third_party` hardlinked, the install symlinked at the worktree root, and a ccache-warmed build
  (~30 s). **Never rename or hide the shared install** — every worktree symlinks the same directory.
- **One merge-time detail that has already bitten once**: `third_party/` is hardlinked per worktree,
  so a dependency a worker *fetches* (pl_mpeg, #40) exists only in that worktree. Run
  `./remake/foundation/build.sh deps` in whichever tree you are building after such a merge.
- The Ghidra bridge is at `http://127.0.0.1:8089`: `/mcp/health`, `/mcp/instance_info` and
  `/mcp/schema` are **discovery only** — the 204 tool endpoints are at the **root** path
  (`/decompile_function?address=0x0040b2b0&program=DaybreakDX.exe`). The project has the **original**
  `DaybreakDX.exe` (md5 `a136ddc01bd7ef355b759b88ac89e02c`) open while `research/` came from a
  **patched** copy, so every address in a report must name which side it came from.
- Verify, do not trust: every merge in this batch was preceded by the coordinator reproducing the
  load-bearing claim (a hash, a pixel count, a failing test, a real CI run). Reports have been wrong
  or stale more than once — #45's stated cause, #43's stated ramp, #47's stated ordering, #28's
  "CI-clean already" premise and #26's whole body were each corrected by measurement.

## Round 10 — the human's reticle report fixed on the spot (#55)

The human reviewed #49's merge and reported that the reticle "is using the same reticle image twice —
there are two reticle images, one circular and one with 4 triangles. right now there are two circular
ones stacked... the original game has the circular one and the triangular one on the outside of the
circle."

**Confirmed in the code**: `hud.cpp` drew `HudIcon::Ring, col, row` for both copies, and
`hudRingTransform` returns one scale, so the owner's two reticles were the same art at the same size
differing only in rotation.

**Confirmed in the art**: `data/object/p03.cnv` decodes to 512×512, and the band the port calls the
ring's base row carries the reticle as a **pair of adjacent 128-px cells per column** — the circle,
then the four outward triangles. The port modelled one cell and drew it twice; the triangles cell
was referenced by nothing. (Decoded with `remake/tools/asset-tools/cnv_convert.py`; crops in
`/tmp/ring_bands.png`.)

**Fixed and verified from the pixels**: the second copy is now `hudRingSecondCellColumn(col)`
(the next cell along), and a capture shows the unlocked owner with the circle plus the four triangles
outside it while a locked fighter still draws its single green copy. `hudRingSecondCellColumn` is
extracted beside `hudRingCounterRotates` so `hud_layout_test` pins which cell each copy uses — the
new checks fail pre-change with `error: 'hudRingSecondCellColumn' is not a member of 'ui'`.

**The honest caveat, recorded in the code**: `FUN_00643230` passes the *same* cell argument to both
`FUN_00655830` calls, so the recovered update does not itself distinguish the two cells. The
selection is read from the shipped sheet and settled by the human's description of the original — a
labelled port rule, not a recovered one. The **row** rule (0 black/acting, 1 red/plain, 2 green/locked)
is recovered and was not touched.

## Round 11 — #51 merged (the LockSwitch tap no longer moves the camera)

Removed `view.camera.cycle_target(true)`; `match.cycle_locked_target` stays. Independently verified:
the 1v1 release-gate capture is **byte-identical** before and after
(`md5 3e4e892adaee5fa73f653689bb357319`), all four ladders `RESULT: ok` with zero non-noise
differing lines, and the new `lock_switch_camera_test` fails pre-change with **55 of 107 checks**
failing and passes 107/107 now. Suite 51 → 52.

Two audited findings worth keeping: `ArenaCamera::cycle_target` now has **no product caller** (kept
as the ported reference API that `arena_camera_test`/`target_lock_test` pin, documented as such), and
**none of the four release-gate scripts contains a LockSwitch gesture**, so the gate never exercised
the tap path — which is why the camera defect survived it.

## Round 12 — batch state and exactly what is in flight

**`main` @ `f70ec38` (plus this commit), 52/52 ctest, CI green.** Fifteen issues closed or merged:
#18, #26 (re-scoped), #28, #29, #37, #40, #41, #42, #43, #45, #46, #49, #51, #55.

**Two workers were still running when this was written, both uncommitted.** Whoever picks this up
should pulse them (a short status request has worked twice — one worker answered with a correction to
its own issue that changed the fix), then verify, rebase onto `main`, merge and push.

| worktree | branch | base | in flight |
|---|---|---|---|
| `../dbd-worktrees/issue-47` | `fix/issue-47-countdown-over-scene` | `86a8d2f` | 8 modified files, no commit |
| `../dbd-worktrees/issue-44` | `feat/issue-44-chibi-reveal-flash` | `86a8d2f` | 3 modified files, no commit |

Both bases predate **four** merges (`#43`, `#40`, `#51`, `#55`), and both are expected to overlap
`src/main.cpp` and `src/ui/screen.cpp` because of #40. **That rebase is the coordinator's job, not the
workers'** — both were told not to rebase. Two specifics that will bite:

- #51 **added a `followed=` token to the `[split] view` evidence line**. Any captured baseline taken
  before it will diff on that token, and it is not a regression.
- #55 changed the owner's second reticle to the triangles cell in `hud.cpp`. A capture that includes
  an unlocked owner's reticle will differ from any baseline taken before it, by design.

**#47's worker's last status, which is a finding in its own right**: the issue says "the match is only
loaded after the countdown", but the match is **already built** at the VS→Battle hand-over; the real
cause is that `screensMode` draws only the UI screen while `matchMode` stays false, so the arena is
never rendered. It predicted **no** tick-ladder movement by construction (front-end script ticks key
on `logicTicks` with `frontendMatch` true, so `matchFrame` cannot shift them) and was asked to report
the measured before/after diff of all four gate runs rather than the argument.

**#44's remaining scope is precisely the two things #43 left**: the flashing mode while a slot's ramp
value is `< 1.0` (`FUN_0040b2b0:99-104` sets `local_2c = 2` while revealing, 0 after) and the white
screen flash built from `DAT_006cfba4` (`FUN_0040d130:33,109-117`, set by `FUN_00417c20:43-47`,
written around `FUN_0041bae0:52-60`). It was told to pin what mode 2 does (cell selection vs tint vs
both) before implementing it, and that a fallback is allowed only if labelled a port rule.

## Round 13 — the two in-flight workers' findings (both substantial)

**#44: the issue's own candidate globals were a red herring.** The issue pointed at `DAT_006cfba0` /
`(&DAT_006cfba4)[DAT_006cfba0]` as the screen flash's alpha list. They are not: they are the
participating **human slot list** (`FUN_0040d130:108-111` appends slot k when controller < 4;
`FUN_00417c20:43-48` takes the pad-0 slot). The flash is drawn by the select scene's own draw —
`FUN_0040b2b0:466-475` (corpus) / `:480-489` (live original, same) — two full-screen 800x600 quads,
**white**, with alpha windows tick 25..34 = `(tick-25)*24+15` (15..231) and tick 35..54 =
`(55-tick)*12+15` (255..27): **peak 255 on tick 35 alone, 30 ticks total**. Confirmed against the
rendered frames by probing pure-black canvas pixels: the measured alpha matches the recovered curve
with **delta 0.00/255 on every tick 20..59**.

**And mode 2 is a cell selection, not a tint.** `FUN_0040b2b0:124-131` calls
`FUN_00655830(x, y, local_2c, bVar1)` with `local_2c = 2` while the value is < 1.0, so the revealing
branch draws atlas cell (col 2, row 1) and the settled branch (0,0). `FUN_00655830` has **no colour
parameter** — its `param_4/param_5` only build the quad's UVs (`:21-28`). Measured on the install:
cell (2,1) of `data/select/i00/i01/i07/i15.cnv` is **100% opaque white** where the other five cells
are coloured art. So the cell explains the white exactly and **no tint was invented**.

**#47: the tick ladders did NOT move — measured, not argued.** All four release-gate runs are
identical tick-for-tick before and after:

| run | ladder |
|---|---|
| `frontend-4p` (4p, 9600) | title 0 \| select 34 \| vs 446 \| [countdown 180] \| result 4382 \| select 4984 \| vs 5584 \| [countdown 180] \| result 9520 |
| `1v1-rematch` (2p, 15500) | title 0 \| select 34 \| vs 446 \| [countdown 180] \| result 4382 \| select 4984 \| vs 5310 \| [countdown 180] \| result 9246 \| select 9848 \| vs 10174 \| [countdown 180] \| result 14110 \| select 14712 |
| `com-rematch` (1p, 15500) | identical to 1v1-rematch, tick for tick |
| `2v2-rematch` (4p, 15500) | identical to 1v1-rematch, tick for tick |

Its prediction held: front-end script ticks key on `logicTicks` with `frontendMatch` true, so
`matchFrame` cannot shift them. **`RELEASE-CHECKLIST.md` §3.1-§3.3 and the script headers need no
edit.** The four runs' final captured frames are also byte-identical before/after (`2483c3aa…` 4p,
`8cc49e6c…` 1v1 and 2v2, `b813155d…` com). Its device-free test **fails when the black quad is
temporarily re-added**, so it is not vacuous.

## Round 14 — #47 merged, and a rebase near-miss worth remembering

**#47 is the batch's biggest UX fix**: the pre-round countdown now draws over the live battle. The
issue's part (b) was wrong — the match is *already* built at the VS→Battle hand-over, so nothing was
reordered; the real cause was that `screensMode` drew the UI screen alone with `matchMode` false, so
the arena existed and was **never rendered** under the countdown's opaque quad. Verified on the merged
tree: ctest 53/53, countdown frames **99.20 %** (610) and **99.33 %** (730) non-black against
**0.93 % / 0.72 %** before, and the frame shows the arena, both fighters, the roster captions and the
"3" over them. All four gate ladders tick-for-tick identical, so §3.1-§3.3 are untouched.

### The rebase lesson (this is the one to carry forward)

**#47 extracted the per-view camera/HUD block out of `tickMatch` into `updateMatchViews()`, and its
base predated #51.** Rebasing therefore presented #51's fix as a *deletion*: the conflict was a
120-line "ours" body against a one-line "theirs" call, and taking it wholesale would have silently
restored `view.camera.cycle_target(true)` and reverted #51 — while looking like a clean refactor.
It was caught by grepping for `cycle_target` **after** resolving, not by reading the conflict.

**Rule for every future rebase of a branch that predates merges to the same function: after
resolving, grep for the specific identifiers the newer merges introduced** (`cycle_target`,
`followed=`, `hudRingSecondCellColumn`, `resolveBootOpening`, …) rather than trusting that the
conflict markers captured every change. A refactor-shaped conflict can swallow a semantic fix.

### Two open questions for the human (from #47)

1. **The arena camera now converges during the countdown**, so the old camera sweep-in on the first
   battle frame is gone, and front-end battle captures past the countdown are deliberately not
   byte-identical (frame 800: 905992 px vs 906168 px). Keep it, or advance the camera only in the
   last N countdown ticks?
2. **The battle HUD is still absent during the countdown** (its first frame is the round's first
   tick). One condition on the HUD pass if it should be up.

## Round 15 — dispatch notes and a decision the human needs to make

**Dispatched #48** (the recovered in-battle debug keys F1/F2/F3/F4/Escape). Its issue body already
carries the whole recovered map — the `DAT_006cfce9` gate, the DIK codes and each key's effect with
its address in `FUN_00634f60` — so the worker was told to spend its time on implementation and proof
rather than re-derivation. Two things it must not hand-wave: the per-fighter AI-enabled flag is
**new state** (the port has no `+0x860` counterpart, because the bot brain simply runs for COM slots),
and #49's report found `--lock-taps` never reached the front-end battle's human panel at
`--screen=battle`, so scripted function keys may not land either — it must actually run whatever
mechanism it claims.

**#2 is not dispatchable and needs the human's decision.** Its own body says the work is *"each glyph
needs a hand pass in an SVG-capable image editor"* — the pipeline (`trace_hud.py`, the 4x-upscale +
Gaussian + re-threshold fix) is done and committed, and what remains is **manual art**, which a
subagent cannot do honestly. The decision is whether to (a) do that hand pass, (b) accept the traced
outlines as-is with their known flat terminals and staircased diagonals, or (c) drop the vector-HUD
goal and keep the bitmap atlas at the shipped resolution. **Not started pending that call.**

## Round 16 — #44 merged (the select entry's flash)

**The issue's lead was a red herring.** `DAT_006cfba0`/`(&DAT_006cfba4)[…]` are the participating
**human slot list** (`FUN_0040d130:108-111` appends each slot whose controller is a pad), not a count
and an alpha list. The real flash is the select scene's own draw tail — `FUN_0040b2b0:466-475`
(research) / `:480-489` (live, same body) — two full-screen 800x600 quads via
`FUN_00651860(0,0,800,600, alpha8 << 24 | 0xffffff)`: **white**, `(tick-25)*24+15` over 25..34 and
`(55-tick)*12+15` over 35..54, so 30 ticks with a single fully-opaque tick 35.

**And mode 2 is a cell selection, not a tint**, argued from both sides: `FUN_00655830` has no colour
parameter at all (its `param_4`/`param_5` appear only in the UV block, in **both** binaries), *and*
cell (2,1) of `data/select/i00.cnv` decodes as **100 % opaque white** where the other five cells are
coloured chibi frames.

**Verified by the coordinator on the merged tree**: ctest 53/53; the peak frame's canvas mean is
**254.73/255**; the **settled frame is byte-identical to the same capture on `main`**
(`md5 300f8666c675b2f23a602c719d6c61fb`) while the peak differs (`2a9d52fa…`) — so the change is real
and confined to the flash window, and both hashes reproduce the worker's reported values exactly. The
measured alpha matches the recovered curve at **delta 0.00/255 on every tick 20..59**. All four gate
ladders and final captures unchanged.

**Reported, out of scope**: the scene-internal page cross-fade (`FUN_0040b1f0:23-24`, a black quad
from `(byte)(scene+0x3c42) << 24` ramped ±15/tick, committing only at exactly 0xff) is a **different
mechanism** from the `ScreenStack` 25-frame `(n*10+5) << 24` fade the port uses to cover the page
swap — different timing *and* different alpha. Worth its own issue if exactness is wanted there.
Also: `data/select/i00.cnv` stores identical art in cells 0, 2 and 4, which is why several distinct
scene ticks render byte-identical frames.

## Round 17 — a worker was lost, and the process rule that prevents it

**#50's first agent was stopped before it finished and left no closing message.** Its worktree's
reflog showed `reset: moving to HEAD` and the tree was clean with no commit and no stash — so its
edits were discarded and the work died with the agent. Nothing was recoverable. It was redispatched to
a fresh agent (`fb513d2c`) with two process rules added to its brief:

1. **Commit incrementally** — the moment one defect is diagnosed and fixed, commit it. Several small
   commits beat one perfect one that never lands.
2. **Never `git reset --hard` / `git checkout -- .` / `git stash` without a named stash first.** To
   prove a test fails pre-change, build the old variant from `git show <base>:<path>` in `/tmp` (what
   every other worker did) rather than destroying the working tree to get a comparison.

**The generalisable version, worth keeping**: a worktree is the only copy of a worker's uncommitted
work — the coordinator cannot recover it. Every brief in this batch already said "commit and report";
this is the first time the absence of an *intermediate* commit actually cost work. Briefs for
long-running issues should say **commit as you go** explicitly, not just "commit before reporting".

## Round 18 — #48 merged (the recovered in-battle debug keys)

F1 restore HP + balloons, F2 freeze COMs, F3 re-enable exactly the COM slots, F4 fill the metres,
Escape leave via #15's own path. ctest 53 → **54**. Merged clean (`e2eb5f9` → `e6d9923`).

**Verified by the coordinator**: with `--debug-keys=f2@400,f3@900` the COM's total displacement is
**4054** units against **6225** in an identical control — what freezing it for the 500 ticks between
the two keys should cost. The worker's `moved=0.00` figures were the per-window trace, not the total;
worth remembering when reading their tables.

**Three implementation notes worth keeping**: the AI enable flag is **new state** on `gameplay::Match`
(the port had none — the bot brain simply ran for COM slots), and a cleared flag feeds the COM a
zeroed `PlayerState` and skips its brain, which is the original's memset input block. F1's two scene
counters needed no invention: `scene+0x12b0`/`+0x12bc` are the two sides' **balloon percentages**.
The keys are sampled once per **simulation** tick at the top of `tickMatch`, not in the read-only
`updateMatchViews` pass, so captures reproduce them. `--debug-keys=KEY@TICK` had to be **added**
because #49 established that scripted input never reaches a front-end battle's human panel.

**Latent trap reported, not fixed**: `Match::step(nullptr, …)` **skips the fighter's whole state
machine**, so a fighter with no input keeps its locomotion state and plays its run animation in place.
The F2 freeze therefore feeds a zeroed `PlayerState` rather than `nullptr`. Anyone who later means
"no input" literally will hit this.

## Round 19 — dispatched #39 (the live-path verification blind spot)

**The most consequential issue left in the queue**, because it is about the verification stack the
rest of this batch relies on. The camera defect that survived twenty-odd issues lived entirely in the
**live interpolation path**: captures set `app.matchAlpha = 1` (D9's one-update-per-frame recipes) and
`buildFrameViews` renders `glm::mix(previousEye, camera.eye(), matchAlpha)` — with alpha 1 the mix
returns the current camera unchanged, so captures were byte-perfect while a played battle swept the
camera every frame. Anything living in presentation-time interpolation, per-frame smoothing, alpha
blending or input-driven per-frame state is invisible to the whole stack.

The worker was pointed at option 1 (a fractional-`matchAlpha` headless mode plus a smoothness
assertion) and at `lock_switch_camera_test.cpp` as the model for asserting on live-path state without
a GPU. Two things were made non-negotiable:

1. **The detector must be shown to fire on the real defect** — reconstruct it on a scratch copy and
   paste the failing run. A detector that has never fired is worthless.
2. **"Off stays byte-identical"** — this changes the machinery that produces every other issue's
   evidence, so a perturbation would corrupt the whole batch's baselines. Prove it on at least two
   recipes including a scripted gate.

**Standing note for the rest of the batch**: `--debug-keys=KEY@TICK` (#48) and now a
fractional-alpha mode are both examples of the same thing — *the port needs headless ways to exercise
paths that captures bypass*. When a future issue's evidence looks flat, that is the first place to
look.

## Round 20 — #33 merged, and the coordinator's own premise was the wrong one

I briefed #33 with the hope that the simple route would be available: "11 is the original's
**capacity**, not a claim that anything fills it", so the worker could prove single-instance
equivalence and keep one draw. **That was false, and the enumeration the brief asked for is what
disproves it.**

`FUN_004205e0`'s loop draws once per matrix in a fixed eleven-slot array at `player+0x38c`
(stride `0x40`). `FUN_0041e180` resolves eleven **fixed bone names** once per character;
`FUN_00421010` copies them in every frame with a blind `MOVSD.REP` and **no presence test**; the draw
walks them all. Across the install: of **139** models, **92 carry all eleven** attach points and
**47 carry none — none is partially equipped**. The array is always fully populated when the draw
runs. Verified on the merged tree: the enumeration reproduces exactly, and the no-aura capture is
byte-identical to `main` (`md5 dc1bdcf852285040bc97c7540a8e5c03`). With the aura live,
`effectDrawsAtExit` goes 10 → 40 beside seven live hit cards — `40 = 7 + 11 × 3`, exactly ten extra
instances.

**The lesson, which applies to the coordinator as much as to the workers**: I wrote the convenient
hypothesis into the brief as if it were a finding ("11 is capacity"), and it would have produced a
false documentation commit if the worker had trusted me. Several issues in this batch arrived with a
wrong premise and the workers corrected them; this is the first time the *brief* was the source.
Ask for the enumeration first and let it decide the route, rather than naming the route and asking
for an enumeration that supports it.

**Also reported**: six of the seven shipped attachment models load and are **never drawn** (only
hypermode draws one) — the muzzle-flash, blue-hit and downed states have no attachment at all, and
each would now need the same per-point placement. That is #17's spawn side.

## Round 21 — #39 merged: the verification stack now sees the live path

**Option 1**: `--match-alpha=<0..1>` plus a device-free smoothness test asserting on **frame-view
state, not pixels** — it drives the product's own composition (fixed-step clock → `tickMatch` →
`buildFrameViews`), so it runs in CI with no GPU, window or game data. ctest 54 → **55**.

**Verified by the coordinator by reconstructing the defect**, not by reading the report: moving the
`previousEye`/`previousTarget` advance back after `camera.update()` and gating it on
`matchFrame == 1` reproduces the reported numbers **exactly** — `1282.8557`, `763.6046` and
`1228.3241` units against a `5.000` limit, `FAIL (25 checks, 3 failed)` — while the camera's own eye
and the followed fighter stay exactly static. Restoring the file returns `ok (25 checks, 0 failed)`.
The detector fires on the real defect.

**The design decision that makes it a real check rather than a cosmetic one**:
`buildFrameViews`' exact-camera shortcut was re-keyed from `capturing` to `app.matchAlpha == 1.f`.
Without that, a fractional-alpha capture would still have drawn the camera's own view matrix — a
check that could never have failed.

**Standing consequence for every later issue**: **a capture is not a live run** (now in `AGENTS.md`
and `decisions.md` D9). The capture path pins the presentation blend to 1, so anything living in
presentation-time interpolation, per-frame smoothing, alpha blending or input-driven per-frame state
is invisible to captures. When evidence looks flat, that is the first place to look.

## Round 22 — #50 and #34 merged (57 tests), and a new defect filed

### #50 — the pause overlay (the human's screenshot)

**Defects 1 and 2 were one bug, and the human's lead held with a correction to the mechanism.** The
white quad *is* the targeting image, but drawn by the **pause overlay's own pass**. `beginFrame` does
clear the quad queue, so the overlay never adopted the HUD's quads — what every pass shares is the
**vertex buffer**: each `render()` writes it at offset 0 and all of a frame's writes complete before
its single submission, so a pass reads the **last** write plus the tail of the longest earlier one.
The overlay pushed 546 quads and the HUD 32, and the HUD's **first** quad is the first fighter's
reticle cell — so the overlay's dim rectangle drew as that reticle textured with the 1×1 white
fallback. The #17 and #21 leads were ruled out with data (reticle suppression removes it; `--no-toon`
reproduces it byte-for-byte; the run reports `fx events=0`).

Fixed by giving the overlay its own `SpriteRenderer` (`App::pauseUi`). **Verified by the coordinator**:
ctest 57/57; paused-frame near-white pixels fall to 2660 against the pre-fix block alone at 10890; the
unpaused 4-view capture is byte-identical to `main`; and the frame shows the panel, the legible rows
and no white block. The layout is a labelled **port rule** (the original's pause has no readable menu).

### New defect filed: #56 — the aliasing corrupts every multi-view UI frame

**The same buffer aliasing is not pause-specific.** In a 4-view frame the separator pass (written
last) overwrites the first 8 vertices of every HUD pass, so **each view's first two quads — fighter
0's reticle — are replaced by separator bars**, and every cell's remaining quads read whichever view
wrote last. `hud_cell_scale.py` structurally cannot see it: every pass pushes its probe markers at
identical coordinates. Fixing it properly (per-render vertex regions) **changes unpaused split-screen
pixels**, which is why it is its own issue rather than a rider on #50.

### #34 — the muzzle slot, and a premise that dissolved

The issue asked which firing state maps to which muzzle slot. **There is no tier→slot relation in the
original**: the slot comes from the fighter's per-**slot** fire-mode byte `+0x318`, set once
(`FUN_0063c2a0:267-277` dispatches on it alone; the story/team setup fills CPU slots with `rand()%3`).
So one fighter shows one muzzle model for a whole match. The port has no `+0x318`, so the slot stays a
**port rule, now labelled with the reason** rather than an unproven guess. Verified: ctest 57/57, the
capture byte-identical, and `effect_catalog_test` pins the three muzzle slots against the shipped
`TextureFilename` blocks.

## Round 23 — a correction to #33's report, and the next dispatch

**#33's claim that "six of the seven shipped attachment models load and are never drawn" is wrong for
the muzzle flashes, and #34 measured it.** `spawnAttachment` pushes a live card and `placeFxCards`
turns it into an instance, so the muzzle flash **is** drawn once at the shot point: with a temporary
trace, a scripted shot fires `spawnAttachment slot=0 asset=36` (`data/aura/00.X`) and the run reports
`spawned=2 … peak=2/128, effectDrawsAtExit=2`, while suppressing that one spawn gives
`spawned=1 … effectDrawsAtExit=1`.

The measured truth is: **three drawn via the muzzle card** (00/01/05), **one via the hyper aura** (03),
**three loaded and never drawn** (02 blue hit, 04 bucket, 06). What is genuinely missing is the
**placement**: the original draws the attachment on the fighter's eleven rig matrices
(`0x420711-0x420770`), while the port's muzzle and blue-hit cards are **world-space spawns**. So the
gap is where it is drawn, not whether — and a slot map nothing consumes is not the same deliverable as
"the flash appears at the right slot". Both are #17's spawn side.

**Dispatched #56** (the shared-vertex-buffer aliasing: in a 4-view frame the separator pass overwrites
every HUD pass's first 8 vertices, so each view's first two quads — fighter 0's reticle — are replaced
by separator bars) and **#32** (the in-flight projectile visual: recover the shot-draw path or label
the port rule with the reason, following #34's precedent). #32 was given the hypothesis worth testing
early — that an in-flight projectile may be drawn by the *same* rig-attachment path as the muzzle
flash, which would make it a rig-attached effect rather than a travelling model.

## Round 24 — max subagents raised to 5; #36 and #35 dispatched

The human raised the concurrency cap to **5** and asked to speed up, so two more went out alongside
the three in flight (#30 the COM tick cost, #32 the in-flight projectile visual, #56 the vertex-buffer
aliasing):

- **#36** — one config file owns the install path. The whole coordinated change was already specified
  by #22 in the issue body (schema v3 + additive migration, `installDir`, precedence after
  `$DAYBREAK_INSTALL`, delete `install.conf` and its writer). The headline symptom is that the binary
  cannot see the launcher's choice, so a direct run re-discovers from scratch.
- **#35** — **actually running** the Windows and web targets, which the project has only ever
  compiled. This one is doable on this box: `wine` **is** installed at `/usr/bin/wine`, the
  `computer-use` skill drives a GUI in an **isolated headless KWin session** (so the user's desktop is
  untouched), and `agent-browser` covers the web side. The acceptance criterion's own phrase is
  "honestly scoped", so a target that reaches the title screen and crashes on battle is a *result*,
  and a target that cannot run at all is also a result — and the brief requires correcting any doc
  sentence the runs contradict.

**Standing observation for the batch**: three of the highest-value issues left (#35, #39 done, #56)
are not about game behaviour at all — they are about the project *believing* it verified something it
did not. #39 was "captures cannot see the live path"; #35 is "compiled is not executed". Both were
surfaced by other work rather than by the checklist.
