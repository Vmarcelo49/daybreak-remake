#pragma once
// FUN_00433eb0: item slot/bullet counts, gauge name[30], two gauge integers,
// slots {model[30], texture[30], nine signed integer anchors}, two six-word
// magazines, then bullet rows {magazine, pool capacity, type, status}.
// Anchors are numeric integer-to-float conversions, not IEEE bit patterns.
// FUN_005f8510 reads the model block, all variant phases/records, and the
// animation-set/texture-event trailer. Original executable handlers provide
// projectile motion and launch rules; the files do not contain their speeds.
// Magazine refill/hold conversion remains a documented port rule.

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include "gameplay/character_moves.h"

namespace gameplay {

// The original's fixed-length name fields (FUN_00433eb0 passes 0x1e).
inline constexpr int kWeaponNameField = 30;

// The nine signed integers FUN_00433eb0 reads per attachment (file 60..96) are three
// bone-local points, not position plus rotations. 0..2 go to the manager's per-prop
// muzzle table, which FUN_00435000 transforms by the slot's posed bone to launch a
// shot; 3..5 and 6..8 become the ribbon prop's two anchors (+0x18/+0x28), which
// FUN_00430120 transforms with D3DXVec4Transform into the endpoint samples.
struct WeaponSlot {
    std::string meshName;      // "" when the file leaves this attachment empty
    std::string textureName;
    float muzzle[3] = {0, 0, 0};
    float ribbonRoot[3] = {0, 0, 0};
    float ribbonTip[3] = {0, 0, 0};

    // FUN_00433eb0 creates/marks a prop available only when meshName[0] is nonzero.
    bool has_prop() const { return !meshName.empty(); }
};

// One ammunition pool. Two per weapon, fixed by FUN_00433eb0:122.
struct MagazineDefinition {
    int num          = 0;   // shots (or shots x units) the pool holds
    int type         = 0;   // 0 = count-valued, 1/2 = time-valued, else no rule
    int reloadTime   = 0;   // units consumed per shot
    int intervalTime = 0;   // magazine interval counter's reset value
    int chargeMax    = 0;   // recovered charge ceiling for this level
    int chargeLevel  = 0;   // 1 = tap/MAIN magazine, 2 = charged/CHARGE magazine

    // FUN_00433eb0:135-143. Returns 0 for an unmodelled type, which is also what the
    // original leaves in the field.
    int capacity() const {
        if (type == 0) return num;
        if (type > 0 && type < 3) return num * reloadTime;
        return 0;
    }
};

// One entry of the weapon's bullet table (FUN_00433eb0:148-156). `magazine` is the
// index of the magazine, `poolCapacity` the number of live instances allocated,
// NOT a volley count (FUN_005f80c0), and `type`/`status` address the record under
// data/bullet/<weaponId>/ (FUN_005f80c0:99-102).
struct BulletDefinition {
    int magazine = 0;
    int poolCapacity  = 0;
    int type     = 0;
    int status   = 0;
    int paramId() const { return type * 10 + status; }   // FUN_00433eb0:155
};

// A parsed data/item/NNN.dat.
struct WeaponDefinition {
    int  id = 0;              // the item id, which is also the bullet directory number
    int  slotCount   = 0;
    int  bulletCount = 0;
    std::string gaugeTexture;
    int gaugeHeight0 = 0;
    int gaugeHeight1 = 0;
    WeaponSlot slots[16]{};         // 16 > the shipped maximum of 12
    MagazineDefinition magazines[2];
    BulletDefinition* bullets = nullptr;   // owned, bulletCount entries

    WeaponDefinition() = default;
    ~WeaponDefinition();
    WeaponDefinition(const WeaponDefinition&) = delete;
    WeaponDefinition& operator=(const WeaponDefinition&) = delete;
    WeaponDefinition(WeaponDefinition&& other) noexcept;
    WeaponDefinition& operator=(WeaponDefinition&& other) noexcept;

    // True when the file parsed whole: every declared record was present and the reader
    // ended exactly at end-of-file is NOT required (11 shipped files carry trailing
    // bytes the reader never reads), so `truncated` only reports a short file.
    bool parse(int itemId, const uint8_t* bytes, size_t size, std::string& error);
    bool valid() const { return bullets != nullptr; }

