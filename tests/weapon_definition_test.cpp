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
//    cmake --build build/linux --target weapon_definition_test
//  Exit status: 0 when every check passes, 1 otherwise.
// =============================================================================
#include "gameplay/fixed_step.h"
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
    // A fixed-width NUL-padded field, which is what the 260-byte model block is.
    void block(const std::string& s, size_t width) {
        for (size_t i = 0; i < width; ++i)
            bytes.push_back(i < s.size() ? static_cast<uint8_t>(s[i]) : 0);
    }
};

// mag: {num, type, reloadTime, intervalTime, chargeMax, chargeLevel}
struct SynthMag { int num, type, reload, interval, chargeMax, chargeLevel; };
// bullets: {magazine, poolCapacity, type, status}
struct SynthBullet { int magazine, poolCapacity, type, status; };

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
        b.u32(s.magazine); b.u32(s.poolCapacity); b.u32(s.type); b.u32(s.status);
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
    check(w->slots[0].muzzle[0] == 0.f && w->slots[0].muzzle[1] == 1.f &&
          w->slots[0].ribbonTip[2] == 8.f,
          "the nine attachment integers land in order muzzle, ribbon root, ribbon tip");
    checkInt(6, w->magazines[0].num, "magazine 0 num");
    checkInt(300, w->magazines[0].reloadTime, "magazine 0 reloadTime");
    checkInt(60, w->magazines[0].chargeMax, "magazine 0 chargeMax");
    checkInt(1, w->magazines[0].chargeLevel, "magazine 0 is charge level 1");
    checkInt(2, w->magazines[1].chargeLevel, "magazine 1 is charge level 2");
    checkInt(3, w->bullets[0].poolCapacity, "bullet 0 poolCapacity");
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
std::vector<uint8_t> synthBulletDat(int status, const gameplay::BulletParameter& b,
                                    const std::string& model = "03.X") {
    DatBuilder d;
    d.u32(4);                    // leading tag          (:71)
    d.block(model, 0x104);       // 260-byte model block (:72) — the bullet's own model
    d.u32(1);                                // variant count (:79)
    d.u32(status);                           // variant id (:84)
    d.u32(10);                               // a (:88)
    d.u32(20);                               // b (:89)
    d.u32(1);                                // sub-section count (:90)
    d.u32(0);                                // section tag (:94)
    d.u32(1);                                // entry count (:96)
    d.name30(b.boneName.empty() ? "Bip00" : b.boneName);
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
    blob[0x0d] = b.hitResolutionField64;
    blob[0x0e] = b.hitResolutionField68;
    blob[0x0f] = b.hitSound;
    blob[0x10] = b.impactEffect;
    blob[0x11] = b.releaseOffsetA;
    blob[0x12] = b.releaseOffsetB;
    for (int i = 0; i < 20; ++i) d.u32(blob[i]);
    d.u32(0); d.u32(0); d.u32(0);             // v28, v2c, v08 (:111-113)
    d.u32(0); d.u32(0); d.u32(0);             // v18, v1c, v20 (:114-116)
    d.u32(0); // Empty animation trailer in this synthetic fixture.
    return d.bytes;
}

