# Higurashi Daybreak — Remake

An open-source remake and reverse-engineering project for **Higurashi Daybreak**, the 3D arena fighting game developed by Twilight Frontier and 07th Expansion.

The goal is to bring the original game to modern platforms while preserving its gameplay, characters, assets, and overall identity.

The remake is written in **C++17**, using **SDL3 and WebGPU**, with Linux, Windows, and browser support as development targets.

![Higurashi Daybreak remake screenshot](https://github.com/user-attachments/assets/64fe73d2-a2a7-4e61-aae6-7d9167c0c874)

## Project status

**Early playable development — not ready for a normal playthrough.**

This is a working remake, not just a model viewer or technical prototype. You can navigate the menus, select characters, enter battles, and reach the results screen.

However, the core combat experience is still incomplete. Many character moves, animations, and combat behaviors are broken or inaccurate.

If you are discovering this project for the first time, expect an experimental build with visible progress, significant bugs, and missing features.

### What works

- **Menus and game flow:** Title screen, character and team selection, weapon selection, stage settings, VS screen, battle, and results.
- **Original game assets:** Loads the original `.X` models, `.cnv` textures, and `.dat` archives directly, without requiring asset conversion.
- **3D rendering:** Characters, weapons, stages, textures, animations, and basic visual effects.
- **Local battles:** 1v1 and 2v2 match structures, including split-screen support.
- **Computer opponents:** An initial implementation of COM-controlled fighters.
- **Battle systems:** Health, damage, projectiles, targeting, camera behavior, HUD, round progression, and match results.
- **Audio and input:** Music, sound effects, keyboard and gamepad input, with configurable controls.
- **Display settings:** Resolution selection, fullscreen, and viewport scaling.

These features are implemented, but implementation does not mean they are bug-free or faithful to the original.

### What's broken or incomplete

| Area | Current limitations |
|---|---|
| Combat | Many attacks, character-specific behaviors, and combat interactions remain incorrect or incomplete. |
| Animations | Animation selection, transitions, and synchronization are unreliable across much of the roster. |
| Visual fidelity | Some effects, shadows, rendering details, and UI behavior still differ from the original. |
| Game balance and AI | Combat behavior and computer opponents are not yet faithful to the original game. |
| Windows | Builds can reach gameplay, but a rematch crash has been documented. |
| Web | Experimental. Asset delivery and rendering still have known problems. |
| Multiplayer | LAN and online multiplayer are not implemented. |
| Story mode | Not implemented. |
| macOS | Not tested. |

This is not an exhaustive bug list. For tracked issues and current priorities, see the [GitHub Issues](https://github.com/Vmarcelo49/daybreak-remake/issues) and [development roadmap](remake/foundation/docs/ROADMAP-PENDING.md).

## What should you expect?

**If you just want to play Higurashi Daybreak:** This remake is not yet a replacement for the original game. You will likely encounter broken moves, incorrect animations, and gameplay bugs.

**If you want to experiment:** You can already explore the menus, load original assets, enter matches, and see how the port is progressing.

**If you're a developer:** There is substantial work to do, especially around combat reconstruction, animation behavior, rendering fidelity, and platform support.

**If you're interested in reverse engineering:** The repository includes a separate research corpus containing thousands of decompiled functions, symbol information, and analysis of the original executable.

The project is actively evolving, and some features may regress as underlying systems are replaced or corrected.

## Building the remake

### Requirements

You will need:

- CMake 3.20+, Ninja, and a C++17 compiler.
- `curl` and `unzip`.
- SDL3 development libraries and a working Vulkan driver on Linux.
- A copy of the original Higurashi Daybreak game data to load the actual game assets.

The repository does **not** distribute the original game's executable or copyrighted assets.

### Linux

From the repository root:

```bash
./remake/foundation/build.sh deps
./remake/foundation/build.sh linux
```

Then launch the remake using your original game installation:

```bash
./remake/foundation/build/linux/foundation_demo \
  --install=/path/to/Higurashi-Daybreak \
  --screen=title
```

### Windows and Web

Cross-compilation targets are also available:

```bash
./remake/foundation/build.sh windows
./remake/foundation/build.sh web
```

Windows cross-compilation requires MinGW-w64. Web builds require the Emscripten SDK.

These targets are experimental and are not guaranteed to provide the same experience as Linux.

For platform-specific instructions and troubleshooting, see the [foundation build documentation](remake/foundation/README.md).

### Running tests

After building the Linux target:

```bash
ctest --test-dir remake/foundation/build/linux --output-on-failure
```

Some tests require original game data and will be skipped when it is unavailable.

For detailed testing procedures, see the [release checklist](remake/foundation/docs/RELEASE-CHECKLIST.md).

## Contributing

Contributions are welcome, whether you're interested in gameplay programming, reverse engineering, rendering, testing, or documentation.

Before starting, check the [open issues](https://github.com/Vmarcelo49/daybreak-remake/issues) and the [remaining roadmap](remake/foundation/docs/ROADMAP-PENDING.md) to avoid duplicating existing work.

### Where to start

| Interest | Relevant area |
|---|---|
| Gameplay and combat | `remake/foundation/src/gameplay/` |
| Animation and asset loading | `remake/foundation/src/assets/` |
| Graphics and shaders | `remake/foundation/src/render/` and `src/shaders/` |
| Menus and HUD | `remake/foundation/src/ui/` |
| Audio and controls | `remake/foundation/src/audio/` and `src/input/` |
| Reverse engineering | `research/` |
| Testing and documentation | `remake/foundation/tests/` and `docs/` |

### Contribution guidelines

1. Open an issue or discuss an existing one before undertaking a large change.
2. Keep changes focused and explain the problem they solve.
3. When reconstructing original behavior, include supporting evidence from the reverse-engineering research whenever possible.
4. Build and run relevant tests before submitting a pull request.
5. Document known limitations rather than presenting incomplete behavior as fully implemented.

Please read [AGENTS.md](AGENTS.md) and [development decisions](remake/docs/decisions.md) before modifying core systems.

**Important:** `research/recomp/` contains generated code and must not be edited manually. Original game assets must not be committed to the repository.

## Repository structure

This repository contains two closely related projects:

| Directory | Purpose |
|---|---|
| `remake/foundation/` | The actual remake: game code, rendering, assets, platform support, and tests. |
| `remake/docs/` | Game specifications, technical decisions, and reference material. |
| `remake/tests/parity-baseline/` | Reference captures and behavioral evidence from earlier implementations. |
| `research/` | Decompiled functions, recovered symbols, binary analysis, and reverse-engineering tools. |
| `docs/` | Research documentation, progress reports, and development conventions. |

The remake and reverse-engineering research are kept separate intentionally. The research provides evidence about how the original works; the remake uses that evidence to reconstruct its behavior.

## Project goals

The long-term objective is a playable, modern, cross-platform version of Higurashi Daybreak that stays faithful to the original experience.

The main priorities are:

1. Make the core combat and animation systems reliable.
2. Improve gameplay accuracy and visual fidelity.
3. Stabilize the Linux, Windows, and browser builds.
4. Continue recovering undocumented behavior from the original executable.
5. Expand supported features once the fundamental gameplay is stable.

There is currently no promised release date.

## Legal notice

This is an unofficial fan project and is not affiliated with or endorsed by Twilight Frontier or 07th Expansion.

The original game, characters, artwork, audio, and other assets belong to their respective rights holders.

The repository does not include the original game executable or copyrighted game data. Users must supply their own game installation.

Reverse-engineering materials are provided for research and educational purposes.
