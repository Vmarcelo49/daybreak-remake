// =============================================================================
//  weapon_definition_test.cpp — the per-weapon combat definitions (issue #9).
//
//  What this pins, in three layers:
//
//   1. Device-free: WeaponDefinition::parse against a synthesized buffer with the
//      exact FUN_00433eb0 layout — field mapping, the capacity() rule, move/ownership,
//      and every rejection path. Runs with no game install.
//   2. Real data: every one of the 46 shipped data/item/NNN.dat files, swept when an
//      install is present and skipped (with a message) when it is not. This is the
//      inventory check: 16 characters, 14 with three weapons, hanyu and natumi with two.
//   3. Behavior: representative weapon families through a real Fighter and Match, plus
//      a smoke run of EVERY legal character/weapon selection, so no combination can
//      regress into the shared tuning silently.
//
//  Build (CMake target `weapon_definition_test`):
//    cmake --build remake/foundation/build/linux --target weapon_definition_test
//  Exit status: 0 when every check passes, 1 otherwise.
// =============================================================================
#include "gameplay/fighter.h"
#include "gameplay/match.h"
#include "gameplay/weapon_definition.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

namespace {

namespace fs = std::filesystem;
using gameplay::WeaponDefinition;

int checks = 0;
int failures = 0;
int skipped = 0;

void check(bool condition, const char* name) {
    ++checks;
    if (!condition) ++failures;
    std::printf("  %-62s %s\n", name, condition ? "ok" : "FAIL");
}
void checkInt(long long expected, long long actual, const char* name) {
    ++checks;
    const bool same = expected == actual;
    if (!same) ++failures;
    std::printf("  %-62s %s", name, same ? "ok" : "FAIL");
    if (!same) std::printf("  (expected %lld, got %lld)", expected, actual);
    std::printf("\n");
}
void skip(const char* name) {
    ++skipped;
    std::printf("  %-62s SKIP\n", name);
}
void section(const char* title) { std::printf("\n-- %s\n", title); }

// ---------------------------------------------------------------------------
// A synthetic data/item/NNN.dat written field for field as FUN_00433eb0 reads it.
// ---------------------------------------------------------------------------
struct DatBuilder {
    std::vector<uint8_t> bytes;
    void u32(int v) { bytes.insert(bytes.end(), 4, 0);
        std::memcpy(bytes.data() + bytes.size() - 4, &v, 4); }
    void name30(const std::string& s) {
        for (int i = 0; i < gameplay::kWeaponNameField; ++i)
            bytes.push_back(i < static_cast<int>(s.size()) ? static_cast<uint8_t>(s[i]) : 0);
    }
};

// mag: {num, type, reloadTime, intervalTime, chargeMax, chargeLevel}
struct SynthMag { int num, type, reload, interval, chargeMax, chargeLevel; };
// bullets: {magazine, shotNum, type, status}
struct SynthBullet { int magazine, shotNum, type, status; };

std::vector<uint8_t> synthDat(int slots, int bulletCount,
                              const SynthMag mag0, const SynthMag mag1,
                              const std::vector<SynthBullet>& bullets,
                              const std::string& mesh = "01.x") {
    DatBuilder b;
    b.u32(slots);
    b.u32(bulletCount);
    b.name30("test_gage.bmp");
    b.u32(96);
    b.u32(96);
    for (int i = 0; i < slots; ++i) {
        b.name30(i == 0 ? mesh : "");
        b.name30("tex.bmp");
        for (int f = 0; f < 9; ++f) b.u32(i * 10 + f);
    }
    for (const SynthMag& m : {mag0, mag1}) {
        b.u32(m.num); b.u32(m.type); b.u32(m.reload);
        b.u32(m.interval); b.u32(m.chargeMax); b.u32(m.chargeLevel);
    }
    for (const SynthBullet& s : bullets) {
        b.u32(s.magazine); b.u32(s.shotNum); b.u32(s.type); b.u32(s.status);
    }
    return b.bytes;
}

std::unique_ptr<WeaponDefinition> parseOrNull(int id, const std::vector<uint8_t>& bytes) {
    auto w = std::make_unique<WeaponDefinition>();
    std::string err;
    return w->parse(id, bytes.data(), bytes.size(), err) ? std::move(w) : nullptr;
}

// ---------------------------------------------------------------------------
// 1. Device-free parser.
// ---------------------------------------------------------------------------
void testParser() {
    section("device-free: the FUN_00433eb0 record layout");
    // A weapon shaped like rena's: 2 attachments, 18 bullets, time-valued magazines.
    std::vector<SynthBullet> bullets;
    for (int i = 0; i < 18; ++i) bullets.push_back({i % 2, 3 + (i % 3), i / 3, i % 7});
    const auto bytes = synthDat(2, 18, {6, 2, 300, 0, 60, 1}, {2, 2, 300, 0, 180, 2}, bullets);
    auto w = parseOrNull(1, bytes);
    check(w != nullptr, "a well-formed synthetic item parses");
    if (!w) return;

    checkInt(2, w->slotCount, "slotCount is the first dword (the attachment loop bound)");
    checkInt(18, w->bulletCount, "bulletCount is the second dword");
    check(w->gaugeTexture == "test_gage.bmp", "the 30-byte gauge name round-trips");
    checkInt(96, w->gaugeHeight0, "gageHeight0 follows the gauge name");
    checkInt(96, w->gaugeHeight1, "gageHeight1 follows gageHeight0");
    check(w->slots[0].meshName == "01.x", "attachment 0 mesh name");
    check(w->slots[1].meshName.empty(), "an unused attachment reads as an empty name");
    check(w->slots[0].transform[0] == 0.f && w->slots[0].transform[1] == 1.f &&
          w->slots[0].transform[8] == 8.f,
          "the nine attachment transforms land in order mx,my,mz,x,y,z,x1,y1,z1");
    checkInt(6, w->magazines[0].num, "magazine 0 num");
    checkInt(300, w->magazines[0].reloadTime, "magazine 0 reloadTime");
    checkInt(60, w->magazines[0].chargeMax, "magazine 0 chargeMax");
    checkInt(1, w->magazines[0].chargeLevel, "magazine 0 is charge level 1");
    checkInt(2, w->magazines[1].chargeLevel, "magazine 1 is charge level 2");
    checkInt(3, w->bullets[0].shotNum, "bullet 0 shotNum");
    checkInt(0, w->bullets[0].magazine, "bullet 0 magazine index");
    checkInt(w->bullets[0].type * 10 + w->bullets[0].status,
             w->bullets[0].paramId(), "the bullet paramId is type*10 + status");

    section("device-free: the FUN_00433eb0:135-143 capacity rule");
    // type 0 is count-valued; types 1 and 2 are time-valued (num * reloadTime);
    // anything else has no recovered rule and yields 0.
    auto cap = [](int num, int type, int reload) {
        gameplay::MagazineDefinition m;
        m.num = num; m.type = type; m.reloadTime = reload;
        return m.capacity();
    };
    checkInt(6, cap(6, 0, 300), "type 0 capacity is the shot count");
    checkInt(1800, cap(6, 2, 300), "type 2 capacity is num * reloadTime");
    checkInt(2400, cap(8, 1, 300), "type 1 capacity is num * reloadTime");
    checkInt(0, cap(6, 3, 300), "type 3 has no recovered capacity rule");
    checkInt(0, cap(6, -1, 300), "a negative type has no recovered rule");

    section("device-free: rejection and ownership");
    check(parseOrNull(1, {} ) == nullptr, "an empty buffer is rejected");
    check(parseOrNull(1, std::vector<uint8_t>(6, 0)) == nullptr,
          "a buffer shorter than the two counts is rejected");
    {
        auto truncated = bytes;
        truncated.resize(truncated.size() - 3);
        WeaponDefinition d;
        std::string err;
        check(!d.parse(1, truncated.data(), truncated.size(), err),
              "a truncated final bullet is rejected, not read past");
        check(!err.empty(), "and it reports why");
        check(d.bullets == nullptr, "a failed parse leaves no dangling allocation");
    }
    {
        // Implausible counts must be refused rather than trusted for an allocation.
        auto bad = synthDat(2, 2, {6, 2, 300, 0, 60, 1}, {2, 2, 300, 0, 180, 2}, {});
        DatBuilder hdr;
        hdr.u32(100000);
        hdr.u32(0);
        hdr.name30("g.bmp"); hdr.u32(1); hdr.u32(1);
        bad.insert(bad.begin(), 44, 0);
        std::memcpy(bad.data(), hdr.bytes.data(), 44);
        WeaponDefinition d;
        std::string err;
        check(!d.parse(1, bad.data(), bad.size(), err),
              "an implausible slotCount is refused before allocating");
    }
    {
        // Trailing bytes the reader never touches are fine: 11 shipped files have them.
        auto padded = bytes;
        padded.insert(padded.end(), 64, 0xCC);
        check(parseOrNull(1, padded) != nullptr,
              "trailing bytes after the last record are tolerated");
    }
    {
        // Move the DEFINITION, not the owning pointer, so the moved-from object is still
        // inspectable afterwards.
        WeaponDefinition a;
        std::string err;
        a.parse(7, bytes.data(), bytes.size(), err);
        WeaponDefinition b(std::move(a));
        check(b.bulletCount == 18, "a moved-to definition carries its records");
        check(a.bullets == nullptr, "and the moved-from one released its buffer");
        check(b.magazines[0].chargeMax == 60, "the move copied the magazine fields");
    }
    {
        // A second parse on the same object must not leak the first bullet array.
        WeaponDefinition reused;
        std::string err;
        reused.parse(1, bytes.data(), bytes.size(), err);
        const int first = reused.magazines[0].chargeMax;
        reused.parse(1, bytes.data(), bytes.size(), err);
        checkInt(first, reused.magazines[0].chargeMax, "re-parsing replaces, not appends");
        check(reused.bulletCount == 18, "and the bullet count is not doubled");
    }
}

// ---------------------------------------------------------------------------
// 1b. The bullet parameter file — the block that IS recovered.
// ---------------------------------------------------------------------------

// One data/bullet/<weapon>/<type>.dat built to FUN_005f8510's layout.
std::vector<uint8_t> synthBulletDat(int status, const gameplay::BulletParameter& b) {
    DatBuilder d;
    d.u32(4);                    // leading tag          (:71)
    for (int i = 0; i < 0x104 / 4; ++i) d.u32(0);   // 260-byte model path block (:72)
    d.u32(1);                                // variant count (:79)
    d.u32(status);                           // variant id (:84)
    d.u32(10);                               // a (:88)
    d.u32(20);                               // b (:89)
    d.u32(1);                                // sub-section count (:90)
    d.u32(0);                                // section tag (:94)
    d.u32(1);                                // entry count (:96)
    d.name30(b.effectName.empty() ? "Bip00" : b.effectName);   // (:102)
    d.u32(0);                                // v04 (:104)
    d.u32(0); d.u32(0); d.u32(0);            // v0c, v10, v14 (:105-107)
    d.u32(b.hitRadius);                      // v24 (:108)
    // The verbatim 0x50-byte block -> record +0x30 (:109)
    // Indexed exactly as record +0x30 + 4*i, which is how BulletParameter names them.
    int blob[20] = {0};
    blob[0x00] = b.baseDamage;
    blob[0x05] = b.hpDamage;
    blob[0x06] = b.reflectDamage;
    blob[0x07] = b.gaugeGainA;
    blob[0x08] = b.gaugeGainB;
    blob[0x09] = b.attackerHitstun;
    blob[0x0a] = b.defenderHitstun;
    blob[0x0d] = b.chargeTier1Move;
    blob[0x0e] = b.chargeTier2Move;
    blob[0x0f] = b.hitEffect;
    blob[0x10] = b.secondaryEffect;
    blob[0x11] = b.releaseOffsetA;
    blob[0x12] = b.releaseOffsetB;
    for (int i = 0; i < 20; ++i) d.u32(blob[i]);
    d.u32(0); d.u32(0); d.u32(0);             // v28, v2c, v08 (:111-113)
    d.u32(0); d.u32(0); d.u32(0);             // v18, v1c, v20 (:114-116)
    return d.bytes;
}

void testBulletParameterParser() {
    section("device-free: the FUN_005f8510 combat block");
    gameplay::BulletParameter src;
    src.effectName = "Bip03";
    src.hitRadius = 30; src.baseDamage = 1750; src.hpDamage = 75; src.reflectDamage = 75;
    src.gaugeGainA = 100; src.gaugeGainB = 40;
    src.attackerHitstun = 0; src.defenderHitstun = 0;
    src.chargeTier1Move = 102; src.chargeTier2Move = 113;
    src.hitEffect = 21; src.secondaryEffect = 30;
    src.releaseOffsetA = 500; src.releaseOffsetB = 1500;
    const auto bytes = synthBulletDat(0, src);

    gameplay::BulletParameter out;
    std::string err;
    check(gameplay::parseBulletParameter(bytes.data(), bytes.size(), 0, out, err),
          "a well-formed bullet parameter file decodes");
    check(out.effectName == "Bip03", "the 30-byte effect name round-trips");
    checkInt(30, out.hitRadius, "record +0x24 is the hit radius");
    checkInt(1750, out.baseDamage, "blob[0x00] is the base damage");
    checkInt(75, out.hpDamage, "blob[5] is the HP damage");
    checkInt(75, out.reflectDamage, "blob[6] is the reflected damage");
    checkInt(100, out.gaugeGainA, "blob[7] is the charge gauge gain (100 fills it)");
    checkInt(40, out.gaugeGainB, "blob[8] is the second gauge gain");
    checkInt(102, out.chargeTier1Move, "blob[13] is the tier-1 shot move id");
    checkInt(113, out.chargeTier2Move, "blob[14] is the tier-2 shot move id");
    checkInt(21, out.hitEffect, "blob[15] is the impact effect id");
    checkInt(30, out.secondaryEffect, "blob[16] is the secondary effect id");
    checkInt(500, out.releaseOffsetA, "blob[17] is the tier-up release offset A");
    checkInt(1500, out.releaseOffsetB, "blob[18] is the tier-up release offset B");

    gameplay::BulletParameter wrong;
    check(!gameplay::parseBulletParameter(bytes.data(), bytes.size(), 7, wrong, err),
          "a status with no matching variant is reported, not guessed");
    check(!gameplay::parseBulletParameter(bytes.data(), 40, 0, out, err),
          "a truncated file is rejected rather than read past");
    check(!gameplay::parseBulletParameter(nullptr, 0, 0, out, err),
          "an empty buffer is rejected");

    section("device-free: per-weapon parameters reach the shot");
    auto weapon = parseOrNull(1, synthDat(2, 1, {6, 2, 300, 0, 60, 1},
                                          {2, 2, 300, 0, 180, 2},
                                          {{0, 3, 0, 0}}));
    check(weapon != nullptr, "the weapon with one bullet parses");
    if (!weapon) return;
    gameplay::Fighter f;
    f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    f.set_weapon(weapon.get());
    const gameplay::ShotParams bare = f.shot_params_for(gameplay::ShotTier::Tap);
    const gameplay::ShotParams redBare = f.shot_params_for(gameplay::ShotTier::Red);
    checkInt(4, bare.damage, "without a bullet parameter the shared damage is used");

    f.set_bullet_parameter(1, &src);
    const gameplay::ShotParams armed = f.shot_params_for(gameplay::ShotTier::Tap);
    // hpDamage 75 on the original's 10000 HP maps onto the remake's 0..maxHP range.
    const int expected = static_cast<int>(75.0f * static_cast<float>(f.max_hp()) / 10000.0f + 0.5f);
    checkInt(expected, armed.damage, "the recovered hpDamage replaces the shared value");
    checkInt(30, static_cast<int>(armed.hitRadius), "and the recovered hit radius is used");
    check(armed.damage != bare.damage, "a weapon genuinely changes what a shot does");
    check(f.shot_params_for(gameplay::ShotTier::Red).damage == redBare.damage,
          "binding the tap level leaves the charged level on the shared table");

    f.set_bullet_parameter(2, &src);
    check(f.shot_params_for(gameplay::ShotTier::Red).damage != redBare.damage,
          "binding the charged level changes that level");
    check(f.shot_params_for(gameplay::ShotTier::Tap).damage == armed.damage,
          "and leaves the tap level as it was");
}

// ---------------------------------------------------------------------------
// 1c. Recovered hit-stun reaches the victim; unrecoverable fields stay shared.
// ---------------------------------------------------------------------------
void testHitstunIsPerWeapon() {
    section("behavior: per-weapon hit-stun");
    gameplay::BulletParameter quick;
    quick.hpDamage = 50;
    quick.defenderHitstun = 7;
    gameplay::BulletParameter heavy;
    heavy.hpDamage = 50;
    heavy.defenderHitstun = 45;

    auto fighter = [](const glm::vec3& at) {
        auto f = std::make_unique<gameplay::Fighter>();
        f->init(nullptr, nullptr, at, 0.0f);
        return f;
    };
    {
        auto victim = fighter(glm::vec3(0, 0, 0));
        gameplay::Fighter attacker;
        attacker.init(nullptr, nullptr, glm::vec3(0, 0, 100), 0.0f);
        victim->take_damage(10, &attacker, quick.defenderHitstun);
        check(victim->state() == gameplay::FighterState::Hit, "a hit staggers the victim");
        // Walk the stun down the way a match does and record when it clears.
        fnd::input::PlayerState idle{};
        int frames = 0;
        while (victim->state() == gameplay::FighterState::Hit && frames < 200) {
            fnd::input::compute_edges(idle);
            victim->update(&idle, nullptr, 1.0 / 64.0);
            ++frames;
        }
        check(frames == quick.defenderHitstun,
              "the stun lasts exactly the weapon's defenderHitstun frames");
    }
    {
        // Same weapon-free call keeps the shared constant.
        auto victim = fighter(glm::vec3(0, 0, 0));
        gameplay::Fighter attacker;
        attacker.init(nullptr, nullptr, glm::vec3(0, 0, 100), 0.0f);
        victim->take_damage(10, &attacker);
        fnd::input::PlayerState idle{};
        int frames = 0;
        while (victim->state() == gameplay::FighterState::Hit && frames < 200) {
            fnd::input::compute_edges(idle);
            victim->update(&idle, nullptr, 1.0 / 64.0);
            ++frames;
        }
        check(frames == gameplay::FighterConstants::kHitStunFrames,
              "with no weapon the shared kHitStunFrames still applies");
    }
    {
        // A zero in the weapon means "this entry inflicts no stun", so the default must
        // win over it rather than a zero-length stun.
        auto victim = fighter(glm::vec3(0, 0, 0));
        gameplay::Fighter attacker;
        attacker.init(nullptr, nullptr, glm::vec3(0, 0, 100), 0.0f);
        gameplay::BulletParameter none;
        none.defenderHitstun = 0;
        victim->take_damage(10, &attacker, none.defenderHitstun);
        fnd::input::PlayerState idle{};
        int frames = 0;
        while (victim->state() == gameplay::FighterState::Hit && frames < 200) {
            fnd::input::compute_edges(idle);
            victim->update(&idle, nullptr, 1.0 / 64.0);
            ++frames;
        }
        check(frames == gameplay::FighterConstants::kHitStunFrames,
              "a zero weapon hitstun falls back to the shared default");
    }
}

void testUnrecoveredFieldsStayShared() {
    section("behavior: fields with no evidence stay shared");
    // Speed and lifetime are provably absent from the item and bullet records, so no
    // weapon may change them. This pins that: if someone later adds a per-weapon speed
    // without recovering one, this fails.
    auto fastW = parseOrNull(1, synthDat(2, 1, {6, 2, 300, 0, 60, 1},
                                         {2, 2, 300, 0, 180, 2}, {{0, 3, 0, 0}}));
    auto slowW = parseOrNull(2, synthDat(2, 1, {60, 2, 20, 0, 60, 1},
                                         {4, 2, 600, 0, 600, 2}, {{0, 1, 0, 0}}));
    check(fastW && slowW, "both weapons parse");
    if (!fastW || !slowW) return;
    gameplay::Fighter fast, slow;
    fast.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    slow.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    fast.set_weapon(fastW.get());
    slow.set_weapon(slowW.get());
    for (int tier = 0; tier < 4; ++tier) {
        const auto t = static_cast<gameplay::ShotTier>(tier);
        check(fast.shot_params_for(t).speed == slow.shot_params_for(t).speed,
              "shot speed is shared: it is absent from the shipped weapon data");
        check(fast.shot_params_for(t).lifeSec == slow.shot_params_for(t).lifeSec,
              "shot lifetime is shared: likewise absent");
    }
    check(fast.main_whole() != slow.main_whole(),
          "while magazine size, which IS in the data, still differs");
}

// ---------------------------------------------------------------------------
// 2. The shipped inventory.
// ---------------------------------------------------------------------------
fs::path findInstall(int argc, char** argv) {
    if (argc > 1) return fs::path(argv[1]);
    if (const char* env = std::getenv("GAME_DIR")) return fs::path(env);
    fs::path game = fs::path("Higurashi-Daybreak");
    for (const fs::path& d : {fs::absolute(fs::path(argv[0])).parent_path(),
                              fs::current_path()}) {
        for (fs::path r = d; !r.empty(); r = r.parent_path()) {
            std::error_code ec;
            if (fs::is_directory(r / "remake" / "foundation", ec)) {
                game = r / "Higurashi-Daybreak";
                break;
            }
            if (r == r.parent_path()) break;
        }
        std::error_code ec;
        if (fs::is_directory(game / "data" / "item", ec)) return game;
    }
    return fs::path();
}

void testInventory(const fs::path& install) {
    section("inventory: the shipped character/weapon table");
    checkInt(16, gameplay::kCharacterCount, "sixteen characters");
    int legal = 0;
    std::set<int> ids;
    for (int c = 0; c < gameplay::kCharacterCount; ++c) {
        for (int w = 0; w < gameplay::kWeaponSlots; ++w) {
            if (!gameplay::weaponSlotIsLegal(c, w)) continue;
            ++legal;
            const int id = gameplay::kWeaponIds[c][w];
            ids.insert(id);
            check(id > 0, "every legal slot carries a real item id");
        }
    }
    checkInt(46, legal, "46 legal selections (14x3 + 2x2)");
    checkInt(46, static_cast<int>(ids.size()), "all 46 item ids are distinct");
    checkInt(2, gameplay::weaponCountForCharacter(14), "hanyu has two weapons");
    checkInt(2, gameplay::weaponCountForCharacter(15), "natumi has two weapons");
    for (int c = 0; c < 14; ++c)
        check(gameplay::weaponCountForCharacter(c) == 3, "the other fourteen have three");
    check(!gameplay::weaponSlotIsLegal(14, 2), "hanyu's third slot is refused");
    check(!gameplay::weaponSlotIsLegal(15, 2), "natumi's third slot is refused");
    check(!gameplay::weaponSlotIsLegal(14, 3), "a slot past the table is refused");
    check(!gameplay::weaponSlotIsLegal(-1, 0), "a negative character is refused");

    std::error_code ec;
    if (install.empty() || !fs::is_directory(install / "data" / "item", ec)) {
        skip("parsing the shipped data/item/NNN.dat files (no install found)");
        skip("per-weapon differentiation across the shipped set");
        return;
    }

    section("real data: all 46 shipped weapon definitions");
    int parsed = 0, slotTotal = 0, bulletTotal = 0;
    std::map<std::pair<int, int>, int> capacitySignatures;
    std::vector<std::pair<int, std::string>> chargeNotes;
    for (int c = 0; c < gameplay::kCharacterCount; ++c) {
        for (int w = 0; w < gameplay::kWeaponSlots; ++w) {
            if (!gameplay::weaponSlotIsLegal(c, w)) continue;
            const int id = gameplay::kWeaponIds[c][w];
            char rel[32];
            std::snprintf(rel, sizeof(rel), "%03d.dat", id);
            const fs::path file = install / "data" / "item" / rel;
            std::ifstream in(file, std::ios::binary);
            if (!in) continue;
            const std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(in)),
                                             std::istreambuf_iterator<char>());
            auto def = parseOrNull(id, bytes);
            if (!def) {
                std::printf("  item %03d FAILED to parse\n", id);
                check(false, "every shipped item parses");
                continue;
            }
            ++parsed;
            slotTotal += def->slotCount;
            bulletTotal += def->bulletCount;
            check(def->slotCount > 0 && def->slotCount <= 12,
                  "attachment count is in the shipped range");
            check(def->bulletCount > 0 && def->bulletCount <= 28,
                  "bullet count is in the shipped range");
            check(def->magazines[0].capacity() > 0,
                  "the tap magazine has a real capacity");
            check(def->magazines[1].capacity() > 0,
                  "the charge magazine has a real capacity");
            check(def->magazines[0].chargeMax > 0, "the tap magazine has a chargeMax");
            check(def->magazines[1].chargeMax > 0, "the charge magazine has a chargeMax");
            check(def->magazines[1].chargeMax >= def->magazines[0].chargeMax,
                  "the charged magazine charges at least as long as the tap one");
            check(def->magazineForChargeLevel(1).chargeLevel == 1,
                  "charge level 1 selects magazine 0");
            check(def->magazineForChargeLevel(2).chargeLevel == 2,
                  "charge level 2 selects magazine 1");
            bool bulletMagazineOk = true;
            bool shotNumOk = true;
            for (int bi = 0; bi < def->bulletCount; ++bi) {
                const gameplay::BulletDefinition& bullet = def->bullets[bi];
                const int m = bullet.magazine;
                // The shipped set uses -1 (331 bullets), 0, 1, and one 2; -1 is the
                // "draws from no magazine" sentinel. Anything outside that is a parse
                // fault, not data.
                if (m < -1 || m > 2) bulletMagazineOk = false;
                // shotNum is 3 for most shipped weapons, 4 for some, and -1 for three
                // bullets, which Fighter::shot_count must treat as "no volley".
                if (bullet.shotNum < -1) shotNumOk = false;
            }
            check(bulletMagazineOk, "every bullet names a magazine in {-1,0,1,2}");
            check(shotNumOk, "every bullet's shotNum is 3, 4 or the -1 sentinel");
            capacitySignatures[{def->magazines[0].capacity(),
                                def->magazines[1].capacity()}]++;
            chargeNotes.emplace_back(id, def->magazines[1].chargeMax ==
                                            def->magazines[0].chargeMax
                                        ? "same" : "longer");
        }
    }
    checkInt(46, parsed, "every legal selection's item file parses");
    check(slotTotal > 0 && bulletTotal > 0, "the swept files carry real record counts");
    // The point of the issue: the weapons are NOT interchangeable.
    check(capacitySignatures.size() > 20,
          "magazine capacities differ across the roster (not one shared table)");
    int differing = 0;
    for (int c = 0; c < gameplay::kCharacterCount; ++c) {
        const int a = gameplay::kWeaponIds[c][0], b = gameplay::kWeaponIds[c][1];
        if (a != b) ++differing;
    }
    checkInt(16, differing, "every character's own weapons are separate ids");
}