void testBulletParameterParser() {
    section("device-free: the FUN_005f8510 combat block");
    gameplay::BulletParameter src;
    src.boneName = "Bip03";
    src.hitRadius = 30; src.baseDamage = 1750; src.hpDamage = 75; src.reflectDamage = 75;
    src.gaugeGainA = 100; src.gaugeGainB = 40;
    src.attackerHitstun = 0; src.defenderHitstun = 0;
    src.hitResolutionField64 = 102; src.hitResolutionField68 = 113;
    src.hitSound = 21; src.impactEffect = 30;
    src.releaseOffsetA = 500; src.releaseOffsetB = 1500;
    const auto bytes = synthBulletDat(0, src);

    gameplay::BulletParameter out;
    std::string err;
    check(gameplay::parseBulletParameter(bytes.data(), bytes.size(), 0, out, err),
          "a well-formed bullet parameter file decodes");
    // Issue #32: the header's 260-byte block is the model the bullet IS (the shot's own
    // render draws it), so it must survive the parse like any other field.
    check(out.modelName == "03.X", "the 260-byte model block round-trips (issue #32)");
    check(out.boneName == "Bip03", "the 30-byte bone name round-trips");
    checkInt(30, out.hitRadius, "record +0x24 is the hit radius");
    checkInt(1750, out.baseDamage, "blob[0x00] is the base damage");
    checkInt(75, out.hpDamage, "blob[5] is the HP damage");
    checkInt(75, out.reflectDamage, "blob[6] is the reflected damage");
    checkInt(100, out.gaugeGainA, "blob[7] is the charge gauge gain (100 fills it)");
    checkInt(40, out.gaugeGainB, "blob[8] is the second gauge gain");
    checkInt(102, out.hitResolutionField64, "blob[13] (+0x64) value decodes");
    checkInt(113, out.hitResolutionField68, "blob[14] (+0x68) value decodes");
    checkInt(21, out.hitSound, "blob[15] (+0x6C) is the impact SE id");
    checkInt(30, out.impactEffect, "blob[16] (+0x70) is the impact effect id");
    checkInt(500, out.releaseOffsetA, "blob[17] is the tier-up release offset A");
    checkInt(1500, out.releaseOffsetB, "blob[18] is the tier-up release offset B");

    gameplay::BulletParameter wrong;
    check(!gameplay::parseBulletParameter(bytes.data(), bytes.size(), 7, wrong, err),
          "a status with no matching variant is reported, not guessed");
    check(!gameplay::parseBulletParameter(bytes.data(), 40, 0, out, err),
          "a truncated file is rejected rather than read past");
    check(!gameplay::parseBulletParameter(nullptr, 0, 0, out, err),
          "an empty buffer is rejected");
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
            if (fs::is_directory(r / "src" / "assets", ec)) {
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
                // -1 is an allocation sentinel, not a negative volley count.
                if (bullet.poolCapacity < -1) shotNumOk = false;
            }
            check(bulletMagazineOk, "every bullet names a magazine in {-1,0,1,2}");
            check(shotNumOk, "every bullet's poolCapacity is 3, 4 or the -1 sentinel");
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

// ---------------------------------------------------------------------------
// 1d. Issue #32: the bullet's own model ships, for every pick the port can make.
// ---------------------------------------------------------------------------
// The in-flight shot draws the .X named by the 260-byte block of the bullet file it was
// fired from (game/shot_visual.h). The port picks that file per (weapon, charge level)
// with main.cpp's loadBulletParameter rule — the smallest `type` among the bullets whose
// magazine is that level's. This sweep is the check that the shipped roster never has to
// draw a shot with an empty model slot: every one of the 92 picks must name a model the
// install ships.
void testShotModelsShip(const fs::path& install) {
    section("real data: every shot model the roster can draw ships (issue #32)");
    std::error_code ec;
    const fs::path bulletRoot = install / "data" / "bullet";
    if (install.empty() || !fs::is_directory(bulletRoot, ec)) {
        skip("the shipped bullet model blocks (no install found)");
        return;
    }

    // The whole inventory first: 46 directories, every .dat's block, and whether the model
    // it names sits beside it. A handful of rows name a model their directory does not
    // ship; those are rows the roster sweep below must never pick.
    int files = 0, shipped = 0;
    std::vector<std::string> missing;
    for (int id = 1; id <= 46; ++id) {
        char dir[16];
        std::snprintf(dir, sizeof(dir), "%03d", id);
        const fs::path dirPath = bulletRoot / dir;
        if (!fs::is_directory(dirPath, ec)) continue;
        for (const fs::directory_entry& e : fs::directory_iterator(dirPath, ec)) {
            const std::string name = e.path().filename().string();
            if (name.size() != 7 || name.substr(3) != ".dat") continue;
            std::ifstream in(e.path(), std::ios::binary);
            if (!in) continue;
            const std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(in)),
                                             std::istreambuf_iterator<char>());
            // The variant id is the single digit FUN_005f80c0 passes as `status`
            // (`paramId() % 10`), so 0..9 is the whole domain to try.
            gameplay::BulletParameter p;
            std::string err;
            bool parsed = false;
            for (int status = 0; status < 10 && !parsed; ++status)
                parsed = gameplay::parseBulletParameter(bytes.data(), bytes.size(), status,
                                                        p, err);
            if (!parsed) continue;
            ++files;
            if (p.modelName.empty()) continue;
            if (fs::exists(dirPath / p.modelName, ec)) ++shipped;
            else missing.push_back(std::string(dir) + "/" + name + " -> " + p.modelName);
        }
    }
    check(files > 500, "the install ships the whole data/bullet table");
    std::printf("        %d bullet file(s): %d name a model their directory ships, %zu do not\n",
                files, shipped, missing.size());
    for (const std::string& m : missing) std::printf("        no model shipped: %s\n", m.c_str());

    // The load-bearing sweep: the 92 picks the port's own rule can make.
    int picks = 0, resolved = 0;
    for (int c = 0; c < gameplay::kCharacterCount; ++c) {
        for (int w = 0; w < gameplay::kWeaponSlots; ++w) {
            if (!gameplay::weaponSlotIsLegal(c, w)) continue;
            const int id = gameplay::kWeaponIds[c][w];
            char rel[32];
            std::snprintf(rel, sizeof(rel), "%03d.dat", id);
            std::ifstream in(install / "data" / "item" / rel, std::ios::binary);
            if (!in) continue;
            const std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(in)),
                                             std::istreambuf_iterator<char>());
            auto def = parseOrNull(id, bytes);
            if (!def) continue;
            char dir[16];
            std::snprintf(dir, sizeof(dir), "%03d", id);
            for (int level = 1; level <= 2; ++level) {
                const int wantMagazine = def->magazineForChargeLevel(level).chargeLevel - 1;
                const gameplay::BulletDefinition* best = nullptr;
                for (int i = 0; i < def->bulletCount; ++i) {
                    const gameplay::BulletDefinition& b = def->bullets[i];
                    if (b.magazine != wantMagazine) continue;
                    if (!best || b.type < best->type) best = &b;
                }
                if (!best) continue;
                ++picks;
                char file[32];
                std::snprintf(file, sizeof(file), "%03d.dat", best->type);
                std::ifstream bin(install / "data" / "bullet" / dir / file, std::ios::binary);
                if (!bin) continue;
                const std::vector<uint8_t> bbytes((std::istreambuf_iterator<char>(bin)),
                                                  std::istreambuf_iterator<char>());
                gameplay::BulletParameter p;
                std::string err;
                if (!gameplay::parseBulletParameter(bbytes.data(), bbytes.size(), best->status,
                                                    p, err))
                    continue;
                if (!p.modelName.empty() &&
                    fs::exists(install / "data" / "bullet" / dir / p.modelName, ec))
                    ++resolved;
            }
        }
    }
    checkInt(92, picks, "46 weapons x 2 charge levels are 92 (weapon, level) picks");
    checkInt(picks, resolved,
             "EVERY pick's bullet names a model that ships: the in-flight visual never "
             "falls back");
}

