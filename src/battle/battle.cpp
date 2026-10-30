#include "sim/battle.h"

#include "basic_battle_roster_assets.hpp"
#include "battle_animated_camera.hpp"
#include "battle_camera_viewports.hpp"
#include "battle_magazine_hud.hpp"
#include "battle_manual_aim_camera.hpp"
#include "battle_special_hud.hpp"
#include "battle_voice_route.hpp"
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
#include "projectile_render_pose.hpp"
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
        roster.option[i] = static_cast<unsigned char>(slot.costume);
        roster.costume[i] = static_cast<unsigned char>(slot.specialMode);
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
    roster.rule_values = config.rules;
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
    std::array<bool, 4> tacticsHeld{};
    std::uint64_t digest = 1469598103934665603ull;
    BattleEvents events;
    std::shared_ptr<BattleVoiceInventory> voices;
    BattleAnimatedCameraAsset cameraAsset;
    std::array<BattleCameraTracking, 4> cameras{};
    std::array<BattleAnimatedCameraState, 4> animatedCameras{};
    std::array<BattleCameraView, 4> manualCameras{};

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
        voices = std::make_shared<BattleVoiceInventory>(assets);
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
        cameraAsset = BattleAnimatedCameraAsset::load(assets);
        update_cameras(true);
    }

    // RuntimeBattle::update_cameras, FUN_006358c0's per-actor camera service.
    void update_cameras(bool immediate) {
        for (unsigned i = 0; i < 4; ++i) {
            const auto pair = combat.target_availability[i].paired_actor;
            const unsigned owner = world.actors[i].motion.blocked && pair < 4 ? pair : i;
            const auto& actor = world.actors[owner];
            auto& camera = cameras[i];
            auto& animation = animatedCameras[i];
            float offset;
            std::memcpy(&offset, &actor.relationships.heading_offset_bits, 4);
            if ((static_cast<unsigned>(combat.full_charge_manual_flag_[owner]) & 255u) != 0) {
                const auto socket = combat.selected_weapon_socket(world, owner);
                manualCameras[i] = manual_battle_camera_view({socket[0], socket[1], socket[2]}, actor.heading + offset,
                                                             combat.full_charge_manual_aim_[owner]);
                animation.special = true;
            } else {
                set_battle_camera_target(camera, world.actors.at(actor.relationships.target).position, immediate);
                set_battle_camera_anchor(camera, actor.position, immediate);
                const int requested = combat.native_contact_mode[owner];
                if (requested < 0) animation.clear();
                else animation.select(requested, actor.heading + offset, cameraAsset);
            }
            advance_battle_camera_tracking(camera);
            animation.advance();
            camera.animated = animation.active;
        }
    }

    void mix(const void* data, size_t size) {
        const auto* bytes = static_cast<const unsigned char*>(data);
        for (size_t i = 0; i < size; ++i) {
            digest ^= bytes[i];
            digest *= 1099511628211ull;
        }
    }

    // RuntimeBattle::update's delivery of the tick's requests, as data. The requests live until
    // the next tick's move_with_projectile_scripts clears them.
    void collect_events() {
        events.effects.clear();
        events.sounds.clear();
        events.voices.clear();
        for (const auto& request : combat.effect_requests) {
            std::array<float, 3> direction;
            if (request.direction) {
                direction = *request.direction;
            } else {
                const float cp = legacy_trig(request.pitch, false);
                direction = {legacy_trig(request.heading, false) * cp, legacy_trig(request.pitch, true),
                             legacy_trig(request.heading, true) * cp};
            }
            events.effects.push_back({static_cast<int>(request.actor), static_cast<int>(request.id), request.position, direction});
        }
        for (const auto& request : combat.sound_requests) {
            if (request.system && !battle_contact_sound_audible(request, roster.controlled_slots, roster.controlled_count)) continue;
            events.sounds.push_back({static_cast<int>(request.actor), static_cast<int>(request.id),
                                     !request.system && request.mode == BattleSoundMode::Spatial, request.position,
                                     request.system});
        }
        // RuntimeBattle::update: an activation notice is a nonpositional system SE for the
        // slots local controllers own (FUN_004220e0 -> FUN_0064af20).
        for (const auto& request : combat.special_activation_events) {
            for (unsigned n = 0; n < roster.controlled_count; ++n)
                if (roster.controlled_slots[n] == request.slot)
                    events.sounds.push_back({static_cast<int>(request.slot), static_cast<int>(request.notification), false, {}, true});
        }
        for (const auto& request : combat.voice_requests) {
            if (!battle_event_voice_audible(request, roster.controlled_slots, roster.controlled_count)) continue;
            if (!request.selection_resolved || request.actor >= 4 || request.bank < 0 || request.selected_choice < 0) continue;
            const unsigned which = voices->bank(request.actor, request.bank != 0);
            const auto& names = voices->names(request.actor, which, request.category);
            if (static_cast<size_t>(request.selected_choice) >= names.size()) continue;
            // FUN_0065b420: with one view (DAT_006cfd00, FUN_006396f0) these two callers use the
            // 3D buffer, which FUN_00420880 keeps at the actor's head. The other callers stay flat.
            const bool positional = battle_voice_alternate_route(request.source) && battle_voice_layout_byte(roster, combat.scene_phase()) != 0;
            const auto& actor = world.actors[request.actor];
            const std::array<float, 3> position{actor.position[0] + 5.f * legacy_trig(actor.heading, false), actor.position[1] + 145.f,
                                                actor.position[2] + 5.f * legacy_trig(actor.heading, true)};
            events.voices.push_back({static_cast<int>(request.actor), names[static_cast<size_t>(request.selected_choice)], positional, position});
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
            update_cameras(false);
            combat.update_with_projectile_contacts(
                world, inputs,
                [&](unsigned pool) { projectiles.resolve_pool_contacts(combat, world, pool, true); },
                &cpuFrame, &buttons);
            projectiles.advance_scripts(combat, world, collision.projectile, 15, true, true);
            effects.spawn_requests(combat);
            effects.advance(&world);
        }
        ++ticks;
        collect_events();
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
        // FUN_0041f580 acts on the tactics press's first tick only.
        const bool tactics = (inputs[i].buttons & Tactics) != 0;
        frame[i].buttons = battle_button_carrier(inputs[i].buttons, tactics && !m_impl->tacticsHeld[i]);
        m_impl->tacticsHeld[i] = tactics;
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
    out.delayedHp = static_cast<int>(combat.delayed_health[slot]);
    out.lockPulse = combat.targeting[slot].cooldown;
    out.gauge = combat.gauge[slot];
    out.grounded = a.grounded != 0;
    out.target = static_cast<int>(a.relationships.target);
    out.actionCamera = combat.native_contact_mode[slot];
    return out;
}