    // The magazine a given charge level draws from. FUN_00433eb0 fixes the count at 2
    // and every shipped weapon writes chargeLevel 1 then 2.
    const MagazineDefinition& magazineForChargeLevel(int level) const {
        return magazines[(level == 2) ? 1 : 0];
    }

private:
    void release() noexcept;
};

// One bullet entry from data/bullet/<weaponId>/<type>.dat: the file's own model block
// plus the effect record decoded at the offsets FUN_00637950 consumes. The reader pulls
// 0x50 bytes VERBATIM at record offset 0x30, so blob[i] lands at record offset 0x30 + 4*i:
// the index for a record offset O is (O - 0x30) / 4, and each comment below gives both.
struct BulletParameter {
    int formatTag = 0;
    // The 260-byte block at file offset 4: the model THIS bullet IS. FUN_005f8510:55-57
    // reads it, joins it to the bullet's own directory and calls FUN_0064d940 (the .X
    // loader) with the bullet's per-variant model object as `this`; the shot spawn
    // (FUN_005f8d50 @0x5f8dc7) hands that same object to the shot, and the shot's own
    // render draws it (FUN_005f60b0: the matrix at 0x5f6185-0x5f61b6, the draw at
    // 0x5f640f). It is NOT the impact effect — that is `impactEffect` below, a data/effect
    // descriptor spawned at the contact point. See game/shot_visual.h for the whole chain.
    // Empty when the block is blank, which is also the case the original loads no model for.
    std::string modelName;
    std::vector<MovePhase> phases;
    // The selected variant's own row pair, read exactly like NN.dat's (row+0 selection
    // value, row+4 cancel threshold compared against a destination row's priority). No
    // runtime consumer yet — bullets do not chain — but a repeated variant id overwrites
    // them the same way NN rows do, so they must come from the WINNING variant.
    int priority = 0;
    int cancelThreshold = 0;
    struct AnimationSet {
        int transition = 0;
        int phaseGate = 0;
        std::vector<TextureEvent> textures;
    };
    std::vector<AnimationSet> animationSets;
    std::string boneName;
    int hitRadius        = 0;  // record +0x24, consumed as a float by FUN_00637950:91,107
    int baseDamage       = 0;  // blob[0] (+0x30) — the HP power, 10000-based, :426
    int hpDamage         = 0;  // provisional alias for combat[5]; resolver feeds victim +0x838
    int reflectDamage    = 0;  // provisional alias for combat[6]; resolver feeds victim +0x840
    int gaugeGainA       = 0;  // provisional alias for combat[7]; resolver feeds victim +0x7b8
    int gaugeGainB       = 0;  // provisional alias for combat[8]; resolver feeds victim +0x7c0
    int attackerHitstun  = 0;  // provisional alias for combat[9], exact recipient/units unresolved
    int defenderHitstun  = 0;  // provisional alias for combat[10], verify across all paths
    // Recovered fields read in FUN_00637950's hit-resolution path and followed by a
    // state change on param_3 at :536-537; shooter/launch-animation role is unproven.
    int hitResolutionField64 = 0;  // blob[13] (+0x64); shooter-selector role unproven
    int hitResolutionField68 = 0;  // blob[14] (+0x68); shooter-selector role unproven
    // Record +0x6C. NOT an effect: FUN_00637950:232-250 switches on it and calls
    // FUN_0064ae70(id, matrix, 1), which indexes the scene's 256-entry SE table at
    // scene+0x98 (FUN_00647e00 fills it from data/se/%03d.wav). Values 10/20/30 are
    // three-SE families: the switch adds rand()%3, so 10 -> 10..12, 20 -> 20..22,
    // 30 -> 30..32.
    int hitSound         = 0;
    // Record +0x70. The impact EFFECT id: FUN_00637950:221-228 spawns it through
    // FUN_00435990(id, pos, matrix, victim) -> the effect manager's create method
    // (FUN_0042f5e0). The id is type*10+variant into data/effect/%03d.dat, so the
    // shipped roster's 0/10/20/30 are descriptors 000/001/002/003 (issue #17).
    int impactEffect     = 0;
    int releaseOffsetA   = 0;  // provisional alias for combat[17]; destination/meaning unresolved
    int releaseOffsetB   = 0;  // provisional alias for combat[18]; destination/meaning unresolved
};

// Retains the selected variant's complete phase vector and animation trailer. Scalar
// aliases describe the winning variant's first section's first record, for legacy
// preview callers; a variant whose winning first section has no entry leaves them
// unset rather than reusing another variant's values.
bool parseBulletParameter(const uint8_t* bytes, size_t size, int status,
                          BulletParameter& out, std::string& error);

// The shipped roster: 16 characters, 14 of them with three weapons and hanyu/natumi
// with two (their third slot is the sentinel 0). This is the original's own table, read
// from the selection data rather than inferred from mesh names — an entry exists only
// because ids.dat maps that character to that item id.
struct RosterWeapon {
    int itemId;
};
inline constexpr int kCharacterCount = 16;
inline constexpr int kWeaponSlots = 3;
// The roster in selection order (ASSET-CATALOG §3.3): directory names that also
// index the kWeaponIds rows. Shared by the frontend selection and the standalone
// match/weapon defaults so the two cannot disagree about who is who.
inline constexpr const char* kCharacterDirs[kCharacterCount] = {
    "rena",   "mion",    "keiichi", "satoko", "rika",  "shion",   "tomitake", "takano",
    "ohishi", "akasaka", "irie",    "chie",   "kasai", "akane",   "hanyu",    "natumi",
};
// Roster index for a character directory basename ("rena" → 0), or -1 when the
// spec names no roster character (custom paths keep the legacy bare fallback).
inline int characterIndexForDir(const std::string& dir) {
    for (int i = 0; i < kCharacterCount; ++i)
        if (dir == kCharacterDirs[i]) return i;
    return -1;
}
// Weapon ids per character, ASSET-CATALOG §3.3 / FUN_0041e180 (weapon id at DAT 0x114).
// A trailing 0 is the "no weapon" sentinel.
inline constexpr int kWeaponIds[kCharacterCount][kWeaponSlots] = {
    {1, 3, 33},   {2, 4, 35},   {5, 18, 34},   {8, 17, 38},
    {7, 19, 37},  {6, 20, 36},  {12, 21, 42},  {11, 22, 41},
    {9, 23, 39},  {10, 24, 40}, {13, 26, 43},  {14, 25, 44},
    {15, 27, 45}, {16, 28, 46}, {31, 32, 0},  {29, 30, 0},
};
// Weapon slot holding an item id in a character's row, or -1. The file-level
// proof: every data/<char>/NN.dat carries its weapon id at file offset 0x114
// (FUN_0041e180.c:99-106 reads it on to FUN_00433eb0), NN is the weapon slot,
// and all 46 files agree with this table exactly.
inline int weaponSlotForItem(int character, int itemId) {
    if (character < 0 || character >= kCharacterCount || itemId <= 0) return -1;
    for (int w = 0; w < kWeaponSlots; ++w)
        if (kWeaponIds[character][w] == itemId) return w;
    return -1;
}
// "Rena 1": combo label — capitalized roster name + weapon INDEX, so Rena 1 is
// her second weapon and Keiichi 1 his Invincible Iron (atlas names in
// ASSET-CATALOG §3.2). Logs and test messages name combos with both halves,
// never a bare character.
inline std::string comboSlotLabel(int character, int slot) {
    if (character < 0 || character >= kCharacterCount || slot < 0 ||
        slot >= kWeaponSlots)
        return "?";
    std::string name = kCharacterDirs[character];
    if (!name.empty() && 'a' <= name[0] && name[0] <= 'z')
        name[0] = static_cast<char>(name[0] - ('a' - 'A'));
    return name + " " + std::to_string(slot);
}
// Legal weapon count for a character index: 2 for the last two, 3 otherwise.
inline int weaponCountForCharacter(int character) {
    if (character < 0 || character >= kCharacterCount) return 0;
    return character < kCharacterCount - 2 ? 3 : 2;
}
// False for the sentinel slot, which is why hanyu and natumi have two.
inline bool weaponSlotIsLegal(int character, int slot) {
    return slot >= 0 && slot < weaponCountForCharacter(character);
}

}  // namespace gameplay
