# Phase 0 — frozen DX9 reference bank

> Banked before the WebGPU cutover as historical behavioral evidence. The DX9
> tree and `remake/build.sh` were deleted in Phase 5; `regen.sh` is preserved as
> provenance, not a runnable recipe. The original game's appearance references
> are the prints under [`remake/docs/reference/`](../../docs/reference/README.md).
> The bank can still verify claims against its committed artifacts, but it
> cannot produce new DX9 output.

Banked 2026-10-02 on `feat/webgpu-groundwork` at `320a8263`, using
`remake/build/daybreak.exe` sha256
`847c2f8405c8216bb2d6d5ba7059e394e302eb607b3004da367388ee6e7948d6`.
The bank contains 33 cases / 36 captures. Its verdict applies only to the
captured cases; it does not establish coverage of every stage, fighter,
costume, weapon, or effect.

## Contents

- `regen.sh` — the old regeneration recipe; it requires the deleted DX9 build
  and visual-suite scripts. It records the exact commands used before cutover.
- `manifest.tsv` — case, command, exit status, frame, file, byte size and
  sha256; hashes cover the committed capture files.
- `captures/` — 36 reference PNGs at 200×150, PNG8, 530,149 bytes total.
  These are framing/HUD-layout evidence, not full-resolution pixel-fidelity
  references.
- `logs/<case>.log` — console output for the banked runs; includes bundle
  loads, draw counts, camera probes and screenshot lines.
- `logs/dat-<nn>.log` and `logs/asset-*.log` — archived bundle inventories
  and selected asset byte-count probes.
- `scripts/` — the bank's P1 input scripts. Older recipes referred to scripts
  under the removed `remake/tests/visual/`; only scripts still present here
  remain in the current tree.

`captures-full/` was gitignored scratch, not part of the bank; it is not
regenerable from the current tree.

## Reading the captures

| Capture | Historical evidence and limit |
|---|---|
| `title-100.png` | Not the main menu: the DX9 scene named `title` drew only `data/select/bg00.cnv`, the shared select-panel background. The original's shrine title menu is `remake/docs/reference/title-menu.webp`; the capture is historical evidence of the old scene, not title-screen parity. |
| `gameplay-default.png`, `gameplay-school.png` | DX9 versus idle on its hardcoded stage21 (schoolyard night); `gameplay-school` varies the spawn/viewpoint, not the stage. |
| `fighter-p1-*`, `fighter-p2-*` | Four fighters reachable through the old CLI; the P2 cases changed camera target with a script and are not additional character coverage. |
| `fighter-bind.png` | DX9 bind pose plus the old mesh/texture survey in its log. The removed DX9 loader bound zero animation sets. |
| `stage-part-00..06.png` | The seven isolated stage21 parts available through the old `DAYBREAK_ONLY` diagnostic. |
| `hud-*` | Archived old HUD states: dash, shot tiers, hypermode, low HP and KO. |
| `action-melee.png`, `action-jump.png`, `action-guard.png` | The old stand-in states. They do not represent complete original move/animation coverage. |
| `action-heavy.png` | Retired stand-in evidence (issue #10): the old heavy action is not an original-game move. Retained only to document what was banked. |
| `camera-alt.png` | Shows that the old camera height/distance override path worked. |

The old CLI clamped `-p1`/`-p2` to four models: Rika, Takano, Akane and Rena.
The bank includes both player camera roles for those four, not the full roster.
The fighters in this bank use the slots that its old fixed-model flags loaded;
these are not a bank of fully validated character+weapon combinations.

## Historical reproducibility

A full replay on 2026-10-02 with the same DX9 binary reproduced all 36 capture
sha256 hashes. Three later spot checks also matched. Logs can differ in their
wall-clock `fps=` line; the image artifacts remained byte-stable. This is a
historical repeatability result, not a current runnable test.

The removed recipe expected a rebuilt `remake/build/daybreak.exe`, Wine,
ImageMagick and Xvfb, with game data supplied through `$GAME_DIR`. To investigate
a new legacy run, use the `pre-webgpu-cutover` tag (`37ed31d`) in a separate
scratch checkout; do not overwrite or regenerate this archive from the WebGPU
tree. The bank's hashes can still be checked against its `manifest.tsv`.

## Coverage limits at cutover

These are limits of the old binary/CLI, not claims about the current product:

1. No stage selector: the DX9 scene hardcoded stage21. Other stages,
   stage-specific spawns/BGM and the stage-select screen were not banked.
2. `-p1`/`-p2` reached only four fixed fighter models. The remaining roster,
   most costumes, weapon selection and 2v2 were not banked.
3. `-scene` special-cased `title`; opening, mode select, character select and
   bootstrap scenes were not directly selectable from the CLI.
4. There were no isolated effect/weapon spawn flags; effects appeared only
   through combat, and the DX9 remake had no weapon models.
5. Fighter models bound zero animation sets, so action captures are not
   animation-frame evidence; the physical-keyboard F2 diagnostic was not
   scriptable headlessly.
6. `TACTICS`, `LOCK` and `PAUSE` input-script tokens were parsed but not wired
   to their namesake actions.
7. The custom `-asset` boot variant was not banked.
8. HP/gauge and camera environment controls were sampled, not swept; mesh/debug
   diagnostics were log-only.
9. `daybreak01.dat` appeared in an inventory but was not in the executable's
   six-bundle load list.
10. All banking evidence was Wine + RADV/Xvfb, not a real Windows/vendor-driver
    run; host gamepad state was neutralized for captures.

A missing capture is not evidence of a match. For current product status use
[`remake/foundation/docs/RELEASE-CHECKLIST.md`](../../foundation/docs/RELEASE-CHECKLIST.md);
for current animation selectors use
[`remake/foundation/docs/ANIMATION-SETS.md`](../../foundation/docs/ANIMATION-SETS.md).
