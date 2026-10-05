#include "render/debug_prims.h"

#include <algorithm>

// gpu/ owns shader-module and buffer creation (it tracks the header spelling both
// backends accept); render/ consumes them exactly as scene_renderer.cpp does, which
// keeps the backend choice a build decision rather than a code change.
#include "gpu/gpu.h"
#include "shaders/debug_line_wgsl.h"

namespace render {
namespace {

WGPUStringView sv(const char* s) { return WGPUStringView{s, WGPU_STRLEN}; }

// Zero-init leaves compare and every op Undefined; nothing here uses stencil, but the
// state has to be legal anyway. Same helper, same reason, as scene_renderer.cpp.
void setStencilOps(WGPUStencilFaceState& s) {
    s.compare = WGPUCompareFunction_Always;
    s.failOp = WGPUStencilOperation_Keep;
    s.depthFailOp = WGPUStencilOperation_Keep;
    s.passOp = WGPUStencilOperation_Keep;
}

// The depth format the pass must match to attach the scene's depth view: one
// definition, in scene_renderer.h, because WebGPU validates the pipeline against the
// attachment rather than coercing them.
constexpr WGPUTextureFormat kDepthFormat = kSceneDepthFormat;

// Smallest vertex buffer to keep around. Below this every frame would resize.
constexpr uint64_t kMinVertexBytes = 4096;

// The vertex layout is raw memory handed to the GPU, so pin it: a glm build with
// aligned gentypes (or any future field) that padded DebugVertex would upload
// uninitialised bytes and make captures differ run to run.
static_assert(sizeof(DebugVertex) == 16, "DebugVertex must stay 16 bytes with no padding");
static_assert(offsetof(DebugVertex, color) == 12, "DebugVertex colour must sit at offset 12");

// Split-screen cells (issue #12): the overlay pass draws into one view's cell, so it
// needs the same viewport and scissor the scene pass used for that cell — the viewport
// places the projection, the scissor keeps the overlay out of its neighbours' cells.
// An empty rect leaves WebGPU's default full-attachment viewport untouched, which is the
// single-view path every banked capture was made with.
void applyViewport(WGPURenderPassEncoder pass, const DebugPrims::Options& options) {
    const ViewportRect& r = options.viewport;
    if (r.empty()) return;
    wgpuRenderPassEncoderSetViewport(pass, r.x, r.y, r.w, r.h, 0.f, 1.f);
    wgpuRenderPassEncoderSetScissorRect(pass, (uint32_t)r.x, (uint32_t)r.y, (uint32_t)r.w,
                                        (uint32_t)r.h);
}

}  // namespace

DebugPrims::~DebugPrims() { shutdown(); }

bool DebugPrims::init(const gpu::Context& ctx, std::string& error) {
    if (!ctx.device || !ctx.queue) {
        error = "debug prims need a live device and queue";
        return false;
    }
    shutdown();
    device_ = ctx.device;
    queue_ = ctx.queue;

    shader_ = gpu::createShaderModule(device_, shaders::kDebugLineWGSL);
    if (!shader_) {
        error = "debug line shader module creation failed";
        shutdown();
        return false;
    }

    // One bind group with one uniform: the viewProj the scene pass also receives. No
    // dynamic offset is needed — there is one camera per frame, not one per draw.
    WGPUBindGroupLayoutEntry entry = {};
    entry.binding = 0;
    entry.visibility = WGPUShaderStage_Vertex;   // the fragment stage reads colour only
    entry.buffer.type = WGPUBufferBindingType_Uniform;
    entry.buffer.minBindingSize = sizeof(glm::mat4);

    WGPUBindGroupLayoutDescriptor bglDesc = {};
    bglDesc.entryCount = 1;
    bglDesc.entries = &entry;
    bgl_ = wgpuDeviceCreateBindGroupLayout(device_, &bglDesc);

    WGPUPipelineLayoutDescriptor plDesc = {};
    plDesc.bindGroupLayoutCount = 1;
    plDesc.bindGroupLayouts = &bgl_;
    layout_ = wgpuDeviceCreatePipelineLayout(device_, &plDesc);

    ubuf_ = gpu::createBuffer(device_, sizeof(glm::mat4),
                              WGPUBufferUsage_Uniform | WGPUBufferUsage_CopyDst, nullptr);
    if (!bgl_ || !layout_ || !ubuf_) {
        error = "debug prims setup failed (bind group layout, pipeline layout or uniform)";
        shutdown();
        return false;
    }

    WGPUBindGroupEntry camEntry = {};
    camEntry.binding = 0;
    camEntry.buffer = ubuf_;
    camEntry.size = sizeof(glm::mat4);
    WGPUBindGroupDescriptor bgDesc = {};
    bgDesc.layout = bgl_;
    bgDesc.entryCount = 1;
    bgDesc.entries = &camEntry;
    group_ = wgpuDeviceCreateBindGroup(device_, &bgDesc);
    if (!group_) {
        error = "debug line camera bind group creation failed";
        shutdown();
        return false;
    }
    return true;
}

void DebugPrims::shutdown() {
    for (PipelineEntry& p : pipelines_)
        if (p.pipeline) wgpuRenderPipelineRelease(p.pipeline);
    pipelines_.clear();

    if (group_) wgpuBindGroupRelease(group_);
    if (ubuf_) wgpuBufferRelease(ubuf_);
    if (vbuf_) wgpuBufferRelease(vbuf_);
    group_ = nullptr;
    ubuf_ = vbuf_ = nullptr;
    vbufCapacity_ = 0;

    if (layout_) wgpuPipelineLayoutRelease(layout_);
    if (bgl_) wgpuBindGroupLayoutRelease(bgl_);
    layout_ = nullptr;
    bgl_ = nullptr;
    if (shader_) wgpuShaderModuleRelease(shader_);
    shader_ = nullptr;

    staging_.clear();
    stats_ = Stats{};
    device_ = nullptr;
    queue_ = nullptr;
}

WGPURenderPipeline DebugPrims::pipelineFor(WGPUTextureFormat format, uint8_t depthMode,
                                           uint8_t blend, uint8_t topology,
                                           std::string& error) {
    for (const PipelineEntry& p : pipelines_)
        if (p.format == format && p.depthMode == depthMode && p.blend == blend &&
            p.topology == topology)
            return p.pipeline;

    WGPUVertexAttribute attrs[2] = {};
    attrs[0].format = WGPUVertexFormat_Float32x3;   // world position
    attrs[0].offset = 0;
    attrs[0].shaderLocation = 0;
    attrs[1].format = WGPUVertexFormat_Uint32;      // D3DCOLOR 0xAARRGGBB, unpacked in WGSL
    attrs[1].offset = 12;
    attrs[1].shaderLocation = 1;

    WGPUVertexBufferLayout vbl = {};
    vbl.arrayStride = sizeof(DebugVertex);
    vbl.stepMode = WGPUVertexStepMode_Vertex;
    vbl.attributeCount = 2;
    vbl.attributes = attrs;

    WGPUColorTargetState target = {};
    target.format = format;
    target.writeMask = WGPUColorWriteMask_All;
    WGPUBlendState blendState = {};
    if (blend == 1) {
        // The DX9 UnlitCubePass(alphaBlend = true) pair: fire-and-forget additive,
        // which is how a bright debug line stays legible over a dark stage.
        blendState.color.srcFactor = WGPUBlendFactor_SrcAlpha;
        blendState.color.dstFactor = WGPUBlendFactor_One;
        blendState.alpha.srcFactor = WGPUBlendFactor_One;
        blendState.alpha.dstFactor = WGPUBlendFactor_One;
    } else {
        // The scene opaque-pass pair, so a caller can fade a line with its alpha.
        blendState.color.srcFactor = WGPUBlendFactor_SrcAlpha;
        blendState.color.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
        blendState.alpha.srcFactor = WGPUBlendFactor_One;
        blendState.alpha.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
    }
    blendState.color.operation = WGPUBlendOperation_Add;
    blendState.alpha.operation = WGPUBlendOperation_Add;
    target.blend = &blendState;

    // Depth is pipeline state, which is why it is a variant rather than a switch at
    // bind time: a pipeline built with a depth-stencil state can only be used in a pass
    // that carries a matching attachment, and one built without cannot be used in a
    // pass that has one. kNoDepth therefore means "the pass has no depth attachment".
    WGPUDepthStencilState depth = {};
    const bool attached = depthMode != kNoDepth;
    if (attached) {
        depth.format = kDepthFormat;
        // Never write: the scene already wrote the surfaces, and a debug overlay that
        // wrote depth would occlude whatever is drawn after it.
        depth.depthWriteEnabled = WGPUOptionalBool_False;
        // kDepthAlways is the DX9 ZENABLE = FALSE case expressed as compare-always, so
        // the overlay keeps the same pass shape as the tested variant.
        depth.depthCompare = depthMode == kDepthTested ? WGPUCompareFunction_LessEqual
                                                       : WGPUCompareFunction_Always;
        setStencilOps(depth.stencilFront);
        setStencilOps(depth.stencilBack);
        depth.stencilReadMask = 0xFF;
        depth.stencilWriteMask = 0xFF;
    }

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
    rpd.primitive.topology = topology == 1 ? WGPUPrimitiveTopology_TriangleList
                                           : WGPUPrimitiveTopology_LineList;
    // Neither face nor cull state affects a line, but neither may be left Undefined.
    rpd.primitive.frontFace = WGPUFrontFace_CCW;
    rpd.primitive.cullMode = WGPUCullMode_None;
    rpd.depthStencil = attached ? &depth : nullptr;
    rpd.multisample.count = 1;
    rpd.multisample.mask = 0xFFFFFFFFu;
    rpd.fragment = &fs;

    WGPURenderPipeline pipeline = wgpuDeviceCreateRenderPipeline(device_, &rpd);
    if (!pipeline) {
        error = "debug line pipeline creation failed for format " +
                std::to_string((int)format) + " depth mode " + std::to_string((int)depthMode);
        return nullptr;
    }
    pipelines_.push_back(PipelineEntry{format, depthMode, blend, topology, pipeline});
    return pipeline;
}

bool DebugPrims::ensureVertexBuffer(uint64_t bytes, std::string& error) {
    if (bytes <= vbufCapacity_) return true;
    // Geometric growth from a fixed floor: deterministic, and it stops once the frame's
    // worst case is reached, so the steady state allocates nothing.
    uint64_t capacity = vbufCapacity_ ? vbufCapacity_ : kMinVertexBytes;
    while (capacity < bytes) capacity *= 2;
    if (vbuf_) wgpuBufferRelease(vbuf_);
    vbuf_ = gpu::createBuffer(device_, capacity,
                              WGPUBufferUsage_Vertex | WGPUBufferUsage_CopyDst, nullptr);
    if (!vbuf_) {
        vbufCapacity_ = 0;
        error = "debug line vertex buffer creation failed";
        return false;
    }
    vbufCapacity_ = capacity;
    return true;
}

bool DebugPrims::drawVertices(const Target& target, const glm::mat4& viewProj,
                              const std::vector<DebugVertex>& verts, WGPUTextureView depthView,
                              const Options& options, std::string& error) {
    stats_ = Stats{};
    if (!device_ || !layout_) {
        error = "debug prims not initialized";
        return false;
    }
    if (!target.encoder || !target.colorView || target.width == 0 || target.height == 0) {
        error = "debug prims render target is incomplete";
        return false;
    }
    if (verts.empty()) return true;   // nothing queued: leave the frame untouched

    // Trim to whole lines, exactly as the batch does: a half line is not a thing.
    const size_t accepted = std::min(verts.size(), kMaxVertices) & ~(size_t)1;
    stats_.droppedVertices = verts.size() - accepted;
    if (accepted == 0) return true;

    // The depth view decides the pipeline variant, not a runtime switch.
    const uint8_t depthMode = depthView ? (options.depthTest ? kDepthTested : kDepthAlways)
                                        : kNoDepth;
    const uint8_t blend = options.additive ? 1 : 0;
    WGPURenderPipeline pipeline = pipelineFor(target.format, depthMode, blend, 0, error);
    if (!pipeline) return false;

    if (!ensureVertexBuffer((uint64_t)accepted * sizeof(DebugVertex), error)) return false;
    wgpuQueueWriteBuffer(queue_, vbuf_, 0, verts.data(), accepted * sizeof(DebugVertex));
    // No transpose: glm and WGSL are both column-major, and the scene pass writes its
    // CameraUniform the same way.
    wgpuQueueWriteBuffer(queue_, ubuf_, 0, &viewProj, sizeof viewProj);

    WGPURenderPassColorAttachment color = {};
    color.view = target.colorView;
    color.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
    // Load, never Clear: this pass annotates a frame that already exists.
    color.loadOp = WGPULoadOp_Load;
    color.storeOp = WGPUStoreOp_Store;

    WGPURenderPassDepthStencilAttachment depth = {};
    depth.depthClearValue = 1.f;   // unused under Load
    if (depthView) {
        depth.view = depthView;
        depth.depthLoadOp = WGPULoadOp_Load;
        depth.depthStoreOp = WGPUStoreOp_Store;
        depth.depthReadOnly = false;
        // The scene's decal pass bumps stencil (INCRSAT overlap guard); Load/Store here
        // leaves whatever it produced exactly as found, and the pipeline's stencil ops
        // are all Keep. Undefined would be the only value that could disturb it.
        depth.stencilLoadOp = WGPULoadOp_Load;
        depth.stencilStoreOp = WGPUStoreOp_Store;
        depth.stencilReadOnly = false;
    }

    WGPURenderPassDescriptor passDesc = {};
    passDesc.colorAttachmentCount = 1;
    passDesc.colorAttachments = &color;
    passDesc.depthStencilAttachment = depthView ? &depth : nullptr;

    WGPURenderPassEncoder pass = wgpuCommandEncoderBeginRenderPass(target.encoder, &passDesc);
    if (!pass) {
        error = "debug line render pass could not be started";
        return false;
    }
    wgpuRenderPassEncoderSetPipeline(pass, pipeline);
    wgpuRenderPassEncoderSetBindGroup(pass, 0, group_, 0, nullptr);
    applyViewport(pass, options);
    wgpuRenderPassEncoderSetVertexBuffer(pass, 0, vbuf_, 0, WGPU_WHOLE_SIZE);
    wgpuRenderPassEncoderDraw(pass, (uint32_t)accepted, 1, 0, 0);
    wgpuRenderPassEncoderEnd(pass);
    wgpuRenderPassEncoderRelease(pass);

    stats_.vertices = accepted;
    stats_.lines = accepted / 2;
    stats_.passes = 1;
    return true;
}

// Solid cubes, the same pass the DX9 file is: same shader, same states, only the
// primitive topology differs from the line list above.
bool DebugPrims::drawCubes(const Target& target, const glm::mat4& viewProj,
                           const CubeBatch& batch, WGPUTextureView depthView,
                           const Options& options, std::string& error) {
    stats_ = Stats{};
    if (!device_ || !layout_) {
        error = "debug prims not initialized";
        return false;
    }
    if (!target.encoder || !target.colorView || target.width == 0 || target.height == 0) {
        error = "debug prims render target is incomplete";
        return false;
    }
    const std::vector<DebugVertex>& verts = batch.vertices();
    if (verts.empty()) return true;

    const uint8_t depthMode = depthView ? (options.depthTest ? kDepthTested : kDepthAlways)
                                        : kNoDepth;
    const uint8_t blend = options.additive ? 1 : 0;
    WGPURenderPipeline pipeline = pipelineFor(target.format, depthMode, blend, 1, error);
    if (!pipeline) return false;
    if (!ensureVertexBuffer((uint64_t)verts.size() * sizeof(DebugVertex), error)) return false;
    wgpuQueueWriteBuffer(queue_, vbuf_, 0, verts.data(), verts.size() * sizeof(DebugVertex));
    wgpuQueueWriteBuffer(queue_, ubuf_, 0, &viewProj, sizeof viewProj);

    WGPURenderPassColorAttachment color = {};
    color.view = target.colorView;
    color.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
    color.loadOp = WGPULoadOp_Load;
    color.storeOp = WGPUStoreOp_Store;

    WGPURenderPassDepthStencilAttachment depth = {};
    depth.depthClearValue = 1.f;
    if (depthView) {
        depth.view = depthView;
        depth.depthLoadOp = WGPULoadOp_Load;
        depth.depthStoreOp = WGPUStoreOp_Store;
        depth.depthReadOnly = false;
        depth.stencilLoadOp = WGPULoadOp_Load;
        depth.stencilStoreOp = WGPUStoreOp_Store;
        depth.stencilReadOnly = false;
    }

    WGPURenderPassDescriptor passDesc = {};
    passDesc.colorAttachmentCount = 1;
    passDesc.colorAttachments = &color;
    passDesc.depthStencilAttachment = depthView ? &depth : nullptr;

    WGPURenderPassEncoder pass = wgpuCommandEncoderBeginRenderPass(target.encoder, &passDesc);
    if (!pass) {
        error = "debug cube render pass could not be started";
        return false;
    }
    wgpuRenderPassEncoderSetPipeline(pass, pipeline);
    wgpuRenderPassEncoderSetBindGroup(pass, 0, group_, 0, nullptr);
    applyViewport(pass, options);
    wgpuRenderPassEncoderSetVertexBuffer(pass, 0, vbuf_, 0, WGPU_WHOLE_SIZE);
    wgpuRenderPassEncoderDraw(pass, (uint32_t)verts.size(), 1, 0, 0);
    wgpuRenderPassEncoderEnd(pass);
    wgpuRenderPassEncoderRelease(pass);

    stats_.cubes = batch.cubes();
    stats_.vertices = verts.size();
    stats_.droppedVertices = batch.droppedVertices();
    stats_.passes = 1;
    return true;
}

bool DebugPrims::draw(const Target& target, const glm::mat4& viewProj,
                      const std::vector<DebugLine>& lines, WGPUTextureView depthView,
                      const Options& options, std::string& error) {
    staging_.clear();   // per-frame reuse: capacity is kept, the drop counter is not
    staging_.append(lines);
    return draw(target, viewProj, staging_, depthView, options, error);
}

bool DebugPrims::draw(const Target& target, const glm::mat4& viewProj,
                      const DebugLineBatch& batch, WGPUTextureView depthView,
                      const Options& options, std::string& error) {
    const bool ok = drawVertices(target, viewProj, batch.vertices(), depthView, options, error);
    // The batch knows about drops the trimmed vector cannot show (a whole box refused
    // for want of six vertices).
    if (ok) stats_.droppedVertices += batch.droppedVertices();
    return ok;
}

bool DebugPrims::draw(const Target& target, const glm::mat4& viewProj,
                      const std::vector<DebugLine>& lines, std::string& error) {
    return draw(target, viewProj, lines, nullptr, Options{}, error);
}

bool DebugPrims::draw(const Target& target, const glm::mat4& viewProj,
                      const DebugLineBatch& batch, std::string& error) {
    return draw(target, viewProj, batch, nullptr, Options{}, error);
}

}  // namespace render
