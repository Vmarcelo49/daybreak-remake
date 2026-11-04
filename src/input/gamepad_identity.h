#pragma once
// input/gamepad_identity.h — which player slot a device takes, device-free.
//
// POLICY (port rule; the owner's, issue #102, replacing issue #19's recorded-slot rule):
//   * a device takes a slot on its first press, the lowest free one, so whoever presses
//     first is player 1 whatever the device;
//   * a pad that leaves reserves its slot for the rest of the session: the same pad
//     (by SDL GUID) takes it back, and any other device skips it while another slot is
//     free, so a pad whose battery dies mid-match does not lose its player;
//   * nothing is recorded across launches: a remembered slot would let a pad pressed
//     first land on player 2.
// The original stores bindings per PLAYER (FUN_006486c0 @0x6486c0 reads a 0xd0-byte block
// = four players x thirteen actions) and has no device identity; the port keeps the
// per-player binding model. Pure std so the host test pins the rules without SDL.
#include <array>
#include <string>

#include "input/input.h"

namespace fnd::input {

inline constexpr int kPadSlots = kMaxPlayers;

// The slot a device with `guid` takes, or -1 when every slot is occupied. `reserved` is
// the per-slot GUID of a pad that left ("" = none); the keyboard passes "" and so never
// matches one.
inline int slotForNewDevice(const std::array<std::string, kPadSlots>& reserved,
                            const std::array<bool, kPadSlots>& occupied,
                            const std::string& guid) {
    if (!guid.empty()) {
        for (int slot = 0; slot < kPadSlots; ++slot)
            if (!occupied[static_cast<size_t>(slot)] && reserved[static_cast<size_t>(slot)] == guid)
                return slot;
    }
    for (int slot = 0; slot < kPadSlots; ++slot)
        if (!occupied[static_cast<size_t>(slot)] && reserved[static_cast<size_t>(slot)].empty())
            return slot;
    for (int slot = 0; slot < kPadSlots; ++slot)
        if (!occupied[static_cast<size_t>(slot)]) return slot;
    return -1;
}

}  // namespace fnd::input
