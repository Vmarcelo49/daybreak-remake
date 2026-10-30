#pragma once
// Plain data shared by the product and whichever simulation backs a battle (game/battle_view.h).
// Nothing here knows Fighter or Match, so these survive the legacy path's removal.
#include <cstdint>
#include <string>
#include <vector>

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

// Hypermode pick (spec §3.4). The selection screen's row is the value the actor keeps at +0x318:
// FUN_0040d130:106 copies the slot's +0x3d18 across untouched.
enum class Hypermode : int {
    Oyashiro   = 0,
    Friendship = 1,
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

// The HUD's caption and aura colour per mode. The colours follow the wiki's mode captures;
// Kakera has no capture yet, so green keeps it distinguishable.
struct HypermodeHud {
    const char* name;
    Rgb aura;
};

inline HypermodeHud hypermode_hud(Hypermode m) {
    switch (m) {
        case Hypermode::Friendship: return {"FRIENDSHIP", packRgb(130, 220, 255)};
        case Hypermode::Oyashiro:   return {"OYASHIRO", packRgb(255, 110, 220)};
        case Hypermode::Kakera:     return {"KAKERA", packRgb(150, 255, 160)};
    }
    return {"FRIENDSHIP", packRgb(255, 255, 255)};
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
    bool roundOver     = false;
    // The WINNING side once roundOver (MatchEconomy::roundOverSide; issue #11). -1
    // only before the round ends — a timed round always resolves to a side.
    int  roundOverSide = -1;
    // What the core asked the presentation to do this tick; one tick can ask for several.
    struct EffectSpawn { int id = -1; glm::vec3 position{0.f}, direction{0.f}; };
    struct SoundCue { int id = -1; bool positional = false; glm::vec3 position{0.f}; bool system = false; };
    struct VoiceCue { int fighter = -1; std::string path; bool positional = false; glm::vec3 position{0.f}; };
    std::vector<EffectSpawn> effectSpawns;
    std::vector<SoundCue> soundCues;
    std::vector<VoiceCue> voiceCues;
};

}  // namespace game
