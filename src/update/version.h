#pragma once
// update/version.h — the release version a manifest claims, compared with the running build.
//
// Strict X.Y.Z on purpose: the updater compares this with VERSION, and a suffix or a
// leading zero would make "is this newer?" ambiguous. VERSION stays the source of the
// running build's version; this type only parses what a release publishes.
#include <cstdint>
#include <string>

namespace update {

struct Version {
    std::uint32_t major = 0;
    std::uint32_t minor = 0;
    std::uint32_t patch = 0;

    // Fails on anything but three plain decimal numbers with no leading zeros.
    static bool parse(const std::string& text, Version* out, std::string* error);
    std::string toString() const;

    bool operator==(const Version& other) const;
    bool operator!=(const Version& other) const { return !(*this == other); }
    bool operator<(const Version& other) const;
};

}  // namespace update
