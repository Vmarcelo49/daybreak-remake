// =============================================================================
//  dat_crypto.h — Higurashi Daybreak .DAT file XOR-encryption primitives.
//
//  Ported 1:1 from remake/src/file_parser/dat_crypto.{h,cpp} (the DX9 side),
//  itself a port of the Go reference github.com/Vmarcelo49/higurashi-daybreak-in-go
//  (crypto/crypto.go).  Two operations:
//
//    1. File-table block: stateful XOR stream keyed by a table index.
//       Used to encrypt/decrypt the (numFiles * 268)-byte table at the start
//       of every .DAT file.  The Go tool always calls this with index = 0, and
//       so does the original exe (FUN_00662d10 @ 0x00662d10 seeds key=100,
//       inc=100), but the index parameter is kept for fidelity.
//
//    2. File-data block: single-byte XOR with a key derived from the file's
//       offset inside the .DAT (FUN_00663030 @ 0x00663030).
//
//  Both operations are their own inverse (XOR-based), so the same functions
//  encrypt and decrypt.
//
//  Deviation from the DX9 header: these take (pointer, size) instead of
//  std::span, because the foundation builds as C++17 (remake/foundation/
//  CMakeLists.txt sets CMAKE_CXX_STANDARD 17) while remake/src/ is C++23.
//  The arithmetic is unchanged.
// =============================================================================
#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace fnd::assets::dat_crypto {

// ---------------------------------------------------------------------------
// File-table stream cipher
//
//   key0     = (100 * (index + 1) + ((0xff & (index * (index - 1) / 2)) * 77)) & 0xff
//   counter0 = (100 + index * 77) & 0xff
//
//   for each byte i:
//     out[i] = in[i] ^ key
//     key     = (key     + counter) & 0xff
//     counter = (counter + 77)      & 0xff
//
// Inverse of itself — the same function encrypts and decrypts.
//
// `index` is masked with 0x1ff (9 bits) per the Go reference.
// ---------------------------------------------------------------------------
void file_table_xor(uint32_t index, uint8_t* data, std::size_t size);

// Convenience overload for std::vector (in-place).  No-op on an empty vector.
inline void file_table_xor(uint32_t index, std::vector<uint8_t>& data) {
    if (!data.empty()) file_table_xor(index, data.data(), data.size());
}

// ---------------------------------------------------------------------------
// File-data single-byte XOR
//
//   key = ((offset >> 1) & 0xff) | 0x08
//
// The same key is XORed against every byte of the payload (no state, no
// chaining).  Like the table cipher, this is its own inverse.
// ---------------------------------------------------------------------------
uint8_t file_data_key(uint64_t offset);

inline void file_data_xor(uint64_t offset, uint8_t* data, std::size_t size) {
    const uint8_t key = file_data_key(offset);
    for (std::size_t i = 0; i < size; ++i) data[i] ^= key;
}

inline void file_data_xor(uint64_t offset, std::vector<uint8_t>& data) {
    if (!data.empty()) file_data_xor(offset, data.data(), data.size());
}

}  // namespace fnd::assets::dat_crypto
