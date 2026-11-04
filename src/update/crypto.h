#pragma once
// update/crypto.h — SHA-256 for archive and file hashes, Ed25519 for the release manifest.
//
// SHA-256 is written here rather than fetched: Monocypher has no SHA-256, and the whole
// need is one streaming hash. Ed25519 is Monocypher's RFC 8032 implementation, wrapped so
// the game holds a list of trusted keys and never a single hard-coded one (docs/AUTO-UPDATE.md).
#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace update {

class Sha256 {
public:
    Sha256();
    void update(const void* data, std::size_t size);
    void final(std::uint8_t digest[32]);

private:
    void compress(const std::uint8_t block[64]);
    std::uint32_t state_[8];
    std::uint64_t length_ = 0;  // bytes fed so far
    std::uint8_t buffer_[64] = {};
    std::size_t buffered_ = 0;
};

std::string sha256Hex(const void* data, std::size_t size);
std::string toHex(const std::uint8_t* bytes, std::size_t size);

struct SignatureCheck {
    bool ok = false;
    std::size_t keyIndex = 0;  // valid when ok
    std::string error;         // one line when !ok
};

// `signature` is the .sig file's text: 128 lowercase hex characters and exactly one
// newline, as tools/release_sign writes it. The first trusted key that verifies wins, so a
// later release can introduce a new key while the old one is still accepted.
SignatureCheck verifySignature(const std::vector<std::array<std::uint8_t, 32>>& keys,
                               const std::string& signature, const void* message,
                               std::size_t messageSize);

}  // namespace update
