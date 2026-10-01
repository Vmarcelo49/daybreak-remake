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
};

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

    void setCamera(const glm::mat4& viewProj);
    void setFog(const xm::StageEnv&);
    void setAppearance(const Appearance&);

    bool render(const Target&, std::string& error);

    // Renders size x size offscreen into an RGBA8Unorm texture and reads the pixels
    // back (RGBA8, tightly packed). Only verification needs this; the window path
    // never calls it.
    bool capture(uint32_t size, std::vector<uint8_t>& rgba, std::string& error);

    const Stats& stats() const { return stats_; }

private:
    struct DrawItem {
        WGPUBuffer vbuf = nullptr, ibuf = nullptr;   // borrowed; owned by buffers_
        uint32_t   firstIndex = 0, indexCount = 0;
        uint32_t   paletteOffset = 0;
        uint32_t   flags = 0;                        // from the material, per draw
        int        texture = -1;                     // -1 -> the 1x1 white fallback
        bool       decal = false;                    // baked shadow: drawn last, multiplied
        glm::mat4  model{1.f};
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
        WGPURenderPipeline main   = nullptr;   // lit, depth-writing
        WGPURenderPipeline decal  = nullptr;   // multiply blend, no depth write, no cull
    };

    WGPURenderPipeline pipelineFor(WGPUTextureFormat, bool decal, std::string& error);
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
};

}  // namespace render
