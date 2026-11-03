#pragma once
// update/manifest_text.h — the line format both manifests share, in one place.
//
// package-manifest.txt and update-manifest.txt are `key = value` lines with LF endings,
// no surrounding whitespace and a final newline. tools/package_manifest.py and
// tools/make_update_manifest.py write them; these parsers are the game's side of the same
// contract (docs/AUTO-UPDATE.md), and the cross-check test runs both halves on the same
// fixtures.
#include <cstdint>
#include <string>
#include <vector>

namespace update {
namespace manifest_text {

inline bool splitLines(const std::string& text, std::vector<std::string>* lines,
                       std::string* error) {
    if (text.find('\r') != std::string::npos) {
        if (error != nullptr) *error = "the file uses CRLF; it must use LF line endings";
        return false;
    }
    if (text.empty() || text.back() != '\n') {
        if (error != nullptr) *error = "the file must end with a newline";
        return false;
    }
    lines->clear();
    std::size_t start = 0;
    while (start < text.size()) {
        const std::size_t newline = text.find('\n', start);
        lines->push_back(text.substr(start, newline - start));
        start = newline + 1;
    }
    return true;
}

// "key = value", exactly one space around '=', value non-empty and not padded.
inline bool headerValue(const std::string& line, const char* key, std::string* value) {
    const std::string prefix = std::string(key) + " = ";
    if (line.compare(0, prefix.size(), prefix) != 0) return false;
    const std::string rest = line.substr(prefix.size());
    if (rest.empty() || rest.front() == ' ' || rest.back() == ' ') return false;
    *value = rest;
    return true;
}

// Canonical decimal: digits only, no leading zero unless the value is exactly "0".
inline bool parseDecimal(const std::string& text, std::uint64_t* out) {
    if (text.empty()) return false;
    if (text.size() > 1 && text[0] == '0') return false;
    std::uint64_t value = 0;
    for (const char character : text) {
        if (character < '0' || character > '9') return false;
        const std::uint64_t digit = static_cast<std::uint64_t>(character - '0');
        if (value > (0xFFFFFFFFFFFFFFFFull - digit) / 10) return false;
        value = value * 10 + digit;
    }
    *out = value;
    return true;
}

inline bool isLowerHex(const std::string& text, std::size_t length) {
    if (text.size() != length) return false;
    for (const char character : text) {
        const bool digit = character >= '0' && character <= '9';
        const bool letter = character >= 'a' && character <= 'f';
        if (!digit && !letter) return false;
    }
    return true;
}

}  // namespace manifest_text
}  // namespace update
