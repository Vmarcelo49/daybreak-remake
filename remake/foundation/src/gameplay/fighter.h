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
//    AttackA                       (one melee input; bounded 300/311/330 selector
//                                   candidates resolve through the equipped NN.dat)
//    ShootA/B/C                    (port charge tiers; firing animation selector unresolved)
//    Jump / Guard                  (port states with unresolved animation selectors)
//    Any → Hit / Knockdown / KO    (reaction selectors recovered from move dispatch)
//    BattleStart → Idle            (round reset move selector recovered)
// =============================================================================
#pragma once

#include <algorithm>
#include <array>
#include <cstdint>
#include <string>

#include "assets/xmodel.h"          // xm::Model / xm::Controller (non-owning)
#include "game/battle_view.h"
#include "game/fighter_pose.h"      // game::IFighterPose / game::FighterPose
#include "gameplay/character_moves.h"  // CharacterMoves (borrowed move table)
#include "gameplay/melee_admission.h"   // recovered attack admission tables
#include "gameplay/match_economy.h"    // the KO/Overkill credit rules (issue #11)
#include "gameplay/projectile.h"
#include "gameplay/simulation_rng.h"
#include "gameplay/shot_launch.h"
#include "gameplay/melee_rules.h"
#include "gameplay/weapon_trail.h"
#include "gameplay/weapon_definition.h"
#include "gameplay/shooting_magazine.h"
#include <vector>
#include "input/input.h"
#include "render/arena_camera.h"    // for render::ArenaTarget

namespace gameplay {

using game::CombatStats;
using game::FighterState;
using game::Hypermode;
using game::state_to_anim_name;

// The foundation's device-free input model has the same 13-action layout as the
// DX9 build's input/input_manager.h (verified field-by-field in the port
// report), so the alias lets every `input::Action` / `input::PlayerState` use
// below read exactly like the source's `input::Action` / `input::PlayerInput`.
namespace input = fnd::input;

// Everything FUN_00637950 hands the victim on a landed hit. The two row words select the
// reaction the victim plays: `row` (record +0x64 = combat[13]) normally, `rowHigh`
// (+0x68 = combat[14]) once the victim's own +0x7c0 has reached 100 — the escalation ladder,
// which is why the same swing looks different late in a combo. `meterA`/`meterB` are the
// record's combat[7]/[8], accumulated into the victim's +0x7b8/+0x7c0; the +0x7b8 stagger
// meter (threshold 100) is what decides whether ANY reaction happens at all.
struct HitReaction {
    int   row = 0;
    int   rowHigh = 0;
    float counter = 0.f;   // combat[17] * 0.01 -> +0x40
    float rise = 0.f;      // combat[18] * 0.01 -> +0x54
    int   meterA = 0;      // combat[7]  -> +0x7b8
    int   meterB = 0;      // combat[8]  -> +0x7c0
    // Record state flags (FUN_00637950 reads +0x28): bit 0x800 selects the 121
    // ground roll and scales the blow to 70%.
    int   flags = 0;
};

// Fighter states are port labels. The executable stores move IDs directly in
// `[player+0xadec]`; only recovered port-state selectors map to those IDs.

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
//   (|bearing - facing| <= 45 || (victimword & 0x2000)) && (victimword & 0x400)
//   && !(attackerword & 8)
// Polarity note (2026-10-16, P2-7 guard work): this read `> 45` until then. Both the
// decompiled `else` — the very branch this note describes — and the bundle's
// `battle_hit_guard.hpp` require the impact to be WITHIN 45 degrees of the victim's facing;
// `> 45` describes the damage branch, so the earlier wording would have inverted the guard.
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

// The executable's own mode numbering (+0x318) runs the other way round:
// Oyashiro 0, Friendship 1, Kakera 2. Established across five independent
// sites (issue #71): the S-press move branch (+0x318==0 starts move 500/501),
// the red flash's +0x844 arm, the HUD caption rows (0 OYASHIRO), the aura
// models (0/1/5), and the victim-side gauge feed for value 0 (param_3 takes
// the HP in FUN_00637950, so value 0 fills by taking damage). The port enum
// above is the UI order and stays; every site that branches on the wire value
// translates through here instead of re-deriving it.
inline int hypermode_wire_value(Hypermode m) {
    switch (m) {
        case Hypermode::Oyashiro:   return 0;
        case Hypermode::Friendship: return 1;
        case Hypermode::Kakera:     return 2;
    }
    return 1;
}

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
    static constexpr float kRunSpeed      = 900.0f;  // 15.0/tick, the modal dash; the
                                                     // pilot side steps use the recovered
                                                     // per-update profile instead
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
    // The BODY-CENTRE distance at which this swing could connect, derived from the record's
    // own volume: the horizontal extent of its anchor (and end anchor, for a capsule) under
    // its bone at the current pose, plus the sphere radii the hit test adds. The bot used to
    // press at `bodyRadius + radius`, which ignores both where the volume sits and how long
    // the blade is — see V3-46.
    float       reach = kLegacyRadius;
    bool        reachKnown = false;
    int         damage = FighterConstants::kLightDamage;
    int         hitstun = 8;              // legacy active-window stun
    int total_ticks() const { return window.total_ticks(); }
    bool is_active(int elapsed) const { return window.is_active(elapsed); }
    bool is_recovery(int elapsed) const { return window.is_recovery(elapsed); }
};

// Handoff from the move callback to the scene's spawn/collide step. Twin callback
// requests remain separate entries and the scene drains them in request order.
struct PendingShot {
    bool          armed = false;
    ShotTier      tier  = ShotTier::Tap;
    glm::vec3     pos   {};
    glm::vec3     dir   {0, 0, 1};
    int           bulletRow = -1;
    Fighter*      target = nullptr;
    ShotOriginSpec origin{};
    ShotAimSpec   aim{};
};

