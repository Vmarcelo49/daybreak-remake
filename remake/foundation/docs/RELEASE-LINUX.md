# Offline Linux versus — release roadmap and acceptance gate (issue #24)

> **What this is.** The ordered path from the tree as it stands to the claim
> *"offline Linux versus is delivered"* — launch the packaged game against the
> user's own install, select characters/weapons/stage, play 1v1 or 2v2 with
> humans and/or COM, get correct results, start another round, each local human
> with their own view and HUD. It owns the **order**, the **dependencies**, the
> **list of load-bearing checks** and the **list of what the gate does not
> cover**. The runnable gate itself — commands, transcripts, tick ladders,
> hashes, timings — is [`RELEASE-CHECKLIST.md`](RELEASE-CHECKLIST.md) (issue
> #23); this file links to it and does not restate its evidence.
>
> **Why this file, and not a section of an existing one.** (a)
> `RELEASE-CHECKLIST.md` is an *evidence record*: dated transcripts, measured
> hashes, the shape of a run. A forward-looking plan inside it would mix "what we
> intend to do" with "what was measured", which is the failure this batch hit
> repeatedly — stale claims living inside the document that is supposed to be
> the evidence. (b) [`ROADMAP-PENDING.md`](ROADMAP-PENDING.md) is the
> per-subsystem engineering handoff (2,000+ lines of dated sections, some
> superseded by later updates in the same file), and its own *"Release gate —
> issue #23 validation update"* already summarises the gate's outcome; a release
> ordering there would be buried and would duplicate that section. (c) A third
> file lets the checklist stay a measurement log and this file stay a plan,
> each linking to the other without owning the other's content.
>
> **Snapshot stamp.** Every number in §1.1 was measured **2026-10-06** in the
> worktree `../dbd-worktrees/issue-24` (branch `docs/issue-24-release-roadmap`,
> base `bfd44a9`), with the game install reachable through the worktree's own
> `Higurashi-Daybreak` symlink — read, never renamed, moved or hidden. Anything
> not measured in that pass is labelled with the document that measured it and
> when.
>
> **Two dates, on purpose.** §1.1 is the audit pass on this branch's base;
> **§1.2, §3 and §4 are written against the merged state, `main` @ `3d763ae`**,
> which this branch's base predates. Where a cited section (the checklist's
> §5.2, the `--allow-problems` flag, `frontend-2v2-longrun.txt`, the 61-test
> count) does not exist in this branch's own tree, that is why: it arrives with
> the merge. The canonical, re-runnable numbers stay in `RELEASE-CHECKLIST.md`;
> when this snapshot and a fresh run disagree, **the fresh run wins** — that is
> this file's own rule, and the reason the numbers carry a date.

## 1. The issue's starting point is stale — the state, re-derived

Issue #24's *"Verified starting point — 2026-10-04"* describes a tree that no
longer exists. What it says, and what a run today says:

| Issue #24 (2026-10-04) | Measured 2026-10-06 | Evidence |
|---|---|---|
| "All **24** Linux CTest tests passed (35.15 seconds)" | **58 registered, 58 passed, 0 skipped, 143.68 s** on this branch's base; `main`'s §2 re-measured **61** after issue #4 added three delivery suites, so the merged denominator is 61 | `ctest --test-dir remake/foundation/build/linux` (this run); `RELEASE-CHECKLIST.md` §2 |
| "asset-backed 2v2 is still **unverified** and its presentation retains two-player assumptions" | four-fighter 2v2 runs **three rounds and four views** with per-participant HUD/VS/results and a four-row report, `RESULT: ok` | §3.3 + the four-player gate; this run (both green, digests below) |
| "No new asset-backed/hardware session was run for this audit" | four scripted capture runs, the 208-cell sweep, the package and a **windowed Wayland** battle were run today | §1.1 below |
| "Execute in this order" #5–#23 | on GitHub the list is closed except **#18** and **#21** (checked today): #18 landed (Guard/Jump mapping and #31's airborne row with it) but carries the selector residuals; #21's row 0 landed and rows 1–2 are open. Beyond the issue's list, **#26** is open and re-scoped to the handler-family remainder | `gh issue list --state open`; `docs/agents/issue-status-2026-10-06.md`; `ROADMAP-PENDING.md` C1 |

What works today, each with the command or doc that proves it:

