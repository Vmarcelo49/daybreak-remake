# Owner exceptions to the freeze

The freeze list in [`../AGENTS.md`](../AGENTS.md) is the default. Work outside it
is allowed **only** through an entry here, written by the repo owner. An entry
without a date or an expiry is not an exception.

**State on 2026-10-30:** the freeze ended with M5, so this file is no longer needed for product
work. The rows below name hand-written combat files that no longer exist and stand as history.

| ID | Date | Expires | Scope (what is allowed, which files) | Why | Owner |
|---|---|---|---|---|---|
| Q23 | 2026-10-29 | 2026-10-30 | Rena+0 powered projectile row 8 → explosion row 10 only: `remake/foundation/src/gameplay/projectile_behavior.h` and associated projectile tests | Restore and verify the sourced wall-triggered explosion for the powered charge | Repo owner (explicitly authorized agent to record) |
| Q24 | 2026-10-29 | 2026-11-05 | Reaction rows 104/105/204/205 only: `remake/foundation/src/gameplay/reaction_motion.h`, the delayed-seed path in `fighter.{h,cpp}`, and their regression tests | Owner ordered the latent-row implementation after the audit: the rows are unreachable from any shipped Rena+0 contact, so no pilot fixture can require them | Repo owner (explicitly ordered in session; agent records) |
| Q25 | 2026-10-29 | 2026-11-05 | Item 001 projectile parameters 40/60/70/90/130/140 only: `remake/foundation/src/gameplay/projectile_behavior.h` plus the projectile tests | Owner-approved scoped exception to complete the remaining recovered projectile frame data (rows 4/6/7/9/13/14); the Q23 exception covered only row 8→10 | Repo owner (approved in session; agent records) |
| Q26 | 2026-10-29 | 2026-11-29 | Shared knockdown/tech/get-up system: `remake/foundation/src/gameplay/fighter.{h,cpp}`, reaction/recovery scripts and their tests, per the staged plan in `docs/reports/knockdown-getup-2026-10-29.md` | Owner named the missing ground-recovery system as a blocker for the "Rena+0 is perfect" claim and authorized the full staged plan | Repo owner (explicitly authorized in session) |

## Rules

- One row per exception. No umbrella entries ("continue the port", "character
  work") — the scope names the files or paths the exception covers.
- When an entry expires, the work stops. Renew it explicitly as a new row; do not
  extend it in place.
- An exception never relaxes the hard rules, the full diff review, the evidence
  tiers, or the original-binary rules.
- If a task feels necessary and no unexpired row covers it, it belongs in
  [`QUESTIONS.md`](QUESTIONS.md), not in a new row written by the agent.

Task list and work reports: [`DIRECTION-STATUS.md`](DIRECTION-STATUS.md).
