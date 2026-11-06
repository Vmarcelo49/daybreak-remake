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

struct ConvertRequest {
    RawMoveset moveset;
    DispatchCombo dispatch;
    std::string character;       // data/ directory name: "satoshi", "miyoko", "okonogi"
    unsigned weapon = 0;         // PSP weapon slot, 0..3 = a..d
    unsigned item_id = 101;      // written into the frame table's parameters[3]
    // Registration index space of the 00.X this table will pair with: the count of AnimationSet
    // children with tracks, in the order battle_actor_assets registers them (reverse document
    // order, empty sets skipped). A phase value the model does not have is remapped inside it.
    // 0 leaves every phase value untouched.
    unsigned take_count = 0;
    // Length of each registered animation set, in PC frames, in the same index space as
    // take_count (registered_animation_frame_counts). The row timer advances a phase once the tick
    // counter passes this length, so a hit window timed beyond it never fires; the converted times
    // are scaled inside it. Empty leaves the dispatch combo's own timing untouched.
    std::vector<unsigned> take_frames;
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

// Number of AnimationSets battle_actor_assets would register from a model's token stream, i.e. the
// exclusive upper bound of a valid phase value. Exposed because the extractor and the tests need
// the same number the load path will use.
unsigned registered_animation_set_count(const std::vector<std::uint8_t>& model);

// The same registration order, as each set's length in PC frames — the number the row timer
// compares a phase's tick counter against (battle_actor_assets' animation_durations_).
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
    // Until Track A's converted 00.X exists, a fighter's own model is not available, so the
    // dispatch combo's PC model is copied under its name. The simulation needs only a skeleton
    // and animation sets; the renderer needs the real one.
    bool copy_dispatch_model = true;
};
struct TreeResult {
    std::vector<std::string> written;
    std::string report;
};
TreeResult prepare_psp_data_tree(const TreeRequest& request);

}
