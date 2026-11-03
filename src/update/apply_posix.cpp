#include "update/apply_platform.h"

#include <cerrno>
#include <cstring>
#include <fstream>
#include <system_error>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <unistd.h>

namespace update {
namespace platform {
namespace {

bool fail(std::string* error, const std::string& message) {
    if (error != nullptr) *error = message;
    return false;
}

}  // namespace

bool renameAside(const std::filesystem::path& path,
                 const std::filesystem::path& aside, std::string* error) {
    std::error_code code;
    std::filesystem::rename(path, aside, code);
    if (code) {
        return fail(error, "cannot rename " + path.string() + " aside: " + code.message());
    }
    return true;
}

bool renameIntoPlace(const std::filesystem::path& from,
                     const std::filesystem::path& to, std::string* error) {
    std::error_code code;
    std::filesystem::rename(from, to, code);
    if (code) {
        return fail(error, "cannot rename " + from.string() + " into place: " +
                               code.message());
    }
    return true;
}

bool removeFile(const std::filesystem::path& path, std::string* error) {
    std::error_code code;
    std::filesystem::remove(path, code);
    if (code) return fail(error, "cannot remove " + path.string() + ": " + code.message());
    return true;
}

bool makeDirectories(const std::filesystem::path& path, std::string* error) {
    std::error_code code;
    std::filesystem::create_directories(path, code);
    if (code) {
        return fail(error, "cannot create " + path.string() + ": " + code.message());
    }
    return true;
}

bool writeFileAtomically(const std::filesystem::path& path, const std::string& bytes,
                         std::string* error) {
    std::filesystem::path temporary = path;
    temporary += ".tmp";
    const int fd = ::open(temporary.c_str(), O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
    if (fd < 0) {
        return fail(error, "cannot create " + temporary.string() + ": " +
                               std::strerror(errno));
    }
    std::size_t written = 0;
    while (written < bytes.size()) {
        const ssize_t count = ::write(fd, bytes.data() + written, bytes.size() - written);
        if (count < 0) {
            if (errno == EINTR) continue;
            const std::string message = std::strerror(errno);
            ::close(fd);
            ::unlink(temporary.c_str());
            return fail(error, "cannot write " + temporary.string() + ": " + message);
        }
        written += static_cast<std::size_t>(count);
    }
    if (::fsync(fd) != 0) {
        const std::string message = std::strerror(errno);
        ::close(fd);
        ::unlink(temporary.c_str());
        return fail(error, "cannot flush " + temporary.string() + ": " + message);
    }
    if (::close(fd) != 0) {
        return fail(error, "cannot close " + temporary.string() + ": " +
                               std::strerror(errno));
    }
    std::error_code code;
    std::filesystem::rename(temporary, path, code);
    if (code) {
        return fail(error, "cannot replace " + path.string() + ": " + code.message());
    }
    return syncDirectory(path.parent_path(), error);
}

bool syncDirectory(const std::filesystem::path& path, std::string* error) {
    if (path.empty()) return true;
    const int fd = ::open(path.c_str(), O_RDONLY | O_DIRECTORY | O_CLOEXEC);
    if (fd < 0) {
        // Not every filesystem exposes a directory fd; the rename itself is still atomic.
        return true;
    }
    const int status = ::fsync(fd);
    ::close(fd);
    if (status != 0 && errno != EINVAL) {
        return fail(error, "cannot flush " + path.string() + ": " + std::strerror(errno));
    }
    return true;
}

bool availableSpace(const std::filesystem::path& path, std::uint64_t* bytes,
                    std::string* error) {
    struct statvfs info {};
    if (::statvfs(path.c_str(), &info) != 0) {
        return fail(error, "cannot read free space for " + path.string() + ": " +
                               std::strerror(errno));
    }
    *bytes = static_cast<std::uint64_t>(info.f_bavail) * info.f_frsize;
    return true;
}

bool selfPath(std::filesystem::path* path, std::string* error) {
    std::string buffer(4096, '\0');
    const ssize_t length = ::readlink("/proc/self/exe", buffer.data(), buffer.size() - 1);
    if (length <= 0) {
        return fail(error, "cannot read /proc/self/exe");
    }
    buffer.resize(static_cast<std::size_t>(length));
    *path = std::filesystem::path(buffer);
    return true;
}

bool exists(const std::filesystem::path& path) {
    std::error_code code;
    return std::filesystem::exists(path, code);
}

std::uint64_t fileSize(const std::filesystem::path& path) {
    std::error_code code;
    const auto size = std::filesystem::file_size(path, code);
    return code ? 0 : static_cast<std::uint64_t>(size);
}

bool setExecutable(const std::filesystem::path& path, bool executable, std::string* error) {
    const mode_t mode = executable ? 0755 : 0644;
    if (::chmod(path.c_str(), mode) != 0) {
        return fail(error, "cannot set the mode of " + path.string() + ": " +
                               std::strerror(errno));
    }
    return true;
}

bool launchProcess(const std::filesystem::path& workingDirectory,
                   const std::filesystem::path& executable,
                   const std::vector<std::string>& arguments, std::string* error) {
    if (::chdir(workingDirectory.c_str()) != 0) {
        return fail(error, "cannot enter " + workingDirectory.string() + ": " +
                               std::strerror(errno));
    }
    std::vector<std::string> storage;
    storage.reserve(arguments.size() + 1);
    storage.push_back(executable.string());
    for (const std::string& argument : arguments) storage.push_back(argument);
    std::vector<char*> argv;
    argv.reserve(storage.size() + 1);
    for (std::string& argument : storage) argv.push_back(argument.data());
    argv.push_back(nullptr);
    ::execv(executable.c_str(), argv.data());
    return fail(error, "cannot start " + executable.string() + ": " +
                           std::strerror(errno));
}

}  // namespace platform
}  // namespace update
