// =============================================================================
//  dat_crypto.h — Higurashi Daybreak .DAT file XOR-encryption primitives.
//
//  Ported 1:1 from the Go reference at github.com/Vmarcelo49/higurashi-daybreak-in-go
//  (crypto/crypto.go).  Two operations:
//
//    1. File-table block: stateful XOR stream keyed by a table index.
//       Used to encrypt/decrypt the (numFiles * 268)-byte table at the start
//       of every .DAT file.  The Go tool always calls this with index = 0,
//       but we keep the index parameter for fidelity with the original.
//
//    2. File-data block: single-byte XOR with a key derived from the file's
//       offset inside the .DAT.  Used for every individual file payload.
//
//  Both operations are their own inverse (XOR-based), so the same functions
//  encrypt and decrypt.
// =============================================================================
#pragma once

#include <cstdint>
#include <span>
#include <vector>

namespace daybreak::file_parser::dat_crypto {

// ---------------------------------------------------------------------------
// File-table stream cipher
//
//   key₀     = (100 * (index + 1) + ((0xff & (index * (index - 1) / 2)) * 77)) & 0xff
//   counter₀ = (100 + index * 77) & 0xff
//
//   for each byte i:
//     out[i] = in[i] ^ key
//     key     = (key     + counter) & 0xff
//     counter = (counter + 77)      & 0xff
//
// Inverse of itself — same function encrypts and decrypts.
//
// `index` is masked with 0x1ff (9 bits) per the Go reference.
// ---------------------------------------------------------------------------
void file_table_xor(uint32_t index, std::span<uint8_t> data);

// Convenience overload for std::vector (in-place).
inline void file_table_xor(uint32_t index, std::vector<uint8_t>& data) {
    file_table_xor(index, std::span<uint8_t>(data));
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

inline void file_data_xor(uint64_t offset, std::span<uint8_t> data) {
    const uint8_t key = file_data_key(offset);
    for (auto& b : data) b ^= key;
}

inline void file_data_xor(uint64_t offset, std::vector<uint8_t>& data) {
    file_data_xor(offset, std::span<uint8_t>(data));
}

} // namespace daybreak::file_parser::dat_crypto
