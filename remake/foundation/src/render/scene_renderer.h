#pragma once
// Draws an xm::Scene: depth buffer, textured pipeline, per-draw uniforms, stage
// camera and fog. This is the second — and last — place outside gpu/ that includes
// webgpu.h, because building render pipelines is not something gpu/ wraps; the
// asset layer's xm::wgpuVertexLayout() is the contract between the two, which is
// why the asset header has to be pulled in with XMODEL_WEBGPU defined.
#include <webgpu/webgpu.h>

#include <cstdint>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "gpu/gpu.h"

// xmodel.h only declares its WebGPU helpers when this is set, and webgpu.h is
// already in scope above (the header has to be included first).
#define XMODEL_WEBGPU
#include "scene.h"

namespace render {

// Where a frame goes. One struct so a swapchain frame and an offscreen capture run
// the same draw path; the format selects (and caches) the pipeline.
struct Target {
    WGPUCommandEncoder encoder   = nullptr;
    WGPUTextureView    colorView = nullptr;
    WGPUTextureFormat  format    = WGPUTextureFormat_Undefined;
    uint32_t           width     = 0;
    uint32_t           height    = 0;
};

// Draw-time switches, as opposed to upload-time ones (Options).
struct Appearance {
    bool fog   = true;   // linear fog from StageEnv (env.dat)
    bool unlit = false;  // skip the lambert term: raw texture/vertex colour
};

struct Options {
    bool textures = true;   // resolve .cnv textures; false binds a 1x1 white instead
};

struct Stats {
    size_t draws           = 0;
    size_t textures        = 0;
    size_t paletteMatrices = 0;
    int    textured        = 0;
    int    untextured      = 0;
    int    decals          = 0;
    int    effects         = 0;
    int    billboarded     = 0;   // effect draws that yaw to the camera (EFFECTS-BILLBOARD.md)
};

// Which blend/depth/cull variant draws an item. The order below is also the
// submission order: lit opaque geometry first, multiply decals over it, additive
// effect cards last. Classification lives in scene_renderer.cpp (classifyPass);
// the asset layer's SceneModel::role is the only effect signal the renderer may
// read, because shipped material terms do not distinguish effect cards (R2).
enum class Pass : uint8_t { Opaque = 0, Decal = 1, Effect = 2 };

class SceneRenderer {
public:
    SceneRenderer() = default;
    ~SceneRenderer();
    SceneRenderer(const SceneRenderer&) = delete;
    SceneRenderer& operator=(const SceneRenderer&) = delete;

    // Borrows device/queue/instance from the context; owns everything it creates.
    bool init(const gpu::Context&, std::string& error);
    void shutdown();

    // Uploads geometry, textures and the draw list for `scene`. `worlds` is the posed
    // hierarchy per model (in scene order), `modelMatrices` the entity transform per
    // model — a weapon's is its owning character's attachment frame.
    bool setScene(const xm::Scene& scene, const std::vector<std::vector<glm::mat4>>& worlds,
                  const std::vector<glm::mat4>& modelMatrices, const Options&, std::string& error);

    // Re-fills the palette storage from a new pose. Animation changes the pose every
    // frame while the geometry stays put, so this is deliberately not part of
    // setScene: uploading vertex and index buffers per frame would be the whole cost
    // of the scene for nothing.
    void updatePose(const std::vector<std::vector<glm::mat4>>& worlds);

    // Re-points every draw at new per-model transforms (entity placement, weapon
    // bones following animated rigs). DrawUniforms rebuild from draws_ on every
    // render(), so this takes effect on the next frame; a no-op before setScene.
    void setModelMatrices(const std::vector<glm::mat4>& modelMatrices);

    void setCamera(const glm::mat4& viewProj);
    // Camera eye in world space, for effect-card billboarding. The viewProj alone
    // cannot yield it (a perspective product does not separate into eye and
    // projection), and main.cpp is the only caller that knows the eye — so until
    // the caller wires this, billboarding stays dormant and every capture is
    // byte-identical to before. See EFFECTS-BILLBOARD.md.
    void setEye(const glm::vec3& eye);
    void setFog(const xm::StageEnv&);
    void setAppearance(const Appearance&);

    bool render(const Target&, std::string& error);

