#pragma once
// The one place SDL and WebGPU meet: turning a window (native) or the SDL canvas
// (web) into a WGPUSurface. Kept apart from both layers so that neither has to
// know about the other.
#include <webgpu/webgpu.h>
#include <SDL3/SDL.h>

namespace plat {
WGPUSurface createSurface(WGPUInstance instance, SDL_Window* window);
}
