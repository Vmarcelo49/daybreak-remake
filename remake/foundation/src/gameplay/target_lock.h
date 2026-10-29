#pragma once
// gameplay/target_lock.h — the per-fighter combat target ("the reticle"), ported
// from the original's two lock writers and the per-player update that maintains them.
//
// WHY this is separate from the camera: in the remake the camera owns *which player is
// followed* (gameplay/arena_camera.h, the ported ArenaCamera) and this file owns *which
// fighter each fighter attacks and faces*. The original keeps both on one player struct
// — the followed player at +0x300 and the locked combat target at +0x304 — but they are
// distinct fields with distinct writers, and FUN_00421e30/FUN_00421f30 write them
// separately. Keeping them apart here is what lets two players hold independent locks
// (issue #8) instead of sharing one camera-owned selection.
//
// INDICES. Everything in this file is a *fighter index*: a launch-slot index in
// [0, fighterCount), matching MatchConfig::side / MatchConfig::spawn and the `i` in
// `match.fighter(i)`. It is NOT a panel slot (battleLaunch.fighters[i].panel), NOT a
// controller slot (frontend.slots[panel].controller) and NOT a team (MatchConfig::side,
// a 0/1 flag with no index meaning). Those three are distinct spaces that the battle
// scene translates through; none of them may be used as a target index, and a target
// index may not be used as any of the others.
//
// WHAT IS RECOVERED (research/decompiled, addresses as stated):
//
//   FUN_00421e30 (0x421e30) — the *cycle* writer. Stores the newly selected player at
//   +0x300, writes the 15-tick lock pulse at +0x30c, copies the selected player's
//   position (+0x38) and team (+0x308), and **clears the combat target at +0x304**
//   (0xffffffff). It then compares the selected player's team (+0x308) against player
//   0's team: equal → writes the ally hold 0xb4 (+0x848) and plays the target-switch
//   voice cue 0xe, or 0xf when the mode flag +0x845 is set; different → clears the hold
//   and plays cue 0xd. So the same writer produces both the enemy and the ally case,
//   and the team comparison is what distinguishes them.
//
//   FUN_00421f30 (0x421f30) — the *direct-set* writer. With 0 <= index < player count
//   (FUN_0064f010 is the player-count query): stores the index at +0x304, writes the
//   pulse, copies position and team, **clears the ally hold**, and plays cue 0xd. With
//   any other index it stores 0xffffffff and touches nothing else — an invalid index
//   clears the lock rather than latching an arbitrary fighter. That asymmetry is the
//   port's "invalid targets never produce an index" rule, kept exactly.
//
//   FUN_004201a0 (0x4201a0) — the per-tick decrement of the +0x30c pulse, clamped at 0.
//   The ring reads it as both a 1.0 + 0.1*pulse scale and a 9-degree-per-tick arc
//   advance (FUN_00643230:71-72).
//
//   FUN_0041f580:216-248 (per-player update) — the maintenance pass:
//     * a validity predicate over the selection; when it fails the lock is cleared
//       (+0x304 = -1, 0x421fecb) and the player is re-picked by walking
//       (selection + 1) % count, wrapping, skipping unusable candidates, and
//       FUN_00421e30 is called only if the walk landed somewhere different
//       (0x421f580:238). The pass can only ever DROP a lock — FUN_00421e30's own body
//       clears +0x304 too (0x421e96) and no store in the pass writes an index — so a
//       fighter that never selected anything stays unlocked (issue #49). The port keeps
//       the walk as the re-pick of a LOST target, which is what FUN_00421e30's
//       clear-then-re-pick pair does for the original's followed selection;
//     * then, if the selection shares player 0's team, +0x848 is **re-pinned to 0xb4
//       every tick**; otherwise a non-zero +0x848 is decremented. The hold therefore
//       reads as "the selection is currently on an ally" and survives indefinitely;
//     * and the pulse protection at 0x421f580:218 — the re-pick is suppressed while
//       the 15-tick pulse is still running, so a fresh switch is not undone instantly.
//
//   FUN_0063c2a0 (0x63c2a0) — the command dispatcher that reaches both writers: command
//   0x2a calls FUN_00421e30 (the cycle) and command 0x2b calls FUN_00421f30 (the direct
//   set, the port's LockSwitch). Every lock a round ever shows is written here or by the
//   state-gated 0x421fe07 call: FUN_00421f30 is the only writer of a valid +0x304. The
//   same dispatcher owns the separate +0xaecc/+0xaed0 lock pair (commands 0x20/0x21 set
//   and clear it); what that pair represents is NOT recovered and is deliberately not
//   modelled here.
//
// WHAT IS A PORT RULE (provisional, not reverse-engineered):
//   * The candidate walk skips dead fighters and the owner. The original's own walk
//     skips the +0xaecc pair described above; "dead or self" is this port's equivalent,
//     and it matches the DX9 reference's ArenaCamera dead-skip already in the tree.
//   * `cycle_enemy` walks HOSTILES only and `select_ally` picks an ally, which is the
//     reading of input.h's "tap = cycle enemy, hold = aim ally". The original does not
//     gate its cycle on team — FUN_00421e30 happily selects an ally and the hold is what
//     makes that selection dwell — so the tap/hold split here is a port rule. The hold
//     itself is recovered and is maintained per FUN_0041f580:242-248 either way.
//   * With no valid lock the fallback picks the first hostile in index order rather than
//     the nearest. The original's fallback is also an index walk, so this stays
//     deterministic; and because a VALID lock is never re-picked, distance never
//     overwrites a lock (issue #8's acceptance criterion).
//
// Determinism: no RNG, no clock, no allocation after construction, fixed-size arrays
// walked in index order.

