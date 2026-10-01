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

- **Attack button**: melee combo starter; variants with held direction
  (horizontal + attack, vertical + attack), dash + attack, and aerial
  versions. 3 tiers exist in data (`attackA/B/C`, `specialA/B/C`).
- **Shoot button**: fires the equipped weapon's projectile (`shotA/B/C`,
  `shotFinal`). **Tap** = quick (black) shot.
- **Charge**: holding shoot fills a meter with **two thresholds**.
  Release at yellow bar = yellow charge attack; at red bar = red charge
  attack (stronger). ([Menus/charge](https://higurashidaybreak.fandom.com/wiki/Menus))
- **Reload states** (`reloadOK/NG`) gate projectile users between volleys.

### 3.2 Movement

- Double-tap a direction = **dash** that way — all 4 ground directions
  **and in the air** (air dash).
- Jump; **holding jump flies** for a short time (limited flight meter).
- Guard, tag (`tagfront/tagback/tagOK` swap the active partner in 2v2),
  provoke (taunt), revival and KO/down states round out the 40+ animation
  states in the binary (full list: `docs/reverse-engineering.md` §14).

### 3.3 Camera

Always locked onto an enemy fighter. A **target button cycles** enemies;
**holding it aims at your ally** instead. Camera keeps 300 height / 800
distance offsets, orbits at 45° baseline, and spring-collides against
`collision_camera.x` (RE: `reverse-engineering.md` §14).

### 3.4 Meters

- **Stamina**: spent by dashing and by holding block. Empty = no dash,
  guard breaks down.
- **Super meter**: fills when dealing **and** taking damage; powers
  `specialA/B/C` and `shotFinal`-class attacks.
- Mapping to RE states: `HPcheck` (low HP), `nearWin/nearLose`,
  `guard/guarded`, `spark` (hit VFX trigger).

### 3.5 Winning — the balloon

Each team has a **balloon** at the screen edge. A KO fills it
**~20–23%**; the KO'd fighter **respawns airborne**. Hitting the downed
fighter scores **Overkill: +1–2% per hit** until the lock-on indicator
turns gray. At **100% the balloon pops and that team loses**.
([Basics](https://higurashidaybreak.fandom.com/wiki/Basics),
[Overkill](https://higurashidaybreak.fandom.com/wiki/Overkill))

## 4. Build plan (ordered)

Status key: ✅ in remake · 🔶 partial · ❌ missing. Current code truth
in `README.md` + audit notes; RE truth in `reverse-engineering.md`.

| # | System | Now | Work |
|---|---|---|---|
| 1 | Melee + hit detection | 🔶 states exist, `take_damage` never called | Wire `D3DXIntersect` raycast (exists) into fighter-vs-fighter checks; damage numbers (light 5 / heavy 12 / special 25); hitstun/knockdown/KO transitions |
| 2 | HP / KO / respawn / balloon | ❌ | HP=100, KO state, airborne respawn, balloon 20–23%/KO, 100% = round loss, result screen |
| 3 | Projectiles + charge | ❌ | `shotA/B/C` + tap/yellow/red charge tiers, reload gating, `collision_tama.x` channel, hit sparks |
| 4 | Movement full set | 🔶 walk/run only | Double-tap dash (8-way + air), hold-jump fly timer, dash+attack and aerial variants |
| 5 | Stamina + super | ❌ (fields exist, unused) | Drain on dash/block, refill rules, super-gated specials |
| 6 | Tag + teams | ❌ | `tagfront/tagback/tagOK`, partner AI-or-player control swap, 2v2 slots |
| 7 | Overkill | ❌ | Downed-hit detection, +1–2%/hit, gray-lock cutoff |
| 8 | Bots | ❌ (P2 is a dummy) | AI: approach/retreat, melee range checks, block/dash reactions, difficulty tiers for empty versus slots |
| 9 | Split-screen | ❌ (RE'd: 4 viewports 256×448 in 800×600) | Viewport grid (1/2/4), per-player ArenaCamera |
| 10 | Versus frontend | 🔶 title/mode/char-select partial | Team select, costume/weapon pick (3 weapons), stage pick, result/rematch flow |
| 11 | LAN netplay | ❌ (DirectPlay 8 documented, not portable) | Replace, don't port: deterministic lockstep over UDP LAN for 2v2; menu + lobby + char/stage sync; desync detection via state hash |
| 12 | Options / controller setup | ❌ stubs | Persisted bindings (4 players), volume/brightness; only what versus needs |
| 13 | Story mode | ❌ (OP video plays) | Deferred: prologue/staffroll playback + preset-team ladder, no branching/saves |

### Milestone cut

- **Playable local versus**: 1–7 + 9–10 (two humans or bots, split-screen, balloon decides).
- **Netplay-ready**: +11 (LAN lobby → synced versus).
- **Complete enough**: +12, story playback (13).

## 5. Non-goals (reaffirmed)

Online matchmaking beyond LAN, story branching/saves, localization
(Japanese UI stays), replays/training/survival extras, graphics settings
(fixed 800×600), mod support, anti-cheat.
