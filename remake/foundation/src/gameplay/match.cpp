// gameplay/match.cpp — see match.h for the order this reproduces and why.
#include "gameplay/match.h"

namespace gameplay {

void Match::reset(const MatchConfig& config, const xm::Model* model[2], xm::Controller* anim[2],
                  const xm::Model* tamaMesh, const game::physics::ModelIndex* tamaIndex) {
    m_config = config;
    m_tamaMesh = tamaMesh;
    m_tamaIndex = tamaIndex;

    for (int i = 0; i < 2; ++i) {
        if (model[i]) m_fighters[i].init(model[i], anim[i], config.spawn[i], config.facing[i]);
        else         m_fighters[i].reset(config.spawn[i], config.facing[i]);
        // init() resets these, so the launch-time injection follows it (scenes.cpp:546-549).
        m_fighters[i].set_hypermode(config.hyper[i]);
        m_fighters[i].set_hyper_gauge(config.startGauge[i]);
        m_fighters[i].set_hp(config.startHP[i]);
    }
    m_shots.clear();
    m_economy.reset();
}

MatchFrame Match::step(const fnd::input::PlayerState* p1Input,
                       const fnd::input::PlayerState* p2Input, double dt) {
    MatchFrame out;
    m_economy.tick(dt);   // scenes.cpp:610

    // Asymmetric on purpose (scenes.cpp:679-680): P1 updates against P2's previous
    // state, P2 against P1's already-updated state. Facing/lock-on and the Oyashiro
    // activation burst read the opponent mid-frame, so the port keeps the order.
    m_fighters[0].update(p1Input, &m_fighters[1], dt);
    m_fighters[1].update(p2Input, &m_fighters[0], dt);

    out.meleeHit[0] = m_fighters[0].try_melee_hit(m_fighters[1]);   // scenes.cpp:683-684
    out.meleeHit[1] = m_fighters[1].try_melee_hit(m_fighters[0]);

    for (int i = 0; i < 2; ++i) {   // scenes.cpp:689-696
        PendingShot shot = m_fighters[i].take_pending_shot();
        if (shot.armed && m_fighters[i].is_alive()) {
            if (m_shots.spawn(shot.pos, shot.dir, shot.tier, &m_fighters[i])) {
                ++out.shotsSpawned;
                m_shots.spawn_spark(shot.pos, 0.2f);   // muzzle flash
                ++out.muzzleSparks;
            }
        }
    }
    m_shots.update(dt, m_fighters, 2, m_tamaMesh, m_tamaIndex);     // scenes.cpp:697-699

    const bool alive[2] = {m_fighters[0].is_alive(), m_fighters[1].is_alive()};
    const MatchStepResult eco = m_economy.update(alive);            // scenes.cpp:701-721
    for (int i = 0; i < 2; ++i) {
        // The reference calls Fighter::reset here; the economy only reports the flag
        // because it owns no positions (see match_economy.h).
        if (eco.respawned[i]) m_fighters[i].reset(m_config.spawn[i], m_config.facing[i]);
        out.respawned[i] = eco.respawned[i];
    }
    out.roundOver = eco.roundOver;
    out.roundOverSide = eco.roundOverSide;
    out.koSting = m_economy.koStingActive();
    return out;
}

}  // namespace gameplay
