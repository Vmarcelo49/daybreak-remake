# Higurashi Daybreak Kai Fan Remake — Linux release (offline versus)

This package is the playable port of *Higurashi Daybreak* (`DaybreakDX.exe`, Twilight
Frontier / 07th Expansion) for 64-bit Linux: title screen, character/weapon selection,
stage settings, VS, a real 1v1 or 2v2 battle, results, and rematch. It is **not** a copy of
the game: it reads **your own** install's files (`.X` models, `.cnv` images,
`daybreakXX.dat` bundles) in place, so you need the original game.

Nothing in this archive is game data. The port is at an early-release stage: see
"What is not supported yet" before reporting something missing.

## 1. What you need

- 64-bit Linux (x86_64) with a **Vulkan** GPU driver (Mesa RADV/AMDVLK, NVIDIA, Intel) and
  a Wayland or X11 desktop session. The port asks for Vulkan specifically and needs **no
  optional WebGPU feature**, so any Vulkan-capable GPU works: NVIDIA Kepler or newer (GTX
  600/700), AMD GCN 1st gen or newer (HD 7000), Intel HD 4000 or newer (3rd-gen Core).
- Your own *Higurashi Daybreak* installation (the folder that contains `daybreak00.dat`).
  Any language release works; the port reads the original files directly.
- About 30 MB of disk for this package (the game install is ~7 GB — 4.4 GB of
  `daybreakNN.dat` bundles plus ~2.6 GB of loose files — and stays where it is).
- **Memory**: measured peaks are ~280 MB of RAM and ~290 MB of GPU memory (VRAM + shared) for
  a four-view 2v2 battle, so 1 GB of RAM and 256 MB of GPU memory are the practical floor and
  2 GB / 512 MB is comfortable. The full measurement, the method and what it does not
  establish are in `docs/PERFORMANCE.md`.

## 2. Unpack and run

```bash
tar -xzf daybreak-0.1.0-linux-x86_64.tar.gz
cd daybreak-0.1.0-linux-x86_64
./daybreak --install="/path/to/Higurashi-Daybreak"
```

`./daybreak` is the launcher: it finds the game folder, remembers it, and starts the title
screen. After the first successful launch, plain `./daybreak` is enough. You can also
double-click `daybreak` in a file manager (a dialog appears if something is wrong).

If the launcher cannot find a game folder it prints the list of places it looked and asks
you for the folder — or tells you exactly what to run when there is no terminal.

### Where to point it

The launcher looks for `daybreak00.dat` in this order, first hit wins:

1. `--install=DIR` on the command line
2. `$DAYBREAK_INSTALL`
3. the remembered folder: `[game] install_dir` in
   `$XDG_CONFIG_HOME/daybreak-decomp/settings.conf`
   (`~/.config/daybreak-decomp/settings.conf` by default)
4. the folder this package was unpacked into (unpack it inside your game folder and it
   just works)
5. the current working directory
6. `$XDG_DATA_HOME/Higurashi-Daybreak` (`~/.local/share/Higurashi-Daybreak`)
7. `~/Higurashi-Daybreak`, `~/Daybreak`, `~/Games/Higurashi-Daybreak`, `~/Games/Daybreak`

Point it at the folder holding `daybreak00.dat` — do **not** extract the `.dat` files: the
port reads the game's own bundles, which are the authority the original executable uses
(some files differ between the bundles and an extracted tree, so the bundles are the right
source). The launcher needs that folder; an extracted `data/` tree is a source-build path,
not something this launcher discovers.

```bash
./daybreak --install="$HOME/Games/Higurashi-Daybreak"   # one-off
export DAYBREAK_INSTALL="$HOME/Games/Higurashi-Daybreak" # per shell
```

The folder is remembered in the port's **own** settings file, next to the port's other
settings and nowhere else: the launcher hands it to the binary, which writes it to
`$XDG_CONFIG_HOME/daybreak-decomp/settings.conf` (`[game] install_dir`) when it opens it.
The launcher itself writes no config file at all, so a direct
`./foundation_demo --screen=title` run — no launcher, no flag — starts from the same folder.
Releases before this one kept the folder in a separate `install.conf` in that directory;
a leftover one is read once (so your answer is not lost), moved into `settings.conf` by the
same mechanism, and then removed.

`--install=DIR` and `$DAYBREAK_INSTALL` still win for the run that names them: they are
instructions for that run, while the remembered folder is only a starting point, and a
remembered folder that has since been moved or deleted is reported and skipped instead of
stopping the launch.

## 3. Controls (defaults)

Menus: **arrow keys** move, **Z** confirms, **X** cancels, **Esc** leaves the screen
(in a battle, **Esc** opens the pause menu).

Battle (player 1):

| Action | Key | Gamepad (Xbox layout) |
|---|---|---|
| Move | arrow keys | D-pad / left stick |
| Melee | X | X |
| Guard | D | A |
| Shoot | C | B |
| Jump | Z | Y |
| Special | S | right shoulder |
| Tactics | Q | Back |
| Lock on / switch target | A | left shoulder |
| Pause | W | Start |
| Camera nudge left / right | Q / E | — |

A connected gamepad takes its own controller slot; the port keeps a pad's bindings with
the pad's identity across replugs. Keys and buttons can be rebound, and volumes, fullscreen
and resolution changed, in **Options** / **Key Config** on the title screen; all of that is
saved in `$XDG_CONFIG_HOME/daybreak-decomp/settings.conf`.

## 4. What is not supported yet

- **Story, prologue and netplay screens.** This is the offline versus front end (decision
  D6); those title items stay on the title screen with a console note.
- **Texture-resolution selection** (renderer Options row 2) and browser-side settings
  persistence are still open. Toon shading (row 0) and character shadows (row 1) are live.
- **3v3/4v4**: a match is at most four fighters, two teams of one or two.
- **Windows, the web and macOS builds** exist in the source tree but are not part of this
  package; macOS has never been executed.
- The **original game's own configuration** (`config.dat`) is not read or written; the port
  keeps its own settings file instead.
- Every legal character/weapon selection the install ships launches (all 46 are verified in
  `tests/weapon_definition_test.cpp`). An item whose data ships no attachment mesh is still
  armed — it just draws no attachment — so a missing mesh is not a launch failure.
- The **victory voice** of some winning pairs is not in the install's `data/voice/win`
  (the quote text still appears; only the spoken line is skipped). That is an install gap,
  not a port error.

## 5. Troubleshooting

| What you see | What to do |
|---|---|
| `No Higurashi Daybreak game data found` | Point the launcher at the folder with `daybreak00.dat`: `./daybreak --install="/path/to/Higurashi-Daybreak"` |
| `no game data in "..."` | The folder is not a game folder (or is a partial copy): it needs the game's `daybreakXX.dat` files |
| `no usable GPU adapter` | Install/update your Vulkan driver, and run from a desktop session (not a bare console or a VM without GPU passthrough) |
| `caption font missing` / `package is incomplete` | The archive was unpacked incompletely: unpack it again (the fonts live in `assets/fonts/`) |
| Nothing happens on a double-click | Run `./daybreak` from a terminal: the reason is printed there |

Run from a terminal to see the full log (adapter, game folder, loaded bundles, settings).

## 6. Licences

The port's own code is under the repository's licence; SDL3, wgpu-native, GLM, stb and the
two caption fonts (Gyrotrope Black, Noto Sans CJK JP) are third-party works redistributed
under their own licences. See `LICENSES/README.md` for the component list and the licence
texts. The game's data files are not distributed here and remain the property of their
rights holders.
