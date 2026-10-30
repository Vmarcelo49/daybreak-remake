#include "sim/battle.h"

#include "basic_battle_roster_assets.hpp"
#include "battle_cpu_driver.hpp"
#include "battle_cpu_obstacle.hpp"
#include "battle_input_buttons.hpp"
#include "battle_presentation_input.hpp"
#include "battle_stage_collision_assets.hpp"
#include "battle_visual_effects.hpp"
#include "battle_voice_inventory.hpp"
#include "battle_world_motion.hpp"
#include "character_names.hpp"
#include "development_animated_combat.hpp"
#include "local_normal_projectiles.hpp"
#include "stage_environment.hpp"
#include "stage_floor_collision.hpp"
#include "stage_wall_collision.hpp"

#include <cstdio>
#include <filesystem>
#include <stdexcept>

namespace sim {

using namespace daybreak;

int character_count() { return static_cast<int>(character_names.size()); }

// load_character_asset_files: characters 0-13 carry three weapons, 14-15 carry two.
int weapon_count(int character) {
    if (character < 0 || character >= character_count()) return 0;
    return character < 14 ? 3 : 2;
}

std::string character_name(int character) {
    if (character < 0 || character >= character_count()) throw std::out_of_range("sim: character");
    return std::string(character_names[static_cast<size_t>(character)]);
}

namespace {

LocalBattleRoster make_roster(const BattleConfig& config) {
    LocalBattleRoster roster;
    unsigned controllers = 0;
    for (unsigned i = 0; i < 4; ++i) {
        const Slot& slot = config.slots[i];
        if (slot.weapon < 0 || slot.weapon >= weapon_count(slot.character))
            throw std::invalid_argument("sim: slot " + std::to_string(i) + " is not a legal combo");
        roster.character[i] = slot.character;
        roster.weapon[i] = slot.weapon;
        if (slot.cpu) {
            roster.owner[i] = 4;  // BattleCpuDriver::configure: owners >= 4 are CPU
        } else {
            roster.owner[i] = static_cast<int>(controllers);
            roster.controller_actor[controllers] = static_cast<int>(i);
            roster.controlled_slots[controllers++] = i;
        }
    }
    roster.controlled_count = controllers;
    roster.stage = config.stage;
    BattleRandom random;
    random.seed(config.seed);
    roster.simulation_random = random;
    return roster;
}

AssetSearchPath mount_assets(const std::string& gameDir) {
    AssetSearchPath assets;
    for (const char* name : {"daybreak07.dat", "daybreak04.dat", "daybreak00.dat"})
        assets.append((std::filesystem::path(gameDir) / name).string());
    return assets;
}

std::string stage_path(unsigned stage) {
    if (stage > 99) throw std::invalid_argument("sim: stage index");
    char path[64];
    std::snprintf(path, sizeof path, "data/stage%02u", stage);
    return path;
}

}  // namespace

struct Battle::Impl {
    AssetSearchPath assets;
    LocalBattleRoster roster;
    LocalNormalProjectiles projectiles;
    BattleVisualEffects effects;
    BattleCpuDriver cpu;
    BasicBattleRosterAssets files;
    DevelopmentAnimatedCombat combat;
    BattleStageCollisionAssets collision;
    BattleWorld world;
    unsigned ticks = 0;
    bool victoryResolved = false;
    std::uint64_t digest = 1469598103934665603ull;

    explicit Impl(const BattleConfig& config)
        : assets(mount_assets(config.gameDir)),
          roster(make_roster(config)),
          projectiles(assets),
          effects(assets),
          files(load_basic_battle_roster_assets(assets, roster)),
          combat(files.assets, files.actions),
          collision(BattleStageCollisionAssets::load(assets, stage_path(config.stage))) {
        cpu.configure(roster);
        // RuntimeBattle's constructor, in its order. The voice inventory is not optional: its
        // selection draws from the battle RNG (queue_voice), so leaving it out changes the match.
        combat.configure_offline_pause(true);
        combat.configure_actor_texture_styles(roster.flags);
        auto voices = std::make_shared<BattleVoiceInventory>(assets);
        for (unsigned i = 0; i < 4; ++i)
            voices->configure(i, static_cast<unsigned>(roster.character[i]),
                              combat.actor_assets(i).parameters[3], roster.option[i], roster.flags[i]);
        combat.configure_voice_selection(voices, roster.owner);
        combat.configure_battle_start(roster.simulation_random);
        combat.use_recovered_melee_timing = true;
        combat.configure_match_values(roster.rule_values, roster.story_mode);
        for (unsigned i = 0; i < 4; ++i) combat.special_gauges[i].mode = roster.costume[i];
        combat.match.primary_actor = local_battle_result_primary_controller(roster);
        combat.match.story_mode = roster.story_mode;
        if (config.timeLimitSeconds) combat.match.configure_time_limit(config.timeLimitSeconds * 60u);
        const auto env = StageEnvironment::decode(assets.read(stage_path(config.stage) + "/env.dat").bytes);
        world.initialize(env.positions, {}, {}, {});
        combat.configure_respawn(env.respawn_bounds());
    }

