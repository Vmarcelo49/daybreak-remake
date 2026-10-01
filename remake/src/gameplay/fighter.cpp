// =============================================================================
//  fighter.cpp — state machine + movement + animation switching.
//
//  Mirrors the original game's fcn.0041f580 (per-player update) and
//  fcn.00420b30 (world matrix update).  The state machine is simplified
//  but follows the same structure: check timers → check input → transition
//  state → update movement → update animation.
// =============================================================================
#include "fighter.h"

#include <algorithm>
#include <cmath>
#include <cstdio>

namespace daybreak::gameplay {

void Fighter::init(XModel* model, const D3DXVECTOR3& pos, float facing) {
    m_model = model;
    m_position = pos;
    m_facing = facing;
    m_velocity = D3DXVECTOR3(0, 0, 0);
    m_hp = FighterConstants::kMaxHP;
    m_stamina = FighterConstants::kMaxStamina;
    m_state = FighterState::BattleStart;
    m_stateTimer = FighterConstants::kBattleStartFrames;
    m_animSetIdx = -1;
    try_switch_animation();
}

void Fighter::reset(const D3DXVECTOR3& pos, float facing) {
    m_position = pos;
    m_facing = facing;
    m_velocity = D3DXVECTOR3(0, 0, 0);
    m_hp = FighterConstants::kMaxHP;
    m_stamina = FighterConstants::kMaxStamina;
    m_state = FighterState::BattleStart;
    m_stateTimer = FighterConstants::kBattleStartFrames;
    m_animSetIdx = -1;
    try_switch_animation();
}

bool Fighter::can_act() const {
    return m_state == FighterState::Idle || m_state == FighterState::Walk ||
           m_state == FighterState::Run;
}

bool Fighter::can_move() const {
    return m_state == FighterState::Idle || m_state == FighterState::Walk ||
           m_state == FighterState::Run;
}

void Fighter::update(const input::PlayerInput* input, const Fighter* opponent, double dt) {
    // 1. Decrement state timer (mirrors +0xa0 in fcn.0041f580).
    if (m_stateTimer > 0) {
        --m_stateTimer;
        if (m_stateTimer == 0) {
            if (m_state != FighterState::KO && m_state != FighterState::TagOut) {
                set_state(FighterState::Idle);
            }
        }
    }

    // 2. Update state machine (check input, transition states).
    if (can_act() && input) {
        update_state_machine(input, dt);
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

    // 5. Regenerate stamina.
    if (m_stamina < FighterConstants::kMaxStamina && can_act()) {
        m_stamina = std::min(m_stamina + 1, FighterConstants::kMaxStamina);
    }

    // 6. Update the model's animation (advance time).
    if (m_model) {
        m_model->update(dt);
    }
}

void Fighter::update_state_machine(const input::PlayerInput* input, double dt) {
    if (!input) return;

    // AttackA (melee key in the original: X). Provisional mapping —
    // see input_manager.h (no dedicated heavy key exists).
    if (input->just_pressed[input::Action::AttackA]) {
        set_state(FighterState::AttackA);
        m_stateTimer = FighterConstants::kAttackFrames;
        return;
    }

    // AttackB (heavy stand-in — unbound by default; see input_manager.h).
    if (input->just_pressed[input::Action::AttackB]) {
        set_state(FighterState::AttackB);
        m_stateTimer = FighterConstants::kAttackFrames;
        return;
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

void Fighter::update_movement(const input::PlayerInput* input, const Fighter* opp, double dt) {
    if (!input) return;

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
        if (m_state == FighterState::Run) speed = FighterConstants::kRunSpeed;

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

    const char* name = state_to_anim_name(new_state);
    if (name) {
        std::printf("[daybreak] fighter state → %s (timer=%d)\n",
                    name, m_stateTimer);
    }
}

void Fighter::try_switch_animation() {
    if (!m_model) return;
    if (m_animSetIdx >= 0) return;  // already set for this state

    const char* anim_name = state_to_anim_name(m_state);
    if (!anim_name) return;

    // The XModel's switch_to_animation(name) method iterates the
    // ID3DXAnimationController's animation sets and calls lstrcmpiA
    // (case-insensitive) to find the matching one.
    if (m_model->switch_to_animation(anim_name)) {
        m_animSetIdx = 0;  // mark as set (we don't track the exact index)
    } else {
        // (Many .X files don't have an "idle" animation; the default
        //  track 0 animation is the idle/standing pose.)
        if (m_model->num_animation_sets() > 0) {
            m_model->switch_to_animation(0);
            m_animSetIdx = 0;
        }
    }
}

void Fighter::take_damage(int amount) {
    if (m_state == FighterState::Guard) {
        // Blocking reduces damage to 20%.
        amount = std::max(1, amount / 5);
    }

    m_hp = std::max(0, m_hp - amount);
    std::printf("[daybreak] fighter took %d damage → HP=%d\n", amount, m_hp);

    if (m_hp <= 0) {
        set_state(FighterState::KO);
        m_stateTimer = 0;  // permanent until round reset
    } else {
        set_state(FighterState::Hit);
        m_stateTimer = FighterConstants::kHitStunFrames;
    }
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
    target.take_damage(dmg);
    return true;
}

void Fighter::render(IDirect3DDevice9* device) {
    if (!m_model || !device) return;

    // The original game uses D3DXMatrixRotationY + D3DXMatrixTranslation.
    D3DXMATRIX rot, trans, world;
    D3DXMatrixRotationY(&rot, m_facing);
    D3DXMatrixTranslation(&trans, m_position.x, m_position.y, m_position.z);
    world = rot * trans;
    device->SetTransform(D3DTS_WORLD, &world);

    m_model->render(device);
}

void Fighter::sync_target(daybreak::CameraTarget& target) const {
    target.position   = m_position;
    target.facing_yaw = m_facing;
    target.alive      = is_alive();
}

} // namespace daybreak::gameplay
