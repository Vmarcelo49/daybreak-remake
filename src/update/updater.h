#pragma once
// update/updater.h — the update engine: check, download, verify, stage, apply, roll back.
//
// Step 3 only: nothing in the game calls this yet (step 4 adds the title-screen notice and
// the settings). The keys are a parameter on purpose: the game passes release_keys.h and
// the tests pass throwaway keys, so no environment variable or file can widen the trust
// list (docs/AUTO-UPDATE.md).
#include <array>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <string>
#include <vector>

#include "update/package_manifest.h"
#include "update/update_manifest.h"
#include "update/version.h"

namespace update {

using TrustedKeys = std::vector<std::array<std::uint8_t, 32>>;

// GitHub's permanent link to the newest stable release's manifest; no API, no JSON.
inline constexpr const char* kDefaultManifestUrl =
    "https://github.com/Vmarcelo49/daybreak-remake/releases/latest/download/"
    "update-manifest.txt";
inline constexpr const char* kWorkspaceDirectory = ".daybreak-update";

enum class CheckStatus { UpToDate, Available, Skipped, ManualOnly, Failed };

struct CheckResult {
    CheckStatus status = CheckStatus::Failed;
    Version version;
    std::string notes;
    std::string archive;
    std::uint64_t size = 0;
    std::string sha256;
    std::string error;
    bool cancelled = false;
};

struct CheckSettings {
    // Empty: use kDefaultManifestUrl, with the DAYBREAK_UPDATE_URL test override. Tests
    // and the step-4 fixture set it explicitly.
    std::string manifestUrl;
    Version currentVersion;
    std::string skipVersion;  // empty = do not skip anything
    TrustedKeys keys;
    std::function<bool(std::uint64_t received, std::uint64_t total)> progress;
    std::function<bool()> cancelled;
};

CheckResult check(const CheckSettings& settings);

enum class ApplyStatus { Ok, Failed, Cancelled };

struct ApplyResult {
    ApplyStatus status = ApplyStatus::Failed;
    std::string error;
    std::string launch;
    Version version;
    bool committed = false;
};

struct ApplySettings {
    std::filesystem::path root;
    UpdateManifest manifest;  // as fetched and verified
    std::string manifestUrl;  // where the manifest came from; empty = the default
    std::function<bool(std::uint64_t received, std::uint64_t total)> progress;
    std::function<bool()> cancelled;
    // Test-only seams. The game leaves all three empty.
    std::function<bool(const UpdateArchive&, std::vector<std::uint8_t>*, std::string*)>
        fetchArchive;
    std::function<bool(std::uint64_t required)> hasSpace;
    std::function<bool(int operation)> failAt;
};

ApplyResult apply(const ApplySettings& settings);

// First thing on startup on native builds: finishes or rolls back an interrupted apply.
// Does nothing (one stat) when there is no journal or when the folder is not an installed
// package, so a normal run and a development tree are unaffected. Returns true when it
// acted, so the caller can log exactly one line.
bool recoverOnStartup(const std::filesystem::path& root);

// Starts the new build through its entry point, appending --updated-from=<old> to the
// original arguments (which exclude argv[0]). On Linux this replaces the process.
bool relaunch(const std::filesystem::path& root, const std::string& launch,
              const std::vector<std::string>& arguments, const std::string& updatedFrom,
              std::string* error);

// The install root: the directory of the running binary.
bool installRoot(std::filesystem::path* root, std::string* error);

}  // namespace update
