#pragma once
// Plain data shared by the product and whichever simulation backs a battle (game/battle_view.h).
// Nothing here knows Fighter or Match, so these survive the legacy path's removal.
#include <cstdint>

#include <glm/glm.hpp>

namespace game {

inline constexpr int kMatchFighterCount = 4;

// Port labels. The executable stores move IDs directly; the values stay stable because
// persisted state and traces carry them.
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

// Hypermode pick (spec §3.4). Index order matches the versus setup list and the -hyper CLI
// argument: Friendship, Oyashiro, Kakera (DX's third mode).
enum class Hypermode : int {
    Friendship = 0,
    Oyashiro   = 1,
    Kakera     = 2,
};

// Packed 0xAARRGGBB, the order the original's D3DCOLOR constants use.
using Rgb = std::uint32_t;

// D3DCOLOR_XRGB(r, g, b): opaque.
inline constexpr Rgb packRgb(std::uint8_t r, std::uint8_t g, std::uint8_t b,
                             std::uint8_t a = 0xffu) {
    return (static_cast<Rgb>(a) << 24) | (static_cast<Rgb>(r) << 16) |
           (static_cast<Rgb>(g) << 8) | static_cast<Rgb>(b);
}

// D3DCOLOR_ARGB(a, r, g, b) — alpha first, unlike packRgb.
inline constexpr Rgb packArgb(std::uint8_t a, std::uint8_t r, std::uint8_t g,
                              std::uint8_t b) {
    return packRgb(r, g, b, a);
}

inline constexpr std::uint8_t rgbR(Rgb c) {
    return static_cast<std::uint8_t>((c >> 16) & 0xffu);
}
inline constexpr std::uint8_t rgbG(Rgb c) {
    return static_cast<std::uint8_t>((c >> 8) & 0xffu);
}
inline constexpr std::uint8_t rgbB(Rgb c) {
    return static_cast<std::uint8_t>(c & 0xffu);
}

inline constexpr std::uint8_t rgbA(Rgb c) {
    return static_cast<std::uint8_t>((c >> 24) & 0xffu);
}

enum class ShotTier : std::uint8_t {
    Tap    = 0,
    Yellow = 1,
    Red    = 2,
    Ex     = 3,
};

struct CombatStats { int kos = 0, deaths = 0, damageDealt = 0, damageTaken = 0; };

// The debug overlay's hit volumes for one fighter.
struct HitboxDebug {
    glm::vec3 anchors[2]{};
    float     anchorRadius = 0.f;
    bool      attacking    = false;
    glm::vec3 attackCenter{};
    glm::vec3 attackEnd{};
    bool      capsule = false;
    float     attackRadius = 0.f;
};

// What one tick did, for the trace, the flow and the effect queue.
struct BattleFrame {
    // FUN_006358c0/FUN_0063dad0 set one scene-wide DirectSound listener to the selected
    // actor's XYZ +150Y. Split-screen therefore uses the primary human view as the port's
    // explicit single-listener rule; these fields feed positional gameplay SEs.
    glm::vec3 audioListenerPosition{0.f};
    glm::vec3 audioListenerForward{0.f, 0.f, 1.f};
    bool audioListenerValid = false;
    bool koSting       = false;  // economy: KO sting window is running
    bool respawned[kMatchFighterCount] = {false, false, false, false};
    bool roundOver     = false;
    // The WINNING side once roundOver (MatchEconomy::roundOverSide; issue #11). -1
    // only before the round ends — a timed round always resolves to a side.
    int  roundOverSide = -1;
    // Issue #11's credits, per fighter: the balloon % a KO added this frame and how
    // many hits landed on an already-down body. Both are already applied to the
    // economy; they are reported so effects/audio/results can key off the event
    // without re-deriving it (the KO credit is one-shot by construction).
    int  koCredits[kMatchFighterCount]     = {0, 0, 0, 0};
    int  overkillHits[kMatchFighterCount]  = {0, 0, 0, 0};
    int  shotsSpawned  = 0;      // accepted by the pool this frame
    int  muzzleSparks  = 0;
    // i hit an opposing fighter this frame
    bool meleeHit[kMatchFighterCount] = {false, false, false, false};
    int meleeVictim[kMatchFighterCount] = {-1, -1, -1, -1};
    // --- live combat events (issue #16) -------------------------------------------------
    // The simulation reports what happened; audio and effects consume it. Every flag here
    // is an EDGE armed by the transition itself (Fighter::take_swing_start /
    // take_hyper_start, the pool's spawn, the economy's respawn) and drained exactly once,
    // so re-reading a frame cannot replay an event and a fixed 60 Hz tick cannot miss one.
    // i armed a melee swing / i's shot was accepted by the pool
    bool swingStarted[kMatchFighterCount] = {false, false, false, false};
    bool sourceShotVoiceAudited[kMatchFighterCount] = {false, false, false, false};
    // True when the actor's running row carries a recovered melee voice cue, so the
    // audio layer suppresses its fallback swing voice for that fighter this tick.
    bool sourceMeleeVoiceAudited[kMatchFighterCount] = {false, false, false, false};
    int shotVoice[kMatchFighterCount] = {-1, -1, -1, -1};
    int shotVoiceAlternative[kMatchFighterCount] = {-1, -1, -1, -1};
    // The melee voice cue (FUN_004223d0/422490), the gameplay SE cue (FUN_0042c8b0/
    // 2c880) and the actor effect request (`(*actor+0xc)` -> FUN_00421aa0 -> FUN_00435990)
    // — one per fighter per tick, -1 when silent. The two id spaces are different calls
    // and stay apart: soundEffectId is a data/se index while effectId is a data/effect
    // id (`id / 10` names the descriptor), whose yaw/pitch carry the request's pose
    // (including the 350 beats' two rand%40-20 draws).
    int meleeVoice[kMatchFighterCount] = {-1, -1, -1, -1};
    int meleeVoiceAlternative[kMatchFighterCount] = {-1, -1, -1, -1};
    int soundEffectId[kMatchFighterCount] = {-1, -1, -1, -1};
    bool soundEffectPositional[kMatchFighterCount] = {};
    glm::vec3 soundEffectPosition[kMatchFighterCount] = {};
    int effectId[kMatchFighterCount] = {-1, -1, -1, -1};
    float effectYaw[kMatchFighterCount] = {};
    float effectPitch[kMatchFighterCount] = {};
    bool shotFired[kMatchFighterCount]    = {false, false, false, false};
    // Where that shot left the muzzle (issue #17): the effect layer spawns the muzzle
    // flash from the event's own position instead of re-deriving it from the pose.
    glm::vec3 shotPoints[kMatchFighterCount] = {glm::vec3(0.f), glm::vec3(0.f),
                                                glm::vec3(0.f), glm::vec3(0.f)};
    // i activated hypermode / i raised its guard
    bool hyperStarted[kMatchFighterCount] = {false, false, false, false};
    // The actor's hypermode WIRE value per fighter (0/1/2, see
    // hypermode_wire_value), read fresh each tick so the per-mode S-press
    // presentation resolves (issue #71).
    int hyperMode[kMatchFighterCount] = {-1, -1, -1, -1};
    bool guardStarted[kMatchFighterCount] = {false, false, false, false};
    // A landed hit's victim was guarding. The port's guard gate is provisional
    // (Fighter::take_damage's 20% block), so this is a port rule, not the original's.
    bool blocked[kMatchFighterCount]      = {false, false, false, false};
    // Shot -> fighter contacts the pool resolved this frame, in pool order. The melee path
    // reports one victim per attacker above; a shot volley can connect with several
    // fighters in one tick, so this is its own list.
    static constexpr int kMaxShotHits = 8;
    struct ShotHit {
        int  shooter = -1;
        int  victim  = -1;
        bool blocked = false;
        // Issue #17: the contact point and the impact effect id the shot carried
        // (bullet record +0x70). The effect layer spawns one instance per hit from
        // these, so overlapping hits cannot retire each other's cards.
        glm::vec3 point{0.f};
        int  effect = -1;
    };
    int     shotHitCount = 0;
    ShotHit shotHits[kMaxShotHits];
};

}  // namespace game
