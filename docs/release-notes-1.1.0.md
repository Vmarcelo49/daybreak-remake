**Story mode in English, and a stronger update and online foundation.** This release completes the
story translation started after 1.0.1: in English mode the dialogue and the victory quotes are
translated, while Japanese mode still shows the game's own text. Voices and the text burned into
the movies stay Japanese. The rest of this release is work you should not normally notice: updates
keep their retry record when Windows cannot delete a running executable, backups no longer risk
overwriting files the updater does not own, online rooms renew with a secret instead of trusting a
public ID, and mismatched builds are refused before a match can drift apart.

**Everyone in a room must be on 1.1.0.** Builds that simulate differently now refuse each other
in both directions, and the rendezvous server's authenticated room renewal speaks a new protocol
version. Joining is still open to older clients, but hosting requires this update.

You need your own copy of Higurashi Daybreak. This download contains none of the game's files.

## Install

1. The game offers this update when it starts: choose **Update**. Or download the file for
   your system below.
2. Extract it into your game folder, the one with `daybreak00.dat`, replacing the previous version.
3. Open `DaybreakRemake.exe` on Windows, or `daybreak` on Linux. If your file manager shows `daybreak` as text, open `daybreak-bin`.

Linux needs glibc 2.38 or newer, such as Ubuntu 24.04, and a Vulkan driver. Your original game is not changed.

## What's new since 1.0.1

### Story in English

- **Dialogue and victory quotes are translated.** The 983 story dialogue lines and 1,291 victory
  quotes are translated into English and ship with the game. Switch the language in Options, or
  start with `--language=en`; Japanese mode still shows the install's original text. Voices stay
  Japanese, and so does the text drawn into the original movies and the game's title logo.
- **The browser version carries the story assets.** Story mode used to fail in the delivered web
  build because its art and scripts belonged to no loading group. It now requests them when you
  choose the story, rather than adding ~106 MB to the title screen or to every match.

### Online

- **Rooms renew with a secret, not just a public ID.** The host ID was visible to everyone in a
  room, so someone who knew it could redirect the room's rendezvous entry. The server now issues a
  secret to the host and requires it on every renewal; a wrong or missing secret changes nothing.
  This does not make the connection private: someone who has observed the host's traffic to the
  server can still use the secret, and UDP spoofing is not fixed. A released 1.0.x client can
  still join a room, but it must update to host one.
- **Different builds can no longer start a match together.** The lobby compared only a protocol
  number and the game data, so builds that computed battles differently could agree to play and
  then drift apart. A mismatch is now refused as a different version in both directions.
- **A desynchronized match is thrown out.** If the peers' state hashes no longer agree, the match
  is invalidated rather than continued with two different battles.

### Updates

- **A deferred cleanup no longer loses its retry record.** On Windows a running executable cannot
  be deleted immediately after an update; the updater now keeps the journal and backup until the
  next start can finish the cleanup.
- **Backups live inside the update's own workspace.** Files at a target's `.old` path that the
  updater does not own — including orphans left by earlier releases — are neither overwritten nor
  deleted. Unexpected collisions refuse the update before anything is changed.
- **The Windows update self-test actually tests what it claims.** A failure in its last suite now
  makes it exit nonzero, its executable-rename probe uses a disposable copy, and recovery is tested
  against a genuinely interrupted transaction.

### Under the hood

- The deterministic math sources are shared by the build and the fingerprint workflow, so the
  cross-platform check can no longer silently omit an implementation file.
- The web target has a bounded, manual build check, and the menu-script state no longer depends on
  include order. A fresh web build failed before this; it compiles and links now.
- Ordinary changes get a small, data-free native build-and-test check before release. Release
  packaging and the install-backed local gate remain separate.

## What to expect

- Online is still in testing. It has been played between two real PCs; the fixes above come from
  that work and from code review, not from a large playtest.
- Some routers can't make direct connections. The lobby tells you who can't reach whom, and
  there's no relay yet.
- If a player drops, everyone freezes for about 5 seconds before a computer player takes over.
- The pause key leaves an online match at once, with no confirmation.
- Any player can send everyone back to the lobby from character select.
- The English story translation is complete for dialogue and victory quotes, but it is a
  translation of a Japanese script: some lines are short, and long English lines can wrap inside
  the original narrow caption box. A few dual-speaker quotes display a `BOTH:` prefix.
- Combat is a reconstruction, so some moves or timing may differ from the original.
- The browser version is experimental. Its story assets are delivered now, but a full story flow
  has not been verified in a browser.

## Report a problem

[Open a test report](https://github.com/Vmarcelo49/daybreak-remake/issues/new?template=test-report.md) and attach `daybreak.log`, plus `daybreak-previous.log` after a crash:

- Windows: `%APPDATA%\daybreak-decomp\`
- Linux: `~/.config/daybreak-decomp/`

## SHA-256

```
08ad33686e9f8468c703b53d8134dbd278d6e6838e41855893dab8f3d726f803  daybreak-1.1.0-linux-x86_64.tar.gz
9d4ccc1ff4e22493f619af57527c0b6a362873be7a54551194e6589b31ebe590  daybreak-1.1.0-88add744-windows-x86_64.zip
```
