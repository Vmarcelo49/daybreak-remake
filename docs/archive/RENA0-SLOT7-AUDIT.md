# Rena+0 slot-7 field and DAT audit

This is a bounded continuation of [`RENA0-SOURCE-MAP.md`](RENA0-SOURCE-MAP.md)
for the pilot combo only: character index 0, weapon slot 0. It inventories the
generated slot-7 admission body, its synchronous host seam and the shipped
data rows it can request. It does not change runtime code, the pilot contract,
or the owner's pending 2g verdict.

## Evidence and limits

The read-only install check pinned `DaybreakDX.exe` to the required SHA-256:
`27e61475fbb3ea67f5058e3e0e6e93ad71d16a4d83fa42b02e605913a6a07f02`.
No original or remake executable was launched. The local DATs had these
SHA-256 values:

| File under `GAME_DIR` | SHA-256 | Size | Parser result |
|---|---|---:|---|
| `data/rena/00.dat` | `acbd92ecaceea4fff430248404cc264a5867a596266e2bd004f9c08dc9c8a1d2` | 69,576 bytes | Entire file consumed; 122 state rows. |
| `data/item/001.dat` | `b534e1845d7bc1bca185f3caa5dc3919b8c376391ef25ba510aaeaa6530a635b` | 574 bytes | Entire file consumed; 2 attachment records, 2 magazines, 18 bullet rows. |

The parser is the existing ignored
`.local-analysis/porting-support/DaybreakPortingSupport-20261010/reference/editor_source/dat_workbench.py`
(`parse_fields(data, 'actor'/'item')`). The body is the exported
`.local-analysis/daybreak-rebuild/DaybreakRebuild-20261010/source/src/slot7_native_bodies_20260929.hpp:3-398`.
The code's own first line warns that generation does not prove native/world
behaviour. This audit has **source-backed branch facts** and an
**install-backed static data check**, but no execution trace. A DAT row can be
selected by a conditional request; its presence does not prove that input,
priority, contact, gauge and mode conditions ever make that request fire.

The following read-only check was run from the repository root with `GAME_DIR`
set to the matching local installation. It checks the three hashes, both
parser-consumed lengths, and every literal slot-7 target against the actor DAT:

```bash
python3 - <<'PY'
from pathlib import Path
import hashlib, os, re, sys
sys.path.insert(0, '.local-analysis/porting-support/DaybreakPortingSupport-20261010/reference/editor_source')
import dat_workbench as m
root = Path(os.environ['GAME_DIR'])
expected = {
    'DaybreakDX.exe': '27e61475fbb3ea67f5058e3e0e6e93ad71d16a4d83fa42b02e605913a6a07f02',
    'data/rena/00.dat': 'acbd92ecaceea4fff430248404cc264a5867a596266e2bd004f9c08dc9c8a1d2',
    'data/item/001.dat': 'b534e1845d7bc1bca185f3caa5dc3919b8c376391ef25ba510aaeaa6530a635b',
}
for name, digest in expected.items():
    assert hashlib.sha256((root / name).read_bytes()).hexdigest() == digest, name
actor_data = (root / 'data/rena/00.dat').read_bytes()
item_data = (root / 'data/item/001.dat').read_bytes()
actor = m.parse_fields(actor_data, 'actor')
item = m.parse_fields(item_data, 'item')
assert actor.pos == len(actor_data) and item.pos == len(item_data)
ids = {actor.fields[f'states[{i}].id']['value']
       for i in range(actor.fields['state_count']['value'])}
row = {actor.fields[f'states[{i}].id']['value']: i
       for i in range(actor.fields['state_count']['value'])}
assert actor.fields[f'states[{row[0]}].priority_b']['value'] == 0
assert actor.fields[f'states[{row[0]}].phases[0].frames[0].flags28']['value'] == 0x100
assert actor.fields[f'states[{row[20]}].priority_a']['value'] == 0
assert actor.fields[f'states[{row[400]}].priority_a']['value'] == 40
source = Path('.local-analysis/daybreak-rebuild/DaybreakRebuild-20261010/source/src/slot7_native_bodies_20260929.hpp').read_text()
body = source.split('inline void slot7_body_0_0', 1)[1].split('inline void slot7_body_0_1', 1)[0]
targets = {int(s, 0) for s in re.findall(r'FUN_00421080\((0x[0-9a-fA-F]+|[0-9]+)\)', body)}
assert len(targets) == 33 and not (targets - ids)
assert item.fields['attachment_count']['value'] == 2
assert item.fields['bullet_count']['value'] == 18
assert item.fields['magazines[0].capacity']['value'] == 6
print(f'PASS actor rows={len(ids)}; slot7 targets={len(targets)}, missing=0; item bullets=18')
PY
```

