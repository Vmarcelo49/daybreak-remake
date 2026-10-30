#pragma once
// game::Battle over the vendored core (docs/DIRECTION.md).
//
// In progress: the owner's closing playtest (M4) and the switch to default (M5) remain.
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "game/battle_view.h"
#include "sim/battle.h"

namespace sim {

class CoreFighter final : public game::FighterView {
public:
    game::FighterPose pose() const override;
    const glm::vec3& position() const override { return m_position; }
    float facing_yaw() const override { return m_yaw; }
    glm::mat4 modelMatrix() const override { return m_world; }
    const gameplay::CharacterMoves* moves() const override { return m_moves; }
    const gameplay::WeaponDefinition* weapon() const override { return m_weapon; }
    game::FighterState state() const override { return m_state; }
    bool is_alive() const override { return m_alive; }
    int hp() const override { return m_hp; }
    int max_hp() const override { return 100; }
    int stamina() const override { return m_gauge / 10; }
    int charge_gauge() const override { return m_gauge; }
    const game::CombatStats& stats() const override { return m_stats; }
    int anim_set_index() const override { return m_animation.lowerSet; }
    const char* anim_set_name() const override { return nullptr; }
    bool anim_fallback() const override { return false; }
    bool anim_no_selector() const override { return false; }
    int phase_elapsed() const override { return m_frame; }
    int attack_move_id() const override { return m_row >= 300 && m_row < 400 ? m_row : -1; }
    int shot_move_id() const override { return m_row >= 400 && m_row < 500 ? m_row : -1; }
    int action_camera() const override { return m_actionCamera; }
    game::HitboxDebug hitbox_debug() const override { return {}; }
    int main_whole() const override { return m_magazines[0].rounds; }
    float main_frac() const override { return m_magazines[0].fill; }
    bool reload_ok() const override { return true; }
    int charge_whole() const override { return m_magazines[1].rounds; }
    float charge_frac() const override { return m_magazines[1].fill; }
    // The product draws one strip; the second stage shows on it once the first is full.
    float charge_hold_frac() const override { return m_magazines[1].followup > 0.f ? m_magazines[1].followup : m_magazines[1].charge; }
    game::ShotTier charge_tier() const override;
    game::ShotTier last_shot_tier() const override { return game::ShotTier::Tap; }
    game::Hypermode hypermode() const override;
    float hyper_gauge() const override { return m_special.fraction; }
    bool hyper_active() const override { return m_special.active; }
    bool hyper_ready() const override { return m_special.ready; }
    float hyper_seconds_left() const override { return static_cast<float>(m_special.ticksLeft) / 60.f; }
    int hyper_flash_alpha() const override { return m_special.flash; }
    bool hyper_activation_playing() const override { return m_special.entryRow != 0; }
    int hyper_activation_elapsed() const override { return m_special.entryFrame; }
    bool aura_active() const override { return m_special.active; }
    glm::vec3 aura_center_local() const override { return glm::vec3(0.f, 58.f, 0.f); }
    float aura_radius() const override { return 0.f; }
    game::Rgb aura_color() const override { return 0; }
    bool draws_item_model(int model) const override { return model == m_held[0] || model == m_held[1]; }
    const gameplay::WeaponTrail& trail(int hand) const override { return m_trails[static_cast<size_t>(hand)]; }
    int trail_item_model(int hand) const override { return m_trailModels[static_cast<size_t>(hand)]; }
    bool core_pose(std::vector<glm::mat4>& worldOut) const override;
    int result_title() const override { return m_title; }
    bool hp_ghost(float& percent) const override { percent = m_ghost; return true; }

    void bind(const Battle* battle, unsigned slot, const gameplay::CharacterMoves* moves,
              const gameplay::WeaponDefinition* weapon);
    void refresh();
    void set_result_title(int title) { m_title = title; }

private:
    void refresh_trails();

    const Battle* m_battle = nullptr;
    unsigned m_slot = 0;
    const gameplay::CharacterMoves* m_moves = nullptr;
    const gameplay::WeaponDefinition* m_weapon = nullptr;
    glm::vec3 m_position{0.f};
    float m_yaw = 0.f;
    glm::mat4 m_world{1.f};
    game::FighterState m_state = game::FighterState::Idle;
    int m_row = 0, m_frame = 0, m_hp = 100, m_gauge = 0, m_actionCamera = -1;
    bool m_alive = true;
    float m_ghost = 100.f;
    std::array<int, 2> m_held{{-1, -1}};
    std::array<MagazineState, 2> m_magazines{};
    ActorAnimation m_animation{};
    SpecialState m_special{};
    int m_title = -1;
    game::CombatStats m_stats{};
    std::array<gameplay::WeaponTrail, 2> m_trails{};
    std::array<int, 2> m_trailModels{{-1, -1}};
    mutable std::vector<std::string> m_boneNames;
    mutable std::vector<Matrix> m_bones;
};

// The port's labels for the core's rows, for the HUD and tools that read a coarse state.
game::FighterState fighter_state_for_row(unsigned row);

class CoreBattle final : public game::Battle {
public:
    void start(const BattleConfig& config, const std::array<const gameplay::CharacterMoves*, 4>& moves,
               const std::array<const gameplay::WeaponDefinition*, 4>& weapons);

    int fighter_count() const override { return m_battle ? 4 : 0; }
    int side(int fighter) const override { return fighter / 2; }
    const game::FighterView& fighter(int index) const override { return m_fighters[static_cast<size_t>(index)]; }
    const gameplay::MatchEconomy& economy() const override { return m_economy; }
    int locked_target(int fighter) const override { return m_battle ? m_battle->actor(static_cast<unsigned>(fighter)).target : -1; }
    int aim_target(int fighter) const override { return locked_target(fighter); }
    int lock_pulse(int fighter) const override { return m_battle ? m_battle->actor(static_cast<unsigned>(fighter)).lockPulse : 0; }
    bool hud_hidden() const override { return m_battle && m_battle->hud_hidden(); }
    game::BattleNotice notice(int fighter) const override;
    game::BattleResultNotice result_notice() const override;
    bool ai_enabled(int) const override { return true; }
    bool camera_pose(int fighter, game::CameraPoseView& out) const override;
    void for_each_shot(const std::function<void(const game::ShotView&)>& visit) const override;
    void for_each_spark(const std::function<void(const game::SparkView&)>&) const override {}

    game::BattleFrame step(const fnd::input::PlayerState* inputs[game::kMatchFighterCount], double dt) override;
    void set_paused(bool paused) override { m_paused = paused; }
    void set_primary_listener_fighter(int fighter) override { m_listener = fighter; }

private:
    std::unique_ptr<sim::Battle> m_battle;
    std::array<CoreFighter, 4> m_fighters{};
    gameplay::MatchEconomy m_economy{};
    bool m_paused = false;
    int m_listener = 0;
    bool m_roundReported = false;
};

}  // namespace sim
