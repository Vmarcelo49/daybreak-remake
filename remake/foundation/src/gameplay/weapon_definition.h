#pragma once
// gameplay/weapon_definition.h — one weapon's combat definition, parsed from the
// original `data/item/NNN.dat`. Device-free: it takes a byte buffer, so the same code
// serves the battle simulation (foundation_gameplay) and the selection front end
// (which is the only layer that touches the asset source). Nothing here renders.
//
// WHY a parsed definition and not a lookup table: the original does not ship weapon
// tuning in code. FUN_00433eb0 (0x433eb0) opens `data/item/%03d.dat` and reads it
// sequentially through FUN_00653760 (0x653760, a thin ReadFile wrapper), so the file
// IS the tuning, and the 46 shipped files differ from each other in exactly the fields
// the battle needs. Hard-coding those numbers here would be inventing a table the game
// already ships; parsing the file is the port.
//
// FILE LAYOUT — the reader's own order, with the record sizes it passes to FUN_00653760:
//
//   u32  slotCount        (= *param_1; the [weaponN] loop bound, 2..12 in the shipped set)
//   u32  bulletCount      (= param_1[0x3e]; [global] bulletType)
//   char gaugeTexture[30] (= local_350, 0x1e bytes, not NUL-terminated on read)
//   i32  gaugeHeight0     (FUN_00433eb0:70)
//   i32  gaugeHeight1     (FUN_00433eb0:71)
//   slotCount x {
//     char meshName[30]     (local_140; skipped when empty)
//     char textureName[30]  (local_460)
//     f32  transform[9]     (mx,my,mz, x,y,z, x1,y1,z1 — read as dwords, stored as float)
//   }
//   2 x {                   (the magazine loop, FUN_00433eb0:121-143, fixed at 2)
//     i32  num, type, reloadTime, intervalTime, chargeMax, chargeLevel
//   }
//   bulletCount x {         (FUN_00433eb0:148-156)
//     i32  magazine, shotNum, type, status
//   }
//
// The nine transform floats are read by FUN_00653760 as 4 raw bytes each and stored
// through a float cast; every shipped file stores them as integers, so they are read
// here as i32 and exposed as float. Cross-checked against all 28 shipped .ini mirrors
// (see the coverage table in docs/ROADMAP-PENDING.md): 909/909 transform fields and
// every structural field agree.
//
// MAGAZINE BLOCK — READ BUT NOT CONSUMED. FUN_00433eb0:135-143 computes
//     if (type == 0)                capacity = num
//     else if (0 < type && type < 3)  capacity = num * reloadTime
// and copies capacity into the "current" field, so the block is fully populated. But a
// corpus-wide scan finds NO function that reads those fields afterwards: `+ 0x64)` and
// the sibling magazine offsets return zero hits across all 3191 decompiled functions.
// The original therefore SHIPS ammo data that this corpus never consumes, and the
// consumption lives wherever the rest of the ammo system is missing.
//   => MagazineDefinition is parsed and exposed for completeness, and the remake uses it
//      to size its magazines, but that usage is a PORT RULE, not recovered behaviour.
//      kMainMax/kChargeMax and the refill rate stay provisional per the coverage table.
//      Do not cite this block as evidence for the ammo model.
//
// WHERE THE REAL COMBAT NUMBERS ARE — data/bullet/<weaponId>/<type>.dat.
// FUN_00433eb0:152 hands each bullet entry's `type * 10 + status` to FUN_005f80c0
// (0x5f80c0), which builds the path `data/bullet/%03d/%03d.dat` with `type` as the file
// and passes `status` on to FUN_005f8510 (0x5f8510) as the variant to select. That
// reader lays out a 0x80-byte entry record per effect instance, of which 80 bytes at
// record offset 0x30..0x7F are read VERBATIM from the file in one call. Those are the
// per-weapon combat scalars, and BulletParameter below names them from the consuming
// code in FUN_00637950 (0x637950). This IS recovered; see the coverage table.

#include <cstddef>
#include <cstdint>
#include <string>

