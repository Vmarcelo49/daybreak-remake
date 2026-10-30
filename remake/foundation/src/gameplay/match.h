#pragma once
// gameplay/match.h — the playable match: Scene_Gameplay's update loop, ported.
//
// Why this file exists and where it came from: `remake/src/core/scenes.cpp:609-732`
// is the only place the DX9 remake composes the game's per-frame order, and Phase 2
// has to move that order into the WebGPU path without changing it. The order is the
// whole content of this file:
//
//   1. advance the match clock            (scenes.cpp:610)
//   1b. maintain each fighter's combat lock (FUN_0041f580:216-248) — see target_lock.h
//   2. fighters update in panel order      (679-680 for the 1v1 reference) — P1 sees P2's previous
//      state and P2 sees P1's already-updated state; the reference is asymmetric
//      here and the port keeps it, because facing/lock-on and the Oyashiro burst
//      read the opponent mid-frame
//   3. melee both directions              (683-684)
//   4. drain each fighter's pending shot into the pool, muzzle spark on success
//      (689-696)
//   5. advance shots vs fighters + the stage's tama channel (697-699)
//   6. KO/balloon/respawn bookkeeping     (701-721) — MatchEconomy
//
// Camera target switching (Guard + AttackB, scenes.cpp:644-646) is NOT here: it is a
// camera decision, so it lives with the camera in the demo, reading the same inputs.
// The per-fighter combat target is ALSO not the camera's: gameplay/target_lock.h holds
// one lock per fighter and the camera keeps its own followed-player selection, so two
// players can be locked onto different enemies at the same time (issue #8).
// Rendering is not here either — the fighters expose modelMatrix()/pose() and the
// pool exposes its shots, which is what the foundation renderer consumes.
//
// Determinism: step() is a pure function of (state, inputs, dt). No clock, no RNG,
// no allocation after reset(), and the only iteration is over fixed-size arrays in
// index order — the DX9-vs-foundation trace comparison depends on all of that.
#include <cstdint>
#include <string>

#include <glm/glm.hpp>

#include "gameplay/fighter.h"
#include "gameplay/match_economy.h"
#include "gameplay/simulation_rng.h"
#include "gameplay/projectile.h"
#include "gameplay/target_lock.h"
#include "input/input.h"
#include "physics/raycast.h"

namespace gameplay {

// Everything on_enter injects (scenes.cpp:527-551, 558-560): where the fighters
// stand, which hypermode each carries, and the launch-time state injections the
// visual suite uses to reach a state without a wind-up.
struct MatchConfig {
    int healthPercent = 100, gaugePercent = 100;
    int timeLimit = 0;
    int balloonSize[2] = {100, 100};
    int       fighterCount = 2;
    int       side[kMatchFighterCount] = {0, 1, 0, 1};
    glm::vec3 spawn[kMatchFighterCount] = {glm::vec3(0.f), glm::vec3(0.f),
                                           glm::vec3(0.f), glm::vec3(0.f)};
    float     facing[kMatchFighterCount] = {0.0f, 3.14159f, 0.0f, 3.14159f};
    Hypermode hyper[kMatchFighterCount] = {Hypermode::Friendship, Hypermode::Oyashiro,
                                           Hypermode::Friendship, Hypermode::Oyashiro};
    float     startGauge[kMatchFighterCount] = {0.0f, 0.0f, 0.0f, 0.0f};
    int       startHP[kMatchFighterCount] = {FighterConstants::kMaxHP,
                                             FighterConstants::kMaxHP,
                                             FighterConstants::kMaxHP,
                                             FighterConstants::kMaxHP};
    // The selected weapon's parsed data/item/NNN.dat, one pointer per fighter. Borrowed
    // and optional: a null entry keeps the historical shared tuning, which is what the
    // standalone --match trace path relies on. A non-null entry gives that fighter its
    // own magazine sizes, charge thresholds, per-shot costs and volley counts, so two
    // fighters with different weapons genuinely fight differently (issue #9).
    const WeaponDefinition* weapon[kMatchFighterCount] = {nullptr, nullptr, nullptr, nullptr};
    // The fighter's parsed data/<char>/NN.dat move table, one pointer per fighter.
    // Borrowed and optional like the weapon: a null entry keeps the legacy shared
    // melee swing, while a bound table resolves each swing to the equipped move's
    // own animation set, reach, damage and stun (issue #26).
    const CharacterMoves* moves[kMatchFighterCount] = {nullptr, nullptr, nullptr, nullptr};
};

using MatchFrame = game::BattleFrame;

class Match {
public:
    // One-time setup after the models are loaded. `anim` and the tama mesh/index are
    // borrowed and must outlive the match; pass nullptr for a stage that ships no
    // collision_tama.x (shots then fly to expiry — the reference's open-field case).
    // `movementCollision` is borrowed too; collision.x supplies separate movement and
    // ground queries when present. A null pointer preserves historical trace captures.
    void reset(const MatchConfig& config, const xm::Model* model[kMatchFighterCount],
               xm::Controller* anim[kMatchFighterCount],
               const xm::Model* tamaMesh, const game::physics::ModelIndex* tamaIndex,
               const game::physics::MovementCollision* movementCollision = nullptr);

