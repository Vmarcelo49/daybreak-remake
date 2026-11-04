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
| The game files | `Higurashi-Daybreak/` beside the checkout | copied, in a folder of their own |
| The game binary | `build/linux/daybreak` | copied from this machine, and it may not run |
| `netctl` | `build/linux/netctl` | copied, or rebuilt there |

The binaries are the one real risk: Arch and Kubuntu are different glibc and different shared
libraries, so a binary built here can fail to start there. `prepare` checks that, and says which
half failed. If `netctl` does not run there, one line builds it there instead:

```
ssh USER@HOST 'sudo apt install -y build-essential cmake ninja-build libsdl3-dev'
```

and then the checkout is needed there after all — at which point `./build.sh deps && ./build.sh
linux --target netctl` on that machine is the shortest path. Nothing else in this plan needs a
build there.

## The four steps

All of it is one script, `tests/net-two-machine/netsuite.py`. Run it from this machine.

```bash
# 1. Copy what the other machine needs, and prove both binaries start there.
tests/net-two-machine/netsuite.py prepare --remote USER@HOST

# 2. Rehearse here first: both sides on this machine, so a script bug is not blamed on the network.
tests/net-two-machine/netsuite.py robustness --remote USER@HOST --same-host --ticks 3600

# 3. Two machines, one headless room, ideal and bad network. This is the real run.
tests/net-two-machine/netsuite.py robustness --remote USER@HOST --ticks 3600

# 4. The interactive run, for what only a person can see.
tests/net-two-machine/netsuite.py interactive --remote USER@HOST --host local
```

Step 2 needs no second machine at all and is how the script was first exercised here; it is worth
running before the real one so a failure in step 3 means the network, not the harness.

## What step 3 checks, and what a failure means

`netctl` is a headless online peer: real sockets, the real battle, no window and no GPU, so this
runs on the Kubuntu machine over ssh without a session. Each peer prints one JSON line, and the
suite asserts five things per network profile:

| Check | A failure means |
|---|---|
| every peer reported | one machine never reached the other: firewall, different network, or a peer crashed. `ssh` working says nothing about UDP — allow `udp/37564` (or the port it prints) |
| no desyncs | the two machines' battles diverged — the hard bug this is for (#107) |
| one round, one end frame | the round resolved differently on the two machines |
| every seat a peer plays is `H` on every machine | a seat one machine plays is being run by the CPU on the other: the slot mapping or the input routing is wrong, and #106's premise would be wrong with it |
| the logs agree frame by frame | the state hashes disagree at a named frame, with the log kept under `build/net-two-machine/` |

Two network profiles run: ideal, and 10 % loss with 80 ms delay and jitter through
`tools/net_proxy.py`, which also covers the rollback path under conditions a LAN rarely produces.

## The checks only a person can make

The headless suite cannot see a label. **This is the check for #106 itself**, and it needs
someone at each screen, or at least a capture from each.

1. Both machines open the game and reach the online menu; this machine hosts, the other joins
   the room code or `ip:37564`.
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

## Troubleshooting

| Symptom | Cause |
|---|---|
| a peer never answers, `ssh` is fine | UDP is not reaching the host: `sudo ufw allow 37564/udp` on the host, and check both machines are on the same subnet |
| `prepare` copies but a binary will not start there | different libc or a missing library; build that binary on the other machine (`docs/BUILD-linux.md`) |
| both peers report but the round never ends | the ticks ran out before the round did; raise `--ticks` or set `--time-limit` |
| desyncs on both machines but none on loopback | the network, not the code: rerun on the ideal profile to confirm, then with the proxy to measure it |

## Limits

- `netctl` asks no one to play: its inputs come from a repeatable script, so it covers
  rollback, round resolution and seat ownership, never a human's timing.
- The interactive run is a `--net-host`/`--net-join` launch; the room-code path needs the
  rendezvous server and is closer to how the playtest happened. Both should be run; only the
  latter was reported broken.
- Every result here is our build against our build. Nothing in it is evidence about the
  original.
