// gameplay/match.cpp — see match.h for the order this reproduces and why.
#include "gameplay/match.h"

namespace gameplay {

void Match::reset(const MatchConfig& config, const xm::Model* model[4], xm::Controller* anim[4],
                  const xm::Model* tamaMesh, const game::physics::ModelIndex* tamaIndex,
                  const game::physics::MovementCollision* movementCollision) {
    m_config = config;
    m_tamaMesh = tamaMesh;
    m_tamaIndex = tamaIndex;
    m_movementCollision = movementCollision;

    m_config.fighterCount = config.fighterCount < 2 ? 2 : (config.fighterCount > 4 ? 4 : config.fighterCount);
    for (int i = 0; i < m_config.fighterCount; ++i) {
        if (m_movementCollision) {
            m_config.spawn[i] = m_movementCollision->resolveSpawn(
                config.spawn[i], config.spawn, static_cast<size_t>(m_config.fighterCount));
        }
        m_fighters[i].clear_stats();
        m_fighters[i].set_battle_rates(config.healthPercent, config.gaugePercent);
        if (model[i]) m_fighters[i].init(model[i], anim[i], m_config.spawn[i], config.facing[i]);
        else         m_fighters[i].reset(m_config.spawn[i], config.facing[i]);
        // init() resets these, so the launch-time injection follows it (scenes.cpp:546-549).
        m_fighters[i].set_hypermode(config.hyper[i]);
        m_fighters[i].set_hyper_gauge(config.startGauge[i]);
        m_fighters[i].set_hp(config.startHP[i]);
        // Before init()/reset(), which size the magazines from it.
        m_fighters[i].set_weapon(config.weapon[i]);
    }
    m_shots.clear();
    m_locks.reset(m_config.fighterCount, m_config.side);
    m_economy.reset();
    m_economy.set_round_rules(config.timeLimit, config.balloonSize);
}

void Match::liveness(bool out[4]) const {
    for (int i = 0; i < 4; ++i) out[i] = m_fighters[i].is_alive();
}

void Match::cycle_locked_target(int fighter, bool forward) {
    if (fighter < 0 || fighter >= m_config.fighterCount) return;
    bool alive[4];
    liveness(alive);
    m_locks.cycle_enemy(fighter, forward, alive);
}

void Match::lock_ally_target(int fighter) {
    if (fighter < 0 || fighter >= m_config.fighterCount) return;
    bool alive[4];
    liveness(alive);
    m_locks.select_ally(fighter, alive);
}

int Match::melee_target(int fighter) const {
    if (fighter < 0 || fighter >= m_config.fighterCount) return kNoTarget;
    bool alive[4];
    liveness(alive);
    // The locked target when it is a living hostile (FUN_00421f30's +0x304). Allies are
    // excluded here unconditionally: an ally may be aimed at, never attacked.
    const int locked = m_locks.target(fighter);
    if (m_locks.targetable(fighter, locked, alive) && !m_locks.is_ally(fighter, locked))
        return locked;
    // Otherwise, and only otherwise, proximity picks: nearest living hostile. This is
    // what keeps a fighter attacking while it is holding an ally lock, and it can never
    // reach an ally because the hostile test is on the same line as the lock test.
    float nearest = 1.0e30f;
    int victim = kNoTarget;
    for (int j = 0; j < m_config.fighterCount; ++j) {
        if (m_locks.is_ally(fighter, j) || !m_fighters[j].is_alive()) continue;
        const glm::vec3 d = m_fighters[j].position() - m_fighters[fighter].position();
        const float distance = d.x * d.x + d.z * d.z;
        if (distance < nearest) { nearest = distance; victim = j; }
    }
    return victim;
}

MatchFrame Match::step(const fnd::input::PlayerState* p1Input,
                       const fnd::input::PlayerState* p2Input, double dt) {
    const fnd::input::PlayerState* inputs[4] = {p1Input, p2Input, nullptr, nullptr};
    return step(inputs, dt);
}

MatchFrame Match::step(const fnd::input::PlayerState* inputs[4], double dt) {
    MatchFrame out;
    m_economy.tick(dt);   // scenes.cpp:610

    // Maintain the per-fighter locks first: FUN_0041f580 does its validity fallback and
    // ally-hold pin before anything reads the selection, and the fighters below read it
    // on this same tick. This snapshot is the liveness as of the tick's START; `alive`
    // further down is re-read after the fighters move, which is what the economy needs.
    bool aliveAtStart[4];
    liveness(aliveAtStart);
    m_locks.step(aliveAtStart);

    // Each fighter faces, aims and shoots at ITS OWN locked target (FUN_00421f30's
    // +0x304), which is what lets two players hold independent locks. Panel order still
    // decides the update order, so a two-fighter match keeps the reference's P1-then-P2
    // asymmetry. A lock naming an ally is passed through as-is: that is the hold gesture.
    for (int i = 0; i < m_config.fighterCount; ++i) {
        const int target = m_locks.target(i);
        m_fighters[i].update(inputs ? inputs[i] : nullptr,
                             (target != kNoTarget && target < m_config.fighterCount)
                                 ? &m_fighters[target] : nullptr,
                             dt, m_movementCollision);
    }

    // Melee evaluates EVERY hostile in the swing volume, not one chosen opponent: a
    // swing that clips two people should connect with both, and the per-victim hit set
    // stops either from being hit twice by the same swing. Ally exclusion is the filter
    // below, which is the single place that rule lives (projectile.h has the same one).
    for (int i = 0; i < m_config.fighterCount; ++i) {
        for (int j = 0; j < m_config.fighterCount; ++j) {
            if (i == j) continue;
            if (m_config.side[i] == m_config.side[j]) continue;      // allies excluded
            if (!m_fighters[j].is_alive()) continue;
            if (m_fighters[i].already_hit_this_swing(j)) continue;   // once per swing
            if (m_fighters[i].try_melee_hit(m_fighters[j], m_movementCollision)) {
                m_fighters[i].note_melee_hit(j);
                out.meleeHit[i] = true;
                out.meleeVictim[i] = j;
            }
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
        if (eco.respawned[i]) {
            const glm::vec3 spawn = m_movementCollision
                ? m_movementCollision->resolveSpawn(m_config.spawn[i], m_config.spawn,
                                                    static_cast<size_t>(m_config.fighterCount))
                : m_config.spawn[i];
            m_config.spawn[i] = spawn;
            m_fighters[i].reset(spawn, m_config.facing[i]);
        }
        out.respawned[i] = eco.respawned[i];
    }
    out.roundOver = eco.roundOver;
    out.roundOverSide = eco.roundOverSide;
    out.koSting = m_economy.koStingActive();
    return out;
}

}  // namespace gameplay