    // Battle pause (issue #15). The original's pause flag (scene+0x4430) gates its entire
    // battle update — FUN_00634f60 @0x635093-0x6350aa skips the frame counter and every
    // fighter/economy/camera step while it is set — so the port gates its authoritative
    // step the same way: a paused step() does nothing at all (no fighter tick, no economy
    // tick, no respawn clock, no projectile motion, no FX event) and returns an empty
    // frame. `dt` is never consumed and no timer is touched, so paused wall time cannot
    // become catch-up ticks. The host also skips its own per-tick work (frame counter, COM
    // decisions, HUD values) so the presented frame stays frozen; see battle_pause.h.
    void set_paused(bool paused) { m_paused = paused; }

    // FUN_006394c0's push-apart (body_separation.h, V3-45), ON by default — it is recovered
    // behaviour, not a pilot experiment. The acceptance fixtures that deliberately place bodies
    // inside the 60-unit radius, and two choreography tests whose rigs assume overlapping bodies,
    // opt out with a documented reason.
    void set_body_separation(bool on) { m_bodySeparation = on; }
    bool body_separation_enabled() const { return m_bodySeparation; }
    bool paused() const { return m_paused; }

    // The two-input overload preserves the trace path; the roster overload accepts
    // one optional input per configured fighter, in launch order.
    MatchFrame step(const fnd::input::PlayerState* p1Input,
                    const fnd::input::PlayerState* p2Input, double dt);
    MatchFrame step(const fnd::input::PlayerState* inputs[kMatchFighterCount], double dt);

    // ---- per-fighter combat target (gameplay/target_lock.h) ---------------------
    // Each fighter owns a lock on another fighter's INDEX, kept independently of
    // whichever player the camera follows. This is the port of FUN_00421f30's +0x304
    // and FUN_00421e30's ally hold, and it is what facing, shots and the melee victim
    // read. The camera's own target selection (gameplay/arena_camera.h) is separate
    // state and does not move these.
    //
    // Every index in this block is a fighter index — the same one `fighter(i)` takes
    // and the one MatchConfig::side/spawn use — not a panel slot, not a controller slot
    // and not a team. Calls are inert for an out-of-range fighter index.
    int  locked_target(int fighter) const { return m_locks.target(fighter); }
    // True when this fighter's selection is an ally and the UX hold is live. This is
    // the lock layer's port-rule predicate for the tap/hold gestures and the ring —
    // NOT the firing predicate below.
    bool lock_holds_ally(int fighter) const { return m_locks.holding_ally(fighter); }
    // This fighter's aim selection (+0x300): the player index it is aiming at,
    // independent of the combat lock above and of the camera's followed player.
    int  aim_selection(int fighter) const { return m_locks.aim_selection(fighter); }
    // Harness seam (P2-7 charge fixtures): arm a fighter's aim selection so the aim hold the
    // powered shooting gate reads can hold. The scene normally drives this from the lock
    // input, which the offline fixture runner has no way to press; the lock's own rule is
    // reused, so this cannot disagree with the runtime path.
    void cycle_aim_selection(int fighter, bool forward) {
        bool alive[kMatchFighterCount] = {false, false, false, false};
        for (int i = 0; i < kMatchFighterCount; ++i) alive[i] = m_fighters[i].is_alive();
        m_locks.cycle_enemy(fighter, forward, alive);
    }
    // Ticks left in the recovered +0x848 hold for the firing predicate.
    int  aim_hold_ticks(int fighter) const { return m_locks.aim_hold_ticks(fighter); }
    // True when this fighter's aim target is the same fighter player 0 is aiming at
    // (the recovered +0x848 predicate, FUN_0041f580:242-248). For fighter 0 this is
    // self-referential and holds continuously. This — not lock_holds_ally — is what
    // the shooting gate reads.
    bool aim_holds(int fighter) const { return m_locks.aim_holds(fighter); }
    // Ticks left in the recovered 15-tick switch pulse (FUN_00421e30's +0x30c), which
    // the ring reads as a scale and arc advance (FUN_00643230:71-72).
    int  lock_pulse(int fighter) const { return m_locks.pulse(fighter); }
    // Tap (LockSwitch): cycle to the next living enemy. Landed on the only enemy, or
    // with none alive, the lock is left alone.
    void cycle_locked_target(int fighter, bool forward = true);
    // Hold (LockSwitch): aim at an ally, arming the recovered hold.
    void lock_ally_target(int fighter);
    // The melee victim for fighter i: its locked target when that target is a living
    // HOSTILE, otherwise the nearest living hostile. An ally lock never makes a fighter
    // punch its own partner, and it never leaves it unable to attack. A fighter still
    // in its airborne respawn re-entry is skipped: the original's target lock treats
    // [fighter+0xaecb] as "not selectable" (FUN_0041f580 @0x41fe26-0x41fe73).
    int  melee_target(int fighter) const;
    // The same selected-or-fallback aim that supplies locomotion's input bearing
    // (FUN_0041f580:216-241); body yaw may turn independently of this target.
    int  aim_target(int fighter) const;
    void set_primary_listener_fighter(int fighter) {
        if (fighter >= 0 && fighter < m_config.fighterCount) m_primaryListener = fighter;
    }
    // The close-target voice cascade's three latches (+0xaec3/+0xaebe/+0xaeb9) for one
    // fighter, as the per-frame update computes them (FUN_0042e110:30-72) — so from the
    // PREVIOUS tick's state. Private use: Match fills the shooting context from this
    // before each fighter updates. `alive` is the tick's starting liveness.
    ShootingContext::VoiceFlags meleeVoiceFlags(int fighter, const bool alive[4]) const;
    void begin_round_entry();
    void step_round_entry(double dt);