#include <algorithm>
#include <cstdint>

#include "gameplay/match_economy.h"  // kMinFighters/kMaxFighters

namespace gameplay {

// The original's "no target" value. Both writers store 0xffffffff in FUN_00421f30's
// invalid branch and FUN_0041f580's fallback, and the ring reads +0x304 > -1 to mean
// "this fighter has a valid target" (FUN_00643230:61).
inline constexpr int kNoTarget = -1;

// 0xf — written to the +0x30c pulse by both writers.
inline constexpr int kLockPulseTicks = 15;

// 0xb4 — the ally hold, re-pinned every tick while the selection is an ally
// (FUN_0041f580:244).
inline constexpr int kAllyHoldTicks = 180;

// One fighter's lock state. The three timers are the original's +0x304/+0x30c/+0x848
// kept together because they are read together by the ring and the per-player update.
struct TargetLock {
    // OFFSET NOTE (2026-10-29): the notes below call this +0x304, but the instructions put the
    // ENEMY selection at +0x300 and the ally one at +0x304 — FUN_00421f30 bounds-checks and
    // indexes the same-team list at +0x2f0 (0x421f40, 0x421f7f) while FUN_00421e30 indexes the
    // other-team list at +0x2e0 (0x421e5d, 0x421e7d), and FUN_00634980 fills those two lists by
    // comparing team records (0x634b75-0x634bb8). This field is the enemy selection, so it is the
    // +0x300 one. The label is left as the file has it because the paragraphs below are built on
    // the old naming; PILOT-EVIDENCE-CONTRACT V3-41 carries the address table.
    int  target     = kNoTarget;  // +0x304: locked combat target, a fighter index
    int  pulseTicks = 0;          // +0x30c: ticks left in the switch pulse
    int  holdTicks  = 0;          // +0x848: ally hold, 0 while the selection is hostile
    bool switched   = false;      // the selection changed this tick (drives the pulse)

