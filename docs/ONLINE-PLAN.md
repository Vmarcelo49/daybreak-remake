# Online plan

The owner made online the priority on 2026-10-30. This is the plan for M6's online work, and it
answers issue #3. Do the steps in order: each ends with something an agent can run and check, except
where marked.

## Decisions

| Question | Decision |
|---|---|
| Netcode | Rollback, through [GekkoNet](https://github.com/HeatXD/GekkoNet) as a pinned dependency |
| Connection | Direct IP and port, plus NAT punching through a rendezvous server. No game traffic passes through a server |
| Platforms | Linux and Windows play together. Web and macOS are out |
| Matches | Versus, 2 to 4 humans, one per machine, with COM in the free slots |
| Disconnect | COM takes over the slot and the match goes on |

Chosen here, and easy to change:

- The default is 2 frames of input delay and a prediction window of 8, both adjustable. The original
  used about 3 frames of delay with no rollback (`docs/game-spec.md`).
- Peers must have an identical game: same protocol version and same bundle hash. A mismatch is
  refused in the lobby with a message.
- Pause is off online. One round per match, as offline, then back to the lobby.
- Spectators, ranking, chat, reconnecting and a relay are not in this plan.
- This does not connect to the original game's netplay.

## What was measured

From 2026-10-30, on one machine. All tier 5 or below, and none of it says anything about the original.

| Result | Limits |
|---|---|
| 25,029 forced rollbacks of 8 ticks, over 5 runs on one roster with up to 51 live projectiles and HP reaching 0, never diverged | The harness copies `Impl`, its fingerprint is partial, and `resolve_victory` was empty |
| The whole state copies with `=`, in about 10 µs on a warm ring, over 113 KB plus heap | Measured once by the first report, in the same harness |
| A tick costs at most 109 µs with 4 idle humans and 327 µs with 4 COMs | Excludes `CoreFighter::refresh()` and rendering |
| `simctl` built with MinGW under Wine gave the Linux hash on 3 rosters at 3,600 ticks | The hash is partial. No native Windows, and no human input script |

## Architecture

```
frame loop (60 Hz)
  └─ src/net/session      owns the GekkoSession and turns its events into battle calls
       ├─ Save  → Battle::saveState(ring slot), and the state hash as checksum
       ├─ Load  → Battle::loadState(ring slot), then refresh the views
       └─ Advance → Battle::step(inputs), collecting presentation only on the last tick
  └─ src/net/udp_socket   one UDP socket, every packet tagged: punch, lobby, or GekkoNet
  └─ src/frontend/screen_online*   host, join, lobby

server/   the rendezvous server, in Go
```

Only `src/net/` includes `gekkonet.h`, as `src/battle/battle.cpp` is the only door to the core.

**State.** GekkoNet saves a block of bytes, and ours holds heap. So `state_size` is 4: the block is an
index into a ring of snapshots we own. This cannot serve spectators who join late, which are out of
this plan. `limited_saving` stays off, because desync detection needs it off.

**Input.** One packed struct per human: `{x, z, buttons, present}`. `present` is always 1 for a live
player. COM slots send nothing.

**Disconnect.** GekkoNet agrees a session-wide disconnect frame and feeds zeros from there. So
`present == 0` appears on the same tick for every peer, rollback included, and the battle then runs
`RuntimeBattle::set_native_actor_owners`' handoff. No extra message is needed. Zeros before frame 60
are ignored, since an input delay and the first prediction also read as zeros.

**Lobby.** Host authority, over the same UDP socket, because that is the socket NAT punching opens.
There are no acknowledgements: each side keeps resending its whole state until the other's state shows
it arrived. The host picks stage, rules and seed.

## Steps

### 1. A battle that can rewind

Done on 2026-10-30.

- `Battle::saveState` and `loadState` in `battle.cpp`: combat, world, projectiles, effects, CPU, ticks,
  `tacticsHeld`, `victoryResolved`, the cumulative hash and the cameras. The owners join at step 4,
  when something first changes them.
- The projectile serial stays in the process-wide counter, and out of the hash. Without host events
  nothing reads it, and supplying a session's own sequence would turn host events on. If step 4 starts
  using host events, this changes.
- `Battle::stateHash`: named fields, including the 624 RNG words, magazines, score and hit state. The
  existing `hash()` stays, so the fingerprints do not move.
- Promote the harness to `tests/rollback_stress_test.cpp`, on the real `Battle`, through match end.

**Done when:** rollbacks every tick for a full match on 4 rosters match an uninterrupted run on
`stateHash`; changing each hashed field changes the hash; the fingerprints are unchanged.

`stateHash` covers what the core exposes. Its private fields are not hashed, so a divergence there
shows only once it reaches a hashed field, such as a position or the RNG.

### 2. Presentation that survives a rewind

Done on 2026-10-30.

- `CoreBattle::save_state` and `load_state` add the fighters, with their trails and result titles, the
  economy and the round-over edge. `advance` takes inputs directly, for the session to call.
- A replayed tick reports only sounds, voices and effects it has not reported for that tick, so a
  correction can add a hit the prediction missed.
- `previousFighter` and the views' cameras stay in the app and are not replayed: they run once per
  shown tick, and a correction moves them from where they were.

**Done when:** a scripted match with rollbacks forced gives a final frame with the same pixels as one
without them, and no event fires twice. A sound or an effect that a wrong prediction already showed
stays, and is judged at step 8.

The app leaves the battle as soon as `economy().roundOver()` is set, which a wrong prediction can do.
Step 4 added the confirmed check, for step 6 to use.

### 3. GekkoNet on one machine

Done on 2026-10-30.

- Commit `9da2363d` is pinned in `scripts/fetch_deps.sh` and built as a separate C++20 static library.
  It built with GCC and MinGW on the first attempt. Native only, without `asio`.
- `src/net/session` drives the real battle through `GekkoStressSession`, with `--net-stress=8`.
- `tests/net_stress_test.cpp` runs a full match. Its MinGW build runs by hand under Wine.

**Done when:** the stress session runs a full match headless, on Linux and under Wine, with no desync
event, and the worst 8-frame rollback fits inside a 16.7 ms frame with rendering.

Measured on one machine, with an 8-tick rollback on every tick, which is harsher than real play:

| | Mean | Worst | Over 11.4 ms |
|---|---|---|---|
| Linux, 4 humans | 1.4 ms | 4.4 ms | 0 |
| Linux, 4 COM | 2.2 ms | 9.1 ms | 0 |

Those are 3 runs with the machine at a load near 4. At a load near 15, the same test reached 79 ms, at
different ticks each run. Under Wine the worst was 37 ms, measured only on a loaded machine. So a busy
player's machine can miss a frame in a rollback, and step 8 has to judge how that feels. 11.4 ms is
16.7 ms less the 5.3 ms `docs/PERFORMANCE.md` gives the four-view renderer, not measured together.

### 4. Two instances over UDP

Done on 2026-10-30.

- `src/net/udp_socket`, `src/net/lobby`, and the handshake: protocol version, bundle hash, roster,
  stage, rules, seed. Only the match's own peers, with its token, reach GekkoNet.
- `netctl`, a headless peer with no window, takes `--host PORT` and `--join IP:PORT`. `daybreak` gets its
  way in at step 6, through the screens.
- `tools/net_proxy.py` adds delay, jitter, loss and duplication.
- Disconnect to COM.
- The bundle hash reads sizes and each bundle's first and last megabyte, not 4.6 GB.

**Done when:** a CTest runs 2 and 4 headless instances on localhost through the proxy (100 ms, 5%
loss), 10,000 ticks, with equal `stateHash`; killing one instance mid-match leaves the rest equal, with
COM in that slot; a different bundle hash is refused.

**For step 6:** leave the battle on `Session::round_over_confirmed`, not `economy().roundOver()`. Sounds
filtered by `controlled_slots` still treat every human as local. Everyone waits out GekkoNet's default
5-second timeout when a player drops, which step 8 has to judge.

### 5. Linux with Windows

Done on 2026-10-30.

- `simctl` builds for Windows too, with `--busy` and `--hash-log`, and `tests/cross_build_check.py`
  compares builds. It skips without Wine or `build/windows/simctl.exe`.
- The two C runtimes differ in the last bits of `sin`, `cos` and `atan2`, in doubles. The core casts to
  float at once, which hides it until a rare value rounds the other way. So the core now uses
  `src/battle/det_math.c`, musl's code, through a macro in `core_prelude.h` and with its headers
  untouched. `pow` was only ever squaring. `fmod`, `sqrt` and the rounding functions stay in the C
  runtime, whose answers are exact by definition.
- `battle_core` builds with `-ffp-contract=off`.
- `.github/workflows/determinism.yml` compares math digests on a real Windows machine.

**Done when:** all 46 combos match between Linux and MinGW for 10,000 ticks.

Result: 36 matches of 10,000 ticks cover the 46 combos as human, COM and a human among COMs, with equal
`stateHash` and `hash`. The fingerprints did not move, and `det_math` stays within 1 ulp of glibc with
no float differing in 4 million samples of each function. On a real Windows machine, every math digest
equals Linux's, the x87 long double included.

Limits:

- The whole simulation ran under Wine only, since a real Windows machine in CI has no game data. Step 8
  is the first full match on real Windows.
- The workflow's executable links Ubuntu's MinGW runtime, while `build.sh windows` links UCRT here.
- MinGW's startup sets the x87 to 64 bits on the main thread, where the simulation runs. A new Windows
  thread starts at 53, so the simulation must not move to another thread.
- macOS, ARM and the web were not compared, and FMA is the risk on ARM.

### 6. Screens

Done on 2026-10-30, except for the owner's judgment of the layout.

- `NETWORK` on the title opens `src/frontend/screen_online.cpp`: host, join by address, and the name, port
  and input delay. Text turns on a wheel, so a pad can enter it. Join by code waits for step 7.
- A lobby: four slots with names and ping to the host, each player's character, weapon and hypermode,
  ready, and stage, time limit and health for the host. The host's start picks random COMs.
- Clear messages for wrong version, wrong game data, a full room, a closed room and silence.
- A `[network]` settings section, schema v7. The server list waits for step 7.
- The match leaves on `Session::round_over_confirmed`, and everyone returns to the lobby after results.
- Pause is off. The pause key leaves the match at once, and the others get a COM after the timeout.
- `--net-host=PORT` and `--net-join=IP:PORT` open the lobby directly. A capture in a room runs at 60 Hz, since
  peers live in real time.

**Done when:** a scripted run walks title, lobby, battle, results and lobby on two instances. **The
owner judges the layout.**

Result: `online_flow_check` starts two headless games at the lobby rather than the title, and they walk
lobby, VS, battle, results and lobby with 0 desyncs. The title and menu rows were not driven by that run.

Limits: the Japanese labels of these screens are this project's own wording and need a reader's check.

### 7. Rendezvous server and NAT punching

Adapt the owner's relay from `Vmarcelo49/ReCaster`, `server/`, into `server/` here. It has what is
needed: TCP signaling, UDP endpoint discovery, room codes, a TTL, Docker, and no external dependencies.

| ReCaster today | Needed here |
|---|---|
| A room is one host and one client | Up to 4 peers. Each receives every other peer's endpoint |
| One public endpoint per peer | Also the private one, so peers behind the same router can connect |
| Done after two `TunInfo` messages | The room stays open until every peer reports all its links, or the TTL ends |
| Client in `src/common/net/relay/`, over ENet | A new client on `src/net/udp_socket` |

A full mesh of 4 is 6 links, and all must open before the match starts. A failure names the peer and
suggests direct IP. Rate-limit joins, because 4-letter codes can be guessed. Players see each other's
IP, and the lobby says so.

**Done when:** Go tests pass, and a CTest runs 4 instances on localhost through the local server.
Real NAT is judged at step 8.

**The owner deploys the server** and gives the address that goes into the default server list.

### 8. Real play (owner)

Linux with Windows on real networks: 2 players, then 4, over LAN and internet. Check the feel at the
default delay, wrong sounds after rollbacks, a dropped player, and whether punching works on real
routers. Then close #3, and decide whether a relay is needed from how many connections failed.

## Stop and ask

- Cross-build hashes differ past the attempt ceiling (step 5).
- GekkoNet does not build with MinGW, or its stress session shows a problem in the library (step 3).
- Keeping the state hash coherent needs broad edits to the core.
- Original-runtime parity stays `not verified`. A game that stays in sync online proves agreement
  between peers, not agreement with the original.