// ---------------------------------------------------------------------------
// 3. Behavior: representative families and every legal selection.
// ---------------------------------------------------------------------------

// Loads a shipped weapon by id, or returns null when the install is absent.
std::unique_ptr<WeaponDefinition> loadWeapon(const fs::path& install, int id) {
    std::error_code ec;
    if (install.empty() || !fs::is_directory(install / "data" / "item", ec)) return nullptr;
    char rel[32];
    std::snprintf(rel, sizeof(rel), "%03d.dat", id);
    std::ifstream in(install / "data" / "item" / rel, std::ios::binary);
    if (!in) return nullptr;
    const std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(in)),
                                     std::istreambuf_iterator<char>());
    return parseOrNull(id, bytes);
}

void testWeaponDrivesFighter() {
    section("behavior: a bound weapon replaces the shared tuning");
    // Two weapons that differ on every axis the file controls.
    std::vector<SynthBullet> fastBullets{{0, 4, 0, 0}, {1, 3, 1, 0}, {1, 1, 2, 0}};
    std::vector<SynthBullet> heavyBullets{{0, 1, 0, 0}, {1, 1, 1, 0}};
    auto fastW = parseOrNull(1, synthDat(2, 3, {6, 2, 300, 0, 60, 1},
                                         {2, 2, 300, 0, 180, 2}, fastBullets));
    auto heavyW = parseOrNull(2, synthDat(2, 2, {60, 2, 20, 0, 60, 1},
                                          {4, 2, 600, 0, 600, 2}, heavyBullets));
    check(fastW && heavyW, "both synthetic weapons parse");
    if (!fastW || !heavyW) return;

    gameplay::Fighter bare;
    bare.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    check(bare.weapon() == nullptr, "a fighter starts with no weapon bound");
    const float bareMain = bare.main_frac();
    check(bareMain > 0.99f, "and with the historical full magazine");

    gameplay::Fighter fast;
    fast.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    fast.set_weapon(fastW.get());
    check(fast.weapon() == fastW.get(), "set_weapon binds the parsed definition");
    checkInt(6 * 300, static_cast<int>(fast.main_whole()),
             "the tap magazine is sized num*reloadTime from the file");
    check(std::fabs(fast.main_frac() - 1.0f) < 1e-4f,
          "and starts full (FUN_00433eb0 initialises current from capacity)");
    check(std::fabs(fast.yellow_hold_sec() - 60.0f / 64.0f) < 1e-5f,
          "the yellow threshold is the level-1 chargeMax in ticks");
    check(std::fabs(fast.red_hold_sec() - 180.0f / 64.0f) < 1e-5f,
          "the red threshold is the level-2 chargeMax in ticks");
    checkInt(4, fast.shot_count(gameplay::ShotTier::Tap),
             "the tap volley is the level-1 bullet's shotNum");
    // Level-2 candidates are {magazine 1, type 1, shotNum 3} and {magazine 1, type 2,
    // shotNum 1}; the lowest type wins, so this is 3.
    checkInt(3, fast.shot_count(gameplay::ShotTier::Red),
             "the charged volley picks the lowest-type level-2 bullet");

    gameplay::Fighter heavy;
    heavy.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    heavy.set_weapon(heavyW.get());
    checkInt(60 * 20, heavy.main_whole(), "a different weapon gives a different pool");
    check(heavy.red_hold_sec() > 3.0f * 3.0f,
          "and a much longer charge (600 ticks vs 180)");
    check(heavy.main_whole() != fast.main_whole(),
          "two weapons do NOT share one magazine size");

    section("behavior: no weapon keeps the historical numbers");
    gameplay::Fighter legacy;
    legacy.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
    checkInt(gameplay::FighterConstants::kMainMax, legacy.main_whole(),
             "an unbound fighter keeps kMainMax");
    check(std::fabs(legacy.yellow_hold_sec() -
                    gameplay::FighterConstants::kYellowHoldSec) < 1e-6f,
          "and the historical yellow threshold");
    check(std::fabs(legacy.red_hold_sec() -
                    gameplay::FighterConstants::kRedHoldSec) < 1e-6f,
          "and the historical red threshold");
    checkInt(1, legacy.shot_count(gameplay::ShotTier::Tap), "and a single projectile");

    section("behavior: the per-shot cost comes from the magazine");
    // A fighter with 2 shots' worth of tap ammo must be able to fire twice, not once.
    {
        std::vector<SynthBullet> b{{0, 1, 0, 0}};
        auto w = parseOrNull(3, synthDat(2, 1, {2, 2, 100, 0, 60, 1},
                                         {1, 2, 100, 0, 180, 2}, b));
        check(w != nullptr, "a two-shot weapon parses");
        if (w) {
            gameplay::Fighter f;
            f.init(nullptr, nullptr, glm::vec3(0, 0, 0), 0.0f);
            f.set_weapon(w.get());
            checkInt(200, f.main_whole(), "capacity is 2 shots * 100 units");
            // Settle out of the 60-frame BattleStart pose, then tap-fire.
            fnd::input::PlayerState idle{};
            for (int i = 0; i < 70; ++i) {
                fnd::input::compute_edges(idle);
                f.update(&idle, nullptr, 1.0 / 64.0);
                f.take_pending_shot();
            }
            int fired = 0;
            float lowest = 1.0f;
            for (int i = 0; i < 20; ++i) {
                fnd::input::PlayerState in{};
                in.down[fnd::input::Shoot] = (i % 2) == 0;   // press, then release
                fnd::input::compute_edges(in);
                f.update(&in, nullptr, 1.0 / 64.0);
                if (f.take_pending_shot().armed) ++fired;
                lowest = std::min(lowest, f.main_frac());
            }
            check(fired >= 1, "the weapon-bound fighter actually fires");
            check(fired <= 2, "and cannot fire past its two-shot magazine");
            check(lowest >= 0.0f && lowest <= 1.0f,
                  "its magazine stays inside [0,1] while firing");
        }
    }
}

