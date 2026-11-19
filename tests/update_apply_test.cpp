#include "update_test_suites.h"

#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "update/apply_platform.h"
#include "update/crypto.h"
#include "update/package_manifest.h"
#include "update/updater.h"

namespace {

using update_test::check;
using update_test::expect;

namespace fs = std::filesystem;

std::string readFile(const fs::path& path) {
    std::ifstream input(path, std::ios::binary);
    return std::string(std::istreambuf_iterator<char>(input),
                       std::istreambuf_iterator<char>());
}

std::string argumentValue(int argc, char** argv, const std::string& flag) {
    for (int index = 1; index < argc; ++index) {
        const std::string argument = argv[index];
        if (argument.rfind(flag, 0) == 0) return argument.substr(flag.size());
    }
    return std::string();
}

std::array<std::uint8_t, 32> keyFromHex(const std::string& hex) {
    std::array<std::uint8_t, 32> key{};
    for (std::size_t index = 0; index < key.size(); ++index) {
        if (index * 2 + 1 >= hex.size()) break;
        key[index] = static_cast<std::uint8_t>(
            std::stoi(hex.substr(index * 2, 2), nullptr, 16));
    }
    return key;
}

std::map<std::string, std::string> snapshot(const fs::path& root) {
    std::map<std::string, std::string> files;
    std::error_code code;
    for (fs::recursive_directory_iterator it(root, code), end; !code && it != end;
         it.increment(code)) {
        if (!it->is_regular_file(code) || code) continue;
        const fs::path relative = fs::relative(it->path(), root, code);
        if (code) continue;
        const std::string bytes = readFile(it->path());
        files[relative.generic_string()] =
            update::sha256Hex(bytes.data(), bytes.size());
    }
    return files;
}

void expectSameFiles(const std::map<std::string, std::string>& before,
                     const std::map<std::string, std::string>& after,
                     const std::string& what) {
    std::string difference;
    for (const auto& item : before) {
        const auto found = after.find(item.first);
        if (found == after.end()) {
            difference = item.first + " disappeared";
            break;
        }
        if (found->second != item.second) {
            difference = item.first + " changed";
            break;
        }
    }
    if (difference.empty()) {
        for (const auto& item : after) {
            if (before.count(item.first) == 0) {
                difference = item.first + " appeared";
                break;
            }
        }
    }
    check(before == after, what + " leaves every file byte-identical" +
                               (difference.empty() ? "" : " (" + difference + ")"));
}

struct Context {
    fs::path fixtures;
    fs::path temporary;
    std::string base;
    update::TrustedKeys keys;
    fs::path stub;
};

fs::path freshRoot(const Context& context, const std::string& name) {
    const fs::path root = context.temporary / ("root-" + name);
    std::error_code code;
    fs::remove_all(root, code);
    fs::create_directories(root, code);
    fs::copy(context.fixtures / "old", root,
             fs::copy_options::recursive | fs::copy_options::overwrite_existing, code);
    return root;
}

update::CheckResult runCheck(const Context& context, const std::string& scenario,
                             const std::string& current, const std::string& skip = "") {
    update::CheckSettings settings;
    settings.manifestUrl =
        context.base + "scenarios/" + scenario + "/update-manifest.txt";
    std::string error;
    update::Version::parse(current, &settings.currentVersion, &error);
    settings.skipVersion = skip;
    settings.keys = context.keys;
    return update::check(settings);
}

update::UpdateManifest loadManifest(const Context& context,
                                    const std::string& scenario) {
    update::UpdateManifest manifest;
    std::string error;
    const std::string text = readFile(context.fixtures / "scenarios" / scenario /
                                      "update-manifest.txt");
    check(update::UpdateManifest::parse(text, &manifest, &error) ==
              update::ParseStatus::Ok,
          scenario + ": the fixture manifest parses: " + error);
    return manifest;
}

update::ApplyResult runApply(const Context& context, const std::string& scenario,
                             const fs::path& root,
                             std::function<bool(int)> failAt = {},
                             std::function<bool(std::uint64_t)> hasSpace = {},
                             std::function<bool()> cancelled = {},
                             std::function<bool(std::uint64_t, std::uint64_t)> progress = {},
                             std::function<bool(const fs::path&, std::string*)>
                                 removeCommittedBackup = {}) {
    update::ApplySettings settings;
    settings.root = root;
    settings.manifest = loadManifest(context, scenario);
    settings.manifestUrl = context.base + "scenarios/" + scenario + "/update-manifest.txt";
    settings.failAt = std::move(failAt);
    settings.hasSpace = std::move(hasSpace);
    settings.cancelled = std::move(cancelled);
    settings.progress = std::move(progress);
    settings.removeCommittedBackup = std::move(removeCommittedBackup);
    return update::apply(settings);
}

std::string installedVersion(const fs::path& root) {
    update::PackageManifest manifest;
    std::string error;
    if (update::PackageManifest::parse(readFile(root / update::kPackageManifestName),
                                       &manifest, &error) != update::ParseStatus::Ok) {
        return "?";
    }
    return manifest.version;
}

void testCheck(const Context& context) {
    const update::CheckResult upToDate = runCheck(context, "uptodate", "1.0.0");
    check(upToDate.status == update::CheckStatus::UpToDate, "an equal version is up to date");

    const update::CheckResult available = runCheck(context, "good", "1.0.0");
    check(available.status == update::CheckStatus::Available, "a newer version is available");
    expect(available.version.toString(), "2.0.0", "the available version");
    check(available.size > 0 && available.sha256.size() == 64 && !available.archive.empty(),
          "the available result carries the archive facts");

    const update::CheckResult skipped = runCheck(context, "skip", "1.0.0", "2.0.0");
    check(skipped.status == update::CheckStatus::Skipped, "skip_version skips that version");

    const update::CheckResult manual = runCheck(context, "manual", "1.0.0");
    check(manual.status == update::CheckStatus::ManualOnly,
          "an unknown format is ManualOnly");
    check(manual.notes.rfind("https://", 0) == 0, "ManualOnly carries the notes URL");

    const update::CheckResult badSignature = runCheck(context, "badsig", "1.0.0");
    check(badSignature.status == update::CheckStatus::Failed, "a bad signature fails");
    check(badSignature.error.find("untrusted") != std::string::npos,
          "the failure says untrusted: " + badSignature.error);

    const update::CheckResult unknownKey = runCheck(context, "unknownkey", "1.0.0");
    check(unknownKey.status == update::CheckStatus::Failed,
          "a key that is not in the list fails");

    update::CheckSettings noKeys;
    noKeys.manifestUrl = context.base + "scenarios/good/update-manifest.txt";
    update::Version::parse("1.0.0", &noKeys.currentVersion, nullptr);
    const update::CheckResult untrusted = update::check(noKeys);
    check(untrusted.status == update::CheckStatus::Failed &&
              untrusted.error.find("no trusted release key") != std::string::npos,
          "an empty key list refuses everything");
}

void testGoodApply(const Context& context) {
    const fs::path root = freshRoot(context, "good");
    const auto before = snapshot(root);
    const update::ApplyResult result = runApply(context, "good", root);
    check(result.status == update::ApplyStatus::Ok, "a good update applies: " + result.error);
    check(result.committed, "the apply committed");
    expect(result.launch, "daybreak", "the new entry point");
    expect(installedVersion(root), "2.0.0", "the installed manifest is the new one");
    check(!fs::exists(root / "lib/libold.so"), "the old library is deleted");
    check(fs::exists(root / "lib/libnew.so"), "the new library is in place");
    expect(readFile(root / "assets/font.otf"), "new font", "a replaced file has the new bytes");
    check(!fs::exists(root / ".daybreak-update"), "the workspace is gone");
    check(!fs::exists(root / "lib/libold.so.old"), "no .old file is left behind");
    // The player's files and the game data are untouched.
    for (const char* name : {"data/game.dat", "data/x.cnv", "custom-textures/a.png",
                             "daybreak00.dat", "player-notes.txt", "settings.conf"}) {
        check(before.at(name) == snapshot(root).at(name),
              std::string(name) + " is byte-identical");
    }
    check(snapshot(root).count("data/game.dat") == 1, "the game data is still there");
}

void testRefusals(const Context& context) {
    for (const char* scenario : {"wrongsize", "wronghash", "stagedmismatch", "collision",
                                 "gamearea"}) {
        const fs::path root = freshRoot(context, scenario);
        const auto before = snapshot(root);
        const update::ApplyResult result = runApply(context, scenario, root);
        check(result.status == update::ApplyStatus::Failed,
              std::string(scenario) + " is refused");
        check(!result.error.empty(), std::string(scenario) + " says why");
        expectSameFiles(before, snapshot(root), scenario);
        check(!fs::exists(root / ".daybreak-update"),
              std::string(scenario) + " leaves no workspace");
        if (std::string(scenario) == "collision") {
            check(result.error.find("player-notes.txt") != std::string::npos,
                  "the collision names the player file: " + result.error);
        }
        if (std::string(scenario) == "gamearea") {
            check(result.error.find("game-data") != std::string::npos,
                  "the game-area refusal says why: " + result.error);
        }
    }
}

void testSpaceCancelReadOnly(const Context& context) {
    {
        const fs::path root = freshRoot(context, "nospace");
        const auto before = snapshot(root);
        const update::ApplyResult result = runApply(
            context, "good", root, {}, [](std::uint64_t) { return false; });
        check(result.status == update::ApplyStatus::Failed &&
                  result.error.find("space") != std::string::npos,
              "the space hook refuses the update: " + result.error);
        expectSameFiles(before, snapshot(root), "no space");
    }
    {
        const fs::path root = freshRoot(context, "cancel");
        const auto before = snapshot(root);
        const update::ApplyResult early =
            runApply(context, "good", root, {}, {}, []() { return true; });
        check(early.status == update::ApplyStatus::Cancelled, "a cancelled apply stops");
        const update::ApplyResult during = runApply(
            context, "good", root, {}, {}, {},
            [](std::uint64_t, std::uint64_t) { return false; });
        check(during.status == update::ApplyStatus::Cancelled,
              "cancelling the download stops the apply");
        expectSameFiles(before, snapshot(root), "cancel");
        check(!fs::exists(root / ".daybreak-update"), "cancel leaves no workspace");
    }
    {
        const fs::path root = freshRoot(context, "readonly");
        const auto before = snapshot(root);
        fs::permissions(root, fs::perms::none, fs::perm_options::replace);
        const update::ApplyResult result = runApply(context, "good", root);
        fs::permissions(root, fs::perms::owner_all, fs::perm_options::replace);
        check(result.status == update::ApplyStatus::Failed, "a read-only root fails");
        expectSameFiles(before, snapshot(root), "read-only");
    }
}

void testLayout(const Context& context) {
    {
        const fs::path root = freshRoot(context, "layout");
        const update::ApplyResult result = runApply(context, "layout", root);
        check(result.status == update::ApplyStatus::Ok, "a layout change applies: " + result.error);
        check(!fs::exists(root / "lib/libold.so"), "the old library is deleted");
        check(!fs::exists(root / "daybreak"), "the old entry point is deleted");
        check(fs::exists(root / "bin/daybreak"), "the new entry point is in place");
        expect(installedVersion(root), "3.0.0", "the layout release is installed");
    }
    {
        // Without an old manifest nothing may be deleted.
        const fs::path root = freshRoot(context, "oldmissing");
        fs::remove(root / update::kPackageManifestName);
        const update::ApplyResult result = runApply(context, "layout", root);
        check(result.status == update::ApplyStatus::Ok,
              "a missing old manifest still adds and replaces: " + result.error);
        check(fs::exists(root / "lib/libold.so"),
              "a missing old manifest deletes nothing");
        check(fs::exists(root / "bin/daybreak"), "the new entry point is added");
        expect(installedVersion(root), "3.0.0", "the new manifest is installed");
    }
}

int operationCount(const Context& context) {
    const fs::path root = freshRoot(context, "count");
    int operations = 0;
    const update::ApplyResult result =
        runApply(context, "good", root, [&operations](int operation) {
            operations = std::max(operations, operation + 1);
            return true;
        });
    check(result.status == update::ApplyStatus::Ok, "the counting apply succeeds");
    return operations;
}

void testFaultInjection(const Context& context, int operations) {
    check(operations > 0, "the apply has operations to fail");
    for (int failAt = 0; failAt < operations; ++failAt) {
        const fs::path root = freshRoot(context, "fault");
        const auto before = snapshot(root);
        const update::ApplyResult result =
            runApply(context, "good", root, [failAt](int operation) {
                return operation != failAt;
            });
        const std::string what = "a failure at operation " + std::to_string(failAt);
        check(result.status == update::ApplyStatus::Failed, what + " fails the apply");
        expectSameFiles(before, snapshot(root), what);
        check(!fs::exists(root / ".daybreak-update"), what + " leaves no workspace");
    }
}

void testCommittedCleanupRetry(const Context& context) {
    const fs::path root = freshRoot(context, "cleanup-retry");
    const fs::path aside = root / update::kWorkspaceDirectory / "2.0.0" /
                           update::kBackupDirectory / "assets/font.otf";
    bool failedInApply = false;
    const update::ApplyResult result = runApply(
        context, "good", root, {}, {}, {}, {},
        [&failedInApply, &aside](const fs::path& path, std::string* error) {
            if (path == aside) {
                failedInApply = true;
                if (error != nullptr) *error = "deterministic simulated lock";
                return false;
            }
            return update::platform::removeFile(path, error);
        });
    check(failedInApply, "apply reaches committed cleanup and fails backup deletion");
    check(result.status == update::ApplyStatus::Ok && result.committed,
          "deferred cleanup does not turn the committed update into failure");
    check(result.cleanupWarning.find("startup retry") != std::string::npos &&
              result.cleanupWarning.find("simulated lock") != std::string::npos,
          "successful apply reports a useful deferred-cleanup warning");
    expect(installedVersion(root), "2.0.0", "the committed new version remains installed");
    check(fs::exists(aside), "failed committed cleanup leaves the old file for retry");
    const fs::path workspace = root / ".daybreak-update" / "2.0.0";
    const std::string journal = readFile(workspace / "journal");
    check(journal.find("state = committed") != std::string::npos,
          "apply preserves the committed journal when cleanup fails");

#ifndef _WIN32
    // Root can unlink through mode-restricted directories, so the runner must use an
    // unprivileged user for this real filesystem failure case.
    if (geteuid() == 0) {
        check(false, "persistent recovery failure test requires a non-root user");
        return;
    }
    const fs::path backupDirectory = aside.parent_path();
    const fs::perms originalPermissions = fs::status(backupDirectory).permissions();
    std::error_code permissionError;
    fs::permissions(backupDirectory, fs::perms::none, fs::perm_options::replace,
                    permissionError);
    if (permissionError) {
        check(false, "test setup makes the backup directory unwritable: " +
                         permissionError.message());
        return;
    }
    const bool firstRecovery = update::recoverOnStartup(root);
    const bool secondRecovery = update::recoverOnStartup(root);
    fs::permissions(backupDirectory, originalPermissions, fs::perm_options::replace,
                    permissionError);
    if (permissionError) {
        check(false, "test setup restores backup directory permissions: " +
                         permissionError.message());
        return;
    }
    check(!firstRecovery && !secondRecovery,
          "persistent cleanup failure is retained on repeated startup recovery");
    check(fs::exists(aside) && fs::exists(workspace / "journal"),
          "persistent recovery failure keeps the backup and journal");
    expect(installedVersion(root), "2.0.0", "recovery failure never rolls back the new version");
#else
    check(false, "persistent recovery failure test is POSIX-only");
    return;
#endif

    const bool recovered = update::recoverOnStartup(root);
    const bool repeated = update::recoverOnStartup(root);
    check(recovered, "recovery removes the backup after the simulated lock is released");
    check(!repeated, "a second recovery after cleanup is harmless");
    check(!fs::exists(aside) && !fs::exists(root / ".daybreak-update"),
          "successful retry removes the backup and workspace");
    expect(installedVersion(root), "2.0.0", "successful cleanup preserves the new version");
}

// Issue #119: a literal <target>.old beside a package file is not ours unless a legacy
// format-1 journal says so. Format 2 must leave it alone on success and on every failure.
void testLegacyOrphans(const Context& context, int operations) {
    const auto plant = [](const fs::path& root) {
        for (const char* name : {"assets/font.otf.old", "lib/libold.so.old",
                                 "README.txt.old", "package-manifest.txt.old"}) {
            std::ofstream(root / name, std::ios::binary) << "legacy orphan " << name;
        }
    };
    {
        const fs::path root = freshRoot(context, "orphan-good");
        plant(root);
        const auto before = snapshot(root);
        const update::ApplyResult result = runApply(context, "good", root);
        check(result.status == update::ApplyStatus::Ok,
              "a legacy .old orphan does not block an update: " + result.error);
        const auto after = snapshot(root);
        for (const auto& item : before) {
            if (item.first.find(".old") == std::string::npos) continue;
            check(after.count(item.first) != 0 && after.at(item.first) == item.second,
                  "a successful apply leaves " + item.first + " byte-identical");
        }
    }
    for (int failAt = 0; failAt < operations; ++failAt) {
        const fs::path root = freshRoot(context, "orphan-fault");
        plant(root);
        const auto before = snapshot(root);
        const update::ApplyResult result = runApply(
            context, "good", root, [failAt](int operation) { return operation != failAt; });
        check(result.status == update::ApplyStatus::Failed,
              "an injected failure beside legacy orphans fails at " +
                  std::to_string(failAt));
        expectSameFiles(before, snapshot(root),
                        "rollback at " + std::to_string(failAt) + " beside legacy orphans");
    }
    for (int crashAt = 0; crashAt < operations; ++crashAt) {
        const fs::path root = freshRoot(context, "orphan-crash");
        plant(root);
        const auto before = snapshot(root);
        const pid_t child = fork();
        if (child == 0) {
            runApply(context, "good", root, [crashAt](int operation) {
                if (operation == crashAt) _exit(99);
                return true;
            });
            _exit(0);
        }
        int status = 0;
        waitpid(child, &status, 0);
        check(WIFEXITED(status) && WEXITSTATUS(status) == 99,
              "the orphan child crashed at operation " + std::to_string(crashAt));
        update::recoverOnStartup(root);
        expectSameFiles(before, snapshot(root),
                        "recovery at " + std::to_string(crashAt) +
                            " beside legacy orphans");
    }
}

void testBackupCollision(const Context& context) {
    const fs::path root = freshRoot(context, "backup-collision");
    const fs::path backup = root / update::kWorkspaceDirectory / "2.0.0" /
                            update::kBackupDirectory / "assets/font.otf";
    fs::create_directories(backup.parent_path());
    std::ofstream(backup, std::ios::binary) << "pre-existing backup";
    const auto before = snapshot(root);
    const update::ApplyResult result = runApply(context, "good", root);
    check(result.status == update::ApplyStatus::Failed,
          "an occupied backup path refuses the apply: " + result.error);
    check(result.error.find("backup path already exists") != std::string::npos &&
              result.error.find("assets/font.otf") != std::string::npos,
          "the refusal names the backup and its target: " + result.error);
    expectSameFiles(before, snapshot(root), "a refused backup collision");
    check(fs::exists(backup), "the pre-existing backup-path file survives the refusal");
    expect(installedVersion(root), "1.0.0", "the old manifest survives the refusal");
}

#ifndef _WIN32
void testBackupSymlinkCollision(const Context& context) {
    const fs::path root = freshRoot(context, "backup-symlink");
    const fs::path backup = root / update::kWorkspaceDirectory / "2.0.0" /
                            update::kBackupDirectory / "assets/font.otf";
    fs::create_directories(backup.parent_path());
    fs::create_symlink(root / "nowhere", backup);  // deliberately dangling
    const auto before = snapshot(root);
    const update::ApplyResult result = runApply(context, "good", root);
    check(result.status == update::ApplyStatus::Failed,
          "a no-follow check refuses a symlink at a backup path: " + result.error);
    check(fs::is_symlink(fs::symlink_status(backup)),
          "the planted dangling symlink is not replaced");
    expectSameFiles(before, snapshot(root), "a symlink backup collision");
}
#endif

void testPendingJournal(const Context& context) {
    const fs::path root = freshRoot(context, "pending");
    const fs::path workspace = root / update::kWorkspaceDirectory / "2.0.0";
    fs::create_directories(workspace);
    const std::string journal = "format = 1\nstate = applying\nversion = 2.0.0\nmanifest = " +
                                std::string(64, 'a') + "\n[operations]\n";
    std::ofstream(workspace / "journal") << journal;
    const auto before = snapshot(root);
    const update::ApplyResult result = runApply(context, "good", root);
    check(result.status == update::ApplyStatus::Failed &&
              result.error.find("earlier update is still pending") != std::string::npos,
          "a pending journal refuses a new apply: " + result.error);
    expectSameFiles(before, snapshot(root), "a refused pending journal");
    check(fs::exists(workspace / "journal"), "the pending journal is kept for recovery");
}

std::string journalFor(const std::string& format, const std::string& state,
                       const std::string& manifestHash) {
    return "format = " + format + "\nstate = " + state +
           "\nversion = 2.0.0\nmanifest = " + manifestHash + "\n";
}

void testJournalRecovery(const Context& context) {
    {
        // A journal an older release could leave behind still rolls its .old file back.
        const fs::path root = freshRoot(context, "journal-v1");
        const fs::path workspace = root / update::kWorkspaceDirectory / "2.0.0";
        fs::create_directories(workspace);
        std::ofstream(root / "foo.txt") << "new contents\n";
        std::ofstream(root / "foo.txt.old") << "old contents\n";
        std::ofstream(workspace / "journal")
            << journalFor("1", "applying", std::string(64, 'a')) +
                   "[operations]\nreplace foo.txt\n";
        check(update::recoverOnStartup(root), "a legacy applying journal is recovered");
        expect(readFile(root / "foo.txt"), "old contents\n",
               "legacy recovery restores the .old file");
        check(!fs::exists(root / "foo.txt.old"), "legacy recovery consumes its own backup");
        check(!fs::exists(root / update::kWorkspaceDirectory),
              "legacy recovery removes the workspace");
    }
    {
        // Format 2 consumes only the backup it names; a legacy orphan at the same target
        // stays a user file even though the journal mentions that target.
        const fs::path root = freshRoot(context, "journal-v2");
        const fs::path workspace = root / update::kWorkspaceDirectory / "2.0.0";
        const fs::path backupDir = workspace / update::kBackupDirectory;
        fs::create_directories(backupDir);
        std::ofstream(backupDir / "foo.txt") << "old contents\n";
        std::ofstream(root / "foo.txt") << "new contents\n";
        std::ofstream(root / "foo.txt.old") << "user orphan\n";
        std::ofstream(workspace / "journal")
            << journalFor("2", "applying", std::string(64, 'a')) +
                   "[backups]\nbackup/foo.txt\tfoo.txt\n[operations]\nreplace foo.txt\n";
        check(update::recoverOnStartup(root), "a format-2 applying journal is recovered");
        expect(readFile(root / "foo.txt"), "old contents\n",
               "format-2 recovery restores only its recorded backup");
        expect(readFile(root / "foo.txt.old"), "user orphan\n",
               "format-2 recovery never adopts a legacy orphan");
        check(!fs::exists(root / update::kWorkspaceDirectory),
              "format-2 recovery removes the workspace");
    }
    {
        // Committed cleanup removes the recorded backup but leaves an orphan untouched.
        const fs::path root = freshRoot(context, "journal-v2-committed");
        const fs::path workspace = root / update::kWorkspaceDirectory / "2.0.0";
        const fs::path backupDir = workspace / update::kBackupDirectory;
        fs::create_directories(backupDir);
        std::ofstream(backupDir / "foo.txt") << "old contents\n";
        std::ofstream(root / "foo.txt") << "new contents\n";
        std::ofstream(root / "foo.txt.old") << "user orphan\n";
        std::ofstream(workspace / "journal")
            << journalFor("2", "committed", std::string(64, 'a')) +
                   "[backups]\nbackup/foo.txt\tfoo.txt\n[operations]\nreplace foo.txt\n";
        check(update::recoverOnStartup(root), "a format-2 committed journal is cleaned");
        expect(readFile(root / "foo.txt"), "new contents\n",
               "committed recovery keeps the installed version");
        check(!fs::exists(backupDir / "foo.txt"), "committed recovery consumes its backup");
        expect(readFile(root / "foo.txt.old"), "user orphan\n",
               "committed recovery leaves the legacy orphan alone");
    }
    {
        // A journal whose backup escapes the workspace is not attributable to it.
        const fs::path root = freshRoot(context, "journal-v2-bad");
        const fs::path workspace = root / update::kWorkspaceDirectory / "2.0.0";
        fs::create_directories(workspace);
        std::ofstream(workspace / "journal")
            << journalFor("2", "committed", std::string(64, 'a')) +
                   "[backups]\n../../outside\tfoo.txt\n[operations]\nreplace foo.txt\n";
        const auto before = snapshot(root);
        check(!update::recoverOnStartup(root), "a malformed backup mapping is refused");
        expectSameFiles(before, snapshot(root), "a malformed journal changes nothing");
        check(fs::exists(workspace / "journal"), "the malformed journal is left for inspection");
    }
}

void testCrashRecovery(const Context& context, int operations) {
    for (int crashAt = 0; crashAt < operations; ++crashAt) {
        const fs::path root = freshRoot(context, "crash");
        const auto before = snapshot(root);
        const pid_t child = fork();
        if (child == 0) {
            runApply(context, "good", root, [crashAt](int operation) {
                if (operation == crashAt) _exit(99);
                return true;
            });
            _exit(0);
        }
        int status = 0;
        waitpid(child, &status, 0);
        check(WIFEXITED(status) && WEXITSTATUS(status) == 99,
              "the child crashed at operation " + std::to_string(crashAt));
        update::recoverOnStartup(root);
        expectSameFiles(before, snapshot(root),
                        "recovery after a crash at operation " +
                            std::to_string(crashAt));
        check(!fs::exists(root / ".daybreak-update"),
              "recovery removes the workspace");
    }
    {
        // A committed journal cleans up without touching the installed version.
        const fs::path root = freshRoot(context, "committed");
        const update::ApplyResult result = runApply(context, "good", root);
        check(result.status == update::ApplyStatus::Ok, "the committed fixture applies");
        const fs::path workspace = root / ".daybreak-update" / "2.0.0";
        fs::create_directories(workspace);
        const std::string manifestText = readFile(root / update::kPackageManifestName);
        const std::string journal =
            "format = 1\nstate = committed\nversion = 2.0.0\nmanifest = " +
            update::sha256Hex(manifestText.data(), manifestText.size()) +
            "\n[operations]\nreplace daybreak-bin\n";
        std::ofstream(workspace / "journal") << journal;
        std::ofstream(root / "daybreak-bin.old") << "stale";
        update::recoverOnStartup(root);
        check(!fs::exists(root / "daybreak-bin.old"), "committed recovery deletes .old");
        check(!fs::exists(root / ".daybreak-update"),
              "committed recovery removes the workspace");
        expect(installedVersion(root), "2.0.0", "committed recovery keeps the new version");
    }
}

void testEndToEnd(const Context& context, const std::string& keyHex) {
    const fs::path root = freshRoot(context, "endtoend");
    const std::string command =
        "\"" + (root / "daybreak").string() + "\" --root=\"" + root.string() +
        "\" --manifest=\"" + context.base + "scenarios/good/update-manifest.txt" +
        "\" --key=" + keyHex + " --current=1.0.0";
    std::FILE* pipe = popen(command.c_str(), "r");
    check(pipe != nullptr, "the stub starts");
    if (pipe == nullptr) return;
    std::string output;
    char buffer[512];
    while (std::fgets(buffer, sizeof buffer, pipe) != nullptr) output += buffer;
    const int status = pclose(pipe);
    check(WIFEXITED(status) && WEXITSTATUS(status) == 0,
          "the stub exits cleanly: " + output);
    check(output.find("updated-from 1.0.0") != std::string::npos,
          "the relaunched build reports --updated-from: " + output);
    check(output.find("version 2.0.0") != std::string::npos,
          "the relaunched build is the new version: " + output);
    expect(installedVersion(root), "2.0.0", "the end-to-end install is updated");
    check(fs::exists(root / "lib/libnew.so"), "the end-to-end package is in place");
}

}  // namespace

