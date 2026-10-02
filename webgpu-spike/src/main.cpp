// webgpu-spike — proves (or disproves) the proposed groundwork on every target.
//
// Native: SDL3 window -> sdl3webgpu surface -> wgpu-native/Dawn -> configure -> render -> present
// Web:    SDL3 canvas -> emdawnwebgpu (the browser's own WebGPU)
//
// What it reports, because these are the things a groundwork has to guarantee:
//   * which implementation and backend actually ran (wgpu-native vs Dawn, Vulkan vs Metal...)
//   * the surface's real capabilities: formats, present modes, alpha modes
//   * whether FIFO (the vsync mode that caps at the display refresh, like the original game)
//     is available, and how long N presented frames actually took
//
// It deliberately uses only webgpu.h — no Dawn- or wgpu-specific calls — so the same source
// compiles on all targets. Zero-initialisation (`= {}`) is used rather than the newer
// WGPU_*_INIT macros, which only exist in recent headers.

#include <webgpu/webgpu.h>

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include <SDL3/SDL.h>
#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>   // emscripten_request_animation_frame_loop: the web "present"
#else
#include "sdl3webgpu.h"
#endif

namespace {

const char* backendName(WGPUBackendType t) {
    switch (t) {
        case WGPUBackendType_Vulkan: return "Vulkan";
        case WGPUBackendType_D3D12: return "D3D12";
        case WGPUBackendType_Metal: return "Metal";
        case WGPUBackendType_OpenGL: return "OpenGL";
        case WGPUBackendType_OpenGLES: return "OpenGLES";
        case WGPUBackendType_WebGPU: return "WebGPU(browser)";
        default: return "other/none";
    }
}

const char* presentModeName(WGPUPresentMode m) {
    switch (m) {
        case WGPUPresentMode_Fifo: return "Fifo(vsync)";
        case WGPUPresentMode_FifoRelaxed: return "FifoRelaxed";
        case WGPUPresentMode_Immediate: return "Immediate";
        case WGPUPresentMode_Mailbox: return "Mailbox";
        default: return "?";
    }
}

std::string sv(WGPUStringView s) {
    return s.data ? std::string(s.data, s.length) : std::string();
}

// ---- async plumbing ----------------------------------------------------------------
// On native the futures are driven by wgpuInstanceProcessEvents. On the web there is no
// such call: the browser drives the callbacks, so the web build uses Asyncify
// (-sASYNCIFY) and emscripten_sleep yields to the event loop while we wait.
struct Waiter {
    bool done = false;
    WGPUAdapter adapter = nullptr;
    WGPUDevice device = nullptr;
};

WGPUInstance g_instance = nullptr;

void waitFor(Waiter& w) {
    while (!w.done) {
        // Both implementations dispatch WGPUCallbackMode_AllowProcessEvents callbacks from
        // wgpuInstanceProcessEvents, so that call is needed everywhere. On the web the
        // browser's own event loop also has to run for the underlying JS promise to
        // settle, which is what emscripten_sleep(0) yields to (requires -sASYNCIFY).
        wgpuInstanceProcessEvents(g_instance);
#if defined(__EMSCRIPTEN__)
        emscripten_sleep(0);
#endif
    }
}

void onAdapter(WGPURequestAdapterStatus status, WGPUAdapter adapter, WGPUStringView message,
               void* ud1, void*) {
    auto* w = static_cast<Waiter*>(ud1);
    w->done = true;
    if (status == WGPURequestAdapterStatus_Success) {
        w->adapter = adapter;
    } else {
        std::fprintf(stderr, "requestAdapter failed (%d): %s\n", (int)status, sv(message).c_str());
    }
}

void onDevice(WGPURequestDeviceStatus status, WGPUDevice device, WGPUStringView message,
              void* ud1, void*) {
    auto* w = static_cast<Waiter*>(ud1);
    w->done = true;
    if (status == WGPURequestDeviceStatus_Success) {
        w->device = device;
    } else {
        std::fprintf(stderr, "requestDevice failed (%d): %s\n", (int)status, sv(message).c_str());
    }
}

void onUncapturedError(WGPUDevice const*, WGPUErrorType type, WGPUStringView message, void*, void*) {
    std::fprintf(stderr, "[wgpu error %d] %s\n", (int)type, sv(message).c_str());
}

// ---- surface -----------------------------------------------------------------------
#if defined(__EMSCRIPTEN__)
WGPUSurface createSurface(WGPUInstance instance) {
    // The browser has no window handle: the surface comes from the canvas element. SDL3
    // creates a canvas with this id, so the two line up.
    // The emscripten port prefixes this struct with "Emscripten" (it is the one Dawn
    // extension that is emscripten-specific rather than backend-generic).
    WGPUEmscriptenSurfaceSourceCanvasHTMLSelector fromCanvas = {};
    fromCanvas.chain.sType = WGPUSType_EmscriptenSurfaceSourceCanvasHTMLSelector;
    fromCanvas.selector = WGPUStringView{"#canvas", WGPU_STRLEN};

    WGPUSurfaceDescriptor desc = {};
    desc.nextInChain = &fromCanvas.chain;
    return wgpuInstanceCreateSurface(instance, &desc);
}
#else
WGPUSurface createSurface(WGPUInstance instance, SDL_Window* window) {
    return SDL_GetWGPUSurface(instance, window);
}
#endif

// Fill a one-colour frame.
bool drawFrame(WGPUDevice device, WGPUQueue queue, WGPUSurface surface) {
    WGPUSurfaceTexture st = {};
    wgpuSurfaceGetCurrentTexture(surface, &st);
    // Both wgpu-native v24 and v29 spell this SuccessOptimal/SuccessSuboptimal; the
    // suboptimal case still presents, so accept either.
    if (st.status != WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal &&
        st.status != WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal) {
        std::fprintf(stderr, "getCurrentTexture status %d\n", (int)st.status);
        return false;
    }
    WGPUTextureView view = wgpuTextureCreateView(st.texture, nullptr);

    WGPURenderPassColorAttachment color = {};
    color.view = view;
    color.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
    color.loadOp = WGPULoadOp_Clear;
    color.storeOp = WGPUStoreOp_Store;
    color.clearValue = WGPUColor{0.0, 0.0, 0.0, 1.0};

    WGPURenderPassDescriptor pass = {};
    pass.colorAttachmentCount = 1;
    pass.colorAttachments = &color;

    WGPUCommandEncoderDescriptor encDesc = {};
    WGPUCommandEncoder enc = wgpuDeviceCreateCommandEncoder(device, &encDesc);
    WGPURenderPassEncoder rp = wgpuCommandEncoderBeginRenderPass(enc, &pass);
    wgpuRenderPassEncoderEnd(rp);
    WGPUCommandBuffer cmd = wgpuCommandEncoderFinish(enc, nullptr);
    wgpuQueueSubmit(queue, 1, &cmd);
    wgpuCommandBufferRelease(cmd);
    wgpuRenderPassEncoderRelease(rp);
    wgpuCommandEncoderRelease(enc);

    // Source-level difference between the implementations: wgpu-native returns a status
    // from wgpuSurfacePresent, the Dawn family (Dawn native and emdawnwebgpu) returns void
    // and reports present failures through the device error callback instead. This is what
    // the distribution's WEBGPU_BACKEND_* defines are for — one #if per real difference.
#if defined(WEBGPU_BACKEND_WGPU)
    const bool presented = wgpuSurfacePresent(surface) == WGPUStatus_Success;
#else
    wgpuSurfacePresent(surface);
    const bool presented = true;
#endif
    wgpuTextureViewRelease(view);
    wgpuTextureRelease(st.texture);
    return presented;
}

// On the web there is no present call at all: the browser composites the canvas during
// the next animation frame, so the frame loop — not a present — is what paces the app.
// emdawnwebgpu reports exactly this: "wgpuSurfacePresent is unsupported (use
// requestAnimationFrame via html5.h instead)".
void drawFrameNoPresent(WGPUDevice device, WGPUQueue queue, WGPUSurface surface) {
    WGPUSurfaceTexture st = {};
    wgpuSurfaceGetCurrentTexture(surface, &st);
    if (st.status != WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal &&
        st.status != WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal)
        return;
    WGPUTextureView view = wgpuTextureCreateView(st.texture, nullptr);
    WGPURenderPassColorAttachment color = {};
    color.view = view;
    color.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
    color.loadOp = WGPULoadOp_Clear;
    color.storeOp = WGPUStoreOp_Store;
    color.clearValue = WGPUColor{0.0, 0.0, 0.0, 1.0};
    WGPURenderPassDescriptor pass = {};
    pass.colorAttachmentCount = 1;
    pass.colorAttachments = &color;
    WGPUCommandEncoder enc = wgpuDeviceCreateCommandEncoder(device, nullptr);
    WGPURenderPassEncoder rp = wgpuCommandEncoderBeginRenderPass(enc, &pass);
    wgpuRenderPassEncoderEnd(rp);
    WGPUCommandBuffer cmd = wgpuCommandEncoderFinish(enc, nullptr);
    wgpuQueueSubmit(queue, 1, &cmd);
    wgpuCommandBufferRelease(cmd);
    wgpuRenderPassEncoderRelease(rp);
    wgpuCommandEncoderRelease(enc);
    wgpuTextureViewRelease(view);
    wgpuTextureRelease(st.texture);
}

#if defined(__EMSCRIPTEN__)
struct WebLoop {
    WGPUDevice device = nullptr;
    WGPUQueue queue = nullptr;
    WGPUSurface surface = nullptr;
    int target = 1, done = 0;
};
WebLoop g_web;

// Returning true keeps the rAF loop running; the browser fires it once per display frame,
// which is the web equivalent of the original game's refresh-rate cap.
bool webFrame(double, void*) {
    drawFrameNoPresent(g_web.device, g_web.queue, g_web.surface);
    if (++g_web.done >= g_web.target) {
        std::printf("rendered %d/%d animation frames (the browser presents them)\n", g_web.done,
                    g_web.target);
        std::printf("RESULT: %s\n", g_web.done == g_web.target ? "ok" : "FAILED");
        return false;
    }
    return true;
}
#endif

}  // namespace

