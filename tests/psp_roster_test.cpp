// The PSP roster: indices 16..18 (Satoshi, Miyoko, Okonogi), four weapon slots each, on their own
// table — D-1 in docs/PSP-CHARACTERS-WORKLOG.md. What this pins, in order:
//
//   * the PC tables did not move (kCharacterCount, kWeaponSlots, kWeaponIds, the 46-combo sweep
//     in weapon_definition_test stays literally true);
//   * the three answer through the roster accessors, with item ids 101..112;
//   * the roster is 19 only while the data is mounted;
//   * a participant's weapon id is bounds-checked, so a stale pair cannot read past the tables;
//   * the launch carries the right identity — "data/satoshi:0" with item 101..104 — and reports a
//     clear error, not a crash, when the item data is not there yet.
//
// The last part needs a real data/item/<NNN>.dat to parse, so it copies the install's own item 1
// into a temp psp-data root and skips itself (exit 77) without a game install.
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <string>
#include <vector>

#include "assets/asset_source.h"
#include "battle/weapon_definition.h"
#include "frontend/frontend_launch.h"
#include "frontend/participants.h"

#define CHECK(x) do { if (!(x)) { std::fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #x); return 1; } } while (false)

namespace fs = std::filesystem;
using namespace gameplay;

namespace {

// The same discovery the other install-backed tests use (tests/combo_fixture.h's gameInstall).
std::string gameInstall() {
    if (const char* configured = std::getenv("GAME_DIR"))
        if (fs::exists(fs::path(configured) / "daybreak00.dat")) return configured;
    for (auto path = fs::current_path(); !path.empty(); path = path.parent_path()) {
        for (const auto& candidate : {path, path / "Higurashi-Daybreak"})
            if (fs::exists(candidate / "daybreak00.dat")) return candidate.string();
        if (path == path.parent_path()) break;
    }
    return {};
}

bool writeFile(const fs::path& file, const void* data, size_t size) {
    fs::create_directories(file.parent_path());
    std::FILE* out = std::fopen(file.string().c_str(), "wb");
    if (!out) return false;
    const size_t wrote = std::fwrite(data, 1, size, out);
    std::fclose(out);
    return wrote == size;
}

}  // namespace

