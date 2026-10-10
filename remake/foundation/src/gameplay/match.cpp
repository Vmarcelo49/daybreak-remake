// gameplay/match.cpp — see match.h for the order this reproduces and why.
#include "gameplay/match.h"

#include <algorithm>

namespace gameplay {

void Match::reset(const MatchConfig& config, const xm::Model* model[kMatchFighterCount],
                  xm::Controller* anim[kMatchFighterCount],
                  const xm::Model* tamaMesh, const game::physics::ModelIndex* tamaIndex,
                  const game::physics::MovementCollision* movementCollision) {
    m_config = config;
    m_tamaMesh = tamaMesh;
    m_tamaIndex = tamaIndex;
    m_movementCollision = movementCollision;

    m_config.fighterCount =
        std::clamp(config.fighterCount, kMinFighters, kMaxFighters);
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
        // After init()/reset(): the move table only feeds swings started later.
        m_fighters[i].set_moves(config.moves[i]);
    }
    m_shots.clear();
    m_locks.reset(m_config.fighterCount, m_config.side);
    m_economy.reset();
    m_economy.set_round_rules(config.timeLimit, config.balloonSize);
    // Issue #48's F2/F3 flag: battle state like the lock table, so a rematch starts with every
    // COM brain live again — the original sets it to 1 wherever a slot is bound to a battle
    // (FUN_0041efa0:10, and FUN_00417200:47 when the roster assigns a COM slot).
    for (int i = 0; i < kMatchFighterCount; ++i) m_aiEnabled[i] = true;
}

void Match::liveness(bool out[kMatchFighterCount]) const {
    for (int i = 0; i < kMatchFighterCount; ++i) out[i] = m_fighters[i].is_alive();
}

void Match::cycle_locked_target(int fighter, bool forward) {
    if (fighter < 0 || fighter >= m_config.fighterCount) return;
    bool alive[kMatchFighterCount];
    liveness(alive);
    m_locks.cycle_enemy(fighter, forward, alive);
}

void Match::lock_ally_target(int fighter) {
    if (fighter < 0 || fighter >= m_config.fighterCount) return;
    bool alive[kMatchFighterCount];
    liveness(alive);
    m_locks.select_ally(fighter, alive);
}

void Match::begin_round_entry() {
    for (int i = 0; i < m_config.fighterCount; ++i) m_fighters[i].begin_round_entry();
}

void Match::step_round_entry(double dt) {
    // Only the entrance falls/animates: no inputs, COM, combat contacts or round clock.
    for (int i = 0; i < m_config.fighterCount; ++i)
        m_fighters[i].update(nullptr, nullptr, dt, m_movementCollision);
}

int Match::aim_target(int fighter) const {
    bool alive[kMatchFighterCount];
    liveness(alive);
    const int target = m_locks.target(fighter);
    return m_locks.targetable(fighter, target, alive)
        ? target : m_locks.fallback_target(fighter, alive);
}

int Match::melee_target(int fighter) const {
    if (fighter < 0 || fighter >= m_config.fighterCount) return kNoTarget;
    bool alive[kMatchFighterCount];
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
        if (m_fighters[j].respawn_locked()) continue;  // not selectable until it lands
        const glm::vec3 d = m_fighters[j].position() - m_fighters[fighter].position();
        const float distance = d.x * d.x + d.z * d.z;
        if (distance < nearest) { nearest = distance; victim = j; }
    }
    return victim;
}

MatchFrame Match::step(const fnd::input::PlayerState* p1Input,
                       const fnd::input::PlayerState* p2Input, double dt) {
    const fnd::input::PlayerState* inputs[kMatchFighterCount] =
        {p1Input, p2Input, nullptr, nullptr};
    return step(inputs, dt);
}