| Claim | Proof |
|---|---|
| title → selection → stage settings → VS/countdown → live battle → results → selection, 1v1 and four-fighter 2v2, one camera + HUD per human controller | §3.1/§3.2/§3.3 and the four-player gate; this run reproduced all four ladders and final captures |
| COM fighters run the recovered decision state (not the old sparring policy) | `bot_brain_test` (in `ctest`); `ROADMAP-PENDING.md` *"COM decision state and tactics"* |
| fixed 64 Hz simulation independent of render rate; bounded catch-up | `fixed_step_test`; checklist §5 (30/60/144 Hz rows); D9 in `remake/docs/decisions.md` |
| KO/overkill/respawn/timeout/team victory, simultaneous outcomes | `match_economy_test`, `round_rules_test`; `ROADMAP-PENDING.md` *"KO, Overkill, respawn and victory rules"* |
| battle pause / resume / return to selection, focus-loss auto-pause | `battle_pause_test`, `pause_overlay_layout_test`, `pause_overlay_panel`; D11 |
| every legal character+weapon selection launches and runs a match | `weapon_definition_test` — measured today `747 checks, 0 failed, 0 skipped`, `all 46 legal selections ran a match` |
| packaged launch finds the user's install and its own libraries/fonts | `scripts/package_linux.sh` + `tests/launcher_test.sh` (measured today, 38 checks, 0 failures); packaged run below |
| a **capture is not a live run**, and the live path has its own gate | D9; §3.5; `live_camera_smoothness_test` — measured today 25 checks, 0 failed |

The proof column names a test or a doc. Where it names a test, that test passed
today inside the 58/58 suite, but its assertions were **not** re-read for this
document: the sentence beside each test is repeated from the doc named with it,
not re-derived from the test body.

### 1.1 Measured in this pass (2026-10-06)

Commands are from `remake/foundation/`; the install was reached as
`--install=../../Higurashi-Daybreak`. Wall times are the demo's own summaries on
a shared box; one sweep ran concurrently with the windowed row, so those two are
upper bounds, not benchmarks — the reproducible numbers are the ladders, the
digests and the logic tick rate.

| Run | Result |
|---|---|
| `ctest --test-dir build/linux --output-on-failure` | `100% tests passed out of 58`, 143.68 s, install present, none skipped (this branch; `main`'s §2 says 61 — issue #4's three delivery suites) |
| §3.1 `--local-players=2 --script=tests/scripts/frontend-1v1-rematch.txt --frames=15500` | `RESULT: ok`, 15500 ticks in 7.020 s; ladder `0/34/446/4382/4984/5310/9246/9848/10174/14110/14712`; roster `1P Rena 0` vs `2P Keiichi 1`; digest `8cc49e6c…` |
| §3.2 `--local-players=1 --script=tests/scripts/frontend-com-rematch.txt --frames=15500` | `RESULT: ok`, 15500 ticks in 15.219 s; the same ladder tick-for-tick; one view, `1P Rena 0` vs `COM Chie 0`; digest `57044cfb…` |
| §3.3 `--local-players=4 --script=tests/scripts/frontend-2v2-rematch.txt --frames=15500` | `RESULT: ok`, 15500 ticks in 19.515 s; the same ladder; four views, `Rena 0`/`Keiichi 0`/`Rika 0`/`Mion 0` as owner/ally/enemy/enemy; digest `8cc49e6c…` |
| four-player gate `--local-players=4 --script=tests/scripts/frontend-4p.txt --frames=9600` | `RESULT: ok`, 9600 ticks in 7.355 s; ladder `0/34/446/4382/4984/5584/9520`; digest `14305bc9…` |
| `./build/linux/weapon_definition_test` | `WEAPON_DEFINITION: ok (747 checks, 0 failed, 0 skipped)` and `all 46 legal selections ran a match ok` |
| `./tests/launcher_test.sh ./package/daybreak` | `launcher_test: 38 checks, 0 failure(s)` |
| `python3 tests/showcase.py --check --out-dir <dir>` | `asset check: 16 character(s) x 13 stage(s) -> 208 runs`, **`165 pass, 43 problem(s)`** — the documented baseline exactly (30 cells on stage05/stage15, 11 on `kasai`, 2 overlapping), so no new untextured draw; the exit-status contract is §3.1 check 9 |
| `./scripts/package_linux.sh` then `--no-build` again | `daybreak-0.1.0-linux-x86_64.tar.gz`, 19,548,061 B, sha256 `0eba2b9d…` **identical on both runs** (determinism); the script's own `== no game data ==` and `== runtime libraries (ldd) ==` checks pass |
| packaged `foundation_demo`, headless, `--screen=title --frames=300` against the install | `RESULT: ok`, adapter `AMD Radeon RX 9070 XT (RADV GFX1201) [Vulkan]` |
| packaged `daybreak --install=<bad path>` with empty `HOME`/XDG dirs | exit 1, `No game data in "…"`, then the search list and the exact command to run |
| `./build/linux/live_camera_smoothness_test` | `LIVE_CAMERA_SMOOTHNESS: ok (25 checks, 0 failed)`; the fractional-alpha check reads `expected 16.1214, got 16.1214` on a 32.243-unit two-tick gap |
| §3.5 companion recipe `--match-alpha` (stage21, Rena 0 vs Mion 0, 3 frames at 400x400) | no flag and `--match-alpha=1` are byte-identical (`f80d0368…`, the prefix §3.5 quotes); `--match-alpha=0.5` moves **118,424 of 160,000 pixels (74.0 %)**, matching §3.5's pixel figure — the same run differs in 324,683 of 480,015 **bytes** (67.6 %), a different metric; `--match-alpha=2` is rejected |
| windowed live run, own `XDG_RUNTIME_DIR` + nested `dbus-run-session -- kwin_wayland --virtual --xwayland` (isolated; no window on the real desktop), `--screen=battle --local-players=2 --script=tests/scripts/split-two-human.txt --frames=1500` | `video driver : wayland`, `surface : 960x540 … fifo=yes`, `present mode : Fifo(vsync)`, `1500 frames in 28.468 s`, `delta avg 18.966 ms (52.7 fps)`, `logic 1815 ticks, 64 Hz`, `RESULT: ok` |
| the committed §3.3 script at `--frames=40000` | **three** `match: round over` lines on this branch's base — §6's prolonged-stability row then named a script that was not in the repo. Closed on `main`: the committed `frontend-2v2-longrun.txt` reaches **five** rounds in 40000 frames, and §6 says why eight is not reachable by extending the taps |

