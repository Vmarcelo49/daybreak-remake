// =============================================================================
//  x_model_loader.cpp — runtime .x loader + animation playback.
//
//  Ports the runtime side of X2Blend's viewer.cpp:
//    ViewerFrame           -> XFrame
//    ViewerMeshContainer   -> XMeshContainer
//    ViewerAllocateHierarchy -> member methods on XModel (via XModelAllocator)
//    UpdateFrameMatrices   -> XModel::update_frame_matrices
//    UpdateSkinnedMeshes   -> XModel::update_skinned_meshes
//    RenderFrame           -> XModel::render_frame
//    AdvanceTime loop      -> XModel::update(double deltaTime)
//
//  Key behavior preserved from X2Blend:
//    - Textures loaded from the .x file's directory via D3DXCreateTextureFromFileW
//      (Shift-JIS path decoded with MultiByteToWideChar).
//    - Skinned meshes cloned once at load time; CPU-skinned every frame via
//      ID3DXSkinInfo::UpdateSkinnedMesh with offset * boneWorld matrices.
//    - Animation switching resets track 0 to a clean state before binding
//      the new animation set (prevents controller state carry-over).
// =============================================================================
#define INITGUID
#include "x_model_loader.h"
#include "x_file_preprocessor.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <windows.h>

namespace daybreak {

// ---------------------------------------------------------------------------
// Win32 string helpers (NOT in shared modules — convert to/from wchar_t
// for D3DXCreateTextureFromFileW and friends).
// ---------------------------------------------------------------------------
static std::wstring shift_jis_to_wstring(const std::string& s) {
    if (s.empty()) return L"";
    int n = MultiByteToWideChar(932, 0, s.c_str(), -1, nullptr, 0);
    if (n <= 0) return L"";
    std::vector<wchar_t> buf(n);
    MultiByteToWideChar(932, 0, s.c_str(), -1, buf.data(), n);
    return std::wstring(buf.data());
}

static std::wstring utf8_to_wstring(const std::string& s) {
    if (s.empty()) return L"";
    int n = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, nullptr, 0);
    if (n <= 0) return L"";
    std::vector<wchar_t> buf(n);
    MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, buf.data(), n);
    return std::wstring(buf.data());
}

static std::wstring directory_of(const std::wstring& filepath) {
    size_t p = filepath.find_last_of(L"\\/");
    return (p == std::wstring::npos) ? L"" : filepath.substr(0, p + 1);
}

// ---------------------------------------------------------------------------
// ID3DXAllocateHierarchy implementation — calls into XModel's private
// create_frame / create_mesh_container / destroy_* methods so they can
// access m_device and m_modelDir.
// ---------------------------------------------------------------------------
class XModelAllocator : public ID3DXAllocateHierarchy {
public:
    explicit XModelAllocator(XModel* model) : m_model(model) {}

    STDMETHOD(CreateFrame)(LPCSTR Name, LPD3DXFRAME* ppNewFrame) override {
        return m_model->create_frame(Name, ppNewFrame);
    }
    STDMETHOD(CreateMeshContainer)(
        LPCSTR Name,
        const D3DXMESHDATA* pMeshData,
        const D3DXMATERIAL* pMaterials,
        const D3DXEFFECTINSTANCE* pEffectInstances,
        DWORD NumMaterials,
        const DWORD* pAdjacency,
        LPD3DXSKININFO pSkinInfo,
        LPD3DXMESHCONTAINER* ppNewMeshContainer) override
    {
        return m_model->create_mesh_container(
            Name, pMeshData, pMaterials, pEffectInstances,
            NumMaterials, pAdjacency, pSkinInfo, ppNewMeshContainer);
    }
    STDMETHOD(DestroyFrame)(LPD3DXFRAME pFrameToFree) override {
        return m_model->destroy_frame(pFrameToFree);
    }
    STDMETHOD(DestroyMeshContainer)(LPD3DXMESHCONTAINER pMC) override {
        return m_model->destroy_mesh_container(pMC);
    }
private:
    XModel* m_model;
};

// ===========================================================================
// XModel
// ===========================================================================
XModel::~XModel() { unload(); }

