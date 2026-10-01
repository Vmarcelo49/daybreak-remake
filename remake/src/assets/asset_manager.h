// =============================================================================
//  asset_manager.h — load and cache game assets from .DAT bundles.
//
//  AssetManager owns:
//    - A registry of open .DAT bundles (BundleRegistry)
//    - A cache of loaded XModels keyed by asset name (e.g. "data/rika/01.X")
//    - The D3D9 device (set once at startup, used for all subsequent loads)
//
//  Lookup flow:
//    1. Caller asks for "data/rika/01.X".
//    2. AssetManager checks its XModel cache — if hit, returns the cached ptr.
//    3. If miss, walks the open bundles in order looking for an entry with
//       that name.  The first bundle that has it wins.
//    4. Reads + decrypts the payload into a memory buffer.
//    5. Calls XModel::load_from_memory to parse + upload to GPU.
//    6. Caches the XModel keyed by name and returns it.
//
//  Lifetime:
//    - AssetManager owns the XModels.  Callers get raw pointers but must
//      NOT delete them.  AssetManager::unload_all() releases everything.
//    - Bundles are owned externally — caller opens them and passes the
//      pointer in.  AssetManager does NOT close them.
//
//  Why this design:
//    - Decouples asset lookup from "where the bytes come from" — gameplay
//      code just says "give me rika's model" and doesn't care which bundle
//      it's in.
//    - Cache prevents double-loading (a Fighter that references "rika/01.X"
//      and a Stage that references the same mesh for a cutscene share one
//      XModel instance).
//    - The bundle registry is intentionally a list, not a map — there are
//      at most 6 bundles in the original game, linear scan is faster than
//      hashing for that size.
// =============================================================================
#pragma once

#include <d3d9.h>

#include <memory>
#include <string>
#include <vector>

#include "file_parser/dat_bundle.h"
#include "file_parser/x_model_loader.h"

namespace daybreak::assets {

class AssetManager {
public:
    AssetManager() = default;
    ~AssetManager();

    AssetManager(const AssetManager&)            = delete;
    AssetManager& operator=(const AssetManager&) = delete;
    AssetManager(AssetManager&&)                 = delete;
    AssetManager& operator=(AssetManager&&)      = delete;

    // Set the D3D9 device used for all subsequent load_x() calls.
    // Must be called before load_x().
    void set_device(IDirect3DDevice9* device) { m_device = device; }

    // Register an open .DAT bundle with the manager.  AssetManager does
    // NOT take ownership — caller must keep the bundle alive.  Lookups
    // scan bundles in registration order, first match wins.
    void register_bundle(daybreak::file_parser::DatBundle* bundle) {
        m_bundles.push_back(bundle);
    }

    // Lookup + load + cache an .X model by its in-bundle filename
    // (e.g. "data/rika/01.X", "data/stage21/collision.x").
    //
    // Returns nullptr if:
    //   - no device set, or
    //   - no registered bundle contains an entry with this name, or
    //   - the entry's payload failed to parse as an .X file.
    //
    // Subsequent calls with the same name return the cached XModel* —
    // the asset is loaded only once.
    daybreak::XModel* load_x(const std::string& name);

    // Convenience: extract a file's payload into the caller's buffer
    // without going through the XModel loader.  Useful for non-mesh
    // assets (audio, data files, etc.).
    //
    // Returns false if no bundle contains the file.
    bool read_file(const std::string& name, std::vector<uint8_t>& out);

    // Check whether any registered bundle contains an entry with the
    // given name.  Does NOT load anything.
    bool has_file(const std::string& name) const;

    // Lookup + decode + cache a texture by in-bundle filename
    // (e.g. "data/title/back00.bmp", "data/select/p00.cnv").
    //
    // Decoding reuses render::UIImage, so CNV payloads decode exactly
    // like menu backgrounds; standard BMP/PNG/JPG go through D3DX.
    // This is the bundle-backed texture provider (mvp's texture_loader.c
    // pattern: archive bytes → texture, no direct-file fallback).
    //
    // Returns nullptr (and logs) when no bundle has the file or the
    // payload does not decode.  Cached by name — repeat calls return
    // the same texture.  Owned by the AssetManager: do NOT release;
    // unload_all() frees textures together with the models.
    IDirect3DTexture9* load_texture(const std::string& name);

    // Releases all cached XModels.  Does NOT close bundles (caller owns
    // those).  After this, all pointers previously returned by load_x()
    // are invalid.
    void unload_all();

    // Stats (for debugging / dev UI).
    size_t num_bundles() const { return m_bundles.size(); }
    size_t num_cached_models() const { return m_models.size(); }
    size_t num_cached_textures() const { return m_textures.size(); }

private:
    struct CachedModel {
        std::string name;
        std::unique_ptr<daybreak::XModel> model;
    };

    struct CachedTexture {
        std::string name;
        IDirect3DTexture9* texture = nullptr;
    };

    IDirect3DDevice9*                  m_device = nullptr;
    std::vector<daybreak::file_parser::DatBundle*> m_bundles;
    std::vector<CachedModel>           m_models;
    std::vector<CachedTexture>         m_textures;
};

} // namespace daybreak::assets
