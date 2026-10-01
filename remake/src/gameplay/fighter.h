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
//    Idle/Walk → ShootA/B/C → Idle (C released: tap/yellow/red tier, 20 frames;
//                                   tiers map to the binary's shotA/B/C anim
//                                   states @0x2b7560+; costs + reloadNG gating
//                                   live in projectile.h)
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
#include "gameplay/projectile.h"
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
    ShootA      = 12,  // tap shot fired (anim "shotA")
    ShootB      = 13,  // yellow charge released (anim "shotB")
    ShootC      = 14,  // red charge released (anim "shotC")
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
        case FighterState::ShootA:      return "shotA";
        case FighterState::ShootB:      return "shotB";
        case FighterState::ShootC:      return "shotC";
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
    // Shot economy (spec §3.1; counts pinned by battle-hud.webp, rest tuning).
    static constexpr float kMainMax       = 6.0f;   // MAIN stock
    static constexpr float kChargeMax     = 2.0f;   // CHARGE stock
    static constexpr float kMainPerSec    = 0.8f;   // MAIN refill rate
    static constexpr float kChargePerSec  = 0.3f;   // CHARGE refill rate
    static constexpr float kYellowHoldSec = 0.45f;  // hold → yellow tier
    static constexpr float kRedHoldSec    = 1.10f;  // hold → red tier
    static constexpr int   kShotFrames    = 20;     // firing pose length
    static constexpr float kMuzzleForward = 60.0f;  // spawn ahead of fighter
    static constexpr float kMuzzleHeight  = 100.0f; // spawn above feet
};

// Handoff from Fighter (input/charge side) to the scene (spawn/collide side):
// update_state_machine() arms this on C release; Scene_Gameplay drains it
// into the ProjectilePool the same frame, so at most one shot queues.
struct PendingShot {
    bool          armed = false;
    ShotTier      tier  = ShotTier::Tap;
    D3DXVECTOR3   pos   {};
    D3DXVECTOR3   dir   {0, 0, 1};
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

    // Scene drains the shot armed by C-release into the ProjectilePool.
    // Disarms on read (at most one pending shot ever queues).
    PendingShot take_pending_shot();

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
    // Fractional stocks feed the HUD bars directly (ammo-bar.webp).
    float main_frac() const { return m_main.value / FighterConstants::kMainMax; }
    float charge_frac() const {
        return m_charge.value / FighterConstants::kChargeMax;
    }
    int main_whole() const { return m_main.whole(); }
    int charge_whole() const { return m_charge.whole(); }
    // 0..1 across the full hold (red threshold = 1); colors the HUD meter.
    float charge_hold_frac() const;
    ShotTier charge_tier() const;
    bool reload_ok() const { return m_reloadTimer <= 0; }

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

    // --- shots (spec §3.1; costs/reload in projectile.h) ---
    AmmoStock    m_main;         // MAIN fractional stock (max 6)
    AmmoStock    m_charge;       // CHARGE fractional stock (max 2)
    float        m_chargeHeld = 0.0f;  // seconds C held (resets on release)
    int          m_reloadTimer = 0;    // reloadNG window (frames, 0 = reloadOK)
    PendingShot  m_pending;      // armed shot awaiting scene spawn

    // --- movement helpers ---
    void update_movement(const input::PlayerInput* input, const Fighter* opp, double dt);
    void update_state_machine(const input::PlayerInput* input, double dt);
    void update_facing(const Fighter* opp, double dt);
    void try_switch_animation();

    // Check if the current state allows movement (not attacking/stunned).
    bool can_act() const;
    bool can_move() const;

    // C-release firing: picks the tier from hold time, spends the matching
    // stock, opens the reloadNG window, and arms m_pending for the scene.
    // Silently drops when reloading or broke (HUD already shows the gate).
    void try_fire();
};

} // namespace daybreak::gameplay