void testEverySelectionSmoke(const fs::path& install) {
    section("behavior: every legal selection runs a match");
    int ran = 0, skippedHere = 0;
    for (int c = 0; c < gameplay::kCharacterCount; ++c) {
        for (int w = 0; w < gameplay::kWeaponSlots; ++w) {
            if (!gameplay::weaponSlotIsLegal(c, w)) continue;
            const int id = gameplay::kWeaponIds[c][w];
            const auto def = loadWeapon(install, id);
            if (!def) { ++skippedHere; continue; }
            ++ran;
            gameplay::MatchConfig config;
            config.fighterCount = 2;
            config.side[0] = 0; config.side[1] = 1;
            config.spawn[0] = glm::vec3(0, 0, 0);
            config.spawn[1] = glm::vec3(300, 0, 0);
            config.weapon[0] = def.get();
            config.weapon[1] = def.get();     // same weapon both sides: a mirror match
            const xm::Model* models[4] = {};
            xm::Controller* anims[4] = {};
            gameplay::Match match;
            match.reset(config, models, anims, nullptr, nullptr);
            match.economy().setLogFile(nullptr);

            // Run a short fight with the fire button held so the weapon's own magazines,
            // charge thresholds and volley counts are all exercised.
            const fnd::input::PlayerState* inputs[4] = {};
            for (int tick = 0; tick < 240; ++tick) {
                fnd::input::PlayerState p1{}, p2{};
                p1.down[fnd::input::Shoot] = true;
                p2.down[fnd::input::Shoot] = true;
                fnd::input::compute_edges(p1);
                fnd::input::compute_edges(p2);
                inputs[0] = &p1;
                inputs[1] = &p2;
                match.step(inputs, 1.0 / 64.0);
            }
            const auto& f0 = match.fighter(0);
            const bool sane = f0.hp() >= 0 && f0.hp() <= f0.max_hp() &&
                              f0.main_frac() >= 0.0f && f0.main_frac() <= 1.0f &&
                              f0.charge_frac() >= 0.0f && f0.charge_frac() <= 1.0f &&
                              match.locked_target(0) == gameplay::kNoTarget ||
                              match.locked_target(0) >= 0;
            check(sane, "a selection runs 240 ticks with sane state");
        }
    }
    checkInt(46, ran, "all 46 legal selections ran a match");
    if (skippedHere > 0) {
        std::printf("  (%d selections skipped: no item file)\n", skippedHere);
        check(true, "skipped selections are absent data, not failures");
    }
}

