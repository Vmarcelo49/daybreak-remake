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

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <string>
#include <system_error>
#include <vector>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

#include "update/apply_platform.h"
#include "update/crypto.h"
#include "update/package_manifest.h"
#include "update/updater.h"

namespace {

namespace fs = std::filesystem;

// Internal child modes are entry points into the same .exe, so they must never operate on
// the developer's build or install tree. The parent creates a temp-directory fixture with
// this prefix and marker; a child requires all three facts before touching any file.
constexpr const wchar_t* kFixturePrefix = L"daybreak-update-selftest-";
constexpr const char* kFixtureMarker = "selftest-fixture.marker";
constexpr const char* kFixtureMarkerText = "daybreak-update-selftest disposable fixture\n";
// A child applies with failAt(1) and dies with this code before apply can roll back.
constexpr DWORD kInterruptExitCode = 0x5A1F;
// A child must never outlive the parent's fixture cleanup.
constexpr DWORD kProbeTimeoutMs = 120000;

bool disposableFixture(const fs::path& directory, fs::path* canonical, std::string* error) {
    std::error_code code;
    const fs::path fixture = fs::weakly_canonical(directory, code);
    if (code) {
        *error = "cannot canonicalize the fixture directory: " + code.message();
        return false;
    }
    const fs::path temp = fs::weakly_canonical(fs::temp_directory_path(), code);
    if (code) {
        *error = "cannot canonicalize the system temp directory: " + code.message();
        return false;
    }
    // native() keeps the comparison in wide form: a rejected direct call must not run a
    // path through the narrow ANSI conversion just to print its name.
    const std::wstring name = fixture.filename().native();
    const std::wstring prefix(kFixturePrefix);
    if (fixture.parent_path() != temp || name.compare(0, prefix.size(), prefix) != 0) {
        *error = "child mode requires a daybreak-update-selftest-* fixture directly under "
                 "the system temp directory";
        return false;
    }
    std::ifstream marker(fixture / kFixtureMarker, std::ios::binary);
    const std::string text((std::istreambuf_iterator<char>(marker)),
                           std::istreambuf_iterator<char>());
    if (text != kFixtureMarkerText) {
        *error = "fixture marker is missing or invalid";
        return false;
    }
    if (canonical) *canonical = fixture;
    return true;
}

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

// Synthetic file bodies: the "exe" entries are just bytes for the updater to replace, never
// a binary this test launches. Only the copied selftest itself is ever a running process.
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

bool makeRoot(const fs::path& root, std::string* error) {
    std::error_code code;
    // symlink_status does not follow a preplanted junction, so an existing root is rejected
    // before a single file is written into it.
    const fs::file_status status = fs::symlink_status(root, code);
    if (!code && fs::exists(status)) {
        *error = "the fresh test root already exists";
        return false;
    }
    if (code && code != std::errc::no_such_file_or_directory) {
        *error = "cannot inspect the test root: " + code.message();
        return false;
    }
    if (!fs::create_directory(root, code)) {
        *error = "cannot create the test root" + (code ? ": " + code.message() : "");
        return false;
    }
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
    return true;
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

std::string fileContents(const fs::path& path) {
    std::ifstream input(path, std::ios::binary);
    return std::string((std::istreambuf_iterator<char>(input)),
                       std::istreambuf_iterator<char>());
}

std::string installedVersion(const fs::path& root) {
    update::PackageManifest manifest;
    std::string error;
    if (update::PackageManifest::parse(fileContents(root / update::kPackageManifestName),
                                       &manifest, &error) != update::ParseStatus::Ok) {
        return "?";
    }
    return manifest.version;
}

// Expected bytes for every file the committed update must leave in place: the new package
// files, the game data and player file that were never part of the package, and the new
// manifest as staged from the archive. Built from the test inputs, not from the tree under
// test, so a comparison here is never circular.
std::vector<std::pair<std::string, std::string>> expectedBytes(
    const std::vector<std::pair<std::string, std::string>>& files,
    const std::string& manifestText) {
    std::vector<std::pair<std::string, std::string>> expected = files;
    expected.push_back({"data/game.dat", "game data"});
    expected.push_back({"player-notes.txt", "player notes"});
    expected.push_back({update::kPackageManifestName, manifestText});
    return expected;
}

// Empty when every protected file still matches; otherwise the first path that changed.
std::string changedFile(const fs::path& root,
                        const std::vector<std::pair<std::string, std::string>>& expected) {
    for (const auto& item : expected) {
        if (fileContents(root / item.first) != item.second) return item.first;
    }
    return {};
}

// A real Windows lock on a backup the updater has already renamed aside. FILE_SHARE_DELETE
// is deliberately absent, so DeleteFileW — the call behind the updater's real removeFile —
// fails. The lock is taken by failAt(1), after operation 0 has renamed DaybreakRemake.exe
// aside: the share mode that blocks delete also blocks rename, so taking it earlier would
// break the replacement being tested. GENERIC_READ, not FILE_READ_ATTRIBUTES alone, because
// Wine only enforces the missing FILE_SHARE_DELETE when the held handle has data access.
class BackupFileLock {
public:
    BackupFileLock() = default;
    ~BackupFileLock() { release(); }
    BackupFileLock(const BackupFileLock&) = delete;
    BackupFileLock& operator=(const BackupFileLock&) = delete;
    BackupFileLock(BackupFileLock&&) = delete;
    BackupFileLock& operator=(BackupFileLock&&) = delete;

    bool grab(const fs::path& path, std::string* error) {
        if (held()) {
            *error = "backup lock is already held";
            return false;
        }
        handle_ = CreateFileW(path.c_str(), GENERIC_READ,
                              FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL, nullptr);
        if (handle_ == INVALID_HANDLE_VALUE) {
            *error = "cannot open the renamed backup for locking: error " +
                     std::to_string(GetLastError());
            return false;
        }
        return true;
    }

    void release() {
        if (!held()) return;
        CloseHandle(handle_);
        handle_ = INVALID_HANDLE_VALUE;
    }

    bool held() const { return handle_ != INVALID_HANDLE_VALUE; }

private:
    HANDLE handle_ = INVALID_HANDLE_VALUE;
};

// MayStillRun is deliberately distinct: the caller must not inspect, recover, clean the
// fixture, or start another child while a probe could still be writing into it.
enum class ProbeOutcome { Ok, Failed, MayStillRun, NotStarted };

struct ProbeResult {
    ProbeOutcome outcome = ProbeOutcome::NotStarted;
    DWORD exitCode = 0;
    std::string error;
};

ProbeResult launchProbe(const fs::path& executable, const std::wstring& arguments) {
    ProbeResult result;
    std::wstring command = L"\"" + executable.wstring() + L"\"";
    if (!arguments.empty()) command += L" " + arguments;
    STARTUPINFOW startup{};
    startup.cb = sizeof startup;
    PROCESS_INFORMATION process{};
    const fs::path workingDirectory = executable.parent_path();
    if (!CreateProcessW(executable.c_str(), command.data(), nullptr, nullptr, FALSE, 0,
                        nullptr, workingDirectory.c_str(), &startup, &process)) {
        result.error = "cannot start probe (error " + std::to_string(GetLastError()) + ")";
        return result;
    }
    result.outcome = ProbeOutcome::MayStillRun;
    CloseHandle(process.hThread);
    const DWORD wait = WaitForSingleObject(process.hProcess, kProbeTimeoutMs);
    if (wait == WAIT_OBJECT_0) {
        if (GetExitCodeProcess(process.hProcess, &result.exitCode)) {
            result.outcome = ProbeOutcome::Ok;  // caller still checks the code it returned
        } else {
            result.error = "cannot read the probe exit code (error " +
                           std::to_string(GetLastError()) + ")";
            result.outcome = ProbeOutcome::Failed;
        }
    } else if (wait == WAIT_TIMEOUT) {
        if (!TerminateProcess(process.hProcess, 1)) {
            result.error = "probe timed out and could not be terminated (error " +
                           std::to_string(GetLastError()) + ")";
        } else if (WaitForSingleObject(process.hProcess, kProbeTimeoutMs) != WAIT_OBJECT_0) {
            result.error = "probe did not exit after termination";
        } else {
            result.error = "probe timed out after " + std::to_string(kProbeTimeoutMs) +
                           " ms and was terminated";
            result.outcome = ProbeOutcome::Failed;
        }
    } else {
        result.error = "cannot wait for probe (error " + std::to_string(GetLastError()) + ")";
    }
    CloseHandle(process.hProcess);
    return result;
}

}  // namespace

int runUpdateWindowsRenameProbe() {
    fs::path self;
    std::string error;
    if (!update::platform::selfPath(&self, &error)) {
        std::fprintf(stderr, "update_selftest: cannot locate probe executable: %s\n",
                     error.c_str());
        return 1;
    }
    if (!disposableFixture(self.parent_path(), nullptr, &error)) {
        std::fprintf(stderr, "update_selftest: rename probe refused: %s\n", error.c_str());
        return 2;
    }
    fs::path aside = self;
    aside += L".old";
    if (!update::platform::renameAside(self, aside, &error)) {
        std::fprintf(stderr, "update_selftest: cannot rename running copy aside: %s\n",
                     error.c_str());
        return 1;
    }
    if (update::platform::renameIntoPlace(aside, self, &error)) return 0;

    // Do not leave even the disposable probe renamed if the primary restore fails.
    std::error_code restoreError;
    fs::rename(aside, self, restoreError);
    std::fprintf(stderr, "update_selftest: cannot rename running copy back: %s%s%s\n",
                 error.c_str(), restoreError ? "; fallback restore failed: " : "",
                 restoreError ? restoreError.message().c_str() : "");
    return 1;
}

// No path is passed on the command line: a narrow argv path could be misdecoded when Temp
// is outside the process ANSI code page. The child derives its own root from the validated
// fixture it was copied into, so it cannot be aimed at a developer's install by a caller.
int runUpdateWindowsInterruptProbe() {
    fs::path self;
    std::string error;
    if (!update::platform::selfPath(&self, &error)) {
        std::fprintf(stderr, "update_selftest: cannot locate interrupt probe: %s\n",
                     error.c_str());
        return 1;
    }
    fs::path fixture;
    if (!disposableFixture(self.parent_path(), &fixture, &error)) {
        std::fprintf(stderr, "update_selftest: interrupt probe refused: %s\n", error.c_str());
        return 2;
    }
    const fs::path root = fixture / "crash-root";
    const auto files = packageFiles();
    const std::string manifestText = manifestFor(files, "2.0.0", "DaybreakRemake.exe");
    std::vector<std::pair<std::string, std::string>> archiveFiles = files;
    archiveFiles.push_back({"package-manifest.txt", manifestText});
    const std::vector<std::uint8_t> archive = zipBytes(archiveFiles);
    if (!makeRoot(root, &error)) {
        std::fprintf(stderr, "update_selftest: interrupt probe cannot create its root: %s\n",
                     error.c_str());
        return 3;
    }
    update::ApplySettings settings = settingsFor(root, archive);
    // failAt runs after the journal is written and after operation 0 replaced the exe and
    // left its .old backup, but before apply's own rollback path can run. Dying here is a
    // real interrupted transaction, not recovery invoked after an in-process failure.
    settings.failAt = [](int operation) -> bool {
        if (operation == 1) ExitProcess(kInterruptExitCode);
        return true;
    };
    update::apply(settings);
    std::fprintf(stderr, "update_selftest: interrupt probe returned without crashing\n");
    return 4;
}

int runUpdateApplyWindowsTests(bool injectFailure) {
    std::error_code code;
    const fs::path temporary = fs::temp_directory_path();
    const auto stamp = std::chrono::steady_clock::now().time_since_epoch().count();
    fs::path base;
    bool created = false;
    for (int attempt = 0; attempt < 8; ++attempt) {
        base = temporary / ("daybreak-update-selftest-" + std::to_string(stamp) + "-" +
                            std::to_string(attempt));
        if (fs::create_directory(base, code)) {
            created = true;
            break;
        }
        if (code) break;
    }
    if (code || !created) {
        update_test::check(false, "windows: create a disposable self-test directory" +
                                      (code ? ": " + code.message() : ""));
        return update_test::report("update_apply_windows_test");
    }

    // The parent owns the fixture marker; both internal child modes refuse any other dir.
    writeFile(base / kFixtureMarker, kFixtureMarkerText);

    fs::path self;
    std::string selfError;
    const bool located = update::platform::selfPath(&self, &selfError);
    update_test::check(located, "windows: selfPath locates the running executable: " + selfError);
    fs::path probe;
    bool copied = false;
    if (located) {
        probe = base / "probe.exe";
        fs::copy_file(self, probe, fs::copy_options::overwrite_existing, code);
        copied = !code;
        update_test::check(copied, "windows: copy the executable into the disposable fixture" +
                                       (code ? ": " + code.message() : ""));
    }

    const auto files = packageFiles();
    const std::string manifestText = manifestFor(files, "2.0.0", "DaybreakRemake.exe");
    std::vector<std::pair<std::string, std::string>> archiveFiles = files;
    archiveFiles.push_back({"package-manifest.txt", manifestText});
    const std::vector<std::uint8_t> archive = zipBytes(archiveFiles);

    // Each case gets its own fresh root: reusing one would need remove_all, which could
    // follow a preplanted junction. makeRoot refuses anything that already exists.
    const auto freshRoot = [&](const char* name, fs::path* root) {
        *root = base / name;
        std::string error;
        if (makeRoot(*root, &error)) return true;
        update_test::check(false, std::string("windows: create fresh root ") + name +
                                      ": " + error);
        return false;
    };
    {
        fs::path root;
        if (freshRoot("root-good", &root)) {
            update::ApplySettings settings = settingsFor(root, archive);
            const update::ApplyResult result = update::apply(settings);
            update_test::check(result.status == update::ApplyStatus::Ok,
                               "windows: a good update applies: " + result.error);
            update_test::check(installedVersion(root) == "2.0.0",
                               "windows: the new manifest is installed");
            update_test::check(std::ifstream(root / "data/game.dat").good(),
                               "windows: the game data is untouched");
        }
    }
    {
        fs::path root;
        if (freshRoot("root-collision", &root)) {
            writeFile(root / "player-notes.txt", "different player notes");
            std::vector<std::pair<std::string, std::string>> collisionFiles = files;
            collisionFiles.push_back({"player-notes.txt", "package notes"});
            const std::string collisionManifest =
                manifestFor(collisionFiles, "2.0.0", "DaybreakRemake.exe");
            std::vector<std::pair<std::string, std::string>> colliding = collisionFiles;
            colliding.push_back({"package-manifest.txt", collisionManifest});
            const std::vector<std::uint8_t> collisionArchive = zipBytes(colliding);
            update::ApplySettings settings = settingsFor(root, collisionArchive);
            const update::ApplyResult result = update::apply(settings);
            update_test::check(result.status == update::ApplyStatus::Failed,
                               "windows: a player-file collision is refused");
            update_test::check(result.error.find("player-notes.txt") != std::string::npos,
                               "windows: the collision names the file: " + result.error);
            update_test::check(fileContents(root / "player-notes.txt") == "different player notes",
                               "windows: a refused collision leaves the player file "
                               "byte-for-byte");
        }
    }
    {
        fs::path root;
        if (freshRoot("root-rollback", &root)) {
            update::ApplySettings settings = settingsFor(root, archive);
            settings.failAt = [](int operation) { return operation != 1; };
            const update::ApplyResult result = update::apply(settings);
            update_test::check(result.status == update::ApplyStatus::Failed,
                               "windows: an injected failure fails the apply");
            update_test::check(installedVersion(root) == "1.0.0",
                               "windows: the rollback restores the old manifest");
        }
    }
    {
        // Issue #120: a real Windows lock on the already-renamed backup must defer
        // committed cleanup without losing the journal, and recovery must retry until
        // the lock is gone.
        fs::path root;
        if (freshRoot("root-cleanup-lock", &root)) {
            const fs::path backup = root / "DaybreakRemake.exe.old";
            const fs::path workspace = root / update::kWorkspaceDirectory / "2.0.0";
            BackupFileLock lock;
            std::string lockError;
            update::ApplySettings settings = settingsFor(root, archive);
            settings.failAt = [&](int operation) {
                if (operation == 1) lock.grab(backup, &lockError);
                return true;
            };
            const update::ApplyResult result = update::apply(settings);
            update_test::check(lock.held(),
                               "windows: apply's fail-point takes a real lock on the "
                               "renamed backup: " + lockError);
            if (lock.held()) {
                const auto expected = expectedBytes(files, manifestText);
                // The updater's own warning, not a probe, proves its real removeFile hit
                // the lock: it names the backup and carries the OS error.
                update_test::check(result.status == update::ApplyStatus::Ok &&
                                       result.committed,
                                   "windows: deferred cleanup still reports a committed "
                                   "update");
                update_test::check(result.cleanupWarning.find("startup retry") !=
                                           std::string::npos &&
                                       result.cleanupWarning.find(
                                           "DaybreakRemake.exe.old") != std::string::npos &&
                                       result.cleanupWarning.find("(error ") !=
                                           std::string::npos,
                                   "windows: apply warns with the backup name and the OS "
                                   "failure: " + result.cleanupWarning);
                std::string changed = changedFile(root, expected);
                update_test::check(changed.empty(),
                                   "windows: installed files, data, notes and manifest stay "
                                   "byte-identical after deferred cleanup (changed: " +
                                       changed + ")");
                update_test::expect(installedVersion(root), "2.0.0",
                                    "windows: the committed new version stays installed");
                update_test::check(fs::exists(backup),
                                   "windows: the locked backup survives the committed "
                                   "apply");
                update_test::check(fileContents(workspace / "journal")
                                           .find("state = committed") != std::string::npos,
                                   "windows: the committed journal survives the deferred "
                                   "cleanup");

                const bool first = update::recoverOnStartup(root);
                const bool second = update::recoverOnStartup(root);
                update_test::check(!first && !second,
                                   "windows: repeated startup recovery keeps the retry "
                                   "record while the file is locked");
                update_test::check(fs::exists(backup) &&
                                       fileContents(workspace / "journal")
                                               .find("state = committed") !=
                                           std::string::npos,
                                   "windows: a locked recovery preserves both backup and "
                                   "journal");
                changed = changedFile(root, expected);
                update_test::check(changed.empty(),
                                   "windows: locked recovery leaves every protected file "
                                   "byte-identical (changed: " + changed + ")");

                lock.release();
                const bool recovered = update::recoverOnStartup(root);
                const bool repeated = update::recoverOnStartup(root);
                update_test::check(recovered,
                                   "windows: recovery after release removes the leftover "
                                   "backups and workspace");
                update_test::check(!repeated,
                                   "windows: another recovery after cleanup is harmless");
                update_test::check(!fs::exists(backup) &&
                                       !fs::exists(root / "SDL3.dll.old") &&
                                       !fs::exists(root / "assets/font.otf.old") &&
                                       !fs::exists(root / update::kWorkspaceDirectory),
                                   "windows: released cleanup consumes every backup and "
                                   "the workspace");
                update_test::expect(installedVersion(root), "2.0.0",
                                    "windows: the new version stays installed after retry");
                changed = changedFile(root, expected);
                update_test::check(changed.empty(),
                                   "windows: successful retry leaves installed files, data, "
                                   "notes and manifest byte-identical (changed: " + changed +
                                       ")");
            }
        }
    }
    {
        // The child dies inside apply before rollback, so the parent sees the exact on-disk
        // state startup recovery must repair, including a genuinely modified file — the
        // synthetic exe stand-in, not a real game executable.
        const fs::path root = base / "crash-root";
        std::error_code rootCode;
        const bool absent = !fs::exists(fs::symlink_status(root, rootCode));
        update_test::check(absent, "windows: the crash root is absent before the child starts");

        ProbeResult interrupt;
        bool owned = false;
        if (!absent) {
            update_test::check(false, "windows: the crash root was already present; "
                                      "the child was not started");
        } else if (!copied) {
            update_test::check(false, "windows: no validated probe copy; the child was not started");
        } else {
            interrupt = launchProbe(probe, L"--selftest-interrupt-apply");
            if (interrupt.outcome == ProbeOutcome::MayStillRun) {
                update_test::check(false, "windows: interrupt probe may still be running: " +
                                              interrupt.error);
                // No inspection, recovery, cleanup or further child while it may still write.
                return update_test::report("update_apply_windows_test");
            }
            owned = interrupt.outcome == ProbeOutcome::Ok &&
                    interrupt.exitCode == kInterruptExitCode;
            update_test::check(owned, "windows: the interrupt probe died inside apply at "
                                      "operation 1 (exit " +
                                          std::to_string(interrupt.exitCode) + "): " +
                                          interrupt.error);
        }

        // The marker exit alone is not enough: confirm the root is the fresh directory the
        // child made, not a preplanted junction, before any read or recovery call.
        if (owned) {
            std::error_code statusCode;
            const fs::file_status status = fs::symlink_status(root, statusCode);
            const bool fresh = !statusCode && fs::is_directory(status) &&
                               !fs::is_symlink(status);
            update_test::check(fresh, "windows: the interrupted root is a fresh real directory");
            owned = fresh;
        }
        if (owned) {
            const fs::path target = root / "DaybreakRemake.exe";
            const fs::path backup = root / "DaybreakRemake.exe.old";
            update_test::check(fileContents(target) == "new exe",
                               "windows: the crash leaves the synthetic replacement on disk");
            update_test::check(fileContents(backup) == "old exe",
                               "windows: the crash leaves the synthetic backup in place");
            update_test::check(fileContents(root / "SDL3.dll") == "old dll",
                               "windows: the crash happened before the second file was replaced");
            const std::string journal =
                fileContents(root / update::kWorkspaceDirectory / "2.0.0" / "journal");
            update_test::check(journal.find("state = applying") != std::string::npos,
                               "windows: the crash leaves an applying journal");

            const bool recovered = update::recoverOnStartup(root);
            update_test::check(recovered,
                               "windows: recovery acts on the genuinely interrupted transaction");
            update_test::check(fileContents(target) == "old exe",
                               "windows: recovery restores the synthetic executable byte-for-byte");
            update_test::check(!fs::exists(backup),
                               "windows: recovery consumes the synthetic backup");
            update_test::check(installedVersion(root) == "1.0.0",
                               "windows: recovery preserves the old manifest");
            update_test::check(!fs::exists(root / update::kWorkspaceDirectory),
                               "windows: recovery removes the interrupted workspace");
        }
    }
    if (copied) {
        const ProbeResult renameResult =
            launchProbe(probe, L"--selftest-rename-running-image");
        if (renameResult.outcome == ProbeOutcome::MayStillRun) {
            update_test::check(false, "windows: rename probe may still be running: " +
                                          renameResult.error);
            return update_test::report("update_apply_windows_test");
        }
        update_test::check(renameResult.outcome == ProbeOutcome::Ok &&
                               renameResult.exitCode == 0,
                           "windows: the running disposable exe can be renamed aside and back "
                           "(exit " + std::to_string(renameResult.exitCode) +
                           "): " + renameResult.error);
    }

    fs::remove_all(base, code);
    update_test::check(!code, "windows: remove the disposable self-test directory" +
                                  (code ? ": " + code.message() : ""));
    if (injectFailure) {
        update_test::check(false, "windows: negative control injected into the last suite");
    }
    return update_test::report("update_apply_windows_test");
}

#endif  // _WIN32
