# Full replacement plan: drop DX9, WebGPU only

> **Historical plan — Phase 5 cutover completed 2026-10-02.** This file records
> the migration proof and what was deliberately retained. It is not a current
> work plan or a source of current product status. For that, use
> [`ROADMAP-PENDING.md`](ROADMAP-PENDING.md) and
> [`RELEASE-CHECKLIST.md`](RELEASE-CHECKLIST.md). The rollback tag is
> `pre-webgpu-cutover` (`37ed31d`).

## 0. Objective and definition of done

The objective was to replace the DX9 + SDL2 product with SDL3 + WebGPU, then
remove the legacy tree and prototypes. The cutover did remove `remake/src/`,
`remake/CMakeLists.txt`, `remake/build.sh`, `remake/cmake/`, the DX9 fixtures,
`webgpu-mvp/`, and `webgpu-spike/`; `remake/foundation/` became the product.
The tag and the bank under `remake/tests/parity-baseline/` preserve historical
evidence, not a second supported build.

The original all-target gate proved too broad for the cutover snapshot. Linux
has a playable release record. Later game-data runs show Windows/Wine reaching
title and battle before a rematch fault, and Web reaching title/live match on a
local `/data` preload rig with software WebGPU; the `?pack=` route fails. Browser
visual parity, hardware browser adapters, and macOS execution are not
established. Read the current checklist before making target claims.

## 1. Rules of the migration (historical)

1. Bank DX9 reference output before deleting its producer; matches claims
   should point to artifacts rather than memory.
2. Port gameplay behind the foundation interfaces before removing the old
   renderer. `glm` replaced D3DX math in the port.
3. Coordinate edits to the legacy source while it exists. At planning time a
   second agent had dirty loader work; the migration stayed in the foundation
   until that handoff ended with Phase 5 deletion. This is not a current
   ownership instruction.
4. Delete prototypes only after their demonstrated capabilities are accounted
   for; keep toolchain and tool payload decisions with the cutover record.

## 2. Preconditions

The `feat/webgpu-groundwork` branch continued from the planned base, the
`pre-webgpu-cutover` rollback tag was created, and the Linux/Wine versus
vignette was green before migration work. A legacy loader handoff was recorded
2026-10-02: the `DAYBREAK_MESH_FLAGS` / `DAYBREAK_ANIM_DEBUG` probes remained
uncommitted and were not staged by the migration; Phase 1–2 work stayed under
`remake/foundation/`. Phase 5 then deleted `remake/src/`.

## 3. Phase 0 — parity banking

Before deletion, 33 cases produced 36 committed 200×150 PNG8 captures
(530,149 bytes), with 47 case logs plus archive inventories and asset probes.
The set and historical replay result are documented in
[`remake/tests/parity-baseline/README.md`](../../tests/parity-baseline/README.md):
a full pre-cutover replay reproduced all 36 hashes. The capture set is now
frozen; the former `regen.sh` requires the deleted DX9 build and visual-suite
scripts.

The proposal's coverage list exceeded what the old CLI could reach. It had no
stage selector (stage21 was hardcoded), only four fixed fighter models, no
weapon models, zero bound animation sets and no isolated effect switch. The
baseline README records the ten gaps. No missing stage, costume or weapon
capture can be treated as evidence of DX9 parity. The pre-cutover grep found
35 files with migration-target APIs; Phase 5 reached zero by deleting that
source tree, not by editing all 35 files in place.

## 4. Phase 1 — foundation-complete (historical evidence)

- Bundle decoding matched the archive-entry oracle on 12,345 entries. The
  extracted tree was found not to be byte-identical to the install; bundle-first
  resolution was retained to match the original's precedence. Cross-implementation
  captures made from tree copies required re-evaluation.
- The CPU Möller–Trumbore raycast had 72 analytic checks and an independent
  float64 cross-check; the measured cost was 5.5 µs/ray on the largest shipped
  camera mesh. The DX9 binary offered no raycast probe, so this was not claimed
  as D3DX output parity.
- Debug primitives were rebuilt in the foundation. The cube capability was
  retained; the open trail/aura/billboard fidelity work remained a separate
  item rather than silently being counted as complete.
- The CJK decision was to use in-process TrueType rasterization; implementation
  and later caption guidance live in the foundation docs.

## 5. Phase 2 — gameplay port (historical quirks, not current status)

