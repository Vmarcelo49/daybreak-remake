// =============================================================================
//  text_codec.h — minimal text-encoding helpers (Shift-JIS -> UTF-8).
//
//  Daybreak's .DAT file tables store filenames in Shift-JIS (CP932), the
//  standard Japanese Windows codepage.  We expose a single helper that
//  converts a CP932 byte string to UTF-8 for display / cross-platform use.
//
//  Implementation uses Win32 MultiByteToWideChar / WideCharToMultiByte —
//  available on every Windows target since Win2k and shipped with MinGW's
//  headers.  On Linux we'd need libiconv; we cross-compile to Windows only,
//  so the Win32 path is sufficient.
// =============================================================================
#pragma once

#include <cstdint>
#include <string>

namespace daybreak::file_parser::text_codec {

// Convert a Shift-JIS (CP932) byte string to UTF-8.
// Returns an empty string on failure or empty input.
std::string shift_jis_to_utf8(const std::string& sjis);

// Convert a raw byte buffer (which may contain embedded nulls before the
// real end of the filename) to a UTF-8 string.  Stops at the first null
// byte — this matches how the Go reference trims the 260-byte filename
// slots in the .DAT file table.
std::string shift_jis_buffer_to_utf8(const uint8_t* data, std::size_t size);

} // namespace daybreak::file_parser::text_codec