int main() {
    // --- the PC tables are exactly what they always were (D-1) --------------------------------
    CHECK(kCharacterCount == 16 && kWeaponSlots == 3);
    CHECK(kWeaponIds[0][2] == 33 && kWeaponIds[13][1] == 28 && kWeaponIds[15][2] == 0);
    CHECK(weaponCountForCharacter(16) == 0 && weaponSlotIsLegal(16, 0) == false);
    CHECK(std::string(kCharacterDirs[0]) == "rena" && std::string(kCharacterDirs[15]) == "natumi");
    CHECK(characterIndexForDir("satoshi") == -1);   // the PC-only form stays PC-only

    // --- the three, as pure table facts ------------------------------------------------------
    CHECK(kPspCharacterCount == 3 && kRosterCharacterCount == 19 && kPspWeaponSlots == 4);
    CHECK(kPspItemIdFirst == 101);
    const char* dirs[3] = {"satoshi", "miyoko", "okonogi"};
    const int firstIds[3] = {101, 105, 109};
    const int pspNumbers[3] = {17, 18, 19};
    for (int i = 0; i < 3; ++i) {
        const int character = kCharacterCount + i;
        const PspRosterEntry* entry = pspRosterEntry(character);
        CHECK(entry != nullptr);
        CHECK(std::string(entry->dir) == dirs[i]);
        CHECK(entry->pspCharacter == pspNumbers[i]);
        CHECK(std::string(rosterCharacterDir(character)) == dirs[i]);
        CHECK(rosterWeaponCount(character) == 4);
        CHECK(weaponSlotForItem(character, entry->itemIds[0]) == 0);
        CHECK(weaponSlotForItem(character, entry->itemIds[3]) == 3);
        CHECK(weaponSlotForItem(character, entry->itemIds[3] + 1) == -1);
        for (int slot = 0; slot < 4; ++slot) {
            CHECK(entry->itemIds[slot] == firstIds[i] + slot);
            CHECK(rosterWeaponItemId(character, slot) == firstIds[i] + slot);
        }
        CHECK(rosterWeaponItemId(character, 4) == 0);       // four slots, not five
        CHECK(rosterCharacterIndexForDir(dirs[i]) == character);
        CHECK(comboSlotLabel(character, 4) == "?");   // four slots, so 4 is not a label
    }
    CHECK(pspRosterEntry(15) == nullptr && pspRosterEntry(19) == nullptr);
    // "Satoshi 3": the combo label, naming the weapon INDEX like every PC combo does.
    CHECK(comboSlotLabel(16, 0) == "Satoshi 0" && comboSlotLabel(17, 1) == "Miyoko 1" &&
          comboSlotLabel(18, 2) == "Okonogi 2");
    CHECK(comboSlotLabel(0, 2) == "Rena 2");   // unchanged for the PC cast
    CHECK(rosterWeaponItemId(0, 2) == 33 && rosterWeaponItemId(15, 2) == 0);
    CHECK(rosterWeaponItemId(-1, 0) == 0 && rosterWeaponItemId(19, 0) == 0 &&
          rosterWeaponItemId(16, -1) == 0);
    CHECK(rosterWeaponCount(-1) == 0 && rosterWeaponCount(19) == 0);

    // --- availability: the roster is 19 only while the data is mounted ------------------------
    CHECK(!pspRosterMounted());
    CHECK(rosterCharacterCount() == kCharacterCount);
    CHECK(ui::frontendCharacterDirectory(16) == nullptr);
    setPspRosterMounted(true);
    CHECK(rosterCharacterCount() == kRosterCharacterCount);
    CHECK(std::string(ui::frontendCharacterDirectory(16)) == "satoshi");
    CHECK(ui::frontendCharacterDirectory(19) == nullptr);
    setPspRosterMounted(false);

    // --- a participant's weapon id cannot read past the tables --------------------------------
    {
        ui::FrontendSlot slots[ui::kParticipantCount];
        slots[0].character = 16; slots[0].weapon = 3;
        slots[2].character = 0;  slots[2].weapon = 2;
        ui::Participant roster[ui::kParticipantCount];
        CHECK(ui::buildParticipants(slots, roster) == 2);
        CHECK(roster[0].weaponId == 104 && roster[0].combo() == "Satoshi 3");
        CHECK(roster[1].weaponId == 33 && roster[1].combo() == "Rena 2");
        // A weapon slot the row does not have: 0, not a read past the row.
        slots[0].weapon = 9;
        CHECK(ui::buildParticipants(slots, roster) == 2);
        CHECK(roster[0].weaponId == 0);
    }

    // --- the launch: right identity, and an explicit error before the data exists -------------
    const std::string game = gameInstall();
    if (game.empty()) {
        std::printf("psp_roster_test: SKIP the launch half (no game install; GAME_DIR or "
                    "Higurashi-Daybreak)\n");
        return 77;
    }
    const fs::path root = fs::temp_directory_path() / "daybreak-psp-roster-test";
    std::error_code ec;
    fs::remove_all(root, ec);
    // A real item file, under the PSP id the launch will ask for: the parser is the real one, so
    // the bytes have to be the format data/item/NNN.dat actually is.
    std::vector<uint8_t> item;
    auto& source = fnd::assets::assetSource();
    CHECK(source.openInstall(game));
    CHECK(source.read("data/item/001.dat", item) && !item.empty());
    CHECK(writeFile(root / "data/item/104.dat", item.data(), item.size()));
    CHECK(source.mountDataRoot(root.u8string()));
    gameplay::setPspRosterMounted(true);

    ui::FrontendState state;
    state.stage = 21;                       // fixed, so the launch names one stage path
    state.slots[0].character = 16;          // Satoshi, weapon d
    state.slots[0].weapon = 3;
    state.slots[0].costume = 2;
    state.slots[2].character = 0;           // Rena, her first
    state.slots[2].weapon = 0;
    ui::FrontendLaunch launch;
    std::string error;
    CHECK(ui::frontendLaunch(state, launch, error, 1u));
    CHECK(launch.fighterCount == 2);
    CHECK(launch.fighters[0].character == "data/satoshi:2");
    CHECK(launch.fighters[0].weaponId == 104);
    CHECK(launch.fighters[0].weapon.rfind("data/item/", 0) == 0);
    CHECK(launch.fighters[1].character == "data/rena:0" && launch.fighters[1].weaponId == 1);

    // The same selection without the converted data: the roster no longer offers index 16, so the
    // launch refuses with the one message the front end has for it — a clear failure, not a crash
    // and not an out-of-range read.
    gameplay::setPspRosterMounted(false);
    error.clear();
    CHECK(!ui::frontendLaunch(state, launch, error, 1u));
    CHECK(error == "front end: invalid character or weapon choice");

    // Mounted but the item file is missing: the error names the file the extractor has not written
    // yet, which is the failure a player sees until Track A/C produce the weapon data.
    gameplay::setPspRosterMounted(true);
    source.clearDataRoots();
    CHECK(source.mountDataRoot(root.u8string()));
    fs::remove(root / "data/item/104.dat", ec);
    error.clear();
    CHECK(!ui::frontendLaunch(state, launch, error, 1u));
    CHECK(error == "front end: cannot read data/item/104.dat (Satoshi 3)");

    source.clearDataRoots();
    source.closeInstall();
    fs::remove_all(root, ec);
    std::printf("psp_roster_test: roster, ids, label, participant guard, launch identity and its "
                "two failure paths\n");
    return 0;
}