// The per-tick world state a shooting body reads from outside the fighter. The
// original reads these straight off the player struct, so the scene publishes them
// instead of the fighter duplicating (or guessing) them. Currently carries the one
// recovered firing predicate; target geometry and the simulation RNG join it as their
// users land.
struct ShootingContext {
    // word +0x848 != 0: the 180-tick hold target_lock.h re-pins while this fighter's
    // aim target is the same fighter player 0 is aiming at (FUN_0041f580:242-248).
    // Together with the Oyashiro special byte +0x845 it forms the roster-wide powered
    // gate. This is the aim-selection predicate, not the combat lock's ally hold.
    bool aimHold = false;
    // The RECOVERED direction decision of an AI-controlled fighter: word +0x278, which
    // Rika 2's tap reads to pick its item row and Irie 1's state 401 reads (with +0x27c)
    // to pick its follow-up state. Only the COM decision routines write it
    // (FUN_0043f4d0/FUN_00447730 — a wander timer driving +-1/0), so it is 0 for every
    // human-controlled fighter, and the port publishes it only for AI slots. The port
    // expresses the brain's intent through the four direction keys, so this is the sign of
    // that applied lateral input.
    int moveLateral = 0;   // -1 left, 0 neutral, +1 right
    // The match's shared random stream. The original draws spread from ONE global
    // MT19937, so the scene owns the stream and publishes it here; a fighter without a
    // scene (unit tests) falls back to its own, which keeps both paths deterministic.
    SimulationRng* rng = nullptr;
    // The close-target voice cascade's three latches (+0xaec3/+0xaebe/+0xaeb9),
    // recomputed each tick by FUN_0042e110 for every actor IMMEDIATELY BEFORE its
    // state dispatch (FUN_00634f60's per-fighter loop runs FUN_0042e110, then the
    // vtable+0x24 handler), so the state they read is the PREVIOUS tick's. Match fills
    // them from its own attention table; a fighter without a match keeps all zero,
    // which is the cascade's ordinary-voice arm. melee_admission.h resolves them.
    struct VoiceFlags {
        unsigned char flags[3] = {0, 0, 0};  // +0xaec3, +0xaebe, +0xaeb9
        bool addAttack() const { return flags[0] != 0; }
        bool intercept() const { return flags[1] != 0; }
        bool backAttack() const { return flags[2] != 0; }
    } voice;
};

// move_behavior.h's executable rule, forward-declared so the gate evaluation beside
// execute_move_program can name it without pulling the tables into this header (the
// same reason m_holdRule is type-erased).
struct MoveRule;


class Fighter : public game::FighterView {
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
    glm::mat4 modelMatrix() const override;

    // game::IFighterPose: position / facing / animation time / alive, for the
    // camera lock-on and the renderer's pose lookup.
    game::FighterPose pose() const override;

    // Hypermode aura (the DX9 render's second, additive cube pass): drawn in
    // the model's own space at aura_center_local(), sized aura_radius(), in
    // aura_color() (mode colour, alpha pulsed by the fighter clock).
    bool      aura_active() const override { return m_hyperActive; }
    glm::vec3 aura_center_local() const override { return glm::vec3(0.0f, 58.0f, 0.0f); }
    float     aura_radius() const override;
    Rgb       aura_color() const override;

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
    // `hitstunFrames` is the victim's hitstop (+0xa0), not reaction length:
    // FUN_00637950:308 reads combat[10] at record+0x58. The legacy timed
    // fallback for a missing playable reaction row is separate.
    // `hitCategory` is the RAW record +0x64 dword the original feeds FUN_0063ba80
    // (@0x638c26) to pick the victim's reaction move; 0 is "unspecified", which takes
    // that function's default branch (198, the downed reaction) exactly as any
    // unmatched value does. `shot` marks projectile damage, whose increment formula and
    // already-down credit differ from melee's (see match_economy.h).
    DamageResult take_damage(int amount, Fighter* source = nullptr, int hitstunFrames = -1,
                             int hitCategory = 0, bool shot = false,
                             const HitReaction& reaction = HitReaction());
    // The row the current reaction plays (a test seam: the row is otherwise internal).
    int reaction_move_for_test() const { return m_reactionMove; }
    int down_row_for_test() const { return m_downRow; }
    // +0x7c0: the down/knockdown accumulator (combat[8]); the tech roll clears it.
    int down_meter_for_test() const { return m_hitMeterB; }
    // +0x7ac: the get-up invincibility timer. > 0 means the shared hit resolver
    // (FUN_00637950's `+0x7ac < 1` test) must skip this fighter.
    int invincible_ticks() const { return m_invincible; }
    // FUN_00637950 writes hit-driven status durations at actor+0x7dc+slot*4;
    // Rena recovery reads slot 6 at actor+0x7f4. The match ticks durations after
    // the fighter executor, preserving the source's same-frame read-before-decrement.
    void apply_hit_status(unsigned slot, int duration, int power);
    void tick_hit_status();
    int hit_status_duration(unsigned slot) const;
    void set_state(FighterState new_state);

    // Body separation (FUN_006394c0): displace this fighter horizontally by `delta`, clamped
    // by the stage exactly as ordinary movement is, because the recovered function applies each
    // half through the horizontal mover (FUN_0042cb50) rather than writing the position.
    void shove(const glm::vec3& delta, const game::physics::MovementCollision* collision);

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
    // P2-7 (2e) slice 2 — the pilot's locomotion policy. The legacy default attaches none and
    // is byte-for-byte unchanged. With --native-actions=rena0 the recovered Rena+0 locomotion
    // body answers the two locomotion questions the seam marks as its own (PILOT-SEAM §16):
    // the Idle/Walk proposal and the walk speed. The turn step and the phase clock stay with
    // the port, which already encodes the same recovered rule and clock convention — driving
    // them would add a second implementation of identical behaviour, not a recovered one.
    //
    // Live implementations are owned by the pilot (src/gameplay/native/rena0_pilot_adapter.h)
    // and must be attached only for the pilot fighter; a value < 0 keeps the legacy answer.
    struct PilotLocomotion {
        virtual ~PilotLocomotion() = default;
        // 0 idle, 10 walk, 43 airborne (the recovered body's state numbers), or -1 to keep
        // the legacy decision.
        virtual int proposed_state(const Fighter& f) const = 0;
        // Walk speed in units per tick, or < 0 to keep the legacy value.
        virtual float walk_speed_per_tick(const Fighter& f) const = 0;
    };
    void set_pilot_locomotion(const PilotLocomotion* policy) { m_pilotLocomotion = policy; }
    const PilotLocomotion* pilot_locomotion() const { return m_pilotLocomotion; }

    // P2-7 (2e) — the pilot's guard policy, attached to the VICTIM. It answers the recovered
    // predicate above; when it says a hit is guarded, the hit applies no damage and no stun,
    // which is what `FUN_00637950`'s guarded branch does (it writes the contact word, the
    // per-slot marker and [victim+0xaf30] and calls no damage helper). The legacy default
    // attaches none and keeps its own provisional 20% rule.
    // P2-7 (2e) charge family: the two charge bases a landed melee hit carries. They are the
    // hit record's combat[5]/[6] columns — the ones the port's own damage-path note identifies
    // as the feeds for the original's mode gauges (+0x838/+0x840/+0x83C at FUN_00637950's sites
    // 0x638321/0x6383e6/0x638493) and deliberately leaves unread because `gain_gauge` feeds the
    // hypermode bar instead. The record parser's `hpDamage`/`reflectDamage` aliases ARE these
    // columns; the names are historical and the pilot reads them under their recovered role.
    struct MeleeChargeBases {
        int victim = 0;    // combat[5], the victim-side (mode 0/2) base
        int attacker = 0;  // combat[6], the attacker-side (mode 1) base
    };
    const MeleeChargeBases& melee_charge_bases() const { return m_meleeChargeBases; }

