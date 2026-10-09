// =============================================================================
//  fighter.h — arena fighter with state machine + animation switching.
//
//  Ported to the SDL3 + WebGPU foundation (docs/FULL-REPLACEMENT-PLAN.md §5
//  item 2b) from remake/src/gameplay/fighter.h: logic only, D3D-free, names
//  kept identical so the two can be diffed. Deviations are listed in "PORT
//  NOTES" at the bottom of this header.
//
//  RE findings (docs/reverse-engineering.md):
//    - The 39 strings including attackA/B/C and shotA/B/C are voice-cue keys
//      loaded by FUN_00431e70, not animation names. The original binds clips
//      through move IDs and each character/weapon NN.dat phase tags. Attack and
//      dash defaults called out below are port inferences where raw selectors
//      remain unresolved (docs/ANIMATION-SETS.md).
//    - fcn.0041f580 = per-player update (3096 bytes): timers at +0x828
//      (just-pressed), +0xa0 (action frames remaining), +0x7ac (=30 when
//      action starts, 0.5s at 60fps).
//    - fcn.00420b30 = world matrix update (D3DXMatrixTranslation +
//      D3DXMatrixRotationY).
//    - HP max = 100 (constant 0x64 near "HPcheck").
//    - Movement uses D3DXVec3Normalize on the stick direction.
//
//  Hypermode (spec §3.4) is modelled from the wiki, which pins the numbers
//  (higurashidaybreak.fandom.com/wiki/Hypermode + per-mode pages): the
//  bottom-left bar fills by damage dealt (Friendship) or taken (Oyashiro,
//  Kakera — slower), S activates it in DX (Kakera instead fires itself on a
//  lethal hit), and while active the fighter gets a coloured aura, the
//  mode's damage/stun/recharge modifiers, and an EX move on S. The
//  original's "auto-activate at full" rule (pre-DX) is not modelled.
//
//  State machine (port inputs are simplified from the original's move graph):
//    Idle ↔ Walk                   (stick or d-pad movement)
//    Idle ↔ Run                    (double-tap dash; forward/back move selectors)
//    AttackA                       (one melee input; neutral ground uses move 300,
//                                   while dash/air animation selectors are unresolved)
//    ShootA/B/C                    (port charge tiers; firing animation selector unresolved)
//    Jump / Guard                  (port states with unresolved animation selectors)
//    Any → Hit / Knockdown / KO    (reaction selectors recovered from move dispatch)
//    BattleStart → Idle            (round reset move selector recovered)
// =============================================================================
#pragma once

#include <algorithm>
#include <cstdint>
#include <string>

#include "assets/xmodel.h"          // xm::Model / xm::Controller (non-owning)
#include "game/fighter_pose.h"      // game::IFighterPose / game::FighterPose
#include "gameplay/character_moves.h"  // CharacterMoves (borrowed move table)
#include "gameplay/match_economy.h"    // the KO/Overkill credit rules (issue #11)
#include "gameplay/projectile.h"
#include "gameplay/melee_rules.h"
#include "gameplay/weapon_trail.h"
#include "gameplay/weapon_definition.h"
#include "input/input.h"
#include "render/arena_camera.h"    // for render::ArenaTarget

