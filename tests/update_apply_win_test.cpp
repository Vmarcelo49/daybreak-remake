// tests/update_apply_win_test.cpp — the step-3 apply cases that only a real Windows run can
// prove, compiled into update_selftest.exe (issue #100).
//
// CTest never runs the MinGW build, so the same engine is exercised here with the archive
// handed in through ApplySettings::fetchArchive (no HTTP, no fixture server): a successful
// apply, the collision refusal, a rollback from an injected failure, startup recovery, and
// the Windows-specific fact this whole design rests on — a running .exe can be renamed
// aside and renamed back.
#include "update_test_suites.h"

#ifdef _WIN32

#include <cstdint>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "update/apply_platform.h"
#include "update/crypto.h"
#include "update/package_manifest.h"
#include "update/updater.h"

namespace {

namespace fs = std::filesystem;

std::uint32_t crc32Of(const std::vector<std::uint8_t>& data) {
    std::uint32_t crc = 0xFFFFFFFFu;
    for (const std::uint8_t byte : data) {
        crc ^= byte;
        for (int bit = 0; bit < 8; ++bit) {
            crc = (crc >> 1) ^ (0xEDB88320u & (0u - (crc & 1u)));
        }
    }
    return ~crc;
}

void appendLe(std::vector<std::uint8_t>* out, std::uint32_t value, int bytes) {
    for (int index = 0; index < bytes; ++index) {
        out->push_back(static_cast<std::uint8_t>(value >> (8 * index)));
    }
}

// A zip of stored entries, enough for the reader the updater uses on Windows.
std::vector<std::uint8_t> zipBytes(
    const std::vector<std::pair<std::string, std::string>>& files) {
    std::vector<std::uint8_t> local;
    std::vector<std::uint8_t> central;
    for (const auto& file : files) {
        const std::uint32_t offset = static_cast<std::uint32_t>(local.size());
        const std::uint32_t size = static_cast<std::uint32_t>(file.second.size());
        const std::uint32_t crc = crc32Of(std::vector<std::uint8_t>(
            file.second.begin(), file.second.end()));
        appendLe(&local, 0x04034B50u, 4);
        appendLe(&local, 20, 2);
        appendLe(&local, 0, 2);
        appendLe(&local, 0, 2);  // stored
        appendLe(&local, 0, 2);
        appendLe(&local, 0, 2);
        appendLe(&local, crc, 4);
        appendLe(&local, size, 4);
        appendLe(&local, size, 4);
        appendLe(&local, static_cast<std::uint32_t>(file.first.size()), 2);
        appendLe(&local, 0, 2);
        local.insert(local.end(), file.first.begin(), file.first.end());
        local.insert(local.end(), file.second.begin(), file.second.end());

        appendLe(&central, 0x02014B50u, 4);
        appendLe(&central, 20, 2);
        appendLe(&central, 20, 2);
        appendLe(&central, 0, 2);
        appendLe(&central, 0, 2);
        appendLe(&central, 0, 2);
        appendLe(&central, 0, 2);
        appendLe(&central, crc, 4);
        appendLe(&central, size, 4);
        appendLe(&central, size, 4);
        appendLe(&central, static_cast<std::uint32_t>(file.first.size()), 2);
        appendLe(&central, 0, 2);
        appendLe(&central, 0, 2);
        appendLe(&central, 0, 2);
        appendLe(&central, 0, 2);
        appendLe(&central, 0100644u << 16, 4);
        appendLe(&central, offset, 4);
        central.insert(central.end(), file.first.begin(), file.first.end());
    }
    std::vector<std::uint8_t> out = local;
    const std::uint32_t centralOffset = static_cast<std::uint32_t>(out.size());
    out.insert(out.end(), central.begin(), central.end());
    appendLe(&out, 0x06054B50u, 4);
    appendLe(&out, 0, 2);
    appendLe(&out, 0, 2);
    appendLe(&out, static_cast<std::uint32_t>(files.size()), 2);
    appendLe(&out, static_cast<std::uint32_t>(files.size()), 2);
    appendLe(&out, static_cast<std::uint32_t>(central.size()), 4);
    appendLe(&out, centralOffset, 4);
    appendLe(&out, 0, 2);
    return out;
}

std::string manifestFor(const std::vector<std::pair<std::string, std::string>>& files,
                        const std::string& version, const std::string& launch) {
    std::string text = "format = 1\nversion = " + version +
                       "\ntarget = windows-x86_64\nlaunch = " + launch + "\n[files]\n";
    for (const auto& file : files) {
        const std::string hash = update::sha256Hex(file.second.data(), file.second.size());
        text += hash + "  " + std::to_string(file.second.size()) + "  -  " + file.first +
                "\n";
    }
    return text;
}

std::vector<std::pair<std::string, std::string>> packageFiles() {
    return {
        {"DaybreakRemake.exe", "new exe"},
        {"SDL3.dll", "new dll"},
        {"assets/font.otf", "new font"},
    };
}

void writeFile(const fs::path& path, const std::string& text) {
    fs::create_directories(path.parent_path());
    std::ofstream(path, std::ios::binary) << text;
}

fs::path makeRoot(const fs::path& base) {
    const fs::path root = base / "root";
    std::error_code code;
    fs::remove_all(root, code);
    writeFile(root / "DaybreakRemake.exe", "old exe");
    writeFile(root / "SDL3.dll", "old dll");
    writeFile(root / "assets/font.otf", "old font");
    writeFile(root / "data/game.dat", "game data");
    writeFile(root / "player-notes.txt", "player notes");
    const std::vector<std::pair<std::string, std::string>> old = {
        {"DaybreakRemake.exe", "old exe"},
        {"SDL3.dll", "old dll"},
        {"assets/font.otf", "old font"},
    };
    writeFile(root / "package-manifest.txt",
              manifestFor(old, "1.0.0", "DaybreakRemake.exe"));
    return root;
}

update::ApplySettings settingsFor(const fs::path& root,
                                  const std::vector<std::uint8_t>& archive) {
    update::ApplySettings settings;
    settings.root = root;
    settings.manifest.format = 1;
    settings.manifest.version.major = 2;
    settings.manifest.notes = "https://example.invalid/";
    settings.manifest.windowsArchive.archive = "daybreak-2.0.0-abc1234-windows-x86_64.zip";
    settings.manifest.windowsArchive.size = archive.size();
    settings.manifest.windowsArchive.sha256 =
        update::sha256Hex(archive.data(), archive.size());
    settings.fetchArchive = [archive](const update::UpdateArchive&, std::vector<std::uint8_t>* out,
                                      std::string*) {
        *out = archive;
        return true;
    };
    settings.hasSpace = [](std::uint64_t) { return true; };
    return settings;
}

std::string installedVersion(const fs::path& root) {
    update::PackageManifest manifest;
    std::string error;
    std::ifstream input(root / update::kPackageManifestName, std::ios::binary);
    std::string text((std::istreambuf_iterator<char>(input)),
                     std::istreambuf_iterator<char>());
    if (update::PackageManifest::parse(text, &manifest, &error) != update::ParseStatus::Ok) {
        return "?";
    }
    return manifest.version;
}

}  // namespace

