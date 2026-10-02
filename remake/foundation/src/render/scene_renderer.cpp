#include "render/scene_renderer.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstring>
#include <unordered_map>

#include <glm/gtc/matrix_transform.hpp>

#include "shaders/model_wgsl.h"

namespace render {
namespace {

WGPUStringView sv(const char* s) { return WGPUStringView{s, WGPU_STRLEN}; }

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

// Cylindrical-billboard verdict for one effect draw, from the submesh geometry
// alone (no texture names — those are deliberately excluded as routing signals).
// Upright cards (single quads, crossed-plane sets, beam fans, Y-symmetric rings)
// yaw around world Y to face the camera; ground-plane cards (normals ±Y, e.g.
// aura/03's 400x400 floor quad) keep their authored orientation, which a Y spin
// could only disturb. All surveyed effect/aura meshes are unskinned, so the pivot
// is the submesh bounds center in mesh space; a skinned mesh can never reach here
// (the caller guards on it) because its vertices leave mesh space per-bone.
bool classifyBillboard(const xm::Mesh& mesh, const xm::Submesh& sub, glm::vec3& centerOut,
                         float& yaw0Out) {
    if (mesh.skinned || mesh.vertices.empty() || mesh.indices.empty()) return false;
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
    if (n == 0) return false;
    centerOut = (lo + hi) * 0.5f;
    // Ground-dominant cards stay put: their plane already contains every camera
    // yaw, so facing is meaningless and spinning only churns directional art.
    if (nySum / (double)n > 0.5) return false;
    // Authored facing: the yaw the card's dominant normal already has, so the
    // render-time yaw is relative to it (a YZ-plane card needs yaw-90°, not yaw).
    // Plain constants, not M_PI_2/M_PI: those need feature-test macros that differ
    // per target, and this file builds for Linux, MinGW and Emscripten alike.
    constexpr float kHalfPi = 1.57079632679f;
    constexpr float kPi = 3.14159265359f;
    if (posX >= negX && posX >= posZ && posX >= negZ)
        yaw0Out = kHalfPi;
    else if (negX >= posZ && negX >= negZ)
        yaw0Out = -kHalfPi;
    else if (negZ >= posZ)
        yaw0Out = kPi;
    else
        yaw0Out = 0.f;
    return true;
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

bool SceneRenderer::init(const gpu::Context& ctx, std::string& error) {
    if (!ctx.device || !ctx.queue || !ctx.instance) {
        error = "renderer needs a live device, queue and instance";
        return false;
    }
    instance_ = ctx.instance;
    device_ = ctx.device;
    queue_ = ctx.queue;

    shader_ = gpu::createShaderModule(device_, shaders::kModelWGSL);
    if (!shader_) {
        error = "model shader module creation failed";
        return false;
    }

    // group 0: camera. group 1: draw + palette. group 2: texture + sampler. The draw
    // uniform is bound with a dynamic offset, so one buffer serves every draw.
    WGPUBindGroupLayoutEntry cameraEntry = {};
    cameraEntry.binding = 0;
    cameraEntry.visibility = WGPUShaderStage_Vertex | WGPUShaderStage_Fragment;
    cameraEntry.buffer.type = WGPUBufferBindingType_Uniform;
    cameraEntry.buffer.minBindingSize = sizeof(xm::CameraUniform);

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

    WGPUBindGroupLayoutDescriptor bglDesc = {};
    bglDesc.entryCount = 1;
    bglDesc.entries = &cameraEntry;
    bindGroupLayouts_[0] = wgpuDeviceCreateBindGroupLayout(device_, &bglDesc);
    bglDesc.entryCount = 2;
    bglDesc.entries = drawEntries;
    bindGroupLayouts_[1] = wgpuDeviceCreateBindGroupLayout(device_, &bglDesc);
    bglDesc.entries = textureEntries;
    bindGroupLayouts_[2] = wgpuDeviceCreateBindGroupLayout(device_, &bglDesc);

    WGPUPipelineLayoutDescriptor plDesc = {};
    plDesc.bindGroupLayoutCount = 3;
    plDesc.bindGroupLayouts = bindGroupLayouts_;
    pipelineLayout_ = wgpuDeviceCreatePipelineLayout(device_, &plDesc);

    WGPUSamplerDescriptor sd = {};
    sd.addressModeU = sd.addressModeV = sd.addressModeW = WGPUAddressMode_Repeat;
    sd.magFilter = WGPUFilterMode_Linear;
    sd.minFilter = WGPUFilterMode_Linear;
    sd.mipmapFilter = WGPUMipmapFilterMode_Nearest;
    sd.lodMinClamp = 0.f;
    sd.lodMaxClamp = 32.f;
    sd.maxAnisotropy = 1;
    sampler_ = wgpuDeviceCreateSampler(device_, &sd);

    // The untextured fallback: binds where a material has no resolvable texture, so
    // the shader's unconditional sample stays valid.
    const uint32_t white = 0xffffffffu;
    WGPUTextureDescriptor td = {};
    td.usage = WGPUTextureUsage_TextureBinding | WGPUTextureUsage_CopyDst;
    td.dimension = WGPUTextureDimension_2D;
    td.size = WGPUExtent3D{1, 1, 1};
    td.format = WGPUTextureFormat_RGBA8Unorm;
    td.mipLevelCount = 1;
    td.sampleCount = 1;
    whiteTex_ = wgpuDeviceCreateTexture(device_, &td);
    if (whiteTex_) {
        WGPUTexelCopyTextureInfo dst = {};
        dst.texture = whiteTex_;
        dst.aspect = WGPUTextureAspect_All;
        WGPUTexelCopyBufferLayout layout = {};
        layout.bytesPerRow = 4;
        layout.rowsPerImage = 1;
        wgpuQueueWriteTexture(queue_, &dst, &white, 4, &layout, &td.size);
        whiteView_ = wgpuTextureCreateView(whiteTex_, nullptr);
    }

    cameraBuffer_ = gpu::createBuffer(device_, sizeof(xm::CameraUniform),
                                      WGPUBufferUsage_Uniform | WGPUBufferUsage_CopyDst, nullptr);

    if (!bindGroupLayouts_[0] || !bindGroupLayouts_[1] || !bindGroupLayouts_[2] ||
        !pipelineLayout_ || !sampler_ || !whiteView_ || !cameraBuffer_) {
        error = "renderer setup failed (bind group layout, sampler or buffer)";
        return false;
    }

    WGPUBindGroupEntry camEntry = {};
    camEntry.binding = 0;
    camEntry.buffer = cameraBuffer_;
    camEntry.size = sizeof(xm::CameraUniform);
    WGPUBindGroupDescriptor bgDesc = {};
    bgDesc.layout = bindGroupLayouts_[0];
    bgDesc.entryCount = 1;
    bgDesc.entries = &camEntry;
    cameraGroup_ = wgpuDeviceCreateBindGroup(device_, &bgDesc);
    if (!cameraGroup_) {
        error = "camera bind group creation failed";
        return false;
    }
    return true;
}

void SceneRenderer::shutdown() {
    for (Pipelines& p : pipelines_) {
        if (p.opaque) wgpuRenderPipelineRelease(p.opaque);
        if (p.decal) wgpuRenderPipelineRelease(p.decal);
        if (p.effect) wgpuRenderPipelineRelease(p.effect);
    }
    pipelines_.clear();

    for (WGPUBindGroup g : textureGroups_)
        if (g) wgpuBindGroupRelease(g);
    textureGroups_.clear();
    if (drawGroup_) wgpuBindGroupRelease(drawGroup_);
    if (cameraGroup_) wgpuBindGroupRelease(cameraGroup_);
    drawGroup_ = cameraGroup_ = nullptr;

    for (WGPUBuffer b : buffers_)
        if (b) wgpuBufferRelease(b);
    buffers_.clear();
    for (Texture& t : textures_) {
        if (t.view) wgpuTextureViewRelease(t.view);
        if (t.tex) wgpuTextureRelease(t.tex);
    }
    textures_.clear();

    if (paletteBuffer_) wgpuBufferRelease(paletteBuffer_);
    if (drawBuffer_) wgpuBufferRelease(drawBuffer_);
    if (cameraBuffer_) wgpuBufferRelease(cameraBuffer_);
    paletteBuffer_ = drawBuffer_ = cameraBuffer_ = nullptr;

    if (depthView_) wgpuTextureViewRelease(depthView_);
    if (depthTex_) wgpuTextureRelease(depthTex_);
    depthView_ = nullptr;
    depthTex_ = nullptr;
    depthWidth_ = depthHeight_ = 0;

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
    for (WGPUBuffer b : buffers_) wgpuBufferRelease(b);
    buffers_.clear();
    for (Texture& t : textures_) {
        wgpuTextureViewRelease(t.view);
        wgpuTextureRelease(t.tex);
    }
    textures_.clear();
    for (WGPUBindGroup g : textureGroups_) wgpuBindGroupRelease(g);
    textureGroups_.clear();
    if (drawGroup_) wgpuBindGroupRelease(drawGroup_);
    drawGroup_ = nullptr;
    if (paletteBuffer_) wgpuBufferRelease(paletteBuffer_);
    if (drawBuffer_) wgpuBufferRelease(drawBuffer_);
    paletteBuffer_ = drawBuffer_ = nullptr;

    draws_.clear();
    meshes_.clear();
    palette_.clear();
    stats_ = Stats{};

    // Images are shared between materials, so upload each one once and index draws
    // into the result.
    std::unordered_map<const xm::CnvImage*, int> texIndex;
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
            if (!vbuf || !ibuf) {
                error = "vertex/index buffer creation failed for " + sm.source;
                return false;
            }

            for (const xm::Submesh& sub : mesh.submeshes) {
                DrawItem d;
                d.vbuf = vbuf;
                d.ibuf = ibuf;
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
                    // const_cast: the cache hands out a shared image and keying white
                    // out is idempotent, which is what makes mutating it here safe.
                    xm::CnvImage* img = const_cast<xm::CnvImage*>(sm.textures.get(mat.texture));
                    if (img && !img->empty()) {
                        // White keys out so the card disappears where it is neutral and
                        // only the blob multiplies.
                        if (pass == Pass::Decal) xm::keyOutWhite(*img);
                        auto it = texIndex.find(img);
                        if (it == texIndex.end()) {
                            Texture tex;
                            WGPUTextureDescriptor td = {};
                            td.usage = WGPUTextureUsage_TextureBinding | WGPUTextureUsage_CopyDst;
                            td.dimension = WGPUTextureDimension_2D;
                            td.size = WGPUExtent3D{img->width, img->height, 1};
                            td.format = WGPUTextureFormat_RGBA8Unorm;
                            td.mipLevelCount = 1;
                            td.sampleCount = 1;
                            tex.tex = wgpuDeviceCreateTexture(device_, &td);
                            if (tex.tex) {
                                WGPUTexelCopyTextureInfo dst = {};
                                dst.texture = tex.tex;
                                dst.aspect = WGPUTextureAspect_All;
                                WGPUTexelCopyBufferLayout layout = {};
                                layout.bytesPerRow = img->width * 4;
                                layout.rowsPerImage = img->height;
                                wgpuQueueWriteTexture(queue_, &dst, img->rgba.data(),
                                                      img->rgba.size(), &layout, &td.size);
                                tex.view = wgpuTextureCreateView(tex.tex, nullptr);
                            }
                            if (!tex.tex || !tex.view) {
                                error = "texture upload failed (device out of memory?)";
                                return false;
                            }
                            it = texIndex.emplace(img, (int)textures_.size()).first;
                            textures_.push_back(tex);
                        }
                        d.texture = it->second;
                        ++stats_.textured;
                    } else {
                        ++stats_.untextured;
                    }
                } else {
                    ++stats_.untextured;
                }
                d.pass = pass;
                // Diffuse rides baseColor the way D3DX feeds faceColor to the pipeline;
                // the renderer used to shade everything white. Observed tinted materials
                // all live in non-drawn collision meshes, so no capture changes from
                // this — it is the real per-material signal, wired rather than dropped.
                d.baseColor = mat.diffuse;
                // Effect cards yaw to face the camera around world Y (cylindrical, not
                // spherical: the world's up axis is load-bearing — ground cards lie in
                // XZ, shockwaves read as verticals — and the arena camera stays near
                // level). The verdict is geometry-only; dormant until setEye().
                if (pass == Pass::Effect && classifyBillboard(mesh, sub, d.bbCenter, d.bbYaw0)) {
                    d.billboard = true;
                    ++stats_.billboarded;
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
                draws_.push_back(d);
            }
        }
    }