Two further passes on the same tree reproduced every load-bearing number here:
`ctest` 58/58 again (115.68 s), and the four gates again with the **same digests**
(`8cc49e6c`, `57044cfb`, `8cc49e6c`, `14305bc9`) and the same ladders. Only the
wall times move with machine load — across the three passes: 1v1 5.5–7.0 s, COM
12.8–15.7 s, 2v2 10.8–19.5 s, 4p 7.1–8.6 s — which is exactly why the table's
"reproducible numbers" are the ladders, digests and tick rate, not the seconds.

Repeated from the docs, **not** re-measured here: the data-free skip shape
(§2: the registered count with eight `Skipped` — 58 on this branch's base, 61 on
`main` — producing it would require hiding the
shared install, which this work is forbidden to do), and every Windows/web claim
(§4; those are issue #35's runs, cited from `RELEASE-CHECKLIST.md` §5.2 on
`main`, which this branch's base predates).

### 1.2 What the audit found, and what `main` has since fixed

The audit pass (§1.1) found ten inconsistencies. **All ten are fixed on `main`**
(`ef63e63`, `81314ff`, the issue #35 merge `b21f79a`, and the issue #4 merge
`ee75075`), which is why this section is a ledger rather than a work list: it is
kept so the corrections have a provenance, not because anything here is open.
The mapping:

| Finding (audit pass) | Where it stands on `main` |
|---|---|
| `docs/status.md` said 50 ctest tests | now **58** — and stale again for a different reason, see the residuals below |
| checklist §4.1's `743 checks` (and `ROADMAP-PENDING.md` G3's copy) | both say **747**, the measured value |
| checklist §3.3's round-1 outcome line quoted `grade 3 margin 0 … 00-02-3.txt` | re-measured to **`grade 4 margin 21 … 00-02-4.txt`**, the value this pass and a byte-identical re-run both produce; round 2 (`1-4 grade 3 margin 1`), the ladder, the roster and the final capture already reproduced |
| checklist §6's two 1v1 wall times (10.690 s vs 5.273 s), unlabelled | the row now reads **`10.690 s (pre-#30; 5.273 s after it)`** |
| `ROADMAP-PENDING.md`'s COM "Open" (chie's `data/item/014.dat` blocks a four-fighter run) | **closed 2026-10-06** in place, citing this audit's `COM Chie 0` and four-fighter runs |
| `decisions.md` D6's "asset-backed four-fighter … remains unverified" and two-fighter VS/result | **superseded 2026-10-06** in place, with the §3 gates named as the evidence |
| "three renderer options" in `AGENTS.md`, `package/README-LINUX.md` §4, `ROADMAP-PENDING.md` E3 and `remake/foundation/README.md` | those four now say **two** (row 0, toon, is live and persisted); three stragglers survive, see below |
| checklist §6's prolonged-stability row named an uncommitted script (this pass measured three rounds from the committed §3.3 script at `--frames=40000`) | the committed **`tests/scripts/frontend-2v2-longrun.txt`** is the row's recipe, re-measured after #32: **five** rounds, `peak=4/128`, `dropped=0`, with §6 stating why eight is not reachable by extending the taps |
| checklist §5's environment matrix was a description, not a recipe (a naive `kwin_wayland` launch dies silently and leaves its socket behind) | §5.1 now carries the working recipe: a private `XDG_RUNTIME_DIR`, `setsid dbus-run-session -- kwin_wayland --virtual --xwayland`, and the healthy-run lines to expect |
| historical-only counts (24/25/26/30/31) read as current | unchanged and correctly dated; the `24` in `ROADMAP-PENDING.md` is still the weak case (no date of its own) |

