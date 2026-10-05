#include "ui/sprite.h"

// gpu/ owns shader-module creation and buffer helpers (it tracks the header
// spelling both backends accept); ui/ consumes them exactly as render/ does,
// which keeps the backend choice a build decision rather than a code change.
#include <cmath>

#include "gpu/gpu.h"
#include "shaders/ui_wgsl.h"

namespace ui {
namespace {

// Viewport uniform, padded to 16 bytes: some drivers are unhappy with sub-16
// uniform bindings even though 8 would be legal here.
struct ViewportUniform {
    float w, h, pad0, pad1;
};

WGPUStringView sv(const char* s) { return WGPUStringView{s, WGPU_STRLEN}; }

}  // namespace

SpriteRenderer::~SpriteRenderer() { shutdown(); }

bool SpriteRenderer::init(WGPUDevice device, WGPUQueue queue, std::string& error) {
    if (!device || !queue) {
        error = "sprite renderer needs a live device and queue";
        return false;
    }
    shutdown();
    device_ = device;
    queue_ = queue;

    shader_ = gpu::createShaderModule(device, shaders::kUiWGSL);
    if (!shader_) {
        // gpu/ owns module creation (it tracks the spelling both backends
        // accept); ui/ must not mint its own variant. See docs/UI-DESIGN.md.
        error = "ui shader module creation failed";
        shutdown();
        return false;
    }

    WGPUBindGroupLayoutEntry vpEntry = {};
    vpEntry.binding = 0;
    vpEntry.visibility = WGPUShaderStage_Vertex;
    vpEntry.buffer.type = WGPUBufferBindingType_Uniform;
    vpEntry.buffer.minBindingSize = sizeof(ViewportUniform);
    // The binding is offset per pass (see kUniformSlots): a frame's passes share one
    // buffer, so the value each pass reads must be its own.
    vpEntry.buffer.hasDynamicOffset = true;

    WGPUBindGroupLayoutDescriptor bglDesc = {};
    bglDesc.entryCount = 1;
    bglDesc.entries = &vpEntry;
    vpLayout_ = wgpuDeviceCreateBindGroupLayout(device_, &bglDesc);

    WGPUBindGroupLayoutEntry texEntries[2] = {};
    texEntries[0].binding = 0;
    texEntries[0].visibility = WGPUShaderStage_Fragment;
    texEntries[0].texture.sampleType = WGPUTextureSampleType_Float;
    texEntries[0].texture.viewDimension = WGPUTextureViewDimension_2D;
    texEntries[1].binding = 1;
    texEntries[1].visibility = WGPUShaderStage_Fragment;
    texEntries[1].sampler.type = WGPUSamplerBindingType_Filtering;
    bglDesc.entryCount = 2;
    bglDesc.entries = texEntries;
    texLayout_ = wgpuDeviceCreateBindGroupLayout(device_, &bglDesc);

    WGPUPipelineLayoutDescriptor plDesc = {};
    const WGPUBindGroupLayout layouts[2] = {vpLayout_, texLayout_};
    plDesc.bindGroupLayoutCount = 2;
    plDesc.bindGroupLayouts = layouts;
    layout_ = wgpuDeviceCreatePipelineLayout(device_, &plDesc);

    WGPUSamplerDescriptor sd = {};
    sd.addressModeU = sd.addressModeV = sd.addressModeW = WGPUAddressMode_ClampToEdge;
    sd.magFilter = WGPUFilterMode_Linear;
    sd.minFilter = WGPUFilterMode_Linear;
    sd.mipmapFilter = WGPUMipmapFilterMode_Nearest;
    sd.maxAnisotropy = 1;   // zero-init leaves 0, which the validator rejects
    sampler_ = wgpuDeviceCreateSampler(device_, &sd);

    vpBuffer_ = gpu::createBuffer(device_, kUniformSlots * kUniformStride,
                                   WGPUBufferUsage_Uniform | WGPUBufferUsage_CopyDst, nullptr);
    uniformSlot_ = 0;

    if (!vpLayout_ || !texLayout_ || !layout_ || !sampler_ || !vpBuffer_) {
        error = "sprite renderer setup failed (layouts, sampler or viewport buffer)";
        shutdown();
        return false;
    }

    WGPUBindGroupEntry entry = {};
    entry.binding = 0;
    entry.buffer = vpBuffer_;
    entry.size = sizeof(ViewportUniform);
    WGPUBindGroupDescriptor bgDesc = {};
    bgDesc.layout = vpLayout_;
    bgDesc.entryCount = 1;
    bgDesc.entries = &entry;
    vpGroup_ = wgpuDeviceCreateBindGroup(device_, &bgDesc);
    if (!vpGroup_) {
        error = "viewport bind group creation failed";
        shutdown();
        return false;
    }

    // Slot 0: the 1x1 white fallback solid quads sample, so the shader's
    // unconditional texture sample stays valid exactly as in scene_renderer.
    const uint32_t white = 0xffffffffu;
    std::string texError;
    if (addTexture(1, 1, &white, texError) != 0) {
        error = "white fallback texture failed: " + texError;
        shutdown();
        return false;
    }
    return true;
}

void SpriteRenderer::shutdown() {
    for (Pipeline& p : pipelines_)
        if (p.pipeline) wgpuRenderPipelineRelease(p.pipeline);
    pipelines_.clear();
    for (Texture& t : textures_) destroyTexture(t);
    textures_.clear();
    if (vpGroup_) wgpuBindGroupRelease(vpGroup_);
    if (vpBuffer_) wgpuBufferRelease(vpBuffer_);
    if (vbuf_) wgpuBufferRelease(vbuf_);
    if (ibuf_) wgpuBufferRelease(ibuf_);
    vpGroup_ = nullptr;
    vpBuffer_ = vbuf_ = ibuf_ = nullptr;
    if (sampler_) wgpuSamplerRelease(sampler_);
    if (layout_) wgpuPipelineLayoutRelease(layout_);
    if (vpLayout_) wgpuBindGroupLayoutRelease(vpLayout_);
    if (texLayout_) wgpuBindGroupLayoutRelease(texLayout_);
    sampler_ = nullptr;
    layout_ = nullptr;
    vpLayout_ = texLayout_ = nullptr;
    if (shader_) wgpuShaderModuleRelease(shader_);
    shader_ = nullptr;
    quads_.clear();
    dropped_ = 0;
    device_ = nullptr;
    queue_ = nullptr;
}

int SpriteRenderer::addTexture(uint32_t w, uint32_t h, const void* rgba, std::string& error) {
    Texture t;
    if (!createTexture(t, w, h, rgba, error)) return -1;
    textures_.push_back(t);
    return (int)textures_.size() - 1;
}

bool SpriteRenderer::updateTexture(int slot, uint32_t w, uint32_t h, const void* rgba,
                                   std::string& error) {
    if (slot < 0 || (size_t)slot >= textures_.size()) {
        error = "ui texture slot " + std::to_string(slot) + " does not exist";
        return false;
    }
    // Build first, swap after: a failed upload must leave the old texture renderable
    // rather than a null slot that the next frame would sample.
    Texture t;
    if (!createTexture(t, w, h, rgba, error)) return false;
    destroyTexture(textures_[slot]);
    textures_[slot] = t;
    return true;
}

bool SpriteRenderer::createTexture(Texture& t, uint32_t w, uint32_t h, const void* rgba,
                                   std::string& error) {
    if (!device_) {
        error = "sprite renderer not initialized";
        return false;
    }
    if (w == 0 || h == 0 || w > 8192 || h > 8192 || !rgba) {
        error = "texture dimensions out of range or null pixels";
        return false;
    }
    WGPUTextureDescriptor td = {};
    td.usage = WGPUTextureUsage_TextureBinding | WGPUTextureUsage_CopyDst;
    td.dimension = WGPUTextureDimension_2D;
    td.size = WGPUExtent3D{w, h, 1};
    td.format = WGPUTextureFormat_RGBA8Unorm;
    td.mipLevelCount = 1;
    td.sampleCount = 1;
    t.w = w;
    t.h = h;
    t.tex = wgpuDeviceCreateTexture(device_, &td);
    if (t.tex) {
        WGPUTexelCopyTextureInfo dst = {};
        dst.texture = t.tex;
        dst.aspect = WGPUTextureAspect_All;
        WGPUTexelCopyBufferLayout layout = {};
        layout.bytesPerRow = w * 4;
        layout.rowsPerImage = h;
        wgpuQueueWriteTexture(queue_, &dst, rgba, (size_t)w * h * 4, &layout, &td.size);
        t.view = wgpuTextureCreateView(t.tex, nullptr);
    }
    if (!t.tex || !t.view) {
        error = "ui texture upload failed (device out of memory?)";
        destroyTexture(t);
        return false;
    }
    WGPUBindGroupEntry entries[2] = {};
    entries[0].binding = 0;
    entries[0].textureView = t.view;
    entries[1].binding = 1;
    entries[1].sampler = sampler_;
    WGPUBindGroupDescriptor bgDesc = {};
    bgDesc.layout = texLayout_;
    bgDesc.entryCount = 2;
    bgDesc.entries = entries;
    t.group = wgpuDeviceCreateBindGroup(device_, &bgDesc);
    if (!t.group) {
        error = "ui texture bind group creation failed";
        destroyTexture(t);
        return false;
    }
    return true;
}

void SpriteRenderer::destroyTexture(Texture& t) {
    if (t.group) wgpuBindGroupRelease(t.group);
    if (t.view) wgpuTextureViewRelease(t.view);
    if (t.tex) wgpuTextureRelease(t.tex);
    t = Texture{};
}

void SpriteRenderer::clearTextures() {
    // Slot 0 is structural (solids sample it); anything above is scene content.
    for (size_t i = 1; i < textures_.size(); ++i) destroyTexture(textures_[i]);
    if (!textures_.empty()) textures_.resize(1);
}

void SpriteRenderer::beginFrame(const UiViewport& viewport) {
    viewport_ = viewport;
    quads_.clear();
    dropped_ = 0;
    resetCanvasTransform();
}

bool SpriteRenderer::pushQuad(const UiQuad& q) {
    if (quads_.size() >= kMaxQuads) {
        ++dropped_;
        return false;
    }
    quads_.push_back(transformQuad(q, canvas_, canvasClip_));
    return true;
}

bool SpriteRenderer::pushSolid(const UiRect& dst, UiColor color, const UiClip& clip) {
    UiQuad q;
    q.dst = dst;
    q.uv = UiRect{0.f, 0.f, 1.f, 1.f};
    q.color = color;
    q.texture = -1;
    q.clip = clip;
    return pushQuad(q);
}

bool SpriteRenderer::pushTextured(int texture, const UiRect& dst, const UiRect& uv, UiColor tint,
                                  const UiClip& clip) {
    UiQuad q;
    q.dst = dst;
    q.uv = uv;
    q.color = tint;
    q.texture = texture;
    q.clip = clip;
    return pushQuad(q);
}

bool SpriteRenderer::textureSize(int texture, uint32_t& w, uint32_t& h) const {
    if (texture < 0 || (size_t)texture >= textures_.size()) return false;
    const Texture& t = textures_[texture];
    if (!t.tex || t.w == 0 || t.h == 0) return false;
    w = t.w;
    h = t.h;
    return true;
}

bool SpriteRenderer::pushSprite(int texture, const UiRect& src, float pivotX, float pivotY,
                                float x, float y, float scale, float rotDeg, UiColor tint,
                                const UiClip& clip) {
    uint32_t tw = 0, th = 0;
    if (src.w <= 0.f || src.h <= 0.f || !textureSize(texture, tw, th)) return false;
    UiQuad q;
    q.dst = spriteDst(x, y, src.w, src.h, pivotX, pivotY, scale);
    q.uv = UiRect{src.x / (float)tw, src.y / (float)th, src.w / (float)tw, src.h / (float)th};
    q.color = tint;
    q.texture = texture;
    q.clip = clip;
    q.rotDeg = rotDeg;
    q.rotCx = x;
    q.rotCy = y;
    return pushQuad(q);
}

bool SpriteRenderer::pushFill(int texture, const UiRect& src, float pivotX, float pivotY,
                              float frac, FillMode mode, float x, float y, UiColor tint,
                              const UiClip& clip) {
    if (frac <= 0.f || src.w <= 0.f || src.h <= 0.f) return false;
    if (frac > 1.f) frac = 1.f;
    uint32_t tw = 0, th = 0;
    if (!textureSize(texture, tw, th)) return false;
    const UiRect dst = fillDst(spriteDst(x, y, src.w, src.h, pivotX, pivotY), frac, mode);
    const UiRect cut = fillSrc(UiRect{src.x / (float)tw, src.y / (float)th, src.w / (float)tw,
                                      src.h / (float)th},
                               frac, mode);
    return pushTextured(texture, dst, cut, tint, clip);
}

WGPURenderPipeline SpriteRenderer::pipelineFor(WGPUTextureFormat format, std::string& error) {
    for (const Pipeline& p : pipelines_)
        if (p.format == format) return p.pipeline;

    WGPUVertexAttribute attrs[3] = {};
    attrs[0].format = WGPUVertexFormat_Float32x2;   // pos, pixels
    attrs[0].offset = 0;
    attrs[0].shaderLocation = 0;
    attrs[1].format = WGPUVertexFormat_Float32x2;   // uv
    attrs[1].offset = 2 * sizeof(float);
    attrs[1].shaderLocation = 1;
    attrs[2].format = WGPUVertexFormat_Float32x4;   // tint
    attrs[2].offset = 4 * sizeof(float);
    attrs[2].shaderLocation = 2;

    WGPUVertexBufferLayout vbl = {};
    vbl.arrayStride = sizeof(UiVertex);
    vbl.stepMode = WGPUVertexStepMode_Vertex;
    vbl.attributeCount = 3;
    vbl.attributes = attrs;

    // SrcAlpha/OneMinusSrcAlpha: the D3DXSPRITE_ALPHABLEND + UIImage quad blend.
    WGPUColorTargetState target = {};
    target.format = format;
    target.writeMask = WGPUColorWriteMask_All;
    WGPUBlendState blend = {};
    blend.color.srcFactor = WGPUBlendFactor_SrcAlpha;
    blend.color.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
    blend.color.operation = WGPUBlendOperation_Add;
    blend.alpha.srcFactor = WGPUBlendFactor_One;
    blend.alpha.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
    blend.alpha.operation = WGPUBlendOperation_Add;
    target.blend = &blend;

    WGPUFragmentState fs = {};
    fs.module = shader_;
    fs.entryPoint = sv("fs_main");
    fs.targetCount = 1;
    fs.targets = &target;

    WGPURenderPipelineDescriptor rpd = {};
    rpd.layout = layout_;
    rpd.vertex.module = shader_;
    rpd.vertex.entryPoint = sv("vs_main");
    rpd.vertex.bufferCount = 1;
    rpd.vertex.buffers = &vbl;
    rpd.primitive.topology = WGPUPrimitiveTopology_TriangleList;
    rpd.primitive.frontFace = WGPUFrontFace_CCW;
    rpd.primitive.cullMode = WGPUCullMode_None;
    rpd.multisample.count = 1;
    rpd.multisample.mask = 0xFFFFFFFFu;
    rpd.fragment = &fs;

    WGPURenderPipeline pipeline = wgpuDeviceCreateRenderPipeline(device_, &rpd);
    if (!pipeline) {
        error = "ui pipeline creation failed for format " + std::to_string((int)format);
        return nullptr;
    }
    pipelines_.push_back(Pipeline{format, pipeline});
    return pipeline;
}

bool SpriteRenderer::ensureBuffers(std::string& error) {
    if (vbuf_ && ibuf_) return true;
    vbuf_ = gpu::createBuffer(device_, sizeof(UiVertex) * kMaxQuads * 4,
                               WGPUBufferUsage_Vertex | WGPUBufferUsage_CopyDst, nullptr);
    // Static index fan: two triangles per quad slot, built once. The batch cap
    // bounds this buffer, which is why the cap exists as a constant.
    std::vector<uint16_t> indices((size_t)kMaxQuads * 6);
    for (uint32_t i = 0; i < kMaxQuads; ++i) {
        const uint16_t v = (uint16_t)(i * 4);
        uint16_t* o = indices.data() + (size_t)i * 6;
        o[0] = v;
        o[1] = (uint16_t)(v + 1);
        o[2] = (uint16_t)(v + 2);
        o[3] = (uint16_t)(v + 1);
        o[4] = (uint16_t)(v + 3);
        o[5] = (uint16_t)(v + 2);
    }
    ibuf_ = gpu::createBuffer(device_, indices.size() * sizeof(uint16_t),
                               WGPUBufferUsage_Index | WGPUBufferUsage_CopyDst, indices.data());
    if (!vbuf_ || !ibuf_) {
        error = "ui vertex/index buffer creation failed";
        return false;
    }
    return true;
}

bool SpriteRenderer::render(WGPUCommandEncoder encoder, WGPUTextureView view,
                            WGPUTextureFormat format, std::string& error) {
    if (!device_) {
        error = "sprite renderer not initialized";
        return false;
    }
    if (!encoder || !view || viewport_.w == 0 || viewport_.h == 0) {
        error = "ui render target is incomplete";
        return false;
    }
    if (quads_.empty()) return true;   // nothing queued: leave the 3D frame alone
    if (!ensureBuffers(error)) return false;

    WGPURenderPipeline pipeline = pipelineFor(format, error);
    if (!pipeline) return false;

    // This pass's own slot: the next render() in the same frame takes the next one, so a
    // later pass can no longer overwrite what this one reads (issue: split-screen HUD).
    const uint64_t uniformOffset = (uint64_t)(uniformSlot_++ % kUniformSlots) * kUniformStride;
    const ViewportUniform vu{(float)viewport_.w, (float)viewport_.h, 0.f, 0.f};
    wgpuQueueWriteBuffer(queue_, vpBuffer_, uniformOffset, &vu, sizeof vu);

    // Expand the batch into vertices, one run per (texture, scissor) so a clip
    // change or texture change costs exactly one draw. Fully clipped quads are
    // dropped on the CPU, before any GPU work.
    struct Run {
        int      texture = 0;
        uint32_t sx = 0, sy = 0, sw = 0, sh = 0;
        uint32_t firstQuad = 0, quadCount = 0;
    };
    std::vector<UiVertex> verts;
    verts.reserve(quads_.size() * 4);
    std::vector<Run> runs;
    for (size_t i = 0; i < quads_.size(); ++i) {
        const UiQuad& q = quads_[i];
        if (q.dst.w <= 0.f || q.dst.h <= 0.f) continue;
        uint32_t sx = 0, sy = 0, sw = 0, sh = 0;
        if (!clipToScissor(q.clip, viewport_, sx, sy, sw, sh)) continue;   // clipped away
        int slot = q.texture < 0 ? 0 : q.texture;
        if ((size_t)slot >= textures_.size()) continue;   // stale id: skip, never crash
        if (!runs.empty()) {
            Run& back = runs.back();
            if (back.texture == slot && back.sx == sx && back.sy == sy && back.sw == sw &&
                back.sh == sh) {
                ++back.quadCount;
            } else {
                runs.push_back(Run{slot, sx, sy, sw, sh, (uint32_t)verts.size() / 4, 1});
            }
        } else {
            runs.push_back(Run{slot, sx, sy, sw, sh, 0, 1});
        }
        const float u0 = q.uv.x, v0 = q.uv.y, u1 = q.uv.x + q.uv.w, v1 = q.uv.y + q.uv.h;
        // FUN_00655d60's rotation: the four corners turn about the draw anchor by
        // sprite[0x8c] degrees, with y down — x' = (x-cx)cos - (y-cy)sin + cx — which
        // is the pair its cos/sin helpers compute. Unrotated quads skip the trig.
        float xs[4] = {q.dst.x, q.dst.x + q.dst.w, q.dst.x, q.dst.x + q.dst.w};
        float ys[4] = {q.dst.y, q.dst.y, q.dst.y + q.dst.h, q.dst.y + q.dst.h};
        if (q.rotDeg != 0.f) {
            const float rad = q.rotDeg * 3.14159265358979323846f / 180.f;
            const float cs = std::cos(rad), sn = std::sin(rad);
            for (int k = 0; k < 4; ++k) {
                const float dx = xs[k] - q.rotCx, dy = ys[k] - q.rotCy;
                xs[k] = q.rotCx + dx * cs - dy * sn;
                ys[k] = q.rotCy + dx * sn + dy * cs;
            }
        }
        verts.push_back(UiVertex{xs[0], ys[0], u0, v0, q.color.r, q.color.g, q.color.b, q.color.a});
        verts.push_back(UiVertex{xs[1], ys[1], u1, v0, q.color.r, q.color.g, q.color.b, q.color.a});
        verts.push_back(UiVertex{xs[2], ys[2], u0, v1, q.color.r, q.color.g, q.color.b, q.color.a});
        verts.push_back(UiVertex{xs[3], ys[3], u1, v1, q.color.r, q.color.g, q.color.b, q.color.a});
    }
    if (verts.empty()) return true;
    wgpuQueueWriteBuffer(queue_, vbuf_, 0, verts.data(), verts.size() * sizeof(UiVertex));

    // Load, not Clear: the UI composes over the 3D frame drawn earlier into the
    // same view. No depth attachment: DX9 disables Z for its 2D quads too.
    WGPURenderPassColorAttachment color = {};
    color.view = view;
    color.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
    color.loadOp = WGPULoadOp_Load;
    color.storeOp = WGPUStoreOp_Store;

    WGPURenderPassDescriptor passDesc = {};
    passDesc.colorAttachmentCount = 1;
    passDesc.colorAttachments = &color;

    WGPURenderPassEncoder pass = wgpuCommandEncoderBeginRenderPass(encoder, &passDesc);
    if (!pass) {
        error = "ui render pass could not be started";
        return false;
    }
    wgpuRenderPassEncoderSetPipeline(pass, pipeline);
    const uint32_t dynamicOffset = (uint32_t)uniformOffset;
    wgpuRenderPassEncoderSetBindGroup(pass, 0, vpGroup_, 1, &dynamicOffset);
    // Viewport origin is top-left in WebGPU (D3D convention, unlike Vulkan), so
    // pixel quads map 1:1 here on every backend with no #if. A split-screen view's
    // origin places its cell; the shader still maps the view's own w x h to NDC.
    wgpuRenderPassEncoderSetViewport(pass, (float)viewport_.x, (float)viewport_.y,
                                     (float)viewport_.w, (float)viewport_.h, 0.f, 1.f);
    wgpuRenderPassEncoderSetVertexBuffer(pass, 0, vbuf_, 0, WGPU_WHOLE_SIZE);
    wgpuRenderPassEncoderSetIndexBuffer(pass, ibuf_, WGPUIndexFormat_Uint16, 0,
                                        WGPU_WHOLE_SIZE);
    for (const Run& r : runs) {
        wgpuRenderPassEncoderSetBindGroup(pass, 1, textures_[(size_t)r.texture].group, 0,
                                          nullptr);
        // The run's scissor is in the view's own pixels; the cell origin moves it onto
        // the target, and the view's clamp above keeps it inside the attachment.
        wgpuRenderPassEncoderSetScissorRect(pass, r.sx + viewport_.x, r.sy + viewport_.y,
                                            r.sw, r.sh);
        wgpuRenderPassEncoderDrawIndexed(pass, r.quadCount * 6, 1, r.firstQuad * 6, 0, 0);
    }
    wgpuRenderPassEncoderEnd(pass);
    wgpuRenderPassEncoderRelease(pass);
    return true;
}

}  // namespace ui
