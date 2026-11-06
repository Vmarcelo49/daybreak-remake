**The first update the game installs for itself.** Open 1.0.0 and it offers you this one:
choose **Update** and it replaces itself. Everything here came out of the first real online
session — two people playing over room codes: battles between two different computers stay in
step, the other player is named as a player instead of COM, the room code survives a match,
Hanyuu's time stop no longer crashes the game, and Takano's transmitter draws its reticle.

**Everyone in a room must be on 1.0.1.** The combat arithmetic changed so that any two
machines compute the same battle, so a 1.0.1 player and a 1.0.0 player will drift apart.

You need your own copy of Higurashi Daybreak. This download contains none of the game's files.

## Install

1. The game offers this update when it starts: choose **Update**. Or download the file for
   your system below.
2. Extract it into your game folder, the one with `daybreak00.dat`, replacing the previous version.
3. Open `DaybreakRemake.exe` on Windows, or `daybreak` on Linux. If your file manager shows `daybreak` as text, open `daybreak-bin`.

Linux needs glibc 2.38 or newer, such as Ubuntu 24.04, and a Vulkan driver. Your original game is not changed.

## What's fixed since 1.0.0

### Online

- **Both machines now fight the same battle.** On different computers, the game could round
  the last bit of a number differently depending on the processor inside, so the two battles
  drifted apart — from the same inputs, the two games disagreed about who a fighter was aiming
  at. Both sides now compute identical numbers, and the two-machine match that used to drift
  apart stayed in step from start to finish.
- **Everyone is named as who they are.** The other machine's fighter was labelled **COM** on
  your screen: on the VS captions, the in-battle HUD and the results badge. Players are now
  named as players, on every machine.
- **The room code survives the match.** The room server forgets a room a minute after it last
  hears from the host, and the host went quiet during a match — so a match longer than a minute
  came back to a new room and a new code, and the old code stopped working. The host now checks
  in while the match runs. While fixing it: a host in a lobby was asking the server about 60
  times a second; it now asks once a second.
- **The match starts when VS starts.** After the VS animation the fighters used to hang in the
  air while the two machines shook hands. Online, the match is now built as the VS screen
  appears, so the wait overlaps the animation.
- **Both players leave the results together.** The result screen used to advance on each
  machine's own controller, so whoever pressed first went back to the lobby while the other sat
  on the report. Any player's press now advances both.

### In battle

- **Hanyuu's time stop no longer crashes the game.** The effect draws an inverted view, and
  the renderer lost track of how many it had drawn, so a fraction of a second in it gave up and
  the game closed. It now runs for its full duration, in one view or split screen.
- **Takano's support transmitter draws its reticle.** The beacon showed a large yellow flash
  stuck on the fighter it hit instead of the green and red target reticle the model is meant to
  show. The projectile's own texture changes are now applied.

## What to expect

- Online is still in testing. It has now been played between two real PCs, and the reports from
  that session are what this release fixes.
- Some routers can't make direct connections. The lobby tells you who can't reach whom, and
  there's no relay yet.
- If a player drops, everyone freezes for about 5 seconds before a computer player takes over.
- The pause key leaves an online match at once, with no confirmation.
- Any player can send everyone back to the lobby from character select.
- Story dialogue is still in Japanese.
- Combat is a reconstruction, so some moves or timing may differ from the original.
- The browser version is experimental and not tested for release.

## Report a problem

[Open a test report](https://github.com/Vmarcelo49/daybreak-remake/issues/new?template=test-report.md) and attach `daybreak.log`, plus `daybreak-previous.log` after a crash:

- Windows: `%APPDATA%\daybreak-decomp\`
- Linux: `~/.config/daybreak-decomp/`

## SHA-256

```
233b1106fd1ff6948945e94acaf573824b0608e5570034781925a6f45fb47bef  daybreak-1.0.1-linux-x86_64.tar.gz
0e776b63bc74b7d3a75db75c37213591000888d3812819950350cd87af05feba  daybreak-1.0.1-33815c8f-windows-x86_64.zip
```
