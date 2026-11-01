# 0.2.1 release notes: DRAFT

> **Not released.** The owner holds this version until the online changes below are decided and done.
> Up to date through `bc3e3cc6`. Add to it as work lands. Everything from "Before publishing" down is
> for us: delete it, and this note, when the text goes on the release page.

**This is a test build.** Online play still needs testing over real networks. Expect problems, and please report them.

You need your own copy of Higurashi Daybreak. This download contains none of the game's files.

## Install

1. Download the file for your system below.
2. Extract it into your game folder, the one with `daybreak00.dat`, replacing the previous version.
3. Open `DaybreakRemake.exe` on Windows, or `daybreak` on Linux. If your file manager shows `daybreak` as text, open `daybreak-bin`.

Linux needs glibc 2.38 or newer, such as Ubuntu 24.04, and a Vulkan driver. Your original game is not changed.

## What's new since 0.2.0

### Online

- **Room codes work out of the box.** The game now uses our server by default, so you no longer have to find and type one. Hosting a room contacts it to get a code, and no game data passes through it. To use another server, change the SERVER row of the online menu or `server` in the settings file.
- **Type in the online menu.** Press Enter on JOIN BY CODE, JOIN BY ADDRESS, NAME, PORT or SERVER and write with the keyboard: Backspace deletes, Enter confirms and Esc cancels. Enter on a join row joins the room. A pad can still write, with up and down.
- **You can see what a join is doing.** The screen says it's looking for the room or connecting to the host, and you can cancel. If it fails, you go back to the menu with your code still there and the reason: no room has that code, the server didn't answer, or the room exists but the host didn't answer.
- **Hosting tells you when there's no code.** The lobby says it's getting a room code, and says so if the server doesn't answer. Others can still join by address.

### Language

- **The game picks its language from your system on first run.** A Japanese system keeps the game's Japanese menus, and anything else starts in English. You can still change it in Options, and your choice is kept. If you chose Japanese in 0.2.0 on a non-Japanese system, choose it once more. Story dialogue is still Japanese.

### Fixes

- **Battles now load from game folders with non-English names.** On Windows, a battle could fail with "Cannot open archive" after the menus had worked.
- **Character select: wrong pictures on the name plates.** On some PCs a name plate could show pieces of other menu art, such as "TAG MODE" or Rena's sprite. The game now loads a smaller copy of a menu sheet if the graphics card refuses the large one. If you saw this, please tell us whether it's gone.
- **Akane's sheathed weapon** rides in the correct hand.
- **Onigari Ryouou's hypermode glow** is no longer a black square.
- **Reflective shots** no longer draw on top of everything.

### Effects added

- **Time stop** inverts the colours of each player's view, and **the long stop** draws a negative sphere on the fighter it holds.
- **The bucket** from Satoko's traps now sits on the victim's head and blacks out their view.
- **Tomitake's camera flash** whites out the victim's view.

### Test keys in versus battles

The original game's test keys are back, and they work in versus but not in story or online:

| Key | What it does |
|---|---|
| F1 | Full health for everyone, balloons back to 0 |
| F2 | Computer players stop |
| F3 | Computer players start again |
| F4 | Fills everyone's hypermode gauge |

We added these for testing, and they aren't in the original:

| Key | What it does |
|---|---|
| F5 | Refills everyone's ammo |
| F6 | Writes every fighter's state to the log |
| F7 | Freezes or resumes the battle |
| F8 | While frozen, advances one tick |

## What to expect

- Not yet tested: online between real PCs, and room codes through real routers.
- Some routers can't make direct connections. The lobby tells you who can't reach whom, and there's no relay yet.
- If a player drops, everyone freezes for about 5 seconds before a computer player takes over.
- The pause key leaves an online match at once, with no confirmation.
- Any player can send everyone back to the lobby from character select.
- Story dialogue is still in Japanese.
- Combat is a reconstruction, so some moves or timing may differ from the original.

## Report a problem

[Open a test report](https://github.com/Vmarcelo49/daybreak-remake/issues/new?template=test-report.md) and attach `daybreak.log`, plus `daybreak-previous.log` after a crash:

- Windows: `%APPDATA%\daybreak-decomp\`
- Linux: `~/.config/daybreak-decomp/`

## SHA-256

```
(from the CI build)
```

---

## Before publishing

- [ ] Write the Online section, once the changes are decided.
- [ ] Re-read "What to expect" against what the online changes did. It is copied from 0.2.0, and the first three online items may be out of date.
- [ ] Change `VERSION` to 0.2.1, which starts CI, and fill in the checksums.
- [ ] Follow `docs/RELEASE-CHECKLIST.md`.
- [ ] #90: reword or drop the fix if a tester says otherwise. It is not verified on an affected machine, and why the device refused the sheet is unknown.
- [ ] F6 goes to stdout. Check that it reaches `daybreak.log` on a packaged build, or reword its row.
- [ ] Type in the online menu with a real keyboard, and write with a real pad. So far only a headless schedule has driven it.
- [ ] Press F1 to F8 by hand in a versus battle. Only a schedule has driven F1 to F6, and F7 and F8 have never run.
- [ ] Look at the bucket and the flash in a real match. So far they've only been seen in headless captures.

## Commits since `v0.2.0`

| Commit | What | In the notes |
|---|---|---|
| `ccb30ca4` | Archives, online data hash and log opened with a wide path on Windows | Fixes |
| `61d95277` | A player's drop counted during a skipped tick | No: the match itself was right |
| `cfed4f23` | Akane's hand, additive weapon materials, time stop and long stop effects, shot depth | Fixes, Effects |
| `dd1577ef` | The status bucket on the head | Effects |
| `a73a74f9` | The victim's view under the flash or the bucket | Effects |
| `76b26cae` | Debug keys, `--plan` and related options, the `combo-test` skill | Test keys |
| `d0766e21` | A session event counted twice, a fragile slot check in `net_play_check` | No: statistics and a test |
| `8fa47413` | #90's fallback, #89's flow gate, `AGENTS.md` | Fixes (#90 only) |
| `2f25d7e5` | The rendezvous server deployed, its port set by `DAYBREAK_PUBLIC_PORT` | No: the server, not the game |
| `a393826a` | The owner's server as the default, and the SERVER row at full width | Online |
| `bc3e3cc6` | Typing in the online menu, `--text-keys` | Online |
