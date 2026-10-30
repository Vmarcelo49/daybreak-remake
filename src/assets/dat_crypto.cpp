// =============================================================================
//  dat_crypto.cpp — see header for the format reference.
// =============================================================================
#include "dat_crypto.h"

namespace fnd::assets::dat_crypto {

void file_table_xor(uint32_t index, uint8_t* data, std::size_t size) {
    // Apply 9-bit mask (matches the Go reference's `index & 0x1ff`).
    index &= 0x1ff;

    // Initial counter and key — bit-exact copy of the Go formulas, which are in
    // turn the exe's loop at 0x00662d10 with index = 0 (key = 100, inc = 100).
    uint8_t counter = static_cast<uint8_t>((100u + index * 77u) & 0xffu);
    // The expression `(index * (index - 1) / 2)` is the index-th triangular
    // number; the `0xff & ...` truncates it to a byte.  Computed in uint32_t to
    // avoid intermediate overflow on large indices.
    uint32_t tri = (index * (index - 1u)) / 2u;
    uint8_t key = static_cast<uint8_t>(
        (100u * (index + 1u) + ((tri & 0xffu) * 77u)) & 0xffu);

    for (std::size_t i = 0; i < size; ++i) {
        data[i] ^= key;
        key     = static_cast<uint8_t>((key     + counter) & 0xffu);
        counter = static_cast<uint8_t>((counter + 77u)     & 0xffu);
    }
}

uint8_t file_data_key(uint64_t offset) {
    return static_cast<uint8_t>(((offset >> 1) & 0xffull) | 0x08ull);
}

}  // namespace fnd::assets::dat_crypto