namespace gameplay {

// The foundation's device-free input model has the same 13-action layout as the
// DX9 build's input/input_manager.h (verified field-by-field in the port
// report), so the alias lets every `input::Action` / `input::PlayerState` use
// below read exactly like the source's `input::Action` / `input::PlayerInput`.
namespace input = fnd::input;

// Fighter states are port labels. The executable stores move IDs directly in
// `[player+0xadec]`; only recovered port-state selectors map to those IDs.
enum class FighterState : int {
    Idle        = 0,   // standing, no input
    Walk        = 1,   // moving (stick/d-pad)
    Run         = 2,   // dashing (double-tap)
    AttackA     = 3,   // melee (the original's single attack bit; see input.h)
    AttackC     = 4,   // special attack (not yet mapped to input)
    // 5 is the removed heavy stand-in's slot (issue #10). The values are labels, not
    // persisted state, and keeping them stable avoids renumbering the remaining states.
    Guard       = 6,   // blocking (block key held)
    Hit         = 7,   // taking damage (stun)
    Knockdown   = 8,   // knocked down
    KO          = 9,   // defeated
    BattleStart = 10,  // round start pose
    TagOut      = 11,  // reserved, never entered: no character swap exists —
                        // the reticle only changes targets (FUN_00421e30), and the
                        // "tag" voice cluster is partner callouts (see below)
    ShootA      = 12,  // provisional firing-state label
    ShootB      = 13,  // provisional firing-state label
    ShootC      = 14,  // provisional firing-state label
    Jump        = 15,  // airborne (leap, fly, or falling out of an air dash)
    ShotFinal   = 16,  // provisional port label for the EX firing state
};

// The executable binds a move's first phase to the animation controller
// (FUN_00421080 → FUN_00421100 → FUN_00421410). The phase section tag is the
// controller set index in that character's NN.dat (FUN_0041e180); the port must
// therefore resolve state → evidenced move ID → this fighter's table → phase
// tag. Missing selectors and rows stay unresolved instead of borrowing a set
// from another character/weapon or interpreting a voice key as an animation.
// These state/move pairs are supported by reset and dispatch paths in
// FUN_0041de68, FUN_004219a0, and FUN_00428510. Contextual moves are carried by
// their transition; unlocated selectors return -1.
inline int state_to_move_id(FighterState s) {
    switch (s) {
        case FighterState::Idle:        return 0;   // reset: FUN_0041de68
        case FighterState::Walk:        return 10;  // walk dispatch: FUN_00428510
        case FighterState::Hit:         return 103; // reaction dispatch
        case FighterState::Knockdown:   return 196; // grounded reaction dispatch
        case FighterState::KO:          return 203; // KO reaction dispatch
        case FighterState::BattleStart: return 194; // round reset: FUN_004219a0
        case FighterState::Run:
        case FighterState::AttackA:
        case FighterState::AttackC:
        case FighterState::Guard:
        case FighterState::ShootA:
        case FighterState::ShootB:
        case FighterState::ShootC:
        case FighterState::Jump:
        case FighterState::ShotFinal:
        case FighterState::TagOut:
        default:                        return -1;
    }
}
// Guard is the one state with NO selector in the source, and that is a recovered
// result rather than a gap: a block is a damage-path branch. Live `DaybreakDX.exe`
// (original, md5 a136ddc01bd7ef355b759b88ac89e02c) via the bridge, `FUN_00637950`
// (0x637950), blocked branch of the decompiled listing (:535-549): it writes the hit
// registry, the per-slot `0x100` marker and `[victim+0xaf30]`, and calls no move bind
// (FUN_00421080 / FUN_00421100 / FUN_00421410) and no effect or voice helper. The
// predicate that reaches it is
//   (|bearing - facing| > 45 || (victimword & 0x2000)) && (victimword & 0x400)
//   && !(attackerword & 8)
// with victimword = [victim+0x10]+0x28 and attackerword = [attacker+0x10]+0x2c, whose
// 8 bit is the unblockable flag. Which physical buttons the two victim bits belong to
// is NOT recovered — the device button word carries `0x10 << slot`, and this is a
// different word whose builder is not located — so the port keeps its own Guard key.
// A state that resolves to -1 for this reason must hold the clip already playing
// instead of reporting a set-0 miss.
inline bool state_has_animation_selector(FighterState s) {
    return s != FighterState::Guard;
}
// The trace's per-fighter field is a port state label, not a recovered animation
// binding. The DX9 build this trace is diffed against binds no animation sets at all
// (its d3dx9 under Wine returns no controller — see tests/visual/out/*.log), so it
// has no set to print, and compare_match_traces.py asserts these names match exactly.
// The set actually bound is exposed by Fighter::anim_set_index()/anim_set_name();
// the shot labels below do not assert links to the executable's numeric move states.
inline const char* state_to_anim_name(FighterState s) {
    switch (s) {
        case FighterState::Idle:        return "idle";
        case FighterState::Walk:        return "walk";
        case FighterState::Run:         return "run";
        case FighterState::AttackA:     return "attackA";
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
        case FighterState::Jump:        return "jump";
        case FighterState::ShotFinal:   return "shotFinal"; // provisional port label
        default: return nullptr;
    }
}

// Hypermode pick (spec §3.4). Index order matches the versus setup list and
// the -hyper CLI argument: Friendship, Oyashiro, Kakera (DX's third mode).
enum class Hypermode : int {
    Friendship = 0,
    Oyashiro   = 1,
    Kakera     = 2,
};

// Per-mode rules. Durations and damage/stun multipliers are wiki numbers;
// fill rates and recharge boosts are provisional tuning (the wiki gives no
// figures, only "slower than Oyashiro" for Kakera).
struct HypermodeParams {
    const char* name;
    float fillPerDamageDealt;  // gauge fraction gained per HP dealt
    float fillPerDamageTaken;  // gauge fraction gained per HP taken
    float durationSec;
    float damageTakenMul;
    float damageDealtMul;
    bool  autoOnDeath;         // Kakera: fires itself when a hit would KO
    bool  stunImmune;          // Kakera: never stunned while active
    bool  stunEveryOtherHit;   // Oyashiro: alternate hits skip the stun
    float mainRechargeMul;     // Friendship: ammo comes back faster
    float chargeRechargeMul;
    Rgb   aura;
};

inline HypermodeParams hypermode_params(Hypermode m) {
    switch (m) {
        // Aura colours follow the wiki's mode captures: Oyashiro burns
        // magenta/pink (Keiichi), Friendship is cyan (Shion). Kakera has no
        // capture yet — green keeps it distinguishable from both.
        case Hypermode::Friendship:
            return {"FRIENDSHIP", 1.0f / 60.0f, 0.0f, 15.0f, 1.0f, 1.0f,
                    false, false, false, 1.6f, 1.6f,
                    packRgb(130, 220, 255)};
        case Hypermode::Oyashiro:
            return {"OYASHIRO", 0.0f, 1.0f / 50.0f, 15.0f, 0.75f, 1.5f,
                    false, false, true, 1.0f, 1.0f,
                    packRgb(255, 110, 220)};
        case Hypermode::Kakera:
            return {"KAKERA", 0.0f, 1.0f / 90.0f, 25.0f, 0.20f, 1.5f,
                    true, true, false, 1.0f, 1.0f,
                    packRgb(150, 255, 160)};
    }
    return {"FRIENDSHIP", 0.0f, 0.0f, 15.0f, 1.0f, 1.0f,
            false, false, false, 1.0f, 1.0f, packRgb(255, 255, 255)};
}

// Movement speed constants for a fighter with NO recovered handler: `move_behavior.h`'s
// kLocomotion now carries every shipped combo, so this table is the custom-character and
// legacy fallback, never the roster paths. The handlers move in units/tick with no ×dt
// (FUN_004202b0 builds displacement as cos/sin(yaw)×speed; FUN_0042cb50/FUN_0042c970 add
// it raw), so u/s = 60 × the tick literal; the observed per-character range is walk
// 2.5–7.5/tick (150–450/s), dash 10–30/tick (600–1800/s), air-dash 12.5–40/tick
// (750–2400/s). The old walk 80 / dash 200 / leap 380 were placeholders with no RE behind
// them.
struct FighterConstants {
    static constexpr float kWalkSpeed     = 420.0f;  // 7.0/tick, the modal walk
    static constexpr float kRunSpeed      = 900.0f;  // 15.0/tick, the modal dash;
                                                     // phase-2 decay not modelled
    static constexpr float kTurnSpeed     = 8.0f;    // radians/sec (lerp factor)
    static constexpr int   kMaxHP         = 100;     // 0x64 in the binary
    static constexpr int   kMaxStamina    = 100;
    static constexpr int   kAttackFrames  = 30;      // 0x1e = 0.5s at 60fps
    static constexpr int   kHitStunFrames = 15;      // ~0.25s stun
    static constexpr int   kBattleStartFrames = 60;  // 1.0s intro pose
    static constexpr float kMeleeRange    = 160.0f;  // legacy shared reach: the
        // fallback when no move table is bound, and the Oyashiro activation burst
        // radius. Data-driven swings use their own hitRadius (30 + hr, FUN_0063b470).
    static constexpr int   kLightDamage   = 5;
    // The launch-time injection seams' bounds. Named because std::clamp cannot take a
    // literal as a bound, and because an unnamed 50/200 below reads as tuning: PORT RULE,
    // these are the selection screen's own battle-setting range in percent.
    static constexpr float kGaugeMin      = 0.0f;   // set_hyper_gauge: 0..1
    static constexpr float kGaugeMax      = 1.0f;
    static constexpr int   kBattleRatePercentMin = 50;   // set_battle_rates
    static constexpr int   kBattleRatePercentMax = 200;
    // Shot economy (spec §3.1; counts pinned by battle-hud.webp, rest tuning).
    static constexpr float kMainMax       = 6.0f;   // MAIN stock
    static constexpr float kChargeMax     = 2.0f;   // CHARGE stock
    static constexpr float kMainPerSec    = 0.8f;   // MAIN refill rate
    static constexpr float kChargePerSec  = 0.3f;   // CHARGE refill rate
    static constexpr float kYellowHoldSec = 0.45f;  // hold → yellow tier
    static constexpr float kRedHoldSec    = 1.10f;  // hold → red tier
    static constexpr int   kShotStateFrames = 20;   // provisional shot-state duration
    static constexpr float kMuzzleForward = 60.0f;  // spawn ahead of fighter
    static constexpr float kMuzzleHeight  = 100.0f; // spawn above feet
    // Air movement: the leap matches the 0x29 fly-takeoff (vy 12.0/tick, 10.5 for
    // flyer characters) under the shared g = 0.5/tick (FUN_00438310:457,474 and
    // FUN_00428510's 0x3F00000 default branch). Sustained hold-climb reuses the
    // takeoff scale — INFERRED from the g=0 hover states (0x28), not a timed rate;
    // the ceiling and budget below are still the port's own.
    static constexpr float kGravity       = 1800.0f; // downward accel (u/s^2)
    static constexpr float kJumpSpeed     = 720.0f;  // leap initial vy (u/s)
    // The source switches the air chain from "going up" to "coming down" when
    // vy drops under the literal 0x40c00000 = 6.0 per tick (live FUN_0043ffc0
    // case 0x29 → FUN_00421080(0x2a)); 6.0/tick at the original's 60 Hz is 360 u/s.
    static constexpr float kJumpApexSpeed = 360.0f;
    static constexpr float kFlyRise       = 720.0f;  // vy while holding Z aloft
    static constexpr float kFlyTimeSec    = 1.2f;   // flight budget per airtime
    static constexpr float kFlyMaxAlt     = 420.0f; // ceiling above takeoff
    static constexpr float kAirControl    = 0.7f;   // stick authority airborne
    // Airborne respawn height: FUN_00421bd0 writes [fighter+0x18] = 0x447a0000
    // (@0x421c62-0x421c65) after FUN_004219a0's state restore, so a revived fighter
    // re-enters in the air and falls back in. ABSOLUTE stage units, not a delta.
    static constexpr float kRespawnAirY   = 1000.0f;
    // Dashes (spec §3.2): double-tap a direction; airborne → air dash.
    static constexpr double kDoubleTapSec = 0.30;   // tap,tap window (seconds)
    static constexpr int   kDashFrames    = 20;     // committed dash length
    static constexpr float kAirDashSpeed  = 1200.0f; // 20.0/tick, the modal air dash
    // Stamina spends (spec §3.4: dashing/jumping/block-hold spend it all).
    static constexpr float kDashStamina    = 20.0f;  // per dash (gated: no
                                                    // dash below this)
    static constexpr float kJumpStamina    = 10.0f;  // per leap (clamped)
    static constexpr float kGuardDrainSec  = 25.0f;  // block-hold drain
    static constexpr float kFlyDrainSec    = 30.0f;  // flight drain
    static constexpr float kStaminaRegenSec = 60.0f; // grounded refill rate
};

// One swing's resolved numbers (issue #26 steps 3–4). Data-driven when a move
// table is bound: windows, reach, damage and stun come from the situation's
// move hit entry. Otherwise the legacy shared tuning, so a fighter with no moves
// bound behaves exactly like the pre-#26 machine.
//
// The legacy defaults ARE melee_rules.h's numbers (kLegacy*), not a second copy of them:
// this struct once carried its own literals while MeleeRules carried another set that
// only tests read, so editing "the attack sphere's radius" in one place changed nothing
// live. `window` is the one window struct build_melee_swing() overrides.
struct MeleeSwing {
    bool        dataDriven = false;
    int         moveId = -1;   // character-.dat move this swing plays (-1 = legacy)
    MeleeWindow window = kLegacyWindow;
    float       radius = kLegacyRadius;   // stands in for weapon+0x24
    int         damage = FighterConstants::kLightDamage;
    int         hitstun = 8;              // legacy active-window stun
    int total_ticks() const { return window.total_ticks(); }
    bool is_active(int elapsed) const { return window.is_active(elapsed); }
    bool is_recovery(int elapsed) const { return window.is_recovery(elapsed); }
};

// Handoff from Fighter (input/charge side) to the scene (spawn/collide side):
// update_state_machine() arms this on C release; Scene_Gameplay drains it
// into the ProjectilePool the same frame, so at most one shot queues.
struct PendingShot {
    bool          armed = false;
    ShotTier      tier  = ShotTier::Tap;
    glm::vec3     pos   {};
    glm::vec3     dir   {0, 0, 1};
    int           bulletRow = -1;
    Fighter*      target = nullptr;
};

struct CombatStats { int kos = 0, deaths = 0, damageDealt = 0, damageTaken = 0; };

class Fighter : public game::IFighterPose {
public:
    Fighter() = default;
    ~Fighter() override = default;

