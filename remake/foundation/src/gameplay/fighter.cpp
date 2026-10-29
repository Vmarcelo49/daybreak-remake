// FUN_0041f580 / FUN_00420b30: fighter update, move records and world pose.
// Recovered executable rules live separately in move_behavior.h; NN.dat owns
// phase/set selection, record geometry and material intervals.
#include "gameplay/reaction_motion.h"
#include "gameplay/fighter.h"
#include "gameplay/animation_period.h"
#include "gameplay/held_axis.h"
#include "gameplay/fixed_step.h"
#include "gameplay/move_behavior.h"
#include "gameplay/melee_admission.h"
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

// A parsed NN row plus the matching equipped item and rig is enough to time a
// move only when every phase has a valid .X period and the source's +0x20 gate
// allows generic phase completion. Nonzero gates require handler callbacks; keep
// the contact-derived fallback timer until those callbacks are represented.
bool hasAutomaticMeleeTimeline(const CharacterMoves* moves,
                               const WeaponDefinition* weapon,
                               const xm::Model* model, int moveId) {
    if (!moves || !weapon || !model || !moves->valid() || !model->ticksPerSecond ||
        weapon->id != moves->weapon_id() ||
        weaponSlotForItem(moves->character_index(), weapon->id) < 0)
        return false;
    const CharacterMove* move = moves->find(moveId);
    if (!move || move->sectionCount <= 0) return false;
    for (int phase = 0; phase < move->sectionCount; ++phase) {
        const int set = move->phase_set_index(phase);
        if (set < 0 || static_cast<size_t>(set) >= model->anims.size() ||
            moves->animation_set_phase_gate(set) != 0)
            return false;
        const float duration = model->anims[static_cast<size_t>(set)].duration;
        if (!std::isfinite(duration) || duration < 0.f) return false;
        const float ticks = duration / model->ticksPerSecond / kOriginalAnimationTick;
        if (!std::isfinite(ticks) || ticks < 0.f) return false;
    }
    return true;
}

// Activation-clip window from the engine's own period rule (issue #71), not a
// shared provisional constant: animation_period_frames() is the original's truncating
// conversion, and FUN_0041f580/FUN_00421410 complete a phase on strict `period <
// elapsed` unless the set's +0x20 gate is nonzero (which holds the phase past expiry —
// cf. the set-14 precedent in docs/ANIMATION-SETS.md). Returns the updates the clip
// occupies, -1 when a gated phase holds it until the fighter's next clip-binding action,
// or 0 when the window cannot be derived from the parsed data.
int hyper_activation_window_frames(const CharacterMoves* moves,
                                   const xm::Model* model, int moveId) {
    if (!moves || !model || !moves->valid() || model->anims.empty()) return 0;
    const CharacterMove* move = moves->find(moveId);
    if (!move || move->sectionCount <= 0) return 0;
    int total = 0;
    for (int phase = 0; phase < move->sectionCount; ++phase) {
        const int set = move->phase_set_index(phase);
        if (set < 0 || static_cast<std::size_t>(set) >= model->anims.size()) return 0;
        if (moves->animation_set_phase_gate(set) != 0) return -1;
        const int window = animation_period_frames(*model, set);
        if (window < 0) return 0;
        total += window;
    }
    return total + 1;
}

bool backInputHeld(const input::PlayerState* input) {
    // The SDL stick uses positive Y for Down; analog Back must match the D-pad.
    return input && (input->down[input::Action::Down] ||
                     input->stick_y > input::kStickDeadzone);
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
    m_actionMeter = 1000;
    m_state = FighterState::BattleStart;
    m_stateTimer = FighterConstants::kBattleStartFrames;
    m_attackMoveId = -1;   // no swing in flight across a round reset
    m_aerialAttack = false;
    m_attackUsesActorFacing = false;
    m_dashMoveId = -1;
    m_dashInputDirection = input::Action::Up;
    m_phaseIndex = 0;
    m_moveElapsedTicks = 0;
    m_swing = MeleeSwing{};
    m_animSetIdx = -1;   // bind() looked the previous state up; BattleStart wins
    clear_tracks();      // a round reset is a fresh bind, never a blend
    apply_weapon_ammo();
    clear_charge_hold();
    m_reloadTimer = 0;
    m_pending = PendingShot{};
    m_pendingShots.clear();
    m_shootingVoice = {};
    m_meleeVoice = {};
    m_pendingSoundEffect = {};
    m_pendingEffect = {};
    m_hitStatusDuration.fill(0);
    m_hitStatusPower.fill(0);
    m_shotMoveId = -1;
    m_moveSpeed = 0.f;
    m_moveCounter = 0;
    m_movePitch = 0.f;
    m_holdTicks = 0;
    m_actionCamera = -1;
    m_chainContact = false;
    m_chainGuarded = false;
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
    m_airDashCarry = false;
    m_dashFall = false;
    m_landingTicks = 0;
    m_reactionMove = 103;
    m_hoverSpent = false;   // a new airtime re-arms the one hover
    try_switch_animation();
}

