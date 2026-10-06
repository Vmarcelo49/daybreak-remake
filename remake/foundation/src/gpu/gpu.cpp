#include "gpu/gpu.h"

#include <cstdio>
#include <cstring>

#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>
#endif

namespace gpu {
namespace {

WGPUInstance g_instance = nullptr;

struct Waiter {
    bool        done   = false;
    WGPUAdapter adapter = nullptr;
    WGPUDevice  device  = nullptr;
};

std::string toString(WGPUStringView s) {
    return s.data ? std::string(s.data, s.length) : std::string();
}

// Both implementations dispatch AllowProcessEvents callbacks from
// wgpuInstanceProcessEvents; on the web the browser's own event loop must also
// run, which is what emscripten_sleep yields to (hence -sASYNCIFY at link time).
void waitFor(Waiter& w) {
    while (!w.done) {
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
        std::fprintf(stderr, "requestAdapter failed: %s\n", toString(message).c_str());
    }
}

void onDevice(WGPURequestDeviceStatus status, WGPUDevice device, WGPUStringView message,
              void* ud1, void*) {
    auto* w = static_cast<Waiter*>(ud1);
    w->done = true;
    if (status == WGPURequestDeviceStatus_Success) {
        w->device = device;
    } else {
        std::fprintf(stderr, "requestDevice failed: %s\n", toString(message).c_str());
    }
}

void onUncapturedError(WGPUDevice const*, WGPUErrorType type, WGPUStringView message, void*, void*) {
    std::fprintf(stderr, "[gpu] uncaptured error (%d): %s\n", (int)type, toString(message).c_str());
}

struct MapWaiter {
    bool done = false;
    bool ok   = false;
};

void onMapped(WGPUMapAsyncStatus status, WGPUStringView message, void* ud1, void*) {
    auto* w = static_cast<MapWaiter*>(ud1);
    w->done = true;
    w->ok = status == WGPUMapAsyncStatus_Success;
    if (!w->ok) std::fprintf(stderr, "[gpu] buffer map failed: %s\n", toString(message).c_str());
}

}  // namespace

const char* backendName(WGPUBackendType t) {
    switch (t) {
        case WGPUBackendType_Vulkan:   return "Vulkan";
        case WGPUBackendType_D3D12:    return "D3D12";
        case WGPUBackendType_Metal:    return "Metal";
        case WGPUBackendType_OpenGL:   return "OpenGL";
        case WGPUBackendType_OpenGLES: return "OpenGLES";
        case WGPUBackendType_WebGPU:   return "WebGPU(browser)";
        default:                       return "unknown";
    }
}

const char* presentModeName(WGPUPresentMode m) {
    switch (m) {
        case WGPUPresentMode_Fifo:        return "Fifo(vsync)";
        case WGPUPresentMode_FifoRelaxed: return "FifoRelaxed";
        case WGPUPresentMode_Immediate:   return "Immediate";
        case WGPUPresentMode_Mailbox:     return "Mailbox";
        default:                          return "?";
    }
}

bool createInstance(Context& ctx, std::string& error) {
    if (ctx.instance) return true;
    WGPUInstanceDescriptor instDesc = {};
    ctx.instance = wgpuCreateInstance(&instDesc);
    if (!ctx.instance) {
        error = "wgpuCreateInstance failed";
        return false;
    }
    g_instance = ctx.instance;
    return true;
}

bool createContext(Context& ctx, WGPUSurface surface, std::string& error) {
    // The instance has to exist before the surface (the surface is created from
    // it), so callers create it first; this keeps working if they do not.
    if (!createInstance(ctx, error)) return false;

    Waiter wa;
    WGPURequestAdapterOptions opts = {};
    opts.compatibleSurface = surface;
    opts.powerPreference = WGPUPowerPreference_HighPerformance;
#if defined(__linux__)
    // Linux asks for Vulkan by name, which is the backend every Linux verification in
    // this repo ran on (D2's evidence: RADV on Wayland) and the one the README requires
    // ("a Vulkan driver"). It is also the difference between an actionable failure and a
    // crash: with no Vulkan driver wgpu-native falls back to its GLES/EGL backend and
    // panics inside wgpu-hal (`gles/egl.rs:899` unwraps a None EGL display, observed with
    // VK_ICD_FILENAMES=/dev/null and no EGL vendor library), aborting the process before
    // any message can be printed. Asking for Vulkan makes that machine report "no usable
    // GPU adapter" plus the driver to install. Other targets keep the default backend set
    // (DX12/Metal), which is what their builds were verified with.
    opts.backendType = WGPUBackendType_Vulkan;
#endif
    WGPURequestAdapterCallbackInfo acb = {};
    acb.mode = WGPUCallbackMode_AllowProcessEvents;
    acb.callback = onAdapter;
    acb.userdata1 = &wa;
    wgpuInstanceRequestAdapter(ctx.instance, &opts, acb);
    waitFor(wa);
    if (!wa.adapter) {
        // User-facing: the packaged launcher surfaces this as the launch failure, so the
        // message names the likely cause and the next step instead of the WebGPU call
        // that returned nothing. A machine with no Vulkan driver (or a VM without GPU
        // passthrough) is by far the common case.
        error = surface
                    ? "no usable GPU adapter: this port needs a Vulkan-capable GPU and its "
                      "driver. Install or update your graphics driver (Mesa RADV/AMDVLK, "
                      "NVIDIA or Intel) and start the game from a desktop session with a "
                      "working Wayland or X11 display"
                    : "no usable GPU adapter: this port needs a Vulkan-capable GPU and its "
                      "driver. Install or update your graphics driver (Mesa RADV/AMDVLK, "
                      "NVIDIA or Intel), or install a software Vulkan driver (Mesa lavapipe)";
        return false;
    }
    ctx.adapter = wa.adapter;

    WGPUAdapterInfo info = {};
    if (wgpuAdapterGetInfo(ctx.adapter, &info) == WGPUStatus_Success) {
        ctx.adapterName = toString(info.device);
        if (ctx.adapterName.empty()) ctx.adapterName = toString(info.description);
        if (ctx.adapterName.empty()) {
            // Browsers redact device/description, so fall back to what is left.
            ctx.adapterName = toString(info.vendor);
            const std::string arch = toString(info.architecture);
            if (!arch.empty()) ctx.adapterName += ctx.adapterName.empty() ? arch : " " + arch;
        }
        ctx.backend = backendName(info.backendType);
    }

    Waiter wd;
    WGPUDeviceDescriptor devDesc = {};
    devDesc.uncapturedErrorCallbackInfo.callback = onUncapturedError;
    WGPURequestDeviceCallbackInfo dcb = {};
    dcb.mode = WGPUCallbackMode_AllowProcessEvents;
    dcb.callback = onDevice;
    dcb.userdata1 = &wd;
    wgpuAdapterRequestDevice(ctx.adapter, &devDesc, dcb);
    waitFor(wd);
    if (!wd.device) {
        error = "requestDevice failed";
        return false;
    }
    ctx.device = wd.device;
    ctx.queue = wgpuDeviceGetQueue(ctx.device);
    return ctx.queue != nullptr;
}

void destroyContext(Context& ctx) {
    if (ctx.queue) wgpuQueueRelease(ctx.queue);
    if (ctx.device) wgpuDeviceRelease(ctx.device);
    if (ctx.adapter) wgpuAdapterRelease(ctx.adapter);
    if (ctx.instance) wgpuInstanceRelease(ctx.instance);
    ctx = Context{};
}

bool configureSwapchain(Context& ctx, Swapchain& sc, uint32_t width, uint32_t height,
                        std::string& error) {
    WGPUSurfaceCapabilities caps = {};
    if (wgpuSurfaceGetCapabilities(sc.surface, ctx.adapter, &caps) != WGPUStatus_Success) {
        error = "wgpuSurfaceGetCapabilities failed";
        return false;
    }
    if (caps.formatCount == 0 || caps.presentModeCount == 0) {
        error = "surface reports no usable format or present mode";
        return false;
    }

    sc.formatCount = (int)caps.formatCount;
    sc.presentModeCount = (int)caps.presentModeCount;
    for (size_t i = 0; i < caps.presentModeCount; ++i)
        if (caps.presentModes[i] == WGPUPresentMode_Fifo) sc.supportsFifo = true;

    // Prefer a non-sRGB 8-bit format: the whole pipeline works in byte (gamma)
    // space — textures decode to raw bytes, lighting runs on those bytes, and
    // the D3D9 reference wrote them straight to its gamma backbuffer. An sRGB
    // swapchain gamma-encodes the image a SECOND time on present, pushing every
    // 3D pixel toward white, while offscreen RGBA8Unorm captures convert nothing
    // — correct captures, white live game (measured: RGBA8UnormSrgb on RADV).
    // RGBA8Unorm first so live matches captures; BGRA8Unorm second for backends
    // that only offer it; otherwise keep formats[0].
    sc.format = caps.formats[0];
    for (size_t i = 0; i < caps.formatCount; ++i) {
        if (caps.formats[i] == WGPUTextureFormat_RGBA8Unorm) {
            sc.format = caps.formats[i];
            break;
        }
    }
    if (sc.format != WGPUTextureFormat_RGBA8Unorm) {
        for (size_t i = 0; i < caps.formatCount; ++i) {
            if (caps.formats[i] == WGPUTextureFormat_BGRA8Unorm) {
                sc.format = caps.formats[i];
                break;
            }
        }
    }
    sc.presentMode = sc.supportsFifo ? WGPUPresentMode_Fifo : caps.presentModes[0];
    sc.width = width;
    sc.height = height;

    WGPUSurfaceConfiguration cfg = {};
    cfg.device = ctx.device;
    cfg.format = sc.format;
    cfg.usage = WGPUTextureUsage_RenderAttachment;
    cfg.width = width;
    cfg.height = height;
    cfg.alphaMode = caps.alphaModeCount ? caps.alphaModes[0] : WGPUCompositeAlphaMode_Auto;
    cfg.presentMode = sc.presentMode;
    wgpuSurfaceConfigure(sc.surface, &cfg);

    wgpuSurfaceCapabilitiesFreeMembers(caps);
    return true;
}

bool beginFrame(Context& ctx, Swapchain& sc, Frame& frame, std::string& error) {
    WGPUSurfaceTexture st = {};
    wgpuSurfaceGetCurrentTexture(sc.surface, &st);
    if (st.status != WGPUSurfaceGetCurrentTextureStatus_SuccessOptimal &&
        st.status != WGPUSurfaceGetCurrentTextureStatus_SuccessSuboptimal) {
        error = "surface texture not acquired (status " + std::to_string((int)st.status) + ")";
        return false;
    }
    frame.texture = st.texture;
    frame.view = wgpuTextureCreateView(st.texture, nullptr);
    frame.encoder = wgpuDeviceCreateCommandEncoder(ctx.device, nullptr);
    return true;
}

bool endFrame(Context& ctx, Swapchain& sc, Frame& frame) {
    WGPUCommandBuffer cmd = wgpuCommandEncoderFinish(frame.encoder, nullptr);
    wgpuQueueSubmit(ctx.queue, 1, &cmd);
    wgpuCommandBufferRelease(cmd);

    // The web has no present call: the browser composites the canvas during the
    // next animation frame, which SDL3's iterate callback is already driven by.
    // There, "presenting" is simply returning from the frame. emdawnwebgpu's
    // wgpuSurfacePresent is a stub that aborts, so it must not be reached.
#if defined(__EMSCRIPTEN__)
    const WGPUStatus presented = WGPUStatus_Success;
#elif defined(WEBGPU_BACKEND_WGPU)
    const WGPUStatus presented = wgpuSurfacePresent(sc.surface);
#else
    wgpuSurfacePresent(sc.surface);
    const WGPUStatus presented = WGPUStatus_Success;
#endif

    wgpuCommandEncoderRelease(frame.encoder);
    wgpuTextureViewRelease(frame.view);
    wgpuTextureRelease(frame.texture);
    frame = Frame{};
    return presented == WGPUStatus_Success;
}

WGPUShaderModule createShaderModule(WGPUDevice device, const char* wgsl) {
    // WGPUShaderSourceWGSL is the current spelling and is what wgpu-native v24/v29
    // and the Dawn family all expose; the older WGPUShaderModuleWGSLDescriptor name
    // is gone from recent headers. `code` is a string view here, not a C string.
    WGPUShaderSourceWGSL wgslDesc = {};
    wgslDesc.chain.sType = WGPUSType_ShaderSourceWGSL;
    wgslDesc.code = WGPUStringView{wgsl, WGPU_STRLEN};

    WGPUShaderModuleDescriptor desc = {};
    desc.nextInChain = &wgslDesc.chain;
    return wgpuDeviceCreateShaderModule(device, &desc);
}

WGPUBuffer createBuffer(WGPUDevice device, uint64_t size, WGPUBufferUsage usage, const void* data) {
    WGPUBufferDescriptor desc = {};
    desc.size = size;
    desc.usage = usage;
    desc.mappedAtCreation = data != nullptr;

    WGPUBuffer buffer = wgpuDeviceCreateBuffer(device, &desc);
    if (buffer && data) {
        void* dst = wgpuBufferGetMappedRange(buffer, 0, size);
        if (dst) std::memcpy(dst, data, size);
        wgpuBufferUnmap(buffer);
    }
    return buffer;
}

bool readBuffer(WGPUInstance instance, WGPUBuffer buffer, uint64_t offset, uint64_t size,
                std::vector<uint8_t>& out, std::string& error) {
    // The map is asynchronous, and the wait is the same "process events until the
    // callback fires" loop the adapter and device requests use — including the
    // emscripten_sleep that lets the browser's event loop run. That is the whole
    // reason this helper belongs in the gpu layer.
    if (!instance || !buffer || size == 0) {
        error = "readBuffer: no instance, no buffer or an empty range";
        return false;
    }

    MapWaiter mw;
    WGPUBufferMapCallbackInfo cb = {};
    cb.mode = WGPUCallbackMode_AllowProcessEvents;
    cb.callback = onMapped;
    cb.userdata1 = &mw;
    wgpuBufferMapAsync(buffer, WGPUMapMode_Read, offset, size, cb);

#if defined(__EMSCRIPTEN__)
    while (!mw.done) {
        wgpuInstanceProcessEvents(instance);
        emscripten_sleep(0);
    }
#else
    while (!mw.done) wgpuInstanceProcessEvents(instance);
#endif

    if (!mw.ok) {
        error = "buffer mapAsync failed";
        return false;
    }
    const void* mapped = wgpuBufferGetConstMappedRange(buffer, offset, size);
    if (!mapped) {
        error = "buffer range is not mapped";
        wgpuBufferUnmap(buffer);
        return false;
    }
    out.assign((const uint8_t*)mapped, (const uint8_t*)mapped + size);
    wgpuBufferUnmap(buffer);
    return true;
}

}  // namespace gpu
