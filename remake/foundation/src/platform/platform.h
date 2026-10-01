#pragma once
// Platform layer. SDL3 only — nothing here knows WebGPU exists; the single seam
// between the two is platform/surface.h.
#include <SDL3/SDL.h>
#include <string>

namespace plat {

bool        init(std::string& error);
void        shutdown();
SDL_Window* createWindow(const char* title, int w, int h, std::string& error);

// Monotonic seconds. The game's frame model is "one variable delta per frame,
// capped by the display refresh"; nothing in the foundation imposes a fixed step.
double      now();
const char* videoDriver();

}  // namespace plat
