// psp/psp_manifest.cpp — reading and locating assets/psp/manifest.txt.
#include "psp/psp_manifest.h"

#include <cstdio>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace psp {
namespace {

bool isHex64(const std::string& text) {
    if (text.size() != 64) return false;
    for (char c : text)
        if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f'))) return false;
    return true;
}

std::string joinPath(const std::string& dir, const std::string& rest) {
    if (dir.empty()) return rest;
    const char last = dir.back();
    return (last == '/' || last == '\\') ? dir + rest : dir + "/" + rest;
}

}  // namespace

PspManifest PspManifest::parse(const std::string& text) {
    PspManifest manifest;
    std::istringstream lines(text);
    std::string line;
    int number = 0;
    while (std::getline(lines, line)) {
        ++number;
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty() || line[0] == '#') continue;
        const size_t first = line.find('\t');
        const size_t second = first == std::string::npos ? std::string::npos : line.find('\t', first + 1);
        if (first == std::string::npos || second == std::string::npos)
            throw std::runtime_error("psp manifest line " + std::to_string(number) +
                                     ": expected path, size and sha256 separated by tabs");
        PspManifestEntry entry;
        entry.path = line.substr(0, first);
        const std::string size = line.substr(first + 1, second - first - 1);
        entry.sha256 = line.substr(second + 1);
        if (entry.path.empty() || entry.path.front() == '/')
            throw std::runtime_error("psp manifest line " + std::to_string(number) +
                                     ": paths carry no leading slash");
        if (size.empty() || size.find_first_not_of("0123456789") != std::string::npos)
            throw std::runtime_error("psp manifest line " + std::to_string(number) +
                                     ": size is not a number");
        if (!isHex64(entry.sha256))
            throw std::runtime_error("psp manifest line " + std::to_string(number) +
                                     ": sha256 is not 64 lowercase hex digits");
        entry.size = std::stoull(size);
        manifest.entries.push_back(std::move(entry));
    }
    if (manifest.entries.empty())
        throw std::runtime_error("psp manifest: no file rows");
    return manifest;
}

PspManifest PspManifest::load(const std::string& file) {
    std::ifstream stream(file, std::ios::binary);
    if (!stream) throw std::runtime_error("cannot read " + file);
    std::ostringstream text;
    text << stream.rdbuf();
    return parse(text.str());
}

std::string findPspManifest(const std::string& executableDir) {
    const std::string candidates[2] = {
        joinPath(joinPath(executableDir, "assets/psp"), "manifest.txt"),
        "assets/psp/manifest.txt",
    };
    for (const std::string& candidate : candidates) {
        std::FILE* probe = std::fopen(candidate.c_str(), "rb");
        if (!probe) continue;
        std::fclose(probe);
        return candidate;
    }
    return {};
}

}  // namespace psp
