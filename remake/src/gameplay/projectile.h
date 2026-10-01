// =============================================================================
//  projectile.h — shot tiers, fractional ammo stocks, projectile pool, sparks.
//
//  RE provenance (DaybreakDX.exe string table @0x2b7530-0x2b75a0, same table
//  that holds attackA/B/C): shotA/shotB/shotC are per-tier firing animations,
//  shotFinal is reserved for the super (out of scope here), reloadNG/reloadOK
//  gate volleys, and spark + fire are hit/muzzle VFX triggers. Stage channel
//  provenance: fcn.004011f0 loads collision_tama.x ("tama" = ball) as the
//  projectile-only mesh, queried here through physics::raycast_model.
//  Capture provenance: battle-hud.webp pins MAIN 6 / CHARGE 2 counters;
//  ammo-bar.webp pins fill fraction = recharge readout (so stocks are
//  fractional floats, not int bullets + timer); Menus/charge pins the two
//  hold thresholds (yellow, then red).
//
//  Only the stock counts (6/2) are capture-pinned. Speeds, damages, costs,
//  recharge rates, and hold times below are provisional tuning until RE'd.
// =============================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <array>
#include <cstddef>
#include <cstdint>

namespace daybreak::gameplay {

class Fighter;  // update() damages fighters; defined in gameplay/fighter.h.

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
    D3DCOLOR color;       // debug render tint per tier
};

inline ShotParams shot_params(ShotTier t) {
    switch (t) {
        case ShotTier::Tap:
            return {650.0f, 4, 55.0f, 2.5f, 1.0f, 0.0f, 15, D3DCOLOR_XRGB(150, 200, 255)};
        case ShotTier::Yellow:
            return {550.0f, 9, 65.0f, 2.5f, 0.0f, 1.0f, 30, D3DCOLOR_XRGB(255, 230, 80)};
        case ShotTier::Red:
            return {460.0f, 16, 80.0f, 3.0f, 0.0f, 2.0f, 45, D3DCOLOR_XRGB(255, 90, 60)};
        case ShotTier::Ex:
            return {520.0f, 22, 90.0f, 3.0f, 0.0f, 1.0f, 60, D3DCOLOR_XRGB(255, 90, 255)};
    }
    return {650.0f, 4, 55.0f, 2.5f, 1.0f, 0.0f, 15, D3DCOLOR_XRGB(150, 200, 255)};
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
    D3DXVECTOR3   pos   {};
    D3DXVECTOR3   vel   {};
    float         age   = 0.0f;
    float         life  = 0.0f;
    Fighter*      owner = nullptr;  // firing fighter; never self-hits, and
                                    // its Hypermode scales the damage dealt
};

// Hit spark: transient impact marker for the binary's `spark` VFX trigger.
// Rendered as an unlit fading cube (ASCII-era stand-in for the real effect).
struct Spark {
    bool        alive = false;
    D3DXVECTOR3 pos   {};
    float       age   = 0.0f;
    float       life  = 0.3f;
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
    bool spawn(const D3DXVECTOR3& pos, const D3DXVECTOR3& dir,
               ShotTier tier, Fighter* owner);

    // Screen-space-free VFX trigger (binary `fire`/`spark` states).
    void spawn_spark(const D3DXVECTOR3& pos, float life = 0.3f);

    // Advance shots (fighter hits → take_damage + spark; tama-channel wall
    // hits → spark; expiry → silent free) and age sparks. fighters[0..n-1]
    // are all potential victims except `owner`. tamaRoot is the loaded
    // collision_tama.x root frame, or nullptr when the stage ships none
    // (then shots fly until expiry — open-field fallback).
    void update(double dt, Fighter* fighters, int fighterCount,
                D3DXFRAME* tamaRoot);

    // Unlit debug render (colored cubes per tier + fading spark cubes).
    // Manages its own lighting/alpha states and restores them.
    void render(IDirect3DDevice9* device);

    int live_shots() const;

private:
    std::array<Projectile, kMaxShots>  m_shots{};
    std::array<Spark, kMaxSparks>      m_sparks{};
};

} // namespace daybreak::gameplay
