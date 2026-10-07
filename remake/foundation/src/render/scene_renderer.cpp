#include "render/scene_renderer.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <optional>

#include <glm/gtc/matrix_transform.hpp>

#include "assets/asset_source.h"
#include "platform/platform.h"
#include "shaders/model_wgsl.h"

namespace render {
namespace {

WGPUStringView sv(const char* s) { return WGPUStringView{s, WGPU_STRLEN}; }
// The D experiment's key light (issue #25), resolved to the one uniform slot the shader
// reads: a world-space direction the character-only term lights from (xyz) and the
// strength the appearance carries (w). NprKey::Camera leans the key in from behind the
// camera and above, which is what "camera-relative" buys in a fighting game — the face
// stays lit while the stage's own key walks around the arena. NprKey::Fixed rotates the
// appearance's direction by the character's own yaw, so the key follows the fighter and
// neither the camera nor the stage.
glm::vec3 nprKeyDirection(const glm::mat4& model, const glm::vec3& eye, bool haveEye,
                          const Appearance& a) {
    glm::vec3 dir = a.keyDir;
    if (a.key == NprKey::Camera) {
        const glm::vec3 p(model[3]);
        glm::vec3 back(0.f, 0.f, -1.f);
        if (haveEye) {
            const glm::vec3 d(p.x - eye.x, p.y - eye.y, p.z - eye.z);
            const glm::vec2 flat(d.x, d.z);
            if (glm::dot(flat, flat) > 1e-6f) back = glm::normalize(glm::vec3(flat.x, 0.f, flat.y));
        }
        dir = glm::normalize(back + glm::vec3(0.f, 0.6f, 0.f));
        return dir;   // already world space
    }
    // NprKey::Fixed: the direction is authored in the character's frame, so rotate it by
    // the yaw the model matrix's basis carries. A degenerate basis keeps the raw value.
    const glm::vec3 x(model[0]), z(model[2]);
    const glm::vec2 fx(x.x, x.z), fz(z.x, z.z);
    if (glm::dot(fx, fx) > 1e-8f && glm::dot(fz, fz) > 1e-8f) {
        const glm::vec3 ex = glm::normalize(glm::vec3(fx.x, 0.f, fx.y));
        const glm::vec3 ez = glm::normalize(glm::vec3(fz.x, 0.f, fz.y));
        const glm::vec3 ey = glm::cross(ez, ex);
        dir = glm::normalize(ex * a.keyDir.x + ey * a.keyDir.y + ez * a.keyDir.z);
    }
    return glm::normalize(dir);
}

// The shipped toon ramp (issue #21). FUN_00650410:19 asks for "data/directx/toon.bmp"
// (the exe's own lowercase spelling) and the archives ship the .cnv conversion, which is
// what the extracted tree carries too — so both spellings are probed through
// AssetSource::resolve(), the case-folding lookup that keeps a case-insensitive bundle
// source from loading one file twice.
constexpr const char* kToonRampCandidates[] = {"data/directX/toon.cnv", "data/directx/toon.cnv"};

// Decodes the ramp through the foundation's one CNV decoder. Returns false with a reason
// rather than throwing: a build without the game data must still run.
bool loadToonRamp(xm::CnvImage& out, std::string& why) {
    std::vector<std::string> candidates;
    for (const char* name : kToonRampCandidates) candidates.emplace_back(name);
    const std::string path = fnd::assets::assetSource().resolve(candidates);
    if (path.empty()) {
        why = "no " + candidates[0] + " in any open bundle or on the filesystem";
        return false;
    }
    std::vector<uint8_t> bytes;
    if (!fnd::assets::assetSource().read(path, bytes)) {
        why = "cannot read " + path;
        return false;
    }
    try {
        out = xm::decodeCnvImage(bytes.data(), bytes.size());
    } catch (const std::exception& e) {
        why = path + ": " + e.what();
        return false;
    }
    if (out.empty()) {
        why = path + ": decoded to no pixels";
        return false;
    }
    return true;
}

// Baked shadow decals are identified by name, exactly as the DX9 fix does: the
// "shadow*" family plus the 影 (kage) names the stages use for 校舎影02 / 手すり影 /
// 影坂01. This stays PROVISIONAL (R1): the real signal would be a per-material
// effect/technique binding, but a token-level survey of all 728 shipped .X files
// found the EffectInstance template defined 491 times and instantiated zero times,
// so D3DX itself would hand the reference loader an empty effect list for every
// shipped asset. Until an asset with a real binding is observed, the name is the
// same signal the DX9 renderer uses — see docs/RENDER-MATERIALS.md.
bool isShadowDecalName(const std::string& raw) {
    std::string s = xm::sjisToUtf8(raw);
    std::string lower;
    lower.reserve(s.size());
    for (char c : s) lower += (char)std::tolower((unsigned char)c);
    if (lower.find("shadow") != std::string::npos) return true;
    return s.find("\xe5\xbd\xb1") != std::string::npos;   // 影 in UTF-8
}

// Effect cards (data/effect, data/aura) are indistinguishable from opaque geometry
// in their parsed material terms — white diffuse, power 0, near-zero specular,
// zero emissive, opaque-alpha textures — so no material signal can route them.
// The scene role is the only honest signal: the asset layer names each model's
// category, and a future `--effect` loader assigns these roles the way loadWeapon
// assigns "weapon" today. Bare `--model` loads keep role "model" and stay opaque.
Pass classifyPass(const std::string& role, const std::string& texture) {
    if (role == "effect" || role == "aura") return Pass::Effect;
    if (!texture.empty() && isShadowDecalName(texture)) return Pass::Decal;
    return Pass::Opaque;
}

// What a billboarded draw needs from its mesh: the pivot and the authored facing yaw.
struct Billboard {
    glm::vec3 center{0.f};
    float     yaw0 = 0.f;
};

// Cylindrical-billboard verdict for one effect draw, from the submesh geometry
// alone (no texture names — those are deliberately excluded as routing signals).
// Upright cards (single quads, crossed-plane sets, beam fans, Y-symmetric rings)
// yaw around world Y to face the camera; ground-plane cards (normals ±Y, e.g.
// aura/03's 400x400 floor quad) keep their authored orientation, which a Y spin
// could only disturb. All surveyed effect/aura meshes are unskinned, so the pivot
// is the submesh bounds center in mesh space; a skinned mesh can never reach here
// (the caller guards on it) because its vertices leave mesh space per-bone.
//
// Returns the pivot and facing only when the card qualifies. It used to write the
// pivot into the caller's DrawItem before deciding, so a rejected card left a center
// behind for a caller that had to know not to read it — std::optional is the same
// information without that coupling.
std::optional<Billboard> classifyBillboard(const xm::Mesh& mesh, const xm::Submesh& sub) {
    if (mesh.skinned || mesh.vertices.empty() || mesh.indices.empty()) return std::nullopt;
    glm::vec3 lo(1e30f), hi(-1e30f);
    double    nySum = 0.0;
    int       posX = 0, negX = 0, posZ = 0, negZ = 0;
    uint32_t  n = 0;
    const uint32_t end = std::min(sub.firstIndex + sub.indexCount, (uint32_t)mesh.indices.size());
    for (uint32_t i = sub.firstIndex; i < end; ++i) {
        const uint32_t vi = mesh.indices[i];
        if (vi >= mesh.vertices.size()) continue;
        const xm::Vertex& v = mesh.vertices[vi];
        lo = glm::min(lo, v.pos);
        hi = glm::max(hi, v.pos);
        nySum += std::fabs((double)v.normal.y);
        // Dominant-axis vote: a single quad votes one axis; a crossed-plane set
        // ties and falls through to +Z, which faces one of its cards at the camera.
        if (std::fabs(v.normal.x) >= std::fabs(v.normal.y) &&
            std::fabs(v.normal.x) >= std::fabs(v.normal.z)) {
            if (v.normal.x >= 0.f) ++posX; else ++negX;
        } else if (std::fabs(v.normal.z) >= std::fabs(v.normal.y)) {
            if (v.normal.z >= 0.f) ++posZ; else ++negZ;
        }
        ++n;
    }
    if (n == 0) return std::nullopt;
    Billboard bb;
    bb.center = (lo + hi) * 0.5f;
    // Ground-dominant cards stay put: their plane already contains every camera
    // yaw, so facing is meaningless and spinning only churns directional art.
    if (nySum / (double)n > 0.5) return std::nullopt;
    // Authored facing: the yaw the card's dominant normal already has, so the
    // render-time yaw is relative to it (a YZ-plane card needs yaw-90°, not yaw).
    // Plain constants, not M_PI_2/M_PI: those need feature-test macros that differ
    // per target, and this file builds for Linux, MinGW and Emscripten alike.
    constexpr float kHalfPi = 1.57079632679f;
    constexpr float kPi = 3.14159265359f;
    if (posX >= negX && posX >= posZ && posX >= negZ)
        bb.yaw0 = kHalfPi;
    else if (negX >= posZ && negX >= negZ)
        bb.yaw0 = -kHalfPi;
    else if (negZ >= posZ)
        bb.yaw0 = kPi;
    else
        bb.yaw0 = 0.f;
    return bb;
}

// COPY_BYTES_PER_ROW_ALIGNMENT is 256: a tightly packed RGBA row is only legal for
// widths that happen to be multiples of 64. Pad the pitch and unpad on readback.
uint32_t alignedRowPitch(uint32_t width) { return (width * 4u + 255u) / 256u * 256u; }

void setStencilOps(WGPUStencilFaceState& s) {
    // Zero-init would leave both ops Undefined; we never use stencil, but the state
    // has to be legal anyway. Field-by-field: WGPU structs are not aggregate-assignable
    // in C++.
    s.compare = WGPUCompareFunction_Always;
    s.failOp = WGPUStencilOperation_Keep;
    s.depthFailOp = WGPUStencilOperation_Keep;
    s.passOp = WGPUStencilOperation_Keep;
}

}  // namespace

SceneRenderer::~SceneRenderer() { shutdown(); }

SceneRenderer::Texture::~Texture() { release(); }

SceneRenderer::Texture::Texture(Texture&& o) noexcept : tex(o.tex), view(o.view) {
    o.tex = nullptr;
    o.view = nullptr;
}

SceneRenderer::Texture& SceneRenderer::Texture::operator=(Texture&& o) noexcept {
    if (this != &o) {
        release();
        tex = o.tex;
        view = o.view;
        o.tex = nullptr;
        o.view = nullptr;
    }
    return *this;
}

// The view first, then the texture it views: the order every release site in this file
// used before they were unified here.
void SceneRenderer::Texture::release() {
    if (view) wgpuTextureViewRelease(view);
    if (tex) wgpuTextureRelease(tex);
    view = nullptr;
    tex = nullptr;
}

void SceneRenderer::releaseSceneResources() {
    for (WGPUBuffer b : buffers_)
        if (b) wgpuBufferRelease(b);
    buffers_.clear();
    // The index is keyed by image pointer, so it describes exactly the list it
    // indexes: clearing one without the other would hand the next scene an index
    // into a released vector.
    textures_.clear();   // each Texture releases its own view and texture
    texIndex_.clear();
    for (WGPUBindGroup g : textureGroups_)
        if (g) wgpuBindGroupRelease(g);
    textureGroups_.clear();
    if (drawGroup_) wgpuBindGroupRelease(drawGroup_);
    drawGroup_ = nullptr;
    if (paletteBuffer_) wgpuBufferRelease(paletteBuffer_);
    if (drawBuffer_) wgpuBufferRelease(drawBuffer_);
    paletteBuffer_ = drawBuffer_ = nullptr;
}

// The sampler state every binding in this renderer shares: LINEAR mag, min and mip,
// the 0..32 LOD range and anisotropy 1. The header's mip note carries the call-site
// survey behind that — sampler 0 receives only the three filter writes, so
// MAXANISOTROPY (10), MIPMAPLODBIAS (8) and MAXMIPLEVEL (9) stay at D3D9's own
// defaults. Only the address mode differs between the three users, which is all this
// takes. A null return is caught by init()'s completeness check, which is why there is
// no error channel here.
WGPUSampler SceneRenderer::createSampler(WGPUAddressMode addressMode) {
    WGPUSamplerDescriptor sd = {};
    sd.addressModeU = sd.addressModeV = sd.addressModeW = addressMode;
    sd.magFilter = WGPUFilterMode_Linear;
    sd.minFilter = WGPUFilterMode_Linear;
    sd.mipmapFilter = WGPUMipmapFilterMode_Linear;
    sd.lodMinClamp = 0.f;
    sd.lodMaxClamp = 32.f;
    sd.maxAnisotropy = 1;
    return wgpuDeviceCreateSampler(device_, &sd);
}

void SceneRenderer::createSolidTexture(uint32_t rgba, WGPUTexture& tex, WGPUTextureView& view) {
    WGPUTextureDescriptor td = {};
    td.usage = WGPUTextureUsage_TextureBinding | WGPUTextureUsage_CopyDst;
    td.dimension = WGPUTextureDimension_2D;
    td.size = WGPUExtent3D{1, 1, 1};
    td.format = WGPUTextureFormat_RGBA8Unorm;
    td.mipLevelCount = 1;
    td.sampleCount = 1;
    tex = wgpuDeviceCreateTexture(device_, &td);
    if (!tex) return;
    WGPUTexelCopyTextureInfo dst = {};
    dst.texture = tex;
    dst.aspect = WGPUTextureAspect_All;
    WGPUTexelCopyBufferLayout layout = {};
    layout.bytesPerRow = 4;
    layout.rowsPerImage = 1;
    wgpuQueueWriteTexture(queue_, &dst, &rgba, 4, &layout, &td.size);
    view = wgpuTextureCreateView(tex, nullptr);
}

bool SceneRenderer::init(const gpu::Context& ctx, std::string& error) {
    if (!ctx.device || !ctx.queue || !ctx.instance) {
        error = "renderer needs a live device, queue and instance";
        return false;
    }
    // Same contract as DebugPrims::init: init() owns everything it creates, so a second
    // call on a live renderer replaces the first rather than orphaning it. On a fresh or
    // already-shut-down renderer this is a no-op.
    shutdown();
    instance_ = ctx.instance;
    device_ = ctx.device;
    queue_ = ctx.queue;

    shader_ = gpu::createShaderModule(device_, shaders::kModelWGSL);
    if (!shader_) {
        error = "model shader module creation failed";
        return false;
    }

    // group 0: camera + the toon ramp. group 1: draw + palette. group 2: texture + sampler.
    // The draw uniform is bound with a dynamic offset, so one buffer serves every draw.
    WGPUBindGroupLayoutEntry cameraEntries[3] = {};
    cameraEntries[0].binding = 0;
    cameraEntries[0].visibility = WGPUShaderStage_Vertex | WGPUShaderStage_Fragment;
    cameraEntries[0].buffer.type = WGPUBufferBindingType_Uniform;
    cameraEntries[0].buffer.minBindingSize = sizeof(xm::CameraUniform);
    // The toon ramp (issue #21) rides the camera group: one scene-wide image, like the
    // light, not a per-material texture. It is bound in every frame — the shader samples
    // it unconditionally (WGSL allows textureSample only in uniform control flow) — so
    // the group is complete whether or not the toggle is on.
    cameraEntries[1].binding = 1;
    cameraEntries[1].visibility = WGPUShaderStage_Fragment;
    cameraEntries[1].texture.sampleType = WGPUTextureSampleType_Float;
    cameraEntries[1].texture.viewDimension = WGPUTextureViewDimension_2D;
    cameraEntries[2].binding = 2;
    cameraEntries[2].visibility = WGPUShaderStage_Fragment;
    cameraEntries[2].sampler.type = WGPUSamplerBindingType_Filtering;

    WGPUBindGroupLayoutEntry drawEntries[2] = {};
    drawEntries[0].binding = 0;
    drawEntries[0].visibility = WGPUShaderStage_Vertex | WGPUShaderStage_Fragment;
    drawEntries[0].buffer.type = WGPUBufferBindingType_Uniform;
    drawEntries[0].buffer.hasDynamicOffset = true;
    drawEntries[0].buffer.minBindingSize = sizeof(xm::DrawUniform);
    drawEntries[1].binding = 1;
    drawEntries[1].visibility = WGPUShaderStage_Vertex;
    drawEntries[1].buffer.type = WGPUBufferBindingType_ReadOnlyStorage;

    WGPUBindGroupLayoutEntry textureEntries[2] = {};
    textureEntries[0].binding = 0;
    textureEntries[0].visibility = WGPUShaderStage_Fragment;
    textureEntries[0].texture.sampleType = WGPUTextureSampleType_Float;
    textureEntries[0].texture.viewDimension = WGPUTextureViewDimension_2D;
    textureEntries[1].binding = 1;
    textureEntries[1].visibility = WGPUShaderStage_Fragment;
    textureEntries[1].sampler.type = WGPUSamplerBindingType_Filtering;

    // group 3: the character shadow map (issue #21 row 1). Its own group rather than two
    // more entries in the camera group, because it is a per-VIEW image: the original runs
    // its caster pass inside the per-view loop, so view N's ground must read view N's map.
    // Binding it per view beside the camera keeps that shape without a second camera
    // group layout.
    WGPUBindGroupLayoutEntry shadowEntries[2] = {};
    shadowEntries[0].binding = 0;
    shadowEntries[0].visibility = WGPUShaderStage_Fragment;
    shadowEntries[0].texture.sampleType = WGPUTextureSampleType_Float;
    shadowEntries[0].texture.viewDimension = WGPUTextureViewDimension_2D;
    shadowEntries[1].binding = 1;
    shadowEntries[1].visibility = WGPUShaderStage_Fragment;
    shadowEntries[1].sampler.type = WGPUSamplerBindingType_Filtering;

    WGPUBindGroupLayoutDescriptor bglDesc = {};
    bglDesc.entryCount = 3;
    bglDesc.entries = cameraEntries;
    bindGroupLayouts_[0] = wgpuDeviceCreateBindGroupLayout(device_, &bglDesc);
    bglDesc.entryCount = 2;
    bglDesc.entries = drawEntries;
    bindGroupLayouts_[1] = wgpuDeviceCreateBindGroupLayout(device_, &bglDesc);
    bglDesc.entries = textureEntries;
    bindGroupLayouts_[2] = wgpuDeviceCreateBindGroupLayout(device_, &bglDesc);
    bglDesc.entries = shadowEntries;
    bindGroupLayouts_[3] = wgpuDeviceCreateBindGroupLayout(device_, &bglDesc);

    WGPUPipelineLayoutDescriptor plDesc = {};
    plDesc.bindGroupLayoutCount = 4;
    plDesc.bindGroupLayouts = bindGroupLayouts_;
    pipelineLayout_ = wgpuDeviceCreatePipelineLayout(device_, &plDesc);
    // The caster pass's layout: groups 0 and 1 only (the map is its target, not a binding).
    WGPUBindGroupLayout casterLayouts[2] = {bindGroupLayouts_[0], bindGroupLayouts_[1]};
    plDesc.bindGroupLayoutCount = 2;
    plDesc.bindGroupLayouts = casterLayouts;
    shadowPipelineLayout_ = wgpuDeviceCreatePipelineLayout(device_, &plDesc);

    // The original's sampler 0 in WebGPU terms: address modes stay at D3D9's WRAP, the
    // default the original never overrides — the header's mip note carries the call-site
    // survey that says so.
    sampler_ = createSampler(WGPUAddressMode_Repeat);

    // The toon ramp's own sampler (issue #21): clamp, because u = N.L = 1 has to read the
    // bright end of the bitmap and WRAP would blend it with the dark end there. Filtering
    // stays LINEAR, the D3D9 default the original's sampler 0 carries, which suits the
    // shipped 64-wide gradient; the ramp has one level, so the mip filter never runs.
    toonRampSampler_ = createSampler(WGPUAddressMode_ClampToEdge);

    // The shadow map's sampler (issue #21 row 1). The original's Tex1 is
    // D3DTADDRESS_BORDER with a black border colour (FUN_00651110 case 3/4), which WebGPU
    // has no address mode for; clamp + linear is the closest state, and the shader's own
    // [0,1] range test supplies the border behaviour. Linear, because the map is a
    // 1024x1024 depth image the original filters with sampler state 1's LINEAR default —
    // and because a fighter's shadow is a few hundred texels wide, so the filter's
    // softness is what the original's own shadows show. It keeps its own handle rather
    // than sharing the ramp's identical state: each member releases what it owns, and a
    // second alias pair in shutdown() is a second load-bearing release order.
    shadowSampler_ = createSampler(WGPUAddressMode_ClampToEdge);

    // The untextured fallback: binds where a material has no resolvable texture, so
    // the shader's unconditional sample stays valid.
    createSolidTexture(0xffffffffu, whiteTex_, whiteView_);

    // The toon ramp (issue #21), decoded through the foundation's one CNV path and
    // uploaded once: it is a 64x64 RGBA8 bitmap with no mip chain, because the original
    // creates it from that single file (FUN_00650410:19) and never generates levels. A
    // missing or undecodable ramp is a warning, not a failure: the toggle stays inert
    // (toonRampReady_ false) and the frame is the pre-#21 one, never a constant ramp
    // standing in for the shipped bitmap.
    xm::CnvImage ramp;
    std::string rampWhy;
    if (loadToonRamp(ramp, rampWhy)) {
        WGPUTextureDescriptor rtd = {};
        rtd.usage = WGPUTextureUsage_TextureBinding | WGPUTextureUsage_CopyDst;
        rtd.dimension = WGPUTextureDimension_2D;
        rtd.size = WGPUExtent3D{ramp.width, ramp.height, 1};
        rtd.format = WGPUTextureFormat_RGBA8Unorm;
        rtd.mipLevelCount = 1;
        rtd.sampleCount = 1;
        toonRampTex_ = wgpuDeviceCreateTexture(device_, &rtd);
        if (toonRampTex_) {
            WGPUTexelCopyTextureInfo dst = {};
            dst.texture = toonRampTex_;
            dst.aspect = WGPUTextureAspect_All;
            WGPUTexelCopyBufferLayout layout = {};
            layout.bytesPerRow = ramp.width * 4;
            layout.rowsPerImage = ramp.height;
            wgpuQueueWriteTexture(queue_, &dst, ramp.rgba.data(), ramp.rgba.size(), &layout,
                                  &rtd.size);
            toonRampView_ = wgpuTextureCreateView(toonRampTex_, nullptr);
        }
        if (!toonRampView_) rampWhy = "ramp texture creation failed";
        toonRampReady_ = toonRampView_ != nullptr;
    }
    if (!toonRampReady_) {
        std::fprintf(stderr, "[render] toon ramp unavailable (%s): toon rendering stays off\n",
                     rampWhy.c_str());
        toonRampView_ = whiteView_;   // the binding still has to be valid
    }

    cameraBuffer_ = gpu::createBuffer(device_, sizeof(xm::CameraUniform),
                                      WGPUBufferUsage_Uniform | WGPUBufferUsage_CopyDst, nullptr);

    // The placeholder shadow map (issue #21 row 1): 1x1 opaque black, i.e. what the
    // original's cleared 1024x1024 map reads as (alpha 1.0 = "nothing cast here"). It
    // stands in for group 3 on every frame the shadow pass does not run, so the group is
    // always complete and a run with shadows off allocates no 1024x1024 target at all.
    createSolidTexture(0xff000000u, shadowPlaceholderTex_, shadowPlaceholderView_);

    if (!bindGroupLayouts_[0] || !bindGroupLayouts_[1] || !bindGroupLayouts_[2] ||
        !bindGroupLayouts_[3] || !pipelineLayout_ || !shadowPipelineLayout_ || !sampler_ ||
        !whiteView_ || !cameraBuffer_ || !toonRampSampler_ || !toonRampView_ ||
        !shadowSampler_ || !shadowPlaceholderView_) {
        error = "renderer setup failed (bind group layout, sampler or buffer)";
        return false;
    }

    WGPUBindGroupEntry camEntries[3] = {};
    camEntries[0].binding = 0;
    camEntries[0].buffer = cameraBuffer_;
    camEntries[0].size = sizeof(xm::CameraUniform);
    camEntries[1].binding = 1;
    camEntries[1].textureView = toonRampView_;
    camEntries[2].binding = 2;
    camEntries[2].sampler = toonRampSampler_;
    WGPUBindGroupDescriptor bgDesc = {};
    bgDesc.layout = bindGroupLayouts_[0];
    bgDesc.entryCount = 3;
    bgDesc.entries = camEntries;
    cameraGroup_ = wgpuDeviceCreateBindGroup(device_, &bgDesc);
    if (!cameraGroup_) {
        error = "camera bind group creation failed";
        return false;
    }

    WGPUBindGroupEntry placeholderEntries[2] = {};
    placeholderEntries[0].binding = 0;
    placeholderEntries[0].textureView = shadowPlaceholderView_;
    placeholderEntries[1].binding = 1;
    placeholderEntries[1].sampler = shadowSampler_;
    bgDesc.layout = bindGroupLayouts_[3];
    bgDesc.entryCount = 2;
    bgDesc.entries = placeholderEntries;
    shadowPlaceholderGroup_ = wgpuDeviceCreateBindGroup(device_, &bgDesc);
    if (!shadowPlaceholderGroup_) {
        error = "shadow placeholder bind group creation failed";
        return false;
    }
    return true;
}

void SceneRenderer::shutdown() {
    for (Pipelines& p : pipelines_)
        for (auto& variants : p.slots)
            for (WGPURenderPipeline pipe : variants)
                if (pipe) wgpuRenderPipelineRelease(pipe);
    pipelines_.clear();

    releaseShadowTargets();
    if (shadowPlaceholderGroup_) wgpuBindGroupRelease(shadowPlaceholderGroup_);
    if (shadowPlaceholderView_) wgpuTextureViewRelease(shadowPlaceholderView_);
    if (shadowPlaceholderTex_) wgpuTextureRelease(shadowPlaceholderTex_);
    shadowPlaceholderGroup_ = nullptr;
    shadowPlaceholderView_ = nullptr;
    shadowPlaceholderTex_ = nullptr;
    if (shadowSampler_) wgpuSamplerRelease(shadowSampler_);
    shadowSampler_ = nullptr;
    if (shadowPipeline_) wgpuRenderPipelineRelease(shadowPipeline_);
    if (shadowPipelineLayout_) wgpuPipelineLayoutRelease(shadowPipelineLayout_);
    shadowPipeline_ = nullptr;
    shadowPipelineLayout_ = nullptr;

    releaseSceneResources();

    // The camera group is NOT part of the scene: it binds the ramp and the scene-wide
    // light, so setScene leaves it standing for the next scene. The same goes for its
    // buffer and the per-view camera slots.
    if (cameraGroup_) wgpuBindGroupRelease(cameraGroup_);
    cameraGroup_ = nullptr;
    for (size_t i = 0; i < kMaxViewCameras; ++i) {
        if (viewCameraGroups_[i]) wgpuBindGroupRelease(viewCameraGroups_[i]);
        viewCameraGroups_[i] = nullptr;
    }
    if (cameraBuffer_) wgpuBufferRelease(cameraBuffer_);
    cameraBuffer_ = nullptr;
    for (WGPUBuffer& b : viewCameraBuffers_) {
        if (b) wgpuBufferRelease(b);
        b = nullptr;
    }

    if (depthView_) wgpuTextureViewRelease(depthView_);
    if (depthTex_) wgpuTextureRelease(depthTex_);
    depthView_ = nullptr;
    depthTex_ = nullptr;
    depthWidth_ = depthHeight_ = 0;

    // The ramp first: toonRampView_ may be an alias of whiteView_ (no game data), so the
    // alias is only recognisable while both pointers are still live.
    if (toonRampView_ && toonRampView_ != whiteView_) wgpuTextureViewRelease(toonRampView_);
    if (toonRampTex_) wgpuTextureRelease(toonRampTex_);
    toonRampView_ = nullptr;
    toonRampTex_ = nullptr;
    toonRampReady_ = false;
    if (toonRampSampler_) wgpuSamplerRelease(toonRampSampler_);
    toonRampSampler_ = nullptr;
    if (whiteView_) wgpuTextureViewRelease(whiteView_);
    if (whiteTex_) wgpuTextureRelease(whiteTex_);
    whiteView_ = nullptr;
    whiteTex_ = nullptr;
    if (sampler_) wgpuSamplerRelease(sampler_);
    if (shader_) wgpuShaderModuleRelease(shader_);
    sampler_ = nullptr;
    shader_ = nullptr;

    if (pipelineLayout_) wgpuPipelineLayoutRelease(pipelineLayout_);
    for (WGPUBindGroupLayout& l : bindGroupLayouts_) {
        if (l) wgpuBindGroupLayoutRelease(l);
        l = nullptr;
    }
    pipelineLayout_ = nullptr;

    draws_.clear();
    meshes_.clear();
    palette_.clear();
    stats_ = Stats{};
    device_ = nullptr;
    queue_ = nullptr;
    instance_ = nullptr;
}

// Finds or uploads the texture a material names. `sm.textures` is the model's own
// cache, so the image is shared between every material that names it and the upload
// happens once per scene: texIndex_ memoises image -> index in textures_.
//
// Returns false when the upload itself failed, with `error` saying why; `index` is
// then meaningless and the caller must abandon the scene. True with `index == -1` is
// the ordinary "this draw has no texture" outcome — the directory ships nothing under
// that name (a weapon naming a texture that lives in the character directory is the
// observed case), and the caller counts it as untextured. The two cannot be folded
// into one -1: -1 is a normal result here, and a caller that read a failure as
// "untextured" would silently drop geometry's texture instead of failing loudly.
//
// `mipmapped` is the caller's policy, not something read here: only stage textures get
// a chain, and scene_renderer.h's mip note carries the evidence for why.
bool SceneRenderer::uploadTexture(const xm::SceneModel& sm, const std::string& name,
                                 bool mipmapped, int& index, std::string& error) {
    index = -1;
    const xm::CnvImage* img = sm.textures.get(name);
    if (!img || img->empty()) return true;

    auto it = texIndex_.find(img);
    if (it != texIndex_.end()) {
        index = it->second;
        return true;
    }

    // Only stage textures get a chain: the reference's other textures are created with
    // MipLevels = 1 because their directories ship no levels. The header's mip note
    // carries that evidence, the original's MIPFILTER state, and the box filter's
    // byte-space rationale; levels 1-2 prefer the shipped _N siblings (B3), the box
    // staying as the fallback past them and for missing art.
    std::vector<std::vector<uint8_t>> levels;
    if (mipmapped) {
        buildMipChain(img->rgba.data(), img->width, img->height, levels);
        // B3: levels 1-2 come from the shipped `base_1`/`base_2` files when present
        // (FUN_00656c80 fills one D3DX level per `%s_%d.bmp`), the box level staying
        // as the fallback otherwise. The lookup rides the same bundle-first cache as
        // the base texture. The chain truncates to the shipped depth, which is
        // D3DXCreateTexture's MipLevels=1+#files: sampling past the smallest shipped
        // level clamps there on the original too. (The one observed misfit, a _2 sized
        // like a _1, truncates to a clean 2-level chain here; the original would leave
        // that level unfilled.)
        uint32_t shipped = 0;
        for (uint32_t l = 1; l <= 2 && l < levels.size(); ++l) {
            const xm::CnvImage* sib = sm.textures.get(mipSiblingName(name, l));
            if (sib && !sib->empty() &&
                mipShippedDimsOk(img->width, img->height, sib->width, sib->height, l)) {
                levels[l] = sib->rgba;
                shipped = l;
            }
        }
        if (shipped > 0) levels.resize(shipped + 1);
    }
    const uint32_t levelCount = mipmapped ? (uint32_t)levels.size() : 1u;

    Texture tex;
    WGPUTextureDescriptor td = {};
    td.usage = WGPUTextureUsage_TextureBinding | WGPUTextureUsage_CopyDst;
    td.dimension = WGPUTextureDimension_2D;
    td.size = WGPUExtent3D{img->width, img->height, 1};
    td.format = WGPUTextureFormat_RGBA8Unorm;
    td.mipLevelCount = levelCount;
    td.sampleCount = 1;
    tex.tex = wgpuDeviceCreateTexture(device_, &td);
    if (tex.tex) {
        WGPUTexelCopyTextureInfo dst = {};
        dst.texture = tex.tex;
        dst.aspect = WGPUTextureAspect_All;
        for (uint32_t level = 0; level < levelCount; ++level) {
            const uint32_t lw = std::max(1u, img->width >> level);
            const uint32_t lh = std::max(1u, img->height >> level);
            WGPUTexelCopyBufferLayout layout = {};
            layout.bytesPerRow = lw * 4;
            layout.rowsPerImage = lh;
            dst.mipLevel = level;
            const WGPUExtent3D extent{lw, lh, 1};
            // A single-level texture uploads its base image exactly as it did before
            // mips existed. writeTexture is a packed copy, so unlike copyBufferToTexture
            // it needs no 256-byte row pitch and odd-sized CNV levels upload as-is.
            const std::vector<uint8_t>& pixels = mipmapped ? levels[level] : img->rgba;
            wgpuQueueWriteTexture(queue_, &dst, pixels.data(), pixels.size(), &layout, &extent);
        }
        tex.view = wgpuTextureCreateView(tex.tex, nullptr);
    }
    if (!tex.tex || !tex.view) {
        // The local Texture owns both halves, so the one that was created is released
        // on the way out of this return rather than outliving the process. textures_
        // only takes ownership at the push_back below.
        error = "texture upload failed (device out of memory?)";
        return false;
    }
    index = (int)textures_.size();
    texIndex_.emplace(img, index);
    textures_.push_back(std::move(tex));
    return true;
}

bool SceneRenderer::setScene(const xm::Scene& scene,
                             const std::vector<std::vector<glm::mat4>>& worlds,
                             const std::vector<glm::mat4>& modelMatrices, const Options& options,
                             std::string& error) {
    if (!device_) {
        error = "renderer not initialized";
        return false;
    }
    // Drop the previous scene's GPU objects: setScene may legitimately be called more
    // than once (a different asset in the same window), and nothing here is shared.
    // shutdown() frees exactly the same set, through the same call.
    releaseSceneResources();

    draws_.clear();
    meshes_.clear();
    palette_.clear();
    stats_ = Stats{};
    // The instance sources are per-scene as well. drawTemplates_ holds this scene's draws plus
    // its instance-only templates, and baseDrawList_ its no-instance fallback, so leaving them
    // behind makes the next setEffectInstances() — the first live effect card — submit the
    // PREVIOUS scene's records, whose vertex/index buffers were released a few lines above.
    // wgpu-native panics on the dead handle; before that the draw reads the wrong texture. A
    // rematch is exactly this path: a second match in the same process.
    drawTemplates_.clear();
    baseDrawList_.clear();
    effectInstances_.clear();

    std::vector<glm::mat4> meshPalette;
    const std::vector<glm::mat4> noWorld;

    for (size_t mi = 0; mi < scene.models.size(); ++mi) {
        const xm::SceneModel& sm = scene.models[mi];
        if (!sm.drawable) continue;   // collision volumes are for queries/framing only
        const glm::mat4 model = mi < modelMatrices.size() ? modelMatrices[mi] : glm::mat4(1.f);
        const std::vector<glm::mat4>& world = mi < worlds.size() ? worlds[mi] : noWorld;

        for (const xm::Mesh& mesh : sm.model.meshes) {
            if (mesh.vertices.empty() || mesh.indices.empty()) continue;

            sm.model.buildPalette(mesh, world, meshPalette);
            const uint32_t paletteOffset = (uint32_t)palette_.size();
            palette_.insert(palette_.end(), meshPalette.begin(), meshPalette.end());
            meshes_.push_back(MeshRecord{&sm.model, &mesh, mi, paletteOffset});

            // Issue #25 experiment E/F: the secondary lighting normal and the generated
            // shadow mask are built ONCE here, from the bind-pose geometry, and uploaded
            // with the mesh. They are not part of the .X and are not animation-dependent:
            // a skinned vertex's normal rotates with its bones through the palette, so a
            // coarse normal authored in bind pose stays coarse through the whole clip.
            // Only the roles the experiments shade get one; every other mesh keeps the
            // (0,0,0,0) that tells the shader to use its geometric normal, which is what
            // leaves the stage's shading untouched.
            std::vector<xm::NprVertex> nprVerts;
            const bool nprRole = (sm.role == "character" || sm.role == "weapon");
            size_t nprFilled = 0;
            if (nprRole) nprFilled = buildNprNormals(mesh, nprVerts);
            if (nprFilled > 0) {
                stats_.nprMeshes += 1;
                stats_.nprVertices += nprFilled;
            }
            // One zero vertex stands in for "this mesh has no secondary normal", so every
            // draw can bind slot 1 from the same code path. The shader treats a zero
            // stream as absent (dot(npr,npr) > 0.25), which is what leaves the stage and
            // every non-NPR mesh on its geometric normal.
            const xm::NprVertex kNoNpr{};
            WGPUBuffer nprbuf = gpu::createBuffer(
                device_,
                nprVerts.empty() ? sizeof(xm::NprVertex)
                                 : nprVerts.size() * sizeof(xm::NprVertex),
                WGPUBufferUsage_Vertex | WGPUBufferUsage_CopyDst,
                nprVerts.empty() ? &kNoNpr : nprVerts.data());

            WGPUBuffer vbuf = gpu::createBuffer(device_,
                                                mesh.vertices.size() * sizeof(xm::Vertex),
                                                WGPUBufferUsage_Vertex | WGPUBufferUsage_CopyDst,
                                                mesh.vertices.data());
            WGPUBuffer ibuf = gpu::createBuffer(device_,
                                                mesh.indices.size() * sizeof(uint32_t),
                                                WGPUBufferUsage_Index | WGPUBufferUsage_CopyDst,
                                                mesh.indices.data());
            buffers_.push_back(vbuf);
            buffers_.push_back(ibuf);
            buffers_.push_back(nprbuf);
            if (!vbuf || !ibuf || !nprbuf) {
                error = "vertex/index/NPR buffer creation failed for " + sm.source;
                return false;
            }

            for (const xm::Submesh& sub : mesh.submeshes) {
                DrawItem d;
                d.vbuf = vbuf;
                d.ibuf = ibuf;
                d.nprbuf = nprbuf;
                d.firstIndex = sub.firstIndex;
                d.indexCount = sub.indexCount;
                d.paletteOffset = paletteOffset;
                d.modelIndex = mi;
                d.model = model;

                const xm::Material& mat =
                    (sub.material >= 0 && (size_t)sub.material < mesh.materials.size())
                        ? mesh.materials[(size_t)sub.material]
                        : (mesh.materials.empty() ? xm::Material{} : mesh.materials[0]);
                const Pass pass = classifyPass(sm.role, mat.texture);
                if (options.textures && !mat.texture.empty()) {
                    // The decal white-out is a pass decision, so it stays here rather
                    // than moving into uploadTexture(): white keys out so the card
                    // disappears where it is neutral and only the blob multiplies, and
                    // it has to happen before the image is uploaded. const_cast: the
                    // cache hands out a shared image, keyOutWhite is idempotent (so a
                    // later decal re-keying it is harmless), and the upload below is
                    // the only reader.
                    if (pass == Pass::Decal) {
                        xm::CnvImage* img =
                            const_cast<xm::CnvImage*>(sm.textures.get(mat.texture));
                        if (img && !img->empty()) xm::keyOutWhite(*img);
                    }
                    if (!uploadTexture(sm, mat.texture, sm.role == "stage", d.texture, error))
                        return false;
                    if (d.texture >= 0) ++stats_.textured; else ++stats_.untextured;
                } else {
                    ++stats_.untextured;
                }

                d.pass = pass;
                // The original's toon technique covers the per-character draw
                // (FUN_006396f0:126-140) and the object material path FUN_005f60b0:121-126,
                // which draws a fighter's body and weapon together — so the port's
                // character and weapon models are the draws the ramp may replace, and the
                // stage keeps its fixed-function lighting. PORT RULE (issue #21): the role
                // is the port's stand-in for "drawn by the toon technique"; the original
                // selects it with a technique switch, not a material term.
                d.toon = (sm.role == "character" || sm.role == "weapon");
                // The character shadow's receiver (issue #21 row 1). The original's
                // technique mode 3 (FUN_00401b80 -> FUN_00652af0) is selected for the
                // stage object and is the only technique that reads the map's alpha, so
                // the port's stage role is its stand-in — the same shape of PORT RULE as
                // the toon role above. The appearance switch decides at uniform-fill time
                // whether the bit is set.
                d.receiver = (sm.role == "stage");
                // Diffuse rides baseColor the way D3DX feeds faceColor to the pipeline;
                // the renderer used to shade everything white. Observed tinted materials
                // all live in non-drawn collision meshes, so no capture changes from
                // this — it is the real per-material signal, wired rather than dropped.
                d.baseColor = mat.diffuse;
                // The toon effect's "MaterialColor" is the material's Emissive (issue #21):
                // the original hands the effect `material + 0x30` of a D3DXMATERIAL, and
                // the effect's own shading is `albedo * saturate(ramp + MaterialColor -
                // 0.1)` — with the diffuse there instead, every character saturates to
                // white. Emissive is parsed but otherwise unused (R4), so nothing else
                // reads it.
                d.emissive = glm::vec4(mat.emissive, 1.f);
                // Issue #25: which draws may light the secondary normal. The outline hull
                // inherits the verdict below (harmless — the hull's entry point ignores it).
                d.nprNormals = nprFilled > 0;
                // Effect cards yaw to face the camera around world Y (cylindrical, not
                // spherical: the world's up axis is load-bearing — ground cards lie in
                // XZ, shockwaves read as verticals — and the arena camera stays near
                // level). The verdict is geometry-only; dormant until setEye().
                if (pass == Pass::Effect) {
                    if (const std::optional<Billboard> bb = classifyBillboard(mesh, sub)) {
                        d.bbCenter = bb->center;
                        d.bbYaw0 = bb->yaw0;
                        d.billboard = true;
                    }
                }
                // Decals and effect cards are lighting, not paint: white has to stay
                // exactly white (decals) and black exactly black (effects) or the blend
                // darkens or washes the ground it is supposed to leave alone.
                if (pass != Pass::Opaque) {
                    d.flags |= xm::kDrawUnlit;
                    if (pass == Pass::Decal) ++stats_.decals; else ++stats_.effects;
                }
                // The original's 3D passes alpha-test: without it the foliage and
                // ground cards draw as opaque quads.
                if (d.texture >= 0) d.flags |= xm::kDrawTextured | xm::kDrawAlphaTest;
                // An instance-only card contributes a template, never a base draw: its
                // copies come from setEffectInstances (issue #17). It is not counted in
                // the scene stats either — those describe what a frame draws.
                if (sm.instancesOnly) {
                    drawTemplates_.push_back(d);
                    continue;
                }
                // The toon state's second draw (issue #21): the same submesh once more as
                // the outline hull. The original's technique is two passes over the same
                // geometry, its pass 0 being the normal-offset hull with no pixel shader,
                // so the port queues a second draw per eligible submesh and lets the
                // frame-time switch decide whether it is submitted. Nothing is uploaded
                // twice: it shares the vertex/index buffers and the palette slice.
                const bool outline = d.toon && pass == Pass::Opaque;
                draws_.push_back(d);
                if (outline) {
                    DrawItem hull = d;
                    hull.pass = Pass::Outline;
                    hull.flags = (d.flags & ~(xm::kDrawTextured | xm::kDrawAlphaTest |
                                              xm::kDrawUnlit)) |
                                 xm::kDrawOutline;
                    hull.texture = -1;    // the outline samples nothing
                    hull.billboard = false;
                    hull.toon = false;    // its own flag, not the ramp term
                    draws_.push_back(hull);
                    ++stats_.outlines;
                }
            }
        }
    }

    if (draws_.empty()) {
        error = "scene has nothing drawable";
        return false;
    }

    // Outline hulls first (issue #21: they belong behind the surfaces they surround),
    // then opaque geometry, then the multiply decals over it, then additive effect
    // cards last: decals are coplanar with the ground and must not occlude anything,
    // and effect glows add over the shadowed ground rather than under it. The
    // decal-after-opaque half reproduces the original's decal-pass-last order; the
    // effect-last half is the renderer's choice, unverified against the original.
    // (The original draws each character's hull immediately before that character's
    // surface; depth testing makes the global order equivalent, and it keeps the pipeline
    // switches to one per pass.) The instance-only templates are ordered with the base
    // draws so an instance lands in the same pass group its model would have.
    std::stable_partition(draws_.begin(), draws_.end(),
                          [](const DrawItem& d) { return d.pass != Pass::Effect; });
    std::stable_partition(draws_.begin(), draws_.end(),
                          [](const DrawItem& d) {
                              return d.pass == Pass::Outline || d.pass == Pass::Opaque;
                          });
    std::stable_partition(draws_.begin(), draws_.end(),
                          [](const DrawItem& d) { return d.pass == Pass::Outline; });
    std::stable_partition(drawTemplates_.begin(), drawTemplates_.end(),
                          [](const DrawItem& d) { return d.pass != Pass::Effect; });
    // The instance source of truth: the base draws in their final pass order, then the
    // instance-only templates. Instance copies are appended after them (inside the Effect
    // group, which is last).
    // Instance-only templates were counted by the per-draw stats above (texture/pass
    // bookkeeping happens before the push); a template is not a draw, so take them back
    // out and let setEffectInstances' copies stand for themselves.
    {
        int tTextured = 0, tUntextured = 0, tDecals = 0, tEffects = 0;
        for (const DrawItem& d : drawTemplates_) {
            if (d.texture >= 0) ++tTextured; else ++tUntextured;
            if (d.pass == Pass::Decal) ++tDecals;
            else if (d.pass == Pass::Effect) ++tEffects;
        }
        stats_.textured -= tTextured;
        stats_.untextured -= tUntextured;
        stats_.decals -= tDecals;
        stats_.effects -= tEffects;
    }
    baseDrawList_ = draws_;
    drawTemplates_.insert(drawTemplates_.end(), draws_.begin(), draws_.end());
    effectInstances_.clear();

    paletteBuffer_ = gpu::createBuffer(device_, palette_.size() * sizeof(glm::mat4),
                                       WGPUBufferUsage_Storage | WGPUBufferUsage_CopyDst,
                                       palette_.data());
    if (!paletteBuffer_) {
        error = "storage buffer creation failed";
        return false;
    }
    // One draw block per view: the split-screen pass rewrites the per-draw uniforms for
    // each view's camera (billboard yaw is per camera), so the buffer holds kMaxViewCameras
    // copies and the single-view path keeps using offset 0 exactly as before. The effect
    // instances of setEffectInstances() grow the draw list after this point, so the
    // capacity is tracked and grown on demand (ensureDrawCapacity).
    if (!ensureDrawCapacity(draws_.size(), error)) return false;

    // Group 2 differs only by the texture view, so one bind group per texture; slot 0
    // is the white fallback every untextured draw indexes into.
    textureGroups_.reserve(textures_.size() + 1);
    for (size_t i = 0; i <= textures_.size(); ++i) {
        WGPUBindGroupEntry entries[2] = {};
        entries[0].binding = 0;
        entries[0].textureView = (i == 0) ? whiteView_ : textures_[i - 1].view;
        entries[1].binding = 1;
        entries[1].sampler = sampler_;
        WGPUBindGroupDescriptor bgDesc = {};
        bgDesc.layout = bindGroupLayouts_[2];
        bgDesc.entryCount = 2;
        bgDesc.entries = entries;
        WGPUBindGroup g = wgpuDeviceCreateBindGroup(device_, &bgDesc);
        if (!g) {
            error = "texture bind group creation failed";
            return false;
        }
        textureGroups_.push_back(g);
    }

    stats_.draws = draws_.size();
    stats_.textures = textures_.size();
    stats_.paletteMatrices = palette_.size();
    baseEffects_ = stats_.effects;
    baseDecals_ = stats_.decals;
    return true;
}

void SceneRenderer::updatePose(const std::vector<std::vector<glm::mat4>>& worlds) {
    if (!paletteBuffer_ || meshes_.empty()) return;
    std::vector<glm::mat4> meshPalette;
    for (const MeshRecord& rec : meshes_) {
        const std::vector<glm::mat4> noWorld;
        const std::vector<glm::mat4>& world =
            rec.modelIndex < worlds.size() ? worlds[rec.modelIndex] : noWorld;
        rec.model->buildPalette(*rec.mesh, world, meshPalette);
        std::memcpy(palette_.data() + rec.paletteOffset, meshPalette.data(),
                    meshPalette.size() * sizeof(glm::mat4));
    }
    wgpuQueueWriteBuffer(queue_, paletteBuffer_, 0, palette_.data(),
                         palette_.size() * sizeof(glm::mat4));
}

void SceneRenderer::setModelMatrices(const std::vector<glm::mat4>& modelMatrices) {
    if (draws_.empty() || modelMatrices.empty()) return;
    for (DrawItem& d : draws_)
        if (!d.instance && d.modelIndex < modelMatrices.size())
            d.model = modelMatrices[d.modelIndex];
}

bool SceneRenderer::ensureDrawCapacity(size_t draws, std::string& error) {
    if (draws <= drawCapacity_ && drawGroup_) return true;
    if (drawGroup_) wgpuBindGroupRelease(drawGroup_);
    drawGroup_ = nullptr;
    if (drawBuffer_) wgpuBufferRelease(drawBuffer_);
    drawBuffer_ = nullptr;
    // A little headroom: a growing live-card set would otherwise recreate the buffer on
    // almost every frame while it fills up.
    const size_t want = draws + draws / 4 + 16;
    drawBuffer_ = gpu::createBuffer(device_, (uint64_t)xm::kDrawStride * want * kMaxViewCameras,
                                    WGPUBufferUsage_Uniform | WGPUBufferUsage_CopyDst, nullptr);
    if (!drawBuffer_) {
        error = "draw uniform buffer creation failed";
        return false;
    }
    WGPUBindGroupEntry drawEntries[2] = {};
    drawEntries[0].binding = 0;
    drawEntries[0].buffer = drawBuffer_;
    drawEntries[0].size = sizeof(xm::DrawUniform);
    drawEntries[1].binding = 1;
    drawEntries[1].buffer = paletteBuffer_;
    drawEntries[1].size = palette_.size() * sizeof(glm::mat4);
    WGPUBindGroupDescriptor bgDesc = {};
    bgDesc.layout = bindGroupLayouts_[1];
    bgDesc.entryCount = 2;
    bgDesc.entries = drawEntries;
    drawGroup_ = wgpuDeviceCreateBindGroup(device_, &bgDesc);
    if (!drawGroup_) {
        error = "draw bind group creation failed";
        return false;
    }
    drawCapacity_ = want;
    return true;
}

void SceneRenderer::setEffectInstances(const std::vector<EffectInstance>& instances) {
    if (instances.size() == effectInstances_.size() &&
        std::equal(instances.begin(), instances.end(), effectInstances_.begin(),
                   [](const EffectInstance& a, const EffectInstance& b) {
                       return a.modelIndex == b.modelIndex && a.model == b.model &&
                              a.billboard == b.billboard;
                   }))
        return;   // unchanged: keep the current draw list (the common frame)
    effectInstances_ = instances;
    draws_.clear();
    draws_.reserve(drawTemplates_.size() + instances.size());
    for (const DrawItem& t : drawTemplates_) draws_.push_back(t);
    for (const EffectInstance& e : instances) {
        for (const DrawItem& t : drawTemplates_) {
            if ((int)t.modelIndex != e.modelIndex) continue;
            DrawItem d = t;
            d.model = e.model;
            d.instance = true;
            // The per-mesh verdict still has the last word: a ground-plane card is never
            // yawed (classifyBillboard), and an instance that opts out is never yawed
            // either. `billboard` is only consulted for Effect-pass draws, so an instance
            // of any other pass is unaffected.
            d.billboard = t.billboard && e.billboard;
            draws_.push_back(d);
        }
    }
    int instEffects = 0, instDecals = 0;
    for (const DrawItem& d : draws_)
        if (d.instance) {
            if (d.pass == Pass::Effect) ++instEffects;
            else if (d.pass == Pass::Decal) ++instDecals;
        }
    stats_.effects = baseEffects_ + instEffects;
    stats_.decals  = baseDecals_ + instDecals;
    stats_.draws   = draws_.size();
    std::string error;
    if (!ensureDrawCapacity(draws_.size(), error)) {
        // No error channel here: drop the instances and keep the frame valid rather than
        // submit a draw list the uniform buffer cannot describe.
        std::fprintf(stderr, "[render] effect instances dropped: %s\n", error.c_str());
        effectInstances_.clear();
        draws_ = baseDrawList_;   // the scene's own draws, with no instance copies
    }
}

void SceneRenderer::setCamera(const glm::mat4& viewProj) { camera_.viewProj = viewProj; }

void SceneRenderer::setEye(const glm::vec3& eye) {
    eye_ = eye;
    haveEye_ = true;
}

void SceneRenderer::setFog(const xm::StageEnv& env) {
    camera_.fogColor = glm::vec4(env.fogColor, 1.f);
    camera_.fogParams = glm::vec4(env.fogStart, env.fogEnd, env.fogEnabled ? 1.f : 0.f, 0.f);
}

void SceneRenderer::setAppearance(const Appearance& a) { appearance_ = a; }

bool SceneRenderer::ensureDepth(uint32_t width, uint32_t height, std::string& error) {
    if (depthTex_ && depthWidth_ == width && depthHeight_ == height) return true;
    if (depthView_) wgpuTextureViewRelease(depthView_);
    if (depthTex_) wgpuTextureRelease(depthTex_);
    depthView_ = nullptr;
    depthTex_ = nullptr;

    // The original renders into a D3DFMT_D16 autodepthstencil. Without a depth buffer
    // a stage is unrenderable: its inverted sky dome encloses the camera, so whichever
    // sub-model is drawn first fills the screen. The texture carries a stencil byte
    // too, for the DX9 decal guard below (first decal to cover a pixel bumps it via
    // INCRSAT); depth values are identical to the old stencil-less texture.
    WGPUTextureDescriptor td = {};
    td.usage = WGPUTextureUsage_RenderAttachment;
    td.dimension = WGPUTextureDimension_2D;
    td.size = WGPUExtent3D{width, height, 1};
    td.format = WGPUTextureFormat_Depth24PlusStencil8;
    td.mipLevelCount = 1;
    td.sampleCount = 1;
    depthTex_ = wgpuDeviceCreateTexture(device_, &td);
    if (!depthTex_) {
        error = "depth texture creation failed";
        return false;
    }
    depthView_ = wgpuTextureCreateView(depthTex_, nullptr);
    depthWidth_ = width;
    depthHeight_ = height;
    return true;
}

WGPURenderPipeline SceneRenderer::pipelineFor(WGPUTextureFormat format, Pass pass, bool npr,
                                              std::string& error) {
    Pipelines* entry = nullptr;
    for (Pipelines& p : pipelines_)
        if (p.format == format) {
            entry = &p;
            break;
        }
    if (!entry) {
        pipelines_.push_back(Pipelines{});
        entry = &pipelines_.back();
        entry->format = format;
    }
    WGPURenderPipeline& slot = entry->slots[(int)pass][npr ? 1 : 0];
    if (slot) return slot;

    WGPUVertexAttribute attrs[xm::kVertexAttributeCount];
    WGPUVertexBufferLayout vbl = xm::wgpuVertexLayout(attrs);
    // Second stream (issue #25): the secondary lighting normal. It is part of every
    // pipeline rather than a variant, so enabling an experiment never rebuilds one; a
    // mesh without the data binds its zero stream instead.
    WGPUVertexAttribute nprAttr[1];
    WGPUVertexBufferLayout nprVbl = xm::wgpuNprVertexLayout(nprAttr);
    WGPUVertexBufferLayout vbls[2] = {vbl, nprVbl};

    // Each pass builds only on first use: the default captures draw no effect cards,
    // so eagerly creating every variant per format would mint pipelines nothing binds.
    auto makePipeline = [&](Pass kind) {
        //   * outline is the toon state's hull (issue #21): the same lit/depth/blend
        //     state as opaque but with FRONT faces culled, because the original's outline
        //     pass draws the back faces of the normal-offset hull (its pass loop sets
        //     D3DRS_CULLMODE = 2 there, i.e. cull clockwise = cull the CW-front faces)
        //     so that only the rim sticking out past the model's silhouette survives the
        //     depth test;
        //   * opaque draws lit, textured 3D geometry, alpha-blended;
        //   * decal reproduces the DX9 path for baked shadows —
        //     dest = src * dst (SRCBLEND = DESTCOLOR, DESTBLEND = ZERO), ZWRITEENABLE
        //     off so the card never occludes anything, and no culling because a decal
        //     card can face either way. The stencil test is the DX9 overlap guard:
        //     pixels already shadowed read 1, not 0, and are skipped, so two cards
        //     darken shared ground exactly once. The reference is set to 0 once the
        //     decal pass binds (render() below);
        //   * effect reproduces the observed need of the glow/spark cards in
        //     data/effect and data/aura: additive over everything, unlit, no depth
        //     write, no culling — the 2D/effect-pass treatment the original gives
        //     such cards (CULLMODE off). SRC_ALPHA,ONE matches the DX9 debug
        //     additive precedent; on shipped effect textures alpha is uniformly 255
        //     (surveyed), so it coincides with ONE,ONE there — see RENDER-PASSES.md.
        WGPUColorTargetState target = {};
        target.format = format;
        target.writeMask = WGPUColorWriteMask_All;
        WGPUBlendState blend = {};
        if (kind == Pass::Decal) {
            blend.color.srcFactor = WGPUBlendFactor_Dst;
            blend.color.dstFactor = WGPUBlendFactor_Zero;
            blend.alpha.srcFactor = WGPUBlendFactor_Zero;
            blend.alpha.dstFactor = WGPUBlendFactor_One;
        } else if (kind == Pass::Effect) {
            blend.color.srcFactor = WGPUBlendFactor_SrcAlpha;
            blend.color.dstFactor = WGPUBlendFactor_One;
            blend.alpha.srcFactor = WGPUBlendFactor_One;
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

        WGPUDepthStencilState depth = {};
        depth.format = WGPUTextureFormat_Depth24PlusStencil8;
        // The outline writes depth like the original's pass loop, which never touches
        // ZWRITEENABLE: the hull has to lay down its own depth or the model drawn after
        // it could not resolve against it.
        depth.depthWriteEnabled = (kind == Pass::Opaque || kind == Pass::Outline)
                                      ? WGPUOptionalBool_True
                                      : WGPUOptionalBool_False;
        depth.depthCompare = WGPUCompareFunction_LessEqual;
        setStencilOps(depth.stencilFront);
        setStencilOps(depth.stencilBack);
        // Full masks on every pass, not just the decal one: the masks are meaningless
        // while all ops are Keep, but a zero mask is a needless backend-validation
        // question on targets this session cannot execute (web/Dawn).
        depth.stencilReadMask = 0xFF;
        depth.stencilWriteMask = 0xFF;
        if (kind == Pass::Decal) {
            // EQUAL 0 / INCRSAT — the DX9 states verbatim.
            for (WGPUStencilFaceState* s : {&depth.stencilFront, &depth.stencilBack}) {
                s->compare = WGPUCompareFunction_Equal;
                s->passOp = WGPUStencilOperation_IncrementClamp;
            }
        }

        WGPUFragmentState fs = {};
        fs.module = shader_;
        fs.entryPoint = sv("fs_main");
        fs.targetCount = 1;
        fs.targets = &target;

        WGPURenderPipelineDescriptor rpd = {};
        rpd.layout = pipelineLayout_;
        rpd.vertex.module = shader_;
        // Issue #25: the experiment draws take the entry point that reads the secondary
        // normal stream. Everything else about the pipeline is identical, so a scene with
        // no experiment on builds exactly the pipelines it built before.
        rpd.vertex.entryPoint = sv(npr ? "vs_npr" : "vs_main");
        rpd.vertex.bufferCount = 2;
        rpd.vertex.buffers = vbls;
        rpd.primitive.topology = WGPUPrimitiveTopology_TriangleList;
        // Assets are authored clockwise-front, left-handed.
        rpd.primitive.frontFace = WGPUFrontFace_CW;
        // The original culls counter-clockwise for 3D (CULLMODE = 3) and disables
        // culling for its 2D/effect passes, which is where the decals belong. The outline
        // pass is the one place it culls the other way (CULLMODE = 2, the hull's front
        // faces), so that is the one pipeline here with cullMode = Front.
        rpd.primitive.cullMode = kind == Pass::Opaque  ? WGPUCullMode_Back
                                 : kind == Pass::Outline ? WGPUCullMode_Front
                                                         : WGPUCullMode_None;
        rpd.depthStencil = &depth;
        rpd.multisample.count = 1;
        rpd.multisample.mask = 0xFFFFFFFFu;
        rpd.fragment = &fs;
        return wgpuDeviceCreateRenderPipeline(device_, &rpd);
    };

    slot = makePipeline(pass);
    if (!slot) error = "render pipeline creation failed for format " + std::to_string((int)format);
    return slot;
}

bool SceneRenderer::render(const Target& target, std::string& error) {
    return renderImpl(target, nullptr, error);
}

bool SceneRenderer::renderViews(const Target& target, const std::vector<ViewCamera>& views,
                                std::string& error) {
    if (views.size() <= 1) return renderImpl(target, nullptr, error);
    if (views.size() > kMaxViewCameras) {
        error = "too many views for one frame";
        return false;
    }
    return renderImpl(target, &views, error);
}

// Per-draw uniforms for every draw in draws_, one record per draw under one camera
// eye. `haveEye` false keeps the historical no-billboard behaviour of callers written
// before setEye existed.
void SceneRenderer::fillDrawData(const glm::vec3& eye, bool haveEye, uint8_t* dst) {
    for (const DrawItem& d : draws_) {
        xm::DrawUniform du;
        du.model = d.model;
        // Cylindrical billboard: yaw the card around its own (posed) center so its
        // plane faces the camera, preserving world up. Unskinned effect meshes pose
        // as world = model * palette[0] * pos, so folding T(C)*Ry*T(-C) into the
        // model matrix rotates the posed card rigidly. The yaw is relative to the
        // card's authored facing (bbYaw0): a YZ-plane card's normal starts at +X,
        // so facing the camera needs yaw - 90°, not yaw. Overhead camera (|d| ~ 0)
        // keeps the authored orientation instead of spinning on a singularity.
        if (d.billboard && haveEye && d.paletteOffset < palette_.size()) {
            const glm::mat4 fw = d.model * palette_[d.paletteOffset];
            const glm::vec3 c = glm::vec3(fw * glm::vec4(d.bbCenter, 1.f));
            const glm::vec2 dxy = glm::vec2(eye.x - c.x, eye.z - c.z);
            if (glm::dot(dxy, dxy) > 1e-6f) {
                const float yaw = std::atan2(dxy.x, dxy.y) - d.bbYaw0;
                const glm::mat4 t1 = glm::translate(glm::mat4(1.f), c);
                const glm::mat4 t0 = glm::translate(glm::mat4(1.f), -c);
                du.model = t1 * glm::rotate(glm::mat4(1.f), yaw, glm::vec3(0.f, 1.f, 0.f)) *
                           t0 * d.model;
            }
        }
        du.paletteOffset = d.paletteOffset;
        // The toon bits are decided here, per frame, from the appearance switch: the
        // toggle is a draw-time state change with no re-upload behind it. A scene with no
        // ramp (no game data) never sets them, so ON degrades to OFF rather than to an
        // invented curve.
        du.flags = d.flags | (appearance_.unlit ? xm::kDrawUnlit : 0u) |
                   (appearance_.toon && toonRampReady_ && d.toon ? xm::kDrawToon : 0u) |
                   (appearance_.shadows && d.receiver && d.pass == Pass::Opaque
                        ? xm::kDrawShadowReceiver
                        : 0u);
        du.baseColor = d.baseColor;
        du.emissive = d.emissive;
        du.nprBand = glm::vec4(1.f, 1.f, 1.f, 0.f);
        if (d.toon && d.pass == Pass::Opaque) {
            // Issue #25 experiments, decided per frame like the toon bits: the whole
            // harness is one draw-time state change, so an A/B needs no re-upload and the
            // OFF path never enters this block. Each experiment writes its OWN uniform
            // slot, so a composed arm keeps every one's values.
            if (appearance_.smoothedNormals && d.nprNormals) {
                du.flags |= xm::kDrawNprNormals;
            }
            if (appearance_.bands != NprBands::Off) {
                du.flags |= xm::kDrawNprShadow;
                du.nprMask = glm::vec4(appearance_.normalMaskBias, 0.f, 0.f, 0.f);
                // w selects the curve: 0 is the hard step, +softness a 2-band smoothstep,
                // -softness the 3-band arm (the shader negates it back and adds the lower
                // edge). One float rather than a mode uniform, because the mode is a
                // property of the curve the shader evaluates, not of the draw.
                float soft = appearance_.bands == NprBands::Hard ? 0.f
                                                                 : appearance_.bandSoftness;
                if (appearance_.bands == NprBands::Three) soft = -soft;
                du.nprBand = glm::vec4(appearance_.shadowTint, soft);
            }
            if (appearance_.key != NprKey::Off) {
                du.flags |= xm::kDrawNprKey;
                du.nprKey = glm::vec4(nprKeyDirection(d.model, eye, haveEye, appearance_),
                                      appearance_.keyStrength);
            }
            if (appearance_.specular) {
                du.flags |= xm::kDrawNprSpec;
                du.nprSpec = glm::vec4(appearance_.specTint, appearance_.specStrength);
            }
            if (appearance_.rim) {
                du.flags |= xm::kDrawNprRim;
                du.nprRim = glm::vec4(appearance_.rimTint, appearance_.rimStrength);
            }
        } else if (d.pass == Pass::Outline) {
            // The outline experiment's only control: the recovered width times a factor.
            // Its own uniform so it cannot be confused with a surface tint.
            du.nprBand = glm::vec4(1.f, 1.f, 1.f, appearance_.outlineScale);
        }
        std::memcpy(dst, &du, sizeof du);
        dst += xm::kDrawStride;
    }
}

void SceneRenderer::releaseShadowTargets() {
    for (ShadowTarget& t : shadowTargets_) {
        if (t.group) wgpuBindGroupRelease(t.group);
        if (t.depthView) wgpuTextureViewRelease(t.depthView);
        if (t.depth) wgpuTextureRelease(t.depth);
        if (t.view) wgpuTextureViewRelease(t.view);
        if (t.tex) wgpuTextureRelease(t.tex);
        t = ShadowTarget{};
    }
}

bool SceneRenderer::dumpShadowMap(const std::string& path, std::string& error) {
    if (!shadowTargets_[0].tex) {
        error = "no shadow map was rendered";
        return false;
    }
    const uint32_t w = kShadowMapSize, h = kShadowMapSize;
    WGPUBuffer buffer = gpu::createBuffer(device_, (uint64_t)w * h * 4,
                                          WGPUBufferUsage_CopyDst | WGPUBufferUsage_MapRead, nullptr);
    if (!buffer) {
        error = "shadow dump buffer creation failed";
        return false;
    }
    WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(device_, nullptr);
    WGPUTexelCopyTextureInfo src = {};
    src.texture = shadowTargets_[0].tex;
    src.aspect = WGPUTextureAspect_All;
    WGPUTexelCopyBufferInfo dst = {};
    dst.buffer = buffer;
    dst.layout.bytesPerRow = w * 4;
    dst.layout.rowsPerImage = h;
    const WGPUExtent3D extent = {w, h, 1};
    wgpuCommandEncoderCopyTextureToBuffer(encoder, &src, &dst, &extent);
    WGPUCommandBuffer commands = wgpuCommandEncoderFinish(encoder, nullptr);
    wgpuQueueSubmit(queue_, 1, &commands);
    wgpuCommandBufferRelease(commands);
    wgpuCommandEncoderRelease(encoder);

    std::vector<uint8_t> pixels;
    if (!gpu::readBuffer(instance_, buffer, 0, (uint64_t)w * h * 4, pixels, error)) {
        wgpuBufferRelease(buffer);
        return false;
    }
    wgpuBufferRelease(buffer);
    std::FILE* f = std::fopen(path.c_str(), "wb");
    if (!f) {
        error = "shadow dump could not be written to " + path;
        return false;
    }
    // PGM of the alpha channel, which is where the caster's light depth lives.
    std::fprintf(f, "P5\n%u %u\n255\n", w, h);
    for (uint32_t i = 0; i < w * h; ++i) std::fputc(pixels[(size_t)i * 4 + 3], f);
    std::fclose(f);
    return true;
}

bool SceneRenderer::ensureShadowTarget(size_t view, std::string& error) {
    if (view >= kMaxViewCameras) {
        error = "shadow map requested for an out-of-range view";
        return false;
    }
    if (shadowTargets_[view].group) return true;
    ShadowTarget& t = shadowTargets_[view];

    WGPUTextureDescriptor td = {};
    // The map is a render target the caster pass writes and the stage samples, with the
    // caster's depth in alpha — the original's A8R8G8B8 (FUN_00650410:0x650476) and
    // nothing else: no mips, one level, the same as the original's CreateTexture call.
    // CopySrc as well: the gated DSH_DUMP_SHADOW readback is the only way to tell an
    // empty map from a receiver bug, and a usage flag is cheaper than a second texture.
    td.usage = WGPUTextureUsage_RenderAttachment | WGPUTextureUsage_TextureBinding |
               WGPUTextureUsage_CopySrc;
    td.dimension = WGPUTextureDimension_2D;
    td.size = WGPUExtent3D{kShadowMapSize, kShadowMapSize, 1};
    td.format = WGPUTextureFormat_RGBA8Unorm;
    td.mipLevelCount = 1;
    td.sampleCount = 1;
    t.tex = wgpuDeviceCreateTexture(device_, &td);
    if (t.tex) t.view = wgpuTextureCreateView(t.tex, nullptr);

    WGPUTextureDescriptor dd = {};
    dd.usage = WGPUTextureUsage_RenderAttachment;
    dd.dimension = WGPUTextureDimension_2D;
    dd.size = WGPUExtent3D{kShadowMapSize, kShadowMapSize, 1};
    // The original's depth surface is D24S8 with an A8R8G8B8 fallback (FUN_00650410's
    // second CreateTexture); the scene's own depth format is the port's equivalent and
    // keeps one depth format across the renderer.
    dd.format = kSceneDepthFormat;
    dd.mipLevelCount = 1;
    dd.sampleCount = 1;
    t.depth = wgpuDeviceCreateTexture(device_, &dd);
    if (t.depth) t.depthView = wgpuTextureCreateView(t.depth, nullptr);

    if (!t.view || !t.depthView) {
        error = "shadow map creation failed";
        releaseShadowTargets();
        return false;
    }
    WGPUBindGroupEntry entries[2] = {};
    entries[0].binding = 0;
    entries[0].textureView = t.view;
    entries[1].binding = 1;
    entries[1].sampler = shadowSampler_;
    WGPUBindGroupDescriptor desc = {};
    desc.layout = bindGroupLayouts_[3];
    desc.entryCount = 2;
    desc.entries = entries;
    t.group = wgpuDeviceCreateBindGroup(device_, &desc);
    if (!t.group) {
        error = "shadow map bind group creation failed";
        releaseShadowTargets();
        return false;
    }
    return true;
}

bool SceneRenderer::ensureViewCameras(std::string& error) {
    if (viewCameraGroups_[0]) return true;
    for (size_t i = 0; i < kMaxViewCameras; ++i) {
        viewCameraBuffers_[i] = gpu::createBuffer(device_, sizeof(xm::CameraUniform),
                                                  WGPUBufferUsage_Uniform | WGPUBufferUsage_CopyDst,
                                                  nullptr);
        if (!viewCameraBuffers_[i]) {
            error = "view camera buffer creation failed";
            return false;
        }
        WGPUBindGroupEntry entries[3] = {};
        entries[0].binding = 0;
        entries[0].buffer = viewCameraBuffers_[i];
        entries[0].size = sizeof(xm::CameraUniform);
        // Every view camera group carries the same scene-wide toon ramp as the
        // single-view one: the split-screen path rebinds group 0 per view, and a group
        // missing these entries is a layout mismatch the whole frame is rejected for.
        entries[1].binding = 1;
        entries[1].textureView = toonRampView_;
        entries[2].binding = 2;
        entries[2].sampler = toonRampSampler_;
        WGPUBindGroupDescriptor desc = {};
        desc.layout = bindGroupLayouts_[0];
        desc.entryCount = 3;
        desc.entries = entries;
        viewCameraGroups_[i] = wgpuDeviceCreateBindGroup(device_, &desc);
        if (!viewCameraGroups_[i]) {
            error = "view camera bind group creation failed";
            return false;
        }
    }
    return true;
}

// The caster pass's pipeline, built on first use: its own layout (groups 0 and 1 only)
// and its own entry points, and nothing else about it is shared with the main passes.
bool SceneRenderer::ensureShadowPipeline(std::string& error) {
    if (shadowPipeline_) return true;

    WGPUVertexAttribute attrs[xm::kVertexAttributeCount];
    WGPUVertexBufferLayout vbl = xm::wgpuVertexLayout(attrs);
    WGPUVertexAttribute nprAttr[1];
    WGPUVertexBufferLayout nprVbl = xm::wgpuNprVertexLayout(nprAttr);
    WGPUVertexBufferLayout vbls[2] = {vbl, nprVbl};
    WGPUColorTargetState shadowTarget = {};
    shadowTarget.format = WGPUTextureFormat_RGBA8Unorm;
    shadowTarget.writeMask = WGPUColorWriteMask_All;
    // No blending: the original's mode-2 entry sets SRCBLEND = ONE, DESTBLEND = ZERO,
    // i.e. a plain overwrite of the target it just cleared.
    WGPUDepthStencilState shadowDepth = {};
    shadowDepth.format = kSceneDepthFormat;
    shadowDepth.depthWriteEnabled = WGPUOptionalBool_True;
    shadowDepth.depthCompare = WGPUCompareFunction_LessEqual;
    setStencilOps(shadowDepth.stencilFront);
    setStencilOps(shadowDepth.stencilBack);
    shadowDepth.stencilReadMask = 0xFF;
    shadowDepth.stencilWriteMask = 0xFF;
    WGPUFragmentState fs = {};
    fs.module = shader_;
    fs.entryPoint = sv("fs_shadow");
    fs.targetCount = 1;
    fs.targets = &shadowTarget;
    WGPURenderPipelineDescriptor rpd = {};
    rpd.layout = shadowPipelineLayout_;
    rpd.vertex.module = shader_;
    rpd.vertex.entryPoint = sv("vs_shadow");
    rpd.vertex.bufferCount = 2;
    rpd.vertex.buffers = vbls;
    rpd.primitive.topology = WGPUPrimitiveTopology_TriangleList;
    rpd.primitive.frontFace = WGPUFrontFace_CW;
    // CULL_CCW, the mode-2 entry's own state (FUN_00652880:0x6528a4): the same winding
    // rule the plain 3D path uses.
    rpd.primitive.cullMode = WGPUCullMode_Back;
    rpd.depthStencil = &shadowDepth;
    rpd.multisample.count = 1;
    rpd.multisample.mask = 0xFFFFFFFFu;
    rpd.fragment = &fs;
    shadowPipeline_ = wgpuDeviceCreateRenderPipeline(device_, &rpd);
    if (!shadowPipeline_) {
        error = "shadow pipeline creation failed";
        return false;
    }
    return true;
}

// One caster pass per view: the view's own map is both the target and, later, what its
// stage draws sample. `views` has the same meaning as in renderImpl — null is the
// single-view path, which uses cameraGroup_ and draw-buffer offset 0.
bool SceneRenderer::renderShadowCasters(const Target& target, const std::vector<ViewCamera>* views,
                                        std::string& error) {
    const bool multiView = views != nullptr;
    const size_t viewCount = multiView ? views->size() : 1;
    for (size_t view = 0; view < viewCount; ++view) {
        if (multiView && (*views)[view].rect.empty()) continue;
        if (!ensureShadowTarget(view, error)) return false;
        const ShadowTarget& map = shadowTargets_[view];
        WGPURenderPassColorAttachment shadowColor = {};
        shadowColor.view = map.view;
        shadowColor.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
        shadowColor.loadOp = WGPULoadOp_Clear;
        shadowColor.storeOp = WGPUStoreOp_Store;
        // 0xff000000 in the original's Clear: black with alpha 1.0.
        shadowColor.clearValue = WGPUColor{0.0, 0.0, 0.0, 1.0};
        WGPURenderPassDepthStencilAttachment shadowDepthAttachment = {};
        shadowDepthAttachment.view = map.depthView;
        shadowDepthAttachment.depthLoadOp = WGPULoadOp_Clear;
        shadowDepthAttachment.depthStoreOp = WGPUStoreOp_Store;
        shadowDepthAttachment.depthClearValue = 1.0f;
        shadowDepthAttachment.depthReadOnly = false;
        shadowDepthAttachment.stencilLoadOp = WGPULoadOp_Clear;
        shadowDepthAttachment.stencilStoreOp = WGPUStoreOp_Discard;
        shadowDepthAttachment.stencilClearValue = 0;
        shadowDepthAttachment.stencilReadOnly = false;
        WGPURenderPassDescriptor shadowDesc = {};
        shadowDesc.colorAttachmentCount = 1;
        shadowDesc.colorAttachments = &shadowColor;
        shadowDesc.depthStencilAttachment = &shadowDepthAttachment;
        WGPURenderPassEncoder caster =
            wgpuCommandEncoderBeginRenderPass(target.encoder, &shadowDesc);
        if (!caster) {
            error = "shadow pass could not be started";
            return false;
        }
        wgpuRenderPassEncoderSetPipeline(caster, shadowPipeline_);
        wgpuRenderPassEncoderSetBindGroup(
            caster, 0, multiView ? viewCameraGroups_[view] : cameraGroup_, 0, nullptr);
        const uint32_t casterBase =
            multiView ? (uint32_t)(view * draws_.size() * xm::kDrawStride) : 0u;
        for (size_t i = 0; i < draws_.size(); ++i) {
            const DrawItem& d = draws_[i];
            // The caster set is the toon technique's own surface set: the fighter's body
            // and weapon, and not the outline hull (which the toon row marks with its own
            // flag rather than `toon`).
            if (!d.toon || d.pass != Pass::Opaque) continue;
            const uint32_t offset = casterBase + (uint32_t)(i * xm::kDrawStride);
            wgpuRenderPassEncoderSetBindGroup(caster, 1, drawGroup_, 1, &offset);
            wgpuRenderPassEncoderSetVertexBuffer(caster, 0, d.vbuf, 0, WGPU_WHOLE_SIZE);
            wgpuRenderPassEncoderSetVertexBuffer(caster, 1, d.nprbuf, 0, WGPU_WHOLE_SIZE);
            wgpuRenderPassEncoderSetIndexBuffer(caster, d.ibuf, WGPUIndexFormat_Uint32, 0,
                                                WGPU_WHOLE_SIZE);
            wgpuRenderPassEncoderDrawIndexed(caster, d.indexCount, 1, d.firstIndex, 0, 0);
            ++stats_.shadowCasters;
        }
        wgpuRenderPassEncoderEnd(caster);
        wgpuRenderPassEncoderRelease(caster);
    }
    return true;
}

bool SceneRenderer::renderImpl(const Target& target, const std::vector<ViewCamera>* views,
                               std::string& error) {
    if (!device_ || !drawGroup_) {
        error = "renderer has no scene";
        return false;
    }
    if (!target.encoder || !target.colorView || target.width == 0 || target.height == 0) {
        error = "render target is incomplete";
        return false;
    }
    if (!ensureDepth(target.width, target.height, error)) return false;

    const bool multiView = views != nullptr;
    const size_t viewCount = multiView ? views->size() : 1;
    if (multiView && !ensureViewCameras(error)) return false;

    // Camera, light and fog, in a local copy: the light is a fixed world-space key,
    // because the original has no dynamic lighting for 3D passes, only these D3D light
    // registers — and drawing must not rewrite the state the caller set.
    //
    // The values are the DX9 gameplay pass's, named in the header with their scenes.cpp
    // provenance. Two of them are not literal copies: the direction is normalised (D3D
    // normalises it for the N.L dot product, and the shader would otherwise have to), and
    // the two ambient terms arrive pre-summed because the fixed-function equation
    // multiplies the material ambient by their sum once, Ca*(Ga + La). Light 0's Specular
    // is zero-initialised and D3DRS_SPECULARENABLE is never set (default FALSE), so there
    // is no specular term to carry.
    xm::CameraUniform camera = camera_;
    // Issue #25: the rim/spec view vector needs an eye the fragment stage can read. It is
    // the same value effect-card billboarding already uses, and haveEye_ is false only on
    // callers written before either existed, where the term is off anyway.
    camera.eye = glm::vec4(eye_, 1.f);
    camera.lightDir = glm::vec4(glm::normalize(kLightDirection), 0.f);
    camera.lightColor = glm::vec4(kLightDiffuse, kLightDiffuse, kLightDiffuse, 1.f);
    const float ambientSum = kGlobalAmbient + kLightAmbient;
    camera.ambient = glm::vec4(ambientSum, ambientSum, ambientSum, 1.f);
    if (!appearance_.fog) camera.fogParams.z = 0.f;
    // Character shadows (issue #21 row 1): the light camera is per view, exactly as the
    // original builds it (FUN_006507c0 runs inside the per-view loop). The pass only runs
    // when there is an eye to anchor it to — the single-view path has one only after
    // setEye(), and a caller that never set it keeps the pre-change frame.
    const bool shadowsOn = appearance_.shadows && (multiView || haveEye_);
    camera.shadowParams = glm::vec4(kShadowDepthBias, kShadowDepthClamp, shadowsOn ? 1.f : 0.f,
                                    kShadowDarken);
    if (!multiView) {
        if (shadowsOn) camera.shadowViewProj = shadowViewProj(eye_);
        wgpuQueueWriteBuffer(queue_, cameraBuffer_, 0, &camera, sizeof camera);
    } else {
        for (size_t v = 0; v < viewCount; ++v) {
            xm::CameraUniform viewCamera = camera;
            viewCamera.viewProj = (*views)[v].viewProj;
            viewCamera.eye = glm::vec4((*views)[v].eye, 1.f);
            if (shadowsOn) viewCamera.shadowViewProj = shadowViewProj((*views)[v].eye);
            wgpuQueueWriteBuffer(queue_, viewCameraBuffers_[v], 0, &viewCamera, sizeof viewCamera);
        }
    }

    std::vector<uint8_t> drawData((size_t)xm::kDrawStride * draws_.size() *
                                  (multiView ? viewCount : 1), 0);
    if (!multiView) {
        fillDrawData(eye_, haveEye_, drawData.data());
    } else {
        for (size_t v = 0; v < viewCount; ++v)
            fillDrawData((*views)[v].eye, true,
                         drawData.data() + v * draws_.size() * xm::kDrawStride);
    }
    wgpuQueueWriteBuffer(queue_, drawBuffer_, 0, drawData.data(), drawData.size());

    // The shadow caster pass (issue #21 row 1), before the main pass and one per view: the
    // original selects technique mode 2 and draws every fighter inside the per-view loop
    // (FUN_006396f0:0x639b8c-0x639bc6), into a map its own view's stage draw then samples.
    // The draws are the same character/weapon surfaces the toon technique covers (the
    // original's FUN_004207d0 draws the fighter's body and weapon sub-objects), and the
    // map is cleared to alpha 1.0 — the "nothing cast here" sentinel the receiver tests.
    stats_.shadowCasters = 0;
    stats_.shadowReceivers = 0;
    if (shadowsOn) {
        if (!ensureShadowPipeline(error)) return false;
        if (!renderShadowCasters(target, views, error)) return false;
    }

    WGPURenderPassColorAttachment color = {};
    color.view = target.colorView;
    color.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
    color.loadOp = WGPULoadOp_Clear;
    color.storeOp = WGPUStoreOp_Store;
    // The DX9 clear, byte for byte (scenes.cpp:736): it shows through wherever no
    // geometry lands, so the background is part of the frame the gate compares.
    color.clearValue = WGPUColor{kClearRed / 255.f, kClearGreen / 255.f, kClearBlue / 255.f, 1.0};

    WGPURenderPassDepthStencilAttachment depth = {};
    depth.view = depthView_;
    depth.depthLoadOp = WGPULoadOp_Clear;
    depth.depthStoreOp = WGPUStoreOp_Store;
    depth.depthClearValue = 1.0f;
    depth.depthReadOnly = false;
    // The decal guard needs a zeroed stencil every frame; nothing reads it back.
    depth.stencilLoadOp = WGPULoadOp_Clear;
    depth.stencilStoreOp = WGPUStoreOp_Discard;
    depth.stencilClearValue = 0;
    depth.stencilReadOnly = false;

    WGPURenderPassDescriptor passDesc = {};
    passDesc.colorAttachmentCount = 1;
    passDesc.colorAttachments = &color;
    passDesc.depthStencilAttachment = &depth;

    WGPURenderPassEncoder pass = wgpuCommandEncoderBeginRenderPass(target.encoder, &passDesc);
    if (!pass) {
        error = "render pass could not be started";
        return false;
    }
    if (!multiView) {
        wgpuRenderPassEncoderSetBindGroup(pass, 0, cameraGroup_, 0, nullptr);
        // Group 3 is the shadow map (issue #21 row 1): the real one when the caster pass
        // ran this frame, the 1x1 "nothing cast here" placeholder otherwise. Bound
        // whether or not the receiver branch is taken — WebGPU requires every binding of
        // the pipeline layout to be set, and the shader only samples it behind the
        // shadowParams.z guard.
        wgpuRenderPassEncoderSetBindGroup(
            pass, 3, shadowsOn ? shadowTargets_[0].group : shadowPlaceholderGroup_, 0, nullptr);
    }

    // Pipelines bind lazily: draws are sorted by pass, so each of the at most three
    // pipelines binds once, and a scene with no decals or effects never creates
    // those pipelines at all. The split-screen path sets them up again per view, because
    // a view is a complete draw of the scene.
    for (size_t view = 0; view < viewCount; ++view) {
        uint32_t drawBase = 0;
        if (multiView) {
            const ViewportRect& rect = (*views)[view].rect;
            if (rect.empty()) continue;
            // Viewport and scissor to the same cell: the viewport places the projection,
            // and the scissor is what keeps this view's fragments out of its neighbours'
            // cells (a viewport alone does not clip in WebGPU).
            wgpuRenderPassEncoderSetViewport(pass, rect.x, rect.y, rect.w, rect.h, 0.f, 1.f);
            wgpuRenderPassEncoderSetScissorRect(pass, (uint32_t)rect.x, (uint32_t)rect.y,
                                                (uint32_t)rect.w, (uint32_t)rect.h);
            wgpuRenderPassEncoderSetBindGroup(pass, 0, viewCameraGroups_[view], 0, nullptr);
            wgpuRenderPassEncoderSetBindGroup(
                pass, 3, shadowsOn ? shadowTargets_[view].group : shadowPlaceholderGroup_, 0,
                nullptr);
            drawBase = (uint32_t)(view * draws_.size() * xm::kDrawStride);
        }
        WGPURenderPipeline boundPipelines[kPassCount] = {};
        // No pipeline bound in this view yet; the first draw always binds one.
        std::optional<Pass> current;
        bool currentNpr = false;
        for (size_t i = 0; i < draws_.size(); ++i) {
            const DrawItem& d = draws_[i];
            // The outline hulls are queued with the scene but submitted only when the
            // toon state is on (issue #21): with it off this loop issues exactly the
            // commands it issued before the hulls existed, which is what keeps every
            // banked capture byte-identical.
            if (d.pass == Pass::Outline && !(appearance_.toon && toonRampReady_)) continue;
            // The receiver count is a per-frame fact, not a per-view one: view 0 alone
            // reports it, so a 4-view frame does not multiply it by four.
            if (view == 0 && appearance_.shadows && d.receiver && d.pass == Pass::Opaque)
                ++stats_.shadowReceivers;
            // Issue #25: only a surface draw the harness actually shades takes the
            // experiment entry point. `nprActive` is the appearance's own predicate, so a
            // run with no --npr flag never binds the second pipeline at all.
            const bool nprDraw = appearance_.nprActive() && d.toon && d.pass == Pass::Opaque;
            if (!current || d.pass != *current || nprDraw != currentNpr) {
                WGPURenderPipeline& slot = boundPipelines[(int)d.pass];
                if (!slot && !(slot = pipelineFor(target.format, d.pass, nprDraw, error))) {
                    wgpuRenderPassEncoderEnd(pass);
                    wgpuRenderPassEncoderRelease(pass);
                    return false;
                }
                wgpuRenderPassEncoderSetPipeline(pass, slot);
                if (d.pass == Pass::Decal) wgpuRenderPassEncoderSetStencilReference(pass, 0);
                current = d.pass;
                currentNpr = nprDraw;
            }
            const uint32_t offset = drawBase + (uint32_t)(i * xm::kDrawStride);
            wgpuRenderPassEncoderSetBindGroup(pass, 1, drawGroup_, 1, &offset);
            wgpuRenderPassEncoderSetBindGroup(pass, 2, textureGroups_[(size_t)(d.texture + 1)], 0,
                                              nullptr);
            wgpuRenderPassEncoderSetVertexBuffer(pass, 0, d.vbuf, 0, WGPU_WHOLE_SIZE);
            wgpuRenderPassEncoderSetVertexBuffer(pass, 1, d.nprbuf, 0, WGPU_WHOLE_SIZE);
            wgpuRenderPassEncoderSetIndexBuffer(pass, d.ibuf, WGPUIndexFormat_Uint32, 0,
                                                WGPU_WHOLE_SIZE);
            wgpuRenderPassEncoderDrawIndexed(pass, d.indexCount, 1, d.firstIndex, 0, 0);
        }
    }
    wgpuRenderPassEncoderEnd(pass);
    wgpuRenderPassEncoderRelease(pass);
    return true;
}

bool SceneRenderer::benchmark(uint32_t width, uint32_t height, int frames, double& msPerFrame,
                             std::string& error, const std::vector<ViewCamera>* views) {
    if (!device_ || !drawGroup_) {
        error = "renderer has no scene";
        return false;
    }
    if (frames < 1 || width == 0 || height == 0) {
        error = "benchmark needs a positive frame count and a non-empty target";
        return false;
    }
    // A dedicated offscreen target, not the swapchain: a headless run has no surface and
    // an interactive one would be measuring presentation. The readback the capture path
    // needs is deliberately absent — copying 2 MB per frame would dominate the number.
    WGPUTextureDescriptor td = {};
    td.usage = WGPUTextureUsage_RenderAttachment;
    td.dimension = WGPUTextureDimension_2D;
    td.size = WGPUExtent3D{width, height, 1};
    td.format = WGPUTextureFormat_RGBA8Unorm;
    td.mipLevelCount = 1;
    td.sampleCount = 1;
    // Owned by a Texture, not a bare pair: this function has five exits (two creation
    // failures, a failed encoder, a failed frame, and the normal one), and the owner
    // releases the target on all of them.
    Texture colorTex;
    colorTex.tex = wgpuDeviceCreateTexture(device_, &td);
    colorTex.view = colorTex.tex ? wgpuTextureCreateView(colorTex.tex, nullptr) : nullptr;
    if (!colorTex.tex || !colorTex.view) {
        error = "benchmark target creation failed";
        return false;
    }
    // Depth is the renderer's own attachment, sized by ensureDepth; it is created here on
    // the benchmark's behalf and left for the next frame to reuse.
    if (!ensureDepth(width, height, error)) return false;

    // Wait for the queue after every submit, so the measured span is the GPU's work and
    // not the depth of the command queue. The wait is the same process-events loop the
    // gpu layer's readback uses (gpu.cpp readBuffer), which is what makes this portable
    // to a backend where the callback only fires while events are processed.
    struct Wait { bool done = false; };
    Wait wait;
    auto onDone = [](WGPUQueueWorkDoneStatus, void* userdata1, void*) {
        static_cast<Wait*>(userdata1)->done = true;
    };

    double total = 0.0;
    for (int f = 0; f < frames; ++f) {
        WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(device_, nullptr);
        if (!encoder) {
            error = "benchmark encoder creation failed";
            return false;
        }
        Target target;
        target.encoder = encoder;
        target.colorView = colorTex.view;
        target.format = WGPUTextureFormat_RGBA8Unorm;
        target.width = width;
        target.height = height;
        const bool ok = (views && views->size() > 1) ? renderViews(target, *views, error)
                                                     : render(target, error);
        WGPUCommandBuffer cmd = ok ? wgpuCommandEncoderFinish(encoder, nullptr) : nullptr;
        if (cmd) wgpuQueueSubmit(queue_, 1, &cmd);
        if (cmd) wgpuCommandBufferRelease(cmd);
        wgpuCommandEncoderRelease(encoder);
        if (!ok) return false;
        wait.done = false;
        WGPUQueueWorkDoneCallbackInfo cb = {};
        cb.mode = WGPUCallbackMode_AllowProcessEvents;
        cb.callback = onDone;
        cb.userdata1 = &wait;
        const double t0 = plat::now();
        wgpuQueueOnSubmittedWorkDone(queue_, cb);
        while (!wait.done) wgpuInstanceProcessEvents(instance_);
        total += plat::now() - t0;
    }
    msPerFrame = 1000.0 * total / (double)frames;
    return true;
}

bool SceneRenderer::capture(uint32_t width, uint32_t height, std::vector<uint8_t>& rgba,
                           std::string& error, UiHook uiHook, void* uiUserdata,
                           const std::vector<ViewCamera>* views) {
    return captureImpl(width, height, rgba, error, uiHook, uiUserdata, /*withScene=*/true, views);
}

bool SceneRenderer::captureUi(uint32_t width, uint32_t height, std::vector<uint8_t>& rgba,
                             std::string& error, UiHook uiHook, void* uiUserdata,
                             const std::vector<ViewCamera>* views) {
    return captureImpl(width, height, rgba, error, uiHook, uiUserdata, /*withScene=*/false, views);
}

bool SceneRenderer::captureImpl(uint32_t width, uint32_t height, std::vector<uint8_t>& rgba,
                               std::string& error, UiHook uiHook, void* uiUserdata,
                               bool withScene, const std::vector<ViewCamera>* views) {
    if (!device_) {
        error = "renderer not initialized";
        return false;
    }
    rgba.clear();

    WGPUTextureDescriptor td = {};
    td.usage = WGPUTextureUsage_RenderAttachment | WGPUTextureUsage_CopySrc;
    td.dimension = WGPUTextureDimension_2D;
    td.size = WGPUExtent3D{width, height, 1};
    td.format = WGPUTextureFormat_RGBA8Unorm;
    td.mipLevelCount = 1;
    td.sampleCount = 1;
    // Owned, like the benchmark target, so the target's lifetime is the function's:
    // there is no release pair at the end for a later early return to get wrong.
    Texture colorTex;
    colorTex.tex = wgpuDeviceCreateTexture(device_, &td);
    colorTex.view = colorTex.tex ? wgpuTextureCreateView(colorTex.tex, nullptr) : nullptr;
    const uint32_t rowPitch = alignedRowPitch(width);
    const uint64_t readbackBytes = (uint64_t)rowPitch * height;
    WGPUBuffer readback = gpu::createBuffer(
        device_, readbackBytes, WGPUBufferUsage_MapRead | WGPUBufferUsage_CopyDst, nullptr);
    WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(device_, nullptr);

    bool ok = colorTex.tex && colorTex.view && readback && encoder;
    Target target;
    target.encoder = encoder;
    target.colorView = colorTex.view;
    target.format = WGPUTextureFormat_RGBA8Unorm;
    target.width = width;
    target.height = height;
    if (ok && withScene) {
        ok = (views && views->size() > 1) ? renderViews(target, *views, error) : render(target, error);
    } else if (ok) {
        // No scene: clear the target to opaque black so the UI is composited over a defined
        // background rather than uninitialised memory.
        WGPURenderPassColorAttachment att = {};
        att.view = colorTex.view;
        att.loadOp = WGPULoadOp_Clear;
        att.storeOp = WGPUStoreOp_Store;
        att.clearValue = WGPUColor{0.0, 0.0, 0.0, 1.0};
        WGPURenderPassDescriptor rp = {};
        rp.colorAttachmentCount = 1;
        rp.colorAttachments = &att;
        WGPURenderPassEncoder pass = wgpuCommandEncoderBeginRenderPass(encoder, &rp);
        wgpuRenderPassEncoderEnd(pass);
        wgpuRenderPassEncoderRelease(pass);
    }
    if (ok && uiHook) ok = uiHook(encoder, colorTex.view, td.format, width, height, uiUserdata);

    std::vector<uint8_t> padded;
    if (ok) {
        WGPUTexelCopyBufferInfo dst = {};
        dst.buffer = readback;
        dst.layout.bytesPerRow = rowPitch;
        dst.layout.rowsPerImage = height;
        WGPUTexelCopyTextureInfo src = {};
        src.texture = colorTex.tex;
        src.aspect = WGPUTextureAspect_All;
        const WGPUExtent3D extent{width, height, 1};
        wgpuCommandEncoderCopyTextureToBuffer(encoder, &src, &dst, &extent);
        WGPUCommandBuffer cmd = wgpuCommandEncoderFinish(encoder, nullptr);
        wgpuQueueSubmit(queue_, 1, &cmd);
        wgpuCommandBufferRelease(cmd);
        ok = gpu::readBuffer(instance_, readback, 0, readbackBytes, padded, error);
    }
    if (ok) {
        rgba.assign((size_t)width * height * 4, 0);
        for (uint32_t y = 0; y < height; ++y)
            std::memcpy(rgba.data() + (size_t)y * width * 4,
                        padded.data() + (size_t)y * rowPitch, (size_t)width * 4);
    } else if (error.empty()) {
        error = "capture setup failed (texture, readback buffer or encoder)";
    }

    if (encoder) wgpuCommandEncoderRelease(encoder);
    if (readback) wgpuBufferRelease(readback);
    return ok;
}

}  // namespace render
