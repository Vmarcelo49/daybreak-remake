// Foundation demo: SDL3 window + WebGPU, one code path for Linux, Windows and web.
//
// It exists to prove the multi-platform plumbing, so it deliberately does the
// things a real frame needs rather than just clearing the screen: a vertex and
// uniform buffer, a pipeline built from embedded WGSL, one draw per frame, and a
// variable per-frame delta driving the animation. On the web the same
// SDL_AppIterate callback is fired once per animation frame by the browser.

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "gpu/gpu.h"
#include "platform/platform.h"
#include "platform/surface.h"
#include "shaders/demo_wgsl.h"

namespace {

struct Mat4 {
    float m[16];
};

// Column-major, matching WGSL's mat4x4<f32>.
Mat4 rotationZ(float radians, float scale) {
    const float c = std::cos(radians) * scale;
    const float s = std::sin(radians) * scale;
    return Mat4{{c, s, 0.f, 0.f,
                 -s, c, 0.f, 0.f,
                 0.f, 0.f, 1.f, 0.f,
                 0.f, 0.f, 0.f, 1.f}};
}

struct App {
    SDL_Window*        window = nullptr;
    gpu::Context       ctx;
    gpu::Swapchain     sc;
    WGPURenderPipeline pipeline = nullptr;
    WGPUBindGroup      bindGroup = nullptr;
    WGPUBuffer         vertexBuffer = nullptr;
    WGPUBuffer         uniformBuffer = nullptr;

    double   startTime = 0.0;
    double   lastTime = 0.0;
    double   deltaSum = 0.0;
    double   deltaMin = 1e30;
    double   deltaMax = 0.0;
    uint64_t frames = 0;
    int      maxFrames = 0;  // 0 = until the window is closed
    float    spin = 0.0f;