    // ---- per-fighter COM enable (issue #48) -------------------------------------------
    // The port's counterpart of the original's [fighter+0x860], which its battle debug keys
    // clear (F2) and set (F3). The original initializes it to 1 wherever a slot is bound to a
    // battle (FUN_0041efa0:10, FUN_00417200:47) and its AI decision is gated on it
    // (FUN_00421730:10), so this flag is battle state like the lock table, not the host's: it
    // is reset with the match, and a capture reproduces it from the same tick-keyed key
    // script that the rest of the simulation is a function of.
    //
    // The host is the only reader — a COM slot whose flag is clear is fed no input at all
    // instead of its brain's decision (FUN_00421730 gates the AI on the same flag). It MUST
    // only consult it for a slot no controller owns; F3 keeps that invariant (debug_keys.h).
    // Out of range reads the default, so a caller cannot read a flag for a slot that has none.
    bool ai_enabled(int fighter) const {
        return fighter < 0 || fighter >= kMatchFighterCount ? true : m_aiEnabled[fighter];
    }
    void set_ai_enabled(int fighter, bool on) {
        if (fighter >= 0 && fighter < kMatchFighterCount) m_aiEnabled[fighter] = on;
    }

    Fighter&       fighter(int i)       { return m_fighters[i]; }
    const Fighter& fighter(int i) const { return m_fighters[i]; }
    ProjectilePool&       shots()       { return m_shots; }
    const ProjectilePool& shots() const { return m_shots; }
    MatchEconomy&         economy()     { return m_economy; }
    const MatchEconomy&   economy() const { return m_economy; }
    const MatchConfig&    config() const { return m_config; }
    // The stage's movement/ground channel (issue #7), borrowed as passed to reset().
    // Read-only query surface: the COM brain probes it to know which directions the stage
    // allows (gameplay/bot_brain.h). Null keeps the historical no-collision behaviour.
    const game::physics::MovementCollision* collision() const { return m_movementCollision; }

    // Rendering is the caller's: shots()/sparks() expose position, tier and age, which
    // is exactly what the DX9 side drew as unlit cubes (its stand-in for un-RE'd VFX)
    // and what the foundation draws through render/debug_prims.h. Combat hits are
    // reported in MatchFrame so the caller can push effect cards for them.

private:
    // FUN_006394c0: push overlapping bodies apart, half each, once per frame. Called after the
    // melee pass, which is where FUN_00634f60 runs it relative to FUN_00637680.
    void separate_bodies();

    // The fighters' current liveness as one 4-wide array. The lock table, the melee
    // victim and the economy all need it, so it is read in one place.
    void liveness(bool out[kMatchFighterCount]) const;

    bool               m_paused = false;   // issue #15; set_paused above
    bool               m_bodySeparation = true;    // V3-45; set_body_separation above
    // Issue #48's F2/F3 flag. True is the original's initialized value (FUN_0041efa0:10).
    bool               m_aiEnabled[kMatchFighterCount] = {true, true, true, true};
    Fighter            m_fighters[kMatchFighterCount];
    ProjectilePool     m_shots;
    MatchEconomy       m_economy;
    // One stream per match, reset per round: the original's global MT19937.
    SimulationRng      m_rng;
    TargetLocks        m_locks;
    MatchConfig        m_config;
    int                m_primaryListener = 0;
    const xm::Model*   m_tamaMesh = nullptr;
    const game::physics::ModelIndex* m_tamaIndex = nullptr;
    const game::physics::MovementCollision* m_movementCollision = nullptr;
};

}  // namespace gameplay
