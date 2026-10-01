// =============================================================================
//  hud.h — battle HUD: text + proportional bars via D3DXFont/D3DXSprite.
//
//  Layout mirrors the captured HUD (docs/reference/battle-hud.webp):
//  balloon % + LIMIT top corners, MAIN/CHARGE counters + HP bottom-right,
//  limit gauge bottom-left, contextual stamina. Bars are fractional —
//  fill fraction IS the readout (docs/reference/ammo-bar.webp).
//  Text is ASCII-only for now (Wine often lacks CJK fonts); the KO sting
//  prints "KO!" until JP text rendering lands.
// =============================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

namespace daybreak::render {

class Hud {
public:
    Hud() = default;
    ~Hud();

    Hud(const Hud&)            = delete;
    Hud& operator=(const Hud&) = delete;

    bool init(IDirect3DDevice9* device);
    void unload();
    bool is_loaded() const { return m_font != nullptr; }

    // Call after the 3D scene, before EndScene. Text/bars draw on top.
    void begin(IDirect3DDevice9* device);
    void text(int x, int y, D3DCOLOR color, const char* fmt, ...);
    void centered(int y, int h, D3DCOLOR color, const char* fmt, ...);
    void bar(int x, int y, int w, int h, float frac,
             D3DCOLOR fill, D3DCOLOR back);
    void end();

private:
    ID3DXFont*         m_font = nullptr;
    ID3DXSprite*       m_sprite = nullptr;
    IDirect3DTexture9* m_white = nullptr;  // 1x1, tinted per bar
    int                m_viewW = 800;
    int                m_viewH = 600;
};

} // namespace daybreak::render
