// settings persistence host test (issue #19): the parser, the validator, the atomic
// write and the two placement policies — all device-free (no SDL, no window, no pad).
#include "settings/user_settings.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#if !defined(_WIN32)
#include <unistd.h>
#endif

#include "input/gamepad_identity.h"
#include "input/input_sdl3.h"

namespace fs = std::filesystem;

namespace {

int g_checks = 0;
int g_failures = 0;

void check(bool ok, const std::string& what) {
    ++g_checks;
    if (!ok) {
        ++g_failures;
        std::printf("  FAIL %s\n", what.c_str());
    }
}

void checkInt(const std::string& what, long long expected, long long actual) {
    ++g_checks;
    if (expected != actual) {
        ++g_failures;
        std::printf("  FAIL %s: expected %lld, got %lld\n", what.c_str(), expected, actual);
    }
}

void checkStr(const std::string& what, const std::string& expected, const std::string& actual) {
    ++g_checks;
    if (expected != actual) {
        ++g_failures;
        std::printf("  FAIL %s: expected '%s', got '%s'\n", what.c_str(), expected.c_str(),
                    actual.c_str());
    }
}

// A fresh directory per case, so no case can see another's file.
fs::path scratch(const char* name) {
    const fs::path dir = fs::temp_directory_path() / (std::string("dbd19-") + name);
    std::error_code ec;
    fs::remove_all(dir, ec);
    fs::create_directories(dir, ec);
    return dir;
}

void writeFile(const fs::path& path, const std::string& text) {
    std::ofstream file(path, std::ios::binary | std::ios::trunc);
    file << text;
}

// Parses and reports the verdict, keeping the call sites one line each.
bool parses(const std::string& text, settings::UserSettings& out, std::string& error) {
    settings::LoadReport report;
    return settings::parse(text, out, error, report);
}

}  // namespace