unsigned Battle::tick() const { return m_impl->ticks; }
unsigned Battle::scene_phase() const { return m_impl->combat.scene_phase(); }
unsigned Battle::live_projectiles() const { return static_cast<unsigned>(m_impl->projectiles.live.size()); }
bool Battle::match_finished() const { return m_impl->combat.match.ready; }
ActorAnimation Battle::animation(unsigned slot) const {
    const auto& service = m_impl->combat.animation_service(slot);
    ActorAnimation out;
    out.lowerSet = service.channels[0].selected;
    out.upperSet = service.channels[1].selected;
    out.lowerTime = service.channels[0].position[out.lowerSet];
    out.upperTime = service.channels[1].position[out.upperSet];
    return out;
}

NoticeState Battle::notice(unsigned slot) const {
    const auto& combat = m_impl->combat;
    NoticeState out;
    if (!combat.startup.enabled || combat.scene_phase() >= 4 || !combat.startup.notice_ticks.at(slot)) return out;
    out.type = combat.startup.notice_type[slot];
    out.scale = combat.startup.notice_scale[slot];
    return out;
}

LockRing Battle::lock_ring(unsigned slot) const {
    const auto& combat = m_impl->combat;
    const auto& relationships = m_impl->world.actors.at(slot).relationships;
    const auto& targeting = combat.targeting[slot];
    LockRing out;
    if (relationships.secondary_target < 4) out.target = static_cast<int>(relationships.secondary_target);
    if (out.target >= 0) out.invincible = damage_signed(combat.stagger[static_cast<size_t>(out.target)].invincible) > 0;
    out.onAlly = targeting.ally_index >= 0;
    const auto& gauge = combat.special_gauges[slot];
    out.friendship = (gauge.mode & 255u) == 1 && gauge.active1;
    out.joint = targeting.joint_ticks != 0;
    out.shared = !relationships.allies.empty() &&
                 relationships.target_index == m_impl->world.actors.at(relationships.allies.front()).relationships.target_index;
    out.manualAim = (static_cast<unsigned>(combat.full_charge_manual_flag_[slot]) & 255u) != 0;
    return out;
}

