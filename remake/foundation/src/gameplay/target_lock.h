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
//       (+0x304 = -1) and the player is re-picked by walking (selection + 1) % count,
//       wrapping, skipping unusable candidates, and FUN_00421e30 is called only if the
//       walk landed somewhere different (0x421f580:238);
//     * then, if the selection shares player 0's team, +0x848 is **re-pinned to 0xb4
//       every tick**; otherwise a non-zero +0x848 is decremented. The hold therefore
//       reads as "the selection is currently on an ally" and survives indefinitely;
//     * and the pulse protection at 0x421f580:218 — the re-pick is suppressed while
//       the 15-tick pulse is still running, so a fresh switch is not undone instantly.
//
//   FUN_0063c2a0 (0x63c2a0) — the command dispatcher that reaches both writers: command
//   0x2a calls FUN_00421e30 (the cycle) and command 0x2b calls FUN_00421f30 (the direct
//   set). The same dispatcher owns the separate +0xaecc/+0xaed0 lock pair (commands
//   0x20/0x21 set and clear it); what that pair represents is NOT recovered and is
//   deliberately not modelled here.
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

#include <cstdint>

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
    // the config. `fighterCount` is clamped to [2, 4] like Match::reset does.
    void reset(int fighterCount, const int side[4]) {
        m_count = fighterCount < 2 ? 2 : (fighterCount > 4 ? 4 : fighterCount);
        for (int i = 0; i < 4; ++i) {
            m_side[i] = side[i];
            m_locks[i] = TargetLock{};
        }
    }

    int  fighter_count() const { return m_count; }
    int  target(int owner) const { return lock_at(owner).target; }
    bool valid_target(int owner) const { return lock_at(owner).valid(); }
    bool switched(int owner) const { return lock_at(owner).switched; }
    int  pulse(int owner) const { return lock_at(owner).pulseTicks; }
    int  hold(int owner) const { return lock_at(owner).holdTicks; }

    // "The selection is an ally" is the recovered meaning of a live +0x848 hold; the
    // renderer reads it as the blink phase (FUN_00643230:78).
    bool holding_ally(int owner) const { return lock_at(owner).holdTicks > 0; }

    bool is_ally(int owner, int index) const {
        if (owner < 0 || owner >= m_count || index < 0 || index >= m_count) return false;
        return m_side[index] == m_side[owner];
    }

    // A target is usable when it is in range, is not the owner, and is alive. Allies
    // pass: aiming at one is a mechanic, attacking one is not (see Match::melee_target).
    bool targetable(int owner, int index, const bool alive[4]) const {
        if (owner < 0 || owner >= m_count) return false;
        if (index < 0 || index >= m_count || index == owner) return false;
        return alive[index];
    }

    // FUN_00421f30 (0x421f30): the direct-set writer. A valid index adopts the target
    // with a fresh pulse and a cleared hold; an out-of-range index clears the lock and
    // changes nothing else — never an out-of-range index is ever stored.
    void set_target(int owner, int index, const bool alive[4]) {
        if (owner < 0 || owner >= m_count) return;
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
    void cycle_enemy(int owner, bool forward, const bool alive[4]) {
        if (owner < 0 || owner >= m_count) return;
        const int current = lock_at(owner).target;
        const int anchor = current == kNoTarget ? owner : current;
        const int next = walk(owner, anchor, forward, /*hostileOnly=*/true, alive);
        if (next == kNoTarget || next == current) return;
        adopt(owner, next, false);   // an enemy selection carries no hold (0x421f30)
    }

    // Hold: aim at an ally (input.h — "hold = aim ally"). Picks the first living ally
    // in index order, so the gesture is deterministic and repeatable, and arms the ally
    // hold FUN_00421e30 writes at 0x421e30:22.
    void select_ally(int owner, const bool alive[4]) {
        if (owner < 0 || owner >= m_count) return;
        for (int i = 0; i < m_count; ++i)
            if (targetable(owner, i, alive) && is_ally(owner, i)) { adopt(owner, i, true); return; }
    }

    // One maintenance tick, run before the fighters update. Order matches
    // FUN_0041f580: the validity fallback first (0x421f580:216-241), then the ally-hold
    // pin and countdown (242-248), then the pulse decrement (FUN_004201a0).
    void step(const bool alive[4]) {
        for (int i = 0; i < m_count; ++i) m_locks[i].switched = false;

        for (int i = 0; i < m_count; ++i) {
            if (!targetable(i, m_locks[i].target, alive)) {
                // FUN_0041f580:229-240: clear, then re-pick by an index walk that only
                // commits when it lands somewhere new. A VALID lock never reaches this
                // branch, so distance can never take a lock away.
                const bool hadSelection = m_locks[i].target != kNoTarget;
                const int anchor = hadSelection ? m_locks[i].target : i;
                m_locks[i].target = kNoTarget;
                const int next = walk(i, anchor, /*forward=*/true, /*hostileOnly=*/true,
                                      alive);
                // Replacing a target that just died or left is a switch and raises the
                // recovered pulse. Acquiring the FIRST selection is not: nobody pressed
                // anything, and pulsing every fighter's ring at round start would be a
                // lie the HUD then animates. The original's writer is the same one in
                // both cases (0x421f580:239 calls FUN_00421e30), so this is a port rule.
                if (next != kNoTarget && next != anchor)
                    hadSelection ? adopt(i, next, false) : acquire(i, next);
            }
            TargetLock& l = m_locks[i];
            if (l.target != kNoTarget && is_ally(i, l.target)) {
                l.holdTicks = kAllyHoldTicks;              // FUN_0041f580:243-244
            } else if (l.holdTicks > 0) {
                --l.holdTicks;                             // FUN_0041f580:246-247
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

    // Taking the FIRST selection: the index is set, but nothing pulses and no switch is
    // reported because no gesture happened (see step()'s fallback).
    void acquire(int owner, int index) {
        TargetLock& l = m_locks[owner];
        if (index != kNoTarget) { l.target = index; l.holdTicks = 0; }
    }

    // The deterministic candidate walk: start next to `anchor` and wrap, skipping
    // unusable candidates, for at most one full lap (FUN_0041f580:231-237).
    int walk(int owner, int anchor, bool forward, bool hostileOnly,
             const bool alive[4]) const {
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
    int         m_side[4] = {0, 0, 0, 0};
    TargetLock  m_locks[4];
};

}  // namespace gameplay