    bool valid() const { return target != kNoTarget; }
};

// The per-fighter lock table. One entry per fighter, indexed by fighter index; the
// table never stores a panel, controller or team index.
class TargetLocks {
public:
    // `side` is the per-fighter team (MatchConfig::side), copied because team
    // membership decides ally-versus-hostile for the whole table and the caller owns
    // the config. `fighterCount` is clamped to the battle's legal count exactly as
    // Match::reset does; both read the same bounds (match_economy.h).
    void reset(int fighterCount, const int side[kMatchFighterCount]) {
        m_count = std::clamp(fighterCount, kMinFighters, kMaxFighters);
        for (int i = 0; i < kMatchFighterCount; ++i) {
            m_side[i] = side[i];
            m_locks[i] = TargetLock{};
            // FUN_00421670: every fighter's aim selection starts at player 0, and the
            // hold starts at 0 (it pins on the first maintenance tick, since all aims
            // match player 0's). A rematch re-runs this, so no aim survives one.
            m_aim[i] = 0;
            m_aimHold[i] = 0;
        }
    }

    int  fighter_count() const { return m_count; }
    int  target(int owner) const { return lock_at(owner).target; }
    bool valid_target(int owner) const { return lock_at(owner).valid(); }
    bool switched(int owner) const { return lock_at(owner).switched; }
    int  pulse(int owner) const { return lock_at(owner).pulseTicks; }
    int  hold(int owner) const { return lock_at(owner).holdTicks; }

    // "The selection is an ally" is a PORT RULE for the lock/UX layer, not the
    // recovered meaning of +0x848: the original re-pins that word while this
    // fighter's aim-selection target equals player 0's (FUN_0041f580:242-248, with
    // +0x308 a player pointer — see 0x41f580:221), which is a different predicate
    // from "locked onto an ally". Kept because the tap/hold gestures, the ring and
    // both lock suites are built on it; shooting reads aim_holds() below instead.
    bool holding_ally(int owner) const { return lock_at(owner).holdTicks > 0; }

    // --- the aim-selection layer (+0x300), kept distinct from the combat lock ---
    // The original stores the aim selection separately from the combat lock
    // (FUN_00421e30 writes +0x300 and clears +0x304; FUN_00421f30 writes +0x304 and
    // clears the hold). The camera's followed player is a third, independent
    // selection owned by arena_camera.h. None of the three may stand in for another.
    //
    // The aim selection is a fighter index (init 0 for everyone, FUN_00421670), changed
    // only by an explicit selection gesture. It is NOT cleared when the combat lock is
    // lost, and it is NOT the fallback facing pick below — that pick reports a target
    // without storing anything, while this stores without reporting.
    int aim_selection(int owner) const {
        return (owner >= 0 && owner < m_count) ? m_aim[owner] : kNoTarget;
    }
    // Ticks left in the recovered +0x848 hold for the shooting gate, maintained by
    // step() from the same-target comparison below.
    int aim_hold_ticks(int owner) const {
        return (owner >= 0 && owner < m_count) ? m_aimHold[owner] : 0;
    }
    // Word +0x848 != 0 for the firing predicate: this fighter's aim target is the same
    // fighter player 0 is aiming at. For fighter 0 that comparison is self-referential,
    // so it holds continuously — which is why the powered branch is reachable in 1v1.
    bool aim_holds(int owner) const { return aim_hold_ticks(owner) > 0; }

    // Which opponent a fighter with NO lock faces: the maintenance walk's pick — the
    // first living hostile at or after the owner, wrapping (FUN_0041f580:229-237). It
    // reports a TARGET, never a lock: nothing is stored, so no ring turns green and no
    // pulse is raised (issue #49). Match::step feeds it to Fighter::update for facing
    // only. It is not the aim selection above: the fallback is recomputed every tick
    // from liveness, while the aim selection persists until a gesture changes it.
    int fallback_target(int owner, const bool alive[kMatchFighterCount]) const {
        if (owner < 0 || owner >= m_count) return kNoTarget;
        return walk(owner, owner, /*forward=*/true, /*hostileOnly=*/true, alive);
    }

    bool is_ally(int owner, int index) const {
        if (owner < 0 || owner >= m_count || index < 0 || index >= m_count) return false;
        return m_side[index] == m_side[owner];
    }

