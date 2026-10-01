// =============================================================================
//  ui_image.cpp — BMP/PNG/CNV → DX9 texture.
// =============================================================================
#include "ui_image.h"

#include <cstdio>
#include <cstring>
#include <vector>

#include "assets/asset_manager.h"

namespace daybreak::render {

struct VertexTVD {
    float    x, y, z, rhw;
    uint32_t color;
    float    u, v;
};
constexpr DWORD kFVF_TVD = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;

UIImage::~UIImage() { unload(); }

// Check if a byte buffer is a CNV file.
// The CNV format has some quirks: sometimes bpp=24 but the file size
// implies 32bpp (4 bytes/pixel).  We trust the file size over the header.
static bool is_cnv(const uint8_t* bytes, size_t size) {
    if (size < 17) return false;
    uint8_t bpp = bytes[0];
    if (bpp != 24 && bpp != 32) return false;
    uint32_t w   = static_cast<uint32_t>(bytes[1]) | (bytes[2] << 8) | (bytes[3] << 16) | (bytes[4] << 24);
    uint32_t h   = static_cast<uint32_t>(bytes[5]) | (bytes[6] << 8) | (bytes[7] << 16) | (bytes[8] << 24);
    uint32_t w2  = static_cast<uint32_t>(bytes[9]) | (bytes[10] << 8) | (bytes[11] << 16) | (bytes[12] << 24);
    if (w == 0 || h == 0 || w > 8192 || h > 8192) return false;
    if (w != w2) return false;
    if (bytes[16] != 0) return false;
    uint32_t size24 = 17 + w * h * 3;
    uint32_t size32 = 17 + w * h * 4;
    return size == size24 || size == size32;
}

bool UIImage::load_cnv(IDirect3DDevice9* device, const uint8_t* bytes, size_t size) {
    uint8_t header_bpp = bytes[0];
    uint32_t w = static_cast<uint32_t>(bytes[1]) | (bytes[2] << 8) | (bytes[3] << 16) | (bytes[4] << 24);
    uint32_t h = static_cast<uint32_t>(bytes[5]) | (bytes[6] << 8) | (bytes[7] << 16) | (bytes[8] << 24);

    uint32_t payload = static_cast<uint32_t>(size) - 17;
    uint32_t pixels = w * h;
    uint32_t bytesPerPixel;
    if (payload == pixels * 4) {
        bytesPerPixel = 4;  // 32bpp BGRA
    } else if (payload == pixels * 3) {
        bytesPerPixel = 3;  // 24bpp BGR
    } else {
        bytesPerPixel = header_bpp / 8;
        if (bytesPerPixel != 3 && bytesPerPixel != 4) bytesPerPixel = 4;
    }

    std::printf("[daybreak] UIImage: CNV %ux%u (header_bpp=%u, actual_bpp=%u, size=%zu)\n",
                w, h, header_bpp, bytesPerPixel * 8, size);

    if (FAILED(D3DXCreateTexture(device, w, h, 1, 0, D3DFMT_A8R8G8B8,
                                  D3DPOOL_MANAGED, &m_texture))) {
        std::fprintf(stderr, "[daybreak] UIImage: D3DXCreateTexture failed for CNV\n");
        return false;
    }

    D3DLOCKED_RECT lr;
    if (FAILED(m_texture->LockRect(0, &lr, nullptr, 0))) {
        m_texture->Release(); m_texture = nullptr;
        return false;
    }

    const uint8_t* src = bytes + 17;  // skip CNV header
    uint8_t* dst = static_cast<uint8_t*>(lr.pBits);

    for (uint32_t y = 0; y < h; ++y) {
        uint8_t* drow = dst + y * lr.Pitch;
        const uint8_t* srow = src + y * w * bytesPerPixel;
        for (uint32_t x = 0; x < w; ++x) {
            // CNV stores BGR (24bpp) or BGRA (32bpp)
            drow[x*4 + 0] = srow[x*bytesPerPixel + 0];  // B
            drow[x*4 + 1] = srow[x*bytesPerPixel + 1];  // G
            drow[x*4 + 2] = srow[x*bytesPerPixel + 2];  // R
            drow[x*4 + 3] = (bytesPerPixel == 4) ? srow[x*bytesPerPixel + 3] : 255;  // A
        }
    }

    m_texture->UnlockRect(0);
    m_width = static_cast<int>(w);
    m_height = static_cast<int>(h);
    // Log already done above with header_bpp info.
    (void)header_bpp;
    return true;
}

bool UIImage::load_standard(IDirect3DDevice9* device, const uint8_t* bytes, size_t size) {
    HRESULT hr = D3DXCreateTextureFromFileInMemory(
        device, bytes, static_cast<UINT>(size), &m_texture);
    if (FAILED(hr)) return false;
    D3DSURFACE_DESC desc;
    if (SUCCEEDED(m_texture->GetLevelDesc(0, &desc))) {
        m_width = static_cast<int>(desc.Width);
        m_height = static_cast<int>(desc.Height);
    }
    return true;
}

bool UIImage::load_from_memory(IDirect3DDevice9* device, const uint8_t* bytes, size_t size) {
    unload();
    if (!device || !bytes || size == 0) return false;

    if (is_cnv(bytes, size)) {
        if (load_cnv(device, bytes, size)) return true;
    }

    // Standard formats (BMP, PNG, JPG, DDS, TGA).
    if (load_standard(device, bytes, size)) return true;

    std::fprintf(stderr, "[daybreak] UIImage: failed to decode image (%zu bytes)\n", size);
    return false;
}

bool UIImage::load_from_asset(daybreak::assets::AssetManager* am,
                               IDirect3DDevice9* device,
                               const std::string& asset_name) {
    if (!am) return false;
    std::vector<uint8_t> bytes;
    if (!am->read_file(asset_name, bytes)) {
        std::fprintf(stderr, "[daybreak] UIImage: asset not found: %s\n",
                     asset_name.c_str());
        return false;
    }
    return load_from_memory(device, bytes.data(), bytes.size());
}

void UIImage::unload() {
    if (m_vb)      { m_vb->Release();      m_vb = nullptr; }
    if (m_texture) { m_texture->Release(); m_texture = nullptr; }
    m_width = 0;
    m_height = 0;
}

IDirect3DTexture9* UIImage::release_texture() {
    if (m_vb) { m_vb->Release(); m_vb = nullptr; }
    IDirect3DTexture9* tex = m_texture;
    m_texture = nullptr;
    m_width = 0;
    m_height = 0;
    return tex;
}

void UIImage::ensure_vb(IDirect3DDevice9* device) {
    if (m_vb) return;
    device->CreateVertexBuffer(4 * sizeof(VertexTVD), D3DUSAGE_WRITEONLY,
                                kFVF_TVD, D3DPOOL_MANAGED, &m_vb, nullptr);
}

static void fill_quad(VertexTVD* v, float x, float y, float w, float h,
                      float uw, float vh, uint32_t color) {
    v[0] = { x,     y,     0.0f, 1.0f, color, 0.0f, 0.0f };
    v[1] = { x + w, y,     0.0f, 1.0f, color, uw,   0.0f };
    v[2] = { x,     y + h, 0.0f, 1.0f, color, 0.0f, vh   };
    v[3] = { x + w, y + h, 0.0f, 1.0f, color, uw,   vh   };
}

static void render_quad(IDirect3DDevice9* device, IDirect3DTexture9* tex,
                         IDirect3DVertexBuffer9* vb, D3DVIEWPORT9& vp,
                         int x, int y, int w, int h) {
    VertexTVD verts[4];
    fill_quad(verts,
              static_cast<float>(x), static_cast<float>(y),
              static_cast<float>(w), static_cast<float>(h),
              1.0f, 1.0f, 0xFFFFFFFF);
    void* p = nullptr;
    if (SUCCEEDED(vb->Lock(0, sizeof(verts), &p, 0))) {
        std::memcpy(p, verts, sizeof(verts));
        vb->Unlock();
    }
    DWORD oldFVF, oldLighting, oldZ, oldAlpha;
    IDirect3DBaseTexture9* oldTex = nullptr;
    device->GetFVF(&oldFVF);
    device->GetRenderState(D3DRS_LIGHTING, &oldLighting);
    device->GetRenderState(D3DRS_ZENABLE, &oldZ);
    device->GetRenderState(D3DRS_ALPHABLENDENABLE, &oldAlpha);
    device->GetTexture(0, &oldTex);
    if (oldTex) oldTex->Release();
    device->SetFVF(kFVF_TVD);
    device->SetRenderState(D3DRS_LIGHTING, FALSE);
    device->SetRenderState(D3DRS_ZENABLE, FALSE);
    device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    device->SetTexture(0, tex);
    device->SetStreamSource(0, vb, 0, sizeof(VertexTVD));
    device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
    device->SetFVF(oldFVF);
    device->SetRenderState(D3DRS_LIGHTING, oldLighting);
    device->SetRenderState(D3DRS_ZENABLE, oldZ);
    device->SetRenderState(D3DRS_ALPHABLENDENABLE, oldAlpha);
    device->SetTexture(0, oldTex);
    if (oldTex) oldTex->Release();
}

void UIImage::render_fullscreen(IDirect3DDevice9* device) {
    if (!m_texture || !device) return;
    ensure_vb(device);
    D3DVIEWPORT9 vp;
    device->GetViewport(&vp);
    render_quad(device, m_texture, m_vb, vp,
                vp.X, vp.Y, vp.Width, vp.Height);
}

void UIImage::render_at(IDirect3DDevice9* device, int x, int y, int w, int h) {
    if (!m_texture || !device) return;
    ensure_vb(device);
    D3DVIEWPORT9 vp;
    device->GetViewport(&vp);
    if (w < 0) w = m_width;
    if (h < 0) h = m_height;
    render_quad(device, m_texture, m_vb, vp, x, y, w, h);
}

} // namespace daybreak::render