    if (draws_.empty()) {
        error = "scene has nothing drawable";
        return false;
    }

    // Opaque geometry first, then the multiply decals over it, then additive effect
    // cards last: decals are coplanar with the ground and must not occlude anything,
    // and effect glows add over the shadowed ground rather than under it. The
    // decal-after-opaque half reproduces the original's decal-pass-last order; the
    // effect-last half is the renderer's choice, unverified against the original.
    std::stable_partition(draws_.begin(), draws_.end(),
                          [](const DrawItem& d) { return d.pass == Pass::Opaque; });
    std::stable_partition(draws_.begin(), draws_.end(),
                          [](const DrawItem& d) { return d.pass != Pass::Effect; });

    paletteBuffer_ = gpu::createBuffer(device_, palette_.size() * sizeof(glm::mat4),
                                       WGPUBufferUsage_Storage | WGPUBufferUsage_CopyDst,
                                       palette_.data());
    drawBuffer_ = gpu::createBuffer(device_, xm::kDrawStride * draws_.size(),
                                    WGPUBufferUsage_Uniform | WGPUBufferUsage_CopyDst, nullptr);
    if (!paletteBuffer_ || !drawBuffer_) {
        error = "uniform/storage buffer creation failed";
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

    // Group 2 differs only by the texture view, so one bind group per texture; slot 0
    // is the white fallback every untextured draw indexes into.
    textureGroups_.reserve(textures_.size() + 1);
    for (size_t i = 0; i <= textures_.size(); ++i) {
        WGPUBindGroupEntry entries[2] = {};
        entries[0].binding = 0;
        entries[0].textureView = (i == 0) ? whiteView_ : textures_[i - 1].view;
        entries[1].binding = 1;
        entries[1].sampler = sampler_;
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
        if (d.modelIndex < modelMatrices.size()) d.model = modelMatrices[d.modelIndex];
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

WGPURenderPipeline SceneRenderer::pipelineFor(WGPUTextureFormat format, Pass pass,
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
    WGPURenderPipeline& slot =
        pass == Pass::Opaque ? entry->opaque : pass == Pass::Decal ? entry->decal : entry->effect;
    if (slot) return slot;

    WGPUVertexAttribute attrs[xm::kVertexAttributeCount];
    WGPUVertexBufferLayout vbl = xm::wgpuVertexLayout(attrs);

    // Each pass builds only on first use: the default captures draw no effect cards,
    // so eagerly creating all three per format would mint pipelines nothing binds.
    auto makePipeline = [&](Pass kind) {
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
        depth.depthWriteEnabled =
            kind == Pass::Opaque ? WGPUOptionalBool_True : WGPUOptionalBool_False;
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
        rpd.vertex.entryPoint = sv("vs_main");
        rpd.vertex.bufferCount = 1;
        rpd.vertex.buffers = &vbl;
        rpd.primitive.topology = WGPUPrimitiveTopology_TriangleList;
        // Assets are authored clockwise-front, left-handed.
        rpd.primitive.frontFace = WGPUFrontFace_CW;
        // The original culls counter-clockwise for 3D (CULLMODE = 3) and disables
        // culling for its 2D/effect passes, which is where the decals belong.
        rpd.primitive.cullMode = kind == Pass::Opaque ? WGPUCullMode_Back : WGPUCullMode_None;
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
    if (!device_ || !drawGroup_) {
        error = "renderer has no scene";
        return false;
    }
    if (!target.encoder || !target.colorView || target.width == 0 || target.height == 0) {
        error = "render target is incomplete";
        return false;
    }
    if (!ensureDepth(target.width, target.height, error)) return false;

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
    camera.lightDir = glm::vec4(glm::normalize(kLightDirection), 0.f);
    camera.lightColor = glm::vec4(kLightDiffuse, kLightDiffuse, kLightDiffuse, 1.f);
    const float ambientSum = kGlobalAmbient + kLightAmbient;
    camera.ambient = glm::vec4(ambientSum, ambientSum, ambientSum, 1.f);
    if (!appearance_.fog) camera.fogParams.z = 0.f;
    wgpuQueueWriteBuffer(queue_, cameraBuffer_, 0, &camera, sizeof camera);

    std::vector<uint8_t> drawData((size_t)xm::kDrawStride * draws_.size(), 0);
    for (size_t i = 0; i < draws_.size(); ++i) {
        xm::DrawUniform du;
        du.model = draws_[i].model;
        // Cylindrical billboard: yaw the card around its own (posed) center so its
        // plane faces the camera, preserving world up. Unskinned effect meshes pose
        // as world = model * palette[0] * pos, so folding T(C)*Ry*T(-C) into the
        // model matrix rotates the posed card rigidly. The yaw is relative to the
        // card's authored facing (bbYaw0): a YZ-plane card's normal starts at +X,
        // so facing the camera needs yaw - 90°, not yaw. Overhead camera (|d| ~ 0)
        // keeps the authored orientation instead of spinning on a singularity.
        if (draws_[i].billboard && haveEye_ &&
            draws_[i].paletteOffset < palette_.size()) {
            const glm::mat4 fw = draws_[i].model * palette_[draws_[i].paletteOffset];
            const glm::vec3 c = glm::vec3(fw * glm::vec4(draws_[i].bbCenter, 1.f));
            const glm::vec2 d = glm::vec2(eye_.x - c.x, eye_.z - c.z);
            if (glm::dot(d, d) > 1e-6f) {
                const float yaw = std::atan2(d.x, d.y) - draws_[i].bbYaw0;
                const glm::mat4 t1 = glm::translate(glm::mat4(1.f), c);
                const glm::mat4 t0 = glm::translate(glm::mat4(1.f), -c);
                du.model = t1 * glm::rotate(glm::mat4(1.f), yaw, glm::vec3(0.f, 1.f, 0.f)) *
                           t0 * draws_[i].model;
            }
        }
        du.paletteOffset = draws_[i].paletteOffset;
        du.flags = draws_[i].flags | (appearance_.unlit ? xm::kDrawUnlit : 0u);
        du.baseColor = draws_[i].baseColor;
        std::memcpy(drawData.data() + i * xm::kDrawStride, &du, sizeof du);
    }
    wgpuQueueWriteBuffer(queue_, drawBuffer_, 0, drawData.data(), drawData.size());

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
    wgpuRenderPassEncoderSetBindGroup(pass, 0, cameraGroup_, 0, nullptr);

    // Pipelines bind lazily: draws are sorted by pass, so each of the at most three
    // pipelines binds once, and a scene with no decals or effects never creates
    // those pipelines at all.
    WGPURenderPipeline boundPipelines[3] = {nullptr, nullptr, nullptr};
    Pass current = Pass::Opaque;
    bool haveCurrent = false;
    for (size_t i = 0; i < draws_.size(); ++i) {
        const DrawItem& d = draws_[i];
        if (!haveCurrent || d.pass != current) {
            WGPURenderPipeline& slot = boundPipelines[(int)d.pass];
            if (!slot && !(slot = pipelineFor(target.format, d.pass, error))) {
                wgpuRenderPassEncoderEnd(pass);
                wgpuRenderPassEncoderRelease(pass);
                return false;
            }
            wgpuRenderPassEncoderSetPipeline(pass, slot);
            if (d.pass == Pass::Decal) wgpuRenderPassEncoderSetStencilReference(pass, 0);
            current = d.pass;
            haveCurrent = true;
        }
        const uint32_t offset = (uint32_t)(i * xm::kDrawStride);
        wgpuRenderPassEncoderSetBindGroup(pass, 1, drawGroup_, 1, &offset);
        wgpuRenderPassEncoderSetBindGroup(pass, 2, textureGroups_[(size_t)(d.texture + 1)], 0,
                                          nullptr);
        wgpuRenderPassEncoderSetVertexBuffer(pass, 0, d.vbuf, 0, WGPU_WHOLE_SIZE);
        wgpuRenderPassEncoderSetIndexBuffer(pass, d.ibuf, WGPUIndexFormat_Uint32, 0,
                                            WGPU_WHOLE_SIZE);
        wgpuRenderPassEncoderDrawIndexed(pass, d.indexCount, 1, d.firstIndex, 0, 0);
    }
    wgpuRenderPassEncoderEnd(pass);
    wgpuRenderPassEncoderRelease(pass);
    return true;
}

bool SceneRenderer::capture(uint32_t width, uint32_t height, std::vector<uint8_t>& rgba,
                           std::string& error, UiHook uiHook, void* uiUserdata) {
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
    WGPUTexture colorTex = wgpuDeviceCreateTexture(device_, &td);
    WGPUTextureView colorView = colorTex ? wgpuTextureCreateView(colorTex, nullptr) : nullptr;
    const uint32_t rowPitch = alignedRowPitch(width);
    const uint64_t readbackBytes = (uint64_t)rowPitch * height;
    WGPUBuffer readback = gpu::createBuffer(
        device_, readbackBytes, WGPUBufferUsage_MapRead | WGPUBufferUsage_CopyDst, nullptr);
    WGPUCommandEncoder encoder = wgpuDeviceCreateCommandEncoder(device_, nullptr);

    bool ok = colorTex && colorView && readback && encoder;
    Target target;
    target.encoder = encoder;
    target.colorView = colorView;
    target.format = WGPUTextureFormat_RGBA8Unorm;
    target.width = width;
    target.height = height;
    if (ok) ok = render(target, error);
    if (ok && uiHook) ok = uiHook(encoder, colorView, td.format, width, height, uiUserdata);

    std::vector<uint8_t> padded;
    if (ok) {
        WGPUTexelCopyBufferInfo dst = {};
        dst.buffer = readback;
        dst.layout.bytesPerRow = rowPitch;
        dst.layout.rowsPerImage = height;
        WGPUTexelCopyTextureInfo src = {};
        src.texture = colorTex;
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
    if (colorView) wgpuTextureViewRelease(colorView);
    if (colorTex) wgpuTextureRelease(colorTex);
    return ok;
}

}  // namespace render
