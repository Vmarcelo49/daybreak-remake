#pragma once
// The one door to the vendored simulation (src/battle/core). Nothing else includes the core, so
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
    bool storyMode = false;  // DAT_006cfce9
    int storyMusic = 0;      // the fight's data/bgm/%02d.ogg
};

// Buttons as the original's physical bits, before battle_button_carrier.
enum Button : unsigned { Jump = 1, Melee = 2, Shoot = 4, Target = 8, Guard = 32, Tactics = 64 };

struct SlotInput {
    int x = 0;  // -1 left, +1 right
    int z = 0;  // -1 forward, +1 back
    unsigned buttons = 0;
};
using Inputs = std::array<SlotInput, 4>;

// One magazine as FUN_00642060 snapshots it for the HUD (battle_magazine_hud).
struct MagazineState {
    int rounds = 0;
    float fill = 0.f;        // the bar: its display counter, or reload progress when empty
    float charge = 0.f;      // the first charge strip
    float followup = 0.f;    // the second charge strip
};

// A row-major D3D matrix: the same 16 floats in memory as a glm::mat4 of the same transform.
using Matrix = std::array<float, 16>;

// The slot's hypermode meter (BattleSpecialGauges). `mode` is the original's +0x318 value.
struct SpecialState {
    unsigned mode = 0;
    bool active = false;
    bool ready = false;      // the meter is full and the mode can start
    float fraction = 0.f;    // the fan: toward the threshold, or the time left while active
    int ticksLeft = 0;       // the running mode's own clock, 0 when not active
    int flash = 0;           // the presentation's red flash, 0..255
    int entryRow = 0;        // 500..503 while the activation plays, else 0
    int entryFrame = 0;
};

// The slot's running totals (ActorStatistics), on the core's 10000-per-fighter HP scale.
struct ActorTotals {
    int kills = 0, deaths = 0, damageDealt = 0, damageTaken = 0;
};

// One actor's centre-screen notice (FUN_0063a130): 0 KO, 1 and 2 respawn, 3..5 the digits, 6 start.
struct NoticeState {
    int type = -1;  // -1 when nothing shows
    float scale = 1.f;
};

// The win or lose glyphs of scene phase 3 (battle_phase_hud).
struct ResultNotice {
    int winner = -1;
    bool main = false, secondary = false;
    float mainScale = 1.f, secondaryScale = 1.f;
    int barOffset = -1;  // scene phases 4 and 5: the bars closing in, 1056 down to 0
};

// What one view's target reticle shows (draw_battle_lock_hud).
struct LockRing {
    int target = -1;
    bool invincible = false, onAlly = false, friendship = false, joint = false, shared = false;
    bool manualAim = false;  // the scope replaces the reticle
};

// One actor+850 record: 0 clear, 1 locked on, 2 attacking; 0 top, 1 bottom, 2 left, 3 right.
struct DirectionWarning {
    int state = 0, direction = 0, ticks = 0;
};

struct MatchState {
    int winner = -1;                       // the winning team once the round is decided
    bool finished = false;                 // the result screens are ready
    bool awardsReady = false;              // the titles below are chosen
    bool story = false;                    // a story fight: no titles, no statistics
    bool exitRequested = false;            // a story win is over (FUN_00635d40:206-211)
    std::array<int, 4> awards{{-1, -1, -1, -1}};  // FUN_00430880's title per slot
    bool timed = false;
    int remainingTicks = 0;
    std::array<float, 2> score{}, limit{};  // the balloon percentages the HUD shows
    std::array<int, 2> scoreDelta{}, scoreDeltaTicks{};  // the "+N%" popup (FUN_006431d0)
};

// What one player's view shows this tick (RuntimeBattle::camera_view, battle_camera_projection).
struct CameraPose {
    std::array<float, 3> eye{}, lookAt{};
    float fovY = 0.f, nearPlane = 0.f;
    bool animated = false;  // a data/camera/01.x clip is driving it
    int actor = 0;          // whose camera it is: the result screens focus another actor
};

