#pragma once
// Device-free input model for Track M.
//
// Why logic and SDL are split: the remake's 4-player shape (fcn.00634f60),
// 13-action layout (controller-setup capture) and script-override format are
// all deterministic and must test without a window or gamepad. This header
// owns that: edges, stick deadzone, digital derivation, script parsing. The
// SDL3 event/poll half lives in input_sdl3.h and stays out of unit tests.

#include <cstddef>
#include <cstdint>
#include <cstring>

namespace fnd::input {

// Verified 1P semantics from the remake (arrows + Z/X/C/A/S/D/Q/W); P2-P4
// pads are buttons 1-8 with exact layout unknown.
//
// There is ONE melee action, because the corpus has one melee input bit: the move
// dispatchers (the shared FUN_0043ded0 and every per-character twin, e.g. FUN_00445ee0)
// test only `[fighter+0x10]+0x28 & 0x100` for attacks and no other input bit at all. The
// heavy stand-in that used to sit at index 5 was a port invention and is gone (issue #10);
// the swing a press plays is chosen by the fighter's situation (grounded, mid-dash,
// airborne) and by the bound move table's rows.
enum Action : int {
    Up = 0,
    Down = 1,
    Left = 2,
    Right = 3,
    AttackA = 4,  // melee (the original's single attack bit)
    Guard = 5,
    Shoot = 6,
    Jump = 7,  // doubles as menu confirm
    Special = 8,
    Tactics = 9,
    LockSwitch = 10,  // tap = cycle enemy, hold = aim ally
    Pause = 11,
    ActionCount = 12,
};

enum class DeviceType : int { None = 0, Keyboard = 1, Gamepad = 2 };

struct PlayerState {
    bool down[ActionCount] = {};
    bool prev_down[ActionCount] = {};
    bool just_pressed[ActionCount] = {};
    bool just_released[ActionCount] = {};
    int16_t stick_x = 0;
    int16_t stick_y = 0;
    int16_t stick_rx = 0;  // camera orbit
    int16_t stick_ry = 0;
    int press_timer[ActionCount] = {};  // mirrors original +0x828 2-frame window
};

inline constexpr int kMaxPlayers = 4;
// Matches the remake's gamepad path: small deflections are rest, not intent.
inline constexpr int16_t kStickDeadzone = 8000;

// Edge + timer update. Runs after device reads (and after a script override,
// so scripted taps derive edges normally like the remake's poll()).
inline void compute_edges(PlayerState& p) {
    for (int a = 0; a < ActionCount; ++a) {
        p.just_pressed[a] = p.down[a] && !p.prev_down[a];
        p.just_released[a] = !p.down[a] && p.prev_down[a];
        p.prev_down[a] = p.down[a];
        if (p.press_timer[a] > 0) --p.press_timer[a];
        if (p.just_pressed[a]) p.press_timer[a] = 2;
    }
}

inline int16_t apply_deadzone(int16_t v) {
    if (v > -kStickDeadzone && v < kStickDeadzone) return 0;
    return v;
}

// Left-stick deflection feeds the digital directions so stick and D-pad agree
// (remake ORs them after the same deadzone).
inline void stick_to_digital(int16_t lx, int16_t ly, bool& left, bool& right,
                             bool& up, bool& down) {
    if (lx < -kStickDeadzone) left = true;
    if (lx > kStickDeadzone) right = true;
    if (ly < -kStickDeadzone) up = true;  // SDL +Y is down, stick up is negative
    if (ly > kStickDeadzone) down = true;
}

// Script line format shared with the remake's visual-validation driver:
// "<frame> <TOKEN>..."; "-" releases all; "#" starts a comment; blanks skip.
// Tokens: UP DOWN LEFT RIGHT MELEE GUARD SHOOT JUMP SPECIAL TACTICS
// LOCK PAUSE. Returns false for blank/comment lines (caller skips).
inline bool parse_script_line(const char* line, uint64_t& frame_out,
                              uint32_t& mask_out) {
    if (!line) return false;
    while (*line == ' ' || *line == '\t') ++line;
    if (*line == '\0' || *line == '#') return false;
    // Frame number first; a line without one is not an event.
    uint64_t frame = 0;
    const char* p = line;
    if (*p < '0' || *p > '9') return false;
    while (*p >= '0' && *p <= '9') frame = frame * 10 + static_cast<uint64_t>(*p++ - '0');
    uint32_t mask = 0;
    char tok[16];
    while (*p) {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0' || *p == '#') break;
        size_t n = 0;
        while (*p && *p != ' ' && *p != '\t' && n + 1 < sizeof(tok)) tok[n++] = *p++;
        tok[n] = '\0';
        while (*p && *p != ' ' && *p != '\t') ++p;  // overlong token: consume rest
        int action = -1;
        if (!std::strcmp(tok, "UP")) action = Up;
        else if (!std::strcmp(tok, "DOWN")) action = Down;
        else if (!std::strcmp(tok, "LEFT")) action = Left;
        else if (!std::strcmp(tok, "RIGHT")) action = Right;
        else if (!std::strcmp(tok, "MELEE")) action = AttackA;
        else if (!std::strcmp(tok, "GUARD")) action = Guard;
        else if (!std::strcmp(tok, "SHOOT")) action = Shoot;
        else if (!std::strcmp(tok, "JUMP")) action = Jump;
        else if (!std::strcmp(tok, "SPECIAL")) action = Special;
        else if (!std::strcmp(tok, "TACTICS")) action = Tactics;
        else if (!std::strcmp(tok, "LOCK")) action = LockSwitch;
        else if (!std::strcmp(tok, "PAUSE")) action = Pause;
        else if (!std::strcmp(tok, "-")) mask = 0;
        if (action >= 0) mask |= (1u << action);
        // Unknown tokens are ignored (remake logs and continues); "-" already
        // handled above, so anything else falling here is a no-op by design.
    }
    frame_out = frame;
    mask_out = mask;
    return true;
}

}  // namespace fnd::input
