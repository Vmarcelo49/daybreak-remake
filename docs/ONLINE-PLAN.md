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
| 24,029 forced rollbacks of 8 ticks, over 5 runs on one roster with up to 51 live projectiles and HP reaching 0, never diverged | The harness copies `Impl`, its fingerprint is partial, and `resolve_victory` was empty |
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

**Input.** One packed struct per slot: `{buttons, x, z, present}`. `present` is always 1 for a live
player.

**Disconnect.** GekkoNet agrees a session-wide disconnect frame and feeds zeros from there. So
`present == 0` appears on the same tick for every peer, rollback included, and the battle then calls
the core's `BattleCpuDriver::set_actor_owners`. No extra message is needed. The ownership in `roster`
then changes mid-match, so it joins the snapshot.

**Lobby.** Host authority, with small reliable messages (sequence and ack) over the same UDP socket,
because that is the socket NAT punching opens. The host picks stage, rules and seed.

## Steps

### 1. A battle that can rewind

- `Battle::saveState` and `loadState` in `battle.cpp`: combat, world, projectiles, effects, CPU, ticks,
  `tacticsHeld`, `victoryResolved`, and the owners.
- Move the projectile serial out of the process-wide counter. `legacy_host_battle_events.hpp` says a
  session can supply its own sequence, so prefer that to editing the core. Any core edit goes in
  `PATCHES.md`.
- `Battle::stateHash`: named fields, including the 624 RNG words, magazines, score and hit state. The
  existing `hash()` stays, so the fingerprints do not move.
- Promote the harness to `tests/rollback_stress_test.cpp`, on the real `Battle`, through match end.

**Done when:** rollbacks every tick for a full match on 4 rosters match an uninterrupted run on
`stateHash`; changing each hashed field changes the hash; the fingerprints are unchanged.

### 2. Presentation that survives a rewind

- Sounds, voices and effects come out only on the last tick of a frame, and never while rolling back.
- Move `tacticsHeld`, `m_roundReported` and the economy edges into the snapshot or derive them again.
- Refresh `CoreFighter` caches after a load. Check `previousFighter`, trails, cameras and the HUD.

**Done when:** a scripted match with rollbacks forced gives a final frame with the same pixels as one
without them, and no event fires twice. A sound that fired for a wrong prediction is accepted, and is
judged at step 7.

### 3. GekkoNet on one machine

- Pin a release in `scripts/fetch_deps.sh`, and build it as a separate C++20 static library. Check
  MinGW first: the project's examples use Visual Studio only. **If it does not build there in 3
  attempts, stop and ask.**
- Replace its socket with our adapter, so `asio` is not linked.
- `src/net/session`, and a `GekkoStressSession` driving the real battle: `--net-stress=8`.
- Measure the worst frame with `refresh()` included.

**Done when:** the stress session runs a full match headless, on Linux and under Wine, with no desync
event, and the worst 8-frame rollback fits inside a 16.7 ms frame with rendering.

### 4. Two instances over UDP

- `src/net/udp_socket`, the lobby protocol, and the handshake: protocol version, bundle hash, roster,
  stage, rules, seed. Validate every packet's length and session token, since these come from strangers.
- `--net-host=PORT` and `--net-join=IP:PORT`, usable headless with scripted input.
- A test proxy in `tools/` that adds delay, jitter, loss and duplication.
- Disconnect to COM.

**Done when:** a CTest runs 2 and 4 headless instances on localhost through the proxy (100 ms, 5%
loss), 10,000 ticks, with equal `stateHash`; killing one instance mid-match leaves the rest equal, with
COM in that slot; a different bundle hash is refused.

### 5. Linux with Windows

- Build `simctl` when cross-compiling, and add a test that compares hashes across builds using busy
  scripted input and `stateHash`.
- Both release builds use the same compiler family and flags. Disable floating-point contraction with
  `-ffp-contract=off`, and confirm that the fingerprints hold.

**Done when:** all 46 combos match between Linux and MinGW for 10,000 ticks.

The risk is `std::sin`, `cos` and `atan2` in about 46 core files and `long double` in 8. If they differ,
replace them with one implementation under `PATCHES.md`, with citations, starting from the first
diverging field. The attempt ceiling applies. Past it, ask whether to ship same-platform play first.

### 6. Screens

- `ONLINE` on the title: the original's sheet already has a row for it. Host, join by IP, join by code.
- A lobby: slots, names (`soft_keyboard.cpp`), character and weapon choice, ready, stage and rules for
  the host, ping per peer.
- Clear messages for wrong version, wrong game data, a full room and a lost peer.
- Pause off, and a return to the lobby after results.
- A `[network]` settings section: name, port, delay, server list. Bump the schema in
  `docs/USER-SETTINGS.md`. Labels go in `assets/locale/en.txt`.

**Done when:** a scripted run walks title, lobby, battle, results and lobby on two instances. **The
owner judges the layout.**

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
