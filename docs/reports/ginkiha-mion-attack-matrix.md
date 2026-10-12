# Ginkiha port — Mion+0/+1/+2 attack matrix

The Mion group (character 1) under the same discipline as the Rena group
(`ginkiha-rena-attack-matrix.md`): **selection**, **execution**, **automated
verification** and **live parity** are four separate claims, and the vocabulary is
defined there. Nothing below claims a status it has not earned; "implemented" never
silently means "verified".

Combos use `Name+N` (weapon index) per AGENTS rule 7. The dispatchers are the port's
`kDispatchIdentity` slot 7 rows, read from the corpus rather than inferred:

| Combo | item | handler (update) | dispatcher (slot 7) |
|---|---|---|---|
| Mion+0 | 002 | 0x004582A0 | 0x0045F4D0 |
| Mion+1 | 004 | 0x00461810 | 0x00467D70 |
| Mion+2 | 035 | 0x0044FA10 | 0x00456030 |

## 1. Melee family (selection + execution)

Mion's melee branch is **common to her three dispatchers**: their melee sections are
the same condition sequence line for line (compared at the 0x15e / 0x154 / 0x155 /
0x12d branches, e.g. `FUN_0045f4d0.c:420-439` vs `FUN_00467d70.c:433-452` vs
`FUN_00456030.c:397-416`), which is why one function serves all three weapons. The
family is *not* Rena's: no 311, no 332, no 334, and the directional kick is **312**.

| Row | Branch (corpus) | Status |
|---|---|---|
| 300 | the neutral/final fallback: `enabled && (gate(300) \|\| (boosted && !ordinaryCombo && state != 320))` | **selection + execution implemented; automated verification** — real input reaches it for all three weapons (fighter_script_test §49) and the synthetic table pins every branch (melee_admission_test) |
| 301 | `state == 300 && normal && gate(301)` — and no 302 follow-up exists for any Mion weapon | same |
| 310 | `z < 0 && enabled && (gate(310) \|\| (boosted && state != 310))` | same (back-held press → 310 for all three) |
| 312 | `x != 0 && enabled && (gate(312) \|\| (boosted && state != 312))` | same (lateral press → 312, never 311) |
| 320 | air: `enabled && (gate(320) \|\| (boosted && state != 320))` | same (airborne press → 320, including from the air-dash row) |
| 330 | `state == 20 && gate(330)`; `(state == 23 \|\| 24) && z < 0 && gate(330)` | same (forward dash → 330) |
| 331 | `state == 20 && x != 0 && gate(331)`; `(state == 23 \|\| 24) && gate(331)` | same (synthetic table pins the dash cross-over) |
| 340 | `(state == 329 \|\| 333 \|\| 44) && enabled && (gate(340) \|\| (boosted && !ordinaryCombo))` | same |
| 341 | `state == 340 && normal && gate(341)` — **all three** Mion weapons (Rena's is weapon 0 only) | same |

`ordinaryCombo` is the corpus's own exclusion set read off the 0x154 branch:
`{300, 301, 302, 340, 341}` (`FUN_0045f4d0.c:420-422`).

**Boosted** is the dispatchers' `byte(+0x845) && word(+0x848)` pair — an armed special
plus its ready flag — inside the branch's `299 < state < 350` window, and it always
requires a melee **contact** (`FUN_0042c7b0() != 0`). The port publishes it from
`m_hyperActive && m_hypermode == Hypermode::Oyashiro`; the ready half is the same
partial mapping the Rena group records (§1 there). The synthetic table covers the
boosted forms including the two `state != <row>` exclusions (a blocked 310 gate must
yield 300, a blocked 320 gate must decline).

## 2. Shooting side (already bound before this matrix)

The four base shot states are bound and were verified earlier (ledger rows): 400/402
taps and 450/460 charges for all three weapons, from `shoot_body_1_{0,1,2}_*`.

**Newly identified gap (recorded, not implemented):** the dispatchers also route the
**walking tap** to Mion's own mobile states — `FUN_0045f4d0.c:309-330` reads the held
axes at state 10 and sends lateral-right/left/back/forward to 0x19b/0x19c/0x19a/0x191
(411/412/410/**401**), falling back to 400. Mion+2 (`FUN_00456030`) has no such branch
at all. The port's `kMionRules` carry only 400/402/450/460, so those mobile taps
currently resolve to the program's plain 400 entry. That is a real shooting-side
pending item; it is *not* covered by the melee slice below and must not be assumed
bound.

## 3. Remaining before acceptance

1. **Mobile tap states** 401/410/411/412 for Mion+0/+1 (see §2) — the bodies exist in
   the bundle (`mion_mobile_ground_shot.hpp`) but are not bound in the port.
2. **0x15e / 360 / 370 for Mion**: her dispatchers target 0x15e (350), 0x168 (360) and
   0x172 (370) from the special/awakened block's air side (`FUN_0045f4d0.c:186-189`),
   and her second charge has no shoot body in scope, so the port keeps `{-1,-1}` for
   that tier and scopes the 350 admission to the Rena group. Unrecovered semantics —
   recorded, not guessed.
3. **Melee execution bodies** (movement/launch rules) for the rows in §1: selection and
   the clip binding are implemented and verified, but the per-row movement bodies
   (e.g. 310's approach, 320's chase parameters) have not been recovered and bound the
   way the Rena group's were.
4. **Live parity** for the whole group — no path holds it; the same environmental
   limitation the Rena matrix records applies verbatim.
