#pragma once
// update/apply_platform.h — the file operations applying an update needs, per platform.
//
// Every applied file takes the same two steps everywhere: the existing file is renamed
// aside, then the staged file is renamed into place. That is what makes a crash leave
// either the old file or the new one and never a half-written mix, and on Windows it is
// also the only way to replace a running .exe or a loaded .dll (they can be renamed but not
// overwritten). The journal, the collision rule and the commit point live in updater.cpp;
// this seam only knows how to move bytes atomically.
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

namespace update {
namespace platform {

bool renameAside(const std::filesystem::path& path,
                 const std::filesystem::path& aside, std::string* error);
bool renameIntoPlace(const std::filesystem::path& from,
                     const std::filesystem::path& to, std::string* error);
bool removeFile(const std::filesystem::path& path, std::string* error);  // absent is fine
bool makeDirectories(const std::filesystem::path& path, std::string* error);
// Temp file, fsync, rename over the target, fsync the directory. Used for the journal and
// for the package manifest, the two files whose replacement is a commit point.
bool writeFileAtomically(const std::filesystem::path& path, const std::string& bytes,
                         std::string* error);
bool syncDirectory(const std::filesystem::path& path, std::string* error);
bool availableSpace(const std::filesystem::path& path, std::uint64_t* bytes,
                    std::string* error);
// The directory of the running binary (/proc/self/exe, GetModuleFileNameW).
bool selfPath(std::filesystem::path* path, std::string* error);
bool exists(const std::filesystem::path& path);
std::uint64_t fileSize(const std::filesystem::path& path);
bool setExecutable(const std::filesystem::path& path, bool executable, std::string* error);
// execv on Linux (does not return on success); CreateProcessW on Windows (returns).
bool launchProcess(const std::filesystem::path& workingDirectory,
                   const std::filesystem::path& executable,
                   const std::vector<std::string>& arguments,
                   std::string* error);

}  // namespace platform
}  // namespace update
