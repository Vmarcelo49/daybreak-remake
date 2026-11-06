# Current project direction

Higurashi Daybreak Remake is playable. Development now improves the game through
owner requests and concrete issues, not a milestone-gated per-character port.
Open issues on GitHub are the current bug list; the owner sets priorities.

## Combat architecture

The attributed, vendored Ginkiha reference simulation in `src/battle/core/` is the
only combat authority. It runs through the `src/battle/` wrapper; rendering, HUD,
audio and other systems consume the battle view. Do not revive the deleted
hand-written per-character combat path. Changes to the core must be narrow,
attributed and recorded in `src/battle/core/PATCHES.md`.

Characters and weapons are bound together: use character+weapon combinations
when testing combat. The research corpus remains in this repository as independent
evidence; it is not game code and does not establish runtime parity by itself.

## Evidence and verification

A successful build is not a gameplay verification; a capture of our build is not
an observation of the original; a skipped test is not a pass. Report the tests
actually run and their limitations. Original-runtime parity is not established:
claims about the original must identify their evidence and scope. A perfectly
verified individual combo is not a prerequisite for ongoing product work. The
evidence tiers and safety rules remain in `AGENTS.md`.

Use `DEVELOPMENT.md` for builds, tests and code organization. Historical plans,
pilot acceptance contracts and the old status log live under `docs/archive/`;
they do not authorize work or impose approvals on current development.
