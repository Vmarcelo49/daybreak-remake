#include "platform/platform.h"

#include <chrono>

namespace plat {

bool init(std::string& error) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        // User-facing: the launcher prints this as the launch failure, so keep SDL's own
        // reason and add the one next step a missing display has.
        error = std::string("could not start the video system (") + SDL_GetError() +
                "). Start the game from a desktop session with a working Wayland or X11 "
                "display";
        return false;
    }
    return true;
}

void shutdown() { SDL_Quit(); }

SDL_Window* createWindow(const char* title, int w, int h, std::string& error) {
    SDL_Window* window = SDL_CreateWindow(title, w, h, SDL_WINDOW_RESIZABLE);
    if (!window)
        error = std::string("could not open a game window (") + SDL_GetError() +
                "). Start the game from a desktop session with a working Wayland or X11 "
                "display";
    return window;
}

double now() {
    // steady_clock rather than SDL_GetPerformanceCounter: SDL3's Emscripten build
    // leaves SDL_CLOCK_GETTIME off and falls back to gettimeofday(), which quantises
    // deltas to whole milliseconds — at 60 fps that snaps every frame between 16 and
    // 17 ms. std::chrono keeps sub-millisecond resolution on every target here,
    // which a variable-delta frame loop actually depends on.
    using clock = std::chrono::steady_clock;
    static const clock::time_point origin = clock::now();
    return std::chrono::duration<double>(clock::now() - origin).count();
}

const char* videoDriver() { return SDL_GetCurrentVideoDriver(); }

}  // namespace plat
