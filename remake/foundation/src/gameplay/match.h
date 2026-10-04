#pragma once
// gameplay/match.h — the playable match: Scene_Gameplay's update loop, ported.
//
// Why this file exists and where it came from: `remake/src/core/scenes.cpp:609-732`
// is the only place the DX9 remake composes the game's per-frame order, and Phase 2
// has to move that order into the WebGPU path without changing it. The order is the
// whole content of this file:
//
//   1. advance the match clock            (scenes.cpp:610)
//   2. P1 update, then P2 update          (679-680)  — note P1 sees P2's previous
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
#include "input/input.h"
#include "physics/raycast.h"

namespace gameplay {

// Everything on_enter injects (scenes.cpp:527-551, 558-560): where the two fighters
// stand, which hypermode each carries, and the launch-time state injections the
// visual suite uses to reach a state without a wind-up.
struct MatchConfig {
    int healthPercent = 100, gaugePercent = 100;
    int timeLimit = 0;
    int balloonSize[2] = {100, 100};
    glm::vec3 spawn[2]  = {glm::vec3(0.f), glm::vec3(0.f)};
    float     facing[2] = {0.0f, 3.14159f};
    Hypermode hyper[2]  = {Hypermode::Friendship, Hypermode::Oyashiro};
    float     startGauge[2] = {0.0f, 0.0f};
    int       startHP[2]    = {FighterConstants::kMaxHP, FighterConstants::kMaxHP};
};

// What one frame did, for the trace, the flow and the effect queue.
struct MatchFrame {
    bool koSting       = false;  // economy: KO sting window is running
    bool respawned[2]  = {false, false};
    bool roundOver     = false;
    int  roundOverSide = -1;
    int  shotsSpawned  = 0;      // accepted by the pool this frame
    int  muzzleSparks  = 0;
    bool meleeHit[2]   = {false, false};  // i hit the other fighter this frame
};

class Match {
public:
    // One-time setup after the models are loaded. `anim` and the tama mesh/index are
    // borrowed and must outlive the match; pass nullptr for a stage that ships no
    // collision_tama.x (shots then fly to expiry — the reference's open-field case).
    void reset(const MatchConfig& config, const xm::Model* model[2], xm::Controller* anim[2],
               const xm::Model* tamaMesh, const game::physics::ModelIndex* tamaIndex);

    // One frame, in the reference's order. Either input may be null (the DX9 side
    // passes null for P2, so a scripted-vs-dummy run reproduces it exactly).
    MatchFrame step(const fnd::input::PlayerState* p1Input,
                    const fnd::input::PlayerState* p2Input, double dt);

    Fighter&       fighter(int i)       { return m_fighters[i]; }
    const Fighter& fighter(int i) const { return m_fighters[i]; }
    ProjectilePool&       shots()       { return m_shots; }
    const ProjectilePool& shots() const { return m_shots; }
    MatchEconomy&         economy()     { return m_economy; }
    const MatchEconomy&   economy() const { return m_economy; }
    const MatchConfig&    config() const { return m_config; }

    // Rendering is the caller's: shots()/sparks() expose position, tier and age, which
    // is exactly what the DX9 side drew as unlit cubes (its stand-in for un-RE'd VFX)
    // and what the foundation draws through render/debug_prims.h. Combat hits are
    // reported in MatchFrame so the caller can push effect cards for them.

private:
    Fighter            m_fighters[2];
    ProjectilePool     m_shots;
    MatchEconomy       m_economy;
    MatchConfig        m_config;
    const xm::Model*   m_tamaMesh = nullptr;
    const game::physics::ModelIndex* m_tamaIndex = nullptr;
};

}  // namespace gameplay
