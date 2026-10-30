#pragma once
// render/muzzle_slot.h — which data/aura muzzle-flash model an attack shows (issue #34).
//
// WHAT THE ORIGINAL DOES, RECOVERED. FUN_004205e0 picks the attachment slot from
// player+0x7d4; when that is out of range (FUN_0042e110 clears it to -1 every frame, :76)
// it falls back to three latches in a fixed priority and draws nothing when all three are
// clear (FUN_004205e0:17-32), then copies each of the eleven rig matrices at player+0x38c
// into the model and draws it (0x420711-0x420770). The latches, one attack start each:
//
//   +0x844 -> slot 0, data/aura/00.X (マズルフラッシュ) — FUN_00421fe0:20, and its sibling
//            FUN_00422060:22, the two arms of one state case split on fighter+0x3b;
//   +0x845 -> slot 1, 01.X (マズルフラッシュ2) — FUN_004220e0:20;
//   +0x846 -> slot 5, 05.X (マズルフラッシュ3) — FUN_00422160:20.
//
// WHICH firing state runs which writer is read AT THE CALL SITE, and it is not a charge
// tier: the battle input action 0x24 dispatches on the fighter's own byte +0x318 and
// nothing else (FUN_0063c2a0:267-277) — 0 -> FUN_00421fe0, 2 -> FUN_00422160, otherwise
// FUN_004220e0. The move-id branches agree: FUN_00428510 runs FUN_00421fe0 (or
// FUN_00422060) from its move-id 500 case (:25) and its 501 case (:170), and FUN_00422160
// from its 502 (:220) and 503 (:270) cases; the 47 per-character handlers (FUN_0043ded0
// :134-138 and its siblings) call FUN_004220e0 from their own `+0x318 == 1` arm.
//
// The byte is per SLOT, not per character or weapon: FUN_0064ab30:36-38 loads it from
// scene+0x5328+slot through FUN_0041dc80:12, and the story/team setup fills the two CPU
// slots with rand()%3 (FUN_006492f0:20-22).
//
// Provenance: read live on the ORIGINAL DaybreakDX.exe (md5
// a136ddc01bd7ef355b759b88ac89e02c) through the Ghidra bridge; research/decompiled agrees
// line for line once its folded float constants are read back and its file header and
// local-variable names are discounted. The `:NN` numbers are that copy's lines — the one a
// reader can open. The slot->texture column comes from the shipped models' own
// TextureFilename blocks, not from the exe.
//
// WHY THE PORT'S MAPPING IS STILL A PORT RULE. The original's selector is a per-slot
// runtime byte the port does not carry: no port screen writes it, no shipped data field
// feeds it, and gameplay/debug_keys.h already records the same byte as the F4 gauge
// selector the port also cannot reproduce. There is consequently no tier->slot relation
// in the original to recover — one fighter shows one muzzle model for a whole match.
// The tier mapping below is the port's own, labelled as such; effect_catalog_test pins
// both tables so neither can drift silently.
#include "battle/battle_types.h"   // game::ShotTier

namespace game {

// The three slots FUN_00633ca0 loads as muzzle flashes, in the original's fire-mode order
// (that is why 5 sits next to 1: the slots are the file numbers, the order is the mode).
// Slots 2/3/4/6 are the blue hit flash, the burning aura, the bucket and an unnamed model
// — never a muzzle flash — and no attack start can select them.
inline constexpr int kMuzzleFireModes = 3;
inline constexpr int kMuzzleSlots[kMuzzleFireModes] = {0, 1, 5};

// RECOVERED: the original's fire mode -> the slot its attack start selects. The dispatch is
// two tests, not a table lookup — mode 0 -> slot 0, mode 2 -> slot 5, ANY other byte -> slot
// 1 — which is why the last arm is not "nothing" (FUN_0063c2a0:267-277). The game only ever
// stores 0, 1 or 2 (FUN_0064ab30:36 reads a byte, and the story setup writes rand()%3),
// so the other 253 values are the byte's unused range, kept here because that is where the
// original sends them. Exposed because #17's spawn side is what will consume it: the port
// has no mode byte to feed it with.
inline constexpr int muzzleSlotForFireMode(int mode) {
    return mode == 0 ? kMuzzleSlots[0] : (mode == 2 ? kMuzzleSlots[2] : kMuzzleSlots[1]);
}

// True when `slot` is one of the three muzzle flashes.
inline constexpr bool isMuzzleSlot(int slot) {
    for (int i = 0; i < kMuzzleFireModes; ++i)
        if (kMuzzleSlots[i] == slot) return true;
    return false;
}

// PORT RULE, and the whole of it: the port has no fire-mode byte, so the shot's charge
// TIER picks among the same three models — Tap -> マズルフラッシュ1, Yellow -> 2, Red and
// the EX move -> 3. Nothing in the original maps a tier to a slot (header note above), so
// this must never be presented as recovered; it is the port's existing behaviour under a
// name, and it keeps all three shipped muzzle models reachable.
inline constexpr int muzzleSlotForTier(game::ShotTier tier) {
    switch (tier) {
        case game::ShotTier::Tap:    return kMuzzleSlots[0];
        case game::ShotTier::Yellow: return kMuzzleSlots[1];
        case game::ShotTier::Red:
        case game::ShotTier::Ex:     return kMuzzleSlots[2];
    }
    // A new tier must decide its own slot; -Wswitch is what asks.
    return kMuzzleSlots[2];
}

}  // namespace game
