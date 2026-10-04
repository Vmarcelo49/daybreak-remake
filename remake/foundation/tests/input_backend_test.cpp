#include "input/input_backend.h"
#include "input/tick_input.h"
#include "gameplay/fighter.h"
#include "gameplay/fixed_step.h"
#include <SDL3/SDL.h>
#include <cstdio>

int main(int argc, char** argv) {
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
    {
        fnd::input::Backend backend;
        using namespace fnd::input;
        check(backend.init(), "event input initialized");
        TickInput ticks[kMaxPlayers];
        backend.note_key(SDL_SCANCODE_Z,true);
        backend.note_key(SDL_SCANCODE_Z,false);
        backend.note_gamepad_button(1,SDL_GAMEPAD_BUTTON_EAST,true);
        backend.note_gamepad_button(1,SDL_GAMEPAD_BUTTON_EAST,false);
        backend.poll(false);
        backend.sample_tick_inputs(ticks);
        check(!backend.player(0).down[Jump], "short tap ends released before poll");
        check(ticks[0].consume().just_pressed[Jump], "stalled-render keyboard press retained");
        check(ticks[0].consume().just_released[Jump], "stalled-render keyboard release retained");
        check(!ticks[0].consume().just_pressed[Jump], "catch-up does not repeat keyboard tap");
        check(ticks[1].consume().just_pressed[Jump], "stalled-render pad press retained");
        check(ticks[1].consume().just_released[Jump], "stalled-render pad release retained");
        backend.suppress_key(SDL_SCANCODE_Z);
        backend.note_key(SDL_SCANCODE_Z,true);
        backend.poll(false);
        backend.sample_tick_inputs(ticks);
        check(!ticks[0].consume().just_pressed[Jump], "binding capture suppresses queued key press");
    }
    {
        using namespace fnd::input;
        SDL_VirtualJoystickDesc desc{};
        SDL_INIT_INTERFACE(&desc);
        desc.type = SDL_JOYSTICK_TYPE_GAMEPAD;
        desc.nbuttons = SDL_GAMEPAD_BUTTON_COUNT;
        desc.button_mask = 1u << SDL_GAMEPAD_BUTTON_SOUTH;
        desc.name = "Guard lifecycle test";
        const auto id = SDL_AttachVirtualJoystick(&desc);
        check(id != 0, "virtual controller attached");
        SDL_Joystick* joystick = SDL_OpenJoystick(id);
        check(joystick != nullptr, "virtual controller opened");
        Backend backend;
        check(backend.init(), "controller input initialized");
        backend.poll(false);
        const int player = backend.gamepad_player(id);
        check(player > 0, "controller assigned a player");
        if (joystick && player > 0) {
            TickInput ticks[kMaxPlayers];
            gameplay::Fighter fighter;
            auto sample = [&]() {
                SDL_UpdateJoysticks();
                backend.poll(false);
                backend.sample_tick_inputs(ticks);
                const auto state = ticks[player].consume();
                fighter.update(&state, nullptr, gameplay::FixedStep::seconds);
                return state;
            };
            SDL_SetJoystickVirtualButton(joystick, SDL_GAMEPAD_BUTTON_SOUTH, true);
            check(sample().just_pressed[Guard], "controller Guard hold reaches tick");
            check(fighter.state() == gameplay::FighterState::Guard, "controller hold starts fighter Guard");
            backend.note_focus_lost();
            check(sample().just_released[Guard], "focus loss releases controller Guard");
            check(fighter.state() == gameplay::FighterState::Idle, "focus loss frees guarding fighter");
            check(!sample().down[Guard], "physical hold cannot re-enter after focus loss");
            SDL_SetJoystickVirtualButton(joystick, SDL_GAMEPAD_BUTTON_SOUTH, false);
            sample();
            SDL_SetJoystickVirtualButton(joystick, SDL_GAMEPAD_BUTTON_SOUTH, true);
            check(sample().just_pressed[Guard], "fresh controller press works after focus loss");
            SDL_DetachVirtualJoystick(id);
            check(sample().just_released[Guard], "controller disconnect releases held Guard");
            check(fighter.state() == gameplay::FighterState::Idle, "disconnect frees guarding fighter");
            check(!sample().down[Guard], "disconnected Guard stays released");
        } else if (id) {
            SDL_DetachVirtualJoystick(id);
        }
        if (joystick) SDL_CloseJoystick(joystick);
    }
    if (argc > 1) {
        fnd::input::Backend backend;
        using namespace fnd::input;
        check(backend.init() && backend.load_script(argv[1]), "tick script loaded");
        PlayerState scripted;
        backend.sample_script(scripted,1);
        check(scripted.just_pressed[Down] && scripted.down[Down], "script press on tick one");
        backend.sample_script(scripted,1);
        check(!scripted.just_pressed[Down], "repeated script tick cannot repeat edge");
        backend.sample_script(scripted,2);
        check(scripted.just_released[Down], "script release on tick two");
        backend.sample_script(scripted,3);
        check(scripted.just_pressed[Jump], "script advances without device polling");
        backend.note_key(SDL_SCANCODE_RIGHT,true);
        backend.poll(false);
        check(backend.player(0).down[Right] && !backend.player(0).down[Jump], "device sample excludes script override");
        check(scripted.stick_x == 0 && scripted.stick_y == 0, "script does not inherit physical axes");
        backend.tick_script(3);
        backend.poll();
        check(backend.player(0).down[Jump] && !backend.player(0).down[Right], "legacy polling keeps script override");
    }
    SDL_Quit();
    std::printf("input_backend_test: %d failures\n",failures);
    return failures ? 1 : 0;
}
