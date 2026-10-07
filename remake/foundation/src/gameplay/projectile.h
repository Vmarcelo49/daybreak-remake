// =============================================================================
//  projectile.h — shot tiers, fractional ammo stocks, projectile pool, sparks.
//
//  Ported to the SDL3 + WebGPU foundation (docs/FULL-REPLACEMENT-PLAN.md §5
//  item 2b) from remake/src/gameplay/projectile.h: logic only, D3D-free, names
//  kept identical so the two can be diffed. Deviations are listed in "PORT
//  NOTES" at the bottom of this header.
//
//  The string table @0x2b7530-0x2b75a0 contains shotA/shotB/shotC/shotFinal
//  alongside attackA/B/C, but the decompiled corpus does not establish that these
//  are per-tier firing animations or map them to the port's tap/yellow/red tiers.
//  The port keeps those names as provisional labels. Stage channel
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

#include <algorithm>
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

// Tap/Yellow/Red and their hold thresholds are port tiers; the string-table labels
// below are provisional names, not a recovered tier-to-firing-animation mapping.
// Ex follows the remake's Hypermode path; the original has a move-503 finisher, but
// the label "shotFinal" does not by itself prove an animation binding.
enum class ShotTier : std::uint8_t {
    Tap    = 0,
    Yellow = 1,
    Red    = 2,
    Ex     = 3,
};

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
// The HUD *count* is a different thing: whole shots remaining (the magazine's
// num), not raw pool units. Time-valued magazines (type 1/2) size the pool as
// num*reloadTime and spend reloadTime per shot, so rena's tap pool reads 1800
// while the count must read 6 — unitsPerShot bridges the two.
struct AmmoStock {
    float max     = 1.0f;
    float value   = 1.0f;
    float perSec  = 0.5f;  // refill rate (provisional tuning)
    float unitsPerShot = 1.0f;  // pool units per displayed shot (magazine reloadTime)

    void recharge(double dt, float rateMul = 1.0f) {
        value = std::min(value + perSec * rateMul * static_cast<float>(dt), max);
    }
    bool can_spend(float n) const { return value >= n; }
    void spend(float n) { value = std::max(value - n, 0.0f); }
    float frac() const { return (max > 0.0f) ? value / max : 0.0f; }
    int whole() const {  // HUD digit: whole SHOTS left, never pool units
        if (unitsPerShot <= 0.0f) return static_cast<int>(value);
        return std::max(static_cast<int>(value / unitsPerShot), 0);
    }
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
    // The impact effect id the shot was FIRED with (bullet record +0x70, via
    // Fighter::impact_effect). Carried on the projectile so the contact can report the
    // effect the shot would have spawned in the original (FUN_00637950:221-228) without
    // re-deriving the weapon binding at hit time (issue #17).
    int           impactEffect = -1;

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
    // are potential victims except `owner`; when `fighterSides` is supplied,
    // teammates are excluded too. `tamaModel`/`tamaIndex` are the loaded
    // collision_tama.x and its traversal order (physics/raycast.h), or null
    // when the stage ships none (then shots fly until expiry — open-field
    // fallback).
    void update(double dt, Fighter* fighters, int fighterCount,
                const xm::Model* tamaModel,
                const game::physics::ModelIndex* tamaIndex,
                const int* fighterSides = nullptr);

    // Shot -> fighter contacts the last update() resolved, in the pool's own
    // iteration order (issue #16). The pool owns the hit test, so it reports the
    // pair instead of letting the caller re-derive it; a volley can connect with
    // several fighters in one frame, hence an array rather than one slot.
    // Cleared at the top of every update().
    struct ShotContact {
        int shooter = -1;  // index into the fighters array update() was given
        int victim  = -1;
        glm::vec3 point{0.f};  // where the shot met the victim (issue #17 effects)
        int effect = -1;       // the shot's impact effect id, -1 when unbound
    };
    int contact_count() const { return m_contactCount; }
    const ShotContact& contact(int i) const { return m_contacts[static_cast<size_t>(i)]; }

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
    std::array<ShotContact, kMaxShots> m_contacts{};
    int                                m_contactCount = 0;
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
