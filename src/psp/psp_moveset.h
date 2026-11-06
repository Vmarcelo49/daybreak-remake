#pragma once
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace daybreak::psp {

// PSP moveset conversion (plan D-3a). Reads a PSP fighter's own attack data and writes the PC
// game's own data layout, so every reader on the PC side stays as it is:
//
//   in   activity/chrNNx.acs, activity/chrNNx.acv, assault/chrNNx.atp   (raw PSP files)
//   in   the dispatch combo's data/<dir>/0W.dat and data/item/NNN.dat    (the PC combo whose
//                                                                        recovered row code runs)
//   out  data/<character>/0W.dat     frame table: rows, phases, hit records, timings
//        data/item/NNN.dat           weapon item: the dispatch combo's, under the PSP item id
//
// Why starting from the dispatch combo's table: the borrowed code addresses PC state ids and
// expects every one of them to exist, with a non-empty state 300 and hit records on bones. The
// PSP only defines a fraction of those rows, so the converter overrides the eleven moves whose
// PC state <-> PSP row pairing the moveset study measured (docs/psp/COMBAT.md §2) and leaves the
// rest of the dispatch combo's table untouched.
//
// Every rule is a port rule (evidence tier 6) unless the header comment names an address or a
// measurement. docs/psp/COMBAT.md lists each one with its tier.
struct RawMoveset {
    std::vector<std::uint8_t> acs, acv, atp;
};

struct DispatchCombo {
    std::vector<std::uint8_t> frame_table;  // data/<dir>/0W.dat, as read from the install
    std::vector<std::uint8_t> weapon_item;  // data/item/NNN.dat, as read from the install
};

// ---------------------------------------------------------------- animation plan
// A PC phase names one animation set; a PSP take is a whole move (docs/psp/COMBAT.md §3.1). So
// every phase of a PC state is pointed at a slice of the one take that state plays
// (psp_take_table.h), and the slices become extra animation sets the model converter appends
// after the 76 takes. Sets 0..75 stay exactly PSP take 0..75.
//
// A derived set is a span of one take's key frames, and it carries the animation settings (blend,
// hold, texture events) of the PC set it replaces, so the borrowed row code keeps its timing
// behaviour: the row timer advances a phase when the phase's tick counter passes its set's length.
struct DerivedSet {
    unsigned take = 0;           // PSP take index the keys are taken from
    unsigned from = 0, to = 0;   // key frames, inclusive, 30 Hz PSP frames
    unsigned pc_set = 0;         // the dispatch combo's set whose settings this one copies
};
struct AnimationPlan {
    unsigned take_count = 0;              // the model's own takes, 0..take_count-1
    std::vector<DerivedSet> derived;      // set take_count + i is derived[i]
    // Per state record of the dispatch table, in file order, per phase: the set index the phase
    // plays. By record, not by id: a table may repeat an id (Satoko 0 has two 311 and two 331
    // records; the core keeps the last, battle_actor_assets.hpp), and each record is rewritten.
    std::vector<std::vector<unsigned>> phases;
    std::string report;
};

// The facts about the fighter's own model the plan needs: each take's key-frame count (30 Hz PSP
// frames + 1; 1 or 2 for a take with no curves) and whether it moves at all.
struct TakeInfo {
    unsigned frames = 0;   // last key frame, 30 Hz; 0 for a take with no motion
    bool usable = false;   // animated, and not one of the table's unusable placeholders
};

// Plans one fighter's animation (roster character 16..18) over the dispatch frame table. The
// table's own phases, settings and state ids are read, and `dispatch_set_frames` (the dispatch PC
// model's registered_animation_frame_counts) gives each phase its share of the take; nothing is
// written. Throws when a phase cannot be given a valid set, which a match would otherwise find at
// runtime.
AnimationPlan plan_psp_animation(unsigned character, const std::vector<std::uint8_t>& dispatch_frame_table,
                                 const std::vector<unsigned>& dispatch_set_frames,
                                 const std::vector<TakeInfo>& takes);

// The settings section a fighter's frame table carries: one record per set, takes first (default
// blend, no hold, no events) and then each derived set's copy of its PC set's record.
std::vector<std::uint8_t> plan_animation_settings(const AnimationPlan& plan,
                                                  const std::vector<std::uint8_t>& dispatch_frame_table);

struct ConvertRequest {
    RawMoveset moveset;
    DispatchCombo dispatch;
    std::string character;       // data/ directory name: "satoshi", "miyoko", "okonogi"
    unsigned weapon = 0;         // PSP weapon slot, 0..3 = a..d
    unsigned item_id = 101;      // written into the frame table's parameters[3]
    // The fighter's animation plan, from the same model the table will be paired with. Without
    // one (a dispatch PC model stands in for the fighter's own), every phase keeps the dispatch
    // combo's set index and its settings section, which is valid for that model.
    const AnimationPlan* plan = nullptr;
    // Length of each set the plan names, in PC frames (registered_animation_frame_counts of the
    // final model). The row timer advances a phase once the tick counter passes this length, so a
    // hit window timed beyond it never fires; the converted times are scaled inside it.
    std::vector<unsigned> set_frames;
    std::string model = "00.X";  // the model file name the frame table names
};

struct OutputFile {
    std::string path;  // relative to psp-data/, e.g. "data/satoshi/00.dat"
    std::vector<std::uint8_t> bytes;
};

struct ConvertResult {
    std::vector<OutputFile> files;
    std::string report;  // one line per rule applied, for the extractor's log
};

// The eleven moves the study measured, as {PC state, PSP row} (docs/PSP-CHARACTERS-PLAN.md,
// "The PC and the PSP share numbers"; re-checked against .atp record 0 for 01a row 107 in
// docs/psp/COMBAT.md §2). Rows outside this table keep the dispatch combo's own data.
inline constexpr std::pair<unsigned, unsigned> kMoveRows[] = {
    {300, 107}, {301, 109}, {302, 110}, {310, 112}, {311, 114}, {320, 163},
    {330, 124}, {331, 126}, {332, 167}, {340, 172}, {341, 174},
};
// def[+0x3c] = 60 and def[+0x40] = 50 for every one of the 19x4 combinations in bin/chr.fpd, so
// the PSP's first attack slot is a sphere of radius 110 around the weapon bone. The PC core's
// shape-0 record is a sphere at the bone too (battle_hit_query.hpp), so the radius transfers with
// no unit change: both casts are authored at 1 unit = 1 cm (PC character top 177-182).
inline constexpr unsigned kAttackSphereRadius = 110;

// Each AnimationSet battle_actor_assets would register from a model's token stream, in its order
// (reverse document order, empty sets skipped), as the set's length in PC frames — the number the
// row timer compares a phase's tick counter against (battle_actor_assets' animation_durations_).
// Its size is the exclusive upper bound of a valid phase value.
std::vector<unsigned> registered_animation_frame_counts(const std::vector<std::uint8_t>& model);

ConvertResult convert_psp_moveset(const ConvertRequest& request);

// The whole prepared tree, for the extractor and for the tests: the twelve combos of the three
// PSP fighters, from a raw directory of PSP files into a psp-data directory the core mounts.
// `raw_dir` may hold the pack paths inside it (activity/chr17a.acs) or their underscored form
// (activity_chr17a.acs, assault_chr17a.atp), which is how the study dumped them.
struct TreeRequest {
    std::string install_dir;  // holds daybreak00.dat; supplies the dispatch combos' own files
    std::string raw_dir;      // the PSP .acs/.acv/.atp files
    std::string output_dir;   // psp-data to write
    // Without a converted 00.X (the model converter has not run), the dispatch combo's PC model is
    // copied under the fighter's name and the tables keep its set indices: a simulation-only
    // stand-in. With one, `plan_for` must supply each fighter's plan, which the model converter
    // also used to append the derived sets; the extractor passes the plans it built.
    bool copy_dispatch_model = true;
    // The plans the model converter appended derived sets for, one per fighter (16, 17, 18 in
    // order). Required when a converted 00.X is present: a plan is a contract between the model's
    // set list and the tables' phase values, so both sides must use the same one.
    const std::vector<AnimationPlan>* plans = nullptr;
};

// Plans all three fighters from the install and each fighter's raw motion facts (in roster
// order). The model converter appends each plan's derived sets; the tree uses the same plans.
std::vector<AnimationPlan> plan_psp_animations(const std::string& install_dir,
                                               const std::vector<std::vector<TakeInfo>>& takes);
struct TreeResult {
    std::vector<std::string> written;
    std::string report;
};
TreeResult prepare_psp_data_tree(const TreeRequest& request);

}
