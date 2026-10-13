#include "settings/user_settings.h"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <optional>
#include <sstream>

#if !defined(_WIN32) && !defined(__EMSCRIPTEN__)
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#include "input/input_sdl3.h"

namespace settings {
namespace {

// Bounds the parser before it allocates or loops: a hostile "config" cannot make the
// port spend memory or time on it.
constexpr size_t kMaxBytes = 64 * 1024;
constexpr size_t kMaxLine = 512;
constexpr size_t kMaxValueLength = 64;   // GUIDs are 32 hex chars; names are shorter
constexpr int    kMaxDimension = 16384;  // generous ceiling for a stored pixel size
// The remembered game folder (issue #36) is the one value that is a PATH, so it gets its
// own budget: a path must fit one line with "install_dir = " in front of it (kMaxLine is
// the hard structural limit). A longer one is a value error, and serialize() drops it
// rather than write a document that could not be read back.
constexpr size_t kMaxPathValue = 480;

std::string trimmed(const std::string& s) {
    size_t begin = 0, end = s.size();
    while (begin < end && std::isspace(static_cast<unsigned char>(s[begin]))) ++begin;
    while (end > begin && std::isspace(static_cast<unsigned char>(s[end - 1]))) --end;
    return s.substr(begin, end - begin);
}

bool parseInt(const std::string& text, int& out) {
    if (text.empty() || text.size() > 12) return false;
    const char* begin = text.c_str();
    char* end = nullptr;
    const long value = std::strtol(begin, &end, 10);
    if (end != begin + text.size()) return false;   // trailing junk ("12abc", "1e9")
    if (value < -1000000L || value > 1000000L) return false;
    out = static_cast<int>(value);
    return true;
}

// "1"/"true"/"yes"/"on" and their negatives; anything else is not a boolean (nullopt), which
// the caller reports as "keeping the default".
std::optional<bool> parseBool(const std::string& text) {
    std::string lowered;
    lowered.reserve(text.size());
    for (const char c : text) lowered.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
    if (lowered == "1" || lowered == "true" || lowered == "yes" || lowered == "on") return true;
    if (lowered == "0" || lowered == "false" || lowered == "no" || lowered == "off") return false;
    return std::nullopt;
}

// "1920x1080", "desktop" or "0x0". Anything else is a value error.
bool parseDisplaySize(const std::string& text, DisplaySize& out) {
    if (text == "desktop") { out = {0, 0}; return true; }
    const size_t x = text.find('x');
    if (x == std::string::npos) return false;
    int width = 0, height = 0;
    if (!parseInt(text.substr(0, x), width) || !parseInt(text.substr(x + 1), height)) return false;
    if (width < 0 || height < 0 || width > kMaxDimension || height > kMaxDimension) return false;
    out = {width, height};
    return true;
}

bool validText(const std::string& value) {
    if (value.size() > kMaxValueLength) return false;
    for (const char c : value) {
        const unsigned char u = static_cast<unsigned char>(c);
        if (u < 0x20 || u == 0x7f) return false;   // no control bytes in a GUID/name
    }
    return true;
}

// Absolute means the same folder wherever the port is started from, which is the only kind
// worth remembering — the same reasoning configDirectory() applies to $XDG_CONFIG_HOME.
// Windows is a cross-build-only target, but its spelling is accepted there too so one
// document stays meaningful on both.
bool absolutePath(const std::string& value) {
    if (value.empty()) return false;
#if defined(_WIN32)
    if (value.size() >= 3 && std::isalpha(static_cast<unsigned char>(value[0])) && value[1] == ':' &&
        (value[2] == '\\' || value[2] == '/'))
        return true;
#endif
    return value[0] == '/';
}

// A comma-separated action table: exactly fnd::input::ActionCount entries.
bool parseBindingRow(const std::string& text, int* out, int count, int minimum, int maximum,
                     std::string& why) {
    std::vector<std::string> parts;
    size_t begin = 0;
    while (begin <= text.size()) {
        const size_t comma = text.find(',', begin);
        parts.push_back(trimmed(text.substr(begin, comma == std::string::npos ? comma : comma - begin)));
        if (comma == std::string::npos) break;
        begin = comma + 1;
    }
    if (static_cast<int>(parts.size()) != count) {
        why = "expected " + std::to_string(count) + " values, got " + std::to_string(parts.size());
        return false;
    }
    for (int i = 0; i < count; ++i) {
        int value = 0;
        if (!parseInt(parts[static_cast<size_t>(i)], value) || value < minimum || value > maximum) {
            why = "entry " + std::to_string(i) + " is not in " + std::to_string(minimum) + ".." +
                  std::to_string(maximum);
            return false;
        }
        out[i] = value;
    }
    return true;
}

// Applies one parsed binding row to a target of fnd::input::ActionCount entries. `maximum` is
// the row's own code bound: scancodes for the keyboard, pad buttons for a gamepad. A v1 row is
// one entry wider than the current layout — it carries the removed heavy action at
// kLegacyHeavyIndex — so every action from that index on is read one entry further along.
bool applyBindingRow(const std::string& value, bool legacyLayout, int maximum, int* target,
                     std::string& why) {
    int row[kLegacyActionCount] = {};
    const int width = legacyLayout ? kLegacyActionCount : fnd::input::ActionCount;
    if (!parseBindingRow(value, row, width, -1, maximum, why)) return false;
    for (int a = 0; a < fnd::input::ActionCount; ++a)
        target[a] = row[a < kLegacyHeavyIndex ? a : a + (legacyLayout ? 1 : 0)];
    return true;
}

// The action names the file uses, in fnd::input::Action order. A name is self-describing
// and survives an enum insertion, which a positional table would not.
struct ActionName { fnd::input::Action action; const char* name; };
constexpr ActionName kActionNames[] = {
    {fnd::input::Up, "up"},           {fnd::input::Down, "down"},
    {fnd::input::Left, "left"},       {fnd::input::Right, "right"},
    {fnd::input::AttackA, "attack_a"},
    {fnd::input::Guard, "guard"},     {fnd::input::Shoot, "shoot"},
    {fnd::input::Jump, "jump"},       {fnd::input::Special, "special"},
    {fnd::input::Tactics, "tactics"}, {fnd::input::LockSwitch, "lock_switch"},
    {fnd::input::Pause, "pause"},
};
static_assert(sizeof(kActionNames) / sizeof(kActionNames[0]) == fnd::input::ActionCount,
              "the persisted action names must cover every action");

}  // namespace

UserSettings::UserSettings() {
    // The same tables the input backend starts from, so "no config" and "default config"
    // are the same bindings.
    for (int a = 0; a < fnd::input::ActionCount; ++a) keyboard[static_cast<size_t>(a)] = fnd::input::sdl3::kP1ScancodeByAction[a];
    for (auto& pad : gamepad)
        for (int a = 0; a < fnd::input::ActionCount; ++a) pad[static_cast<size_t>(a)] = fnd::input::sdl3::kPadButtonByAction[a];
}

bool UserSettings::operator==(const UserSettings& other) const {
    return installDir == other.installDir && fullscreen == other.fullscreen &&
           resolution == other.resolution &&
           toonRendering == other.toonRendering &&
           shadowRendering == other.shadowRendering &&
           volumes.master == other.volumes.master && volumes.music == other.volumes.music &&
           volumes.voice == other.volumes.voice && volumes.sfx == other.volumes.sfx &&
           keyboard == other.keyboard && gamepad == other.gamepad && padGuid == other.padGuid &&
           padName == other.padName;
}

std::string configDirectory(const char* xdgConfigHome, const char* home) {
    // XDG: an empty or RELATIVE $XDG_CONFIG_HOME is invalid and falls back to
    // $HOME/.config (base directory spec). A hostile value therefore cannot redirect the
    // write into the working directory.
    const std::string xdg = xdgConfigHome ? xdgConfigHome : "";
    if (absolutePath(xdg)) return xdg + "/" + kAppDirectory;
    const std::string base = home ? home : "";
    if (base.empty()) return {};
    return base + "/.config/" + kAppDirectory;
}

std::string configFilePath(const char* xdgConfigHome, const char* home) {
    const std::string dir = configDirectory(xdgConfigHome, home);
    return dir.empty() ? std::string() : dir + "/" + kFileName;
}

std::string defaultConfigPath() {
    return configFilePath(std::getenv("XDG_CONFIG_HOME"), std::getenv("HOME"));
}

bool persistenceSupported() {
#if defined(__EMSCRIPTEN__)
    return false;
#else
    return true;
#endif
}

bool storableInstallDir(const std::string& value) {
    return absolutePath(value) && value.size() <= kMaxPathValue;
}

bool parse(const std::string& text, UserSettings& out, std::string& error, LoadReport& report) {
    // Reset only what this function owns: load() records `existed` before it calls here.
    report.warnings = 0;
    report.messages.clear();
    report.loaded = false;
    error.clear();
    if (text.size() > kMaxBytes) {
        error = "config is larger than " + std::to_string(kMaxBytes) + " bytes";
        return false;
    }
    if (text.find('\0') != std::string::npos) {
        error = "config contains a NUL byte (binary file?)";
        return false;
    }

    UserSettings candidate;   // defaults; only a clean parse reaches `out`
    // The document's own version, 0 until its version line is read. The migration switch at
    // the end of this function keys off it: v1 is the one migration that DROPS a value (the
    // removed heavy-melee binding) and therefore warns, while v2..v5 are additive and report
    // context instead (see the header).
    int documentVersion = 0;
    // The remembered folder must be PRESENT, even empty: "not set" and "no folder chosen"
    // are different statements, and only the first is worth a warning.
    bool sawInstallDir = false;
    std::string section;
    std::istringstream stream(text);
    std::string raw;
    int lineNumber = 0;
    // The parser's two report forms, both stamped with the line they came from: `fail` rejects
    // the whole document (a structure error), `warn` defaults the one key and keeps going (a
    // value error). `fail`'s argument is the rest of the message, separator included — ": ..."
    // for a parse error, " is ..." for the raw-length guard below.
    auto fail = [&](const std::string& rest) {
        error = "line " + std::to_string(lineNumber) + rest;
        return false;
    };
    auto warn = [&](const std::string& what) {
        ++report.warnings;
        report.messages.push_back("line " + std::to_string(lineNumber) + ": " + what);
    };
    while (std::getline(stream, raw)) {
        ++lineNumber;
        if (raw.size() > kMaxLine) {
            return fail(" is longer than " + std::to_string(kMaxLine) + " bytes");
        }
        if (!raw.empty() && raw.back() == '\r') raw.pop_back();
        const std::string line = trimmed(raw);
        if (line.empty() || line[0] == '#' || line[0] == ';') continue;

        if (line.front() == '[') {
            if (line.back() != ']') return fail(": unterminated section header");
            section = trimmed(line.substr(1, line.size() - 2));
            if (section != "game" && section != "display" && section != "render" &&
                section != "audio" && section != "bindings" && section != "controllers") {
                return fail(": unknown section [" + section + "]");
            }
            continue;
        }

        const size_t equals = line.find('=');
        if (equals == std::string::npos) return fail(": expected key = value");
        const std::string key = trimmed(line.substr(0, equals));
        const std::string value = trimmed(line.substr(equals + 1));
        if (key.empty()) return fail(": empty key");
        if (value.size() > kMaxLine) return fail(": value too long");

        // Nothing but the version line may stand outside a section, and a section header is
        // what fills `section` (an empty or unknown one was rejected above).
        if (section.empty()) {
            if (key == "version") {
                int version = 0;
                if (!parseInt(value, version)) return fail(": version is not a number");
                if (version != kSchemaVersion && version != kSchemaVersionLegacy &&
                    version != kSchemaVersionV2 && version != kSchemaVersionV3 &&
                    version != kSchemaVersionV4) {
                    error = "unsupported config version " + std::to_string(version) +
                            " (this build writes " + std::to_string(kSchemaVersion) + ")";
                    return false;
                }
                documentVersion = version;
                continue;
            }
            return fail(": key '" + key +
                        "' before any section (only version = belongs here)");
        }

        if (section == "game") {
            // v4's section (issue #36). An empty value is the documented "no folder is
            // remembered" spelling — the one serialize() writes for a fresh document — so
            // it is not a warning; a relative or over-long folder is a value error for
            // this key (the folder stays unchosen, every other key still applies).
            if (key == "install_dir") {
                sawInstallDir = true;
                if (value.empty()) {
                    candidate.installDir.clear();
                } else if (value.size() > kMaxPathValue) {
                    warn("install_dir: the folder is longer than " + std::to_string(kMaxPathValue) +
                         " bytes, which does not fit one line of the file, ignoring it");
                } else if (!absolutePath(value)) {
                    warn("install_dir: '" + value + "' is not an absolute folder, ignoring it");
                } else {
                    candidate.installDir = value;
                }
            } else {
                warn("ignoring unknown key '" + key + "'");
            }
        } else if (section == "display") {
            if (key == "fullscreen") {
                const std::optional<bool> on = parseBool(value);
                if (!on) warn("fullscreen: keeping the default");
                else candidate.fullscreen = *on;
            } else if (key == "resolution") {
                DisplaySize size;
                if (!parseDisplaySize(value, size)) warn("resolution: keeping the default");
                else candidate.resolution = size;
            } else {
                warn("ignoring unknown key '" + key + "'");
            }
        } else if (section == "render") {
            // v3's section. Read whatever the version line says: a key this build knows is
            // never a reason to reject or warn (see the header).
            if (key == "toon") {
                const std::optional<bool> on = parseBool(value);
                if (!on) warn("toon: keeping the default");
                else candidate.toonRendering = *on;
            } else if (key == "shadows") {
                const std::optional<bool> on = parseBool(value);
                if (!on) warn("shadows: keeping the default");
                else candidate.shadowRendering = *on;
            } else {
                warn("ignoring unknown key '" + key + "'");
            }
        } else if (section == "audio") {
            int* slot = nullptr;
            if (key == "master") slot = &candidate.volumes.master;
            else if (key == "music") slot = &candidate.volumes.music;
            else if (key == "voice") slot = &candidate.volumes.voice;
            else if (key == "sfx") slot = &candidate.volumes.sfx;
            if (!slot) {
                warn("ignoring unknown key '" + key + "'");
            } else {
                int volume = 0;
                if (!parseInt(value, volume) || volume < 0 || volume > 100)
                    warn(key + ": expected 0..100, keeping the default");
                else
                    *slot = volume;
            }
        } else if (section == "bindings") {
            // A v1 row is read with the v1 width; the shift past the dropped heavy action
            // lives in applyBindingRow (see the header).
            const bool legacyLayout = documentVersion == kSchemaVersionLegacy;
            if (key == "keyboard") {
                std::string why;
                if (!applyBindingRow(value, legacyLayout, kMaxScancode, candidate.keyboard.data(),
                                     why))
                    warn("keyboard: " + why + ", keeping the defaults");
            } else if (key.size() > 3 && key.compare(0, 3, "pad") == 0 &&
                       key[3] >= '1' && key[3] <= '4') {
                const int player = key[3] - '1';
                if (key.size() != 4) {
                    warn("ignoring unknown key '" + key + "'");
                } else {
                    std::string why;
                    if (!applyBindingRow(value, legacyLayout, kMaxPadButton,
                                         candidate.gamepad[static_cast<size_t>(player)].data(),
                                         why))
                        warn(key + ": " + why + ", keeping the defaults");
                }
            } else {
                warn("ignoring unknown key '" + key + "'");
            }
        } else if (section == "controllers") {
            // padN_guid / padN_name. Values are opaque identity strings, kept only if
            // they are printable and short; a wrong one just means no GUID preference.
            if (key.size() > 5 && key.compare(0, 3, "pad") == 0 && key[3] >= '1' && key[3] <= '4') {
                const int player = key[3] - '1';
                const std::string field = key.substr(4);
                if (field == "_guid" || field == "_name") {
                    if (!validText(value)) {
                        warn(key + ": unusable text, ignoring");
                    } else if (field == "_guid") {
                        candidate.padGuid[static_cast<size_t>(player)] = value;
                    } else {
                        candidate.padName[static_cast<size_t>(player)] = value;
                    }
                } else {
                    warn("ignoring unknown key '" + key + "'");
                }
            } else {
                warn("ignoring unknown key '" + key + "'");
            }
        }
    }

    if (documentVersion == 0) {
        error = "missing version line";
        return false;
    }
    switch (documentVersion) {
    case kSchemaVersionLegacy:
        // The only migration that drops a value, so the only one that warns.
        ++report.warnings;
        report.messages.push_back(
            "config version 1: migrated to " + std::to_string(kSchemaVersion) +
            " (the removed heavy-melee binding was dropped, every other binding kept; no "
            "game folder is remembered until a run opens one)");
        break;
    case kSchemaVersionV2:
        report.messages.push_back(
            "config version 2: migrated to " + std::to_string(kSchemaVersion) +
            " (toon rendering defaults to off, no game folder is remembered until a run "
            "opens one, and shadows default to off; every stored value kept)");
        break;
    case kSchemaVersionV3:
        report.messages.push_back(
            "config version 3: migrated to " + std::to_string(kSchemaVersion) +
            " (the game folder is remembered in this file from now on and shadows default "
            "to off; every stored value kept)");
        break;
    case kSchemaVersionV4:
        report.messages.push_back(
            "config version 4: migrated to " + std::to_string(kSchemaVersion) +
            " (character shadows default to off; every stored value kept)");
        break;
    case kSchemaVersion:
        // A CURRENT document always carries the folder key — serialize() writes it even when
        // no folder is remembered — so its absence is a hand-edit or a lossy writer, and the
        // one thing that changes is worth a warning. The older documents above cannot have
        // the key and get their context line instead, the rule #21's v2 migration follows.
        if (!sawInstallDir) {
            ++report.warnings;
            report.messages.push_back(
                "install_dir: a version " + std::to_string(kSchemaVersion) +
                " document should carry the game folder key, so no folder is remembered");
        }
        break;
    }
    out = candidate;
    report.loaded = true;
    return true;
}

std::string serialize(const UserSettings& settings) {
    std::ostringstream out;
    out << "# daybreak-decomp user settings (issue #19). Written atomically; delete this\n"
        << "# file to reset every setting to its default. Session state (earned titles,\n"
        << "# result stats) is deliberately not stored here.\n"
        << "# Format and policies: remake/foundation/docs/USER-SETTINGS.md\n"
        << "version = " << kSchemaVersion << "\n\n";

    // The key is ALWAYS written, empty when no folder is remembered: the load reports a
    // MISSING key (an older file, a hand-edit) as "nothing is remembered", so the port's
    // own output must always carry it. A value the parser would refuse to read back — a
    // relative folder, or one that does not fit the line budget — is written as empty
    // rather than producing a document that cannot round-trip.
    out << "[game]\n"
        << "# The game folder this port last opened (issue #36). Absolute; empty means no\n"
        << "# folder is remembered yet. --install= and $DAYBREAK_INSTALL still win for a\n"
        << "# single run, and the packaged launcher reads this key.\n"
        << "install_dir = "
        << (storableInstallDir(settings.installDir) ? settings.installDir : std::string())
        << "\n\n";

    out << "[display]\n"
        << "fullscreen = " << (settings.fullscreen ? "true" : "false") << "\n"
        << "resolution = ";
    if (settings.resolution.width <= 0 || settings.resolution.height <= 0) out << "desktop";
    else out << settings.resolution.width << "x" << settings.resolution.height;
    out << "\n\n";

    out << "[render]\n"
        << "# The Options screen's toon-rendering row (issue #21): the characters' diffuse\n"
        << "# term reads the shipped data/directX/toon ramp instead of the linear N.L.\n"
        << "toon = " << (settings.toonRendering ? "true" : "false") << "\n"
        << "# The Options screen's shadow row (issue #21 row 1, 影の表示): every fighter's\n"
        << "# body and weapon are drawn once more into a light-space map that the stage\n"
        << "# samples, so the fighters cast a shadow on the ground.\n"
        << "shadows = " << (settings.shadowRendering ? "true" : "false") << "\n\n";

    out << "[audio]\n"
        << "master = " << settings.volumes.master << "\n"
        << "music = " << settings.volumes.music << "\n"
        << "voice = " << settings.volumes.voice << "\n"
        << "sfx = " << settings.volumes.sfx << "\n\n";

    out << "[bindings]\n"
        << "# One comma-separated value per action, in this order:\n";
    constexpr size_t kNamesPerLine = 8;
    const size_t nameCount = sizeof(kActionNames) / sizeof(kActionNames[0]);
    for (size_t i = 0; i < nameCount; ++i) {
        out << (i % kNamesPerLine == 0 ? "#   " : " ") << kActionNames[i].name;
        if (i + 1 != nameCount) out << ",";
        if (i % kNamesPerLine == kNamesPerLine - 1 || i + 1 == nameCount) out << "\n";
    }
    out << "# -1 is unbound. keyboard values are SDL scancodes; pad values are SDL gamepad\n"
        << "# buttons (the same numbering the options screen prints).\n"
        << "keyboard = ";
    for (int a = 0; a < fnd::input::ActionCount; ++a)
        out << (a ? ", " : "") << settings.keyboard[static_cast<size_t>(a)];
    out << "\n";
    for (int p = 0; p < fnd::input::kMaxPlayers; ++p) {
        out << "pad" << (p + 1) << " = ";
        for (int a = 0; a < fnd::input::ActionCount; ++a)
            out << (a ? ", " : "") << settings.gamepad[static_cast<size_t>(p)][static_cast<size_t>(a)];
        out << "\n";
    }
    out << "\n[controllers]\n"
        << "# The controller that last used each player slot. Bindings stay on the PLAYER\n"
        << "# (the original's keyconfig is per player); the GUID only decides which slot a\n"
        << "# pad is given when it is plugged in, so a replug cannot move bindings to\n"
        << "# another pad. Cleared when no pad has been seen yet.\n";
    for (int p = 0; p < fnd::input::kMaxPlayers; ++p) {
        out << "pad" << (p + 1) << "_guid = " << settings.padGuid[static_cast<size_t>(p)] << "\n";
        out << "pad" << (p + 1) << "_name = " << settings.padName[static_cast<size_t>(p)] << "\n";
    }
    return out.str();
}

bool load(const std::string& path, UserSettings& out, LoadReport& report) {
    report = LoadReport{};
    if (!persistenceSupported() || path.empty()) {
        report.messages.push_back("user settings are not persisted on this target");
        return false;
    }
    std::ifstream file(std::filesystem::u8path(path), std::ios::binary);
    if (!file) {
        report.messages.push_back("no config file at " + path + " (first launch)");
        return false;
    }
    report.existed = true;
    std::ostringstream buffer;
    buffer << file.rdbuf();
    if (file.bad()) {
        report.messages.push_back("cannot read " + path);
        return false;
    }
    std::string error;
    if (!parse(buffer.str(), out, error, report)) {
        report.loaded = false;
        report.messages.push_back("ignoring " + path + ": " + error);
        return false;
    }
    report.loaded = true;
    return true;
}

bool save(const std::string& path, const UserSettings& settings, std::string& error) {
    error.clear();
    if (!persistenceSupported()) {
        error = "user settings are not persisted on this target";
        return false;
    }
    if (path.empty()) {
        error = "no user config directory ($XDG_CONFIG_HOME/$HOME are unset)";
        return false;
    }
    const size_t slash = path.find_last_of("/\\");
    const std::string directory = slash == std::string::npos ? std::string(".") : path.substr(0, slash);
    const std::string text = serialize(settings);

    namespace fs = std::filesystem;
    // The XDG path may not exist yet (first run, a nested value, a path with spaces), so
    // create the whole directory; a failure here is the unwritable-directory case and is
    // reported by the write below.
    std::error_code ec;
    fs::create_directories(fs::u8path(directory), ec);

#if defined(_WIN32) || defined(__EMSCRIPTEN__)
    // Best-effort fallback for the non-Linux targets: still a temp file in the same
    // directory and a rename, but without fsync (the issue's atomicity requirement is a
    // Linux one; the Windows cross-build only has to compile and behave).
    const std::string temp = path + ".tmp";
    {
        std::ofstream out(fs::u8path(temp), std::ios::binary | std::ios::trunc);
        if (!out) { error = "cannot write " + temp; return false; }
        out << text;
        out.flush();
        if (!out) { error = "cannot write " + temp; return false; }
    }
    fs::rename(fs::u8path(temp), fs::u8path(path), ec);
    if (ec) { fs::remove(fs::u8path(temp), ec); error = "cannot replace " + path; return false; }
    return true;
#else
    const std::string temp = path + ".tmp";
    const int fd = ::open(temp.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd < 0) {
        error = "cannot create " + temp;
        return false;
    }
    // O_CREAT does not touch the mode of a file that already exists, and a leftover temp
    // file from a crashed writer is exactly that: force the private mode every time.
    ::fchmod(fd, 0600);
    size_t written = 0;
    while (written < text.size()) {
        const ssize_t n = ::write(fd, text.data() + written, text.size() - written);
        if (n <= 0) {
            ::close(fd);
            ::unlink(temp.c_str());
            error = "cannot write " + temp;
            return false;
        }
        written += static_cast<size_t>(n);
    }
    if (::fsync(fd) != 0) {
        ::close(fd);
        ::unlink(temp.c_str());
        error = "cannot flush " + temp;
        return false;
    }
    ::close(fd);
    if (::rename(temp.c_str(), path.c_str()) != 0) {
        ::unlink(temp.c_str());
        error = "cannot replace " + path;
        return false;
    }
    // fsync the directory so the rename itself is durable, not just the data.
    const int dir = ::open(directory.c_str(), O_RDONLY);
    if (dir >= 0) {
        ::fsync(dir);
        ::close(dir);
    }
    return true;
#endif
}

int chooseResolutionIndex(const std::vector<DisplaySize>& available, DisplaySize stored) {
    if (available.empty()) return 0;
    // Desktop is always index 0 in the port's list (main.cpp builds it that way), so it
    // is the fallback both for "the user chose desktop" and for "the display changed".
    if (stored.width <= 0 || stored.height <= 0) return 0;
    for (size_t i = 0; i < available.size(); ++i)
        if (available[i] == stored) return static_cast<int>(i);
    return 0;
}

}  // namespace settings