    // Initialize the fighter with a model + its animation controller and a
    // starting position. Both pointers are borrowed (the asset layer owns
    // them); either may be null for a pose-only fighter.
    void init(const xm::Model* model, xm::Controller* anim,
              const glm::vec3& pos, float facing);
    void reset(const glm::vec3& pos, float facing);
    void begin_round_entry();

    // Bind (or rebind) the model + controller without touching state. The DX9
    // build's XModel owned both halves; the foundation splits them, so this is
    // the one place the split is joined (see PORT NOTES 3).
    void bind(const xm::Model* model, xm::Controller* anim);

    // Verification toggle (the parent wires --no-anim to it): with animation off no
    // set is bound and no playhead advances, so the fighter renders the bind pose and
    // a gate frame is comparable with the DX9 reference, which binds 0 sets. The pose
    // then comes from evalLocal's bind defaults rather than from any animation set.
    void set_animate(bool on);
    bool animate() const { return m_animate; }

    // Update the fighter for this frame.
    // `input` = the player's input (or nullptr for AI/dummy).
    // `opponent` = the other fighter (lock-on facing, and the target of an
    // Oyashiro activation burst — hence non-const).
    // `dt` = delta time in seconds.
    void update(const input::PlayerState* input, Fighter* opponent, double dt,
                const game::physics::MovementCollision* collision = nullptr);

    // --- render data (the DX9 render(IDirect3DDevice9*) split) ---
    // World matrix the DX9 build pushed as D3DTS_WORLD (FUN_00420b30):
    // RotationY(facing + 180°) then Translation(position), i.e. T * R in glm's
    // column-vector convention. The half turn maps the rigs' own front (-Z, measured
    // on the shipped SkinWeights — see fighter.cpp) onto the movement facing. The
    // foundation renderer passes this to xm::DrawUniform::model.
    glm::mat4 modelMatrix() const;

    // game::IFighterPose: position / facing / animation time / alive, for the
    // camera lock-on and the renderer's pose lookup.
    game::FighterPose pose() const override;

    // Hypermode aura (the DX9 render's second, additive cube pass): drawn in
    // the model's own space at aura_center_local(), sized aura_radius(), in
    // aura_color() (mode colour, alpha pulsed by the fighter clock).
    bool      aura_active() const { return m_hyperActive; }
    glm::vec3 aura_center_local() const { return glm::vec3(0.0f, 58.0f, 0.0f); }
    float     aura_radius() const;
    Rgb       aura_color() const;

    // --- combat ---
    // What one damage event did (issue #11). The scene reads it to credit the balloon
    // exactly once per event; a caller that only cares about HP may ignore it.
    enum class DamageResult : unsigned char {
        Hit,       // HP lost, the fighter is still up
        Overkill,  // the target was already down: +1 balloon, no new KO credit
        Ko,        // this blow took it to 0: one KO credit is pending
    };