**Residual inconsistencies on `main`, still live and not fixed here** (each is a
one-line change; they are listed so the next reader does not re-derive them):

1. **`docs/status.md:29` says 58 while §2 and `AGENTS.md` say 61.** The status
   doc was fixed from 50 to 58 and then issue #4's three delivery suites landed,
   so it is stale by three again. Its own sentence points at §2, which is why it
   is survivable — but it is a dated, current-tense count.
2. **Three "three renderer options" stragglers**: `README.md:57`, and
   `remake/docs/game-spec.md:270` and `:272` (the latter says "the three renderer
   toggles stay unavailable"). The Options screen marks rows 1–2 `UNAVAILABLE`;
   row 0 is live.
3. **Checklist §4.2's printed command cannot exit 0 on its own documented
   baseline.** `python3 tests/showcase.py --check` exits 1 with 43 problem cells
   (the tool's default `--allow-problems=0`); the tool has the right flag
   (`--allow-problems=43`, added for exactly this) but §4.2 and §8 still print the
   bare command. Gate check 9 below uses the flag.
4. **Checklist §6 still carries two paragraphs about "the eight-round row"**
   ("was not re-run: its recipe needs the operator's extended script" and "The
   eight-round row's numbers predate that change") after the row itself was
   re-measured as a **five-round** run with a committed script. The leftovers
   contradict the paragraph above them.

## 2. The ordered roadmap

Two bands. **Band A is the delivery path** — the sequence that makes the
documented gate pass and the claim honest. **Band B is product work the gate's
own acceptance criteria name but the scripted checks cannot see**; each Band B
item says whether it blocks the gate. The issue's rule — *"any visual defect that
prevents reading combat should be promoted into the playable milestone"* — is the
only thing that moves an item from B to A, and it is a judgement for the
operator, not something these checks decide.

### Band A — the delivery path

**A1. Re-establish the baseline.** `./remake/foundation/build.sh deps` (once per
worktree — `third_party/` is hardlinked, and a dependency fetched by one branch
exists only there; this worktree needed it for issue #40's `pl_mpeg.h`), then
`./remake/foundation/build.sh linux`, then
`ctest --test-dir remake/foundation/build/linux --output-on-failure`.
*Depends on:* nothing. *Done when:* `100% tests passed` out of the registered
count, none `Failed`; read ctest's own summary, not a number in a doc.
*Evidence:* checklist §1–§2; measured 58/58 on this branch's base, and the
registered count on `main` is 61.

**A2. Prove the packaged launch path.** `./scripts/package_linux.sh`, then
`./tests/launcher_test.sh ./package/daybreak`; then run the packaged binary
against the user's install from the staged directory, and run the launcher with a
bad `--install=` path under an empty `HOME`/XDG to see the failure message.
*Depends on:* A1 (the package stages the build). *Done when:* the script's own
assertions pass (no game data; `ldd` resolves every library inside the package or
from the base system; two consecutive runs give the same digest),
`launcher_test` reports 0 failures, the packaged binary reaches `RESULT: ok` with
the install, and the bad path prints the search list and exits non-zero.
*Do not* compare the tarball digest against the one checklist §1 quotes: it is a
function of the built binary and moves with every merge. Compare a run against a
second run of the same tree. *Evidence:* checklist §1; `package/README-LINUX.md`.

**A3. Run the four scripted gates.** §3.1 (two humans, 1v1, three rounds), §3.2
(one human + COM, three rounds), §3.3 (four humans, 2v2, three rounds) and the
four-player front-end loop. All four are **capture runs**: one logic tick per
rendered frame, which is what makes the script ticks exact and the run
reproducible. *Depends on:* A1. *Done when:* each run ends `RESULT: ok` on its
documented tick ladder with its documented roster and its documented
final-capture sha256 prefix — and, for §3.3, reading the ladder and the digest as
the stable evidence rather than the outcome line, which follows combat state
(§1.2's ledger). *Evidence:* §3, §8; measured in this pass: 7.0 s + 15.2 s +
19.5 s + 7.4 s of wall time on a loaded shared box.

**A4. Run the two asset sweeps.** `./build/linux/weapon_definition_test` (§4.1:
all 46 legal selections launch and run a match) and
`python3 tests/showcase.py --check --allow-problems=43` (§4.2: the character ×
stage texture matrix). *Depends on:* A1. *Done when:* `0 failed` and `0 skipped`
with the install, and the sweep shows **no new untextured draw** beyond the
documented install gaps — 43 problems is the documented baseline and the flag is
the count contract: more than 43 exits non-zero as a regression. The pass/flag
counts are a baseline, not a target. *Evidence:* §4.1, §4.2; G3.
The sweep is the long pole (208 headless runs; five minutes measured in this
pass), so run it in the background while doing A5.

**A5. Do the live-path manual step and the window path.** The one check no
capture owns (§3.5): run `--screen=battle --local-players=2` for ~30 s in a real
session, confirm the camera settles behind the fighter instead of sweeping, then
take a hit and confirm it stays settled. The window/compositor half of that can
be prepared headlessly (A5's own supporting evidence is the nested-KWin run in
§1.1, whose recipe `RELEASE-CHECKLIST.md` §5.1 now carries), but the camera
judgement needs a person watching. *Depends on:* A3 (same tree). *Done when:* the
observation is recorded with the command, the session (Wayland/X11) and the date.
*Evidence:* §3.5; D9.

**A6. Close the hardware and environment rows that need hardware.** Checklist
§5.1 names them: a physical controller walking a panel and a battle with its own
bindings (`--devices`); hardware audio listening (the backend's dummy-device
verification is not listening); a second GPU vendor; an interactive
compositor-side window drag-resize. *Depends on:* A3; runs in parallel with A5.
*Done when:* each row is either **run** (with the transcript) or explicitly
recorded as unavailable — the checklist already carries the "what would settle
it" sentence per row, which is the honest form. *Evidence:* §5, §5.1.

**A7. Keep the corrected docs corrected.** The audit's ten findings are fixed on
`main` (§1.2's ledger), so this step is a maintenance pass, not a repair: close
the four residuals §1.2 lists — `docs/status.md:29`'s 58 vs §2's 61, the three
"three renderer options" stragglers (`README.md:57`,
`remake/docs/game-spec.md:270` and `:272`), checklist §4.2/§8's bare
`showcase.py --check` command (it exits 1 on its own documented baseline; the
tool's `--allow-problems=43` is the fix), and §6's two leftover "eight-round row"
paragraphs that contradict the five-round row above them. *Depends on:* A1–A4
(replacement numbers must come from a measured run, not from this file).
*Done when:* no doc claims a count, hash or timing that a fresh run contradicts,
and every number that moves with the tree says when it was measured.
*Evidence:* §1.2.

**A8. Re-run the whole gate end to end and record it.** Checklist §8 is the
reproduction script; run it in one sitting on the tree that will be released,
record the date, the commit and the transcripts, and only then call the milestone
delivered. *Depends on:* A1–A7. *Done when:* the recorded run is green by §3.2's
criteria and the checklist carries it.

### Band B — product work the gate names but cannot see

Order within Band B follows the data dependencies, not severity: #52 changes what
a fighter faces, which #53's forward motion and action camera read; #54's
per-tier firing animation reads the same move/weapon dimension #53 and #26 touch;
#17's placement is the last consumer.

**B1. #52 — fighters never rotate.** Nothing applies the recovered turn
(`FUN_00421780`'s 8-way yaw + `FUN_0042db10`'s rate-limited shortest-way turn);
the port steers facing-relative instead (`gameplay/bot_brain.h:81` states this as
a port rule). *Depends on:* nothing. *Gate-blocking:* no — rounds finish — but it
is the first candidate for the issue's "defect that prevents reading combat"
promotion. *Done when:* the recovered turn is applied and a capture shows a
fighter facing its movement/attack direction.

**B2. #53 — melee moves are still not data-driven** (no forward motion, wrong
timing, no move effect, no follow-up chain, no action camera; the issue uses
Rena 0). *Depends on:* B1 for the facing/action-camera half. *Gate-blocking:* no
for the round loop; it is the core of the issue's *"every exposed character/weapon
choice has intentional gameplay, not mesh-only variation"* criterion.

**B3. #54 — shots: firing animation per charge tier and the thrown object.**
*Depends on:* the same move/weapon tables as B2; coordinate with #26 so two set
tables are not created. **Premise check before starting:** #54 §2 argues from
issue #17's old port rule that the in-flight visual is "the effect its record
names"; issue #32 (merged after #54 was filed) recovered the shipped model from
the bullet file's own 260-byte header block and retired that rule — the tree now
loads it (`bindShotModels`, `game::shotModelMatrix`, `shotModels=` counters).
The human's ground truth (nata → grenade → two natas) and #32's recovered model
identity must be reconciled on the merged tree before implementing, or the work
will re-fix what #32 fixed.

**B4. #26 and `ROADMAP-PENDING.md` C1's selector residuals.** #26 was re-scoped
to what is genuinely unrecovered: the vtable-`0x20` per-character handler-family
melee hits (40/41/42, the 400-family). C1's own "what is left" adds the
projectile and TagOut selectors, the side/air dash pair (moves 23/24), the
physical identity of the two Guard bits (needs the weapon-word builder) and the
fresh AttackA selector's branch conditions. #18 and #31 landed — Guard binds no
clip *in the source* (`anim_no_selector()` is a report, not a gap) and the
airborne swing plays its own row — so neither should be re-fixed. *Depends on:*
B2/B3 (shared move/set tables). *Gate-blocking:* no.

**B5. #17's residual spawn placement.** #17 is closed, but its own follow-ups
record what is left: three shipped attachment models load and are never drawn,
and the muzzle/blue-hit cards are world-space spawns where the original draws the
attachment on the fighter's eleven rig matrices. *Depends on:* nothing.
*Gate-blocking:* no (the gate's §6 counters are the bound it checks).

**B6. #21 rows 1–2 (shadows, texture resolution) and the visual checks.** Row 0
(toon) landed and persists; rows 1–2 were dispatched to a sibling worktree —
**record that outcome when it lands; do not assume it**. #38 needs a human eye on
the toon/outline captures. #2 (fonts) is **closed** — the owner's call was that
the font the port already uses is the answer — so it is not a work item here even
though `ROADMAP-PENDING.md` E3 still lists renderer controls as an Options gap.
*Depends on:* nothing. *Gate-blocking:* no — the issue says the graphics toggles
do not independently block a basic match.

## 3. The acceptance gate

**The checklist is the canonical text.** The commands below are an index with
the load-bearing flag and the pass criterion; the transcripts, ladders, hashes
and timings live in the cited section, and if this table and that document ever
disagree, that document wins.

### 3.1 The load-bearing checks

| # | Check | Command (from `remake/foundation/`) | Canonical | Pass criterion |
|---|---|---|---|---|
| 1 | Host suite | `ctest --test-dir build/linux --output-on-failure` | §2 | `100% tests passed` out of the registered count — **61** on `main` as of 2026-10-06 (58 on this branch's base); none `Failed`. The asset-dependent tests may be `Skipped` **only** in the documented data-free shape. |
| 2 | 1v1, two humans, three rounds | `./build/linux/foundation_demo --install=<game-dir> --screen=title --local-players=2 --script=tests/scripts/frontend-1v1-rematch.txt --headless --out=/tmp/rel-1v1.ppm --size=1280x720 --frames=15500` | §3.1 | `RESULT: ok`; the documented ladder; `[split]` roster `Rena 0` vs `Keiichi 1`; sha256 prefix `8cc49e6c` |
| 3 | One human + COM, three rounds | same with `--local-players=1 --script=tests/scripts/frontend-com-rematch.txt --out=/tmp/rel-com.ppm` | §3.2 | `RESULT: ok`; the same ladder tick-for-tick; a single view with a `COM` opponent; sha256 prefix `57044cfb` |
| 4 | 2v2, four humans, three rounds | same with `--local-players=4 --script=tests/scripts/frontend-2v2-rematch.txt --out=/tmp/rel-2v2.ppm` | §3.3 | `RESULT: ok`; the same ladder; four views and the four documented combos (`Rena 0`/`Keiichi 0`/`Rika 0`/`Mion 0`); sha256 prefix `8cc49e6c`. **Read the ladder and the digest, not the outcome line** — the grade/margin/script follow combat state. |
| 5 | Four-player front-end loop | `… --local-players=4 --script=tests/scripts/frontend-4p.txt --out=/tmp/rel-4p.ppm --frames=9600` | §3 preamble | `RESULT: ok`; ladder `0/34/446/4382/4984/5584/9520`; sha256 prefix `14305bc9` |
| 6 | **Live-path manual step** | `--screen=battle --local-players=2` in a real session, ~30 s, then take a hit | §3.5 | A person confirms the camera settles behind the fighter and stays settled through a hit. Nothing headless substitutes. |
| 7 | Package + launcher | `./scripts/package_linux.sh` then `./tests/launcher_test.sh ./package/daybreak` | §1 | The script's assertions (no game data; `ldd` inside the package/base system; same digest twice); `launcher_test` 0 failures; the packaged run and the bad-path exit are done too |
| 8 | All 46 selections | `./build/linux/weapon_definition_test` | §4.1 | `0 failed`; with the install `0 skipped` and `all 46 legal selections ran a match` |
| 9 | Character × stage sweep | `python3 tests/showcase.py --check --allow-problems=43 --out-dir /tmp/sweep` | §4.2 | **Exit 0 with 43 problem cells** (the documented install gaps) and no new untextured draw; more than 43 is a regression and exits non-zero. The bare `--check` in §4.2/§8 exits 1 on that same baseline — §1.2 residual 3 |
| 10 | Window path and pacing | the §5 rows (Wayland, X11, 30 Hz, high refresh, fullscreen), recipe in §5.1 | §5 | A window presents with FIFO vsync and the simulation stays 64 Hz regardless of the render rate |
| 11 | Prolonged-match stability | `… --local-players=4 --script=tests/scripts/frontend-2v2-longrun.txt --frames=40000` | §6 | **Five** `match: round over` lines (the committed script's reach; §6 says why eight is not reachable by extending the taps), `RESULT: ok`, no crash, bounded live cards (`peak=4/128`, `dropped=0`) |

Also load-bearing by inclusion: `live_camera_smoothness_test` (§3.5's device-free
gate), `launcher_test`, `weapon_definition_test`'s sweep,
`controller_scene_lifetime_test`, `hud_view_geometry`, `round_rules_test`,
`battle_pause_test` and `device_isolation_test` all run inside check 1.

### 3.2 What "green" means

A run is green when it ends `RESULT: ok`, every expected `[menu] scene:` /
`match: round over` line is present, and the `[split]` roster matches the
scenario. A missing `[menu] scene: result`, a panic, or a `RESULT:` other than
`ok` is a gate failure: **record the exact command and the transcript rather than
re-running until it passes** (§8's own rule).

Recorded, **not** pass/fail: the §6 wall times and peak-card counts (upper bounds
on a shared machine), the §3.6/§3.7 before/after baseline tables (regression
reference), and the tarball digest (it moves with the binary).

### 3.3 What the gate does **not** cover

1. **A played battle's live camera, by eye.** The manual step (check 6) is the
   only thing that covers a window, a compositor, real pacing and a real device;
   until it is done, the camera claim rests on a headless composition test and a
   fractional-alpha capture.
2. **Physical controllers.** Every gate run is driven by a script plus
   `--local-players` synthetic pads. The attached pad has never walked a panel or
   a battle by hand (§5.1).
3. **Hardware audio listening.** The backend runs and the voice/SE counts are in
   the log, but nobody listened on real hardware.
4. **A second GPU vendor.** One RADV adapter was exercised.
5. **Other distributions, older Mesa, other compositors, and an interactive
   compositor-side drag-resize.** Resize was driven through the port's own
   Options list, not a mouse drag on the window edge.
6. **Browser visual parity, hardware browser adapters and macOS execution** —
   unverified; the web evidence is software-WebGPU game-data runs (G1; §5.2).
7. **Windows and the web as *executed* targets.** No longer slot-open, and not a
   clean bill: issue #35 ran both with game data for the first time, and the
   record is `RELEASE-CHECKLIST.md` §5.2 — Windows reached the title and a battle
   and then faulted in a rematch (issue #57); the web reached title and battle
   only on a locally preloaded `/data` rig on software WebGPU, and the `?pack=`
   path cannot at all (issue #58), the scripted browser run never leaves the
   selection screen (#59), and a missing candidate asset floods the console
   (#60). Nothing there is rung 5 of §5.2's ladder (*compiled < launched <
   title < battle < played*), and none of it was re-run here.
8. **Story mode** (not built), **online transport** (#3, a separate milestone;
   D6's LAN lockstep is not implemented), and **3v3/4v4** (an opt-in experiment,
   not a requirement — the match path holds at most four fighters).
9. **Combat fidelity the scripted gates do not measure**: rotation (#52), melee
   motion/timing/chain (#53), per-tier firing animation and the thrown object
   (#54), the handler-family and selector remainder (#26; `ROADMAP-PENDING.md`
   C1), attachment placement (#17), and the two open renderer rows (#21).
10. **Anything else that lives in presentation-time interpolation, per-frame
    smoothing, alpha blending or input-driven per-frame state** beyond what
    `live_camera_smoothness_test` composes (D9; §3.5).
11. **The launcher's GUI window path** (double-click, the dialog when something
    is wrong): `launcher_test` drives a stub binary, and the packaged run in
    §1.1 was headless.
12. **The gate's own reproducibility, now closed on `main` but worth knowing.**
    This pass found two gate rows that could not be re-run from the tree: §6's
    prolonged-stability row named an uncommitted script (the committed §3.3
    script reaches three rounds at `--frames=40000`), and §5's environment matrix
    was a description with no recipe (a naive `kwin_wayland` launch dies silently
    and leaves its socket behind). Both are fixed on `main` — the committed
    `frontend-2v2-longrun.txt` is the row's recipe and §5.1 carries the working
    compositor invocation — so this item is a *rule*, not a gap: see §5's last
    bullet.

## 4. Separate milestones (outside this gate)

| Milestone | Status | Owner |
|---|---|---|
| Story mode | not built; ids registered, builders absent (D6) | separate |
| Browser game-data run / visual parity / hardware adapters | software-WebGPU `/data`-rig run verified (title + battle); visual parity and hardware adapters open (G1; §5.2) | separate |
| macOS execution | never executed (G2); §5.1 names the §5.2 Windows recipe as what would settle it | separate |
| Windows and web **execution** | run for the first time by issue #35; not clean — #57 (Windows rematch fault), #58 (`?pack=`), #59 (browser front end stuck on select), #60 (console spam). Cited from `main`'s §5.2, not re-run here | #35 / follow-ups |
| Web asset delivery | landed 2026-10-06 (merge `ee75075`, issue #4 closed); its three delivery suites are why `main`'s host count is 61. The browser-side gaps it did not close are #58/#59/#60 | #4 (done) |
| Online / rollback architecture | research only; the fixed-tick prerequisite landed with D9 | #3 |
| 3v3 / 4v4 | optional experiment with its own sequence in `ROADMAP-PENDING.md` | not a requirement |

## 5. Rules for whoever runs or edits this

* **Hashes here are sha256 prefixes, not md5.** The two families were mixed once
  and cost a day (§3's note). Label any digest you add.
* **Read `ctest`'s own summary**, never a count in a document — every added suite
  moves the denominator.
* **Do not move a number you did not measure.** If you cite a count, a timing or
  a hash, either run it or point at the doc that says when it was measured.
* **Never hide or rename the game install to produce a data-free count.** Pass a
  bad path on argv instead; the shared install is symlinked by every worktree.
* **A capture is not a live run** (D9). When evidence looks flat, that is the
  first place to look.
* Every battle recipe names a **character+weapon combo**, never a bare fighter.
* **A gate row that cannot be re-run is not a gate row.** If a check needs a
  script, a rig or a command that is not in the repo, either commit it or say in
  the row that it is unreproducible — this file's audit found two such rows
  (§3.3 item 12) and both are fixed on `main`; keep it that way.