int main(int argc, char** argv) {
    // The loopback fixture is the one plain-HTTP exception (docs/AUTO-UPDATE.md); the
    // stub this test relaunches inherits the switch.
    setenv("DAYBREAK_UPDATE_TEST_HTTP", "1", 1);
    Context context;
    context.fixtures = argumentValue(argc, argv, "--fixtures=");
    context.base = argumentValue(argc, argv, "--base=");
    const std::string keyHex = argumentValue(argc, argv, "--key=");
    context.stub = argumentValue(argc, argv, "--stub=");
    if (context.fixtures.empty() || context.base.empty() || keyHex.empty()) {
        std::fprintf(stderr, "usage: update_apply_test --fixtures= --base= --key= --stub=\n");
        return 2;
    }
    context.keys.push_back(keyFromHex(keyHex));
    context.temporary = fs::temp_directory_path() / "daybreak-update-apply-test";
    std::error_code code;
    fs::remove_all(context.temporary, code);
    fs::create_directories(context.temporary, code);

    testCheck(context);
    testGoodApply(context);
    testRefusals(context);
    testSpaceCancelReadOnly(context);
    testLayout(context);
    const int operations = operationCount(context);
    testFaultInjection(context, operations);
    testCommittedCleanupRetry(context);
    testLegacyOrphans(context, operations);
    testBackupCollision(context);
#ifndef _WIN32
    testBackupSymlinkCollision(context);
#endif
    testPendingJournal(context);
    testJournalRecovery(context);
    testCrashRecovery(context, operations);
    testEndToEnd(context, keyHex);

    fs::remove_all(context.temporary, code);
    return update_test::report("update_apply_test");
}