// Private shared core: takes a pre-processed buffer (text-format templates
// already injected if needed) and calls D3DXLoadMeshHierarchyFromXInMemory.
// Both load() and load_from_memory() funnel through here.
//
// On entry: m_device and m_modelDir must already be set by the caller.
// On failure: cleans up via unload() and returns false.
bool XModel::load_from_buffer_impl(const void* bytes, size_t size,
                                    const std::string& name_hint) {
    constexpr DWORD kMeshFlags =
        D3DXMESH_32BIT | D3DXMESH_NPATCHES;   // 0x0020 | 0x0200 = 0x220

    XModelAllocator alloc(this);

    HRESULT hr = D3DXLoadMeshHierarchyFromXInMemory(
        bytes,
        static_cast<DWORD>(size),
        kMeshFlags,
        m_device,
        &alloc,
        nullptr,
        &m_rootFrame,
        &m_animController);

    // Wine's D3DX InMemory loader sometimes returns no animation controller
    // for binary .X files (known Wine bug).  Fall back to the file-based loader.
    bool needFallback = FAILED(hr) ||
        (SUCCEEDED(hr) && (!m_animController ||
         m_animController->GetNumAnimationSets() == 0));

    if (needFallback) {
        if (SUCCEEDED(hr)) {
            std::fprintf(stderr,
                         "[daybreak] XModel: InMemory returned %s — retrying with file-based loader\n",
                         m_animController ? "0 anim sets" : "no anim controller");
            if (m_rootFrame) { D3DXFrameDestroy(m_rootFrame, &alloc); m_rootFrame = nullptr; }
            if (m_animController) { m_animController->Release(); m_animController = nullptr; }
        }

        char tempPath[MAX_PATH] = {0};
        GetTempPathA(MAX_PATH, tempPath);
        char tempFile[MAX_PATH] = {0};
        GetTempFileNameA(tempPath, "dbx", 0, tempFile);
        std::string tempXFile = std::string(tempFile) + ".x";
        DeleteFileA(tempFile);
        {
            std::ofstream out(tempXFile, std::ios::binary);
            out.write(static_cast<const char*>(bytes), static_cast<std::streamsize>(size));
        }

        XModelAllocator alloc2(this);
        hr = D3DXLoadMeshHierarchyFromXA(
            tempXFile.c_str(),
            kMeshFlags,
            m_device,
            &alloc2,
            nullptr,
            &m_rootFrame,
            &m_animController);

        DeleteFileA(tempXFile.c_str());

        if (FAILED(hr)) {
            std::fprintf(stderr,
                         "[daybreak] XModel: D3DXLoadMeshHierarchyFromXA also failed (hr=0x%08lx)\n",
                         static_cast<unsigned long>(hr));
            unload();
            return false;
        }
    }

    if (FAILED(hr)) {
        std::fprintf(stderr,
                     "[daybreak] XModel: D3DXLoadMeshHierarchyFromXInMemory failed (hr=0x%08lx) on %s\n",
                     static_cast<unsigned long>(hr), name_hint.c_str());
        unload();
        return false;
    }

    D3DXMATRIX id;
    D3DXMatrixIdentity(&id);
    update_frame_matrices(m_rootFrame, &id);

    // The original game binds up to 2 at load time — classic arena-fighter
    // upper/lower body blend (track 0 = full body, track 1 = upper overlay).
    if (m_animController) {
        DWORD numSets = m_animController->GetNumAnimationSets();
        DWORD maxTracks = m_animController->GetMaxNumAnimationSets();
        for (DWORD t = 0; t < maxTracks; ++t) {
            m_animController->SetTrackEnable(t, FALSE);
        }
        const DWORD tracksToBind = (numSets < 2) ? numSets : 2;
        for (DWORD i = 0; i < tracksToBind; ++i) {
            ID3DXAnimationSet* set = nullptr;
            if (SUCCEEDED(m_animController->GetAnimationSet(i, &set)) && set) {
                m_animController->SetTrackAnimationSet(i, set);
                m_animController->SetTrackEnable(i, TRUE);
                m_animController->SetTrackWeight(i, (i == 0) ? 1.0f : 0.0f);
                m_animController->SetTrackSpeed(i, 1.0f);
                m_animController->SetTrackPosition(i, 0.0);
                set->Release();
            }
        }
        m_animController->AdvanceTime(0.0, nullptr);
        if (numSets > 0) m_activeAnimIdx = 0;
    }

    std::printf("[daybreak] XModel loaded: %s  (animations=%u, tracks bound=%d)\n",
                name_hint.c_str(),
                m_animController ? m_animController->GetNumAnimationSets() : 0u,
                m_animController ? ((m_animController->GetNumAnimationSets() < 2)
                                     ? m_animController->GetNumAnimationSets() : 2)
                                 : 0);
    return true;
}

