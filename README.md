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
| Browser version | Not ready: battles end in a crash after about 30 seconds |
| macOS | Not available |

Some routers can't make direct connections. Those players can't play online together yet, and the lobby tells you who
can't reach whom.

## What has been tested

We'd rather say this plainly than promise too much.

| | Tested? |
|---|---|
| Linux, with a person playing | Yes |
| Windows | **Not on a real Windows PC yet in this version**, only in an emulated environment (Wine) |
| Online on one PC, on a simulated bad connection | Yes, automatically, with 2 and 4 players |
| Online between real PCs | **Not yet.** That is what this test version is for |
| Room codes through real routers | **Not yet** |
| Linux players against Windows players | Only the game's calculations on real Windows, and a match under Wine |
| The whole story, start to finish | **Not yet**, only in parts |

## Playing online

1. Choose **NETWORK** on the title screen.
2. **To use a room code:** enter the server's address in the **SERVER** row. The person running the server gives it to you.
3. The host chooses **HOST A ROOM**, and the room code appears in the lobby. Everyone else enters it and chooses **JOIN BY
   CODE**.
4. When everyone is ready, you all go to the character select together.

Everyone needs the same version of this remake and the same game data. Other players in your room can see your IP
address.

## Found a problem?

[Open a test report](https://github.com/Vmarcelo49/daybreak-remake/issues/new?template=test-report.md) and attach
`daybreak.log`, and `daybreak-previous.log` if the game crashed. You'll find them here:

- **Windows:** `%APPDATA%\daybreak-decomp\`
- **Linux:** `~/.config/daybreak-decomp/`

## Legal

This is an unofficial fan project, not connected to Twilight Frontier or 07th Expansion, who own the original game's
engine, art, audio and story. Please support them by owning the game. See [LICENSE](LICENSE) for this project's code.
