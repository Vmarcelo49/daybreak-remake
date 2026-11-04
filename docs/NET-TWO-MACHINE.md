# Two machines, one online match

Issue #106 was reported from the first session against another person. Everything since has been
checked on one machine: `netctl` pairs on loopback, and unit tests. This is the plan and the
tooling for the real thing — two machines on one network — so the next session is a scripted
sequence instead of an ad-hoc run.

Nothing here is evidence about the original, which has no netplay to compare with. It is our own
build against itself, so the strongest tier it can reach is 5, and the one claim only a person
can settle (what the screens show) is separated out below.

## What the two machines need

| | this machine (Arch, holds the checkout) | the other machine (Kubuntu) |
|---|---|---|
| Build tools | yes | **no** — nothing is built there |
| This checkout | yes | **no** — nothing is checked out there |
| The game files | `Higurashi-Daybreak/` beside the checkout | copied, in `~/daybreak-net/data` |
| The game binary | `build/linux/daybreak` | only for the interactive step, and it may not run |
| `netctl` and its libraries | `build/linux/netctl` | copied to `~/daybreak-net/{bin,lib}` |

The binaries are the one real risk: Arch and Kubuntu are different glibc and different shared
libraries, so a binary built here can fail to start there. `netctl` needs two libraries that are
not part of a base system, and both go along with it by the SONAME its own `ldd` resolves:
`libwgpu_native.so` (fetched, never installed anywhere) and `libSDL3.so.0` (SDL3 may be absent).
`prepare` copies them and the binary into `~/daybreak-net/{bin,lib}` and runs each peer under
`LD_LIBRARY_PATH=~/daybreak-net/lib`, not a patched rpath, so no binary it ships is modified.
It then runs `netctl --help` there, and if that fails prints the remote `ldd` that says which
library is missing. The glibc and libstdc++ runtime deliberately stay the other machine's own.

Nothing needs to be installed on the other machine, and nothing is built there.

## This machine cannot host the room

Measured on this machine: its nftables rules **drop inbound UDP**, so a peer here never hears a
peer on the other machine, even though `ssh` from here works and every outbound flow does. The
rules need root, which a session does not have, so the room is **hosted on the other machine** and
this machine joins: the reply to an outbound flow passes conntrack. `robustness --host remote` is
that arrangement, and it is what a real run uses; `--host local` is kept for a machine whose
firewall allows it.

## The four steps

All of it is one script, `tests/net-two-machine/netsuite.py`. Run it from this machine.

```bash
# 1. Copy netctl and the two libraries it needs, and prove it starts there.
tests/net-two-machine/netsuite.py prepare --remote USER@HOST

# 2. Rehearse here first: every peer on this machine, so a script bug is not blamed on the network.
tests/net-two-machine/netsuite.py robustness --remote USER@HOST --host remote --rehearse --ticks 3600

# 3. Two machines, one headless room. This is the real run.
tests/net-two-machine/netsuite.py robustness --remote USER@HOST --host remote --ticks 3600

# 4. The interactive run, for what only a person can see.
tests/net-two-machine/netsuite.py interactive --remote USER@HOST --host remote
```

Step 2 needs no second machine at all; it is worth running before the real one so a failure in
step 3 means the network or the code, not the harness.

## What step 3 checks, and what a failure means

`netctl` is a headless online peer: real sockets, the real battle, no window and no GPU, so this
runs on the Kubuntu machine over ssh without a session. Each peer prints one JSON line, and the
suite asserts five things per network profile:

| Check | A failure means |
|---|---|
| every peer reported | one machine never reached the other: firewall, different network, or a peer crashed. `ssh` working says nothing about UDP — allow `udp/<port>` on the host (or host on the other machine, as above) |
| no desyncs | the two machines' battles diverged — the hard bug this is for (#107) |
| one round, one end frame | the round resolved differently on the two machines |
| every seat a peer plays is `H` on every machine | a seat one machine plays is being run by the CPU on the other: the slot mapping or the input routing is wrong, and #106's premise would be wrong with it |
| the logs agree frame by frame | the state hashes disagree at a named frame, with the log kept under `build/net-two-machine/` |

Both profiles always run, but only one of them crosses the network:

- **ideal network** — one side on each machine. This is the profile that measures two machines.
- **10 % loss, 80 ms delay, 5 ms jitter** — the whole room on this machine, through
  `tools/net_proxy.py`. A peer told `--proxy` sends every packet to the proxy and trusts the
  6-byte prefix it comes back with, so every peer of a room must share one proxy, and
  `net_proxy.py` binds to loopback; measured, a proxied joiner never reaches a direct host. The
  profile therefore stays a one-machine rehearsal: it exercises rollback under loss and delay,
  which is what it is for, and it says nothing about the network between the two machines.

## The checks only a person can make

The headless suite cannot see a label. **This is the check for #106 itself**, and it needs
someone at each screen, or at least a capture from each.

1. Both machines open the game and reach the online menu; the other machine hosts (this one's
   firewall drops inbound UDP), and this one joins with the room code or `ip:37564`.
2. **On the character select**, each player takes a different panel. The stage page waits until
   every machine's player has a panel of their own — if it opens early, a seat was left on the
   COM sentinel and every number after it shifts.
3. **On the VS screen**, the caption under each portrait names that player's own controller
   (`Rena 1  1P`, `Keiichi 1  2P`), never `COM` for a human. Both machines should read the same
   names for the same fighters.
4. **In the battle**, the overhead tag over the other player reads a controller, not `COM`. This
   holds from the first second — the fix's own regression was `COM` for the first moment of a
   match.
5. **On the results screen**, each row's badge is that player's controller. This is the row the
   first attempt got wrong.
6. Then have **one player drop** (close the game on the other machine, or pull its network).
   That player's tag and badge must switch to `COM` once the CPU takes the fighter over, and the
   remaining player's must stay theirs.

Record each step's screen for the issue: `PRINT SCREEN` on both machines, or
`grim -o DP-1 shot.png` on Wayland.

`interactive` prints the command line for each side and writes nothing: the game creates its own
`settings.conf` on first run, and each side runs with `XDG_CONFIG_HOME` pointed at a folder of its
own, so nobody's real settings are touched.

## Troubleshooting

| Symptom | Cause |
|---|---|
| a peer never answers, `ssh` is fine | UDP is not reaching the host. This machine's own firewall drops inbound, so host on the other machine: `--host remote` |
| `prepare` copies but netctl will not start there | a missing library; `prepare` prints the remote `ldd`, and the two that go along are `libwgpu_native.so` and `libSDL3.so.0` |
| both peers report but the round never ends | the ticks ran out before the round did; raise `--ticks` or set `--time-limit` |
| desyncs on both machines but none on loopback | a real cross-machine divergence: keep the logs and treat it as #107. Rerun with `--rehearse` to confirm the harness is not the cause, then read the first disagreeing frame |
| `interactive` says there is no packaged tree | staging one needs a build tree configured as a release, which the development one is not; run the game on each machine from a build of this checkout instead |

## Limits

- `netctl` asks no one to play: its inputs come from a repeatable script, so it covers rollback,
  round resolution and seat ownership, never a human's timing.
- The interactive run is a `--net-host`/`--net-join` launch; the room-code path needs the
  rendezvous server and is closer to how the playtest happened. Both should be run; only the
  latter was reported broken.
- The loss-and-delay profile is a single machine. Only the ideal profile measures the network
  between the two machines.
- Every result here is our build against our build. Nothing in it is evidence about the original.