bool XModel::load(IDirect3DDevice9* device, const std::string& filepath) {
    m_device = device;
    m_modelDir = directory_of(utf8_to_wstring(filepath));

    // For text-format .X files, this injects the XSkinMeshHeader /
    // VertexDuplicationIndices / SkinWeights templates that Wine's d3dxof
    // parser does not pre-register.  Binary and bzip files pass through
    // unchanged (the preprocessor's isTextFormat check handles that).
    std::string xContent;
    if (!x_file_preprocessor::read_and_preprocess(filepath, xContent)) {
        return false;
    }

    return load_from_buffer_impl(xContent.data(), xContent.size(), filepath);
}

bool XModel::load_from_memory(IDirect3DDevice9* device,
                              const uint8_t* bytes,
                              size_t size,
                              const std::string& name_hint,
                              const std::wstring& texture_search_dir) {
    m_device = device;
    m_modelDir = texture_search_dir;

    if (!bytes || size == 0) {
        std::fprintf(stderr, "[daybreak] XModel: empty buffer for %s\n",
                     name_hint.c_str());
        return false;
    }

    // Check if this is a text-format .X (magic "xof 030[23]txt").
    // If yes, run the template preprocessor on a copy.  If no (binary or
    // bzip), pass the bytes straight to D3DX.
    const size_t kMinTextHeader = 11;
    const char* bytes_c = reinterpret_cast<const char*>(bytes);
    const bool is_text_format =
        (size >= kMinTextHeader) &&
        (std::memcmp(bytes, "xof 030", 7) == 0) &&
        (bytes_c[10] == 't' || bytes_c[10] == 'T');

    if (!is_text_format) {
        return load_from_buffer_impl(bytes, size, name_hint);
    }

    // Text format — need to inject missing mesh-extension templates.
    // The preprocessor takes a std::string, so copy the buffer in.
    std::string xContent(bytes_c, size);

    // Inline re-implementation of x_file_preprocessor::read_and_preprocess
    // since we already have the bytes (no file to read).  The original
    // function reads from disk; here we just do the template injection.
    static const char* const k_templateMarkers[] = {
        "template XSkinMeshHeader",
        "template VertexDuplicationIndices",
        "template SkinWeights",
    };
    static const char* k_missingTemplates = R"x(
template XSkinMeshHeader {
  <3CF169CE-FF7C-44AB-93C0-F78F62D172E2>
  WORD nMaxSkinWeightsPerVertex;
  WORD nMaxSkinWeightsPerFace;
  WORD nBones;
}

template VertexDuplicationIndices {
  <B8D65549-D7C9-4995-89CF-53A9A8B031E3>
  DWORD nIndices;
  DWORD nOriginalVertices;
  array DWORD indices[nIndices];
}

template SkinWeights {
  <6F0D123B-BAD2-4167-A0D0-80224F25FABB>
  STRING transformNodeName;
  DWORD nWeights;
  array DWORD vertexIndices[nWeights];
  array float weights[nWeights];
  Matrix4x4 matrixOffset;
}
)x";

    size_t headerEnd = xContent.find('\n');
    if (headerEnd == std::string::npos) {
        headerEnd = xContent.size();
    } else {
        ++headerEnd;
    }

    std::string injection;
    for (const char* marker : k_templateMarkers) {
        if (xContent.find(marker) == std::string::npos) {
            static const std::string src = k_missingTemplates;
            auto start = src.find(marker);
            if (start != std::string::npos) {
                auto next = src.find("template ", start + 1);
                std::string body = (next == std::string::npos)
                    ? src.substr(start)
                    : src.substr(start, next - start);
                injection += body;
            }
        }
    }
    if (!injection.empty()) {
        xContent.insert(headerEnd, std::string("\n") + injection);
    }

    return load_from_buffer_impl(xContent.data(), xContent.size(), name_hint);
}

void XModel::unload() {
    if (m_rootFrame && m_device) {
        XModelAllocator alloc(this);
        D3DXFrameDestroy(m_rootFrame, &alloc);
        m_rootFrame = nullptr;
    }
    if (m_animController) {
        m_animController->Release();
        m_animController = nullptr;
    }
    m_device = nullptr;
    m_activeAnimIdx = -1;
}

