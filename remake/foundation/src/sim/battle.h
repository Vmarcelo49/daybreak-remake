#pragma once
// The one door to the vendored simulation (src/sim/core). Nothing else includes the core, so
// its headers, its global names and its 284k lines stay out of every other translation unit.
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace sim {

// Indices are the core's (core/character_names.hpp), which differ from the data-directory
// order in gameplay::kCharacterDirs. A slot is always a character AND a weapon.
struct Slot {
    int character = 0;
    int weapon = 0;
    bool cpu = true;
};

struct BattleConfig {
    std::string gameDir;           // holds daybreak00.dat and friends
    std::array<Slot, 4> slots{};   // slots 0-1 and 2-3 are the two teams
    unsigned stage = 1;
    std::uint32_t seed = 1;
    unsigned timeLimitSeconds = 0;  // 0 keeps the match's own rule
};

// Buttons as the original's physical bits, before battle_button_carrier.
enum Button : unsigned { Jump = 1, Melee = 2, Shoot = 4, Target = 8, Guard = 32 };

struct SlotInput {
    int x = 0;  // -1 left, +1 right
    int z = 0;  // -1 forward, +1 back
    unsigned buttons = 0;
};
using Inputs = std::array<SlotInput, 4>;

struct ActorState {
    std::array<float, 3> position{};
    float heading = 0.f;
    unsigned state = 0;    // the move row, e.g. 300 or 118
    unsigned phase = 0;    // the section within the row
    unsigned frame = 0;    // the section's animation clock
    int hp = 0;
    int gauge = 0;         // +0x834, 0..1000
    bool grounded = false;
};

int character_count();
int weapon_count(int character);
std::string character_name(int character);

class Battle {
public:
    // Throws std::exception on an invalid combo or missing game data.
    explicit Battle(const BattleConfig& config);
    ~Battle();
    Battle(const Battle&) = delete;
    Battle& operator=(const Battle&) = delete;

    void step(const Inputs& inputs);

    ActorState actor(unsigned slot) const;
    unsigned tick() const;
    unsigned scene_phase() const;
    unsigned live_projectiles() const;
    bool match_finished() const;
    // Every row the slot's NN.dat declares, for coverage reports.
    std::vector<unsigned> declared_rows(unsigned slot) const;
    // FNV-1a over every completed tick's actor states, projectile count and RNG cursor.
    std::uint64_t hash() const;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};

}  // namespace sim
