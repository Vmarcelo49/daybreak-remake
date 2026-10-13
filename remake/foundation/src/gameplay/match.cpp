// gameplay/match.cpp — see match.h for the order this reproduces and why.
#include "gameplay/match.h"

#include <algorithm>
#include <cmath>

namespace gameplay {

void Match::reset(const MatchConfig& config, const xm::Model* model[kMatchFighterCount],
                  xm::Controller* anim[kMatchFighterCount],
                  const xm::Model* tamaMesh, const game::physics::ModelIndex* tamaIndex,
                  const game::physics::MovementCollision* movementCollision) {
    m_config = config;
    m_primaryListener = 0;
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
    // A fresh round restarts the stream, so a rematch replays the same spread sequence
    // rather than continuing the previous round's draws.
    m_rng.reset();
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

// The close-target voice cascade's producer (FUN_0042e110:30-72), for one fighter.
// Runs before any fighter updates, so every field read is the previous tick's —
// see the call site for the ordering proof and the two recorded approximations.
ShootingContext::VoiceFlags Match::meleeVoiceFlags(int fighter,
                                                   const bool alive[4]) const {
    ShootingContext::VoiceFlags out;
    const Fighter& self = m_fighters[fighter];
    // FUN_004236c0: the reaction state band 100..299. Attacks are not admittable out of
    // one (`can_act`), so the addattack latch never arms for a row the port can run.
    const int state = self.action_state();
    if (state >= 100 && state <= 299) return out;
    // The attention actor: +0x308, written by both selectors. A valid combat lock
    // (+0x304, the direct writer) is the most recent one, else the aim selection
    // (+0x300, the cycle writer, which init starts at 0 for everybody).
    const int attention = m_locks.valid_target(fighter) ? m_locks.target(fighter)
                                                       : m_locks.aim_selection(fighter);
    if (attention < 0 || attention >= m_config.fighterCount || attention == fighter)
        return out;
    const Fighter& other = m_fighters[attention];
    // The original tests whether the attention actor's OWN attention points back here,
    // read the same way, and ORs in "I hold a combat lock". Either one makes the target
    // mutually engaged, which is the ordinary-voice arm.
    const int theirAttention = m_locks.valid_target(attention)
                                  ? m_locks.target(attention)
                                  : m_locks.aim_selection(attention);
    const bool engaged = theirAttention == fighter || m_locks.valid_target(fighter);
    if (engaged) return out;
    // The yaw test: the attention actor's effort heading (its body yaw plus its battle
    // offset, both at +0x5c/+0x64) against this body's own yaw, wrapped to +-180.
    // The port carries the body yaw only — the offset is one of the two terms the
    // cascade's own gate cannot supply — so the comparison is on body yaw alone.
    const float difference = std::remainder(other.facing_yaw() - self.facing_yaw(),
                                            glm::two_pi<float>());
    if (std::abs(difference) >= glm::radians(90.f)) return out;
    out.flags[2] = 1;  // +0xaeb9 — the "speaking the same direction" latch
    // FUN_0042e950: an attack-or-shot state. Read on the PREVIOUS tick's state, so a
    // chained attack (the press that arrived while already in a 3xx row) arms the
    // intercept latch and a fresh press out of locomotion does not.
    if ((state >= 300 && state <= 379) || state >= 400) out.flags[1] = 1;
    return out;
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
        // The scene's single stream: the original draws spread from one global MT19937,
        // so every participant shares this and the sequence depends on the match's own
        // draw order (which is deterministic but not the original's).
        context.rng = &m_rng;
        // Word +0x278, the AI's own movement decision. Only the COM decision routines write
        // it, so a human slot leaves it at 0 — publishing an input-derived value for a human
        // would invent a branch the original never takes. The port's brain expresses the same
        // intent through the direction keys, so the sign of the applied lateral input is what
        // the shot bodies would have read.
        if (ai_enabled(i) && inputs && inputs[i]) {
            const auto& in = *inputs[i];
            context.moveLateral = in.down[fnd::input::Right] ? 1
                                  : in.down[fnd::input::Left] ? -1 : 0;
        }
        // The close-target voice cascade's three latches, computed BEFORE any fighter
        // updates so the state they read is the previous tick's — FUN_00634f60 runs
        // FUN_0042e110 for a fighter and only then its state handler, in the same
        // per-fighter loop, so a latch computed after the update would read this tick's
        // state. FUN_0042e110:30-72, read against FUN_004236c0 / FUN_0042e950:
        //   * `+0xaec3` arms only from a REACTION state (100..299, FUN_004236c0), and
        //     the state machine refuses attacks out of one, so no admitted attack can
        //     carry it — the addattack voice is unreachable through an attack row.
        //   * the armed pair `+0xaeb9`/`+0xaebe` needs the attention actor NOT to
        //     attend back (`P->+0x308 != me`) and no combat lock of my own, plus the
        //     yaw test; `+0xaebe` additionally needs an attack-or-shot state.
        // Two terms of that producer are not modelled here and are recorded, not
        // guessed: the per-slot device code at `+0x7d8` (written by FUN_00635d40 from
        // FUN_00430880, whose button order is unrecovered) only ever DISJUNCTS the
        // unreachable arm, and the battle-offset yaw `+0x19` that the cascade's
        // `|offset| < 30` gate reads is not carried by this port at all — so the gate
        // is evaluated with the offset held at 0 and the distance term alone decides.
        context.voice = meleeVoiceFlags(i, aliveAtStart);
        m_fighters[i].set_shooting_context(context);
        m_fighters[i].update(inputs ? inputs[i] : nullptr,
                             (target != kNoTarget && target < m_config.fighterCount)
                                 ? &m_fighters[target] : nullptr,
                             dt, m_movementCollision);
    }

    if (m_primaryListener >= 0 && m_primaryListener < m_config.fighterCount) {
        const Fighter& listener = m_fighters[m_primaryListener];
        out.audioListenerPosition = listener.position() + glm::vec3(0.f, 150.f, 0.f);
        // IDirectSound3DListener::SetOrientation at raw VA 0x635c20-0x635c6d gets
        // front=(FUN_0065d050(yaw),0,FUN_0065d010(yaw)), top=(0,1,0). Both helpers
        // round 0.1-degree indices, take abs(index) and wrap by 3600 before reading the
        // sine table (FUN_0065cfa0). Apply that lookup exactly; a plain sin/cos formula
        // differs for negative yaw because of the source's abs step.
        const float yawDegrees = glm::degrees(listener.facing_yaw());
        const auto sourceSine = [](float degrees) {
            const int index = std::abs(static_cast<int>(std::nearbyint(degrees * 10.f))) % 3600;
            return std::sin(glm::radians(static_cast<float>(index) * .1f));
        };
        out.audioListenerForward = glm::normalize(glm::vec3(
            sourceSine(yawDegrees), 0.f, sourceSine(yawDegrees - 90.f)));
        out.audioListenerValid = true;
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
            // The guard read must happen BEFORE try_melee_hit: the damage call
            // inside it can stun the victim out of Guard this same tick, and the
            // attacker's 392 exit (FUN_0042c7b0() bit 2) reads the guarded state of
            // the strike's landing frame, not of a post-stun victim.
            const bool guarded = m_fighters[j].state() == FighterState::Guard;
            if (m_fighters[i].try_melee_hit(m_fighters[j], m_movementCollision)) {
                m_fighters[i].note_melee_hit(j, guarded);
                out.meleeHit[i] = true;
                out.meleeVictim[i] = j;
                // The victim's own state at the landing frame decides the block report
                // (issue #16).
                if (guarded) out.blocked[j] = true;
            }
        }
    }

    for (int i = 0; i < m_config.fighterCount; ++i) {   // scenes.cpp:689-696
        out.sourceShotVoiceAudited[i] = m_fighters[i].source_shot_voice_audited();
        const auto voice = m_fighters[i].take_shooting_voice();
        out.shotVoice[i] = voice.event;
        out.shotVoiceAlternative[i] = voice.alternative;
        // The melee voice and effect cues drain the same way (FUN_004223d0/422490
        // and FUN_0042c8b0/2c880's per-tick latches).
        const auto meleeVoice = m_fighters[i].take_melee_voice();
        out.meleeVoice[i] = meleeVoice.event;
        out.meleeVoiceAlternative[i] = meleeVoice.alternative;
        out.sourceMeleeVoiceAudited[i] = m_fighters[i].source_melee_voice_audited();
        const auto sound = m_fighters[i].take_sound_effect();
        out.soundEffectId[i] = sound.id;
        out.soundEffectPositional[i] = sound.positional;
        out.soundEffectPosition[i] = sound.position;
        const auto effect = m_fighters[i].take_effect();
        out.effectId[i] = effect.id;
        out.effectYaw[i] = effect.yaw;
        out.effectPitch[i] = effect.pitch;
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