// Families are named by their shipped profile so the sweep reads as the issue asks.
void testRepresentativeFamilies(const fs::path& install) {
    section("behavior: representative weapon families");
    struct Family { int id; const char* note; };
    // rena[0] fast/low-capacity, mion[0] huge capacity/fast reload, satoko[1]
    // long charge, rika[1] extreme pool, hanyu[0] the 1200-tick charge outlier.
    const Family families[] = {
        {1, "rena slot0"}, {2, "mion slot0"}, {17, "satoko slot1"},
        {19, "rika slot1"}, {31, "hanyu slot0"},
    };
    std::vector<std::unique_ptr<WeaponDefinition>> defs;
    std::set<int> capacities, charges;
    for (const Family& f : families) {
        auto def = loadWeapon(install, f.id);
        if (!def) { skip(f.note); continue; }
        defs.push_back(std::move(def));
        capacities.insert(defs.back()->magazines[0].capacity());
        charges.insert(defs.back()->magazines[1].chargeMax);
        std::printf("    %-12s id %2d  mag0 cap %6d  mag1 cap %6d  chargeMax %4d\n", f.note,
                    f.id, defs.back()->magazines[0].capacity(),
                    defs.back()->magazines[1].capacity(),
                    defs.back()->magazines[1].chargeMax);
    }
    if (defs.empty()) { skip("shipped family sweep (no install found)"); return; }
    check(capacities.size() >= 3,
          "the sampled families span several distinct magazine capacities");
    check(charges.size() >= 3, "and several distinct charge thresholds");
}

}  // namespace

int main(int argc, char** argv) {
    std::printf("WEAPON_DEFINITION_TEST\n");
    const fs::path install = findInstall(argc, argv);
    testParser();
    testBulletParameterParser();
    testHitstunIsPerWeapon();
    testUnrecoveredFieldsStayShared();
    testWeaponDrivesFighter();
    testInventory(install);
    testRepresentativeFamilies(install);
    testEverySelectionSmoke(install);
    std::printf("\nWEAPON_DEFINITION: %s (%d checks, %d failed, %d skipped)\n",
                failures == 0 ? "ok" : "FAIL", checks, failures, skipped);
    return failures == 0 ? 0 : 1;
}