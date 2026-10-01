// =============================================================================
//  debug_prim.h — placeholder 3D primitives for un-RE'd VFX.
//
//  Shots, hit sparks, and the hypermode aura are all stand-ins until the real
//  effects are decoded from the game's 10 compiled shaders (effect_system.h,
//  docs/port-from-mvp-plan.md P3.1). They share one unlit, unculled,
//  optionally alpha-blended cube draw — kept here rather than duplicated per
//  caller so state save/restore stays in one place.
// =============================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

namespace daybreak::render {

// Scoped render-state override for unlit cube drawing. Saves the states it
// touches and restores them on destruction, so callers can draw any number
// of cubes inside one pass.
//
// Two states matter beyond the obvious:
//   * World matrix is forced to identity — DrawPrimitiveUP is transformed by
//     D3DTS_WORLD, and callers pass world-space centres. Without this the
//     cubes inherit the last model's matrix and land in the wrong place.
//   * Alpha test is forced off — the scene enables it (REF 8, GE) for foliage
//     cutouts, and a NULL texture makes the fixed-function alpha come out 0,
//     so every cube pixel would be discarded.
//   * Texture stage 0 is switched to SELECTARG1(DIFFUSE). With the default
//     MODULATE(TEXTURE, DIFFUSE) and no texture bound, the stage samples a
//     NULL texture and the cubes come out black (or, additively blended,
//     invisible) — vertex colour must drive both colour and alpha here.
class UnlitCubePass {
public:
    // `alphaBlend` enables src-alpha/one blending (fire-and-forget VFX);
    // leave false for opaque stand-ins.
    // `worldSpace` forces an identity world matrix, for callers passing world
    // coordinates (shots, sparks). Pass false to keep the current matrix —
    // model-attached VFX (the Hypermode aura) then rides the model's
    // transform with local coordinates.
    UnlitCubePass(IDirect3DDevice9* device, bool alphaBlend,
                  bool worldSpace = true);
    ~UnlitCubePass();

    UnlitCubePass(const UnlitCubePass&)            = delete;
    UnlitCubePass& operator=(const UnlitCubePass&) = delete;

    void draw(const D3DXVECTOR3& center, float halfExtent, D3DCOLOR color);

private:
    IDirect3DDevice9* m_device = nullptr;
    DWORD m_prevLighting = TRUE;
    DWORD m_prevCull     = D3DCULL_CCW;
    DWORD m_prevBlend    = FALSE;
    DWORD m_prevAlphaTest = FALSE;
    DWORD m_prevColorOp = D3DTOP_MODULATE;
    DWORD m_prevColorArg1 = D3DTA_TEXTURE;
    DWORD m_prevAlphaOp = D3DTOP_SELECTARG1;
    DWORD m_prevAlphaArg1 = D3DTA_TEXTURE;
    DWORD m_prevFvf = 0;
    bool  m_worldSpace = true;
    D3DXMATRIX m_prevWorld;
};

} // namespace daybreak::render
