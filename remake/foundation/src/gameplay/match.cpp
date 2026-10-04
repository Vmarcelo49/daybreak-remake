// gameplay/match.cpp — see match.h for the order this reproduces and why.
#include "gameplay/match.h"

namespace gameplay {

void Match::reset(const MatchConfig& config, const xm::Model* model[4], xm::Controller* anim[4],
                  const xm::Model* tamaMesh, const game::physics::ModelIndex* tamaIndex) {
    m_config = config;
    m_tamaMesh = tamaMesh;
    m_tamaIndex = tamaIndex;

    m_config.fighterCount = config.fighterCount < 2 ? 2 : (config.fighterCount > 4 ? 4 : config.fighterCount);
    for (int i = 0; i < m_config.fighterCount; ++i) {
        m_fighters[i].clear_stats();
        m_fighters[i].set_battle_rates(config.healthPercent, config.gaugePercent);
        if (model[i]) m_fighters[i].init(model[i], anim[i], config.spawn[i], config.facing[i]);
        else         m_fighters[i].reset(config.spawn[i], config.facing[i]);
        // init() resets these, so the launch-time injection follows it (scenes.cpp:546-549).
        m_fighters[i].set_hypermode(config.hyper[i]);
        m_fighters[i].set_hyper_gauge(config.startGauge[i]);
        m_fighters[i].set_hp(config.startHP[i]);
    }
    m_shots.clear();
    m_economy.reset();
    m_economy.set_round_rules(config.timeLimit, config.balloonSize);
}

MatchFrame Match::step(const fnd::input::PlayerState* p1Input,
                       const fnd::input::PlayerState* p2Input, double dt) {
    const fnd::input::PlayerState* inputs[4] = {p1Input, p2Input, nullptr, nullptr};
    return step(inputs, dt);
}

MatchFrame Match::step(const fnd::input::PlayerState* inputs[4], double dt) {
    MatchFrame out;
    m_economy.tick(dt);   // scenes.cpp:610

    // Keep panel order stable. Each fighter tracks the nearest living opponent;
    // two-fighter matches therefore retain the reference's P1-then-P2 update order.
    int targets[4] = {-1, -1, -1, -1};
    for (int i = 0; i < m_config.fighterCount; ++i) {
        float nearest = 1.0e30f;
        for (int j = 0; j < m_config.fighterCount; ++j) {
            if (i == j || m_config.side[i] == m_config.side[j] || !m_fighters[j].is_alive()) continue;
            const glm::vec3 d = m_fighters[j].position() - m_fighters[i].position();
            const float distance = d.x * d.x + d.z * d.z;
            if (distance < nearest) { nearest = distance; targets[i] = j; }
        }
        if (targets[i] < 0) {
            for (int j = 0; j < m_config.fighterCount; ++j)
                if (i != j && m_config.side[i] != m_config.side[j]) { targets[i] = j; break; }
        }
        if (targets[i] >= 0) m_fighters[i].update(inputs ? inputs[i] : nullptr, &m_fighters[targets[i]], dt);
        else m_fighters[i].update(inputs ? inputs[i] : nullptr, nullptr, dt);
    }

    for (int i = 0; i < m_config.fighterCount; ++i) {
        const int target = targets[i];
        if (target >= 0 && m_fighters[i].try_melee_hit(m_fighters[target])) {
            out.meleeHit[i] = true;
            out.meleeVictim[i] = target;
        }
    }

    for (int i = 0; i < m_config.fighterCount; ++i) {   // scenes.cpp:689-696
        PendingShot shot = m_fighters[i].take_pending_shot();
        if (shot.armed && m_fighters[i].is_alive()) {
            if (m_shots.spawn(shot.pos, shot.dir, shot.tier, &m_fighters[i])) {
                ++out.shotsSpawned;
                m_shots.spawn_spark(shot.pos, 0.2f);   // muzzle flash
                ++out.muzzleSparks;
            }
        }
    }
    m_shots.update(dt, m_fighters, m_config.fighterCount, m_tamaMesh, m_tamaIndex,
                   m_config.side); // scenes.cpp:697-699; allied fighters are not projectile targets

    bool alive[4] = {true, true, true, true};
    for (int i = 0; i < m_config.fighterCount; ++i) alive[i] = m_fighters[i].is_alive();
    const MatchStepResult eco = m_config.fighterCount == 2
        ? m_economy.update(alive) : m_economy.update(alive, m_config.side); // port team extension
    for (int i = 0; i < m_config.fighterCount; ++i) {
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