void Fighter::reset(const glm::vec3& pos, float facing) {
    m_position = pos;
    m_safePosition = pos;
    m_facing = facing;
    m_velocity = glm::vec3(0, 0, 0);
    m_hp = m_maxHP;
    m_stamina = static_cast<float>(FighterConstants::kMaxStamina);
    m_actionMeter = 1000;
    m_state = FighterState::BattleStart;
    m_stateTimer = FighterConstants::kBattleStartFrames;
    m_attackMoveId = -1;
    m_aerialAttack = false;
    m_attackUsesActorFacing = false;
    m_dashMoveId = -1;
    m_dashInputDirection = input::Action::Up;
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
    m_airDashCarry = false;
    m_dashFall = false;
    m_landingTicks = 0;
    m_reactionMove = 103;
    m_hoverSpent = false;   // a new airtime re-arms the one hover
    // FUN_00435660 restores round capacity while retaining refill/interval progress.
    restore_ammo();
    clear_charge_hold();
    m_reloadTimer = 0;
    m_pending = PendingShot{};
    m_pendingShots.clear();
    m_shootingVoice = {};
    m_meleeVoice = {};
    m_pendingSoundEffect = {};
    m_pendingEffect = {};
    m_hitStatusDuration.fill(0);
    m_hitStatusPower.fill(0);
    m_shotMoveId = -1;
    m_moveSpeed = 0.f;
    m_moveCounter = 0;
    m_movePitch = 0.f;
    m_holdTicks = 0;
    m_actionCamera = -1;
    m_chainContact = false;
    m_chainGuarded = false;
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
    m_airDashCarry = false;
    m_dashFall = false;
    m_landingTicks = 0;
    m_reactionMove = 103;
    m_hoverSpent = false;   // a new airtime re-arms the one hover
    m_hp = m_maxHP;
    m_stamina = static_cast<float>(FighterConstants::kMaxStamina);
    m_actionMeter = 1000;
    m_guardExhausted = false;
    // Move 0xc2 (194) plays on re-entry; its set is 43, which is exactly the set
    // state_to_anim_set(BattleStart) binds. The timer is held at 0 so the landing —
    // not a frame count — ends the pose.
    m_state = FighterState::BattleStart;
    m_stateTimer = 0;
    m_animSetIdx = -1;
    clear_tracks();
    m_attackMoveId = -1;
    m_aerialAttack = false;
    m_attackUsesActorFacing = false;
    m_dashMoveId = -1;
    m_dashInputDirection = input::Action::Up;
    m_phaseIndex = 0;
    m_swing = MeleeSwing{};
    clear_charge_hold();
    m_reloadTimer = 0;
    m_pending = PendingShot{};
    m_pendingShots.clear();
    m_shootingVoice = {};
    m_meleeVoice = {};
    m_pendingSoundEffect = {};
    m_pendingEffect = {};
    m_hitStatusDuration.fill(0);
    m_hitStatusPower.fill(0);
    m_shotMoveId = -1;
    m_moveSpeed = 0.f;
    m_moveElapsedTicks = 0;
    m_moveCounter = 0;
    m_movePitch = 0.f;
    m_holdTicks = 0;
    m_actionCamera = -1;
    m_chainContact = false;
    m_chainGuarded = false;
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
    m_shootingVoice = {};
    m_sourceShotVoiceAudited = false;
    m_sourceMeleeVoiceAudited = false;
    m_time += dt;
    m_animationBoundThisUpdate = false;

    // Hypermode first: it can activate this frame (S), expire, or drain
    // Kakera HP, all before the state machine reads the mode's modifiers.
    update_hypermode(dt);

    // Expiry of a timed activation overlay re-binds the state's own clip, but
    // only when the overlay is still what's playing: a superseding action has
    // already rebound (set_state clears the overlay's set), and rebinding here
    // would restart that action's clip mid-play (issue #71).
    if (m_hyperActivationFrames > 0) {
        --m_hyperActivationFrames;
        if (m_hyperActivationFrames == 0) {
            if (m_hyperActivationSet >= 0 && m_animSetIdx == m_hyperActivationSet) {
                m_animSetIdx = -1;
                try_switch_animation();
            }
            m_hyperActivationSet = -1;
        }
    }
    // The overlay's own event clock runs while it is armed — including a gated
    // hold, whose elapsed keeps counting past the period in the source (the
    // +0x20 gate holds the phase, not the clock). Superseding actions leave the
    // set cleared, which freezes this clock via hyper_activation_elapsed().
    if (m_hyperActivationSet >= 0) ++m_hyperActivationElapsed;
    // The activation flash decays 4 a tick from 0xFC (FUN_0041f580's +0x334
    // maintenance), independent of states and overlays.
    if (m_hyperFlash > 0) m_hyperFlash = std::max(0, m_hyperFlash - 4);
    // The stagger meter's window (+0x7bc) and the combo window (+0x7c4): both expire together
    // with their counters (FUN_0041f580 0x41f673-0x41f732).
    if (m_staggerDecay > 0 && --m_staggerDecay == 0) m_hitMeterA = 0;
    if (m_comboDecay > 0 && --m_comboDecay == 0) { m_hitMeterB = 0; m_comboHits = 0; }
    // The hit's reaction clock (+0x40): -0x3e99999a = 0.3 per tick, and reaching zero switches
    // the victim to move 0x76 (118) — the recovered consumer at 0x428943/0x428946/0x42897a.
    if (m_reactionCounter > 0.f) {
        m_reactionCounter = std::max(0.f, m_reactionCounter - 0.3f);
        if (m_reactionCounter == 0.f && m_state == FighterState::Hit) {
            m_swing = resolve_swing(0x76);
            switch_attack_row(0x76);
        }
    }

    // 1. Decrement state timer (mirrors +0xa0 in fcn.0041f580).
    if (m_stateTimer > 0) {
        --m_stateTimer;
        if (m_stateTimer == 0) {
            // The knockdown chain: lying (118/119) plays out, then the get-up row 120, and only
            // then does the victim stand. Everything is animation-length driven — the original
            // advances on move completion, never on a stun counter.
            if (m_state == FighterState::Knockdown) {
                if (m_downPhase == 1) {
                    m_downPhase = 2;
                    m_reactionMove = 120;
                    m_stateTimer = std::max(1, move_row_frames(120));
                } else {
                    m_downPhase = 0;
                    set_state(FighterState::Idle);
                }
            } else if (m_state != FighterState::KO && m_state != FighterState::TagOut) {
                // Timed states expire back into the fall when airborne
                // (a dash/attack/volley started mid-air lands as Jump). This is the DEFAULT
                // path's approximation, not the recovered completion: the original advances
                // row 30 through its own sections and enters state 43 from that exit, which
                // this timer stands in for. So the fall here stays on the jump chain and does
                // not claim row 43 (V3-42).
                set_state(m_grounded ? FighterState::Idle : FighterState::Jump);
            }
        }
    }

    // Guard is not actionable: release must bypass can_act(). Port rule until
    // the incoming-damage block flag is recovered (FUN_00431e70's voice keys
    // do not establish it). Exhaustion requires a release before another hold.
    const bool guardHeld = input && input->down[input::Action::Guard];
    if (!guardHeld) m_guardExhausted = false;
    // Guard is a grounded stance only (owner: the original does not allow blocking in the
    // air). Leaving the ground therefore ends it as well as releasing the button or
    // draining the meter — the same three exits, one of them now positional.
    if (m_state == FighterState::Guard &&
        (!guardHeld || !m_grounded || m_stamina <= 0.0f)) {
        if (guardHeld) m_guardExhausted = true;
        m_guardClip = -1;
        m_guardPhase = 0;
        m_guardTicks = 0;
        set_state(m_grounded ? FighterState::Idle : FighterState::Jump);
    }

    // FUN_004202b0 forms movement from the target-facing basis plus the input
    // offset, then FUN_0042dd90 refreshes that basis from the selected fighter
    // while preserving the body's relative heading. Sample it before input
    // dispatch so a dash edge cannot use the previous walk heading or old tick.
    m_inputFacing = opponent ? std::atan2(opponent->position().x - m_position.x,
                                         opponent->position().z - m_position.z) : m_facing;
    const FighterState stateBeforeInput = m_state;

    // 2. Update state machine (check input, transition states).
    // A lost action window (hit, KO) breaks any charge hold in progress.
    if (!can_act()) clear_charge_hold();
    if (m_state == FighterState::AttackA && input &&
        input->just_pressed[input::Action::AttackA] &&
        (attack_admission_recovered(m_moves ? m_moves->character_index() : -1) ||
         move_program(m_moves))) {
        // Chains admit through the same dispatcher as the first press: the
        // original reads the CURRENT attack row, its phase and its 0x100 window
        // (FUN_00445ee0), so every family in melee_admission.h — not just the
        // 300->301->302 pair — can follow a contact-window press. Unrecovered
        // combos keep the bounded pair below.
        int next = -1;
        if (m_moves && attack_admission_recovered(m_moves->character_index())) {
            next = melee_admission_for(m_moves->character_index(),
                                       attack_input(!m_grounded, input),
                                       AttackAdmissionTable{m_moves});
        } else {
            const CharacterMove* from = m_moves->find(m_attackMoveId);
            const CharacterMove* to = m_moves->find(m_attackMoveId + 1);
            const MoveEntry* record = current_move_record();
            // FUN_00445ee0: row 300->301->302 compares row priority and state bit 0x100.
            if (from && to && m_attackMoveId >= 300 && m_attackMoveId < 302 && record &&
                (record->stateFlags & 0x100) && from->cancelThreshold <= to->priority)
                next = m_attackMoveId + 1;
        }
        if (next >= 0) {
            if (m_aerialAttack && m_moves->character_index() == 0 && m_moves->weapon_id() == 1) {
                m_attackUsesActorFacing = backInputHeld(input);
                if (!m_attackUsesActorFacing) m_facing = m_inputFacing;
            }
            switch_attack_row(next);
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
    const bool enteringActionPose =
        m_state == FighterState::Guard || m_state == FighterState::ShootA ||
        m_state == FighterState::ShootB || m_state == FighterState::ShootC ||
        m_state == FighterState::Jump;
    if (input && opponent && opponent->is_alive() && stateBeforeInput != m_state &&
        (stateBeforeInput == FighterState::Idle || stateBeforeInput == FighterState::Walk ||
         stateBeforeInput == FighterState::Run) && enteringActionPose) {
        const bool backJump = m_state == FighterState::Jump && backInputHeld(input);
        const int moveId = state_move_id();
        const MoveProgram* program = move_program(m_moves);
        bool hasTurnRuleAtEntry = false;
        if (program && moveId >= 0) {
            for (size_t i = 0; i < program->count; ++i) {
                const MoveRule& rule = program->rules[i];
                if (rule.operation == MoveOp::Turn && rule.move == moveId &&
                    (rule.phase < 0 || rule.phase == m_phaseIndex) &&
                    rule.first <= m_moveElapsedTicks && m_moveElapsedTicks <= rule.last &&
                    rule_gate_holds(rule, opponent ? glm::dot(opponent->position() - m_position,
                                                   opponent->position() - m_position) : -1.f)) {
                    hasTurnRuleAtEntry = true;
                    break;
                }
            }
        }
        // Melee entry stays under directional dispatch, including the backward
        // air-dash actor-facing rule. Shot rows with a recovered Turn keep that
        // first tick; jump, guard and unruled shots face the lock on entry. An
        // already-armed fallback shot has committed its aim before this point.
        if (!hasTurnRuleAtEntry && !m_pending.armed && !backJump) m_facing = m_inputFacing;
    }
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
    // The hit freeze (+0xa0 = the record's combat[10]): the original's motion integrator
    // (FUN_004202b0) skips physics while that word is non-zero, so a victim is pinned in place
    // for the freeze window even when the blow is not strong enough to change its state row.
    // The animation clock keeps running, which is why the freeze reads as an impact and not as
    // a pause.
    if (m_hitFreeze > 0) {
        --m_hitFreeze;
        m_velocity = glm::vec3(0.f);
    } else if (((m_state == FighterState::AttackA || m_shotMoveId >= 0) && move_program(m_moves)) ||
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
    if (opponent && opponent->is_alive() && !locomotion(m_moves) &&
        !(m_state == FighterState::AttackA && m_aerialAttack && m_attackUsesActorFacing)) {
        update_facing(opponent, dt);
    }

    // 5. Stamina: the original refills in the standing handler (executor case 0,
    // +40/tick) and drains while blocking; dash/leap/flight spends happen at the
    // trigger sites below. The pilot path applies the recovered integer rates; the
    // legacy path keeps its grounded 60/s port rule.
    if (m_grounded && can_act() && !(m_state == FighterState::Run && m_dashMoveId == 20 &&
                                   locomotion(m_moves) && m_model)) {
        if (m_pilotMeter) {
            // The original's ordinary refill: executor case 0 (standing/idle,
            // FUN_0043ffc0) adds 0x28 (40) to +0x834 every tick, or 5 while hit-status
            // slot 6 is set, clamped at 1000 — before input handling, but NOT on a tick
            // that leaves the standing branch: one tick runs exactly one executor case,
            // so a launch/guard/attack tick takes that row's rule instead. The port's
            // state only changes after this section, hence stateBeforeInput. Mode 2's
            // extra +1 rides FUN_0041f580:97-98 independently.
            if (stateBeforeInput == FighterState::Idle && m_state == FighterState::Idle) {
                const int refill = m_hitStatusDuration[6] > 0 ? 5 : 40;
                m_actionMeter = std::min(1000, m_actionMeter + refill);
            }
            if (m_hyperActive && m_hypermode == Hypermode::Kakera)
                m_actionMeter = std::min(1000, m_actionMeter + 1);
        } else {
            m_stamina = std::min(m_stamina + FighterConstants::kStaminaRegenSec *
                                 static_cast<float>(dt),
                                 static_cast<float>(FighterConstants::kMaxStamina));
        }
    }
    // P2-7 meter, jump rows: the launch row refills +40 (+5 with hit-status slot 6)
    // every tick it is bound (jump bodies 40; the port binds row 40 for exactly the
    // launch tick via m_jumpStartup, and refresh_state_move runs after this section
    // so the flag is still set here). Landing refills the same way through the
    // landing transition below, and the row itself is bound now: row 44 plays for its
    // own derived length and Idle adds the same +40 per tick, so the multi-tick window
    // costs the meter nothing (V3-42).
    if (m_pilotMeter && m_state == FighterState::Jump && m_jumpStartup) {
        const int refill = m_hitStatusDuration[6] > 0 ? 5 : 40;
        m_actionMeter = std::min(1000, m_actionMeter + refill);
    }
    if (m_state == FighterState::Guard) {
        // Guard stance progression, recovered from the shipped data. Row 390's sections
        // are [preparation, hold, release]; the stance advances to the next section only
        // when the CURRENT clip has played past its own duration AND that clip does not
        // declare a hold phase. Animation-set +0x20 is that flag -- the format is
        // (blend_frames, hold_phase, event_count), which the port already parses as
        // animation_set_phase_gate() and never applied. A hold phase stays put and its
        // clip loops, which is the looping guard animation the original shows. The
        // release section (63) is not reached: releasing leaves Guard directly.
        if (m_moves && m_model && m_guardClip >= 0) {
            const CharacterMove* guardMove = m_moves->find(390);
            m_guardTicks += 1;
            if (guardMove && m_guardPhase + 1 < guardMove->sectionCount &&
                m_moves->animation_set_phase_gate(m_guardClip) == 0) {
                const std::size_t clip = static_cast<std::size_t>(m_guardClip);
                // anim.duration is in the model's X tick scale, not seconds: divide by
                // ticksPerSecond (xmodel.h; Rena's clips declare 4800) to get the clip's
                // wall-clock length. Comparing the raw value against seconds never
                // elapsed, so the stance never reached the hold phase.
                const double duration =
                    clip < m_model->anims.size() && m_model->ticksPerSecond > 0.f
                        ? static_cast<double>(m_model->anims[clip].duration) /
                              static_cast<double>(m_model->ticksPerSecond)
                        : 0.0;
                const int nextSet = guardMove->phase_set_index(m_guardPhase + 1);
                if (duration > 0.0 && m_guardTicks * dt > duration && nextSet >= 0 &&
                    static_cast<std::size_t>(nextSet) < m_model->anims.size()) {
                    m_guardPhase += 1;
                    m_guardTicks = 0;
                    m_guardClip = nextSet;
                    bind_animation_set(nextSet);
                }
            }
        }
        if (m_pilotMeter) {
            // Recovered guard 390 phase 1 drains 10/tick and exits at 0
            // (guard_native_control.hpp:38-42). The port has no guard phases, so the
            // drain runs every Guard tick; that granularity stays a named limit.
            m_actionMeter = std::max(0, m_actionMeter - 10);
            if (m_actionMeter <= 0) {
                m_guardExhausted = true;
                set_state(m_grounded ? FighterState::Idle : FighterState::Jump);
            }
        } else {
            m_stamina = std::max(0.0f, m_stamina - FighterConstants::kGuardDrainSec *
                                 static_cast<float>(dt));
            if (m_stamina <= 0.0f) {
                m_guardExhausted = true;
                set_state(m_grounded ? FighterState::Idle : FighterState::Jump);
            }
        }
    }

    // 5b. Vertical motion: hold-Z flight against the fly budget, else
    // gravity. Runs for every state (corpses fall too); only Jump and an
    // airborne dash convert the landing into Idle — Hit/KO/attacks keep
    // their state through touchdown.
    if (!m_grounded) {
        const float step = static_cast<float>(dt);
        // One hover per airtime: the original admits the jump row only while grounded
        // (FUN_00445ee0's jump branch needs the grounded byte 0x84 != 0), so releasing
        // the button mid-air ends that airtime's hover for good — a re-press falls
        // instead of climbing again (V3-10). The latch arms on the release, not on the
        // first hover tick, so a held button keeps climbing for the whole budget.
        const bool jumpDown = input && input->down[input::Action::Jump];
        if (!jumpDown) m_hoverSpent = true;
        // The pilot path has NO time budget: the recovered climb ends only when the button
        // is released or the meter is empty (row 41's exits are `0x3a`/meter comparisons,
        // never a duration). The 1.2 s kFlyTimeSec budget cut the climb with ~28% of the
        // bar still full — the meter is the only limit (V3-12). The legacy path keeps it.
        const bool flyBudget = m_pilotMeter ? m_actionMeter > 0 : m_flyLeft > 0.0f;
        // State 43 — the fall an air dash completes into — has no hover: its body writes only
        // the fall, the turn and the gravity restore (case 0x2b :529-545). So the row-41 climb
        // is not available until the fighter lands and leaves that state.
        const bool wantFly = jumpDown && m_state == FighterState::Jump && !m_dashFall &&
                             flyBudget && !m_hoverSpent && is_alive();
        // An air dash hangs while its phase is below 2 and then falls. FUN_0043ffc0 case
        // 0x1e subtracts 0.5/tick from +0x10 in BOTH windows but only the early one floors
        // it at zero (:386-390), so the dash can never descend before its recovery phase;
        // phase 2 subtracts +0x16 with no floor (:422-424), i.e. an ordinary fall. The
        // port hung for all three sections. kGravity is 1800 u/s^2, which is exactly the
        // body's 0.5 per tick per tick, so the normal fall is the recovered rate.
        const bool dashHang = m_state == FighterState::Run && m_dashAir &&
                              !(m_pilotMeter && m_phaseIndex >= 2);
        // A recovered attack body owns its fall while the value it published is
        // live: the bodies' per-tick^2 gravity (FUN_0043ffc0's air field +58)
        // replaces the locomotion rate, and 0 is a real hang (the chase's
        // pre-phase-2 flight), not "unset". -1 keeps the locomotion fall for
        // air rows with no recovered body — today's behavior.
        const bool attackFall =
            (m_state == FighterState::AttackA || m_shotMoveId >= 0) &&
            move_program(m_moves) && m_attackGravity >= 0.f;
        if (wantFly) {
            // Recovered row-41 climb: vy accelerates by +0.2/tick while the button is
            // held, capped at 6.0/tick, and every climbing tick spends 10 of the action
            // meter. THE METER IS THE ONLY LIMIT — no altitude cap exists in the air
            // chain (FUN_00421bd0, which an earlier note cited as a "flight cap", only
            // writes spawn X/Z and a 1000.0 respawn Y). The port used to overwrite vy
            // with a constant 12/tick and clamp the position at kFlyMaxAlt.
            if (m_pilotMeter) {
                constexpr float kClimbAccel = 0.2f * 60.f;   // 0.2 u/tick^2 in u/s^2
                constexpr float kClimbMax = 6.0f * 60.f;     // 6.0 u/tick in u/s
                m_vy = std::min(m_vy + kClimbAccel * static_cast<float>(dt), kClimbMax);
                if (!m_jumpStartup) m_actionMeter = std::max(0, m_actionMeter - 10);
            } else {
                m_vy = FighterConstants::kFlyRise;
                m_stamina = std::max(0.0f, m_stamina - FighterConstants::kFlyDrainSec * step);
            }
            m_flyLeft -= step;
        } else if (!dashHang) {
            if (attackFall)
                m_vy -= m_attackGravity * 4096.f * step;  // u/tick^2 -> u/s^2
            else
                m_vy -= FighterConstants::kGravity * step;
        }
        const float previousY = m_position.y;
        m_position.y += m_vy * step;
        // The 420-unit "flight cap" was a port invention with a misattributed citation
        // (FUN_00421bd0 has no cap); the recovered jump has no altitude limit at all, so
        // the pilot path keeps the legacy clamp only for the paths that still use it.
        const float ceiling = m_groundY + FighterConstants::kFlyMaxAlt;
        if (!m_pilotMeter && m_position.y > ceiling && !m_respawnLock) {
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
            m_airDashCarry = false;
            m_dashFall = false;
            m_landingTicks = 0;
            m_hoverSpent = false;   // a new airtime re-arms the one hover
            // A launched victim that touches down goes into the knockdown chain instead of
            // standing up: the original's airborne rows rebind to 118 (or its +100 back twin
            // 213-216 -> 119) the moment the grounded byte sets, and the lying row plays out
            // before the get-up. Which of the two is chosen is the SIGN of the victim's own
            // horizontal speed (0x4296ae): still travelling away means the back fall.
            if (m_state == FighterState::Hit && m_launched) {
                m_launched = false;
                const bool backwards = glm::dot(m_velocity, glm::vec3(-std::sin(m_facing), 0.f,
                                                                     -std::cos(m_facing))) > 0.f;
                m_reactionMove = backwards ? 119 : 118;
                m_downPhase = 1;
                set_state(FighterState::Knockdown);
                m_stateTimer = std::max(1, move_row_frames(m_reactionMove));
            }
            if (m_state == FighterState::Jump ||
                (m_state == FighterState::Run && m_dashAir)) {
                // Row 44 refills +40 (or +5 while status slot 6 is set) on every update, and
                // the port's Idle adds the same amount, so for a JUMP landing the window is
                // animation-only and the meter timing does not move. The dash arm below still
                // skips the landing tick's refill (its own gate is Jump-only), which is the
                // pre-existing gap; the window does not change it either way.
                if (m_pilotMeter && m_state == FighterState::Jump) {
                    const int refill = m_hitStatusDuration[6] > 0 ? 5 : 40;
                    m_actionMeter = std::min(1000, m_actionMeter + refill);
                }
                m_landingTicks = landing_row_frames();
                set_state(FighterState::Idle);
            } else if (m_state == FighterState::AttackA || m_shotMoveId >= 0) {
                // The recovered attack bodies' landing branches: a LandExit rule
                // matching the current row/phase/tick switches into the landing
                // move (320 -> 329, 334 -> 333, the air taps' 402 -> 403 and the
                // air charges' 460/370 -> 469), a LandPhase rule ends the move in
                // one of its own phases with speed and vertical zeroed (the hop's
                // and 341's landing), a LandSeek rule enters the phase and seeks its
                // clock (Rena 2's late landing: phase 1 at tick 25, vertical zeroed).
                // The tick windows are the bodies' own frame compares. Shot rows are
                // included: 402/408/460 are Shoot states in this port and their
                // bodies branch on the ground contact just like the melee rows.
                const MoveProgram* program = move_program(m_moves);
                if (program) {
                    const int moveId = state_move_id();
                    for (size_t i = 0; i < program->count; ++i) {
                        const MoveRule& rule = program->rules[i];
                        if (rule.move != moveId ||
                            (rule.phase >= 0 && rule.phase != m_phaseIndex) ||
                            m_moveElapsedTicks < rule.first || m_moveElapsedTicks > rule.last)
                            continue;
                        if (rule.operation == MoveOp::LandExit) {
                            switch_attack_row(static_cast<int>(rule.value));
                            break;
                        }
                        if (rule.operation == MoveOp::LandPhase) {
                            m_moveSpeed = 0.f;
                            m_vy = 0.f;
                            enter_phase(static_cast<int>(rule.value));
                            break;
                        }
                        // The late-landing seek (FUN_00438310 case 0x192: grounded at
                        // tick>=15 enters phase 1 with both clocks set to 25 and the
                        // vertical cleared): enter the phase and move the clock,
                        // leaving the carried speed to the row's own bleed.
                        if (rule.operation == MoveOp::LandSeek) {
                            m_vy = 0.f;
                            enter_phase(static_cast<int>(rule.value));
                            m_moveElapsedTicks = static_cast<int>(rule.second);
                            break;
                        }
                    }
                }
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
            m_airDashCarry = false;
            m_dashFall = false;
            m_landingTicks = 0;
            m_hoverSpent = false;   // a new airtime re-arms the one hover
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
        // The landing window counts down here, before the refresh, and the tick that closes it
        // rebinds Idle's own row below (refresh_state_move returns early for anything but Jump,
        // so the rebind cannot come from there). Leaving Idle (walking, attacking, jumping) ends
        // the window early, which is what the port's immediate cancel means today.
        if (m_landingTicks > 0) {
            if (m_state != FighterState::Idle) {
                m_landingTicks = 0;
            } else {
                --m_landingTicks;
                // Ending the window has to clear the bound set first: try_switch_animation
                // returns early while m_animSetIdx is still >= 0, which is what keeps a state's
                // clip stable across ticks.
                if (m_landingTicks == 0) {
                    // The row clock has to go with the set: it still reads row 44's last tick,
                    // and Idle's playhead is derived from it, so a landing would start the
                    // standing clip at ~frame 22 instead of frame 0. This is what set_state()
                    // did for the landing before the row existed.
                    m_animSetIdx = -1;
                    m_phaseIndex = 0;
                    m_moveElapsedTicks = 0;
                    try_switch_animation();
                }
            }
        }
        refresh_state_move();
        advance_animation_phase();
        if (m_state == FighterState::Guard && m_animate) {
            // Guard runs no move, so m_moveElapsedTicks never advances and driving the
            // playhead from it pinned the stance to frame 0 forever -- the "one frame,
            // static" the owner reported. The original advances the guard clip from its
            // own tick counter (bundle: `actor_animation_key_time(guard_tick, ...)`), so
            // the playhead follows m_guardTicks and wraps inside the clip's duration,
            // which is what makes a hold phase loop.
            double time = m_guardTicks * kOriginalAnimationTick;
            if (m_model && m_guardClip >= 0) {
                const std::size_t clip = static_cast<std::size_t>(m_guardClip);
                if (clip < m_model->anims.size() && m_model->anims[clip].duration > 0.0 &&
                    m_model->ticksPerSecond > 0.f) {
                    const double clipSeconds =
                        static_cast<double>(m_model->anims[clip].duration) /
                        static_cast<double>(m_model->ticksPerSecond);
                    if (clipSeconds > 0.0) time = std::fmod(time, clipSeconds);
                }
            }
            m_anim->setTrackPosition(m_blendTicks >= 0 ? 1 : 0, static_cast<float>(time));
            if (m_blendTicks < 0) m_anim->setTrackPosition(1, static_cast<float>(time));
        } else if (m_moves && m_animate) {
            const float time = m_moveElapsedTicks * kOriginalAnimationTick;
            m_anim->setTrackPosition(m_blendTicks >= 0 ? 1 : 0, time);
            if (m_blendTicks < 0) m_anim->setTrackPosition(1, time);
        } else if (m_animate && !m_animationBoundThisUpdate) {
            m_anim->advanceTime(std::min(dt, 0.1));
        }
        // The recovered class-specific blend counter advances once per update,
        // matching FUN_0041f580's per-tick weight calculation.
        tick_blend();
    }
    if (m_weapon) {
        for (int hand = 0; hand < 2; ++hand) {
            const int itemModel = m_trailItemModel[static_cast<size_t>(hand)];
            if (itemModel < 0 || itemModel >= m_weapon->slotCount ||
                !m_weapon->slots[itemModel].has_prop()) {
                m_trails[static_cast<size_t>(hand)].reset();
                continue;
            }
            const auto& slot = m_weapon->slots[itemModel];
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
    m_inputAxisX = held_axis_x(input);
    m_inputAxisZ = held_axis_z(input);
    if (input->just_pressed[input::Action::AttackA]) {
        // Attack selection runs through the recovered dispatcher for the Rena
        // group (melee_admission.h: FUN_00445ee0/44d850/43ded0 with their
        // weapon-specific families — 310/311 directional kicks, the dash-attack
        // rows, 320/332 air, the chains and 340/341 landing); other combos keep
        // the bounded #31/#66 candidates. NN.dat still supplies every row/clip.
        // Admission resolves BEFORE any attack-entry mutation: FUN_00445ee0's
        // declined branches take no action and execution continues to the later
        // input checks, so a rejected press must not enter AttackA, bind a
        // fallback clip, arm a swing or touch facing/aerial metadata.
        const bool aerial = !m_grounded;
        const int admitted = admit_attack_move(aerial, input);
        if (admitted >= 0) {
            set_aerial_attack(aerial);
            const bool rena0 =
                m_moves && m_moves->character_index() == 0 && m_moves->weapon_id() == 1;
            m_attackUsesActorFacing = rena0 && aerial && backInputHeld(input);
            if (rena0 && aerial && !m_attackUsesActorFacing) m_facing = m_inputFacing;
            m_attackMoveId = admitted;
            build_melee_swing(m_attackMoveId);
            set_state(FighterState::AttackA);
            // For a combo whose complete NN/.X phase timeline can auto-complete,
            // let FUN_00421100/FUN_004c57f0's period path end the move; contact-window
            // duration must not preempt later callbacks such as Akane's 300 phase-2
            // ribbon in FUN_00595460. Sets with a nonzero +0x20 gate still use the
            // contact timer until their handler-specific phase transition is mapped.
            const bool renaAirTimeline = rena0 && aerial &&
                (admitted == 320 || admitted == 332);
            m_stateTimer = renaAirTimeline ||
                               hasAutomaticMeleeTimeline(m_moves, m_weapon, m_model, admitted)
                               ? 0 : m_swing.total_ticks();
            return;
        }
        // Declined: fall through so simultaneous inputs keep their dispatch
        // order, exactly as FUN_00445ee0 evaluates jump/dash/etc. after the
        // declined attack branches.
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
        if (m_hyperActive && try_ex_move()) return;
    }

    // Shoot (C) — or S when neither of the above applies: holding
    // accumulates charge without interrupting the state (mobile charge —
    // the original's charge/movement interplay is un-RE'd, so the least
    // surprising model wins); releasing fires the held tier. Charge only
    // accrues while actionable so hits/attacks break the hold.
    const bool chargeDown = input->down[input::Action::Shoot] ||
                            (input->down[input::Action::Special] && !m_hyperActive);
    if (chargeDown) {
        // The release count the recovered empty-tap branch tests counts held frames, not
        // seconds: a bound weapon pins the seconds field to one tick.
        if (m_chargeHeldTicks < kChargeHoldTickCap) ++m_chargeHeldTicks;
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
        clear_charge_hold();
        if (m_pending.armed) return;
    }

    // Grounded only: the original has no air block, so an airborne press neither enters
    // the stance nor consumes the meter.
    if (input->down[input::Action::Guard] && m_grounded && !m_guardExhausted &&
        (m_pilotMeter ? m_actionMeter > 0 : m_stamina > 0.0f)) {
        // This branch runs on every HELD tick, not just the press edge, so the stance
        // reset must be edge-gated: resetting here unconditionally wiped the clip and the
        // tick counter every frame, which pinned the guard to frame 0 and made it static.
        if (m_state != FighterState::Guard) {
            m_guardClip = -1;   // re-bind row 390's opening clip for this stance
            m_guardPhase = 0;
            m_guardTicks = 0;
        }
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

    // P2-7 (2e) slice 2: with the pilot policy attached the recovered body answers the
    // Idle/Walk question; -1 (any state outside locomotion) keeps the legacy answer.
    if (m_pilotLocomotion) {
        const int proposal = m_pilotLocomotion->proposed_state(*this);
        if (proposal == 0 || proposal == 10) moving = proposal == 10;
    }

    if (moving && m_state == FighterState::Idle) {
        set_state(FighterState::Walk);
    } else if (!moving && m_state == FighterState::Walk) {
        set_state(FighterState::Idle);
    }
}

glm::vec3 Fighter::relative_direction(float yaw, float screenRight, float screenUp) const {
    const float fx = std::sin(yaw);
    const float fz = std::cos(yaw);
    // Right = up × facing in the left-handed yaw=0-faces-+Z world.
    return glm::vec3(fz, 0.0f, -fx) * screenRight + glm::vec3(fx, 0.0f, fz) * screenUp;
}

// The body's rendered yaw can turn with walking input; the combat lock remains
// the movement reference for directional actions (FUN_004202b0, FUN_0042dd90).
glm::vec3 Fighter::facing_relative(float screenRight, float screenUp) const {
    return relative_direction(m_facing, screenRight, screenUp);
}

glm::vec3 Fighter::target_relative(float screenRight, float screenUp) const {
    return relative_direction(m_inputFacing, screenRight, screenUp);
}

void Fighter::update_movement(const input::PlayerState* input, double dt) {
    if (!input) return;

    // Committed dash: steering is locked to the tapped direction for the
    // dash window (ground or air — m_dashDir was resolved at trigger time).
    if (m_state == FighterState::Run) {
        if (const auto* motion = locomotion(m_moves)) {
            if (m_dashMoveId == 20) m_dashSpeed = motion->forwardDash / static_cast<float>(dt);
        }
        // FUN_0043ffc0 case 0x17/0x18 store the side dash's movement as +/-90 (:265-271),
        // i.e. relative to the actor's target-facing basis, and the basis is refreshed
        // every update — so the step arcs toward the target rather than following the
        // direction captured at the tap. Re-derive it here, after this update's basis.
        if (m_pilotMeter && m_dashSide != 0)
            m_dashDir = target_relative(static_cast<float>(m_dashSide), 0.0f);
        // Case 0x1e re-runs FUN_00421780 every update with +0x874 = 60 deg/tick in phase 0
        // (:408) and 2 deg/tick from phase 1 (:414), so the dash turns with the stick
        // instead of freezing its entry direction.
        if (m_pilotMeter && m_dashAir && (m_inputAxisX != 0 || m_inputAxisZ != 0)) {
            const glm::vec3 wanted = relative_direction(
                m_inputFacing, static_cast<float>(m_inputAxisX),
                static_cast<float>(m_inputAxisZ));
            const float current = std::atan2(m_dashDir.x, m_dashDir.z);
            const float difference = std::remainder(std::atan2(wanted.x, wanted.z) - current,
                                                    glm::two_pi<float>());
            const float rate = glm::radians(m_phaseIndex == 0 ? 60.0f : 2.0f);
            const float next = current + std::clamp(difference, -rate, rate);
            m_dashDir = glm::vec3(std::sin(next), 0.0f, std::cos(next));
            m_facing = next;
        }
        m_velocity.x = m_dashDir.x * m_dashSpeed;
        m_velocity.z = m_dashDir.z * m_dashSpeed;
        m_position += m_velocity * static_cast<float>(dt);
        return;
    }

    // Momentum after an air dash. Case 0x2b (state 43) never writes the horizontal speed
    // or the movement angle, so the dash's slide continues and only the angle is steered,
    // at +0x874 = 1.0 deg/tick (:485-486). Without this the port zeroed the velocity when
    // no direction was held and the fighter dropped straight down (owner: D2).
    if (m_pilotMeter && m_airDashCarry && !m_grounded && m_state == FighterState::Jump) {
        if (m_inputAxisX != 0 || m_inputAxisZ != 0) {
            const glm::vec3 wanted = relative_direction(
                m_inputFacing, static_cast<float>(m_inputAxisX),
                static_cast<float>(m_inputAxisZ));
            const float current = std::atan2(m_dashDir.x, m_dashDir.z);
            const float difference = std::remainder(std::atan2(wanted.x, wanted.z) - current,
                                                    glm::two_pi<float>());
            constexpr float kFallTurnDegrees = 1.0f;   // +0x874 in case 0x2b
            const float next = current + std::clamp(difference, -glm::radians(kFallTurnDegrees),
                                                    glm::radians(kFallTurnDegrees));
            m_dashDir = glm::vec3(std::sin(next), 0.0f, std::cos(next));
            m_facing = next;
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

    // Recovered handlers classify walk input from the target bearing before
    // applying the body turn; unknown handlers keep a body-relative fallback.
    const float basis = locomotion(m_moves) ? m_inputFacing : m_facing;
    glm::vec3 dir = relative_direction(basis, screenRight, screenUp);

    // Normalize the direction vector (mirrors D3DXVec3Normalize in the original).
    float len = glm::length(dir);
    if (len > 0.001f) {
        dir /= len;

        const auto* motion = locomotion(m_moves);
        float speed = motion ? motion->walk / static_cast<float>(dt) : FighterConstants::kWalkSpeed;
        // P2-7 (2e) slice 2: the pilot policy's speed is the recovered body's own output; the
        // body reports units per tick, and the legacy expression divides the recovered
        // per-tick value by dt for the same reason (fighter.cpp's walk speed comment).
        if (m_pilotLocomotion) {
            const float pilotSpeed = m_pilotLocomotion->walk_speed_per_tick(*this);
            if (pilotSpeed >= 0.f) speed = pilotSpeed / static_cast<float>(dt);
        }
        if (!m_grounded) speed *= FighterConstants::kAirControl;

        const bool pilotAttached = m_pilotMeter || m_pilotLocomotion;
        if (pilotAttached && !m_grounded) {
            // Recovered air turn: the airborne movement branch (FUN_00428510 @0x428d9b)
            // writes +0x874 = 0x40000000 (2.0 degrees/tick) and calls FUN_00421780, which
            // turns the yaw toward the input's compass bearing by at most that step
            // (FUN_0042db10). So holding a direction mid-air rotates the body — the ground
            // turn's airborne counterpart, at its own rate. Without it the body never
            // rotated while airborne: the walk branch below only runs in the Walk state.
            const float desired = std::atan2(dir.x, dir.z);
            const float difference = std::remainder(desired - m_facing, glm::two_pi<float>());
            constexpr float kAirTurnDegrees = 2.0f;   // +0x874, per tick
            m_facing += std::clamp(difference, -glm::radians(kAirTurnDegrees),
                                   glm::radians(kAirTurnDegrees));
        } else if (motion && m_state == FighterState::Walk) {
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

void Fighter::apply_hit_status(unsigned slot, int duration, int power) {
    if (slot >= m_hitStatusDuration.size() || duration <= 0) return;
    int& oldDuration = m_hitStatusDuration[slot];
    int& oldPower = m_hitStatusPower[slot];
    if (oldDuration == 0 || (oldPower <= power && oldDuration < duration)) {
        oldDuration = duration;
        oldPower = power;
    }
}

void Fighter::tick_hit_status() {
    for (int& duration : m_hitStatusDuration)
        if (duration > 0) --duration;
}

int Fighter::hit_status_duration(unsigned slot) const {
    return slot < m_hitStatusDuration.size() ? m_hitStatusDuration[slot] : 0;
}

void Fighter::shove(const glm::vec3& delta, const game::physics::MovementCollision* collision) {
    if (delta == glm::vec3(0.f)) return;
    const glm::vec3 start = m_position;
    const glm::vec3 desired = start + delta;
    if (!collision) {
        m_position = desired;
        return;
    }
    // Same mover the ordinary step uses, so walls clamp the push instead of letting it tunnel
    // (the recovered function calls FUN_0042cb50 for each half for exactly this reason).
    const game::physics::MovementResult moved = collision->move(start, desired, m_grounded);
    m_position = moved.position;
    m_grounded = moved.grounded;
    if (m_grounded) m_groundY = m_position.y;
}

void Fighter::set_state(FighterState new_state) {
    if (m_state == new_state) return;
    // The air dash's carried momentum belongs to the airborne window it opened; a hit,
    // knockdown or KO that interrupts that window must not leave the fighter sliding at
    // dash speed when the reaction ends back in Jump.
    if (new_state == FighterState::Hit || new_state == FighterState::Knockdown ||
        new_state == FighterState::KO)
        m_airDashCarry = false;
    m_state = new_state;
    if (new_state != FighterState::AttackA) {
        m_aerialAttack = false;
        m_attackUsesActorFacing = false;
    }
    m_moveCounter = 0;
    m_movePitch = 0.f;
    m_holdTicks = 0;
    m_propActive = {false, false};
    m_actionCamera = -1;
    // Fresh action: the attack-body fall/lean state starts clean (the original's
    // +40/+58 persist only across row switches within one air action).
    m_attackGravity = -1.f;
    m_chaseStrength = 0;
    m_clockSkip = 0;
    m_bodyPitch = 0.f;
    m_bodyPivotHeight = 0.f;
    m_contactDisabled = false;
    if (new_state != FighterState::ShootA && new_state != FighterState::ShootB &&
        new_state != FighterState::ShootC) m_shotMoveId = -1;
    // A state with no selector (Guard) leaves the running move alone: the source's
    // block branch never re-binds, so the move, its phase cursor and its clip keep
    // going. Every other state starts a fresh row and a fresh phase.
    if (state_has_animation_selector(new_state)) {
        m_animSetIdx = -1;  // force animation re-lookup
        m_phaseIndex = 0;
        m_moveElapsedTicks = 0;
        // A fresh action supersedes a pending activation overlay: its clip is
        // already replaced by the rebind below, so the overlay's expiry must
        // not rebind (and restart) this action's clip later (issue #71). Guard
        // keeps this field: it never re-binds.
        m_hyperActivationSet = -1;
    }
    // Leaving the attack state ends this swing: the per-victim hit set clears so a
    // fresh swing may connect again (issue #10's per-swing accounting).
    if (new_state == FighterState::AttackA) {
        m_chainContact = false;
        m_chainGuarded = false;
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
        // No selector for this state (Guard): the source binds nothing, so the move and
        // the clip already playing continue. Only a state entered with nothing bound
        // (animation was off) needs a clip, and the standing set is that clip — it is
        // not a substituted guess, so it is not reported as a fallback.
        //
        // Guard is nonetheless NOT animateless. The character DAT carries the guard
        // stance as row 390 (preparation/hold/release), 391 (successful block) and 392
        // (the attacker's recoil), each with its own clips (Rena+0: 390 -> sets
        // 60/61/63, 391 -> 77/62/63, 392 -> 64/65). Not adopting the 390 MOVE body is a
        // deliberate separation: that body is a two-button chord (button_a &&
        // button_b) whose phase 1 exits on a missing button, so running it here would
        // drop the stance instead of holding it. Binding the opening clip gives the
        // stance its animation without touching the guard logic.
        if (m_state == FighterState::Guard && m_moves &&
            (m_animSetIdx < 0 || m_guardClip < 0)) {
            if (const CharacterMove* guardMove = m_moves->find(390)) {
                const int guardSet = guardMove->first_set_index();
                if (guardSet >= 0 && static_cast<std::size_t>(guardSet) < m_model->anims.size() &&
                    guardSet != m_animSetIdx) {
                    bind_animation_set(guardSet);
                    m_guardClip = guardSet;
                }
            }
        }
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
                                           int hitCategory, bool shot,
                                           const HitReaction& reaction) {
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

    // The freeze is applied on EVERY landed hit, before any stagger decision: it is what makes
    // a light blow interrupt movement even when it does not change the victim's row.
    m_hitFreeze = hitstunFrames > 0 ? hitstunFrames : 0;

    // The stagger meter (+0x7b8) decides whether this blow produces a reaction AND the damage
    // proration tier, so it is settled before the HP math. Below 100 the victim takes damage
    // and the freeze and keeps its current state row.
    m_hitMeterA += (reaction.meterA * kStaggerResist) / 100;
    m_staggerDecay = 120;   // +0x7bc: the meter's own 120-tick window
    const bool trips = m_hitMeterA >= 100;
    if (trips) {
        m_hitMeterA = 0;
        m_hitMeterB += reaction.meterB;   // +0x7c0: the heavy-row counter
        m_comboDecay = 120;
    }

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

    // Damage proration by the combo counter (+0x7b0): the resolver scales the blow by
    // 100/70/50/33 % for the first four staggering hits of a sequence (0x63854e-0x6385b8), and
    // the same table reappears in the projectile path (0x422ab0).
    if (trips) {
        static constexpr int kProration[4] = {100, 70, 50, 33};
        const int tier = std::min(m_comboHits, 3);
        amount = amount * kProration[tier] / 100;
        ++m_comboHits;
    }

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
        // The heavy row's counter (+0x7c0) is settled above with the trip.
        const bool heavy = m_hitMeterB >= 100;
        // combat[13] is the normal row, combat[14] the heavy one (0x6386f9-0x63870d), and a
        // hit from more than 90 degrees behind adds 100 — the back variant of the same band.
        // The heavy row is selected by the victim's own state as well: an AIRBORNE victim takes
        // combat[14] whatever the combo counter says (FUN_00637950 :349-356 tests the grounded
        // byte +0x84 alongside +0x7c0).
        const bool heavyRow = (heavy || !m_grounded) && reaction.rowHigh > 0;
        int row = heavyRow ? reaction.rowHigh : hitCategory;
        if (source) {
            const glm::vec3 toAttacker = source->position() - m_position;
            if (std::abs(toAttacker.x) > 1e-4f || std::abs(toAttacker.z) > 1e-4f) {
                const float bearing = std::atan2(toAttacker.x, toAttacker.z);
                const float relative =
                    glm::degrees(std::remainder(m_facing - bearing, glm::two_pi<float>()));
                if (std::abs(relative) > 90.f) row += 100;
            }
        }
        m_reactionMove = row > 0 ? row : 103;
        if (!trips) {
            // No reaction: damage and freeze only, the state row untouched.
            return DamageResult::Hit;
        }
        if (stun) {
            set_state(FighterState::Hit);
            // The stun a weapon inflicts is that weapon's own (FUN_00637950:308); a
            // weapon that specifies none keeps the shared default.
            m_stateTimer = hitstunFrames > 0 ? hitstunFrames
                                             : FighterConstants::kHitStunFrames;
            // The record's launch (FUN_00637950 @0x638633/0x638645 → the consumer at
            // 0x428af8-0x428b2e). A record with no launch keeps the victim planted.
            m_reactionCounter = reaction.counter;
            m_reactionRise = reaction.rise;
            // The ROW decides what the victim does — the hit code itself writes no motion
            // (FUN_00428510's per-row handlers own every constant). A row with no motion
            // profile leaves the victim planted: that is the "crumple in place" reaction.
            const ReactionMotion motion = reaction_motion(m_reactionMove);
            // A launch has to land somewhere: remember it so the touchdown turns into the
            // knockdown chain rather than a normal landing.
            m_launched = motion.liftFromRecord || motion.rise > 0.f;
            if (m_launched) {
                // A launch does not end on a stun counter: the victim stays in the reaction
                // until it touches down, which is what the row's own handler does (it rebinds
                // to 118 from the grounded test, never from a timer).
                m_stateTimer = 0;
            }
            if (motion.applies) {
                const float inverseStep = 1.f / static_cast<float>(FixedStep::seconds);
                const float speed = motion.slideFromRecord ? -reaction.counter : motion.speed;
                // +0x54 is applied along the body's own facing by the motion integrator
                // (FUN_004202b0 at 0x420349-0x420398); negative means backwards.
                if (speed != 0.f) {
                    const glm::vec3 forward(-std::sin(m_facing), 0.f, -std::cos(m_facing));
                    m_velocity = forward * (speed * inverseStep);
                }
                const float rise = motion.liftFromRecord ? std::fabs(reaction.counter) : motion.rise;
                if (rise > 0.f) {
                    m_vy = std::max(m_vy, rise * inverseStep);
                    m_grounded = false;
                }
            }
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
    // The cap-crossing ding (issue #71): the wire-0 feed plays SE 5 and the
    // wire-1 feed SE 6 exactly when the gauge reaches full (FUN_00637950's two
    // feed branches); wire 2 crosses silently.
    const bool wasFull = m_gauge >= 1.0f;
    m_gauge = std::min(1.0f, m_gauge + fraction * m_gaugeRate);
    if (!wasFull && m_gauge >= 1.0f) {
        const int wire = hypermode_wire_value(m_hypermode);
        if (wire == 0) m_pendingSoundEffect = {5, false, m_position};
        else if (wire == 1) m_pendingSoundEffect = {6, false, m_position};
    }
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
    // Per-wire presentation (issue #71; see hypermode_wire_value). Only wire 0
    // (Oyashiro) starts the move-500/501 pose: FUN_00445ee0's +0x318==0 branch
    // binds its phase-0 set (FUN_00421100 binds phase 0 on move start; every
    // Rena combo carries move 500 -> set 69), held as an overlay without
    // changing state. Its length is move 500's own phase window (see
    // hyper_activation_window_frames). A negative window is a gated hold: no
    // restore is scheduled and the fighter's next clip-binding action replaces
    // the clip. Friendship (wire 1) only arms (SE 7 plus the TagBack line ride
    // the audio event); it keeps the idle clip.
    // The red flash rides the same arm: the original sets +0x334 to 0xFC here
    // and FUN_0041f580 decays it 4 a tick while FUN_0063a130 fills the screen
    // with (alpha << 24) | 0xB00000. Kakera never sets it (no flash, per the
    // original's death-trigger path).
    const bool poses = hypermode_wire_value(m_hypermode) == 0;
    const CharacterMove* actMove = (m_moves && poses) ? m_moves->find(500) : nullptr;
    const int actSet = actMove ? actMove->first_set_index() : -1;
    if (m_animate && m_model && !m_model->anims.empty() && actSet >= 0 &&
        static_cast<std::size_t>(actSet) < m_model->anims.size()) {
        bind_animation_set(actSet);
        m_hyperActivationFrames = hyper_activation_window_frames(m_moves, m_model, 500);
        m_hyperActivationSet = actSet;
        m_hyperActivationElapsed = 0;
    } else {
        m_hyperActivationFrames = 0;
        m_hyperActivationSet = -1;
    }
    if (poses) m_hyperFlash = 0xFC;

    // Move 500's frame-8 ring shoves anyone in range away with no damage, so
    // only the posing (wire-0) activation shoves.
    if (poses && opponent && opponent->is_alive()) {
        const glm::vec3& tp = opponent->position();
        glm::vec3 away(tp.x - m_position.x, 0.0f, tp.z - m_position.z);
        const float dist = glm::length(away);
        if (dist > 0.0001f && dist <= FighterConstants::kMeleeRange) {
            opponent->apply_knockback(away / dist, FighterConstants::kRunSpeed);
        }
    }
    return true;
}

bool Fighter::try_ex_move() {
    // The armed S-press fires move 0x15e (FUN_00445ee0's EX branch; 350 for
    // Rena) once the +0x84 descent/grounded flag is set — rising fighters fall
    // through to the charge logic instead. Other characters' EX rows are
    // unmapped, so they keep the provisional ShotFinal path (issue #71).
    if (!m_grounded && m_vy > 0.f) return false;
    if (m_moves && m_moves->character_index() == 0 && present_move(350)) {
        set_aerial_attack(!m_grounded);
        m_attackMoveId = 350;
        build_melee_swing(m_attackMoveId);
        set_state(FighterState::AttackA);
        m_stateTimer = hasAutomaticMeleeTimeline(m_moves, m_weapon, m_model, 350)
                           ? 0
                           : m_swing.total_ticks();
        return true;
    }
    // EX content per character is un-RE'd. `shotFinal` is a provisional port
    // label; the corpus confirms a conditional numeric move-503 follow-up, not a cue binding.
    fire_shot(ShotTier::Ex);
    return true;
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

// P2-7 (2e) guard gate: the recovered predicate, answered by the pilot policy when one is
// attached to the victim. `FUN_00637950`'s guarded branch applies no damage and no stun, so a
// guarded hit must not reach take_damage. Asked only once a hit has landed, so the predicate
// can never change whether a swing connects.
inline bool pilot_guard_blocks(const Fighter& victim, const Fighter& attacker) {
    const Fighter::PilotGuard* guard = victim.pilot_guard();
    return guard && guard->guards_hit(victim, attacker);
}

bool Fighter::try_melee_hit(Fighter& target, const game::physics::MovementCollision* collision) {
    // Only the light/chain melee plays this path; the EX and shots go elsewhere.
    if (m_state != FighterState::AttackA) return false;
    // The dive body cuts its volume past phase-1 frame 22 (keiichi_dive's
    // disable_contact) — the posed record stays, the hit does not.
    if (m_contactDisabled) return false;
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
        m_meleeChargeBases = {record->hpDamage, record->reflectDamage};
        if (!pilot_guard_blocks(target, *this)) {
            const int damage = portDamage(meleePoolDamage(record->baseDamage), m_maxHP);
            // combat[17]/[18] are the launch words (+0x87c/+0x878, 0x638633/0x638645); the
            // consumer scales them by the global 0.01 at 0x6a24c4.
            HitReaction reaction;
            reaction.row = record->reactionMove;
            reaction.rowHigh = record->combat[14];
            reaction.counter = static_cast<float>(record->combat[17]) * 0.01f;
            reaction.rise = static_cast<float>(record->combat[18]) * 0.01f;
            reaction.meterA = record->combat[7];
            reaction.meterB = record->combat[8];
            target.take_damage(damage, this, record->defenderHitstun, record->reactionMove, false,
                               reaction);
        }
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
    // P2-7 (2e) guard gate: with the pilot policy attached to the victim, a guarded hit
    // applies no damage and no stun — `FUN_00637950`'s guarded branch writes only the contact
    // word, the per-slot marker and [victim+0xaf30], and calls no damage helper. The block
    // report and the attacker's 392 recoil still happen in the match pass. The legacy default
    // has no policy and keeps the provisional 20% rule inside take_damage.
    // The legacy swing carries no record columns; the recovered charge bases are a record
    // property, so they stay zero here and the pilot's mode gauges simply do not advance.
    m_meleeChargeBases = {};
    if (!pilot_guard_blocks(target, *this)) {
        const int dmg = m_swing.dataDriven ? m_swing.damage : FighterConstants::kLightDamage;
        target.take_damage(dmg, this, m_swing.hitstun);
    }
    return true;
}

void Fighter::begin_melee_swing() {
    m_swingHits = 0;
    m_swingHitCount = 0;
    m_meleeElapsed = 0;
}

void Fighter::note_melee_hit(int victimIndex, bool guarded) {
    if (victimIndex < 0 || victimIndex >= kMatchFighterCount) return;
    m_swingHits |= (1u << victimIndex);
    ++m_swingHitCount;
    m_chainContact = true;
    m_chainGuarded = guarded;
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

int Fighter::numeric_state() const {
    // The numeric action row the original's dispatcher reads: attack rows during
    // AttackA, the dash row during Run, the air-dash row 30 (scoped to Rena+0's
    // binding) or the jump chain 40..42 airborne, and 10/0 for locomotion.
    switch (m_state) {
        case FighterState::AttackA: return m_attackMoveId;
        case FighterState::Run:
            if (!m_dashAir) return m_dashMoveId;
            [[fallthrough]];
        case FighterState::Jump:
            return m_dashAir && m_dashMoveId > 0 ? m_dashMoveId : jump_chain_move();
        case FighterState::Walk:    return 10;
        default:                    return 0;
    }
}

int Fighter::weapon_slot_index() const {
    if (!m_moves || !m_weapon) return -1;
    return weaponSlotForItem(m_moves->character_index(), m_weapon->id);
}

AttackAdmissionInput Fighter::attack_input(bool aerial,
                                           const input::PlayerState* input) const {
    AttackAdmissionInput in;
    in.weaponSlot = weapon_slot_index();
    in.state = numeric_state();
    in.phase = m_phaseIndex;
    in.grounded = !aerial;
    in.x = held_axis_x(input);
    in.z = held_axis_z(input);
    // Locomotion and air rows are actionable; an attack row carries its own
    // 0x100 window from the current NN record (the pinned chain evidence).
    in.normalFlag = m_state == FighterState::AttackA
        ? (current_move_record() && (current_move_record()->stateFlags & 0x100))
        : true;
    in.contact = m_chainContact ? 1u : 0u;
    // The dispatchers' boosted pair (`byte(+0x845) && word(+0x848)`) is an armed special
    // plus its ready flag; the port carries the armed Oyashiro state, and the ready half
    // is the gauge/aim layer the powered shot gate already models (recorded deltas at the
    // 350 branch and in §1 of the attack matrix).
    in.boosted = m_hyperActive && m_hypermode == Hypermode::Oyashiro;
    return in;
}

int Fighter::admit_attack_move(bool aerial, const input::PlayerState* input) const {
    if (!m_moves || !attack_admission_recovered(m_moves->character_index()))
        return resolve_attack_move(m_state == FighterState::Run, aerial);
    // NO gauge gate on the melee press. Every explicit `0 < +0x834` test in FUN_00445ee0
    // guards a DASH or JUMP arm (its lines 59/65/72/82/92/100/441/449 bind moves
    // 0x14/0x1e/0x28 and the +0x830 dash-selector arm), and the single `+0x834 < 1`
    // (line 168) is an OR term that routes the press into the SHOT path -- it is not a
    // refusal. The recovered meter therefore gates blocking, dashes, jump and the air
    // dash only; a plain attack stays available at zero. Owner report (V3-18) and the
    // line-by-line reading agree. The tap-shot gauge question lives in fire_shot, which
    // gates on ammunition, not on this meter.
    const AttackAdmissionInput in = attack_input(aerial, input);
    // FUN_0044d850:117-118 / FUN_00445ee0:117-118 — the boosted branch is a TWO-LATCH
    // CHORD: `(+0x288 != 0) && (+0x284 != 0)`, both `< 3`, on top of the ordinary
    // admission's own single-button entry `+0x284 == 3` at :316. `+0x284` is the melee
    // latch (the melee arm takes it alone) and `+0x288` the second one, whose chord with
    // it also drives the hyper arming command (FUN_0063c2a0 case 0x24). The port carries
    // the melee button as AttackA and that second button as Special, so the chord is
    // `down[AttackA] && down[Special]`; a lone attack press is the ORDINARY melee, not
    // the awakened one. The chord's `< 3` half (the latch held rather than on its press
    // frame) is not recoverable: the latch's decay inside FUN_0041efe0's max-merge is not
    // established, so the port accepts either. Recorded, not guessed.
    //
    // The arming half is `+0x845 || +0x844 || +0x846` (:164-165). Those three bytes are
    // the three hyper LEVELS, not "Oyashiro / aim lock / hyper-2": FUN_0063c2a0:267-277
    // dispatches ONE activation command on the per-slot byte +0x318 into FUN_00421fe0
    // (level 1, +0x844), FUN_004220e0 (level 2, +0x845) or FUN_00422160 (level 3, +0x846).
    // The port's single m_hyperActive is therefore the faithful reading of the
    // disjunction, and the earlier note calling +0x844 an "aim-lock-only" arming was a
    // misreading of that byte; it is withdrawn.
    //
    // Scoped to weapons 0/1 because only their 0x15e is the awakened MELEE: weapon 2's
    // 0x15e is the full-charge SHOT, which the port selects through the charge path's
    // {350,360} tier. The dispatcher itself is weapon-independent, so an attack-key press
    // on weapon 2 with a special armed is a port-side scoping decision, not a source claim.
    // Scoped to the Rena group: Mion's 0x15e is reached from a different section of her
    // dispatchers (the air side of the special/awakened block, FUN_0045f4d0:186-189) and
    // her 0x15e semantics are unrecovered, so admitting it for her would bind a row with
    // no body. A recorded gap, not a silent extension.
    const bool specialHeld = input && input->down[input::Action::Special];
    if (!aerial && m_moves && m_moves->character_index() == 0 && m_hyperActive &&
        (in.weaponSlot == 0 || in.weaponSlot == 1) && in.normalFlag && specialHeld &&
        AttackAdmissionTable{m_moves}.gate(in.state, 350) && present_move(350) > 0)
        return 350;
    const int character = m_moves ? m_moves->character_index() : -1;
    return melee_admission_for(character, in, AttackAdmissionTable{m_moves});
}

int Fighter::resolve_attack_move(bool dashAttack, bool aerial) const {
    if (!m_moves) return -1;
    const bool rena0 = m_moves->character_index() == 0 && m_moves->weapon_id() == 1;
    if (aerial && !rena0) return present_move(340);
    // FUN_00445ee0:319-323 selects 332 from airborne dash row30 (phase<2).
    // Live inspection rejected both 311 and 340; validate this route visually.
    if (dashAttack && aerial && rena0) return present_move(332);
    if (dashAttack) {
        const int lunge = present_move(330);
        if (lunge >= 0) return lunge;
    } else if (aerial) {
        const int jump = present_move(320);
        if (jump >= 0) return jump;
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
    if (!m_moves) return -1;
    // FUN_00445ee0:69-110 sends Rena's airborne directional dash requests to
    // row 30, not the grounded 20/23/24/27 families. Other combos stay unresolved.
    if (!m_grounded) {
        if (m_moves->character_index() == 0 && m_moves->weapon_id() == 1)
            return present_move(30);
        return -1;
    }
    if (dir == input::Action::Up) return present_move(20);
    if (dir == input::Action::Down) return present_move(27);
    // Side-step rows are command-mapped, not screen-mirrored: the direction
    // history yields command 3 for x=-1 (Left) and 4 for x=+1 (Right), and every
    // admission switch routes command 3 -> row 24 and command 4 -> row 23
    // (FUN_00445ee0:86-95 branches +0x830==3 -> 0x18 / ==4 -> 0x17; donor
    // rena_dash.hpp:11, battle_roster_air_dash_admission.hpp:8,
    // dash_melee_native_control.hpp:82). NN.dat supplies their clips (Rena0
    // row 24 opens on set 19, row 23 on set 22).
    // Retain the facing-relative movement policy while playing the equipped clips.
    if (dir == input::Action::Left) return present_move(24);
    if (dir == input::Action::Right) return present_move(23);
    return -1;
}

int Fighter::state_move_id() const {
    switch (m_state) {
        // The swing keeps the combo row chosen on its input edge: 300 for neutral
        // ground/jump, 330 for a grounded dash and 311 after an air dash. The
        // special 340 selector contexts are not broadened by the #31 repair.
        case FighterState::AttackA:
            return present_move(m_attackMoveId);
        case FighterState::ShootA:
        case FighterState::ShootB:
        case FighterState::ShootC: return present_move(m_shotMoveId);
        case FighterState::Run:     return m_dashMoveId;
        case FighterState::Jump:    return jump_chain_move();
        // Guard binds no MOVE: the block branch of FUN_00637950 binds nothing at the
        // instant of the block, and the 390 body is a two-button chord
        // (button_a && button_b) that would exit the stance rather than hold it. The
        // stance's CLIP is bound in try_switch_animation instead -- see the note there.
        case FighterState::Guard:   return -1;
        // The landing window: row 44's clip, then Idle's own row.
        case FighterState::Idle:
            return m_landingTicks > 0 ? present_move(44) : state_to_move_id(m_state);
        // The reaction row: the record that landed names it in combat[13], which reaches
        // take_damage as `hitCategory` (FUN_00637950 hands the victim the row before the state
        // change). One constant row for every hit was the port's stand-in; the shipped tables
        // use 100 for the light swing, 101 for the kicks, 130/131 for the Hyper EX and so on,
        // which is what makes two hits look different.
        case FighterState::Hit: {
            // Fall back to the state's own row when the table does not carry the reaction id
            // (a synthetic table in a test, or a table without the row) — the same rule the
            // landing row uses, so a missing row cannot silently unbind the state.
            const int row = present_move(m_reactionMove);
            return row >= 0 ? row : state_to_move_id(m_state);
        }
        default:                    return state_to_move_id(m_state);
    }
}

int Fighter::move_row_frames(int row) const {
    // A row's own clip length, the same derivation the landing window uses: the row names a
    // phase whose set is the clip, and the loader turns its period into frames.
    const CharacterMove* move = m_moves ? m_moves->find(row) : nullptr;
    if (!move || !m_model) return 0;
    return std::max(0, animation_period_frames(*m_model, move->phase_set_index(0)));
}

int Fighter::landing_row_frames() const {
    // The recovered length is the row's own clip, not a constant: set 44 is 1760 ticks at the
    // model's 4800 ticks/second, and the original's window is the frame count its loader derives
    // from that period (trunc(1760 / 4800 / 0.016) = 22). Reading the bound model keeps the
    // number honest for a combo whose landing clip differs.
    const CharacterMove* landing = m_moves ? m_moves->find(44) : nullptr;
    const int set = landing ? landing->phase_set_index(0) : -1;
    if (!m_model) return 0;
    return std::max(0, animation_period_frames(*m_model, set));
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
    // State 43 has NO clock of its own and no hover: it is the row an air dash completes into
    // (FUN_0043ffc0 case 0x1e -> FUN_00421080(0x2b), :379-381), its body only falls and steers
    // (case 0x2b :529-545), and it leaves only on landing (into row 44). Binding it here is what
    // makes the first post-dash update play set 43 instead of the jump chain's set 5.
    if (m_dashFall) return present_move(43);
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
    // The weapon-2 spin's double-speed frames (advance_battle_attack300's extra
    // ++frame through 16..28): the whole phase clock — the record cursor the
    // rules read and the animation's own phase advancement — runs the extra ticks
    // the ClockSkip rule published this update.
    //
    // Row 23's body adds a SECOND increment when the entering primary clock is divisible
    // by 9 (FUN_0043ffc0 case 0x17, :288-291), before the common tail's ordinary one
    // (:2439-2443). Zero is divisible, so the phase opens on frame 2 and the sequence runs
    // 2,3,...9,11,12; without it every section lasts one update too long. Row 24's body
    // (case 0x18) carries the same rule and remains a named follow-up.
    const bool sideDashClock = m_pilotMeter && m_state == FighterState::Run && m_dashMoveId == 23;
    const int clockStep =
        1 + m_clockSkip + ((sideDashClock && m_moveElapsedTicks % 9 == 0) ? 1 : 0);
    if (!m_holdAnimation) m_moveElapsedTicks += clockStep;
    if (m_moves->animation_set_phase_gate(set) != 0) return;

    // FUN_0041e180's window: GetPeriod() / 0.016 through the CRT's truncating
    // float->int conversion (animation_period.h), so a 23.96-frame clip occupies 23
    // updates. A gated phase holds past expiry and is handled above.
    const int periodThreshold = animation_period_frames(*m_model, set);
    if (periodThreshold < 0) return;   // data cannot settle the window; 0 is a real window

    const bool lastSection = m_phaseIndex + 1 == move->sectionCount;
    // FUN_004218c0 ends the ROW on `period <= frame + 1`, using the frame the update
    // entered with, and only once the phase is the row's last (it also requires
    // `FUN_0063bf40() - 1 <= phase`, and that function is just `this + 0x10`, the section
    // count cached by FUN_00421100). That is one update earlier than the tail's
    // `period < frame` advance between sections (:2442), so the last section ends before
    // its clock passes the period. Both read the SAME record: FUN_00421410:31 stores one
    // pointer per set (`+set*0xe + 0x1d78`) for both tracks, at +0xade4 (track 0, the
    // tail) and +0xade8 (track 1, this predicate).
    if (lastSection && !m_holdAnimation && periodThreshold <= m_moveElapsedTicks - clockStep + 1) {
        if (m_state == FighterState::AttackA || m_state == FighterState::Run ||
            m_state == FighterState::ShootA || m_state == FighterState::ShootB ||
            m_state == FighterState::ShootC) {
            // An air dash that ends still airborne lands in the original's state 43, not in
            // the jump chain: remember it so the fall binds move 43's clip (V3-42).
            if (m_state == FighterState::Run && m_dashAir && !m_grounded) m_dashFall = true;
            set_state(m_grounded ? FighterState::Idle : FighterState::Jump);
        }
        return;
    }
    if (periodThreshold >= m_moveElapsedTicks) return;

    if (lastSection) {
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
    m_clockSkip = 0;
    // FUN_0043ffc0's prologue: slot0<-prop0, slot1<-prop1, then both props deactivated.
    // Hide and Active windows below re-state what this frame actually wants.
    m_propBound = {true, true};
    m_propActive = {false, false};
    m_trailItemModel = {0, 1};
    // The port's contact model: the posed records own the swing by default, and the
    // MoveOp::ContactOff windows cut it where the bodies call FUN_00434bd0 (which runs
    // inside the state bodies, not in a prologue). The reset therefore starts enabled
    // and each ContactOff rule disables for its ticks.
    m_contactDisabled = false;
    const MoveProgram* program = move_program(m_moves);
    m_sourceShotVoiceAudited = shot_voice_policy_audited(program, state_move_id());
    m_sourceMeleeVoiceAudited = melee_voice_policy_audited(program, state_move_id());
    const auto* motion = locomotion(m_moves);
    const CharacterMove* move = m_moves ? m_moves->find(state_move_id()) : nullptr;
    if (move && m_model && m_phaseIndex + 1 == move->sectionCount &&
        (m_state == FighterState::AttackA ||
         (motion && m_state == FighterState::Run && m_dashMoveId == 20) || m_shotMoveId >= 0)) {
        const int set = move->phase_set_index(m_phaseIndex);
        const int period = animation_period_frames(*m_model, set);
        if (set >= 0 && static_cast<size_t>(set) < m_model->anims.size() && period >= 0) {
            if (period <= m_moveElapsedTicks + 1) {
                set_state(m_grounded ? FighterState::Idle : FighterState::Jump);
                m_moveSpeed = 0.f;
                return;
            }
        }
    }
    // FUN_0043ffc0:946-954 exits row 320's gated approach phase; that callback is
    // now the chase body below (which carries the height term and the strength
    // exit for the whole group, superseding the Rena+0-only special case).
    if (m_state == FighterState::AttackA && program) {
        const int moveId = state_move_id();
        // The attacker-side guard reaction: the melee bodies test the contact
        // word's bit 2 (FUN_0042c7b0() & 2) every tick and hand the attacker to
        // the 392 knockback for the rows whose bodies carry the branch — the
        // per-weapon table in rena_guard_exit_row, recovered from the 0x188
        // switch sites of all three handlers.
        if (m_chainGuarded) {
            const int guardRow = rena_guard_exit_row(weapon_slot_index(), moveId);
            if (guardRow > 0 && present_move(guardRow)) {
                switch_attack_row(guardRow);
                return;
            }
        }
        if (program->chase && moveId == 320) {
            advance_rena_chase(*program->chase, opponent);
        } else if (program->dive && (moveId == 332 || moveId == 334)) {
            advance_rena_dive(*program->dive, opponent);
        }
    }
    // Rena+1's air tap dive launch (FUN_00448220 case 0x192, phase 1 tick 0): the
    // vertical/horizontal split comes from the target's geometry, so it runs as a
    // body the same way the chase/dive feedback loops do.
    if (m_shotMoveId == 402 && m_moves && weapon_slot_index() == 1)
        advance_rena1_dive_shot(opponent);
    if (motion && m_model && m_state == FighterState::Run && m_dashMoveId == 20) {
        // Constructor-bound handlers use the same phase contract with different
        // profile values. NN.dat supplies each phase's pose/gate/period.
        // Rena+0's grounded dash drains the recovered -12/tick on the pilot path
        // (dash bodies :53); the -3 inner arm of air dash 30 is a named limit (it needs
        // the +0x280 word, and the port has no state-30 frame clock), so state 30 takes
        // the outer -11.
        if (m_phaseIndex < 2) {
            if (m_pilotMeter) m_actionMeter = std::max(0, m_actionMeter - 12);
            else m_stamina = std::max(0.f,m_stamina-motion->dashDrain);
        }
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
            if ((!x && !z) || (m_pilotMeter ? m_actionMeter <= 0 : m_stamina <= 0.f)) { enter_phase(2); return; }
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
    // Pilot path: the dash states the move-20 block above does not model drain the
    // recovered per-state rates, and the default path keeps the legacy flat trigger
    // spend. Ground rows 23/24/27/28 drain -12 only while the phase is below 2
    // (FUN_0043ffc0 case 0x14 :195, 0x17 :257-259, 0x18 :309-311, 0x1b/0x1c :355) — the
    // recovery phase spends nothing. Those rows also carry NO meter exit, unlike the
    // forward dash (:229) and the air dash (:418) which leave phase 1 on `+0x834 < 1`,
    // so an admitted side or back dash runs to its last update even at zero. Air dash 30
    // guards on `phase < 3` (:382-383), which is every section of its three-phase row, so
    // its -11 covers the whole state. Its extra -3 sits inside `phase < 2` and is gated on
    // the word at byte +0x280 (:384-396; `param_1[0xa0]` is word index 0xa0, not byte
    // +0xa0 — that byte is the prologue's freeze word, `param_1[0x28]`), which the port
    // leaves UNMAPPED; that arm stays a named limit.
    // The air dash's travel section is a GATED hold: its set declares +0x20, so neither
    // the clock nor the completion predicate can end it. The body counts its own visits in
    // +0x3a and leaves for the recovery phase once more than five have passed and either
    // no direction is held or the meter is empty (FUN_0043ffc0 :413-420). Holding the
    // stick therefore extends the dash, which is what makes it steerable.
    if (m_pilotMeter && m_state == FighterState::Run && m_dashMoveId == 30 &&
        m_phaseIndex == 1) {
        ++m_airDashTicks;
        const bool noDirection = m_inputAxisX == 0 && m_inputAxisZ == 0;
        if (m_airDashTicks > 5 && (noDirection || m_actionMeter <= 0)) {
            enter_phase(2);
            return;
        }
    }
    if (m_pilotMeter && m_state == FighterState::Run) {
        if (m_dashMoveId == 23 || m_dashMoveId == 24 ||
            m_dashMoveId == 27 || m_dashMoveId == 28) {
            if (m_phaseIndex < 2) m_actionMeter = std::max(0, m_actionMeter - 12);
        } else if (m_dashMoveId == 30) {
            m_actionMeter = std::max(0, m_actionMeter - 11);
        }
    }
    // The air dash's lift. Byte +0x280 is the JUMP button's held-frame counter (slot 0 of
    // the input counters at actor+0x280..0x29c; incremented while the key is down and
    // zeroed on release by the per-frame poll, FUN_00657390), *not* the +0xa0 freeze word.
    // While it is non-zero and the phase is below 2 the body adds 0.5/tick to the vertical
    // (cap 8.0/tick) and charges an extra -3 meter (FUN_0043ffc0 :385-396); with the button
    // up it bleeds 0.5/tick back to zero, which is the hang the port had hard-coded.
    // Phase 2 then subtracts gravity from whatever this accumulator reached (:423-425).
    if (m_pilotMeter && m_state == FighterState::Run && m_dashMoveId == 30 &&
        m_phaseIndex < 2) {
        constexpr float kLiftStep = 0.5f * 60.0f;    // 0.5 u/tick per tick, in u/s
        constexpr float kLiftCap = 8.0f * 60.0f;     // 8.0 u/tick, in u/s
        const bool jumpHeld = input && input->down[input::Action::Jump];
        if (jumpHeld) {
            m_vy = std::min(m_vy + kLiftStep, kLiftCap);
            m_actionMeter = std::max(0, m_actionMeter - 3);
        } else {
            m_vy = std::max(0.0f, m_vy - kLiftStep);
        }
    }
    // Side-step travel speed. FUN_0043ffc0 case 0x17/0x18 seeds 20.0 on the phase's
    // first update, bleeds 0.5 per update while the phase is below 2 (floor 12.5) and
    // 0.7 per update in recovery (floor 0) (:186-214). A constant kRunSpeed covers the
    // same updates at the wrong speed, ~57% more ground, so the profile is per update in
    // the units the movement step consumes (u/s = per-update * 60). Pilot-only, like the
    // recovered row rules beside it; the COM keeps the constant legacy speed.
    if (m_pilotMeter && m_state == FighterState::Run &&
        (m_dashMoveId == 23 || m_dashMoveId == 24)) {
        constexpr float kDashSpeedScale = 60.0f;          // per-update units to units/second
        constexpr float kSideSeed = 20.0f * kDashSpeedScale;
        constexpr float kSideFloor = 12.5f * kDashSpeedScale;
        constexpr float kSideBleed = 0.5f * kDashSpeedScale;
        constexpr float kSideStop = 0.7f * kDashSpeedScale;
        if (m_phaseIndex == 0 && m_moveElapsedTicks == 0) m_dashSpeed = kSideSeed;
        if (m_phaseIndex < 2) m_dashSpeed = std::max(kSideFloor, m_dashSpeed - kSideBleed);
        else m_dashSpeed = std::max(0.0f, m_dashSpeed - kSideStop);
    }
    // Akane+0's recovered handler binds Prop0 to item model 2 for these
    // exact move windows (FUN_00595460 -> FUN_00434a70). Keep this
    // trail-only descriptor outside MoveProgram so it does not claim her
    // unrelated shot or voice callbacks are implemented.
    if (m_weapon) {
        for (int hand = 0; hand < 2; ++hand) {
            const TrailBinding* binding = trail_binding(m_moves,state_move_id(),hand);
            const int itemModel = binding ? binding->itemModel : hand;
            // The recovered shot body's clear takes precedence over the derived binding; only
            // the pilot policy ever asks for it, so the default path is unchanged.
            m_trailItemModel[static_cast<size_t>(hand)] =
                (m_pilotShot && m_pilotShot->clears_item_models()) ? -1 : itemModel;
            if (!trail_window(m_moves,state_move_id(),m_phaseIndex,m_moveElapsedTicks,hand))
                continue;
            if (itemModel >= 0 && itemModel < m_weapon->slotCount &&
                m_weapon->slots[itemModel].has_prop())
                m_propActive[static_cast<size_t>(hand)] = true;
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
        if (!rule_gate_holds(rule, distanceSquared)) continue;
        switch (rule.operation) {
        case MoveOp::Speed:
            m_moveSpeed = opponent && rule.third > 0.f && distanceSquared < rule.third
                              ? rule.second : rule.value;
            break;
        // The bodies' bleeds floor at zero for positive speeds; the guard-knockback's
        // -15 entry (FUN_0043ffc0 case 0x188) recovers TOWARD zero from below, so the
        // op moves the speed toward zero from either side.
        case MoveOp::Decelerate:
            m_moveSpeed = m_moveSpeed > 0.f ? std::max(0.f, m_moveSpeed - rule.value)
                                            : std::min(0.f, m_moveSpeed + rule.value);
            break;
        case MoveOp::Turn:
            // Contact-gated turn (second > 0); the Back-held actor-facing rule and
            // the null-opponent case live in turn_toward.
            if (rule.second > 0.f && !m_chainContact) break;
            turn_toward(opponent, rule.value);
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
            if (slot >= 0 && slot < 2 && m_weapon && slot < m_weapon->slotCount &&
                m_weapon->slots[slot].has_prop())
                m_propActive[static_cast<size_t>(slot)] = true;
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
        case MoveOp::Voice:
            m_shootingVoice.event = resolve_shot_voice_event(
                rule.voice, main_whole(), charge_whole());
            if (m_shootingVoice.event >= 0 && rule.voice.alternativeFirst >= 0 &&
                rule.voice.alternativeSecond >= 0) {
                m_shootingVoice.alternative =
                    rng_source().modulo(100) < static_cast<std::uint32_t>(
                        rule.voice.alternativeSecondPercent)
                        ? rule.voice.alternativeSecond : rule.voice.alternativeFirst;
            }
            break;
        case MoveOp::ActionCamera:
            // `second` marks a camera the move plays regardless of contact: the Hyper
            // EX attack (row 350) shows its cinematic on a whiff too, which is what the
            // owner's original-runtime screenshot shows. Everything else stays a hit
            // effect, as the melee chain is.
            if (m_chainContact || rule.second > 0.f)
                m_actionCamera = static_cast<int>(rule.value);
            break;
        // The attack bodies' vertical channel: value is the bodies' per-tick unit,
        // converted once here (u/tick -> u/s), matching the horizontal channel's
        // per-tick m_moveSpeed convention.
        case MoveOp::Vertical:
            // A nonzero impulse leaves the ground the way try_jump does: the
            // vertical block only integrates while airborne, so arming the
            // velocity without clearing the grounded flag would never lift.
            m_vy = rule.value * 64.f;
            if (rule.value != 0.f) m_grounded = false;
            break;
        case MoveOp::Gravity: m_attackGravity = rule.value; break;
        case MoveOp::PhaseExit:
            enter_phase(static_cast<int>(rule.value));
            return;
        case MoveOp::ContactExit:
            // The dive family's rebound: only a connected hit inside the window
            // switches the row (the original's in.contact branch).
            if (m_chainContact) {
                switch_attack_row(static_cast<int>(rule.value));
                return;
            }
            break;
        case MoveOp::JumpCancel:
            // FUN_0043ffc0's 310 tail: a connected hit past the window with jump
            // held leaves the kick into the air chain (next_state 40).
            if (m_chainContact && input && input->down[input::Action::Jump]) {
                try_jump();
                return;
            }
            break;
        case MoveOp::ClockSkip: m_clockSkip = static_cast<int>(rule.value); break;
        case MoveOp::Gauge:
            // The dash-recovery refill: gauge thousandths per tick, clamped by
            // set_hyper_gauge's 0..1 range (the original's min(1000, +40)).
            set_hyper_gauge(m_gauge + rule.value / 1000.f);
            break;
        case MoveOp::Recharge: {
            // FUN_00637950 writes actor status slot 6 at +0x7f4 when a hit record's
            // flags2c carries 0x1000. The native move callback reads it before the later
            // FUN_0042e110 decrement; generic producer is implemented, but scanned Rena
            // actor/projectile DATs do not establish natural slot-6 reachability.
            const int refill = m_hitStatusDuration[6] > 0 ? 5 : static_cast<int>(rule.value);
            // The refill lands on the unified word on the pilot path, the legacy
            // counter otherwise; the rule (+40/+5, clamp 1000) is the same.
            if (m_pilotMeter) m_actionMeter = std::min(1000, m_actionMeter + refill);
            else m_chargeGauge = std::min(1000, m_chargeGauge + refill);
            break;
        }
        case MoveOp::MeleeVoice: {
            // FUN_004223d0/FUN_00422490 with the melee event ids. The 422490 choice
            // draw reproduces the 32-family's `rand%100 < percent` pair exactly.
            //
            // The close-target cascade (voices 0/15/5 at priority 12) resolves first:
            // the bodies nest the same test three deep inside their distance and
            // bearing gate — `dist^2 < G && |+0x19| < 30` then +0xaec3 / +0xaebe /
            // +0xaeb9, else the ordinary id. `rule.second` carries G, and the bearing
            // term is absent here because the port does not carry the battle offset
            // (the producer records that), so the distance arm alone decides. The
            // producer latches come from the shooting context's voice flags, which the
            // match fills from FUN_0042e110's own reading before the fighter updates.
            // The addattack arm is unreachable through an attack row at all: it needs a
            // reaction state, and `can_act` refuses to admit one. The backattack arm is
            // unreachable at the rows this port binds for the mirror reason: its latch is
            // the SAME condition minus FUN_0042e950's attack-state test, and the cascade
            // always runs inside the attack row, so the previous tick's state is that
            // row and the intercept arm outranks it. Both stay in the nest anyway — they
            // are the source's order, and a row bound later at its entry tick would need
            // them — but the reachable pair here is intercept-vs-ordinary.
            int event = static_cast<int>(rule.value);
            if (rule.second > 0.f && distanceSquared < rule.second) {
                const auto& cascade = m_shooting.voice;
                if (cascade.addAttack())        event = 0;   // addattack
                else if (cascade.intercept())   event = 15;  // intercept
                else if (cascade.backAttack())  event = 5;   // backattack
            }
            int alternative = -1;
            if (rule.voice.alternativeFirst >= 0 && rule.voice.alternativeSecond >= 0) {
                alternative = rng_source().modulo(100) <
                                      static_cast<std::uint32_t>(
                                          rule.voice.alternativeSecondPercent)
                                  ? rule.voice.alternativeSecond
                                  : rule.voice.alternativeFirst;
            } else if (rule.voice.alternativeFirst >= 0) {
                alternative = rule.voice.alternativeFirst;  // the fixed 422490 choice
            }
            m_meleeVoice = {event, alternative};
            break;
        }
        case MoveOp::SoundEffect:
            // FUN_0042c8b0's flag=1 is the positional SE request at actor +0x14;
            // FUN_0042c880's flag=0 has no position. Capture the source where the body
            // makes the call, before Fighter::update integrates this tick's movement.
            m_pendingSoundEffect = {static_cast<int>(rule.value), rule.soundPositional,
                                    m_position};
            break;
        case MoveOp::ContactReset:
            // FUN_0042c800(0) + FUN_0042c840(1): clear the per-victim markers and allow one hit
            // each, which the row calls on every tick of its flurry window. The port's model of
            // that registry is the per-swing hit set, so clearing it is the equivalent.
            m_swingHits = 0;
            break;
        case MoveOp::Effect:
            // The actor's effect request (`(*actor+0xc)` -> FUN_00421aa0 ->
            // FUN_00435990): the id indexes data/effect by `id / 10`, and the heading and
            // pitch are the request's own pose. The jittered beats draw yaw then pitch
            // first — two rand%40-20 per emission (FUN_0043ffc0 case 0x15e @0x15e-0x16a)
            // — so the draw consumption matches the body.
            m_pendingEffect = {static_cast<int>(rule.value), 0.f, 0.f};
            if (rule.third > 0.f) {
                m_pendingEffect.yaw = static_cast<float>(
                    static_cast<int>(rng_source().modulo(40)) - 20);
                m_pendingEffect.pitch = static_cast<float>(
                    static_cast<int>(rng_source().modulo(40)) - 20);
            }
            break;
        case MoveOp::ClockSeek:
            // Rena+2's clock jumps (the 350/360 42->95 jump, FUN_00438310 cases
            // 0x15e/0x168): the primary clock moves; the secondary clock (+0xae08,
            // the animation service's second channel) takes the same seek in the
            // original — a recorded single-clock approximation.
            m_moveElapsedTicks = static_cast<int>(rule.value);
            break;
        case MoveOp::ClockClamp:
            m_moveElapsedTicks = std::min(m_moveElapsedTicks,
                                          static_cast<int>(rule.value));
            break;
        case MoveOp::PropModel: {
            // FUN_00434a70's per-tick rebind: slot (value) carries item model
            // (second) for this move — Rena+1's 450/460 bind slot 0 to model 2, so
            // the visible weapon and the ribbon anchors follow the model-2 muzzle.
            const int slot = static_cast<int>(rule.value);
            const int model = static_cast<int>(rule.second);
            // A negative model CLEARS the slot, which is what the recovered shot body does at
            // its frame 12 (`battle_rena_ground_shot.hpp:37`: `if (frame > 11)` emits
            // `model -1` for slots 0 and 1), and what this port's own consumer already
            // implements: `itemModel < 0` resets the trail (fighter.cpp:751-755). The writer
            // previously refused negatives, so the clear could not be expressed at all —
            // measured as 0/148 on the shot scenario. No shipped row carries a negative model
            // (only Rena+1's 450/460, which bind model 2), so accepting them changes nothing
            // on the current default path.
            if (slot >= 0 && slot < 2) m_trailItemModel[size_t(slot)] = model;
            break;
        }
        case MoveOp::ScaleMotion:
            // The entry scalings: the carried speed (value) and vertical (second)
            // multiply at the window's first tick (Rena+1's 460 halves the speed;
            // Rena+2's air 360 keeps a tenth of both).
            m_moveSpeed *= rule.value;
            m_vy *= rule.second;
            break;
        case MoveOp::ContactOff:
            // The bodies' FUN_00434bd0 windows: cut the contact volume for the
            // matching ticks (reset each pass, so the posed records' own windows
            // apply everywhere else).
            m_contactDisabled = true;
            break;
        // LandExit/LandPhase/LandSeek never act inside the loop: the landing
        // branch in update() consults them when the ground is actually reached.
        case MoveOp::LandExit:
        case MoveOp::LandPhase:
        case MoveOp::LandSeek:
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

bool Fighter::rule_gate_holds(const MoveRule& rule, float distanceSquared) const {
    if (rule.gate == kGateNone) return true;
    // The AI direction (+0x278): three exclusive sign tests, so a rule states the branch
    // the body took rather than encoding it in a value.
    if ((rule.gate & kGateDirLeft) != 0 && !(m_shooting.moveLateral < 0)) return false;
    if ((rule.gate & kGateDirNeutral) != 0 && !(m_shooting.moveLateral == 0)) return false;
    if ((rule.gate & kGateDirRight) != 0 && !(m_shooting.moveLateral > 0)) return false;
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
    // Squared-distance gates: -1 (no opponent context) fails both, so a gated
    // rule simply never fires without a target rather than guessing.
    if ((rule.gate & kGateNear) != 0 &&
        !(distanceSquared >= 0.f && distanceSquared < static_cast<float>(rule.gateValue)))
        return false;
    if ((rule.gate & kGateFar) != 0 &&
        !(distanceSquared >= 0.f && distanceSquared >= static_cast<float>(rule.gateValue)))
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
            if (spread.lateralModulus <= 0 && spread.lateralPerTick == 0.f) break;
            // A zero modulus draws nothing, which is what a counter-only sweep needs.
            int draw = 0;
            if (spread.lateralModulus > 0)
                draw = static_cast<int>(rng_source().modulo(
                    static_cast<std::uint32_t>(spread.lateralModulus)));
            // This is a YAW OFFSET, not a position. FUN_00435220's third argument (and
            // FUN_00435000's) is added to the bone's own angles and run through the sin/cos
            // table — FUN_00435250 does exactly that at 0x4352a0 — so a "lateral" value in a
            // hand or attachment request swings the shot, it does not slide the muzzle. Only
            // FUN_00435450's world form takes a perpendicular POSITION, and those families
            // state it per rule through origin_actor_relative instead.
            resolvedAim.yawDegrees +=
                static_cast<float>(m_moveCounter) * spread.lateralPerTick +
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
        const int model = resolvedOrigin.itemModel >= 0 ? resolvedOrigin.itemModel : slot;
        if (resolvedOrigin.itemModel >= m_weapon->slotCount)
            throw std::out_of_range("projectile item model");
        const bool hasAttachment = weapon_slot_bound(slot) && model < m_weapon->slotCount;
        const glm::vec3 offset = (hasAttachment
            ? glm::vec3(m_weapon->slots[model].muzzle[0], m_weapon->slots[model].muzzle[1],
                        m_weapon->slots[model].muzzle[2])
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
            rangeTerm = std::clamp(horizontal * 40.f / resolvedAim.rangeDivisor,
                                   resolvedAim.rangeMinimum, resolvedAim.rangeMaximum);
            if (base < 0.f) rangeTerm *= resolvedAim.rangeNegativeScale;
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

void Fighter::switch_attack_row(int moveId) {
    // FUN_00421080's row switch: a fresh phase cursor and clip, a fresh swing with
    // per-victim accounting, and the contact volume re-armed. The air fields
    // (m_attackGravity — the original's +58) carry across the switch, matching the
    // persistent scratch the original reads in the landing bodies; the lean pair
    // clears because every recovered transition that switches rows zeroes the pitch.
    // The active channel decides which row id moves: FUN_00421080 is the same call
    // for melee and shot states, and a shot state's row lives in m_shotMoveId.
    if (m_shotMoveId >= 0) m_shotMoveId = moveId;
    else m_attackMoveId = moveId;
    build_melee_swing(moveId);
    begin_melee_swing();
    m_phaseIndex = 0;
    m_moveElapsedTicks = 0;
    m_animSetIdx = -1;
    m_contactDisabled = false;
    m_bodyPitch = 0.f;
    m_bodyPivotHeight = 0.f;
    try_switch_animation();
}

void Fighter::turn_toward(const Fighter* opponent, float degrees) {
    if (!opponent) return;
    // The Back-held aerial attack keeps the actor's visible yaw (the same contract
    // the Turn op enforces): the movement basis is not re-aimed at the target while
    // that rule owns the fighter.
    if (m_state == FighterState::AttackA && m_aerialAttack && m_attackUsesActorFacing)
        return;
    const glm::vec3 offset = opponent->position() - m_position;
    const float target = std::atan2(offset.x, offset.z);
    const float difference = std::remainder(target - m_facing, glm::two_pi<float>());
    const float rate = glm::radians(degrees);
    m_facing += std::clamp(difference, -rate, rate);
}

void Fighter::advance_rena_chase(const ChasePolicy& policy, Fighter* opponent) {
    // FUN_0043ffc0/448220/438310 case 0x140 (chasing air melee, character 0) read
    // through the Ginkiha reference: while strength holds the body steers its own
    // flight angle toward the target bearing each tick (speed/vertical re-derived
    // from the angle and the decaying strength), phase 1 hands to phase 2 near the
    // target or past the timeout, then gravity runs and the landing exits into the
    // 329 recovery (the LandExit rule carries that window). The original's trig
    // table (FUN_0065d010, 0.1-degree steps) is replaced with exact trig — a
    // labeled delta under the tick budget. The 180-degree entry snap is the port's
    // attack-entry facing rule, not repeated here.
    const glm::vec3 offset = opponent ? opponent->position() - m_position : glm::vec3(0.f);
    const double distance2 = static_cast<double>(glm::dot(offset, offset));
    const float height = offset.y;
    const auto flightAngle = [&]() {
        return glm::degrees(std::atan2(m_vy / 64.f, m_moveSpeed));
    };
    const bool first = m_phaseIndex == 0 && m_moveElapsedTicks == 0;
    if (first) {
        // air.vertical clamp and the strength latch at entry; zero gravity until
        // the phase-2 window (the Gravity rules carry those).
        m_vy = std::clamp(m_vy, policy.minimumVertical * 64.f, policy.maximumVertical * 64.f);
        m_moveSpeed = policy.initialSpeed;
        m_chaseStrength = distance2 < policy.initialDistance2 ? policy.initialStrength : 0;
        m_bodyPitch = flightAngle() + policy.pitchBias;
        m_bodyPivotHeight = 70.f;
    }
    if (m_phaseIndex < 2 && m_chaseStrength > 0) {
        const float targetAngle = glm::degrees(std::atan2(
            static_cast<double>(height), std::sqrt(std::max(0.0, distance2)))) + 10.f;
        float current = first ? targetAngle : flightAngle();
        if (current > targetAngle) current = std::max(targetAngle, current - 5.f);
        if (current < targetAngle) current = std::min(targetAngle, current + 5.f);
        current = std::clamp(current, policy.minimumAngle, policy.maximumAngle);
        const float magnitude = static_cast<float>(m_chaseStrength) * .1f;
        m_moveSpeed = std::cos(glm::radians(current)) * magnitude;
        m_vy = std::sin(glm::radians(current)) * magnitude * 64.f;
        m_bodyPitch = flightAngle() + policy.pitchBias;
        m_bodyPivotHeight = 70.f;
        turn_toward(opponent, policy.turnStep);
        m_chaseStrength = std::max(policy.minimumStrength, m_chaseStrength - policy.strengthDecay);
    }
    if (m_phaseIndex == 1) {
        // The phase-1 approach runs on top of the steering turn (chasing_air_melee
        // applies both), then the exit: close enough, timed out, or out of strength.
        turn_toward(opponent, 2.f);
        if (m_moveElapsedTicks > policy.approachAfter &&
            (distance2 + static_cast<double>(height) * height < policy.attackDistance2 ||
             m_moveElapsedTicks > policy.approachTimeout || m_chaseStrength == 0)) {
            enter_phase(2);
            return;
        }
    }
    if (m_phaseIndex == 2) {
        // FUN_00438310:953-955 seeks BOTH clocks from 13 to 22 before the remaining
        // phase-2 work. Keep this seek here, before rule evaluation, so cues, contact
        // and animation all sample the same clock. Pitch recovers 5 a tick past 25.
        if (policy.skipAttackFrames && m_moveElapsedTicks == 13) m_moveElapsedTicks = 22;
        if (m_moveElapsedTicks > 25) {
            m_bodyPitch = m_bodyPitch > 0.f ? std::max(0.f, m_bodyPitch - 5.f)
                                        : std::min(0.f, m_bodyPitch + 5.f);
        }
    }
}

void Fighter::advance_rena_dive(const DivePolicy& policy, Fighter* opponent) {
    // FUN_0043ffc0 case 0x14c (keiichi_dive, character 0 — the same body serves
    // weapons 0/1) and the 334 followup tail read through the Ginkiha reference.
    // The dash transition's grounded exit to 333 and the completion exit ride the
    // port's landing (LandExit rules) and period paths; this body owns the launch
    // arc, the contact rebound and the pre-landing fall.
    const glm::vec3 offset = opponent ? opponent->position() - m_position : glm::vec3(0.f);
    if (state_move_id() == 334) {
        // 334: rise until vertical < 6 u/tick hands to phase 1; the fall itself is
        // the carried gravity (the contact exit set .35) through the vertical block;
        // the landing exits into 333 through the LandExit rule.
        if (m_phaseIndex == 0 && m_vy < 6.f * 64.f) {
            enter_phase(1);
            return;
        }
        return;
    }
    // 332 dive.
    if (m_phaseIndex == 0) {
        turn_toward(opponent, 5.f);
        if (m_moveElapsedTicks == 0) {
            m_moveSpeed = 0.f;
            m_vy = 0.f;
        }
    }
    if (m_phaseIndex == 1) {
        // The signed-offset approach: one degree toward the battle basis while the
        // movement offset sits under 90 (the original tests the signed offset, not
        // its magnitude).
        if (opponent) {
            const float basis = std::atan2(offset.x, offset.z);
            const float movementOffset =
                glm::degrees(std::remainder(m_facing - basis, glm::two_pi<float>()));
            if (movementOffset < 90.f) turn_toward(opponent, 1.f);
        }
        if (m_moveElapsedTicks == 0) {
            // Launch: the dive angle is the target elevation clamped into [-20,-5]
            // degrees; speed/vertical split along it; the lean is the flight angle
            // plus ten, floored at zero.
            const float elevation = glm::degrees(std::atan2(
                static_cast<double>(offset.y),
                static_cast<double>(std::hypot(offset.x, offset.z))));
            const float angle = std::clamp(elevation, policy.minimumAngle, policy.maximumAngle);
            m_moveSpeed = std::cos(glm::radians(angle)) * policy.launchSpeed;
            m_vy = std::sin(glm::radians(angle)) * policy.launchSpeed * 64.f;
            m_bodyPitch = std::min(
                0.f, glm::degrees(std::atan2(m_vy / 64.f, m_moveSpeed)) + 10.f);
            m_bodyPivotHeight = 70.f;
        }
        if (m_chainContact) {
            // Contact rebound into 334: pitch cleared, vertical 10 up, speed -7
            // back, gravity .35 carried, contact cleared for the follow-up.
            m_bodyPitch = 0.f;
            m_vy = policy.contactVertical * 64.f;
            m_moveSpeed = policy.contactSpeed;
            m_attackGravity = policy.contactGravity;
            m_chainContact = false;
            switch_attack_row(policy.contactExitState);
            return;
        }
        m_contactDisabled = m_moveElapsedTicks > policy.disableContactAfter;
        if (m_moveElapsedTicks > policy.phaseExitFrame) {
            m_moveSpeed = 10.f;
            enter_phase(2);
            return;
        }
    }
    if (m_phaseIndex == 2 || (m_phaseIndex == 1 && m_moveElapsedTicks > policy.disableContactAfter)) {
        // The fall: gravity .5 from the first fall tick (the Gravity rules carry
        // the window), the pitch recovers 5 a tick in phase 2 only.
        if (m_phaseIndex == 2) {
            m_bodyPitch = m_bodyPitch > 0.f ? std::max(0.f, m_bodyPitch - 5.f)
                                        : std::min(0.f, m_bodyPitch + 5.f);
        }
        if (m_attackGravity < 0.f) m_attackGravity = .5f;
        m_moveSpeed = std::max(0.f, m_moveSpeed);
    }
}

void Fighter::advance_rena1_dive_shot(Fighter* opponent) {
    // FUN_00448220 case 0x192, phase 1 tick 0 — the dive launch. The vertical is a
    // fixed -40 u/tick (0xc2200000); the horizontal closing speed is the target's own
    // geometry: (horizontal distance + 1) * -40 / height difference (FUN_0042d980's
    // squared-distance sum, FUN_0042de80's sqrt, FUN_0042da30's target-minus-self
    // height), clamped into [0, 10] — a steeper approach dives more vertically, and a
    // target at or above the attacker clamps to a pure drop. No gravity is applied by
    // the body (the original never integrates +0x16 here), so the dive is a
    // constant-velocity drop until the row's landing or completion.
    if (m_phaseIndex != 1 || m_moveElapsedTicks != 0) return;
    m_vy = -40.f * 64.f;
    float horizontal = 0.f;
    if (opponent) {
        const glm::vec3 offset = opponent->position() - m_position;
        const float distance = std::sqrt(std::max(0.f, offset.x * offset.x +
                                                        offset.z * offset.z));
        const float height = offset.y;
        if (height < 0.f) horizontal = (distance + 1.f) * -40.f / height;
    }
    m_moveSpeed = std::clamp(horizontal, 0.f, 10.f);
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
    // The volume's own horizontal reach: the farthest point of the anchor (and of the end
    // anchor when the record is a capsule) from this fighter's centre, under the record's
    // bone at the current pose. A body-part sphere sits close to the body; a swept blade
    // reaches a blade length past it. Radii are added by the caller's gate.
    {
        const auto horizontal = [&](const glm::vec3& point) {
            const float dx = point.x - m_position.x;
            const float dz = point.z - m_position.z;
            return std::sqrt(dx * dx + dz * dz);
        };
        const glm::vec3 start =
            bone_point(hit->boneName, glm::vec3(hit->anchor[0], hit->anchor[1], hit->anchor[2]));
        float extent = horizontal(start);
        if (hit->collisionShape != 0) {
            const glm::vec3 end = bone_point(hit->boneName, glm::vec3(hit->endAnchor[0],
                                                                      hit->endAnchor[1],
                                                                      hit->endAnchor[2]));
            extent = std::max(extent, horizontal(end));
        }
        swing.reach = extent + static_cast<float>(hit->hitRadius) + m_meleeRules.bodyRadius;
        swing.reachKnown = true;
    }
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
            // FUN_0063dad0:242 transforms FUN_00423750(0xc1c80000,0,0) = (-25,0,0) by the
            // Spine frame. The recovered literal is the rules' chestAnchorOffset.
            const float spineX = m_meleeRules.chestAnchorOffset;
            const int f = m_model->findFrame("Bip01_Spine");
            if (f >= 0 && m_anim) return bone_point("Bip01_Spine", glm::vec3(spineX,0.f,0.f)) - m_position;
            if (f >= 0) return glm::vec3(bindWorld(m_model, f) * glm::vec4(spineX, 0.f, 0.f, 1.f));
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
    // FUN_004219a0's battle-init block: the fighter-level shot gauge returns to
    // 1000 with the magazines at every respawn/round reset. The unified meter resets
    // with it so a stale value cannot leak across a round.
    m_chargeGauge = 1000;
    m_actionMeter = 1000;
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
    // No launch spend on the pilot path: none of the jump bodies charges one. Row 41
    // spends -10 (-4/-6/-12 by combo) only while gravity reads zero — the hover
    // states — and rows 40/44 refill instead (see the per-tick rules below). The
    // legacy path keeps its explicit per-leap trigger cost.
    if (!m_pilotMeter) m_stamina = std::max(0.0f, m_stamina - FighterConstants::kJumpStamina);
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
    // This IS the recovered `0 < +0x834` dash gate: on the pilot path the unified
    // meter answers it (the recovered 12/tick drain is meter -12, and the body's
    // phase-1 exit at `+0x834 < 1` is `meter <= 0` in the Run update above). The
    // default path keeps the legacy stamina gate and flat trigger spend.
    if (m_pilotMeter) {
        if (m_actionMeter <= 0) return false;
    } else if (programmed ? m_stamina <= 0.f : m_stamina < FighterConstants::kDashStamina) {
        return false;
    }
    if (!m_grounded && m_airDashed) return false;
    m_dashInputDirection = dir;
    const bool backwardAirDash = !m_grounded && dir == input::Action::Down;

    // Directional dash controls use the live lock bearing, not the body's last
    // walk heading. The original keeps this basis separate from the body yaw
    // (FUN_004202b0 / FUN_0042dd90); forward move 20 still owns its recovered
    // phase turn/steer window below.
    glm::vec3 d(0, 0, 0);
    if (dir == input::Action::Up)         d = target_relative(0.0f, 1.0f);
    else if (dir == input::Action::Down)  d = target_relative(0.0f, -1.0f);
    else if (dir == input::Action::Right) d = target_relative(1.0f, 0.0f);
    else                                  d = target_relative(-1.0f, 0.0f);

    // The user-requested backward air-dash attack follows the actor's visible
    // facing. Preserve that pose while its committed movement stays lock-relative;
    // ground side/back clips have no turn callback and snap to the lock here.
    // Forward move 20 keeps its recovered phase-0 snap and phase-1 steering.
    if (!programmed && !backwardAirDash) m_facing = m_inputFacing;

    // No flat trigger spend on the pilot path: the recovered dash costs per-tick
    // drain only. The legacy path keeps its explicit twenty-percent spend.
    if (!programmed && !m_pilotMeter) m_stamina -= FighterConstants::kDashStamina;
    m_dashDir = d;
    // Only the pilot's grounded side steps re-derive their direction per tick; every other
    // dash keeps the world vector its arm resolved. Row 23 is the Right step, 24 the Left.
    m_dashSide = 0;
    if (m_pilotMeter && m_grounded && (dashMove == 23 || dashMove == 24))
        m_dashSide = dashMove == 23 ? 1 : -1;
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
        // FUN_0043ffc0 case 0x1e :407 writes +0x15 = 0x41840000 = 16.5/tick, and :408
        // puts the movement angle +0x18 at 0 — i.e. along the actor's own angle, which
        // FUN_00421780 then steers toward the held input's compass bearing. So an air dash
        // points where it was input rather than at the target (owner: D3).
        m_dashSpeed = FighterConstants::kAirDashSpeed;
        m_airDashTicks = 0;
        if (m_pilotMeter) {
            m_dashSpeed = 16.5f * 60.0f;
            if (m_inputAxisX != 0 || m_inputAxisZ != 0) {
                const glm::vec3 wanted = relative_direction(
                    m_inputFacing, static_cast<float>(m_inputAxisX),
                    static_cast<float>(m_inputAxisZ));
                d = wanted;
                m_facing = std::atan2(wanted.x, wanted.z);
            }
            m_airDashCarry = true;
        }
    } else {
        m_dashSpeed = FighterConstants::kRunSpeed;
    }
    const bool wasRunning = m_state == FighterState::Run;
    set_state(FighterState::Run);
    // A second dash can replace its candidate without changing the port state.
    // set_state() intentionally early-outs for identical labels, so rebind after
    // the candidate reset above instead of leaving the previous clip active.
    if (wasRunning && m_animSetIdx < 0) try_switch_animation();
    // A dash whose row is recovered and multi-section must be PHASE-driven, not cut by
    // a fixed frame count. `programmed` covers only the forward dash (move 20), so the
    // side steps (23/24) and the back dash (27) were ending on kDashFrames = 20 before
    // their last section: a side row is 7/12/24 ticks across three phases, and 8+11 left
    // it inside phase 1 — which is why neither side step ever played its recovery clip
    // (row 23 phase 2 = set 24, row 24 phase 2 = set 21). The phase clock now ends the
    // dash through advance_animation_phase's last-section branch instead.
    const CharacterMove* dashRow = m_moves ? m_moves->find(dashMove) : nullptr;
    // PILOT PATH ONLY: the COM drives the same fighter class, and its cadence (and the bot
    // suite's expectations) were built on the truncated dash, so the recovered full-length
    // dash applies where the recovered rules already apply. Airborne too: row 30's three
    // sections are 10/15/10 updates, and the 20-update kDashFrames timer cut the air dash
    // inside phase 1 — its recovery phase, which is where the body starts to descend
    // (case 0x1e :422-424), never ran at all.
    const bool phaseDriven =
        programmed || (m_pilotMeter && dashRow && dashRow->sectionCount > 1);
    m_stateTimer = phaseDriven ? 0 : FighterConstants::kDashFrames;
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
    if (!can_fire(tier)) {
        // The recovered release branch services an empty tap without a state: one voice and the
        // empty-shot statistic, inside the wrapper whose `+0x834 < 1` term excludes the ordinary
        // shot admission (slot7_native_bodies_20260929.hpp:172-182; PILOT-SEAM.md §26). It also
        // requires the body's release count `0 < released < 20`, so a longer hold asks for
        // nothing. The port reaches no voice at all because it returns here, so the pilot
        // answers the voice half on the per-tick cue the host already drains. The statistic has
        // no port owner and is not invented as a Fighter field.
        if (tier == ShotTier::Tap && m_pilotShot && m_moves &&
            attack_admission_recovered(m_moves->character_index()) &&
            m_chargeHeldTicks > 0 && m_chargeHeldTicks < kChargeHoldTickCap) {
            const int voice = m_pilotShot->empty_shot_voice();
            if (voice >= 0) m_shootingVoice.event = voice;
        }
        return;
    }
    // The fighter-level shot gauge (+0x834) gates the tap admission in the
    // recovered selector (FUN_00445ee0: `0 < +0x834` on the 40x branches); the
    // recovery states refill it. Scoped to the recovered group so other combos
    // keep their previous admission behavior. On the pilot path the unified meter
    // answers; the default path reads the legacy counter.
    if (tier == ShotTier::Tap && m_moves &&
        attack_admission_recovered(m_moves->character_index()) &&
        (m_pilotMeter ? m_actionMeter : m_chargeGauge) <= 0)
        return;
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
    int programmed =
        (program && tier != ShotTier::Ex)
            ? program->shot[static_cast<size_t>(tier)][m_grounded ? 0 : 1]
            : -1;
    // Recovered tap routing (Rena group, FUN_00445ee0's slot-7 branches): the
    // situation at release selects the shot state — the walking/dash shots
    // 401/405/406/407 for the weapons whose handlers request them, and the
    // air-dash fast shot 408 — in place of the program's own 400/402 entry.
    // Only a state the program can actually fire (its own entry or its rules)
    // is selected, so no clip is ever bound without its launch body.
    // Rena's routing only: Mion's dispatchers route the walking tap to her own mobile
    // states (401/410/411/412 for weapons 0/1), which the port has not bound yet — that
    // is a shooting-side pending item, not something this block may guess from Rena's.
    if (tier == ShotTier::Tap && program && m_moves && m_weapon &&
        m_moves->character_index() == 0) {
        const int slot = weaponSlotForItem(m_moves->character_index(), m_weapon->id);
        int admitted = -1;
        if (m_grounded) {
            admitted = rena_tap_shot_state(slot, numeric_state(), true);
            if (admitted != 400 && !present_move(admitted)) admitted = 400;
        } else if (rena_air_dash_fast_shot(
                       slot, numeric_state(), m_phaseIndex,
                       m_inputAxisX != 0 || m_inputAxisZ != 0) &&
                   present_move(408)) {
            admitted = 408;
        }
        if (admitted >= 0 && admitted != programmed) {
            bool covered = false;
            for (size_t i = 0; i < program->count; ++i)
                if (program->rules[i].move == admitted) { covered = true; break; }
            if (covered) programmed = admitted;
        }
    }
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
    // The chase/dive lean is the original's field sum, in the original's own slots:
    // FUN_00420b30's unattached-actor branch builds T(0,-pivot,0) * Rx(pitch) *
    // Ry(-(heading+90+offset+extra)) * T(position + pivot), where +0x2c is the PITCH
    // (RotationX, degrees) and +0x2d8 the pivot HEIGHT the model turns about. The
    // earlier cut summed pitch+pivot into the Y angle, which is neither. The donor's
    // transcription (actor_world_pose.hpp:14) agrees with the handler. glm point-map
    // equivalence: the donor's tilt matrix maps (y,z) -> (c*y - s*z, s*y + c*z),
    // bit-for-bit glm::rotate(+X), so the pitch sign carries over unchanged; the yaw
    // sum is the negated one that m_facing + pi already encodes for the -Z rig (see
    // the half-turn note above), so a recovered yaw offset (+0x64/+0x30) would
    // subtract — neither is modeled, so neither appears.
    const float pivot = m_bodyPivotHeight;
    return glm::translate(glm::mat4(1.0f), m_position + glm::vec3(0.0f, pivot, 0.0f)) *
           glm::rotate(glm::mat4(1.0f), m_facing + glm::pi<float>(),
                       glm::vec3(0.0f, 1.0f, 0.0f)) *
           glm::rotate(glm::mat4(1.0f), glm::radians(m_bodyPitch),
                       glm::vec3(1.0f, 0.0f, 0.0f)) *
           glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -pivot, 0.0f));
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
