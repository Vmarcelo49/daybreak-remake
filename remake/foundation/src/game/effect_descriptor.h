#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace game {
// FUN_0042eec0 reads a version dword followed by one fixed 0x104-byte path.
// Stale bytes after its first NUL are not additional mesh names.
inline std::string effectModelPath(const std::vector<uint8_t>& bytes) {
    if (bytes.size() < 0x108) return {};
    size_t end = 4;
    while (end < 0x108 && bytes[end]) ++end;
    if (end == 0x108) return {};
    return std::string(reinterpret_cast<const char*>(bytes.data()+4),end-4);
}
}
