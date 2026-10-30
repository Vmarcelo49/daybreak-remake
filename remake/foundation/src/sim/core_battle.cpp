#include "sim/core_battle.h"

#include <cmath>
#include <cstring>
#include <stdexcept>

#include "input/input.h"

namespace gameplay { namespace input = fnd::input; }
#include "gameplay/held_axis.h"

namespace sim {

namespace {

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
}

game::BattleFrame CoreBattle::step(const fnd::input::PlayerState* inputs[game::kMatchFighterCount], double) {
    game::BattleFrame frame;
    if (m_paused || !m_battle) return frame;
    Inputs next{};
    for (unsigned i = 0; i < 4; ++i)
        if (inputs[i]) next[i] = slot_input(*inputs[i]);
    m_battle->step(next);
    for (CoreFighter& fighter : m_fighters) fighter.refresh();
    return frame;
}

}  // namespace sim
