# Windows test package

1. Extract **all files** from this ZIP into your existing Higurashi Daybreak game
   folder, beside `DaybreakDX.exe` and `daybreak00.dat`.
2. Double-click **DaybreakRemake.exe**. The opening movie leads to the title menu.
3. Choose Versus, select character + weapon and Player/COM, then start a battle.

Keep `DaybreakRemake.exe`, `SDL3.dll`, `wgpu_native.dll` and `assets/fonts/`
together. Copying the executable alone is insufficient. The package contains no
original game data; you need your own installation. It does not replace
`DaybreakDX.exe`.

## Controls

Arrow keys move. Z jumps/confirms, X uses melee/cancels, C shoots, A changes
target (hold for 250 ms to aim at your ally), S uses special/hypermode, D guards,
Q changes tactics, and W or Escape pauses. The pause menu uses arrows, Z to
confirm and X to resume. Bindings can be changed in Options.

Settings are stored in your Windows application-data folder under
`daybreak-decomp/settings.conf`. The game files are not used for settings storage.

## Playing online

Choose **NETWORK** on the title. To use a room code, first enter the server's address in the **SERVER** row, which
you get from whoever runs it. The host chooses **HOST A ROOM**, and the room code appears in the lobby. Everyone else
enters it and chooses **JOIN BY CODE**. Once everyone is ready, you all go to the character select. Other players can
see your IP address.

Everyone needs this same package and the same game data, or the lobby refuses them.

## Reporting a problem

Attach `daybreak.log`, and `daybreak-previous.log` if the game crashed. Both are in
`%APPDATA%\daybreak-decomp\`. Say which character and stage you had, and for online problems, what everyone's
lobby showed.

## What to test

Check title → selection → countdown → battle → results → rematch. Confirm that
movement, attacks, target changes, pause and audio work. Try a second round and
report any crash, including which character + weapon and stage were selected.
Animation fidelity remains incomplete.

This is a Windows x64 test build. Cross-compilation and Wine checks do not replace
a run on actual Windows hardware. Install a current graphics driver. If startup
fails, the executable displays an error dialog naming missing files or the failure.

Third-party notices are in `LICENSES/`. `BUILD-INFO.txt` identifies the build.
