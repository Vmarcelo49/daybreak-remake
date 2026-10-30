#include "platform/surface.h"

#if defined(__EMSCRIPTEN__)
WGPUSurface plat::createSurface(WGPUInstance instance, SDL_Window*) {
    // The browser has no window handle: the surface comes from the canvas element,
    // and the emscripten port spells this struct with an "Emscripten" prefix.
    WGPUEmscriptenSurfaceSourceCanvasHTMLSelector fromCanvas = {};
    fromCanvas.chain.sType = WGPUSType_EmscriptenSurfaceSourceCanvasHTMLSelector;
    fromCanvas.selector = WGPUStringView{"#canvas", WGPU_STRLEN};

    WGPUSurfaceDescriptor desc = {};
    desc.nextInChain = &fromCanvas.chain;
    return wgpuInstanceCreateSurface(instance, &desc);
}
#else
#include "sdl3webgpu.h"
WGPUSurface plat::createSurface(WGPUInstance instance, SDL_Window* window) {
    return SDL_GetWGPUSurface(instance, window);
}
#endif