    // The KO credit the economy needs (FUN_00639160 @0x639399-0x6393c6 for melee,
    // FUN_00637950 @0x638cad-0x638d35 for shots): how far below zero the blow drove
    // HP, whether the killing blow's reaction was the downed one, and which of the two
    // increment formulas applies.
    struct KoCredit {
        int  overkillHp = 0;
        bool reactionBonus = false;
        bool shot = false;
    };

    // `source` applies the attacker's Hypermode damage bonus and earns its
    // gauge (Friendship). Pass nullptr for environmental damage.
    // `hitstunFrames` overrides the hit-stun length when > 0: FUN_00637950:308 writes
    // the attacker's weapon block defenderHitstun (blob index 10, record +0x58) into
    // the victim's +0xa0 action counter, so the stun length is per weapon. 0 and
    // negative (the default) keep the shared kHitStunFrames.
    // `hitCategory` is the RAW record +0x64 dword the original feeds FUN_0063ba80
    // (@0x638c26) to pick the victim's reaction move; 0 is "unspecified", which takes
    // that function's default branch (198, the downed reaction) exactly as any
    // unmatched value does. `shot` marks projectile damage, whose increment formula and
    // already-down credit differ from melee's (see match_economy.h).
    DamageResult take_damage(int amount, Fighter* source = nullptr, int hitstunFrames = -1,
                             int hitCategory = 0, bool shot = false);
    void set_state(FighterState new_state);

    // A hit on an already-down fighter credits the balloon but must not re-enter the
    // KO state, restart the death clock or count another death. The scene drains the
    // pending credit into MatchEconomy, so it is counted exactly once.
    bool pending_ko() const { return m_koPending; }
    KoCredit take_ko_credit() {
        m_koPending = false;
        const KoCredit c = m_koCredit;
        m_koCredit = KoCredit{};
        return c;
    }
    // Hits that landed on this fighter while it was already down (Overkill). Drained
    // by the scene, one note_overkill_hit() per hit.
    int take_overkill_hits() {
        const int n = m_overkillHits;
        m_overkillHits = 0;
        return n;
    }

    // One-frame event latches for the frame report (issue #16). Same discipline as the
    // KO credit above: the transition arms the latch exactly once, the simulation drains
    // it into MatchFrame, so an event cannot fire twice or be missed by a tick.
    bool pending_swing_start() const { return m_swingStartedPending; }
    bool take_swing_start() {
        const bool armed = m_swingStartedPending;
        m_swingStartedPending = false;
        return armed;
    }
    bool pending_guard_start() const { return m_guardStartedPending; }
    bool take_guard_start() {
        const bool armed = m_guardStartedPending;
        m_guardStartedPending = false;
        return armed;
    }
    bool pending_hyper_start() const { return m_hyperStartedPending; }
    bool take_hyper_start() {
        const bool armed = m_hyperStartedPending;
        m_hyperStartedPending = false;
        return armed;
    }


    // --- respawn (issue #11) ---
    // FUN_004219a0 (0x4219a0) is a full state restore — HP at both +0x7a4 and +0x7a8
    // back to full, +0x7c0/+0x7c4/+0x7dc.. cleared, the action counter +0x7ac = 30,
    // +0x834 = 1000, the KO-bonus latch +0x84c = 0, 0xaeb8..0xaec7 zeroed, velocities
    // and +0x54 zeroed — and FUN_00421bd0 then repositions the fighter (a random point
    // inside the stage bounds in the original; this port keeps the fighter's OWN spawn
    // slot, which is the identity the issue requires) at the recovered air height. Move
    // 0xc2 (194) plays on re-entry, whose set is 43 — the set this port's BattleStart
    // plays — and [fighter+0xaecb] = 1 marks the fighter as not selectable by the
    // target lock until it is back on its feet.
    void respawn(const glm::vec3& spawn, float facing, float airY);
    // True from respawn() until the fighter lands. READ BY TARGET SELECTION ONLY: the
    // original's flag is read exclusively by FUN_0041f580's lock-validity test
    // (@0x41fe26-0x41fe73), so there is NO damage immunity to claim here.
    bool respawn_locked() const { return m_respawnLock; }

    // ---- character move table (gameplay/character_moves.h, issue #26) ----
    // Binds the parsed data/<char>/NN.dat for this fighter's own rig. Borrowed,
    // like the model and the weapon; null keeps legacy shared melee tuning and
    // leaves animation states without a recovered table binding on set 0.
    void set_moves(const CharacterMoves* moves);
    const CharacterMoves* moves() const { return m_moves; }
    // The character-.dat move currently used for melee tuning. Exposed for
    // combo-bound evidence checks.
    int attack_move_id() const { return m_attackMoveId; }
    // Port candidate for a grounded Up/Down dash (an input-to-move inference);
    // -1 means no candidate is used, including side and air dashes.
    int dash_move_id() const { return m_dashMoveId; }
    // Firing move the current shot plays, keyed off the charge tier and whether the
    // fighter was airborne at the release (move_behavior.h's MoveProgram::shot).
    int shot_move_id() const { return m_shotMoveId; }

    // ---- selected weapon (gameplay/weapon_definition.h, issue #9) ----
    // Binds the parsed data/item/NNN.dat for the selected weapon. Borrowed, like the
    // model; null keeps the historical shared tuning, which is what the standalone
    // --match trace path passes. A non-null weapon sizes this fighter's magazines and
    // charge thresholds from the file instead of the shared 6/2 constants.
    void set_weapon(const WeaponDefinition* weapon);
    const WeaponDefinition* weapon() const { return m_weapon; }

    // Binds the decoded data/bullet/<id>/<type>.dat scalars for a charge level, taken
    // from the weapon's own bullet table. These ARE recovered — FUN_005f8510's verbatim
    // 80-byte block, consumed by FUN_00637950 — unlike the magazine block. `level` is 1
    // (tap) or 2 (charged); a null argument clears it.
    void set_bullet_parameter(int level, const BulletParameter* parameter);
    const BulletParameter* bullet_parameter(int level) const {
        return m_bulletParams[(level == 2) ? 1 : 0];
    }
    void set_bullet_row(int row, const BulletParameter* parameter) {
        if (row >= 0 && row < 64) m_bulletRows[static_cast<size_t>(row)] = parameter;
    }
    const BulletParameter* bullet_row(int row) const {
        return row >= 0 && row < 64 ? m_bulletRows[static_cast<size_t>(row)] : nullptr;
    }
    void set_bullet_model(int row, const xm::Model* model) {
        if (row >= 0 && row < 64) m_bulletModels[static_cast<size_t>(row)] = model;
    }
    const xm::Model* bullet_model(int row) const {
        return row >= 0 && row < 64 ? m_bulletModels[static_cast<size_t>(row)] : nullptr;
    }
    ShotParams shot_params_for_row(ShotTier tier, int row) const;

