#pragma once
// input/gamepad_identity.h — the stable-controller policy (issue #19), device-free.
//
// WHY this is a policy and not just "first free slot": the backend opens pads in
// enumeration order, so with two pads plugged in, unplugging and replugging them can
// swap which physical pad is player 1 and which is player 2 — and with it whose
// bindings apply. The original has the same shape (its config.dat stores bindings per
// PLAYER: FUN_006486c0 @0x6486c0 reads a 0xd0-byte block = four players x thirteen
// actions, and its pads are the per-player button tables) but no device identity at all,
// so the port adds the identity and keeps the original's per-player binding model.
//
// POLICY (port decision, labelled as such):
//   * bindings belong to the PLAYER slot, which is the unit the keyconfig screen edits
//     and the unit the original stores;
//   * a pad is placed in the slot whose recorded GUID matches it, when that slot is
//     free — so a replugged pad keeps its player and its bindings;
//   * a pad with no recorded GUID (or one whose slot is taken by another pad) takes the
//     lowest free slot, which is the enumeration behaviour the backend had;
//   * a recorded GUID that is not connected changes nothing: the bindings stay on the
//     player slot and remain usable by the keyboard or the next pad.
// Pure std so the host test pins the placement rules without SDL.
#include <array>
#include <string>

#include "input/input.h"

namespace fnd::input {

inline constexpr int kPadSlots = kMaxPlayers;

// The slot a pad with `guid` should be opened into, or -1 when every slot is occupied.
// `guidHints` is the per-slot recorded identity ("" = none); `occupied` says which slots
// already hold an open pad. Empty `guid` never matches a hint (an unidentified pad must
// not steal a named slot).
inline int preferredPadSlot(const std::array<std::string, kPadSlots>& guidHints,
                            const std::array<bool, kPadSlots>& occupied,
                            const std::string& guid) {
    if (!guid.empty()) {
        for (int slot = 0; slot < kPadSlots; ++slot)
            if (!occupied[static_cast<size_t>(slot)] && guidHints[static_cast<size_t>(slot)] == guid)
                return slot;
    }
    for (int slot = 0; slot < kPadSlots; ++slot)
        if (!occupied[static_cast<size_t>(slot)]) return slot;
    return -1;
}

}  // namespace fnd::input