    // Optional UI compositing for verification captures: invoked after the 3D pass
    // into the capture encoder, before copy-to-readback. Uses only WebGPU types so
    // render/ never includes ui/ headers; the caller adapts. Null keeps current
    // behavior, and existing captures byte-identical.
    using UiHook = bool (*)(WGPUCommandEncoder, WGPUTextureView, WGPUTextureFormat,
                            uint32_t, uint32_t, void* userdata);
    // Renders size x size offscreen into an RGBA8Unorm texture and reads the pixels
    // back (RGBA8, tightly packed). Only verification needs this; the window path
    // never calls it.
    bool capture(uint32_t size, std::vector<uint8_t>& rgba, std::string& error,
                 UiHook uiHook = nullptr, void* uiUserdata = nullptr);

    const Stats& stats() const { return stats_; }

private:
    struct DrawItem {
        WGPUBuffer vbuf = nullptr, ibuf = nullptr;   // borrowed; owned by buffers_
        uint32_t   firstIndex = 0, indexCount = 0;
        uint32_t   paletteOffset = 0;
        uint32_t   flags = 0;                        // from the material, per draw
        int        texture = -1;                     // -1 -> the 1x1 white fallback
        Pass       pass = Pass::Opaque;
        size_t     modelIndex = 0;   // owning model, for per-frame re-placement
        glm::mat4  model{1.f};
        glm::vec4  baseColor{1.f};                   // material diffuse (D3DX faceColor)
        // Cylindrical-billboard candidate: mesh-space pivot (submesh bounds center),
        // authored facing yaw, plus the verdict from setScene. Only Effect-pass
        // draws from unskinned meshes are ever marked; ground-plane cards are
        // excluded (see .cpp).
        glm::vec3  bbCenter{0.f};
        float      bbYaw0 = 0.f;
        bool       billboard = false;
    };

    // What updatePose() needs to rebuild one mesh's slice of the palette storage.
    struct MeshRecord {
        const xm::Model* model = nullptr;
        const xm::Mesh*  mesh  = nullptr;
        size_t           modelIndex = 0;
        uint32_t         paletteOffset = 0;
    };

    struct Texture {
        WGPUTexture     tex  = nullptr;
        WGPUTextureView view = nullptr;
    };

    struct Pipelines {
        WGPUTextureFormat format = WGPUTextureFormat_Undefined;
        WGPURenderPipeline opaque = nullptr;   // lit, depth-writing
        WGPURenderPipeline decal  = nullptr;   // multiply blend, no depth write, no cull
        WGPURenderPipeline effect = nullptr;   // additive, unlit, no depth write, no cull
    };

    WGPURenderPipeline pipelineFor(WGPUTextureFormat, Pass, std::string& error);
    bool ensureDepth(uint32_t width, uint32_t height, std::string& error);
    bool buildBindings(std::string& error);

    WGPUInstance instance_ = nullptr;   // borrowed from the context
    WGPUDevice   device_   = nullptr;
    WGPUQueue    queue_    = nullptr;

    WGPUBindGroupLayout bindGroupLayouts_[3] = {nullptr, nullptr, nullptr};
    WGPUPipelineLayout  pipelineLayout_ = nullptr;
    WGPUShaderModule    shader_ = nullptr;
    WGPUSampler         sampler_ = nullptr;

    WGPUTexture     whiteTex_ = nullptr;
    WGPUTextureView whiteView_ = nullptr;
    WGPUBindGroup   cameraGroup_ = nullptr;
    WGPUBindGroup   drawGroup_ = nullptr;                    // group 1, dynamic offset
    std::vector<WGPUBindGroup> textureGroups_;               // [0] = white, then one per texture

    WGPUBuffer cameraBuffer_ = nullptr;
    WGPUBuffer drawBuffer_ = nullptr;
    WGPUBuffer paletteBuffer_ = nullptr;

    std::vector<Pipelines> pipelines_;
    std::vector<DrawItem>  draws_;
    std::vector<MeshRecord> meshes_;
    std::vector<WGPUBuffer> buffers_;      // owned vertex/index buffers
    std::vector<Texture>    textures_;     // owned, deduplicated by image
    std::vector<glm::mat4>  palette_;      // CPU copy, uploaded by updatePose()

    WGPUTexture     depthTex_ = nullptr;
    WGPUTextureView depthView_ = nullptr;
    uint32_t        depthWidth_ = 0, depthHeight_ = 0;

    xm::CameraUniform camera_{};
    Appearance        appearance_{};
    Stats             stats_{};
    // Billboard eye. haveEye_ is false until setEye() runs, which keeps the
    // billboard path dormant (and captures byte-identical) on callers that were
    // written before it existed.
    glm::vec3         eye_{0.f};
    bool              haveEye_ = false;
};

}  // namespace render