// One hand's weapon trail source (WeaponVisualController, RuntimeBattle::advance_weapon_trails).
struct HandTrail {
    int model = -1;       // the held item model, -1 for an empty hand
    bool active = false;  // the current move asks this model for a trail
    Matrix boneWorld{};   // Bip01_Prop1/2 in the world, valid when the rig has the bone
    bool hasBone = false;
};

// One live projectile, in the render pass's terms (projectile_render_pose).
struct ProjectileState {
    int owner = 0, item = 0, row = 0;
    std::array<float, 3> position{};
    Matrix modelMatrix{};
    bool billboard = false;
    int tint = 0;
    int frame = 0;  // the model's animation clock, in original updates
};

// What the last tick asked the presentation to do, after the core's audibility rules.
struct BattleEvents {
    struct Effect { int actor, id; std::array<float, 3> position, direction; };
    struct Sound { int actor, id; bool positional; std::array<float, 3> position; bool system; };
    struct Voice { int actor; std::string path; bool positional; std::array<float, 3> position; };
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
    int delayedHp = 0;     // the ghost behind the HP bar
    int lockPulse = 0;     // the target ring's retarget pulse
    int gauge = 0;         // +0x834, 0..1000
    bool grounded = false;
    int target = 0;        // the slot this actor is locked on to
    int actionCamera = -1; // +0x684: the data/camera/01.x clip the actor asks for, -1 for none
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

// A copy of a battle's simulation, for rollback. A slot keeps its allocation, so reusing one is
// cheap. It may only go back into the Battle that saved it.
class BattleSnapshot {
public:
    BattleSnapshot();
    ~BattleSnapshot();
    BattleSnapshot(const BattleSnapshot&) = delete;
    BattleSnapshot& operator=(const BattleSnapshot&) = delete;

private:
    friend class Battle;
    struct State;
    std::unique_ptr<State> m_state;
};

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
    // The result phases (3 and up) draw no battle HUD (RuntimeBattle's draw, phase < 3).
    bool hud_hidden() const { return scene_phase() >= 3; }
    ActorAnimation animation(unsigned slot) const;
    SpecialState special(unsigned slot) const;
    NoticeState notice(unsigned slot) const;
    LockRing lock_ring(unsigned slot) const;
    std::vector<DirectionWarning> direction_warnings(unsigned slot) const;
    // The tactic this seat can give its CPU ally, or -1; `pulse` is the press's extra scale.
    int cpu_command(unsigned slot, float& pulse) const;
    ResultNotice result_notice() const;
    ActorTotals totals(unsigned slot) const;
    HandTrail hand_trail(unsigned slot, unsigned hand) const;
    CameraPose camera(unsigned slot) const;
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
    // Test seam for the original's keyboard shortcut (fill_keyboard_special): a full hypermode meter.
    void fill_special_for_test();
    // FNV-1a over every completed tick's actor states, projectile count and RNG cursor.
    std::uint64_t hash() const;
    // Hands a human's slot to the CPU from this tick on. Repeating it changes nothing.
    void handSlotToCpu(unsigned slot);
    bool slotIsCpu(unsigned slot) const;
    // Online, every human is in the roster, and this machine hears only its own player's notices.
    void setHearingSlot(unsigned slot);
    void saveState(BattleSnapshot& snapshot) const;
    // events() is empty until the next step.
    void loadState(const BattleSnapshot& snapshot);
    // The current state, not its history, so peers can compare it for desyncs. Covers named
    // scalars and never whole structs, whose padding differs between machines. Leaves out the
    // process-wide projectile serial, which nothing reads without host events.
    std::uint64_t stateHash() const;
    // Test seam: stateHash's writable fields, and flipping a bit in one. Flipping again restores it.
    unsigned stateFieldCount();
    void flipStateFieldForTest(unsigned field);

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};

}  // namespace sim
