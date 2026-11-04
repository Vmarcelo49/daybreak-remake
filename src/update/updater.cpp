#include "update/updater.h"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <system_error>
#include <vector>

#include "platform/http.h"
#include "update/apply_platform.h"
#include "update/archive.h"
#include "update/crypto.h"
#include "update/manifest_text.h"
#include "update/paths.h"

namespace update {
namespace {

constexpr std::uint64_t kMaxManifestBytes = 64 * 1024;
constexpr std::uint64_t kMaxSignatureBytes = 1024;

bool fail(std::string* error, const std::string& message) {
    if (error != nullptr) *error = message;
    return false;
}

const char* platformTarget() {
#ifdef _WIN32
    return "windows-x86_64";
#else
    return "linux-x86_64";
#endif
}

const UpdateArchive& platformArchive(const UpdateManifest& manifest) {
#ifdef _WIN32
    return manifest.windowsArchive;
#else
    return manifest.linuxArchive;
#endif
}

bool readFile(const std::filesystem::path& path, std::string* out) {
    std::ifstream input(path, std::ios::binary);
    if (!input) return false;
    out->assign(std::istreambuf_iterator<char>(input), std::istreambuf_iterator<char>());
    return true;
}

std::string directoryOf(const std::string& url) {
    const std::size_t slash = url.rfind('/');
    return slash == std::string::npos ? url : url.substr(0, slash + 1);
}

std::string joinUrl(const std::string& base, const std::string& name) {
    if (!base.empty() && base.back() == '/') return base + name;
    return base + "/" + name;
}

// GitHub keeps the newest release's manifest under releases/latest/download/ and the
// archives under releases/download/v<version>/. Any other base (the CTest fixture) keeps
// the archive beside the manifest.
std::string archiveUrlFor(const std::string& manifestUrl, const Version& version,
                          const std::string& archive) {
    static const std::string kLatest = "/releases/latest/download/";
    const std::size_t at = manifestUrl.find(kLatest);
    if (at != std::string::npos) {
        return manifestUrl.substr(0, at) + "/releases/download/v" + version.toString() +
               "/" + archive;
    }
    return joinUrl(directoryOf(manifestUrl), archive);
}

std::string notesUrlFrom(const std::string& text) {
    std::vector<std::string> lines;
    std::string ignored;
    if (!manifest_text::splitLines(text, &lines, &ignored)) return std::string();
    for (const std::string& line : lines) {
        std::string value;
        if (manifest_text::headerValue(line, "notes", &value)) return value;
    }
    return std::string();
}

bool fetchText(const std::string& url, std::uint64_t cap, std::string* out,
               std::string* error, bool* cancelled) {
    out->clear();
    plat::HttpRequest request;
    request.url = url;
    request.maxBytes = cap;
    const plat::HttpResult result = plat::httpGet(
        request,
        [out](const std::uint8_t* data, std::size_t size) {
            out->append(reinterpret_cast<const char*>(data), size);
            return true;
        },
        nullptr);
    if (result.error == plat::HttpError::Cancelled) {
        if (cancelled != nullptr) *cancelled = true;
        *error = "cancelled";
        return false;
    }
    if (result.error != plat::HttpError::None) {
        *error = result.message;
        return false;
    }
    return true;
}

// DAYBREAK_UPDATE_URL may point the check at the CTest fixture, and only there: it needs
// the test-only HTTP switch and a loopback host. A release build has no way to reach it.
bool manifestUrlFor(const std::string& overrideUrl, std::string* url, std::string* error) {
    if (overrideUrl.empty()) {
        *url = kDefaultManifestUrl;
        return true;
    }
    if (!plat::testHttpAllowed()) {
        return fail(error,
                    "DAYBREAK_UPDATE_URL is only honoured together with "
                    "DAYBREAK_UPDATE_TEST_HTTP=1");
    }
    if (!plat::testLoopbackUrl(overrideUrl)) {
        return fail(error, "DAYBREAK_UPDATE_URL must be a loopback http URL");
    }
    *url = joinUrl(overrideUrl, "update-manifest.txt");
    return true;
}

std::string resolvedManifestUrl() {
    const char* overrideUrl = std::getenv("DAYBREAK_UPDATE_URL");
    std::string url;
    if (!manifestUrlFor(overrideUrl != nullptr ? overrideUrl : "", &url, nullptr)) {
        return kDefaultManifestUrl;
    }
    return url;
}

// --- journal ------------------------------------------------------------------------

enum class OperationKind { Add, Replace, Delete };

struct Operation {
    OperationKind kind = OperationKind::Add;
    std::string path;
};

const char* operationName(OperationKind kind) {
    switch (kind) {
        case OperationKind::Add: return "add";
        case OperationKind::Replace: return "replace";
        case OperationKind::Delete: return "delete";
    }
    return "?";
}

std::string renderJournal(const char* state, const std::string& version,
                          const std::string& manifestSha,
                          const std::vector<Operation>& operations) {
    std::string text = "format = 1\n";
    text += "state = ";
    text += state;
    text += "\nversion = " + version + "\nmanifest = " + manifestSha +
            "\n[operations]\n";
    for (const Operation& operation : operations) {
        text += operationName(operation.kind);
        text += " " + operation.path + "\n";
    }
    return text;
}

bool parseJournal(const std::string& text, std::string* state,
                  std::string* manifestSha, std::vector<Operation>* operations,
                  std::string* error) {
    std::vector<std::string> lines;
    if (!manifest_text::splitLines(text, &lines, error)) return false;
    if (lines.size() < 5) return fail(error, "the journal is truncated");
    std::string format;
    if (!manifest_text::headerValue(lines[0], "format", &format) || format != "1") {
        return fail(error, "the journal's format is not 1");
    }
    if (!manifest_text::headerValue(lines[1], "state", state) ||
        (*state != "applying" && *state != "committed")) {
        return fail(error, "the journal's state is not applying or committed");
    }
    std::string version;
    if (!manifest_text::headerValue(lines[2], "version", &version)) {
        return fail(error, "the journal has no version");
    }
    if (!manifest_text::headerValue(lines[3], "manifest", manifestSha) ||
        !manifest_text::isLowerHex(*manifestSha, 64)) {
        return fail(error, "the journal has no manifest hash");
    }
    if (lines[4] != "[operations]") return fail(error, "the journal has no operations");
    for (std::size_t index = 5; index < lines.size(); ++index) {
        const std::string& line = lines[index];
        const std::size_t space = line.find(' ');
        if (space == std::string::npos) return fail(error, "malformed journal line");
        const std::string kind = line.substr(0, space);
        Operation operation;
        if (kind == "add") {
            operation.kind = OperationKind::Add;
        } else if (kind == "replace") {
            operation.kind = OperationKind::Replace;
        } else if (kind == "delete") {
            operation.kind = OperationKind::Delete;
        } else {
            return fail(error, "unknown journal operation '" + kind + "'");
        }
        operation.path = line.substr(space + 1);
        std::string pathError;
        if (!paths::validRelative(operation.path, &pathError)) {
            return fail(error, pathError);
        }
        operations->push_back(operation);
    }
    return true;
}

// --- staging ------------------------------------------------------------------------

bool hashFile(const std::filesystem::path& path, std::string* hex) {
    std::ifstream input(path, std::ios::binary);
    if (!input) return false;
    Sha256 hash;
    char buffer[1 << 16];
    while (input) {
        input.read(buffer, sizeof buffer);
        const std::streamsize count = input.gcount();
        if (count > 0) hash.update(buffer, static_cast<std::size_t>(count));
    }
    std::uint8_t digest[32];
    hash.final(digest);
    *hex = toHex(digest, sizeof digest);
    return true;
}

bool extractArchive(const std::vector<std::uint8_t>& bytes,
                    const std::filesystem::path& staged,
                    std::vector<std::string>* files, std::string* error) {
    std::unique_ptr<Archive> archive;
#ifdef _WIN32
    archive = Archive::openZip(bytes, error);
#else
    archive = Archive::openTarGz(bytes, error);
#endif
    if (archive == nullptr) return false;
    for (const ArchiveEntry& entry : archive->entries()) {
        if (entry.isDirectory) continue;
        const std::filesystem::path target =
            staged / std::filesystem::u8path(entry.path);
        if (!platform::makeDirectories(target.parent_path(), error)) return false;
        std::ofstream output(target, std::ios::binary | std::ios::trunc);
        if (!output) return fail(error, "cannot write " + target.string());
        const bool extracted = archive->extract(
            entry.path,
            [&output](const std::uint8_t* data, std::size_t size) {
                output.write(reinterpret_cast<const char*>(data),
                             static_cast<std::streamsize>(size));
                return output.good();
            },
            error);
        output.close();
        if (!extracted) return false;
        if (!platform::setExecutable(target, entry.executable, error)) return false;
        files->push_back(entry.path);
    }
    return true;
}

bool verifyStaged(const std::filesystem::path& staged, const PackageManifest& manifest,
                  std::string* error) {
    for (const PackageEntry& entry : manifest.entries) {
        const std::filesystem::path target = staged / std::filesystem::u8path(entry.path);
        if (!platform::exists(target)) {
            return fail(error, "the archive is missing " + entry.path);
        }
        if (platform::fileSize(target) != entry.size) {
            return fail(error, entry.path + " is not the size the manifest says");
        }
        std::string hex;
        if (!hashFile(target, &hex)) return fail(error, "cannot read " + entry.path);
        if (hex != entry.sha256) {
            return fail(error, entry.path + " does not match the manifest's sha256");
        }
#ifndef _WIN32
        const auto permissions = std::filesystem::status(target).permissions();
        const bool executable =
            (permissions & std::filesystem::perms::owner_exec) !=
            std::filesystem::perms::none;
        if (executable != entry.executable) {
            return fail(error, entry.path + " has the wrong executable bit");
        }
#endif
    }
    return true;
}

void removeWorkspace(const std::filesystem::path& root,
                     const std::filesystem::path& workspace) {
    std::error_code code;
    std::filesystem::remove_all(workspace, code);
    // The per-version directory is ours; the parent only disappears once it is empty.
    std::filesystem::remove(root / kWorkspaceDirectory, code);
}

// Removes the per-version workspace unless the caller kept it on purpose (a rollback that
// could not finish keeps its journal for the next start).
struct WorkspaceGuard {
    std::filesystem::path root;
    std::filesystem::path workspace;
    bool keep = false;
    ~WorkspaceGuard() {
        if (!keep) removeWorkspace(root, workspace);
    }
};

bool rollback(const std::filesystem::path& root, const std::filesystem::path& workspace,
              const std::vector<Operation>& operations, std::string* error) {
    for (auto it = operations.rbegin(); it != operations.rend(); ++it) {
        const std::filesystem::path target = root / std::filesystem::u8path(it->path);
        std::filesystem::path aside = target;
        aside += ".old";
        if (it->kind == OperationKind::Add) {
            if (!platform::removeFile(target, error)) return false;
        } else if (platform::exists(aside)) {
            if (!platform::removeFile(target, error)) return false;
            if (!platform::renameIntoPlace(aside, target, error)) return false;
        }
    }
    removeWorkspace(root, workspace);
    return true;
}

// Deletes the .old files a committed apply left behind. A failure (a locked file on
// Windows) keeps the workspace so the next start retries instead of losing the journal.
bool finishCommitted(const std::filesystem::path& root,
                     const std::filesystem::path& workspace,
                     const std::vector<Operation>& operations, std::string* error) {
    for (const Operation& operation : operations) {
        if (operation.kind == OperationKind::Add) continue;
        std::filesystem::path aside = root / std::filesystem::u8path(operation.path);
        aside += ".old";
        if (!platform::removeFile(aside, error)) return false;
    }
    removeWorkspace(root, workspace);
    return true;
}

}  // namespace

CheckResult check(const CheckSettings& settings) {
    CheckResult result;
    if (settings.keys.empty()) {
        result.error = "no trusted release key is configured";
        return result;
    }
    if (settings.cancelled && settings.cancelled()) {
        result.cancelled = true;
        result.error = "cancelled";
        return result;
    }
    std::string manifestUrl = settings.manifestUrl;
    if (manifestUrl.empty()) {
        const char* overrideUrl = std::getenv("DAYBREAK_UPDATE_URL");
        if (!manifestUrlFor(overrideUrl != nullptr ? overrideUrl : "", &manifestUrl,
                            &result.error)) {
            return result;
        }
    }
    if (!plat::allowedUrl(manifestUrl, &result.error)) return result;

    std::string manifestText;
    if (!fetchText(manifestUrl, kMaxManifestBytes, &manifestText, &result.error,
                   &result.cancelled)) {
        return result;
    }
    if (settings.cancelled && settings.cancelled()) {
        result.cancelled = true;
        result.error = "cancelled";
        return result;
    }
    std::string signatureText;
    if (!fetchText(manifestUrl + ".sig", kMaxSignatureBytes, &signatureText,
                   &result.error, &result.cancelled)) {
        return result;
    }
    const SignatureCheck signature =
        verifySignature(settings.keys, signatureText, manifestText.data(),
                        manifestText.size());
    if (!signature.ok) {
        result.error = "untrusted update manifest: " + signature.error;
        return result;
    }

    UpdateManifest manifest;
    std::string parseError;
    const ParseStatus status = UpdateManifest::parse(manifestText, &manifest, &parseError);
    if (status == ParseStatus::UnknownFormat) {
        result.status = CheckStatus::ManualOnly;
        result.notes = notesUrlFrom(manifestText);
        return result;
    }
    if (status != ParseStatus::Ok) {
        result.error = parseError;
        return result;
    }
    const UpdateArchive& archive = platformArchive(manifest);
    if (archive.archive.empty()) {
        result.error = "the update manifest has no archive for this platform";
        return result;
    }
    if (!(settings.currentVersion < manifest.version)) {
        // Same version or older: never offer a downgrade.
        result.status = CheckStatus::UpToDate;
        result.version = manifest.version;
        return result;
    }
    if (!settings.skipVersion.empty() &&
        settings.skipVersion == manifest.version.toString()) {
        result.status = CheckStatus::Skipped;
        result.version = manifest.version;
        return result;
    }
    result.status = CheckStatus::Available;
    result.manifest = manifest;
    result.version = manifest.version;
    result.notes = manifest.notes;
    result.archive = archive.archive;
    result.size = archive.size;
    result.sha256 = archive.sha256;
    return result;
}

ApplyResult apply(const ApplySettings& settings) {
    ApplyResult result;
    result.version = settings.manifest.version;
    const std::filesystem::path root = settings.root;
    const std::string version = settings.manifest.version.toString();
    const std::filesystem::path workspace = root / kWorkspaceDirectory / version;
    const std::filesystem::path staged = workspace / "staged";
    const std::filesystem::path archivePath = workspace / "archive";
    const std::filesystem::path journalPath = workspace / "journal";
    WorkspaceGuard workspaceGuard{root, workspace};
    const UpdateArchive& archiveInfo = platformArchive(settings.manifest);
    if (archiveInfo.archive.empty()) {
        result.error = "the update manifest has no archive for this platform";
        return result;
    }
    const auto cancelled = [&settings]() {
        return settings.cancelled && settings.cancelled();
    };
    if (cancelled()) {
        result.status = ApplyStatus::Cancelled;
        result.error = "cancelled";
        return result;
    }

    // The old manifest decides what this install owns: it is what makes the collision
    // rule and deletions safe.
    PackageManifest oldManifest;
    bool haveOld = false;
    {
        std::string text;
        if (readFile(root / kPackageManifestName, &text)) {
            std::string ignored;
            haveOld = PackageManifest::parse(text, &oldManifest, &ignored) ==
                      ParseStatus::Ok;
        }
    }
    if (haveOld && oldManifest.target != platformTarget()) {
        result.error = "the installed package is for another platform";
        return result;
    }

    if (!platform::makeDirectories(workspace, &result.error)) return result;

    // Before the download: archive plus twice a conservative unpack. The package manifest
    // that would give the exact total is inside the archive.
    const std::uint64_t required = archiveInfo.size * 3;
    if (settings.hasSpace) {
        if (!settings.hasSpace(required)) {
            result.error = "not enough free space for the update";
            return result;
        }
    } else {
        std::uint64_t freeBytes = 0;
        if (!platform::availableSpace(root, &freeBytes, &result.error)) return result;
        if (freeBytes < required) {
            result.error = "not enough free space for the update";
            return result;
        }
    }

    if (settings.phase) settings.phase(ApplyPhase::Downloading);
    std::vector<std::uint8_t> archiveBytes;
    if (settings.fetchArchive) {
        if (!settings.fetchArchive(archiveInfo, &archiveBytes, &result.error)) {
            return result;
        }
        if (archiveBytes.size() != archiveInfo.size) {
            result.error = "the archive is not the size the manifest says";
            return result;
        }
        if (sha256Hex(archiveBytes.data(), archiveBytes.size()) != archiveInfo.sha256) {
            result.error = "the archive does not match the manifest's sha256";
            return result;
        }
    } else {
        Sha256 hash;
        std::uint64_t received = 0;
        std::ofstream output(archivePath, std::ios::binary | std::ios::trunc);
        if (!output) {
            result.error = "cannot write " + archivePath.string();
            return result;
        }
        plat::HttpRequest request;
        request.url = archiveUrlFor(
            settings.manifestUrl.empty() ? resolvedManifestUrl() : settings.manifestUrl,
            settings.manifest.version, archiveInfo.archive);
        request.maxBytes = archiveInfo.size;
        const plat::HttpResult http = plat::httpGet(
            request,
            [&hash, &received, &output](const std::uint8_t* data, std::size_t size) {
                hash.update(data, size);
                received += size;
                output.write(reinterpret_cast<const char*>(data),
                             static_cast<std::streamsize>(size));
                return output.good();
            },
            settings.progress);
        output.close();
        if (http.error == plat::HttpError::Cancelled) {
            result.status = ApplyStatus::Cancelled;
            result.error = "cancelled";
            platform::removeFile(archivePath, nullptr);
            return result;
        }
        if (http.error != plat::HttpError::None) {
            result.error = http.message;
            platform::removeFile(archivePath, nullptr);
            return result;
        }
        std::uint8_t digest[32];
        hash.final(digest);
        if (received != archiveInfo.size) {
            platform::removeFile(archivePath, nullptr);
            result.error = "the archive is not the size the manifest says";
            return result;
        }
        if (toHex(digest, sizeof digest) != archiveInfo.sha256) {
            platform::removeFile(archivePath, nullptr);
            result.error = "the archive does not match the manifest's sha256";
            return result;
        }
        std::string bytes;
        if (!readFile(archivePath, &bytes)) {
            result.error = "cannot read the downloaded archive";
            return result;
        }
        archiveBytes.assign(bytes.begin(), bytes.end());
    }
    if (cancelled()) {
        result.status = ApplyStatus::Cancelled;
        result.error = "cancelled";
        return result;
    }

    // Stage, then prove the staged tree against the manifest the archive carries.
    if (settings.phase) settings.phase(ApplyPhase::Verifying);
    if (!platform::makeDirectories(staged, &result.error)) return result;
    std::vector<std::string> archiveFiles;
    if (!extractArchive(archiveBytes, staged, &archiveFiles, &result.error)) {
        return result;
    }
    std::string stagedManifestText;
    if (!readFile(staged / kPackageManifestName, &stagedManifestText)) {
        result.error = "the archive has no package-manifest.txt";
        return result;
    }
    PackageManifest newManifest;
    std::string parseError;
    if (PackageManifest::parse(stagedManifestText, &newManifest, &parseError) !=
        ParseStatus::Ok) {
        result.error = parseError;
        return result;
    }
    if (newManifest.version != version) {
        result.error = "the archive's manifest names version " + newManifest.version +
                       ", not " + version;
        return result;
    }
    if (newManifest.target != platformTarget()) {
        result.error = "the archive is for another platform";
        return result;
    }
    if (!verifyStaged(staged, newManifest, &result.error)) return result;

    // The archive may not carry a file the manifest does not list, or omit one it does.
    {
        std::set<std::string> listed;
        for (const PackageEntry& entry : newManifest.entries) listed.insert(entry.path);
        std::set<std::string> present;
        for (const std::string& path : archiveFiles) {
            if (path == kPackageManifestName) continue;
            present.insert(path);
        }
        if (listed != present) {
            result.error = "the archive's file set does not match its manifest";
            return result;
        }
    }
    if (cancelled()) {
        result.status = ApplyStatus::Cancelled;
        result.error = "cancelled";
        return result;
    }

    // Ownership: a path the new manifest lists may only overwrite a file the old package
    // owns or one whose bytes already match. Game data and player files are never touched.
    std::set<std::string> oldFiles;
    if (haveOld) {
        for (const PackageEntry& entry : oldManifest.entries) oldFiles.insert(entry.path);
    }
    std::map<std::string, const PackageEntry*> newFiles;
    for (const PackageEntry& entry : newManifest.entries) newFiles[entry.path] = &entry;
    // Without an old manifest there is no ownership information: the apply may only add
    // and replace (no deletes), and the new manifest's paths are trusted to be the
    // package's own (docs/AUTO-UPDATE.md).
    if (haveOld) {
        for (const auto& item : newFiles) {
            const std::filesystem::path target =
                root / std::filesystem::u8path(item.first);
            if (!platform::exists(target)) continue;
            if (oldFiles.count(item.first) != 0) continue;
            std::string hex;
            if (!hashFile(target, &hex)) {
                result.error = "cannot read " + item.first;
                return result;
            }
            if (hex != item.second->sha256) {
                result.error = "refusing to overwrite " + item.first +
                               ": the installed package does not own it";
                return result;
            }
        }
    }

    std::vector<Operation> operations;
    for (const auto& item : newFiles) {
        const std::filesystem::path target = root / std::filesystem::u8path(item.first);
        if (!platform::exists(target)) {
            operations.push_back({OperationKind::Add, item.first});
            continue;
        }
        std::string hex;
        if (!hashFile(target, &hex)) {
            result.error = "cannot read " + item.first;
            return result;
        }
        if (hex != item.second->sha256) {
            operations.push_back({OperationKind::Replace, item.first});
        }
    }
    if (haveOld) {
        for (const PackageEntry& entry : oldManifest.entries) {
            if (newFiles.count(entry.path) != 0) continue;
            const std::filesystem::path target = root / std::filesystem::u8path(entry.path);
            if (platform::exists(target)) {
                operations.push_back({OperationKind::Delete, entry.path});
            }
        }
    }
    std::sort(operations.begin(), operations.end(),
              [](const Operation& left, const Operation& right) {
                  return left.path < right.path;
              });

    if (settings.phase) settings.phase(ApplyPhase::Installing);
    const std::string manifestSha =
        sha256Hex(stagedManifestText.data(), stagedManifestText.size());
    if (!platform::writeFileAtomically(
            journalPath, renderJournal("applying", version, manifestSha, operations),
            &result.error)) {
        std::error_code code;
        std::filesystem::remove_all(workspace, code);
        return result;
    }

    const auto applyFailed = [&](const std::string& message) {
        std::string rollbackError;
        if (!rollback(root, workspace, operations, &rollbackError)) {
            workspaceGuard.keep = true;  // the journal is the retry record
            result.error = message + "; rollback failed: " + rollbackError;
        } else {
            result.error = message;
        }
        return result;
    };

    for (std::size_t index = 0; index < operations.size(); ++index) {
        if (cancelled()) {
            result.status = ApplyStatus::Cancelled;
            return applyFailed("cancelled");
        }
        if (settings.failAt && !settings.failAt(static_cast<int>(index))) {
            return applyFailed("the apply was stopped at operation " +
                               std::to_string(index));
        }
        const Operation& operation = operations[index];
        const std::filesystem::path target =
            root / std::filesystem::u8path(operation.path);
        if (operation.kind != OperationKind::Add) {
            std::filesystem::path aside = target;
            aside += ".old";
            if (platform::exists(target) &&
                !platform::renameAside(target, aside, &result.error)) {
                return applyFailed(result.error);
            }
        }
        if (operation.kind != OperationKind::Delete) {
            if (!platform::makeDirectories(target.parent_path(), &result.error)) {
                return applyFailed(result.error);
            }
            const std::filesystem::path source =
                staged / std::filesystem::u8path(operation.path);
            if (!platform::renameIntoPlace(source, target, &result.error)) {
                return applyFailed(result.error);
            }
            const auto entry = newFiles.find(operation.path);
            if (entry != newFiles.end() &&
                !platform::setExecutable(target, entry->second->executable,
                                         &result.error)) {
                return applyFailed(result.error);
            }
        }
    }
    if (cancelled()) {
        result.status = ApplyStatus::Cancelled;
        return applyFailed("cancelled");
    }

    // The commit point: the new package manifest replaces the old one atomically.
    if (!platform::writeFileAtomically(root / kPackageManifestName, stagedManifestText,
                                       &result.error)) {
        return applyFailed(result.error);
    }
    std::string ignored;
    platform::writeFileAtomically(
        journalPath, renderJournal("committed", version, manifestSha, operations),
        &ignored);
    // A leftover .old that cannot be deleted yet (Windows) is retried on the next start.
    std::string cleanupError;
    finishCommitted(root, workspace, operations, &cleanupError);
    result.status = ApplyStatus::Ok;
    result.launch = newManifest.launch;
    result.committed = true;
    return result;
}

bool recoverOnStartup(const std::filesystem::path& root) {
    std::error_code code;
    // A development tree has no package manifest, so nothing here is an installed package
    // and no update can be in flight (docs/AUTO-UPDATE.md).
    if (!std::filesystem::exists(root / kPackageManifestName, code) || code) return false;
    const std::filesystem::path workspaceRoot = root / kWorkspaceDirectory;
    if (!std::filesystem::exists(workspaceRoot, code) || code) return false;

    bool acted = false;
    std::vector<std::filesystem::path> workspaces;
    for (std::filesystem::directory_iterator it(workspaceRoot, code), end; !code && it != end;
         it.increment(code)) {
        if (it->is_directory(code) && !code) workspaces.push_back(it->path());
    }
    for (const std::filesystem::path& workspace : workspaces) {
        std::string text;
        if (!readFile(workspace / "journal", &text)) {
            // A workspace without a journal never reached the first rename.
            removeWorkspace(root, workspace);
            acted = true;
            continue;
        }
        std::string state;
        std::string manifestSha;
        std::vector<Operation> operations;
        std::string error;
        if (!parseJournal(text, &state, &manifestSha, &operations, &error)) continue;
        bool committed = state == "committed";
        if (!committed) {
            // A crash between the manifest rename and the journal update leaves the new
            // manifest in place: that is the commit, and the .old files can go.
            std::string current;
            committed = readFile(root / kPackageManifestName, &current) &&
                        sha256Hex(current.data(), current.size()) == manifestSha;
        }
        if (committed) {
            acted = finishCommitted(root, workspace, operations, &error) || acted;
        } else {
            acted = rollback(root, workspace, operations, &error) || acted;
        }
    }
    return acted;
}

bool relaunch(const std::filesystem::path& root, const std::string& launch,
              const std::vector<std::string>& arguments, const std::string& updatedFrom,
              std::string* error) {
    std::vector<std::string> forwarded = arguments;
    forwarded.push_back("--updated-from=" + updatedFrom);
    return platform::launchProcess(root, root / std::filesystem::u8path(launch), forwarded,
                                   error);
}

bool installRoot(std::filesystem::path* root, std::string* error) {
    std::filesystem::path self;
    if (!platform::selfPath(&self, error)) return false;
    *root = self.parent_path();
    return true;
}

}  // namespace update