// ---------------------------------------------------------------------------
// ID3DXAllocateHierarchy callbacks (private)
// ---------------------------------------------------------------------------
STDMETHODIMP XModel::create_frame(LPCSTR Name, LPD3DXFRAME* ppNewFrame) {
    *ppNewFrame = nullptr;
    auto* frame = new XFrame();
    std::memset(static_cast<void*>(frame), 0, sizeof(XFrame));

    if (Name) {
        size_t len = std::strlen(Name) + 1;
        frame->Name = new char[len];
        std::strcpy(frame->Name, Name);
    }

    D3DXMatrixIdentity(&frame->TransformationMatrix);
    D3DXMatrixIdentity(&frame->worldMatrix);
    *ppNewFrame = frame;
    return S_OK;
}

STDMETHODIMP XModel::create_mesh_container(
    LPCSTR Name,
    const D3DXMESHDATA* pMeshData,
    const D3DXMATERIAL* pMaterials,
    const D3DXEFFECTINSTANCE* pEffectInstances,
    DWORD NumMaterials,
    const DWORD* /*pAdjacency*/,
    LPD3DXSKININFO pSkinInfo,
    LPD3DXMESHCONTAINER* ppNewMeshContainer)
{
    *ppNewMeshContainer = nullptr;
    if (!pMeshData || pMeshData->Type != D3DXMESHTYPE_MESH) return E_FAIL;

    auto* mc = new XMeshContainer();
    std::memset(static_cast<void*>(mc), 0, sizeof(XMeshContainer));

    if (Name) {
        size_t len = std::strlen(Name) + 1;
        mc->Name = new char[len];
        std::strcpy(mc->Name, Name);
    }

    mc->MeshData.Type  = D3DXMESHTYPE_MESH;
    mc->MeshData.pMesh = pMeshData->pMesh;
    mc->MeshData.pMesh->AddRef();
    mc->pOriginalMesh = pMeshData->pMesh;
    mc->pOriginalMesh->AddRef();

    // Materials + textures.
    // Suite probe: log per-material effect bindings (the game's 10-shader
    // EffectSystem likely drives blend modes like shadow multiply).
    if (pEffectInstances) {
        for (DWORD ei = 0; ei < NumMaterials; ++ei) {
            if (pEffectInstances[ei].pEffectFilename) {
                std::printf("[daybreak] XModel effect: mat %lu -> %s\n",
                            static_cast<unsigned long>(ei),
                            pEffectInstances[ei].pEffectFilename);
            }
        }
    }
    mc->NumMaterials = NumMaterials;
    if (NumMaterials > 0) {
        mc->d3dMaterials.resize(NumMaterials);
        mc->textures.assign(NumMaterials, nullptr);
        mc->textureFiles.assign(NumMaterials, {});
        mc->shadowDecal.assign(NumMaterials, 0);
        for (DWORD i = 0; i < NumMaterials; ++i) {
            if (pMaterials) {
                mc->d3dMaterials[i] = pMaterials[i].MatD3D;
                mc->d3dMaterials[i].Ambient = mc->d3dMaterials[i].Diffuse;
            } else {
                std::memset(&mc->d3dMaterials[i], 0, sizeof(D3DMATERIAL9));
                mc->d3dMaterials[i].Diffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
                mc->d3dMaterials[i].Ambient = { 1.0f, 1.0f, 1.0f, 1.0f };
            }

            if (pMaterials && pMaterials[i].pTextureFilename) {
                // Keep the raw requested name for the bundle-backed pass;
                // the disk loader below only fires when a search dir exists.
                mc->textureFiles[i] = pMaterials[i].pTextureFilename;
                std::wstring texW  = shift_jis_to_wstring(pMaterials[i].pTextureFilename);
                std::wstring fullW = m_modelDir + texW;
                IDirect3DTexture9* tex = nullptr;
                if (SUCCEEDED(D3DXCreateTextureFromFileW(m_device, fullW.c_str(), &tex))) {
                    mc->textures[i] = tex;
                }
            }
        }
        // NOTE: we deliberately do NOT set mc->pMaterials (which is a
        // D3DXMATERIAL*).  We keep materials in d3dMaterials (D3DMATERIAL9
        // array) and reference them by index during render.  The D3DX
        // pMaterials pointer would point into the loader's temporary array
        // which is invalid after CreateMeshContainer returns.
    }

    // Skin info + skinned-mesh clone.
    if (pSkinInfo) {
        mc->pSkinInfo = pSkinInfo;
        mc->pSkinInfo->AddRef();

        ID3DXMesh* skinned = nullptr;
        if (SUCCEEDED(mc->pOriginalMesh->CloneMeshFVF(
                D3DXMESH_MANAGED,
                mc->pOriginalMesh->GetFVF(),
                m_device,
                &skinned))) {
            mc->pSkinnedMesh = skinned;
            // Replace the active mesh pointer so render() draws the skinned one.
            mc->MeshData.pMesh->Release();
            mc->MeshData.pMesh = skinned;
            mc->MeshData.pMesh->AddRef();
        }
    }

    *ppNewMeshContainer = mc;
    return S_OK;
}

