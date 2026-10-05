// =============================================================================
//  fighter.h — arena fighter with state machine + animation switching.
//
//  Ported to the SDL3 + WebGPU foundation (docs/FULL-REPLACEMENT-PLAN.md §5
//  item 2b) from remake/src/gameplay/fighter.h: logic only, D3D-free, names
//  kept identical so the two can be diffed. Deviations are listed in "PORT
//  NOTES" at the bottom of this header.
//
//  RE findings (docs/reverse-engineering.md):
//    - 40+ animation state names in .data: attackA/B/C, guard, damage,
//      damagedown, damageKO, battlestart, recovery, etc. They are the VOICE cue
//      keys (data/voice/<char>/<key>/NNN.wav, FUN_00431e70 at 0x432042), not
//      animation names; the states select animation-set INDICES (see the table
//      above state_to_anim_set).
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
//  State machine (simplified from the original's ~40 move ids; input mapping is
//  provisional — see input.h: the original has ONE melee key (X),
//  no dedicated heavy key, and separate shoot/special/tactics keys):
//    Idle → Walk → Idle            (stick moved / released)
//    Idle → Run → Idle             (dash: double-tap direction)
//    Idle/Walk → AttackA → Idle    (melee key — light, 30 frames)
//    Idle/Walk → AttackB → Idle    (heavy — currently same-key stand-in,
//                                   real game uses directional variants)
//    Idle/Walk → ShootA/B/C → Idle (C released: tap/yellow/red tier, 20 frames;
//                                   tiers map to the binary's weapon shot moves
//                                   300/301/302; costs + reloadNG gating live
//                                   in projectile.h)
//    Idle/Walk/Run/Jump → Jump     (Z: leap; hold to fly on the fly timer)
//    tap,tap dir → Run             (ground dash) or Run-air (air dash, once
//                                   per airtime); X mid-dash = dash attack,
//                                   X airborne = aerial (same swing, gravity
//                                   keeps running underneath it)
//    Idle/Walk → Guard → Idle      (block key held)
//    Any → Hit → Idle              (took damage, 15 frames stun)
//    Any → Knockdown → KO          (HP reached 0)
//    BattleStart → Idle            (round start pose, 60 frames)
// =============================================================================
#pragma once

#include <cstdint>
#include <string>

#include "assets/xmodel.h"          // xm::Model / xm::Controller (non-owning)
#include "game/fighter_pose.h"      // game::IFighterPose / game::FighterPose
#include "gameplay/character_moves.h"  // CharacterMoves (borrowed move table)
#include "gameplay/projectile.h"
#include "gameplay/melee_rules.h"
#include "gameplay/weapon_definition.h"
#include "input/input.h"
#include "render/arena_camera.h"    // for render::ArenaTarget