This run printed `PASS actor rows=122; slot7 targets=33, missing=0; item
bullets=18`. It checks row identity and parser completeness, not action
execution.

## What the body reads and writes

`Slot7BodyContext::w` is an array of 32-bit words; a source expression
`w[index]` addresses actor byte offset `index * 4`. The 397-line Rena+0 body
contains **61 distinct direct `w[...]` indices**, including reads and writes,
plus five distinct byte-read offsets (`0x84`, `0x318`, `0x844`, `0x845`,
`0x846`). Of the 61 word indices, **29 are constant priority-row references**.
This is a syntactic census, not the complete dependency count: the body also
uses `current_priority()`, `frame_flags`, partner reads, contact queries and
helpers with their own bank writes.

The word-index groups below are complete for direct `w[...]` references in
this body. A label is used only where the bundle's world bridge or parser
establishes it; other words stay unresolved.

| Body word indices | Actor byte offsets / meaning | Port counterpart or gap |
|---|---|---|
| `0x9e`, `0x9f` | `+0x278/+0x27c` input axes (`slot7_native_world.inc.hpp:92`). | `PlayerState` has directions and stick values (`input/input.h:44-70`); source sign and acquisition order need a case-level map. **Partial.** |
| `0xa0`, `0xa1`, `0xa2`, `0xa4`; `0xac`, `0xad`, `0xae` | `+0x280/+0x284/+0x288/+0x290` held jump/melee/shoot/special and `+0x2b0/+0x2b4/+0x2b8` released counters (`slot7_native_world.inc.hpp:93-94`). | `PlayerState::down`, edges and two-tick `press_timer` exist; they are not automatically the same held/release counters. **Partial.** |
| `0xc9`, `0xcb` | `+0x324/+0x32c` special limits (`slot7_native_world.inc.hpp:95`). | `CharacterMoves::header_values()` supplies the shipped actor header in the pilot; confirm units and exact slot before writing. **Candidate existing.** |
| `0x1f8`, `0x1f9`, `0x1fd` | `+0x7e0/+0x7e4/+0x7f4` status durations; `0x1f2-0x1f4` are `+0x7c8/+0x7cc/+0x7d0` combat-modifier outputs (`slot7_native_world.inc.hpp:96-97`). | The pilot seam already names the `+0x7f4` mapping as unresolved; no silent zero or stamina substitution. Modifier ownership also needs an explicit map. **Unresolved.** |
| `0x20c`, `0x20d`, `0x20e`, `0x20f`, `0x212` | `+0x830` dash-command cache, `+0x834` fighter charge gauge, `+0x838/+0x83c` mode charges, `+0x848` ready flag (`slot7_native_world.inc.hpp:97-98`). | `Fighter::charge_gauge()` is a real port channel (`fighter.h:794-811`); mode and command words need separate source-to-port checks. **Mixed.** |
| `0x2`, `0x1b7`, `0x1c8`, `0x1cc`, `0x2b7b`, `0x2b7d` | Actor slot; primary rounds `+0x6dc`; secondary rounds `+0x720`; secondary charge stage `+0x730`; current action `+0xadec`; phase `+0xadf4` (`slot7_native_world.inc.hpp:96-108`, `battle_magazine.hpp:4-13`). | Equipped `WeaponDefinition`, two `ShootingMagazine`s, `Fighter::action_state()` and phase exist. `Fighter` collapses some states and the timing/charge words need exact mapping. **Partial.** |
| `0x2ac` through `0xeb4` (29 constants; table below) | Destination row's priority A at `0x880 + state*0x1c`; `current_priority()` reads the current row's priority B at `+4` (`slot7_native_world.inc.hpp:86-89`, `slot7_native_control.hpp:43-46`). | `CharacterMoves::parse` reads the same consecutive DAT words into `CharacterMove::priority` and `cancelThreshold` (`character_moves.cpp:82-101`). **Data mapping established; timing of the current row still matters.** |
| `0x2bd3-0x2bd5` | `+0xaf4c/+0xaf50/+0xaf54` shot statistics, incremented by the body and copied back by the bridge (`slot7_native_world.inc.hpp:104,119`). | Do not equate a statistic increment with magazine admission, projectile birth or contact. **Output mapping pending.** |

