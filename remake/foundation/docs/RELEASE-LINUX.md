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
> **Snapshot stamp.** Every "today" number below was measured **2026-10-06** on
> `main` @ `bfd44a9` (branch `docs/issue-24-release-roadmap`), game install
> present, on a shared machine. The canonical, re-runnable numbers stay in
> `RELEASE-CHECKLIST.md`; when this snapshot and a fresh run disagree, **the
> fresh run wins** — that is this file's own rule, and the reason the numbers
> carry a date.

## 1. The issue's starting point is stale — the state, re-derived

Issue #24's *"Verified starting point — 2026-10-04"* describes a tree that no
longer exists. What it says, and what a run today says:

| Issue #24 (2026-10-04) | Measured 2026-10-06 | Evidence |
|---|---|---|
| "All **24** Linux CTest tests passed (35.15 seconds)" | **58 registered, 58 passed, 112.50 s, 0 skipped** | `ctest --test-dir remake/foundation/build/linux` (§2; this run) |
| "asset-backed 2v2 is still **unverified** and its presentation retains two-player assumptions" | four-fighter 2v2 runs **three rounds, four views, per-participant HUD/VS/results**, `RESULT: ok` | §3.3 + the four-player gate (§3 preamble); this run |
| "No new asset-backed/hardware session was run for this audit" | the gate has run repeatedly since (checklist §3/§5/§6) and was re-run today | §3–§6; this run |
| "Execute in this order" #5–#23 | closed on GitHub except **#18** and **#21**: #18 landed (Guard/Jump mapping, and #31's airborne row with it) but carries the selector residuals; #21's row 0 landed and rows 1–2 are open. Beyond the issue's list, #26 also carries residuals | `gh issue list --state all`; `docs/agents/issue-status-2026-10-06.md`; `tests/scripts/air-attack.txt`; `ROADMAP-PENDING.md` C1 |

What works today, each with the command or doc that proves it:

| Claim | Proof |
|---|---|
| title → selection → stage settings → VS/countdown → live battle → results → selection, 1v1 and four-fighter 2v2, one camera + HUD per human controller | §3.1/§3.2/§3.3 and the four-player gate; this run reproduced all four ladders and final captures |
| COM fighters run the recovered decision state (not the old sparring policy) | `bot_brain_test` (in `ctest`); `ROADMAP-PENDING.md` *"COM decision state and tactics"* |
| fixed 64 Hz simulation independent of render rate; bounded catch-up | `fixed_step_test`; checklist §5 (30/60/144 Hz rows); D9 in `remake/docs/decisions.md` |
| KO/overkill/respawn/timeout/team victory, simultaneous outcomes | `match_economy_test`, `round_rules_test`; `ROADMAP-PENDING.md` *"KO, Overkill, respawn and victory rules"* |
| battle pause / resume / return to selection, focus-loss auto-pause | `battle_pause_test`, `pause_overlay_layout_test`, `pause_overlay_panel`; D11 |
| every legal character+weapon selection launches and runs a match | `weapon_definition_test` — measured today `747 checks, 0 failed, 0 skipped` |
| packaged launch finds the user's install and its own libraries/fonts | `scripts/package_linux.sh` + `launcher_test` (in `ctest`); package assertions below |
| a **capture is not a live run**, and the live path has its own gate | D9; §3.5; `live_camera_smoothness_test` — measured today 25 checks, 0 failed, rendered eye max step 0.0000 units (limit 5.000) |

The proof column names a test or a doc. Where it names a test, that test passed
today inside the 58/58 suite, but its assertions were **not** re-read for this
document: the sentence above each test is repeated from the doc named beside it,
not re-derived from the test body.

### 1.1 Measured in this worktree on 2026-10-06

Commands are from `remake/foundation/`; `<game-dir>` is the user's own install
(the shared install was read, never renamed, moved or hidden).

