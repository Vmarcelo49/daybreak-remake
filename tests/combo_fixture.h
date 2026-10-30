#pragma once

#include "assets/asset_source.h"
#include "assets/xmodel.h"
#include "battle/character_moves.h"
#include "battle/weapon_definition.h"

#include <array>
#include <cstdlib>
#include <filesystem>
#include <memory>
#include <vector>

namespace test {

inline std::string gameInstall() {
    if (const char* configured = std::getenv("GAME_DIR"))
        if (std::filesystem::exists(std::filesystem::path(configured) / "daybreak00.dat"))
            return configured;
    for (auto path = std::filesystem::current_path(); !path.empty(); path = path.parent_path()) {
        for (const auto& candidate : {path, path / "Higurashi-Daybreak"})
            if (std::filesystem::exists(candidate / "daybreak00.dat")) return candidate.string();
        if (path == path.parent_path()) break;
    }
    return {};
}

// AssetSource's winning bundle, the equipped item, and the named rig are one
// fixture. A table without its controller cannot advance phase-local records.
struct Combo {
    gameplay::CharacterMoves moves;
    gameplay::WeaponDefinition weapon;
    xm::Model model;
    std::array<gameplay::BulletParameter,64> bullets;
    std::array<bool,64> hasBullet{};

    bool load(int character, int slot, std::string& error) {
        auto& source = fnd::assets::assetSource();
        if (!source.bundlesOpen() && !source.openInstall(gameInstall())) return false;
        std::vector<uint8_t> bytes;
        char path[100];
        std::snprintf(path,sizeof path,"data/%s/%02d.dat",gameplay::kCharacterDirs[character],slot);
        if (!source.read(path,bytes) || !moves.parse(bytes.data(),bytes.size(),error)) return false;
        moves.set_character_index(character);
        const int item = gameplay::kWeaponIds[character][slot];
        if (moves.weapon_id() != item) { error = "NN.dat/item mismatch"; return false; }
        std::snprintf(path,sizeof path,"data/item/%03d.dat",item);
        if (!source.read(path,bytes) || !weapon.parse(item,bytes.data(),bytes.size(),error)) return false;
        const auto rig = std::string("data/") + gameplay::kCharacterDirs[character] + "/" + moves.model_name();
        if (!source.read(rig,bytes)) return false;
        model = xm::loadMemory(bytes.data(),bytes.size());
        if (model.anims.empty()) { error = "missing rig animation sets"; return false; }
        if (weapon.bulletCount > 64) { error = "bullet row capacity exceeded"; return false; }
        for (int row = 0; row < weapon.bulletCount; ++row) {
            std::snprintf(path,sizeof path,"data/bullet/%03d/%03d.dat",item,weapon.bullets[row].type);
            if (!source.read(path,bytes)) continue;
            if (!gameplay::parseBulletParameter(bytes.data(),bytes.size(),weapon.bullets[row].status,
                                                bullets[static_cast<size_t>(row)],error)) return false;
            hasBullet[static_cast<size_t>(row)] = true;
        }
        return true;
    }
};
} // namespace test
