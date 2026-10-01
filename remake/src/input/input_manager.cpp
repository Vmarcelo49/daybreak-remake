// =============================================================================
//  input_manager.cpp — SDL2-based 4-player input polling.
//
//  Mirrors the original game's fcn.00634f60: loops over 4 players, reads
//  each player's device (keyboard or gamepad), fills the 7-action state,
//  and computes just_pressed/just_released edges.
//
//  Key design difference from the original:
//    - Original uses DirectInput8 (GetDeviceState on IDirectInputDevice8).
//    - We use SDL2 (SDL_GetKeyboardState + SDL_GameControllerGetButton/Axis).
//    - The action enum and 4-player structure are identical.
// =============================================================================
#include "input_manager.h"

#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>

namespace daybreak::input {

// Default keyboard bindings:
//   P0: verified 1P layout (arrows + Z/X/C/A/S/D/Q/W).
//   P1-P3: provisional fallbacks (the original uses pads for these slots).
static KeyboardBindings defaultKbBindings(int player) {
    switch (player) {
        case 0: return { SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT,
                          SDL_SCANCODE_X, SDL_SCANCODE_UNKNOWN, SDL_SCANCODE_D,
                          SDL_SCANCODE_C, SDL_SCANCODE_Z, SDL_SCANCODE_S,
                          SDL_SCANCODE_Q, SDL_SCANCODE_A, SDL_SCANCODE_W };
        case 1: return { SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D,
                          SDL_SCANCODE_F, SDL_SCANCODE_UNKNOWN, SDL_SCANCODE_H,
                          SDL_SCANCODE_G, SDL_SCANCODE_T, SDL_SCANCODE_R,
                          SDL_SCANCODE_Y, SDL_SCANCODE_U, SDL_SCANCODE_I };
        case 2: return { SDL_SCANCODE_I, SDL_SCANCODE_K, SDL_SCANCODE_J, SDL_SCANCODE_L,
                          SDL_SCANCODE_U, SDL_SCANCODE_UNKNOWN, SDL_SCANCODE_O,
                          SDL_SCANCODE_P, SDL_SCANCODE_H, SDL_SCANCODE_Y,
                          SDL_SCANCODE_N, SDL_SCANCODE_B, SDL_SCANCODE_M };
        case 3: return { SDL_SCANCODE_KP_8, SDL_SCANCODE_KP_5, SDL_SCANCODE_KP_4, SDL_SCANCODE_KP_6,
                          SDL_SCANCODE_KP_1, SDL_SCANCODE_UNKNOWN, SDL_SCANCODE_KP_3,
                          SDL_SCANCODE_KP_0, SDL_SCANCODE_KP_PERIOD, SDL_SCANCODE_KP_7,
                          SDL_SCANCODE_KP_9, SDL_SCANCODE_KP_DIVIDE, SDL_SCANCODE_KP_MULTIPLY };
        default: return {};
    }
}

InputManager::~InputManager() { shutdown(); }

bool InputManager::init() {
    // SDL_Init must have been called already (with SDL_INIT_GAMECONTROLLER).
    int nJoysticks = SDL_NumJoysticks();
    int gamepadIdx = 0;
    for (int i = 0; i < nJoysticks && gamepadIdx < kMaxPlayers; ++i) {
        if (SDL_IsGameController(i)) {
            SDL_GameController* gc = SDL_GameControllerOpen(i);
            if (gc) {
                m_gamepads[gamepadIdx] = gc;
                m_players[gamepadIdx].device = DeviceType::Gamepad;
                std::printf("[daybreak] input: gamepad %d opened (SDL index %d): %s\n",
                            gamepadIdx, i, SDL_GameControllerName(gc));
                ++gamepadIdx;
            }
        }
    }

    if (m_players[0].device == DeviceType::None) {
        m_players[0].device = DeviceType::Keyboard;
    }

    for (int i = 0; i < kMaxPlayers; ++i) {
        m_kbBindings[i] = defaultKbBindings(i);
    }

    m_keyboardState = SDL_GetKeyboardState(nullptr);
    std::printf("[daybreak] input: %d gamepad(s) + keyboard (player 0)\n", gamepadIdx);
    return true;
}

void InputManager::shutdown() {
    for (int i = 0; i < kMaxPlayers; ++i) {
        if (m_gamepads[i]) {
            SDL_GameControllerClose(m_gamepads[i]);
            m_gamepads[i] = nullptr;
        }
        m_players[i].device = DeviceType::None;
    }
    m_keyboardState = nullptr;
}

void InputManager::poll() {
    // Pump SDL events (needed for both keyboard and gamepad state to update).
    SDL_PumpEvents();

    for (int i = 0; i < kMaxPlayers; ++i) {
        switch (m_players[i].device) {
            case DeviceType::Keyboard:
                update_player_keyboard(i);
                break;
            case DeviceType::Gamepad:
                update_player_gamepad(i);
                break;
            default:
                break;
        }
        // Script override (visual-validation runs): replace P1's held set
        // wholesale so scripted taps/holds read exactly as played.
        if (m_scriptActive && i == 0) {
            for (int a = 0; a < ActionCount; ++a) {
                m_players[i].down[a] = (m_scriptMask & (1u << a)) != 0;
            }
        }
        compute_edges(i);
    }
}

bool InputManager::load_script(const char* path) {
    static const struct { const char* name; Action action; } kTokens[] = {
        {"UP", Up}, {"DOWN", Down}, {"LEFT", Left}, {"RIGHT", Right},
        {"MELEE", AttackA}, {"HEAVY", AttackB}, {"GUARD", Guard},
        {"SHOOT", Shoot}, {"JUMP", Jump}, {"SPECIAL", Special},
        {"TACTICS", Tactics}, {"LOCK", LockSwitch}, {"PAUSE", Pause},
    };
    std::ifstream f(path);
    if (!f.is_open()) {
        std::fprintf(stderr, "[daybreak] input script not found: %s\n", path);
        return false;
    }
    std::vector<ScriptEvent> events;
    std::string line;
    int lineno = 0;
    while (std::getline(f, line)) {
        ++lineno;
        std::istringstream ls(line);
        uint64_t frame = 0;
        if (!(ls >> frame)) continue;  // blank or `#` comment
        uint32_t mask = 0;
        std::string tok;
        while (ls >> tok) {
            if (!tok.empty() && tok[0] == '#') break;  // EOL comment
            if (tok == "-") { mask = 0; continue; }
            bool known = false;
            for (const auto& t : kTokens) {
                if (tok == t.name) {
                    mask |= (1u << t.action);
                    known = true;
                    break;
                }
            }
            if (!known) {
                std::fprintf(stderr,
                             "[daybreak] input script %s:%d: unknown token %s\n",
                             path, lineno, tok.c_str());
            }
        }
        events.push_back({frame, mask});
    }
    m_script = std::move(events);
    m_scriptPos = 0;
    m_scriptMask = 0;
    m_scriptActive = true;
    std::printf("[daybreak] input script: %s (%zu events)\n",
                path, m_script.size());
    return true;
}

void InputManager::tick_script(uint64_t frame) {
    if (!m_scriptActive) return;
    while (m_scriptPos < m_script.size() && m_script[m_scriptPos].frame <= frame) {
        m_scriptMask = m_script[m_scriptPos].mask;
        ++m_scriptPos;
    }
}

const PlayerInput& InputManager::player(int index) const {
    static PlayerInput empty;
    if (index < 0 || index >= kMaxPlayers) return empty;
    return m_players[index];
}

void InputManager::set_keyboard_bindings(int index, const KeyboardBindings& kb) {
    if (index >= 0 && index < kMaxPlayers) {
        m_kbBindings[index] = kb;
    }
}

bool InputManager::any_just_pressed(Action action) const {
    for (int i = 0; i < kMaxPlayers; ++i) {
        if (m_players[i].just_pressed[action]) return true;
    }
    return false;
}

bool InputManager::any_down(Action action) const {
    for (int i = 0; i < kMaxPlayers; ++i) {
        if (m_players[i].down[action]) return true;
    }
    return false;
}

// ----------------------------------------------------------------------------
// Per-device update
// ----------------------------------------------------------------------------
void InputManager::update_player_keyboard(int index) {
    if (!m_keyboardState) return;
    const KeyboardBindings& kb = m_kbBindings[index];

    m_players[index].down[Up]      = m_keyboardState[kb.up];
    m_players[index].down[Down]    = m_keyboardState[kb.down];
    m_players[index].down[Left]    = m_keyboardState[kb.left];
    m_players[index].down[Right]   = m_keyboardState[kb.right];
    m_players[index].down[AttackA] = m_keyboardState[kb.attackA];
    m_players[index].down[AttackB] = kb.attackB != SDL_SCANCODE_UNKNOWN &&
                                     m_keyboardState[kb.attackB];
    m_players[index].down[Guard]   = m_keyboardState[kb.guard];
    m_players[index].down[Shoot]   = m_keyboardState[kb.shoot];
    m_players[index].down[Jump]    = m_keyboardState[kb.jump];
    m_players[index].down[Special] = m_keyboardState[kb.special];
    m_players[index].down[Tactics] = m_keyboardState[kb.tactics];
    m_players[index].down[LockSwitch] = m_keyboardState[kb.lockSwitch];
    m_players[index].down[Pause]   = m_keyboardState[kb.pause];

    // Keyboard has no analog sticks; set from digital D-pad.
    m_players[index].stick_x = m_players[index].down[Right] ? 32767 :
                               m_players[index].down[Left]  ? -32768 : 0;
    m_players[index].stick_y = m_players[index].down[Down] ? 32767 :
                               m_players[index].down[Up]   ? -32768 : 0;

    // Q/E for camera orbit (keyboard right-stick emulation).
    m_players[index].stick_rx = m_keyboardState[SDL_SCANCODE_E] ? 32767 :
                                m_keyboardState[SDL_SCANCODE_Q] ? -32768 : 0;
    m_players[index].stick_ry = 0;
}

void InputManager::update_player_gamepad(int index) {
    SDL_GameController* gc = m_gamepads[index];
    if (!gc) return;

    // D-pad.
    m_players[index].down[Up]      = SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_DPAD_UP);
    m_players[index].down[Down]    = SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    m_players[index].down[Left]    = SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    m_players[index].down[Right]   = SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