| Run | Result |
|---|---|
| `ctest --test-dir build/linux --output-on-failure` | `100% tests passed out of 58`, 112.50 s, install present, none skipped |
| §3.1 `--local-players=2 --script=tests/scripts/frontend-1v1-rematch.txt --frames=15500` | `RESULT: ok`, 15500 ticks in 6.729 s; ladder `0/34/446/4382/4984/5310/9246/9848/10174/14110/14712`; roster `1P Rena 0` vs `2P Keiichi 1`; final capture sha256 `8cc49e6c…` |
| §3.2 `--local-players=1 --script=tests/scripts/frontend-com-rematch.txt --frames=15500` | `RESULT: ok`, 15500 ticks in 15.668 s; same ladder tick-for-tick; roster `1P Rena 0` vs `COM Chie 0`; sha256 `b813155d…` |
| §3.3 `--local-players=4 --script=tests/scripts/frontend-2v2-rematch.txt --frames=15500` | `RESULT: ok`, 15500 ticks in 12.496 s; same ladder; roster `Rena 0`/`Keiichi 0`/`Rika 0`/`Mion 0`, four views; sha256 `8cc49e6c…` |
| four-player gate `--local-players=4 --script=tests/scripts/frontend-4p.txt --frames=9600` | `RESULT: ok`, 9600 ticks in 8.613 s; ladder `0/34/446/4382/4984/5584/9520`; sha256 `2483c3aa…` |
| `./build/linux/weapon_definition_test` | `WEAPON_DEFINITION: ok (747 checks, 0 failed, 0 skipped)`, `all 46 legal selections ran a match ok` |
| `./tests/launcher_test.sh ./package/daybreak` | `launcher_test: 38 checks, 0 failure(s)` |
| `python3 tests/showcase.py --check --out-dir /tmp/sweep` | `asset check: 16 character(s) x 13 stage(s) -> 208 runs`, **`165 pass, 43 problem(s)`** — the documented baseline exactly (30 cells on stage05/stage15, 11 on `kasai`, 2 overlapping), so no new untextured draw |
| `./scripts/package_linux.sh --no-build` (twice) | `daybreak-0.1.0-linux-x86_64.tar.gz`, 19M (19,548,061 B), staged 31M, sha256 `0eba2b9d…` **identical on both runs** (determinism); no game data; `ldd` resolves `libSDL3.so.0` and `libwgpu_native.so` inside the package |
| packaged `foundation_demo`, headless, `--screen=title --frames=300` against the install | `RESULT: ok`, adapter `AMD Radeon RX 9070 XT (RADV GFX1201) [Vulkan]`, no `caption font missing` line (that chain is silent on success) |
| packaged `daybreak --install=<bad path>` (empty `HOME`/XDG) | exit 1, `No game data in "…"`, then the search-order list and the exact command to run |
| windowed live run, own `XDG_RUNTIME_DIR` + nested `kwin_wayland --virtual`, `--screen=battle --local-players=2 --script=tests/scripts/split-two-human.txt --frames=1500` | `video driver : wayland`, `present mode : Fifo(vsync)`, `1500 frames in 24.942 s`, `delta avg 16.615 ms (60.2 fps)`, `logic 1595 ticks, 64 Hz`, `RESULT: ok` |
| §3.5 companion `--match-alpha` recipe (stage21, Rena 0 vs Mion 0) | no flag and `--match-alpha=1` are byte-identical (`f80d0368…`, the digest §3.5 quotes); `--match-alpha=0.5` differs in 324,683 of 480,000 bytes (67.6 % — a byte metric; §3.5 quotes 74 % of *pixels*, a different metric on the same recipe) |

Repeated from the docs, **not** re-measured here: the data-free skip shape (§2:
58 registered with eight `Skipped` — producing it would require hiding the shared
install, which this work is forbidden to do).

### 1.2 Where the docs disagree with each other (reported, not fixed here)

1. **`docs/status.md:29`** says the host suite "has **50** ctest tests
   (2026-10-06)". Measured today: **58** — the same number `AGENTS.md` and
   checklist §2 carry. A dated, current-tense claim that is wrong.
