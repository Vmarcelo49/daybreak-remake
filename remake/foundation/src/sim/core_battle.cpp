#include "sim/core_battle.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <stdexcept>

#include "input/input.h"

namespace gameplay { namespace input = fnd::input; }
#include "gameplay/held_axis.h"

namespace sim {

namespace {

// FUN_0041fb09's frame-to-seconds constant (actor_track_time.hpp).
constexpr float kOriginalAnimationTick = 0.016000000759959221f;

glm::mat4 to_glm(const Matrix& m) {
    glm::mat4 out;
    std::memcpy(&out[0][0], m.data(), sizeof(float) * 16);
    return out;
}

float fraction(const MagazineState& magazine) {
    return magazine.capacity > 0 ? static_cast<float>(magazine.rounds) / static_cast<float>(magazine.capacity) : 0.f;
}

SlotInput slot_input(const fnd::input::PlayerState& state) {
    using fnd::input::Action;
    SlotInput out;
    out.x = gameplay::held_axis_x(&state);
    out.z = -gameplay::held_axis_z(&state);  // the core's z is down minus up
    if (state.down[Action::Jump]) out.buttons |= Jump;
    if (state.down[Action::AttackA]) out.buttons |= Melee;
    if (state.down[Action::Shoot]) out.buttons |= Shoot;
    if (state.down[Action::LockSwitch]) out.buttons |= Target;
    if (state.down[Action::Guard]) out.buttons |= Guard;
    // The port's Special key is the original's melee + shot chord (FUN_0063c2a0 case 0x24).
    if (state.down[Action::Special]) out.buttons |= Melee | Shoot;
    return out;
}

}  // namespace

game::FighterState fighter_state_for_row(unsigned row) {
    using game::FighterState;
    if (row >= 10 && row <= 12) return FighterState::Walk;
    if (row >= 20 && row <= 30) return FighterState::Run;
    if (row >= 40 && row <= 45) return FighterState::Jump;
    if (row >= 118 && row <= 129) return FighterState::Knockdown;
    if ((row >= 190 && row <= 199)) return FighterState::KO;
    if (row >= 100 && row < 300) return FighterState::Hit;
    if (row >= 390 && row <= 394) return FighterState::Guard;
    if (row >= 300 && row < 400) return FighterState::AttackA;
    if (row >= 400 && row < 500) return FighterState::ShootA;
    return FighterState::Idle;
}

void CoreFighter::bind(const Battle* battle, unsigned slot, const gameplay::CharacterMoves* moves,
                       const gameplay::WeaponDefinition* weapon) {
    m_battle = battle;
    m_slot = slot;
    m_moves = moves;
    m_weapon = weapon;
    refresh();
}

void CoreFighter::refresh() {
    const ActorState actor = m_battle->actor(m_slot);
    m_position = glm::vec3(actor.position[0], actor.position[1], actor.position[2]);
    m_world = to_glm(m_battle->actor_world(m_slot));
    // The authored rig faces -Z (FUN_00420b30), and the port's yaw has forward = (sin, 0, cos).
    const glm::vec3 forward = -glm::vec3(m_world[2]);
    m_yaw = std::atan2(forward.x, forward.z);
    m_row = static_cast<int>(actor.state);
    m_frame = static_cast<int>(actor.frame);
    m_state = fighter_state_for_row(actor.state);
    m_hp = actor.hp / 100;  // the core's scale is 10000; the product's HUD reads percent
    m_gauge = actor.gauge;
    m_held = m_battle->held_models(m_slot);
    m_magazines = m_battle->magazines(m_slot);
    m_animation = m_battle->animation(m_slot);
    m_special = m_battle->special(m_slot);
    // The product's stats read on its 100-per-fighter HP scale.
    const ActorTotals totals = m_battle->totals(m_slot);
    m_stats = {totals.kills, totals.deaths, totals.damageDealt / 100, totals.damageTaken / 100};
    refresh_trails();
}

// Anchors 3..5 and 6..8 of the held slot are the ribbon's two endpoints (FUN_00430120).
void CoreFighter::refresh_trails() {
    for (unsigned hand = 0; hand < 2; ++hand) {
        const HandTrail source = m_battle->hand_trail(m_slot, hand);
        gameplay::WeaponTrail& trail = m_trails[hand];
        m_trailModels[hand] = source.model;
        if (!m_weapon || !source.hasBone || source.model < 0 || source.model >= m_weapon->slotCount ||
            !m_weapon->slots[source.model].has_prop()) {
            trail.reset();
            continue;
        }
        const auto& slot = m_weapon->slots[source.model];
        const glm::mat4 bone = to_glm(source.boneWorld);
        const auto point = [&](const auto& p) { return glm::vec3(bone * glm::vec4(p[0], p[1], p[2], 1.f)); };
        trail.step(source.active, point(slot.ribbonRoot), point(slot.ribbonTip));
    }
}

game::Hypermode CoreFighter::hypermode() const {
    switch (m_special.mode & 255u) {
        case 0: return game::Hypermode::Oyashiro;
        case 2: return game::Hypermode::Kakera;
        default: return game::Hypermode::Friendship;
    }
}

float CoreFighter::hyper_gauge() const {
    return m_special.limit > 0 ? std::min(1.f, static_cast<float>(m_special.charge) / static_cast<float>(m_special.limit)) : 0.f;
}

game::FighterPose CoreFighter::pose() const {
    game::FighterPose out;
    out.position = m_position;
    out.facingYaw = m_yaw;
    out.alive = is_alive();
    return out;
}

float CoreFighter::main_frac() const { return fraction(m_magazines[0]); }
float CoreFighter::charge_frac() const { return fraction(m_magazines[1]); }

bool CoreFighter::core_pose(std::vector<glm::mat4>& worldOut) const {
    m_battle->bone_poses(m_slot, m_boneNames, m_bones);
    // Bone 0 is the core's implicit root, so frame i is bone i+1 (sim_pose_test pins this).
    if (m_bones.size() != worldOut.size() + 1) throw std::runtime_error("sim: core skeleton does not match the rig");
    for (size_t i = 0; i < worldOut.size(); ++i) worldOut[i] = to_glm(m_bones[i + 1]);
    return true;
}

void CoreBattle::start(const BattleConfig& config, const std::array<const gameplay::CharacterMoves*, 4>& moves,
                       const std::array<const gameplay::WeaponDefinition*, 4>& weapons) {
    m_battle = std::make_unique<sim::Battle>(config);
    for (unsigned i = 0; i < 4; ++i) m_fighters[i].bind(m_battle.get(), i, moves[i], weapons[i]);
    m_paused = false;
    m_roundReported = false;
    m_economy.reset();
}

game::BattleFrame CoreBattle::step(const fnd::input::PlayerState* inputs[game::kMatchFighterCount], double) {
    game::BattleFrame frame;
    if (m_paused || !m_battle) return frame;
    Inputs next{};
    for (unsigned i = 0; i < 4; ++i)
        if (inputs[i]) next[i] = slot_input(*inputs[i]);
    m_battle->step(next);
    for (CoreFighter& fighter : m_fighters) fighter.refresh();

    const auto toVec = [](const std::array<float, 3>& v) { return glm::vec3(v[0], v[1], v[2]); };
    const BattleEvents& events = m_battle->events();
    for (const auto& e : events.effects) frame.effectSpawns.push_back({e.id, toVec(e.position), toVec(e.direction)});
    for (const auto& s : events.sounds) frame.soundCues.push_back({s.id, s.positional, toVec(s.position)});
    for (const auto& v : events.voices) frame.voiceCues.push_back({v.actor, v.path});

    // FUN_006358c0: one listener at the selected actor's XYZ +150Y.
    const CoreFighter& listener = m_fighters[static_cast<size_t>(m_listener)];
    frame.audioListenerPosition = listener.position() + glm::vec3(0.f, 150.f, 0.f);
    frame.audioListenerForward = glm::vec3(std::sin(listener.facing_yaw()), 0.f, std::cos(listener.facing_yaw()));
    frame.audioListenerValid = true;

    const MatchState match = m_battle->match_state();
    const float score[2] = {match.score[0], match.score[1]};
    const float limit[2] = {match.limit[0], match.limit[1]};
    // The product leaves the battle on roundOver, so it waits for the core's own result
    // preparation (the KO presentation, then the titles) rather than the first decided tick.
    const int finishedWinner = match.awardsReady ? match.winner : -1;
    m_economy.mirror(score, limit, finishedWinner, match.timed ? match.remainingTicks / 60 : 0);
    frame.roundOver = match.awardsReady && !m_roundReported;
    frame.roundOverSide = match.winner;
    m_roundReported = match.awardsReady;
    if (match.awardsReady)
        for (size_t i = 0; i < m_fighters.size(); ++i) m_fighters[i].set_result_title(match.awards[i]);
    return frame;
}

void CoreBattle::for_each_shot(const std::function<void(const game::ShotView&)>& visit) const {
    if (!m_battle) return;
    m_battle->for_each_projectile([&](const ProjectileState& p) {
        // The product's bullet models are loaded per owner from its weapon's rows; a scene
        // effect the core spawns from another item has no card there yet.
        const auto* weapon = m_fighters[static_cast<size_t>(p.owner)].weapon();
        if (!weapon || weapon->id != p.item) return;
        game::ShotView view;
        view.owner = p.owner;
        view.bulletRow = p.row;
        view.pos = glm::vec3(p.position[0], p.position[1], p.position[2]);
        view.modelMatrix = to_glm(p.modelMatrix);
        view.billboard = p.billboard;
        view.tint = p.tint;
        view.animationSeconds = static_cast<float>(p.frame) * kOriginalAnimationTick;
        visit(view);
    });
}

}  // namespace sim
