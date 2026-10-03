// =============================================================================
//  fighter.cpp — state machine + movement + animation switching.
//
//  Faithful translation of remake/src/gameplay/fighter.cpp (see the PORT NOTES
//  in fighter.h for the deviation list): same update() ordering, same timer
//  arithmetic, same constants. Mirrors the original game's fcn.0041f580
//  (per-player update) and fcn.00420b30 (world matrix update).
// =============================================================================
#include "gameplay/fighter.h"

#include <algorithm>
#include <cmath>
#include <cstddef>

#include <glm/gtc/matrix_transform.hpp>

namespace gameplay {

void Fighter::bind(const xm::Model* model, xm::Controller* anim) {
    m_model = model;
    m_anim  = anim;
    // The controller needs the model too (it resolves set indices against it),
    // and the new model invalidates the cached set index.
    if (m_anim) m_anim->bind(m_model);
    m_animSetIdx = -1;
    // The DX9 init()/reset() ended with this call; binding is where the two
    // halves of the split XModel are joined, so it belongs here.
    try_switch_animation();
}

void Fighter::init(const xm::Model* model, xm::Controller* anim,
                   const glm::vec3& pos, float facing) {
    bind(model, anim);
    m_position = pos;
    m_facing = facing;
    m_velocity = glm::vec3(0, 0, 0);
    m_hp = FighterConstants::kMaxHP;
    m_stamina = static_cast<float>(FighterConstants::kMaxStamina);
    m_state = FighterState::BattleStart;
    m_stateTimer = FighterConstants::kBattleStartFrames;
    m_animSetIdx = -1;   // bind() looked the previous state up; BattleStart wins
    clear_tracks();      // a round reset is a fresh bind, never a blend
    m_main = AmmoStock{FighterConstants::kMainMax, FighterConstants::kMainMax,
                       FighterConstants::kMainPerSec};
    m_charge = AmmoStock{FighterConstants::kChargeMax, FighterConstants::kChargeMax,
                         FighterConstants::kChargePerSec};
    m_chargeHeld = 0.0f;
    m_reloadTimer = 0;
    m_pending = PendingShot{};
    m_vy = 0.0f;
    m_grounded = true;
    m_groundY = pos.y;
    m_flyLeft = FighterConstants::kFlyTimeSec;
    m_dashAir = false;
    m_airDashed = false;
    try_switch_animation();
}

void Fighter::reset(const glm::vec3& pos, float facing) {
    m_position = pos;
    m_facing = facing;
    m_velocity = glm::vec3(0, 0, 0);
    m_hp = FighterConstants::kMaxHP;
    m_stamina = static_cast<float>(FighterConstants::kMaxStamina);
    m_state = FighterState::BattleStart;
    m_stateTimer = FighterConstants::kBattleStartFrames;
    m_animSetIdx = -1;
    clear_tracks();      // same fresh-bind rule as init()
    m_vy = 0.0f;
    m_grounded = true;
    m_groundY = pos.y;
    m_flyLeft = FighterConstants::kFlyTimeSec;
    m_dashAir = false;
    m_airDashed = false;
    m_main.value = FighterConstants::kMainMax;
    m_charge.value = FighterConstants::kChargeMax;
    m_chargeHeld = 0.0f;
    m_reloadTimer = 0;
    m_pending = PendingShot{};
    m_gauge = 0.0f;
    m_hyperActive = false;
    m_hyperTimer = 0.0f;
    m_hitsActive = 0;
    try_switch_animation();
}

bool Fighter::can_act() const {
    return m_state == FighterState::Idle || m_state == FighterState::Walk ||
           m_state == FighterState::Run || m_state == FighterState::Jump;
}

bool Fighter::can_move() const {
    return m_state == FighterState::Idle || m_state == FighterState::Walk ||
           m_state == FighterState::Run || m_state == FighterState::Jump;
}

void Fighter::update(const input::PlayerState* input, Fighter* opponent, double dt) {
    m_time += dt;

    // Hypermode first: it can activate this frame (S), expire, or drain
    // Kakera HP, all before the state machine reads the mode's modifiers.
    update_hypermode(dt, opponent);

    // 1. Decrement state timer (mirrors +0xa0 in fcn.0041f580).
    if (m_stateTimer > 0) {
        --m_stateTimer;
        if (m_stateTimer == 0) {
            if (m_state != FighterState::KO && m_state != FighterState::TagOut) {
                // Timed states expire back into the fall when airborne
                // (a dash/attack/volley started mid-air lands as Jump).
                set_state(m_grounded ? FighterState::Idle : FighterState::Jump);
            }
        }
    }

    // 2. Update state machine (check input, transition states).
    // A lost action window (hit, KO) breaks any charge hold in progress.
    if (!can_act()) m_chargeHeld = 0.0f;
    if (can_act() && input) {
        update_state_machine(input, opponent, dt);
    }

    // 3. Update movement (if the state allows it).
    if (can_move() && input) {
        update_movement(input, opponent, dt);
    } else {
        m_velocity *= 0.8f;
        m_position += m_velocity * static_cast<float>(dt);
    }

    // 4. Update facing (always face the opponent).
    if (opponent && opponent->is_alive()) {
        update_facing(opponent, dt);
    }

    // 5. Stamina: grounded refill (fast after use — battle-stamina.webp)
    // plus block-hold drain. Dash/leap/flight spends happen at trigger
    // sites below; airtime never refills, so flight is a real budget.
    if (m_grounded && can_act()) {
        m_stamina = std::min(m_stamina + FighterConstants::kStaminaRegenSec *
                             static_cast<float>(dt),
                             static_cast<float>(FighterConstants::kMaxStamina));
    }
    if (m_state == FighterState::Guard) {
        m_stamina = std::max(0.0f, m_stamina - FighterConstants::kGuardDrainSec *
                             static_cast<float>(dt));
    }

    // 5b. Vertical motion: hold-Z flight against the fly budget, else
    // gravity. Runs for every state (corpses fall too); only Jump and an
    // airborne dash convert the landing into Idle — Hit/KO/attacks keep
    // their state through touchdown.
    if (!m_grounded) {
        const float step = static_cast<float>(dt);
        const bool wantFly = input && input->down[input::Action::Jump] &&
                             m_state == FighterState::Jump && m_flyLeft > 0.0f &&
                             is_alive();
        // An air dash hangs for its window (no fall until it expires).
        const bool dashHang = m_state == FighterState::Run && m_dashAir;
        if (wantFly) {
            m_vy = FighterConstants::kFlyRise;
            m_flyLeft -= step;
            m_stamina = std::max(0.0f, m_stamina - FighterConstants::kFlyDrainSec * step);
        } else if (!dashHang) {
            m_vy -= FighterConstants::kGravity * step;
        }
        m_position.y += m_vy * step;
        const float ceiling = m_groundY + FighterConstants::kFlyMaxAlt;
        if (m_position.y > ceiling) {
            m_position.y = ceiling;
            if (m_vy > 0.0f) m_vy = 0.0f;
        }
        if (m_position.y <= m_groundY) {
            m_position.y = m_groundY;
            m_vy = 0.0f;
            m_grounded = true;
            m_flyLeft = FighterConstants::kFlyTimeSec;
            m_airDashed = false;
            if (m_state == FighterState::Jump ||
                (m_state == FighterState::Run && m_dashAir)) {
                set_state(FighterState::Idle);
            }
            m_dashAir = false;
        }
    }

    // 5b. Recharge ammo continuously (the HUD sweep IS this refill —
    // ammo-bar.webp) and tick the reloadNG window down. Friendship mode
    // brings the stocks back faster (spec §3.4).
    const HypermodeParams& hyp = hypermode_params(m_hypermode);
    const float mainMul   = m_hyperActive ? hyp.mainRechargeMul   : 1.0f;
    const float chargeMul = m_hyperActive ? hyp.chargeRechargeMul : 1.0f;
    m_main.recharge(dt, mainMul);
    m_charge.recharge(dt, chargeMul);
    if (m_reloadTimer > 0) --m_reloadTimer;

    // 6. Update the animation playhead. The DX9 XModel::update() clamped dt to
    // 0.1 s against post-stall jumps (file_parser/x_model_loader.cpp:588-590);
    // xm::Controller::advanceTime does not, so the clamp lives here.
    if (m_anim && m_animate) {
        const float animDt = (dt > 0.1) ? 0.1f : static_cast<float>(dt);
        m_anim->advanceTime(animDt);
        // One cross-fade step per tick (the FUN_0041f580 weight half), so the
        // blend stays deterministic under the fixed-dt capture.
        tick_blend();
    }
}

void Fighter::update_state_machine(const input::PlayerState* input,
                                    Fighter* opponent, double dt) {
    if (!input) return;

    // AttackA (melee key in the original: X). Provisional mapping —
    // see input.h (no dedicated heavy key exists).
    if (input->just_pressed[input::Action::AttackA]) {
        set_state(FighterState::AttackA);
        m_stateTimer = FighterConstants::kAttackFrames;
        return;
    }

    // AttackB (heavy stand-in — unbound by default; see input.h).
    if (input->just_pressed[input::Action::AttackB]) {
        set_state(FighterState::AttackB);
        m_stateTimer = FighterConstants::kAttackFrames;
        return;
    }

    // Jump (Z): grounded leap; holding Z aloft flies against the fly budget
    // (vertical block in update()). X/C/S all stay usable airborne — aerials
    // are the same swings with gravity running underneath.
    if (input->just_pressed[input::Action::Jump] && m_grounded) {
        try_jump();
        return;
    }

    // Double-tap dash: tap,tap on a direction within the window commits a
    // facing-relative dash (Up = forward ...) — or an air dash when airborne
    // (once per airtime). Runs before Guard so a tap under a held block key
    // still sidesteps.
    {
        const input::Action dirs[4] = {input::Action::Up, input::Action::Down,
                                       input::Action::Left, input::Action::Right};
        for (int d = 0; d < 4; ++d) {
            if (!input->just_pressed[dirs[d]]) continue;
            const bool chained =
                (m_time - m_lastTap[d]) <= FighterConstants::kDoubleTapSec;
            m_lastTap[d] = m_time;
            if (chained && try_dash(dirs[d])) return;
        }
    }

    // Special (S) has three roles in priority order (spec §3.1): activate
    // Hypermode at a full bar, then the EX move while active, and only
    // otherwise does it charge the shot like C does.
    if (input->just_pressed[input::Action::Special]) {
        if (try_activate_hypermode(opponent)) return;
        if (m_hyperActive) {
            try_ex_move();
            return;
        }
    }

    // Shoot (C) — or S when neither of the above applies: holding
    // accumulates charge without interrupting the state (mobile charge —
    // the original's charge/movement interplay is un-RE'd, so the least
    // surprising model wins); releasing fires the held tier. Charge only
    // accrues while actionable so hits/attacks break the hold.
    const bool chargeDown = input->down[input::Action::Shoot] ||
                            (input->down[input::Action::Special] && !m_hyperActive);
    if (chargeDown) {
        if (m_chargeHeld < FighterConstants::kRedHoldSec) {
            m_chargeHeld += static_cast<float>(dt);
        }
    } else if (m_chargeHeld > 0.0f) {
        // Fire even on a sub-frame tap (charge_tier() then reads Tap).
        // Drops under reloadNG/no stock.
        try_fire();
        m_chargeHeld = 0.0f;
        if (m_pending.armed) return;
    }

    // Guard (block key held).
    if (input->down[input::Action::Guard]) {
        if (m_state != FighterState::Guard) {
            set_state(FighterState::Guard);
        }
        return;
    } else {
        if (m_state == FighterState::Guard) {
            set_state(FighterState::Idle);
        }
    }

    bool moving = input->down[input::Action::Up] ||
                  input->down[input::Action::Down] ||
                  input->down[input::Action::Left] ||
                  input->down[input::Action::Right] ||
                  std::abs(input->stick_x) > 8000 ||
                  std::abs(input->stick_y) > 8000;

    if (moving && m_state == FighterState::Idle) {
        set_state(FighterState::Walk);
    } else if (!moving && m_state == FighterState::Walk) {
        set_state(FighterState::Idle);
    }
}

void Fighter::update_movement(const input::PlayerState* input, const Fighter* opp, double dt) {
    (void)opp;
    if (!input) return;

    // Committed dash: steering is locked to the tapped direction for the
    // dash window (ground or air — m_dashDir was resolved at trigger time).
    if (m_state == FighterState::Run) {
        m_velocity.x = m_dashDir.x * m_dashSpeed;
        m_velocity.z = m_dashDir.z * m_dashSpeed;
        m_position += m_velocity * static_cast<float>(dt);
        return;
    }

    float dx = 0.0f, dz = 0.0f;

    if (std::abs(input->stick_x) > 8000 || std::abs(input->stick_y) > 8000) {
        dx = static_cast<float>(input->stick_x) / 32768.0f;
        dz = static_cast<float>(input->stick_y) / 32768.0f;
    } else {
        if (input->down[input::Action::Left])  dx -= 1.0f;
        if (input->down[input::Action::Right]) dx += 1.0f;
        if (input->down[input::Action::Up])    dz -= 1.0f;  // up = -Z
        if (input->down[input::Action::Down])  dz += 1.0f;
    }

    // Normalize the direction vector (mirrors D3DXVec3Normalize in the original).
    float len = std::sqrt(dx * dx + dz * dz);
    if (len > 0.001f) {
        dx /= len;
        dz /= len;

        float speed = FighterConstants::kWalkSpeed;
        if (!m_grounded) speed *= FighterConstants::kAirControl;

        m_velocity.x = dx * speed;
        m_velocity.z = dz * speed;
    } else {
        m_velocity.x = 0.0f;
        m_velocity.z = 0.0f;
    }

    m_position += m_velocity * static_cast<float>(dt);
}

void Fighter::update_facing(const Fighter* opp, double dt) {
    if (!opp) return;

    float dx = opp->m_position.x - m_position.x;
    float dz = opp->m_position.z - m_position.z;

    // In the game's coordinate system, yaw=0 faces +Z, positive yaw rotates
    // toward +X (left-handed).
    float target_yaw = std::atan2(dx, dz);

    float diff = target_yaw - m_facing;
    // Wrap to [-π, π].
    while (diff >  3.14159265f) diff -= 2.0f * 3.14159265f;
    while (diff < -3.14159265f) diff += 2.0f * 3.14159265f;

    m_facing += diff * FighterConstants::kTurnSpeed * static_cast<float>(dt);
}

void Fighter::set_state(FighterState new_state) {
    if (m_state == new_state) return;
    m_state = new_state;
    m_animSetIdx = -1;  // force animation re-lookup
    m_didHitThisSwing = false;  // new swing may hit again
    try_switch_animation();
}

void Fighter::set_animate(bool on) {
    if (m_animate == on) return;
    m_animate = on;
    m_animSetIdx = -1;
    m_animFallback = false;   // no set is bound while animation is off
    m_blendTicks = 0;         // and no cross-fade is in flight
    clear_tracks();
    if (m_animate) try_switch_animation();
}

// No track may stay bound through a fresh bind: evalLocal then leaves every
// frame at its bind T/R/S, which is the pose the renderer uploads, and the
// next try_switch_animation() hard-cuts instead of blending from stale sets.
void Fighter::clear_tracks() {
    if (!m_anim) return;
    for (int t = 0; t < xm::Controller::kMaxTracks; ++t) {
        m_anim->setTrackEnable(t, false);
        m_anim->setTrackAnimationSet(t, -1);
    }
}

void Fighter::try_switch_animation() {
    if (!m_animate) return;
    if (!m_model || !m_anim) return;
    if (m_animSetIdx >= 0) return;  // already set for this state
    if (m_model->anims.empty()) return;

    // The original's selection: state → move id → the move's first phase → set
    // index (see the table above state_to_anim_set in fighter.h). The index is
    // the D3DX set index, which is this model's `anims` index.
    const int want = state_to_anim_set(m_state);
    const int resolved =
        (want >= 0 && static_cast<std::size_t>(want) < m_model->anims.size())
            ? want
            : 0;
    const bool fallback = (resolved != want) || (want < 0);

    // Move-change blend (FUN_004211f0/FUN_00421240 + FUN_0041f580 weights):
    // the old set stays on track 0 while the new set starts on track 1, and
    // tick_blend() cross-fades them. A mid-blend interruption only retargets
    // track 1 (the original rebinds track 1 alone): the weights continue from
    // their current values so the pose never snaps. The initial bind and
    // same-set rebinds cut both tracks at once (the FUN_00421100 steady state).
    const int old = m_anim->trackAnimationSet(0);
    if (old >= 0 && old != resolved &&
        static_cast<std::size_t>(old) < m_model->anims.size()) {
        const float w1 = m_anim->trackWeight(1);
        m_anim->setTrackAnimationSet(1, resolved);
        m_anim->setTrackPosition(1, 0.0);
        m_anim->setTrackEnable(1, true);
        m_anim->setTrackLoop(1, true);
        if (m_blendTicks <= 0) {
            m_anim->setTrackWeight(0, 1.f);
            m_anim->setTrackWeight(1, 0.f);
            m_blendTicks = FighterConstants::kAnimBlendTicks;
        } else {
            // Continue the ramp where it is: remaining ticks from the live
            // track-1 weight, so the next tick_blend() step is continuous.
            m_blendTicks = std::max(
                1, static_cast<int>((1.f - w1) *
                                   static_cast<float>(FighterConstants::kAnimBlendTicks) +
                                   0.5f));
        }
        m_blendTotal = FighterConstants::kAnimBlendTicks;
    } else {
        m_anim->setAnimationBothTracks(resolved);
        m_blendTicks = 0;
    }
    m_animSetIdx = resolved;
    // Fallback, deliberately visible: states the table does not cover (Guard,
    // Jump, TagOut — see the table's "not settled" list) and models with fewer
    // sets than the index play set 0, the bind-anchored default, and report it
    // through anim_fallback() instead of silently looking like a mapped state.
    m_animFallback = fallback;
}

void Fighter::commit_blend() {
    if (!m_anim) return;
    const int cur = m_anim->trackAnimationSet(1);
    if (cur >= 0) {
        m_anim->setTrackAnimationSet(0, cur);
        m_anim->setTrackPosition(0, m_anim->trackPosition(1));
        m_anim->setTrackEnable(0, true);
        m_anim->setTrackLoop(0, true);
    }
    m_anim->setTrackWeight(0, 1.f);
    m_anim->setTrackWeight(1, 0.f);
    m_blendTicks = 0;
}

void Fighter::tick_blend() {
    if (!m_anim || m_blendTicks <= 0) return;
    if (--m_blendTicks <= 0) {
        // Steady state: both tracks on the new set at full weight, which is
        // the FUN_00421100 bind the blend started from (same set twice is a
        // no-op through the ordered weighted blend).
        commit_blend();
        m_anim->setTrackWeight(1, 1.f);
        return;
    }
    // FUN_0041f580's ramp is linear in the remaining counter (old decays by
    // remaining/total, new rises complementarily), so lerp the two weights.
    const float t =
        1.f - static_cast<float>(m_blendTicks) / static_cast<float>(m_blendTotal);
    m_anim->setTrackWeight(0, 1.f - t);
    m_anim->setTrackWeight(1, t);
}

const char* Fighter::anim_set_name() const {
    if (!m_model || m_animSetIdx < 0 ||
        static_cast<std::size_t>(m_animSetIdx) >= m_model->anims.size()) {
        return "";
    }
    return m_model->anims[static_cast<std::size_t>(m_animSetIdx)].name.c_str();
}

void Fighter::take_damage(int amount, Fighter* source) {
    const HypermodeParams& mine = hypermode_params(m_hypermode);

    if (m_state == FighterState::Guard) {
        // Blocking reduces damage to 20%.
        amount = std::max(1, amount / 5);
    }

    // Hypermode damage trades: the attacker's mode boosts what it deals
    // (Oyashiro/Kakera ×1.5), ours cuts what we take (×0.75 / ×0.20).
    if (source && source->hyper_active()) {
        const float mul = hypermode_params(source->m_hypermode).damageDealtMul;
        amount = static_cast<int>(std::lround(amount * mul));
    }
    if (m_hyperActive) {
        amount = static_cast<int>(std::lround(amount * mine.damageTakenMul));
    }
    amount = std::max(1, amount);

    // Gauge credit happens on the damage that actually lands: the attacker's
    // mode may feed on dealing it, ours on taking it (never while active, so
    // an active mode cannot refill itself).
    if (source) source->gain_gauge(amount *
                                   hypermode_params(source->m_hypermode)
                                       .fillPerDamageDealt);
    gain_gauge(amount * mine.fillPerDamageTaken);

    m_hp = std::max(0, m_hp - amount);

    if (m_hp <= 0) {
        // Kakera fires on the killing blow instead of dying (spec §3.4).
        if (mine.autoOnDeath && !m_hyperActive && m_gauge >= 1.0f) {
            m_hp = FighterConstants::kMaxHP;
            m_gauge = 0.0f;
            m_hyperActive = true;
            m_hyperTimer = mine.durationSec;
            m_hitsActive = 0;
            return;
        }
        set_state(FighterState::KO);
        m_stateTimer = 0;  // permanent until round reset
    } else {
        // Stun rules while active: Kakera ignores stun entirely, Oyashiro
        // skips every other hit ("avoids being stunned every other hit" —
        // the wiki doesn't say which of the pair, we skip the 2nd, 4th, …).
        bool stun = true;
        if (m_hyperActive) {
            ++m_hitsActive;
            if (mine.stunImmune ||
                (mine.stunEveryOtherHit && m_hitsActive % 2 == 0)) {
                stun = false;
            }
        }
        if (stun) {
            set_state(FighterState::Hit);
            m_stateTimer = FighterConstants::kHitStunFrames;
        }
    }
}

// ---------------------------------------------------------------------------
// Hypermode (spec §3.4)
// ---------------------------------------------------------------------------
void Fighter::gain_gauge(float fraction) {
    if (m_hyperActive || fraction <= 0.0f || !is_alive()) return;
    // The battle setting ゲージ増加量 (gauge rate) scales this once the
    // settings screen exists (spec §3.4).
    m_gauge = std::min(1.0f, m_gauge + fraction);
}

bool Fighter::try_activate_hypermode(Fighter* opponent) {
    const HypermodeParams& p = hypermode_params(m_hypermode);
    // Kakera has no manual activation — it fires on a lethal hit instead.
    if (p.autoOnDeath || m_hyperActive || !is_alive() || m_gauge < 1.0f) {
        return false;
    }

    m_gauge = 0.0f;
    m_hyperActive = true;
    m_hyperTimer = p.durationSec;
    m_hitsActive = 0;

    // Oyashiro's activation shoves anyone in melee range away, no damage.
    if (opponent && opponent->is_alive()) {
        const glm::vec3& tp = opponent->position();
        glm::vec3 away(tp.x - m_position.x, 0.0f, tp.z - m_position.z);
        const float dist = glm::length(away);
        if (dist > 0.0001f && dist <= FighterConstants::kMeleeRange) {
            opponent->apply_knockback(away / dist, FighterConstants::kRunSpeed);
        }
    }
    return true;
}

void Fighter::try_ex_move() {
    // EX content per character is un-RE'd; the binary reserves "shotFinal"
    // for it, so the stand-in fires that animation with an EX-tier shot.
    fire_shot(ShotTier::Ex);
}

void Fighter::update_hypermode(double dt, Fighter* opponent) {
    (void)opponent;
    if (!m_hyperActive) return;
    const HypermodeParams& p = hypermode_params(m_hypermode);

    m_hyperTimer -= static_cast<float>(dt);
    // Kakera trades its HP for the buff: 100% -> 1% over the duration, and
    // the mode ends (bonuses dropped, still alive at 1%) when it bottoms out.
    if (p.autoOnDeath) {
        const float drain = (FighterConstants::kMaxHP - 1.0f) / p.durationSec;
        m_hp = std::max(1, m_hp - static_cast<int>(drain * static_cast<float>(dt) + 0.5f));
        if (m_hp <= 1) m_hyperTimer = 0.0f;
    }
    if (m_hyperTimer <= 0.0f) {
        m_hyperActive = false;
        m_hyperTimer = 0.0f;
    }
}

void Fighter::apply_knockback(const glm::vec3& dir, float speed) {
    m_velocity = dir * speed;
    set_state(FighterState::Hit);
    m_stateTimer = FighterConstants::kHitStunFrames;
}

bool Fighter::try_melee_hit(Fighter& target) {
    if (m_state != FighterState::AttackA && m_state != FighterState::AttackB) {
        return false;
    }
    if (m_didHitThisSwing || !target.is_alive()) {
        return false;
    }
    // Active window: skip the first few startup frames so the swing has
    // to actually come out (mirrors +0xa0 action-frames counting down).
    const int elapsed = FighterConstants::kAttackFrames - m_stateTimer;
    if (elapsed < 5) {
        return false;
    }

    const float dx = target.m_position.x - m_position.x;
    const float dz = target.m_position.z - m_position.z;
    const float distSq = dx * dx + dz * dz;
    const float range = FighterConstants::kMeleeRange;
    if (distSq > range * range) {
        return false;
    }

    m_didHitThisSwing = true;
    const int dmg = (m_state == FighterState::AttackB)
        ? FighterConstants::kHeavyDamage
        : FighterConstants::kLightDamage;
    target.take_damage(dmg, this);
    return true;
}

float Fighter::charge_hold_frac() const {
    float f = m_chargeHeld / FighterConstants::kRedHoldSec;
    if (f < 0.0f) f = 0.0f;
    if (f > 1.0f) f = 1.0f;
    return f;
}

ShotTier Fighter::charge_tier() const {
    if (m_chargeHeld >= FighterConstants::kRedHoldSec)    return ShotTier::Red;
    if (m_chargeHeld >= FighterConstants::kYellowHoldSec) return ShotTier::Yellow;
    return ShotTier::Tap;
}

void Fighter::try_jump() {
    m_stamina = std::max(0.0f, m_stamina - FighterConstants::kJumpStamina);
    m_grounded = false;
    m_vy = FighterConstants::kJumpSpeed;
    set_state(FighterState::Jump);
    m_stateTimer = 0;  // physics-driven: gravity/landing own this state
}

bool Fighter::try_dash(input::Action dir) {
    // Stamina gate (spec §3.4: empty = no dash) and the once-per-airtime
    // rule for air dashes.
    if (m_stamina < FighterConstants::kDashStamina) return false;
    if (!m_grounded && m_airDashed) return false;

    // Facing-relative dash: Up is toward the opponent (the camera sits
    // behind us, so screen-up ≈ forward), Down peels away, Left/Right
    // sidestep. Right = up × facing (left-handed yaw=0-faces-+Z world).
    const float fx = std::sin(m_facing);
    const float fz = std::cos(m_facing);
    glm::vec3 d(0, 0, 0);
    if (dir == input::Action::Up)         d = glm::vec3(fx, 0, fz);
    else if (dir == input::Action::Down)  d = glm::vec3(-fx, 0, -fz);
    else if (dir == input::Action::Right)  d = glm::vec3(fz, 0, -fx);
    else                                  d = glm::vec3(-fz, 0, fx);

    m_stamina -= FighterConstants::kDashStamina;
    m_dashDir = d;
    m_dashAir = !m_grounded;
    if (m_dashAir) {
        m_airDashed = true;
        m_vy = 0.0f;  // air dash hangs: no fall during the window
        m_dashSpeed = FighterConstants::kAirDashSpeed;
    } else {
        m_dashSpeed = FighterConstants::kRunSpeed;
    }
    set_state(FighterState::Run);
    m_stateTimer = FighterConstants::kDashFrames;
    return true;
}

void Fighter::try_fire() { fire_shot(charge_tier()); }

void Fighter::fire_shot(ShotTier tier) {
    const ShotParams p = shot_params(tier);
    // Tap draws MAIN, charged tiers and the EX move draw CHARGE.
    AmmoStock& stock = (tier == ShotTier::Tap) ? m_main : m_charge;
    const float cost = (tier == ShotTier::Tap) ? p.mainCost : p.chargeCost;
    if (m_reloadTimer > 0 || !stock.can_spend(cost)) return;  // reloadNG: drop
    stock.spend(cost);
    m_reloadTimer = p.reloadFrames;

    // Muzzle ahead of the fighter at chest height, aimed along facing
    // (yaw=0 faces +Z — same convention as update_facing).
    const glm::vec3 dir(std::sin(m_facing), 0.0f, std::cos(m_facing));
    m_pending.armed = true;
    m_pending.tier  = tier;
    m_pending.dir   = dir;
    m_pending.pos   = m_position + dir * FighterConstants::kMuzzleForward;
    m_pending.pos.y += FighterConstants::kMuzzleHeight;

    switch (tier) {
        case ShotTier::Tap:    set_state(FighterState::ShootA);    break;
        case ShotTier::Yellow: set_state(FighterState::ShootB);    break;
        case ShotTier::Red:    set_state(FighterState::ShootC);    break;
        case ShotTier::Ex:     set_state(FighterState::ShotFinal); break;
    }
    m_stateTimer = FighterConstants::kShotFrames;
}

PendingShot Fighter::take_pending_shot() {
    PendingShot out = m_pending;
    m_pending.armed = false;
    return out;
}

// ---------------------------------------------------------------------------
// Render data — the DX9 render(IDirect3DDevice9*) split (PORT NOTES 4)
// ---------------------------------------------------------------------------
glm::mat4 Fighter::modelMatrix() const {
    // The original game uses D3DXMatrixRotationY + D3DXMatrixTranslation and
    // composes rot * trans in the row-vector convention (fighter.cpp:667-672),
    // i.e. rotate then translate → T * R for glm's column-vector matrices.
    //
    // The yaw carries a half turn that the port dropped.
    //
    // The original's world-matrix update rotates by -(angle + 90°) (FUN_00420b30 at
    // 0x420b30: D3DXMatrixRotationY((field_5c + 90 + field_64 + field_30) * -pi/180)),
    // and the aim point derived from the same angle is pos + (x, 145, z) with x/z its
    // sine/cosine pair (FUN_00420880 at 0x420880). For one fixed model axis to land on
    // that direction at EVERY yaw, the angle must be measured from +X (angle = 90° -
    // yaw): with a yaw-based angle, -(angle + 90°) swings the front by 2·yaw instead.
    // In this tree's convention, forward = (sin yaw, 0, cos yaw) (fighter.cpp:667),
    // that is Ry(yaw + 180°).
    //
    // The rigs are authored facing -Z, which is why the half turn belongs here:
    //   * their own geometry puts the face at -Z — data/rena/00.X's "eye" mesh (22
    //     verts, y 112..124) spans z -5.9..+1.1 while the hair spans -12.3..+26.4, and
    //     both ankle→ball vectors are (0, -14.2, -10.6) / (0, -14.5, -11.0). The frames
    //     those meshes hang off are identity and no bind frame carries a half turn
    //     (Bip00's is 89.2° about Y, the meshes' own is identity);
    //   * an identity model matrix from a -Z camera shows her face, and the DX9
    //     reference draws exactly that — it sets D3DTS_WORLD to identity for skinned
    //     meshes (x_model_loader.cpp:711) — yet from the +Z camera its log records at
    //     (183,500,779) with the fighter at (0,200,0) it shows her back
    //     (tests/parity-baseline/captures/fighter-p1-rena.png);
    //   * the print the arena camera was fitted to (docs/reference/battle-hud.webp)
    //     shows the player's back with the eye behind her.
    return glm::translate(glm::mat4(1.0f), m_position) *
           glm::rotate(glm::mat4(1.0f), m_facing + glm::pi<float>(),
                       glm::vec3(0.0f, 1.0f, 0.0f));
}

game::FighterPose Fighter::pose() const {
    game::FighterPose p;
    p.position  = m_position;
    p.facingYaw = m_facing;
    p.animTime  = m_anim ? static_cast<float>(m_anim->time()) : 0.0f;
    p.alive     = is_alive();
    return p;
}

float Fighter::hyper_pulse() const {
    return 0.5f + 0.5f * std::sin(static_cast<float>(m_time) * 8.0f);
}

float Fighter::aura_radius() const {
    return 56.0f + 4.0f * hyper_pulse();
}

Rgb Fighter::aura_color() const {
    // Additive light over the arena's bright ground saturates to white fast;
    // this keeps the mode colour readable (fighter.cpp:649-653).
    const int alpha = static_cast<int>(70.0f + 40.0f * hyper_pulse());
    const Rgb base = hypermode_params(m_hypermode).aura;
    return packArgb(static_cast<std::uint8_t>(alpha), rgbR(base), rgbG(base),
                    rgbB(base));
}

}  // namespace gameplay
