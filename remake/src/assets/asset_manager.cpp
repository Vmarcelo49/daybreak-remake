// =============================================================================
//  asset_manager.cpp — see asset_manager.h for design rationale.
// =============================================================================
#include "asset_manager.h"

#include <cstdio>
#include <utility>

#include "file_parser/text_codec.h"
#include "render/ui_image.h"

namespace daybreak::assets {

namespace {

// White-key a decal texture: texels that are exactly white become fully
// transparent (baked blob shadows are white cards with a dark blob; the
// original devs key on the white). Runs on the A8R8G8B8 MANAGED textures
// UIImage produces. Idempotent — re-keying changes nothing.
void key_out_white(IDirect3DTexture9* tex) {
    if (!tex) return;
    D3DSURFACE_DESC desc;
    if (FAILED(tex->GetLevelDesc(0, &desc))) return;
    if (desc.Format != D3DFMT_A8R8G8B8) return;
    D3DLOCKED_RECT lr;
    if (FAILED(tex->LockRect(0, &lr, nullptr, 0))) return;
    for (UINT y = 0; y < desc.Height; ++y) {
        auto* row = reinterpret_cast<uint32_t*>(
            static_cast<uint8_t*>(lr.pBits) + y * lr.Pitch);
        for (UINT x = 0; x < desc.Width; ++x) {
            if ((row[x] & 0x00FFFFFFu) == 0x00FFFFFFu) row[x] = 0x00000000u;
        }
    }
    tex->UnlockRect(0);
}

bool is_shadow_decal(const std::string& refUtf8) {
    return refUtf8.find("shadow") != std::string::npos;
}

} // namespace

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

    // 4. Resolve material textures from the bundle. The .X references
    //    bare Shift-JIS filenames ("服.bmp") that live next to the model
    //    as .cnv in the same bundle dir (no .bmp ships anywhere — verified
    //    across all bundles). Candidates tried in order: exact name,
    //    stem + .cnv, stem + .bmp. has_file() guards so load_texture only
    //    logs real decode failures, not expected misses.
    std::string dir;
    {
        const size_t slash = name.find_last_of('/');
        if (slash != std::string::npos) dir = name.substr(0, slash + 1);
    }
    auto resolve = [this, &dir](const std::string& ref) -> IDirect3DTexture9* {
        // Bundle entry names are UTF-8 (decoded at ingest); .X texture refs
        // are raw Shift-JIS — convert once so non-ASCII stems can match.
        const std::string refUtf8 =
            file_parser::text_codec::shift_jis_to_utf8(ref);
        const size_t dot = refUtf8.find_last_of('.');
        const std::string stem = (dot == std::string::npos) ? refUtf8
                                                            : refUtf8.substr(0, dot);
        const char* cands[3] = { nullptr, nullptr, nullptr };
        std::string c0 = dir + ref;
        std::string c1 = dir + stem + ".cnv";
        std::string c2 = dir + stem + ".bmp";
        cands[0] = c0.c_str();
        cands[1] = c1.c_str();
        cands[2] = c2.c_str();
        for (const char* c : cands) {
            if (!has_file(c)) continue;
            IDirect3DTexture9* tex = load_texture(c);
            // Shadow decals double as their own mask: white keys out
            // (alpha-tested away by the scene), the dark blob multiplies.
            // Mutating the cached texture is contained: only shadow*
            // refs resolve to these files (verified in the material
            // inventory), and re-keying is idempotent.
            if (tex && is_shadow_decal(refUtf8)) key_out_white(tex);
            return tex;
        }
        std::fprintf(stderr,
                     "[daybreak] AssetManager: texture miss: %s (tried %s, %s)\n",
                     refUtf8.c_str(), c1.c_str(), c2.c_str());
        return nullptr;
    };

    // 5. Parse + upload to GPU (disk texture lookup skipped: empty dir —
    //    bundle resolution below is the only texture path).
    auto model = std::make_unique<daybreak::XModel>();
    if (!model->load_from_memory(m_device, bytes.data(), bytes.size(),
                                  name, std::wstring())) {
        // load_from_memory already logged the error.
        return nullptr;
    }
    model->resolve_material_textures(resolve);

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
