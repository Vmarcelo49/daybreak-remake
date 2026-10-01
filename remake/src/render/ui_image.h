// =============================================================================
//  ui_image.h — load BMP/PNG/CNV from .DAT bundle → DX9 texture.
//
//  Supports:
//    - BMP/PNG/JPG/DDS via D3DXCreateTextureFromFileInMemory
//    - CNV (Higurashi Daybreak custom image format) via manual decode →
//      D3DXCreateTexture (D3DFMT_A8R8G8B8)
//
//  CNV format (from Go reference convert/image.go):
//    [0]      bpp (uint8) — 24 or 32
//    [1:5]    width (uint32 LE)
//    [5:9]    height (uint32 LE)
//    [9:13]   width2 (uint32 LE) — redundant, must match width
//    [13:16]  unknown (3 bytes)
//    [16]     zero (uint8, must be 0)
//    [17+]    pixel data (BGR for 24bpp, BGRA for 32bpp)
// =============================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include <cstdint>
#include <string>

namespace daybreak {

namespace assets { class AssetManager; }

namespace render {

class UIImage {
public:
    UIImage() = default;
    ~UIImage();

    UIImage(const UIImage&)            = delete;
    UIImage& operator=(const UIImage&) = delete;

    // Loads an image from an in-memory byte buffer.  Auto-detects format:
    // CNV (if first byte is 24 or 32 and size matches), BMP/ PNG/JPG via D3DX.
    bool load_from_memory(IDirect3DDevice9* device,
                          const uint8_t* bytes, size_t size);

    // Loads an image from the AssetManager by asset name.
    bool load_from_asset(assets::AssetManager* am,
                         IDirect3DDevice9* device,
                         const std::string& asset_name);

    void unload();

    // Detaches the decoded texture: returns it (caller owns it and must
    // Release) and resets this UIImage to unloaded (vertex buffer freed,
    // dimensions zeroed).  Used by AssetManager::load_texture so bundle
    // textures share UIImage's CNV + D3DX decode paths.
    IDirect3DTexture9* release_texture();

    bool is_loaded() const { return m_texture != nullptr; }
    int  width()     const { return m_width; }
    int  height()    const { return m_height; }

    void render_fullscreen(IDirect3DDevice9* device);
    void render_at(IDirect3DDevice9* device, int x, int y,
                   int w = -1, int h = -1);

private:
    IDirect3DTexture9*       m_texture = nullptr;
    IDirect3DVertexBuffer9*  m_vb      = nullptr;
    int                      m_width   = 0;
    int                      m_height  = 0;

    bool load_cnv(IDirect3DDevice9* device, const uint8_t* bytes, size_t size);
    bool load_standard(IDirect3DDevice9* device, const uint8_t* bytes, size_t size);
    void ensure_vb(IDirect3DDevice9* device);
};

} // namespace render
} // namespace daybreak