Six scripted fighter/projectile cases were compared against the DX9 build:
59 samples × two fighters, worst position delta 0, matching animation-state
names. That is a historical measurement, not proof of general capture parity.
Later testing found Linux/Wine animated frames can differ by compiler math;
`RELEASE-CHECKLIST.md` §3.5 and decision D9 explain why a capture is not a live
run and why the live camera has its own gate.

The port kept some observed DX9-remake behavior during the initial parity phase:
its Guard state was one-way, some constants appeared unreachable, and Kakera's
HP drain rounded to zero at the then-used cadence. Those are historical notes,
not a current bug list. Guard release was later corrected for playable updates;
use the current roadmap/source for state and tuning status. The old camera clamp
also differed from the DX9 remake, deliberately, for the A/B comparison.

## 6. Phase 3 — fidelity

Fidelity work originally compared the foundation against the banked DX9 frames.
The migration record includes those measured snapshots, but they did not make
the unfinished DX9 renderer the appearance specification. See §6a for the
correction.

### 6a. Fidelity target, corrected 2026-10-03

The visual target is the original game's prints in `remake/docs/reference/`,
not the DX9 remake's unfinished frames. The two evidence sources have different
jobs: the banked DX9 output can preserve behavior/trace evidence; the prints
specify original appearance. The original prints exposed differences in camera
framing, HUD art/layout, brightness and the day/night stage variant. The old
RMSE/luminance values in the original plan were measured snapshots against
specific captures, some against the wrong comparison target; do not reuse them
as current results. The current checklist and the reference captures govern
present claims.

A second correction: the foundation's `env.dat` parser matched the original's
reader layout (four header integers from 0x14, then four triples from 0x24,
stride 12). The deleted DX9 remake hardcoded its spawn pair, so it was not a
loader oracle. The later consumer tracing and current spawn status are in
[`ROADMAP-PENDING.md`](ROADMAP-PENDING.md) item A1.

The plan also recorded a cross-platform render invariant correction: measured
Linux/Wine frames were byte-identical only in tested cases, not for every
animated frame. The implementation's math path can differ by an ULP and affect
pixels. Behavioral trace comparisons and visual capture comparisons therefore
serve different gates; see `RELEASE-CHECKLIST.md` §3.5 and D9.

## 7. Phase 4 — netplay (not part of the cutover)

Netplay was explicitly out of scope for replacing the renderer. The historical
proposal required a separate determinism design (delay/rollback, state hashes,
desync handling, and cross-toolchain behavior) before implementation. Current
scope/status is governed by decision D6 and the roadmap, not this old phase
outline.

## 8. Phase 5 — cutover (executed 2026-10-02)

The cutover deleted the old source/build files, launch script, CMake files,
visual fixtures and the two WebGPU prototypes. Local-only DX9 and SDL2 payloads
were removed separately. The old build script was deleted rather than retargeted;
the foundation has its own build script.

The cutover deliberately kept:

- `remake/tests/parity-baseline/` as a frozen DX9 evidence bank;
- `remake/docs/`, especially the original prints, decisions, game spec and
  explicitly historical DX9 records;
- `remake/tools/{asset-tools,hook-tracer}`, shaders, scripts and host tooling.

The D2 reversal is recorded in
[`remake/docs/decisions.md`](../../docs/decisions.md). The deleted DX9 tree
means the old API grep target went to zero by construction. The cutover-era
verification did not establish game-data Web play or macOS execution; later
Windows/Web results are summarized in the current release checklist.

One post-cutover correction was kept in the original plan: its mip attribution
for a DX9-frame difference was wrong. The DX9 remake used single-level textures;
the original's prints remained the appropriate appearance instrument. That
measurement and its correction are historical; use current print comparisons
for new claims.

## 9. Risk register (historical)

The migration-era risks were incomplete parity coverage, CJK text, netplay
determinism, Wine as a Windows proxy and scope creep into story mode. Their
current product consequences have since changed: consult the foundation
roadmap/checklist rather than treating this old register as open actions.

## 10. What this plan deliberately did not do

The cutover did not implement macOS execution, netplay, or story-mode video.
It did not invent gameplay beyond the reverse-engineered remake behavior. The
plan's phases were migration sequencing, not a claim that all original-game
fidelity work was complete. Current status lives in the foundation docs; asset
names and evidence live in
[`remake/docs/ASSET-CATALOG.md`](../../docs/ASSET-CATALOG.md).
