#include "update/update_manifest.h"

#include <vector>

#include "update/manifest_text.h"

namespace update {
namespace {

bool invalid(std::string* error, const std::string& message) {
    if (error != nullptr) *error = message;
    return false;
}

// The archive name ends up in a URL and on a `key = value` line.
bool validArchiveName(const std::string& name) {
    if (name.empty()) return false;
    for (const char character : name) {
        const bool digit = character >= '0' && character <= '9';
        const bool upper = character >= 'A' && character <= 'Z';
        const bool lower = character >= 'a' && character <= 'z';
        const bool punctuation = character == '.' || character == '_' ||
                                 character == '+' || character == '-';
        if (!digit && !upper && !lower && !punctuation) return false;
    }
    return true;
}

bool validNotes(const std::string& notes) {
    if (notes.compare(0, 8, "https://") != 0) return false;
    for (const char character : notes) {
        const unsigned char value = static_cast<unsigned char>(character);
        if (value <= 0x20 || value == 0x7F) return false;
    }
    return true;
}

bool parseArchive(const std::string& archiveLine, const std::string& sizeLine,
                  const std::string& shaLine, UpdateArchive* out, std::string* error) {
    if (!manifest_text::headerValue(archiveLine, "archive", &out->archive)) {
        return invalid(error, "the archive line is missing");
    }
    if (!validArchiveName(out->archive)) {
        return invalid(error, "archive '" + out->archive + "' is not URL-safe");
    }
    std::string sizeText;
    if (!manifest_text::headerValue(sizeLine, "size", &sizeText)) {
        return invalid(error, "the size line is missing");
    }
    if (!manifest_text::parseDecimal(sizeText, &out->size)) {
        return invalid(error, "size '" + sizeText + "' is not canonical");
    }
    if (!manifest_text::headerValue(shaLine, "sha256", &out->sha256)) {
        return invalid(error, "the sha256 line is missing");
    }
    if (!manifest_text::isLowerHex(out->sha256, 64)) {
        return invalid(error, "sha256 is not 64 lowercase hex characters");
    }
    return true;
}

}  // namespace

ParseStatus UpdateManifest::parse(const std::string& text, UpdateManifest* out,
                                  std::string* error) {
    std::vector<std::string> lines;
    if (!manifest_text::splitLines(text, &lines, error)) return ParseStatus::Invalid;
    if (lines.size() != 11) {
        invalid(error, "the update manifest must be exactly 11 lines");
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
            *error = "the update manifest has format " + formatText +
                     ", which this build does not understand";
        }
        return ParseStatus::UnknownFormat;
    }

    UpdateManifest parsed;
    parsed.format = 1;
    std::string versionText;
    if (!manifest_text::headerValue(lines[1], "version", &versionText)) {
        invalid(error, "line 2 must be 'version = <X.Y.Z>'");
        return ParseStatus::Invalid;
    }
    if (!Version::parse(versionText, &parsed.version, error)) {
        return ParseStatus::Invalid;
    }
    if (!manifest_text::headerValue(lines[2], "notes", &parsed.notes)) {
        invalid(error, "line 3 must be 'notes = <url>'");
        return ParseStatus::Invalid;
    }
    if (!validNotes(parsed.notes)) {
        invalid(error, "notes '" + parsed.notes + "' is not an https URL");
        return ParseStatus::Invalid;
    }
    if (lines[3] != "[linux-x86_64]") {
        invalid(error, "line 4 must be '[linux-x86_64]'");
        return ParseStatus::Invalid;
    }
    if (!parseArchive(lines[4], lines[5], lines[6], &parsed.linuxArchive, error)) {
        return ParseStatus::Invalid;
    }
    if (lines[7] != "[windows-x86_64]") {
        invalid(error, "line 8 must be '[windows-x86_64]'");
        return ParseStatus::Invalid;
    }
    if (!parseArchive(lines[8], lines[9], lines[10], &parsed.windowsArchive, error)) {
        return ParseStatus::Invalid;
    }

    *out = parsed;
    return ParseStatus::Ok;
}

}  // namespace update
