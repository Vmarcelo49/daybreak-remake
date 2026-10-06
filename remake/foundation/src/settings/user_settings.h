#pragma once
// settings/user_settings.h — the port's persisted user configuration (issue #19).
//
// WHY this exists and why it is not the original's format: the original keeps its
// settings in a flat binary `config.dat` beside the executable, read by FUN_006486c0
// (0x6486c0) and written by FUN_006488d0 (0x6488d0) — 253 bytes: a 4-byte leading
// field, a 0xd0-byte block that is exactly four players x thirteen actions x int32
// DirectInput scancodes, then the option bytes/ints (the read order in FUN_006486c0 is
// the layout). Two of its properties are deliberately NOT copied:
//   * it writes next to the executable (CreateFileA("config.dat") with a relative path)
//     and truncates in place (dwCreationDisposition 4 = CREATE_ALWAYS), so a crash
//     mid-write loses the settings. The port writes into the XDG user config directory
//     and swaps the file in atomically;
//   * it is unversioned and unvalidated. The port's document carries a schema version
//     and every field is range-checked before it is applied.
// PORT DECISION: the text format below is the port's own (a versioned INI-style
// document), not a recovery of the original's binary layout; what IS recovered from the
// original is WHICH settings exist (per-player bindings, volumes, display toggles) and
// that bindings are per PLAYER, not per physical device.
//
// Session state stays out on purpose: earned titles, result stats, match outcomes and
// punishment-costume flags are session-scoped in the original too, and the issue keeps
// them out of permanent saves. There is no field for them here, and adding one needs a
// scope decision, not a schema bump.
//
// std only: no SDL, no WebGPU, no glm — the host test drives the parser, the validator
// and the atomic write with no device.
#include <array>
#include <string>
#include <vector>

#include "audio/audio.h"
#include "input/input.h"

namespace settings {

// Bumped whenever the key set or a key's meaning changes. A file whose version is not
// this one (or a version this build can migrate) is ignored WHOLE (never partially
// applied); the next save rewrites it in the current version.
//
// v2 (issue #10) removed the port-invented heavy melee action: the binding rows lost their
// sixth entry. A v1 file is MIGRATED, not rejected — its rows are read with the v1 layout
// and the removed entry is dropped, so an existing config keeps every other binding.
//
// v3 (issue #21) added the toon-rendering toggle ([render] toon). A v2 file is MIGRATED:
// every value it carries is read as v2 wrote it, the new toggle takes its default (off,
// which is what a v2 file meant — the option did not exist), and nothing is dropped, so
// that migration reports context without a warning. The [render] section itself is read
// whatever the version line says, so a hand-edited file is not rejected for naming a key
// this build knows.
//
// v4 (issue #36) added [game] install_dir: the game folder a run opened, so one config
// file owns it (the packaged launcher's own install.conf is gone) and a DIRECT binary run
// honours a remembered folder. A v3 file is MIGRATED additively — every value it carries
// is read as v3 wrote it, and the new key takes its default (empty = no folder
// remembered), which the migration line reports — and #21's v2→v3 migration stays in the
// chain, so the oldest files keep loading too. The key itself is special in one way: the
// document always carries it (serialize writes it empty when nothing is remembered), so a
// MISSING key in a current document is a hand-edit and warns, while a value that is not a
// usable folder warns and defaults that one key.
//
// v5 (issue #21 row 1) added the character-shadow toggle ([render] shadows) the same way.
// #36 and #21 both branched from v3 and both first called themselves v4; the merge gives
// #36 the v4 slot it shipped in and puts the shadow toggle at v5, so a v4 document written
// by a #36 build loads with its install_dir intact and the toggle defaulted off (what v4
// meant, since the option did not exist there). Both migrations are additive and both are
// reported.inline constexpr int kSchemaVersion = 5;
inline constexpr int kSchemaVersionLegacy = 1;
inline constexpr int kSchemaVersionV2 = 2;
inline constexpr int kSchemaVersionV3 = 3;
inline constexpr int kSchemaVersionV4 = 4;
// The v1 action count and the index the removed heavy action occupied in it.
inline constexpr int kLegacyActionCount = 13;
inline constexpr int kLegacyHeavyIndex = 5;

// The user config directory name under $XDG_CONFIG_HOME and the file inside it.
inline constexpr const char* kAppDirectory = "daybreak-decomp";
inline constexpr const char* kFileName = "settings.conf";

// A pixel size; {0,0} is "desktop", the display's own mode (D8's index 0).
struct DisplaySize {
    int width = 0, height = 0;
    bool operator==(const DisplaySize& other) const {
        return width == other.width && height == other.height;
    }
    bool operator!=(const DisplaySize& other) const { return !(*this == other); }
};

// Everything the port persists. Defaults are the shipped bindings and full volume, so a
// missing or rejected file yields exactly the behaviour of a first launch.
struct UserSettings {
    // The game folder a run last opened (issue #36), absolute; empty = never chosen.
    // PORT DECISION, labelled as such: the original has no such setting (it reads assets
    // relative to its own folder), and how a folder is DISCOVERED stays the launcher's
    // search (#22). This field only remembers which folder was opened, so the launcher and
    // a direct run agree on it. A relative value is refused by the parser (see
    // storableInstallDir) because it would name a different folder per working directory.
    std::string installDir;
    bool        fullscreen = false;
    DisplaySize resolution{0, 0};
    // Toon rendering (issue #21), the Options screen's first row. Off is the shipped
    // default (DAT_006cfcec is zero-initialised) and the state every banked capture was
    // made in.
    bool        toonRendering = false;
    // Character shadows (issue #21 row 1), the Options screen's second row (影の表示).
    // Off is the shipped default (DAT_006cfcea is zero-initialised) and the state every
    // banked capture was made in.
    bool        shadowRendering = false;
    fnd::audio::Volumes volumes;
    std::array<int, fnd::input::ActionCount> keyboard{};
    std::array<std::array<int, fnd::input::ActionCount>, fnd::input::kMaxPlayers> gamepad{};
    // Stable-controller identity: the SDL GUID (and name, for diagnostics) of the pad
    // that last occupied each player slot. See input/gamepad_identity.h for the policy.
    std::array<std::string, fnd::input::kMaxPlayers> padGuid{};
    std::array<std::string, fnd::input::kMaxPlayers> padName{};

