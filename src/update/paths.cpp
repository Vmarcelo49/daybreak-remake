#include "update/paths.h"

#include <cctype>
#include <cstdint>
#include <set>

namespace update {
namespace paths {
namespace {

bool fail(std::string* error, const std::string& message) {
    if (error != nullptr) *error = message;
    return false;
}

bool asciiAlpha(char character) {
    return (character >= 'A' && character <= 'Z') ||
           (character >= 'a' && character <= 'z');
}

bool ntfsForbidden(char character) {
    switch (character) {
        case '<':
        case '>':
        case ':':
        case '"':
        case '|':
        case '?':
        case '*':
            return true;
        default:
            return false;
    }
}

// RFC 3629 well-formedness: no overlongs, no surrogates, nothing above U+10FFFF.
bool validUtf8(const std::string& text) {
    std::size_t index = 0;
    while (index < text.size()) {
        const unsigned char lead = static_cast<unsigned char>(text[index]);
        if (lead < 0x80) {
            ++index;
            continue;
        }
        std::size_t length = 0;
        std::uint32_t code = 0;
        if ((lead & 0xE0) == 0xC0) {
            length = 2;
            code = lead & 0x1F;
        } else if ((lead & 0xF0) == 0xE0) {
            length = 3;
            code = lead & 0x0F;
        } else if ((lead & 0xF8) == 0xF0) {
            length = 4;
            code = lead & 0x07;
        } else {
            return false;
        }
        if (index + length > text.size()) return false;
        for (std::size_t offset = 1; offset < length; ++offset) {
            const unsigned char next =
                static_cast<unsigned char>(text[index + offset]);
            if ((next & 0xC0) != 0x80) return false;
            code = (code << 6) | (next & 0x3F);
        }
        if ((length == 2 && code < 0x80) || (length == 3 && code < 0x800) ||
            (length == 4 && code < 0x10000)) {
            return false;
        }
        if (code > 0x10FFFF || (code >= 0xD800 && code <= 0xDFFF)) return false;
        index += length;
    }
    return true;
}

// "CON", "con.txt" and "aux.tar.gz" all name a device on Windows.
bool reservedName(const std::string& component) {
    const std::string stem = component.substr(0, component.find('.'));
    const std::string folded = foldCase(stem);
    if (folded == "con" || folded == "prn" || folded == "aux" || folded == "nul") {
        return true;
    }
    if (folded.size() == 4 &&
        (folded.compare(0, 3, "com") == 0 || folded.compare(0, 3, "lpt") == 0)) {
        return folded[3] >= '1' && folded[3] <= '9';
    }
    return false;
}

}  // namespace

std::string foldCase(const std::string& path) {
    std::string folded = path;
    for (char& character : folded) {
        if (character >= 'A' && character <= 'Z') {
            character = static_cast<char>(character - 'A' + 'a');
        }
    }
    return folded;
}

bool validRelative(const std::string& path, std::string* error) {
    if (path.empty()) return fail(error, "empty path");
    if (std::isspace(static_cast<unsigned char>(path.front())) ||
        std::isspace(static_cast<unsigned char>(path.back()))) {
        return fail(error, "'" + path + "' starts or ends with whitespace");
    }
    for (const char character : path) {
        const unsigned char value = static_cast<unsigned char>(character);
        if (value < 0x20 || value == 0x7F) {
            return fail(error, "'" + path + "' contains a control character");
        }
    }
    if (!validUtf8(path)) return fail(error, "'" + path + "' is not valid UTF-8");
    if (path.find('\\') != std::string::npos) {
        return fail(error, "'" + path + "' contains a backslash; paths use '/'");
    }
    if (path.front() == '/') return fail(error, "'" + path + "' is an absolute path");
    if (path.size() >= 2 && asciiAlpha(path[0]) && path[1] == ':') {
        return fail(error, "'" + path + "' starts with a drive letter");
    }

    std::size_t start = 0;
    for (;;) {
        const std::size_t slash = path.find('/', start);
        const std::string component =
            path.substr(start, slash == std::string::npos ? std::string::npos
                                                          : slash - start);
        if (component.empty() || component == "." || component == "..") {
            return fail(error, "'" + path +
                                   "' has an empty, '.' or '..' path component");
        }
        for (const char character : component) {
            if (ntfsForbidden(character)) {
                return fail(error, "'" + path + "' contains '" + character +
                                       "', which NTFS does not allow");
            }
        }
        if (component.back() == '.' || component.back() == ' ') {
            return fail(error, "'" + path +
                                   "' has a component ending in '.' or a space, which "
                                   "Windows silently drops");
        }
        if (reservedName(component)) {
            return fail(error, "'" + path + "' has a Windows device name");
        }
        if (slash == std::string::npos) break;
        start = slash + 1;
    }
    return true;
}

bool validSet(const std::vector<std::string>& paths, std::string* error) {
    std::set<std::string> folded;
    for (const std::string& path : paths) {
        if (!folded.insert(foldCase(path)).second) {
            return fail(error, "'" + path +
                                   "' collides with another entry that differs only in case");
        }
    }
    const std::set<std::string> files(paths.begin(), paths.end());
    for (const std::string& path : paths) {
        for (std::size_t slash = path.find('/'); slash != std::string::npos;
             slash = path.find('/', slash + 1)) {
            const std::string prefix = path.substr(0, slash);
            if (files.count(prefix) != 0) {
                return fail(error, "'" + prefix + "' is a file and also a directory of '" +
                                       path + "'");
            }
        }
    }
    return true;
}

}  // namespace paths
}  // namespace update
