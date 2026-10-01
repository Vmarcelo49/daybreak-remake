# Higurashi Daybreak — game spec & build plan

> What the game is, how it plays, and in what order we rebuild it.
> Sources: original-game observation (owner), RE findings in
> `docs/reverse-engineering.md`, and the [Higurashi Daybreak Wiki](https://higurashidaybreak.fandom.com/wiki/Higurashi_Daybreak_Wiki).
> Scope authority: `decisions.md` D6 (versus + LAN netplay are the focus).

## 1. What the game is

A **2v2 3D arena fighter** set in the *Higurashi When They Cry* universe
(Twilight Frontier / 07th Expansion, 2005; Kai expansion 2007).
Two teams of two fight in 3D stages modeled on series locations
(Hinamizawa areas), each with its own layout, collision, and BGM.

- **Roster**: 14 fighters (16 in Daybreak DX: +Hanyuu, +Natsumi).
  Each has **3 selectable weapons** (the third needs the expansion),
  which change the projectile/attack set.
  ([Characters](https://higurashidaybreak.fandom.com/wiki/Characters))
- **Stages**: ~12 (`stage01`–`stage06`, `stage11`–`stage15`, `stage21`
  confirmed in shipped data), each with visible meshes plus separate
  `collision.x` / `collision_camera.x` / `collision_tama.x`.
- **Boot flow**: `movie/op.mpg` plays (skippable with any button) →
  static main menu. Menu text is Japanese; a community mod translates it:
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
  versions. 3 tiers exist in data (`attackA/B/C`, `specialA/B/C`).
  There is **no dedicated heavy button** — heavy is likely a
  directional variant (input model still provisional, see §3.6).
- **Shoot button (C)**: fires the equipped weapon's projectile
  (`shotA/B/C`, `shotFinal`). **Tap** = quick (black) shot. Ammo is a
  **counted stock** (MAIN 6, CHARGE 2), recharging over time — the HUD
  bar fill fraction *is* the recharge readout (model as fractional
  stock, not bullets + timer).
- **Charge**: holding shoot fills a meter with **two thresholds**.
  Release at yellow bar = yellow charge attack; at red bar = red charge
  attack (stronger). ([Menus/charge](https://higurashidaybreak.fandom.com/wiki/Menus))
- **Reload states** (`reloadOK/NG`) gate projectile users between volleys.
- **Special button (S)**, **tactics button (Q/作戦)**: exist on the
  controller table; tactics (team orders?) is unmodeled — investigate
  with bot work.

### 3.2 Movement

- Double-tap a direction = **dash** that way — all 4 ground directions
  **and in the air** (air dash).
- Jump (**Z**); **holding jump flies** for a short time (limited flight).
- Guard (**D**, hold), tag (`tagfront/tagback/tagOK` swap the active
  partner in 2v2), provoke (taunt), revival and KO/down states round out
  the 40+ animation states in the binary (full list:
  `docs/reverse-engineering.md` §14).

### 3.3 Camera

Always locked onto an enemy fighter. A **target button cycles** enemies;
**holding it aims at your ally** instead. Camera keeps 300 height / 800
distance offsets, orbits at 45° baseline, and spring-collides against
`collision_camera.x` (RE: `reverse-engineering.md` §14).

### 3.4 Meters

- **Stamina**: spent by dashing, **jumping**, and holding block — and the
  bar is **contextual** (appears on use, drains while held, refills fast
  after). Empty = no dash, guard breaks down.
- **Limit gauge (super)**: fills when dealing **and** taking damage;
  behavior depends on the picked **hypermode** (Friendship / Oyashiro /
  Kakera): Oyashiro charges by taking damage (→ +attack/+defense/stun
  immunity), Kakera charges slower and triggers on death. Per-slot pick
  at versus setup, after weapon.
- Mapping to RE states: `HPcheck` (low HP), `nearWin/nearLose`,
  `guard/guarded`, `spark` (hit VFX trigger).

### 3.5 Winning — the balloon

Each team has a **balloon** at the screen edge with a **`LIMIT` readout
(both default 100%) — the team loses when its balloon EXCEEDS its limit**,
not at a fixed 100%. Battle settings add a **per-team balloon-size
handicap %** (spec multiplier on capacity).
A KO fills ~20–23% (observed +21%); the KO'd fighter **respawns
airborne**. KO presentation is sting (撃破！) → inflate → floating `+N%`
delta. Hitting the downed fighter scores **Overkill: +1/hit**
(captured; wiki says 1–2%) until the lock-on indicator turns gray.
([Basics](https://higurashidaybreak.fandom.com/wiki/Basics),
[Overkill](https://higurashidaybreak.fandom.com/wiki/Overkill))

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

1P = keyboard; P2–P4 = pads (buttons 1–8). The 11-function/7-slot
mapping in our input layer is still provisional (see `input_manager.h`).
Menus vs battle accept different keys — menu handling must be
slot/context-aware, not a single global confirm/cancel pair.

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

Status key: ✅ in remake · 🔶 partial · ❌ missing. Current code truth
in `README.md` + audit notes; RE truth in `reverse-engineering.md`.

| # | System | Now | Work |
|---|---|---|---|
| 1 | Melee + hit detection | 🔶 states exist, `take_damage` never called | Wire `D3DXIntersect` raycast (exists) into fighter-vs-fighter checks; damage numbers (light 5 / heavy 12 / special 25); hitstun/knockdown/KO transitions |
| 2 | HP / KO / respawn / balloon | ❌ | HP=100, KO state, airborne respawn, balloon 20–23%/KO vs per-team LIMIT (+size handicap %), KO sting → inflate → +N% delta, 3-beat result, loop back to team select |
| 3 | Projectiles + charge | ❌ | `shotA/B/C` + tap/yellow/red tiers, **fractional ammo stocks** (MAIN 6, CHARGE 2, fill = recharge readout), reload gating, `collision_tama.x` channel, hit sparks |
| 4 | Movement full set | 🔶 walk/run only | Double-tap dash (8-way + air), hold-jump fly timer, dash+attack and aerial variants |
| 5 | Stamina + limit gauge | ❌ (fields exist, unused) | **Contextual** stamina drain on dash/jump/block-hold + fast refill; limit gauge with 3 hypermode behaviors (Friendship/Oyashiro/Kakera) |
| 6 | Tag + teams | ❌ | `tagfront/tagback/tagOK`, partner AI-or-player control swap, 2v2 slots |
| 7 | Overkill | ❌ | Downed-hit detection, **+1/hit**, gray-lock cutoff |
| 8 | Bots | ❌ (P2 is a dummy) | AI: approach/retreat, melee range checks, block/dash reactions, difficulty tiers for empty versus slots |
| 9 | Split-screen | ❌ (RE'd: 4 viewports 256×448 in 800×600) | Viewport grid (1/2/4), per-player ArenaCamera |
| 10 | Versus frontend | 🔶 title partial; select scenes missing | Team → char → weapon/costume → hypermode → controller → ready → stage/settings → VS sting → result sequence (all captured in `docs/reference/`); punishment/titles as session flags |
| 11 | LAN netplay | ❌ (DirectPlay 8 documented, not portable) | Replace, don't port: delay-based (original uses input delay ~3) lockstep over UDP, default port **37564**, `addresslist.txt` server list, lobby (8 max, team/member lock, chat flag, host-start), char/stage sync, desync hash |
| 12 | Options / controller setup | ❌ stubs | Bindings table (Z/X/C/A/S/D/Q/W + arrows, 1P kbd / P2-4 pads) persisted; 4 toggles + 4 sliders; input-model redesign first (11 functions, 7 slots) |
| 13 | Story mode | ❌ (OP video plays) | Deferred: prologue/staffroll playback + preset-team ladder, no branching/saves |

### Milestone cut

- **Playable local versus**: 1–7 + 9–10 (two humans or bots, split-screen, balloon decides).
- **Netplay-ready**: +11 (LAN lobby → synced versus).
- **Complete enough**: +12, story playback (13).

## 5. Non-goals (reaffirmed)

Online matchmaking beyond LAN, story branching/saves, localization
(Japanese UI stays), replays/training/survival extras, graphics settings
(fixed 800×600), mod support, anti-cheat.
