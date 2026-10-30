#pragma once
// The one door to the vendored simulation (src/sim/core). Nothing else includes the core, so
// its headers, its global names and its 284k lines stay out of every other translation unit.
#include <array>
#include <cstdint>
#include <functional>
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
    int costume = 0;   // the rig variant: 0 is data/<name>, N is data/<name>_<'A'+N>
    unsigned specialMode = 1;  // the hypermode's +0x318 value: 0 Oyashiro, 1 Friendship, 2 Kakera
};

struct BattleConfig {
    std::string gameDir;           // holds daybreak00.dat and friends
    std::array<Slot, 4> slots{};   // slots 0-1 and 2-3 are the two teams
    unsigned stage = 1;
    std::uint32_t seed = 1;
    unsigned timeLimitSeconds = 0;  // 0 keeps the match's own rule
    // Health, gauge, blue and red limits, in percent. The core rejects values its menus cannot
    // produce (configure_match_values).
    std::array<int, 4> rules{{100, 100, 100, 100}};
};

// Buttons as the original's physical bits, before battle_button_carrier.
enum Button : unsigned { Jump = 1, Melee = 2, Shoot = 4, Target = 8, Guard = 32 };

struct SlotInput {
    int x = 0;  // -1 left, +1 right
    int z = 0;  // -1 forward, +1 back
    unsigned buttons = 0;
};
using Inputs = std::array<SlotInput, 4>;

struct MagazineState {
    int rounds = 0, capacity = 0;
};

// A row-major D3D matrix: the same 16 floats in memory as a glm::mat4 of the same transform.
using Matrix = std::array<float, 16>;

// The slot's hypermode meter (BattleSpecialGauges). `mode` is the original's +0x318 value.
struct SpecialState {
    unsigned mode = 0;
    bool active = false;
    int charge = 0, limit = 0;
};

struct MatchState {
    int winner = -1;                       // the winning team once the round is decided
    bool finished = false;                 // the result screens are ready
    bool timed = false;
    int remainingTicks = 0;
    std::array<float, 2> score{}, limit{};  // the balloon percentages the HUD shows
};

// One live projectile, in the render pass's terms (projectile_render_pose).
struct ProjectileState {
    int owner = 0, item = 0, row = 0;
    std::array<float, 3> position{};
    Matrix modelMatrix{};
    bool billboard = false;
    int tint = 0;
};

// What the last tick asked the presentation to do, after the core's audibility rules.
struct BattleEvents {
    struct Effect { int actor, id; std::array<float, 3> position, direction; };
    struct Sound { int actor, id; bool positional; std::array<float, 3> position; };
    struct Voice { int actor; std::string path; };
    std::vector<Effect> effects;
    std::vector<Sound> sounds;
    std::vector<Voice> voices;
};

struct ActorState {
    std::array<float, 3> position{};
    float heading = 0.f;
    unsigned state = 0;    // the move row, e.g. 300 or 118
    unsigned phase = 0;    // the section within the row
    unsigned frame = 0;    // the section's animation clock
    int hp = 0;
    int gauge = 0;         // +0x834, 0..1000
    bool grounded = false;
    int target = 0;        // the slot this actor is locked on to
};

// The bound animation sets. The two channels are the rig's lower and upper body; a row usually
// binds the same set to both.
struct ActorAnimation {
    unsigned lowerSet = 0, upperSet = 0;
    float lowerTime = 0.f, upperTime = 0.f;  // seconds into each set
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
    ActorAnimation animation(unsigned slot) const;
    SpecialState special(unsigned slot) const;
    MatchState match_state() const;
    const BattleEvents& events() const;
    void for_each_projectile(const std::function<void(const ProjectileState&)>& visit) const;
    // The item models the actor holds, -1 for an empty hand.
    std::array<int, 2> held_models(unsigned slot) const;
    // The weapon's first two magazines, as the HUD reads them.
    std::array<MagazineState, 2> magazines(unsigned slot) const;
    // Where the actor's root sits in the world.
    Matrix actor_world(unsigned slot) const;
    // Every bone in model space, in the rig's frame order, with the core's implicit root at 0.
    void bone_poses(unsigned slot, std::vector<std::string>& names, std::vector<Matrix>& model) const;
    // Every row the slot's NN.dat declares, for coverage reports.
    std::vector<unsigned> declared_rows(unsigned slot) const;
    // FNV-1a over every completed tick's actor states, projectile count and RNG cursor.
    std::uint64_t hash() const;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};

}  // namespace sim
