#pragma once
// What the product reads from a battle, and the commands it may send. The renderer, HUD, audio
// and front end see only this, so the simulation behind it can change (docs/DIRECTION.md, M3-M4).
//
// The parsers and plain data these name (CharacterMoves, WeaponDefinition, WeaponTrail,
// MatchEconomy) hold no fighter logic and stay after the legacy path is removed.
#include <functional>
#include <string>
#include <utility>
#include <vector>

#include <glm/glm.hpp>

#include "assets/xmodel.h"
#include "game/battle_types.h"
#include "game/fighter_pose.h"
#include "gameplay/character_moves.h"
#include "gameplay/match_economy.h"
#include "gameplay/weapon_definition.h"
#include "gameplay/weapon_trail.h"
#include "input/input.h"

namespace game {

class FighterView : public IFighterPose {
public:
    // Placement and identity.
    virtual const glm::vec3& position() const = 0;
    virtual float facing_yaw() const = 0;
    virtual glm::mat4 modelMatrix() const = 0;
    virtual const gameplay::CharacterMoves* moves() const = 0;
    virtual const gameplay::WeaponDefinition* weapon() const = 0;

    // State.
    virtual FighterState state() const = 0;
    virtual bool is_alive() const = 0;
    virtual int hp() const = 0;
    virtual int max_hp() const = 0;
    virtual int stamina() const = 0;
    virtual int charge_gauge() const = 0;
    virtual const CombatStats& stats() const = 0;

    // Animation and action.
    virtual int anim_set_index() const = 0;
    virtual const char* anim_set_name() const = 0;
    virtual bool anim_fallback() const = 0;
    virtual bool anim_no_selector() const = 0;
    virtual int phase_elapsed() const = 0;
    virtual int attack_move_id() const = 0;
    virtual int shot_move_id() const = 0;
    virtual int action_camera() const = 0;
    virtual HitboxDebug hitbox_debug() const = 0;

    // Magazines.
    virtual int main_whole() const = 0;
    virtual float main_frac() const = 0;
    virtual bool reload_ok() const = 0;
    virtual int charge_whole() const = 0;
    virtual float charge_frac() const = 0;
    virtual float charge_hold_frac() const = 0;
    virtual ShotTier charge_tier() const = 0;
    virtual ShotTier last_shot_tier() const = 0;

    // Hypermode and aura.
    virtual Hypermode hypermode() const = 0;
    virtual float hyper_gauge() const = 0;
    virtual bool hyper_active() const = 0;
    virtual bool hyper_ready() const = 0;
    virtual float hyper_seconds_left() const = 0;
    virtual int hyper_flash_alpha() const = 0;
    virtual bool hyper_activation_playing() const = 0;
    virtual int hyper_activation_elapsed() const = 0;
    virtual bool aura_active() const = 0;
    virtual glm::vec3 aura_center_local() const = 0;
    virtual float aura_radius() const = 0;
    virtual Rgb aura_color() const = 0;

    // Weapon presentation.
    virtual bool draws_item_model(int model) const = 0;
    virtual const gameplay::WeaponTrail& trail(int hand) const = 0;
    virtual int trail_item_model(int hand) const = 0;

    // A simulation that samples its own skeleton fills one model-space matrix per rig frame
    // and returns true. The legacy path animates the rig's xm::Controller instead.
    virtual bool core_pose(std::vector<glm::mat4>&) const { return false; }
    // The HP bar's ghost in percent, when the simulation keeps one.
    virtual bool hp_ghost(float&) const { return false; }
    // The earned title, when the simulation chose it itself; -1 leaves it to the product's rules.
    virtual int result_title() const { return -1; }
};

inline constexpr float kShotCubeSize = 16.0f;
inline constexpr int kMaxLiveShots = 32;

// One live shot, as the effect pass and the debug overlays read it.
struct ShotView {
    int owner = -1;       // fighter index, -1 when none
    int bulletRow = -1;   // the item row it was launched from
    glm::vec3 pos{0.f};
    Rgb color = 0;
    glm::mat4 modelMatrix{1.f};
    bool billboard = false;
    const xm::Controller* controller = nullptr;  // null without a model
    // With no controller, the time into the model's first set the shot's pose samples, or < 0.
    float animationSeconds = -1.f;
    std::vector<std::pair<std::string, std::string>> textureOverrides;
    int tint = 0;
};

struct SparkView {
    glm::vec3 pos{0.f};
    float size = 0.f;
    Rgb color = 0;
};

// A simulation's own camera for one fighter's view.
struct CameraPoseView {
    glm::vec3 eye{0.f}, lookAt{0.f};
    float fovY = 0.f, nearPlane = 0.f;
};

class BattleView {
public:
    virtual ~BattleView() = default;

    // The result presentation draws no battle HUD.
    virtual bool hud_hidden() const { return false; }
    // False leaves the view to the product's own ArenaCamera.
    virtual bool camera_pose(int, CameraPoseView&) const { return false; }

    virtual int fighter_count() const = 0;
    virtual int side(int fighter) const = 0;
    virtual const FighterView& fighter(int index) const = 0;
    virtual const gameplay::MatchEconomy& economy() const = 0;

    // Combat targets, by fighter index (gameplay/target_lock.h).
    virtual int locked_target(int fighter) const = 0;
    virtual int aim_target(int fighter) const = 0;
    virtual int lock_pulse(int fighter) const = 0;
    virtual bool ai_enabled(int fighter) const = 0;

    virtual void for_each_shot(const std::function<void(const ShotView&)>& visit) const = 0;
    virtual void for_each_spark(const std::function<void(const SparkView&)>& visit) const = 0;
};

class Battle : public BattleView {
public:
    // One optional input per fighter, in launch order. A paused battle returns an empty frame.
    virtual BattleFrame step(const fnd::input::PlayerState* inputs[kMatchFighterCount], double dt) = 0;
    virtual void set_paused(bool paused) = 0;
    virtual void begin_round_entry() = 0;
    virtual void step_round_entry(double dt) = 0;
    virtual void cycle_locked_target(int fighter, bool forward) = 0;
    virtual void lock_ally_target(int fighter) = 0;
    virtual void set_primary_listener_fighter(int fighter) = 0;
};

}  // namespace game
