# Pending work — the foundation, after the DX9 cutover

> Written 2026-10-02, the day of the Phase 5 cutover
> (`FULL-REPLACEMENT-PLAN.md` §8). DX9 is gone, so this file is the handoff:
> what is still open, what evidence points at it, and a concrete way in.
> Ordered by **what unblocks the most**, not by size: first the two
> instruments every other number depends on (A), then the battle frame's
> remaining fidelity (B–D), then front-end breadth (E–F), then the claim
> debts that must not be outrun (G).
>
> Honesty labels, used per item: **measured** = a number or artifact exists
> and is cited; **inferred** = read from the original's code or the prints
> but not yet executed; **unknown** = no pointer was found in this repo.
> Every pointer was re-checked on 2026-10-02 against the cutover tree; the
> two places where the hand-off notes were wrong say so inline. Line numbers
> for the deleted DX9 tree refer to the `pre-webgpu-cutover` tag
> (`37ed31d`).

## Implementation update — 2026-10-04

The front end now runs title → team/character/weapon/hypermode/controller
selection → stage settings → VS → countdown → two- or four-fighter matches →
victory/quote/report → selection. The earlier evidence and sketches below
remain the historical handoff; these status notes supersede their claims
that these screens or their audio do not exist.

| Item | Current status | Remaining work |
|---|---|---|
| D2 | Complete: both arcs and the 15-tick lock-switch pulse | None for the recovered ring transform |
| D3 | Countdown and winning-team sting implemented; four-fighter simulation builds and passes host tests | The recovered pre-round phase is THREE frames, not three seconds, and the code that walks the P09 3/2/1 digits is not in the corpus, so the port keeps its three-second countdown (a documented flow rule) and now draws it with the battle state: the round's settings and all four participants. Stings recovered: per-view round-start 60 frames at 6.0→1.0 scale, per-view KO 90 frames (0x5a) and respawn 120 frames (0x78), the team victory sting two layers of 180/120 frames with the second armed 60 frames in (FUN_00635d40:152-205, FUN_0063a130:89-98). Issue #11's KO sting was corrected to 90 frames (1.5 s) by that issue's owner; the 120-frame respawn presentation remains unmodelled there. Issue #47: the phase now runs OVER THE LIVE BATTLE, as the original's does — the match is built when the VS intro ends (the Battle screen's factory builds scene, fighters, cameras and weapons), the scene pass draws the arena under the digit and the round is HELD (no `tickMatch`) until the countdown's own clock ends, which is the round-start input gate. The three-second duration is unchanged and stays a PORT RULE: the code that walks the three P09 digits is still not in the corpus |
| E1 | Selection, real atlases, roster tables, costumes, weapons, controller slots, seeded COM choices and entry voices implemented; selected panels load into the four-fighter match path | Four-fighter presentation landed with issue #13: the roster (`src/ui/participants.h`) drives the HUD (one marker per participant with owner/ally/enemy/locked art), VS (four portraits, four name cells, combo + controller captions) and the results (four per-participant rows plus the winning TEAM). Exact original navigation parity remains open; the asset-backed launch is verified by issue #13's title→selection→VS→battle→results→selection run |
| E2 | Stage/variation and all five battle settings implemented and connected; the balloon capacity, KO/Overkill credit and timed-round rules are recovered (2026-10-05, issue #11) | Between-rounds red-capacity creep and the KO move's own respawn clock remain; see the issue #11 update below |
| E3 | Volumes, fullscreen, native resolution selection, keyboard/gamepad rebinding and their persistence implemented (issue #19) | Three renderer controls are unavailable; browser-side persistence (IndexedDB/OPFS) is open |
| E8 | Gear-up resolution fixed (issue #23 blocker): the launch attaches the item's first **non-empty** attachment mesh across its slots, and an item that ships no mesh anywhere is ARMED, not a failed launch (recovered: FUN_00433eb0:90-116 loads every slot and skips the empty names at :111). Before: 20 of the 46 roster items were rejected (12 with their mesh in slot 2 — 009/011/013/014/022/025/026/032/039/041/043/044 — and 8 with no mesh at all — 008/010/017/023/024/031/038/040); after: 46/46 launch, the 8 armed with nothing to draw | The original may load a mesh per non-empty slot; the port draws the first one only. Slot 2 is as deep as the shipped data goes (039 has 12 slots, its mesh in slot 2) |
| E7 | Offline battle pause implemented (issue #15): the recovered freeze (`Match::set_paused` gates the authoritative step; the fixed clock is not advanced, so paused wall time cannot become catch-up ticks), a four-row readable menu on the D7 caption path, rematch through VS with the stage pinned, return to selection, quit, SFX-bus suspension, focus-loss auto-pause and the stale-edge rule | The four-row menu, its captions and the return/quit rows are PORT FEATURES (the original's pause UI is a banner plus a yes/no rematch prompt); a physical pad replug and real hardware audio are unverified |
| E4 | 109-update VS transition implemented; four participants land on the original's four portrait/name slots (FUN_00411cb0) with combo + controller captions | Confirm-to-skip is a port extension; a one-member team keeps the port's centred single slot (the original always has four players) |
| E5 | Sting, quote, voice, actual participant stats and draw handling implemented; the report draws one row per ACTIVE participant (badge at the recovered x 200, the earned title at 300/y+32, combo and KO/death/damage) and names the winning TEAM. Issue #20 recovered the quote rule (winning pair, persona variant, outcome grade 1..4, the 16/17 single-script fallback, one of the file's several alternatives) and the earned-title chain over the per-fighter record, with the names read from the exe's own table at VA 0x6b7308 | The title chain's conditions whose fields are not recovered are SKIPPED and flagged (`[title] ... (chain reached unrecovered conditions)`): +0x20, +0x48, +0x54, +0x58, +0x5c, +0x60, +0x64, +0x68, +0x6c, +0x70, +0x74, +0x78, +0x7c/+0x80 and the damage-event pair. The original also marks a penalized panel forced/auto-ready (FUN_00409340:170-172); the port only forces the costume. With the current balance a round's damage and hit totals rarely reach the damage-heavy thresholds, so most rounds end on the chain's own fallback or a low-threshold title |
| E6 | Reusable two-page atlas keyboard implemented and tested | Netplay host remains outside D6 scope |
| F1 | Four menu SEs, entry/result voices and menu BGM connected | Hardware audio listening remains separate from dummy-device verification |
| G1 | Real-asset versus and live match executed in a browser | Hardware GPU and usable browser screenshots remain unverified |
| G2 | Unverified | No macOS hardware available |
| G3 | Re-measured for the issue #23 release gate: **165 pass, 43 known flags, 0 pipeline failures** (16 characters × 13 stages = 208 runs) | Existing install gaps remain and are unchanged: stage05/stage15 miss 4 dust textures on every other character and `kasai` misses its `g` texture on every stage. The old note here — "two roster characters (Satoko, item 008; Takano, item 011) currently fail the loud gear-up join" — is STALE and was retired by E8: all 46 selections launch |
| #12 | One view per human controller: its own camera, cell and HUD values, match still stepped once; recovered one/two/four-cell layouts, viewport + scissor per view, per-view marker projection | Three-human layout is the original's four-cell grid with an empty cell (port policy for the placeholder); non-Linux execution unverified. Physical pads and interactive resize/fullscreen were the other two gaps: the port's own Options screen now drives a resolution change and a fullscreen toggle on both Wayland and X11 (nested compositor, `[display]` lines in `docs/RELEASE-CHECKLIST.md` §5), but a compositor-side mouse drag on the window edge is still untested and no run has driven the attached physical pad — the pad attached to the gate machine perturbed runs until device isolation was added (issue #29: a verification run ignores physical devices by default, `--devices` asks for them back, an unfocused window takes no input) — `docs/SPLIT-SCREEN.md` |
| #23 | Release gate: the checklist in `docs/RELEASE-CHECKLIST.md` demonstrates two humans (1v1), one human with COM and four humans (2v2) through three rounds each, the 46-selection sweep, the character × stage texture matrix, Wayland/X11, 30/60/high-refresh pacing, resize/fullscreen and an eight-round stability run | Three release-blocking defects were found and fixed by the gate (the 1v1 result screen never loaded; a rematch submitted released vertex buffers and aborted; rematch rounds diverged from round 1). Still unverified, and named as such in the checklist: a second GPU vendor, physical controllers, hardware audio listening, other distributions and an interactive compositor-side resize |
| #48 | The original's in-battle debug keys implemented (F1 full HP + both balloons, F2 COMs off, F3 COMs on, F4 gauges, Escape leave) with the recovered map, the per-fighter AI flag on `Match`, sampling on the fixed-step boundary, `--no-debug-keys` and the `--debug-keys=KEY@TICK` injection | Two port rules: the `DAT_006cfce9` gate becomes "always active in a battle" (the port has no story mode) and F4 fills every meter the port models because the original's per-slot `+0x318` selector has no counterpart; the interactive Escape stays issue #15's pause key, so the recovered leave is reached through the pause menu there. Full map, addresses and the evidence trace: `docs/DEBUG-KEYS.md` |

Implementation lives in `src/ui/screen_select.*`, `screen_stage_select.*`,
`screen_options.*`, `screen_vs.*`, `screen_result.*`, `soft_keyboard.*`,
`frontend_launch.*` and `frontend_settings.*`; the host in `src/main.cpp`
loads the selected assets and applies `MatchConfig`. A 1v1 match uses upper
panels and env slots 0 (blue) and 2 (red); a multi-fighter match uses each
selected panel's corresponding env slot. Standalone parity captures retain
their existing 0/1 spawn recipe. COM battle input is a deterministic decision state
built on the recovered tactic cells and timers — see "COM decision state and tactics"
below; the fixed-frame sparring policy it replaced is gone.

## COM decision state and tactics — 2026-10-05

Issue #14. `gameplay/bot_input.h`'s old policy (walk at the opponent, press
melee/shoot/special on frame modulos) is deleted. A COM is now a deterministic decision
state in `src/gameplay/bot_brain.{h,cpp}`, with `bot_input.{h,cpp}` as the host seam
(Match state → `BotView` → the tick's input). 97 host checks cover it
(`tests/bot_brain_test.cpp`), including an asset-backed four-combo 2v2.

**Recovered.**

* **Tactic cells.** Player `+0x310` is a 6-valued cell, `+0x314` its HUD timer.
  `FUN_0041f580:291-295` cycles it `(cell + 1) % 6` on the Tactics press, mirrors it
  onto player 0's cell and writes `+0x314 = 2.0f` (0x40000000); `FUN_004201a0:13-15`
  drains that by 0.2/frame to -6.0 and `FUN_00644150:92-96` fades the boxed readout with
  it. `FUN_00421730:11` resets the cell to 0 at round start; `FUN_0063c2a0` case 0x2d
  writes it from a character script. The port keeps ONE team cell (which is what the
  mirroring produces) and drives `ui::HudState::commandCell` from the same value, so the
  readout cannot disagree with the decision.
* **Per-cell weights**, read verbatim from `FUN_0043f4d0:22-63`: rangeScale / engage /
  power = 1.0/100/100 (cell 0 適当), 0.25/50/200 (1 格闘), 2.5/200/50 (2 射撃),
  1.0/100/100 (3 集中, 4 各個), 7.0/5/5 (5 後退). `engage` percent-gates the
  movement/attack branch (`:235`), `power` the in-range dash branch (`:194`, inside
  `dist² < 250000`), and rangeScale scales the advance re-roll threshold
  (`250000 * c² <= dist²`, `:154`) — 125 / 500 / 1250 / 3500 units.
* **Decision inputs**: squared XZ distance to the current target (`FUN_0042d980`,
  dx² + dz² against the `+0x38` target pointer); the distance to the first surface along
  the line to that target, kept in `player+0x80` by `FUN_0042cc90`'s D3DXIntersect walk
  (`FUN_0042d2c0`, default 10000.0) and read as "is the target behind something" at
  `:240`; airborne `+0x84`; move id `+0xadec`; the 0..1000 resource `+0x834`
  (`0x28a < +0x834`, `500 < +0x834` at `:79,116`); the mode latches `+0x844/845/846`;
  and the shared MT19937 `FUN_0065d150` for every probability gate.
* **Decision outputs** the port mirrors: an 8-way movement direction (`+0x278/+0x27c`,
  mapped onto 45° yaw steps by `FUN_00421780`); attack requests `+0x284/+0x288`, which
  the act function consumes and then writes 0x14 back into (a 20-tick re-request lockout,
  `FUN_0043ded0:140-141`); a retarget request `+0x28c`; a shot request `+0x2b8`; the
  dash selector `+0x830` (1..4 → air dash moves 0x14/0x17/0x18/0x1b, ground
  jump-forward 0x1e, `FUN_0043ded0:61-107`); and the four jitter timers
  `+0x864` (lateral, ±200), `+0x868` (advance/retreat, sign from the rangeScale test),
  `+0x86c` (airborne reposition, 1% per tick, 10..129 ticks) and `+0x870` (power-attack
  window, 1/450 per tick, 180..359 ticks — active better than half the time).
* **Target selection is the AI's own**: `FUN_00421c80` measures both players and writes
  `+0x28c = 1` only when the pick differs from its `+0x300`; cells 3/4 instead compare
  that field with player 0's (集中 wants the same target, 各個 a different one).
* **COM class selection**: `FUN_006492f0:14-38` picks one of three per-character AI
  classes per slot with `rng % 3` (reduced to `% 2` for rena and rika), and
  `FUN_00649790(characterId, kind)` builds it from the class table at 0x6a4e10. There is
  no difficulty setting in the original.

**Port rules (provisional, labelled in code).** The original steers by absolute yaw
(`FUN_00421780`/`FUN_0042db10`); this port's fighters are lock-on facing-relative
(#8), so the brain emits the same intent through the four direction keys and probes the
world direction that intent resolves to. The original has no path search — its only
obstacle input is the `+0x80` line distance — so the directional probes, the wall-side
memory and the bounded stuck recovery are the port's answer to the issue's "must not
remain blocked at a wall or corner", built on #7's sweeps. Ammo/stamina/reload and
guard-exhaustion gates are the port's resource model (#6/#9). `BotDifficulty`
(Relaxed/Standard/Sharp, default Standard) scales the plan window, the recovered
weights and the defensive chances; it is a documented port policy because the original
randomises one of three AI classes instead. Two further port rules keep a COM in the
fight: outside `1.6 *` the cell's engagement band the lateral jitter is dropped and the
advance forced, and the forward push stops once the target is inside the swing (the
recovered walk is a distance band, not a footsies rule — measured, a COM without it
crossed a 240-unit gap eleven times in 900 ticks and never pressed). The port's charge
hold is mobile, so a COM closes while it charges; a 格闘 cell taps only and only from
outside its band, because a full charge costs the fighter its firing pose.

**Verification.** `ctest` = 31/31 (97 checks in `bot_brain_test`, which skips its
asset-backed section without an install). Asset-backed 1v1:

```bash
SDL_AUDIODRIVER=dummy ./remake/foundation/build/linux/foundation_demo \
  --headless --install=Higurashi-Daybreak --screen=battle \
  --frames=11000 --out=/tmp/battle.ppm --size=320x240
```

fights Rena 0 against Mion 0 (COM) on `data/stage03` (shrine grounds, collision.x and
collision_tama.x loaded) and **finishes**: time up at frame 10800, side 1 (the COM)
wins with the idle human at HP 30/100. Its own counters for that match: moved 52196,
melee 51 pressed / 35 withheld while mid-move, 112 shots started / 101 fired / 34
refusals, 18 dashes, 1 jump, 1 hyper activation, 209 wall probes refused with a single
bounded recovery, 170 direction changes.

**Open.** A *front-end* four-fighter run cannot start on this install: the select
screen's auto-fill (deterministic, `FrontendState::nextRandom`) gives panel 2 chie,
whose slot-0 item `data/item/014.dat` fails `readItemFirstMesh`, and the rule-7 gear-up
check then aborts the launch (`fighter 1 data/chie:0 has no weapon`). That is issue #9's
item-data gap, not the COM layer; the 2v2 evidence is the asset-backed host run above
(four shipped combos, walled stage, COM-only sides).

### Future remake-only experiment: 3v3 and 4v4

This is a new feature for the remake; the original game does not have 3v3 or
4v4. Keep it opt-in and describe it as an experiment, not as recovered game
behavior. The current match path holds at most four fighters total: two teams
with one or two members each, selected from panels 0/1 (blue) and 2/3 (red).
That is not a 4v4 implementation. A 3v3 match needs six fighters total and a
4v4 match needs eight.

When asked to implement either mode, use this sequence:

1. **Define the roster contract first.** Add an explicit experimental team-size
   choice and a stable roster entry per fighter containing at least team side,
   character/weapon choices, and human-controller-or-COM assignment. Keep
   `fighterIndex`, menu panel, and controller index separate; they stop being
   interchangeable once each team has more than two members. Represent the
   chosen side on every fighter and require exactly three or four entries per
   side before launching. Preserve the existing two- and four-total-fighter
   flows when the experiment is not selected.
2. **Raise the simulation capacity as one change.** Introduce a named maximum
   of eight and use it consistently in `MatchConfig`, `MatchFrame`, `Match`,
   `MatchEconomy`, launch data, and the host's rig, bot-input, and camera-target
   storage. Remove the current four-fighter clamp in `loadScene` and audit each
   loop, fixed array, and result/HUD index in `src/main.cpp`; do not merely set
   `fighterCount` to six or eight. Keep team economy at two sides, but track
   each fighter's KO/respawn clock separately and award balloon progress to
   that fighter's side exactly once per KO. Continue excluding allies from
   melee targets and projectiles, and retarget living opponents after KOs with
   a deterministic roster-order tie break.
3. **Give extra fighters safe, repeatable spawns.** The original environment
   spawn data is for its four-fighter limit. Use existing team positions as
   anchors and assign additional members deterministic formation offsets that
   respect stage bounds and avoid overlap. Reuse the same member-specific
   spawn/facing data after respawn. Never read a fifth or later environment
   point unless a new format has actually been established.
4. **Extend the front end and presentation for a roster, not two portraits.**
   `FrontendState::slots`, `resultStats`, `kFrontendBattleSlots`,
   `FrontendLaunch`, and the selection/VS/result screens currently assume at
   most four panels and two primary participants. Add a team-roster selection
   flow (for example, scrollable member rows) with per-member character,
   weapon, hypermode, and controller/COM choices. Load every selected model
   and weapon. Show team balloon state plus a readable alive/KO summary; choose
   a camera framing policy that can keep group fights visible. Results should
   retain per-member combat stats while naming the winning team. If quotes or
   portraits still use a captain, label that as an experiment instead of
   implying original multi-member result fidelity.
5. **Prove both sizes independently.** Add host coverage for exact 3v3/4v4
   rosters, side assignment, launch rejection for incomplete teams, target and
   friendly-fire rules, simultaneous deaths, per-member respawns, and team
   round-over. Check boundaries for 2, 4, 6, and 8 fighters so existing modes
   and unused slots do not regress. Then run asset-backed 6- and 8-fighter
   matches on representative stages; verify model/weapon attachments, spawn
   spacing, camera/HUD readability, results, and frame time. Keep these tests
   separate from original-binary parity expectations.

Primary extension points are `src/gameplay/match.h`, `match.cpp`,
`match_economy.h`, `match_economy.cpp`, `projectile.h`, and `projectile.cpp`,
the UI state and selection/VS/result files under `src/ui/`, and the
roster-loading, input, camera, HUD, and results paths in `src/main.cpp`. These
are remake product changes; do not edit generated `research/recomp/` or present
the new rules as reverse-engineered facts.

Recovered details: the roster anchors/order/costume limits are the tables
at `0x6b71d0/0x6b7210/0x6b7250/0x6b7290`; the stage constructor's count
makes the school stage three-way and other stages two-way. Result report
art is in `FUN_00633ca0` (header y=320, width=288). D2's writer is
`FUN_00421e30`/`FUN_00421f30`, decrement `FUN_004201a0`: lock switch writes
15 and ticks decrement it; the first arc adds 9 degrees per pulse tick,
both arcs scale by `1 + 0.1*pulse`.

B1 also received a parser correction: `FUN_0042eec0` reads a version dword
then one fixed 260-byte model path at offset 4, not a mesh count and short
name slots. `src/game/effect_descriptor.h` now checks that contract.
Lifetime remains unresolved: all 22 installed descriptor variants have a
zero raw lifetime field. `FUN_00436630` ticks instance `+0x130` against the
variant referenced at `+0x120`; constructor/factory are `FUN_0042f820` /
`FUN_0042f5e0`. Aura defaults in `FUN_004205e0` select 0/5/1, with an
explicit override at `+0x7d4`; state overrides in `FUN_0042e110` select 2/3.
These findings do not yet establish the complete mode mapping or a safe
replacement for the placeholder effect lifetime. B1 trails and C1's
unproven guard/jump writers remain open.

Verification: native full-flow runs reached live battle and results with
`RESULT: ok`, including a result voice. The browser asset run used
SwiftShader (details in `BUILD-web.md`). The full texture sweep reproduced
the existing 43 flags without new misses. Regression tests cover menu
states, settings, launch mapping, results, descriptor parsing, ring pulse,
match rules and combat statistics. All 24 Linux CTest tests pass; Linux,
Windows cross-build and web asset builds succeed. Native smoke recipe:

```bash
SDL_AUDIODRIVER=dummy ./remake/foundation/build/linux/foundation_demo \
  --headless --install=Higurashi-Daybreak --screen=title \
  --script=remake/foundation/tests/scripts/frontend-smoke.txt \
  --frames=4700 --out=/tmp/frontend-smoke.ppm --size=800x600
```

Display support now derives battle HUD anchors from the viewport, projects fighter
markers through the actual battle camera, and keeps menus on a uniformly scaled
4:3 canvas with black bars. Aspect handling is automatic, including ultrawide.
Native Options offers Desktop/common/display-mode resolution choices; browser
and headless rows show their externally controlled sizing. Linux native Wayland
checks exercised window resize, fullscreen toggling and fullscreen resolution
changes. Real-asset captures checked 1920×1080 and 3440×1440 battle layout,
3440×1440 selection, and an irregular 1373×777 menu viewport. Layout tests also
cover portrait, 4:3 and clipped/rotated sprites.

## Fixed-tick implementation update — 2026-10-04

Issue #5 now has a live 64 Hz accumulator, tick-indexed input/scripts and bot
cadence, bounded catch-up, queued short keyboard/gamepad taps, and interpolated
fighter/camera presentation. The owner-selected rate and explicit legacy capture
exception are binding decision D9. Tests compare two- and four-fighter matches
at 30/60/144 Hz rendering with simulation fixed at 64 Hz; long stalls and
zero-tick renders cannot erase or repeat input edges. The original countdown
trigger is still unrecovered; the port's countdown remains three seconds (a PORT
RULE), and since issue #47 it runs over the LIVE BATTLE: the arena, fighters and
camera are built when the VS intro ends, and only the round's simulation is held
until the clock ends.

Effect models now load before scene model pointers are borrowed by fighters,
controllers and collision queries. The full-flow run exposed a projectile
collision crash from those pointers becoming invalid when effect appends moved
scene storage; ordering scene assembly before binding fixes that lifetime.

Verification: 25 Linux host tests pass; Linux/Windows/web builds succeed.
The native Wayland match separates render counts from 64 Hz logic ticks, and
real-asset frontend smoke reaches results and selection. The saved legacy melee
capture remains byte-identical. Details are in `BUILD-linux.md`.

This is the first offline prerequisite for issue #3, not rollback completion.
Snapshot/save/restore, explicit RNG/state hashes, cross-platform determinism and
network transport remain open. Basic playability work continues through issues
#6–#23 and the ordered Linux release tracker #24.

## Split-screen implementation update — 2026-10-04 (issue #12)

Local versus now renders one view per **human controller**: its own camera, its own cell on
the render target and its own HUD values, while the match is stepped once at 64 Hz. The
layouts are the original's own, recovered from `FUN_006396f0` @ `0x006396f0` — one full
800×600 frame; two 400×300 views at top-left and bottom-right; the four-cell TL/BL/TR/BR grid
for four humans; and, for three humans, that same four-cell grid with the human-less cell left
empty (the original marks it `-1` and skips it, `:74-81`/`:109`). `FUN_0040d130:105-119` is
the human count that selects the layout and also the no-human fallback to one view on
controller 0. Views are keyed by controller slot, as the original keys them
(`game+0x44b4`, per-view context at `game+0x454c + slot*0x160`).

Implementation: `src/game/view_layout.h` (recovered geometry + controller-keyed assignment),
`src/game/match_view.h` (per-view camera/HUD context), `renderViews()` in
`src/render/scene_renderer.*` (one pass, colour and depth cleared once, viewport **and**
scissor set per view, per-view camera uniform and per-view draw uniforms for billboards),
per-view cells for the debug-prim overlays, an origin on `ui::UiViewport` for per-view HUD
batches, and the per-view camera/HUD loop in `src/main.cpp`.

Explicit port policies (not recovered): per-view aspect is automatic per D8 rather than the
original's fixed 4:3 cells; separator thickness scales from the original's one pixel;
a human-less cell keeps the clear colour because the placeholder sprite was not identified;
the FPS counter is drawn in the first view only (the original draws it once, outside its view
loop). `--local-players=N` is a verification instrument with a deterministic synthetic pad
pattern for controllers with no device — synthetic input, not physical-pad evidence.

Verification: 30/30 Linux host tests pass (`view_layout_test` pins the cells, the assignment,
per-view projection and the guard that 1-view and 4-view runs end in identical simulation
state with identical tick/audio counts; `hud_layout_test` covers per-view HUD layout, including
the original's 0.5 scale for a 400×300 view; `arena_camera_test` §7 covers independent per-view
cameras). Single-view parity against a pristine `HEAD` build is byte-identical for `--match`,
`--versus`, `--screen=battle` (800×600 and 1920×1080) and `--hud-test`. Asset-backed runs:
two humans at 800×600 (two views, separate HUD values), three humans (four-cell grid with one
empty cell), four humans at 1920×1080 (2v2, 142 melee hits, one KO credited, round over and the
result screen reached), ultrawide 3440×1440 and odd 1373×777. A windowed Wayland run exercised
the window path with two views. Physical gamepads, interactive resize/fullscreen and non-Linux
execution remain unverified. Details, provenance and the exact commands: `docs/SPLIT-SCREEN.md`.

## Issue #13 update — four-fighter presentation

The front end's four selection panels are now one roster that the HUD, VS and the results all
read (`src/ui/participants.h`: panel, team, fighter index and controller stay separate index
spaces). Verified end to end on real assets with
`--screen=title --local-players=4 --script=tests/scripts/frontend-4p.txt`: title → selection →
VS (four portraits, four name cells, four combo/controller captions) → countdown (settings and
all four participants) → 2v2 battle (four views, four markers each, per-view roles and
off-screen alert markers) → results (four per-participant rows and "RED TEAM WINS") →
selection. 32/32 Linux host tests pass, including the new device-free
`participant_layout_test` (1v1/2v1/2v2 rosters, the four recovered VS slots, the report's rows
and the victory layer's frame-60 transition).

Open, filed rather than invented:

* **Spawn spacing (policy item, LABELLED).** `MatchConfig` keys each fighter's spawn to its
  PANEL (`FUN_00423420` indexes the stage's env points by the selected panel), so a 2v2 starts
  from the stage's own four points. On `data/stage21` they are 900+ units apart
  (`(-463,200,-2200)`, `(-1363,200,-2200)`, `(-406,200,-105)`, `(-1363,200,-105)`), so the
  crowding issue #12 saw is stage-dependent; any formation that spreads teammates further
  would be a port policy with no evidence behind it. `[menu]   fighter N panel P spawn=...` now
  prints them at battle entry.
* **Countdown trigger/timing.** Recovered: the round reset sets phase 1 and the fight starts
  three frames later (FUN_00634760, FUN_00635d40:62-83), arming each view's centre sting for
  60 frames at 6.0→1.0 scale. The digit walk over P09's three cells is not in the corpus, so
  the port keeps its three-second countdown and shows the battle state with it.
* **KO sting window.** FUN_00635d40:152-157 arms the KO sting for 0x5a (90 frames = 1.5 s,
  re-armed every frame the fighter stays down) and the respawn presentation for 0x78 (120
  frames) on the credit frame's headroom branch (@0x637173). Issue #11's
  `MatchEconomy::kKoStingSec` is now 1.5 s accordingly; the 120-frame respawn presentation
  is not modelled separately and stays on that issue's unresolved list.

## Guard lifecycle update — 2026-10-04

Issue #6's live blocker is fixed. Guard release is processed outside `can_act()`;
release or missing input returns to Idle on the ground or Jump in the air,
allowing the next action on that tick. Hit/KO retain priority. Guard clears its
inherited action timer on entry and exits on the tick stamina reaches zero.
An exhausted hold must be released before Guard can start again; stamina can
recover and other actions remain available while that button is held. This
re-entry rule is explicitly an interim port rule, not recovered binary behavior.
Focus loss releases all players' queued buttons and suppresses physically held
keyboard/pad buttons until release. Controller removal samples neutral input.

Damage blocking still uses the existing provisional `max(1, amount / 5)` rule
and guarded hits still enter Hit/KO. The corpus search found no
`FUN_0064ae10` key-12 call; key-13 calls in `FUN_00421e30`/`FUN_00421f30`
are target-switch cues, not an incoming-damage gate. The voice table loader
`FUN_00431e70` establishes names, not block conditions. Directional block gates,
attack exclusions and original damage reduction remain unrecovered. No damage
fidelity is claimed by this fix. The old DX9 one-way Guard remains frozen
in the evidence bank; playable updates and new captures use the corrected rule.
No legacy runtime mode is needed for the release acceptance criteria.

Verification: all 25 Linux host tests pass. Guard behavior tests run at 64 Hz
and cover release into movement/jump/melee/shoot, grounded/airborne release,
exhaustion/re-entry, missing input, and Hit/KO priority. The input integration
test uses an SDL virtual controller to verify actual polling, focus loss,
held-button suppression and unplugging through the fighter's Guard state.
Linux, Windows cross-build and web builds pass. A real-asset stage21
Rika/Takano run completes 850 ticks with Guard → Walk → Jump, exhaustion to
Idle and a fresh Guard hold in its trace (`RESULT: ok`). Reproduce with:

```bash
SDL_AUDIODRIVER=dummy DAYBREAK_CAMINFO=1 ./remake/foundation/build/linux/foundation_demo \
  --headless --install=Higurashi-Daybreak --match --stage=data/stage21 \
  --character=data/rika --enemy=data/takano --frames=850 --size=400x400 \
  --dt=0.015625 --script=remake/foundation/tests/scripts/guard-lifecycle.txt \
  --out=/tmp/guard-lifecycle.ppm
```

This explicit 1/64 capture checks asset-backed integration; device-free tests
exercise live tick semantics. Virtual-controller checks are not physical
controller testing, and dummy audio is not a listening check.

## Per-fighter combat target — 2026-10-04

Issue #8's blocker is fixed. Each fighter now owns a lock on another fighter,
independent of which player the camera follows. `src/gameplay/target_lock.h` holds
the rules; `Match` owns the table and is what `step()` reads, so facing, shots and the
melee victim all follow the selection. `Match::step()` no longer re-picks the nearest
living enemy every tick — that was a function-local with no accessor, so nothing could
be locked, held or observed.

**Recovered, with provenance.** `FUN_00421e30` (0x421e30) is the cycle writer: it stores
the selection, writes the 15-tick pulse at `+0x30c`, **clears** the combat target at
`+0x304`, and compares the selected player's team against player 0's — equal arms the
ally hold `0xb4` at `+0x848` and plays cue 0xe (0xf when the mode flag `+0x845` is set),
different clears the hold and plays cue 0xd. `FUN_00421f30` (0x421f30) is the direct
set: a valid index is adopted with a fresh pulse and a cleared hold, and **any other
index stores `0xffffffff` and touches nothing else** — which is the port's
"invalid targets never produce an index" rule, kept exactly. `FUN_004201a0` (0x4201a0)
decrements the pulse. `FUN_0041f580:216-248` is the maintenance pass: a validity
predicate whose failure clears the lock and re-picks by walking `(selection + 1) %
count` with a wrap and a skip, committing only when the walk lands somewhere new
(`:238`); then the ally hold **re-pinned to 0xb4 every tick** while the selection is an
ally and decremented otherwise. `FUN_0063c2a0` (0x63c2a0) is the dispatcher that reaches
both writers — command 0x2a calls `FUN_00421e30`, command 0x2b calls `FUN_00421f30`.

**Port rules, explicitly not RE.** The candidate walk skips dead fighters and the owner;
the original's own walk skips the `+0xaecc`/`+0xaed0` pair that commands 0x20/0x21 set
and clear, and what that pair represents is not recovered. Tap cycles hostiles and hold
picks an ally — the reading of `input.h`'s "tap = cycle enemy, hold = aim ally"; the
original's cycle is not gated on team. With no valid lock the fallback takes the first
hostile in index order rather than the nearest, which keeps it deterministic. The
hold-gesture threshold is a port constant. `+0xaecc`, `+0xaed0`, `+0xaed8`, `+0x845`,
`+0x318` and the `+0xaecb` "busy" flag in the validity predicate are all still
unmapped, so those guards of the original predicate are not modelled.

**Corrected by issue #49 (2026-10-06).** The first selection is *not* acquired silently.
The port rule this section used to record ("nobody pressed anything … a lie the HUD then
animates") was wrong: it made every ring green at round start and
suppressed the owner's counter-rotating ring. `FUN_0041f580`'s maintenance branch (live
`0x41fdea-0x41ff7a`; `FUN_0041f580.c:213-241` in the corpus) clears `+0x304` at
`0x421fecb` and then calls `FUN_00421e30`, whose own body clears `+0x304` again
(`0x421e96`) — so a fighter with no prior selection comes out of the pass still unlocked;
`FUN_00421f30` (`0x421f65`) is the only store that can make `+0x304` valid, and it is
reached only from the command dispatcher's LockSwitch command and the state-gated
`0x421fe07` call (`+0x28c == 0x1e`, a value nothing on the player object is observed to
write). The pass therefore only ever *drops* a lock, which is what the port keeps for a
lost target. A lock now comes from a gesture — the human's LockSwitch tap
(`main.cpp`, `Match::cycle_locked_target`) or the COM brain's own `retarget` decision
(`bot_input.cpp`) — and `Match::step()` feeds facing from `TargetLocks::fallback_target()`,
the maintenance walk's pick, which is the original's independent `+0x300` aim selection
(`FUN_00421c80` requests it) rather than the `+0x304` lock.

**Behaviour.** A valid lock is never re-picked, so a nearer unselected enemy cannot
silently override it; only a tap or an invalid lock moves it. A lock naming an ally is
aim-only — `Match::melee_target()` returns it only when it is a living hostile, and
otherwise falls back to the nearest living hostile, so an ally can be faced and shot at
but never hit and a fighter holding an ally is never left unable to attack.
`ProjectilePool::update` already excluded allies from shot collisions and still does.
The HUD ring and com bar now mark the fighter the **viewer** has selected, driven from
that viewer's lock pulse — previously the ring was the inverse of the camera's target,
so it moved onto the player's own fighter whenever the camera switched, and the field's
own comment already said it should be "the locked target". The COM bot aims at its
fighter's lock, which deleted the duplicate nearest-enemy scan that sat in `main.cpp`.

**Camera.** The camera keeps its own followed-player selection — that separation is the
point of the issue. A real target change now arms a retarget window (10 calls at blend
0.45 instead of the reference's 0.1) so a switch lands fast without cutting or
overshooting; the window is armed only by an actual change, so a match that never
switches — every banked 1v1 capture — stays on the reference rate.

**Verification.** 154 checks in `tests/target_lock_test.cpp` (27 host tests total, all
passing) cover 2v2 tap cycling and wrapping, backward cycling, ally-skipping in both
directions, the one-enemy no-op, independent per-fighter locks on all four fighters,
240 ticks of a closer enemy failing to steal a lock, KO of the target and of the owner,
respawn, dead allies, every invalid-index branch, out-of-range owners, the hold pin and
countdown, the 15-tick pulse and its clamp, index-space distinctness, facing and melee
following a far locked target while a near one stands closer, ally locks never producing
a hostile victim, and the camera's retarget window plus the no-boost cases. Linux,
Windows cross-build and web builds succeed. A real-asset 1v1 capture (stage01,
Rika/Takano, 200 frames at 1/64) is **byte-identical** to the pre-change binary, both
in the `DAYBREAK_CAMINFO` trace and in the rendered frame, confirming the no-LockSwitch
path is untouched. A capture that presses LockSwitch differs by design: that is the
camera retarget and the ring's new owner.

**Corrected by issue #51 (2026-10-06).** The LockSwitch tap must not move the camera. The
recovered writer `FUN_00421e30` stores only the fighter's own target state (`+0x300`,
`+0x304` cleared, `+0x30c` pulse, `+0x308`, `+0x848` + cue) and its other caller
(`FUN_0063c2a0` case 0x2a) applies a REMOTE player's switch, so the tap above — which then
also called `ArenaCamera::cycle_target` — was wrong: it re-pointed the camera's followed
player at the enemy, the reported "the whole camera moves onto the enemy". The tap now
re-picks the combat target only and a view follows its own fighter for the whole match;
`ArenaCamera::cycle_target` keeps no match caller (it stays as the ported reference API,
pinned by `tests/arena_camera_test.cpp`) and `tests/lock_switch_camera_test.cpp` pins the
rule by driving `tickMatch` in a 1v1 and a four-view 2v2.

## Per-weapon combat definitions — 2026-10-04

Issue #9's selection data now reaches combat. `src/gameplay/weapon_definition.h/.cpp`
parse the original files device-free; `frontendLaunch` loads them; `MatchConfig::weapon`
carries them into `Fighter`. A weapon selection changes magazine sizes, charge
thresholds, per-shot costs, volley counts, projectile damage and hit radius.

### What the data actually is

Two files, two readers, and a correction to the premise the issue was written against.

`data/item/NNN.dat` (FUN_00433eb0, 0x433eb0, read through FUN_00653760 = ReadFile):
dword slotCount, dword bulletCount, a 30-byte gauge name, two gauge heights,
`slotCount` attachments of {30-byte mesh, 30-byte texture, 9 floats}, then **two**
magazines of six ints, then `bulletCount` bullets of four ints. Note the first dword is
the **attachment count** (2..12 across the shipped set), not a version.

`data/bullet/<weaponId>/<type>.dat` (FUN_005f8510, 0x5f8510), reached because
FUN_00433eb0:152 hands each bullet's `type * 10 + status` to FUN_005f80c0, which builds
`data/bullet/%03d/%03d.dat`. Each effect record is 0x80 bytes, of which **80 bytes at
record offset 0x30 are read verbatim in one call**. Those are the per-weapon combat
scalars; `BulletParameter` names them from FUN_00637950 (0x637950), the hit-resolution
function that consumes them.

**Correction worth recording.** An earlier reading of this work treated the item file's
magazine block as recovered ammo. It is not: a corpus-wide scan finds no function that
reads those fields (`+ 0x64)` returns zero hits across all 3191 decompiled functions).
The block is parsed and never consumed in this corpus. The remake still uses it to size
magazines, but that is a **port rule**, and the header says so. The original's charge is
a 100-point gauge with a 120-frame decay window, **not** a hold duration — so
`yellow_hold_sec()`/`red_hold_sec()` are also port rules, not recovered behaviour.

### Coverage table — 46 legal selections

Per-weapon magazine figures below are read from `data/item/NNN.dat`. `hp/rad/base` are
`hpDamage / hitRadius / baseDamage` from the tier's `data/bullet/<id>/<type>.dat` block.
`—` means the tier found no bullet for that magazine and keeps the shared table.

| char | slot | id | slots | bullets | m0 num | m0 reload | m1 num | m1 reload | chg0 | chg1 | tap hp/rad/base | charged hp/rad/base |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| rena | 0 | 1 | 2 | 18 | 6 | 300 | 2 | 300 | 60 | 180 | 75/30/1750 | — |
| rena | 1 | 3 | 3 | 10 | 1 | 360 | 15 | 40 | 60 | 300 | 100/165/2500 | — |
| rena | 2 | 33 | 2 | 12 | 1 | 180 | 1 | 360 | 60 | 300 | 50/150/2000 | 30/70/1000 |
| mion | 0 | 2 | 5 | 12 | 30 | 40 | 4 | 420 | 60 | 180 | 20/9/500 | 50/45/1500 |
| mion | 1 | 4 | 5 | 9 | 8 | 150 | 20 | 60 | 60 | 240 | 35/14/1250 | 15/18/400 |
| mion | 2 | 35 | 5 | 10 | 4 | 360 | 10 | 90 | 60 | 240 | 125/20/2250 | — |
| keiichi | 0 | 5 | 3 | 10 | 8 | 300 | 2 | 420 | 60 | 180 | 75/25/1750 | 100/40/2250 |
| keiichi | 1 | 18 | 2 | 12 | 6 | 360 | 3 | 540 | 60 | 180 | 75/30/1750 | — |
| keiichi | 2 | 34 | 3 | 10 | 15 | 45 | 3 | 360 | 60 | 180 | 35/25/1250 | 100/60/2750 |
| satoko | 0 | 8 | 2 | 17 | 20 | 60 | 16 | 40 | 60 | 300 | — | 25/15/750 |
| satoko | 1 | 17 | 2 | 25 | 10 | 180 | 4 | 600 | 60 | 600 | 15/50/500 | — |
| satoko | 2 | 38 | 2 | 15 | 10 | 180 | 3 | 480 | 60 | 600 | — | — |
| rika | 0 | 7 | 2 | 9 | 8 | 40 | 8 | 90 | 60 | 240 | 40/18/1400 | 30/20/1400 |
| rika | 1 | 19 | 6 | 12 | 60 | 20 | 4 | 150 | 60 | 150 | 10/25/500 | 20/0/1000 |
| rika | 2 | 37 | 2 | 17 | 8 | 270 | 6 | 120 | 60 | 120 | — | 30/35/1250 |
| shion | 0 | 6 | 2 | 10 | 8 | 420 | 1 | 300 | 60 | 180 | 75/30/1750 | 50/30/500 |
| shion | 1 | 20 | 2 | 12 | 2 | 180 | 2 | 600 | 60 | 180 | 25/50/1250 | — |
| shion | 2 | 36 | 3 | 18 | 5 | 300 | 4 | 240 | 60 | 180 | 65/30/1000 | 75/10/1750 |
| tomitake | 0 | 12 | 5 | 12 | 12 | 240 | 1 | 480 | 60 | 480 | 50/150/1750 | 50/2000/1000 |
| tomitake | 1 | 21 | 5 | 12 | 6 | 720 | 1 | 360 | 60 | 300 | 50/20/1500 | 125/30/2500 |
| tomitake | 2 | 42 | 5 | 10 | 30 | 40 | 2 | 360 | 60 | 480 | 15/15/450 | — |
| takano | 0 | 11 | 3 | 12 | 20 | 90 | 4 | 480 | 60 | 300 | 20/10/— | 100/25/— |
| takano | 1 | 22 | 3 | 15 | 15 | 120 | 4 | 210 | 60 | 300 | 75/30/— | — |
| takano | 2 | 41 | 3 | 25 | 6 | 280 | 5 | 120 | 60 | 300 | — | — |
| ohishi | 0 | 9 | 3 | 11 | 6 | 420 | 2 | 360 | 60 | 300 | 100/15/2250 | — |
| ohishi | 1 | 23 | 2 | 7 | 1 | 150 | 1 | 360 | 60 | 120 | 50/0/1750 | 50/0/1750 |
| ohishi | 2 | 39 | 12 | 28 | 4 | 300 | 3 | 360 | 60 | 480 | — | — |
| akasaka | 0 | 10 | 2 | 11 | 6 | 240 | 3 | 480 | 60 | 180 | 50/25/1500 | 100/40/2750 |
| akasaka | 1 | 24 | 2 | 10 | 4 | 360 | 3 | 240 | 60 | 180 | 100/50/2000 | — |
| akasaka | 2 | 40 | 2 | 10 | 4 | 360 | 4 | 480 | 60 | 180 | — | — |
| irie | 0 | 13 | 5 | 20 | 15 | 70 | 3 | 480 | 60 | 300 | 35/10/750 | 100/30/1500 |
| irie | 1 | 26 | 5 | 13 | 2 | 180 | 4 | 360 | 60 | 300 | 40/30/1250 | 100/20/2250 |
| irie | 2 | 43 | 4 | 16 | 10 | 90 | 3 | 480 | 60 | 300 | 35/10/1000 | 100/30/1750 |
| chie | 0 | 14 | 5 | 12 | 10 | 150 | 1 | 270 | 60 | 180 | 50/20/1500 | 50/40/1500 |
| chie | 1 | 25 | 5 | 12 | 4 | 240 | 10 | 120 | 60 | 300 | 15/20/750 | 35/50/1250 |
| chie | 2 | 44 | 5 | 10 | 20 | 60 | 3 | 360 | 60 | 360 | 30/20/750 | 75/40/1500 |
| kasai | 0 | 15 | 5 | 12 | 6 | 420 | 3 | 540 | 60 | 210 | 50/0/1250 | 125/30/2500 |
| kasai | 1 | 27 | 5 | 15 | 30 | 60 | 12 | 180 | 60 | 600 | 15/15/450 | 35/25/1350 |
| kasai | 2 | 45 | 3 | 13 | 6 | 360 | 4 | 480 | 60 | 240 | 100/15/2000 | 150/20/2500 |
| akane | 0 | 16 | 5 | 10 | 5 | 480 | 6 | 300 | 60 | 300 | 100/30/2000 | 75/65/2000 |
| akane | 1 | 28 | 5 | 12 | 4 | 300 | 5 | 360 | 60 | 300 | 100/60/2000 | 75/0/2000 |
| akane | 2 | 46 | 5 | 8 | 5 | 480 | 3 | 360 | 60 | 300 | 100/0/2000 | 100/15/2000 |
| hanyu | 0 | 31 | 2 | 9 | 6 | 360 | 3 | 360 | 60 | 1200 | 40/30/— | 75/80/1750 |
| hanyu | 1 | 32 | 3 | 18 | 6 | 320 | 8 | 420 | 60 | 240 | 35/20/1400 | — |
| natumi | 0 | 29 | 3 | 10 | 6 | 360 | 2 | 360 | 60 | 360 | 75/30/1750 | 75/0/1750 |
| natumi | 1 | 30 | 2 | 12 | 6 | 300 | 1 | 1200 | 60 | 180 | 20/20/750 | 30/45/500 |

Every one of the 46 resolves a bullet-parameter file; there are **78 distinct
(hpDamage, hitRadius, baseDamage, blob[13], blob[14]) value signatures** across 46
weapons, so the roster is not a re-skin of one profile.

### Status per parameter

| parameter | status | source |
|---|---|---|
| attachment count, mesh/texture names, 9 transforms | **recovered** | FUN_00433eb0:96-120, 909/909 cross-checked against the shipped `.ini` mirrors |
| gauge texture + both heights | **recovered** | FUN_00433eb0:67-71 |
| bullet table (magazine, shotNum, type, status) | **recovered** | FUN_00433eb0:148-156 |
| bullet param id = `type*10 + status` | **recovered** | FUN_00433eb0:155 -> FUN_005f80c0:99 |
| **hpDamage, baseDamage, reflect** | **recovered** | block indices 5/0/6, consumed by FUN_00637950:280,426,300 |
| **hitRadius** | **recovered** | record +0x24, FUN_00637950:91,107 |
| **blob indices 13/14** | **values recovered; role unresolved** | FUN_00637950:345-347 reads bullet fields +0x64/+0x68 during hit-resolution; the subsequent state change does not establish tier-shot selection |
| **defender hitstun** | **recovered and wired** | index 10 (record +0x58), FUN_00637950:308 -> victim +0xa0; reaches the fight through `take_damage(..., hitstunFrames)` |
| gauge gain A/B (100 fills a gauge), attacker hitstun | **recovered, not wired** | indices 7/8/9, FUN_00637950:334-347 |
| magazine capacity rule (`num`, else `num*reloadTime`) | **recovered arithmetic, unconsumed** | FUN_00433eb0:135-143 — see the correction above |
| magazine sizing / per-shot cost / refill rate | **PORT RULE** | the block is never read by the corpus |
| charge thresholds as hold seconds | **PORT RULE** | the original uses a 100-point gauge with a 120-frame decay, FUN_00637950:333-347 |
| tier -> which bullet fires | **PORT RULE** | the binding happens in code absent from the corpus; the count itself is the file's |
| projectile **speed** and **lifetime** | **provisional, shared — and provably absent from the shipped data** | see the exhaustive search below |
| **EX move** per weapon | **structure recovered, binding not** | see the EX note below |
| melee range / damage per weapon | **provisional, shared** | not in the item or bullet data |

### Projectile speed and lifetime: searched, and not in the data

This was chased properly rather than assumed. The bullet entity's velocity is three
floats at +0x3C (FUN_005f9090:34-36), and FUN_005f60b0:40-49 orients the bullet by
them, so the field is certain — but it is a **caller argument**: FUN_005f8d50 passes it
straight through to the constructor and has **no caller anywhere in the corpus**, so
whatever computes a launch speed is code this corpus does not contain.

The 20-slot combat block was then enumerated exhaustively rather than sampled: across
the shipped weapons, blob indices 1, 2, 3, 4, 11 and 12 are **zero in every file**, and
every non-zero slot is one of the thirteen already named (base/HP/reflect damage, gauge
gains, hitstun, blob indices 13/14, effect ids, release offsets). There is no remaining slot
that could hold a speed or a lifetime, and no per-weapon frame threshold exists — the
only bullet frame counter, +0x154, is used by FUN_005f60b0:23-27 to pick a looping
effect and by :72 as a time uniform, never against an expiry.

So the speed and lifetime stay one shared provisional policy, and that is now a
**finding**, not a gap left unexamined. Two weapons already say `speed` explicitly in
the table: `hitRadius` varies 9..2000 across the roster, so weapons differ in how hard
and how wide they hit while the ballistics stay shared.

### The EX move: structure recovered, per-weapon binding not

Recovered and implemented in the remake's existing Hypermode EX path
(`Fighter::try_ex_move`, `ShotTier::Ex`), which now reads the charged (level-2) block for
its damage and hit radius like the other tiers:

* move **502** is the EX activation: FUN_00422160 heals to 10000, enters "state 2"
  (`+0x846 = 1`) and swaps the state byte; FUN_00428510:211 dispatches it.
* move **503** is a conditional EX follow-up: while it runs, FUN_00428510:295-297
  pins HP at 9999, grants 60 frames (0x3C) of invulnerability at +0x7AC and force-fills
  the second gauge to 100. This numeric move id is not established as the animation
  for the separate string key `shotFinal`.
* FUN_00639160:47-52 selects 503 over the normal move exactly when the victim is in
  EX-state-2, is dying, and held a full EX gauge; FUN_00422bd0 then plays the queued
  follow-up.

The per-weapon values at blob indices 13/14 are recovered, but their role is unresolved:
FUN_00637950 reads fields +0x64/+0x68 in hit-resolution, not an established tier-shot
selector. The original's binding of a specific weapon to an EX follow-up is also
unresolved; this port does not execute the relevant character move scripts. The EX
therefore keeps its own shared damage rather than a per-weapon one, and says so.

### Honest status

Weapons now differ in **damage, hit radius, hit-stun length, magazine size, charge
length, per-shot cost and volley count**. They do **not** yet differ in projectile
speed, lifetime, or EX binding — and the table above records exactly why, with the
search that established it. That is the line between "recovered" and "not present in
the shipped data".

### Verification

709 checks in `tests/weapon_definition_test.cpp` (28 host tests, all passing): the
FUN_00433eb0 layout against a synthesized buffer; the FUN_005f8510 combat block field by
field; the capacity rule including the unrecovered types; move/ownership and every
rejection path; the 46-combination inventory and the hanyu/natumi two-weapon rule; all
46 shipped item files swept with per-field invariants; representative families spanning
distinct capacities and charge thresholds; per-weapon damage and radius reaching a real
`Fighter`; and a 240-tick match smoke run of **every** legal selection. Linux, Windows
cross-build and web builds succeed. The standalone `--match` 1v1 capture is
**byte-identical** to the pre-change binary, because that path binds no weapon and keeps
the historical shared tuning.

**Bug the tests caught during this work**, worth keeping in mind for the next reader:
`Fighter::main_frac()` divided by the hardcoded `kMainMax` instead of the stock's own
`max`, so any weapon-resized magazine would have driven the HUD bar to nonsense.



These gate every number the other items are judged by, which is why they
come before the visible work.

### A1. `env.dat` spawn: which point, and in which order — **diagnosis changed**

* **What.** The foundation's default (no `--spawn`/`--spawn2`) takes P1/P2
  from `scene.env.points[0]`/`[1]`, and a trace A/B only matched after
  passing `--spawn2` explicitly. Every default-spawned match is therefore
  placed on unverified coordinates.
* **Evidence.** Plan §6a's note ("puts P2 at `(-1363,200,-2200)` where the
  DX9 log has `(-2200,200,-1363)` — x and z swapped"); the wiring is
  `src/main.cpp:762-763, 810-826`.
  **What this pass measured, and it changes the item:** the original's own
  reader is `FUN_004011f0` (`research/decompiled/FUN_004011f0.c:40-64`) —
  five fog ints, four header ints at `0x14`–`0x20`, then **four** spawn
  triples at `0x24`, stride 12, in stored order. `src/assets/scene.h:253-273`
  (`readEnv`) reads exactly the same offsets in the same order, so this is
  **not** a field-order bug against the original. The installed
  `data/stage21/env.dat` holds `(-463,200,-2200)`, `(-1363,200,-2200)`,
  `(-406,200,-105)`, `(-1363,200,-105)` there; `data/stage01/env.dat` holds
  the same spawn region byte for byte (verified: identical from `0x14` to the
  end of the 84-byte file, only the fog header differs) — two points at
  `z = -2200`, two at `z = -105`, which reads like two teams' spawn pairs.
  The DX9 pair starts one int
  earlier (`0x20`) and reads `(x, z, y)`, which is where its
  `(1393,-463,200)` came from. Also: the DX9 side had **no** env.dat parse
  at all — `pre-webgpu-cutover:remake/src/core/scenes.cpp:527-535` is a
  hardcode plus that comment — so "compare against the DX9 loader" has
  nothing to compare, and the plan's word "loader bug" overstates what was
  established.
* **Resolved (this pass).** The consumer is `FUN_00423420`
  (`research/decompiled/FUN_00423420.c`): it copies **three floats
  verbatim** from `scene + 0x44 + slot*12` into the fighter's position
  (`*dest = *src; dest[1]=src[1]; dest[2]=src[2]`) — **no axis swap**, so the
  file's `(a,b,c)` is the vec3 `(x,y,z)` (the middle `200` is the y-up
  height). The slot is read as the fighter's own `+8` field, `+0x14` the dest
  (Ghidra elides the index in `FUN_0041dcb0`'s
  `FUN_00423420(param_1+5, param_1[2])` call — the `+5` is the *dest*
  `fighter+0x14`, the `[2]` is the *index* `*(fighter+8)`; the call shape
  fits exactly, though no writer of the slot field was located, so the
  field's meaning is triangulated inference, not a confirmed store).
  `FUN_0064ab30(i)` creates the four fighters in slot order 0..3 (with four
  consecutive `FUN_0041dcb0` applications beside it), so **P1 takes
  `points[0]` and P2 `points[1]`** — the two `z=-2200` points in
  stage01/stage21. The port's `readEnv` + `points[0]`/`points[1]` default was
  already correct; the old "trace A/B only matched with `--spawn2`" was
  matching the deleted DX9 build's hardcoded pair, not the original's
  env.dat pick. Provenance added to `src/main.cpp` (`initMatch` comment).
  The sketch's `compare_match_traces.py` re-run is moot (the DX9 tree it
  compared against is deleted); port-side determinism is pinned by
  `fighter_script_test` case 14 instead. Pinned by `tests/env_spawn_test.cpp`
  (ctest): both stages' fog/header/points through the port's own `readEnv`,
  the shared spawn region, and the far/near pairing. No code change required.

### A2. The exact viewpoint within `stage01` — the instrument for every print claim

* **What.** Print-parity frames are compared against `battle-hud.webp`
  without the print's capture position being pinned, so part of the
  background RMSE is framing, not renderer error.
* **Evidence.** The camera itself is solved from the print and lands
  (`dist 288.9`, `height 210.9`, `aimHeight 138.3`, 0.0 px residual on the
  four rows that over-determine it, baseline orbit 0) — commit `92156ac`.
  The residual floor is measured: every HUD band is now better than the
  **0.2755 scene-only floor** (commit `37657cd`, `tests/hud_bands.py`).
  **Not found anywhere in the tree or history:** the claim that the camera
  track's spawn was a coarse grid-search match — treat that as unverified
  and this item as "the spawn is not pinned", which the floor supports
  either way.
* **Sketch.** Either solve it from the print's own geometry (two ground
  contacts — the wall base and the building's pixels — back-projected
  against `data/stage01/collision.x`'s ground height and the known π/4 FOV),
  or score the stage's four `env.dat` points through the now-solved camera
  and keep the minimum scene-band RMSE (`tests/hud_bands.py` reports the
  bands; `tests/compare_frames.py` the whole-frame number). Record the
  winner in the capture recipe so later numbers stay comparable.
* **Resolved (this pass, second route).** Four converged captures, P1 on each
  env point with P2 on its pair-mate (far pair `z=-2200`, near pair `z=-105`),
  print cast (rena/mion), `--match --frames=150 --size=800x600`: scene-floor
  RMSE **0.2772** (P1 `points[0]`), 0.2908 (`points[1]`), 0.3162 (`points[2]`),
  0.2961 (`points[3]`). The winner is **P1 at `points[0]`
  `(-463,200,-2200)`, P2 at `points[1]`** — within 0.002 of the documented
  0.2755 floor (**correction 2026-10-03:** the original entry said "landing
  exactly on"; 0.2772 is near, not equal), and corroborating A1
  (P1=`points[0]`) by an independent method. Re-runnable as
  `tests/pin_viewpoint.py` (same four captures, same instruments, winner and
  tolerances asserted — reproduced 2026-10-03 to all four decimals on the
  post-B1/B2 binary).
  Whole-frame context: 0.2567 / 0.2438 / 0.2699 / 0.2478 (config 1 lower, but
  whole-frame is confounded by the mirrored fighter pose and HUD art; the
  scene band is the prescribed instrument). Converged trace eye
  `(-174,411,-2200)` = P1+`(289,211,0)` — the preset offset exactly, and the
  sim faces the fighters toward each other. Gotchas for the recipe: match
  frames render through `gameplay::ArenaCamera` (original preset), **not** the
  static `camera arena at ...` log line (remake-preset seed, overwritten by
  the first tick); `--frames` must be ≥121 (eye converges 10%/call from the
  origin — the frame-1 eye is unconverged); capturing fixes `--dt` at 1/60 so
  the run is deterministic; the match path passes a null collision frame, so
  the eye is unclamped. Recipe recorded in `BATTLE-HUD-SPEC.md` §7.

## Directional, aerial and multi-target melee — 2026-10-04

Issue #10's melee is rebuilt against evidence where evidence exists and against explicit
port rules where it does not. Three premises had to be corrected during the work, and the
corrections changed the implementation.

### CORRECTION 1 — the melee hitbox is a sphere, not a cone

`FUN_00637950` (0x637950) is the hit resolver for bullets **and** players; it never
branches on attacker type, it just reads the weapon/phase record at `*(entity+0x10)`. On
`weapon+0x08` it picks between two tests:

* `== 0` -> `FUN_0063b470`: a hard **3D sphere**, `dist^2 < (30.0 + weaponRadius)^2`.
* `!= 0` -> `FUN_0063b4d0`: point-to-**segment** distance against the same bound, i.e. a
  capsule between two anchors.

Neither has an angle term. An earlier draft of this work invented a 60-degree swing cone;
it is gone, and `melee_rules.h` now reproduces the sphere. The `30.0` is the literal
`0x41f00000` the original passes as the body radius — recovered, not a tuned constant.

The victim's extent is the real vertical limit and it is **anatomical**: `FUN_0063dad0`
builds exactly **two** victim anchors, from the `Bip01_Head` and `Bip01_Spine` bones
(spine at -50.0). A fighter is a head sphere and a chest sphere and nothing else, which
is why legs cannot be hit. The port reproduces the two-anchor shape.

A directional filter **does** exist — `weapon+0x2C` is an 8-way facing mask filtered at
`FUN_00637950:383-385` — but its bit order is unverified and it selects which *inbound*
faces are hittable rather than shaping the volume, so it is deliberately **not**
implemented rather than guessed.

### CORRECTION 2 — move record `+0x04` is not a phase duration

It is a file-loaded constant with **no writer anywhere in the binary's `.text`**, read
only as a threshold against a frame budget (35 sites in `FUN_0043ded0`, e.g.
`move[4] <= player[0xce0]`) — i.e. a **cancel window**. The real duration is at
the animation set's D3DX period, constructed from the matching `.X` rig by
`FUN_0041e180`; trailer `+0x1c` is cross-fade metadata, and `+0x20` gates phase
auto-advance (`FUN_004c57f0` / `FUN_00438310`). The parser now consumes both trailer
values and the event payload. An earlier draft called `+0x04` a frame count and argued
it from a numerical sequence; that animation/shot-chain inference is **withdrawn**
because the relevant move roles are not established by the corpus.
`CharacterMove::cancelWindow` is named for what is recovered.

### CORRECTION 3 — what the melee move records actually contain

`src/gameplay/character_moves.{h,cpp}` parses `data/<char>/NN.dat` (same reader shape as
the weapon files: `FUN_0041e180` and `FUN_005f8510` are the same code twice) and
reproduces each character's move inventory: rena parses 122 records whose ids are exactly
the families `fighter.h` documents. But the `0x28-0x2D` group every character ships has
an **entirely zero combat block**, and `0x2B` is not a melee hit at all — it is the
universal cancel-out move, started from ~2000 sites. Per-character melee radius, damage
and timing are produced by a per-character handler-class **virtual at vtable slot 0x20**
(`FUN_00421410.c:15`, across ~46 classes), not by any file. So the melee **values** are
port rules; only the **shape** above is recovered, and `melee_rules.h` says so.

### What the evidence settled about input

The corpus has **exactly one attack bit** — `weapon+0x28 & 0x100`, used 1378 times — and
no heavy or strong bit anywhere, and the per-character move dispatchers (e.g.
`FUN_00445ee0`) test that one bit and nothing else. The heavy stand-in is now gone from the
code as well as from the design: the action enum, the `FighterState`, its damage value and
its camera-switch use are all removed (issue #10), and the persisted binding schema moved to
v2 with a v1 migration so an existing config still loads. The swing is chosen by the
fighter's situation at the press (grounded, mid-dash or airborne) and by the bound move
table's rows, never by a second key.

### What changed in behaviour

* **Vertical separation** now works: the sphere is 3D, so a fighter off the floor cannot
  be hit by a grounded swing at identical XZ — the issue's headline criterion, which the
  old XZ-only test made impossible.
* **Barriers.** `game::physics::segmentBlocked` (new, on `raycastModelAny`'s early-out
  walk — the same occlusion shape the camera clamp uses) rejects a swing through the
  stage. An absent or empty collision mesh stays permissive, as movement does.
* **Several opponents, each once.** The single `m_didHitThisSwing` flag could not express
  a swing clipping two people; it is now a per-victim set, cleared when the swing ends.
  `Match::step` evaluates every hostile in the volume with ally exclusion still the single
  filter on that loop.
* **Recovery** is a real lockout, and an interrupted attack cannot land.

### Verification

80 checks in `tests/melee_rules_test.cpp` (29 host tests, all passing) cover the issue's
list: aerial separation, attacks through walls (with the same pair proving it connects
when the wall is removed), multiple opponents, repeated contact, interrupted attacks,
recovery lockout, and the situation→family mapping (300/330/340 with their set indices). `fighter_script_test`'s melee section was
updated rather than deleted, so its range and one-hit-per-swing coverage still runs —
including an assertion that a target **behind** the attacker connects, which is the
sphere's actual behaviour and the opposite of what the withdrawn cone claimed. The move
table sweep skips without an install and asserts the melee-has-no-geometry claim when one
is present. Linux, Windows cross-build and web builds succeed; the standalone `--match` 1v1
capture is byte-identical (melee does not fire in it) and the front-end smoke still
reaches `RESULT: ok`.

**Two bugs this work caught in itself**: the vertical test measured the victim's feet
against its own position, so it was always zero; and a per-victim hit set needs Match to
record each hit, so calling `try_melee_hit` twice without `note_melee_hit` correctly
connects twice.

**Next dig, highest value**: the ~46 per-character handler classes behind vtable slot
0x20, which is where per-character melee hitboxes, damage and timing actually live.

## B. Battle visuals

### B1. VFX: the effect table, per-instance cards, trails are vestigial — **implemented (issue #17)**

* **The effect table is recovered.** `FUN_0042eba0` loads **100** descriptors,
  `data/effect/%03d.dat`, into the manager at `scene+0x5210`, with a 1000-entry
  0x1c-byte variant array, a 100-entry 0x38-byte descriptor array and 100 model
  pointers. An **effect id is `type*10 + variant`**: `FUN_0042f5e0` (the manager's
  create method, vtable `0x6a2500` +0x08) indexes the model/descriptor arrays with
  `id/10` and the variant array with the full id. The install ships 22 of the 100
  files, every one of them with exactly one variant.
* **The descriptor carries NO lifetime.** `FUN_0042eec0` reads a version dword, a fixed
  260-byte model path (`0x104`, relative to `data/effect/`), the variant count at file
  offset **0x108** and the per-variant part records — and then takes the lifetime from
  the **model's own first animation**: `FUN_0064e8b0(model, 0)` through the model's
  vtable, divided by the float **0.016** at `0x6a2434` and rounded to whole frames
  (`0x42f412-0x42f423` stores it into `descriptor[0]`). `FUN_00436630` ages the instance
  once per frame (`+0x130`) and retires it when `descriptor[0] <= age`; `FUN_00436150`
  drives the model's animation with `age * 0.016` seconds. That is the plain answer to
  the audit's "all 22 installed descriptors report a zero raw lifetime": the number is
  not in the file at all. The recovered lifetimes are the models' animation lengths,
  0.150–1.000 s — the melee-hit card (`000.dat` → `14.X`) is **0.250 s**, so the port's
  old 12 s placeholder was 48x too long.
* **Variants own parts with frame windows.** `FUN_00436150` walks a variant's part list
  and draws part *p* while `start <= (period ? age % period : age) < end` — the same
  age counter that expires the instance. Every shipped file declares one variant, so the
  port's variant half is a clamp, not a behaviour.
* **The "aura" table is the attachment table.** `FUN_00633ca0` loads **7** models
  `data/aura/%02d.x` into `scene+0x4498` (and 10 trail bitmaps into `scene+0x445c`).
  Their textures name their roles, read from the models' own `TextureFilename` blocks:
  **0/1/5 = マズルフラッシュ 1/2/3** (the three muzzle flashes), **2 = hitblue0000**,
  **3 = 炎上オーラ** (the burning aura), 4 = バケツ, 6 unnamed. `FUN_004205e0:17-32` picks
  the slot from `player+0x7d4`, which `FUN_0042e110` sets from the **move id** — 2 for
  `0x68/0x69/0xcc/0xcd` (hit/stagger), 3 for `0x6a/0x6b/0x6c/0xce` (downed/burning) — and
  otherwise falls back to three mode latches in a fixed priority: `+0x844` → slot 0,
  `+0x846` → slot 5, `+0x845` → slot 1, and nothing at all when the three are clear. It
  draws the model **once per fighter matrix** (11 matrices at `player+0x38c`, stride 0x40).
* **Which firing state sets which latch is recovered, and it is not a tier** (issue #34).
  One attack start per latch: `FUN_00421fe0:20` sets `+0x844` (slot 0), with its sibling
  `FUN_00422060:22` as the other arm of the same state case (split on `fighter+0x3b`);
  `FUN_004220e0:20` sets `+0x845` (slot 1); `FUN_00422160:20` sets `+0x846` (slot 5).
  Which one runs is decided by the fighter's own byte **`+0x318`** and nothing else — the
  battle input action `0x24` dispatches on it (`FUN_0063c2a0:267-277`: 0 → `FUN_00421fe0`,
  2 → `FUN_00422160`, otherwise → `FUN_004220e0`) — and the move-id branches agree:
  `FUN_00428510` runs `FUN_00421fe0`/`FUN_00422060` from its move-id 500 case (`:25`) and
  its 501 case (`:170`), and `FUN_00422160` from its 502 (`:220`) and 503 (`:270`) cases,
  while the 47 per-character handlers (`FUN_0043ded0:134-138` and siblings) call
  `FUN_004220e0` from their own `+0x318 == 1` arm. The byte is **per slot, not per character
  or weapon**: `FUN_0064ab30:36-38` loads it from `scene+0x5328+slot` through
  `FUN_0041dc80:12`, and the story/team setup fills the two CPU slots with `rand()%3`
  (`FUN_006492f0:20-22`). One fighter therefore shows one muzzle model for a whole match,
  and **the original has no charge-tier → slot relation to recover**.
* **The port's tier rule stays a labelled port rule** (issue #34). The port carries no
  `+0x318` byte — no port screen writes it, no shipped data field feeds it, and
  `gameplay/debug_keys.h` already records the same byte as the F4 gauge selector the port
  cannot reproduce either — so the muzzle slot remains tap → 0, yellow → 1, red/EX → 5
  (`src/game/muzzle_slot.h`). Both tables are pinned in `tests/effect_catalog_test.cpp`: the
  recovered one injective over three modes, the port's colliding on slot 5, which is the
  shape a per-fighter selector cannot produce. **The placement half is #17's, not this
  issue's**: the port draws the muzzle card **once, at the shot point**, while
  `FUN_004205e0` draws the selected attachment on the fighter's eleven rig matrices.
  Measured on this tree, the muzzle card is live and drawn (suppressing that one spawn takes
  `effectDrawsAtExit` 2 → 1 and `spawned` 2 → 1 for a single shot), so of the seven shipped
  attachment models three (00/01/05, the muzzle flashes) are drawn, one (03) by the hyper
  aura, and three (02 blue hit, 04 bucket, 06 unnamed) are loaded and never drawn.
* **The eleven draws are the rig's, and the port now makes all eleven** (issue #33). The
  count is not a capacity waiting to be filled: `FUN_0041e180` resolves eleven fixed bone
  names (`Bip00`, `Bip01_Head`, `Bip01_Spine`, `Bip01_L/R_Forearm`, `Bip00_L/R_Calf`,
  `Bip01_L/R_Hand`, `Bip00_L/R_Foot`) into `player+0x64c..0x674`
  (`0x41edfb-0x41ef4f`) once per character, and `FUN_00421010` copies their world matrices
  into `player+0x38c + i*0x40` every frame (`0x42104f-0x421071`). All **92** shipped
  character models carry all eleven and none is partially equipped (enumerated in
  `tests/effect_catalog_test.cpp`), so every shipped attachment is drawn eleven times — the
  old single local-space placement was not an equivalent. The card is now one instance per
  attach point (`src/game/aura_attach.h`), which needed only the rig's posed bone matrices
  (`app.worlds`); on a live hyper aura the card's draw count goes 1 → 11
  (`effectDrawsAtExit` 10 → 40 beside seven live hit cards, the aura card being three
  meshes).
* **Status emitters** (`FUN_0042e110`): timers `+0x7ec`/`+0x7f0`/`+0x7f4` spawn effect
  ids **60/90/80** every 15/10/15 frames (SE 34/37/35 every 60), `+0x7e0`/`+0x7e4` spawn
  **400/390** every 30, and the downed/burning move family spawns **380 every 7 frames**
  (SE 36 every 60) inside a ±50/0..+60 jitter box around the fighter.
* **A shot's impact is in its own record.** `FUN_00637950:221-228` spawns the bullet
  record's **+0x70** field as the impact effect (through `FUN_00435990` → the manager's
  create), and `:232-250` plays its **+0x6C** field as an SE (`FUN_0064ae70` indexes the
  scene's 256-entry `data/se` table at `scene+0x98`; 10/20/30 are three-SE families that
  add `rand()%3`). The port had both fields parsed but **named the other way round**;
  they are now `impactEffect` (+0x70) and `hitSound` (+0x6C). The shipped roster's
  impact ids are 0/10/20/30 — descriptors 000/001/002/003, i.e. `14.X`/`12.X`.
* **Trails are vestigial — the definitive negative result.** `FUN_00633ca0` loads the 10
  `data/trail/%02d.bmp` bitmaps into `scene+0x445c`; the **only** code in the whole
  binary that reads that array is the destructor `FUN_00634520` (`0x63473a`). There is no
  vertex producer, no slot→texture selection and no blend technique to recover for
  trails in `DaybreakDX.exe` — the feature was cut and the loader left behind. The port
  therefore draws **no** trail ribbons, and says so instead of inventing them.
* **Blend technique** is per model: `FUN_00436150` switches on the model's `+0x7c` and
  sets the D3D state set for cases 1–4 (default: `FUN_00651110(1)`); the port's
  `Pass::Effect` (additive, unlit, unculled, cylindrical billboard) is the equivalent
  pass, and the survey in `EFFECTS-BILLBOARD.md` still holds.
* **What changed in the port.** `game/effect_catalog.h` owns the table (descriptor
  header, id mapping, the recovered lifetime arithmetic) and supersedes
  `game/effect_descriptor.h`. Every card is one **instance** of one combat event with its
  own id from a monotonic counter (the old code reused ids as a FIFO and kill-chained the
  previous card on every hit, so overlapping hits retired unrelated effects), the live set
  is **bounded** (`kMaxLiveFxCards = 128`, a counted drop, a tally in the run log) and
  `SceneRenderer::setEffectInstances` draws one copy per live card — a scene model has one
  placement, so before this N cards sharing one `.X` drew once. Effect models are
  `SceneModel::instancesOnly`: they contribute templates, never a base draw, so the load
  draw count does not grow with the table and only the live population adds draws.
  Shots and sparks are **no longer cubes by default** (`--debug-prims` keeps the A/B).
* **Verification.** 40/40 host tests (the new `effect_catalog_test` checks all 22
  descriptors against their models and lifetimes; `fx_cards_test` pins per-instance
  identity, the cap and the drop count). Asset-backed:
  * 1v1, `--screen=battle --frames=11000` on `data/stage03`: 624 cards spawned, 621
    expired, **0 dropped, peak 12/128**, 9937 live-shot refreshes, 0 unshipped ids; the
    round finishes.
  * four-fighter 2v2, `--screen=title --local-players=4 --script=tests/scripts/frontend-4p.txt
    --frames=9600` on `data/stage21`: round over at frame 3600 with 120 spawned, **0
    dropped, peak 6/128**.
  * `--match` (close spawns, a `SHOOT` script) lands a hit and spawns its impact card;
    the documented README `--match` recipe still fails on this install for the known
    issue #9 item gap (takano 011), not for anything here.
* **Port rules (all labelled in code).** The muzzle-flash slot is picked by the shot tier
  because the port carries no `+0x318` fire-mode byte (the recovered selector is a per-slot
  mode — see above; `src/game/muzzle_slot.h` names both tables); the melee hit's effect id is
  the port's existing choice (the original's melee path spawns none); the in-flight shot is
  drawn with the effect its own record names because the original's projectile visual is not
  in the shipped data; the cap's default is sized from the heaviest recovered emitter (8
  cards per burning fighter, 32 for a four-fighter 2v2, ~4x headroom); the spawn jitter
  uses a deterministic hash of (fighter, tick) where the original used `rand()`.
* **Draw-count change (banked recipes).** Effect models are instance-only, so a scene's
  own draw count **drops** by the hidden cards it used to submit and grows only with the
  live population: the `--match`/battle load line went 177 → 169, versus 175 → 169, and
  the front-end 2v2 191 with 4 decals. Pixels are unchanged when no card is live (the old
  hidden cards emitted only degenerate triangles). The versus vignette's scripted card is
  now the recovered `14.X` with its recovered 0.250 s lifetime, so a capture must be
  taken within ~15 frames of a scripted hit: `--versus --frames=60` (the hits are at
  30/55/80 % of `--frames`) instead of the old 5 s placeholder's any-frame recipe.
* **Still open.** Who writes `scene+0x5328+slot` — the source of the `+0x318` byte — for
  slots 0/1 in versus mode: the reader chain is complete (`FUN_0064ab30:36-38` →
  `FUN_0041dc80:12`) and so is the story/team path (`FUN_006492f0:20-22`, `rand()%3`), but
  the writer of the two player slots is not in the dumped corpus (3191 of the binary's 4092
  functions), so whether a player picks it or it is derived from the character is unresolved,
  and until it is, no port can reproduce the original's muzzle choice. Also open: the
  per-effect fade (nothing in
  `FUN_00436150`/`FUN_00436630` ramps alpha — the animation itself carries the fade); the
  descriptor's part windows are parsed by the reference but the port draws a card whole;
  and the in-flight projectile visual, which no shipped data describes.
### B2. The idle pose is a composite: two controllers per model

**Current animation correction (2026-10-05).** The earlier sketch below mixed the timed
effect cursor with phase changes and generalized one observed cross-fade. The phase tails
in `FUN_004c57f0` and `FUN_00438310` increment elapsed count and call `FUN_00421100(next)`
only when rounded D3DX period `<` elapsed and the active set's `+0x20` gate is zero.
`FUN_004212f0` remains the separate timed-effect cursor. Trailer `+0x1c` seeds the old-set
blend countdown and the destination set's value normalizes weights. `FUN_0064ab30` passes
character/slot to `FUN_00649790`; its `(0,2)` branch constructs the class whose vtable
`+0x20` callback is `FUN_0064c8a0`, allowing only `1→31/34/39`. Rena's roster slot 2
joins to item 33, and the matching `02.dat` supplies the blend values. The old universal
eight-tick blend is retracted.
The current implementation and tests are documented in `ANIMATION-SETS.md`.

* **What.** The print's lowered-arm idle is not any single shipped set, and
  the port binds one set per state.
* **Evidence (measured).** Commit `8fae1f9`: round start (set 43) 0.3933,
  walk (set 13) 0.2749, the closest single set in the whole rig (91, from
  the shot finisher) 0.3003 — against idle's own band 0.2747. The original
  clones **two controllers per model** (`FUN_0064d940`: the
  `for (local_24 = 0; local_24 < 2)` clone loop at
  `research/decompiled/FUN_0064d940.c:60-68`; earlier notes cited a
  transposed `FUN_00464d94`, which does not exist — corrected 2026-10-03)
  and the `.dat`
  animation entries carry per-track floats at `+0xc` and `+0x10`
  (`research/decompiled/FUN_0041e180.c:145,149` — offsets verified this
  pass, the *weight* semantics are inferred), cross-faded by
  `FUN_0041f580`. The missing link is `FUN_00421410`'s vtable call
  `(*(*player + 0x20))(oldIdx, newIdx)`.
  `src/gameplay/fighter.h:96-119` documents the binding the port needs:
  `FUN_00421100` binds phase 0 to **both** tracks.
* **Sketch.** Give `xm::Controller` a second track plus per-track weights,
  read the weight fields `FUN_0041f580` actually consumes, bind `phase[0]`
  to both tracks as `FUN_00421100` does, then re-measure the pose band
  against `battle-hud.webp` (the instrument that produced 0.2747).
* **Result (in progress, commit `563a3e3` is scaffolding, not the close).**
  `xm::Controller` already carried 8 tracks with an ordered weighted blend,
  so the first gap was the bind: added
  `Controller::setAnimationBothTracks()` (the `FUN_00421100` starting state)
  and `Fighter::try_switch_animation()` now uses it on both the mapped and
  fallback paths. The weight fields `FUN_0041f580` consumes are the per-track
  table at `player+0x75e0 + i*0x38` (track 0 at `+0xc`, track 1 at `+0x10`)
  plus the cross-fade counters at `+0xae14/0xae18` — read, not guessed
  (the `+0xc/+0x10` mapping derives at `research/decompiled/FUN_00421410.c:30-35`:
  the two `0x3f800000` writes land exactly on those slots).
  **Correction 2026-10-03:** the `563a3e3` entry reported "idle band
  unchanged at 0.2772" — that number is the **scene-floor control band**
  (`tests/hud_bands.py --bands scene-floor` on the post-change capture
  `/tmp/bh_p0.ppm` re-runs at 0.2772), not the pose band (0.2747 in commit
  `8fae1f9`). Scene-floor is pose-insensitive by construction
  (`hud_bands.py`: "scene-only control"), so the reading is vacuous as pose
  evidence; and the no-op is analytically guaranteed anyway (same set, same
  `t=0`, weights 1.0/1.0 through the incremental blend is `mix(v,v,·) = v`).
  **Status at that commit (historical, superseded 2026-10-05):** the
  interrupt-side rebind — `FUN_00421240` (track-1-only) with its driver
  `FUN_004211f0` — and `FUN_0041f580`'s per-tick weight evolution are
  unported; the port binds once per state and ticks both tracks identically,
  so track 1 can never diverge. The earlier attribution of phase advance to
  `FUN_004212f0`'s event cursor and `.dat` phase durations was also incorrect;
  that interpretation is withdrawn. Then re-measure a **pose-relevant** band
  (`per-fighter` / `ring` / `com-bar`, or the `8fae1f9` pose protocol),
  never scene-floor.
* **Historical result (2026-10-03 — first move-change blend port).** The
  interrupt path is now in place: `Fighter::set_state` keeps the old set on
  track 0 and binds the new set on track 1 from t=0
  (`FUN_004211f0`/`FUN_00421240`), `tick_blend()` ramps the weights
  1->0 / 0->1 over `kAnimBlendTicks = 8` ticks (INFERRED duration — the
  `+0xae14/0xae18` initial value was not located; only the decay/rise
  mechanism is read), then `commit_blend()` restores the both-tracks steady
  state. This fixed eight-tick implementation predates the callback and timing
  recovery above; its weights and capture do not establish the corrected behavior.
  `init`/`reset` share a `clear_tracks` fresh bind. A/B against the pre-blend binary on the
  BattleStart(43)->Idle(0) transition, per-fighter band RMSE:
  frame 55: **0.0000** (pre-transition control), frame 61: **0.0536**,
  frame 64: **0.0508**, frame 68: **0.0000** (committed), frame 75:
  **0.0000**, and frame 150 byte-identical — the composite exists exactly
  inside the 8-tick window and converges to the same steady state, so all
  static parity numbers stand. `fighter_script_test` case 12 pins the
  semantics (track-1 target, weight ramp, commit, interruption retarget).
  That test and capture describe the old implementation only; the correction
  above supersedes its blend and phase rules.
* **Overlay negative result (this pass).** The two dev-only tools added in
  `a96f6bf` (`tools/anim_sets_dump.cpp`, `tools/anim_frames_dump.cpp`;
  build with `g++ -std=c++17 -O1 -I src -I third_party/glm
  tools/anim_sets_dump.cpp -o /tmp/asd`) were built to hunt base
  (full-body) vs overlay (arms-only) sets. Run on `data/rena/00.X`: all
  **124 sets are full-body** (typical 37 bones incl. legs+torso; minimum 14
  bones on set 17, none arms-only). No base/overlay split exists in the
  shipped sets, which constrains what the composite can be: same-set binds
  plus cross-faded phase changes, not bone-masked overlays (D3DX tracks have
  no bone masks anyway).
* **Weapon (separate, not started).** The print's raised blade is why the
  capture can't match the band, and it is a distinct task from the track
  composite. Measured on the install: `data/bullet/001/03.X` (rena's weapon-1
  cleaver) has **one** anim set (`dur=880`, verified with
  `tools/anim_sets_dump.cpp`) — the idle pose needs no weapon anim at all,
  the weapon must stay rigid on the hand bone. Three gaps, each blocking:
  (a) the per-weapon local offset (`FUN_00433eb0`, position + rotation
  floats read from `data/item/*.dat` at `FUN_00433eb0.c:93-110` and passed
  to `FUN_0042fe90`) is un-parsed — `loadWeapon` (`src/assets/scene.h`)
  attaches to `Bip01_Prop1` with no offset, so a loaded weapon sits
  un-rotated on the hand; (b) **hypothesis, unverified:** the weapon's ring
  mesh may show its black background instead of vanishing — but the stated
  mechanism ("no alpha-test") contradicts `src/render/scene_renderer.cpp:470`,
  where every textured draw gets `kDrawAlphaTest`, so if the symptom is real
  the cause is likelier the texture's own alpha (or an untextured mesh), and
  no ring mesh has even been identified (the file's 3 meshes are unnamed);
  needs a weapon-in-frame capture before it is claimed; (c) **hypothesis,
  unverified:** the single set was described as "the spin", but no
  rotation-key analysis was done (3 channels on 3 unnamed bones), and nothing
  in the tree drives weapon animations today. None of these is part of B2.

### B3. Mips: feed the shipped levels instead of the box chain

* **What.** The renderer builds a 2x2 box chain for stage textures; the
  original's own filtered levels ship as `X_1.cnv`/`X_2.cnv`.
* **Evidence (measured).** Commit `429ccf8`: shipped levels differ from the
  box chain by ~12/255 (`アスファルト05_1`) and ~1.6/255 (`shadow01_1`);
  only stage dirs ship them (85 groups in `stage01`, 94.7% of its referenced
  textures); the original walks `%s_%d.bmp` and fills one level per file
  (`FUN_00656c80.c:87-118`). `src/assets/cnv.h` has no level concept (it
  decodes one image per name), and `src/render/scene_renderer.cpp:389-426`
  generates the chain with `mipLevelCount`. The siblings are on disk and
  plentiful (`data/stage01/` has 143 `_[12].cnv` names — counted on the
  install), and the asset source reads by name, so they should resolve
  through the bundle path; **not yet verified through a bundle lookup**.
* **Sketch.** In the stage-role texture load, probe the `_1`/`_2` sibling
  names before `.cnv`, and when present upload those levels instead of the
  box levels; keep the box chain as the fallback for the ~5% with no shipped
  art and for every non-stage role. Regression checks: level 0 write stays
  byte-identical, and the stage band against `battle-hud.webp` improves past
  0.254041.
* **Result (done, mechanism faithful, print number honest).**
  `mipSiblingName()` / `mipShippedDimsOk()` (`scene_renderer.h`, unit-tested
  in `lighting_test`: name surgery, the width gate, the one observed misfit)
  plus a substitution loop at the stage-role upload: levels 1–2 upload the
  shipped bytes when the sibling resolves through the same bundle-first
  cache at exactly the halved dims, else the box level stays. The chain
  truncates to the shipped depth — `D3DXCreateTexture`'s `MipLevels=1+#files`
  (`FUN_00656c80.c:87-118`: load loop breaks on first miss, per-level copy
  gated on width) — so sampling past the smallest shipped level clamps
  there as on the original. Verified live: 166 substitutions in the stage01
  capture (bundle path — the sketch's "not yet verified" is now verified);
  dims survey: all 85 `_1` exact, 57/58 `_2` exact, the one `_2`-sized-like-
  `_1` truncating to a clean 2-level chain. Draws unchanged (177/177/0);
  level 0 is the same bytes through the same path by construction.
  **Measured (pinned recipe, SPEC §7):** overall 0.2567 → **0.2596**,
  hud-all 0.2483 → 0.2522, scene-floor 0.2772 → 0.2777 — the print number
  moves the *wrong* way, and the sketch's "past 0.254041" is not met (that
  figure itself does not reproduce on the pinned recipe: current baseline is
  0.2567 — flagged, not chased). Two variants were tried first (full chain
  with shipped L1/L2: 0.2591; truncated: 0.2596); truncation ships as the
  structure-faithful one. **Why this is instrument error, not render error:**
  grain energy in the wall band reads print 4.33 < box 5.63 < shipped 7.60 —
  the lossy resampled print is smoother than *both* renders, so the overall
  RMSE rewards blur and cannot adjudicate the sharpness the shipped levels
  restore (visual triple-check: print mush vs box mottle vs shipped grain).
  The bytes are authoritative; the +0.003 overall residual is recorded as
  print-pipeline confound. Open and un-actionable: whether D3D9 and WebGPU
  pick identical LODs at these pixels (same trilinear math, possibly
  different derivative conventions) — no experiment available distinguishes
  it from correct rendering, so it stays a note, not a task.

## Renderer options (issue #21) — status 2026-10-05: row 0 landed, rows 1-2 open

`FRONTEND-PLAN.md` §2.11 gives the three rows the options screen draws above the window toggle
(`FUN_00403470.c:25-53`: toon `DAT_006cfcec`, shadows `DAT_006cfcea`, texture resolution
`DAT_006cfceb`). This is what each one actually gates, from its read sites, what the port now
does with it, and what is still open.

### Row 0 — toon shading (`DAT_006cfcec`) — DONE

* **The row's own name is recovered, not inferred.** The baked label sheet
  (`data/config/0002.cnv`, the sheet `FUN_00403470` draws) reads トゥーンシェーディング on row 0,
  and the help sheet (`data/config/0003.cnv`, the same screen's footer) reads
  「トゥーンシェーディングを使用するかどうかを←→で選択します。トゥーンシェーディングを使用しない
  場合、動作が少し軽くなります。」 — "choose whether to use toon shading with ←→; without it the
  game runs a little lighter". The cost profile it admits is the second geometry pass below.
* **Read site.** `FUN_006396f0:126-140`, the per-character draw inside the battle view loop:
  `FUN_00651110(0)` selects the plain technique, and with the toggle on it selects **mode 1**
  for a single view or **mode 7** for a split view (`FUN_00651110:9-30` maps 1 and 7 to
  `FUN_00652220`, with `+0x28` carrying 0 or 7). `FUN_005f60b0:121-126` reads the same global
  for the material path and calls `FUN_00651110(0|1)` there.
* **What the technique actually draws.** OFF (`FUN_006519f0`) is the single-pass device path
  the port already reproduces. ON (`FUN_00652220`) is a **two-pass D3DX effect**: the ten
  effects are precompiled blobs embedded in the exe (`FUN_0064ff80` calls `D3DXCreateEffect`
  on `DAT_006a5f68`/`0x6a6cd8`/`0x6a7b10`/… into the singleton at `0x6d13c0`; modes 1 and 7
  use blobs `0x6a5f68` and `0x6a9bd0`, the material path uses `0x6a6cd8`). Its pass loop is
  `SetRenderState(D3DRS_CULLMODE, pass == 0 ? 2 : 3)` (`FUN_00652220:50-55`, state `0x16`:
  D3DCULL_CW then D3DCULL_CCW) with `SetTexture(0, NULL)` and a per-material `MaterialColor`
  in pass 0, and the material's own texture as the effect's `Tex0` in pass 1. Disassembling
  the blobs with the shipped `d3dx9_25.dll` (`D3DXDisassembleShader`) gives both passes:
  * **pass 0 = the outline hull** (blob `+0x934`): a preshader computes
    `c5 = MaterialColor * 0.285714286`, and the vertex shader offsets the clip position along
    the world normal scaled by clip `w` — `mad oPos.x, n.x, 0.00275*w`, `…y, 0.00366666657*w`,
    `…z, 1e-6*w` — so the rim is a constant ~1.1 px at the original's 800x600 (the constants
    are `0.011/4` and `0.011/3`, the same pixel width in x and y). It has **no pixel shader**,
    so the flat darkened colour reaches the blender unchanged; drawing the hull's *back*
    faces (CULLMODE 2 on CW-front assets) leaves only the rim that sticks out past the
    silhouette after the model's depth wins. This is the outline the player sees.
  * **pass 1 = the toon-shaded surface** (blob `+0x628` / `+0x4d0`): the vertex shader
    computes `oT1 = (min(max(N·(0, 0.287347883, 0.957826257), 0), 1), 0.5)` from the
    **object-space** normal (the light direction is baked into the shader, `dp3 r0.x, v1, c9`)
    and `oD0 = MaterialColor`; the pixel shader is
    `tex t0/t1/t2 ; sub r0, v0, 0.1 ; add_sat r0, t1, r0 ; mul r0, t0, r0`, i.e.
    `albedo * saturate(ramp + MaterialColor − 0.1)` — no ambient term, no light colour and no
    vertex colour in this path.
* **What `MaterialColor` is, and what the ramp is.** The runtime material records are verbatim
  `D3DXMATERIAL` copies (`FUN_00661f60:90/116`: `operator_new(count * 0x48)` +
  `memcpy(dst, src, count * 0x48)`), so the float4 handed to the effect at `material + 0x30`
  is **D3DMATERIAL9.Emissive** (the layout is Diffuse +0x00, Ambient +0x10, Specular +0x20,
  Emissive +0x30, Power +0x40, texture name +0x44), and the pass loop's
  `*(float*)(material + 0x40) == 0.0` test is "Power == 0". The ramp is the technique's
  `Tex1` parameter, bound from the singleton's `+0x30` — the texture `FUN_00650410:19` loads
  from `data/directx/toon.bmp` (the install ships it as `data/directX/toon.cnv`; the bundles
  convert .bmp to .cnv, `assets/cnv.h:258`). The plain technique never binds `Tex1`/`Tex2`:
  the only references to `0x6d13f0`/`0x6d13f4` in the whole `.text` are the effect
  techniques' `SetTexture` calls. So the ramp is part of the ON path only, loaded once at
  device setup because the effects are.
* **What the port does now.** `SceneRenderer::init` uploads the shipped bitmap once
  (`AssetSource::resolve` over both spellings + `xm::decodeCnvImage` — the same bundle-first
  read and the one CNV decoder the texture cache uses, no new loader), 64x64 RGBA8Unorm with
  a single mip level, and binds it beside the camera (group 0, bindings 1 and 2). For the
  `character`/`weapon` draws the scene queues a second draw of the same submesh as
  `Pass::Outline`, and the shader implements both recovered passes: the hull offsets the clip
  position exactly as the blob does and returns `emissive * 0.285714286`, and the surface
  returns `albedo * saturate(ramp(object-space N·L, 0.5) + emissive − 0.1)`. The per-draw bits
  are decided per frame in `fillDrawData` from `Appearance::toon`, so the toggle is a
  draw-time switch with no re-upload; with it off the outline draws are never submitted and
  the lighting is the fixed-function term bit for bit. Options row 0 draws the original's own
  state cells (`FUN_00403470:25-26`: the cell row is the toggle value at x=368 and its
  complement at x=464) and flips live; `[render] toon` persists it as settings v3.
* **PORT RULES (labelled, issue #21):**
  1. **Eligibility.** Only the `character` and `weapon` roles get the hull and the ramp. The
     original selects the technique at the per-character draw and on the object material path
     that draws a fighter's body and weapon together; the stage keeps its fixed-function
     lighting. The port's role is the stand-in for that technique switch, which no material
     term carries. Measured: a stage-only frame is byte-identical with the toggle either way.
  2. **Ramp coordinate and sampler.** `u = saturate(object-space N·L)`, `v = 0.5` (the bitmap
     is constant down its columns), read from `.r`: the original's ramp target is a luminance
     surface (`FUN_00650410` allocates a `D3DFMT_L8` target), so the greyscale value is the
     term. The sampler is clamp + linear, because `u = 1` has to read the bright end and WRAP
     would blend it with the dark end; the original's effect-file sampler state is not
     recoverable from the dump.
  3. **The hull is the same geometry, not a second mesh.** The original's two passes draw the
     same submeshes, so the port queues one extra draw per eligible submesh sharing the
     vertex/index buffers and the palette slice, and draws all hulls before the surfaces
     (the original interleaves per character; depth testing makes the global order equivalent
     and it keeps the pipeline switches to one per pass).
  4. **No synthesized ramp.** Without the game data the bitmap cannot be loaded: the sampler
     binds the 1x1 white fallback, the bits are never set, and ON degrades to OFF with one
     stderr line. A constant standing in for the shipped bitmap would be a false claim about
     what the original samples.
* **Verification.** `toon_ramp` (CTest; skips 77 without a renderer or the install) renders
  the same bind-pose character frame with no flag / `--no-toon` / `--toon` at 800x600 and
  asserts the default is byte-identical to OFF; that ON adds a thin dark rim outside the OFF
  silhouette (measured 1152 rim px with mean luminance 35.9 against a 72284 px silhouette of
  mean 108.2 — 1.6% of the silhouette, so a rim and not a filled hull); that no silhouette
  pixel is lost; that ≥50% of the surface pixels changed (the ramp shading, measured 71787 of
  72284); that a stage-only frame is byte-identical either way; and that all four views of a
  4-view 2v2 battle frame change (4907/5123/3000/2487 px). Verified the pin fails when the
  hull stops being submitted: "rim 0 px … the outline no longer draws". `user_settings_test`
  and `frontend_config_test` cover the v2→v3 migration and the option round trip. The
  pre-change binary (`c996291`, built separately) and this build produce **byte-identical**
  frames with the toggle off for the bind-pose character, stage01 and both 960x540 battle
  captures (md5 `eb191e0f`, `a7049fe3`, `bcfd50ca`, `b6c99cbf`), so no banked capture moves.
* **Left for this row.** Nothing functional. One deployment note: a browser pack built from
  a single asset directory (`scripts/make_pack.py`) does not carry
  `data/directX/toon.cnv`, so the toggle is inert there until the pack includes it — the
  same "no game data" path as rule 4, not a silent substitution.

### Issue #25 — the NPR experiment harness (2026-10-05) — DONE, OPT-IN

Issue #25 is an experiment issue: it asks which modern anime/NPR techniques suit Daybreak,
and its deliverable is controlled A/B evidence plus a recommendation, not a new art style.
The harness landed as `--npr=<spec>` (one modifier per experiment: band curves, shadow
tint, character key light, secondary lighting normals, generated shadow mask, stylized
specular, rim, outline width) plus `--pose-step=<n>` and `--bench=<n>`. Everything is
draw-time state on draws that already exist, and **`--npr` is off by default: the bind-pose
capture with no flag and with `--npr=off` is byte-identical to the pre-#25 binary**
(md5 `eb191e0f`), which `tests/npr_experiments.py` pins along with the specific visual
property of every technique. The experiments take a second vertex entry point (`vs_npr`)
rather than a branch inside `vs_main`, because a branch — or a `select` — changes how the
driver compiles the unmodified path and the OFF frame moved by a pixel when that was tried.
The secondary lighting normal is built once at upload from the bind-pose geometry
(`src/render/npr_normals.h`, device-free) and rides its own vertex stream, so no existing
vertex stride changes. Full evidence, per-arm cost, the authoring gaps (the generated mask
and the generated normals are placeholders for authored data), the four experiments that
were deliberately **not** run (J stepped pose, K unlit VFX, L impact presentation, M
stage-aware colour) and the recommendation: `foundation/docs/NPR-EXPERIMENTS.md`; captures:
`tests/npr-evidence/`.

### Row 1 — shadows (`DAT_006cfcea`) — IMPLEMENTABLE, NOT A BLOB

* **Read site.** `FUN_006396f0:115-119`: with the toggle on, the view loop calls
  `FUN_004207d0()` **once per fighter** (four times) *after* `FUN_00651110(2)` and before the
  main character draw. `FUN_004207d0` is `FUN_0064e1a0(matrix)` + `FUN_00434970()`, and
  `FUN_00434970` draws the character's own two sub-objects (body and weapon) through their
  virtual draw. So the original's shadow is a **second draw of the character's meshes with a
  projection matrix and the flat technique that mode 2 selects** (`FUN_00652880`) — a
  projected character shadow, not a blob and not a shadow map.
* **Port plan.** Reuse the model pass with a ground-projection matrix and an unlit dark
  variant of the model shader; it needs a shader variant plus a per-fighter shadow draw in
  the scene pass, which is why it is not in this pass.
* **Status: not implemented.** Until this slice lands, row 1 keeps its own message rather
  than the generic `UNAVAILABLE`: the honest one is a projected character shadow, recovered
  but unimplemented (e.g. `SHADOW: NOT IMPLEMENTED (PROJECTED CHARACTER SHADOW)`). The
  toggle must not be offered as working before the second draw exists.

### Row 2 — texture resolution (`DAT_006cfceb`) — A LOADER POLICY, NOT A RUNTIME SAMPLER

* **Read site.** `FUN_00647e00:96-101` (scene setup) and `FUN_00402be0:111-114` (the options
  screen) both call `FUN_00687260(2)` when the toggle is off and `FUN_00687260(0)` when it is
  on. That function is a one-line setter (`*this = value`), and the field it writes is read by
  the texture loader: `FUN_00687010`/`FUN_006871f0` build the DDS pixel-format descriptor and
  allocate the surface from it.
* **What it is.** The toggle chooses the **texture preparation quality** at load time — full
  resolution (2) versus a reduced preparation (0) — not a sampler or mip state applied at
  draw time. WebGPU can express it, but only where the port prepares textures: a texture-size
  or mip policy in the texture cache, which must rebuild the scene's textures when it changes.
* **Status: not implemented.** The honest port equivalent is a texture-cache policy, so the
  row keeps its own message rather than the generic `UNAVAILABLE` — it is a load-time
  texture policy the port's cache cannot rebuild in place yet (e.g.
  `TEXTURE RESOLUTION: NOT IMPLEMENTED (LOAD-TIME POLICY)`).

## C. Animation states

### C1. Guard / Jump mapping (RESOLVED — issue #18; TagOut reframed, see below)

* **What.** Guard and Jump both reported the set-0 fallback instead of their
  real animation; a third state was a mistaken mechanic.
* **Jump — recovered (issue #18).** The air chain is three move rows the move
  executor advances by physics: live `DaybreakDX.exe` (original, md5
  `a136ddc01bd7ef355b759b88ac89e02c`) via the bridge, `FUN_0043ffc0` case
  `0x28` binds `0x29` once `FUN_004218c0`'s air gate passes, and case `0x29`
  binds `0x2a` once `vy < 6.0`/tick (`0x40c00000`) with the row's second
  section active; `FUN_00421080(0x28)` in the act function's airborne branch is
  the entry. Their `NN.dat` phase tags are the shipped jump clips — 40 → `[2]`
  (startup), 41 → `[3,4]` (takeoff, up momentum), 42 → `[5,43]` (down momentum,
  falling) — and `FUN_004218c0`'s own frame/phase budget is the one piece not
  carried, so the port plays row 40 for the launch tick and then follows vy
  (apex literal 6.0/tick = 360 u/s). `FUN_004235d0` is steering (relation index
  + relative angle from `FUN_0041f580`), not the jump driver.
* **Guard — recovered as "no selector" (issue #18).** Live `FUN_00637950`'s
  blocked branch (`~:535-549`) writes the hit registry, the per-slot `0x100`
  guard marker and `[victim+0xaf30]`, and calls no move bind and no
  effect/voice helper. The block predicate is
  `(|bearing - facing| > 45 || [weaponword+0x28] & 0x2000) &&
   ([weaponword+0x28] & 0x400) && !([attackerweapon+0x2c] & 8)`. Which physical
  button those two weapon-word bits belong to is NOT recoverable: the word is
  not the device button word (that one carries bits `0x10 << slot`, live
  `FUN_00657390:219`, and only its slot-4 bit `0x100` is ever tested for game
  actions), those two bits appear exactly once each in the whole corpus, and the
  word's builder is not located. The port therefore keeps its own Guard action
  and holds the playing clip (`anim_no_selector()`), which is a report, not a
  guess.
* **Attack rows (issue #31).** The three attack selectors the port already
  resolves (300 grounded, 330 mid-dash, 340 airborne) now play their own table
  rows; only the *choice* among them remains a port inference. Before this the
  presentation path honoured 300 alone, so a live aerial swing bound move 340
  for its hit test and then showed set 0 while airborne. Which of `0x100`'s
  neighbours gate the original's `FUN_00445ee0` transitions (300→301→302,
  20→330/331, 23/24→330/331, 329/333/44→340) is still open.
* **Evidence trail.** `FUN_00428510` (49-case move-id switch, count from
  `8fae1f9`) is the per-move executor, not the selector hunt it once looked
  like; `FUN_0043ded0` and its 46 per-character twins are the per-character act
  functions (they read the AI request fields `+0x280..+0x2bc` and the human
  intent fields `FUN_0041efe0` writes, so they serve both controller types).
* **TagOut — reframed, not mapped (owner observation 2026-10-03).** There is
  no character swap: control never transfers between fighters, and the only
  switch mechanic is the reticle target cycle (`FUN_00421e30`, which also
  plays the 0xd/0xe/0xf switch cues). The swap story traces to old PT
  `remake/docs/roadmap.md:127-128`, an inference from voice-dir names
  (`tagfront`/`tagback`/`tagOK`) that `remake/docs/game-spec.md:93` and then
  `fighter.h` repeated. Those keys sit between `tactics` and `thank` in the
  16-byte key table — a team-communication cluster (orders, callouts,
  thanks), consistent with COM-partner coordination, not a swap. Consequences
  landed: the `TagOut` state (never entered by anything) keeps its fallback
  with corrected comments; LockSwitch tap now cycles the camera target in
  match mode beside the DX9 combo (camera-only in this 1v1 port — shots fly
  the facing, which tracks the single enemy; hold-for-ally needs allies).
  Corrected by issue #51: the tap re-picks the COMBAT target only and never the
  camera, so this bullet's "cycles the camera target" no longer describes it.
  "recovery" stays as the state's trace name (the voice key exists; the
  state never occurs, so no trace changes).
* **What is left.** (a) The projectile and TagOut selectors, and the side/air
  dash pair (moves 23/24; their `[22,23,24]`/`[19,20,21]` tags are air-dash rows,
  not a guard pose). They keep the visible `anim_fallback()`. (b) The physical
  identity of the two guard bits, which needs the weapon-word builder. (c) The
  fresh AttackA selector's branch conditions.

## D. HUD leftovers

The HUD's remaining gaps are listed verbatim in commit `0294916`'s "Still
open, deliberately" paragraph; the pointers below are from
`BATTLE-HUD-SPEC.md`. Rewritten 2026-10-03 in plain language: each item now
says what you SEE on screen, not just which function draws it.

### D1. The top-right counter `181` — DONE (it is the render-FPS counter)

* **What you see.** Yellow 3D digits at the top-right edge reading `181`.
  Owner-confirmed: this is the **rendering FPS counter** — fixed-timestep
  logic underneath, uncapped rendering on top (which is also why netplay
  stays deterministic), and the number floats with machine speed, render
  only, never logic.
* **How the original draws it.** `FUN_006396f0` (the per-frame battle render)
  draws `DAT_006d18a4` right-aligned at x=800, y=0, scale 0.5
  (`FUN_00431b20(DAT_006d18a4, 0x44480000, 0, 0x3f000000, 0)`), unconditionally
  — no gate surrounds the call, so it is always on in battle. The value is a
  render-thread present count (`FUN_006580a0` bumps `DAT_006d18a8` per
  present in a worker thread; the per-second reduction into `DAT_006d18a4`
  was not located and does not matter — the port measures its own presents).
  A sibling counter draws two `FUN_0063bf40` counts at x=20 top-left; its
  values are unmapped (decompiler arg confusion) and out of scope.
* **What the port does.** `HudFont::SmallYellow` (`hud_atlas.h`: P00 row
  y288–319, 32 px cells, pitch 32, leading 0 — measured off the atlas; the
  old Q5 guess bands were wrong, and a 28 px pitch fails at cell 6),
  `HudState::fps` (default 60), drawn in `composeBattle` at (800,0,0.5).
  The App meters wall-clock renders over a rolling half second; fixed-dt
  captures pin the display at 60 so `--out` frames stay deterministic
  (a live counter would make `hud-all` nondeterministic run to run).
  Unit-tested (`hud_sprite_table`: the "181" layout — units x=784 stepping
  16 px left — plus the font spec). Measured: our "60" ink is game
  (772–796, 2–7) against the print's (763–793, 2–7) — same height (scale
  confirmed), same right edge family (anchor 800 in both; 3 px is
  threshold noise), narrower only because "60" is two digits. Draws
  unchanged (177, HUD is one batch).
* **Not this.** The `DAT_006cf3c4` top-centre counter and `FUN_0064c1e0`
  are a different element; the sketch's old next step is retired.

### D2. The mirrored second ring — DONE (counter-rotating arcs)

* **What you see.** The red ring around the targeted fighter is really two
  arc groups sweeping opposite ways (in the print: arcs above, below, left
  and right of her — one P03 four-arc cell drawn twice, counter-rotated).
* **How the original draws it.** `FUN_00643230` draws the P03 ring cell once
  rotated `+(frame/2 + 9*hud+0x30c)`, then — gated on local_31 — draws the same cell at the
  same anchor/scale rotated `-(frame/2)` with NO 9-term (`0x643545-0x64354b`).
* **What local_31 actually is (corrected by issue #49).** The gate is NOT "this fighter is
  the viewer's locked target". Live `DaybreakDX.exe` (md5 `a136ddc0…`), `0x6433b0-0x6433f7`:
  it looks up element 0 of the drawn fighter's own `+0x2f0` container, compares that
  object's `+0x300` with the fighter's `+0x300` (`0x6433d7-0x6433e3`), and ANDs it with
  `owner+0x304 < 0` (`0x6433a3-0x6433ad`, `SETGE`/`JNZ`). So the copy appears when the
  drawn fighter is the one that container's element 0 faces **and that fighter has no lock
  of its own** — the opposite of the `f.target` reading this entry used to carry, and not
  "both fighters aiming at each other" either (nothing in the ring path reads another
  fighter's `+0x304`; the earlier symptom was simply that the port gave everyone a lock at
  round start, so the copy was always suppressed).
* **What the port does.** `ui/hud.h`'s `hudRingCounterRotates()` keeps the drawing in
  `composeFighters` under the port's per-view mapping of the first half of the gate
  (`HudFighterRole::Owner`) AND `!locked`, and `hud_layout_test` pins both halves. Verified
  structurally (same cell/anchor/scale, mirrored rotation, correct gate) and visually
  across frames (arcs at ±50° in frame 100 vs ±75° in
  frame 150 — counter-rotation live). Single-frame RMSE is phase lottery
  (0.3888 → 0.4025: added red pixels at non-print phases), so the band is
  reported, not chased — same confound class as the mirrored fighter pose.
* **Resolved 2026-10-03.** The lock-switch writer/decrement and pulse
  transform are implemented and tested; see the implementation update above.

### D3. Other fighters' com bars, round countdown, team stings — PARTIAL (1v1 transients implemented)

* **What you see (and don't).** The print shows exactly one com bar with its
  `com` tag, over the targeted (distant) fighter — which is exactly what the
  port draws (target's drawer, `0x643e38`: frame + ghost + live fill + tag
  cell). Nothing is missing in this frame.
* **Why the rest stays out.** The "other-fighters bar" (a different sprite
  set in `FUN_00643230`'s per-fighter loop) only matters with 3–4 fighters
  on screen (allies, extra enemies); this port's match is 1v1, and the
  followed fighter correctly carries no bar. Round countdown (`3 2 1`) and
  team stings (`赤組/青組 大勝利`) are transients absent from the print and
  need new gameplay state first (round timer, winning team in
  `gameplay::Match`/`MatchEconomy` driving `HudState`); their art and layout
  are already surveyed (`BATTLE-HUD-SPEC.md` §5 item 7, `P09/P04/P05/P08`
  via `FUN_00633ca0.c:77-86`). No parity pixels depend on any of it.
* **Sketch.** (a) Other-fighters bars come with the third fighter, not
  before. (b) Countdown/stings come with `Match` round state — gameplay
  breadth, not parity; schedule it with the front-end track (E), not here.

## E. Front end (`FRONTEND-PLAN.md` is the spec)

The plan's own order: **select page 0 → select page 1 → the rest**. Title
already landed on the screen stack (`src/ui/screen_title.*`, commit
`c67ead3`), so new screens follow that pattern: device-free update returning
the next screen id, a factory for construction, tests against fakes.

### E1. Select page 0 — IMPLEMENTED (four-fighter presentation landed, issue #13)

* **What.** One state machine for team → character → weapon → hypermode →
  PLAYER/COM → ready, covering **six of the 23 prints** (team-select,
  char-select, weapon-select, hypermode-select, controller-select,
  ready-confirm — plan lines 102-107, 1152).
* **Evidence.** Layout and per-slot states: plan §2.3-2.8 (lines 338-507);
  file plan: `src/ui/screens/select.cpp` (line 1092). The **16-cell roster
  positions** are no longer an open extraction job: they are
  `DAT_006b71d0`/`DAT_006b7210` × 48/36, the table the port has carried as
  `kSelectRosterX/Y` since the icons landed, and issue #41's cursor rule pins
  them as the selection's own coordinate space. What is still unread in
  `FUN_0040b2b0` is its per-panel **cell/anchor** set (plan §7 item 1, lines
  1247-1252); the second open geometry is the team-select diamond's **y anchor
  150 px below** the measured centres (pivot vs quadrant origin, plan §2.3
  lines 355-359).
* **Sketch.** First transcribe `FUN_0040b2b0`'s anchor/cell tables
  (mechanical read), reconcile the diamond y anchor against the print, then
  implement the screen on the landed stack. The roster grid formula is
  plan §2.17.
* **Lifecycle (issue #45).** The selection belongs to the select *scene*, not
  to the process. The original destroys the current scene and constructs the
  next one through the factory on every switch (`FUN_00657c80:51-58`), and
  scene 3's constructor initialises every field the scene owns —
  cursor `+0x3c48`, character `+0x3c58`, panel owner `+0x3c80`, controller
  phase `+0x3c90`, owned panel `+0x3ca0`, controller `+0x3cf8`, weapon
  `+0x3d08`, hypermode `+0x3d18`, costume `+0x3d28`, ready `+0x3d38`, the
  per-slot flags `+0x3cb0`/`+0x3cd4`, the stage page flag `+0x3c40` and the
  stage pair `+0x3d48`/`+0x3d4c` (`FUN_00408330:143-158`; the first-pass
  corpus and the live original on the Ghidra bridge agree). Versus mode's
  battle returns scene 3 when the match is over (`FUN_00403b70`), so a
  title→select trip and a result→select return both start empty. The port
  therefore clears on **entry** (`ui::FrontendState::beginSelection`, called by
  the select screen's own constructor) and keeps what the original keeps
  outside the scene: the stage page's settings (`DAT_006cf3c0` /
  `3b8` / `3bc` / `3b0` / `3b4`), the RNG, the round's outcome data and the
  penalty flag `DAT_006cfdf1` (issue #20). A pause-menu *Rematch* never
  constructs the select scene, so it still replays the same fighters with the
  same settings (that is what `pinFrontendStage` is for).
* **Character-select cursor (issue #41, 2026-10-06) — recovered, and it replaces
  the discrete grid walk.** `FUN_00409340` case 2 (`:232-300`) slides a FREE
  cursor at a fixed **rate per call on the sign of the stick** (magnitude is
  unused, so `ScreenInput`'s booleans are the whole input): 4.0/tick
  horizontally (`0x40800000`) and 3.0/tick vertically (`0x40400000`), clamped to
  `[-200,200]` (`0xc3480000`/`0x43480000`) and `[-60,300]`
  (`0xc2700000`/`0x43960000`). While the stick is centred, a cursor within 20
  units (400 squared) of the *currently selected* character snaps exactly onto
  it (`:257-270`); the selection itself is re-made every call from two squared
  radii — the first icon within 50 units (2500) is the fallback and the first
  within 30 (900) overrides it, and neither means `character = -1`, the cursor
  resting in empty space with nothing selected and no SE (`:294`), while a change
  of character plays `FUN_0064aed0(2)` (`:284-288`, `:296-299`). Two **port
  rules** sit on top: an empty panel's team confirm seeds the phase on character
  0 and the cursor onto that position (`:114-127`, so issue #45's
  empty-on-entry selection needs no special case), and the character confirm
  **refuses** while `character == -1` — the original instead rolls a random
  character for the empty panel (`:305-317`), which is this port's stage-page COM
  autofill, so refusing leaves the panel to it. The marker now rides the
  cursor's own position instead of the selected icon's (PORT RULE, the anchor
  only). Device-free test: `tests/select_cursor_test.cpp`; Shion and Akasaka —
  the off-grid icons the report named — are reachable in 12 + 36 ticks of held
  direction, and the four scripted gate runs were re-measured with the same
  characters selected (`RELEASE-CHECKLIST.md` §3). Property worth knowing: with
  a 50-unit select radius and a 60-unit minimum icon spacing, **no** position
  between two icons can be unselected — the empty-space state only exists
  outside the diamond.
* **Row/entry transitions (issue #43, 2026-10-06) — recovered, and the issue
  named the wrong one of the two.** The select scene has **two** entry
  transitions, and #43's report ("the weapon/hypermode/controller rows are
  swapped in instantly") describes the second, while #43's recovered animation
  is the first:
  1. **The 16 roster icons' entry reveal.** `scene+0x3d50+i*4` ramps 0 -> 1 in
     steps of 0.1 and slot `i` only starts once the tick has passed `i + 5`
     (`FUN_004090a0:24-26`, same loop `FUN_0041bae0:37-40`; the constructor
     zeroes the array and the tick, `FUN_00408330:0x408c96`/`0x408eff`), so the
     slots start one tick apart and each settles ten ticks later. The draw
     consumes the value at `FUN_0040b2b0:96-104` as the **PAIR**
     `FUN_0040da60(value, 2.0 - value)` — `+0x84` = x scale, `+0x88` = y scale,
     which `FUN_00655830:0x65583f-0x6558db` multiplies into the quad's pivot and
     cell size (`x0 = x - pivotX*sx, w = srcW*sx`, likewise y). It is a scale,
     **not** an offset: the sprite is `v` times as wide and `2-v` times as tall.
     `FUN_0040da60` is called on the objects at `scene+0x150c+i*0xa0`, whose
     `i%02d.bmp` textures and (40,80) pivot come from `FUN_00408330:0x408be7-
     0x408c14` — the 16 chibis of the diamond, which is where the port applies
     it. The draw's own other argument — the atlas cell `(2,1)` while `v < 1`,
     else `(0,0)` — selects the flashing cell: that half, and the screen flash,
     stay issue #44's (confirmed there: "the same per-slot ramp").
  2. **The phase rows' slide.** `FUN_00409340:589-595` — the per-panel update's
     own tail — restarts `0x3cc4[controller]` at 300.0 (`0x43960000`) whenever
     that controller's phase changed during the call, then takes 20.0
     (`_DAT_006a16c4`) off it while it is above 0.0 (`_DAT_006a16c8`).
     `FUN_0040b2b0:0x40c09f-0x40c0c4` signs it by the panel's column
     (`1 - 2*(panel < 2)`) and adds it to the x of that panel's phase header and
     of every phase row, so the left column's rows start 300 px to the LEFT of
     their place and travel right and the right column's start 300 px right and
     travel left: 280, 260, ... 0 over the 15 ticks after a phase change. That
     is the human's "slides in from the left to the right". The sibling write in
     the same tail — the READY banner's uniform scale `0x3cb4 = 4.0`
     (`0x40800000`) decaying by 0.2 to 1.0, drawn through `FUN_00408250` at
     `FUN_0040b2b0:0x40ca2b` — is **not** implemented here (it is a per-panel
     state, not a phase row) and is left for a follow-up.
  Both run on the fixed tick (the scene's own counter and one update per tick).
  The port keys the slide by **controller** (as the original writes it) and
  signs it by the **panel** the draw is drawing (as the original reads it).
  Device-free test: `tests/select_row_slidein_test.cpp` (ramp, stagger, the
  `(v, 2-v)` quad and the slide's 15-tick arithmetic); evidence recipe
  `tests/scripts/select-slidein.txt` with captures at ticks 47/50/53 against the
  settled 61+ frame (tick 53 measures 140.0 units of slide on the nameplate band
  against the recovered 300 - 20*8 = 140, and the chibi reveal is visible as
  narrow stretched icons with the not-yet-started slots absent); the four
  scripted gate runs re-measured with the same characters
  (`RELEASE-CHECKLIST.md` §3).
* **The reveal's flash and the entry screen flash (issue #44, 2026-10-06) — both
  recovered, and the issue's candidate globals were the wrong ones.** The issue
  pointed at `DAT_006cfba0` / `(&DAT_006cfba4)[...]` as a count and an alpha list.
  They are not: `FUN_0040d130:108-111` appends each slot whose controller is a pad
  (`(&DAT_006cfaf8)[slot] < 4`) to that list, so `DAT_006cfba0` is the number of
  participating **human** players and the entries are their slot indices
  (`FUN_00417c20:43-48` takes the pad-0 slot; `FUN_0041a260:47-48` is the
  no-human fallback 1/0). The port's own two halves of the transition are:
  1. **The flashing chibi is an atlas CELL, not a tint.** `FUN_0040b2b0:97-102`
     sets `local_2c = 2` while a slot's value is `< 1.0` and 0 after, and its
     non-selected branch (`:123-130` in `research/decompiled`, `:124-131` in the
     live original via the bridge) is the only place that argument goes:
     `FUN_00655830(x, y, local_2c, bVar1)`, with `bVar1` the same `< 1.0` test.
     The pair is the cell's **column and row**, so an unselected slot draws
     **(2,1) while revealing and (0,0) once settled** — and the cell is where the
     white is: `FUN_00655830` has no colour parameter at all, its param_4/param_5
     only build the quad's UVs (`:21-28`, `u = col*stepU + baseU`,
     `v = row*stepV + baseV`). Measured on this install, cell (2,1) of
     `data/select/i00/i01/i07/i15.cnv` is 100 % opaque white (mean RGB
     255,255,255) where the other five cells are the coloured chibi frames. A slot
     one of the panels has selected keeps its **idle cycle** instead
     (`:107-112` — cells (1,0) (2,0) (0,1) (1,1) over 40 ticks), because that
     branch tests the panel match, not the ramp.
  2. **The screen flash is a WHITE full-screen quad with a recovered 30-tick
     alpha curve.** The select scene's own draw ends with two overlapping quads —
     `FUN_0040b2b0:466-475` in `research/decompiled`, `:480-489` in the live
     original — `FUN_00651860(0, 0, 800.0, 600.0, alpha8 << 24 | 0xffffff)`:
     `tick 25..34` at `(tick - 25) * 24 + 15` (15 -> 231) and `tick 35..54` at
     `(55 - tick) * 12 + 15` (255 -> 27), nothing outside. The peak is **tick 35
     alone at 255** (the byte casts are exact over both windows, so the port does
     the same arithmetic without them). The `| 0xffffff` is why it is white: the
     black sibling is `FUN_0040b1f0:23-24`'s bare `(byte)(scene+0x3c42) << 24`,
     a scene-internal page cross-fade drawn *after* the scene, which the port
     already has as `ScreenStack`'s 25-frame fade.
  Both run on the scene's fixed tick, so the flash opens exactly as the black
  scene-switch fade-in reaches zero (scene tick 25 is 25 frames after the swap)
  and peaks five ticks after the last chibi settled (slot 15 settles at tick 30).
  Device-free test: `tests/select_row_slidein_test.cpp`, extended with the cell
  rule, the 30-tick window, the single-tick peak, the white colour and the
  reveal/flash overlap. Evidence recipe `tests/scripts/select-slidein.txt` with
  captures at frames 54, 58, 69 and 100 (scene ticks 20/24/35/66): ticks 20 and 24
  show the white silhouettes — narrow and stretched for the slots early in their
  ramp — beside coloured, settled chibis, tick 35 is the fully white canvas, and
  tick 66 is settled and byte-identical to the same capture before this change.
  The curve itself was measured off the rendered frames: probing canvas pixels
  that are pure black in the settled frame gives an implied alpha that matches the
  recovered one at **delta 0.00/255 on every tick 20..59**.

### E2. Select page 1 — IMPLEMENTED (original match-rule fidelity remains open)

* **Evidence.** Contract fully extracted (plan §2.9, lines 508-568): five
  knobs, their domains/steps, the eight-row list, confirm returns 9 = VS
  intro. Assets `sbg00`/`pbg01`/`pbg02`/`P01`; numerals through
  `FUN_00431b20`/`FUN_00431ce0`. **Blocker:** the stage variation count —
  the count byte at `scene+0x3d90` and the default 2-way cycle vs the three
  names in `pbg02.cnv` need one on-screen cycle capture (plan §7 item 5).
* **Sketch.** `src/ui/screens/stage_select.cpp` writing `MatchConfig`
  (plan line 1093); capture the variation cycle with the original to settle
  the count.

### E3. Options and key config — PARTIAL (three renderer controls unavailable)

* **Evidence.** Plan §1.3: both optional/deferrable. Option scope is tiny
  and closed — 4 toggles + 4 sliders (`option-screen.webp`); key config's
  binding reference is already in `src/input/input.h`, so the screen is a
  luxury (plan §2.10/§2.11, lines 569-613).
* **Sketch.** Two small screens on the same stack; wire the volume sliders
  to `fnd::audio` (the backend already has a UI channel,
  `src/audio/audio.h:26`). Defer toon/shadow toggles until the effect
  system exists (item B1).
* **Persistence (issue #19, 2026-10-05).** Implemented. The settings live in
  `$XDG_CONFIG_HOME/daybreak-decomp/settings.conf` (default `~/.config/...`),
  schema version 1, written atomically (temp file in the same directory, fsync,
  rename, directory fsync, mode 0600). They are loaded before the frontend builds
  and validated first: an unsupported version, an unknown section or a malformed
  line rejects the whole document (defaults, reason printed), a bad value defaults
  only that key, and a stored resolution the display does not offer falls back to
  desktop. Bindings stay per player — the original's own unit — and the pad-to-player
  mapping is stabilised by the SDL GUID recorded per slot, so a replug cannot move
  bindings to another pad. Session state (earned titles, result stats) is not
  persisted. Only an interactive frontend run reads or writes the file: `--match`,
  `--versus`, `--hud-test`, `--out`/`--headless` captures and any `--frames` run are
  unchanged by a user config. Provenance and policies: `docs/USER-SETTINGS.md`,
  decision D10. Remaining: browser-side persistence (IndexedDB/OPFS), and the three
  renderer toggles (item B1/#21) still have no schema keys.

### E4. VS intro (scene 9) — IMPLEMENTED for 1v1

* **Evidence.** `vs-intro.webp`; draw functions `FUN_004115f0`,
  `FUN_00411ae0`, `FUN_00411cb0` (plan line 112, §2.12 line 614); the
  plan's coverage table says the draw function and coordinates are read.
* **Sketch.** A skippable transition screen with the entry tween; portraits
  slide in and the VS animates centre.

### E5. The result sequence (sting → quote → report) — IMPLEMENTED (issue #20 closed the titles and the quote selection)

* **Evidence.** Three beats in one screen: victory sting (`FUN_00633ca0`
  loads `P05`/`P08`), quote (`FUN_00635d40` result phase, sub-phase 0, GDI
  text), report (`result-report.webp`). The report's layout function is
  **not isolated** (plan §7 item 2, lines 1253-1256; coverage line 837).
* **Issue #20's recovery.**
  * **Quote selection** (`ui/result_quote.h`, FUN_00635d40:246-353): the winning side's two
    selections are persona-substituted (character 0 or 4 with weapon slot 2 → ids 16/17 and
    the `data/win/%02db` art; the same gate picks the B-variant entry voice in
    FUN_00409340:180-186), sorted into `data/scenario/win/<min>-<max>-<grade>.txt`, with the
    grade from `min(winnerCapacity, loserBalloon) - winnerBalloon` (<30 → 3, or 4 when both
    winners are below half HP; <50 → 2; else 1). A missing pair script falls back to the
    single script of whichever id is 16 or 17, else 17. Files hold several VOICE/quote
    alternatives and the original picks one at random; the port's pick is deterministic per
    round. The 1v1 self-pair is a PORT RULE — the original always fields two per side, and all
    16 self-pair scripts ship.
  * **Earned titles** (`gameplay/result_title.h`, FUN_00430880 @0x430880): a 41-entry name
    table at VA 0x6b7308 (read from the installed exe by `assets/exe_strings.h`, so the game's
    text stays out of the repository), chosen from the fighter's own record at fighter+0xaedc.
    The record's fields were read from their writers: capacities (FUN_00634980), the KO'd
    selector (FUN_00635d40 writes capacity - balloon), damage dealt/taken split by the lock
    (FUN_00639160 / FUN_00637950), hits dealt/taken split by a mutual lock and hits landed on
    the local player's fighter (FUN_00423000 / FUN_004230e0), melee vs shot hits, and the
    damage-event pairs. The chain has a KO'd branch and a standing branch and ends on index 26.
  * **Session flags** (FrontendState, never persisted): the penalty flag `DAT_006cfdf1` set
    when a player earns the penalty title (FUN_00635d40:377-380), cleared when the panel is COM
    (FUN_0040d130:99-101), and the penalty costume table `DAT_006b72a0` (VA 0x6b72a0) that the
    flag forces on the next selection (FUN_00409340:165-172). `DAT_006cfdfc` (a per-player
    counter with no recovered reader) is deliberately not modelled.
  * **Not recovered, skipped and flagged:** the record fields +0x20, +0x48, +0x54, +0x58,
    +0x5c, +0x60, +0x64, +0x68, +0x6c, +0x70, +0x74, +0x78 and +0x7c/+0x80 (the two float
    accumulators and the frame pair), plus the damage-event counters the port does not fill.
    Every condition reading one is marked UNRESOLVED in `gameplay/result_title.cpp`; the chain
    skips it and reports `resolved = false`, and the host logs the flag.

### E6. Soft keyboard — DONE as reusable widget

* **Evidence.** The grid **is** the name font: `data/chat/name_p1.cnv` grid
  cells (ASCII/kana), names stored as `(cellX,cellY)` pairs via
  `FUN_00646bd0`; action bar `network/nameMenu.cnv`; host scene known
  (scene 13), the widget function is not isolated (plan §2.16 lines 713-755;
  the name-font identity at lines 744 and 879; §7 item 4, lines 1259-1260).
* **Sketch.** Build the reusable widget as the plan schedules it
  (`src/ui/soft_keyboard.*`, line 1097); needed only when names are
  editable, so host it in the netplay track later.

**The plan's thin-RE list (`FRONTEND-PLAN.md` §7) is the checklist for all
of E:** the `FUN_0040b2b0` / `FUN_004072b0` anchor tables, the result-report
composition, the KO trigger (its art is located in `P09`, the firing
sequence is not — §7 item 3), the soft-keyboard widget, the stage variation
counts, and the team-select diamond's y anchor discrepancy. Scenes 2 and
14–19 and scene 5 stay story-mode scope by D6.

## F. Audio

### F0. Live combat SEs and character voices — IMPLEMENTED (issue #16)

* **What landed.** The frontend battle now dispatches attack, firing, hit, block, KO, respawn
  and hypermode cues out of the fixed 64 Hz `MatchFrame`, through the battle engine, with the
  recovered per-character voice vocabulary and the recovered SE ids.
* **Recovered.** The voice vocabulary is a 40-entry table of 16-byte names at VA 0x6b73b0
  (`addattack`, `attackA`..`specialC`); `FUN_00431e70` loads each event's alternatives from
  `data/voice/<dir>/<event>/NNN.wav`, probing NNN upward until the file is missing, and uses the
  `<event>_B` directory for exactly events 4/7/10/26 when the character's voice variant is B.
  `FUN_0041e180:196-206` picks the directory (`data/voice/<name>` or `<name>B`; renaB/rikaB/
  chieB/hanyuB ship). SE ids from their call sites: 9 = the blow that takes a LIVE fighter down
  (FUN_00639160:57 melee, FUN_00637950:504 shot), 10 = a hit on an already-down body
  (FUN_00637950:489), 0xb/0xc = the two victory-sting layers (FUN_00635d40:165, :203),
  0x16/0x15 = the report appearing and its per-row tick (FUN_00635d40:495-508), 0x11 = a menu
  press, 0xd/0xe/0xf = the target-switch gesture. The gameplay bank is `data/se/%03d.wav`, 32
  slots (`FUN_0064ade0`'s `< 0x20` bound); the menu's `data/sysse` bank stays separate. One
  voice channel per fighter mirrors the original's per-player audio object (`FUN_0064ada0`:
  `scene+0x5600 + player*0x34`).
* **Port rules, labelled.** The KO pair (attackKO for a melee blow, damageKO for a shot) is a
  reading of the two names, not a recovered trigger. The swing/fire/block/respawn SE ids are
  NOT recovered, so those events carry the character's voice only and `CombatCue::se_id` stays
  -1. The alternative pick is deterministic from the event identity instead of the original's
  `rand % count`. The B-persona voice directory is gated by the persona rule #20 recovered
  (character 0/4 with weapon slot 2), so chie's and hanyu's B voices are unused.
* **Identity.** `tick + kind + fighters + per-tick sequence`, with a duplicate-history ring:
  a replayed frame or a rollback resimulation carries the same ids and plays nothing twice.
  `end_match()` is "stop everything this match started" (cuts the SFX bus, releases every voice
  channel); `Sdl3Engine::stop_bus(SfxBus)` is the bus-level seam issue #15 asked for.
* **Remaining.** The pause-time policy is #15's (this layer has no pause test: a paused
  `Match::step` produces no events). A live slider drag during a battle was not exercised
  interactively, though the engine applies `set_volumes` to every busy slot. The hypermode cue
  is exercised by the asset-backed COM 2v2 test but not by a live frontend round (the synthetic
  pads never press Special and the four-pad selection walk produces no COM panel): wired and
  unit-covered, live-unexercised. The standalone `--match`/`--versus` parity paths stay silent
  by design. The real-device check is a *measurement*, not a listening check — `parec` on the
  default sink's monitor captured the port's own streams at rms 0.25-0.40 across the battle
  window after they were unmuted; PipeWire stream-restore had `foundation_demo` muted, which is
  why the same run was silent beforehand.

### F1. A seam from the screen layer to the audio backend (menu SEs) — DONE

* **What.** Menu cursor/confirm SEs are silent: the screen stack returns an
  action but cannot play a sound.
* **Evidence (measured).** `src/ui/screen_title.h:76-79`: the screen returns
  `TitleAction::{Moved,Activated}` "so the caller can play the SE the
  original plays there (`FUN_0064aed0`: 0 on confirm, 2 on a cursor move)
  without the state machine needing an audio seam. Audio is not wired on
  this screen yet". The ids and the full mapping (0 決定, 1 戻る, 2 cursor,
  3 lock/ready) are in plan lines 279-280, 309-311. The backend exists and
  reserves channel 0 for UI (`src/audio/audio.h:26`).
* **Sketch.** Give the screen host in `main.cpp` a small SE callback (or map
  `TitleAction` there) and load the SE bank through the existing audio
  backend; count plays under a headless run the way `--audio-test` does.

## G. Verification debts — do not make these claims yet

### G1. Web — GAME DATA VERIFIED on software WebGPU; hardware/visual check remains open

* **Evidence (measured).** `BUILD-web.md:32-47` records a real run —
  Chrome for Testing 152 headless, SwiftShader, 845 frames, 60.1 fps,
  `RESULT: ok`. The same file documents the asset-preload build as
  *expected* output (`:54-74`) and its own "Not verified" list: canvas
  screenshots come back black headless, and only SwiftShader has been
  exercised (`:107-116`). So the corrected statement is: the **plain web
  demo** has been executed; a browser run **with game data and the versus
  scene** has not, nor has a hardware adapter.
* **Sketch.** Run the `FOUNDATION_WEB_ASSETS` build against `data/`, record
  the console numbers in `BUILD-web.md`, and only then extend the claim to
  the game; the screenshot path needs an X server that outlives the command
  (`--headed`).

### G2. macOS: never executed

* **Evidence.** `README.md:189` ("not attempted — no Mac available"),
  `PORT-PLAN.md:11-12`, `MEDIA-INPUT.md:179`, `WEB-ASSETS-RUNTIME.md:242`,
  and D2's macOS bullet all agree. No execution evidence exists anywhere.
* **Sketch.** Either keep the explicit "unverified" status (the honest
  default every doc currently uses) or do a first run on real hardware:
  wgpu-native prebuilts + `sdl3webgpu`'s Metal path, `foundation_demo`
  offscreen, and record the adapter/backend lines. Nothing in the code is
  claimed to block it; nothing has been run.

### G3. Texture coverage: two install data gaps, checked by `tests/showcase.py`

* **What.** Full texture coverage of the asset pipeline has **not** been
  claimed. A 16-character × 13-stage sweep found 43 untextured draws, all
  reducing to gaps in the installed game data — not loader bugs. This is the
  baseline to re-check in the future.
* **Evidence (measured, this pass — issue #23's release gate).** `tests/showcase.py --check`
  runs every (character, stage) pair headless and reads the demo's own
  `draws: N (X textured, Y untextured)` line, so the loader is the oracle.
  Re-measured 2026-10-05 with `--no-devices`: **165/208 pass, 43 flag, zero
  pipeline failures** — the same baseline as the earlier pass, with the same
  breakdown (30 cells at 4 untextured draws on stage05/stage15, 11 cells at 2
  on `kasai`, 2 cells at 6 where both gaps overlap). The 43 reduce to
  two install gaps:
  - **stage05 / stage15** — the stage `.X` scenes name dust/particle
    textures as `.bmp` (e.g. `01`–`05`, `08`, `11`) that have no `.cnv` in
    these two dirs; the cache resolves `.bmp`→`.cnv` and misses 4 per stage,
    on every character.
  - **kasai** — `data/kasai/00.X` references a `g` texture present
    **nowhere** in the install (checked `g.cnv`/`g.bmp` across `data/`);
    2 untextured draws on every stage.
  Both are data the install does not ship, so the loader is doing the right
  thing (reporting the miss, not fabricating a texture).
* **Check in the future.** Re-run `tests/showcase.py --check` after any
  install update, re-extraction, or new character/stage. The two gaps above
  are the known baseline; any **new** untextured draw is a regression (a
  loader or cache bug), not a data gap, and needs investigation.
* **Not a baseline item: gear-up.** Every one of the 46 legal
  character/weapon selections launches and runs a match
  (`tests/weapon_definition_test.cpp`: "all 46 legal selections ran a match",
  743 checks, 0 failed, 0 skipped with the install present). The earlier
  "Satoko, item 008 / Takano, item 011 fail the loud gear-up join" note was
  retired by the E8 fix and is not part of this baseline.

## Release gate — issue #23 validation update, 2026-10-05

The offline Linux release is gated by
[`RELEASE-CHECKLIST.md`](RELEASE-CHECKLIST.md): a second person can re-run the
package build, the host suite, the three acceptance scenarios, the sweeps, the
environment matrix and the stability run, and compare against the quoted lines.
It demonstrated the acceptance criterion (two humans, one human with COM and
four fighters, three rounds each) and it found three release-blocking defects,
all fixed:

1. **The 1v1 result screen never loaded.** Issue #20's two-winner art made
   `ResultScreen::loaded()` require both winner sheets while a one-member
   winning side loads one, so the screen refused, `ScreenStack` read the null
   scene as "no scene" and the run ended as a *successful* quit with no results
   screen. `winnerPortraitCount()` states the recovered rule (one portrait per
   winning slot, FUN_00635d40:255-273); the one-member side draws its portrait
   in the port's centred 1v1 position (PORT RULE: the original always fields two
   winners), and `loaded()` now names the reason when it refuses.
2. **A rematch aborted the process.** `SceneRenderer::setScene` released the
   previous scene's buffers but kept `drawTemplates_`/`baseDrawList_`, so the
   first live effect card after a rematch submitted a released vertex buffer:
   wgpu-native panicked (`Buffer[Id(...)] does not exist`) and the run died with
   exit 134 a few seconds into round 2.
3. **Rematch rounds diverged from round 1.** The `--local-players` synthetic
   pads' menu clock was latched on the first selection screen (a rematch could
   not reach the OK cell), their roster nudge then moved the cursor onto the
   Back cell (the run left to the title), and their directions moved the stage
   page's settings cursor (a rematch played 240 s/175 % where the script asks
   for 60 s/50 %).

Two evidence gaps were closed with them: `[menu] battle:` prints the round's
settings, the display callbacks print what a fullscreen/resolution request
actually did, and `--no-devices` keeps a verification run off physical input
devices — SDL reports a connected pad whether or not the window has focus, and
the pad attached to the gate machine moved menus and changed a HUD capture
until the host suite and the demo-driving tools stopped reading devices. Issue
#29 then made that the *default* for a verification run (the obstruction was
opt-in, so any new recipe silently got contaminated results), added `--devices`
to ask for the devices back, and made an unfocused window take no input.

Still open, and stated as such in the checklist: a second GPU vendor, physical
controllers, hardware audio listening, other distributions, an interactive
compositor-side resize, and Windows/web/macOS execution (not this issue's
target; their own docs carry their evidence).

## H. Out of scope (stated, not scheduled)

* **Netplay and video stay out of scope by D6** (LAN netplay is a
  design-first Phase 4; story-mode video stays stubbed). They are named
  here only so the next session does not re-litigate it: the versus loop and
  the front end come first.

## Stage collision implementation update — 2026-10-04

Issue #7 is implemented in `src/physics/raycast.*`, `src/gameplay/{fighter,match}.*`,
`src/assets/scene.h` and the match host in `src/main.cpp`. The loader records four
query purposes separately: movement and ground both use `collision.x`, projectiles
use `collision_tama.x`, and the live camera uses `collision_camera.x` (the three file
loads are recovered in `FUN_004011f0`). `collision_tama.x` now has its own scene role
and typed channel instead of sharing the general collision label.

The movement query sweeps a 20-unit-radius, 145-unit-high body stencil across each
requested horizontal segment, filters wall triangles, and removes the wall-normal
part of the remaining displacement so fighters slide. Ground height comes from
upward-facing triangles; slopes are accepted up to normal-Y 0.45, steps up to 50
units and drops up to 120 units are followed, and airborne descent sweeps the full
vertical interval before landing. The radius follows the existing 20-unit movement
measurement in `FighterConstants` (RE section 14.7); body height and movement thresholds
are provisional port rules. The stage's `env.dat` spawn XZ coordinates
are preserved while Y is projected to support geometry. Invalid spawns fall back to
the nearest valid supplied env slot, then a walkable triangle centroid; invalid runtime
positions return to the fighter's last supported point. Respawns reuse the resolved
slot position.

Scene models remain borrowed by fighters and collision queries. `initScene()` finishes
loading effect cards before it binds any scene-model pointer or builds a model index;
the front-end battle rebuild follows the same order before resetting the match. The
standalone scripted/offscreen `--match` capture remains the unclamped historical path
for both movement and camera traces. Interactive matches use the movement and camera
queries, and `--no-camera-clamp` retains the explicit camera A/B override.

Verification: all 26 Linux CTest tests pass. The new movement test passes 34 synthetic
checks for flat ground, slopes, low/high steps, wall sliding, corners, long dash sweeps,
airborne landing, spawn recovery and respawn. Its optional local-data run adds checks
for the movement mesh and original spawn slots 0/2 on stages 01, 04, 06, 15 and 21
(49 checks total). An asset-backed front-end battle capture loaded all four collision
channels and completed with `RESULT: ok`; the standalone melee trace still matches its
banked fighter positions and states exactly. Windows/web rebuilds have not been run
for this update.

## KO, Overkill, respawn and victory rules — 2026-10-05

Issue #11 is implemented in `src/gameplay/{match_economy,fighter,match,projectile}.*`,
`src/gameplay/rng.h`, `src/gameplay/hud_fill.h` and the result/HUD print in
`src/main.cpp`. The battle scene is a global singleton at base `0x6cafec`
(`[fighter+0x23c]` is set to it at `0x41d9c2`), which is what made the economy
readable: its balloon array is `scene+0x12ac`/`+0x12b8`, twelve bytes per side
(`{int side; int balloon %; int capacity}`, `FUN_00634980` @0x6349a2-0x6349df), and
the two capacities are the battle settings 青/赤チーム風船サイズ at `scene+0x43c4`/
`+0x43c8` (`FUN_00633ca0` @0x634432-0x634452 defaults both to 100, `FUN_0040acb0`
@0x40af57-0x40afe2 steps 40..200 by 20 and wraps at the ends).

Recovered and implemented:

* **The handicap is the LIMIT, not an increment multiplier.** A KO adds the raw
  increment to the victim's own side (`FUN_00639650` @0x639650 through
  `[victim+0xc]`); a side bursts when `capacity - balloon < 1` (`FUN_00421930`
  @0x42194e-0x421955, tested in `FUN_00635d40` @0x6370dc-0x6370e3). The normalized
  100%-LIMIT port rule is gone.
* **KO increment** = 20 (0x14) + overkill + a one-shot reaction bonus: melee
  `-HP/1000` uncapped (`FUN_00639160` @0x639399-0x6393c6), shots
  `min(-HP/500, 5)` plus +1 below -3500 and +1 below -4500 (`FUN_00637950`
  @0x638cad-0x638d35). The bonus is the killing blow's reaction landing the victim
  in the downed/airborne reaction (`FUN_0063ba80` @0x63ba80) while it was not
  already down; the shot path latches it once per life at `victim+0x84c`.
* **Overkill**: a hit on a body already at HP <= 0 credits exactly +1 to that body's
  side and nothing else (`FUN_00637950` @0x638e0d-0x638e37). The melee path credits
  nothing there at all, which is why the port's melee never offers a dead candidate.
* **Timed round**: the LOWER balloon wins, then the higher total remaining HP, then
  `FUN_0065d150() % 2` (`FUN_00635d40` @0x636e90-0x636fd0). There is no draw exit,
  and the port's old inverted comparison plus its `-1` draw are both gone. The final
  tie uses the port's own seeded generator (`gameplay/rng.h`) so a replay resolves
  the same tie.
* **Airborne respawn**: `FUN_004219a0` is a full state restore gated on the side
  still having balloon headroom (@0x4219aa-0x4219bd), then `FUN_00421bd0` repositions
  the fighter at `[fighter+0x18] = 1000.0f` (@0x421c62-0x421c65) and move 0xc2 plays
  the descent. `Fighter::respawn()` implements that; `[fighter+0xaecb]` is modelled
  as the target-lock exclusion the dump shows it to be (read only by `FUN_0041f580`
  @0x41fe26-0x41fe73), with no damage immunity claimed.
* **Simultaneous outcomes**: every participant is credited in one pass, each exactly
  once, and when both sides run out of balloon in the same frame the winner comes
  from the highest participating fighter index — the original's own slot-order scan
  (`FUN_00635d40` @0x6370a7-0x637171), made explicit so no loop order can change it.

Explicit port rules, all listed in `match_economy.h`: the burst is detected in the
same `update()` that credits it (the original sees it one frame later, because the
per-frame flag `fighter+0xaeca` is cleared at the end of each frame); the countdown
is seconds rather than frames, keeping a 64 Hz limit honest; `kRespawnSec` (3 s) is a
single KO clock where the original runs the KO move's phases and respawns 30 frames
into the second one (`FUN_00428510` @0x42a14d-0x42a17d); and the respawn keeps the
fighter's own spawn slot where the original picks a random X/Z inside the stage
bounds (the issue requires spawn identity to be preserved).

Unresolved, recorded rather than guessed: the between-rounds red-capacity creep
(`FUN_00635d40` case 4 @0x63691c-0x63692b, `if (cap_red > 0x46) cap_red -= 5`, run
with the battle reset — multi-round only, so this single-round port does not carry
it), the per-character move handler's choice of the victim's reaction move for melee
(the port's shared swing passes "unspecified", i.e. `FUN_0063ba80`'s default 198),
the unrecovered `[attacker+0x10]+0x28 & 0x800` branch of `FUN_0063ba80` (returns 191),
and the KO move's per-phase durations (what would turn the 3 s port clock into the
recovered one). Presentation, also unresolved: the original arms one per-fighter
triple (`[+0x43e4]/[+0x4404]/[+0x43f4]`) from two branches — a downed fighter that was
NOT credited this frame gets `0x5a` (90 frames = 1.5 s KO sting, re-armed every frame,
`FUN_00635d40` @0x6371ba-0x637230), while the credit frame's headroom branch gets
`0x78` (120 frames = 2.0 s with flag 1, @0x637173-0x6371b8, the respawn presentation).
The port keeps one shared 1.5 s window (`kKoStingSec`) and does not model the 2.0 s
respawn presentation. Animation follow-up for issue #18: move 0xc2's descent/recovery
and the KO chain (0xc0/0xc1 sets [117, 29]; 0xcb sets [97, 37]) are the clips that
carry the respawn timing.

Verification: all 30 Linux CTest tests pass. `match_economy_test` went from 210 to
387 checks (capacity extremes, both timeout tiebreaks, the seeded generator,
simultaneous deaths, both-side bursts, the Overkill window and its cutoff, the
single-counted credit audit, the inflate/popup arithmetic); the new `round_rules_test`
adds 114 checks driving Match end to end (1v1 and 2v2 KO -> Overkill -> respawn, the
killing-blow-versus-Overkill split, capacity extremes at 40%/200%, simultaneous
deaths, both-side bursts including through Overkill, and winner reporting).
`fighter_script_test` (576 checks), `fixed_step_test` and `stage_movement_test` moved
their stale expectations to the recovered rules. Windows/web rebuilds have not been
run for this update.

## Controller lifetime across a scene swap (issue #46) — 2026-10-06

`std::bad_alloc` at the start of a second match. The reporter's core (coredumpctl
563299) faults in `xm::Controller::evalLocal` -> `operator new`: `nf` came out as
66584576 and the request as 0x5555555555555580 bytes. That is not an out-of-memory
condition — it is a `Controller::model_` pointing into a freed scene, whose
`frames` vector header read as float data.

Mechanism, all in the port's own structures: `Controller::model_` is a raw
`const Model*` (`assets/xmodel.h:238`); `initMatch` binds the fighters' controllers
to `&app.scene.models[rigs[i]].model` (`src/main.cpp:2259-2261`), where `rigs[i]` is
the i-th `role == "character"` model — an index that moves with the stage;
`initScene` replaces the whole scene (`:3522`) and `app.controllers.resize(...)`
(`:3570`) only constructs and destroys entries, so a controller bound by an earlier
round survived the swap still naming the freed `Model`; `advanceAnimation`
(`:3855-3856`) then evaluates every controller with a non-null model. Measured with
the front-end rematch recipe: match 1 (`stage04`) binds rigs 8/10, match 2
(`stage15`/`stage21` by the stage roll) binds 7/9, and the stale pair is dereferenced
on the next tick. Both failure modes are the same defect: the reporter's
`std::bad_alloc` and a plain SIGSEGV, depending on what the allocator put back.

Fix: `initScene` clears every controller binding before it replaces the scene
(`:3510-3519`, `Controller::bind(nullptr)`). The invariant it restores: at every
point `advanceAnimation` can run, a controller's `model_` is null or names a model of
the CURRENT `app.scene.models`. Deliberately unchanged: the `advanceAnimation` model
check itself — turning it into a silent skip would hide the next instance of this
defect instead of fixing it.

Neighbours checked, no second live instance: `app.worlds` is truncated by its own
`resize` and then rewritten for every index of the new scene by the pose loop
(`:3574-3584`; `Model::evalPose` resizes and fills the whole vector), so it cannot
hand a stale pose to `buildPalette`; `app.match` and `app.matchRig` are written
together by `initMatch` and the skip test reads only the first `fighterCount`
entries; `app.modelMatrices` and the `sm.attachFrame` lookups (`:3590-3599`) are
rebuilt per scene and bounds-checked. `--versus` binds no controller at all, and the
standalone `--match` pause rematch (`:1277`) calls `initMatch` against the *same*
scene, so nothing is freed there. Residual: between the swap and that same call's
`initMatch`, the previous `Match` still holds raw model/controller pointers — unreached
today because nothing ticks a match inside `initScene`, and the structural answer is
for the scene to own its controllers and match rather than for `App` to index them
alongside.

Regression guard: `tests/controller_scene_lifetime_test.cpp` (registered with ctest;
skips with exit 77 without the install, like the capture tests). It compiles
`src/main.cpp` into its own TU to drive the real `initScene`/`initMatch` over
`stage04` -> `stage15` -> `stage02`, asserts the invariant after each swap and then
runs `advanceAnimation` once per swap. It FAILS against the pre-fix tree (controllers
8/10 still naming the freed `stage04` scene) and passes with the fix. Limits, stated
rather than implied: it needs the game install; it stops at `initScene`'s renderer
stage (no WebGPU device is needed — the whole controller half runs before that); and
it cannot observe the windowed path. Captures cannot see this class at all:
`capturing` is `!opts.out.empty()` (`:4943`) and `advanceAnimation` runs only
`if (!capturing)` (`:5018`), so every `--out`/`--headless` recipe skips the crashing
function — the blind spot issue #39 owns.

Verified on 2026-10-06 (Linux, RADV, four-view battles at ~180 fps): the non-capturing
windowed recipe (`--screen=title --local-players=4 --no-devices
--script=tests/scripts/frontend-2v2-rematch.txt`) died with `std::bad_alloc`/SIGABRT
at the second scene swap before the fix, and after it ran round 1 (`stage04`) and
round 2 (`stage21`) through their round-over and a third round (`stage01`) past its
own swap, with no crash. That recipe cannot end by itself — its script stops at logic
tick 14688 and the result screen needs confirms no synthetic pad sends outside the
selection screen, while `--frames` disables the pause path (`battlePauseAvailable`) —
so the terminating form of the same command adds `--frames=42000`: `RESULT: ok`,
14965 logic ticks, 42000 frames in 239 s. A 5600-frame headless capture of the same
recipe (which crosses the second swap and, before the fix, completes without
crashing) is byte-identical before and after the change, so no capture recipe moves.
`ctest` went from 45 to 46 tests, all passing; the MinGW Windows cross-build passes.