STDMETHODIMP XModel::destroy_frame(LPD3DXFRAME pFrameToFree) {
    if (!pFrameToFree) return S_OK;
    delete[] pFrameToFree->Name;
    delete pFrameToFree;
    return S_OK;
}

STDMETHODIMP XModel::destroy_mesh_container(LPD3DXMESHCONTAINER pMC) {
    if (!pMC) return S_OK;
    auto* mc = static_cast<XMeshContainer*>(pMC);

    delete[] mc->Name;
    if (mc->pOriginalMesh) mc->pOriginalMesh->Release();
    if (mc->pSkinnedMesh)  mc->pSkinnedMesh->Release();
    if (mc->MeshData.pMesh) mc->MeshData.pMesh->Release();
    for (auto* t : mc->textures) if (t) t->Release();
    if (mc->pSkinInfo) mc->pSkinInfo->Release();
    delete mc;
    return S_OK;
}

// ---------------------------------------------------------------------------
// Animation control
// ---------------------------------------------------------------------------
int XModel::num_animation_sets() const {
    return m_animController ? static_cast<int>(m_animController->GetNumAnimationSets()) : 0;
}

DWORD XModel::num_tracks_bound() const {
    if (!m_animController) return 0;
    DWORD numSets = m_animController->GetNumAnimationSets();
    return (numSets < 2) ? numSets : 2;
}

std::string XModel::animation_set_name(int index) const {
    if (!m_animController || index < 0 ||
        index >= static_cast<int>(m_animController->GetNumAnimationSets())) {
        return {};
    }
    ID3DXAnimationSet* set = nullptr;
    if (FAILED(m_animController->GetAnimationSet(static_cast<DWORD>(index), &set)) || !set) {
        return {};
    }
    LPCSTR name = set->GetName();
    std::string r = name ? name : "Anim_" + std::to_string(index);
    set->Release();
    return r;
}

bool XModel::switch_to_animation(int index) {
    if (!m_animController) return false;
    DWORD n = m_animController->GetNumAnimationSets();
    if (n == 0) return false;
    if (index < 0) index = static_cast<int>(n) - 1;
    if (index >= static_cast<int>(n)) index = 0;

    ID3DXAnimationSet* set = nullptr;
    if (FAILED(m_animController->GetAnimationSet(static_cast<DWORD>(index), &set)) || !set) {
        return false;
    }

    // Reset ALL tracks except 0 to a clean state (prevents state carry-over).
    DWORD maxTracks = m_animController->GetMaxNumAnimationSets();
    for (DWORD t = 0; t < maxTracks; ++t) m_animController->SetTrackEnable(t, FALSE);
    m_animController->SetTrackEnable(0, TRUE);
    m_animController->SetTrackAnimationSet(0, set);
    m_animController->SetTrackWeight(0, 1.0f);
    m_animController->SetTrackSpeed(0, 1.0f);
    m_animController->SetTrackPosition(0, 0.0);
    m_animController->AdvanceTime(0.0, nullptr);

    set->Release();
    m_activeAnimIdx = index;
    return true;
}

bool XModel::switch_to_animation(const std::string& name) {
    if (!m_animController) return false;
    DWORD n = m_animController->GetNumAnimationSets();
    for (DWORD i = 0; i < n; ++i) {
        if (animation_set_name(static_cast<int>(i)) == name) {
            return switch_to_animation(static_cast<int>(i));
        }
    }
    return false;
}

double XModel::current_track_time() const {
    if (!m_animController) return 0.0;
    return m_animController->GetTime();
}

