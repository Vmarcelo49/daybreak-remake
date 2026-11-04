#include "update/version.h"

namespace update {
namespace {

bool parsePart(const std::string& text, std::size_t begin, std::size_t end,
               std::uint32_t* out) {
    if (begin == end) return false;
    // Semver forbids leading zeros, and VERSION is semver.
    if (text[begin] == '0' && end - begin > 1) return false;
    std::uint64_t value = 0;
    for (std::size_t index = begin; index < end; ++index) {
        if (text[index] < '0' || text[index] > '9') return false;
        value = value * 10 + static_cast<std::uint64_t>(text[index] - '0');
        if (value > 0xFFFFFFFFull) return false;
    }
    *out = static_cast<std::uint32_t>(value);
    return true;
}

}  // namespace

bool Version::parse(const std::string& text, Version* out, std::string* error) {
    const std::size_t first = text.find('.');
    const std::size_t second =
        first == std::string::npos ? std::string::npos : text.find('.', first + 1);
    if (first == std::string::npos || second == std::string::npos ||
        text.find('.', second + 1) != std::string::npos) {
        if (error != nullptr) *error = "'" + text + "' is not X.Y.Z";
        return false;
    }
    Version parsed;
    if (!parsePart(text, 0, first, &parsed.major) ||
        !parsePart(text, first + 1, second, &parsed.minor) ||
        !parsePart(text, second + 1, text.size(), &parsed.patch)) {
        if (error != nullptr) {
            *error = "'" + text + "' is not X.Y.Z (plain numbers, no leading zeros)";
        }
        return false;
    }
    *out = parsed;
    return true;
}

std::string Version::toString() const {
    return std::to_string(major) + "." + std::to_string(minor) + "." +
           std::to_string(patch);
}

bool Version::operator==(const Version& other) const {
    return major == other.major && minor == other.minor && patch == other.patch;
}

bool Version::operator<(const Version& other) const {
    if (major != other.major) return major < other.major;
    if (minor != other.minor) return minor < other.minor;
    return patch < other.patch;
}

}  // namespace update
