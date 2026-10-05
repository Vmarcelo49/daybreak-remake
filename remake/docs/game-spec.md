# Higurashi Daybreak — game spec & build plan

> What the game is, how it plays, and in what order we rebuild it.
> Sources: original-game observation (owner), RE findings in
> `docs/reverse-engineering.md`, and the [Higurashi Daybreak Wiki](https://higurashidaybreak.fandom.com/wiki/Higurashi_Daybreak_Wiki).
> Scope authority: `decisions.md` D6 (versus + LAN netplay are the focus).

## 1. What the game is

A **2v2 3D arena fighter** set in the *Higurashi When They Cry* universe
(Twilight Frontier / 07th Expansion, **2006** — first release 2006-08-13 at
Comiket 70; Kai expansion 2007-04-22).
Two teams of two fight in 3D stages modeled on series locations
(Hinamizawa areas), each with its own layout, collision, and BGM.

- **Roster**: **16 fighters**, keyed by character index 0–15
  (`ASSET-CATALOG.md` §2.1–§2.2): the 2006 roster plus Hanyuu and Natsumi.
  **46 weapons** — indices 0–13 have three each, Hanyuu (14) and Natsumi (15)
  have **two** (§3.2–§3.3) — which change the projectile/attack set. The third
  slot is the Kai/DX addition (item ids 33–46) and ships in this build, so a
  picker must offer two weapons to those two characters, not three.
  ([Characters](https://higurashidaybreak.fandom.com/wiki/Characters))
- **Stages**: **13** shipped directories. `stageNN` is scene + time of day,
  *not* a number (`ASSET-CATALOG.md` §1.1): `stage01/11/21` = schoolyard
  day/sunset/**night**, `stage02/12` = village paddies, `stage03/13` = shrine
  grounds, `stage04/14` = mountain stream, `stage05/15` = riverbed,
  `stage06/16` = shrine upper. `stage21` is the **night** schoolyard (the
  stage the DX9 remake hardcoded); there is no `stage22`–`stage26`. Each
  ships visible meshes plus separate `collision.x` / `collision_camera.x` /
  `collision_tama.x`.
- **Boot flow** (target): `movie/op.mpg` plays (skippable with any button) →
  title menu; in the foundation the movie path is stubbed
  (`foundation/src/audio/video.h`), so it boots straight to the title screen.
  Menu text is Japanese; a community mod translates it:
  **Story · Versus · Netplay · Option · Controller · Exit**.
- **Modes**: Story (preset teams, bracketed fights + movies), Versus
  offline (split-screen, bots fill empty slots), Netplay (online/LAN),
  Option, Controller setup.

## 2. Focus

**Versus and netplay.** Everything in this plan serves those two first:
local 2v2 with splitscreen + bots, then LAN netplay. Story mode exists
in the original and stays loadable/watchable long-term, but it is not
the focus — no branching, scenario scripting, or save system is planned.
Options/controller setup are built only as far as versus needs them.

## 3. Gameplay systems

### 3.1 Offense

- **Melee button (X/格闘)**: combo starter; variants with held direction
  (horizontal + attack, vertical + attack), dash + attack, and aerial
  versions. The old `0x28/0x29/0x2a` → sets 2/3/5 interpretation is withdrawn:
  moves 40/41/42 are jump-chain records, not a universal AttackA/B/C map. Weapon
  attacks instead use the selected character/item move table; how the original
  chooses among those moves is still unresolved. The names `attackA/B/C` and
  `specialA/B/C` are voice-cue keys, not recovered attack tiers.
  There is **no dedicated heavy button** — heavy is likely a
  directional variant (input model still provisional, see §3.6).
- **Shoot button (C)**: fires the equipped weapon's projectile in the remake.
  The binary's 300→301→302 sequence is a conditional character-move transition,
  not an established shooting or charge-tier chain; blob fields +0x64/+0x68 are
  read in hit-resolution, not established shot selectors. The string keys `shotA`,
  `shotB`, `shotC`, and `shotFinal` are labels only, not proof of projectile types
  or firing animations. The tap/yellow/red mapping therefore remains provisional.
  Ammo is a **counted stock** (MAIN 6, CHARGE 2), recharging over time — the HUD
  bar fill fraction *is* the recharge readout (model as fractional stock, not
  bullets + timer).
- **Shot tiers** ([Basics](https://higurashidaybreak.fandom.com/wiki/Basics)):
  **NS** Neutral Shot (tap, or under the yellow threshold), **CS** Charge
  Shot (yellow filled), **FCS** Full Charge Shot (red maxed). The charge
  meter **also fills while holding the Special button**, not just shoot.
- **Reload gate**: a projectile user is held between volleys; `reloadOK`/
  `reloadNG` are **voice cue keys**, not states (§3.4). The window itself is
  `gameplay/fighter.h:441`, :485 (`reloadNG` after firing).
- **Special button (S)**: three roles, in priority order —
  1. **Activate Hypermode** when its bar is full (§3.4),
  2. **EX move** while Hypermode is active ([Hypermode](https://higurashidaybreak.fandom.com/wiki/Hypermode)),
  3. otherwise **charge the shot** alongside C.
- **Tactics button (Q/作戦)**: exists on the controller table; behavior
  unmodeled — investigate with bot work.
- Melee variants are named in the wiki as NA/FA/HA/DashA/StepA/j.A/LA/ADA
  (neutral / forward / horizontal / dash / sidestep / air / landing /
  airdash attack). We currently have one swing plus dash and aerial
  stand-ins; LA and StepA have no input path yet.

### 3.2 Movement

- Double-tap a direction ([Basics](https://higurashidaybreak.fandom.com/wiki/Basics)):
  **forward = dash**, **back = backdash**, **left/right = sidestep**,
  and in the air an **airdash** (all four directions).
- Jump (**Z**). Flight is documented as a **rising airdash** — "press the
  jump button and a direction in the air" (wiki) — while the owner's
  observation and §3.6 describe **holding jump** to fly. Both models are
  in the spec until re-checked in the original; we implement hold-jump.
- Aerial/landing attack variants (j.A, LA, ADA) ride on these states.
- Guard (**D**, hold), tag (CORRECTED 2026-10-03: a partner swap is not established —
  current evidence shows control never transfers in the covered front-end flow;
  the reticle changes targets via `FUN_00421e30`, and tag* voice keys alone do
  not establish a fighter swap — see ROADMAP-PENDING.md C1),
  provoke (taunt),
  revival and KO/down states round out the original's ~40 move ids. The
  "40+ animation states" are **not** a name table in the binary: every shipped
  `.X` names its sets `Anim-1`…`Anim-124` and the state→set mapping ships in
  each character's `data/<char>/NN.dat` (see `foundation/docs/ANIMATION-SETS.md`).

### 3.3 Camera

Always locked onto an enemy fighter. A **target button cycles** enemies;
**holding it aims at your ally** instead. Camera keeps **height 211 /
distance 289** offsets with the aim raised **138** units and sits **directly
behind** the locked fighter (baseline orbit 0, not 45°), and spring-collides
against `collision_camera.x` (fitted with 0.0 px residual —
`foundation/src/gameplay/arena_camera.h:75-82`,
`foundation/tests/arena_camera_test.cpp:604`). Projection is the original's
own: fov π/4, near 50, far 150000 from `0x6338ae`; the old 300/800 constants
are a different projection's near/far offsets
(`foundation/src/gameplay/arena_camera.h:110-112`), not a framing.

The **combat target is not the camera**: each fighter holds its own, from
`foundation/src/gameplay/target_lock.h` (`FUN_00421e30`/`FUN_00421f30`'s
`+0x304` and the `0xb4` ally hold), so two players can hold different targets
while the camera follows one of them. Facing, shots and the melee victim read
the lock; the camera's followed player is separate state.

### 3.4 Meters

- **Stamina**: spent by dashing, **jumping**, and holding block — and the
  bar is **contextual** (appears on use, drains while held, refills fast
  after). Empty = no dash, guard breaks down.
- **Hypermode bar** (the large bottom-left gauge): fills by dealing or
  taking damage depending on the mode; at full, **S activates** it in DX
  (the original auto-activated) and the fighter gains a **coloured
  aura**, the mode's modifiers, and an **EX move** (S while active).
  Per-slot pick at versus setup, after weapon
  ([Hypermode](https://higurashidaybreak.fandom.com/wiki/Hypermode)).

  | Mode | Fills from | Activation | Duration | Modifiers |
  |---|---|---|---|---|
  | **Friendship** | damage **dealt** | S at full | 15 s | MAIN + CHARGE recharge faster; locking the same target as your ally enhances black/yellow charge shots (DX also chains normal/command attacks on the focused target) |
  | **Oyashiro** | damage **taken** | S at full (auto in the original) | 15 s | take ×0.75, deal ×1.5; **every other hit** avoids stun; activation knocks back enemies in melee range (no damage). DX: activating while being hit or KO'd leaves the bar at 25% and lasts 4 s |
  | **Kakera** | damage taken, **slower than Oyashiro** | **automatic on death** from a direct hit | 25 s unhit | HP restored to 100% then drains to 1%; stun-immune to **all** hits; take ×0.20, deal ×1.5; at 1% the bonuses drop but the fighter lives |

  The battle setting ゲージ増加量 (gauge rate, default 100%) scales fill.
- **Not the same as `LIMIT`**: the top-corner `LIMIT %` is the balloon
  lose condition (§3.5). The bottom-left bar is this gauge.
- Mapping to RE keys: `oyashiro`/`oyashiroB`, `HPcheck`, `nearWIN`/`nearLOSE`,
  `guard`/`guarded`, `spark`, `reloadOK`/`reloadNG`, `tagfront`/`tagback`/`tagOK`
  are **voice cue keys** in the exe's 16-byte-stride table at VMA 0x6b73b0
  (file 0x2b73b0), consumed only by `FUN_00431e70` (0x432042) to build
  `data/voice/<char>/<key>/%03d.wav` — they are not animation, aura or reload
  states. Animation is index-based: each rig names its sets `Anim-1`…`Anim-124`
  and the state→set mapping ships in each character's `data/<char>/NN.dat`
  (see `foundation/docs/ANIMATION-SETS.md`). Tag/swap mechanics remain unresolved;
  those voice keys do not establish them.

### 3.5 Winning — the balloon

Each team has a **balloon** at the screen edge with its own **`LIMIT` readout**
(default 100%) — the team loses when its balloon **reaches** its own limit
(`>=`, not past it; the original computes `capacity - balloon < 1` in
`FUN_00421930` @0x42194e-0x421955 and tests it in `FUN_00635d40`
@0x6370dc-0x6370e3). Battle settings add a **per-team balloon-size handicap %**
(40..200, step 20, default 100 — `FUN_0040acb0` @0x40af57-0x40afe2), and it IS
the per-side LIMIT: the increment is not scaled by it (`gameplay/match_economy.h`,
`capacity(side)`/`limit()`).

A KO credits the **victim's own team** with 20% plus an overkill term plus a
one-shot reaction bonus (`FUN_00639160` @0x639399-0x6393c6 melee,
`FUN_00637950` @0x638cad-0x638d35 shots), which is where the observed +21%
comes from. The KO'd fighter **respawns airborne**: `FUN_004219a0` restores the
full state (gated on the side still having balloon headroom, @0x4219aa-0x4219bd)
and `FUN_00421bd0` repositions it at `[fighter+0x18] = 1000.0f`
(@0x421c62-0x421c65) before move 0xc2 plays the descent — implemented in
`Fighter::respawn()`, with `[fighter+0xaecb]` modelled as the target-lock
exclusion the dump shows it to be (read only by `FUN_0041f580`
@0x41fe26-0x41fe73) and no damage immunity claimed. KO presentation is sting
(撃破！, 90 frames = 1.5 s while the fighter is down, `FUN_00635d40`
@0x6371ba-0x637230) → inflate (0.5%/frame, `FUN_006430f0`) → floating `+N%` delta
(60-frame readout, `FUN_006431d0`); the 120-frame 2.0 s arm at @0x637173 is the
respawn presentation, which the port does not model separately. Hitting the downed fighter scores
**Overkill: +1/hit** to that fighter's own team (`FUN_00637950`
@0x638e0d-0x638e37) until it respawns — the port's KO clock; the original ends
the window when the KO move's descent/recovery ends, which is also when the
lock-on indicator turns gray.
([Basics](https://higurashidaybreak.fandom.com/wiki/Basics),
[Overkill](https://higurashidaybreak.fandom.com/wiki/Overkill))

A timed round compares the two balloons **lower-first** (the balloon counts your
own team's KOs, so the lower one is the healthier team), then the two teams'
total remaining HP, then `FUN_0065d150() % 2`
(`FUN_00635d40` @0x636e90-0x636fd0). There is no draw exit: the winner is always
a side, and the port resolves the final tie with its own seeded generator
(`gameplay/rng.h`).

### 3.6 Controls (authoritative table)

From the controller-setup capture (`docs/reference/controller-setup.webp`):

| Key | Battle | Menus |
|---|---|---|
| Arrows | Move | Navigate (snapping grid cursor) |
| Z | Jump (+ hold = fly) | **Confirm** (observed: team pick, result advance) |
| X | Melee (格闘) | **Cancel on filled slots** (deselects to char pick) |
| C | Shoot (+ hold = charge) | — |
| A | Target switch (hold = aim ally) | — |
| S | Special | — |
| D | Guard (hold) | — |
| Q | Tactics (作戦, unmodeled) | — |
| W | Pause | — (ESC quits) |

1P = keyboard; P2–P4 = pads (buttons 1–8). The input layer is the foundation's
**13-action** model (arrows + Z/X/C/A/S/D/Q/W,
`foundation/src/input/input.h:19-33`), with the 1P scancodes pinned by
static_asserts (`input_sdl3.h:38`, `pin_tables.cpp:20-46`); P2–P4 pad layouts
remain the unverified half. The original's internal 7-slot polling loop is
deliberately not mirrored.
Menus vs battle accept different keys — menu handling must be
slot/context-aware, not a single global confirm/cancel pair.

### 3.6b Versus debug keys (wiki)

Versus doubles as a training mode via function keys
([Basics](https://higurashidaybreak.fandom.com/wiki/Basics)):
**F1** max HP for everyone + both balloons to 0%, **F2** CPUs off
(stand still), **F3** CPUs on, **F4** max Hypermode. The foundation has no
F-key debug hooks yet (its only raw key is ESC to quit, `src/main.cpp:2225`);
F2 is reserved for the original's CPU-off key, so animation debug must move off
it when these land. Captures are made with `--out`, not an F12 screenshot.

### 3.7 Versus flow (captured end-to-end)

Title → **Team** (blue/red panels) → Character (grid, P1 starts on Rena,
hover animates chibi) → Weapon (up/down) + Costume (left/right) →
Hypermode → Controller per slot (PLAYER/COM — bots assigned here) →
Ready lock-in (準備完了, slot-contextual cancel) → Stage + battle
settings (one list, left/right edits: stage+variation, time, HP%,
gauge%, balloon-blue/red%, start/back) → VS sting (animated portraits +
VS, unset slots autofill COM-random) → Battle → Result sequence (sting
→ winner quote, Z → activity report with session titles, Z) → back to
Team select. Punishment costumes and report titles are **session-scoped
flags, never saves**. Full shot log: `docs/reference/README.md`.

## 4. Build plan (ordered)

Status key: ✅ in the foundation (`remake/foundation/`) · 🔶 partial · ❌ missing.
Code truth: `foundation/README.md` + `foundation/docs/ROADMAP-PENDING.md`; the
DX9 remake this table was written against is deleted (cutover commit `5a63db3`,
`pre-webgpu-cutover` tag `37ed31d`) and its rows survive only as provenance.
RE truth: `reverse-engineering.md` (camera numbers corrected by
`foundation/src/gameplay/arena_camera.h`); the "Now" column below still leans on
the deleted tree in places and is marked where it does.

| # | System | Now | Work |
|---|---|---|---|
| 1 | Melee + hit detection | ✅ weapon-move hit data wired | Damage and hitstun are read from character/weapon move phases where present; light 5 / heavy 12 / special 25 remain old port assumptions without selector/value evidence. **Remaining:** original input branches, FA/HA variants, LA/StepA inputs and per-character special behavior |
| 2 | HP / KO / respawn / balloon | ✅ HP 100, KO, **airborne** respawn (`Fighter::respawn()`), Overkill +1/hit, per-team LIMIT, 20+bonus%/KO | Remaining: the KO move's own descent/recovery as the respawn clock (the port uses one 3 s KO clock — `match_economy.h` port rules), the random stage-bounds respawn point (the port keeps the spawn slot), the between-rounds red-capacity creep (`FUN_00635d40` case 4 @0x63691c-0x63692b, multi-round only), the 3-beat result sequence and the loop back to team select (issues #13/#20) |
| 3 | Projectiles + charge | ✅ port tiers, fractional stocks, reload gate, tama channel, sparks | Tap/yellow/red tiers are port rules; `shotA/B/C` labels have no established tier/animation mapping. **Fractional ammo stocks** (MAIN 6, CHARGE 2, fill = recharge readout), reload gating, `collision_tama.x` channel, hit sparks |
| 4 | Movement full set | ✅ dash/backdash/sidestep + air dash, hold-jump flight | Double-tap dash (8-way + air), hold-jump fly timer, dash+attack and aerial variants |
| 5 | Stamina + limit gauge | ✅ bar + 3 modes; aura/EX are placeholders | **Contextual** stamina drain + fast refill. Hypermode bar per §3.4: fill by damage dealt/taken per mode, S to activate (Kakera auto on death), 15/25 s durations, damage ×0.75/×1.5 (Oyashiro), ×0.20/×1.5 (Kakera), stun rules, Friendship recharge boost. Remaining: real aura VFX (cube stand-in), per-character EX content (move 503 is a conditional EX follow-up; its animation/string-key binding is unresolved), ゲージ増加量 battle setting |
| 6 | Teams and partner control | ❌ | 2v2 slots and partner control remain open; the tag voice keys alone do not establish a swap mechanic |
| 7 | Overkill | ❌ | Downed-hit detection, **+1/hit** within the **3 s** window, gray-lock cutoff |
| 8 | Bots | ❌ (P2 is a dummy) | AI: approach/retreat, melee range checks, block/dash reactions, difficulty tiers for empty versus slots |
| 9 | Split-screen | ❌ (RE'd: 4 viewports as a **400×300** quadrant grid in 800×600 — `research/decompiled/FUN_006396f0.c:63-66`, :82-96; the old 256×448 reading came from the options-screen ctor `FUN_00402890`, not the split path) | Viewport grid (1/2/4), per-player ArenaCamera |
| 10 | Versus frontend | ✅ **title** (`foundation/src/ui/screen_title.*`, `--screen=title`); select/VS/result missing | Team → char → weapon/costume → hypermode → controller → ready → stage/settings → VS sting → result sequence (all captured in `docs/reference/`; order per `ROADMAP-PENDING.md` §E); punishment/titles as session flags |
| 11 | LAN netplay | ❌ (DirectPlay 8 documented, not portable) | Replace, don't port: delay-based (original uses input delay ~3) lockstep over UDP, default port **37564**, `addresslist.txt` server list, lobby (8 max, team/member lock, chat flag, host-start), char/stage sync, desync hash |
| 12 | Options / controller setup | ❌ stubs | Bindings table (Z/X/C/A/S/D/Q/W + arrows, 1P kbd / P2-4 pads) persisted; 4 toggles + 4 sliders; input-model redesign first (11 functions, 7 slots) |
| 13 | Story mode | ❌ (video player is a stub reporting `Unimplemented` — `foundation/src/audio/video.h`; no movie plays) | Deferred: prologue/staffroll playback + preset-team ladder, no branching/saves |

### Milestone cut

- **Playable local versus**: 1–7 + 9–10 (two humans or bots, split-screen, balloon decides).
- **Netplay-ready**: +11 (LAN lobby → synced versus).
- **Complete enough**: +12, story playback (13).

## 5. Non-goals (reaffirmed)

Online matchmaking beyond LAN, story branching/saves, localization
(Japanese UI stays), replays/training/survival extras, graphics settings
(fixed 800×600), mod support, anti-cheat.
