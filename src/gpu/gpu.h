#pragma once
// GPU layer. webgpu.h only — no backend-specific header is ever included here,
// so swapping wgpu-native for Dawn (or adding a third implementation) stays a
// build-system decision rather than a code change.
#include <webgpu/webgpu.h>
#include <cstdint>
#include <string>
#include <vector>

namespace gpu {

struct Context {
    WGPUInstance instance = nullptr;
    WGPUAdapter  adapter  = nullptr;
    WGPUDevice   device   = nullptr;
    WGPUQueue    queue    = nullptr;
    std::string  backend;      // "Vulkan", "D3D12", "Metal", "WebGPU(browser)"
    std::string  adapterName;  // driver/device string, for logs and bug reports
};

// What the platform actually offers. Worth reporting rather than assuming: the
// web exposes exactly one present mode, and surface formats differ per backend.
struct Swapchain {
    WGPUSurface       surface        = nullptr;
    WGPUTextureFormat format         = WGPUTextureFormat_Undefined;
    WGPUPresentMode   presentMode    = WGPUPresentMode_Fifo;
    uint32_t          width          = 0;
    uint32_t          height         = 0;
    bool              supportsFifo   = false;
    int               formatCount    = 0;
    int               presentModeCount = 0;
};

struct Frame {
    WGPUTexture        texture = nullptr;
    WGPUTextureView    view    = nullptr;
    WGPUCommandEncoder encoder = nullptr;
};

// The surface is created from the instance, so instance creation is separate:
// createInstance -> plat::createSurface -> createContext.
bool createInstance(Context&, std::string& error);
bool createContext(Context&, WGPUSurface, std::string& error);
void destroyContext(Context&);

// Configures FIFO when the platform has it — that is the cap-at-refresh behaviour
// the original game has, and on the web it is the only mode there is.
bool configureSwapchain(Context&, Swapchain&, uint32_t width, uint32_t height, std::string& error);

bool beginFrame(Context&, Swapchain&, Frame&, std::string& error);
bool endFrame(Context&, Swapchain&, Frame&);

WGPUShaderModule createShaderModule(WGPUDevice, const char* wgsl);
WGPUBuffer       createBuffer(WGPUDevice, uint64_t size, WGPUBufferUsage usage, const void* data);

// Copies a buffer's [offset, offset + size) range into host memory. The wait is the
// same AllowProcessEvents loop the adapter and device requests use — which on the web
// also has to yield to the browser's event loop — so it lives here rather than being
// re-implemented by every caller that reads a texture back.
bool readBuffer(WGPUInstance, WGPUBuffer, uint64_t offset, uint64_t size,
                std::vector<uint8_t>& out, std::string& error);

const char* presentModeName(WGPUPresentMode);
const char* backendName(WGPUBackendType);

}  // namespace gpu