The body writes modifiers `0x1f2-0x1f4`, gauge `0x20d`, scratch `0x3b`,
held-control words `0xa1/0xa2/0xa4`, and statistics `0x2bd3-0x2bd5` directly.
`FUN_00435560` writes magazine multiplier words; `FUN_0043f3e0` advances the
copied secondary magazine (`slot7_native_control.hpp:79-86`). These are
**in-bank operations**. `FUN_004220e0` calls a world activation service, then
updates the mode charge/active byte in the bank (`:72`). The bridge copies
selected outputs back after dispatch (`slot7_native_world.inc.hpp:110-122`).

### Priority words decode to requested state rows

Each listed priority index is `((0x880 + state*0x1c) / 4)` — the A word for
the destination state, not an arbitrary scratch field. The 29 constant
references in `slot7_body_0_0` decode as follows:

| Body word indices | Destination states |
|---|---|
| `0x2ac, 0x2c1, 0x2c8, 0x2dd, 0x2f2, 0x338` | 20, 23, 24, 27, 30, 40 |
| `0xa54, 0xa5b, 0xa62, 0xa9a, 0xaa1, 0xae0` | 300, 301, 302, 310, 311, 320 |
| `0xb26, 0xb2d, 0xb34, 0xb6c, 0xb73` | 330, 331, 332, 340, 341 |
| `0xbb2, 0xbf8, 0xc3e, 0xcca` | 350, 360, 370, 390 |
| `0xd10, 0xd17, 0xd1e, 0xd33, 0xd3a, 0xd48, 0xe6e, 0xeb4` | 400, 401, 402, 405, 406, 408, 450, 460 |

This constant set does not include every requested state: some branches share
a threshold, use contact/mode tests, or use `current_priority()` dynamically.
The actor DAT has priority rows for the requested states below.

## Synchronous host services

`Slot7BodyContext::event` calls the bound service immediately
(`slot7_native_control.hpp:59-63`), before the next generated statement. The
Rena+0 body uses six world-service kinds:

| Kind | Body call and source | World bridge result |
|---|---|
| `N` | `FUN_00421080(next)` in the action branches. | Validate the next state/phase against loaded actor DAT, update state and pose, or record explicit missing-DAT recovery (`slot7_native_world.inc.hpp:20-51`). |
| `R` | `FUN_0042c7b0()` in contact-gated branches. | Refresh combined contact flags from the actor ledger (`slot7_native_world.inc.hpp:72`). |
| `A` | `FUN_004220e0()` on special activation. | Begin the special mode and record its event (`slot7_native_world.inc.hpp:53`). |
| `V`, `v` | `FUN_00422240` and `FUN_00422560`. | Queue ordered voice requests; `v` validates its receiver tag (`slot7_native_world.inc.hpp:54-63`). |
| `P` | `FUN_00658a10(0)` on the mode-1 partner branch. | Return a copied ally snapshot used for partner charge/active comparison (`slot7_native_world.inc.hpp:73-77`). |

The body does not call the available `Y`, `T`, or `Z` world services in its
`3-398` span. The local `FUN_00435560` and `FUN_0043f3e0` are not additional
world callbacks. A mock that returns a final event vector after the body would
miss these intermediate reads/writes.

## Installed Rena+0 rows requested by slot 7

The generated body contains **33 distinct literal `FUN_00421080(next)` targets**.
All 33 have a state row in the installed Rena `00.dat`; none was missing.
The table gives each row's priority A/B and its phase animation-set sequence
from the existing read-only DAT workbench. It establishes data presence and
binding candidates, not actual gameplay admission.