int main() {
    std::printf("\n-- defaults: no config is the same as the shipped bindings\n");
    {
        settings::UserSettings defaults;
        checkInt("keyboard Up default", fnd::input::sdl3::kP1ScancodeByAction[fnd::input::Up],
                 defaults.keyboard[fnd::input::Up]);
        checkInt("every action has a default binding (no unbound stand-in left)",
                 fnd::input::sdl3::kP1ScancodeByAction[fnd::input::Pause],
                 defaults.keyboard[fnd::input::Pause]);
        for (int a = 0; a < fnd::input::ActionCount; ++a)
            check(defaults.keyboard[static_cast<size_t>(a)] ==
                      fnd::input::sdl3::kP1ScancodeByAction[a],
                  "keyboard default for action " + std::to_string(a));
        checkInt("pad1 Guard default", fnd::input::sdl3::kPadButtonByAction[fnd::input::Guard],
                 defaults.gamepad[0][fnd::input::Guard]);
        checkInt("master default", 100, defaults.volumes.master);
        checkInt("music default", 100, defaults.volumes.music);
        checkInt("voice default", 100, defaults.volumes.voice);
        checkInt("sfx default", 100, defaults.volumes.sfx);
        check(!defaults.fullscreen, "fullscreen default is off");
        check(defaults.resolution == settings::DisplaySize{0, 0}, "resolution default is desktop");
        check(defaults.padGuid[0].empty() && defaults.padGuid[3].empty(),
              "no controller identity before a pad is seen");
    }

    std::printf("\n-- round trip: serialize -> parse is lossless for the persisted set\n");
    {
        settings::UserSettings original;
        original.fullscreen = true;
        original.resolution = {1280, 720};
        original.volumes = {80, 70, 60, 50};
        original.keyboard[fnd::input::Jump] = 42;
        original.keyboard[fnd::input::Guard] = -1;   // an explicitly unbound action
        original.gamepad[2][fnd::input::Guard] = 7;
        original.padGuid[1] = "030000005e0400008e02000000007801";
        original.padName[1] = "Xbox Wireless Controller";
        settings::UserSettings parsed;
        std::string error;
        check(parses(settings::serialize(original), parsed, error),
              "the port's own output parses: " + error);
        check(parsed == original, "round trip preserves every persisted field");
        check(parses(settings::serialize(settings::UserSettings{}), parsed, error),
              "the default document parses");
        check(parsed == settings::UserSettings{}, "the default document round-trips");
        // The document must not grow a session-state field by accident: no persisted KEY
        // may name one (the header comment explains why they are absent).
        bool sessionKey = false;
        std::istringstream lines(settings::serialize(original));
        std::string line;
        while (std::getline(lines, line)) {
            if (line.empty() || line[0] == '#' || line[0] == ';' || line[0] == '[') continue;
            const size_t equals = line.find('=');
            if (equals == std::string::npos) continue;
            const std::string key = line.substr(0, equals);
            if (key.find("title") != std::string::npos || key.find("result") != std::string::npos ||
                key.find("session") != std::string::npos || key.find("punish") != std::string::npos)
                sessionKey = true;
        }
        check(!sessionKey, "no session state (titles/results) is serialized");
    }

    std::printf("\n-- versioning: only this schema version is applied\n");
    {
        settings::UserSettings out;
        std::string error;
        check(!parses("[display]\nfullscreen = true\n", out, error), "missing version is rejected");
        check(error.find("version") != std::string::npos, "the reason names the version line");
        check(!parses("version = 3\n[display]\nfullscreen = true\n", out, error),
              "an unsupported version is rejected");
        check(error.find("unsupported config version 3") != std::string::npos,
              "the reason names the version it found");
        // v1 is the previous schema and is MIGRATED, not rejected (issue #10 removed the
        // port-invented heavy binding, which shortened the binding rows).
        check(parses("version = 1\n[display]\nfullscreen = true\n", out, error),
              "the previous schema still loads");
        check(!parses("version = 1.0\n", out, error), "a non-integer version is rejected");
        check(parses("version = 1\nversion = 1\n", out, error),
              "a repeated version line is accepted (last wins)");
        check(!parses("[display]\nversion = 1\n", out, error),
              "version inside a section does not count as the version line");
        // An unknown key is forward compatibility, not corruption; an unknown SECTION is
        // not, because a newer schema ships with a version bump.
        settings::LoadReport report;
        check(!settings::parse("version = 1\n[render]\ntoon = 1\n", out, error, report),
              "an unknown section is rejected");
        settings::UserSettings warned;
        check(settings::parse("version = 2\n[audio]\nmaster = 40\nsurround = 1\n", warned, error, report),
              "an unknown key inside a known section is tolerated");
        checkInt("the known key still applied", 40, warned.volumes.master);
        checkInt("one warning for the unknown key", 1, report.warnings);
    }

    std::printf("\n-- malformed files: structure errors reject the whole document\n");
    {
        settings::UserSettings out;
        std::string error;
        const char* cases[] = {
            "this is not a config file at all\n",
            "master = 50\n",                                  // key before any section
            "version = 1\n[display\nfullscreen = true\n",      // unterminated section
            "version = 1\n[display]\nfullscreen\n",            // no '='
            "version = 1\n[display]\n = true\n",               // empty key
            "version = 1\n[render]\ntoon = 1\n",               // unknown section
        };
        for (const char* text : cases) {
            out = settings::UserSettings{};
            check(!parses(text, out, error), std::string("rejected: ") + text);
            check(out == settings::UserSettings{}, "a rejected file leaves the defaults alone");
            check(!error.empty(), "a rejection always explains itself");
        }
        // A binary file (the original's config.dat, a truncated download) must not be
        // parsed as text.
        std::string binary = "version = 1\n[audio]\nmaster = 50\n";
        binary.push_back('\0');
        binary += "junk";
        out = settings::UserSettings{};
        check(!parses(binary, out, error), "a NUL byte is rejected");
        check(error.find("NUL") != std::string::npos, "the reason names the NUL byte");
        // The report keeps what the loader already knew: the file was there.
        {
            const fs::path dir = scratch("report");
            const std::string path = (dir / "settings.conf").string();
            writeFile(path, "garbage\n");
            settings::LoadReport report;
            settings::UserSettings ignored;
            check(!settings::load(path, ignored, report), "a present but malformed file fails to load");
            check(report.existed, "the report still says the file existed");
            check(!report.loaded, "and that nothing was applied");
            check(!report.messages.empty(), "with a reason for the console");
        }
        // Truncation: a file cut anywhere must not be applied half-way. Cutting the port's
        // own output mid-line is the realistic case (a killed writer without the atomic
        // rename cannot happen, but a hand-edited file can).
        const std::string full = settings::serialize(settings::UserSettings{});
        bool rejectedSomewhere = false;
        for (size_t cut = 1; cut < full.size(); cut += 37) {
            out = settings::UserSettings{};
            if (!parses(full.substr(0, cut), out, error)) rejectedSomewhere = true;
        }
        check(rejectedSomewhere, "a truncated document is rejected, not applied");
        // Size and line limits: a hostile file cannot make the parser work.
        out = settings::UserSettings{};
        check(!parses("version = 1\n" + std::string(70 * 1024, '#'), out, error),
              "an oversized file is rejected");
        out = settings::UserSettings{};
        check(!parses("version = 1\n[audio]\nmaster = " + std::string(600, '1'), out, error),
              "an oversized line is rejected");
        out = settings::UserSettings{};
        check(!parses("version = 1\n[audio]\n" + std::string(2000, 'k') + " = 1\n", out, error),
              "an oversized key is rejected");
    }

    std::printf("\n-- value errors: that key keeps its default, the rest still applies\n");
    {
        settings::LoadReport report;
        settings::UserSettings out;
        std::string error;
        const std::string text =
            "version = 2\n"
            "[display]\n"
            "fullscreen = maybe\n"
            "resolution = 1280x720\n"
            "[audio]\n"
            "master = 101\n"
            "music = -1\n"
            "voice = abc\n"
            "sfx = 55\n"
            "[bindings]\n"
            "keyboard = 1,2,3\n"
            "pad1 = 1,2,3,4,5,6,7,8,9,10,11,12,26\n"
            "[controllers]\n"
            "pad1_guid = short\n";
        check(settings::parse(text, out, error, report), "a value error does not reject the file: " + error);
        check(!out.fullscreen, "fullscreen kept its default");
        check(out.resolution == settings::DisplaySize{1280, 720}, "a valid value still applies");
        checkInt("master kept its default", 100, out.volumes.master);
        checkInt("music kept its default", 100, out.volumes.music);
        checkInt("voice kept its default", 100, out.volumes.voice);
        checkInt("sfx applied", 55, out.volumes.sfx);
        checkInt("a short keyboard row keeps every default",
                 fnd::input::sdl3::kP1ScancodeByAction[fnd::input::Jump], out.keyboard[fnd::input::Jump]);
        checkInt("an out-of-range pad button keeps every default",
                 fnd::input::sdl3::kPadButtonByAction[fnd::input::Guard], out.gamepad[0][fnd::input::Guard]);
        checkStr("a short GUID is still a usable identity", "short", out.padGuid[0]);
        checkInt("six warnings (5 values + the short row counts once each)", 6, report.warnings);
        // A v1 row is one entry WIDER (the removed heavy binding), so the same text is a
        // short row under v2 and a valid row under v1: the migration is what keeps an
        // existing config loading.
        {
            settings::LoadReport legacyReport;
            settings::UserSettings legacy;
            std::string row;
            for (int a = 0; a < fnd::input::ActionCount; ++a)
                row += (a ? "," : "") + std::to_string(10 + a);
            check(settings::parse("version = 2\n[bindings]\nkeyboard = " + row + "\n",
                                  legacy, error, legacyReport),
                  "the 12-entry row is the current width: " + error);
            std::string stale;
            for (int a = 0; a < 13; ++a) stale += (a ? "," : "") + std::to_string(10 + a);
            // A wrong-width row is a VALUE error (that row keeps its defaults, the rest of
            // the file still applies) — the module's documented rule.
            settings::LoadReport staleReport;
            settings::UserSettings staleOut;
            check(settings::parse("version = 2\n[bindings]\nkeyboard = " + stale + "\n",
                                  staleOut, error, staleReport),
                  "a 13-entry row does not reject the file");
            checkInt("it is one value warning", 1, staleReport.warnings);
            checkInt("and that row kept the defaults",
                     fnd::input::sdl3::kP1ScancodeByAction[fnd::input::Guard],
                     staleOut.keyboard[fnd::input::Guard]);
            settings::LoadReport migrated;
            settings::UserSettings out2;
            // The v1 row carries the removed heavy binding between AttackA and Guard: 13
            // entries, with the sixth being the heavy key.
            std::string v1row;
            for (int a = 0; a < 13; ++a) v1row += (a ? "," : "") + std::to_string(100 + a);
            std::string v1pad;
            for (int a = 0; a < 13; ++a) v1pad += (a ? "," : "") + std::to_string(a % 20);
            const std::string v1 = "version = 1\n[bindings]\nkeyboard = " + v1row +
                                   "\npad1 = " + v1pad + "\n[audio]\nmaster = 70\n";
            check(settings::parse(v1, out2, error, migrated), "a v1 config loads: " + error);
            checkInt("and reports the migration", 1, migrated.warnings);
            checkStr("bindings before the removed one are kept", "100",
                     std::to_string(out2.keyboard[fnd::input::Up]));
            checkStr("the entry AFTER the removed heavy binding shifted down", "106",
                     std::to_string(out2.keyboard[fnd::input::Guard]));
            checkInt("the removed heavy slot is gone: Guard is index 5",
                     (int)fnd::input::Guard, 5);
            checkInt("the last v1 entry lands on the last action", 112,
                     out2.keyboard[fnd::input::Pause]);
            checkInt("the pad row migrated the same way", 6 % 20,
                     out2.gamepad[0][fnd::input::Guard]);
            checkInt("and the rest of the file still applied", 70, out2.volumes.master);
            // Saving after a migration writes the current schema.
            const std::string saved = settings::serialize(out2);
            check(saved.find("version = 2") != std::string::npos,
                  "a migrated document saves as the current version");
        }
        // Inline comments are not a feature: the value must parse whole.
        report = settings::LoadReport{};
        out = settings::UserSettings{};
        check(settings::parse("version = 1\n[audio]\nmaster = 50 # half\n", out, error, report),
              "a trailing comment is tolerated as a value error");
        checkInt("and the value keeps its default", 100, out.volumes.master);
        // Hostile text in the identity fields.
        report = settings::LoadReport{};
        out = settings::UserSettings{};
        std::string hostile = "version = 1\n[controllers]\npad2_name = ";
        hostile += std::string(200, 'x');
        hostile += "\npad3_guid = ok\n";
        check(settings::parse(hostile, out, error, report), "long text is a value error, not a rejection");
        check(out.padName[1].empty(), "an over-long name is dropped");
        checkStr("a valid sibling still applies", "ok", out.padGuid[2]);
    }

    std::printf("\n-- tolerant syntax: whitespace, comments, CRLF, desktop\n");
    {
        settings::UserSettings out;
        std::string error;
        const std::string text =
            "# a hand-edited file\r\n"
            "; another comment style\r\n"
            "version=1\r\n"
            "\r\n"
            "  [display]  \r\n"
            "  resolution = desktop  \r\n"
            "  fullscreen=on\r\n"
            "[audio]\r\n"
            "master=0\r\n"
            "[bindings]\r\n"
            "keyboard = -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1\r\n"
            "[controllers]\r\n"
            "pad4_guid = \r\n";
        check(parses(text, out, error), "a tolerant but valid file parses: " + error);
        check(out.fullscreen, "fullscreen = on");
        check(out.resolution == settings::DisplaySize{0, 0}, "resolution = desktop");
        checkInt("master = 0 (muted, not defaulted)", 0, out.volumes.master);
        checkInt("every action unbound", -1, out.keyboard[fnd::input::Up]);
        check(out.padGuid[3].empty(), "an empty GUID is no identity");
    }

    std::printf("\n-- paths: the XDG rule, including hostile values\n");
    {
        checkStr("absolute XDG wins", "/tmp/xdg/daybreak-decomp",
                 settings::configDirectory("/tmp/xdg", "/home/u"));
        checkStr("empty XDG falls back to HOME", "/home/u/.config/daybreak-decomp",
                 settings::configDirectory("", "/home/u"));
        checkStr("a RELATIVE XDG is invalid (spec) and falls back", "/home/u/.config/daybreak-decomp",
                 settings::configDirectory("relative/dir", "/home/u"));
        checkStr("no HOME either: no directory", "", settings::configDirectory(nullptr, nullptr));
        checkStr("the file inside it", "/tmp/xdg/daybreak-decomp/settings.conf",
                 settings::configFilePath("/tmp/xdg", "/home/u"));
        // A path with spaces is just a path: nothing here splits on whitespace.
        const fs::path spaced = scratch("space dir") / "nested dir";
        const std::string path = (spaced / "settings.conf").string();
        settings::UserSettings document;
        document.volumes.music = 33;
        std::string error;
        check(settings::save(path, document, error), "save into a path with spaces: " + error);
        settings::UserSettings loaded;
        settings::LoadReport report;
        check(settings::load(path, loaded, report), "load it back");
        checkInt("the value survived the spaced path", 33, loaded.volumes.music);
    }

    std::printf("\n-- atomic write: temp file, rename, no leftovers, no clobber on failure\n");
    {
        const fs::path dir = scratch("atomic");
        const std::string path = (dir / "settings.conf").string();
        settings::UserSettings first;
        first.volumes.master = 10;
        std::string error;
        check(settings::save(path, first, error), "first save: " + error);
        check(fs::exists(path), "the target exists");
        check(!fs::exists(path + ".tmp"), "no temp file is left behind");
        settings::UserSettings loaded;
        settings::LoadReport report;
        check(settings::load(path, loaded, report), "the written file loads");
        checkInt("content of the first save", 10, loaded.volumes.master);
        // A stale temp file from a crashed writer is replaced, not appended to.
        writeFile(path + ".tmp", "garbage that must not survive");
        settings::UserSettings second;
        second.volumes.master = 20;
        check(settings::save(path, second, error), "second save over a stale temp: " + error);
        check(!fs::exists(path + ".tmp"), "the stale temp file is gone");
        checkInt("content of the second save", 20, [&] {
            settings::UserSettings again;
            settings::LoadReport againReport;
            settings::load(path, again, againReport);
            return again.volumes.master;
        }());
        // Unwritable destination: the parent is a regular file, so the temp file cannot be
        // created. The previous content must survive untouched.
        const fs::path blockedParent = dir / "not-a-directory";
        writeFile(blockedParent, "x");
        const std::string blocked = (blockedParent / "settings.conf").string();
        settings::UserSettings third;
        third.volumes.master = 30;
        check(!settings::save(blocked, third, error), "an unwritable directory fails");
        check(!error.empty(), "and says why: " + error);
        settings::UserSettings stillThere;
        settings::LoadReport stillReport;
        check(settings::load(path, stillThere, stillReport), "the earlier file is still loadable");
        checkInt("and unchanged", 20, stillThere.volumes.master);
#if !defined(_WIN32)
        // A read-only directory is the same failure through the permission bit. Root
        // bypasses DAC, so this branch only runs unprivileged.
        if (::geteuid() != 0) {
            const fs::path readOnly = scratch("readonly");
            fs::permissions(readOnly, fs::perms::owner_read | fs::perms::owner_exec);
            check(!settings::save((readOnly / "settings.conf").string(), third, error),
                  "a read-only directory fails");
        }
#endif
        // The file is private (0600): it can carry a controller identity.
        std::error_code ec;
        const fs::perms perms = fs::status(path, ec).permissions();
        check((perms & fs::perms::group_all) == fs::perms::none &&
                  (perms & fs::perms::others_all) == fs::perms::none,
              "the config file is owner-only");
        // No config directory at all: load reports first launch, save refuses.
        settings::UserSettings none;
        settings::LoadReport noneReport;
        check(!settings::load("", none, noneReport), "an empty path is a first launch");
        check(!noneReport.existed, "and reports no file");
        check(!settings::save("", none, error), "an empty path cannot be written");
    }

    std::printf("\n-- resolution fallback: a changed display keeps a safe mode\n");
    {
        const std::vector<settings::DisplaySize> available = {{0, 0}, {800, 600}, {1920, 1080}};
        checkInt("stored size found", 2, settings::chooseResolutionIndex(available, {1920, 1080}));
        checkInt("desktop stays desktop", 0, settings::chooseResolutionIndex(available, {0, 0}));
        checkInt("a size this display does not offer falls back to desktop", 0,
                 settings::chooseResolutionIndex(available, {1280, 720}));
        checkInt("negative sizes fall back", 0, settings::chooseResolutionIndex(available, {-8, -8}));
        checkInt("an empty list still yields index 0", 0,
                 settings::chooseResolutionIndex({}, {1920, 1080}));
    }

    std::printf("\n-- stable-controller policy: bindings follow the player, not the pad order\n");
    {
        using fnd::input::preferredPadSlot;
        std::array<std::string, 4> hints{};
        // The backend marks slot 0 (keyboard) occupied.
        const std::array<bool, 4> keyboardOnly = {true, false, false, false};
        checkInt("no identity: lowest free pad slot", 1,
                 preferredPadSlot(hints, keyboardOnly, "padA"));
        hints[2] = "padA";
        checkInt("a recorded pad returns to its player", 2,
                 preferredPadSlot(hints, keyboardOnly, "padA"));
        checkInt("an unknown pad takes the lowest free slot", 1,
                 preferredPadSlot(hints, keyboardOnly, "padB"));
        // The replug case the policy exists for: the pads enumerate in the other order.
        hints[1] = "padA";
        hints[2] = "padB";
        std::array<bool, 4> occupied = {true, false, false, false};
        const int first = preferredPadSlot(hints, occupied, "padB");
        checkInt("pad B goes to player 2 even though it enumerated first", 2, first);
        occupied[static_cast<size_t>(first)] = true;
        checkInt("pad A goes to player 1", 1, preferredPadSlot(hints, occupied, "padA"));
        occupied[1] = true;
        checkInt("the last free pad slot", 3, preferredPadSlot(hints, occupied, "padC"));
        occupied[3] = true;
        checkInt("all pad slots taken", -1, preferredPadSlot(hints, occupied, "padD"));
        // An unidentified pad takes a free slot but never displaces a pad that is already
        // sitting in its recorded one.
        std::array<std::string, 4> named{};
        named[1] = "padA";
        const std::array<bool, 4> firstTaken = {true, true, false, false};
        checkInt("an empty GUID takes the lowest FREE slot", 2,
                 preferredPadSlot(named, firstTaken, ""));
        // A recorded pad that is not connected changes nothing.
        checkInt("an absent pad leaves its slot free for the lowest-slot rule", 1,
                 preferredPadSlot(named, keyboardOnly, "padZ"));
    }

    std::printf("\nchecks: %d, failures: %d\n", g_checks, g_failures);
    if (g_failures == 0) std::printf("USER_SETTINGS: ok\n");
    return g_failures == 0 ? 0 : 1;
}