    // Face buttons (Xbox layout: A=bottom, B=right, X=left, Y=top).
    // PROVISIONAL pad map (original P2-P4 pads are buttons 1-8, exact
    // layout unknown — see input_manager.h). Melee=X, jump=B, guard=A
    // mirror the keyboard semantics; triggers/shoulders cover the rest.
    m_players[index].down[AttackA] = SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_X);
    m_players[index].down[AttackB] = false;  // unbound (no key exists)
    m_players[index].down[Guard]   = SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_A);
    m_players[index].down[Jump]    = SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_B);
    m_players[index].down[Shoot]   = SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_Y);
    m_players[index].down[Special] = SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
    m_players[index].down[LockSwitch] = SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
    m_players[index].down[Tactics] = SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_BACK);
    m_players[index].down[Pause]   = SDL_GameControllerGetButton(gc, SDL_CONTROLLER_BUTTON_START);

    m_players[index].stick_x = SDL_GameControllerGetAxis(gc, SDL_CONTROLLER_AXIS_LEFTX);
    m_players[index].stick_y = SDL_GameControllerGetAxis(gc, SDL_CONTROLLER_AXIS_LEFTY);
    m_players[index].stick_rx = SDL_GameControllerGetAxis(gc, SDL_CONTROLLER_AXIS_RIGHTX);
    m_players[index].stick_ry = SDL_GameControllerGetAxis(gc, SDL_CONTROLLER_AXIS_RIGHTY);

    // Analog stick → digital direction (with deadzone).
    constexpr int16_t kDeadzone = 8000;
    int16_t lx = m_players[index].stick_x;
    int16_t ly = m_players[index].stick_y;
    if (std::abs(lx) > kDeadzone) {
        m_players[index].down[Left]  = m_players[index].down[Left]  || (lx < -kDeadzone);
        m_players[index].down[Right] = m_players[index].down[Right] || (lx >  kDeadzone);
    }
    if (std::abs(ly) > kDeadzone) {
        m_players[index].down[Up]   = m_players[index].down[Up]   || (ly < -kDeadzone);
        m_players[index].down[Down] = m_players[index].down[Down] || (ly >  kDeadzone);
    }
}

void InputManager::compute_edges(int index) {
    PlayerInput& p = m_players[index];
    for (int a = 0; a < ActionCount; ++a) {
        p.just_pressed[a]  = p.down[a] && !p.prev_down[a];
        p.just_released[a] = !p.down[a] && p.prev_down[a];
        p.prev_down[a] = p.down[a];

        // Decrement press timer (mirrors +0x828 in the original).
        if (p.press_timer[a] > 0) --p.press_timer[a];
        if (p.just_pressed[a]) p.press_timer[a] = 2;  // 2-frame window
    }
}

} // namespace daybreak::input
