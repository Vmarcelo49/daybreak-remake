# Online plan — implementation record

The owner made online the priority on 2026-10-30. This document records the plan that built
online play (issue #3) and the measurements taken with it. The numbered steps below are
**history, not a work order**: steps 1–7 record completed implementation (the step 6 layout
still awaits the owner's judgment), and step 8 is the owner's manual real-play check.
Unbuilt ideas in "Later: the v2 lobby" are owner ideas, not assignments. Current
bugs and work are tracked in GitHub issues; current architecture and status are in
[`DIRECTION.md`](DIRECTION.md) and [`DEVELOPMENT.md`](../DEVELOPMENT.md).

## Decisions

| Question | Decision |
|---|---|
| Netcode | Rollback, through [GekkoNet](https://github.com/HeatXD/GekkoNet) as a pinned dependency |
| Connection | Direct IP and port, plus NAT punching through a rendezvous server. No game traffic passes through a server |
| Platforms | Linux and Windows play together. Web and macOS are out |
| Matches | Versus, 2 to 4 humans, one per machine, with COM in the free slots, chosen together on the game's selection screen |
| Disconnect | COM takes over the slot and the match goes on |

Chosen here, and easy to change:

- The default is 2 frames of input delay and a prediction window of 8, both adjustable. The original
  used about 3 frames of delay with no rollback (`docs/game-spec.md`).
- Peers must have an identical game: same protocol version, same simulation version and same
  bundle hash. A mismatch is refused in the lobby with a message. `kSimulationVersion`
  (`src/net/lobby.h`) is bumped with every change that can alter a simulated tick, which
  includes every change that moves a SIM fingerprint (issue #121).
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

**Invalid matches (issue #122).** A GekkoNet checksum mismatch immediately invalidates the
battle, logs the first frame, peer, checksums and build/protocol/simulation versions, and sends a
match-token-scoped abort. Peers acknowledge aborts, which are retransmitted to unacknowledged
peers for a bounded period. At round end peers exchange the round frame and a rolling digest of the
confirmed state hashes from frame zero through that frame. Each peer seals only after every offer
matches, and presents a result only after receiving every seal. A ten-second missing-peer timeout
fails closed; decisions are retransmitted after leaving battle, and late invalidation exits the
result screen. Periodic retransmission lasts ten seconds; the room keeps the outcome until the
next battle, so a late offer can still receive a response. A peer can leave the room rather than
waiting. The digest is bounded and is not a cryptographic proof of equality; the underlying state
hash is likewise not a proof of all possible simulation state. UDP cannot guarantee timely delivery
during a partition, so an already displayed result can be withdrawn on a late abort, but no protocol
can ensure simultaneous knowledge at all peers. This is a port-side online policy, not
original-runtime evidence. Protocol 6 is incompatible with older builds.

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
it arrived. The host picks the seed, and the selection screen decides everything else.

## Steps (historical implementation record)

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

Done on 2026-10-31, except for the owner's judgment of the layout.

- `NETWORK` on the title opens `src/frontend/screen_online.cpp`: host, join by address, and the name, port
  and input delay. The keyboard types a line, with a cursor, Backspace, Enter and Esc, and a pad turns its characters on a wheel. Enter on a join row joins. Join by code waits for step 7.
- **The lobby holds only the players, their ping and ready signs, a ready button and a leave button**, by the
  owner's decision. Chat is for a later version. It starts by itself once at least two are ready.
- **The match is chosen on the game's own selection screen**, played together with no rollback. `MenuLockstep`
  is a GekkoNet session with no prediction window: each machine runs the screen on the same frame with everyone's
  held buttons, and each peer plays as that controller. So characters, stage, rules and random picks need no
  packets, and the room's seed starts the same random numbers everywhere. Peers compare a hash of what it decided.
- Online, the selection cannot start the match until every player has a panel, and no player can make theirs COM.
- Backing out of the selection takes everyone back to the lobby, and so does a player leaving it or a differing hash.
- A `[network]` settings section, schema v7. The server list waits for step 7.
- The match leaves on `Session::round_over_confirmed`, and everyone returns to the lobby after results.
- Pause is off. The pause key leaves the match at once, and the others get a COM after the timeout.
- `--net-host=PORT` and `--net-join=IP:PORT` open the lobby directly, and a room opened so asks no server for a code. A capture in a room runs at 60 Hz, since
  peers live in real time.

**Done when:** a scripted run walks title, lobby, battle, results and lobby on two instances. **The
owner judges the layout.**

Result: `online_flow_check` starts four headless games at the lobby rather than the title, and they walk lobby,
selection, VS, battle, results and lobby with 0 desyncs. The title and menu rows were not driven by that run.

Limits: the Japanese labels of these screens are this project's own wording and need a reader's check. Any
player can edit the stage page and any player can back everyone out. One run, the first after a rebuild, went
back to the lobby by itself at tick 327 on both games, and the next 11 runs of the same script did not; the
reason now goes to the log as `[net] selection ended`.

### 7. Rendezvous server and NAT punching

Built on 2026-10-31, and running on the owner's server since then, on UDP port 3939. It is the game's default server, and the SERVER row or the settings file can name another. Real routers are judged at step 8.

- `server/` is adapted from the owner's relay in `Vmarcelo49/ReCaster`. It is UDP only and takes a room of up to 4,
  since a client already resends everything and only the game socket's address matters. It introduces a joiner and
  a host, and no game packet passes through it. A request is at least as large as any answer, so a forged sender gains
  nothing, and joins are limited to 20 a minute per address.
- A host gets a 4-letter code, shown in its lobby. A joiner tries the host's public and private addresses, and the
  first to answer is used. Meanwhile the host knocks on the joiner's addresses, which opens its own router.
- **Every peer proves a link to every other in the lobby**, with direct IP too. Each peer's public and private addresses
  reach the room in the host's plan, everyone probes everyone, and the start waits for the full mesh. If a link does
  not form within 10 seconds of everyone being ready, the lobby names the two players.
- GekkoNet knows a peer by one address, but a machine can show several. So a game packet carries its sender's number.
- `[network] server` holds the address, as an IP and port. Names are not resolved, so the online menu's SERVER row
  can edit it. Until one is set, there are no codes and direct IP still works.

**Done when:** Go tests pass, and a CTest runs 4 instances on localhost through the local server. Real NAT is judged
at step 8.

Result: `rendezvous_server_test` passes, and `net_play_check` plays 4 peers by room code on localhost, 885 frames
with equal `stateHash`, and refuses a wrong code. Limits: localhost has no router, so punching itself has not been
exercised. Symmetric NAT cannot be punched, and needs a relay. IPv4 only.

#### Rendezvous host renewal: trust model and residual risks (issue #126)

The source review behind issue #126 found that the server renewed a room's host endpoints from the
client-supplied 32-bit ID alone. That ID is not a secret: `encode_plan` (`src/net/lobby.cpp`) sends it
to every room member in match-plan packets. A member who learned the ID could send a host request and
redirect the room's rendezvous entry until the real host renewed. This was a source-backed concern,
not a demonstrated exploit; no packet was ever sent to the deployed server, and none of the tests
below use anything but in-process state or a loopback socket.

**Decision (owner approved Option B, 2026-11-19).** Rooms are authenticated. The server issues a
random 128-bit renewal secret when it creates a room and returns it to the host alone in the hosted
answer; the host echoes it in the 16 unused padding bytes of every later host request. Renewing a
live room requires the matching secret, compared in constant time; a wrong or missing secret is
answered with `failUnauthorized` and changes no state, not even the room's last-seen time. With no
live room for that ID, any request starts a fresh room and secret — that is the server-restart and
post-expiry path. A host that loses its in-memory secret is refused until its room expires (60 s),
then gets a fresh room and code, which its client takes without a prompt. Secrets rotate only when a
room is replaced, so a lost answer cannot lock a host out early. Host requests also have a per-IP
budget of 240/min (a host asks about once a second; failed renewals count), on top of the existing
20/min join budget. The request stays 48 bytes and the hosted answer grows from 12 to 28 bytes, so
the server still cannot amplify a forged sender and the secret is never sent to joiners.

**Migration.** `protocolVersion` is now 2. A version-1 host request is refused with `failVersion`,
which released 1.0.x clients already display as the "different version of the game" lobby message;
they must update to host again. This deliberately changes released-client behavior: hosting on the
current 1.0.x build needs an update. Version-1 **joins are still accepted**, because a join only
reads a room and is budgeted, so a released client can still join a game and play direct. An updated
client tries version 2 first and, on `failVersion`, drops to version 1 for that lobby, so it keeps
working against the 1.0.x server until the new server is deployed. Neither the client fallback nor
any of this work deploys or contacts the public service.

**Trust model.** The secret is a bearer token: whoever holds it can renew the room. The server trusts
the observed UDP source address as the host's public endpoint and never relays a game packet; peers
still introduce each other in the lobby and connect directly (no-game-packet-relay design preserved).
The secret is only ever sent to the host, in an answer to the address the server observed, and no
other state in a room is authoritative for identity. Client IDs, room codes and endpoints are not
credentials. Once a match starts, the lobby's keepalive keeps echoing the secret so the room cannot
expire mid-match (issue #110).

**Residual risks, stated plainly.**

- A bearer secret raises the bar from "any room member who knows the client ID" to "someone who has
  observed the host's traffic to the server." It does **not** provide cryptographic authentication
  of the host's identity, and it is not a defense against on-path attackers: anyone who captures the
  secret from the host's datagrams can renew the room until the host renews or it expires.
- UDP source addresses can be spoofed. The server trusts the observed source for the public
  endpoint and only checks the secret, so spoofed packets that carry a captured secret can still
  affect the room; rate limiting bounds floods, not a determined on-path attacker.
- The client trusts any packet arriving from the configured server's address. A spoofed
  `failVersion` answer can make an updated client fall back to version 1; that is the same class of
  UDP spoofing risk, not something this change fixes. Falling back does not weaken a version-2 room
  at the server: a version-1 request can never renew it.
- Against a server still running the 1.0.x code, every room — including those of updated clients that
  fell back — is as redirectable as before this change. The fix takes effect only where the new
  server runs; this work performs no deployment.
- The secret is in process memory and in one short UDP datagram; it is not encrypted on the wire and
  no transport confidentiality is claimed. The room code remains a meet-up hint, not a credential.
- The secret is 128 bits and guesses are infeasible in principle; the per-IP budget only bounds
  strictly local floods, and a distributed flood is limited instead by room creation and the same
  secret entropy. No claim of DoS prevention is made.

**Verification scope.** Go unit tests and the C++ `net_lobby_test` cover, entirely in-process or on
loopback: unauthorized renewal rejected with no state or last-seen change, legitimate renewal from a
changed address, host restart, server restart, expiry, host and join rate limits, version-1 join
accepted and host refused, secret echo and wire layout, and the anti-amplification invariant. They
do not exercise real routers, real NAT, the deployed service, or an on-path attacker.

### 8. Real play (owner's manual check, not an agent work order)

Linux with Windows on real networks: 2 players, then 4, over LAN and internet. Check the feel at the
default delay, wrong sounds after rollbacks, a dropped player, and whether punching works on real
routers. Then close #3, and decide whether a relay is needed from how many connections failed.

## Later: the v2 lobby

The owner's idea of 2026-10-31, not part of this plan's steps. Nothing below is built, and the room and
ready flow of step 6 already leads into it.

- **Room list on entering online:** public rooms as `Room <ID> <Current / Max> <Host ping>`, with helper buttons
  for Create Room, Join Room (a room number or direct IP, and the only way into a private room) and Matchmaking
  (joins any room with a free slot, or creates one).
- **Room settings:** public or private, online or LAN.
- **Inside a room:** names on the left, chat on the right, and a large Ready button at the bottom. Once all are
  ready, Character Select follows, as now.
- **Chat:** T starts typing, Enter sends, Esc cancels, in English and Japanese.

What it needs that does not exist yet:

- The rendezvous server has to keep public rooms and answer a list, in several packets, since a list outgrows the
  48-byte request that keeps it from amplifying. Matchmaking is a server query on top of that.
- A host's ping in the list means reaching a host the player has not joined, so each listed host would have to be
  told to open its router. A ping to the server is the cheap stand-in.
- LAN rooms need discovery by broadcast on the local network, with no server.
- Chat cannot use the lobby's resend-the-whole-state rule, so it needs numbered messages. Names are plain ASCII
  today, and chat needs UTF-8 with validation, SDL text input for the Japanese IME, and a line of history.

## Stop and ask

- Cross-build hashes differ past the attempt ceiling (step 5).
- GekkoNet does not build with MinGW, or its stress session shows a problem in the library (step 3).
- Keeping the state hash coherent needs broad edits to the core.
- Original-runtime parity stays `not verified`. A game that stays in sync online proves agreement
  between peers, not agreement with the original.

---

## Proposal (NOT a work order): Online v2 phasing for issue #92 — owner decision requested, 2026-11-19

> **Marker.** Everything above this line is the implementation record and the owner's 2026-10-31
> idea; it is unchanged by this section. Everything below is a **proposal**, written on 2026-11-19
> at the owner's request to scope [issue #92](https://github.com/Vmarcelo49/daybreak-remake/issues/92)
> so the owner can decide phasing. It is **not** a work order, not an amendment to steps 1–8, and
> not authorization to write code. No decision is taken here: the three owner questions get a
> **recommendation and rationale each**, and the owner decides. Lead reviews before any commit.

### P0. Precedence and what this document is

Step 8 — the owner's manual real-network playtest (Linux with Windows, 2 then 4 players, LAN and
internet, feel/rollbacks/drop/punching) — **stays the priority**. v2 is a *later phase*: this
section proposes only how to slice issue #92 when the owner decides to start it; it does not move
step 8, close an issue, deploy a server, or change `docs/decisions.md` (no D-numbers added) or
`AGENTS.md`. Nothing here contacts the deployed rendezvous server; every test described is
in-process or on a loopback socket, with a locally launched server whose address is overridden to
`127.0.0.1`. The default `kDefaultServer` in `src/settings/user_settings.h` is the deployed service
and is never used by a v2 test.

**Why appended here, not a new `ONLINE-V2-PLAN.md`.** Issue #92 and the "Later: the v2 lobby"
section already live in this file, and the issue names that section as its source. Appending one
clearly marked proposal keeps the lineage in one document and makes it impossible to read the
proposal as a new work order or as a rewrite of the record. A separate file would duplicate
"Later: the v2 lobby" and invite two documents drifting apart. If the owner later promotes this to
a binding plan, split it into its own file *then*, as an explicit act.

### P1. Grounding: what exists today (all from the record and the current tree)

- The room/ready flow of step 6 is the entry point: `OnlineMenuScreen` and `OnlineLobbyScreen`
  in `src/frontend/screen_online.cpp` build the panels with `PanelScreen`/`say()`; the host picks
  seed/token and the selection screen decides the match. The lobby holds names, ping, ready signs,
  a Ready button and Leave, and starts selection by itself once all are ready.
- `net::Lobby` (`src/net/lobby.{h,cpp}`) resends whole state on one UDP socket (`net::UdpSocket`),
  tags packets by first byte (`kLobbyPacket`, `kGamePacket`, `kOutcomePacket`, `kServerPacket`),
  and talks to the rendezvous server with a fixed **48-byte** request. A name is encoded with
  `put_name`/`Reader::name` as **12 bytes, plain ASCII only** (`0x20..0x7e`); this matters for chat.
- The server (`server/{main,rooms,protocol}.go`) knows only a code, the host's public/private
  endpoints, and (since #126) a 128-bit renewal secret in the host request's padding. It keeps no
  room metadata, lists, or match state. `protocolVersion = 2`, `legacyVersion = 1`: v1 **hosts**
  get `failVersion`, v1 **joins** are still accepted; `net_lobby_test.cpp` and `server_test.go`
  pin the secret echo, the fallback, and the `len(answer) <= requestSize` anti-amplification
  invariant.
- Text input already reaches the C++ side as UTF-8: `appEvent` appends `event->text.text` to
  `TextKeys::typed` (`src/app/frame_loop.inc`), and `syncTextEntry` calls `SDL_StartTextInput` /
  `SDL_StopTextInput` from `Screen::wantsText()`. `TextEdit::apply` (`src/frontend/text_edit.h`)
  then filters each byte through an ASCII `allowed` set and `toupper`, which is why names and
  fields are ASCII today. The transport carries UTF-8; the editor discards it.
- Direct-IP join already works (`beginOnlineJoin` → `Lobby::join`), and room-code join works
  (`beginOnlineCode` → `Lobby::join_code`). Both are unaffected by anything proposed here.

### P2. The owner's three questions — recommendations (owner decides)

**Q1 — Which pieces come first: server-dependent public rooms/matchmaking, or server-independent
LAN rooms?**
*Recommendation:* **LAN rooms + the room-list/room-settings UI shell first; public rooms +
matchmaking second; chat last (see Q2).** Rationale: the room-list screen, the Create/Join buttons
and the public/private + online/LAN settings are a *shared prerequisite* for both paths. Building
them against a server-independent backend lets the owner judge the layout early — exactly as step 6
left the layout to the owner's judgment — and yields an independently useful LAN-party feature
(D6 explicitly keeps LAN netplay in scope). It also avoids gating the first v2 slice on rendezvous
protocol decisions. Public rooms then drop into the same UI and are testable against a **local**
server on loopback; production use still needs a separate, owner-controlled server deployment,
which this plan does not do. *Tradeoff, stated for the owner:* if the headline internet room list
is the priority, reversing slices 1 and 2 is defensible — public rooms are also loopback-testable
and do not wait on a real deployment for development. This is a recommendation, not a decision.

**Q2 — Chat in the first v2 release, or after the room list?**
*Recommendation:* **after the room list.** Rationale: chat is self-contained — it rides the
existing per-room UDP socket, not the server — but it is the highest-risk surface: a new numbered
message protocol, strict UTF-8 validation on untrusted bytes, SDL IME text entry whose candidate
window behaviour needs a human at a real keyboard, and a one-line history. Keeping it in its own
slice protects the working room/ready/select flow and keeps the first release small while step 8
real-play remains the priority. It also lets the owner sign off the v2 room-screen layout (names
left, chat right, big Ready) in slice 1/2 before chat is drawn into it. *Alternative:* shipping chat
with the first release is possible but couples four independent risks to the room-list rollout; if
the owner chooses that, chat becomes part of slice 3 moving earlier, with the same acceptance
criteria.

**Q3 — Host ping in the list, or the cheap server-ping stand-in?**
*Recommendation:* **server ping, labelled honestly as "server ping" (RTT to the rendezvous
server), for the first v2 release; do not add the router-opening step.** Rationale: a true host
ping means contacting a host you have not joined and asking it to open its router for a stranger —
a new unsolicited-inbound path with NAT-traversal and abuse/privacy implications, and it duplicates
the full-mesh probing step 7 already performs *after* joining. The server RTT is cheap (the list
request/answer can carry a timestamp echo) and is a reasonable quality proxy. Label it as server
ping in the UI so no player reads it as a measured host RTT. Revisit only if step 8 shows players
actually need host-side latency. This does not weaken the in-room ping already shown in the lobby
(`MatchPlan::pingMs`); it only changes what the *pre-join list* displays.

### P3. Proposed slices

Each slice is independently useful and can be reviewed/committed on its own. Scope estimates are
orders of magnitude for the owner's phasing judgment, not commitments. "Synthetic" means
device-free C++/Go unit tests or a loopback socket with a locally launched peer/server — **never**
the deployed service.

#### Slice 1 — Room-list shell, room settings, and LAN rooms (server-independent)

- **Delivers:** a room-list screen on entering online, with helper buttons Create Room, Join Room
  (room number **or** direct IP) and Matchmaking (UI present; Matchmaking is inert until slice 2,
  with a clear "needs server" hint). Room settings: public/private and online/LAN. For online/LAN,
  "LAN" hosts a room **without** announcing to a server; for online/public, hosting announces as
  today. LAN rooms are discovered by broadcast (design in P4.D) and populate the same list.
  Direct-IP join remains the fallback and the only way into a private room. The existing lobby
  screen is reused unchanged behind the list.
- **Independently useful:** LAN parties get discoverable rooms with no IP typing and explicit
  privacy/scope settings; the room-list UI exists and can be owner-reviewed before any server work.
- **Dependencies:** none on slice 2/3. Reuses `OnlineMenuScreen`/`OnlineLobbyScreen`, `PanelScreen`,
  `Lobby::host/join`, and the `[network]` settings. Introduces a discovery backend seam (injectable
  so tests never need a real broadcast interface).
- **Estimated scope:** client small–medium (one new `RoomListScreen`, a settings row pair, a
  discovery module); UI medium (needs `frontend-design`, see P5); server **none**; tests small
  (device-free discovery/dedupe/expiry tests, menu-flow script on loopback).
- **Acceptance criteria:** (a) entering online shows a list; a synthetic LAN announce appears,
  dedupes by host/client ID, and expires after a timeout; (b) clicking a discovered room performs
  the same `beginOnlineJoin("IP:PORT")` path as manual direct-IP; (c) private rooms are never
  announced; (d) "LAN" hosting makes zero server requests; (e) an owner-visible layout review gate,
  as in step 6. Synthetic: all of the above with an injected discovery source and loopback — no
  router, no deployed server. Real LAN broadcast stays a manual check.

#### Slice 2 — Public rooms and matchmaking on the rendezvous server

- **Delivers:** the server keeps a *listed* flag per room, answers a paged room list, and answers a
  matchmaking query; the client requests pages, assembles the list, and the helper buttons become
  live. The list shows `Room <ID> <Current/Max> <server ping>` with the honest server-ping label
  (Q3). Matchmaking picks a listed, non-full, non-started room and joins by code via the existing
  flow, or hosts a new public room if none is suitable.
- **Independently useful:** internet room browsing and one-click matchmaking — the headline of
  #92 — with no change to how a match is played.
- **Dependencies:** slice 1's room-list UI and settings (or a minimal equivalent carried in this
  slice). Server work must preserve every #126 property (P4.A) and the 48B invariant (P4.B).
- **Estimated scope:** server medium (room metadata, list/match request kinds, paging and rate
  budgets); client medium (list request/assembly, matchmaking action); UI small (fills slice 1's
  rows); tests medium (Go list/match tests including anti-amplification, C++ list-assembly tests,
  an end-to-end loopback run with a locally launched server).
- **Acceptance criteria:** (a) a list outgrows 48B and arrives as several ≤48B answer packets, each
  tied to its own 48B request — the existing `len(answer) <= requestSize` test still passes and is
  extended to list/match answers; (b) the client assembles pages by (generation, page index),
  discards a list whose generation changed mid-assembly, and re-requests lost pages; (c) private
  and non-accepting rooms are omitted; (d) matchmaking joins a suitable room by the existing
  code flow, or hosts when none exists; (e) #126's renewal-secret and v1-join tests pass unchanged;
  (f) a full loopback run (local server bound to `127.0.0.1`) shows a room created in one client in
  another client's list. No traffic to `kDefaultServer`.

#### Slice 3 — Room screen and chat (server-independent transport)

- **Delivers:** the v2 room screen (names left, chat right, large Ready button at bottom; selection
  still follows automatically when everyone is ready) and chat: `T` starts typing, `Enter` sends,
  `Esc` cancels, English and Japanese, one line of history.
- **Independently useful:** better in-room UX and text chat in **any** room (LAN or online),
  with no server dependency for chat itself.
- **Dependencies:** none on slice 2 for transport (chat is peer-to-peer over the lobby socket);
  the room-screen layout ideally follows the owner's sign-off from slices 1/2.
- **Estimated scope:** client medium (numbered chat channel + strict UTF-8 validator + history);
  UI medium–large (new room screen; needs `frontend-design`); server **none**; tests medium
  (UTF-8 validator fuzz cases, numbered-message ordering/dedupe, IME-facing text-edit tests, a
  two-instance loopback chat run).
- **Acceptance criteria:** (a) messages are numbered, deduped and ordered per sender, with bounded
  resend/ACK; (b) invalid UTF-8 is dropped before it reaches the renderer and cannot crash or
  garble the screen; (c) Japanese text typed through an SDL text-input event survives into a sent
  message end-to-end on loopback; (d) `T`/`Enter`/`Esc` behave as specified and Up recalls the one
  history line; (e) names remain the existing ASCII (no protocol change to names in this slice).
  A real IME/candidate-window check remains a manual gate (P5).

### P4. Cross-cutting protocol design (must hold in every slice)

#### A. Preserve #126's authenticated renewal (non-negotiable)

The 128-bit server-issued renewal secret stays in the 16 unused padding bytes (offset 21) of every
**host** request; renewal keeps constant-time comparison, `failUnauthorized` with **no state or
last-seen change**, secret rotation only when a room is replaced, per-IP host budget (240/min), and
the v1-join fallback (v1 joins accepted, v1 hosts refused). The list/matchmaking work is **additive
request kinds**, not a change to those paths: existing clients never send them, and the renewal
secret is **never** put in a list, joiner, or matchmaking answer. "Public/listed" is a new flag on
the host request (in the still-spare padding *after* the secret, offsets 37–47), not a reuse of the
secret. A "no longer accepting players" bit on the renewal lets the server omit started/full rooms
from the list without the server learning match state. If a clean version bump is preferred, keep
accepting v2 hosts and v1/v2 joins — do **not** regress the #126 migration. Re-run
`rendezvous_server_test`/`server_test.go` and `net_lobby_test` unchanged as the first gate on any
server edit.

#### B. 48-byte request / anti-amplification and the multi-packet list framing

The invariant in `server/protocol.go` is: **a response to an unvalidated source is never larger
than its 48-byte request**, so a forged sender gains nothing. A list is larger than 48B, so it
cannot be one answer. Two framings were considered; recommendation is the first.

- **Recommended — client-paged requests (stateless, no new secret).** Keep the request exactly 48B
  with a new kind `kindList`. Reuse the 4-byte code field (offset 17) as `generation:2 + page:2`;
  the rest of the layout, including `clientID` and the private endpoint, is unchanged. Page 0 is
  answered with `answerList`: prefix, kind, generation, page index, page count, entry count, then N
  entries, where each entry is ≤8B (4B code, packed current/max, a ping field, a flags byte). With
  an 8B header and ≤8B entries, one answer stays **≤48B**. The client sends page 0, reads page
  count/generation, then sends one request per remaining page; a generation that changed between
  pages yields a small "stale" error and the client restarts from page 0. Lost pages are recovered
  by re-sending that page's 48B request after a timeout (no server-side state, no ACK scheme).
  Because **every** answer is ≤48B and is produced by exactly one 48B request, total answer bytes
  never exceed total request bytes — the existing anti-amplification test extends directly to
  list answers. Matchmaking is a separate small `kindMatch` answer (one room code, ≤48B, like
  `answerRoom`), so it needs no paging. Cap listed rooms (e.g. 32) and pages (e.g. 8); sort by fill
  then ping for stable ordering; give list/match their own per-IP budgets alongside join/host.
- **Alternative if fewer client datagrams matter more — stateless cookie.** A first 48B list
  request gets a small cookie answer (≤48B); the client echoes the cookie in a second 48B request,
  proving it can receive at that source, and the server then bursts the full list. A forged sender
  cannot receive the cookie, so it gets at most 48B. This adds a server MAC secret and a round trip,
  and requires a careful argument that the *validated* burst is not amplification; it is safer to
  avoid unless paging proves too chatty. Either way, the 48B request size is never changed.
- **Server ping source:** put a client timestamp in the list request and echo it in `answerList`,
  giving an RTT sample per page without a separate protocol. Display as "server ping" (Q3).

#### C. Chat transport, UTF-8, SDL IME, one-line history

- **Transport:** a new packet tag (e.g. `kChatPacket = 'C'`) on the existing room UDP socket —
  peer-to-peer, no server. Each message is `{sender clientId, monotonic per-sender sequence, byte
  length, UTF-8 bytes}`. Unlike lobby state, chat is **not** "resend the whole state": the sender
  resends only unacknowledged messages, and receivers ACK a highest-contiguous sequence plus a
  small bitmap, with a bounded window (e.g. last 32 messages). Deduplicate by (sender, sequence);
  order per sender by sequence, interleave senders by arrival. Cap message bytes (e.g. 512) and a
  per-tick byte budget.
- **UTF-8 validation:** validate every received message with a strict decoder before it reaches the
  renderer — reject overlong encodings, surrogates, values above U+10FFFF and truncated sequences;
  drop invalid messages (log once, never display). This is a robustness/UI-safety measure, not a
  confidentiality claim. **Names stay plain ASCII** (`Reader::name`, 12 bytes) in this slice; widening
  names to UTF-8 is a separate protocol/version change, not smuggled into chat.
- **SDL text input / IME:** the event path already carries UTF-8 (`event->text.text` →
  `TextKeys::typed`) and toggles `SDL_StartTextInput` via `wantsText()`. Add a chat-specific editor
  that consumes **code points, not bytes** (the current `TextEdit::apply` filters bytes through an
  ASCII `allowed` set and would drop Japanese). Keep `wantsText()` true while composing, pass
  `SDL_TEXTEDITING` composition through to a pre-edit display, and call `SDL_SetTextInputArea` near
  the chat box so IME candidate windows appear in the right place. `T` activates, `Enter` sends,
  `Esc` cancels. A real IME needs a human check; synthetic tests feed UTF-8 through `--text-keys` /
  injected `TextKeys`.
- **One line of history:** keep the last sent line and recall it with Up. Interpretation flagged
  for the owner: "a line of history" is read as *recall the previous sent line*, not a scrollback
  buffer; confirm before implementing.

#### D. LAN discovery and its interaction with direct-IP join

Broadcast a small, fixed-format LAN announce on a dedicated UDP port (e.g. derived from the game
port) containing a magic/version, host name, room code, current/max, and a LAN host endpoint. Hosts
in LAN mode emit it at a bounded rate (e.g. 1/s); the client listens, ignores its own announce,
dedupes by host/client ID, and drops entries not refreshed within a few seconds. Announces are
**discovery only**: clicking a LAN room calls the existing `beginOnlineJoin("IP:PORT")` with the
advertised endpoint, so no join/transport code changes and direct-IP join remains the manual
fallback and the only route into a private room. Private rooms are never announced. Real broadcast
cannot be tested on loopback, so inject a discovery backend: unit tests supply synthetic announces
and assert parse/dedupe/expiry/list population device-free; real LAN broadcast is a manual check.
No server and no deployed service are involved in LAN mode.

### P5. Skills, gates, and synthetic testability

- **frontend-design skill:** load it before implementing the UI in **slices 1, 2 (list rows/buttons)
  and 3 (room screen)** — the team uses it for distinctive UI. This proposal does not load or use
  it; it only flags the need.
- **Unrelated standing gates:** a **real-Mac tester** and a **real-Windows run** remain separate
  gates (macOS is not built; Windows cross-build/real-machine determinism is step 5). Neither is a
  v2 acceptance item and neither is touched by this plan.
- **Synthetic/loopback everywhere:** Go unit tests for server list/match and anti-amplification;
  C++ device-free tests for list assembly, chat ordering/UTF-8 and discovery dedupe/expiry;
  `netctl`/`online_flow_check`-style runs with a **local** server bound to `127.0.0.1`. Real routers,
  real NAT, a real IME and real LAN broadcast are manual checks, owned by step 8/the owner, not by
  an agent against the deployed service.

### P6. Residual risks and what this plan does NOT claim

- The paged list keeps the 48B invariant but is eventually consistent: entries can change between
  pages; the generation scheme detects this rather than preventing it. Chattiness of many small
  page requests is bounded by caps and per-IP budgets, not eliminated. Matchmaking is first-fit,
  not balanced, and reveals only listed rooms.
- UDP spoofing remains: a captured renewal secret still enables renewal against #126's known
  limitations, and list/match answers are unauthenticated hints. This plan neither fixes nor worsens
  those risks; the cookie alternative in P4.B is the only new trust surface and is optional.
- Chat adds untrusted UTF-8 to the render path; validation is necessary but IME/candidate behaviour
  varies by OS and IME and needs human verification. Symmetric NAT and a relay remain out of scope.
- Production public rooms/matchmaking require the owner to deploy an updated rendezvous server;
  this plan does not deploy one and this work sends nothing to the deployed service.
- **No gameplay or original-runtime verification is claimed.** "Built" is not "verified"; a capture
  is not a live run (D9); a skip is not a pass. Staying in sync online proves peer agreement, not
  agreement with the original (whose netplay this port does not speak). All evidence tiers for any
  future v2 work will be stated at the time; none is asserted by this document.