| State | Priority A/B | Phase sets | State | Priority A/B | Phase sets |
|---:|---:|---|---:|---:|---|
| 20 | 0 / 5 | 13, 14, 15 | 23 | 0 / 5 | 22, 23, 24 |
| 24 | 0 / 5 | 19, 20, 21 | 27 | 0 / 5 | 16, 17, 18 |
| 28 | 0 / 150 | 16, 17, 18 | 30 | 0 / 10 | 54, 55, 56 |
| 40 | 5 / 0 | 2 | 300 | 10 / 20 | 31, 73, 74 |
| 301 | 20 / 30 | 33 | 302 | 30 / 50 | 34 |
| 310 | 20 / 40 | 39, 79, 80 | 311 | 20 / 40 | 40 |
| 320 | 10 / 100 | 47, 81, 82 | 330 | 10 / 100 | 51, 52, 53 |
| 331 | 10 / 50 | 59, 75, 76 | 332 | 10 / 100 | 83, 84, 85 |
| 340 | 20 / 30 | 88 | 341 | 30 / 150 | 89, 90, 43, 91 |
| 350 | 100 / 150 | 32 | 360 | 100 / 150 | 6, 7, 8 |
| 370 | 100 / 150 | 9, 10, 11 | 390 | 0 / 150 | 60, 61, 63 |
| 400 | 40 / 99 | 57 | 401 | 40 / 99 | 57 |
| 402 | 40 / 49 | 67 | 405 | 40 / 49 | 57 |
| 406 | 40 / 49 | 57 | 407 | 40 / 49 | 58 |
| 408 | 40 / 49 | 66 | 450 | 100 / 150 | 92 |
| 460 | 100 / 150 | 93 | 500 | 0 / 150 | 69 |
| 501 | 0 / 150 | 69 | | | |

Other Rena+0 DAT states, such as 329, 333, 334 and 469, are not literal
`FUN_00421080` targets in this slot-7 body. They may belong to action-body
transitions; do not report them as absent from the DAT or unreachable overall.

### Item 001 data that the host must use

The same installed-data pass read two attachment records and 18 bullet rows
from `data/item/001.dat`:

| Magazine | Capacity | Mode | Reload threshold | Shot interval | Charge stage threshold | Max stage |
|---:|---:|---:|---:|---:|---:|---:|
| 0 | 6 | 2 | 300 | 0 | 60 | 1 |
| 1 | 2 | 2 | 300 | 0 | 180 | 2 |

Bullet-table indexes 0-9 and 15-17 draw from magazine 0 except indexes 2
and 8, which draw from magazine 1. Indexes 10-14 have magazine `-1`
(unlimited by that admission rule). All 18 rows have variant 0; their `file`
values are 0-17 in index order. The `word04` value is 4 for indexes 0 and 6
and 3 for the others. These are parsed item fields, not a claim that every
bullet row spawns in a particular action. A shot-body request still needs
per-request magazine admission, a successful pool birth, script motion and
contact resolution (`RENA0-SOURCE-MAP.md` "Shooting to projectile lifecycle").

## Port consequence and next bounded check

The **DAT-row absence hypothesis is ruled out for the 33 literal slot-7 state
requests** in this pinned install. The open work is semantic: map each
load-bearing read/write and synchronous callback to the port's `Match`/
`Fighter`/`CharacterMoves`/`WeaponDefinition` owners, then test individual
conditional branches with explicit input, prior state and service results.
This audit does not promote the four mocks in
[`RENA0-ADAPTER-MOCKS.md`](RENA0-ADAPTER-MOCKS.md) to implementation.

### Bounded execution of the generated body

A local-only probe under ignored
`local-data/harness/rena0_slot7_body_probe.cpp` (SHA-256
`97153ace2c1b05ae7e47104b54cb2f8d2739b9455439a96fcf4eb79f71d6a126`)
compiled the bundle's actual `slot7_body_0_0` through its real
`Slot7BodyContext`. It set the unused controls/status/magazines explicitly to
zero and supplied the following tested values. The installed Rena idle row 0
has priority B `0` and its phase-0 frame has flag `0x100`; destination row 20
has priority A `0`; row 400 has priority A `40`; item 001's primary magazine
capacity is `6`.

