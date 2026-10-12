#include "input/input_backend.h"
#include "input/tick_input.h"
#include "gameplay/fighter.h"
#include "gameplay/fixed_step.h"
#include <SDL3/SDL.h>
#include <cstdio>
#include <filesystem>
#include <system_error>

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
        // --no-devices (issue #23's verification instrument): with devices disabled the
        // backend reports no pad for slots 1..3 and drops the keyboard, so a run is driven
        // only by its script and the synthetic pads. SDL reports a connected controller
        // whether or not the window has focus, so without this a second application's pad
        // moves a capture's menus (measured: hud_cell_scale's probe markers moved).
        fnd::input::Backend isolated;
        if (!isolated.init()) { SDL_Quit(); return 1; }
        isolated.set_devices_enabled(false);
        isolated.poll();
        check(isolated.device(0) == fnd::input::DeviceType::Keyboard,
              "device-free run keeps the keyboard slot for the script");
        for (int p = 1; p < 4; ++p)
            check(isolated.device(p) == fnd::input::DeviceType::None,
                  "device-free run reports no pad for a pad-less slot");
        bool anyHeld = false;
        for (int p = 0; p < 4; ++p)
            for (int a = 0; a < fnd::input::ActionCount; ++a)
                anyHeld = anyHeld || isolated.player(p).down[a];
        check(!anyHeld, "device-free run starts with no held action");
    }
    {
        // Issue #29's focus gate: an unfocused window accepts no device input, and the
        // DEFAULT is focused — a compositor that never delivers FOCUS_GAINED (or a run with
        // no window at all, like --headless) must not leave the game unresponsive.
        using namespace fnd::input;
        Backend backend;
        check(backend.init(), "focus-gate backend initialized");
        check(backend.window_focused(), "unknown focus means focused");
        TickInput ticks[kMaxPlayers];
        backend.note_key(SDL_SCANCODE_Z,true);
        backend.poll(false);
        check(backend.player(0).just_pressed[Jump],
              "a run that never saw a focus event reads the key feed");
        backend.note_key(SDL_SCANCODE_Z,false);
        backend.poll(false);
        backend.note_focus_lost();
        check(!backend.window_focused(), "focus loss is observed");
        backend.note_key(SDL_SCANCODE_Z,true);
        backend.poll(false);
        check(!backend.player(0).down[Jump], "an unfocused window drops the key feed");
        backend.note_gamepad_button(1,SDL_GAMEPAD_BUTTON_EAST,true);
        backend.poll(false);
        backend.sample_tick_inputs(ticks);
        check(!ticks[1].consume().just_pressed[Jump], "an unfocused window drops the pad feed");
        backend.note_focus_gained();
        check(backend.window_focused(), "focus gain is observed");
        backend.note_key(SDL_SCANCODE_Z,true);
        backend.poll(false);
        check(backend.player(0).just_pressed[Jump], "the key feed works again after focus is regained");
        backend.note_gamepad_button(1,SDL_GAMEPAD_BUTTON_EAST,true);
        backend.poll(false);
        backend.sample_tick_inputs(ticks);
        check(ticks[1].consume().just_pressed[Jump], "the pad feed works again after focus is regained");
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
        // Issue #29: input stays ignored until focus returns (an unfocused window accepts
        // nothing), so the stale-suppression check has to run after note_focus_gained.
        backend.note_focus_gained();
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
            // Issue #29: the pad keeps its slot while unfocused, and input resumes only once
            // focus returns — which is what the next sample does.
            check(backend.device(player) == DeviceType::Gamepad,
                  "an unfocused window keeps its pad in the slot (no synthetic takeover)");
            backend.note_focus_gained();
            SDL_SetJoystickVirtualButton(joystick, SDL_GAMEPAD_BUTTON_SOUTH, false);
            sample();
            check(!backend.player(player).just_pressed[Guard],
                  "a hold from before focus loss cannot re-enter on regain");
            SDL_SetJoystickVirtualButton(joystick, SDL_GAMEPAD_BUTTON_SOUTH, true);
            check(sample().just_pressed[Guard], "fresh controller press works after focus is regained");
            SDL_DetachVirtualJoystick(id);
            check(sample().just_released[Guard], "controller disconnect releases held Guard");
            check(fighter.state() == gameplay::FighterState::Idle, "disconnect frees guarding fighter");
            check(!sample().down[Guard], "disconnected Guard stays released");
        } else if (id) {
            SDL_DetachVirtualJoystick(id);
        }
        if (joystick) SDL_CloseJoystick(joystick);
    }
    {
        // `WAIT <scene>` holds the script until the named scene is current. This is what
        // lets a menu whose navigation is state-dependent (the selection screen after a
        // rematch) be driven without guessing frame offsets.
        const auto path = std::filesystem::temp_directory_path() / "fnd_wait_script.txt";
        {
            std::FILE* f = std::fopen(path.string().c_str(), "w");
            check(f != nullptr, "wait script can be written");
            if (f) {
                std::fputs("1 JUMP\n\n5 -\n\n9 WAIT battle\n\n13 MELEE\n", f);
                std::fclose(f);
            }
        }
        fnd::input::Backend backend;
        using namespace fnd::input;
        check(backend.init() && backend.load_script(path.string().c_str()),
              "wait script loaded");
        PlayerState state;
        // No scene yet: the WAIT cannot match, so the script parks on the released event
        // at frame 5 and never reaches the MELEE at 13.
        backend.sample_script(state, 5);
        check(!state.down[Jump] && !state.down[AttackA],
              "a wait with no current scene holds the script");
        backend.sample_script(state, 20);
        check(!state.down[AttackA], "a held wait does not advance past its frame");
        // The wrong scene still holds it.
        backend.set_scene_name("select");
        backend.sample_script(state, 30);
        check(!state.down[AttackA], "a wait for another scene holds the script");
        // The named scene releases it, and the following event lands.
        backend.set_scene_name("battle");
        backend.sample_script(state, 30);
        check(state.down[AttackA], "the wait releases on its scene");
        // A WAIT with no scene name is malformed: it must not silently become a release.
        {
            uint64_t frame = 0;
            uint32_t mask = 0xffffffffu;
            std::string wait;
            check(!fnd::input::parse_script_line("9 WAIT", frame, mask, wait),
                  "a WAIT with no scene is rejected");
            check(fnd::input::parse_script_line("9 WAIT battle", frame, mask, wait) &&
                      wait == "battle",
                  "a WAIT with a scene reports it");
            check(fnd::input::parse_script_line("9 JUMP", frame, mask, wait) && wait.empty(),
                  "a normal line reports no wait");
        }
        std::error_code ec;
        std::filesystem::remove(path, ec);
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
