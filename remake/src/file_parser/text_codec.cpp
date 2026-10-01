// =============================================================================
//  text_codec.cpp — see header for docs.
// =============================================================================
#include "text_codec.h"

#include <windows.h>

#include <cstring>
#include <vector>

namespace daybreak::file_parser::text_codec {

namespace {

// Helper: narrow a UTF-16 wstring to UTF-8 using WideCharToMultiByte.
std::string wide_to_utf8(const std::wstring& w) {
    if (w.empty()) return {};
    int n = WideCharToMultiByte(CP_UTF8, 0, w.c_str(), -1,
                                nullptr, 0, nullptr, nullptr);
    if (n <= 0) return {};
    std::vector<char> buf(n);
    WideCharToMultiByte(CP_UTF8, 0, w.c_str(), -1,
                        buf.data(), n, nullptr, nullptr);
    // The null terminator is included in `n`; resize it away.
    return std::string(buf.data());
}

// Helper: widen a CP932 string to UTF-16 using MultiByteToWideChar.
std::wstring cp932_to_wide(const char* s, int len) {
    if (!s || len <= 0) return {};
    int n = MultiByteToWideChar(932, 0, s, len, nullptr, 0);
    if (n <= 0) return {};
    std::vector<wchar_t> buf(n);
    MultiByteToWideChar(932, 0, s, len, buf.data(), n);
    return std::wstring(buf.data(), n);
}

} // namespace

std::string shift_jis_to_utf8(const std::string& sjis) {
    return wide_to_utf8(cp932_to_wide(sjis.c_str(),
                                       static_cast<int>(sjis.size())));
}

std::string shift_jis_buffer_to_utf8(const uint8_t* data, std::size_t size) {
    if (!data || size == 0) return {};

    // Stop at the first null byte (matches the Go reference's
    // `strings.TrimRight(filename, "\x00")` — the Go code trims trailing
    // nulls, but since the field is fixed-width and the name is always
    // at the start, stopping at the first null is equivalent and faster).
    std::size_t real_len = 0;
    while (real_len < size && data[real_len] != 0) ++real_len;
    if (real_len == 0) return {};

    return wide_to_utf8(cp932_to_wide(
        reinterpret_cast<const char*>(data),
        static_cast<int>(real_len)));
}

} // namespace daybreak::file_parser::text_codec