    // A target is usable when it is in range, is not the owner, and is alive. Allies
    // pass: aiming at one is a mechanic, attacking one is not (see Match::melee_target).
    bool targetable(int owner, int index, const bool alive[kMatchFighterCount]) const {
        if (owner < 0 || owner >= m_count) return false;
        if (index < 0 || index >= m_count || index == owner) return false;
        return alive[index];
    }

    // FUN_00421f30 (0x421f30): the direct-set writer. A valid index adopts the target
    // with a fresh pulse and a cleared hold; an out-of-range index clears the lock and
    // changes nothing else — never an out-of-range index is ever stored. The original
    // clears +0x848 here unconditionally, so the aim hold below is cleared too while
    // the aim selection itself is left alone (0x421f30 never stores +0x300).
    void set_target(int owner, int index, const bool alive[kMatchFighterCount]) {
        if (owner < 0 || owner >= m_count) return;
        m_aimHold[owner] = 0;
        if (!targetable(owner, index, alive)) {
            adopt(owner, kNoTarget, false);
            return;
        }
        adopt(owner, index, false);   // FUN_00421f30:24-26 writes only +0x304
    }

    // Tap: cycle to the next HOSTILE target (input.h — "tap = cycle enemy"). The walk
    // starts at (current + 1) % count and wraps, which is FUN_0041f580:230-237's rule;
    // landing back on the current selection is a no-op, as it is at 0x421f580:238.
    // Port rule: allies are skipped, because aiming at one is the hold gesture.
    // A landing also moves the aim selection: the tap descends from the cycle command
    // (0x2a → FUN_00421e30), which is the only writer of +0x300 besides init.
    void cycle_enemy(int owner, bool forward, const bool alive[kMatchFighterCount]) {
        if (owner < 0 || owner >= m_count) return;
        const int current = lock_at(owner).target;
        const int anchor = current == kNoTarget ? owner : current;
        const int next = walk(owner, anchor, forward, /*hostileOnly=*/true, alive);
        if (next == kNoTarget || next == current) return;
        m_aim[owner] = next;
        adopt(owner, next, false);   // an enemy selection carries no hold (0x421f30)
    }

    // Hold: aim at an ally (input.h — "hold = aim ally"). Picks the first living ally
    // in index order, so the gesture is deterministic and repeatable, and arms the ally
    // hold FUN_00421e30 writes at 0x421e30:22. The ally is also the new aim selection:
    // the original's cycle does not gate on team, so selecting an ally is a selection.
    void select_ally(int owner, const bool alive[kMatchFighterCount]) {
        if (owner < 0 || owner >= m_count) return;
        for (int i = 0; i < m_count; ++i)
            if (targetable(owner, i, alive) && is_ally(owner, i)) {
                m_aim[owner] = i;
                adopt(owner, i, true);
                return;
            }
    }