    // ShotParams for this fighter's tier. Damage and hit radius come from the bound
    // BulletParameter when there is one; speed and lifetime stay the shared provisional
    // table, which the coverage table records as not recovered.
    ShotParams shot_params_for(ShotTier tier) const;

    // The pool units one shot of this tier costs, and whether it can fire at all right
    // now (reload window closed and that tier's own stock can pay the cost). fire_shot()
    // applies exactly these two gates, so a caller that asks first never loses a shot to
    // the silent drop (gameplay/bot_brain.h's shoot gate).
    float shot_cost(ShotTier tier) const;
    bool  can_fire(ShotTier tier) const;

    // The tier of the last shot this fighter armed. The armed flag is drained by
    // take_pending_shot(); the tier stays, which is what the muzzle-flash selector needs
    // on the tick the frame reports shotFired (issue #17).
    ShotTier last_shot_tier() const { return m_pending.tier; }

    // The recovered charge thresholds in SECONDS. FUN_00433eb0's per-magazine
    // chargeMax is a tick count (the shipped values run 60..1200, and 180 is the same
    // 0xb4 the ally hold is written with), converted through the fixed tick. PORT RULE:
    // the original's charge is a 100-point gauge with a 120-frame decay window, not a
    // hold timer, so this conversion is a design choice, not recovered behaviour.
    float yellow_hold_sec() const;
    float red_hold_sec() const;

    // --- hypermode (spec §3.4) ---
    void set_hypermode(Hypermode m) { m_hypermode = m; }
    // Launch-time state injection, 0..1, clamped. It stood in for the original's F4 (wiki
    // Basics §training: "F4 maxes Hypermode") until issue #48 implemented the key itself
    // (fill_gauges below), and stays as the launch-time seam the visual suite drives.
    void set_hyper_gauge(float f) {
        m_gauge = std::clamp(f, FighterConstants::kGaugeMin, FighterConstants::kGaugeMax);
    }
    // Startup HP (-hp): lets a test reach a lethal-hit path without a
    // wind-up (Kakera's death save, Overkill's downed window).
    void set_hp(int hp) {
        m_hp = std::clamp(hp, 1, m_maxHP);
    }
    void set_battle_rates(int healthPercent, int gaugePercent) {
        m_maxHP = std::clamp(healthPercent, FighterConstants::kBattleRatePercentMin,
                             FighterConstants::kBattleRatePercentMax);
        m_gaugeRate = std::clamp(gaugePercent, FighterConstants::kBattleRatePercentMin,
                                 FighterConstants::kBattleRatePercentMax) / 100.f;
    }
    // F1 (issue #48): the original writes HP AND max HP to 10000 at fighter+0x7a4/+0x7a8
    // (FUN_00634f60:175-182, after the two balloon stores at :173-174), i.e. the fighter's
    // full capacity in one store. The port's
    // capacity is m_maxHP — 100 in the original's own units (10000/100, the ×100 UNIT note
    // in main.cpp's result record) and scaled by the battle's HP setting — so "full" is
    // m_maxHP and this writes HP alone: m_maxHP is the battle's configured capacity, not a
    // value a debug key should rewrite. No clamp to 1, unlike set_hp(): a KO'd fighter is
    // restored exactly as the original's raw store restores it.
    void restore_full_hp() { m_hp = m_maxHP; }
    // F4 (issue #48): the original fills ONE gauge per fighter, selected by its +0x318 byte
    // (FUN_00634f60:184-204). The port carries no selector, so every meter it models is
    // filled; debug_keys.h names the recovered arm behind each (MAIN, CHARGE, hypermode).
    void fill_gauges() {
        m_main.value = m_main.max;
        m_charge.value = m_charge.max;
        set_hyper_gauge(1.0f);
    }
    int max_hp() const { return m_maxHP; }
    const CombatStats& stats() const { return m_stats; }
    void clear_stats() { m_stats = {}; }
    Hypermode hypermode() const { return m_hypermode; }
    bool  hyper_active() const { return m_hyperActive; }
    bool  hyper_ready() const { return m_gauge >= 1.0f && !m_hyperActive; }
    float hyper_gauge() const { return m_gauge; }
    float hyper_seconds_left() const { return m_hyperTimer; }

    // Scene drains the shot armed by C-release into the ProjectilePool.
    // Disarms on read (at most one pending shot ever queues).
    PendingShot take_pending_shot();

    // Melee hit test for ONE candidate, called once per attacker→candidate pair while
    // the swing is active. Rejects a candidate that is out of reach vertically, outside
    // the swing arc, or behind a solid barrier, and reports true only on the first
    // frame the pair connects.
    //
    // `collision` is the stage's answer to "is the straight line attacker→victim
    // blocked", from gameplay::MovementCollision (issue #7); nullptr disables the test.
    // Which reach applies comes from this fighter's OWN swing kind (aerial_attack(),
    // chosen when the swing started) rather than a second argument, so the caller cannot
    // disagree with the swing it is resolving. Ally exclusion is the caller's job (Match
    // only offers hostile candidates).
    bool try_melee_hit(Fighter& target,
                       const game::physics::MovementCollision* collision = nullptr);

    // A swing may connect with several opponents, each exactly once. The single
    // m_didHitThisSwing flag could not express that, so hits are tracked per victim
    // index for the duration of the swing and cleared when the state changes.
    bool already_hit_this_swing(int victimIndex) const {
        return victimIndex >= 0 && victimIndex < kMatchFighterCount &&
               (m_swingHits & (1u << victimIndex));
    }
    int  swing_hit_count() const { return m_swingHitCount; }

    // The move this fighter is playing, as a fighter index, or kNoTarget.
    static constexpr int kNoMeleeVictim = -1;

    // True while this fighter may start an action (can_act(), exposed for callers that
    // are not the state machine). A COM must not request a move the state machine would
    // drop: attacking mid-swing or during the respawn lock is exactly that (bot_brain.h).
    bool actionable() const { return can_act(); }
    // The Guard hold is refused while exhausted until the key is released (issue #6).
    // Exposed so a COM asks before holding instead of pressing into the lockout.
    bool guard_exhausted() const { return m_guardExhausted; }

    bool melee_in_recovery() const;
    bool melee_in_active() const {
        const MoveEntry* record = current_move_record();
        return record ? record->has_combat() : !m_moves && m_swing.is_active(m_meleeElapsed);
    }
    const MoveEntry* current_move_record() const;
    int move_phase() const { return m_phaseIndex; }
    int phase_elapsed() const { return m_moveElapsedTicks; }
    // FUN_00435000 launches from the bound slot's item muzzle anchor and falls back to
    // the bone origin only when the slot's prop id is -1 (FUN_00434a70's clear).
    bool weapon_slot_bound(int slot) const;
    int action_camera() const { return m_actionCamera; }
    const WeaponTrail& trail(int hand) const { return m_trails[static_cast<size_t>(hand)]; }