    std::string error;
};

// Interleaved position (3f) + colour (3f).
const float kVertices[] = {
    0.00f,  0.62f, 0.0f, 1.00f, 0.35f, 0.25f,
   -0.58f, -0.52f, 0.0f, 0.25f, 0.90f, 0.45f,
    0.58f, -0.52f, 0.0f, 0.30f, 0.55f, 1.00f,
};

bool buildPipeline(App& app) {
    WGPUShaderModule shader = gpu::createShaderModule(app.ctx.device, shaders::kDemoWGSL);
    if (!shader) {
        app.error = "shader module creation failed";
        return false;
    }

    WGPUVertexAttribute attrs[2] = {};
    attrs[0].format = WGPUVertexFormat_Float32x3;
    attrs[0].offset = 0;
    attrs[0].shaderLocation = 0;
    attrs[1].format = WGPUVertexFormat_Float32x3;
    attrs[1].offset = 3 * sizeof(float);
    attrs[1].shaderLocation = 1;

    WGPUVertexBufferLayout vbl = {};
    vbl.arrayStride = 6 * sizeof(float);
    vbl.stepMode = WGPUVertexStepMode_Vertex;
    vbl.attributeCount = 2;
    vbl.attributes = attrs;

    WGPUBindGroupLayoutEntry entry = {};
    entry.binding = 0;
    entry.visibility = WGPUShaderStage_Vertex;
    entry.buffer.type = WGPUBufferBindingType_Uniform;
    entry.buffer.minBindingSize = 64;

    WGPUBindGroupLayoutDescriptor bglDesc = {};
    bglDesc.entryCount = 1;
    bglDesc.entries = &entry;
    WGPUBindGroupLayout bgl = wgpuDeviceCreateBindGroupLayout(app.ctx.device, &bglDesc);

    WGPUPipelineLayoutDescriptor plDesc = {};
    plDesc.bindGroupLayoutCount = 1;
    plDesc.bindGroupLayouts = &bgl;
    WGPUPipelineLayout layout = wgpuDeviceCreatePipelineLayout(app.ctx.device, &plDesc);

    WGPUColorTargetState target = {};
    target.format = app.sc.format;
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
    fs.module = shader;
    fs.entryPoint = WGPUStringView{"fs_main", WGPU_STRLEN};
    fs.targetCount = 1;
    fs.targets = &target;

    WGPURenderPipelineDescriptor rpd = {};
    rpd.layout = layout;
    rpd.vertex.module = shader;
    rpd.vertex.entryPoint = WGPUStringView{"vs_main", WGPU_STRLEN};
    rpd.vertex.bufferCount = 1;
    rpd.vertex.buffers = &vbl;
    rpd.primitive.topology = WGPUPrimitiveTopology_TriangleList;
    rpd.primitive.frontFace = WGPUFrontFace_CCW;
    rpd.primitive.cullMode = WGPUCullMode_None;
    rpd.multisample.count = 1;
    rpd.multisample.mask = 0xFFFFFFFFu;
    rpd.fragment = &fs;

    app.pipeline = wgpuDeviceCreateRenderPipeline(app.ctx.device, &rpd);

    WGPUBindGroupEntry bgEntry = {};
    bgEntry.binding = 0;
    bgEntry.buffer = app.uniformBuffer;
    bgEntry.offset = 0;
    bgEntry.size = 64;
    WGPUBindGroupDescriptor bgDesc = {};
    bgDesc.layout = bgl;
    bgDesc.entryCount = 1;
    bgDesc.entries = &bgEntry;
    app.bindGroup = wgpuDeviceCreateBindGroup(app.ctx.device, &bgDesc);

    wgpuPipelineLayoutRelease(layout);
    wgpuBindGroupLayoutRelease(bgl);
    wgpuShaderModuleRelease(shader);

    if (!app.pipeline || !app.bindGroup) {
        app.error = "pipeline creation failed";
        return false;
    }
    return true;
}

void report(App& app) {
    const double elapsed = plat::now() - app.startTime;
    const double avg = app.frames ? app.deltaSum / (double)app.frames : 0.0;
    std::printf("\n-- frame timing (variable delta, no fixed step) --\n");
    std::printf("frames      : %llu in %.3f s\n", (unsigned long long)app.frames, elapsed);
    std::printf("delta avg   : %.3f ms (%.1f fps)\n", avg * 1000.0, avg > 0 ? 1.0 / avg : 0.0);
    std::printf("delta min   : %.3f ms\n", app.deltaMin * 1000.0);
    std::printf("delta max   : %.3f ms\n", app.deltaMax * 1000.0);
    std::printf("RESULT: %s\n", app.error.empty() ? "ok" : app.error.c_str());
}

void teardown(App& app) {
    if (app.bindGroup) wgpuBindGroupRelease(app.bindGroup);
    if (app.pipeline) wgpuRenderPipelineRelease(app.pipeline);
    if (app.vertexBuffer) wgpuBufferRelease(app.vertexBuffer);
    if (app.uniformBuffer) wgpuBufferRelease(app.uniformBuffer);
    if (app.sc.surface) wgpuSurfaceRelease(app.sc.surface);
    gpu::destroyContext(app.ctx);
    if (app.window) SDL_DestroyWindow(app.window);
    plat::shutdown();
}

}  // namespace

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
    auto* app = new App();
    *appstate = app;

    for (int i = 1; i < argc; ++i)
        if (std::strncmp(argv[i], "--frames=", 9) == 0)
            app->maxFrames = std::atoi(argv[i] + 9);

    if (!plat::init(app->error)) return SDL_APP_FAILURE;

    app->window = plat::createWindow("daybreak foundation", 960, 540, app->error);
    if (!app->window) return SDL_APP_FAILURE;

    // instance -> surface -> adapter/device: the surface has to exist before the
    // adapter is chosen, because it is requested as "compatible with" it.
    if (!gpu::createInstance(app->ctx, app->error)) return SDL_APP_FAILURE;
    app->sc.surface = plat::createSurface(app->ctx.instance, app->window);
    if (!app->sc.surface) {
        app->error = "surface creation failed";
        return SDL_APP_FAILURE;
    }
    if (!gpu::createContext(app->ctx, app->sc.surface, app->error)) return SDL_APP_FAILURE;

    int w = 960, h = 540;
    SDL_GetWindowSizeInPixels(app->window, &w, &h);
    if (!gpu::configureSwapchain(app->ctx, app->sc, (uint32_t)w, (uint32_t)h, app->error))
        return SDL_APP_FAILURE;

    std::printf("=== daybreak foundation ===\n");
    std::printf("video driver : %s\n", plat::videoDriver());
    std::printf("adapter      : %s [%s]\n", app->ctx.adapterName.c_str(), app->ctx.backend.c_str());
    std::printf("surface      : %dx%d, %d format(s), %d present mode(s), fifo=%s\n", w, h,
                app->sc.formatCount, app->sc.presentModeCount, app->sc.supportsFifo ? "yes" : "no");
    std::printf("present mode : %s\n", gpu::presentModeName(app->sc.presentMode));

    app->vertexBuffer = gpu::createBuffer(app->ctx.device, sizeof(kVertices),
                                          WGPUBufferUsage_Vertex | WGPUBufferUsage_CopyDst,
                                          kVertices);
    app->uniformBuffer = gpu::createBuffer(app->ctx.device, 64,
                                           WGPUBufferUsage_Uniform | WGPUBufferUsage_CopyDst,
                                           nullptr);
    if (!app->vertexBuffer || !app->uniformBuffer) {
        app->error = "buffer creation failed";
        return SDL_APP_FAILURE;
    }
    if (!buildPipeline(*app)) return SDL_APP_FAILURE;

    app->startTime = app->lastTime = plat::now();
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    auto* app = static_cast<App*>(appstate);

    // The whole frame model, in three lines: real elapsed time in, no fixed step,
    // no accumulator. Present pacing is the swapchain's job (FIFO).
    const double now = plat::now();
    const double delta = now - app->lastTime;
    app->lastTime = now;
    if (app->frames > 0) {  // skip the first sample: it includes setup time
        app->deltaSum += delta;
        if (delta < app->deltaMin) app->deltaMin = delta;
        if (delta > app->deltaMax) app->deltaMax = delta;
    }

    app->spin += (float)delta * 1.2f;
    const Mat4 transform = rotationZ(app->spin, 1.0f);
    wgpuQueueWriteBuffer(app->ctx.queue, app->uniformBuffer, 0, transform.m, sizeof(transform.m));

    gpu::Frame frame;
    if (!gpu::beginFrame(app->ctx, app->sc, frame, app->error)) {
        // A lost/outdated surface is recoverable in principle; for the foundation
        // demo it is enough to stop cleanly rather than spin on a broken swapchain.
        return SDL_APP_FAILURE;
    }

    WGPURenderPassColorAttachment color = {};
    color.view = frame.view;
    color.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
    color.loadOp = WGPULoadOp_Clear;
    color.storeOp = WGPUStoreOp_Store;
    color.clearValue = WGPUColor{0.06, 0.07, 0.09, 1.0};

    WGPURenderPassDescriptor pass = {};
    pass.colorAttachmentCount = 1;
    pass.colorAttachments = &color;

    WGPURenderPassEncoder rp = wgpuCommandEncoderBeginRenderPass(frame.encoder, &pass);
    wgpuRenderPassEncoderSetPipeline(rp, app->pipeline);
    wgpuRenderPassEncoderSetBindGroup(rp, 0, app->bindGroup, 0, nullptr);
    wgpuRenderPassEncoderSetVertexBuffer(rp, 0, app->vertexBuffer, 0, WGPU_WHOLE_SIZE);
    wgpuRenderPassEncoderDraw(rp, 3, 1, 0, 0);
    wgpuRenderPassEncoderEnd(rp);
    wgpuRenderPassEncoderRelease(rp);

    if (!gpu::endFrame(app->ctx, app->sc, frame)) return SDL_APP_FAILURE;

    ++app->frames;
    if (app->maxFrames > 0 && app->frames >= (uint64_t)app->maxFrames) return SDL_APP_SUCCESS;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    auto* app = static_cast<App*>(appstate);
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
        case SDL_EVENT_KEY_DOWN:
            if (event->key.key == SDLK_ESCAPE) return SDL_APP_SUCCESS;
            break;
        case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED: {
            // A resized window needs the swapchain reconfigured, not just a new
            // viewport: the surface's back buffers are sized at configure time.
            const uint32_t w = (uint32_t)event->window.data1;
            const uint32_t h = (uint32_t)event->window.data2;
            if (w && h && !gpu::configureSwapchain(app->ctx, app->sc, w, h, app->error))
                return SDL_APP_FAILURE;
            break;
        }
        default:
            break;
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult) {
    auto* app = static_cast<App*>(appstate);
    if (!app) return;
    report(*app);
    teardown(*app);
    delete app;
}
