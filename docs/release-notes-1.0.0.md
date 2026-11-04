**The first stable release.** The game now checks for new versions, downloads them, verifies
they really come from us, and installs them — so you no longer need to download each release by
hand. From here on, updates arrive by themselves.

**If you are on 0.2.x, download this one by hand.** That release had no updater, so it cannot
fetch this one for you. After 1.0.0, the game keeps itself up to date.

You need your own copy of Higurashi Daybreak. This download contains none of the game's files.

## Install

1. Download the file for your system below.
2. Extract it into your game folder, the one with `daybreak00.dat`, replacing the previous version.
3. Open `DaybreakRemake.exe` on Windows, or `daybreak` on Linux. If your file manager shows `daybreak` as text, open `daybreak-bin`.

Linux needs glibc 2.38 or newer, such as Ubuntu 24.04, and a Vulkan driver. Your original game is not changed.

Online play is compatible with 0.2.1: the network protocol did not change.

## What's new since 0.2.1

### The game updates itself

- **It tells you when there's a new version.** At startup, a banner appears over the title
  screen: **Update**, **Release notes**, **Later**, or **Skip this version**. Later hides it
  until you restart. Skip means that version is never offered to you again.
- **The update installs in the background of a small screen.** It shows the download with its
  size and a progress bar, then checking the download, then installing. You can cancel until
  installing starts, at which point it has to finish.
- **Your files are never touched.** An update only replaces the remake's own files. Your game
  data, your settings, your earned titles and your texture packs stay exactly as they are. If
  an update fails, the old version keeps working and you can download the new one from the
  Releases page by hand.
- **You can turn it off.** Options → **UPDATES** switches the startup check off. Turning it off
  while a check is running cancels that check.
- **If the game is closed in the middle of an update**, the next launch finishes or undoes it
  before anything else runs, so you're never left with half of two versions.

### Controllers, at last

- **Whoever presses first is player 1.** No device owns a player at startup. The keyboard and
  each pad take the next free player the first time you press something, and that press counts
  — so you press A on a pad and you're player 1, ready to play. A pad you unplug keeps its
  player for the rest of the session.
- **A new pad layout:** A jump/confirm, B guard/cancel, X melee, Y change target, RB shoot,
  LB special, RT tactics, Start pause. If you never rebound your pad, you get this layout
  automatically. If you did rebind it, your bindings are kept.
- **The menus cancel with B** on a pad. The keyboard still cancels with X.
- **Rebinding a controller now works.** Controls shows a **KEYS** column and one column per
  player, named after the pad you have (Xbox, PlayStation, Nintendo). Press whatever you're
  using — a key changes the keys, a pad button changes that pad's player — from any column.
  The triggers can be bound too, which the old version could not do.

### The title screen

- **The shrine grounds are now the title background**, drawn live behind the menu, with the
  camera sweeping slowly over them. The original's painted title is still there: Options →
  **TITLE BACKGROUND** → **ORIGINAL**, or `backdrop = off` in the settings file.

### Online

- **Web battles finish.** A whole match played through the web build used to die at the moment
  a round was won, because the winner's lines and their portrait were never loaded. Fixed.

### Language

- **Result titles are translated.** Winning a match with a character can earn them a title;
  these were always shown in the original's Japanese in English mode. All 41 now have English
  names, and one we have no English name for shows `UNKNOWN TITLE` instead of Japanese text.
- Long titles now fit inside the results panel instead of running past it.

### Fixes

- **Split-screen markers landed in the wrong view.** The boxes the battle draws over fighters'
  hit and aura areas were placed using the last camera's view, so with two or more views on
  screen they appeared bunched into one view instead of each fighter's own. Each view now gets
  its own markers.

## What to expect

- Not yet tested: online between real PCs, and room codes through real routers.
- Some routers can't make direct connections. The lobby tells you who can't reach whom, and there's no relay yet.
- If a player drops, everyone freezes for about 5 seconds before a computer player takes over.
- The pause key leaves an online match at once, with no confirmation.
- Any player can send everyone back to the lobby from character select.
- Story dialogue is still in Japanese.
- Combat is a reconstruction, so some moves or timing may differ from the original.
- Updating on Windows is new. If the game offers you an update and installing it does
  something unexpected, download the release by hand from this page and tell us.

## Report a problem

[Open a test report](https://github.com/Vmarcelo49/daybreak-remake/issues/new?template=test-report.md) and attach `daybreak.log`, plus `daybreak-previous.log` after a crash:

- Windows: `%APPDATA%\daybreak-decomp\`
- Linux: `~/.config/daybreak-decomp/`

## SHA-256

```
36f8e308cc3b36be8b8550bfc61d9f46afb5bda1942b400cd93758ca7a313a29  daybreak-1.0.0-linux-x86_64.tar.gz
5a751a33aa76e92d447221f4bd9bc110e1e1a8b9086dc0320631b490a684c162  daybreak-1.0.0-6c83505-windows-x86_64.zip
```