    // The swing this fighter WOULD start right now for the given situation — the same
    // resolution set_state(AttackA) performs at the press, without touching state. A COM
    // reads it to decide whether a press can connect (reach and startup), instead of
    // pressing and hoping. (gameplay/bot_brain.h.)
    MeleeSwing preview_melee_swing(bool dashAttack, bool aerial) const {
        return resolve_swing(resolve_attack_move(dashAttack, aerial));
    }
    // The horizontal distance at which that swing can connect: the recovered
    // `bodyRadius + radius` sphere (FUN_0063b470 via melee_rules.h), which
    // try_melee_hit() applies. Nothing else is a melee range in this port.
    float melee_reach(bool dashAttack, bool aerial) const {
        return m_meleeRules.bodyRadius + preview_melee_swing(dashAttack, aerial).radius;
    }

    // Swing bookkeeping driven by Match: begin clears the per-victim hit set, note
    // records that this swing already connected with one victim.
    void begin_melee_swing();
    void note_melee_hit(int victimIndex);

    // Debug view of the recovered melee hitbox (issue #10). Data only, so drawing stays
    // in the render layer: `anchors` are the victim's TWO spheres -- head and chest, the
    // Head and Spine bones FUN_0063dad0:238-243 builds -- and `attack*` is the attack
    // sphere FUN_0063b470 tests, present only while a swing is in its active window.
    // The same anchors and radius try_melee_hit() uses, so what this draws is what the
    // simulation actually tests rather than a second description of it.
    struct HitboxDebug {
        glm::vec3 anchors[2]{};
        float     anchorRadius = 0.f;
        bool      attacking    = false;
        glm::vec3 attackCenter{};
        glm::vec3 attackEnd{};
        bool      capsule = false;
        float     attackRadius = 0.f;
    };
    HitboxDebug hitbox_debug() const;

    // The victim's two hurtbox anchor OFFSETS from the fighter root, in model space,
    // as FUN_0063dad0:241-245 builds them:
    //   anchor0 = the Bip01_Head bone origin (transform of (0,0,0) by its frame)
    //   anchor1 = the Bip01_Spine bone with the local offset (-50.0, 0, 0)
    // Both are BONE positions, so they come from the rig's bind pose; a rig without
    // those bones falls back to fractions of kFighterHeight (see melee_rules.h). These
    // offsets are what the hit test AND the debug overlay both read, so they cannot
    // disagree.
    glm::vec3 hurtbox_anchor_offset(int index) const;

    // Aerial melee: the same melee control, played from the air with the aerial reach.
    void set_aerial_attack(bool aerial) { m_aerialAttack = aerial; }
    bool aerial_attack() const { return m_aerialAttack; }

    // --- getters ---
    const glm::vec3&   position()   const { return m_position; }
    float              facing_yaw() const { return m_facing; }
    int                hp()         const { return m_hp; }
    int                stamina()    const { return static_cast<int>(m_stamina); }
    FighterState       state()      const { return m_state; }
    bool               is_alive()   const { return m_hp > 0; }
    bool               airborne()   const { return !m_grounded; }
    const xm::Model*   model()      const { return m_model; }
    // Which set is bound right now, and whether it is the fallback. The index
    // comes from the bound move table's phase tag; -1 means nothing is bound.
    // anim_set_name() is the model's own set name ("Anim-124" at index 0 on a
    // shipped rig), or "" when none is bound.
    int                anim_set_index() const { return m_animSetIdx; }
    const char*        anim_set_name() const;
    // True when a state selector or table row is unresolved, or its set index
    // does not fit the model: the fighter then plays set 0. Exposed so the fallback
    // is not silent —
    // the trace wiring in main.cpp and tests/fighter_script_test.cpp read it.
    bool               anim_fallback() const { return m_animFallback; }
    // True when the state has no selector at all and the playing clip is held on
    // purpose (Guard; see state_has_animation_selector). Distinct from
    // anim_fallback(): holding a clip is the source behaviour, while a fallback is
    // a selector or table row this port has not recovered.
    bool               anim_no_selector() const { return m_animNoSelector; }
    // Fractional stocks feed the HUD bars directly (ammo-bar.webp).
    // Divide by the stock's OWN max, not the kMainMax/kChargeMax constants: a bound
    // weapon resizes both pools from data/item/NNN.dat, and the HUD bar is a fraction of
    // whatever the pool currently is. With no weapon max still equals the constant.
    float main_frac() const { return m_main.frac(); }
    float charge_frac() const { return m_charge.frac(); }
    int main_whole() const { return m_main.whole(); }
    int charge_whole() const { return m_charge.whole(); }
    // 0..1 across the full hold (red threshold = 1); colors the HUD meter.
    float charge_hold_frac() const;
    ShotTier charge_tier() const;
    bool reload_ok() const { return m_reloadTimer <= 0; }

    // For ArenaTarget compatibility.
    // (ArenaCamera reads position + facingYaw from ArenaTarget; the DX9
    // CameraTarget also carried `alive`, which render::ArenaTarget dropped —
    // callers read is_alive() / pose().alive instead.)
    void sync_target(render::ArenaTarget& target) const {
        target.position  = m_position;
        target.facingYaw = m_facing;
    }

private:
    // --- visual ---
    const xm::Model* m_model = nullptr;   // borrowed
    xm::Controller*  m_anim  = nullptr;   // borrowed; owns the playhead
    bool             m_animate = true;    // false = bind pose (see set_animate)

    // --- transform ---
    glm::vec3    m_position   {0, 0, 0};
    glm::vec3    m_safePosition{0, 0, 0};  // last stage-supported position for invalid-world recovery
    glm::vec3    m_velocity   {0, 0, 0};
    float        m_facing     = 0.0f;   // yaw (radians, around Y)

    // --- stats ---
    int          m_hp          = FighterConstants::kMaxHP;
    int          m_maxHP       = FighterConstants::kMaxHP;
    float        m_gaugeRate   = 1.f;
    CombatStats  m_stats;
    bool         m_guardExhausted = false;
    float        m_stamina     = static_cast<float>(FighterConstants::kMaxStamina);

    // --- KO / Overkill credit (issue #11) ---
    KoCredit m_koCredit{};
    bool     m_koPending = false;
    bool     m_swingStartedPending = false;
    bool     m_guardStartedPending = false;
    bool     m_hyperStartedPending = false;
    int      m_overkillHits = 0;
    // The per-life latch the shot path keeps at victim+0x84c (FUN_00637950 @0x638c81,
    // cleared by the respawn at FUN_004219a0 @0x421a08): the killing-blow reaction
    // bonus is once per life for shots. The melee path has no such test
    // (FUN_00639160 @0x6392e8-0x639325).
    bool     m_koBonusLatch = false;
    bool     m_respawnLock = false;
    // The victim's own reaction move as FUN_0063ba80's callers read it: this port's
    // Knockdown state is the original's grounded reaction (move 0xc4/196, sets
    // [28, 29] — the lying pose), and nothing else the port can enter is in the
    // exclusion set {198,199,196}. The Hit state is the launched reaction (195/0xc3),
    // which is not excluded.
    //
    // UNREACHABLE IN A LIVE MATCH: this is the ONLY reader that can yield
    // kReactionGrounded, and no production path enters Knockdown — take_damage() routes
    // every non-lethal stun to Hit and the lethal blow straight to KO, and the grounded
    // reaction is not among the selectors the port reproduces. The state and the 196 it
    // maps to stay because they pin recovered rows (state_to_move_id, the damagedown
    // label), and match_economy.h records the exclusion as modelled-but-unreachable
    // rather than silently dropping it. Do NOT "fix" this by routing a hit reaction here
    // without the recovered selector evidence.
    int reaction_move() const {
        return m_state == FighterState::Knockdown ? kReactionGrounded : 0;
    }