namespace gameplay {

// The original's fixed-length name fields (FUN_00433eb0 passes 0x1e).
inline constexpr int kWeaponNameField = 30;

// One weapon attachment point: the mesh bound to a bone, its texture, and the two
// offset/rotation triples FUN_00433eb0:100-118 reads. `x/y/z` and `x1/y1/z1` are the
// shipped pairs; the reader keeps both and the remake exposes both so a renderer can
// pick without re-deriving.
struct WeaponSlot {
    std::string meshName;      // "" when the file leaves this attachment empty
    std::string textureName;
    float transform[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
};

// One ammunition pool. Two per weapon, fixed by FUN_00433eb0:122.
struct MagazineDefinition {
    int num          = 0;   // shots (or shots x units) the pool holds
    int type         = 0;   // 0 = count-valued, 1/2 = time-valued, else no rule
    int reloadTime   = 0;   // units consumed per shot
    int intervalTime = 0;   // ticks between the shots of one burst (ShotNum)
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
// index of the pool this bullet draws from, `shotNum` how many projectiles one trigger
// releases, and `type`/`status` together address the behaviour record under
// data/bullet/<weaponId>/ (FUN_005f80c0:99-102).
struct BulletDefinition {
    int magazine = 0;
    int shotNum  = 0;
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

// One effect instance from data/bullet/<weaponId>/<type>.dat, decoded at the record
// offsets FUN_00637950 consumes. The reader pulls 0x50 bytes VERBATIM at record offset
// 0x30, so blob[i] lands at record offset 0x30 + 4*i: the index for a record offset O is
// (O - 0x30) / 4, and each comment below gives both.
struct BulletParameter {
    std::string effectName;
    int hitRadius        = 0;  // record +0x24, consumed as a float by FUN_00637950:91,107
    int baseDamage       = 0;  // blob[0] (+0x30) — 10000-based, FUN_00637950:426
    int hpDamage         = 0;  // blob[5] (+0x44) — the HP actually removed, :280
    int reflectDamage    = 0;  // blob[6] (+0x48) — dealt back to the attacker, :300
    int gaugeGainA       = 0;  // blob[0x1C] (+0x4C) — 100 fills a charge gauge, :334
    int gaugeGainB       = 0;  // blob[8] (+0x50) — the second gauge, :345
    int attackerHitstun  = 0;  // blob[9] (+0x54) — frames written to the attacker's +0xa0
    int defenderHitstun  = 0;  // blob[10] (+0x58) — frames written to the victim's, :308
    int chargeTier1Move  = 0;  // blob[13] (+0x64) — shot move id at gauge 100..199
    int chargeTier2Move  = 0;  // blob[14] (+0x68) — shot move id at gauge >= 200
    int hitEffect        = 0;  // blob[0x3C] (+0x6C) — impact effect id, :232-250
    int secondaryEffect  = 0;  // blob[16] (+0x70) — EX/secondary impact, :221-228
    int releaseOffsetA   = 0;  // blob[17] (+0x74) — written to player+0x87c on tier-up
    int releaseOffsetB   = 0;  // blob[18] (+0x78) — written to player+0x878 on tier-up
};

// Decodes the variant `status` out of one data/bullet/<weaponId>/<type>.dat, taking the
// first effect entry of its first sub-section (FUN_005f8510:95-129). Device-free.
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
// Weapon ids per character, ASSET-CATALOG §3.3 / FUN_0041e180 (weapon id at DAT 0x114).
// A trailing 0 is the "no weapon" sentinel.
inline constexpr int kWeaponIds[kCharacterCount][kWeaponSlots] = {
    {1, 3, 33},   {2, 4, 35},   {5, 18, 34},   {8, 17, 38},
    {7, 19, 37},  {6, 20, 36},  {12, 21, 42},  {11, 22, 41},
    {9, 23, 39},  {10, 24, 40}, {13, 26, 43},  {14, 25, 44},
    {15, 27, 45}, {16, 28, 46}, {31, 32, 0},  {29, 30, 0},
};
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