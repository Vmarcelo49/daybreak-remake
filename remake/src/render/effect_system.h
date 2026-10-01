// =============================================================================
//  effect_system.h — D3DX effect (.fx-compiled blob) registry.
//
//  Loads the 10 compiled effects extracted from DaybreakDX.exe
//  (FUN_0064ff80, "CreateAllShaders") from assets/shaders/effect_N.bin,
//  mirroring mvp/src/shader_load.c — with one deliberate divergence: mvp
//  warns via MessageBox and continues with NULL slots, while we fail
//  loudly (return false) because rendering without effects is a bug here,
//  not a degraded mode.
//
//  Technique/pass binding per mesh category is fresh RE (mvp never bound
//  any) — see docs/port-from-mvp-plan.md P3.1. Until then this owns the
//  ID3DXEffect lifetime and hands out raw pointers; callers must NOT
//  release them (unload_all() invalidates everything).
// =============================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <string>

namespace daybreak::render {

class EffectSystem {
public:
    static constexpr int kEffectCount = 10;  // NUM_SHADERS in the original

    EffectSystem() = default;
    ~EffectSystem();

    EffectSystem(const EffectSystem&)            = delete;
    EffectSystem& operator=(const EffectSystem&) = delete;

    // Loads assets/shaders/effect_0..9.bin via D3DXCreateEffect.
    // shader_dir defaults to "assets/shaders" (resolved relative to CWD).
    // Returns false (after logging which slot failed) if any effect is
    // missing or fails to compile — caller should abort startup.
    bool load(IDirect3DDevice9* device,
              const std::string& shader_dir = "assets/shaders");

    void unload_all();

    // Raw access; nullptr if not loaded. Do NOT release.
    ID3DXEffect* effect(int index) const;
    int          loaded_count() const { return m_loaded; }
    bool         all_loaded() const { return m_loaded == kEffectCount; }

private:
    ID3DXEffect* m_effects[kEffectCount] = {};
    int          m_loaded = 0;
};

} // namespace daybreak::render
