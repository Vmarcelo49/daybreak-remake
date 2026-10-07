// Inventory bundle-winning combat-record bits through the runtime asset seam.
#include "assets/asset_source.h"
#include "gameplay/character_moves.h"
#include "gameplay/weapon_definition.h"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "usage: audit_attack_flags <game-install> [mask]\n");
        return 2;
    }
    const int mask = argc > 2 ? static_cast<int>(std::strtol(argv[2], nullptr, 0)) : 8;
    auto& source = fnd::assets::assetSource();
    if (!source.openInstall(argv[1])) {
        std::fprintf(stderr, "could not open bundles\n");
        return 2;
    }
    int total = 0, set = 0, setWithRadius = 0;
    for (int character = 0; character < gameplay::kCharacterCount; ++character) {
        for (int slot = 0; slot < gameplay::weaponCountForCharacter(character); ++slot) {
            char key[128];
            std::snprintf(key, sizeof key, "data/%s/%02d.dat", gameplay::kCharacterDirs[character], slot);
            std::vector<uint8_t> bytes;
            if (!source.read(key, bytes)) {
                std::fprintf(stderr, "missing combo table %s\n", key);
                return 1;
            }
            gameplay::CharacterMoves moves;
            std::string error;
            if (!moves.parse(bytes.data(), bytes.size(), error)) {
                std::fprintf(stderr, "parse error %s: %s\n", key, error.c_str());
                return 1;
            }
            const int item = gameplay::kWeaponIds[character][slot];
            if (moves.weapon_id() != item) {
                std::fprintf(stderr, "item mismatch %s: %d != %d\n", key,
                             moves.weapon_id(), item);
                return 1;
            }
            for (int moveId = 0; moveId < gameplay::CharacterMoves::kMaxMoves; ++moveId) {
                const auto* move = moves.find(moveId);
                if (!move) continue;
                for (int phase = 0; phase < move->sectionCount; ++phase) {
                    const auto& section = move->phases[phase];
                    for (int record = 0; record < section.entryCount; ++record) {
                        const auto& entry = section.entries[record];
                        ++total;
                        if (entry.attackFlags & mask) {
                            ++set;
                            if (entry.hitRadius != 0) ++setWithRadius;
                            std::printf("%s+%d item=%03d set=%d move=%d phase=%d record=%d "
                                        "frame=%d bone=%s radius=%d state=0x%08x attack=0x%08x\n",
                                        gameplay::kCharacterDirs[character], slot, item,
                                        section.setIndex, move->id, phase, record,
                                        entry.activeFrame, entry.boneName.c_str(), entry.hitRadius,
                                        static_cast<unsigned>(entry.stateFlags),
                                        static_cast<unsigned>(entry.attackFlags));
                        }
                    }
                }
            }
        }
    }
    std::printf("source=bundle-first records=%d mask=0x%x set=%d set_radius_nonzero=%d clear=%d\n",
                total, mask, set, setWithRadius, total - set);
}