std::vector<DirectionWarning> Battle::direction_warnings(unsigned slot) const {
    std::vector<DirectionWarning> out;
    for (const auto& warning : m_impl->combat.direction_warnings[slot])
        out.push_back({warning.state, warning.direction, warning.ticks});
    return out;
}

int Battle::cpu_command(unsigned slot, float& pulse) const {
    pulse = 0.f;
    if (m_impl->roster.owner[slot] >= 4) return -1;  // FUN_00644150 hides it for a CPU seat
    pulse = m_impl->cpu.command_display_scale[slot];
    return m_impl->cpu.commands[slot];
}

ResultNotice Battle::result_notice() const {
    const auto& combat = m_impl->combat;
    ResultNotice out;
    if (combat.scene_phase() >= 4 && combat.match.presentation_phase == 0)
        out.barOffset = std::max(0, static_cast<int>(combat.match.presentation_offset));
    if (combat.scene_phase() != 3 || combat.match.winner < 0 || combat.match.ready) return out;
    out.winner = combat.match.winner;
    out.main = combat.match.countdown != 0;
    out.mainScale = combat.phase_notices.main_scale;
    out.secondary = combat.phase_notices.secondary_ticks != 0;
    out.secondaryScale = combat.phase_notices.secondary_scale;
    return out;
}

SpecialState Battle::special(unsigned slot) const {
    const auto& combat = m_impl->combat;
    const auto& gauge = combat.special_gauges[slot];
    const BattleSpecialHud hud = battle_special_hud(gauge);
    SpecialState out;
    out.mode = gauge.mode & 255u;
    out.active = hud.active;
    out.ready = hud.ready;
    out.fraction = hud.fraction;
    // While active the mode's charge counter is the clock the fan divides by its duration.
    if (hud.active) out.ticksLeft = static_cast<int>(out.mode == 0 ? gauge.charge0 : out.mode == 1 ? gauge.charge1 : gauge.charge2);
    out.flash = gauge.flash;
    out.entryRow = static_cast<int>(combat.special_entry[slot].state);
    out.entryFrame = static_cast<int>(combat.special_entry[slot].frame);
    return out;
}

HandTrail Battle::hand_trail(unsigned slot, unsigned hand) const {
    const auto& combat = m_impl->combat;
    HandTrail out;
    out.model = combat.selected_held_weapon_models(slot)[hand];
    if (out.model >= 0 && out.model < 12) out.active = combat.weapon_visual_controllers[slot].model_trail[static_cast<size_t>(out.model)];
    std::optional<ActorSkeleton> fallback;
    const unsigned bone = combat.render_pose_view(slot, fallback).find(hand ? "Bip01_Prop2" : "Bip01_Prop1");
    if (bone) {
        out.hasBone = true;
        out.boneWorld = combat.actor_bone_world(m_impl->world, slot, bone);
    }
    return out;
}

CameraPose Battle::camera(unsigned slot) const {
    const auto& impl = *m_impl;
    // FUN_006396f0's layout: result phases 3..5 show one fixed actor's camera to everyone.
    const unsigned phase = impl.combat.scene_phase();
    const auto layout = battle_camera_viewports(impl.roster, phase >= 3 ? phase : 0, static_cast<int>(impl.combat.match.focus),
                                                static_cast<int>(impl.combat.last_defeat_attacker));
    unsigned actor = slot;
    if (phase >= 3 && layout.slots[0].active && layout.slots[0].actor >= 0) actor = static_cast<unsigned>(layout.slots[0].actor);
    const auto& animation = impl.animatedCameras.at(actor);
    const BattleCameraView view =
        animation.special ? impl.manualCameras[actor]
        : animation.active ? animated_battle_camera_view(impl.cameraAsset, animation, impl.cameras[actor].smoothed_anchor)
                           : ordinary_battle_camera_view(impl.cameras[actor]);
    const BattleCameraProjection projection = battle_camera_projection(animation.special);
    CameraPose out;
    out.eye = view.eye;
    out.lookAt = view.look_at;
    out.fovY = projection.fov_y;
    out.nearPlane = projection.near_plane;
    out.animated = animation.active;
    out.actor = static_cast<int>(actor);
    return out;
}

ActorTotals Battle::totals(unsigned slot) const {
    const auto& s = m_impl->combat.statistics[slot];
    ActorTotals out;
    out.kills = static_cast<int>(s.kills);
    out.deaths = static_cast<int>(s.deaths);
    out.damageDealt = static_cast<int>(s.dealt[0] + s.dealt[1]);
    out.damageTaken = static_cast<int>(s.received[0] + s.received[1]);
    return out;
}