    // One maintenance tick, run before the fighters update. Order matches
    // FUN_0041f580: the validity fallback first (0x421f580:216-241), then the ally-hold
    // pin and countdown (242-248), then the pulse decrement (FUN_004201a0).
    void step(const bool alive[kMatchFighterCount]) {
        for (int i = 0; i < m_count; ++i) m_locks[i].switched = false;

        for (int i = 0; i < m_count; ++i) {
            // FUN_0041f580:216-241 (research numbering; 0x41fdea-0x41ff7a live) is a
            // maintenance pass over a selection that has GONE BAD, never a first
            // selection. Its branch clears +0x304 (0x421fecb) and ends in FUN_00421e30,
            // whose own body clears +0x304 again (0x421e96); the only store that can make
            // +0x304 valid is FUN_00421f30's (0x421f65), reached from the command
            // dispatcher's LockSwitch command (FUN_0063c2a0 case 0x2b) and the
            // state-gated call at 0x421fe07. A fighter that never selected anything
            // therefore stays unlocked: the port must not invent a lock for it, and the
            // HUD must draw its red ring until a gesture (Match::cycle_locked_target —
            // the LockSwitch tap for a human, the COM brain's own retarget decision for a
            // COM) hands it one. Issue #49.
            if (m_locks[i].target != kNoTarget && !targetable(i, m_locks[i].target, alive)) {
                // FUN_0041f580:229-240: clear, then re-pick by an index walk that only
                // commits when it lands somewhere new (0x421f580:238). A VALID lock never
                // reaches this branch, so distance can never take a lock away.
                const int anchor = m_locks[i].target;
                m_locks[i].target = kNoTarget;
                const int next = walk(i, anchor, /*forward=*/true, /*hostileOnly=*/true,
                                      alive);
                // Replacing a target that just died or respawned is a switch and raises
                // the recovered pulse. The walk skips the anchor by construction (it is
                // untargetable, which is why the branch was taken), so any landing is
                // somewhere new.
                if (next != kNoTarget) {
                    m_aim[i] = next;   // the re-pick calls FUN_00421e30, which stores +0x300
                    adopt(i, next, false);
                }
            }
            TargetLock& l = m_locks[i];
            if (l.target != kNoTarget && is_ally(i, l.target)) {
                l.holdTicks = kAllyHoldTicks;              // FUN_0041f580:243-244
            } else if (l.holdTicks > 0) {
                --l.holdTicks;                             // FUN_0041f580:246-247
            }
            // The aim-layer hold for the firing predicate (FUN_0041f580:242-248 read
            // against +0x308): re-pin while this fighter's aim target is the same
            // fighter player 0 is aiming at, decay otherwise. Indices stand in for the
            // original's actor pointers — slots are stable for a match, so equal indices
            // mean the same actor. No liveness test here, matching the original, whose
            // hold maintenance does not check validity either; a dead aim target simply
            // stops matching once player 0 re-aims.
            {
                const int mine = (i >= 0 && i < m_count) ? m_aim[i] : kNoTarget;
                const int ref = (m_count > 0) ? m_aim[0] : kNoTarget;
                const bool same = mine != kNoTarget && mine == ref;
                if (same) m_aimHold[i] = kAllyHoldTicks;   // 0xb4, the same constant
                else if (m_aimHold[i] > 0) --m_aimHold[i];
            }
            if (l.pulseTicks > 0) --l.pulseTicks;          // FUN_004201a0
        }
    }

private:
    const TargetLock& lock_at(int owner) const {
        static const TargetLock kEmpty{};
        return (owner >= 0 && owner < m_count) ? m_locks[owner] : kEmpty;
    }

    void adopt(int owner, int index, bool ally) {
        TargetLock& l = m_locks[owner];
        if (l.target == index) return;      // no change: no pulse, no hold re-arm
        l.target = index;
        if (index != kNoTarget) {
            l.pulseTicks = kLockPulseTicks; // FUN_00421e30:14 / FUN_00421f30:15
            l.holdTicks  = ally ? kAllyHoldTicks : 0;
            l.switched   = true;
        }
    }

    // The deterministic candidate walk: start next to `anchor` and wrap, skipping
    // unusable candidates, for at most one full lap (FUN_0041f580:231-237).
    int walk(int owner, int anchor, bool forward, bool hostileOnly,
             const bool alive[kMatchFighterCount]) const {
        const int n = m_count;
        int i = anchor;
        for (int steps = 0; steps < n; ++steps) {
            i = forward ? (i + 1) % n : (i - 1 + n) % n;
            if (!targetable(owner, i, alive)) continue;
            if (hostileOnly && is_ally(owner, i)) continue;
            return i;
        }
        return kNoTarget;
    }

    int         m_count = 0;
    int         m_side[kMatchFighterCount] = {0, 0, 0, 0};
    TargetLock  m_locks[kMatchFighterCount];
    // The aim-selection layer (+0x300 per fighter, init 0) and its recovered hold.
    // Parallel arrays — not fields on TargetLock — so the combat-lock struct keeps
    // its tested shape and the two selections cannot be confused in review.
    int         m_aim[kMatchFighterCount] = {0, 0, 0, 0};
    int         m_aimHold[kMatchFighterCount] = {0, 0, 0, 0};
};

}  // namespace gameplay