2. **Checklist §4.1** quotes the expected tail as `743 checks`, while §2 says
   `747 with the install`. Measured today: **747**. §4.1's quoted block is stale
   (the sweep grew with issue #32's asset-backed half).
3. **Checklist §3.3**'s outcome lines did not reproduce. §3.3's round 1 is
   `side 0 … pair 0-2 grade 3 margin 0 script data/scenario/win/00-02-3.txt`;
   today's is `side 0 … pair 0-2 grade 4 margin 21 script
   data/scenario/win/00-02-4.txt persona 0/0 voice W00-02-10.wav` — same winner
   and pair, and the grade/margin/script/voice move together. §3.3 also quotes
   no round-3 result line, and today's run prints one. §3.1's caveat — *read the
   ladder, not the winner* — describes exactly this class, but it is scoped to
   §3.1; §3.2 and §3.3 quote outcome fields without it. The ladder, settings,
   roster and final captures reproduced exactly.
4. **Checklist §6** gives the 1v1 wall time as **10.690 s** in the table and
   **5.273 s** in the issue #30 paragraph (COM 12.110 s in both). Two passes on
   different machine loads, not labelled as such; the ratio sentence depends on
   the second. Today's runs on a loaded shared box: 6.729 s (1v1), 15.668 s
   (COM), 12.496 s (2v2) — wall time is an upper bound here, not a benchmark.
5. **`ROADMAP-PENDING.md`, "COM decision state and tactics" → "Open"** says a
   front-end four-fighter run cannot start because the auto-fill gives panel 2
   `chie`, whose `data/item/014.dat` fails the gear-up check. Both halves are now
   false: today's §3.2 gate ran `COM Chie 0`, and §3.3 ran a four-fighter 2v2
   through three rounds. The `E8` entry in the same file (46/46 launch) retires
   the cause; the "Open" paragraph was never updated.
6. **`remake/docs/decisions.md` D6** still says an asset-backed four-fighter run
   "remains unverified" and that VS/result presentation "still use two-fighter
   layouts". Both were retired by issue #13 and the §3.3 gate; D6 is dated
   2026-10-01 and its scope ruling stands, but that paragraph does not.
7. **How many renderer options are still unavailable.** `AGENTS.md` ("the three
   renderer options and original result-title/quote fidelity remain open"),
   `package/README-LINUX.md` §4 ("three of the renderer options"),
   `ROADMAP-PENDING.md` E3 ("three renderer controls are unavailable") and
   `remake/foundation/README.md` ("the first three options rows are marked
   unavailable") all say three. The code says **two**: `src/ui/screen_options.cpp`
   prints `UNAVAILABLE` for rows 1 and 2 only (shadows, texture resolution), and
   row 0 is the live toon toggle — issue #21's row 0, done, which is what
   `ROADMAP-PENDING.md`'s own *"Renderer options (issue #21)"* section says
   ("row 0 landed, rows 1–2 open"). The result-title/quote half of the
   `AGENTS.md` sentence is stale too: E5 records it implemented by issue #20.

Two other numbers that look stale but are **correctly dated historical
sections**, not live claims: `ROADMAP-PENDING.md`'s dated updates ("24 Linux
CTest tests", "26", "30") and `BUILD-linux.md`'s "2026-10-04" section ("25
tests"). The file's preamble says later status notes supersede earlier ones, so
they are read as history.

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
worktree — `third_party/` is hardlinked and a dependency fetched by one branch
exists only there), then `./remake/foundation/build.sh linux`, then
`ctest --test-dir remake/foundation/build/linux --output-on-failure`.
*Depends on:* nothing. *Done when:* `100% tests passed` out of the registered
count, none `Failed`; read ctest's own summary, not a number in a doc.
*Evidence:* checklist §1–§2.

**A2. Prove the packaged launch path.** `./scripts/package_linux.sh`, then
`./tests/launcher_test.sh ./package/daybreak`; then run the packaged binary
against the user's install from the staged directory, and run the launcher with a
bad `--install=` path under an empty `HOME`/XDG to see the failure message.
*Depends on:* A1 (the package stages the build). *Done when:* the script's own
assertions pass (no game data; `ldd` resolves every library inside the package or
the base system; two consecutive runs give the same digest), `launcher_test`
reports 0 failures, the packaged binary reaches `RESULT: ok` with the install,
and the bad path prints the search list and exits non-zero.
*Do not* compare the tarball digest against §1's quoted one: it is a function of
the built binary and moves with every merge. Compare a run against a second run
of the same tree. *Evidence:* checklist §1; `package/README-LINUX.md`.

**A3. Run the four scripted gates and the two sweeps.** §3.1 (two humans, 1v1,
three rounds), §3.2 (one human + COM, three rounds), §3.3 (four humans, 2v2,
three rounds) and the four-player front-end loop, then §4.1
(`weapon_definition_test`) and §4.2 (`tests/showcase.py --check`). The four are
**capture runs**: one logic tick per rendered frame, which is what makes the
script ticks exact and the run reproducible. *Depends on:* A1. *Done when:* each
run ends `RESULT: ok` on its documented tick ladder with its documented roster
and its documented final-capture sha256 prefix, and the §4.2 sweep shows no new
untextured draw beyond the documented install gaps. *Evidence:* §3, §4, §8.
(Today the four capture gates cost 6.7 s + 15.7 s + 12.5 s + 8.6 s of wall time
on a loaded shared box; the sweep is the long one.)

**A4. Do the live-path manual step.** The one check no capture owns (§3.5): run
`--screen=battle --local-players=2` for ~30 s in a real session, confirm the
camera settles behind the fighter instead of sweeping, then take a hit and
confirm it stays settled. A windowed run with a compositor is *not* the check —
the compositor path can be exercised headlessly (A4's supporting evidence is the
windowed row in §1.1) but the camera judgement needs a person watching.
*Depends on:* A3 (same tree). *Done when:* the observation is recorded with the
command, the session (Wayland/X11) and the date. *Evidence:* §3.5; D9.

**A5. Close the hardware and environment rows that need hardware.** Checklist
§5.1 names them: a physical controller walking a panel and a battle with its own
bindings (`--devices`); hardware audio listening (the backend's dummy-device
verification is not listening); a second GPU vendor; an interactive
compositor-side window drag-resize. *Depends on:* A3; runs in parallel with A4.
*Done when:* each row is either **run** (with the transcript) or explicitly
recorded as unavailable — the checklist already carries the "what would settle
it" sentence per row, which is the honest form. *Evidence:* §5, §5.1.

**A6. Truth-up the docs that contradict the measured run.** The items in §1.2:
`docs/status.md:29`; checklist §4.1's 743 → 747; §3.2/§3.3's outcome-line
caveat; §6's two 1v1 wall times; `ROADMAP-PENDING.md`'s COM "Open" paragraph;
`decisions.md` D6's stale paragraph; the "three renderer options" count in
`AGENTS.md`, the package README, `ROADMAP-PENDING.md` E3 and the foundation
README. *Depends on:* A1–A3 (the replacement numbers
must come from a measured run, not from this file). *Done when:* no doc claims a
count, hash or timing that a fresh run contradicts, and every number that moves
with the tree says when it was measured. *Evidence:* §1.2 above.

**A7. Re-run the whole gate end to end and record it.** Checklist §8 is the
reproduction script; run it in one sitting on the tree that will be released,
record the date, the commit and the transcripts, and only then call the milestone
delivered. *Depends on:* A1–A6. *Done when:* the recorded run is green by §3.2's
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
to what is genuinely unrecovered: the vtable-`0x20` per-character
handler-family melee hits (40/41/42, the 400-family). C1's own "what is left"
adds the projectile and TagOut selectors, the side/air dash pair (moves 23/24),
the physical identity of the two Guard bits (needs the weapon-word builder) and
the fresh AttackA selector's branch conditions. #18 and #31 landed — Guard binds
no clip *in the source* (`anim_no_selector()` is a report, not a gap) and the
airborne swing plays its own row — so neither should be re-fixed. *Depends on:*
B2/B3 (shared move/set tables). *Gate-blocking:* no.

**B5. #17's residual spawn placement.** #17 is closed, but its own follow-ups
record what is left: three shipped attachment models load and are never drawn,
and the muzzle/blue-hit cards are world-space spawns where the original draws the
attachment on the fighter's eleven rig matrices. *Depends on:* nothing.
*Gate-blocking:* no (the gate's §6 counters are the bound it checks).

**B6. #21 rows 1–2 (shadows, texture resolution) and the visual checks.** Row 0
(toon) landed; rows 1–2 were dispatched to a sibling worktree — **record that
outcome when it lands; do not assume it**. #38 needs a human eye on the
toon/outline captures. #2 (fonts) is **closed** — the owner's call was that the
font the port already uses is the answer — so it is not a work item here even
though `ROADMAP-PENDING.md` E3 still lists the three renderer controls as the
only Options gap. *Depends on:* nothing. *Gate-blocking:* no — the issue says the
graphics toggles do not independently block a basic match.

## 3. The acceptance gate

**The checklist is the canonical text.** The commands below are an index with
the load-bearing flag and the pass criterion; the transcripts, ladders, hashes
and timings live in the cited section, and if this table and that document ever
disagree, that document wins.

### 3.1 The load-bearing checks

| # | Check | Command (from `remake/foundation/`) | Canonical | Pass criterion |
|---|---|---|---|---|
| 1 | Host suite | `ctest --test-dir build/linux --output-on-failure` | §2 | `100% tests passed` out of the registered count; none `Failed`. The asset-dependent tests may be `Skipped` **only** in the documented data-free shape. |
| 2 | 1v1, two humans, three rounds | `./build/linux/foundation_demo --install=<game-dir> --screen=title --local-players=2 --script=tests/scripts/frontend-1v1-rematch.txt --headless --out=/tmp/rel-1v1.ppm --size=1280x720 --frames=15500` | §3.1 | `RESULT: ok`; the documented ladder; `[split]` roster `Rena 0` vs `Keiichi 1`; sha256 prefix `8cc49e6c` |
| 3 | One human + COM, three rounds | same with `--local-players=1 --script=tests/scripts/frontend-com-rematch.txt --out=/tmp/rel-com.ppm` | §3.2 | `RESULT: ok`; the same ladder tick-for-tick; a single view with a `COM` opponent; sha256 prefix `b813155d` |
| 4 | 2v2, four humans, three rounds | same with `--local-players=4 --script=tests/scripts/frontend-2v2-rematch.txt --out=/tmp/rel-2v2.ppm` | §3.3 | `RESULT: ok`; the same ladder; four views and the four documented combos (`Rena 0`/`Keiichi 0`/`Rika 0`/`Mion 0`); sha256 prefix `8cc49e6c` |
| 5 | Four-player front-end loop | `… --local-players=4 --script=tests/scripts/frontend-4p.txt --out=/tmp/rel-4p.ppm --frames=9600` | §3 preamble | `RESULT: ok`; ladder `0/34/446/4382/4984/5584/9520`; sha256 prefix `2483c3aa` |
| 6 | **Live-path manual step** | `--screen=battle --local-players=2` in a real session, ~30 s, then take a hit | §3.5 | A person confirms the camera settles behind the fighter and stays settled through a hit. Nothing headless substitutes. |
| 7 | Package + launcher | `./scripts/package_linux.sh` then `./tests/launcher_test.sh ./package/daybreak` | §1 | The script's assertions (no game data; `ldd` inside the package/base system; same digest twice); `launcher_test` 0 failures |
| 8 | All 46 selections | `./build/linux/weapon_definition_test` | §4.1 | `0 failed`; with the install `0 skipped` and `all 46 legal selections ran a match` |
| 9 | Character × stage sweep | `python3 tests/showcase.py --check --out-dir /tmp/sweep` | §4.2 | **No new untextured draw** beyond the documented install gaps; the pass/flag counts are a baseline, not a target |
| 10 | Window path and pacing | the §5 rows (Wayland, X11, 30 Hz, high refresh, fullscreen) | §5 | A window presents with FIFO vsync and the simulation stays 64 Hz regardless of the render rate |
| 11 | Prolonged-match stability | the eight-round 2v2 row | §6 | Eight `match: round over` lines, `RESULT: ok`, no crash, bounded live cards (`dropped=0`) |

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
on a shared machine), the §3.6 before/after baseline table (regression
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
   unverified; only software-WebGPU game-data runs exist (G1/G2).
7. **Windows and the web as *executed* targets.** Compiled, but execution is
   issue #35's subject and was still in flight when this was written — **its slot
   is open; do not assume its outcome**.
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

## 4. Separate milestones (outside this gate)

| Milestone | Status | Owner |
|---|---|---|
| Story mode | not built; ids registered, builders absent (D6) | separate |
| Browser game-data run / visual parity / hardware adapters | software-WebGPU run verified; visual parity and hardware adapters open (G1) | separate |
| macOS execution | never executed (G2) | separate |
| Windows and web **execution** | in flight — leave the slot open | #35 |
| Web asset delivery | in flight | #4 |
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