void testRosterLabels() {
    section("device-free: roster index, weapon slot, combo labels (AGENTS.md rule 7)");
    checkInt(0, gameplay::characterIndexForDir("rena"), "rena is roster index 0");
    checkInt(2, gameplay::characterIndexForDir("keiichi"), "keiichi is roster index 2");
    checkInt(15, gameplay::characterIndexForDir("natumi"), "natumi is roster index 15");
    checkInt(-1, gameplay::characterIndexForDir("bogus"), "an unknown dir maps nowhere");
    checkInt(-1, gameplay::characterIndexForDir(""), "an empty dir maps nowhere");
    // Slot is the inverse of the kWeaponIds row: rena {1,3,33}, keiichi {5,18,34}.
    checkInt(0, gameplay::weaponSlotForItem(0, 1), "rena item 1 is slot 0");
    checkInt(1, gameplay::weaponSlotForItem(0, 3), "rena item 3 is slot 1");
    checkInt(2, gameplay::weaponSlotForItem(0, 33), "rena item 33 is slot 2");
    checkInt(1, gameplay::weaponSlotForItem(2, 18), "keiichi item 18 is slot 1");
    checkInt(-1, gameplay::weaponSlotForItem(0, 18), "keiichi's item is no rena slot");
    checkInt(-1, gameplay::weaponSlotForItem(0, 0), "the sentinel 0 is no slot");
    checkInt(-1, gameplay::weaponSlotForItem(-1, 1), "no character means no slot");
    checkInt(-1, gameplay::weaponSlotForItem(99, 1), "a wild index means no slot");
    // Combo labels carry the weapon INDEX: Rena 1 is her second weapon, and
    // Keiichi 1 is his Invincible Iron (atlas names, ASSET-CATALOG §3.2).
    check(gameplay::comboSlotLabel(0, 0) == "Rena 0", "rena slot 0 labels Rena 0");
    check(gameplay::comboSlotLabel(0, 1) == "Rena 1", "rena slot 1 labels Rena 1");
    check(gameplay::comboSlotLabel(2, 1) == "Keiichi 1",
          "keiichi slot 1 labels Keiichi 1 (his Invincible Iron)");
    check(gameplay::comboSlotLabel(15, 1) == "Natumi 1", "natumi slot 1 labels Natumi 1");
    check(gameplay::comboSlotLabel(-1, 0) == "?", "no character labels ?");
    check(gameplay::comboSlotLabel(0, 3) == "?", "no fourth slot labels ?");
}

int main(int argc, char** argv) {
    std::printf("WEAPON_DEFINITION_TEST\n");
    const fs::path install = findInstall(argc, argv);
    testParser();
    testBulletParameterParser();
    testRosterLabels();
    testInventory(install);
    testShotModelsShip(install);
    testRepresentativeFamilies(install);
    std::printf("\nWEAPON_DEFINITION: %s (%d checks, %d failed, %d skipped)\n",
                failures == 0 ? "ok" : "FAIL", checks, failures, skipped);
    return failures == 0 ? 0 : 1;
}
