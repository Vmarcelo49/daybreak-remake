# Orchestrating subagents on this repo — the playbook that worked

This is a record of how the #10–#25 batch and the bug-gathering round that followed were
run: one coordinator agent, one durable subagent per issue, one git worktree per issue, and
every claim verified by the coordinator before it reached `main`. It is written so a future
session (or a human) can reproduce the shape without re-deriving it.

The short version: **the coordinator's job is not to write the code, it is to control the
information each worker gets, and to refuse to believe a report until it is reproduced.**

---

## 1. Shape of the run

```
human ──► coordinator (long-lived, owns main, pushes, closes issues)
              │
              ├─ subagent A ── worktree/branch ── issue #N  ──► report ──► coordinator verifies ──► merge
              ├─ subagent B ── worktree/branch ── issue #M  ──► report ──┘
              └─ subagent C (spawned fresh when A's context is exhausted, pointed at A's landed evidence)
```

* **One issue = one branch = one worktree = one subagent.** Never two issues in one branch:
  it makes the rebase surface unreadable and hides which change broke what.
* **Concurrency 1–2.** Two is the sweet spot: enough overlap that a merge is always ready,
  few enough that the coordinator can still read every diff. Three is possible but only when
  the third is a small defect fix that touches disjoint files.
* **The coordinator keeps `main`.** Workers never push, never rebase `main`, never merge.
  They commit on their branch and report; the coordinator rebases, verifies, merges, pushes.

## 2. What goes into a per-issue brief

Every brief is self-contained (the subagent does not see the coordinator's conversation) and
contains, in this order:

1. **The worktree and branch**, plus the isolation sentence: *"never write to
   `<primary checkout>` or the other worktrees (`X`, `Y`); no push, no rebase, no merge."*
2. **The setup already done for it** — `third_party/` hardlinked, the game install symlinked
   at the worktree root, the build pre-warmed — so its first minutes are not spent on setup.
   State the exact run command and the failure mode of getting it wrong (e.g. a relative
   `--install` fails as `cannot read data/item/001.dat`).
3. **What to read first**, by name: the issue (`gh issue view N`), `AGENTS.md`, the decisions
   doc, the roadmap section that owns the area, and any prior write-up of the same subsystem.
4. **The recovered evidence the coordinator already has**, with addresses. This is the single
   highest-value part of the brief: it converts a research task into an implementation task.
   Say explicitly when something is *not* recovered, and forbid inventing it.
5. **Scope and non-scope.** What to implement, what to leave alone (other owners' areas), and
   which decisions are the human's.
6. **Hard constraints**: full `git diff` + `git diff --cached` before every commit; no game
   data / builds / `third_party/` / `research/recomp/`; character+weapon combos, never bare
   fighters; provenance in comments; label port rules as port rules.
7. **The verification the deliverable must contain** — tests that would fail without the fix,
   asset-backed runs with exact commands, builds for every target, and *measurements* rather
   than adjectives ("ticks before/after", "md5 before/after", "peak population N/128").
8. **The report format**, item by item, ending with *"what you could not verify"* and *"what
   you need from me"*.

## 3. Rules that did the heavy lifting

* **Evidence or it did not happen.** Every claim in a report is reproduced by the coordinator:
  rerun the command, re-measure the number, re-read the diff. Several reports were corrected
  this way (a wrong character list in a census, an effect that was "additive" while removing
  light, a camera defect every capture-based check had missed).
* **"Off must be byte-identical."** For renderer work, the default path is pinned by hashes
  against the pre-change build. It caught three accidental pixel moves and made every
  follow-up change safe to land.
* **A negative result is a deliverable.** "The trail bitmaps have no producer in this binary"
  and "the descriptor has no lifetime field" are as valuable as a feature, provided the
  search is described.
* **Stop work that is heading the wrong way, immediately and with evidence.** When a human
  said the toon row was really an outline, the in-flight ramp implementation was stopped
  mid-branch, the read sites were re-derived from the game's own effect blobs, and the fix
  became both (outline pass *and* ramp) — with the correction visible in the commit history.
* **Fresh context beats a long conversation.** When a worker's context runs out mid-issue,
  spawn a new one pointed at the *landed* evidence (docs + commits) rather than resuming the
  exhausted agent. The evidence is the handoff.
* **Tell workers about each other.** Name the shared files (`MatchFrame`, `fighter.*`, the
  settings schema, the scene pass) and who is editing them, so rebases stay mechanical.
* **File the systemic gap, not just the bug.** The camera defect survived because captures
  run with `matchAlpha = 1`; that blind spot became its own issue with three options for
  closing it.

## 4. The prompt template

Paste this and fill the brackets. It is deliberately written as *policy* rather than as a
task list, because the policy is what produces consistent output.

```
You are the coordinator. Work through the per-issue prompts in <path to prompt file>
(<issue list>) one or two at a time. The goal is <one-sentence objective>.

Rules for you:
- Delegate each issue to a durable subagent in its own git worktree and branch
  (worktree per issue, third_party hardlinked, game install symlinked, build pre-warmed).
- The primary checkout's `main` is yours alone: workers never push, rebase or merge.
  Review every diff, rerun the verification yourself, then rebase and merge.
- Do not clobber the parallel work in <worktree/branch>; it is owned by another agent.
- Keep a running per-issue status: implemented / verified / merged / closed, with hashes.

Rules for every brief you write:
- Self-contained: worktree+branch, isolation sentence, what to read first, the evidence
  already recovered (with addresses), scope and non-scope, hard constraints, the exact
  verification required (tests, asset-backed runs, builds, before/after numbers), and the
  report format.
- Require provenance for recovered behaviour and explicit labels for port rules.
- Forbid invention: if something cannot be recovered, the worker must say so and label
  the fallback, never guess silently.
- Require a "what I could not verify" section and an honest list of unresolved criteria.
- Require "off stays byte-identical" for anything touching rendering or simulation defaults.

When a new defect is reported:
- Fix it yourself if it is small, contained and verifiable now.
- File a GitHub issue if it needs multiple iterations, recovered evidence you do not have,
  or an art/design decision — and say which of those applies.
- Ask the human if the *expected* behaviour is ambiguous.
- Group issues with area labels and propose a dispatch order with dependencies.

Report to me: per-issue status, the evidence you reproduced yourself, and anything that
needs my decision.
```

## 5. What the human should keep doing

* **Say when something looks wrong, even vaguely.** "The camera is broken" produced a
  measurement, a root cause and a fix; "the NPR prints barely differ" produced a redo issue
  with acceptance criteria. Vague reports are useful; only ambiguous *expectations* need a
  question back.
* **Correct the naming.** "It should be a character outline" redirected a whole slice.
* **Set the pace explicitly.** "1–2 at a time, no rush" is what keeps the merge queue clean.
* **Ask for the grouping when the list gets long** — the area labels and the wave order are
  what make a 35-issue backlog dispatchable.
