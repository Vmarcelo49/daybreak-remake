# WebGPU port plan — historical handoff

> **Archive, not current status.** This plan was captured on 2026-10-04, at
> the post-cutover point when the foundation host suite had 13 tests. Its
> owner-file lists, pending-work descriptions, and checkpoint are historical;
> implementation has since moved on. The current product is the repository root
> (SDL3 + WebGPU).
>
> Use [`ROADMAP-PENDING.md`](ROADMAP-PENDING.md) for remaining product work,
> [`RELEASE-CHECKLIST.md`](RELEASE-CHECKLIST.md) for release verification,
> [`WEB-DELIVERY-PLAN.md`](WEB-DELIVERY-PLAN.md) for web asset delivery, and
> [`decisions.md`](../../docs/decisions.md) for binding architecture/scope.
> In particular, the Phase 5 cutover is recorded in
> [`FULL-REPLACEMENT-PLAN.md`](FULL-REPLACEMENT-PLAN.md) §8.

## Historical scope and track names

The original plan organized foundation work into four tracks. These labels are
retained because other design notes refer to them; they are not live task lists.

- **R — renderer parity:** techniques, effect passes, decals/materials, and the
  game camera. Current fidelity gaps and evidence are tracked in
  `ROADMAP-PENDING.md` and the renderer/effects documents.
- **U — UI/HUD:** sprite/text infrastructure and composition. The framework and
  playable front end have since grown beyond the original skeleton plan; use
  `FRONTEND-PLAN.md`, `BATTLE-HUD-SPEC.md`, and the pending-work roadmap for
  present behavior and gaps.
- **W — web delivery:** the original handoff described moving from pack-wide
  fetching to per-asset delivery and a prepared-data catalog. Its transitional
  `?pack=` path is not the production path; issue #4's implementation and
  deviations are recorded in `WEB-DELIVERY-PLAN.md`, while `WEB-ASSETS-RUNTIME.md`
  documents runtime constraints and verification.
- **M — media/input:** SDL3 audio and input backends, their harnesses, and
  integration. The original “callers pending” status has been superseded; current
  platform evidence and remaining caveats live in `MEDIA-INPUT.md` and the
  release checklist.

## Continuing boundary

- **macOS has not been executed here.** Keep platform support claims limited to
  the evidence in the target build and release documents. Code portability is
  not execution evidence.
- No game data belongs in the repository; local installs and prepared web data
  remain outside Git.
- The original shared-file ownership and merge-order instructions applied to
  the now-completed cutover. They do not grant or define current edit ownership.

This short record preserves the original track vocabulary and the important
handoff boundary while avoiding the superseded task lists and checkpoint claims
from the full plan snapshot.
