#pragma once
// FUN_00633ca0's attachment table, and the attach points FUN_004205e0 draws it on.
//
// WHY this is separate from effect_catalog.h: that header owns the descriptor table and
// the effect-id space (data/effect/%03d.dat). FUN_00633ca0 fills a second table in the
// same pass — the seven data/aura/%02d.x models — and the draw call that uses it places
// the selected model on a fixed eleven-point attach set, not on one transform.
//
// The multiplicity is the RIG's, not the attachment's. Every shipped attachment is a
// single .X model (one frame hierarchy, 1..3 unskinned meshes; enumerated in
// tests/effect_catalog_test.cpp), and FUN_0041e180 resolves these eleven bone names into
// player+0x64c..0x674 once per character (0x41edfb-0x41ef4f). FUN_00421010 copies their
// world matrices into player+0x38c + i*0x40 every frame (0x42104f-0x421071), and
// FUN_004205e0 renders the attachment once per matrix (0x420711-0x420770). All 92 shipped
// character rigs carry all eleven names, so every one of those draws lands: eleven
// instances per active attachment, for every shipped attachment — not one. The port's
// single placement was therefore an assumption, and this header carries the enumeration
// that replaced it.
//
// A rig missing one of the names has no matrix to copy there (the original copies from
// the null frame pointer and would fault); the port skips that point and says so.

namespace game {

// data/aura/%02d.x, loaded by FUN_00633ca0 into scene+0x4498 (slots 0..6). Their
// textures name the roles: 0/1/5 the three muzzle flashes, 2 the blue hit flash,
// 3 the burning aura (炎上オーラ), 4 a bucket; 6 ships unnamed.
inline constexpr int kAuraSlots = 7;

// The attach points in the order FUN_0041e180 stores them, so point i is the frame whose
// world matrix lands at player+0x38c + i*0x40 and becomes aura instance i.
inline constexpr int kAuraAttachPoints = 11;
inline constexpr const char* kAuraAttachBone[kAuraAttachPoints] = {
    "Bip00",            // player+0x64c
    "Bip01_Head",       //        0x650
    "Bip01_Spine",      //        0x654
    "Bip01_L_Forearm",  //        0x658
    "Bip01_R_Forearm",  //        0x65c
    "Bip00_L_Calf",     //        0x660
    "Bip00_R_Calf",     //        0x664
    "Bip01_L_Hand",     //        0x668
    "Bip01_R_Hand",     //        0x66c
    "Bip00_L_Foot",     //        0x670
    "Bip00_R_Foot",     //        0x674
};

// One fighter's attach points, resolved on its own rig at match setup: `frame[i]` is the
// rig frame index for kAuraAttachBone[i] (-1 when the rig does not carry it), and `found`
// is the number of resolved points — the number of aura instances that fighter draws.
struct AuraAttach {
    int frame[kAuraAttachPoints];
    int found = 0;
    AuraAttach() {
        for (int& f : frame) f = -1;
    }
};

// The port's instance rule, and the whole of it: one instance per resolved attach point,
// never one per attachment model. Exposed as a template so a rig is whatever answers
// findFrame(name) — the shipped xm::Model in the product, a stub in the unit test — which
// keeps the rule testable without an install.
template <typename Rig>
inline AuraAttach resolveAuraAttach(const Rig& rig) {
    AuraAttach attach;
    for (int point = 0; point < kAuraAttachPoints; ++point) {
        const int frame = rig.findFrame(kAuraAttachBone[point]);
        if (frame < 0) continue;
        attach.frame[attach.found++] = frame;
    }
    return attach;
}

}  // namespace game
