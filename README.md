# Higurashi Daybreak — Fan Remake

> **Developer?** Building, tests and how the code is organized are in [DEVELOPMENT.md](DEVELOPMENT.md).

A free fan remake of **Higurashi Daybreak**, the 3D arena fighter by Twilight Frontier and 07th Expansion. It runs on
modern computers and adds online play with rollback.

**You need your own copy of the original game.** This project includes none of its characters, art, music or story, and
it does not change your original files.

![Higurashi Daybreak remake screenshot](https://github.com/user-attachments/assets/64fe73d2-a2a7-4e61-aae6-7d9167c0c874)

## How to play

1. Download the package for your system from the [Releases page](https://github.com/Vmarcelo49/daybreak-remake/releases).
2. Extract it into your Higurashi Daybreak folder, the one with `daybreak00.dat`.
3. Open it:
   - **Windows:** `DaybreakRemake.exe`
   - **Linux:** `daybreak`. If your file manager shows it as text, open `daybreak-bin` instead.

Your original game keeps working as before.

## What's new compared to the original

| Feature | What it means |
|---|---|
| **Online with rollback** | 2 to 4 players, with less input delay than waiting on the slowest connection. |
| **Room codes** | Friends can join with a 4-letter code, usually without touching router settings. Joining by IP also works. |
| **Windows and Linux** | Runs natively on Linux, and players on both systems can play each other. |
| **English menus and HUD** | Switch between English and Japanese in Options. |
| **Modern displays** | Higher resolutions, widescreen and sharper menu text. |
| **Texture packs** | Optional high-resolution textures: put them in a folder beside the game. No pack is available yet. |

If someone leaves an online match, a computer player takes over and the match goes on.

## What works and what doesn't

| Area | State |
|---|---|
| Versus against people on one PC or the computer | Works |
| Story mode | Works, with the dialogue still in Japanese |
| Online | **New and in testing.** Expect problems, and please tell us about them |
| Faithfulness to the original | Close, but **not confirmed**. Combat is a reconstruction, so some moves or timing may differ |
| Story dialogue in English | Not done |
| Browser version | **Experimental.** A battle can run in the browser, but it is unfinished and not tested for release |
| macOS | Not available |

Some routers can't make direct connections. Those players can't play online together yet, and the lobby tells you who
can't reach whom.

## What has been tested

We'd rather say this plainly than promise too much.

| | Tested? |
|---|---|
| Linux, with a person playing | Yes |
| Windows | Yes, a native run on 2026-11-04 (menus and controller), but no full playthrough yet |
| Online on one PC, on a simulated bad connection | Yes, automatically, with 2 and 4 players |
| Online between real PCs | Yes, first tested 2026-11-04; still in testing |
| Room codes through real routers | Yes, in that first real-PC session |
| Linux players against Windows players | Only the game's calculations on real Windows, and a match under Wine |
| The whole story, start to finish | **Not yet**, only in parts |

## Updates

The game asks GitHub once when it starts whether a newer release exists, and the title
screen tells you when one does. You can turn that off in Options → UPDATES.

An update replaces only the remake's own files. Your game files, your settings and your
texture packs stay where they are. If an update fails, the old version keeps working, and
you can download the new release from the Releases page by hand.

Players on 0.2.x had no updater, so they download 1.0.0 once by hand; from then on the game
keeps itself up to date.

## Playing online

1. Choose **NETWORK** on the title screen.
2. **To use a room code:** enter the server's address in the **SERVER** row. The person running the server gives it to you.
3. The host chooses **HOST A ROOM**, and the room code appears in the lobby. Everyone else enters it and chooses **JOIN BY
   CODE**.
4. When everyone is ready, you all go to the character select together.

Everyone needs the same version of this remake and the same game data. Other players in your room can see your IP
address.

## PSP characters

The PSP version, *Higurashi Daybreak Portable Mega Edition*, has three fighters the PC game does not: **Satoshi
Houjou**, **Miyoko Tanashi** and **Okonogi**. If you own that version too, the remake can add them.

Run this once, from the folder the remake is in, pointing at your own PSP ISO and at your Higurashi Daybreak folder:

```
# Linux
./daybreak --extract-psp=/home/you/psp-daybreak.iso --install=/home/you/Higurashi-Daybreak
# Windows
DaybreakRemake.exe --extract-psp=C:\roms\psp-daybreak.iso --install=C:\games\Higurashi-Daybreak
```

It takes a moment, checks every file it reads against a list of hashes, and writes a `psp-data` folder next to the
game. The three then appear on the character select, with their own models and their own art, and can be played in
offline matches. Pass `--psp-data=<folder>` if you want that folder somewhere else; the game then needs the same
flag on every start.

What to expect:

- Their moves are borrowed from the PC fighter with the closest moveset, so they play close to the PSP version
  rather than exactly like it.
- The chibi, costume and weapon pictures are place-holders: the PSP game ships no such art.
- Online play stays on the PC fighters for now, so everyone in a room uses the same data.

Nothing from the PSP game is included here. Delete `psp-data` at any time and the remake runs as it did before.

## Found a problem?

[Open a test report](https://github.com/Vmarcelo49/daybreak-remake/issues/new?template=test-report.md) and attach
`daybreak.log`, and `daybreak-previous.log` if the game crashed. You'll find them here:

- **Windows:** `%APPDATA%\daybreak-decomp\`
- **Linux:** `~/.config/daybreak-decomp/`

## Legal

This is an unofficial fan project, not connected to Twilight Frontier or 07th Expansion, who own the original game's
engine, art, audio and story. Please support them by owning the game. See [LICENSE](LICENSE) for this project's code.