int main(int argc, char** argv) {
    int frames = 1;
    for (int i = 1; i < argc; ++i)
        if (std::strncmp(argv[i], "--frames=", 9) == 0) frames = std::atoi(argv[i] + 9);

    std::printf("=== webgpu-spike ===\n");

    // SDL3 on every target. On the web this creates the <canvas> that the WebGPU
    // surface is then bound to, which is why the same call works on both.
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("webgpu-spike", 640, 360, 0);
    if (!window) {
        std::fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        return 1;
    }
#if defined(__EMSCRIPTEN__)
    std::printf("SDL3 ready (emscripten canvas)\n");
#else
    std::printf("SDL3 video driver: %s\n", SDL_GetCurrentVideoDriver());
#endif

    WGPUInstanceDescriptor instDesc = {};
    g_instance = wgpuCreateInstance(&instDesc);
    if (!g_instance) { std::fprintf(stderr, "wgpuCreateInstance failed\n"); return 1; }

#if defined(__EMSCRIPTEN__)
    WGPUSurface surface = createSurface(g_instance);
#else
    WGPUSurface surface = createSurface(g_instance, window);
#endif
    if (!surface) { std::fprintf(stderr, "surface creation failed\n"); return 1; }
    std::printf("surface created: %p\n", (void*)surface);

    // Adapter, asked for one that can present to this surface.
    Waiter wa;
    WGPURequestAdapterOptions opts = {};
    opts.compatibleSurface = surface;
    opts.powerPreference = WGPUPowerPreference_HighPerformance;
    WGPURequestAdapterCallbackInfo acb = {};
    acb.mode = WGPUCallbackMode_AllowProcessEvents;
    acb.callback = onAdapter;
    acb.userdata1 = &wa;
    wgpuInstanceRequestAdapter(g_instance, &opts, acb);
    waitFor(wa);
    if (!wa.adapter) return 1;

    WGPUAdapterInfo info = {};
    if (wgpuAdapterGetInfo(wa.adapter, &info) == WGPUStatus_Success) {
        std::printf("adapter: %s | %s | backend=%s type=%d\n",
                    sv(info.device).c_str(), sv(info.description).c_str(),
                    backendName(info.backendType), (int)info.adapterType);
    }

    Waiter wd;
    WGPUDeviceDescriptor devDesc = {};
    devDesc.uncapturedErrorCallbackInfo.callback = onUncapturedError;
    WGPURequestDeviceCallbackInfo dcb = {};
    dcb.mode = WGPUCallbackMode_AllowProcessEvents;
    dcb.callback = onDevice;
    dcb.userdata1 = &wd;
    wgpuAdapterRequestDevice(wa.adapter, &devDesc, dcb);
    waitFor(wd);
    if (!wd.device) return 1;
    WGPUQueue queue = wgpuDeviceGetQueue(wd.device);
    std::printf("device + queue ready\n");

    // Surface capabilities: formats and present modes the platform actually offers.
    WGPUSurfaceCapabilities caps = {};
    if (wgpuSurfaceGetCapabilities(surface, wa.adapter, &caps) != WGPUStatus_Success) {
        std::fprintf(stderr, "surface capabilities unavailable\n");
        return 1;
    }
    std::printf("surface formats (%zu):", caps.formatCount);
    for (size_t i = 0; i < caps.formatCount && i < 6; ++i)
        std::printf(" %d", (int)caps.formats[i]);
    std::printf("\npresent modes (%zu):", caps.presentModeCount);
    bool hasFifo = false;
    for (size_t i = 0; i < caps.presentModeCount; ++i) {
        std::printf(" %s", presentModeName(caps.presentModes[i]));
        if (caps.presentModes[i] == WGPUPresentMode_Fifo) hasFifo = true;
    }
    std::printf("\nFIFO (refresh-rate cap) available: %s\n", hasFifo ? "yes" : "NO");
    if (caps.formatCount == 0) { std::fprintf(stderr, "no surface formats\n"); return 1; }

    int w = 640, h = 360;
    SDL_GetWindowSizeInPixels(window, &w, &h);

    WGPUSurfaceConfiguration cfg = {};
    cfg.device = wd.device;
    cfg.format = caps.formats[0];
    cfg.usage = WGPUTextureUsage_RenderAttachment;
    cfg.width = (uint32_t)w;
    cfg.height = (uint32_t)h;
    cfg.alphaMode = caps.alphaModeCount ? caps.alphaModes[0] : WGPUCompositeAlphaMode_Auto;
    cfg.presentMode = hasFifo ? WGPUPresentMode_Fifo : caps.presentModes[0];
    wgpuSurfaceConfigure(surface, &cfg);
    std::printf("configured %dx%d format=%d presentMode=%s\n", w, h, (int)cfg.format,
                presentModeName(cfg.presentMode));

    // Present a few frames and time them. Under FIFO this is where the display's refresh
    // rate becomes the frame cap; on a headless X server there is nothing to sync to, so
    // treat the number as "the loop works", not as a frame-rate measurement.
#if defined(__EMSCRIPTEN__)
    g_web.device = wd.device;
    g_web.queue = queue;
    g_web.surface = surface;
    g_web.target = frames;
    std::printf("starting rAF-driven frame loop for %d frames\n", frames);
    emscripten_request_animation_frame_loop(webFrame, nullptr);
    return 0;                       // the browser drives the rest
#else
    auto t0 = std::chrono::steady_clock::now();
    int ok = 0;
    for (int i = 0; i < frames; ++i) {
        if (drawFrame(wd.device, queue, surface)) ++ok;
        SDL_PumpEvents();
    }
    auto t1 = std::chrono::steady_clock::now();
    double ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
    std::printf("presented %d/%d frames in %.1f ms (%.2f ms/frame)\n", ok, frames, ms,
                frames ? ms / frames : 0.0);

    std::printf("RESULT: %s\n", ok == frames ? "ok" : "FAILED");

#if !defined(__EMSCRIPTEN__)
    wgpuQueueRelease(queue);
    wgpuDeviceRelease(wd.device);
    wgpuAdapterRelease(wa.adapter);
    wgpuSurfaceRelease(surface);
    wgpuInstanceRelease(g_instance);
    SDL_DestroyWindow(window);
    SDL_Quit();
#endif
    return ok == frames ? 0 : 1;
#endif
}
