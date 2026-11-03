#include "update/apply_platform.h"

#include <windows.h>

#include <string>
#include <vector>

namespace update {
namespace platform {
namespace {

std::wstring widen(const std::string& text) {
    if (text.empty()) return std::wstring();
    const int length = MultiByteToWideChar(CP_UTF8, 0, text.data(),
                                           static_cast<int>(text.size()), nullptr, 0);
    if (length <= 0) return std::wstring();
    std::wstring wide(static_cast<std::size_t>(length), L'\0');
    MultiByteToWideChar(CP_UTF8, 0, text.data(), static_cast<int>(text.size()),
                        wide.data(), length);
    return wide;
}

std::string narrow(const std::wstring& text) {
    if (text.empty()) return std::string();
    const int length = WideCharToMultiByte(CP_UTF8, 0, text.data(),
                                           static_cast<int>(text.size()), nullptr, 0,
                                           nullptr, nullptr);
    if (length <= 0) return std::string();
    std::string utf8(static_cast<std::size_t>(length), '\0');
    WideCharToMultiByte(CP_UTF8, 0, text.data(), static_cast<int>(text.size()),
                        utf8.data(), length, nullptr, nullptr);
    return utf8;
}

bool fail(std::string* error, const std::string& message) {
    if (error != nullptr) *error = message;
    return false;
}

// Antivirus scanners and the still-exiting old process can hold a freshly written .exe or
// .dll for a moment; retrying briefly is the documented Windows answer (issue #100 §6).
bool retryable(DWORD code) {
    return code == ERROR_ACCESS_DENIED || code == ERROR_SHARING_VIOLATION ||
           code == ERROR_LOCK_VIOLATION;
}

bool moveWithRetry(const std::filesystem::path& from, const std::filesystem::path& to,
                   DWORD flags, std::string* error) {
    DWORD code = 0;
    for (int attempt = 0; attempt < 50; ++attempt) {
        if (MoveFileExW(from.c_str(), to.c_str(), flags)) return true;
        code = GetLastError();
        if (!retryable(code)) break;
        Sleep(100);
    }
    return fail(error, "cannot move " + narrow(from.wstring()) + " (error " +
                           std::to_string(code) + ")");
}

// Windows command-line quoting, the same rules CreateProcessW documents.
std::wstring quote(const std::wstring& argument) {
    if (!argument.empty() &&
        argument.find_first_of(L" \t\n\v\"") == std::wstring::npos) {
        return argument;
    }
    std::wstring result = L"\"";
    for (auto character = argument.begin();; ++character) {
        std::size_t backslashes = 0;
        while (character != argument.end() && *character == L'\\') {
            ++character;
            ++backslashes;
        }
        if (character == argument.end()) {
            result.append(backslashes * 2, L'\\');
            break;
        }
        if (*character == L'"') {
            result.append(backslashes * 2 + 1, L'\\');
            result.push_back(L'"');
        } else {
            result.append(backslashes, L'\\');
            result.push_back(*character);
        }
    }
    result.push_back(L'"');
    return result;
}

}  // namespace

bool renameAside(const std::filesystem::path& path,
                 const std::filesystem::path& aside, std::string* error) {
    if (GetFileAttributesW(aside.c_str()) != INVALID_FILE_ATTRIBUTES) {
        if (!removeFile(aside, error)) return false;
    }
    return moveWithRetry(path, aside, MOVEFILE_WRITE_THROUGH, error);
}

bool renameIntoPlace(const std::filesystem::path& from,
                     const std::filesystem::path& to, std::string* error) {
    // No REPLACE_EXISTING: the caller renamed the old file aside first, so a target here
    // is a bug in the plan, not something to overwrite.
    return moveWithRetry(from, to, MOVEFILE_WRITE_THROUGH, error);
}

bool removeFile(const std::filesystem::path& path, std::string* error) {
    DWORD code = 0;
    for (int attempt = 0; attempt < 50; ++attempt) {
        if (DeleteFileW(path.c_str())) return true;
        code = GetLastError();
        if (code == ERROR_FILE_NOT_FOUND || code == ERROR_PATH_NOT_FOUND) return true;
        if (!retryable(code)) break;
        Sleep(100);
    }
    return fail(error, "cannot remove " + narrow(path.wstring()) + " (error " +
                           std::to_string(code) + ")");
}

bool makeDirectories(const std::filesystem::path& path, std::string* error) {
    if (path.empty()) return true;
    std::filesystem::path current;
    for (const std::filesystem::path& part : path) {
        current /= part;
        if (current.empty()) continue;
        if (!CreateDirectoryW(current.c_str(), nullptr)) {
            const DWORD code = GetLastError();
            if (code != ERROR_ALREADY_EXISTS) {
                return fail(error, "cannot create " + narrow(current.wstring()) +
                                       " (error " + std::to_string(code) + ")");
            }
        }
    }
    return true;
}

bool writeFileAtomically(const std::filesystem::path& path, const std::string& bytes,
                         std::string* error) {
    std::filesystem::path temporary = path;
    temporary += L".tmp";
    const HANDLE handle = CreateFileW(temporary.c_str(), GENERIC_WRITE, 0, nullptr,
                                      CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (handle == INVALID_HANDLE_VALUE) {
        return fail(error, "cannot create " + narrow(temporary.wstring()) + " (error " +
                               std::to_string(GetLastError()) + ")");
    }
    DWORD written = 0;
    std::size_t offset = 0;
    while (offset < bytes.size()) {
        const DWORD chunk = static_cast<DWORD>(
            (bytes.size() - offset) > 0x10000000 ? 0x10000000 : (bytes.size() - offset));
        if (!WriteFile(handle, bytes.data() + offset, chunk, &written, nullptr)) {
            const DWORD code = GetLastError();
            CloseHandle(handle);
            DeleteFileW(temporary.c_str());
            return fail(error, "cannot write " + narrow(temporary.wstring()) +
                                   " (error " + std::to_string(code) + ")");
        }
        offset += written;
    }
    FlushFileBuffers(handle);
    CloseHandle(handle);
    if (!MoveFileExW(temporary.c_str(), path.c_str(),
                     MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
        return fail(error, "cannot replace " + narrow(path.wstring()) + " (error " +
                               std::to_string(GetLastError()) + ")");
    }
    return true;
}

bool syncDirectory(const std::filesystem::path&, std::string*) {
    // Windows has no directory fsync; MoveFileExW with WRITE_THROUGH covers the rename.
    return true;
}

bool availableSpace(const std::filesystem::path& path, std::uint64_t* bytes,
                    std::string* error) {
    ULARGE_INTEGER available{};
    if (!GetDiskFreeSpaceExW(path.c_str(), &available, nullptr, nullptr)) {
        return fail(error, "cannot read free space for " + narrow(path.wstring()) +
                               " (error " + std::to_string(GetLastError()) + ")");
    }
    *bytes = available.QuadPart;
    return true;
}

bool selfPath(std::filesystem::path* path, std::string* error) {
    std::wstring buffer(512, L'\0');
    for (;;) {
        const DWORD length =
            GetModuleFileNameW(nullptr, buffer.data(), static_cast<DWORD>(buffer.size()));
        if (length == 0) {
            return fail(error, "cannot read the executable path");
        }
        if (length < buffer.size()) {
            buffer.resize(length);
            *path = std::filesystem::path(buffer);
            return true;
        }
        buffer.resize(buffer.size() * 2);
    }
}

bool exists(const std::filesystem::path& path) {
    return GetFileAttributesW(path.c_str()) != INVALID_FILE_ATTRIBUTES;
}

std::uint64_t fileSize(const std::filesystem::path& path) {
    WIN32_FILE_ATTRIBUTE_DATA data{};
    if (!GetFileAttributesExW(path.c_str(), GetFileExInfoStandard, &data)) return 0;
    return (static_cast<std::uint64_t>(data.nFileSizeHigh) << 32) | data.nFileSizeLow;
}

bool setExecutable(const std::filesystem::path&, bool, std::string*) {
    // Windows has no exec bit; the manifest says '-' for every file there.
    return true;
}

bool launchProcess(const std::filesystem::path& workingDirectory,
                   const std::filesystem::path& executable,
                   const std::vector<std::string>& arguments, std::string* error) {
    std::wstring command = quote(executable.wstring());
    for (const std::string& argument : arguments) {
        command += L" ";
        command += quote(widen(argument));
    }
    STARTUPINFOW startup{};
    startup.cb = sizeof startup;
    PROCESS_INFORMATION process{};
    if (!CreateProcessW(executable.c_str(), command.data(), nullptr, nullptr, FALSE, 0,
                        nullptr, workingDirectory.c_str(), &startup, &process)) {
        return fail(error, "cannot start " + narrow(executable.wstring()) + " (error " +
                               std::to_string(GetLastError()) + ")");
    }
    CloseHandle(process.hThread);
    CloseHandle(process.hProcess);
    return true;
}

}  // namespace platform
}  // namespace update