    // P2-7 (2e) shot family: the recovered shot body clears both held item-model slots on every
    // frame after its frame 11 (`battle_rena_ground_shot.hpp:37`), and this port re-derives the
    // slots every tick from the move's trail binding (fighter.cpp:1898-1903), so the clear has
    // to be part of that derivation rather than a write to the array. The pilot drives it from
    // the fire event; the default path has no policy and keeps the derived binding.
    // P2-7 (2e) guard family: the guard state binds no clip or phase in this port
    // (`state_move_id()` returns -1 for Guard, and its own note records why), so the live frame
    // record the recovered guard predicate reads does not exist while a human fighter guards.
    // The pilot supplies it from the recovered guard row instead: the row's guard-capable
    // record (stateFlags 0x400), which is what the predicate's victim word carries.
    struct PilotGuardMotion {
        virtual ~PilotGuardMotion() = default;
        virtual const MoveEntry* guard_record() const { return nullptr; }
    };
    void set_pilot_guard_motion(const PilotGuardMotion* motion) { m_pilotGuardMotion = motion; }
    const PilotGuardMotion* pilot_guard_motion() const { return m_pilotGuardMotion; }

    struct PilotShot {
        virtual ~PilotShot() = default;
        virtual bool clears_item_models() const { return false; }
        // The recovered empty-magazine tap: the adapted slot-7 body's release branch
        // (`0 < released < 20 && primary rounds == 0`) requests ONE voice and increments the
        // empty-shot statistic, and never requests a shot row — it is inside the wrapper whose
        // `+0x834 < 1` term excludes the ordinary admission (PILOT-SEAM.md §26). The port's own
        // `can_fire` returns before any voice is queued, so the pilot answers the voice half on
        // the same per-tick cue the host already drains. < 0 is "no opinion"; the unowned
        // statistic is NOT published through a new Fighter field.
        virtual int empty_shot_voice() const { return -1; }
    };
    void set_pilot_shot(const PilotShot* shot) { m_pilotShot = shot; }
    const PilotShot* pilot_shot() const { return m_pilotShot; }

    struct PilotGuard {
        virtual ~PilotGuard() = default;
        virtual bool guards_hit(const Fighter& victim, const Fighter& attacker) const = 0;
    };
    void set_pilot_guard(const PilotGuard* policy) { m_pilotGuard = policy; }
    const PilotGuard* pilot_guard() const { return m_pilotGuard; }

    // P2-7 meter family: the unified action meter (+0x834, 0..1000). Attached by the
    // pilot flag for Rena+0 (and by the acceptance runner for its fixtures); a null
    // policy keeps the legacy m_stamina/m_chargeGauge pair exactly as it was. The meter
    // carries the recovered integer rates — dash -12/tick (air dash 30: -11; the -3
    // inner arm is a named limit), guard -10/tick, jump launch/landing +40, hover
    // -10, recovery +40/+5 clamped at 1000, mode-2 +1/tick — with no passive refill
    // and no launch spend (FUN_0041f580's only unconditional +1 is behind the mode-2
    // special flag; every other refill rides a body row). The Kakera gate at the
    // refill site names its mapping limit.
    struct PilotMeter {
        virtual ~PilotMeter() = default;
    };
    void set_pilot_meter(const PilotMeter* meter) { m_pilotMeter = meter; }
    const PilotMeter* pilot_meter() const { return m_pilotMeter; }

    void set_moves(const CharacterMoves* moves);
    const CharacterMoves* moves() const override { return m_moves; }
    // The character-.dat move currently used for melee tuning. Exposed for
    // combo-bound evidence checks.
    int attack_move_id() const override { return m_attackMoveId; }
    // The numeric action row this fighter is in, as the original's dispatcher reads
    // it (+0xadec): an attack row during AttackA, a dash row during Run, the air-dash
    // row 30 or the jump chain airborne, and 10/0 for locomotion. Match reads it for
    // the close-target voice cascade's state-class tests, which sample it BEFORE the
    // fighter updates — so it is the previous tick's row at that point.
    int action_state() const { return numeric_state(); }
    // Non-zero while the fighter is playing the landing row (44) instead of Idle's own: the
    // original's state 44 is a row, not a flavour of Idle, so this is what tells a reader that
    // the Idle *state* is in its landing window.
    int landing_ticks() const { return m_landingTicks; }
    int bound_move_id() const { return m_boundMoveId; }
    bool air_dash_context() const { return m_dashAir; }
    // NN.dat move selected for a grounded directional dash, or -1 when the
    // combo has no row or the dash is airborne.
    int dash_move_id() const { return m_dashMoveId; }
    input::Action dash_input_direction() const { return m_dashInputDirection; }
    // Firing move the current shot plays, keyed off the charge tier and whether the
    // fighter was airborne at the release (move_behavior.h's MoveProgram::shot).
    int shot_move_id() const override { return m_shotMoveId; }

    // ---- selected weapon (gameplay/weapon_definition.h, issue #9) ----
    // Binds the parsed data/item/NNN.dat for the selected weapon. Borrowed, like the
    // model; null keeps the historical shared tuning, which is what the standalone
    // --match trace path passes. A non-null weapon sizes this fighter's magazines and
    // charge thresholds from the file instead of the shared 6/2 constants.
    void set_weapon(const WeaponDefinition* weapon);
    const WeaponDefinition* weapon() const override { return m_weapon; }

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
    ShotTier last_shot_tier() const override { return m_pending.tier; }

    // The recovered charge thresholds in SECONDS. FUN_00433eb0's per-magazine
    // chargeMax is a tick count (the shipped values run 60..1200, and 180 is the same
    // 0xb4 the ally hold is written with), converted through the fixed tick. PORT RULE:
    // the original's charge is a 100-point gauge with a 120-frame decay window, not a
    // hold timer, so this conversion is a design choice, not recovered behaviour.
    float yellow_hold_sec() const;
    float red_hold_sec() const;