MatchState Battle::match_state() const {
    const auto& combat = m_impl->combat;
    MatchState out;
    out.winner = combat.match.winner;
    out.finished = combat.match.ready;
    out.awardsReady = combat.awards.ready;
    if (out.awardsReady)
        for (unsigned i = 0; i < 4; ++i) out.awards[i] = static_cast<int>(combat.awards.ids[i]);
    out.timed = combat.match.timed;
    out.remainingTicks = static_cast<int>(combat.match.remaining_ticks);
    const auto scores = combat.displayed_team_scores();
    const auto& feedback = combat.score_feedback();
    for (unsigned team = 0; team < 2; ++team) {
        out.score[team] = scores[team];
        out.scoreDelta[team] = static_cast<int>(feedback.value[team]);
        out.scoreDeltaTicks[team] = static_cast<int>(feedback.timer[team]);
        out.limit[team] = static_cast<float>(m_impl->roster.rule_values[2 + team]);
    }
    return out;
}

const BattleEvents& Battle::events() const { return m_impl->events; }

void Battle::for_each_projectile(const std::function<void(const ProjectileState&)>& visit) const {
    static const LegacyMatrix kIdentity{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    for (const auto& p : m_impl->projectiles.live) {
        const auto& frame = p.cursor.current(p.assets->selected());
        LegacyMatrix external;
        const bool bound = LocalNormalProjectiles::bound_render_pose(p, m_impl->combat, m_impl->world, external);
        ProjectileState out;
        out.owner = static_cast<int>(p.pool_owner);
        out.item = static_cast<int>(p.state.item);
        // The core keeps the bullet's registration number; the product indexes the weapon's rows.
        const auto& weapon = *m_impl->combat.actor_assets(p.pool_owner).weapon_item;
        out.row = -1;
        for (unsigned row = 0; row < weapon.bullets.size() && out.row < 0; ++row)
            if (weapon.bullets[row].registration_id() == static_cast<int>(p.registration)) out.row = static_cast<int>(row);
        out.position = p.state.position;
        out.modelMatrix = projectile_render_pose(p.state, frame.flags28, kIdentity, bound ? &external : nullptr);
        out.billboard = (frame.flags28 & 0x1000u) != 0;
        out.tint = frame.fields[19];
        out.frame = static_cast<int>(p.state.frame);
        visit(out);
    }
}

std::array<int, 2> Battle::held_models(unsigned slot) const {
    return m_impl->combat.selected_held_weapon_models(slot);
}

std::array<MagazineState, 2> Battle::magazines(unsigned slot) const {
    std::array<MagazineState, 2> out;
    const auto& source = m_impl->combat.magazines[slot];
    for (size_t i = 0; i < out.size() && i < source.size(); ++i) {
        const BattleMagazineHud hud = battle_magazine_hud(source[i]);
        out[i].rounds = static_cast<int>(hud.rounds);
        out[i].fill = hud.fill_fraction;
        out[i].charge = hud.initial_charge_fraction;
        out[i].followup = hud.followup_charge_fraction;
    }
    return out;
}

Matrix Battle::actor_world(unsigned slot) const {
    return m_impl->combat.world_pose(m_impl->world, slot);
}

void Battle::bone_poses(unsigned slot, std::vector<std::string>& names, std::vector<Matrix>& model) const {
    std::optional<ActorSkeleton> fallback;
    const ActorSkeleton& pose = m_impl->combat.render_pose_view(slot, fallback);
    static const LegacyMatrix kIdentity{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    std::vector<LegacyMatrix> combined;
    combine_actor_world_hierarchy(pose, kIdentity, combined);
    names.resize(pose.bones.size());
    model.resize(pose.bones.size());
    for (size_t i = 0; i < pose.bones.size(); ++i) {
        names[i] = pose.bones[i].name;
        model[i] = combined[i];
    }
}

void Battle::fill_special_for_test() { m_impl->combat.fill_keyboard_special(); }

std::vector<unsigned> Battle::declared_rows(unsigned slot) const {
    std::vector<unsigned> rows;
    for (const auto& entry : m_impl->combat.actor_assets(slot).state_frames_) rows.push_back(entry.first);
    return rows;
}
std::uint64_t Battle::hash() const { return m_impl->digest; }

}  // namespace sim