| Case | Changed fixture input | Body outcome |
|---|---|---|
| Grounded idle → dash | Dash command word `+0x830 = 1`, gauge `+0x834 = 1000`, flag `0x100` | One synchronous `N` request for state 20. |
| Wrong frame gate | Same context, flag `0` | No state request or world service. |
| Empty fighter gauge | Same dash command and flag, gauge `+0x834 = 0` | No state request or world service. |
| Grounded idle → tap shot | First shoot-release tick `+0x2b8 = 1`, primary rounds `+0x6dc = 6`, flag `0x100` | One synchronous `N` request for state 400. |
| Empty magazine | Same release and flag, primary rounds `0` | No state request; one `v` voice request and `+0xaf4c` empty-shot statistic increments once. |

The commands run from the repository root were:

```bash
g++ -std=c++17 -O0 -I .local-analysis/daybreak-rebuild/DaybreakRebuild-20261010/source/src \
  local-data/harness/rena0_slot7_body_probe.cpp -o local-data/harness/rena0_slot7_body_probe
./local-data/harness/rena0_slot7_body_probe
```

Result: `PASS Rena+0 slot7: dash20 frame/gauge gates, shot400 admission,
empty-magazine refusal`. Assertions check both accepted and refused paths.
This is **standalone body execution with explicit stubbed world services**.
The `N` stub records the state request but does not bind animation, move an
actor or spawn a projectile. The fixture does not reproduce an entire live
actor's initialization; its inactive zeros are stated assumptions. It proves
these bounded body branches are sensitive to a frame flag, the fighter gauge
and ammunition,
not an integrated port outcome or original-runtime parity.

### Mapping the two probed branches to the port

| Gate or effect | Bundle body and data | Current port path | Evidence limit |
|---|---|---|---|
| Current/destination priority | Idle B `0`; dash-20 A `0`; shot-400 A `40`; loaded through `slot7_native_world.inc.hpp:86-89`. | `CharacterMoves::parse` owns these as `cancelThreshold`/`priority` (`character_moves.cpp:82-101`); melee admission already compares them (`melee_admission.h:67`). | A source field match; not proof the port checks them at the same tick for dash and shoot. |
| Frame's `0x100` window | Rena idle row 0 has this flag in its installed frame record; `slot7_body_0_0:69,301` gates the tested requests. | `current_move_record()->stateFlags` is available (`fighter.h:849-852`); the main `Fighter::update_state_machine` calls `try_dash` and `try_fire` from broader actionable logic (`fighter.cpp:815-861`). | The probed empty-flag refusal is not yet a port scenario. |
| Dash command and gauge | `+0x830 = 1`, `+0x834 > 0` requests state 20 with the priority/flag gates (`slot7_body_0_0:66-74`). | Double-tap calls `try_dash`; its programmed forward branch checks `m_stamina`, which **is** the recovered `+0x834` rule at 1/10 scale (`dashDrain` 1.20 = 12/tick; phase exit at `m_stamina <= 0`), while `Fighter` separately carries `m_chargeGauge` (`fighter.cpp:826-836,2940-2951`; `fighter.h:794-811`). | **Corrected 2026-10-22:** the gauge-zero comparison below was an **injected-state artefact** (gauge 0 with stamina 100 is not a state the original can be in), not a behaviour difference; the owner's observation that only the stamina meter gates a dash is what settled it. The pilot gate added on the charge counter was removed. Original-runtime parity remains unverified. |
| Released shot and main rounds | `+0x2b8` in 1..19 and `+0x6dc > 0` request 400 (`slot7_body_0_0:259-305`); zero rounds request voice `v` and increment `+0xaf4c` (`:178-181`). The wrapper at `:172` is what makes the empty branch reachable: its `+0x834 < 1` term excludes the ordinary shot admission. | The port stores a charge hold, calls `try_fire` on release, and returns early when `can_fire` finds zero bound rounds (`fighter.cpp:2992-3014`). Programmed callbacks later call `admit_shooting_row` (`fighter.cpp:2460`). A pilot `PilotShot::empty_shot_voice` consultation in that empty branch publishes the body's voice id on the port's existing per-tick cue. | The equipped `Match` comparison below confirms **no port voice** on the flag-off empty tap, and that finding is now an asserted part of `rena0_pilot_gate_test`. The body statistic has no mapped observable; it is not measured in the port and no field was invented for it. |
| `N` state service | The body invokes `FUN_00421080` synchronously; the bundle host validates and binds the next state (`slot7_native_world.inc.hpp:20-51`). | The port's `Fighter::set_state`, move row and resolver own state/phase/set binding (`fighter.cpp:1038-1060`; `native/rena0_resolver.h:74-108`). | Exact admission and binding order still needs a same-fixture adapter check. |