float XModel::current_track_duration() const {
    if (!m_animController || m_activeAnimIdx < 0) return 0.0f;
    ID3DXAnimationSet* set = nullptr;
    if (FAILED(m_animController->GetAnimationSet(static_cast<DWORD>(m_activeAnimIdx), &set)) || !set) {
        return 0.0f;
    }
    double period = set->GetPeriod();
    set->Release();
    return static_cast<float>(period);
}

// ---------------------------------------------------------------------------
// Per-frame update — advance animation, update world matrices, re-skin.
// ---------------------------------------------------------------------------
void XModel::update(double deltaTime) {
    if (m_animController) {
        // Clamp delta to avoid huge jumps after a stall (e.g. debugger break).
        if (deltaTime > 0.1) deltaTime = 0.1;
        m_animController->AdvanceTime(deltaTime, nullptr);
    }
    D3DXMATRIX id;
    D3DXMatrixIdentity(&id);
    if (m_rootFrame) {
        update_frame_matrices(m_rootFrame, &id);
        update_skinned_meshes(m_rootFrame, m_rootFrame);
    }
}

void XModel::update_frame_matrices(D3DXFRAME* frame,
                                    const D3DXMATRIX* parentWorld) const {
    if (!frame) return;
    auto* vf = static_cast<XFrame*>(frame);
    if (parentWorld) {
        D3DXMatrixMultiply(&vf->worldMatrix, &vf->TransformationMatrix, parentWorld);
    } else {
        vf->worldMatrix = vf->TransformationMatrix;
    }
    if (vf->pFrameFirstChild) update_frame_matrices(vf->pFrameFirstChild, &vf->worldMatrix);
    if (vf->pFrameSibling)    update_frame_matrices(vf->pFrameSibling,    parentWorld);
}

void XModel::update_skinned_meshes(D3DXFRAME* frame, D3DXFRAME* rootFrame) const {
    if (!frame) return;

    D3DXMESHCONTAINER* pMC = frame->pMeshContainer;
    while (pMC) {
        auto* vmc = static_cast<XMeshContainer*>(pMC);
        if (vmc->pSkinInfo && vmc->pSkinnedMesh) {
            DWORD numBones = vmc->pSkinInfo->GetNumBones();
            std::vector<D3DXMATRIX> boneXforms(numBones);

            for (DWORD i = 0; i < numBones; ++i) {
                LPCSTR boneName = vmc->pSkinInfo->GetBoneName(i);
                D3DXFRAME* boneFrame = D3DXFrameFind(rootFrame, boneName);
                if (boneFrame) {
                    auto* vf = static_cast<XFrame*>(boneFrame);
                    D3DXMatrixMultiply(&boneXforms[i],
                                       vmc->pSkinInfo->GetBoneOffsetMatrix(i),
                                       &vf->worldMatrix);
                } else {
                    D3DXMatrixIdentity(&boneXforms[i]);
                }
            }

            void* src = nullptr;
            void* dst = nullptr;
            if (SUCCEEDED(vmc->pOriginalMesh->LockVertexBuffer(D3DLOCK_READONLY, &src))) {
                if (SUCCEEDED(vmc->pSkinnedMesh->LockVertexBuffer(0, &dst))) {
                    vmc->pSkinInfo->UpdateSkinnedMesh(boneXforms.data(), nullptr, src, dst);
                    vmc->pSkinnedMesh->UnlockVertexBuffer();
                }
                vmc->pOriginalMesh->UnlockVertexBuffer();
            }
        }
        pMC = pMC->pNextMeshContainer;
    }

    if (frame->pFrameFirstChild) update_skinned_meshes(frame->pFrameFirstChild, rootFrame);
    if (frame->pFrameSibling)    update_skinned_meshes(frame->pFrameSibling,    rootFrame);
}

// ---------------------------------------------------------------------------
// Render
// ---------------------------------------------------------------------------
void XModel::render(IDirect3DDevice9* device) const {
    if (!m_rootFrame) return;
    render_frame(m_rootFrame, device);
}

