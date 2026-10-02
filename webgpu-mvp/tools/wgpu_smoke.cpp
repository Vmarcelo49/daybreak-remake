// wgpu_smoke — renders the game's three model categories offscreen through wgpu-native.
//
//   wgpu_smoke <model.x>                           a single .X file
//   wgpu_smoke --stage=<dir>                       data/stageNN: up to 8 sub-models + fog
//   wgpu_smoke --character=<base>/<name>[:c]       data/<name>[_B.._F] costume directory
//   wgpu_smoke --weapon=<bulletDir>:<slot>         a weapon (model named by its .dat)
//
// Common options:
//   --out=frame.ppm  --size=N  --winding=cw|ccw  --flip-y=0|1  --unlit  --alpha-test
//   --anim=N  --time=S  --frames=N --dt=S   (advance animation by a variable delta)
//   --no-textures   --camera=iso|front|top   --list
//
// What this proves beyond "it draws something":
//   * the loader feeds a real GPU — vertex layout, bind groups, palettes, textures;
//   * textures resolve and decode (cnv.h) and land on the right materials;
//     --no-textures renders the same scene untextured for comparison;
//   * a stage is many sub-models in world space, a character is a skinned hierarchy,
//     a weapon rides a bone of it — all three go through one draw path;
//   * animation is a pure function of elapsed time, so the frame delta may be whatever
//     the display gives us. The CPU-side proof is `xmodel_tool dtcheck`.
//
// Build: see build.sh; needs model.wgsl in the working directory.

#define XMODEL_WEBGPU
#include <webgpu/webgpu.h>

#define XMODEL_IMPLEMENTATION
#define CNV_IMPLEMENTATION
#define SCENE_IMPLEMENTATION
#include "../scene.h"

#include <glm/gtc/matrix_transform.hpp>

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>

