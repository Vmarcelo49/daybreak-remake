#include "update/package_manifest.h"

#include <cstddef>

#include "update/manifest_text.h"
#include "update/paths.h"

namespace update {
namespace {

bool invalid(std::string* error, const std::string& message) {
    if (error != nullptr) *error = message;
    return false;
}

bool validVersionToken(const std::string& text) {
    if (text.empty()) return false;
    const auto allowed = [](char character) {
        const bool digit = character >= '0' && character <= '9';
        const bool upper = character >= 'A' && character <= 'Z';
        const bool lower = character >= 'a' && character <= 'z';
        return digit || upper || lower || character == '.' || character == '+' ||
               character == '~' || character == '-';
    };
    if (!allowed(text.front())) return false;
    for (const char character : text) {
        if (!allowed(character)) return false;
    }
    return true;
}

// "<sha256>  <size>  <mode>  <path>", two spaces between fields, path last so it may
// contain spaces of its own (leading/trailing ones are refused by the path rules).
bool parseEntry(const std::string& line, PackageEntry* entry, std::string* error) {
    constexpr std::size_t kHashLength = 64;
    if (line.size() < kHashLength + 2 + 1 + 2 + 1 + 2 + 1) {
        return invalid(error, "the entry is too short");
    }
    entry->sha256 = line.substr(0, kHashLength);
    if (!manifest_text::isLowerHex(entry->sha256, kHashLength)) {
        return invalid(error, "the hash is not 64 lowercase hex characters");
    }
    if (line.compare(kHashLength, 2, "  ") != 0) {
        return invalid(error, "fields must be separated by two spaces");
    }
    const std::size_t sizeStart = kHashLength + 2;
    const std::size_t sizeEnd = line.find("  ", sizeStart);
    if (sizeEnd == std::string::npos) {
        return invalid(error, "the size is missing");
    }
    if (!manifest_text::parseDecimal(line.substr(sizeStart, sizeEnd - sizeStart),
                                     &entry->size)) {
        return invalid(error, "the size is not canonical");
    }
    const std::size_t modeAt = sizeEnd + 2;
    if (modeAt >= line.size() || (line[modeAt] != 'x' && line[modeAt] != '-')) {
        return invalid(error, "the mode must be 'x' or '-'");
    }
    if (line.compare(modeAt + 1, 2, "  ") != 0) {
        return invalid(error, "fields must be separated by two spaces");
    }
    entry->path = line.substr(modeAt + 3);
    if (entry->path.empty()) return invalid(error, "the path is empty");
    entry->executable = line[modeAt] == 'x';
    std::string pathError;
    if (!paths::validRelative(entry->path, &pathError)) {
        return invalid(error, pathError);
    }
    return true;
}

}  // namespace

ParseStatus PackageManifest::parse(const std::string& text, PackageManifest* out,
                                   std::string* error) {
    std::vector<std::string> lines;
    if (!manifest_text::splitLines(text, &lines, error)) return ParseStatus::Invalid;
    if (lines.size() < 5) {
        invalid(error, "the manifest is truncated: fewer than five header lines");
        return ParseStatus::Invalid;
    }

    std::string formatText;
    if (!manifest_text::headerValue(lines[0], "format", &formatText)) {
        invalid(error, "line 1 must be 'format = 1'");
        return ParseStatus::Invalid;
    }
    std::uint64_t format = 0;
    if (!manifest_text::parseDecimal(formatText, &format)) {
        invalid(error, "line 1: the format is not a number");
        return ParseStatus::Invalid;
    }
    if (format != 1) {
        if (error != nullptr) {
            *error = "the manifest has format " + formatText +
                     ", which this build does not understand";
        }
        return ParseStatus::UnknownFormat;
    }

    PackageManifest parsed;
    parsed.format = 1;
    if (!manifest_text::headerValue(lines[1], "version", &parsed.version)) {
        invalid(error, "line 2 must be 'version = <value>'");
        return ParseStatus::Invalid;
    }
    if (!validVersionToken(parsed.version)) {
        invalid(error, "line 2: '" + parsed.version + "' is not a version token");
        return ParseStatus::Invalid;
    }
    if (!manifest_text::headerValue(lines[2], "target", &parsed.target)) {
        invalid(error, "line 3 must be 'target = <value>'");
        return ParseStatus::Invalid;
    }
    if (parsed.target != "linux-x86_64" && parsed.target != "windows-x86_64") {
        invalid(error, "line 3: target '" + parsed.target + "' is not known");
        return ParseStatus::Invalid;
    }
    if (!manifest_text::headerValue(lines[3], "launch", &parsed.launch)) {
        invalid(error, "line 4 must be 'launch = <value>'");
        return ParseStatus::Invalid;
    }
    {
        std::string pathError;
        if (!paths::validRelative(parsed.launch, &pathError)) {
            invalid(error, "launch: " + pathError);
            return ParseStatus::Invalid;
        }
    }
    if (lines[4] != "[files]") {
        invalid(error, "line 5 must be '[files]'");
        return ParseStatus::Invalid;
    }

    for (std::size_t index = 5; index < lines.size(); ++index) {
        const std::string number = std::to_string(index + 1);
        if (lines[index].empty()) {
            invalid(error, "line " + number + ": blank line");
            return ParseStatus::Invalid;
        }
        PackageEntry entry;
        std::string entryError;
        if (!parseEntry(lines[index], &entry, &entryError)) {
            invalid(error, "line " + number + ": " + entryError);
            return ParseStatus::Invalid;
        }
        if (entry.path == kPackageManifestName) {
            invalid(error, "line " + number + ": the manifest must not list itself");
            return ParseStatus::Invalid;
        }
        parsed.entries.push_back(entry);
    }
    if (parsed.entries.empty()) {
        invalid(error, "the manifest lists no files");
        return ParseStatus::Invalid;
    }

    std::vector<std::string> entryPaths;
    entryPaths.reserve(parsed.entries.size());
    for (std::size_t index = 0; index < parsed.entries.size(); ++index) {
        if (index > 0 &&
            !(parsed.entries[index - 1].path < parsed.entries[index].path)) {
            invalid(error, "entries must be sorted bytewise by path");
            return ParseStatus::Invalid;
        }
        entryPaths.push_back(parsed.entries[index].path);
    }
    std::string setError;
    if (!paths::validSet(entryPaths, &setError)) {
        invalid(error, setError);
        return ParseStatus::Invalid;
    }

    const PackageEntry* launch = parsed.find(parsed.launch);
    if (launch == nullptr) {
        invalid(error, "launch '" + parsed.launch + "' is not listed");
        return ParseStatus::Invalid;
    }
    if (parsed.target == "linux-x86_64" && !launch->executable) {
        invalid(error, "launch '" + parsed.launch + "' must have mode 'x'");
        return ParseStatus::Invalid;
    }
    if (parsed.target == "windows-x86_64") {
        for (const PackageEntry& entry : parsed.entries) {
            if (entry.executable) {
                invalid(error,
                        "a windows-x86_64 manifest uses '-' for every file");
                return ParseStatus::Invalid;
            }
        }
    }

    *out = parsed;
    return ParseStatus::Ok;
}

const PackageEntry* PackageManifest::find(const std::string& path) const {
    for (const PackageEntry& entry : entries) {
        if (entry.path == path) return &entry;
    }
    return nullptr;
}

}  // namespace update
