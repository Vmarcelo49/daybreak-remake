// FUN_0041f580 / FUN_00420b30: fighter update, move records and world pose.
// Recovered executable rules live separately in move_behavior.h; NN.dat owns
// phase/set selection, record geometry and material intervals.
#include "gameplay/fighter.h"
#include "gameplay/fixed_step.h"
#include "gameplay/move_behavior.h"
#include "gameplay/combat_volume.h"

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <utility>

#include <glm/gtc/matrix_transform.hpp>

namespace gameplay {
namespace {

// --- the two recovered damage chains (one place, so they cannot drift) --------------
// MELEE, FUN_00639160 @0x639160-0x6391b0 (dump :21-23):
//   victim[+0x7a4] -= ((((power * attacker[+0x7c8]) / 100) * victim[+0x7cc]) / 100) * 100
//                     / scene[+0x43cc];
// SHOT, FUN_00637950 @0x637950 (dump :317-328 and :425-431):
//   local_2c = ((tier * 100) / scene[+0x43cc]) * bullet[+0x3c] / 100;   // tier: victim
//   victim[+0x7a4] -= ((((baseDamage * local_2c) / 100) * attacker[+0x7c8]) / 100)
//                     * victim[+0x7cc]) / 100;
// The HP field is the record's FIRST damage slot — combat[0x00] / blob[0] (+0x30), named
// `baseDamage` in this port. The +0x44 slot (combat[0x05] / blob[5], `hpDamage`) is NOT HP
// damage: FUN_00637950:280 accumulates it into the victim's own gauge (and the melee path
// never reads it at all). Reading hpDamage here is what made every hit remove ~1 HP.
//
// The stat and setting factors are the live neutral values, cited where they are set:
//   attacker[+0x7c8] = 100   attack  (FUN_0043ded0 @0x43dee3-0x43dee6, reset every frame)
//   victim[+0x7cc]   = 50    defense (FUN_0043ded0 @0x43dee9-0x43dee9)
//   scene[+0x43cc]   = 100   the battle's health setting (FUN_00633ca0 @0x633cf3-0x633cf6)
// so a neutral melee hit is `power / 2` and a neutral first-hit shot is `baseDamage / 2`
// on the original's 10000-based pool. The port's HP runs 0..maxHP, so the recovered figure
// is scaled onto that range (the same convention the KO/Overkill economy already uses).
//
// NOT modelled, and deliberately: the combo damage scaling (the victim's +0x7b0 counter
// steps the shot chain's tier to 70/50/33% on later hits — the port has no combo counter),
// bullet[+0x3c]'s per-bullet multiplier (its condition is unrecovered), and the
// `baseDamage > 9999 && head hit` /3 rule (the port's shot test has no head/chest split).
// Each would only *reduce* damage, so the port is conservative, not generous.
inline constexpr int kPoolScale = 10000;         // the original's HP pool
inline constexpr int kNeutralAttackStat = 100;   // FUN_0043ded0 @0x43dee3
inline constexpr int kNeutralDefenseStat = 50;   // FUN_0043ded0 @0x43dee9
inline constexpr int kNeutralSetting = 100;      // FUN_00633ca0 @0x633cf3

// The melee chain, integer steps in the original's order (each division truncates).
int meleePoolDamage(int power) {
    if (power <= 0) return 0;
    return ((((power * kNeutralAttackStat) / 100) * kNeutralDefenseStat) / 100) * 100 /
           kNeutralSetting;
}

// The shot chain, first hit of a combo (tier 100) and no per-bullet multiplier.
int shotPoolDamage(int baseDamage) {
    if (baseDamage <= 0) return 0;
    const int tier = ((100 * 100) / kNeutralSetting) * 100 / 100;
    return ((((baseDamage * tier) / 100) * kNeutralAttackStat) / 100) * kNeutralDefenseStat / 100;
}

// The recovered 10000-based figure on the port's 0..maxHP range.
int portDamage(int poolDamage, int maxHP) {
    if (poolDamage <= 0 || maxHP <= 0) return 0;
    return static_cast<int>(static_cast<float>(poolDamage) * static_cast<float>(maxHP) /
                                static_cast<float>(kPoolScale) +
                            0.5f);
}

struct AnimationBlendRule {
    int characterIndex;
    int weaponId;
    int oldSet;
    int newSet;
};

constexpr AnimationBlendRule kRecoveredAnimationBlendRules[] = {
    // FUN_0064ab30 passes character/slot to FUN_00649790; (0,2) constructs
    // FUN_0064c880, whose vtable slot +0x20 is FUN_0064c8a0. NN.dat joins slot 2 to item 33.
    {0, kWeaponIds[0][2], 1, 31},
    {0, kWeaponIds[0][2], 1, 34},
    {0, kWeaponIds[0][2], 1, 39},
};

bool has_recovered_animation_blend(int characterIndex, int weaponId,
                                  int oldSet, int newSet) {
    for (const AnimationBlendRule& rule : kRecoveredAnimationBlendRules)
        if (rule.characterIndex == characterIndex && rule.weaponId == weaponId &&
            rule.oldSet == oldSet && rule.newSet == newSet)
            return true;
    return false;
}

}  // namespace

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
    m_safePosition = pos;
    m_facing = facing;
    m_velocity = glm::vec3(0, 0, 0);
    m_hp = m_maxHP;
    m_stamina = static_cast<float>(FighterConstants::kMaxStamina);
    m_state = FighterState::BattleStart;
    m_stateTimer = FighterConstants::kBattleStartFrames;
    m_attackMoveId = -1;   // no swing in flight across a round reset
    m_dashMoveId = -1;
    m_phaseIndex = 0;
    m_moveElapsedTicks = 0;
    m_swing = MeleeSwing{};
    m_animSetIdx = -1;   // bind() looked the previous state up; BattleStart wins
    clear_tracks();      // a round reset is a fresh bind, never a blend
    apply_weapon_ammo();
    m_chargeHeld = 0.0f;
    m_reloadTimer = 0;
    m_pending = PendingShot{};
    m_pendingShots.clear();
    m_shotMoveId = -1;
    m_moveSpeed = 0.f;
    m_moveCounter = 0;
    m_movePitch = 0.f;
    m_holdTicks = 0;
    m_actionCamera = 0;
    m_chainContact = false;
    m_previousWalkInput = {};
    m_propActive = {false, false};
    for (auto& trail : m_trails) trail.reset();
    m_vy = 0.0f;
    m_grounded = true;
    m_guardExhausted = false;
    m_groundY = pos.y;
    m_flyLeft = FighterConstants::kFlyTimeSec;
    m_dashAir = false;
    m_airDashed = false;
    try_switch_animation();
}

void Fighter::reset(const glm::vec3& pos, float facing) {
    m_position = pos;
    m_safePosition = pos;
    m_facing = facing;
    m_velocity = glm::vec3(0, 0, 0);
    m_hp = m_maxHP;
    m_stamina = static_cast<float>(FighterConstants::kMaxStamina);
    m_state = FighterState::BattleStart;
    m_stateTimer = FighterConstants::kBattleStartFrames;
    m_attackMoveId = -1;
    m_dashMoveId = -1;
    m_phaseIndex = 0;
    m_moveElapsedTicks = 0;
    m_swing = MeleeSwing{};
    m_animSetIdx = -1;
    clear_tracks();      // same fresh-bind rule as init()
    m_vy = 0.0f;
    m_grounded = true;
    m_guardExhausted = false;
    m_groundY = pos.y;
    m_flyLeft = FighterConstants::kFlyTimeSec;
    m_dashAir = false;
    m_airDashed = false;
    // FUN_00435660 restores round capacity while retaining refill/interval progress.
    restore_ammo();
    m_chargeHeld = 0.0f;
    m_reloadTimer = 0;
    m_pending = PendingShot{};
    m_pendingShots.clear();
    m_shotMoveId = -1;
    m_moveSpeed = 0.f;
    m_moveCounter = 0;
    m_movePitch = 0.f;
    m_holdTicks = 0;
    m_actionCamera = 0;
    m_chainContact = false;
    m_previousWalkInput = {};
    m_propActive = {false, false};
    for (auto& trail : m_trails) trail.reset();
    m_gauge = 0.0f;
    m_hyperActive = false;
    m_hyperTimer = 0.0f;
    m_hitsActive = 0;
    try_switch_animation();
}

void Fighter::begin_round_entry() {
    // Use FUN_00421bd0's Y=1000 / move 0xc2 descent for round entry. The
    // port keeps at least 800 units of drop above higher support floors.
    m_position.y = std::max(FighterConstants::kRespawnAirY, m_groundY + 800.f);
    m_velocity = glm::vec3(0.f);
    m_vy = 0.f;
    m_grounded = false;
    m_respawnLock = true;
    m_state = FighterState::BattleStart;
    m_stateTimer = 0;
    m_animSetIdx = -1;
    clear_tracks();
    try_switch_animation();
}

void Fighter::respawn(const glm::vec3& spawn, float facing, float airY) {
    // FUN_004219a0's state restore, then FUN_00421bd0's airborne reposition. The
    // fighter keeps its team and its spawn slot (the port's deliberate deviation from
    // the original's random X/Z inside the stage bounds).
    m_position = glm::vec3(spawn.x, airY, spawn.z);
    m_safePosition = spawn;
    m_facing = facing;
    m_velocity = glm::vec3(0, 0, 0);
    m_vy = 0.0f;
    m_grounded = false;   // FUN_00421bd0's Y is above the floor: the fighter falls in
    m_groundY = spawn.y;
    m_flyLeft = FighterConstants::kFlyTimeSec;
    m_dashAir = false;
    m_airDashed = false;
    m_hp = m_maxHP;
    m_stamina = static_cast<float>(FighterConstants::kMaxStamina);
    m_guardExhausted = false;
    // Move 0xc2 (194) plays on re-entry; its set is 43, which is exactly the set
    // state_to_anim_set(BattleStart) binds. The timer is held at 0 so the landing —
    // not a frame count — ends the pose.
    m_state = FighterState::BattleStart;
    m_stateTimer = 0;
    m_animSetIdx = -1;
    clear_tracks();
    m_attackMoveId = -1;
    m_dashMoveId = -1;
    m_phaseIndex = 0;
    m_swing = MeleeSwing{};
    m_chargeHeld = 0.0f;
    m_reloadTimer = 0;
    m_pending = PendingShot{};
    m_pendingShots.clear();
    m_shotMoveId = -1;
    m_moveSpeed = 0.f;
    m_moveElapsedTicks = 0;
    m_moveCounter = 0;
    m_movePitch = 0.f;
    m_holdTicks = 0;
    m_actionCamera = 0;
    m_chainContact = false;
    m_previousWalkInput = {};
    m_propActive = {false, false};
    for (auto& trail : m_trails) trail.reset();
    // FUN_004219a0 clears the KO-bonus latch (+0x84c = 0, @0x421a08-0x421a0b) and the
    // recovery fields; the magazines are restored from their own capacity by the same
    // per-player rule reset() uses (FUN_0041f580), and the pending credits belong to
    // the death that just ended.
    restore_ammo();
    m_koBonusLatch = false;
    m_koPending = false;
    m_koCredit = KoCredit{};
    m_overkillHits = 0;
    m_respawnLock = true;   // [fighter+0xaecb] = 1 (@0x421a6c): not targetable yet
    try_switch_animation();
}

bool Fighter::can_act() const {
    // The respawn re-entry is a control lock: FUN_004219a0 starts move 0xc2 and the
    // fighter cannot act again until it lands (move 0xc2's own descent state ends on
    // touchdown, FUN_00428510's case 0xc2: `[0x84] != 0 && [0x10] < 0` -> move 0x2c).
    if (m_respawnLock) return false;
    return m_state == FighterState::Idle || m_state == FighterState::Walk ||
           m_state == FighterState::Run || m_state == FighterState::Jump;
}