namespace {

struct Options {
    std::string model, stage, character, weapon, out = "frame.ppm";
    int         size = 512;
    std::string winding = "cw";
    bool        flipY = false;      // see model.wgsl: no Vulkan-style Y negation for wgpu
    bool        unlit = false, alphaTest = false, noTextures = false, list = false;
    bool        noFog = false;
    bool        noCull = false;    // diagnose backdrop shells seen from inside
    int         anim = -1;
    float       time = 0.f;
    int         frames = 1;
    float       dt = 1.f / 60.f;
    std::string camera = "auto";
    std::string look;          // frame a named mesh (e.g. the school building)
    float       azimuth = 0.f, elevation = 0.f, dist = 0.f;
    bool        haveEye = false, haveAt = false;
    glm::vec3   eyePos{0.f}, atPos{0.f};
};

struct GpuState {
    WGPUInstance instance = nullptr;
    WGPUAdapter  adapter  = nullptr;
    WGPUDevice   device   = nullptr;
    WGPUQueue    queue    = nullptr;
};

std::string g_lastError;
bool g_noCull = false;
bool g_noFog = false;   // --no-fog, for isolating geometry from stage fog

WGPUStringView sv(const char* s) { return WGPUStringView{s, std::strlen(s)}; }
WGPUStringView sv(const std::string& s) { return WGPUStringView{s.data(), s.size()}; }

void onUncapturedError(WGPUDevice const*, WGPUErrorType type, WGPUStringView message,
                       void*, void*) {
    char buf[1024];
    std::snprintf(buf, sizeof buf, "wgpu error (type %d): %.*s", (int)type, (int)message.length,
                  message.data ? message.data : "");
    g_lastError = buf;
    std::fprintf(stderr, "[wgpu] %s\n", buf);
}

struct AdapterRequest { WGPUAdapter adapter = nullptr; bool done = false; };
void onAdapter(WGPURequestAdapterStatus status, WGPUAdapter adapter, WGPUStringView msg,
               void* ud1, void*) {
    auto* r = (AdapterRequest*)ud1;
    r->done = true;
    if (status == WGPURequestAdapterStatus_Success) r->adapter = adapter;
    else std::fprintf(stderr, "[wgpu] requestAdapter failed: %.*s\n", (int)msg.length,
                      msg.data ? msg.data : "");
}

struct DeviceRequest { WGPUDevice device = nullptr; bool done = false; };
void onDevice(WGPURequestDeviceStatus status, WGPUDevice device, WGPUStringView msg,
              void* ud1, void*) {
    auto* r = (DeviceRequest*)ud1;
    r->done = true;
    if (status == WGPURequestDeviceStatus_Success) r->device = device;
    else std::fprintf(stderr, "[wgpu] requestDevice failed: %.*s\n", (int)msg.length,
                      msg.data ? msg.data : "");
}

struct MapRequest { bool done = false; bool ok = false; };
void onMapped(WGPUMapAsyncStatus status, WGPUStringView msg, void* ud1, void*) {
    auto* r = (MapRequest*)ud1;
    r->done = true;
    r->ok = (status == WGPUMapAsyncStatus_Success);
    if (!r->ok) std::fprintf(stderr, "[wgpu] mapAsync failed: %.*s\n", (int)msg.length,
                             msg.data ? msg.data : "");
}

bool initGpu(GpuState& gpu) {
    gpu.instance = wgpuCreateInstance(nullptr);
    if (!gpu.instance) { std::fprintf(stderr, "no wgpu instance\n"); return false; }

    AdapterRequest ar;
    WGPURequestAdapterOptions opts = WGPU_REQUEST_ADAPTER_OPTIONS_INIT;
    opts.powerPreference = WGPUPowerPreference_HighPerformance;
    WGPURequestAdapterCallbackInfo acb = WGPU_REQUEST_ADAPTER_CALLBACK_INFO_INIT;
    acb.mode = WGPUCallbackMode_AllowProcessEvents;
    acb.callback = onAdapter;
    acb.userdata1 = &ar;
    wgpuInstanceRequestAdapter(gpu.instance, &opts, acb);
    while (!ar.done) wgpuInstanceProcessEvents(gpu.instance);
    if (!ar.adapter) return false;
    gpu.adapter = ar.adapter;

    WGPUDeviceDescriptor dd = WGPU_DEVICE_DESCRIPTOR_INIT;
    dd.uncapturedErrorCallbackInfo.callback = onUncapturedError;
    DeviceRequest dr;
    WGPURequestDeviceCallbackInfo dcb = WGPU_REQUEST_DEVICE_CALLBACK_INFO_INIT;
    dcb.mode = WGPUCallbackMode_AllowProcessEvents;
    dcb.callback = onDevice;
    dcb.userdata1 = &dr;
    wgpuAdapterRequestDevice(gpu.adapter, &dd, dcb);
    while (!dr.done) wgpuInstanceProcessEvents(gpu.instance);
    if (!dr.device) return false;
    gpu.device = dr.device;
    gpu.queue = wgpuDeviceGetQueue(gpu.device);
    return gpu.queue != nullptr;
}

WGPUBuffer makeBuffer(WGPUDevice dev, const void* data, uint64_t size, WGPUBufferUsage usage) {
    if (size == 0) size = 4;                     // a zero-sized binding is invalid
    WGPUBufferDescriptor bd = WGPU_BUFFER_DESCRIPTOR_INIT;
    bd.usage = usage | WGPUBufferUsage_CopyDst;
    bd.size = size;
    bd.mappedAtCreation = true;
    WGPUBuffer buf = wgpuDeviceCreateBuffer(dev, &bd);
    if (!buf) return nullptr;
    void* p = wgpuBufferGetMappedRange(buf, 0, size);
    if (p && data) std::memcpy(p, data, (size_t)size);
    else if (p) std::memset(p, 0, (size_t)size);
    wgpuBufferUnmap(buf);
    return buf;
}

// Left-handed view + projection. Deliberately no clip-space Y flip: wgpu presents a
// Y-up NDC on every backend, so the negation a raw Vulkan port needs would render
// everything upside down here. --flip-y=1 exists to demonstrate exactly that.
glm::mat4 makeViewProj(const glm::vec3& eye, const glm::vec3& target, float aspect, bool flipY,
                       float radius, float sceneReach) {
    const float dist = glm::length(eye - target);
    // Near scales with the distance being framed; FAR must reach the whole scene, not
    // just the subject. The sky dome sits ~80 000 units out on these stages, so a far
    // plane sized to the framed mesh clips the entire sky to the clear colour — which
    // reads as "the skybox has no texture" rather than as a clipping bug.
    const float nearZ = std::max(0.01f, dist * 0.001f);
    const float farZ  = std::max({1000.f, dist + radius * 4.f, sceneReach * 1.05f});
    glm::mat4 view = glm::lookAtLH(eye, target, glm::vec3(0, 1, 0));
    glm::mat4 proj = glm::perspectiveLH_ZO(glm::radians(45.f), aspect, nearZ, farZ);
    if (flipY) proj[1][1] *= -1.f;
    return proj * view;
}

// ---------------------------------------------------------------------------------------
// GPU objects built from a scene
// ---------------------------------------------------------------------------------------
struct GpuTexture {
    WGPUTexture     tex  = nullptr;
    WGPUTextureView view = nullptr;
};

struct DrawItem {
    WGPUBuffer vbuf = nullptr, ibuf = nullptr;   // borrowed; owned by SceneGpu::buffers
    uint32_t   firstIndex = 0, indexCount = 0;
    uint32_t   paletteOffset = 0;
    uint32_t   flags = 0;                        // per-draw, from the material
    int        texture = -1;                     // -1 -> the 1x1 white fallback
    bool       decal = false;                    // baked shadow: drawn last, multiplied
    glm::mat4  model{1.f};
};

// Baked shadow decals are identified by name, exactly as the DX9 fix does: the
// "shadow*" family plus the 影 (kage) names the stages use for 校舎影02 / 手すり影 /
// 影坂01. Effect-technique binding (P3.1) would replace this heuristic; until then the
// name is the same provisional signal the remake uses.
bool isShadowDecalName(const std::string& raw) {
    std::string s = xm::sjisToUtf8(raw);
    std::string lower;
    lower.reserve(s.size());
    for (char c : s) lower += (char)std::tolower((unsigned char)c);
    if (lower.find("shadow") != std::string::npos) return true;
    return s.find("\xe5\xbd\xb1") != std::string::npos;   // 影 in UTF-8
}

struct SceneGpu {
    std::vector<DrawItem>   draws;
    std::vector<WGPUBuffer> buffers;      // owned
    std::vector<GpuTexture> textures;     // owned
    std::vector<glm::mat4>  palette;
    int textured = 0, untextured = 0;
};

GpuTexture uploadTexture(GpuState& gpu, const xm::CnvImage& img) {
    GpuTexture out;
    WGPUTextureDescriptor td = WGPU_TEXTURE_DESCRIPTOR_INIT;
    td.usage = WGPUTextureUsage_TextureBinding | WGPUTextureUsage_CopyDst;
    td.dimension = WGPUTextureDimension_2D;
    td.size = WGPUExtent3D{img.width, img.height, 1};
    td.format = WGPUTextureFormat_RGBA8Unorm;
    td.mipLevelCount = 1;
    td.sampleCount = 1;
    out.tex = wgpuDeviceCreateTexture(gpu.device, &td);
    if (!out.tex) return out;

    WGPUTexelCopyTextureInfo dst = {};
    dst.texture = out.tex;
    dst.aspect = WGPUTextureAspect_All;
    WGPUTexelCopyBufferLayout layout = {};
    layout.bytesPerRow = img.width * 4;
    layout.rowsPerImage = img.height;
    const WGPUExtent3D extent{img.width, img.height, 1};
    wgpuQueueWriteTexture(gpu.queue, &dst, img.rgba.data(), img.rgba.size(), &layout, &extent);
    out.view = wgpuTextureCreateView(out.tex, nullptr);
    return out;
}

// One draw per submesh, palettes packed back to back, textures deduplicated by image.
void buildSceneGpu(GpuState& gpu, const xm::Scene& scene,
                   const std::vector<std::vector<glm::mat4>>& worlds,
                   const std::vector<glm::mat4>& modelMatrices, bool useTextures, SceneGpu& out) {
    std::unordered_map<const xm::CnvImage*, int> texIndex;
    std::vector<glm::mat4> meshPalette;

    for (size_t mi = 0; mi < scene.models.size(); ++mi) {
        const xm::SceneModel& sm = scene.models[mi];
        if (!sm.drawable) continue;      // collision volumes are for queries/framing only
        const glm::mat4 model = mi < modelMatrices.size() ? modelMatrices[mi] : glm::mat4(1.f);
        const std::vector<glm::mat4>& world = mi < worlds.size() ? worlds[mi]
                                                                 : std::vector<glm::mat4>();

        for (const xm::Mesh& mesh : sm.model.meshes) {
            if (mesh.vertices.empty() || mesh.indices.empty()) continue;
            sm.model.buildPalette(mesh, world, meshPalette);
            const uint32_t paletteOffset = (uint32_t)out.palette.size();
            out.palette.insert(out.palette.end(), meshPalette.begin(), meshPalette.end());

            WGPUBuffer vbuf = makeBuffer(gpu.device, mesh.vertices.data(),
                                         mesh.vertices.size() * sizeof(xm::Vertex),
                                         WGPUBufferUsage_Vertex);
            WGPUBuffer ibuf = makeBuffer(gpu.device, mesh.indices.data(),
                                         mesh.indices.size() * sizeof(uint32_t),
                                         WGPUBufferUsage_Index);
            out.buffers.push_back(vbuf);
            out.buffers.push_back(ibuf);

            for (const xm::Submesh& sub : mesh.submeshes) {
                DrawItem d;
                d.vbuf = vbuf;
                d.ibuf = ibuf;
                d.firstIndex = sub.firstIndex;
                d.indexCount = sub.indexCount;
                d.paletteOffset = paletteOffset;
                d.model = model;

                const xm::Material& mat =
                    (sub.material >= 0 && (size_t)sub.material < mesh.materials.size())
                        ? mesh.materials[(size_t)sub.material]
                        : (mesh.materials.empty() ? xm::Material{} : mesh.materials[0]);
                const bool decal = !mat.texture.empty() && isShadowDecalName(mat.texture);
                if (useTextures && !mat.texture.empty()) {
                    xm::CnvImage* img = const_cast<xm::CnvImage*>(sm.textures.get(mat.texture));
                    if (img && !img->empty()) {
                        // White keys out so the card disappears where it is neutral and
                        // only the blob multiplies. Idempotent, so shared textures are
                        // safe to process once here.
                        if (decal) xm::keyOutWhite(*img);
                        auto it = texIndex.find(img);
                        if (it == texIndex.end()) {
                            it = texIndex.emplace(img, (int)out.textures.size()).first;
                            out.textures.push_back(uploadTexture(gpu, *img));
                        }
                        d.texture = it->second;
                        ++out.textured;
                    } else {
                        ++out.untextured;
                    }
                } else {
                    ++out.untextured;
                }
                d.decal = decal;
                // A decal must not be shaded: white has to stay exactly white or the
                // multiply darkens the ground it is supposed to leave alone.
                if (decal) d.flags |= xm::kDrawUnlit;
                out.draws.push_back(d);
            }
        }
    }
    // Baked shadows are coplanar with the ground and do not write depth, so they must be
    // drawn after it. The original draws its decal pass last for the same reason.
    std::stable_partition(out.draws.begin(), out.draws.end(),
                          [](const DrawItem& d) { return !d.decal; });
}

struct Frame {
    std::vector<uint8_t> rgba;
    int width = 0, height = 0, covered = 0;
    float minLum = 1.f, maxLum = 0.f;
};

Frame renderOnce(GpuState& gpu, const xm::Scene& scene, const SceneGpu& sg,
                 const glm::mat4& viewProj, int size, const std::string& winding, bool writeFile,
                 const std::string& out, uint32_t extraFlags) {
    Frame frame;
    frame.width = frame.height = size;
    if (sg.draws.empty()) { std::fprintf(stderr, "nothing to draw\n"); return frame; }

    WGPUBuffer paletteBuf = makeBuffer(gpu.device, sg.palette.data(),
                                       sg.palette.size() * sizeof(glm::mat4),
                                       WGPUBufferUsage_Storage);

    xm::CameraUniform cam;
    cam.viewProj = viewProj;
    cam.lightDir = glm::vec4(glm::normalize(glm::vec3(0.3f, -0.8f, 0.5f)), 0.f);
    cam.lightColor = glm::vec4(1.f, 0.98f, 0.95f, 1.f);
    cam.ambient = glm::vec4(0.35f, 0.36f, 0.40f, 1.f);
    if (scene.env.present && scene.env.fogEnabled && !g_noFog) {
        cam.fogColor = glm::vec4(scene.env.fogColor, 1.f);
        cam.fogParams = glm::vec4(scene.env.fogStart, scene.env.fogEnd, 1.f, 0.f);
    }
    WGPUBuffer camBuf = makeBuffer(gpu.device, &cam, sizeof cam, WGPUBufferUsage_Uniform);

    std::vector<uint8_t> drawData((size_t)xm::kDrawStride * sg.draws.size(), 0);
    for (size_t i = 0; i < sg.draws.size(); ++i) {
        xm::DrawUniform du;
        du.model = sg.draws[i].model;
        du.paletteOffset = sg.draws[i].paletteOffset;
        du.flags = extraFlags | sg.draws[i].flags;
        // The original enables alpha test for 3D passes with ref 0x08 and GE — a very
        // low threshold, which trims foliage and ground cards without eating soft edges.
        if (sg.draws[i].texture >= 0) du.flags |= xm::kDrawTextured | xm::kDrawAlphaTest;
        std::memcpy(drawData.data() + i * xm::kDrawStride, &du, sizeof du);
    }
    WGPUBuffer drawBuf = makeBuffer(gpu.device, drawData.data(), drawData.size(),
                                    WGPUBufferUsage_Uniform);

    const uint32_t white = 0xffffffffu;
    WGPUTextureDescriptor td = WGPU_TEXTURE_DESCRIPTOR_INIT;
    td.usage = WGPUTextureUsage_TextureBinding | WGPUTextureUsage_CopyDst;
    td.dimension = WGPUTextureDimension_2D;
    td.size = WGPUExtent3D{1, 1, 1};
    td.format = WGPUTextureFormat_RGBA8Unorm;
    td.mipLevelCount = 1;
    td.sampleCount = 1;
    WGPUTexture whiteTex = wgpuDeviceCreateTexture(gpu.device, &td);
    WGPUTexelCopyTextureInfo wdst = {};
    wdst.texture = whiteTex;
    wdst.aspect = WGPUTextureAspect_All;
    WGPUTexelCopyBufferLayout wlayout = {};
    wlayout.bytesPerRow = 4;
    wlayout.rowsPerImage = 1;
    wgpuQueueWriteTexture(gpu.queue, &wdst, &white, 4, &wlayout, &td.size);
    WGPUTextureView whiteView = wgpuTextureCreateView(whiteTex, nullptr);

    WGPUSamplerDescriptor sd = WGPU_SAMPLER_DESCRIPTOR_INIT;
    sd.addressModeU = sd.addressModeV = sd.addressModeW = WGPUAddressMode_Repeat;
    sd.magFilter = WGPUFilterMode_Linear;
    sd.minFilter = WGPUFilterMode_Linear;
    sd.mipmapFilter = WGPUMipmapFilterMode_Nearest;
    sd.maxAnisotropy = 1;
    WGPUSampler sampler = wgpuDeviceCreateSampler(gpu.device, &sd);

    std::FILE* f = std::fopen("model.wgsl", "rb");
    if (!f) { std::fprintf(stderr, "cannot open model.wgsl (run from the webgpu-mvp dir)\n"); return frame; }
    std::string wgsl;
    { char buf[4096]; size_t n; while ((n = std::fread(buf, 1, sizeof buf, f)) > 0) wgsl.append(buf, n); }
    std::fclose(f);

    WGPUShaderSourceWGSL wgslDesc = WGPU_SHADER_SOURCE_WGSL_INIT;
    wgslDesc.code = sv(wgsl);
    WGPUShaderModuleDescriptor smd = WGPU_SHADER_MODULE_DESCRIPTOR_INIT;
    smd.nextInChain = &wgslDesc.chain;
    WGPUShaderModule shader = wgpuDeviceCreateShaderModule(gpu.device, &smd);
    if (!shader) { std::fprintf(stderr, "shader module failed: %s\n", g_lastError.c_str()); return frame; }

    WGPUBindGroupLayoutEntry bgl0[1] = {};
    bgl0[0].binding = 0;
    bgl0[0].visibility = WGPUShaderStage_Vertex | WGPUShaderStage_Fragment;
    bgl0[0].buffer = WGPU_BUFFER_BINDING_LAYOUT_INIT;
    bgl0[0].buffer.type = WGPUBufferBindingType_Uniform;
    bgl0[0].buffer.minBindingSize = sizeof(xm::CameraUniform);

    WGPUBindGroupLayoutEntry bgl1[2] = {};
    bgl1[0].binding = 0;
    bgl1[0].visibility = WGPUShaderStage_Vertex | WGPUShaderStage_Fragment;
    bgl1[0].buffer = WGPU_BUFFER_BINDING_LAYOUT_INIT;
    bgl1[0].buffer.type = WGPUBufferBindingType_Uniform;
    bgl1[0].buffer.hasDynamicOffset = true;
    bgl1[0].buffer.minBindingSize = sizeof(xm::DrawUniform);
    bgl1[1].binding = 1;
    bgl1[1].visibility = WGPUShaderStage_Vertex;
    bgl1[1].buffer = WGPU_BUFFER_BINDING_LAYOUT_INIT;
    bgl1[1].buffer.type = WGPUBufferBindingType_ReadOnlyStorage;

    WGPUBindGroupLayoutEntry bgl2[2] = {};
    bgl2[0].binding = 0;
    bgl2[0].visibility = WGPUShaderStage_Fragment;
    bgl2[0].texture = WGPU_TEXTURE_BINDING_LAYOUT_INIT;
    bgl2[0].texture.sampleType = WGPUTextureSampleType_Float;
    bgl2[0].texture.viewDimension = WGPUTextureViewDimension_2D;
    bgl2[1].binding = 1;
    bgl2[1].visibility = WGPUShaderStage_Fragment;
    bgl2[1].sampler = WGPU_SAMPLER_BINDING_LAYOUT_INIT;
    bgl2[1].sampler.type = WGPUSamplerBindingType_Filtering;

    WGPUBindGroupLayoutDescriptor bglDesc[3];
    WGPUBindGroupLayout layouts[3];
    for (int i = 0; i < 3; ++i) bglDesc[i] = WGPU_BIND_GROUP_LAYOUT_DESCRIPTOR_INIT;
    bglDesc[0].entryCount = 1; bglDesc[0].entries = bgl0;
    bglDesc[1].entryCount = 2; bglDesc[1].entries = bgl1;
    bglDesc[2].entryCount = 2; bglDesc[2].entries = bgl2;
    for (int i = 0; i < 3; ++i) {
        layouts[i] = wgpuDeviceCreateBindGroupLayout(gpu.device, &bglDesc[i]);
        if (!layouts[i]) { std::fprintf(stderr, "bgl %d failed: %s\n", i, g_lastError.c_str()); return frame; }
    }
    WGPUPipelineLayoutDescriptor pld = WGPU_PIPELINE_LAYOUT_DESCRIPTOR_INIT;
    pld.bindGroupLayoutCount = 3;
    pld.bindGroupLayouts = layouts;
    WGPUPipelineLayout pipelineLayout = wgpuDeviceCreatePipelineLayout(gpu.device, &pld);

    WGPUBindGroupEntry entries[2];
    WGPUBindGroupDescriptor bgDesc = WGPU_BIND_GROUP_DESCRIPTOR_INIT;
    bgDesc.layout = layouts[0];
    entries[0] = WGPU_BIND_GROUP_ENTRY_INIT;
    entries[0].binding = 0;
    entries[0].buffer = camBuf;
    entries[0].size = sizeof(xm::CameraUniform);
    bgDesc.entryCount = 1;
    bgDesc.entries = entries;
    WGPUBindGroup bg0 = wgpuDeviceCreateBindGroup(gpu.device, &bgDesc);

    bgDesc.layout = layouts[1];
    entries[0] = WGPU_BIND_GROUP_ENTRY_INIT;
    entries[0].binding = 0;
    entries[0].buffer = drawBuf;
    entries[0].size = sizeof(xm::DrawUniform);
    entries[1] = WGPU_BIND_GROUP_ENTRY_INIT;
    entries[1].binding = 1;
    entries[1].buffer = paletteBuf;
    entries[1].size = sg.palette.size() * sizeof(glm::mat4);
    bgDesc.entryCount = 2;
    WGPUBindGroup bg1 = wgpuDeviceCreateBindGroup(gpu.device, &bgDesc);

    // group 2 differs only by the texture view, so one bind group per texture.
    std::vector<WGPUBindGroup> texGroups;
    texGroups.reserve(sg.textures.size() + 1);
    for (size_t i = 0; i <= sg.textures.size(); ++i) {
        bgDesc.layout = layouts[2];
        entries[0] = WGPU_BIND_GROUP_ENTRY_INIT;
        entries[0].binding = 0;
        entries[0].textureView = (i == 0) ? whiteView : sg.textures[i - 1].view;
        entries[1] = WGPU_BIND_GROUP_ENTRY_INIT;
        entries[1].binding = 1;
        entries[1].sampler = sampler;
        bgDesc.entryCount = 2;
        texGroups.push_back(wgpuDeviceCreateBindGroup(gpu.device, &bgDesc));
    }

    WGPUVertexAttribute attrs[xm::kVertexAttributeCount];
    WGPUVertexBufferLayout vbl = xm::wgpuVertexLayout(attrs);

    // Two pipelines share everything except the blend/depth-write/cull state:
    //   * the normal one draws lit, textured 3D geometry with alpha blending;
    //   * the decal one reproduces what the DX9 path does for baked shadows —
    //     dest = src * dst (SRCBLEND = DESTCOLOR, DESTBLEND = ZERO in the remake),
    //     ZWRITEENABLE off so the card never occludes anything, and culling off
    //     because a decal card can face either way.
    auto makePipeline = [&](bool multiply, bool depthWrite, WGPUCullMode cull) -> WGPURenderPipeline {
        WGPUColorTargetState target = WGPU_COLOR_TARGET_STATE_INIT;
        target.format = WGPUTextureFormat_RGBA8Unorm;
        WGPUBlendState blend = WGPU_BLEND_STATE_INIT;
        if (multiply) {
            blend.color.srcFactor = WGPUBlendFactor_Dst;
            blend.color.dstFactor = WGPUBlendFactor_Zero;
            blend.alpha.srcFactor = WGPUBlendFactor_Zero;
            blend.alpha.dstFactor = WGPUBlendFactor_One;
        } else {
            blend.color.srcFactor = WGPUBlendFactor_SrcAlpha;
            blend.color.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
            blend.alpha.srcFactor = WGPUBlendFactor_One;
            blend.alpha.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
        }
        blend.color.operation = WGPUBlendOperation_Add;
        blend.alpha.operation = WGPUBlendOperation_Add;
        target.blend = &blend;
        target.writeMask = WGPUColorWriteMask_All;

        WGPUFragmentState fs = WGPU_FRAGMENT_STATE_INIT;
        fs.module = shader;
        fs.entryPoint = sv("fs_main");
        fs.targetCount = 1;
        fs.targets = &target;

        // The original renders into a D3DFMT_D16 autodepthstencil. Without a depth
        // buffer a stage is unrenderable: its inverted sky dome encloses the camera, so
        // whichever sub-model is drawn first fills the screen.
        WGPUDepthStencilState depth = WGPU_DEPTH_STENCIL_STATE_INIT;
        depth.format = WGPUTextureFormat_Depth24Plus;
        depth.depthWriteEnabled = depthWrite ? WGPUOptionalBool_True : WGPUOptionalBool_False;
        depth.depthCompare = WGPUCompareFunction_LessEqual;

        WGPURenderPipelineDescriptor rpd = WGPU_RENDER_PIPELINE_DESCRIPTOR_INIT;
        rpd.layout = pipelineLayout;
        rpd.vertex.module = shader;
        rpd.vertex.entryPoint = sv("vs_main");
        rpd.vertex.bufferCount = 1;
        rpd.vertex.buffers = &vbl;
        rpd.primitive.topology = WGPUPrimitiveTopology_TriangleList;
        rpd.primitive.frontFace = (winding == "ccw") ? WGPUFrontFace_CCW : WGPUFrontFace_CW;
        // The original culls counter-clockwise for 3D (CULLMODE = 3) and disables culling
        // for 2D/effect passes.
        rpd.primitive.cullMode = cull;
        rpd.depthStencil = &depth;
        rpd.multisample = WGPU_MULTISAMPLE_STATE_INIT;
        rpd.multisample.count = 1;
        rpd.multisample.mask = 0xFFFFFFFFu;
        rpd.fragment = &fs;
        return wgpuDeviceCreateRenderPipeline(gpu.device, &rpd);
    };

    WGPURenderPipeline pipeline = makePipeline(false, true,
                                               g_noCull ? WGPUCullMode_None : WGPUCullMode_Back);
    WGPURenderPipeline decalPipeline = makePipeline(true, false, WGPUCullMode_None);
    if (!pipeline || !decalPipeline) {
        std::fprintf(stderr, "pipeline failed: %s\n", g_lastError.c_str());
        return frame;
    }

    WGPUTextureDescriptor ctd = WGPU_TEXTURE_DESCRIPTOR_INIT;
    ctd.usage = WGPUTextureUsage_RenderAttachment | WGPUTextureUsage_CopySrc;
    ctd.dimension = WGPUTextureDimension_2D;
    ctd.size = WGPUExtent3D{(uint32_t)size, (uint32_t)size, 1};
    ctd.format = WGPUTextureFormat_RGBA8Unorm;
    ctd.mipLevelCount = 1;
    ctd.sampleCount = 1;
    WGPUTexture colorTex = wgpuDeviceCreateTexture(gpu.device, &ctd);
    WGPUTextureView colorView = wgpuTextureCreateView(colorTex, nullptr);

    WGPUTextureDescriptor dtd = WGPU_TEXTURE_DESCRIPTOR_INIT;
    dtd.usage = WGPUTextureUsage_RenderAttachment;
    dtd.dimension = WGPUTextureDimension_2D;
    dtd.size = WGPUExtent3D{(uint32_t)size, (uint32_t)size, 1};
    dtd.format = WGPUTextureFormat_Depth24Plus;
    dtd.mipLevelCount = 1;
    dtd.sampleCount = 1;
    WGPUTexture depthTex = wgpuDeviceCreateTexture(gpu.device, &dtd);
    WGPUTextureView depthView = wgpuTextureCreateView(depthTex, nullptr);

    // COPY_BYTES_PER_ROW_ALIGNMENT is 256: a tightly packed RGBA row is only legal for
    // widths that happen to be multiples of 64. Pad the pitch and unpad on readback.
    const uint32_t rowPitch = ((uint32_t)size * 4u + 255u) / 256u * 256u;
    const uint64_t readbackBytes = (uint64_t)rowPitch * (uint64_t)size;
    WGPUBufferDescriptor rbd = WGPU_BUFFER_DESCRIPTOR_INIT;
    rbd.usage = WGPUBufferUsage_MapRead | WGPUBufferUsage_CopyDst;
    rbd.size = readbackBytes;
    WGPUBuffer readback = wgpuDeviceCreateBuffer(gpu.device, &rbd);

    WGPURenderPassColorAttachment colorAtt = WGPU_RENDER_PASS_COLOR_ATTACHMENT_INIT;
    colorAtt.view = colorView;
    colorAtt.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
    colorAtt.loadOp = WGPULoadOp_Clear;
    colorAtt.storeOp = WGPUStoreOp_Store;
    colorAtt.clearValue = WGPUColor{0.05, 0.06, 0.08, 1.0};
    WGPURenderPassDepthStencilAttachment depthAtt = WGPU_RENDER_PASS_DEPTH_STENCIL_ATTACHMENT_INIT;
    depthAtt.view = depthView;
    depthAtt.depthLoadOp = WGPULoadOp_Clear;
    depthAtt.depthStoreOp = WGPUStoreOp_Store;
    depthAtt.depthClearValue = 1.0f;
    depthAtt.depthReadOnly = false;
    depthAtt.stencilLoadOp = WGPULoadOp_Undefined;
    depthAtt.stencilStoreOp = WGPUStoreOp_Undefined;

    WGPURenderPassDescriptor rpDesc = WGPU_RENDER_PASS_DESCRIPTOR_INIT;
    rpDesc.colorAttachmentCount = 1;
    rpDesc.colorAttachments = &colorAtt;
    rpDesc.depthStencilAttachment = &depthAtt;

    WGPUCommandEncoderDescriptor ced = WGPU_COMMAND_ENCODER_DESCRIPTOR_INIT;
    WGPUCommandEncoder enc = wgpuDeviceCreateCommandEncoder(gpu.device, &ced);
    WGPURenderPassEncoder pass = wgpuCommandEncoderBeginRenderPass(enc, &rpDesc);
    wgpuRenderPassEncoderSetPipeline(pass, pipeline);
    wgpuRenderPassEncoderSetBindGroup(pass, 0, bg0, 0, nullptr);
    bool decalBound = false;
    for (size_t i = 0; i < sg.draws.size(); ++i) {
        const DrawItem& d = sg.draws[i];
        if (d.decal != decalBound) {          // draws are sorted, so this flips once
            wgpuRenderPassEncoderSetPipeline(pass, d.decal ? decalPipeline : pipeline);
            decalBound = d.decal;
        }
        uint32_t offset = (uint32_t)(i * xm::kDrawStride);
        wgpuRenderPassEncoderSetBindGroup(pass, 1, bg1, 1, &offset);
        wgpuRenderPassEncoderSetBindGroup(pass, 2, texGroups[(size_t)(d.texture + 1)], 0, nullptr);
        wgpuRenderPassEncoderSetVertexBuffer(pass, 0, d.vbuf, 0, WGPU_WHOLE_SIZE);
        wgpuRenderPassEncoderSetIndexBuffer(pass, d.ibuf, WGPUIndexFormat_Uint32, 0, WGPU_WHOLE_SIZE);
        wgpuRenderPassEncoderDrawIndexed(pass, d.indexCount, 1, d.firstIndex, 0, 0);
    }
    wgpuRenderPassEncoderEnd(pass);

    WGPUTexelCopyBufferInfo copy = {};
    copy.buffer = readback;
    copy.layout.bytesPerRow = rowPitch;
    copy.layout.rowsPerImage = (uint32_t)size;
    WGPUTexelCopyTextureInfo src = {};
    src.texture = colorTex;
    src.aspect = WGPUTextureAspect_All;
    wgpuCommandEncoderCopyTextureToBuffer(enc, &src, &copy, &ctd.size);
    WGPUCommandBuffer cmd = wgpuCommandEncoderFinish(enc, nullptr);
    wgpuQueueSubmit(gpu.queue, 1, &cmd);

    MapRequest mr;
    WGPUBufferMapCallbackInfo mcb = WGPU_BUFFER_MAP_CALLBACK_INFO_INIT;
    mcb.mode = WGPUCallbackMode_AllowProcessEvents;
    mcb.callback = onMapped;
    mcb.userdata1 = &mr;
    wgpuBufferMapAsync(readback, WGPUMapMode_Read, 0, readbackBytes, mcb);
    while (!mr.done) wgpuInstanceProcessEvents(gpu.instance);
    if (mr.ok) {
        const uint8_t* px = (const uint8_t*)wgpuBufferGetConstMappedRange(readback, 0, readbackBytes);
        if (px) {
            frame.rgba.assign((size_t)size * size * 4, 0);
            for (int y = 0; y < size; ++y)
                std::memcpy(frame.rgba.data() + (size_t)y * size * 4, px + (size_t)y * rowPitch,
                            (size_t)size * 4);
            for (int i = 0; i < size * size; ++i) {
                const uint8_t* p = frame.rgba.data() + i * 4;
                float lum = (0.2126f * p[0] + 0.7152f * p[1] + 0.0722f * p[2]) / 255.f;
                if (!(p[0] < 20 && p[1] < 22 && p[2] < 26)) {
                    ++frame.covered;
                    frame.minLum = std::min(frame.minLum, lum);
                    frame.maxLum = std::max(frame.maxLum, lum);
                }
            }
        }
        wgpuBufferUnmap(readback);
    }

    if (writeFile) {
        std::FILE* o = std::fopen(out.c_str(), "wb");
        if (o) {
            std::fprintf(o, "P6\n%d %d\n255\n", size, size);
            for (int i = 0; i < size * size; ++i) std::fwrite(frame.rgba.data() + i * 4, 1, 3, o);
            std::fclose(o);
            std::printf("wrote %s\n", out.c_str());
        }
    }

    wgpuCommandBufferRelease(cmd);
    wgpuRenderPassEncoderRelease(pass);
    wgpuCommandEncoderRelease(enc);
    wgpuBufferRelease(readback);
    wgpuTextureViewRelease(depthView);
    wgpuTextureRelease(depthTex);
    wgpuTextureViewRelease(colorView);
    wgpuTextureRelease(colorTex);
    wgpuRenderPipelineRelease(decalPipeline);
    wgpuRenderPipelineRelease(pipeline);
    for (WGPUBindGroup g : texGroups) wgpuBindGroupRelease(g);
    wgpuBindGroupRelease(bg0);
    wgpuBindGroupRelease(bg1);
    wgpuPipelineLayoutRelease(pipelineLayout);
    for (int i = 0; i < 3; ++i) wgpuBindGroupLayoutRelease(layouts[i]);
    wgpuShaderModuleRelease(shader);
    wgpuSamplerRelease(sampler);
    wgpuTextureViewRelease(whiteView);
    wgpuTextureRelease(whiteTex);
    wgpuBufferRelease(drawBuf);
    wgpuBufferRelease(camBuf);
    wgpuBufferRelease(paletteBuf);
    return frame;
}

void releaseSceneGpu(SceneGpu& sg) {
    for (WGPUBuffer b : sg.buffers) wgpuBufferRelease(b);
    for (GpuTexture& t : sg.textures) {
        if (t.view) wgpuTextureViewRelease(t.view);
        if (t.tex) wgpuTextureRelease(t.tex);
    }
    sg.buffers.clear();
    sg.textures.clear();
    sg.draws.clear();
}

}  // namespace

