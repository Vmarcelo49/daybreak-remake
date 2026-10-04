#include "input/input_backend.h"
#include <SDL3/SDL.h>
#include <cstdio>

int main() {
    int failures = 0;
    auto check = [&](bool value, const char* name) {
        if (!value) { std::fprintf(stderr,"FAIL %s\n",name); ++failures; }
    };
    if (!SDL_Init(SDL_INIT_EVENTS)) {
        std::fprintf(stderr,"SDL events: %s\n",SDL_GetError());
        return 1;
    }
    {
        fnd::input::Backend backend;
        if (!backend.init()) { SDL_Quit(); return 1; }
        using namespace fnd::input;
        check(backend.set_keyboard_binding(Jump,SDL_SCANCODE_F),"runtime rebind accepts new key");
        backend.note_key(SDL_SCANCODE_Z,true);
        backend.poll();
        check(!backend.player(0).down[Jump],"former confirm key no longer activates rebound action");
        backend.note_key(SDL_SCANCODE_F,true);
        backend.poll();
        check(backend.player(0).just_pressed[Jump],"new confirm binding produces an edge");
        backend.suppress_key(SDL_SCANCODE_F);
        backend.poll();
        check(!backend.player(0).down[Jump],"capture consumes its held key");
        backend.note_key(SDL_SCANCODE_F,true);
        backend.poll();
        check(!backend.player(0).just_pressed[Jump] && !backend.player(0).down[Jump],"key repeat cannot rearm capture");
        backend.poll();
        check(!backend.player(0).down[Jump],"suppression persists while held");
        backend.note_key(SDL_SCANCODE_F,false);
        backend.poll();
        backend.note_key(SDL_SCANCODE_F,true);
        backend.poll();
        check(backend.player(0).just_pressed[Jump],"release then repress enables rebound key");
        backend.poll();
        check(backend.player(0).down[Jump] && !backend.player(0).just_pressed[Jump],"held rebound key produces only one edge");
        check(backend.set_keyboard_binding(Jump,-1),"runtime unbinding accepted");
        backend.poll();
        check(!backend.player(0).down[Jump],"unbound action ignores physical held key");
        check(!backend.set_keyboard_binding(Jump,512),"out-of-range key rejected");
        check(backend.set_keyboard_binding(Jump,SDL_SCANCODE_F),"runtime rebind restored");
        backend.suppress_key(SDL_SCANCODE_F);
        backend.note_focus_lost();
        backend.poll();
        check(!backend.player(0).down[Jump],"focus loss clears held key");
        backend.note_key(SDL_SCANCODE_F,true);
        backend.poll();
        check(backend.player(0).just_pressed[Jump],"focus loss also clears stale suppression");
    }
    SDL_Quit();
    std::printf("input_backend_test: %d failures\n",failures);
    return failures ? 1 : 0;
}
