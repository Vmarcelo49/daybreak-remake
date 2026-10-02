// =============================================================================
//  projectile.h — shot tiers, fractional ammo stocks, projectile pool, sparks.
//
//  Ported to the SDL3 + WebGPU foundation (docs/FULL-REPLACEMENT-PLAN.md §5
//  item 2b) from remake/src/gameplay/projectile.h: logic only, D3D-free, names
//  kept identical so the two can be diffed. Deviations are listed in "PORT
//  NOTES" at the bottom of this header.
//
//  RE provenance (DaybreakDX.exe string table @0x2b7530-0x2b75a0, same table
//  that holds attackA/B/C): shotA/shotB/shotC are per-tier firing animations,
//  shotFinal is reserved for the super (out of scope here), reloadNG/reloadOK
//  gate volleys, and spark + fire are hit/muzzle VFX triggers. Stage channel
//  provenance: fcn.004011f0 loads collision_tama.x ("tama" = ball) as the
//  projectile-only mesh, queried here through game::physics::raycastModel.
//  Capture provenance: battle-hud.webp pins MAIN 6 / CHARGE 2 counters;
//  ammo-bar.webp pins fill fraction = recharge readout (so stocks are
//  fractional floats, not int bullets + timer); Menus/charge pins the two
//  hold thresholds (yellow, then red).
//
//  Only the stock counts (6/2) are capture-pinned. Speeds, damages, costs,
//  recharge rates, and hold times below are provisional tuning until RE'd.
// =============================================================================
#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include <glm/glm.hpp>

#include "assets/xmodel.h"        // xm::Model (read-only use)
#include "physics/raycast.h"      // game::physics::ModelIndex / raycastModel

namespace gameplay {

class Fighter;  // update() damages fighters; defined in gameplay/fighter.h.

// D3DCOLOR replacement, same 0xAARRGGBB wire format as render::DebugColor /
// render::packColor (render/debug_prims.h:51-63). Declared here instead of
// included from there because debug_prims.h pulls <webgpu/webgpu.h> and gpu/gpu.h
// into every TU that includes it (debug_prims.h:40-47), and this simulation must
// stay device-free; tests/fighter_script_test.cpp static_asserts that the two
// layouts agree, so the renderer can consume these values directly.
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

// Tap = quick black shot; Yellow/Red = charged releases at the two hold
// thresholds (spec §3.1); Ex = the Hypermode EX move on S, whose reserved
// animation is "shotFinal" in the binary's string table (@0x2b7590). Each
// tier maps 1:1 to a firing animation state.
enum class ShotTier : std::uint8_t {
    Tap    = 0,  // "shotA"
    Yellow = 1,  // "shotB"
    Red    = 2,  // "shotC"
    Ex     = 3,  // "shotFinal"
};

inline const char* shot_tier_anim(ShotTier t) {
    switch (t) {
        case ShotTier::Tap:    return "shotA";
        case ShotTier::Yellow: return "shotB";
        case ShotTier::Red:    return "shotC";
        case ShotTier::Ex:     return "shotFinal";
    }
    return "shotA";
}

// Per-tier tuning (all provisional — only the 6/2 stock counts are pinned).
struct ShotParams {
    float speed;          // world units/sec
    int   damage;         // HP on a clean fighter hit
    float hitRadius;      // XZ hit radius around the shot
    float lifeSec;        // self-destruct timer (caps range)
    float mainCost;       // MAIN stock consumed (tap tier)
    float chargeCost;     // CHARGE stock consumed (charged tiers)
    int   reloadFrames;   // reloadNG window after firing (60fps frames)
    Rgb   color;          // debug render tint per tier
};

inline ShotParams shot_params(ShotTier t) {
    switch (t) {
        case ShotTier::Tap:
            return {650.0f, 4, 55.0f, 2.5f, 1.0f, 0.0f, 15, packRgb(150, 200, 255)};
        case ShotTier::Yellow:
            return {550.0f, 9, 65.0f, 2.5f, 0.0f, 1.0f, 30, packRgb(255, 230, 80)};
        case ShotTier::Red:
            return {460.0f, 16, 80.0f, 3.0f, 0.0f, 2.0f, 45, packRgb(255, 90, 60)};
        case ShotTier::Ex:
            return {520.0f, 22, 90.0f, 3.0f, 0.0f, 1.0f, 60, packRgb(255, 90, 255)};
    }
    return {650.0f, 4, 55.0f, 2.5f, 1.0f, 0.0f, 15, packRgb(150, 200, 255)};
}

// Fractional ammo stock: the HUD bar fill IS this value / max (ammo-bar.webp),
// so recharge is a continuous refill, not bullets + a separate cooldown icon.
struct AmmoStock {
    float max     = 1.0f;
    float value   = 1.0f;
    float perSec  = 0.5f;  // refill rate (provisional tuning)

