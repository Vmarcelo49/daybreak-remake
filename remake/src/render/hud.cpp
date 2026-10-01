// =============================================================================
//  hud.cpp — see hud.h.
// =============================================================================
#include "render/hud.h"

#include <cstdarg>
#include <cstdint>
#include <cstdio>

namespace daybreak::render {

Hud::~Hud() { unload(); }

bool Hud::init(IDirect3DDevice9* device) {
    if (!device) return false;
    unload();

    HRESULT hr = D3DXCreateFontA(device, 22, 0, FW_BOLD, 1, FALSE,
                                 DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                                 DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
                                 "Arial", &m_font);
    if (FAILED(hr) || !m_font) {
        std::fprintf(stderr, "[daybreak] Hud: D3DXCreateFont failed\n");
        unload();
        return false;
    }

    hr = D3DXCreateSprite(device, &m_sprite);
    if (FAILED(hr) || !m_sprite) {
        std::fprintf(stderr, "[daybreak] Hud: D3DXCreateSprite failed\n");
        unload();
        return false;
    }

    hr = D3DXCreateTexture(device, 1, 1, 1, 0, D3DFMT_A8R8G8B8,
                           D3DPOOL_MANAGED, &m_white);
    if (FAILED(hr) || !m_white) {
        std::fprintf(stderr, "[daybreak] Hud: white texture failed\n");
        unload();
        return false;
    }
    D3DLOCKED_RECT lr{};
    if (SUCCEEDED(m_white->LockRect(0, &lr, nullptr, 0))) {
        *static_cast<uint32_t*>(lr.pBits) = 0xFFFFFFFFu;
        m_white->UnlockRect(0);
    }

    D3DVIEWPORT9 vp{};
    if (SUCCEEDED(device->GetViewport(&vp))) {
        m_viewW = static_cast<int>(vp.Width);
        m_viewH = static_cast<int>(vp.Height);
    }
    return true;
}

void Hud::unload() {
    if (m_font)   { m_font->Release();   m_font = nullptr; }
    if (m_sprite) { m_sprite->Release(); m_sprite = nullptr; }
    if (m_white)  { m_white->Release();  m_white = nullptr; }
}

void Hud::begin(IDirect3DDevice9* device) {
    if (m_sprite) m_sprite->Begin(D3DXSPRITE_ALPHABLEND);
    (void)device;
}

void Hud::text(int x, int y, D3DCOLOR color, const char* fmt, ...) {
    if (!m_font || !fmt) return;
    char buf[256];
    va_list ap;
    va_start(ap, fmt);
    std::vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    RECT rc{ x, y, x + 760, y + 30 };
    m_font->DrawTextA(nullptr, buf, -1, &rc, DT_LEFT | DT_NOCLIP, color);
}

void Hud::centered(int y, int h, D3DCOLOR color, const char* fmt, ...) {
    if (!m_font || !fmt) return;
    char buf[256];
    va_list ap;
    va_start(ap, fmt);
    std::vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    RECT rc{ 0, y, m_viewW, y + h };
    m_font->DrawTextA(nullptr, buf, -1, &rc,
                      DT_CENTER | DT_VCENTER | DT_NOCLIP, color);
}

void Hud::bar(int x, int y, int w, int h, float frac,
              D3DCOLOR fill, D3DCOLOR back) {
    if (!m_sprite || !m_white) return;
    if (frac < 0.0f) frac = 0.0f;
    if (frac > 1.0f) frac = 1.0f;

    D3DXMATRIX scale, trans, mat;
    // NOTE: sprite position must be origin — the transform already places
    // the quad (transform applies on top of the position argument).
    D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);

    // Back (full width).
    D3DXMatrixScaling(&scale, static_cast<float>(w), static_cast<float>(h), 1.0f);
    D3DXMatrixTranslation(&trans, static_cast<float>(x), static_cast<float>(y), 0.0f);
    mat = scale * trans;
    m_sprite->SetTransform(&mat);
    m_sprite->Draw(m_white, nullptr, nullptr, &pos, back);

    // Fill (fractional width).
    const int fw = static_cast<int>(w * frac);
    if (fw > 0) {
        D3DXMatrixScaling(&scale, static_cast<float>(fw), static_cast<float>(h), 1.0f);
        mat = scale * trans;
        m_sprite->SetTransform(&mat);
        m_sprite->Draw(m_white, nullptr, nullptr, &pos, fill);
    }
}

void Hud::end() {
    if (m_sprite) m_sprite->End();
}

} // namespace daybreak::render