int main(int argc, char** argv) {
    Options o;
    for (int i = 1; i < argc; ++i) {
        std::string a = argv[i];
        auto val = [&](const char* k) {
            return a.rfind(k, 0) == 0 ? a.substr(std::strlen(k)) : std::string();
        };
        if (a.rfind("--", 0) == 0) {
            std::string v;
            if (!(v = val("--stage=")).empty()) o.stage = v;
            else if (!(v = val("--character=")).empty()) o.character = v;
            else if (!(v = val("--weapon=")).empty()) o.weapon = v;
            else if (!(v = val("--out=")).empty()) o.out = v;
            else if (!(v = val("--size=")).empty()) o.size = std::atoi(v.c_str());
            else if (!(v = val("--winding=")).empty()) o.winding = v;
            else if (!(v = val("--flip-y=")).empty()) o.flipY = (v != "0");
            else if (!(v = val("--anim=")).empty()) o.anim = std::atoi(v.c_str());
            else if (!(v = val("--time=")).empty()) o.time = (float)std::atof(v.c_str());
            else if (!(v = val("--frames=")).empty()) o.frames = std::max(1, std::atoi(v.c_str()));
            else if (!(v = val("--dt=")).empty()) o.dt = (float)std::atof(v.c_str());
            else if (!(v = val("--camera=")).empty()) o.camera = v;
            else if (!(v = val("--look=")).empty()) o.look = v;
            else if (!(v = val("--azimuth=")).empty()) o.azimuth = (float)std::atof(v.c_str());
            else if (!(v = val("--elevation=")).empty()) o.elevation = (float)std::atof(v.c_str());
            else if (!(v = val("--dist=")).empty()) o.dist = (float)std::atof(v.c_str());
            else if (!(v = val("--eye=")).empty()) {
                std::sscanf(v.c_str(), "%f,%f,%f", &o.eyePos.x, &o.eyePos.y, &o.eyePos.z);
                o.haveEye = true;
            } else if (!(v = val("--at=")).empty()) {
                std::sscanf(v.c_str(), "%f,%f,%f", &o.atPos.x, &o.atPos.y, &o.atPos.z);
                o.haveAt = true;
            }
            else if (a == "--unlit") o.unlit = true;
            else if (a == "--alpha-test") o.alphaTest = true;
            else if (a == "--no-textures") o.noTextures = true;
            else if (a == "--no-fog") o.noFog = true;
            else if (a == "--no-cull") o.noCull = true;
            else if (a == "--list") o.list = true;
            else { std::fprintf(stderr, "unknown option %s\n", a.c_str()); return 2; }
        } else {
            o.model = a;
        }
    }
    if (o.model.empty() && o.stage.empty() && o.character.empty() && o.weapon.empty()) {
        std::fprintf(stderr,
            "usage: wgpu_smoke <model.x> | --stage=<dir> | --character=<base>/<name>[:c] | "
            "--weapon=<dir>:<slot> [--out=frame.ppm] [--size=N] [--anim=N] [--time=S] "
            "[--frames=N --dt=S] [--no-textures] [--no-fog] "
            "[--camera=auto|player|front|top|bounds] [--list]\n");
        return 2;
    }

    xm::SceneOptions sopt;
    sopt.resolveTextures = !o.noTextures;
    sopt.includeCollision = true;   // framing only; never drawn
    xm::Scene scene;
    try {
        if (!o.stage.empty()) {
            scene = xm::loadStage(o.stage, sopt);
        } else if (!o.character.empty()) {
            std::string spec = o.character;
            int costume = 0;
            // The costume suffix is `:N`, but a Windows path starts with a drive-letter
            // colon — so take the LAST colon and only when it is followed by digits.
            const size_t colon = spec.find_last_of(':');
            if (colon != std::string::npos && colon + 1 < spec.size() &&
                std::isdigit((unsigned char)spec[colon + 1])) {
                costume = std::atoi(spec.c_str() + colon + 1);
                spec = spec.substr(0, colon);
            }
            const size_t slash = spec.find_last_of("/\\");
            const std::string base = (slash == std::string::npos) ? "." : spec.substr(0, slash);
            const std::string name = (slash == std::string::npos) ? spec : spec.substr(slash + 1);
            scene = xm::loadCharacter(base, name, costume, sopt);
            // A weapon rides a bone of the character, so it can only be attached once
            // the character's rig exists. --weapon=<dir>:<slot> loads it against that rig.
            if (!o.weapon.empty()) {
                std::string wspec = o.weapon;
                int slot = 0;
                const size_t wcolon = wspec.find_last_of(':');
                if (wcolon != std::string::npos && wcolon + 1 < wspec.size() &&
                    std::isdigit((unsigned char)wspec[wcolon + 1])) {
                    slot = std::atoi(wspec.c_str() + wcolon + 1);
                    wspec = wspec.substr(0, wcolon);
                }
                const xm::Model* rig = scene.models.empty() ? nullptr : &scene.models[0].model;
                xm::Scene w = xm::loadWeapon(wspec, slot, rig, sopt);
                for (xm::SceneModel& sm : w.models) scene.models.push_back(std::move(sm));
            }
        } else if (!o.weapon.empty()) {
            std::string spec = o.weapon;
            int slot = 0;
            const size_t colon = spec.find_last_of(':');
            if (colon != std::string::npos) {
                slot = std::atoi(spec.c_str() + colon + 1);
                spec = spec.substr(0, colon);
            }
            scene = xm::loadWeapon(spec, slot, nullptr, sopt);
        } else {
            xm::SceneModel sm;
            sm.model = xm::loadFile(o.model);
            sm.source = o.model;
            sm.role = "model";
            const size_t slash = o.model.find_last_of("/\\");
            sm.textures = xm::TextureCache(slash == std::string::npos
                                               ? std::string()
                                               : o.model.substr(0, slash + 1));
            scene.models.push_back(std::move(sm));
            scene.source = o.model;
        }
    } catch (const std::exception& e) {
        std::fprintf(stderr, "load failed: %s\n", e.what());
        return 1;
    }
    if (scene.models.empty()) { std::fprintf(stderr, "nothing loaded\n"); return 1; }

    if (o.list) {
        for (const xm::SceneModel& sm : scene.models)
            std::printf("  %-10s %-46s meshes=%-3zu anims=%-4zu frames=%-4zu%s\n", sm.role.c_str(),
                        sm.source.c_str(), sm.model.meshes.size(), sm.model.anims.size(),
                        sm.model.frames.size(), sm.attachFrame >= 0 ? " (bone-attached)" : "");
        std::printf("  %zu models, %zu meshes, %zu vertices\n", scene.models.size(),
                    scene.totalMeshes(), scene.totalVertices());
        return 0;
    }
    xm::resolveSceneTextures(scene);

    // ---- pose: bind pose, or an animation driven through the Controller
    std::vector<xm::Controller> controllers(scene.models.size());
    std::vector<std::vector<glm::mat4>> worlds(scene.models.size());
    for (size_t i = 0; i < scene.models.size(); ++i) {
        xm::Model& m = scene.models[i].model;
        if (o.anim >= 0 && (size_t)o.anim < m.anims.size()) {
            controllers[i].bind(&m);
            controllers[i].setAnimation(o.anim, true);
            controllers[i].setTrackPosition(0, (double)o.time);
            controllers[i].evalWorld(worlds[i]);
        } else {
            m.evalPose(nullptr, 0.f, false, worlds[i]);
        }
    }

    // ---- bounds over the posed scene, so the camera frames whatever was loaded
    // Weapons are placed by the owning character's attachment bone: the original hangs
    // them off Bip01_Prop1/Prop2 and draws nothing else for them (FUN_00433eb0).
    std::vector<glm::mat4> modelMatrices(scene.models.size(), glm::mat4(1.f));
    {
        int rigIndex = -1;
        for (size_t i = 0; i < scene.models.size(); ++i)
            if (scene.models[i].role == "character") { rigIndex = (int)i; break; }
        for (size_t i = 0; i < scene.models.size(); ++i) {
            const xm::SceneModel& sm = scene.models[i];
            if (sm.attachFrame < 0) continue;
            if (rigIndex < 0 || (size_t)rigIndex >= worlds.size() ||
                (size_t)sm.attachFrame >= worlds[(size_t)rigIndex].size()) {
                std::fprintf(stderr, "[scene] %s: attachment frame %d unusable, drawing at the "
                                     "origin\n", sm.source.c_str(), sm.attachFrame);
                continue;
            }
            modelMatrices[i] = worlds[(size_t)rigIndex][(size_t)sm.attachFrame];
        }
    }
    glm::vec3 lo(1e30f), hi(-1e30f);
    bool framed = scene.bounds(lo, hi, /*playArea=*/true);
    if (!framed) framed = scene.bounds(lo, hi, /*playArea=*/false);
    if (!framed) { lo = glm::vec3(-1.f); hi = glm::vec3(1.f); }
    glm::vec3 center = (lo + hi) * 0.5f;
    float radius = glm::length(hi - lo) * 0.5f;
    if (!(radius > 0.f)) radius = 1.f;
    // Framing a whole stage from its mesh bounds does not work: the visible set
    // includes an inverted sky dome tens of thousands of units across while the play
    // area is a couple of thousand, and env.dat's fog ends at 10000 — so a bounds-fit
    // camera ends up outside the fog and renders a flat wall of fog colour. env.dat
    // carries the four spawn points, which is exactly the play area, so stages frame
    // from those and everything else frames from its bounds.
    // Frame the play area, not the sky dome: a dome is tens of thousands of units
    // across and would push the camera outside env.dat's fog range, rendering a flat
    // wall of fog. The collision meshes are the play area by construction.
    // env.dat's trailing four vec3s are the player spawn points, so they are the one
    // place guaranteed to be on the ground inside the play area — and the game's own
    // camera lives in there (env.dat fog ends at ~10 000 units, so anything framed from
    // outside the arena is a flat wall of fog by construction).
    glm::vec3 target = center;
    float camDist = radius * 2.0f;
    glm::vec3 spawnEye(0.f);
    bool haveSpawn = false;
    if (scene.env.present) {
        spawnEye = scene.env.points[0];
        haveSpawn = true;
    }
    // --look=<mesh> frames one named mesh (the school building, a weapon, a shed) with
    // an explicit azimuth/elevation/distance so a view can be matched to a reference.
    if (!o.look.empty()) {
        glm::vec3 llo(1e30f), lhi(-1e30f);
        bool found = false;
        for (const xm::SceneModel& sm : scene.models) {
            if (!sm.drawable) continue;      // collision meshes borrow the same names
            for (const xm::Mesh& mesh : sm.model.meshes) {
                if (mesh.name.rfind(o.look, 0) != 0) continue;
                for (const xm::Vertex& v : mesh.vertices) {
                    llo = glm::min(llo, v.pos);
                    lhi = glm::max(lhi, v.pos);
                    found = true;
                }
                std::printf("look: mesh '%s' in %s, %zu verts\n", mesh.name.c_str(),
                            sm.source.c_str(), mesh.vertices.size());
            }
        }
        if (found) {
            target = (llo + lhi) * 0.5f;
            const float d = glm::length(lhi - llo);
            radius = d * 0.5f;
            camDist = o.dist > 0.f ? d * o.dist : d * 1.15f;
            std::printf("look target [%.0f %.0f %.0f] extents [%.0f %.0f %.0f] distance %.0f\n",
                        target.x, target.y, target.z, lhi.x - llo.x, lhi.y - llo.y, lhi.z - llo.z,
                        camDist);
        } else {
            std::fprintf(stderr, "no mesh named '%s'\n", o.look.c_str());
        }
    }

    glm::vec3 eye;
    if (o.haveAt) target = o.atPos;
    if (o.haveEye) {
        // Explicit placement wins: matching a reference screenshot is a matter of
        // putting the eye exactly where the other renderer had it.
        eye = o.eyePos;
        camDist = glm::length(eye - target);
    }
    else if (!o.look.empty()) {
        const float az = glm::radians(o.azimuth);
        const float el = glm::radians(o.elevation);
        eye = target + glm::vec3(std::sin(az) * std::cos(el), std::sin(el),
                                 -std::cos(az) * std::cos(el)) * camDist;
    }
    else if (o.camera == "front")      eye = target + glm::vec3(0.f, 0.f, -1.f) * camDist;
    else if (o.camera == "top")   eye = target + glm::vec3(0.02f, 1.f, -0.16f) * camDist;
    else if (o.camera == "bounds") eye = target + glm::vec3(0.9f, 0.45f, -1.15f) * camDist;
    else if (o.camera == "player" && haveSpawn)
        eye = spawnEye + glm::vec3(0.f, 320.f, 0.f);   // eye height above the spawn
    else                          eye = target + glm::vec3(0.62f, 0.34f, -0.71f) * camDist;

    std::printf("scene %s: %zu model(s), %zu meshes, %zu vertices, %zu palette matrices\n",
                scene.source.c_str(), scene.models.size(), scene.totalMeshes(),
                scene.totalVertices(), scene.paletteSize());
    std::printf("bounds [%.0f %.0f %.0f] .. [%.0f %.0f %.0f]  radius %.0f\n",
                lo.x, lo.y, lo.z, hi.x, hi.y, hi.z, radius);
    std::printf("camera %s at [%.0f %.0f %.0f] looking at [%.0f %.0f %.0f] (distance %.0f)\n",
                o.camera.c_str(), eye.x, eye.y, eye.z, target.x, target.y, target.z, camDist);
    if (scene.env.present)
        std::printf("fog from env.dat: %.0f..%.0f rgb(%.2f %.2f %.2f)%s\n", scene.env.fogStart,
                    scene.env.fogEnd, scene.env.fogColor.r, scene.env.fogColor.g,
                    scene.env.fogColor.b, scene.env.fogEnabled ? "" : " (disabled)");

    GpuState gpu;
    if (!initGpu(gpu)) { std::fprintf(stderr, "GPU init failed\n"); return 1; }

    // Reach from the eye to the farthest scene corner, so the far plane always covers
    // every sub-model including the backdrop dome.
    glm::vec3 slo(1e30f), shi(-1e30f);
    scene.bounds(slo, shi, /*playArea=*/false);
    float sceneReach = 0.f;
    if (slo.x < 1e29f)
        for (int c = 0; c < 8; ++c) {
            const glm::vec3 corner((c & 1) ? shi.x : slo.x, (c & 2) ? shi.y : slo.y,
                                   (c & 4) ? shi.z : slo.z);
            sceneReach = std::max(sceneReach, glm::length(corner - eye));
        }
    glm::mat4 viewProj = makeViewProj(eye, center, 1.f, o.flipY, radius, sceneReach);
    std::printf("far plane reach %.0f units (sky dome included)\n", sceneReach);

    SceneGpu sg;
    try {
        buildSceneGpu(gpu, scene, worlds, modelMatrices, !o.noTextures, sg);
    } catch (const std::exception& e) {
        std::fprintf(stderr, "scene upload failed: %s\n", e.what());
        return 1;
    }
    std::printf("draws: %zu (%d textured, %d untextured), %zu GPU textures\n", sg.draws.size(),
                sg.textured, sg.untextured, sg.textures.size());

    g_noFog = o.noFog;
    g_noCull = o.noCull;
    uint32_t flags = 0;
    if (o.unlit) flags |= xm::kDrawUnlit;
    if (o.alphaTest) flags |= xm::kDrawAlphaTest;

    Frame cw = renderOnce(gpu, scene, sg, viewProj, o.size, o.winding, true, o.out, flags);
    std::printf("winding=%s : covered %d px (%.2f%%)  luminance %.3f..%.3f\n", o.winding.c_str(),
                cw.covered, 100.0 * cw.covered / (double)(o.size * o.size), cw.minLum, cw.maxLum);

    const std::string other = (o.winding == "cw") ? "ccw" : "cw";
    Frame alt = renderOnce(gpu, scene, sg, viewProj, o.size, other, false, "", flags);
    std::printf("winding=%s : covered %d px (%.2f%%)\n", other.c_str(), alt.covered,
                100.0 * alt.covered / (double)(o.size * o.size));
    std::printf("front faces are %s\n", (cw.covered >= alt.covered ? o.winding : other).c_str());

    // ---- variable frame delta: advance by whatever the display gives us and confirm the
    // animation tracks wall-clock time rather than a fixed number of steps. The original
    // caps at the monitor refresh rate, which is what a Fifo swapchain does; the CPU-side
    // proof that the pose is delta-independent is `xmodel_tool dtcheck`.
    if (o.frames > 1) {
        // Advancing the clock only: the point is that the delta is arbitrary, not that
        // this loop is fast. Actual frame pacing comes from the swapchain, where the
        // present mode (Fifo) is what caps the rate at the display's refresh.
        auto t0 = std::chrono::steady_clock::now();
        for (int f = 0; f < o.frames; ++f)
            for (xm::Controller& c : controllers)
                if (c.model()) c.advanceTime(o.dt);
        auto t1 = std::chrono::steady_clock::now();
        const double us = std::chrono::duration<double, std::micro>(t1 - t0).count();
        const double animated = (double)o.frames * (double)o.dt;
        std::printf("%d steps x %.4f s delta = %.3f s of animation, clock advanced in %.1f us "
                    "(no GPU work; frame pacing is the swapchain's job)\n",
                    o.frames, o.dt, animated, us);
        if (o.anim >= 0) {
            for (size_t i = 0; i < controllers.size(); ++i)
                if (controllers[i].model()) controllers[i].evalWorld(worlds[i]);
            SceneGpu sg2;
            buildSceneGpu(gpu, scene, worlds, modelMatrices, !o.noTextures, sg2);
            Frame after = renderOnce(gpu, scene, sg2, viewProj, o.size, o.winding, false, "", flags);
            std::printf("after %.3f s of simulated time: covered %d px\n", animated, after.covered);
            releaseSceneGpu(sg2);
        }
    }

    releaseSceneGpu(sg);
    wgpuQueueRelease(gpu.queue);
    wgpuDeviceRelease(gpu.device);
    wgpuAdapterRelease(gpu.adapter);
    wgpuInstanceRelease(gpu.instance);
    return cw.covered > 0 ? 0 : 1;
}
