// =============================================================================
//  asset_manager.cpp — see asset_manager.h for design rationale.
// =============================================================================
#include "asset_manager.h"

#include <cstdio>
#include <utility>

#include "render/ui_image.h"

namespace daybreak::assets {

AssetManager::~AssetManager() { unload_all(); }

daybreak::XModel* AssetManager::load_x(const std::string& name) {
    if (!m_device) {
        std::fprintf(stderr, "[daybreak] AssetManager: no device set\n");
        return nullptr;
    }

    // 1. Cache lookup — linear scan is fine, cache size stays small
    //    (tens of unique meshes per match, not thousands).
    for (auto& c : m_models) {
        if (c.name == name) return c.model.get();
    }

    // 2. Find the file in any registered bundle (first match wins).
    const daybreak::file_parser::DatFileEntry* entry = nullptr;
    daybreak::file_parser::DatBundle*          src_bundle = nullptr;
    for (daybreak::file_parser::DatBundle* b : m_bundles) {
        if (!b) continue;
        entry = b->find_by_name(name);
        if (entry) {
            src_bundle = b;
            break;
        }
    }
    if (!entry || !src_bundle) {
        std::fprintf(stderr,
                     "[daybreak] AssetManager: file not found in any bundle: %s\n",
                     name.c_str());
        return nullptr;
    }

    // 3. Read + decrypt the payload into a memory buffer.
    std::vector<uint8_t> bytes;
    if (!src_bundle->read_file(*entry, bytes)) {
        std::fprintf(stderr,
                     "[daybreak] AssetManager: read_file failed for %s\n",
                     name.c_str());
        return nullptr;
    }

    // 4. Compute the texture search dir from the asset's path.
    //    Textures are referenced by relative filename in the .X file
    //    (e.g. TextureFilename { "rika_diffuse.bmp"; }), and the original
    //    game stores them in the same directory as the .X.  We derive
    //    the directory from the asset's in-bundle path.
    //
    //    The .X file paths in the bundle use forward slashes
    //    ("data/rika/01.X").  We need to:
    //      - Convert to wide string for D3DXCreateTextureFromFileW
    //      - Extract just the directory portion
    //    The actual textures are also stored in the .DAT bundle, so
    //    D3DXCreateTextureFromFileW will FAIL — we'd need to intercept
    //    texture loading.  We pass an empty dir (no textures loaded yet)
    //    until a bundle-backed texture provider exists.
    std::wstring texture_dir;

    // 5. Parse + upload to GPU.
    auto model = std::make_unique<daybreak::XModel>();
    if (!model->load_from_memory(m_device, bytes.data(), bytes.size(),
                                  name, texture_dir)) {
        // load_from_memory already logged the error.
        return nullptr;
    }

    // 6. Cache + return.
    CachedModel c;
    c.name  = name;
    c.model = std::move(model);
    m_models.push_back(std::move(c));
    return m_models.back().model.get();
}

bool AssetManager::read_file(const std::string& name,
                              std::vector<uint8_t>& out) {
    for (daybreak::file_parser::DatBundle* b : m_bundles) {
        if (!b) continue;
        const daybreak::file_parser::DatFileEntry* e = b->find_by_name(name);
        if (e) {
            return b->read_file(*e, out);
        }
    }
    return false;
}

bool AssetManager::has_file(const std::string& name) const {
    for (daybreak::file_parser::DatBundle* b : m_bundles) {
        if (b && b->find_by_name(name)) return true;
    }
    return false;
}

void AssetManager::unload_all() {
    for (auto& t : m_textures) {
        if (t.texture) {
            t.texture->Release();
            t.texture = nullptr;
        }
    }
    m_textures.clear();
    m_models.clear();
    // m_bundles is not owned — don't touch.
}

IDirect3DTexture9* AssetManager::load_texture(const std::string& name) {
    if (!m_device) {
        std::fprintf(stderr, "[daybreak] AssetManager: no device set\n");
        return nullptr;
    }

    for (auto& t : m_textures) {
        if (t.name == name) return t.texture;
    }

    std::vector<uint8_t> bytes;
    if (!read_file(name, bytes)) {
        std::fprintf(stderr,
                     "[daybreak] AssetManager: texture not found in any bundle: %s\n",
                     name.c_str());
        return nullptr;
    }

    render::UIImage img;
    if (!img.load_from_memory(m_device, bytes.data(), bytes.size())) {
        // load_from_memory already logged the decode error.  If the
        // payload is CNV, convert it offline with tools/asset-tools/
        // (cnv_convert.py) — this path only decodes what UIImage knows.
        return nullptr;
    }

    IDirect3DTexture9* tex = img.release_texture();
    if (!tex) return nullptr;

    CachedTexture c;
    c.name    = name;
    c.texture = tex;
    m_textures.push_back(c);
    return tex;
}

} // namespace daybreak::assets