The bundle's main-round test at slot 7 happens before projectile creation. The
port's programmed shot callbacks consume the DAT-selected magazine later,
before `Match` drains pending shots into its pool (`fighter.cpp:2460`,
`match.cpp:299-331`). Those stages must be compared separately; a shot-400
state request is not evidence that a projectile was born.

### Production `Match`/`Fighter` comparisons

Two local-only probes link the **current `foundation_gameplay` sources**, load
real Rena+0 actor/item/rig data through `test::Combo`, equip both fighters, and
step normal BattleStart to grounded Idle with a neutral equipped opponent.
They use open-field movement. No pilot policy is attached: these measure the
current flag-off port path. Sources and saved output are ignored under
`local-data/harness/`:

| Probe | Source SHA-256 | Saved output SHA-256 |
|---|---|---|
| `dash_rena0_match_probe.cpp` | `d2a224d9ad171db9a887495e2326068619e18651e25a6be0afb8fd19781a0c3d` | `dash_rena0_match_probe.log`: `0cec45e297d1be433a5b33f902f154b413042193329694962de7784ac776fe02` |
| `empty_shot_probe.cpp` | `c7892549f312b726709867b80845087a2c753cf5dcc08835dcd6c5e00357c4cb` | `empty_shot_probe_v3.log`: `7c219504343dc68f2767074c6076c1977879e4df18d37d646c6e07700e3e4a00` |

The two probes build from a local-only CMake project without touching the
existing `build/linux` directory:

```bash
cmake -S local-data/harness/empty_shot_project -B local-data/harness/empty_shot_build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build local-data/harness/empty_shot_build --target dash_rena0_match_probe empty_shot_probe -j2
./local-data/harness/empty_shot_build/dash_rena0_match_probe
./local-data/harness/empty_shot_build/empty_shot_probe
```

Set `GAME_DIR` to the verified local installation before running these commands
(or let `test::gameInstall()` discover it). Neither command launches or changes
that game. Both probes exited 0. The dash sequence is run twice
within one process and requires identical samples. Two saved runs of the
updated empty-shot probe were byte-identical (`cmp` exit 0).

**Dash input equivalence.** The bundle keyboard maps Up to `z=-1`
(`local_battle_keyboard.hpp:14-18`). Its actual `BattleDashHistory::push`
returns command `1` for `z=-1,0,-1` (`battle_ground_dash.hpp:9-20`);
`local-data/harness/dash_history_rena0_probe.cpp` compiled that helper and
printed `PASS bundle dash history: Up, release, Up -> command 1`. The port
used the same Up press/release/press sequence through `compute_edges`.

| Dash step | Equipped port observation | Recovered body result under the same tested branch fields |
|---|---|---|
| Before input | Idle row 0, bound move 0, record flag `0x100`, stamina 100; `set_charge_gauge(0)` leaves gauge 0 but does **not** drain stamina — the injected state the correction above describes. | Idle B 0, dash-20 A 0, grounded, flag `0x100`, command 1, gauge 0. |
| Tick 0 Up; tick 1 release | Port returns to Idle row 0; gauge remains 0. | Bundle history produces command 1 on the next Up. |
| Tick 2 Up | Port enters dash row **20**, bound set **13**, stamina **98**, gauge **0**; tick 3 remains on row 20. | Slot-7 body makes **no `N` request** at gauge 0 (`slot7_body_0_0:66-74`; body probe assertion). |

This is a **bounded mismatch between the recovered body and the current
flag-off port** under an injected zero-gauge setup with real equipped data.
It does not establish how often zero gauge arises naturally or original-runtime
parity. The port's `try_dash` checks separate stamina
(`fighter.cpp:2940-2946`), which explains its admission in this setup.

**Empty-tap input equivalence.** The bundle's `BattleHumanInput::acquire`
publishes the previous held shoot count on release
(`battle_human_input.hpp:31-37`). A local compiled helper
`shot_release_rena0_probe.cpp` printed `held=1 released=1` for a one-tick
Shoot press/release, satisfying slot 7's `1..19` gate. The port used the
same one-tick press/release shape.