bool Fighter::can_move() const {
    return can_act();
}

void Fighter::update(const input::PlayerState* input, Fighter* opponent, double dt,
                     const game::physics::MovementCollision* collision) {
    m_time += dt;
    m_animationBoundThisUpdate = false;

    // Hypermode first: it can activate this frame (S), expire, or drain
    // Kakera HP, all before the state machine reads the mode's modifiers.
    update_hypermode(dt);

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

    // Guard is not actionable: release must bypass can_act(). Port rule until
    // the incoming-damage block flag is recovered (FUN_00431e70's voice keys
    // do not establish it). Exhaustion requires a release before another hold.
    const bool guardHeld = input && input->down[input::Action::Guard];
    if (!guardHeld) m_guardExhausted = false;
    if (m_state == FighterState::Guard && (!guardHeld || m_stamina <= 0.0f)) {
        if (guardHeld) m_guardExhausted = true;
        set_state(m_grounded ? FighterState::Idle : FighterState::Jump);
    }

    // 2. Update state machine (check input, transition states).
    // A lost action window (hit, KO) breaks any charge hold in progress.
    if (!can_act()) m_chargeHeld = 0.0f;
    if (m_state == FighterState::AttackA && input &&
        input->just_pressed[input::Action::AttackA] && move_program(m_moves)) {
        const CharacterMove* from = m_moves->find(m_attackMoveId);
        const CharacterMove* to = m_moves->find(m_attackMoveId + 1);
        const MoveEntry* record = current_move_record();
        // FUN_00445ee0: row 300->301->302 compares row priority and state bit 0x100.
        if (from && to && m_attackMoveId >= 300 && m_attackMoveId < 302 && record &&
            (record->stateFlags & 0x100) && from->cancelThreshold <= to->priority) {
            ++m_attackMoveId;
            build_melee_swing(m_attackMoveId);
            begin_melee_swing();
            m_phaseIndex = 0;
            m_moveElapsedTicks = 0;
            m_animSetIdx = -1;
            try_switch_animation();
        }
    } else if (input && shot_jump_cancel_pressed(input)) {
        // Pilot cancel (Rena 0, handler 0x43ffc0): the bundle's slot7 TSV sampled
        // jump out of shot move 400 at (phase 0, frame 20, flags 0x100) into state
        // 40 with runtime == expected, and no request at frame 0. Shot states are
        // not actionable, so the admission is evaluated here, outside the gate
        // below — mirroring the original, where slot7 runs its own input
        // evaluation instead of the normal action dispatch.
        try_jump();
    } else if (can_act() && input) {
        update_state_machine(input, opponent, dt);
    }
    m_inputFacing = opponent ? std::atan2(opponent->position().x - m_position.x,
                                         opponent->position().z - m_position.z) : m_facing;
    execute_move_program(opponent, input);
    // The ribbon samples the prop's own active latch, which the executor re-derives
    // every frame; keep the value this frame's move program produced before anything
    // below can bind a different row or phase.
    const std::array<bool, 2> propActive = m_propActive;
    // The swing clock drives startup/active/recovery (melee_rules.h). It advances on
    // every tick the attack state is held, including recovery, so the recovery window is
    // a real lockout rather than a label.
    if (m_state == FighterState::AttackA)
        ++m_meleeElapsed;

    // 3. Update movement (if the state allows it).
    const glm::vec3 movementStart = m_position;
    if (((m_state == FighterState::AttackA || m_shotMoveId >= 0) && move_program(m_moves)) ||
        (m_state == FighterState::Run && m_dashMoveId == 20 && locomotion(m_moves) && m_model)) {
        m_velocity = facing_relative(0.f, m_moveSpeed / static_cast<float>(dt));
        m_position += facing_relative(0.f, m_moveSpeed);
    } else if (can_move() && input) {
        update_movement(input, dt);
    } else {
        m_velocity *= 0.8f;
        m_position += m_velocity * static_cast<float>(dt);
    }
    if (collision) {
        // FUN_0041f580 owns the source's per-player update, while the collision mesh
        // contract comes from FUN_004011f0. Body size and step thresholds are port rules.
        const game::physics::MovementResult moved = collision->move(movementStart, m_position,
                                                                     m_grounded);
        m_position = moved.position;
        m_grounded = moved.grounded;
        if (m_grounded) {
            m_groundY = m_position.y;
            m_vy = 0.f;
        }
        if (dt > 0.0) {
            const float inverseDt = 1.f / static_cast<float>(dt);
            m_velocity.x = (m_position.x - movementStart.x) * inverseDt;
            m_velocity.z = (m_position.z - movementStart.z) * inverseDt;
        }
    }

    // Custom characters without a recovered handler retain the legacy turn rule.
    if (opponent && opponent->is_alive() && !locomotion(m_moves)) {
        update_facing(opponent, dt);
    }

    // 5. Stamina: grounded refill (fast after use — battle-stamina.webp)
    // plus block-hold drain. Dash/leap/flight spends happen at trigger
    // sites below; airtime never refills, so flight is a real budget.
    if (m_grounded && can_act() && !(m_state == FighterState::Run && m_dashMoveId == 20 &&
                                   locomotion(m_moves) && m_model)) {
        m_stamina = std::min(m_stamina + FighterConstants::kStaminaRegenSec *
                             static_cast<float>(dt),
                             static_cast<float>(FighterConstants::kMaxStamina));
    }
    if (m_state == FighterState::Guard) {
        m_stamina = std::max(0.0f, m_stamina - FighterConstants::kGuardDrainSec *
                             static_cast<float>(dt));
        if (m_stamina <= 0.0f) {
            m_guardExhausted = true;
            set_state(m_grounded ? FighterState::Idle : FighterState::Jump);
        }
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
        const float previousY = m_position.y;
        m_position.y += m_vy * step;
        const float ceiling = m_groundY + FighterConstants::kFlyMaxAlt;
        // FUN_00421bd0 starts descent above the flight cap; clamping it here
        // teleports the entrant downward instead of letting gravity land it.
        if (m_position.y > ceiling && !m_respawnLock) {
            m_position.y = ceiling;
            if (m_vy > 0.0f) m_vy = 0.0f;
        }
        bool landed = false;
        if (collision && collision->hasGround() && m_vy <= 0.f &&
            m_position.y <= previousY) {
            const game::physics::GroundHit support = collision->groundAt(
                m_position.x, m_position.z, previousY, 1.f,
                std::max(0.f, previousY - m_position.y) + 1.f);
            if (support.hit) {
                m_position.y = support.height;
                m_groundY = support.height;
                landed = true;
            }
        } else if ((!collision || !collision->hasGround()) && m_position.y <= m_groundY) {
            m_position.y = m_groundY;
            landed = true;
        }
        if (landed) {
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

    if (collision) {
        if (!collision->validPosition(m_position)) {
            // An invalid override or a fall beyond the stage mesh returns to the last
            // supported point. Match::reset projects env.dat spawns before this can run.
            m_position = m_safePosition;
            m_groundY = m_safePosition.y;
            m_velocity = glm::vec3(0.f);
            m_vy = 0.f;
            m_grounded = true;
            m_flyLeft = FighterConstants::kFlyTimeSec;
            m_dashAir = false;
            m_airDashed = false;
        } else if (m_grounded) {
            m_safePosition = m_position;
        }
    }

    // The respawn re-entry ends the moment the fighter is back on its feet: the
    // original's move 0xc2 hands over to move 0x2c on touchdown, which is also when
    // [fighter+0xaecb] stops mattering (FUN_004201a0 zeroes it every frame).
    if (m_respawnLock && m_grounded) {
        m_respawnLock = false;
        if (m_state == FighterState::BattleStart) set_state(FighterState::Idle);
    }

    // FUN_0043ded0 sets both refill steps; FUN_0041f580 then ticks magazines once.
    if (m_weapon) {
        const unsigned refill = !m_hyperActive ? 1u : m_hypermode == Hypermode::Friendship ? 3u
                                                    : m_hypermode == Hypermode::Kakera ? 2u : 1u;
        for (auto& magazine : m_shootingMagazines) {
            magazine.refillStep = refill;
            magazine.tick();
        }
    } else {
        const HypermodeParams& hyp = hypermode_params(m_hypermode);
        m_main.recharge(dt, m_hyperActive ? hyp.mainRechargeMul : 1.f);
        m_charge.recharge(dt, m_hyperActive ? hyp.chargeRechargeMul : 1.f);
    }
    if (m_reloadTimer > 0) --m_reloadTimer;

    // FUN_0041f580 samples elapsed * 0.016, independently of host time.
    if (m_anim) {
        // Original state/phase dispatch runs before its common animation update
        // (FUN_00634f60 → FUN_0041f580), so bind a section before advancing its
        // playhead and applying any eligible class blend for this same tick. A
        // FUN_00421100 bind resets both elapsed counters; the common update leaves
        // that newly selected set at position zero on this tick.
        refresh_state_move();
        advance_animation_phase();
        if (m_moves && m_animate) {
            m_anim->setTrackPosition(m_blendTicks >= 0 ? 1 : 0,
                                    m_moveElapsedTicks * kOriginalAnimationTick);
            if (m_blendTicks < 0)
                m_anim->setTrackPosition(1, m_moveElapsedTicks * kOriginalAnimationTick);
        } else if (m_animate && !m_animationBoundThisUpdate) {
            m_anim->advanceTime(std::min(dt, 0.1));
        }
        // The recovered class-specific blend counter advances once per update,
        // matching FUN_0041f580's per-tick weight calculation.
        tick_blend();
    }
    if (m_weapon) {
        for (int hand = 0; hand < 2; ++hand) {
            if (hand >= m_weapon->slotCount) continue;
            const auto& slot = m_weapon->slots[hand];
            const std::string bone = hand ? "Bip01_Prop2" : "Bip01_Prop1";
            // Anchors 3..5 and 6..8 are the two endpoints FUN_00430120 samples.
            m_trails[static_cast<size_t>(hand)].step(propActive[static_cast<size_t>(hand)],
                bone_point(bone, glm::vec3(slot.ribbonRoot[0],slot.ribbonRoot[1],slot.ribbonRoot[2])),
                bone_point(bone, glm::vec3(slot.ribbonTip[0],slot.ribbonTip[1],slot.ribbonTip[2])));
        }
    }
}

void Fighter::update_state_machine(const input::PlayerState* input,
                                    Fighter* opponent, double dt) {
    if (!input) return;

    // Melee is ONE key in the original (X), and there is no second heavy attack to bind:
    // the corpus tests exactly one attack bit, `[fighter+0x10]+0x28 & 0x100` (1378 uses),
    // and no heavy/strong bit anywhere (input.h). The swing that plays is chosen by the
    // fighter's situation at the press — grounded, mid-dash or airborne — and by the bound
    // move table's chain rows, never by a second key (issue #10).
    if (input->just_pressed[input::Action::AttackA]) {
        // Combat tuning uses a situation-based candidate. The grounded neutral
        // animation uses a documented port inference to move 300; the source's
        // conditional transition does not prove this initial selector. Dash/air
        // animation candidates remain unresolved and use the visible fallback.
        // With no table bound the legacy shared swing plays (issue #26).
        const bool dashAttack = (m_state == FighterState::Run);
        const bool aerial = !m_grounded;
        set_aerial_attack(aerial);
        m_attackMoveId = resolve_attack_move(dashAttack, aerial);
        build_melee_swing(m_attackMoveId);
        set_state(FighterState::AttackA);
        m_stateTimer = m_model && m_moves && move_program(m_moves) ? 0 : m_swing.total_ticks();
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
        if (m_weapon) {
            m_shootingMagazines[1].charge();
            // A held C still releases a primary tap when the secondary stock is empty.
            m_chargeHeld = static_cast<float>(FixedStep::seconds);
        } else if (m_chargeHeld < red_hold_sec()) {
            m_chargeHeld += static_cast<float>(dt);
        }
    } else if (m_chargeHeld > 0.0f) {
        // Fire even on a sub-frame tap (charge_tier() then reads Tap).
        // Drops under reloadNG/no stock.
        try_fire();
        m_chargeHeld = 0.0f;
        if (m_pending.armed) return;
    }

    if (input->down[input::Action::Guard] && !m_guardExhausted && m_stamina > 0.0f) {
        set_state(FighterState::Guard);
        m_stateTimer = 0;
        m_guardStartedPending = true;  // the guard edge for the frame report (issue #16)
        return;
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

// Screen direction → world direction under the lock-on camera: the eye sits
// behind the facing looking at the locked opponent, so screen-up IS the facing.
// The original classifies the same stick-vs-facing relative angle into its
// directional variants (FUN_004235d0's 45°/135° sector bands feeding FUN_0043ded0's
// 0x14/0x17/0x18/0x1b selection) — the evidence that input is facing-relative
// rather than world-fixed. Up walks toward the locked opponent, not toward -Z.
glm::vec3 Fighter::facing_relative(float screenRight, float screenUp) const {
    const float fx = std::sin(m_facing);
    const float fz = std::cos(m_facing);
    // Right = up × facing in the left-handed yaw=0-faces-+Z world.
    return glm::vec3(fz, 0.0f, -fx) * screenRight + glm::vec3(fx, 0.0f, fz) * screenUp;
}

void Fighter::update_movement(const input::PlayerState* input, double dt) {
    if (!input) return;

    // Committed dash: steering is locked to the tapped direction for the
    // dash window (ground or air — m_dashDir was resolved at trigger time).
    if (m_state == FighterState::Run) {
        if (const auto* motion = locomotion(m_moves)) {
            if (m_dashMoveId == 20) m_dashSpeed = motion->forwardDash / static_cast<float>(dt);
        }
        m_velocity.x = m_dashDir.x * m_dashSpeed;
        m_velocity.z = m_dashDir.z * m_dashSpeed;
        m_position += m_velocity * static_cast<float>(dt);
        return;
    }

    float screenRight = 0.0f, screenUp = 0.0f;

    if (std::abs(input->stick_x) > 8000 || std::abs(input->stick_y) > 8000) {
        screenRight = static_cast<float>(input->stick_x) / 32768.0f;
        screenUp = -static_cast<float>(input->stick_y) / 32768.0f;  // up is -Y
    } else {
        if (input->down[input::Action::Left])  screenRight -= 1.0f;
        if (input->down[input::Action::Right]) screenRight += 1.0f;
        if (input->down[input::Action::Up])    screenUp += 1.0f;
        if (input->down[input::Action::Down])  screenUp -= 1.0f;
    }

    // Facing-relative, like the dash below: screen-up is the facing direction.
    const float basis = locomotion(m_moves) ? m_inputFacing : m_facing;
    glm::vec3 dir = glm::vec3(std::cos(basis),0.f,-std::sin(basis))*screenRight +
                    glm::vec3(std::sin(basis),0.f,std::cos(basis))*screenUp;

    // Normalize the direction vector (mirrors D3DXVec3Normalize in the original).
    float len = glm::length(dir);
    if (len > 0.001f) {
        dir /= len;

        const auto* motion = locomotion(m_moves);
        float speed = motion ? motion->walk / static_cast<float>(dt) : FighterConstants::kWalkSpeed;
        if (!m_grounded) speed *= FighterConstants::kAirControl;

        if (motion && m_state == FighterState::Walk) {
            // FUN_00421780 / FUN_0042db10: input-relative yaw, shortest bounded step.
            const glm::vec2 inputDirection(screenRight, screenUp);
            if (inputDirection != m_previousWalkInput) m_walkTurnRate = 20.f;
            m_previousWalkInput = inputDirection;
            m_walkTurnRate = std::max(1.f, m_walkTurnRate - 1.f);
            const float desired = std::atan2(dir.x, dir.z);
            const float difference = std::remainder(desired - m_facing, glm::two_pi<float>());
            m_facing += std::clamp(difference, -glm::radians(m_walkTurnRate), glm::radians(m_walkTurnRate));
            // FUN_004202b0 translates along the current turn, so reversal travels an arc.
            dir = facing_relative(0.f, 1.f);
        }
        m_velocity.x = dir.x * speed;
        m_velocity.z = dir.z * speed;
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
    // glm::pi<float>() is bit-identical to the 3.14159265f literal that used to sit
    // here (both round to 0x40490fdb), and fighter.cpp:1496 already spells it that way.
    while (diff >  glm::pi<float>()) diff -= 2.0f * glm::pi<float>();
    while (diff < -glm::pi<float>()) diff += 2.0f * glm::pi<float>();

    m_facing += diff * FighterConstants::kTurnSpeed * static_cast<float>(dt);
}

void Fighter::set_state(FighterState new_state) {
    if (m_state == new_state) return;
    m_state = new_state;
    m_moveCounter = 0;
    m_movePitch = 0.f;
    m_holdTicks = 0;
    m_propActive = {false, false};
    m_actionCamera = 0;
    if (new_state != FighterState::ShootA && new_state != FighterState::ShootB &&
        new_state != FighterState::ShootC) m_shotMoveId = -1;
    // A state with no selector (Guard) leaves the running move alone: the source's
    // block branch never re-binds, so the move, its phase cursor and its clip keep
    // going. Every other state starts a fresh row and a fresh phase.
    if (state_has_animation_selector(new_state)) {
        m_animSetIdx = -1;  // force animation re-lookup
        m_phaseIndex = 0;
        m_moveElapsedTicks = 0;
    }
    // Leaving the attack state ends this swing: the per-victim hit set clears so a
    // fresh swing may connect again (issue #10's per-swing accounting).
    if (new_state == FighterState::AttackA) {
        m_chainContact = false;
        begin_melee_swing();
    }
    try_switch_animation();
}

void Fighter::set_animate(bool on) {
    if (m_animate == on) return;
    m_animate = on;
    m_animSetIdx = -1;
    m_animFallback = false;   // no set is bound while animation is off
    m_animNoSelector = false;  // and no clip is being held either
    m_blendTicks = -1;        // and no class-specific cross-fade is in flight
    clear_tracks();
    if (m_animate) try_switch_animation();
}

// No track may stay bound through a fresh bind: evalLocal then leaves every
// frame at its bind T/R/S, which is the pose the renderer uploads, and the
// next try_switch_animation() hard-cuts instead of blending from stale sets.
void Fighter::clear_tracks() {
    m_blendTicks = -1;
    m_blendTotal = 0;
    if (!m_anim) return;
    for (int t = 0; t < xm::Controller::kMaxTracks; ++t) {
        m_anim->setTrackEnable(t, false);
        m_anim->setTrackAnimationSet(t, -1);
    }
}

void Fighter::try_switch_animation() {
    if (!m_animate) return;
    if (!m_model || !m_anim) return;
    if (m_model->anims.empty()) return;

    const int move = state_move_id();
    m_boundMoveId = move;  // what refresh_state_move() compares against next tick

    if (!state_has_animation_selector(m_state)) {
        // No selector for this state (Guard): the source binds nothing, so the move
        // and the clip already playing continue. Only a state entered with nothing
        // bound (animation was off) needs a clip, and the standing set is that clip —
        // it is not a substituted guess, so it is not reported as a fallback.
        if (m_animSetIdx < 0) bind_animation_set(0);
        m_animNoSelector = true;
        m_animFallback = false;
        return;
    }
    if (m_animSetIdx >= 0) return;  // already set for this state

    // FUN_00421100 binds the current section tag through FUN_00421410. Resolve
    // it only from this fighter's bound NN.dat; there is no raw-set table.
    int want = -1;
    if (m_moves && move >= 0) {
        const CharacterMove* resolved = m_moves->find(move);
        if (resolved) want = resolved->phase_set_index(m_phaseIndex);
    }
    const int resolved =
        (want >= 0 && static_cast<std::size_t>(want) < m_model->anims.size())
            ? want
            : 0;
    const bool fallback = (resolved != want) || (want < 0);

    bind_animation_set(resolved);
    // Missing selectors/rows and invalid set indices use set 0 and remain
    // visible through anim_fallback(); they do not masquerade as recovered clips.
    m_animFallback = fallback;
    m_animNoSelector = false;
}

void Fighter::bind_animation_set(int setIndex) {
    // FUN_00421410 asks the character-class compatibility callback before it
    // blends. The recovered Rena+2 callback permits only 1→31/34/39. This port
    // method represents the full-bind path: rejected changes hard-bind both
    // remake tracks, matching FUN_00421100's calls for both source banks.
    const int currentSet = m_blendTicks >= 0
                               ? m_anim->trackAnimationSet(1)
                               : m_anim->trackAnimationSet(0);
    const int oldDuration = m_moves
                                ? m_moves->animation_set_transition_duration(currentSet)
                                : -1;
    const int newDuration = m_moves
                                ? m_moves->animation_set_transition_duration(setIndex)
                                : -1;
    if (currentSet >= 0 && currentSet != setIndex &&
        has_recovered_animation_blend(m_moves ? m_moves->character_index() : -1,
                                      m_moves ? m_moves->weapon_id() : 0,
                                      currentSet, setIndex) &&
        oldDuration > 0 && newDuration > 0) {
        m_anim->setTrackAnimationSet(0, currentSet);
        m_anim->setTrackWeight(0, 1.f);
        m_anim->setTrackAnimationSet(1, setIndex);
        m_anim->setTrackPosition(1, 0.0);
        m_anim->setTrackEnable(0, true);
        m_anim->setTrackEnable(1, true);
        // FUN_0063dad0 uses NN.dat +0x20 only to gate its elapsed counter.
        // The source clip's D3DX playback mode is not recovered here, so retain
        // the controller's existing looping policy instead of deriving it from that gate.
        m_anim->setTrackLoop(0, true);
        m_anim->setTrackLoop(1, true);
        m_anim->setTrackWeight(1, 0.f);
        // FUN_00421410 seeds from the old row; FUN_0041f580 normalizes with
        // the newly selected row. Both values are parsed from this NN.dat.
        m_blendTicks = oldDuration;
        m_blendTotal = newDuration;
    } else {
        m_anim->setAnimationBothTracks(setIndex, true);
        m_blendTicks = -1;
        m_blendTotal = 0;
    }
    m_animSetIdx = setIndex;
    m_animationBoundThisUpdate = true;
}

void Fighter::commit_blend() {
    if (!m_anim) return;
    const int cur = m_anim->trackAnimationSet(1);
    if (cur >= 0) {
        m_anim->setTrackAnimationSet(0, cur);
        m_anim->setTrackPosition(0, m_anim->trackPosition(1));
        m_anim->setTrackEnable(0, true);
        m_anim->setTrackLoop(0, m_anim->trackLoop(1));
    }
    m_anim->setTrackWeight(0, 1.f);
    m_anim->setTrackWeight(1, 0.f);
    m_blendTicks = -1;
}

void Fighter::tick_blend() {
    if (!m_anim || m_blendTicks < 0 || m_blendTotal <= 0) return;
    const float remaining = static_cast<float>(m_blendTicks);
    const float duration = static_cast<float>(m_blendTotal);
    // FUN_0041f580 evaluates the current counter before decrementing it. The
    // two sets in the recovered Rena+2 transition start with weights 1 and 0.
    m_anim->setTrackWeight(0, remaining / duration);
    m_anim->setTrackWeight(1, (duration - remaining) / duration);
    --m_blendTicks;
    if (m_blendTicks < 0) {
        commit_blend();
        m_anim->setTrackWeight(1, 1.f);
    }
}

const char* Fighter::anim_set_name() const {
    if (!m_model || m_animSetIdx < 0 ||
        static_cast<std::size_t>(m_animSetIdx) >= m_model->anims.size()) {
        return "";
    }
    return m_model->anims[static_cast<std::size_t>(m_animSetIdx)].name.c_str();
}

Fighter::DamageResult Fighter::take_damage(int amount, Fighter* source, int hitstunFrames,
                                           int hitCategory, bool shot) {
    if (!is_alive()) {
        // Already down: this is Overkill. The original credits exactly +1 per hit to
        // the victim's own side and does not touch HP, the KO clock or the death count
        // (FUN_00637950 @0x638e0d-0x638e37; the melee path credits nothing at all for
        // an already-dead body, FUN_00639160 @0x63938d-0x639393, and the port keeps
        // that: melee never offers a dead target).
        if (shot) ++m_overkillHits;
        return DamageResult::Overkill;
    }
    const HypermodeParams& mine = hypermode_params(m_hypermode);

    if (m_state == FighterState::Guard) {
        // Blocking reduces damage to 20% (PROVISIONAL: genre-standard, but the
        // original's guard damage gate is unmapped — see the unresolved guard
        // selector in state_to_move_id() in fighter.h). The floor applies only to a
        // positive amount: a record with no HP power must stay a no-damage contact even
        // against a guard, while 1..4 blocked damage keeps its historical 1.
        amount = amount > 0 ? std::max(1, amount / 5) : 0;
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
    // NO floor here. FUN_00637950's entry test is radius != 0 (0x6379e0, byte-verified)
    // and combat[0] is read only inside the HP math, so a record with power 0 contacts,
    // applies everything below and takes 0 HP. Clamping to 1 turned every zero-power
    // record into a 1-HP hit, which is neither what the record says nor what the
    // original does. Negative amounts cannot reach here (the chain floors at 0), but the
    // clamp also covered that, so keep a zero floor explicitly.
    amount = std::max(0, amount);

    // Gauge credit. NOTE: the record's combat[5]/[6] columns are NOT wired here, and that
    // is deliberate. In the original they accumulate the victim's/attacker's internal mode
    // gauges (FUN_00637950 @0x638321/@0x6383e6/@0x638493 write +0x838/+0x840/+0x83C), which
    // are 0..100 counters with their own thresholds. This port's gain_gauge() feeds
    // m_gauge, the HYPERMODE bar, which is the player-selected battle gauge (gaugePercent,
    // fighter.h) — a different mechanic with a different consumer. Routing the recovered
    // columns into it would report the right number through the wrong system, and would
    // also pick up m_gaugeRate. Until the port has the mode-gauge accumulators, the
    // damage-derived hyper credit below stands and the record's columns stay unread.
    if (source) source->gain_gauge(amount * hypermode_params(source->m_hypermode)
                                              .fillPerDamageDealt);
    gain_gauge(amount * mine.fillPerDamageTaken);

    // KNOCKBACK IS NOT APPLIED YET. combat[17]/[18] are the original's release offsets
    // (+0x87c/+0x878, FUN_00637950 @0x638633/@0x638645), but the port has no recovered unit
    // for them: the original writes them into a launch-velocity field, not into the port's
    // m_velocity, and nothing in the corpus fixes the conversion. Applying them at a
    // guessed scale would be invented motion, so a zero-power record currently contacts
    // (HP, hitstop, reaction) without recoiling. Recover the writer's units first.

    const int landed = std::min(m_hp, amount);
    m_stats.damageTaken += landed;
    if (source) source->m_stats.damageDealt += landed;
    // The KO credit needs the UNCLAMPED result: the original's overkill term is
    // computed from how far below zero HP went (FUN_00639160 @0x639399-0x6393a5).
    const int hpAfter = m_hp - amount;
    const int overkillHp = hpAfter < 0 ? -hpAfter : 0;
    m_hp = std::max(0, hpAfter);

    if (m_hp <= 0) {
        // Kakera fires on the killing blow instead of dying (spec §3.4).
        if (mine.autoOnDeath && !m_hyperActive && m_gauge >= 1.0f) {
            m_hp = m_maxHP;
            m_gauge = 0.0f;
            m_hyperActive = true;
            m_hyperTimer = mine.durationSec;
            m_hitsActive = 0;
            return DamageResult::Hit;
        }
        ++m_stats.deaths;
        if (source) ++source->m_stats.kos;
        set_state(FighterState::KO);
        m_stateTimer = 0;  // permanent until round reset
        // The credit the scene hands to MatchEconomy (FUN_0063ba80 picks the victim's
        // reaction move from the blow's category and its own airborne flag).
        const int reaction = reactionMoveForHitCategory(hitCategory, airborne());
        const bool latchFree = !shot || !m_koBonusLatch;
        const bool bonus = downedReactionBonus(reaction, reaction_move(), latchFree, shot);
        if (bonus && shot) m_koBonusLatch = true;
        m_koCredit = KoCredit{overkillHp, bonus, shot};
        m_koPending = true;
        return DamageResult::Ko;
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
            // The stun a weapon inflicts is that weapon's own (FUN_00637950:308); a
            // weapon that specifies none keeps the shared default.
            m_stateTimer = hitstunFrames > 0 ? hitstunFrames
                                             : FighterConstants::kHitStunFrames;
        }
    }
    return DamageResult::Hit;
}

// ---------------------------------------------------------------------------
// Hypermode (spec §3.4)
// ---------------------------------------------------------------------------
void Fighter::gain_gauge(float fraction) {
    if (m_hyperActive || fraction <= 0.0f || !is_alive()) return;
    // DAT_006cf3bc is the select page gauge percentage (FUN_0040acb0).
    m_gauge = std::min(1.0f, m_gauge + fraction * m_gaugeRate);
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
    m_hyperStartedPending = true;  // the activation edge for the frame report (issue #16)

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
    // EX content per character is un-RE'd. `shotFinal` is a provisional port
    // label; the corpus confirms a conditional numeric move-503 follow-up, not a cue binding.
    fire_shot(ShotTier::Ex);
}

void Fighter::update_hypermode(double dt) {
    if (!m_hyperActive) return;
    const HypermodeParams& p = hypermode_params(m_hypermode);

    m_hyperTimer -= static_cast<float>(dt);
    // Kakera trades its HP for the buff: 100% -> 1% over the duration, and
    // the mode ends (bonuses dropped, still alive at 1%) when it bottoms out.
    if (p.autoOnDeath) {
        const float drain = (m_maxHP - 1.0f) / p.durationSec;
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

bool Fighter::try_melee_hit(Fighter& target, const game::physics::MovementCollision* collision) {
    // Only the light/chain melee plays this path; the EX and shots go elsewhere.
    if (m_state != FighterState::AttackA) return false;
    if (!melee_in_active()) return false;
    if (!target.is_alive()) return false;

    if (const MoveEntry* record = current_move_record()) {
        const auto point = [&](const std::array<float, 3>& p) {
            return bone_point(record->boneName, glm::vec3(p[0], p[1], p[2]));
        };
        const glm::vec3 start = point(record->anchor);
        const glm::vec3 end = point(record->endAnchor);
        const glm::vec3 head = target.m_position + target.hurtbox_anchor_offset(0);
        const glm::vec3 chest = target.m_position + target.hurtbox_anchor_offset(1);
        if (!combatVolumeHits(start,end,record->collisionShape != 0,
                              static_cast<float>(record->hitRadius),head,chest)) return false;
        if (collision && !collision->empty() &&
            game::physics::segmentBlocked(start, chest, collision->movementMesh())) return false;
        const int damage = portDamage(meleePoolDamage(record->baseDamage), m_maxHP);
        target.take_damage(damage, this, record->defenderHitstun, record->reactionMove);
        return true;
    }

    // The recovered hitbox: FUN_00637950 picks a 3D sphere test (FUN_0063b470) whose
    // predicate is dist < 30.0 + weaponRadius, run against the victim's TWO anchors.
    // FUN_0063dad0:238-243 builds those from the Head and Spine bones, so a fighter is
    // a head sphere and a chest sphere and nothing else - which is the real vertical
    // limit, and why a swing cannot reach legs.
    //
    // The radius is the swing's own weapon hitRadius when a move table is bound
    // (issue #26: e.g. rena move 300's 20); otherwise the shared legacy number stands in
    // for the unrecovered weapon+0x24. The SHAPE is recovered in both cases.
    const float bodyHeight = game::physics::MovementCollision::kFighterHeight;
    const float attackerY  = m_position.y + bodyHeight * m_meleeRules.chestHeightFrac;
    const float headY       = target.m_position.y + target.hurtbox_anchor_offset(0).y;
    const float chestY      = target.m_position.y + target.hurtbox_anchor_offset(1).y;
    const float dx = target.m_position.x - m_position.x;
    const float dz = target.m_position.z - m_position.z;
    const float horizontalSq = dx * dx + dz * dz;

    const float toHead = (horizontalSq) + (headY - attackerY) * (headY - attackerY);
    const float toChest = (horizontalSq) + (chestY - attackerY) * (chestY - attackerY);
    // Either anchor connecting is a hit, so the NEARER one decides; the predicate itself
    // is melee_rules.h's (FUN_0063b470), the same one melee_reach() is written in terms of.
    if (!m_meleeRules.sphere_hits(std::min(toHead, toChest), m_swing.radius)) return false;

    // Solid barriers: the swing must not reach through the stage. #7's collision already
    // answers segment queries for the camera; the fighter's own mesh is the same
    // collision.x, so a melee line uses it too. A missing mesh is permissive, which is
    // what the reference does when collision.x is absent.
    if (collision && !collision->empty()) {
        const glm::vec3 from = m_position + glm::vec3(0.0f, attackerY - m_position.y, 0.0f);
        const glm::vec3 to = target.m_position + glm::vec3(0.0f, chestY - target.m_position.y, 0.0f);
        if (game::physics::segmentBlocked(from, to, collision->movementMesh())) return false;
    }

    // A data-driven swing carries its move's own power (FUN_00639160's chain); the legacy
    // swing keeps the shared light value. There is no heavy variant: the corpus has one
    // melee input bit and no heavy bit at all (issue #10).
    const int dmg = m_swing.dataDriven ? m_swing.damage : FighterConstants::kLightDamage;
    target.take_damage(dmg, this, m_swing.hitstun);
    return true;
}

void Fighter::begin_melee_swing() {
    m_swingHits = 0;
    m_swingHitCount = 0;
    m_meleeElapsed = 0;
}

void Fighter::note_melee_hit(int victimIndex) {
    if (victimIndex < 0 || victimIndex >= kMatchFighterCount) return;
    m_swingHits |= (1u << victimIndex);
    ++m_swingHitCount;
    m_chainContact = true;
}

void Fighter::set_moves(const CharacterMoves* moves) {
    if (m_moves == moves) return;
    m_moves = moves;
    // Match binds the table after init/reset; refresh the current pose now so
    // round-start and movement states use the character's own phase tag.
    m_phaseIndex = 0;
    m_moveElapsedTicks = 0;
    m_animSetIdx = -1;
    try_switch_animation();
}

int Fighter::resolve_attack_move(bool dashAttack, bool aerial) const {
    if (!m_moves) return -1;
    if (dashAttack) {
        const int lunge = present_move(330);
        if (lunge >= 0) return lunge;
    } else if (aerial) {
        const int air = present_move(340);
        if (air >= 0) return air;
    } else {
        const int neutral = present_move(300);
        if (neutral >= 0) return neutral;
    }
    return -1;
}

int Fighter::present_move(int id) const {
    if (!m_moves) return -1;
    // A move counts when the table ships it with at least one phase (a costume
    // that drops the row's move must not resolve to a phaseless id).
    const CharacterMove* m = m_moves->find(id);
    return (m && m->first_set_index() >= 0) ? id : -1;
}

int Fighter::dash_move_for(input::Action dir) const {
    // The original selects dash move IDs through opaque state/cancel fields.
    // Up/Down → 20/27 is a ground-only port inference from the directional move
    // families; the dumps do not establish either raw-input or air-dash mapping.
    if (!m_moves || !m_grounded) return -1;
    if (dir == input::Action::Up) return present_move(20);
    if (dir == input::Action::Down) return present_move(27);
    return -1;
}

int Fighter::state_move_id() const {
    switch (m_state) {
        // The swing's move was chosen at the press by resolve_attack_move: 300
        // grounded neutral, 330 mid-dash, 340 airborne. Which of the three a fresh
        // press selects is still a port inference, but the presentation must play
        // the row that inference already bound — dropping 330/340 here is what made
        // a live aerial swing show set 0 while its own table row is set 88 (issue #31).
        case FighterState::AttackA:
            return present_move(m_attackMoveId);
        case FighterState::ShootA:
        case FighterState::ShootB:
        case FighterState::ShootC: return present_move(m_shotMoveId);
        case FighterState::Run:     return m_dashMoveId;
        case FighterState::Jump:    return jump_chain_move();
        // Guard binds nothing; see state_has_animation_selector for the recovered
        // block path. try_switch_animation holds the playing clip for it.
        case FighterState::Guard:   return -1;
        default:                    return state_to_move_id(m_state);
    }
}

int Fighter::jump_chain_move() const {
    // The source's air chain is three rows the move executor advances by physics:
    // live FUN_0043ffc0 case 0x28 binds 0x29 once FUN_004218c0's air gate passes,
    // and case 0x29 binds 0x2a once vy < 6.0/tick with the row's second section
    // active. Their phase tags are the shipped jump clips: 40 → [2] (startup),
    // 41 → [3,4] (leaving the ground, up momentum), 42 → [5,43] (down momentum,
    // falling). The port's single Jump label spans the whole airtime and resolves
    // the same three rows; each row still advances its own sections through
    // advance_animation_phase().
    if (!m_moves) return -1;
    // FUN_004218c0's gate is a per-character frame/phase budget this port does not
    // carry, and the port's leap is airborne on the press tick: one startup tick is
    // what plays the recovered move-40 set-2 clip without inventing a duration.
    if (m_grounded || m_jumpStartup) return present_move(40);
    if (m_vy >= FighterConstants::kJumpApexSpeed) return present_move(41);
    return present_move(42);
}

void Fighter::refresh_state_move() {
    // Only the air chain changes its move without a state change; every other port
    // state resolves one row and rebinds through set_state()/try_dash(). The source
    // rebinds the changed id through FUN_00421080, which resets the section cursor.
    if (m_state != FighterState::Jump) {
        m_jumpStartup = false;
        return;
    }
    const int move = state_move_id();
    m_jumpStartup = false;   // the launch tick's startup row is consumed either way
    if (move == m_boundMoveId) return;
    m_phaseIndex = 0;
    m_moveElapsedTicks = 0;
    m_animSetIdx = -1;
    try_switch_animation();
}

void Fighter::advance_animation_phase() {
    if (!m_model || !m_anim || !m_moves || m_model->anims.empty()) return;
    const int moveId = state_move_id();
    const CharacterMove* move = m_moves->find(moveId);
    if (!move || m_phaseIndex < 0 || m_phaseIndex >= move->sectionCount) return;

    const int set = move->phase_set_index(m_phaseIndex);
    if (set < 0 || static_cast<std::size_t>(set) >= m_model->anims.size()) return;
    if (!m_holdAnimation) ++m_moveElapsedTicks;
    if (m_moves->animation_set_phase_gate(set) != 0) return;

    const float ticksPerSecond = m_model->ticksPerSecond;
    if (!std::isfinite(ticksPerSecond) || ticksPerSecond <= 0.0f) return;
    const float setDuration = m_model->anims[static_cast<std::size_t>(set)].duration;
    if (!std::isfinite(setDuration) || setDuration < 0.0f) return;
    // FUN_0041e180 passes D3DX GetPeriod() through x87 ROUND (nearest-even at
    // the game's default FP mode); the native DLL matches duration/ticksPerSecond
    // for every set in Rena 00, Rika 01, and Akane 00.
    const int periodThreshold = static_cast<int>(std::nearbyint(
        (setDuration / ticksPerSecond) / kOriginalAnimationTick));
    // Original loader 0x41e839 divides GetPeriod by 0.016 before x87 rounding.
    if (periodThreshold >= m_moveElapsedTicks) return;

    if (m_phaseIndex + 1 == move->sectionCount) {
        if (m_state == FighterState::AttackA || m_state == FighterState::Run || m_state == FighterState::ShootA ||
            m_state == FighterState::ShootB || m_state == FighterState::ShootC)
            set_state(m_grounded ? FighterState::Idle : FighterState::Jump);
        return;
    }

    const int nextSet = move->phase_set_index(m_phaseIndex + 1);
    if (nextSet < 0 || static_cast<std::size_t>(nextSet) >= m_model->anims.size()) return;
    enter_phase(m_phaseIndex + 1);
}

void Fighter::enter_phase(int phase) {
    const CharacterMove* move = m_moves ? m_moves->find(state_move_id()) : nullptr;
    if (!move || phase < 0 || phase >= move->sectionCount) return;
    m_phaseIndex = phase;
    m_moveElapsedTicks = 0;
    m_holdTicks = 0;
    m_holdAnimation = true; // FUN_00421100's explicit transition returns before clock advance.
    if (m_anim) bind_animation_set(move->phase_set_index(phase));
    m_animFallback = false;
}

void Fighter::execute_move_program(Fighter* opponent, const input::PlayerState* input) {
    m_holdAnimation = false;
    // FUN_0043ffc0's prologue: slot0<-prop0, slot1<-prop1, then both props deactivated.
    // Hide and Active windows below re-state what this frame actually wants.
    m_propBound = {true, true};
    m_propActive = {false, false};
    const MoveProgram* program = move_program(m_moves);
    const auto* motion = locomotion(m_moves);
    const CharacterMove* move = m_moves ? m_moves->find(state_move_id()) : nullptr;
    if (move && m_model && m_phaseIndex + 1 == move->sectionCount &&
        (m_state == FighterState::AttackA ||
         (motion && m_state == FighterState::Run && m_dashMoveId == 20) || m_shotMoveId >= 0)) {
        const int set = move->phase_set_index(m_phaseIndex);
        if (set >= 0 && static_cast<size_t>(set) < m_model->anims.size() && m_model->ticksPerSecond > 0.f) {
            const int period = static_cast<int>(std::nearbyint(
                m_model->anims[static_cast<size_t>(set)].duration / m_model->ticksPerSecond / kOriginalAnimationTick));
            if (period <= m_moveElapsedTicks + 1) {
                set_state(m_grounded ? FighterState::Idle : FighterState::Jump);
                m_moveSpeed = 0.f;
                return;
            }
        }
    }
    if (motion && m_model && m_state == FighterState::Run && m_dashMoveId == 20) {
        // Constructor-bound handlers use the same phase contract with different
        // profile values. NN.dat supplies each phase's pose/gate/period.
        if (m_phaseIndex < 2) m_stamina = std::max(0.f,m_stamina-motion->dashDrain);
        if (m_phaseIndex == 0 && m_moveElapsedTicks == 0) {
            m_moveSpeed = motion->forwardDash;
            m_facing = m_inputFacing;
        }
        if (m_phaseIndex == 1) {
            float x = input ? float(input->down[input::Action::Right])-float(input->down[input::Action::Left]) : 0.f;
            float z = input ? float(input->down[input::Action::Up])-float(input->down[input::Action::Down]) : 0.f;
            if (input && (std::abs(input->stick_x)>8000 || std::abs(input->stick_y)>8000)) {
                x = static_cast<float>(input->stick_x); z = -static_cast<float>(input->stick_y);
            }
            if ((!x && !z) || m_stamina <= 0.f) { enter_phase(2); return; }
            const float target = m_inputFacing + std::atan2(x,z);
            const float diff = std::remainder(target-m_facing,glm::two_pi<float>());
            const float turn = glm::radians(motion->dashSteer);
            m_facing += std::clamp(diff,-turn,turn);
        }
        if (m_phaseIndex == 2) {
            m_moveSpeed = std::max(0.f,m_moveSpeed-motion->dashDecay);
            if (m_moveElapsedTicks == motion->dashHoldTick)
                m_holdAnimation = m_holdTicks++ < motion->dashHoldLength;
        }
    }
    if (!program) return;
    const glm::vec3 offset = opponent ? opponent->position() - m_position : glm::vec3(0.f);
    const float distanceSquared = glm::dot(offset, offset);
    for (size_t i = 0; i < program->count; ++i) {
        const auto& rule = program->rules[i];
        if (rule.move != state_move_id() || (rule.phase >= 0 && rule.phase != m_phaseIndex) ||
            m_moveElapsedTicks < rule.first || m_moveElapsedTicks > rule.last)
            continue;
        if (!rule_gate_holds(rule)) continue;
        switch (rule.operation) {
        case MoveOp::Speed:
            m_moveSpeed = opponent && rule.third > 0.f && distanceSquared < rule.third
                              ? rule.second : rule.value;
            break;
        case MoveOp::Decelerate: m_moveSpeed = std::max(0.f, m_moveSpeed - rule.value); break;
        case MoveOp::Turn:
            if (rule.second > 0.f && !m_chainContact) break;
            if (opponent) {
                const float target = std::atan2(offset.x, offset.z);
                const float difference = std::remainder(target - m_facing, glm::two_pi<float>());
                const float rate = glm::radians(rule.value);
                m_facing += std::clamp(difference, -rate, rate);
            }
            break;
        case MoveOp::Approach:
            if ((opponent && distanceSquared < rule.value) || m_moveElapsedTicks > rule.second) {
                enter_phase(static_cast<int>(rule.third));
                return;
            }
            break;
        case MoveOp::Launch:
            // The bodies' `for` loop around a request: the whole volley lands in this
            // tick, and each iteration re-draws its spread, which is what fans it out.
            for (int repeat = 0; repeat < std::max(1, rule.repeats); ++repeat)
                launch_bullet(static_cast<int>(rule.value), rule.origin, rule.aim,
                              rule.second, rule.third, rule.spread, opponent);
            break;
        case MoveOp::Hide: {
            const int slot = static_cast<int>(rule.value);
            if (slot >= 0 && slot < 2) m_propBound[static_cast<size_t>(slot)] = false;
            break;
        }
        case MoveOp::Active: {
            const int slot = static_cast<int>(rule.value);
            if (slot >= 0 && slot < 2) m_propActive[static_cast<size_t>(slot)] = true;
            break;
        }
        case MoveOp::Hold:
            // Per-rule hold progress (see m_holdRule): a newly matching rule restarts
            // the count, a continuing one keeps it. Single-hold moves behave exactly
            // as before — the latch only matters from the second Hold in one move.
            if (m_holdRule != &rule) { m_holdRule = &rule; m_holdTicks = 0; }
            m_holdAnimation = m_holdTicks++ < static_cast<int>(rule.value);
            break;
        // The bodies' scratch counters: `write_scratch(0x3e, 0)` at phase0/tick0 and
        // `actor_word_add(0x3e, 1)` after the fire checks, so a gate on the counter
        // reads the pre-increment value and a gated Hold that follows reads the
        // post-increment one. That ordering is what makes a frozen interval keep
        // counting while its clock is pinned.
        case MoveOp::CounterSet: m_moveCounter = static_cast<int>(rule.value); break;
        case MoveOp::Counter:    m_moveCounter += static_cast<int>(rule.value); break;
        // FUN_0042da80 -> FUN_0066b668 -> write_scratch(0x3c): the clamped target
        // elevation, truncated to int the way the original's int scratch is, stored for
        // the later requests that read source_float(0x3c) back.
        case MoveOp::CapturePitch:
            m_movePitch = capture_target_pitch(rule.second, rule.third, rule.value, opponent);
            break;
        case MoveOp::ActionCamera:
            if (m_chainContact) m_actionCamera = static_cast<int>(rule.value);
            break;
        }
    }
}

// FUN_0042da80 -> FUN_0066b668 -> write_scratch: the target elevation in whole
// degrees, as the original's integer scratch stores it. No opponent reads as
// elevation 0, matching atan2(0, 0). The bodies bound the scratch with two
// independent compares, so low/high are separate: most clamp symmetrically, but
// Mion 0's 450 clamps [-40, +45], and a nonzero snapDegrees reproduces the
// compare/assign mismatch (Keiichi's air tap and Mion 1's 460 compare +-30 and
// assign +-45) instead of clamping.
float Fighter::capture_target_pitch(float lowDegrees, float highDegrees,
                                     float snapDegrees, const Fighter* opponent) {
    float elevation = 0.f;
    if (opponent) {
        const glm::vec3 difference = opponent->position() - m_position;
        elevation = glm::degrees(std::atan2(difference.y,
                                            std::hypot(difference.x, difference.z)));
    }
    int pitch = static_cast<int>(elevation);
    const int low = -static_cast<int>(lowDegrees);
    const int high = static_cast<int>(highDegrees);
    if (snapDegrees != 0.f) {
        const int assign = static_cast<int>(snapDegrees);
        if (pitch < low) pitch = -assign;
        else if (pitch > high) pitch = assign;
    } else {
        pitch = std::clamp(pitch, low, high);
    }
    return static_cast<float>(pitch);
}

bool Fighter::rule_gate_holds(const MoveRule& rule) const {
    if (rule.gate == kGateNone) return true;
    if ((rule.gate & kGatePowered) != 0 && !shoot_gate_powered()) return false;
    if ((rule.gate & kGateNormal) != 0 && shoot_gate_powered()) return false;
    if ((rule.gate & kGateCounter) != 0 && !(m_moveCounter > 0)) return false;
    if ((rule.gate & kGateCounterMod) != 0 && rule.gateValue > 0 &&
        (m_moveCounter % rule.gateValue) != 0)
        return false;
    if ((rule.gate & kGateCounterBelow) != 0 && !(m_moveCounter < rule.gateValue))
        return false;
    // NOT `m_chainContact == true`: the bodies test the sign (`0 < w[0x1b7]`), so a
    // flag that never latched reads as "has not connected" rather than "connected".
    if ((rule.gate & kGateContact) != 0 && !m_chainContact) return false;
    // The rules see the pre-increment elapsed tick (execute_move_program runs before
    // advance_animation_phase), which is exactly the bodies' `n.w[0x2b81]` at entry.
    if ((rule.gate & kGateTickMod) != 0 && rule.gateValue > 0 &&
        (m_moveElapsedTicks % rule.gateValue) != 0)
        return false;
    // The scratch counters are read in the order the bodies read them: the fires gate on
    // the post-increment value, so a Counter rule must precede the rules it enables.
    if ((rule.gate & kGateCounterEquals) != 0 && m_moveCounter != rule.gateValue)
        return false;
    if ((rule.gate & kGateCounterAbove) != 0 && !(m_moveCounter > rule.gateValue2))
        return false;
    return true;
}

void Fighter::launch_bullet(int row, const ShotOriginSpec& origin, const ShotAimSpec& aim,
                            float legacyLateral, float legacyPitchLimit,
                            const ShotSpreadSpec& spread, Fighter* opponent) {
    if (!m_weapon) return;
    PendingShot shot;
    shot.armed = true;
    shot.tier = m_pending.tier;
    shot.bulletRow = row;
    shot.target = opponent;
    shot.origin = origin;
    shot.aim = aim;

    // Compatibility path for the legacy `Launch(row, lateral, pitch)` tables. These
    // constants are Rena 0's MEASURED red-charge shape (FUN_0043ffc0.c:1526-1543:
    // forward 70, lateral 70, height +70, yaw = heading + movement offset +-1.0 deg),
    // not a general world-request model. A body that measures anything else must use
    // typed origin/aim specs — Rika 1's charge (forward 60, no yaw offset) is the
    // example that was mis-routed through here.
    ShotOriginSpec resolvedOrigin = origin;
    ShotAimSpec resolvedAim = aim;
    // The bodies' spread, in the order they draw it: the PITCH jitter first (it is added
    // to the already-clamped scratch), then the yaw offset. Zero moduli consume no draw,
    // so a deterministic rule leaves the shared stream untouched.
    // The sweep first: a body that grows a scratch each tick aims `counter * yawPerTick`
    // off its base, and the jitter below is added on top.
    resolvedAim.yawDegrees += static_cast<float>(m_moveCounter) * spread.yawPerTick;
    // Draw the axes in the order the body states (see spread_axis_order). The lateral one
    // moves the bone origin's own local offset; the other two move the aim.
    for (const SpreadAxis axis : spread_axis_order(spread.order)) {
        switch (axis) {
        case SpreadAxis::Pitch: {
            if (spread.pitchModulus <= 0) break;
            const int draw = static_cast<int>(rng_source().modulo(
                static_cast<std::uint32_t>(spread.pitchModulus)));
            resolvedAim.pitchDegrees += (static_cast<float>(draw) + spread.pitchOffset) *
                                        spread.pitchScale;
            break;
        }
        case SpreadAxis::Yaw: {
            if (spread.yawModulus <= 0) break;
            const int draw = static_cast<int>(rng_source().modulo(
                static_cast<std::uint32_t>(spread.yawModulus)));
            resolvedAim.yawDegrees += (static_cast<float>(draw) + spread.yawOffset) *
                                      spread.yawScale;
            break;
        }
        case SpreadAxis::Lateral: {
            if (spread.lateralModulus <= 0) break;
            const int draw = static_cast<int>(rng_source().modulo(
                static_cast<std::uint32_t>(spread.lateralModulus)));
            resolvedOrigin.localOffset[0] +=
                (static_cast<float>(draw) + spread.lateralOffset) * spread.lateralScale;
            break;
        }
        case SpreadAxis::None: break;
        }
    }
    if (resolvedOrigin.kind == ShotOriginKind::MoveRuleAdapter) {
        if (legacyLateral != 0.f) {
            resolvedOrigin.kind = ShotOriginKind::ActorRelativeOffset;
            resolvedOrigin.actorRightForwardHeight = {legacyLateral, 70.f, 70.f};
        } else {
            const bool bound = weapon_slot_bound(0) && m_weapon->slotCount > 0;
            resolvedOrigin.kind = bound ? ShotOriginKind::WeaponAttachment
                                        : ShotOriginKind::BoundBoneFallback;
            resolvedOrigin.attachmentSlot = 0;
            resolvedOrigin.boneName = "Bip01_Prop1";
        }
    }
    if (resolvedAim.kind == ShotAimKind::MoveRuleAdapter) {
        resolvedAim.kind = ShotAimKind::TargetElevation;
        resolvedAim.yawDegrees = legacyLateral
            ? (legacyLateral > 0.f ? 1.f : -1.f) : 0.f;
        resolvedAim.minimumPitchDegrees = -legacyPitchLimit;
        resolvedAim.maximumPitchDegrees = legacyPitchLimit;
    }
    shot.origin = resolvedOrigin;
    shot.aim = resolvedAim;

    switch (resolvedOrigin.kind) {
    case ShotOriginKind::MoveRuleAdapter:
        throw std::logic_error("unresolved projectile origin");
    case ShotOriginKind::WeaponAttachment: {
        const int slot = resolvedOrigin.attachmentSlot;
        if (slot < 0 || slot >= 2)
            throw std::out_of_range("projectile attachment slot");
        const std::string bone = slot == 0 ? "Bip01_Prop1" : "Bip01_Prop2";
        const bool hasAttachment = weapon_slot_bound(slot) && slot < m_weapon->slotCount;
        const glm::vec3 offset = (hasAttachment
            ? glm::vec3(m_weapon->slots[slot].muzzle[0], m_weapon->slots[slot].muzzle[1],
                        m_weapon->slots[slot].muzzle[2])
            : glm::vec3(0.f)) +
            glm::vec3(resolvedOrigin.localOffset[0], resolvedOrigin.localOffset[1],
                      resolvedOrigin.localOffset[2]);
        if (!hasAttachment) resolvedOrigin.kind = ShotOriginKind::BoundBoneFallback;
        shot.origin = resolvedOrigin;
        shot.pos = bone_point(bone, offset);
        break;
    }
    case ShotOriginKind::BoundBoneFallback:
        shot.pos = bone_point(origin.boneName ? origin.boneName : "Bip01_Prop1",
                              glm::vec3(origin.localOffset[0], origin.localOffset[1],
                                        origin.localOffset[2]));
        break;
    case ShotOriginKind::NamedBone: {
        if (!origin.boneName || !*origin.boneName)
            throw std::invalid_argument("projectile bone origin requires a bone name");
        if (!m_model || !m_anim || m_model->findFrame(origin.boneName) < 0)
            throw std::runtime_error(std::string("projectile origin bone missing: ") +
                                     origin.boneName);
        // The RESOLVED copy, not the spec: the spread adjusts localOffset (a lateral fan
        // moves the hand origin), so reading the spec would silently drop it.
        shot.pos = bone_point(origin.boneName,
                              glm::vec3(resolvedOrigin.localOffset[0],
                                        resolvedOrigin.localOffset[1],
                                        resolvedOrigin.localOffset[2]));
        break;
    }
    case ShotOriginKind::ActorRelativeOffset:
        shot.pos = m_position + facing_relative(origin.actorRightForwardHeight[0],
                                                 origin.actorRightForwardHeight[1]) +
                   glm::vec3(0.f, origin.actorRightForwardHeight[2], 0.f);
        break;
    }

    float pitch = 0.f;
    const auto target_pitch = [&] {
        if (!opponent) return 0.f;
        const glm::vec3 difference = opponent->position() - m_position;
        return std::atan2(difference.y, std::hypot(difference.x, difference.z));
    };
    const auto clamp_aim_pitch = [&](float value) {
        const float minimum = glm::radians(resolvedAim.minimumPitchDegrees);
        const float maximum = glm::radians(resolvedAim.maximumPitchDegrees);
        if (!std::isfinite(minimum) || !std::isfinite(maximum) || minimum > maximum)
            throw std::invalid_argument("invalid projectile pitch bounds");
        return std::clamp(value, minimum, maximum);
    };
    switch (resolvedAim.kind) {
    case ShotAimKind::MoveRuleAdapter:
        throw std::logic_error("unresolved projectile aim");
    case ShotAimKind::TargetElevation: {
        // The remake's own basis: forward = (sin yaw, cos yaw), no legacy conversion.
        const float yaw = m_facing + glm::radians(resolvedAim.yawDegrees);
        pitch = clamp_aim_pitch(target_pitch());
        shot.dir = glm::vec3(std::sin(yaw) * std::cos(pitch), std::sin(pitch),
                             std::cos(yaw) * std::cos(pitch));
        break;
    }
    case ShotAimKind::ActorHeadingTargetElevation: {
        const float legacyYawDegrees = 90.f - glm::degrees(m_facing) +
                                       resolvedAim.yawDegrees;
        pitch = clamp_aim_pitch(target_pitch() + glm::radians(resolvedAim.pitchDegrees));
        const float legacyYaw = glm::radians(legacyYawDegrees);
        shot.dir = glm::vec3(std::cos(legacyYaw) * std::cos(pitch), std::sin(pitch),
                             std::sin(legacyYaw) * std::cos(pitch));
        break;
    }
    // The pitch a CapturePitch rule latched earlier in this move: the body reads
    // source_float(0x3c) back instead of re-deriving the elevation, so a target that
    // moved vertically mid-attack does not re-aim salvos that already have their pitch.
    case ShotAimKind::StoredPitch: {
        const float legacyYawDegrees = 90.f - glm::degrees(m_facing) +
                                       resolvedAim.yawDegrees;
        pitch = glm::radians(m_movePitch + resolvedAim.pitchDegrees);
        const float legacyYaw = glm::radians(legacyYawDegrees);
        shot.dir = glm::vec3(std::cos(legacyYaw) * std::cos(pitch), std::sin(pitch),
                             std::sin(legacyYaw) * std::cos(pitch));
        break;
    }
    case ShotAimKind::FixedAngles: {
        const float yaw = m_facing + glm::radians(resolvedAim.yawDegrees);
        pitch = glm::radians(resolvedAim.pitchDegrees);
        shot.dir = glm::vec3(std::sin(yaw) * std::cos(pitch), std::sin(pitch),
                             std::cos(yaw) * std::cos(pitch));
        break;
    }
    case ShotAimKind::ElevationPlusRange: {
        // shoot_body_2_1_450/460, same tick throughout: base pitch plus a live term
        // from the current target distance. Constants are the body's own (40/5000,
        // clamp 0-40, x0.95 when the base is negative), not tuning. The distance is
        // horizontal (FUN_0042d980 feeds both this term and the elevation's
        // atan2(height, sqrt(dist))), never 3D.
        float base = 0.f;
        float rangeTerm = 0.f;
        if (opponent) {
            const glm::vec3 difference = opponent->position() - m_position;
            const float horizontal = std::hypot(difference.x, difference.z);
            base = static_cast<float>(static_cast<int>(
                glm::degrees(std::atan2(difference.y, horizontal))));
            base = std::clamp(base, -40.f, 40.f);
            rangeTerm = std::clamp(horizontal * 40.f / 5000.f, 0.f, 40.f);
            if (base < 0.f) rangeTerm *= 0.95f;
        }
        const float legacyYawDegrees = 90.f - glm::degrees(m_facing) +
                                       resolvedAim.yawDegrees;
        pitch = glm::radians(base + rangeTerm + resolvedAim.pitchDegrees);
        const float legacyYaw = glm::radians(legacyYawDegrees);
        shot.dir = glm::vec3(std::cos(legacyYaw) * std::cos(pitch), std::sin(pitch),
                             std::sin(legacyYaw) * std::cos(pitch));
        break;
    }
    }
    const float directionLengthSquared = glm::dot(shot.dir, shot.dir);
    if (!(directionLengthSquared > 0.f) || !std::isfinite(directionLengthSquared))
        throw std::invalid_argument("invalid projectile direction");
    shot.dir *= 1.f / std::sqrt(directionLengthSquared);

    // Resolve transforms before admission, as FUN_00435000/00435220 do before
    // FUN_00435920. If the later pool rejects the request, consumption remains spent.
    if (!std::isfinite(shot.pos.x) || !std::isfinite(shot.pos.y) ||
        !std::isfinite(shot.pos.z))
        throw std::invalid_argument("invalid projectile origin");
    if (!admit_shooting_row(*m_weapon, row, m_shootingMagazines)) return;
    m_pendingShots.push_back(std::move(shot));
}

bool Fighter::weapon_slot_bound(int slot) const {
    return slot >= 0 && slot < 2 && m_propBound[static_cast<size_t>(slot)];
}

const MoveEntry* Fighter::current_move_record() const {
    if (!m_moves) return nullptr;
    const CharacterMove* move = m_moves->find(state_move_id());
    if (!move || m_phaseIndex < 0 || m_phaseIndex >= move->sectionCount) return nullptr;
    return move->phases[m_phaseIndex].record_at(m_moveElapsedTicks);
}

bool Fighter::melee_in_recovery() const {
    if (m_state != FighterState::AttackA) return false;
    if (!m_moves) return m_swing.is_recovery(m_meleeElapsed);
    const auto* move = m_moves->find(m_attackMoveId);
    if (!move) return false;
    bool pastCombat = false;
    const auto* current = current_move_record();
    for (int phase = 0; phase < move->sectionCount; ++phase) {
        const auto& records = move->phases[phase];
        for (int entry = 0; entry < records.entryCount; ++entry) {
            const auto* record = &records.entries[entry];
            if (!record->has_combat()) continue;
            if (phase > m_phaseIndex ||
                (phase == m_phaseIndex && current && record >= current)) return false;
            pastCombat = true;
        }
    }
    return pastCombat;
}

glm::vec3 Fighter::bone_point(const std::string& name, const glm::vec3& local) const {
    if (m_model && m_anim) {
        const int frame = m_model->findFrame(name);
        if (frame >= 0) {
            std::vector<glm::mat4> posed;
            m_anim->evalWorld(posed);
            return glm::vec3(modelMatrix() * posed[static_cast<size_t>(frame)] * glm::vec4(local, 1.f));
        }
    }
    return m_position + local;
}

void Fighter::build_melee_swing(int moveId) {
    m_swing = resolve_swing(moveId);
    // The swing is armed here and nowhere else, so this is the attack event's own edge
    // (FUN_0043ffc0's swing entry); the frame report drains it (issue #16).
    m_swingStartedPending = true;
}

MeleeSwing Fighter::resolve_swing(int moveId) const {
    MeleeSwing swing;  // legacy shared swing; data overwrites below
    if (!m_moves || moveId < 0) return swing;
    const CharacterMove* move = m_moves->find(moveId);
    if (!move) return swing;
    // The hit is the first combat entry across the phases in order (e.g. rena 300
    // phase 74 entry 1: Prop1, frame 4, hr 20). Whiff/trail phases carry no combat.
    const MoveEntry* hit = nullptr;
    int nextFrame = -1;
    for (int p = 0; p < move->sectionCount && !hit; ++p) {
        const MovePhase& ph = move->phases[p];
        for (int e = 0; e < ph.entryCount; ++e) {
            if (ph.entries[e].has_combat()) {
                hit = &ph.entries[e];
                if (e + 1 < ph.entryCount) nextFrame = ph.entries[e + 1].activeFrame;
                break;
            }
        }
    }
    if (!hit) return swing;
    swing.dataDriven = true;
    swing.moveId = moveId;
    // The hit goes live on its own in-phase frame (rena 300 → 4, 301 → 7).
    swing.window.startupTicks = hit->activeFrame;
    // ... and lives until the phase's next effect fires (300 → 6, 301 → 9,
    // 311 → 11, 330 → 5). A last-entry hit keeps the legacy 8-tick window.
    if (nextFrame > hit->activeFrame) swing.window.activeTicks = nextFrame - hit->activeFrame;
    if (hit->hitRadius > 0) swing.radius = static_cast<float>(hit->hitRadius);
    // The melee HP damage is the move's combat[0x00] power through FUN_00639160's chain
    // (see the top of this file). A hit with no power at all keeps the legacy value, which
    // is also what a move table with no combat entry falls back to.
    if (hit->baseDamage > 0 && m_maxHP > 0)
        swing.damage = std::max(1, portDamage(meleePoolDamage(hit->baseDamage), m_maxHP));
    if (hit->defenderHitstun > 0) swing.hitstun = hit->defenderHitstun;
    return swing;
}

ShotParams Fighter::shot_params_for_row(ShotTier tier, int row) const {
    if (row < 0) return shot_params_for(tier);
    ShotParams params = shot_params(tier);
    const BulletParameter* b = bullet_row(row);
    if (!b) return params;
    params.damage = portDamage(shotPoolDamage(b->baseDamage), m_maxHP);
    params.hitRadius = static_cast<float>(b->hitRadius);
    return params;
}

float Fighter::yellow_hold_sec() const {
    // FUN_0043f3e0: secondary magazine reaches first stage after initial 30 updates.
    return m_weapon ? 30.f / FixedStep::tickRate : FighterConstants::kYellowHoldSec;
}

float Fighter::red_hold_sec() const {
    return m_weapon ? (30.f + m_shootingMagazines[1].chargeThreshold) / FixedStep::tickRate
                    : FighterConstants::kRedHoldSec;
}

void Fighter::set_weapon(const WeaponDefinition* weapon) {
    if (m_weapon == weapon) return;
    const float mainFrac = main_frac();
    const float chgFrac = charge_frac();
    m_weapon = weapon;
    apply_weapon_ammo();
    if (m_weapon) {
        m_shootingMagazines[0].preserve_fraction(mainFrac);
        m_shootingMagazines[1].preserve_fraction(chgFrac);
    }
}

// Composes a frame's bind-pose world matrix by walking parent links. The rig stores each
// frame's transform relative to its parent, so a bone's model-space position is the
// product along that chain. Depth is bounded by the rig's own parent graph.
static constexpr int kMaxBoneChain = 256;

static glm::mat4 bindWorld(const xm::Model* model, int frame) {
    glm::mat4 m{1.f};
    // Follow parent links, not indices: each frame stores its transform relative to its
    // parent, so the world matrix is their product along the chain. The guard is the
    // rig's own parent graph rather than a trust assumption — a malformed parent cycle
    // would otherwise spin here forever.
    for (int steps = 0; frame >= 0 && frame < static_cast<int>(model->frames.size()) &&
                       steps < kMaxBoneChain;
         ++steps) {
        m = model->frames[static_cast<size_t>(frame)].bindLocal * m;
        frame = model->frames[static_cast<size_t>(frame)].parent;
    }
    return m;
}

glm::vec3 Fighter::hurtbox_anchor_offset(int index) const {
    const float bodyHeight = game::physics::MovementCollision::kFighterHeight;
    if (m_model) {
        if (index == 0) {
            // FUN_0063dad0:241 transforms (0,0,0) by the Head frame.
            const int f = m_model->findFrame("Bip01_Head");
            if (f >= 0 && m_anim) return bone_point("Bip01_Head", glm::vec3(0.f)) - m_position;
            if (f >= 0) return glm::vec3(bindWorld(m_model, f)[3]);
        } else {
            // FUN_0063dad0:244 transforms (-50.0,0,0) by the Spine frame.
            const int f = m_model->findFrame("Bip01_Spine");
            if (f >= 0 && m_anim) return bone_point("Bip01_Spine", glm::vec3(-50.f,0.f,0.f)) - m_position;
            if (f >= 0) return glm::vec3(bindWorld(m_model, f) * glm::vec4(-50.f, 0.f, 0.f, 1.f));
        }
    }
    // No rig, or a rig without these bones: fractions of the collision body height. Only
    // the body's SIZE is measured (#7); where the head sits on it is not.
    const float frac = index == 0 ? m_meleeRules.headHeightFrac : m_meleeRules.chestHeightFrac;
    return glm::vec3(0.f, bodyHeight * frac, 0.f);
}

Fighter::HitboxDebug Fighter::hitbox_debug() const {
    const float bodyHeight = game::physics::MovementCollision::kFighterHeight;
    HitboxDebug d;
    d.anchors[0] = m_position + hurtbox_anchor_offset(0);
    d.anchors[1] = m_position + hurtbox_anchor_offset(1);
    d.anchorRadius = m_meleeRules.bodyRadius;
    d.attacking = m_state == FighterState::AttackA &&
                  melee_in_active();
    if (d.attacking) {
        if (const MoveEntry* record = current_move_record()) {
            d.attackCenter = bone_point(record->boneName, glm::vec3(record->anchor[0], record->anchor[1], record->anchor[2]));
            d.attackEnd = bone_point(record->boneName, glm::vec3(record->endAnchor[0], record->endAnchor[1], record->endAnchor[2]));
            d.capsule = record->collisionShape != 0;
            d.attackRadius = static_cast<float>(record->hitRadius);
            return d;
        }
        // The attack sphere is centred where try_melee_hit() measures from, so the two
        // can never disagree.
        d.attackCenter = m_position +
                         glm::vec3(0.0f, bodyHeight * m_meleeRules.chestHeightFrac, 0.0f);
        // The ATTACKER's own volume, which is the swing's radius — the weapon's own
        // hitRadius when moves are bound, melee_rules.h's legacy stand-in for weapon+0x24
        // otherwise. It is deliberately NOT bodyRadius + radius: in
        // FUN_0063b470 that sum is the combined test distance (the VICTIM's 30-unit body
        // radius plus this), so drawing it would show the reach, not the attack volume.
        d.attackRadius = m_swing.radius;
    }
    return d;
}

void Fighter::set_bullet_parameter(int level, const BulletParameter* parameter) {
    const int i = (level == 2) ? 1 : 0;
    if (m_bulletParams[i] == parameter) return;
    m_bulletParams[i] = parameter;
}

ShotParams Fighter::shot_params_for(ShotTier tier) const {
    ShotParams params = shot_params(tier);
    const BulletParameter* b = bullet_parameter((tier == ShotTier::Tap) ? 1 : 2);
    if (!b) return params;
    // FUN_00637950 @0x637950's chain removes blob[0] (baseDamage) from the victim's
    // 10000-based pool; see the top of this file for the field mapping and the neutral
    // factors. The radius is already a world-space length.
    if (b->baseDamage > 0 && m_maxHP > 0)
        params.damage = portDamage(shotPoolDamage(b->baseDamage), m_maxHP);
    if (b->hitRadius > 0) params.hitRadius = static_cast<float>(b->hitRadius);
    return params;
}

void Fighter::restore_ammo() {
    if (m_weapon) {
        for (auto& magazine : m_shootingMagazines) magazine.reset();
    } else {
        m_main.value = m_main.max;
        m_charge.value = m_charge.max;
    }
}

void Fighter::apply_weapon_ammo() {
    if (!m_weapon) {
        // No weapon bound: the historical shared tuning, unchanged, so the banked 1v1
        // capture and its trace keep the numbers they were banked with.
        m_main   = AmmoStock{FighterConstants::kMainMax, FighterConstants::kMainMax,
                             FighterConstants::kMainPerSec};
        m_charge = AmmoStock{FighterConstants::kChargeMax, FighterConstants::kChargeMax,
                             FighterConstants::kChargePerSec};
        return;
    }
    for (size_t i = 0; i < m_shootingMagazines.size(); ++i)
        m_shootingMagazines[i] = ShootingMagazine::from_definition(m_weapon->magazines[i]);
}

float Fighter::charge_hold_frac() const {
    const float limit = red_hold_sec();
    const float held = m_weapon ? static_cast<float>(m_shootingMagazines[1].initialHold +
                                                    m_shootingMagazines[1].laterHold) / FixedStep::tickRate
                                : m_chargeHeld;
    const float f = (limit > 0.0f) ? held / limit : 0.0f;
    return std::clamp(f, 0.0f, 1.0f);
}

ShotTier Fighter::charge_tier() const {
    if (m_weapon) return m_shootingMagazines[1].chargeStage >= 2 ? ShotTier::Red
                         : m_shootingMagazines[1].chargeStage == 1 ? ShotTier::Yellow : ShotTier::Tap;
    if (m_chargeHeld >= red_hold_sec())    return ShotTier::Red;
    if (m_chargeHeld >= yellow_hold_sec()) return ShotTier::Yellow;
    return ShotTier::Tap;
}

bool Fighter::shot_jump_cancel_pressed(const input::PlayerState* input) const {
    if (!input || !input->just_pressed[input::Action::Jump] || !m_grounded) return false;
    if (m_state != FighterState::ShootA && m_state != FighterState::ShootB &&
        m_state != FighterState::ShootC)
        return false;
    const auto* binding = locomotion(m_moves);
    if (!binding) return false;
    for (const auto& row : kShotJumpCancel)
        if (row.handler == binding->handler && row.move == state_move_id())
            return m_moveElapsedTicks >= row.frame;
    return false;
}

void Fighter::try_jump() {
    m_stamina = std::max(0.0f, m_stamina - FighterConstants::kJumpStamina);
    m_grounded = false;
    m_vy = FighterConstants::kJumpSpeed;
    // The launch tick still plays the air chain's startup row (move 40 / set 2);
    // refresh_state_move() consumes this once the rise has its own row.
    m_jumpStartup = true;
    set_state(FighterState::Jump);
    m_stateTimer = 0;  // physics-driven: gravity/landing own this state
}

bool Fighter::try_dash(input::Action dir) {
    const int dashMove = dash_move_for(dir);
    const bool programmed = m_grounded && m_model && dashMove == 20 && locomotion(m_moves);
    // FUN_0043ffc0 drains twelve pool units per update, not a twenty-percent
    // trigger cost. Unsupported handlers still use the explicitly legacy path.
    if (programmed ? m_stamina <= 0.f : m_stamina < FighterConstants::kDashStamina) return false;
    if (!m_grounded && m_airDashed) return false;

    // Facing-relative dash (see facing_relative): the tapped key is a screen
    // direction — Up toward the opponent, Down away, Left/Right sidesteps —
    // committed for the dash window.
    glm::vec3 d(0, 0, 0);
    if (dir == input::Action::Up)         d = facing_relative(0.0f, 1.0f);
    else if (dir == input::Action::Down)  d = facing_relative(0.0f, -1.0f);
    else if (dir == input::Action::Right)  d = facing_relative(1.0f, 0.0f);
    else                                  d = facing_relative(-1.0f, 0.0f);

    if (!programmed) m_stamina -= FighterConstants::kDashStamina;
    m_dashDir = d;
    if (m_state == FighterState::Run && m_dashMoveId != dashMove) {
        m_phaseIndex = 0;
        m_moveElapsedTicks = 0;
        m_animSetIdx = -1;
    }
    m_dashMoveId = dashMove;
    m_dashAir = !m_grounded;
    if (m_dashAir) {
        m_airDashed = true;
        m_vy = 0.0f;  // air dash hangs: no fall during the window
        m_dashSpeed = FighterConstants::kAirDashSpeed;
    } else {
        m_dashSpeed = FighterConstants::kRunSpeed;
    }
    const bool wasRunning = m_state == FighterState::Run;
    set_state(FighterState::Run);
    // A second dash can replace its candidate without changing the port state.
    // set_state() intentionally early-outs for identical labels, so rebind after
    // the candidate reset above instead of leaving the previous clip active.
    if (wasRunning && m_animSetIdx < 0) try_switch_animation();
    m_stateTimer = programmed
                        ? 0 : FighterConstants::kDashFrames;
    return true;
}

void Fighter::try_fire() { fire_shot(charge_tier()); }

float Fighter::shot_cost(ShotTier tier) const {
    const ShotParams p = shot_params_for(tier);
    const float cost = (tier == ShotTier::Tap) ? p.mainCost : p.chargeCost;
    return cost;
}

bool Fighter::can_fire(ShotTier tier) const {
    if (m_weapon) return m_shootingMagazines[tier == ShotTier::Tap ? 0 : 1].rounds != 0;
    const AmmoStock& stock = (tier == ShotTier::Tap) ? m_main : m_charge;
    return m_reloadTimer <= 0 && stock.can_spend(shot_cost(tier));
}

void Fighter::fire_shot(ShotTier tier) {
    if (!can_fire(tier)) return;
    if (!m_weapon) {
        const ShotParams p = shot_params_for(tier);
        AmmoStock& stock = (tier == ShotTier::Tap) ? m_main : m_charge;
        stock.spend(shot_cost(tier));
        m_reloadTimer = p.reloadFrames;
    }

    // Muzzle ahead of the fighter at chest height, aimed along facing
    // (yaw=0 faces +Z — same convention as update_facing).
    const glm::vec3 dir(std::sin(m_facing), 0.0f, std::cos(m_facing));
    m_pending = PendingShot{};
    m_pending.armed = true;
    m_pending.tier  = tier;
    m_pending.dir   = dir;
    m_pending.pos   = m_position + dir * FighterConstants::kMuzzleForward;
    m_pending.pos.y += FighterConstants::kMuzzleHeight;

    const MoveProgram* program = move_program(m_moves);
    // A -1 row means that tier has no recovered program (Mion 0's second charge:
    // no 360/370 body exists for her) — it keeps the provisional path below, which is
    // today's behavior for every combo without an exact program.
    const int programmed =
        (program && tier != ShotTier::Ex)
            ? program->shot[static_cast<size_t>(tier)][m_grounded ? 0 : 1]
            : -1;
    if (programmed >= 0) {
        m_shotMoveId = programmed;
        m_pending.armed = false;
    } else if (m_weapon) {
        // Preserve the old provisional selector only for unrecovered handlers.
        // It is not format evidence: exact-row programs bypass this branch.
        const int magazine = tier == ShotTier::Tap ? 0 : 1;
        for (int row = 0; row < m_weapon->bulletCount; ++row)
            if (m_weapon->bullets[row].magazine == magazine &&
                (m_pending.bulletRow < 0 || m_weapon->bullets[row].type <
                                           m_weapon->bullets[m_pending.bulletRow].type))
                m_pending.bulletRow = row;
    }

    if (m_weapon && programmed < 0) {
        // Unbound move selection remains provisional; known rows still use their own
        // admission. A row-less custom request retains the tier's magazine choice.
        m_pending.armed = m_pending.bulletRow >= 0
            ? admit_shooting_row(*m_weapon, m_pending.bulletRow, m_shootingMagazines)
            : m_shootingMagazines[tier == ShotTier::Tap ? 0 : 1].consume();
    }

    switch (tier) {
        case ShotTier::Tap:    set_state(FighterState::ShootA);    break;
        case ShotTier::Yellow: set_state(FighterState::ShootB);    break;
        case ShotTier::Red:    set_state(FighterState::ShootC);    break;
        case ShotTier::Ex:     set_state(FighterState::ShotFinal); break;
    }
    m_stateTimer = programmed >= 0 ? 0 : FighterConstants::kShotStateFrames;
}

PendingShot Fighter::take_pending_shot() {
    if (!m_pendingShots.empty()) {
        PendingShot out = m_pendingShots.front();
        m_pendingShots.erase(m_pendingShots.begin());
        return out;
    }
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