    UserSettings();  // shipped defaults (same tables the input backend starts from)

    bool operator==(const UserSettings& other) const;
    bool operator!=(const UserSettings& other) const { return !(*this == other); }
};

// --- where the file lives ---------------------------------------------------------
// XDG base-directory rule (spec: only an ABSOLUTE $XDG_CONFIG_HOME counts; an empty or
// relative one falls back to $HOME/.config). Both inputs are the raw environment values
// so the rule is testable without touching the process environment.
std::string configDirectory(const char* xdgConfigHome, const char* home);
std::string configFilePath(const char* xdgConfigHome, const char* home);
// The same for the running process ($XDG_CONFIG_HOME then $HOME), or "" when neither is
// usable — in which case the host runs with defaults and never writes.
std::string defaultConfigPath();
// False on the web, where there is no durable filesystem: load() then reports the file
// absent and save() refuses, so the browser build keeps its process-local settings.
bool persistenceSupported();

// --- the remembered game folder (issue #36) ----------------------------------------
// True when `value` may be a remembered folder at all: non-empty, ABSOLUTE, and short
// enough to fit one line of the document. main.cpp applies it before writing a folder a
// run opened, and serialize() writes an unstorable value as empty, so the file can never
// carry the one thing the parser would refuse to read back.
bool storableInstallDir(const std::string& value);

// --- parse / serialize ------------------------------------------------------------
// One line of human-readable context per accepted warning and one message per rejection.
struct LoadReport {
    bool existed = false;   // the file was present on disk
    bool loaded = false;    // it parsed, validated and was applied
    int  warnings = 0;      // entries defaulted or ignored; the rest still applied
    std::vector<std::string> messages;
};

// Parses `text`. Structure errors (bad line, unknown section, missing/unsupported
// version, NUL byte, oversize) reject the whole document — `out` is untouched and the
// caller keeps its defaults. Value errors (out of range, unparseable) default that one
// key, keep the rest and add a warning. Unknown keys inside a known section are ignored
// with a warning, so a newer version's extra keys never destroy older settings.
bool parse(const std::string& text, UserSettings& out, std::string& error, LoadReport& report);

// Stable key order, one comment header, trailing newline. Round-trips through parse().
std::string serialize(const UserSettings& settings);

// --- load / save ------------------------------------------------------------------
// load() never throws and never fails the caller: a missing file is a first launch, a
// malformed file is a defaulted launch with the reason in the report.
bool load(const std::string& path, UserSettings& out, LoadReport& report);
// Atomic: a temp file in the SAME directory, fsync, rename over the target, then fsync
// the directory. A failure leaves the previous file untouched and removes the temp file.
// Returns false with `error` set; never writes anywhere else (no CWD fallback).
bool save(const std::string& path, const UserSettings& settings, std::string& error);

// --- policies ---------------------------------------------------------------------
// D8's resolution rule applied to a persisted size: the index of `stored` in
// `available`, or 0 (desktop) when the current display does not offer it. `available`
// always has {0,0} at index 0, which is what makes the fallback safe on a new display.
int chooseResolutionIndex(const std::vector<DisplaySize>& available, DisplaySize stored);

}  // namespace settings
