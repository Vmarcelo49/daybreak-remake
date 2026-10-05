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
    int       side[4] = {0, 1, 0, 1};
    glm::vec3 spawn[4]  = {glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f)};
    float     facing[4] = {0.0f, 3.14159f, 0.0f, 3.14159f};
    Hypermode hyper[4]  = {Hypermode::Friendship, Hypermode::Oyashiro,
                           Hypermode::Friendship, Hypermode::Oyashiro};
    float     startGauge[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    int       startHP[4]    = {FighterConstants::kMaxHP, FighterConstants::kMaxHP,
                               FighterConstants::kMaxHP, FighterConstants::kMaxHP};
    // The selected weapon's parsed data/item/NNN.dat, one pointer per fighter. Borrowed
    // and optional: a null entry keeps the historical shared tuning, which is what the
    // standalone --match trace path relies on. A non-null entry gives that fighter its
    // own magazine sizes, charge thresholds, per-shot costs and volley counts, so two
    // fighters with different weapons genuinely fight differently (issue #9).
    const WeaponDefinition* weapon[4] = {nullptr, nullptr, nullptr, nullptr};
    // The fighter's parsed data/<char>/NN.dat move table, one pointer per fighter.
    // Borrowed and optional like the weapon: a null entry keeps the legacy shared
    // melee swing, while a bound table resolves each swing to the equipped move's
    // own animation set, reach, damage and stun (issue #26).
    const CharacterMoves* moves[4] = {nullptr, nullptr, nullptr, nullptr};
};

// What one frame did, for the trace, the flow and the effect queue.
struct MatchFrame {
    bool koSting       = false;  // economy: KO sting window is running
    bool respawned[4]  = {false, false, false, false};
    bool roundOver     = false;
    // The WINNING side once roundOver (MatchEconomy::roundOverSide; issue #11). -1
    // only before the round ends — a timed round always resolves to a side.
    int  roundOverSide = -1;
    // Issue #11's credits, per fighter: the balloon % a KO added this frame and how
    // many hits landed on an already-down body. Both are already applied to the
    // economy; they are reported so effects/audio/results can key off the event
    // without re-deriving it (the KO credit is one-shot by construction).
    int  koCredits[4]     = {0, 0, 0, 0};
    int  overkillHits[4]  = {0, 0, 0, 0};
    int  shotsSpawned  = 0;      // accepted by the pool this frame
    int  muzzleSparks  = 0;
    bool meleeHit[4]   = {false, false, false, false};  // i hit an opposing fighter this frame
    int meleeVictim[4] = {-1, -1, -1, -1};
    // --- live combat events (issue #16) -------------------------------------------------
    // The simulation reports what happened; audio and effects consume it. Every flag here
    // is an EDGE armed by the transition itself (Fighter::take_swing_start /
    // take_hyper_start, the pool's spawn, the economy's respawn) and drained exactly once,
    // so re-reading a frame cannot replay an event and a fixed 64 Hz tick cannot miss one.
    bool swingStarted[4] = {false, false, false, false};  // i armed a melee swing
    bool shotFired[4]    = {false, false, false, false};  // i's shot was accepted by the pool
    bool hyperStarted[4] = {false, false, false, false};  // i activated hypermode
    bool guardStarted[4] = {false, false, false, false};  // i raised its guard
    // A landed hit's victim was guarding. The port's guard gate is provisional
    // (Fighter::take_damage's 20% block), so this is a port rule, not the original's.
    bool blocked[4]      = {false, false, false, false};
    // Shot -> fighter contacts the pool resolved this frame, in pool order. The melee path
    // reports one victim per attacker above; a shot volley can connect with several
    // fighters in one tick, so this is its own list.
    static constexpr int kMaxShotHits = 8;
    struct ShotHit {
        int  shooter = -1;
        int  victim  = -1;
        bool blocked = false;
    };
    int     shotHitCount = 0;
    ShotHit shotHits[kMaxShotHits];
};

class Match {
public:
    // One-time setup after the models are loaded. `anim` and the tama mesh/index are
    // borrowed and must outlive the match; pass nullptr for a stage that ships no
    // collision_tama.x (shots then fly to expiry — the reference's open-field case).
    // `movementCollision` is borrowed too; collision.x supplies separate movement and
    // ground queries when present. A null pointer preserves historical trace captures.
    void reset(const MatchConfig& config, const xm::Model* model[4], xm::Controller* anim[4],
               const xm::Model* tamaMesh, const game::physics::ModelIndex* tamaIndex,
               const game::physics::MovementCollision* movementCollision = nullptr);

    // The two-input overload preserves the trace path; the roster overload accepts
    // one optional input per configured fighter, in launch order.
    MatchFrame step(const fnd::input::PlayerState* p1Input,
                    const fnd::input::PlayerState* p2Input, double dt);
    MatchFrame step(const fnd::input::PlayerState* inputs[4], double dt);

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
    // True when this fighter's selection is an ally and the recovered hold is live
    // (FUN_00421e30's 0xb4, re-pinned by FUN_0041f580:244).
    bool lock_holds_ally(int fighter) const { return m_locks.holding_ally(fighter); }
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
    // The fighters' current liveness as one 4-wide array. The lock table, the melee
    // victim and the economy all need it, so it is read in one place.
    void liveness(bool out[4]) const;

    Fighter            m_fighters[4];
    ProjectilePool     m_shots;
    MatchEconomy       m_economy;
    TargetLocks        m_locks;
    MatchConfig        m_config;
    const xm::Model*   m_tamaMesh = nullptr;
    const game::physics::ModelIndex* m_tamaIndex = nullptr;
    const game::physics::MovementCollision* m_movementCollision = nullptr;
};

}  // namespace gameplay
