// =============================================================================
//  x_model_loader.h — runtime .x model + animation loader.
//
//  Loads a DirectX 9 .x file via D3DXLoadMeshHierarchyFromXA, retaining:
//    - The D3DXFRAME hierarchy (with per-frame worldMatrix)
//    - All mesh containers (with materials, textures, skin info, skinned clone)
//    - The ID3DXAnimationController (for AdvanceTime / SetTrackAnimationSet)
//
//  Direction: ports the runtime side of X2Blend's viewer.cpp (ViewerFrame,
//  ViewerMeshContainer, ViewerAllocateHierarchy, UpdateFrameMatrices,
//  UpdateSkinnedMeshes) into the daybreak project namespace.  The
//  export-only modules (HierarchyBuilder, MeshExtractor, AnimationBaker)
//  are intentionally NOT ported — daybreak renders the mesh directly off
//  the D3DX runtime objects instead of baking them to JSON.
//
//  Runtime DLL requirement:
//    - d3dx9_43.dll  (DirectX End-User Runtime, June 2010)
//    - d3d9.dll      (ships with Windows)
// =============================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9anim.h>

#include <cstdint>
#include <string>
#include <vector>

namespace daybreak {

// ---------------------------------------------------------------------------
// Hierarchy types — extend D3DX's plain structs with runtime fields.
// ---------------------------------------------------------------------------
struct XFrame : public D3DXFRAME {
    D3DXMATRIX worldMatrix;   // recomputed every frame from TransformationMatrix
};

struct XMeshContainer : public D3DXMESHCONTAINER {
    ID3DXMesh*                       pOriginalMesh = nullptr;  // raw, un-skinned
    ID3DXMesh*                       pSkinnedMesh  = nullptr;  // CPU-skinned output
    std::vector<IDirect3DTexture9*>  textures;
    std::vector<D3DMATERIAL9>        d3dMaterials;
};

// ---------------------------------------------------------------------------
// XModel — owns the loaded hierarchy + animation controller.
//
//  Loading flow:
//    XModel m;
//    m.load(device, "path/to/model.x");
//    ...
//    m.update(deltaTime);          // advance animation, update world matrices,
//                                  // skin meshes
//    m.render(device);             // draw
//    ...
//    m.unload();                   // free everything (or just destroy m)
// ---------------------------------------------------------------------------
class XModel {
public:
    XModel() = default;
    ~XModel();

    XModel(const XModel&)            = delete;
    XModel& operator=(const XModel&) = delete;
    XModel(XModel&&)                 = delete;
    XModel& operator=(XModel&&)      = delete;

    // Loads the .x file at `filepath` using `device`.  Returns true on
    // success.  On failure, the model is left in a clean state.
    //
    // Reads from disk, runs the text-format template preprocessor, then
    // hands the bytes to D3DXLoadMeshHierarchyFromXInMemory.
    bool load(IDirect3DDevice9* device, const std::string& filepath);

    // Loads a .x file from an in-memory byte buffer.  `bytes` is NOT
    // copied — caller must keep it alive for the duration of the call.
    // `name_hint` is used only for error messages (typically the original
    // filename, e.g. "data/rika/01.X").  `texture_search_dir` is the
    // directory the loader will look in for textures referenced by the
    // .X file (typically the directory the .X would have lived in if
    // loaded from disk); pass empty to skip texture loading.
    //
    // This is the primary entry point used by the asset manager —
    // payloads are extracted from .DAT bundles into memory buffers,
    // then handed directly to D3DX without going through the filesystem.
    //
    // The function applies the text-format template preprocessor IF the
    // buffer starts with `xof 030[23]txt`.  Binary and bzip buffers are
    // passed straight to D3DX (they don't need template injection).
    bool load_from_memory(IDirect3DDevice9* device,
                          const uint8_t* bytes,
                          size_t size,
                          const std::string& name_hint,
                          const std::wstring& texture_search_dir);

    // Releases all D3D resources.  Safe to call multiple times.
    void unload();

    // Advances the animation controller by `deltaTime` seconds, recomputes
    // every frame's worldMatrix, and re-skins every skinned mesh container.
    void update(double deltaTime);

    // Draws all mesh containers using `device` (world/view/proj matrices
    // must be set by the caller; this method sets the per-mesh world matrix).
    void render(IDirect3DDevice9* device) const;

    // ---- animation-set control --------------------------------------------
    int  num_animation_sets() const;
    std::string animation_set_name(int index) const;
    bool switch_to_animation(int index);
    bool switch_to_animation(const std::string& name);

    // ---- multi-track blending ---------------------------------------------
    // The original game binds up to 2 animation tracks at load time.  Track
    // 0 is the "base" (full-body) animation, track 1 is the "overlay" (often
    // upper-body only).  The gameplay code blends them by setting weights.
    //
    // These accessors expose the controller directly so the gameplay layer
    // can call SetTrackWeight / SetTrackEnable / SetTrackAnimationSet
    // without poking at XModel internals.
    ID3DXAnimationController* anim_controller() const { return m_animController; }
    DWORD num_tracks_bound() const;

    // ---- introspection -----------------------------------------------------
    bool   has_animations() const { return m_animController != nullptr; }
    double current_track_time() const;
    float  current_track_duration() const;

    // ---- frame hierarchy access -------------------------------------------
    // Exposes the root D3DXFRAME so subsystems (e.g. physics::raycast_model)
    // can traverse the hierarchy directly.  The pointer is owned by XModel
    // — callers must not free it.  Returns nullptr if no model is loaded.
    //
    // The frame tree is updated every call to update(), so the worldMatrix
    // field on each XFrame is current as of the last update().
    LPD3DXFRAME root_frame() const { return m_rootFrame; }

private:
    // ID3DXAllocateHierarchy callbacks
    STDMETHOD(create_frame)(LPCSTR Name, LPD3DXFRAME* ppNewFrame);
    STDMETHOD(create_mesh_container)(
        LPCSTR Name,
        const D3DXMESHDATA* pMeshData,
        const D3DXMATERIAL* pMaterials,
        const D3DXEFFECTINSTANCE* pEffectInstances,
        DWORD NumMaterials,
        const DWORD* pAdjacency,
        LPD3DXSKININFO pSkinInfo,
        LPD3DXMESHCONTAINER* ppNewMeshContainer);
    STDMETHOD(destroy_frame)(LPD3DXFRAME pFrameToFree);
    STDMETHOD(destroy_mesh_container)(LPD3DXMESHCONTAINER pMeshContainerToFree);

    // Recursive helpers
    void update_frame_matrices(D3DXFRAME* frame, const D3DXMATRIX* parentWorld) const;
    void update_skinned_meshes(D3DXFRAME* frame, D3DXFRAME* rootFrame) const;
    void render_frame(D3DXFRAME* frame, IDirect3DDevice9* device) const;

    // Shared core for load() and load_from_memory().  Caller must have
    // already set m_device and m_modelDir, and must have already done any
    // text-format template injection.  bytes/size point at the (possibly
    // preprocessed) buffer to hand to D3DX.
    bool load_from_buffer_impl(const void* bytes, size_t size,
                                const std::string& name_hint);

    IDirect3DDevice9*           m_device         = nullptr;
    LPD3DXFRAME                 m_rootFrame      = nullptr;
    ID3DXAnimationController*   m_animController = nullptr;
    std::wstring                m_modelDir;        // for texture lookups
    int                         m_activeAnimIdx  = -1;

    friend class XModelAllocator;  // ID3DXAllocateHierarchy impl
};

} // namespace daybreak