int runUpdateApplyWindowsTests() {
    const fs::path base = fs::temp_directory_path() / "daybreak-update-selftest";
    std::error_code code;
    fs::remove_all(base, code);
    fs::create_directories(base, code);

    const auto files = packageFiles();
    const std::string manifestText = manifestFor(files, "2.0.0", "DaybreakRemake.exe");
    std::vector<std::pair<std::string, std::string>> archiveFiles = files;
    archiveFiles.push_back({"package-manifest.txt", manifestText});
    const std::vector<std::uint8_t> archive = zipBytes(archiveFiles);

    {
        const fs::path root = makeRoot(base);
        update::ApplySettings settings = settingsFor(root, archive);
        const update::ApplyResult result = update::apply(settings);
        update_test::check(result.status == update::ApplyStatus::Ok,
                           "windows: a good update applies: " + result.error);
        update_test::check(installedVersion(root) == "2.0.0",
                           "windows: the new manifest is installed");
        update_test::check(std::ifstream(root / "data/game.dat").good(),
                           "windows: the game data is untouched");
    }
    {
        const fs::path root = makeRoot(base);
        writeFile(root / "player-notes.txt", "different player notes");
        std::vector<std::pair<std::string, std::string>> colliding = archiveFiles;
        colliding.push_back({"player-notes.txt", "package notes"});
        const std::vector<std::uint8_t> collisionArchive = zipBytes(colliding);
        update::ApplySettings settings = settingsFor(root, collisionArchive);
        const update::ApplyResult result = update::apply(settings);
        update_test::check(result.status == update::ApplyStatus::Failed,
                           "windows: a player-file collision is refused");
        update_test::check(result.error.find("player-notes.txt") != std::string::npos,
                           "windows: the collision names the file");
    }
    {
        const fs::path root = makeRoot(base);
        update::ApplySettings settings = settingsFor(root, archive);
        settings.failAt = [](int operation) { return operation != 1; };
        const update::ApplyResult result = update::apply(settings);
        update_test::check(result.status == update::ApplyStatus::Failed,
                           "windows: an injected failure fails the apply");
        update_test::check(installedVersion(root) == "1.0.0",
                           "windows: the rollback restores the old manifest");
    }
    {
        const fs::path root = makeRoot(base);
        update::ApplySettings settings = settingsFor(root, archive);
        settings.failAt = [](int) { return false; };
        update::apply(settings);
        update::recoverOnStartup(root);
        update_test::check(installedVersion(root) == "1.0.0",
                           "windows: recovery restores the old manifest");
        update_test::check(!fs::exists(root / update::kWorkspaceDirectory),
                           "windows: recovery removes the workspace");
    }
    {
        // The design's Windows premise: the running .exe can be renamed aside and back.
        fs::path self;
        std::string error;
        update_test::check(update::installRoot(&self, &error),
                           "windows: installRoot finds the running binary: " + error);
        fs::path aside = self;
        aside += ".old";
        update_test::check(update::platform::renameAside(self, aside, &error),
                           "windows: a running exe can be renamed aside: " + error);
        update_test::check(update::platform::renameIntoPlace(aside, self, &error),
                           "windows: and renamed back: " + error);
    }

    fs::remove_all(base, code);
    return 0;
}

#endif  // _WIN32