namespace gameplay {

// The foundation's device-free input model has the same 13-action layout as the
// DX9 build's input/input_manager.h (verified field-by-field in the port
// report), so the alias lets every `input::Action` / `input::PlayerState` use
// below read exactly like the source's `input::Action` / `input::PlayerInput`.
namespace input = fnd::input;

// Fighter states. The original has no such enum: its state is a "move id"
// (`[player+0xadec]`, see the table below), and these are the port's names for
// the move ids it models.
enum class FighterState : int {
    Idle        = 0,   // standing, no input
    Walk        = 1,   // moving (stick/d-pad)
    Run         = 2,   // dashing (double-tap)
    AttackA     = 3,   // melee (provisional input; see input.h)
    AttackB     = 4,   // heavy stand-in (no dedicated key in original)
    AttackC     = 5,   // special attack (not yet mapped to input)
    Guard       = 6,   // blocking (block key held)
    Hit         = 7,   // taking damage (stun)
    Knockdown   = 8,   // knocked down
    KO          = 9,   // defeated
    BattleStart = 10,  // round start pose
    TagOut      = 11,  // reserved, never entered: no character swap exists —
                        // the reticle only changes targets (FUN_00421e30), and the
                        // "tag" voice cluster is partner callouts (see below)
    ShootA      = 12,  // tap shot fired
    ShootB      = 13,  // yellow charge released
    ShootC      = 14,  // red charge released
    Jump        = 15,  // airborne (leap, fly, or falling out of an air dash)
    ShotFinal   = 16,  // Hypermode EX move
};

// ---------------------------------------------------------------------------
// State → animation set index (the original's selection).
//
// The original never looks an animation up by name. A fighter's state IS a
// "move id" (`[player+0xadec]`), and a move names animation-set indices in the
// character's own `data/<char>/NN.dat`:
//
//   FUN_00428510 (0x428510) switches on `[player+0xadec]`; every case value is a
//   move id present in the shipped .dat files (measured on rena/mion/rika/
//   satoko/keiichi/shion/hanyu 00–02.dat).
//   FUN_00421080 (0x421080) starts a move: `[+0xadec] = [+0xadf0] = moveId`,
//   `[+0xade0] = &moves[moveId]` (28-byte entries), then FUN_00421100(0).
//   FUN_00421100 (0x421100) takes phase 0 of that move —
//   `FUN_004244e0(&move->phases, phaseIndex)` is a std::vector index (0x4244e0
//   is a _Vector_iterator over the container at move+8) — and binds the phase's
//   FIRST dword to both tracks: `FUN_00421410(0, phase[0])` and
//   `FUN_00421410(1, phase[0])` (0x421410 sets the set for the track).
//   FUN_0041e180 (0x41e180) fills the per-player 124-entry animation table
//   (+0x75e0, stride 0x38) from the .dat's animation table, whose entry i is
//   `controller->GetAnimationSet(i)` — FUN_0064e8b0 (0x64e8b0) is
//   GetAnimationSet + ID3DXAnimationSet::GetDuration. So the .dat's index is the
//   D3DX set index, i.e. this port's `Model::anims` index (Parser::finish
//   already reversed the file order to match D3DX; see xmodel.h:1615-1623).
//   FUN_0041f580 (0x41f580, per-player update) reads the same `phase[0]` back
//   as the current animation index and cross-fades its weight.
//
//   Move CHANGES blend instead of cutting: FUN_004211f0 takes the new move id
//   and FUN_00421240(0) binds its phase 0 to track 1 only, while track 0 keeps
//   showing the old move; FUN_0041f580's per-tick loop then decays the old
//   weights and raises the new ones (the +0xae14/0xae18 counters bound the
//   window). The port mirrors this: a state change keeps the old set on
//   track 0, binds the new set on track 1 from t=0, ramps the weights over
//   kAnimBlendTicks ticks, and commits both tracks to the new set. The
//   initial bind (no old set) and same-set rebinds cut directly to both
//   tracks, which is the FUN_00421100 steady state.
//
// The state/move KEY table at VMA 0x6b73b0 (16-byte stride: addattack, attackA …
// specialC) is NOT this mapping: the only code that indexes it is the voice
// system inside FUN_00431e70 (0x432042: `shl edx,4; add edx,0x6b73b0`) which
// wsprintfA's `data/voice/<char>/<key>/%03d.wav` (formats at 0x6a281c/0x6a2830/
// 0x6a2844). Those names never appear in a .X, whose sets are `Anim-1`…`Anim-124`.
//
// Rows below: port state → (move id, first-phase set index). The move id is
// recorded because it is the citation; the index is what the model plays. The
// set index is per-character data, but the shipped rigs order the 124 sets
// identically and the .dat files agree on the index for every shared move id
// (measured across the 11 character .dat files above), so one table serves all
// characters — except for the weapon-specific moves (300+, see ShootA/B/C),
// whose indices differ per character and are therefore taken from rena's
// weapon-1 slot (data/rena/00.dat, weapon id 1).
//
// Not settled (deliberately left to the set-0 default rather than guessed):
//   * Guard — the block key's move is not pinned; the "guard"/"guarded" voice
//     keys exist (indices 12/13, shipped for all 12 characters) but the corpus
//     holds no FUN_0064ae10 key-12 play site, so no call site was found that
//     way either. Blocking may be a damage-path flag rather than a move —
//     next step is the flag read on incoming damage, not another case hunt.
//   * Jump — the port's leap/fly/fall may span several original moves (the
//     locomotion selector FUN_0043ded0's air branches start 0x168/0x15e/0x1cc
//     among others), and pinning one needs the jump input-bit mapping, which
//     is not located. Note: FUN_004235d0 is steering (called from FUN_0041f580
//     with a relation index and a relative angle), not air locomotion —
//     earlier notes misread it as the jump driver.
//   * TagOut — no such mechanic: control never transfers between fighters
//     (input slots are per fixed index; the only switch in the original is
//     the reticle target cycle, FUN_00421e30, wired to LockSwitch tap in
//     main.cpp). The "tag" story came from voice-dir names (tagfront/
//     tagback/tagOK, shipped for all characters) sitting beside tactics and
//     thank in the key table — partner callouts, not a swap. "recovery" is a
//     voice key of unknown cue (knockdown-recovery and round-transition both
//     fit; neither is pinned). The state is never entered and stays on the
//     fallback.
// ---------------------------------------------------------------------------
inline int state_to_anim_set(FighterState s) {
    switch (s) {
        // move 0 → Anim-124: the player reset (0x41de68) sets [+0xadec] = 0 and
        // calls FUN_00421080(0); FUN_00428510 returns to 0 whenever nothing else
        // applies. Its single phase names set 0.
        case FighterState::Idle:        return 0;
        // Move 10 is the walk: a single phase naming set 1 (measured across every
        // shipped character .dat; controller index 1 is the walk clip in
        // --anim-player). An earlier revision named move 0x14 (20) here, but its
        // phases [13, 14, 15] are dash startup/loop/recovery (issue #26).
        case FighterState::Walk:        return 1;
        // Move 0x14 (20) is the forward dash chain, selected by FUN_0043ded0
        // (0x43ded0: `FUN_00421080(0x14)`); its first phase names set 13, the dash
        // startup (0x17/0x18/0x1b are the other directional dash chains). An earlier
        // revision named move 0x1e (30) here, but its phases [54, 55, 56] are the
        // jump-forward chain (issue #26). The port's Run IS the double-tap dash.
        case FighterState::Run:         return 13;
        // KNOWN-WRONG placeholders (issue #26), values unchanged pending the weapon
        // dimension: moves 0x28/0x29/0x2a (40/41/42) are the JUMP chain — first
        // phases 2, 3, 5, all zero combat — not the melee chain they were mistaken
        // for. No character has an unarmed attack; real attacks are the weapon
        // moves (300+: first phases 31/33/34 nata, 39/40 kick, 51–53 lunge), whose
        // sets differ per character and costume. AttackA must resolve to the
        // equipped weapon's set; until then these rows play the jump clips.
        case FighterState::AttackA:     return 2;
        case FighterState::AttackB:     return 3;
        case FighterState::AttackC:     return 5;
        // Move 0x67 (103) is the "cannot act" reaction FUN_00428510 plays in cases
        // 0xe7/0xca; its chain is (95, 27) — the launched pose then the ground.
        case FighterState::Hit:         return 95;
        // Move 0xc4 (196) is the grounded reaction (cases 0xc4/0xc6/199); its
        // chain (28, 29) is the lying pose.
        case FighterState::Knockdown:   return 28;
        // Move 0xcb (203) is the KO chain (cases 0xc9/0xcc/0xce): (97, 37).
        case FighterState::KO:          return 97;
        // Move 0xc2 (194) is the round reset's pose: FUN_004219a0 (0x4219a0)
        // restores HP/inputs and plays it; its single phase is 43.
        case FighterState::BattleStart: return 43;
        // Moves 0x12c/0x12d/0x12e (300/301/302) are the weapon's shot moves — the
        // character scripts start them 20+ times each and the AI reads the shot
        // move id out of the weapon parameter block (`[+0x64]`/`[+0x68]` of
        // `[input+0x10]`, FUN_00637950:350-357). rena weapon 1: 31/33/34.
        case FighterState::ShootA:      return 31;
        case FighterState::ShootB:      return 33;
        case FighterState::ShootC:      return 34;
        // Move 0x1f7 (503) is the EX/finisher move FUN_00422bd0 falls back to
        // (`if (result == 0x1f7) FUN_00421080(0x1f7)`); its phase is 69.
        case FighterState::ShotFinal:   return 69;
        case FighterState::Guard:
        case FighterState::Jump:
        case FighterState::TagOut:
        default:                        return -1;
    }
}

// The trace's per-fighter field. It stays the STATE name on purpose: the DX9
// build this trace is diffed against binds no animation sets at all (its d3dx9
// under Wine returns no controller — see tests/visual/out/*.log), so it has no
// set to print, and compare_match_traces.py asserts these names match exactly.
// The set actually bound is exposed by Fighter::anim_set_index()/anim_set_name().
inline const char* state_to_anim_name(FighterState s) {
    switch (s) {
        case FighterState::Idle:        return "idle";
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
        case FighterState::Jump:        return "jump";
        case FighterState::ShotFinal:   return "shotFinal";
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
    static constexpr float kMeleeRange    = 160.0f;  // legacy shared reach: the
        // fallback when no move table is bound, and the Oyashiro activation burst
        // radius. Data-driven swings use their own hitRadius (30 + hr, FUN_0063b470).
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
    // Air movement (spec §3.2; all provisional — no RE numbers yet).
    static constexpr float kGravity       = 900.0f; // downward accel (u/s^2)
    static constexpr float kJumpSpeed     = 380.0f; // leap initial vy (u/s)
    static constexpr float kFlyRise       = 40.0f;  // vy while holding Z aloft
    static constexpr float kFlyTimeSec    = 1.2f;   // flight budget per airtime
    static constexpr float kFlyMaxAlt     = 420.0f; // ceiling above takeoff
    static constexpr float kAirControl    = 0.7f;   // stick authority airborne
    // Dashes (spec §3.2): double-tap a direction; airborne → air dash.
    static constexpr double kDoubleTapSec = 0.30;   // tap,tap window (seconds)
    static constexpr int   kDashFrames    = 20;     // committed dash length
    static constexpr float kAirDashSpeed  = 260.0f; // ground dash uses kRunSpeed
    // Stamina spends (spec §3.4: dashing/jumping/block-hold spend it all).
    static constexpr float kDashStamina    = 20.0f;  // per dash (gated: no
                                                    // dash below this)
    static constexpr float kJumpStamina    = 10.0f;  // per leap (clamped)
    static constexpr float kGuardDrainSec  = 25.0f;  // block-hold drain
    static constexpr float kFlyDrainSec    = 30.0f;  // flight drain
    static constexpr float kStaminaRegenSec = 60.0f; // grounded refill rate
    // Move-change cross-fade length in update ticks (~0.13 s at 60 fps).
    // INFERRED: the original's blend runs off the +0xae14/0xae18 counters
    // under FUN_0041f580, whose initial value was not located in the
    // decompiled tree — only the mechanism (old decays, new rises) is read.
    // 8 ticks follows fighting-game convention; the number stands until a
    // dynamic oracle pins it.
    static constexpr int   kAnimBlendTicks = 8;
};

// One swing's resolved numbers (issue #26 steps 3–4). Data-driven when a move
// table is bound: windows, reach, damage and stun come from the situation's
// move hit entry. Otherwise the legacy shared tuning below, so a fighter with
// no moves bound behaves exactly like the pre-#26 machine.
struct MeleeSwing {
    bool  dataDriven = false;
    int   moveId = -1;      // character-.dat move this swing plays (-1 = legacy)
    int   startupTicks  = 5;
    int   activeTicks   = 8;
    int   recoveryTicks = 17;
    float radius = 130.0f;                            // stands in for weapon+0x24
    int   damage = FighterConstants::kLightDamage;
    int   hitstun = 8;                                // legacy active-window stun
    int total_ticks() const { return startupTicks + activeTicks + recoveryTicks; }
    bool is_active(int elapsed) const {
        return elapsed >= startupTicks && elapsed < startupTicks + activeTicks;
    }
    bool is_recovery(int elapsed) const { return elapsed >= startupTicks + activeTicks; }
};

// Handoff from Fighter (input/charge side) to the scene (spawn/collide side):
// update_state_machine() arms this on C release; Scene_Gameplay drains it
// into the ProjectilePool the same frame, so at most one shot queues.
struct PendingShot {
    bool          armed = false;
    ShotTier      tier  = ShotTier::Tap;
    glm::vec3     pos   {};
    glm::vec3     dir   {0, 0, 1};
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
    // `source` applies the attacker's Hypermode damage bonus and earns its
    // gauge (Friendship). Pass nullptr for environmental damage.
    // `hitstunFrames` overrides the hit-stun length when >= 0: FUN_00637950:308 writes
    // the attacker's weapon block defenderHitstun (blob index 10, record +0x58) into
    // the victim's +0xa0 action counter, so the stun length is per weapon. Negative
    // keeps the shared kHitStunFrames.
    void take_damage(int amount, Fighter* source = nullptr, int hitstunFrames = -1);
    void set_state(FighterState new_state);

    // ---- character move table (gameplay/character_moves.h, issue #26) ----
    // Binds the parsed data/<char>/NN.dat for this fighter's own rig. Borrowed,
    // like the model and the weapon; null keeps the legacy shared tuning (the
    // state_to_anim_set rows and MeleeRules), which is what the standalone
    // --match trace path and the install-free tests rely on.
    void set_moves(const CharacterMoves* moves);
    const CharacterMoves* moves() const { return m_moves; }
    // The character-.dat move the current (or most recent) swing plays, or -1
    // when the swing is the legacy shared one. Exposed so tests pin the
    // situation → move mapping without needing a model.
    int attack_move_id() const { return m_attackMoveId; }

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

    // ShotParams for this fighter's tier. Damage and hit radius come from the bound
    // BulletParameter when there is one; speed and lifetime stay the shared provisional
    // table, which the coverage table records as not recovered.
    ShotParams shot_params_for(ShotTier tier) const;

    // The recovered charge thresholds in SECONDS. FUN_00433eb0's per-magazine
    // chargeMax is a tick count (the shipped values run 60..1200, and 180 is the same
    // 0xb4 the ally hold is written with), converted through the fixed tick. PORT RULE:
    // the original's charge is a 100-point gauge with a 120-frame decay window, not a
    // hold timer, so this conversion is a design choice, not recovered behaviour.
    float yellow_hold_sec() const;
    float red_hold_sec() const;

    // How many projectiles one trigger of this tier releases. PORT RULE: the tier ->
    // bullet binding is not recovered, so this picks the lowest-type bullet drawing
    // from the magazine that tier spends; the COUNT is the file's own shotNum.
    int shot_count(ShotTier tier) const;

    // --- hypermode (spec §3.4) ---
    void set_hypermode(Hypermode m) { m_hypermode = m; }
    // Launch-time state injection (the suite's stand-in for the original's
    // F-keys: F4 maxes Hypermode, wiki Basics §training). 0..1, clamped.
    void set_hyper_gauge(float f) {
        m_gauge = f < 0.0f ? 0.0f : (f > 1.0f ? 1.0f : f);
    }
    // Startup HP (-hp): lets a test reach a lethal-hit path without a
    // wind-up (Kakera's death save, Overkill's downed window).
    void set_hp(int hp) {
        m_hp = hp < 1 ? 1 : (hp > m_maxHP ? m_maxHP : hp);
    }
    void set_battle_rates(int healthPercent, int gaugePercent) {
        m_maxHP = healthPercent < 50 ? 50 : (healthPercent > 200 ? 200 : healthPercent);
        m_gaugeRate = (gaugePercent < 50 ? 50 : (gaugePercent > 200 ? 200 : gaugePercent)) / 100.f;
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
        return victimIndex >= 0 && victimIndex < 4 && (m_swingHits & (1u << victimIndex));
    }
    int  swing_hit_count() const { return m_swingHitCount; }

    // The move this fighter is playing, as a fighter index, or kNoTarget.
    static constexpr int kNoMeleeVictim = -1;

    // True while the current attack is in its startup, active or recovery window. A
    // recovery swing must not chain into another action (issue #10). The windows
    // are this swing's own (data-driven when moves are bound, legacy otherwise).
    bool melee_in_recovery() const { return m_swing.is_recovery(m_meleeElapsed); }
    bool melee_in_active() const { return m_swing.is_active(m_meleeElapsed); }

    // Swing bookkeeping driven by Match: begin clears the per-victim hit set, note
    // records that this swing already connected with one victim.
    void begin_melee_swing(int victimIndexBase = 0);
    void note_melee_hit(int victimIndex);
    // Ticks of hit-stun a melee inflicts: the swing's own (the weapon entry's
    // defenderHitstun when moves are bound, the legacy active-window stun else).
    int  m_meleeHitstun() const { return m_swing.hitstun; }

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
    // Which set is bound right now, and whether it is the fallback. The original's
    // index is state_to_anim_set(m_state); -1 means nothing is bound (no model, no
    // sets, or animation switched off). anim_set_name() is the model's own set name
    // ("Anim-124" for index 0 of a shipped rig), or "" when none is bound.
    int                anim_set_index() const { return m_animSetIdx; }
    const char*        anim_set_name() const;
    // True when the state has no row in the original's table, or this model has too
    // few sets for its index: the fighter then plays set 0 (the bind-anchored
    // default) instead of the state's set. Exposed so the fallback is not silent —
    // the trace wiring in main.cpp and tests/fighter_script_test.cpp read it.
    bool               anim_fallback() const { return m_animFallback; }
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

    // --- state machine ---
    FighterState m_state       = FighterState::Idle;
    int          m_stateTimer  = 0;    // frames remaining in current state
    int          m_animSetIdx  = -1;   // set bound for the current state (-1 = none)
    bool         m_animFallback = false;  // m_animSetIdx is the set-0 default
    int          m_blendTicks  = 0;    // cross-fade ticks left (0 = steady state)
    int          m_blendTotal  = 1;    // blend length the weights interpolate over
    // Per-swing hit accounting (issue #10): a bit per victim index, plus a count, both
    // cleared when the state changes so one swing can hit several opponents once each.
    unsigned     m_swingHits = 0;
    int          m_swingHitCount = 0;
    int          m_meleeElapsed = 0;      // ticks since the swing started
    MeleeRules   m_meleeRules{};           // legacy tuning + recovered shape;
                                           // data-driven swings override it via m_swing
    const CharacterMoves* m_moves = nullptr;  // borrowed move table (issue #26)
    int          m_attackMoveId = -1;       // move the current swing plays (-1 legacy)
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
    // pool geometry below is the remake's design. What is recovered — per-weapon damage,
    // hit radius, hitstun, gauge gain and the two charge-tier move ids — arrives through
    // m_bulletParams instead.
    const WeaponDefinition* m_weapon = nullptr;   // borrowed
    const BulletParameter*  m_bulletParams[2] = {nullptr, nullptr};  // per charge level
    AmmoStock    m_main;         // MAIN pool (charge level 1)
    AmmoStock    m_charge;       // CHARGE pool (charge level 2)
    float        m_chargeHeld = 0.0f;  // seconds C held (resets on release)
    int          m_reloadTimer = 0;    // reloadNG window (frames, 0 = reloadOK)
    PendingShot  m_pending;      // armed shot awaiting scene spawn

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
    void update_movement(const input::PlayerState* input, const Fighter* opp, double dt);
    void update_state_machine(const input::PlayerState* input, Fighter* opponent,
                              double dt);
    void update_facing(const Fighter* opp, double dt);
    void try_switch_animation();
    // One cross-fade tick (the FUN_0041f580 weight half): the old set on
    // track 0 decays 1 -> 0 while the new set on track 1 rises 0 -> 1, then
    // both tracks commit to the new set (the FUN_00421100 steady state).
    void tick_blend();
    // End-of-blend commit: track 0 takes over track 1's set at its playhead
    // at full weight, restoring the FUN_00421100 both-tracks steady state.
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
    void update_hypermode(double dt, Fighter* opponent);

    // Z leap (grounded only) and double-tap dash setup. try_dash maps the
    // tapped key to a facing-relative dash (Up = forward ...) and returns
    // false when the stamina gate or the once-per-airtime rule blocks it.
    void try_jump();
    bool try_dash(input::Action dir);

    // Knocks the target away without damage (Oyashiro activation). Reuses
    // the Hit state's friction branch to carry the push; the real knockback
    // animation state is un-RE'd.
    void apply_knockback(const glm::vec3& dir, float speed);

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
    // Fills m_swing from the move's first combat entry (or the legacy tuning
    // when there is no table, no move, or no combat entry).
    void build_melee_swing(int moveId);

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
//     through bind()/init(). try_switch_animation() binds the index
//     state_to_anim_set(state) — the original's move → phase → set chain (see the
//     table above) — and only falls back to set 0 when the table has no row for the
//     state or the model is shorter than the index.
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
