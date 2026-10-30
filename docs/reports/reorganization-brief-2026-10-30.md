# Repository reorganization brief (2026-10-30)

Approved by the owner. A delegate agent does the mechanical work; the owner and the planning
agent review it afterwards against section 6.

**Objective:** the same game, byte for byte in its output, from a repository whose layout says
what each part is. No behaviour changes. No new features. No fixes that are not needed to keep
this work building.

Base revision: `b389ca6d`. Work on a topic branch named `reorganize`, created from it. Do not
merge it into `main`: the owner does that after review.

## 1. Rules

These override anything else you find in the repository.

1. **Commit each stage in reviewable commits on `reorganize`.** Put pure moves (`git mv`) in their
   own commit, separate from edits, so Git keeps following each file's history. Before every
   commit read `git diff` and `git diff --cached`. End each message with the attribution your
   harness requires. Prefixes: `refactor:`, `chore:`, `docs:`.
2. **Never** push, force push, rewrite history, `reset --hard`, `clean -fd` or `checkout .`.
3. **Never edit the content of `src/sim/core/`.** It is vendored and byte-pinned. Moving the folder
   is allowed; `MANIFEST.sha256` must still verify afterwards. The same goes for `research/recomp/`,
   `research/decompiled/` and `research/binary_data/`: do not touch them.
4. **Never commit** game files, `Higurashi-Daybreak/`, `.local-analysis/`, `local-data/`, build
   outputs, `third_party/` or anything else that is ignored today. Check the staged paths.
5. **Delete nothing on disk that Git does not track.** Stage 6 belongs to the owner.
6. **Do not change game logic to make a test pass.** If a check fails and the cause is not a path,
   a name or a build setting, stop and report it.
7. **A claim needs a command behind it.** "Built" is not "verified", and a skipped test is not a
   pass. Run `ctest` and read its summary. Check every command's exit status, because a failed
   build leaves old binaries behind that still "pass".
8. Each focused problem gets 3 attempts. After that, stop and write what blocks you in
   `docs/QUESTIONS.md`, in that file's format, and in your report.
9. Do not push through a stage whose checks fail. Stop there. A partial result with an honest
   report is fine; a finished one with a hidden failure is not.
10. Keep verification silent: pass `--no-audio`. Do not read the whole documentation tree: the
    documents here are mostly history and many give retired instructions.

## 2. Target layout

```
src/
  app/          main.cpp, split in stage 4
  battle/       sim/battle.*, sim/core_battle.*, simctl, simfuzz, script.h, core_prelude.h,
                game/battle_*, and from gameplay/: character_moves, combat_record, weapon_definition,
                weapon_trail, match_economy, rng, held_axis
  battle/core/  today's sim/core/, content untouched
  hud/          ui/hud*, game/hud_*, gameplay/hud_fill.*
  frontend/     ui/screen*, frontend_*, participants, result_quote; result_title goes here too
  ui/           what remains: sprite, font, text, caption
  camera/       gameplay/arena_camera.* and render/arena_camera.h, with distinct names
  render/ gpu/ shaders/ assets/ audio/ movie/ input/ platform/ physics/ settings/   as today
tests/  cmake/  scripts/  package/  webdelivery/  assets/  third_party/  (ignored)  build/  (ignored)
docs/       one documentation tree; closed plans in docs/archive/
research/   as today, plus research/evidence/
tools/      harness, launch_original.sh, asset-tools, hook-tracer, the audit tools
CMakeLists.txt  build.sh  VERSION  README.md  AGENTS.md  LICENSE
```

`remake/`, `src/game/`, `src/gameplay/` and `src/sim/` must not exist at the end. Where the table
leaves a file's home open, pick the folder its header describes and list the choice in your report.

The rule that only `sim/battle.cpp` includes the core stays true after the rename. Keep the
`foundation_sim` private include path and the `core_prelude.h` force-include working under their
new paths.

## 3. Baseline, before any move

Do this first, on the base revision.

1. Commit the pending `docs/DIRECTION-STATUS.md` change and this file as one `docs:` commit.
2. Build and run the suite. All must pass; record the count:
   ```bash
   ./remake/foundation/build.sh linux
   ctest --test-dir remake/foundation/build/linux -j4 --timeout 400
   ```
3. Record the fingerprints in `local-data/harness/reorg-baseline/` (ignored), with
   `SDL_GAMECONTROLLER_IGNORE_DEVICES_EXCEPT=0x0000/0x0000` set so a connected pad cannot change a run.
   Run each one twice: if two runs differ, report it and leave that one out rather than comparing it.
   - **Simulation:** `simctl --roster rena:0:human mion:0 keiichi:0 satoko:0 --ticks 3600`, plus one run
     for each of `--roster chie:1 rika:2 irie:0 hanyu:1` and `--roster akasaka:2 natumi:0 tomitake:1 shion:2`. Keep the printed hash.
   - **Pixels:** sha256 of the `--out` PPM from `foundation_demo --headless --no-audio --install=Higurashi-Daybreak`
     with `--screen=battle --frames=400 --size=640x360`, with `--screen=title --frames=200 --size=1280x720`,
     and with `--screen=title --local-players=4 --script=<tests/scripts>/frontend-4p.txt --frames=3500 --size=640x360`.

