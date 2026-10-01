// =============================================================================
//  fighter.h — arena fighter with state machine + animation switching.
//
//  RE findings (docs/reverse-engineering.md):
//    - 40+ animation state names in .data: attackA/B/C, guard, damage,
//      damagedown, damageKO, battlestart, recovery, etc.
//    - Animation sets are looked up BY NAME via lstrcmpiA (case-insensitive).
//    - fcn.0041f580 = per-player update (3096 bytes): timers at +0x828
//      (just-pressed), +0xa0 (action frames remaining), +0x7ac (=30 when
//      action starts, 0.5s at 60fps).
//    - fcn.00420b30 = world matrix update (D3DXMatrixTranslation +
//      D3DXMatrixRotationY).
//    - HP max = 100 (constant 0x64 near "HPcheck").
//    - Movement uses D3DXVec3Normalize on the stick direction.
//
//  State machine (simplified from the 40+ anim states; input mapping is
//  provisional — see input_manager.h: the original has ONE melee key (X),
//  no dedicated heavy key, and separate shoot/special/tactics keys):
//    Idle → Walk → Idle            (stick moved / released)
//    Idle → Run → Idle             (dash: double-tap direction)
//    Idle/Walk → AttackA → Idle    (melee key — light, 30 frames)
//    Idle/Walk → AttackB → Idle    (heavy — currently same-key stand-in,
//                                   real game uses directional variants)
//    Idle/Walk → Guard → Idle      (block key held)
//    Any → Hit → Idle              (took damage, 15 frames stun)
//    Any → Knockdown → KO          (HP reached 0)
//    BattleStart → Idle            (round start pose, 60 frames)
// =============================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <cstdint>
#include <string>

#include "file_parser/x_model_loader.h"
#include "input/input_manager.h"
#include "render/arena_camera.h"  // for CameraTarget

namespace daybreak::gameplay {

// Fighter states — mirror the original game's animation state names.
enum class FighterState : int {
    Idle        = 0,   // standing, no input
    Walk        = 1,   // moving (stick/d-pad)
    Run         = 2,   // dashing (double-tap)
    AttackA     = 3,   // melee (provisional input; see input_manager.h)
    AttackB     = 4,   // heavy stand-in (no dedicated key in original)
    AttackC     = 5,   // special attack (not yet mapped to input)
    Guard       = 6,   // blocking (block key held)
    Hit         = 7,   // taking damage (stun)
    Knockdown   = 8,   // knocked down
    KO          = 9,   // defeated
    BattleStart = 10,  // round start pose
    TagOut      = 11,  // 2v2: tagged out (partner tagged in)
};

// Maps FighterState → animation set name (matching the .X file's named
// AnimationSets).  The original game uses lstrcmpiA for case-insensitive
// matching, so the name must match the AnimationSet name in the .X file.
inline const char* state_to_anim_name(FighterState s) {
    switch (s) {
        case FighterState::Idle:        return "idle";      // may not exist → falls back to track 0
        case FighterState::Walk:        return "walk";
        case FighterState::Run:         return "run";
        case FighterState::AttackA:     return "attackA";
        case FighterState::AttackB:     return "attackB";
        case FighterState::AttackC:     return "attackC";
        case FighterState::Guard:       return "guard";
        case FighterState::Hit:         return "damage";
        case FighterState::Knockdown:   return "damagedown";
        case FighterState::KO:          return "damageKO";
        case FighterState::BattleStart: return "battlestart";
        case FighterState::TagOut:      return "recovery";
        default: return nullptr;
    }
}

// Movement speed constants (from RE section 14.7 + gameplay tuning).
// The original uses 20.0 as capsule radius and generous distances.
struct FighterConstants {
    static constexpr float kWalkSpeed     = 80.0f;   // units/sec
    static constexpr float kRunSpeed      = 200.0f;  // units/sec (dash)
    static constexpr float kTurnSpeed     = 8.0f;    // radians/sec (lerp factor)
    static constexpr int   kMaxHP         = 100;     // 0x64 in the binary
    static constexpr int   kMaxStamina    = 100;
    static constexpr int   kAttackFrames  = 30;      // 0x1e = 0.5s at 60fps
    static constexpr int   kHitStunFrames = 15;      // ~0.25s stun
    static constexpr int   kBattleStartFrames = 60;  // 1.0s intro pose
    static constexpr float kMeleeRange    = 160.0f;  // XZ reach of melee swings
    static constexpr int   kLightDamage   = 5;
    static constexpr int   kHeavyDamage   = 12;
};

class Fighter {
public:
    Fighter() = default;
    ~Fighter() = default;

    // Initialize the fighter with a model and starting position.
    void init(XModel* model, const D3DXVECTOR3& pos, float facing);
    void reset(const D3DXVECTOR3& pos, float facing);

    // Update the fighter for this frame.
    // `input` = the player's input (or nullptr for AI/dummy).
    // `opponent` = the other fighter (for lock-on facing).
    // `dt` = delta time in seconds.
    void update(const input::PlayerInput* input, const Fighter* opponent, double dt);

    // Render the fighter's model.  The caller should have already set up
    // the view/projection matrices; this sets the world matrix from the
    // fighter's position + facing.
    void render(IDirect3DDevice9* device);

    // --- combat ---
    void take_damage(int amount);
    void set_state(FighterState new_state);

    // Melee hit check, called once per frame by the scene for each
    // attacker→target pair. Only fires during the attack's active window,
    // at most once per swing (m_didHitThisSwing). Range-only for now —
    // real hitboxes (mesh raycast) come with the projectile milestone.
    // Returns true if the hit connected.
    bool try_melee_hit(Fighter& target);

    // --- getters ---
    const D3DXVECTOR3& position()   const { return m_position; }
    float              facing_yaw() const { return m_facing; }
    int                hp()         const { return m_hp; }
    int                stamina()    const { return m_stamina; }
    FighterState       state()      const { return m_state; }
    bool               is_alive()   const { return m_hp > 0; }
    XModel*            model()      const { return m_model; }

    // For CameraTarget compatibility.
    // (ArenaCamera reads position + facing_yaw from CameraTarget;
    // we provide a method to sync.)
    void sync_target(daybreak::CameraTarget& target) const;

private:
    // --- visual ---
    XModel*      m_model = nullptr;

    // --- transform ---
    D3DXVECTOR3  m_position   {0, 0, 0};
    D3DXVECTOR3  m_velocity   {0, 0, 0};
    float        m_facing     = 0.0f;   // yaw (radians, around Y)

    // --- stats ---
    int          m_hp          = FighterConstants::kMaxHP;
    int          m_stamina     = FighterConstants::kMaxStamina;

    // --- state machine ---
    FighterState m_state       = FighterState::Idle;
    int          m_stateTimer  = 0;    // frames remaining in current state
    int          m_animSetIdx  = -1;   // cached animation set index for current state
    bool         m_didHitThisSwing = false;  // melee connected already this swing

    // --- movement helpers ---
    void update_movement(const input::PlayerInput* input, const Fighter* opp, double dt);
    void update_state_machine(const input::PlayerInput* input, double dt);
    void update_facing(const Fighter* opp, double dt);
    void try_switch_animation();

    // Check if the current state allows movement (not attacking/stunned).
    bool can_act() const;
    bool can_move() const;
};

} // namespace daybreak::gameplay