void XModel::resolve_material_textures(const MaterialResolver& resolver) {
    if (!resolver.load || !m_rootFrame) return;
    int resolved = 0, missed = 0;
    std::function<void(D3DXFRAME*)> walk = [&](D3DXFRAME* frame) {
        for (D3DXFRAME* f = frame; f; f = f->pFrameSibling) {
            for (D3DXMESHCONTAINER* mc = f->pMeshContainer; mc;
                 mc = mc->pNextMeshContainer) {
                auto* vmc = static_cast<XMeshContainer*>(mc);
                for (DWORD i = 0; i < vmc->NumMaterials; ++i) {
                    if (i >= vmc->textures.size() || i >= vmc->textureFiles.size() ||
                        i >= vmc->shadowDecal.size()) break;
                    if (vmc->textureFiles[i].empty()) continue;
                    if (!vmc->textures[i]) {
                        IDirect3DTexture9* tex = resolver.load(vmc->textureFiles[i]);
                        if (tex) {
                            tex->AddRef();  // container owns one ref (see header)
                            vmc->textures[i] = tex;
                            ++resolved;
                        } else {
                            ++missed;
                        }
                    }
                    if (resolver.isShadowDecal) {
                        vmc->shadowDecal[i] =
                            resolver.isShadowDecal(vmc->textureFiles[i]) ? 1 : 0;
                    }
                }
            }
            if (f->pFrameFirstChild) walk(f->pFrameFirstChild);
        }
    };
    walk(m_rootFrame);
    if (resolved + missed > 0) {
        std::printf("[daybreak] XModel textures: %d resolved, %d missed\n",
                    resolved, missed);
    }
}

void XModel::render_frame(D3DXFRAME* frame, IDirect3DDevice9* device) const {
    if (!frame) return;

    auto* vf = static_cast<XFrame*>(frame);
    D3DXMESHCONTAINER* pMC = vf->pMeshContainer;
    while (pMC) {
        auto* vmc = static_cast<XMeshContainer*>(pMC);

        // Skinned vertices are already in model-root space (bone offset * bone
        // world applied), so for skinned meshes the world matrix is identity.
        // For non-skinned meshes we apply the frame's world matrix.
        if (vmc->pSkinInfo) {
            D3DXMATRIX id;
            D3DXMatrixIdentity(&id);
            device->SetTransform(D3DTS_WORLD, &id);
        } else {
            device->SetTransform(D3DTS_WORLD, &vf->worldMatrix);
        }

        ID3DXMesh* mesh = vmc->MeshData.pMesh;
        for (DWORD i = 0; i < vmc->NumMaterials; ++i) {
            if (i < vmc->d3dMaterials.size()) {
                device->SetMaterial(&vmc->d3dMaterials[i]);
            }
            if (i < vmc->textures.size() && vmc->textures[i]) {
                device->SetTexture(0, vmc->textures[i]);
            } else {
                device->SetTexture(0, nullptr);
            }
            // Baked blob shadows (e.g. stage21 shadow01: white card, dark
            // blob, opaque alpha) are only meaningful under multiply blend —
            // opaque/alpha variants all print the white quad. The real
            // trigger is an effect-technique binding (open RE, P3.1); until
            // that lands, the "shadow" texture name is the provisional
            // signal. dest = src*dst: white keeps ground, blob darkens it.
            // Depth write off so the decal never occludes later geometry.
            bool multiply = i < vmc->shadowDecal.size() && vmc->shadowDecal[i];
            if (multiply) {
                // Baked shadows are lighting, not paint: two overlapping
                // decal cards (stage21: the shed's shadow01 over the school's
                // 校舎影02) otherwise multiply twice and draw a hard dark
                // outline exactly along their overlap — visible in captures.
                // Stencil "already shadowed" pixels (0 = unshadowed; the
                // first decal to cover a pixel bumps it to 1 via INCRSAT), so
                // each pixel darkens at most once. Alpha-tested-away texels
                // never reach the stencil, so silhouettes stay exact.
                device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
                device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
                device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
                device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
                device->SetRenderState(D3DRS_STENCILENABLE, TRUE);
                device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
                device->SetRenderState(D3DRS_STENCILREF, 0);
                device->SetRenderState(D3DRS_STENCILMASK, 0xFFFFFFFF);
                device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xFFFFFFFF);
                device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT);
                device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
                device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
            }
            mesh->DrawSubset(i);
            if (multiply) {
                device->SetRenderState(D3DRS_STENCILENABLE, FALSE);
                device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
                device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
            }
        }
        pMC = pMC->pNextMeshContainer;
    }

    if (frame->pFrameFirstChild) render_frame(frame->pFrameFirstChild, device);
    if (frame->pFrameSibling)    render_frame(frame->pFrameSibling,    device);
}

} // namespace daybreak
