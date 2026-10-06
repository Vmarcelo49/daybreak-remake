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
| #18 (+#31) | animation | `feat/issue-18-guard-jump-sets` @ `dbd-worktrees/issue-18` | dispatched | in progress | — |
| #29 | verification | `fix/issue-29-input-devices` @ `dbd-worktrees/issue-29` | dispatched | in progress | — |
| #26 | animation | — | **re-scoped on GitHub** (per the human) | issue edited |
| #38 | renderer | — | deferred to last (per the human) | — |
| #41, #44, #43, #47, #40 | frontend | — | next wave | — |
| #49, #50, #2, #21, #32, #33, #34, #27, #51, #48, #30, #35, #36, #4, #39, #24, #3 | — | — | queued | — |

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