    void mix(const void* data, size_t size) {
        const auto* bytes = static_cast<const unsigned char*>(data);
        for (size_t i = 0; i < size; ++i) {
            digest ^= bytes[i];
            digest *= 1099511628211ull;
        }
    }

    // The presentation half of RuntimeBattle::advance_scene_presentation that touches the
    // simulation: both calls draw from the battle RNG, once, when the result screen opens.
    void resolve_victory() {
        const auto& match = combat.match;
        if (victoryResolved || !match.ready || match.presentation_phase != 1) return;
        combat.victory_line([&](const std::string& p) { return assets.contains(p); },
                            [&](const std::string& p) { return assets.read(p).bytes; });
        combat.finalize_awards();
        victoryResolved = true;
    }

    // RuntimeBattle::update's non-fixture path, without its audio, camera and render services.
    void step(const net::InputChannel::Frame& inputs) {
        const auto buttons = local_battle_result_buttons(roster, inputs);
        StageWallCollision wall(collision.actor);
        StageFloorCollision floor(collision.actor);
        const auto& cpuFrame = cpu.advance(combat, world, BattleCpuObstacleQuery(collision.actor));
        auto scripts = [&]() {
            projectiles.spawn_requests(combat, world);
            projectiles.advance_scripts(combat, world, collision.projectile, combat.owner_script_mask());
        };
        auto poolMotion = [&](unsigned pool) { projectiles.advance_motion(world, &collision.projectile, 1u << pool); };
        auto globalMotion = [&]() { projectiles.advance_motion(world, &collision.projectile, 15, true); };
        combat.move_with_projectile_scripts(world, inputs, wall, floor, scripts, 0, &cpuFrame, &cpu, {},
                                            poolMotion, globalMotion, &buttons, [] {},
                                            [&] { resolve_victory(); }, [] {});
        if (!combat.offline_pause.paused) {
            combat.update_with_projectile_contacts(
                world, inputs,
                [&](unsigned pool) { projectiles.resolve_pool_contacts(combat, world, pool, true); },
                &cpuFrame, &buttons);
            projectiles.advance_scripts(combat, world, collision.projectile, 15, true, true);
            effects.spawn_requests(combat);
            effects.advance(&world);
        }
        ++ticks;
        for (unsigned i = 0; i < 4; ++i) {
            const auto& a = world.actors[i];
            mix(a.position.data(), sizeof(float) * 3);
            mix(&a.heading, sizeof a.heading);
            const unsigned state = combat.current_action_state(i), hp = combat.health[i];
            const int gauge = combat.gauge[i];
            mix(&state, sizeof state);
            mix(&hp, sizeof hp);
            mix(&gauge, sizeof gauge);
        }
        const auto live = static_cast<unsigned>(projectiles.live.size());
        mix(&live, sizeof live);
        const auto random = combat.simulation_random_state();
        mix(&random.index, sizeof random.index);
    }
};

Battle::Battle(const BattleConfig& config) : m_impl(std::make_unique<Impl>(config)) {}
Battle::~Battle() = default;

void Battle::step(const Inputs& inputs) {
    net::InputChannel::Frame frame{};
    for (unsigned i = 0; i < 4; ++i) {
        frame[i].x = static_cast<std::int16_t>(inputs[i].x);
        frame[i].z = static_cast<std::int16_t>(inputs[i].z);
        frame[i].buttons = battle_button_carrier(inputs[i].buttons);
    }
    m_impl->step(frame);
}

ActorState Battle::actor(unsigned slot) const {
    const auto& combat = m_impl->combat;
    const auto& a = m_impl->world.actors.at(slot);
    ActorState out;
    out.position = a.position;
    out.heading = a.heading;
    out.state = combat.current_action_state(slot);
    out.phase = combat.projectile_owner_phase(slot);
    out.frame = combat.projectile_owner_animation_frame(slot);
    out.hp = static_cast<int>(combat.health[slot]);
    out.gauge = combat.gauge[slot];
    out.grounded = a.grounded != 0;
    return out;
}

unsigned Battle::tick() const { return m_impl->ticks; }
unsigned Battle::scene_phase() const { return m_impl->combat.scene_phase(); }
unsigned Battle::live_projectiles() const { return static_cast<unsigned>(m_impl->projectiles.live.size()); }
bool Battle::match_finished() const { return m_impl->combat.match.ready; }
std::uint64_t Battle::hash() const { return m_impl->digest; }

}  // namespace sim