    void recharge(double dt, float rateMul = 1.0f) {
        value += perSec * rateMul * static_cast<float>(dt);
        if (value > max) value = max;
    }
    bool can_spend(float n) const { return value >= n; }
    void spend(float n) {
        value -= n;
        if (value < 0.0f) value = 0.0f;
    }
    float frac() const { return (max > 0.0f) ? value / max : 0.0f; }
    int whole() const { return static_cast<int>(value); }  // HUD digit
};

struct Projectile {
    bool          alive = false;
    ShotTier      tier  = ShotTier::Tap;
    glm::vec3     pos   {};
    glm::vec3     vel   {};
    float         age   = 0.0f;
    float         life  = 0.0f;
    Fighter*      owner = nullptr;  // firing fighter; never self-hits, and
                                    // its Hypermode scales the damage dealt

    // DX9 render() split: the shot's unlit cube half-size was a literal at the
    // draw call (projectile.cpp:117) and its colour is the tier tint.
    static constexpr float kCubeSize = 16.0f;
    Rgb color() const { return shot_params(tier).color; }
};

// Hit spark: transient impact marker for the binary's `spark` VFX trigger.
// Rendered as an unlit fading cube (ASCII-era stand-in for the real effect).
struct Spark {
    bool        alive = false;
    glm::vec3   pos   {};
    float       age   = 0.0f;
    float       life  = 0.3f;

    // DX9 render() split (projectile.cpp:122-130): grow + fade over life.
    float life_frac() const { return (life > 0.0f) ? age / life : 0.0f; }
    float size() const { return 14.0f + 46.0f * life_frac(); }
    Rgb color() const {
        const float t = life_frac();
        const int alpha = static_cast<int>(255.0f * (1.0f - t));
        const int green = static_cast<int>(240.0f - 120.0f * t);
        return packArgb(static_cast<std::uint8_t>(alpha), 255,
                        static_cast<std::uint8_t>(green), 120);
    }
};

class ProjectilePool {
public:
    static constexpr std::size_t kMaxShots  = 32;
    static constexpr std::size_t kMaxSparks = 32;

    ProjectilePool() = default;

    void clear();

    // Muzzle spawn in world space; dir must be normalized. Returns false when
    // the pool is full (caller drops the shot — same as the original, which
    // has a fixed tama table and silently refuses overflow).
    bool spawn(const glm::vec3& pos, const glm::vec3& dir,
               ShotTier tier, Fighter* owner);

    // Screen-space-free VFX trigger (binary `fire`/`spark` states).
    void spawn_spark(const glm::vec3& pos, float life = 0.3f);

    // Advance shots (fighter hits → take_damage + spark; tama-channel wall
    // hits → spark; expiry → silent free) and age sparks. fighters[0..n-1]
    // are all potential victims except `owner`. `tamaModel`/`tamaIndex` are the
    // loaded collision_tama.x and its traversal order (physics/raycast.h), or
    // null when the stage ships none (then shots fly until expiry — open-field
    // fallback).
    void update(double dt, Fighter* fighters, int fighterCount,
                const xm::Model* tamaModel,
                const game::physics::ModelIndex* tamaIndex);

    // DX9 render() split: the foundation renderer walks the live entries of
    // these two fixed arrays (index order, no sorting) and draws each as the
    // unlit cube the DX9 pass drew — Projectile::kCubeSize / color() and
    // Spark::size() / color().
    const std::array<Projectile, kMaxShots>& shots() const { return m_shots; }
    const std::array<Spark, kMaxSparks>& sparks() const { return m_sparks; }

    int live_shots() const;

private:
    std::array<Projectile, kMaxShots>  m_shots{};
    std::array<Spark, kMaxSparks>      m_sparks{};
};

}  // namespace gameplay

// =============================================================================
//  PORT NOTES — every deviation from remake/src/gameplay/projectile.h:
//
//  1. Types: D3DXVECTOR3 → glm::vec3; D3DCOLOR/D3DCOLOR_XRGB → gameplay::Rgb /
//     packRgb (same 0xAARRGGBB bits; see the note at the top of this file).
//  2. update()'s D3DXFRAME* tamaRoot → const xm::Model* + const
//     game::physics::ModelIndex* (the ported D3DXIntersect replacement; the
//     index is the flattened traversal order, raycast.h:112-131). The call
//     site uses game::physics::raycastModel, whose RayHit::point/dist carry the
//     same meaning as the DX9 physics::RaycastHit fields used here.
//  3. render(IDirect3DDevice9*) is deleted, not ported: the DX9 pass's cube
//     geometry/state belonged to render::UnlitCubePass. Its data half survives
//     as shots()/sparks() plus Projectile::color()/kCubeSize and
//     Spark::size()/color(), which reproduce the DX9 per-cube arguments
//     exactly (16 units opaque for shots; 14 + 46*t growing, fading sparks).
//  4. No other logic change: spawn caps, tier table, expiry order (age before
//     move, wall before fighters), self-hit exclusion and the spark lifetimes
//     are the source's.
// =============================================================================