MatchFrame Match::step(const fnd::input::PlayerState* inputs[kMatchFighterCount], double dt) {
    MatchFrame out;
    // Paused: the authoritative step does not run at all (issue #15). Nothing below this
    // point executes — not the economy tick, not the fighters, not the projectile pool —
    // and `dt` is dropped rather than accumulated, so paused wall time cannot be replayed
    // as catch-up ticks on resume.
    if (m_paused) return out;
    m_economy.tick(dt);   // scenes.cpp:610

    // Maintain the per-fighter locks first: FUN_0041f580 does its validity fallback and
    // ally-hold pin before anything reads the selection, and the fighters below read it
    // on this same tick. This snapshot is the liveness as of the tick's START; `alive`
    // further down is re-read after the fighters move, which is what the economy needs.
    bool aliveAtStart[kMatchFighterCount];
    liveness(aliveAtStart);
    m_locks.step(aliveAtStart);

    // Each fighter faces, aims and shoots at ITS OWN locked target (FUN_00421f30's
    // +0x304), which is what lets two players hold independent locks. Panel order still
    // decides the update order, so a two-fighter match keeps the reference's P1-then-P2
    // asymmetry. A lock naming an ally is passed through as-is: that is the hold gesture.
    //
    // Facing is NOT the lock, though. In the original the fighter's aim/facing selection
    // (+0x300, which FUN_00421c80 requests and FUN_0041f580:216-241 re-picks) is
    // maintained independently of the combat lock (+0x304), so a fighter with no lock
    // still turns to an opponent. The port's stand-in is the same maintenance walk the
    // lock's own fallback uses; before issue #49 it wrote that pick INTO the lock table,
    // which is why every ring was green at round start. Asking for it here instead keeps
    // the facing and the ring honest at the same time.
    for (int i = 0; i < m_config.fighterCount; ++i) {
        int target = m_locks.target(i);
        if (target == kNoTarget) target = m_locks.fallback_target(i, aliveAtStart);
        // Publish the firing-relevant aim state the original reads straight off the
        // player struct: word +0x848, re-pinned while this fighter's aim target is the
        // same fighter player 0 is aiming at, is one half of the powered gate every
        // shoot body tests (the other is the fighter's own Oyashiro special). This is
        // the aim-selection predicate, not the combat lock's ally hold.
        ShootingContext context;
        context.aimHold = m_locks.aim_holds(i);
        m_fighters[i].set_shooting_context(context);
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
                // The victim's own state at the landing frame decides the block report
                // (issue #16); it is read here, before anything can change it this tick.
                if (m_fighters[j].state() == FighterState::Guard) out.blocked[j] = true;
            }
        }
    }

    for (int i = 0; i < m_config.fighterCount; ++i) {   // scenes.cpp:689-696
        for (PendingShot shot = m_fighters[i].take_pending_shot(); shot.armed;
             shot = m_fighters[i].take_pending_shot()) {
            if (m_fighters[i].is_alive() &&
                m_shots.spawn(shot.pos, shot.dir, shot.tier, &m_fighters[i], shot.bulletRow,shot.target)) {
                ++out.shotsSpawned;
                out.shotFired[i] = true;
                if (i < kMatchFighterCount) out.shotPoints[i] = shot.pos;
                m_shots.spawn_spark(shot.pos, 0.2f);   // muzzle flash
                ++out.muzzleSparks;
            }
        }
    }
    m_shots.update(dt, m_fighters, m_config.fighterCount, m_tamaMesh, m_tamaIndex,
                   m_config.side); // scenes.cpp:697-699; allied fighters are not projectile targets
    // The pool resolved its own contacts; carry them into the frame so audio/effects key
    // off the same hits the damage path applied (issue #16).
    for (int i = 0; i < m_shots.contact_count() && out.shotHitCount < MatchFrame::kMaxShotHits; ++i) {
        const ProjectilePool::ShotContact& c = m_shots.contact(i);
        if (c.victim < 0 || c.victim >= m_config.fighterCount) continue;
        MatchFrame::ShotHit& hit = out.shotHits[out.shotHitCount++];
        hit.shooter = c.shooter;
        hit.victim  = c.victim;
        hit.blocked = m_fighters[c.victim].state() == FighterState::Guard;
        hit.point   = c.point;
        hit.effect  = c.effect;
        if (hit.blocked) out.blocked[c.victim] = true;
    }

    // The per-fighter edges the frame carries to audio/effects (issue #16): a swing
    // armed, hypermode activated. Both latches are drained here exactly once, the same
    // discipline as the KO credit below.
    for (int i = 0; i < m_config.fighterCount; ++i) {
        out.swingStarted[i] = m_fighters[i].take_swing_start();
        out.hyperStarted[i] = m_fighters[i].take_hyper_start();
        out.guardStarted[i] = m_fighters[i].take_guard_start();
    }

    // Hand the economy what it cannot see for itself: the KO/Overkill events that
    // landed this frame (issue #11). Each is drained exactly once — a KO credit is
    // armed only by the blow that took HP to zero, and the overkill counter counts
    // hits — so a complete match cannot double-credit either.
    for (int i = 0; i < m_config.fighterCount; ++i) {
        if (m_fighters[i].pending_ko()) {
            const Fighter::KoCredit credit = m_fighters[i].take_ko_credit();
            m_economy.note_death(i, credit.overkillHp, credit.reactionBonus, credit.shot);
        }
        for (int hit = m_fighters[i].take_overkill_hits(); hit > 0; --hit)
            m_economy.note_overkill_hit(i);
    }

    bool alive[kMatchFighterCount] = {true, true, true, true};
    int hp[kMatchFighterCount] = {0, 0, 0, 0};
    for (int i = 0; i < m_config.fighterCount; ++i) {
        alive[i] = m_fighters[i].is_alive();
        // The timed round's second key sums each side's remaining HP
        // (FUN_00635d40 @0x636ef4-0x636f8a); the scale does not matter, only the
        // comparison, so the port's 0..max_hp crosses as-is.
        hp[i] = m_fighters[i].hp();
    }
    const MatchStepResult eco = m_config.fighterCount == 2
        // The 1v1 trace path keeps the side == fighter mapping; the HP totals still
        // cross, so the timed round's second key applies in 1v1 as well
        // (FUN_00635d40 @0x636ef4-0x636f8a).
        ? m_economy.update(alive, hp)
        : m_economy.update(alive, m_config.side, m_config.fighterCount, hp);
    for (int i = 0; i < m_config.fighterCount; ++i) {
        // The reference calls FUN_004219a0/Fighter::reset here; the economy only
        // reports the flag because it owns no positions (see match_economy.h).
        if (eco.respawned[i]) {
            const glm::vec3 spawn = m_movementCollision
                ? m_movementCollision->resolveSpawn(m_config.spawn[i], m_config.spawn,
                                                    static_cast<size_t>(m_config.fighterCount))
                : m_config.spawn[i];
            m_config.spawn[i] = spawn;
            // The respawn is airborne (FighterConstants::kRespawnAirY) and keeps this
            // fighter's own spawn slot and team.
            m_fighters[i].respawn(spawn, m_config.facing[i],
                                  FighterConstants::kRespawnAirY);
        }
        out.respawned[i] = eco.respawned[i];
        out.koCredits[i] = eco.koCredits[i];
        out.overkillHits[i] = eco.overkillCredits[i];
    }
    out.roundOver = eco.roundOver;
    out.roundOverSide = eco.roundOverSide;
    out.koSting = m_economy.koStingActive();
    return out;
}

}  // namespace gameplay