    // --- state machine ---
    FighterState m_state       = FighterState::Idle;
    int          m_stateTimer  = 0;    // frames remaining in current state
    int          m_animSetIdx  = -1;   // set bound for the current state (-1 = none)
    bool         m_animFallback = false;  // m_animSetIdx is the set-0 default
    bool         m_animNoSelector = false;  // state has no selector: the clip is held
    int          m_boundMoveId = -1;   // move whose phase bound m_animSetIdx (-1 = none)
    bool         m_jumpStartup = false;  // launch tick: the air chain plays row 40 first
    bool         m_animationBoundThisUpdate = false;
    int          m_blendTicks  = -1;   // source countdown; negative means no class blend
    int          m_blendTotal  = 0;    // destination set's +0x1c normalization value
    int          m_phaseIndex = 0;     // current section within the selected move
    int          m_moveElapsedTicks = 0;  // integer counter reset at each section bind
    // Per-swing hit accounting (issue #10): a bit per victim index, plus a count, both
    // cleared when the state changes so one swing can hit several opponents once each.
    unsigned     m_swingHits = 0;
    int          m_swingHitCount = 0;
    bool         m_chainContact = false;
    int          m_meleeElapsed = 0;      // ticks since the swing started
    MeleeRules   m_meleeRules{};           // legacy tuning + recovered shape;
                                           // data-driven swings override it via m_swing
    const CharacterMoves* m_moves = nullptr;  // borrowed move table (issue #26)
    int          m_attackMoveId = -1;       // move the current swing plays (-1 legacy)
    int          m_shotMoveId = -1;
    int          m_holdTicks = 0;
    bool         m_holdAnimation = false;
    // Attachment slots 0/1. The executor re-binds slot0<-prop0, slot1<-prop1 and
    // deactivates both at the top of every frame, so a slot is unbound only while a
    // Hide rule's ticks match (FUN_00434a70(slot,-1)) and a prop is active only inside
    // an Active window. Both slots can be bound/active at once, and the prop's active
    // latch is what grows its ribbon.
    std::array<bool, 2> m_propBound{true, true};
    std::array<bool, 2> m_propActive{false, false};
    int          m_actionCamera = 0;
    float        m_moveSpeed = 0.f;
    float        m_walkTurnRate = 20.f;
    float        m_inputFacing = 0.f;
    std::array<WeaponTrail, 2> m_trails;
    glm::vec2    m_previousWalkInput{0.f};
    int          m_dashMoveId = -1;         // inferred grounded dash candidate, or unresolved
    MeleeSwing   m_swing{};                 // this swing's resolved numbers
    bool         m_aerialAttack = false;   // this swing is the aerial variant

    // --- hypermode (spec §3.4; numbers in hypermode_params) ---
    Hypermode    m_hypermode    = Hypermode::Friendship;
    float        m_gauge        = 0.0f;   // 0..1; full = ready (S activates)
    bool         m_hyperActive  = false;
    float        m_hyperTimer   = 0.0f;   // seconds left while active
    int          m_hitsActive   = 0;      // hits taken since activation

    // --- shots (spec §3.1; costs/reload in projectile.h) ---
    //
    // PORT RULE, see weapon_definition.h: the magazine block this reads IS parsed by the
    // original (FUN_00433eb0:121-143) but no function in the corpus consumes it, so the
    // pool geometry below is the remake's design. Recovered per-weapon damage, hit radius,
    // hitstun and gauge gain arrive through m_bulletParams. Blob fields +0x64/+0x68 are
    // also decoded there, but their hit-resolution use does not establish shot-tier moves.
    const WeaponDefinition* m_weapon = nullptr;   // borrowed
    const BulletParameter*  m_bulletParams[2] = {nullptr, nullptr};  // per charge level
    AmmoStock    m_main;         // MAIN pool (charge level 1)
    AmmoStock    m_charge;       // CHARGE pool (charge level 2)
    float        m_chargeHeld = 0.0f;  // seconds C held (resets on release)
    int          m_reloadTimer = 0;    // reloadNG window (frames, 0 = reloadOK)
    PendingShot  m_pending;      // armed shot awaiting scene spawn
    std::array<PendingShot, 8> m_pendingShots{};
    int m_pendingShotCount = 0;
    std::array<const BulletParameter*, 64> m_bulletRows{};
    std::array<const xm::Model*, 64> m_bulletModels{};

    // --- air + dash (spec §3.2) ---
    float        m_vy = 0.0f;          // vertical velocity (u/s)
    bool         m_grounded = true;    // false between takeoff and landing
    float        m_groundY = 0.0f;      // takeoff height (flat-arena landing)
    float        m_flyLeft = FighterConstants::kFlyTimeSec;  // flight budget
    glm::vec3    m_dashDir{0, 0, 1};   // committed dash direction (world XZ)
    float        m_dashSpeed = FighterConstants::kRunSpeed;
    bool         m_dashAir = false;     // current dash started airborne
    bool         m_airDashed = false;   // air dash spent (resets on landing)
    double       m_time = 0.0;          // per-fighter clock (double-tap)
    double       m_lastTap[4] = {-1.0, -1.0, -1.0, -1.0};  // Up/Down/Left/Right

    // --- movement helpers ---
    // Screen (lock-on camera) direction → world direction. The eye sits behind
    // the facing looking at the locked opponent, so screen-up is the facing
    // (toward the opponent) and screen-right is 90° clockwise of it. Walk,
    // dash and air control all share this basis, so a tap and a hold never
    // disagree about where "up" goes.
    glm::vec3 facing_relative(float screenRight, float screenUp) const;
    void update_movement(const input::PlayerState* input, double dt);
    void update_state_machine(const input::PlayerState* input, Fighter* opponent,
                              double dt);
    void update_facing(const Fighter* opp, double dt);
    void try_switch_animation();
    void bind_animation_set(int setIndex);
    // One source countdown tick for the recovered Rena+2 blend callback.
    void tick_blend();
    // End-of-blend commit restores the controller's both-tracks steady state.
    void commit_blend();
    // Unbind every track (bind pose). Round resets and animation-off share
    // it: both need "no set bound", and only try_switch_animation may bind.
    void clear_tracks();