    // The fighter-level special/charge gauge (+0x834, 0..1000). The original writes it
    // from battle init, the hyper regen, the recoveries and the special spend; this
    // setter is the test seam for the admission/guard gates that read it. On the pilot
    // path it doubles as the unified-meter injector: admission and recovery tests set
    // the meter through the same call.
    void set_charge_gauge(int value) {
        m_chargeGauge = std::clamp(value, 0, 1000);
        if (m_pilotMeter) m_actionMeter = m_chargeGauge;
    }

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
        restore_ammo();
        set_hyper_gauge(1.0f);
    }
    int max_hp() const override { return m_maxHP; }
    const CombatStats& stats() const override { return m_stats; }
    void clear_stats() { m_stats = {}; }
    Hypermode hypermode() const override { return m_hypermode; }
    bool  hyper_active() const override { return m_hyperActive; }
    bool  hyper_ready() const override { return m_gauge >= 1.0f && !m_hyperActive; }
    float hyper_gauge() const override { return m_gauge; }
    float hyper_seconds_left() const override { return m_hyperTimer; }

    // Scene drains the shot armed by C-release into the ProjectilePool.
    // Disarms on read (at most one pending shot ever queues).
    PendingShot take_pending_shot();
    struct ShootingVoice { int event = -1; int alternative = -1; };
    ShootingVoice take_shooting_voice() { auto cue = m_shootingVoice; m_shootingVoice = {}; return cue; }
    bool source_shot_voice_audited() const { return m_sourceShotVoiceAudited; }
    // True when the running row carries a recovered melee voice cue, so the audio layer
    // can let the source-timed cue stand alone instead of also firing the fallback swing
    // voice (the melee ids ARE the voice vocabulary's indices: FUN_004223d0(1,10,0) =
    // "attackA", FUN_004223d0(0xd,10,0) = "guarded", FUN_00422490(0x20,...) = "specialA").
    bool source_melee_voice_audited() const { return m_sourceMeleeVoiceAudited; }

    // The melee voice cue (FUN_004223d0/FUN_00422490), the gameplay SE cue
    // (FUN_0042c8b0 positional / FUN_0042c880 non-positional) and the actor effect cue
    // (`(*actor+0xc)` = FUN_00421aa0 -> FUN_00435990's manager create with a pose),
    // drained once per tick by the scene the same way the shot voice is. The melee
    // alternative carries the FUN_00422490 choice (fixed, or the rand%100 pair the
    // 32-family draws); the close-target cascade (voices 0/15/5) is documented at the op
    // site as requiring the pairing tracker the port does not model. The SE `id` is a
    // data/se/%03d.wav index and the effect `id` a data/effect id (`id / 10` names the
    // descriptor) — two different call paths, kept apart so neither consumer can read
    // the other's ids.
    struct MeleeVoiceCue { int event = -1; int alternative = -1; };
    MeleeVoiceCue take_melee_voice() { auto cue = m_meleeVoice; m_meleeVoice = {}; return cue; }
    struct SoundEffectCue {
        int id = -1;
        bool positional = false;
        glm::vec3 position{0.f};
    };
    SoundEffectCue take_sound_effect() {
        auto cue = m_pendingSoundEffect;
        m_pendingSoundEffect = {};
        return cue;
    }
    // The pose the body passed: heading is added to the actor's own, pitch is absolute.
    struct EffectCue { int id = -1; float yaw = 0.f; float pitch = 0.f; };
    EffectCue take_effect() { auto cue = m_pendingEffect; m_pendingEffect = {}; return cue; }

    // The original's fighter-level special/charge gauge (int +0x834, 0..1000). The
    // bodies spell it `param_1[0x20d]` because the actor pointer is `int*`; the two
    // spellings are the same field, confirmed by the whole-corpus scan (every
    // `[0x20d]` site declares `int *param_1`). Producers: battle init/reset writes
    // 1000 (FUN_004219a0:19, FUN_0041dcb0:66); +1 a tick only while a hyper flag
    // (+0x844/0x845/0x846) is armed (FUN_0041f580:96-99 and 46 siblings — not modeled
    // here, recorded); Rena recoveries refill +40 when actor status slot 6 at +0x7f4 is
    // clear and +5 while it is active. FUN_00637950 is the generic projectile-hit producer
    // (attackFlags bit 0x1000, duration/power from the contact record); this port carries
    // that path. The scanned shipped Rena actor/projectile DATs have no bit-0x1000 contacts,
    // so natural Rena recovery reachability remains unproven. Scene+0x7f4 is a different field.
    // The gauge loses 500 on a special-move spend (FUN_00508a60:91). Consumers:
    // the melee/shot admission gates (`0 < +0x834`, FUN_00445ee0/FUN_0044d850), the
    // guard-reaction exits (`(FUN_0042c7b0() & 2) && 0 < +0x834`, the 390/393 bodies)
    // and the awakened-melee spend threshold (`500 < +0x834`). This is NOT the
    // item-data magazine: the rounds-counted 0x44-byte magazine (FUN_00433eb0) is a
    // separate per-request cost the launch path already pays.
    int  charge_gauge() const override { return m_pilotMeter ? m_actionMeter : m_chargeGauge; }

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
    int phase_elapsed() const override { return m_moveElapsedTicks; }
    int move_counter() const { return m_moveCounter; }
    // The horizontal per-tick channel the movement rules/bodies drive (u/tick).
    float move_speed() const { return m_moveSpeed; }
    // The recovered attack-body state, for execution witnesses: the bodies' fall
    // rate (u/tick^2, -1 = unowned), FUN_00420b30's lean pair and the dive's contact
    // cut. +0x2c is a PITCH in degrees (applied as a RotationX) and +0x2d8 a pivot
    // HEIGHT (the model's Y rotation center) — not two yaw terms.
    float attack_gravity() const { return m_attackGravity; }
    float body_pitch() const { return m_bodyPitch; }
    float body_pivot_height() const { return m_bodyPivotHeight; }
    int chase_strength() const { return m_chaseStrength; }
    bool contact_disabled() const { return m_contactDisabled; }
    // The original's `byte(+0x845) != 0 && word(+0x848) != 0`, read by 514 of the 841
    // recovered shoot bodies and by every other action family. +0x845 is the Oyashiro
    // special armed byte (FUN_004220e0 sets it, FUN_0041f580:88-92 clears it when its
    // countdown ends) and +0x848 is the aim hold the scene publishes (same aim target
    // as player 0). A fighter running Friendship or Kakera never takes a powered
    // branch, which is source behavior and not a gap.
    bool shoot_gate_powered() const {
        return m_hyperActive && m_hypermode == Hypermode::Oyashiro && m_shooting.aimHold;
    }
    // The scene publishes the per-tick firing context before update().
    void set_shooting_context(const ShootingContext& context) {
        m_shooting = context;
        m_rng = context.rng;
    }
    // FUN_00435000 launches from the bound slot's item muzzle anchor and falls back to
    // the bone origin only when the slot's prop id is -1 (FUN_00434a70's clear).
    bool weapon_slot_bound(int slot) const;
    int action_camera() const override { return m_actionCamera; }
    const WeaponTrail& trail(int hand) const override { return m_trails[static_cast<size_t>(hand)]; }
    // P2-7 (2e) shot family: the recovered shot body clears both held item-model slots at its
    // frame 12 (`battle_rena_ground_shot.hpp:37`), and this port's consumer already reads a
    // negative model as "no prop in that slot" (fighter.cpp:751-755). The pilot drives the
    // clear behind the flag from the fire event, which is the same frame the body clears on.
    void set_item_model_slot(int slot, int model) {
        if (slot >= 0 && slot < 2) m_trailItemModel[static_cast<size_t>(slot)] = model;
    }
    int trail_item_model(int hand) const override {
        return hand >= 0 && hand < static_cast<int>(m_trailItemModel.size())
                   ? m_trailItemModel[static_cast<size_t>(hand)] : -1;
    }
    // FUN_00434a70's per-slot item-model binding decides which of the item's attachment
    // models is on screen, so one canonical item model (`model`, the index the DAT ships)
    // is drawn exactly when a bound prop slot names it. The render gate and the tests
    // share this predicate: a correct launch origin alone does not prove the visible
    // weapon is right (Rena 1's 450/460 move slot 0 from model 0 = 11.x to model 2 = 12.x).
    bool draws_item_model(int model) const override {
        for (int slot = 0; slot < 2; ++slot)
            if (weapon_slot_bound(slot) && trail_item_model(slot) == model) return true;
        return false;
    }

    // The swing this fighter WOULD start right now for the given situation — the same
    // resolution set_state(AttackA) performs at the press, without touching state. A COM
    // reads it to decide whether a press can connect (reach and startup), instead of
    // pressing and hoping. (gameplay/bot_brain.h.)
    MeleeSwing preview_melee_swing(bool dashAttack, bool aerial) const {
        return resolve_swing(resolve_attack_move(dashAttack, aerial));
    }
    // The horizontal distance at which that swing can connect. try_melee_hit() tests the
    // record's volume against the VICTIM's head/chest spheres, so the conversion to a
    // body-centre gate needs the volume's own reach (resolve_swing derives it from the
    // record's anchor, end anchor and bone) plus the two radii. The previous form,
    // `bodyRadius + radius`, assumed the volume sat on the body centre and had no length,
    // which put the gate below the 60-unit body separation a COM can never pass (measured:
    // zero presses in 8000 ticks, and 14 presses with no hits once the separation was on).
    float melee_reach(bool dashAttack, bool aerial) const {
        const MeleeSwing swing = preview_melee_swing(dashAttack, aerial);
        if (swing.reachKnown) return swing.reach;
        return m_meleeRules.bodyRadius + swing.radius;   // no record: the legacy sphere
    }

    // Swing bookkeeping driven by Match: begin clears the per-victim hit set, note
    // records that this swing already connected with one victim. `guarded` carries
    // FUN_0042c7b0()'s bit 2 — the strike met a guarding opponent — which the melee
    // bodies read to hand the attacker to the 392 knockback.
    void begin_melee_swing();
    void note_melee_hit(int victimIndex, bool guarded = false);

    // Debug view of the recovered melee hitbox (issue #10). Data only, so drawing stays
    // in the render layer: `anchors` are the victim's TWO spheres -- head and chest, the
    // Head and Spine bones FUN_0063dad0:238-243 builds -- and `attack*` is the attack
    // sphere FUN_0063b470 tests, present only while a swing is in its active window.
    // The same anchors and radius try_melee_hit() uses, so what this draws is what the
    // simulation actually tests rather than a second description of it.
    using HitboxDebug = game::HitboxDebug;
    HitboxDebug hitbox_debug() const override;

    // The victim's two hurtbox anchor OFFSETS from the fighter root, in model space,
    // as FUN_0063dad0:241-245 builds them:
    //   anchor0 = the Bip01_Head bone origin (transform of (0,0,0) by its frame)
    //   anchor1 = the Bip01_Spine bone with the local offset (-25.0, 0, 0)
    // Both are BONE positions, so they come from the rig's bind pose; a rig without
    // those bones falls back to fractions of kFighterHeight (see melee_rules.h). These
    // offsets are what the hit test AND the debug overlay both read, so they cannot
    // disagree.
    glm::vec3 hurtbox_anchor_offset(int index) const;

    // Aerial melee: the same melee control, played from the air with the aerial reach.
    void set_aerial_attack(bool aerial) { m_aerialAttack = aerial; }
    bool aerial_attack() const { return m_aerialAttack; }

    // --- getters ---
    const glm::vec3&   position()   const override { return m_position; }
    float              facing_yaw() const override { return m_facing; }
    int                hp()         const override { return m_hp; }
    int                stamina()    const override { return m_pilotMeter ? m_actionMeter / 10
                                                              : static_cast<int>(m_stamina); }
    FighterState       state()      const override { return m_state; }
    bool               is_alive()   const override { return m_hp > 0; }
    bool               airborne()   const { return !m_grounded; }
    const xm::Model*   model()      const { return m_model; }
    // Which set is bound right now, and whether it is the fallback. The index
    // comes from the bound move table's phase tag; -1 means nothing is bound.
    // anim_set_name() is the model's own set name ("Anim-124" at index 0 on a
    // shipped rig), or "" when none is bound.
    int                anim_set_index() const override { return m_animSetIdx; }
    const char*        anim_set_name() const override;
    // True when a state selector or table row is unresolved, or its set index
    // does not fit the model: the fighter then plays set 0. Exposed so the fallback
    // is not silent —
    // the trace wiring in main.cpp and tests/fighter_script_test.cpp read it.
    bool               anim_fallback() const override { return m_animFallback; }
    // True when the state has no selector at all and the playing clip is held on
    // purpose (Guard; see state_has_animation_selector). Distinct from
    // anim_fallback(): holding a clip is the source behaviour, while a fallback is
    // a selector or table row this port has not recovered.
    bool               anim_no_selector() const override { return m_animNoSelector; }
    // Activation-overlay clock (issue #71): ticks since the move-500 clip was
    // bound, or -1 when no overlay is playing. The overlay set's own texture
    // events (e.g. Rena set 69's face swap) key off this, not the state's move
    // clock, which belongs to a different row while the overlay plays.
    int                hyper_activation_elapsed() const override {
        return m_hyperActivationSet >= 0 ? m_hyperActivationElapsed : -1;
    }
    // True while the activation overlay's own clip is still what's bound: a
    // superseding action's rebind ends the overlay even before its window lapses.
    bool               hyper_activation_playing() const override {
        return m_hyperActivationSet >= 0 && m_animSetIdx == m_hyperActivationSet;
    }
    // Activation flash alpha (0 when idle): FUN_0063a130 fills the viewport
    // with (alpha << 24) | mode-colour while nonzero. The renderer reads it
    // per view (issue #71).
    int                hyper_flash_alpha() const override { return m_hyperFlash; }
    // Bound weapon digits count rounds; bars include the original refill progress.
    float main_frac() const override { return m_weapon ? m_shootingMagazines[0].fraction() : m_main.frac(); }
    float charge_frac() const override { return m_weapon ? m_shootingMagazines[1].fraction() : m_charge.frac(); }
    int main_whole() const override { return m_weapon ? static_cast<int>(m_shootingMagazines[0].rounds) : m_main.whole(); }
    int charge_whole() const override { return m_weapon ? static_cast<int>(m_shootingMagazines[1].rounds) : m_charge.whole(); }
    // 0..1 across the full hold (red threshold = 1); colors the HUD meter.
    float charge_hold_frac() const override;
    ShotTier charge_tier() const override;
    bool reload_ok() const override {
        return m_weapon ? m_shootingMagazines[m_pending.tier == ShotTier::Tap ? 0 : 1].can_consume()
                        : m_reloadTimer <= 0;
    }

    // For ArenaTarget compatibility.
    // (ArenaCamera reads position + facingYaw from ArenaTarget; the DX9
    // CameraTarget also carried `alive`, which render::ArenaTarget dropped —
    // callers read is_alive() / pose().alive instead.)
    void sync_target(render::ArenaTarget& target) const {
        target.position  = m_position;
        target.facingYaw = m_facing;
    }