The equipped port consumed its actual primary stock from 6 to 0 through six
funded taps, waiting for each programmed firing callback and recovery before
the next. The callback spent a round about 49 ticks after release; admission
and consumption were recorded separately. On a seventh, empty tap it reported:

```text
empty-tap release beforeState=0 afterState=0 action=0 shotRequest=-1 ammo=0
shotFired=0 shotsSpawned=0 voice=-1 voiceAlt=-1 audited=0 pendingShot=0
```

The recovered slot-7 body, with released count 1 and primary rounds 0,
requested **one `v` voice** and incremented `+0xaf4c` once, without requesting
state 400 (`slot7_body_0_0:178-181`; body probe assertion). The **voice event
differs in this bounded comparison**. The port exposes no corresponding
empty-shot statistic in this scenario, so the statistic is an unmapped source
output rather than a measured port difference. The port's early `can_fire`
return explains the absent voice (`fighter.cpp:3002-3015`).

One funded tap spent a round and voiced but produced no pool birth. A follow-up
diagnostic counted **four live row-0 projectiles** immediately before that
spend, matching item 001 bullet row 0's pool capacity 4. The port's
`ProjectilePool::spawn` rejects at capacity (`projectile.cpp:80-90`). This is
a separate admitted-request versus pool-birth case, not an empty-tap result.

The production scenarios are **install-backed port checks (tier 4)**. Bundle
outcomes are compiled recovered-body checks with explicit context and stubbed
world services. Neither is original-runtime observation. The scenarios provide
concrete Rena+0 pilot discrepancies but do not themselves approve a contract
change or production fix.

An existing [original Rena weapon-selection print](../remake/docs/reference/weapon-select-rena.webp)
shows the selection UI only. It cannot expose priority rows, slot-7 field
values, callback order or projectile admission, so this report uses the source
and pinned DAT parse for those claims. No new screenshot or original-game run
was needed for this question.

### The two discrepancies are reproduced, and a pilot seam now owns them

A later pass reproduced both comparisons byte-for-byte against the current
source (dash log `sha256 0cec45e2…`, empty-tap log `sha256 7c219504…`, both
`cmp`-identical to the saved outputs; the compiled body probe still passes).

Of the two, **one was a real port gap and one was not**:

| Observation | Outcome | Evidence |
|---|---|---|
| Empty tap silent in the port, one voice + statistic in the body | **real gap, closed on the pilot path**: one method on the existing `PilotShot` interface (`empty_shot_voice` = the body's id 24) consulted in `fire_shot`'s empty branch. The owner independently confirmed the behaviour ("Rena says a line in Japanese that she needs to wait") | the offline fixture pins the voice's full argument tuple `(tag, 0x18, 10, 1)` and the statistic; the port test measures voice 24 with no shot row, no spawn and an unchanged magazine, and no voice with the flag off |
| Gauge-0 dash admitted by the port, refused by the body | **withdrawn 2026-10-22: not a behaviour difference.** `+0x834` is the stamina meter and the port already applies the recovered rule to `m_stamina` at 1/10 scale (`dashDrain` 1.20 = 12/tick, same phase exit, same `m_stamina <= 0` refusal). The measured "difference" came from forcing the *other* counter to 0 while stamina stayed full — a state the original cannot produce | the pilot gate test now pins the drain equivalence, flag-on/flag-off agreement on row 20/set 13, and a seeded wrong gate that must fail; `PILOT-EVIDENCE-CONTRACT.md` V3-6 records the erratum |

The statistic (`+0xaf4c`) still has **no port owner** and is deliberately not
published through a new `Fighter` field. The command word `+0x830` stays a named
stand-in for the port's double-tap history. The remaining modelling debt is the
port's two counters for the one original resource, with different regen rates —
named in V3-6 and deferred to the post-verdict cleanup.

Shot voice/statistics remain distinct from successful projectile pool birth, and
none of this establishes complete pilot coverage, contract acceptance or a
verdict. The field-level maps that go with these two rows are `PILOT-SEAM.md`
§25-§27; the command word's producer and the 33-state ownership census are in
the source map.