    // Check if the current state allows movement (not attacking/stunned).
    bool can_act() const;
    bool can_move() const;

    // C-release firing: picks the tier from hold time, then fire_shot().
    void try_fire();

    // (Re)builds m_main/m_charge from m_weapon, or restores the historical fractional
    // stocks when no weapon is bound. Called on bind and on reset.
    void apply_weapon_ammo();

    // Spends the tier's stock, opens the reloadNG window, and arms
    // m_pending for the scene. Silently drops when reloading or broke (the
    // HUD already shows the gate).
    void fire_shot(ShotTier tier);

    // Hypermode plumbing: gauge credit, S activation (with Oyashiro's
    // no-damage knockback burst), the EX move, and the Kakera death save.
    void gain_gauge(float fraction);
    bool try_activate_hypermode(Fighter* opponent);
    void try_ex_move();
    void update_hypermode(double dt);

    // Z leap (grounded only) and double-tap dash setup. try_dash maps the
    // tapped key to a facing-relative dash (Up = forward ...) and returns
    // false when the stamina gate or the once-per-airtime rule blocks it.
    void try_jump();
    bool try_dash(input::Action dir);
    // Slot7 jump-cancel for shot states, evaluated outside the actionable gate (the
    // normal state machine never runs mid-shot): true only for a recovered admission
    // — pilot combo Rena 0 out of shot move 400 at elapsed frame 20
    // (kPilotShotJumpCancel). Everything else keeps today's behavior.
    bool shot_jump_cancel_pressed(const input::PlayerState* input) const;

    // Knocks the target away without damage (Oyashiro activation). Reuses
    // the Hit state's friction branch to carry the push; the real knockback
    // animation state is un-RE'd.
    void apply_knockback(const glm::vec3& dir, float speed);

    // Current move choice for combat tuning. Its port-context heuristic does not
    // establish an animation selector; animation resolution uses the separate
    // confirmed ID below.
    // Situation → character-.dat move id for a melee press (issue #26 step 3),
    // or -1 when no table is bound or the situation's move is absent. The map
    // is provisional: FUN_0043ded0 gates several attack moves per situation on
    // unrecovered flags, so each row is the best-evidenced candidate —
    //   dash (press while Run) → 330, the lunge ("dash forward + attack", nata)
    //   air                     → 340, the single-phase weapon aerial ([88])
    //   ground                  → 300, the ground neutral (first phase 31)
    // — with 320 (ground branch at FUN_0043ded0:311, frame-1 startup) on record
    // as the alternative for ground/air, and the kicks (310/311) unused for lack
    // of a recovered selection rule. A costume that drops the row's move falls
    // through to any weapon-family move present rather than the jump clip.
    int resolve_attack_move(bool dashAttack, bool aerial) const;
    // The resolved numbers for one move id: the move's first combat entry, or the
    // legacy tuning when there is no table, no move, or no combat entry. Shared by
    // build_melee_swing() (which binds it) and preview_melee_swing() (which does not).
    MeleeSwing resolve_swing(int moveId) const;
    // Fills m_swing from the move's first combat entry (or the legacy tuning
    // when there is no table, no move, or no combat entry).
    void build_melee_swing(int moveId);
    // A move counts when the table ships it with at least one phase (a costume
    // that drops the move must not resolve to a phaseless id).
    int present_move(int id) const;
    // Facing-relative forward/back (moves 20/27 in FUN_00438310). Side-dash
    // move order has no recovered link to the port's left/right inputs.
    int dash_move_for(input::Action dir) const;
    // The move whose phases the current state plays, or -1 if its selector is
    // not recovered. Grounded neutral 300, the dash lunge 330 and the aerial 340
    // are all bound rows now (issue #31); Jump resolves the recovered air chain.
    int state_move_id() const;
    // The jump chain the source advances by physics (live FUN_0043ffc0 cases
    // 0x28/0x29/0x2a): 40 on the ground, 41 while rising, 42 once vy falls under
    // the apex literal. Each row's first phase tag is the jump clip.
    int jump_chain_move() const;
    // A state can change its move without changing its port label (only the air
    // chain does today). The source rebinds through FUN_00421080 whenever the
    // move id changes, so re-check the binding once per update.
    void refresh_state_move();
    // Mirrors the source handler tail: elapsed move ticks advance once per update,
    // and the NN.dat set gate controls whether the current phase advances.
    void advance_animation_phase();
    glm::vec3 bone_point(const std::string& name, const glm::vec3& local) const;
    void execute_move_program(Fighter* opponent, const input::PlayerState* input);
    void enter_phase(int phase);
    void launch_bullet(int row, float lateral, float pitchLimit, Fighter* opponent);

    // Shared pulse for the aura's alpha + radius (DX9 render did both from one
    // expression; kept single-sourced so they cannot drift).
    float hyper_pulse() const;
};

}  // namespace gameplay

// =============================================================================
//  PORT NOTES — every deviation from remake/src/gameplay/fighter.h:
//
//  1. Namespace: daybreak::gameplay → gameplay (only the daybreak:: prefix is
//     dropped, so a line-by-line diff against the source stays possible).
//  2. Input: const daybreak::input::PlayerInput* → const fnd::input::PlayerState*
//     through the `input` alias above. The 13 Action indices and every field
//     used here (down / just_pressed / stick_x / stick_y) are identical in both
//     headers; the port report carries the field-by-field check.
//  3. Model/animation: XModel* m_model (which owned mesh + ID3DXAnimationController)
//     → const xm::Model* m_model + xm::Controller* m_anim, both borrowed, bound
//     through bind()/init(). try_switch_animation() resolves the selected move's
//     first phase through the bound NN.dat and falls back to set 0 when the move
//     selector or row is unknown, or the model lacks the named set.
//  4. render(IDirect3DDevice9*) is deleted, not ported. Its three products are
//     now data: modelMatrix() (the world matrix), pose() (camera/pose lookup)
//     and the aura accessors (colour/radius/centre, in model space). The
//     DX9 cube pass itself belongs to render/debug_prims.h, which the parent
//     wires.
//  5. sync_target(daybreak::CameraTarget&) → sync_target(render::ArenaTarget&);
//     the DX9 struct's `alive` field has no counterpart there (pose().alive).
//  6. D3DCOLOR → gameplay::Rgb (same 0xAARRGGBB bits; see gameplay/projectile.h).
//  7. The DX9 build's std::printf transition log is dropped: the simulation is
//     required to be a pure function of (state, input, dt), and the parent's
//     A/B comparison reads state traces, not stdout. No logic depends on it.
//  8. Guard release/exhaustion bypass the action-entry gate; an exhausted hold
//     requires release before re-entry (issue #6). The historical one-way
//     DX9 state is not a live rule. Damage reduction remains provisional.
//  9. Remaining behavior retains the update() ordering, the
//     integer/float mix of every timer, the double-tap window, the melee
//     active-window rule and the hypermode arithmetic.
// =============================================================================