private:
    void reset_hit_reaction();
    void seed_pending_reaction();
    // Binds the next shared-recovery row (118/119 -> 120 -> 124/128) and restarts
    // its phase clock; the original advances on row completion, not on a timer.
    void bind_recovery_row(int row);
    void halt_row_motion();
    void update_getup_roll(const input::PlayerState* input);
    void apply_reaction_motion(const HitReaction& reaction, bool fromPhaseOne);
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
    // FUN_00637950 @0x638633/0x638645 supplies combat[17]/[18] at +0x87c/+0x878.
    // FUN_00428510 case 0x71 scales them by 0.01 into vertical +0x40 and
    // horizontal +0x54 respectively, with gravity +0x58 = 0.3 per update.
    // The row a hit reaction plays: combat[13] of the record that landed, handed in as
    // take_damage's `hitCategory`. 103 is the constant the port used before the records were
    // read (state_to_move_id's Hit entry), kept as the default when a record names none.
    int          m_reactionMove = 103;
    int          m_hitMeterA = 0;      // +0x7b8: stagger meter, threshold 100
    int          m_hitMeterB = 0;      // +0x7c0: combo count inside its own window
    int          m_hitFreeze = 0;      // +0xa0: record combat[9] attacker / combat[10] victim
    // The reaction row's own horizontal law (+0x54): a per-TICK facing-relative speed and its
    // per-tick decay, re-applied while the row plays (FUN_00428510's handlers own both numbers).
    float        m_rowSpeed = 0.f;
    float        m_rowDecel = 0.f;
    // Rows 104/105/204/205 hold their gated phase 0 before seeding motion, so the
    // record's pair waits here until the phase-1 transition (Q24).
    HitReaction  m_pendingReaction;
    bool         m_reactionSeedPending = false;
    bool         m_launched = false;   // the current Hit is a launch: landing becomes a knockdown
    int          m_downRow = 0;        // 118/119 lying, 120 get-up, 124 roll / 128 in place (0 = none)
    // The 120 completion chooses 124 (stick held) or 128 and resolves next update,
    // where the input is in scope (FUN_00428510 case 0x78 reads +0x278/+0x27c).
    bool         m_getupChoicePending = false;
    int          m_getupRollTicks = 0; // +0xe8: row 124's phase-1 counter
    // +0x7ac: refreshed to 30 every tick during the get-up roll (124..129), decaying
    // outside the reaction range and while no hitstop holds the actor.
    int          m_invincible = 0;
    int          m_staggerDecay = 0;   // +0x7bc
    int          m_comboDecay = 0;     // +0x7c4
    int          m_comboHits = 0;      // +0x7b0: the damage-proration counter
    // +0x7d0: the victim's stun susceptibility. The initializer writes 100 (0x41e067); the 50
    // at 0x43df11 is a conditional recompute, not the default. At 100 a 120-power contact fills
    // the meter in ONE hit, which is why every swing flinches.
    static constexpr int kStaggerResist = 100;
    int          m_hyperActivationFrames = 0;  // overlay window, or <0 for a gated hold (issue #71)
    int          m_hyperActivationSet = -1;   // overlay's bound set; -1 once superseded (issue #71)
    int          m_hyperActivationElapsed = 0;  // ticks since the overlay bound (issue #71)
    int          m_hyperFlash = 0;              // activation flash alpha, 0xFC down 4/tick (issue #71)
    int          m_animSetIdx  = -1;   // set bound for the current state (-1 = none)
    bool         m_animFallback = false;  // m_animSetIdx is the set-0 default
    const PilotLocomotion* m_pilotLocomotion = nullptr;  // P2-7 slice 2; null on the default path
    const PilotGuard* m_pilotGuard = nullptr;            // P2-7 guard gate; null on the default path
    const PilotMeter* m_pilotMeter = nullptr;            // P2-7 unified meter; null on the default path
    const PilotShot* m_pilotShot = nullptr;              // P2-7 item-model clear; null by default
    const PilotGuardMotion* m_pilotGuardMotion = nullptr; // P2-7 guard record supply; null by default
    MeleeChargeBases m_meleeChargeBases{};                // P2-7 charge bases of the last landed hit
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
    bool         m_chainGuarded = false;   // FUN_0042c7b0() bit 2: the strike was guarded
    ShootingVoice m_shootingVoice;
    MeleeVoiceCue m_meleeVoice;
    SoundEffectCue     m_pendingSoundEffect;
    EffectCue     m_pendingEffect;
    int           m_chargeGauge = 1000;
    // P2-7 unified action meter (+0x834, 0..1000). Authoritative only when a pilot meter
    // policy is attached; the default path never reads it. Reset alongside the legacy
    // pair so a stale value cannot leak across a round.
    int           m_actionMeter = 1000;
    // Nine actor-owned status timers (`+0x7dc..+0x7fc`), decremented after the
    // body executor by FUN_0042e110. Slot 6 is the Rena +40/+5 recovery gate.
    std::array<int, 9> m_hitStatusDuration{};
    std::array<int, 9> m_hitStatusPower{};
    bool m_sourceShotVoiceAudited = false;
    bool m_sourceMeleeVoiceAudited = false;
    SimulationRng* m_rng = nullptr;   // the scene's stream, null for a bare fighter
    SimulationRng  m_ownRng;          // fallback: deterministic per fighter
    int          m_meleeElapsed = 0;      // ticks since the swing started
    MeleeRules   m_meleeRules{};           // legacy tuning + recovered shape;
                                           // data-driven swings override it via m_swing
    const CharacterMoves* m_moves = nullptr;  // borrowed move table (issue #26)
    int          m_attackMoveId = -1;       // move the current swing plays (-1 legacy)
    int          m_shotMoveId = -1;
    int          m_holdTicks = 0;
    bool         m_holdAnimation = false;
    // Which MoveRule Hold owns m_holdTicks (type-erased: move_behavior.h stays out of
    // this header). A move holding twice (Keiichi's 450/460 stall at two ticks via
    // clock rewinds) needs per-rule progress — the shared counter alone would starve
    // the second hold. The dash hold path never consults this latch.
    const void*  m_holdRule = nullptr;
    // Per-move scratch counter (MoveOp::Counter/CounterSet), the port stand-in for the
    // bodies' `write_scratch(0x3e, ...)` counters. Reset with the move, not with each
    // section, because a body seeds it once at phase0/tick0 and then counts updates —
    // including the frozen ones a gated Hold pins, which is what makes Rika 1's
    // counter-gated salvo repeat.
    int          m_moveCounter = 0;
    // FUN_0042da80's latched pitch (whole degrees) for the bodies that read it back
    // from scratch 0x3c instead of re-deriving the elevation.
    float         m_movePitch = 0.f;
    // The attack bodies' own fall (original actor +40/+58): a per-move gravity in
    // the bodies' u/tick^2, sticky within the move and carried across row switches
    // the way the original's fields persist. -1 means no body owns the fall yet and
    // the locomotion rate applies (today's behavior for unbound air rows).
    float         m_attackGravity = -1.f;
    // The chase/dive bodies' lean (original +0x64/+0x30): summed into the model's yaw
    // rotation like the original's field sum (FUN_00420b30). Zero outside those rows.
    float         m_bodyPitch = 0.f;
    float         m_bodyPivotHeight = 0.f;
    // The state-320 chase strength (chasing_air_melee's air.strength): latched at
    // entry from the target distance, decays through the arc.
    int          m_chaseStrength = 0;
    // Extra phase-clock ticks this update (weapon 2's double-speed spin frames).
    int          m_clockSkip = 0;
    // The dive body turns its contact volume off past phase-1 frame 22.
    bool         m_contactDisabled = false;
    // The scene's per-tick publication of the firing-relevant world state.
    ShootingContext m_shooting;
    // Attachment slots 0/1. The executor re-binds slot0<-prop0, slot1<-prop1 and
    // deactivates both at the top of every frame, so a slot is unbound only while a
    // Hide rule's ticks match (FUN_00434a70(slot,-1)) and a prop is active only inside
    // an Active window. Both slots can be bound/active at once, and the prop's active
    // latch is what grows its ribbon.
    std::array<bool, 2> m_propBound{true, true};
    std::array<bool, 2> m_propActive{false, false};
    std::array<int, 2> m_trailItemModel{0, 1};
    // The actor's +0x684 camera-request word: NEGATIVE means no action camera, any other
    // value is an animation set on data/camera/01.x (FUN_006358c0:59-64 tests `< 0`). 0 is a
    // real set, which is what the Hyper EX row 350 requests (V3-37).
    int          m_actionCamera = -1;
    float        m_moveSpeed = 0.f;
    float        m_walkTurnRate = 20.f;
    float        m_inputFacing = 0.f;
    std::array<WeaponTrail, 2> m_trails;
    glm::vec2    m_previousWalkInput{0.f};
    int          m_dashMoveId = -1;         // inferred grounded dash candidate, or unresolved
    MeleeSwing   m_swing{};                 // this swing's resolved numbers
    bool         m_aerialAttack = false;   // this swing is the aerial variant
    bool         m_attackUsesActorFacing = false; // D-pad/stick Back at this aerial attack edge

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
    std::array<ShootingMagazine, 2> m_shootingMagazines{};
    AmmoStock    m_main;         // legacy stock without a bound weapon
    AmmoStock    m_charge;
    float        m_chargeHeld = 0.0f;  // legacy hold seconds / bound C-held marker
    // Frames the charge button has been held, reset on release: the recovered empty-tap branch
    // tests this count (`0 < released < 20`), which the seconds field cannot express because a
    // bound weapon pins it to one tick. See the empty-shot voice note on PilotShot.
    static constexpr int kChargeHoldTickCap = 20;  // the exclusive bound the body tests
    int          m_chargeHeldTicks = 0;
    void clear_charge_hold() {
        m_chargeHeld = 0.0f;
        m_chargeHeldTicks = 0;
    }
    int          m_reloadTimer = 0;    // legacy reloadNG window
    PendingShot  m_pending;      // armed shot awaiting scene spawn
    std::vector<PendingShot> m_pendingShots;
    std::array<const BulletParameter*, 64> m_bulletRows{};
    std::array<const xm::Model*, 64> m_bulletModels{};

    // --- air + dash (spec §3.2) ---
    float        m_vy = 0.0f;          // vertical velocity (u/s)
    bool         m_grounded = true;    // false between takeoff and landing
    float        m_groundY = 0.0f;      // takeoff height (flat-arena landing)
    float        m_flyLeft = FighterConstants::kFlyTimeSec;  // flight budget
    // The hover is ONE shot per airtime, not a re-enterable mode: the original admits
    // the jump row (40) only while grounded (FUN_00445ee0's jump branch requires the
    // grounded byte 0x84 != 0), so releasing and re-pressing the button mid-air
    // resumes nothing — the air chain runs once, then the fighter falls or takes
    // another air action. Set while hovering; cleared only by landing.
    bool         m_hoverSpent = false;
    // The Guard stance's own clip (character row 390's opening set), bound once on entry
    // so the state animates instead of holding whatever was playing. -1 = not bound.
    int          m_guardClip = -1;
    // Row 390's stance progression: 0 = preparation clip, 1 = hold clip. The release
    // section is a named limit (leaving Guard goes straight to Idle).
    int          m_guardPhase = 0;
    int          m_guardTicks = 0;
    glm::vec3    m_dashDir{0, 0, 1};   // committed dash direction (world XZ)
    // The tapped action owns this dash's committed travel. A later aerial attack
    // reads the direction held at its own press instead of reusing this value.
    input::Action m_dashInputDirection = input::Action::Up;
    // Held directional axes sampled at input dispatch; the tap-shot admission's
    // air-dash fast-shot branch reads them at the release edge.
    int m_inputAxisX = 0;
    int m_inputAxisZ = 0;
    float        m_dashSpeed = FighterConstants::kRunSpeed;
    // Side dash's screen axis (+1 right, -1 left, 0 for every other dash). The body
    // writes the movement angle as +/-90 RELATIVE to the target-facing basis (whose own
    // refresh is the port's m_inputFacing), so the direction has to be re-derived each
    // tick; freezing it into a world vector makes the step a straight line (owner: the
    // side steps should arc toward the target).
    int          m_dashSide = 0;
    // An air dash's momentum survives into the airborne state it ends in: FUN_0043ffc0
    // case 0x1e completes into state 43, and case 0x2b never writes the horizontal speed
    // (+0x15) or the movement angle (+0x18) — it only steers the angle (+0x874 = 1.0) and
    // integrates vertical gravity. So the fighter keeps sliding after the dash instead of
    // dropping straight down (owner: D2).
    bool         m_airDashCarry = false;
    // An air dash that ends in the air completes into the original's state 43, whose row is
    // move 43 / set 43 — not the jump chain's falling row 42, whose FIRST section is set 5
    // (32 frames) and only its second section is set 43. The port reached set 43 anyway, but
    // one 32-frame clip late. This flag makes the fall bind row 43 directly, and it also
    // suppresses the row-41 hover, which state 43 does not have (V3-42).
    bool         m_dashFall = false;
    // Landing screen. State 44 is a real row — move 44, one section tagged 44, 22 frames at the
    // shipped 1760/4800 ticks — entered by the air states whose landing is a normal touchdown:
    // state 41/42/43 all exit into it (FUN_0043ffc0 :54-81, and state 43's own exit at :530-536).
    // An AIR ATTACK's touchdown is a different branch: its body lands through its own LandExit /
    // LandPhase rows, so this window does not open for it. The port has no 44 state and keeps the
    // fighter in Idle, so this counter plays the row's clip for its recovered length and then
    // falls back to Idle's own. It runs on BOTH paths — the row is recovered behaviour, not a
    // pilot experiment. What it does NOT carry is the row's frame-10 flags-0x100 record, so the
    // port can still cancel out of the landing on the first tick (V3-42).
    int          m_landingTicks = 0;
    // The air dash's phase-1 visit counter (the body's +0x3a). Set 55 declares the +0x20
    // hold, so its clock can never advance the phase; the body leaves for phase 2 once
    // more than five visits have passed and either no direction is held or the meter is
    // empty (FUN_0043ffc0 :413-420).
    int          m_airDashTicks = 0;
    bool         m_dashAir = false;     // current dash started airborne
    bool         m_airDashed = false;   // air dash spent (resets on landing)
    double       m_time = 0.0;          // per-fighter clock (double-tap)
    double       m_lastTap[4] = {-1.0, -1.0, -1.0, -1.0};  // Up/Down/Left/Right

    // --- movement helpers ---
    // Convert a screen-relative input using either the rendered body yaw or the
    // current target bearing. The original keeps those separate while moving
    // (FUN_004202b0 / FUN_0042dd90), so a walked heading cannot redefine dash-up.
    glm::vec3 relative_direction(float yaw, float screenRight, float screenUp) const;
    glm::vec3 facing_relative(float screenRight, float screenUp) const;
    glm::vec3 target_relative(float screenRight, float screenUp) const;
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

    // C release selects the secondary magazine stage (legacy hold time without a weapon).
    void try_fire();

    // DAT-backed magazines own bound weapons; legacy stocks serve custom unarmed data.
    void apply_weapon_ammo();
    void restore_ammo();

    // Selects an admitted move without spending programmed shots' ammo. Their
    // firing callbacks consume the row-selected magazine before pool creation.
    void fire_shot(ShotTier tier);

    // Hypermode plumbing: gauge credit, S activation (with Oyashiro's
    // no-damage knockback burst), the EX move, and the Kakera death save.
    void gain_gauge(float fraction);
    bool try_activate_hypermode(Fighter* opponent);
    bool try_ex_move();
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

    // Live input and COM previews share table resolution. Rena+0 ordinary-air320
    // and air-dash332 have user-confirmed pose identities, not timing parity.
    // Other combos retain their prior aerial340 candidate; #66 owns selector recovery.
    // Every selected move resolves through the equipped combo's NN.dat.
    int resolve_attack_move(bool dashAttack, bool aerial) const;
    // Recovered dispatcher admission (melee_admission.h): the Rena group's
    // weapon-specific selector, fed by the numeric state and held axes. Other
    // combos keep resolve_attack_move's bounded candidates (issue #66).
    AttackAdmissionInput attack_input(bool aerial,
                                       const input::PlayerState* input) const;
    int admit_attack_move(bool aerial, const input::PlayerState* input) const;
    int numeric_state() const;
    int weapon_slot_index() const;
    // The resolved numbers for one move id: the move's first combat entry, or the
    // legacy tuning when there is no table, no move, or no combat entry. Shared by
    // build_melee_swing() (which binds it) and preview_melee_swing() (which does not).
    MeleeSwing resolve_swing(int moveId) const;
    // Fills m_swing from the move's first combat entry (or the legacy tuning
    // when there is no table, no move, or no combat entry).
    void build_melee_swing(int moveId);
    // FUN_00421080's row switch shared by chains, landings and contact exits: fresh
    // phase cursor/clip and per-row swing, with the air fields (gravity, lean)
    // carried the way the original's +40/+58 persist across the switch.
    void switch_attack_row(int moveId);
    // The state-320 chase and 332/334 dive bodies (ChasePolicy/DivePolicy in
    // move_behavior.h): feedback loops that re-derive speed/vertical from the live
    // flight angle each tick, so they run as bodies rather than static rules.
    void advance_rena_chase(const struct ChasePolicy& policy, Fighter* opponent);
    void advance_rena_dive(const struct DivePolicy& policy, Fighter* opponent);
    // Rena+1's 402 dive launch (FUN_00448220 case 0x192, phase 1 tick 0): the fixed
    // -40 u/tick drop with the horizontal closing speed derived from the target's
    // geometry — see the implementation for the exact clamp.
    void advance_rena1_dive_shot(Fighter* opponent);
    void turn_toward(const Fighter* opponent, float degrees);
    // A move counts when the table ships it with at least one phase (a costume
    // that drops the move must not resolve to a phaseless id).
    int present_move(int id) const;
    // Facing-relative forward/back (moves 20/27 in FUN_00438310). Side-dash
    // move order has no recovered link to the port's left/right inputs.
    int dash_move_for(input::Action dir) const;
    // The move whose phases the current state plays, or -1 if its selector is
    // not recovered. AttackA preserves the selected combo move; Jump resolves the
    // recovered 40→41→42 air chain.
    int state_move_id() const;
    // The jump chain the source advances by physics (live FUN_0043ffc0 cases
    // 0x28/0x29/0x2a): 40 on the ground, 41 while rising, 42 once vy falls under
    // the apex literal. Each row's first phase tag is the jump clip.
    int jump_chain_move() const;
    int landing_row_frames() const;
    int move_row_frames(int row) const;
    // A state can change its move without changing its port label (only the air
    // chain does today). The source rebinds through FUN_00421080 whenever the
    // move id changes, so re-check the binding once per update.
    void refresh_state_move();
    // Mirrors the source handler tail: elapsed move ticks advance once per update,
    // and the NN.dat set gate controls whether the current phase advances.
    void advance_animation_phase();
    glm::vec3 bone_point(const std::string& name, const glm::vec3& local) const;
    void execute_move_program(Fighter* opponent, const input::PlayerState* input);
    // A rule's gate bits evaluated against current fighter state (kGatePowered,
    // the counter tests). Kept beside the executor so the gate vocabulary and the
    // state it reads cannot drift apart.
    bool rule_gate_holds(const MoveRule& rule, float distanceSquared) const;
    float capture_target_pitch(float lowDegrees, float highDegrees,
                               float snapDegrees, const Fighter* opponent);
    void enter_phase(int phase);
    void launch_bullet(int row, const ShotOriginSpec& origin, const ShotAimSpec& aim,
                       float legacyLateral, float legacyPitchLimit,
                       const ShotSpreadSpec& spread, Fighter* opponent);
    // The stream a spread draws from: the scene's when one was published, else this
    // fighter's own.
    SimulationRng& rng_source() { return m_rng ? *m_rng : m_ownRng; }

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