## 4. Stages

After each one, run section 5's checks before starting the next.

1. **Flatten.** Move `remake/foundation/*` to the root and fix what that breaks: the `../../` paths in
   `CMakeLists.txt`, `build.sh`, `scripts/package_*`, the `.gitignore` files, tests that search for a
   `remake/foundation` marker (`tests/env_spawn_test.cpp`), `tools/rebuild_and_run.sh`,
   `tools/wt-setup.sh`, `remake/scripts`, `tests/npr_evidence.py`. Rename the executable to `daybreak` and
   drop the `foundation_` prefix from CMake targets, using `battle_core` and similar names for what
   would collide. Keep the `fnd::` namespace. Update `AGENTS.md`'s commands and paths in the same stage.
2. **Unify.** Merge `remake/docs/` and `foundation/docs/` into `docs/`, and `remake/tools/` (tracked parts)
   and `foundation/tools/` into `tools/`. Delete the tracked duplicate `remake/scripts/fetch_deps.sh`
   and `remake/scripts/r2.sh`, which points at a path that does not exist. Move `remake/assets/`,
   `remake/tests/parity-baseline/` and `remake/tests/npr-evidence/` to `research/evidence/`, and fix what
   reads them. The local untracked contents of `remake/tools/` stay where they are, and the build must
   keep finding its toolchains: report any path you had to keep, so stage 6 can handle it.
3. **Regroup `src/`** as in section 2. Update includes and CMake. Give the two `arena_camera.h` different
   names. No logic edits.
4. **Split `main.cpp`.** Move blocks into `src/app/`, one block per commit: options and usage, scene
   assembly, combat audio sink, match tick and views, render and capture hooks, frame loop. Code moves;
   behaviour does not. `tests/controller_scene_lifetime_test.cpp` and `tests/windows_startup_smoke.cpp`
   compile `main.cpp` into their own translation unit, so keep that working or port them to link
   the new app library. Stop when what is left in `main.cpp` is entry points and wiring. If a block
   cannot move without changing logic, leave it there and say so.
5. **Archive docs.** Move to `docs/archive/`: `PILOT-SEAM.md`, `PILOT-EVIDENCE-CONTRACT.md`, `RENA0-*`,
   `FULL-REPLACEMENT-PLAN.md`, `FRONTEND-PLAN.md`, `port-from-mvp-plan.md`, `roadmap.md`, `placeholders.md`,
   and `docs/reports/ginkiha-*`, `docs/reports/fighter-*`. Do not rewrite their text. Add
   `docs/PATHS.md` mapping old paths to new ones. Rewrite `README.md` for the new layout. Update `AGENTS.md`
   and `docs/DIRECTION.md` so every path they name exists, keeping their rules intact. Append one entry to
   `docs/DIRECTION-STATUS.md`. In `docs/QUESTIONS.md`, add the open question that `research/recomp/` has
   3,169 tracked files while `AGENTS.md` forbids committing it.
6. **Do not do this one.** List in your report what could be deleted from disk and its size: stale folders
   under `build/`, and what remains of `remake/` locally.

## 5. Checks for every stage

All of these, from the root once stage 1 is done:

- `./build.sh linux`, exit 0, then `ctest --test-dir build/linux -j4 --timeout 400`: same pass count as the
  baseline, except tests the stage deliberately renamed. No new skips.
- Every fingerprint from section 3 is identical. A difference stops the work.
- `python3 tests/release_flow_check.py build/linux/daybreak Higurashi-Daybreak --recipe 2v2 --fighters 4` and the
  same with `--recipe 4p`.
- `./build.sh windows` and `./build.sh web`, exit 0.
- `sha256sum -c MANIFEST.sha256` passes inside the core folder.
- `git status --short` shows nothing unexpected, and no ignored path is staged.

At the end of stages 1 and 5 also run `scripts/package_linux.sh` and `tests/launcher_test.sh` on its result, and
`git grep -n "remake/foundation\|foundation_demo"` outside `docs/archive/`, `research/evidence/` and
`docs/PATHS.md`. Each remaining hit must be justified in the report.

## 6. Report, and what the review will check

Finish with a report in your last message, not in a new document, with:

1. The last stage finished, and the commit list.
2. Each check's real outcome per stage: counts, exit codes, whether fingerprints matched.
3. Every decision this brief left open, and every place you kept an old path or skipped something.
4. Anything you could not finish, and why.
5. Stage 6's list, with sizes.

The review will repeat these on the final commit, so they must hold:

- `remake/`, `src/game/`, `src/gameplay/`, `src/sim/` are gone from the tree.
- The fingerprints match the baseline, and `MANIFEST.sha256` verifies.
- `git log --follow` still reaches old history for a sample of moved files.
- `git diff b389ca6d --stat -M` shows moves as renames, and the non-rename changes can be explained.
- `git diff b389ca6d -M -- '*.cpp' '*.h' '*.hpp'` shows no logic change outside the `main.cpp` split.
- Every path in `AGENTS.md`, `README.md` and `docs/DIRECTION.md` exists.
- `main` is untouched, and nothing was pushed.
