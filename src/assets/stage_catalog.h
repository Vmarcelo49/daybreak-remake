#pragma once
// What a stage or character directory actually *is*, in words.
//
// Why this exists: the shipped names mislead, and the project has already paid for it
// twice. `data/stage21` is not "stage 21" — it is the schoolyard at *night*, and the DX9
// remake hardcodes it, so days of frame comparison were measured on the night variant
// while the reference prints show the day one. `data/title` is not the title screen. The
// identification and its evidence live in `docs/ASSET-CATALOG.md`; this header is
// the one place code should ask instead of parsing a path.
//
// The stage scheme is a two-digit code, not a number (catalog §1.1):
//   stageNN   first digit = time of day (0 day, 1 sunset, 2 night)
//             second digit = scene (1..6)
// and the pairs share their texture vocabulary, which is how the axis was proven:
// 01/11/21 are one scene, 02/12 another, and so on.
//
// Evidence tiers, because they are not equal:
//   * scene 1's name is the game's own (雛見沢分校 校庭, from stage-select-school.webp);
//   * scenes 2..6 are *our* descriptive names, taken from each scene's own texture
//     vocabulary — the executable contains no stage-name strings at all (catalog §1.3);
//   * the character index table is the game's, pinned by the characters' own dialogue in
//     data/scenario/D*.txt (catalog §2).
// Code and logs should carry both halves: the stable name and the raw directory, so a
// reader can always check the claim against the asset.

#include <cstddef>
#include <string>

namespace assets {

struct StageId {
    const char* dir;      // "stage01"
    const char* name;     // "schoolyard_day" — stable, used by code and logs
    const char* gameName; // the *game's* own Japanese name, or "" when it is not known
    int         scene;    // second digit: 1..6
    int         timeOfDay;   // first digit: 0 day, 1 sunset, 2 night
};

// 13 shipped stages. A directory that is not listed (a test fixture, a mod) resolves to
// nullptr and callers fall back to printing the path alone.
// `name` is the stable identifier; `gameName` is filled in ONLY where the game itself
// supplies the string. Scenes 2..6 have no game-side name anywhere (the executable holds
// no stage strings and the select screen was captured for scene 1 only), so translating
// their descriptive names into Japanese here would be inventing evidence — the one thing
// the catalog exists to prevent. Leave them empty until a print or an RE address names
// them.
inline constexpr StageId kStages[] = {
    {"stage01", "schoolyard_day",        "雛見沢分校 校庭", 1, 0},
    {"stage11", "schoolyard_sunset",     "雛見沢分校 校庭", 1, 1},
    {"stage21", "schoolyard_night",      "雛見沢分校 校庭", 1, 2},
    {"stage02", "village_paddies_day",   "", 2, 0},
    {"stage12", "village_paddies_sunset","", 2, 1},
    {"stage03", "shrine_grounds_day",    "", 3, 0},
    {"stage13", "shrine_grounds_sunset", "", 3, 1},
    {"stage04", "mountain_stream_day",   "", 4, 0},
    {"stage14", "mountain_stream_sunset","", 4, 1},
    {"stage05", "riverbed_dump_day",     "", 5, 0},
    {"stage15", "riverbed_dump_sunset",  "", 5, 1},
    {"stage06", "shrine_upper_day",      "", 6, 0},
    {"stage16", "shrine_upper_sunset",   "", 6, 1},
};

// Looks up the last path component of `stageDir` (".../data/stage21" -> stage21). Returns
// nullptr when the directory is not one of the shipped stages.
inline const StageId* lookupStage(const std::string& stageDir) {
    const size_t slash = stageDir.find_last_of("/\\");
    const std::string leaf = slash == std::string::npos ? stageDir : stageDir.substr(slash + 1);
    for (const StageId& s : kStages)
        if (leaf == s.dir) return &s;
    return nullptr;
}

inline const char* timeOfDayName(int t) {
    switch (t) {
        case 0: return "day";
        case 1: return "sunset";
        case 2: return "night";
        default: return "unknown";
    }
}

// One log line that cannot be misread: the stable name, the game's name where known, the
// decoded axes, and the raw directory so the claim stays checkable. Callers print this at
// load time; a capture log that says "schoolyard_night (data/stage21)" cannot be mistaken
// for a daytime scene the way "stage21" was.
inline std::string describeStage(const std::string& stageDir) {
    const StageId* s = lookupStage(stageDir);
    if (!s) return stageDir;   // an unlisted directory: print it rather than guess
    std::string out = s->name;
    out += " (scene ";
    out += std::to_string(s->scene);
    out += ", ";
    out += timeOfDayName(s->timeOfDay);
    if (s->gameName[0]) {
        out += ", ";
        out += s->gameName;
    }
    out += ") [";
    out += stageDir;
    out += "]";
    return out;
}

}  // namespace assets
