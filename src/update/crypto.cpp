#include "update/crypto.h"

#include <algorithm>
#include <cstring>

#include "monocypher-ed25519.h"

namespace update {
namespace {

constexpr std::uint32_t kRoundConstants[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
    0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
    0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
    0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
};

constexpr std::uint32_t kInitialState[8] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19,
};

std::uint32_t rotateRight(std::uint32_t value, int bits) {
    return (value >> bits) | (value << (32 - bits));
}

int hexDigit(char character) {
    if (character >= '0' && character <= '9') return character - '0';
    if (character >= 'a' && character <= 'f') return character - 'a' + 10;
    return -1;
}

}  // namespace

Sha256::Sha256() {
    std::memcpy(state_, kInitialState, sizeof state_);
}

void Sha256::compress(const std::uint8_t block[64]) {
    std::uint32_t schedule[64];
    for (int index = 0; index < 16; ++index) {
        schedule[index] = (static_cast<std::uint32_t>(block[index * 4]) << 24) |
                          (static_cast<std::uint32_t>(block[index * 4 + 1]) << 16) |
                          (static_cast<std::uint32_t>(block[index * 4 + 2]) << 8) |
                          static_cast<std::uint32_t>(block[index * 4 + 3]);
    }
    for (int index = 16; index < 64; ++index) {
        const std::uint32_t s0 = rotateRight(schedule[index - 15], 7) ^
                                 rotateRight(schedule[index - 15], 18) ^
                                 (schedule[index - 15] >> 3);
        const std::uint32_t s1 = rotateRight(schedule[index - 2], 17) ^
                                 rotateRight(schedule[index - 2], 19) ^
                                 (schedule[index - 2] >> 10);
        schedule[index] = schedule[index - 16] + s0 + schedule[index - 7] + s1;
    }

    std::uint32_t a = state_[0];
    std::uint32_t b = state_[1];
    std::uint32_t c = state_[2];
    std::uint32_t d = state_[3];
    std::uint32_t e = state_[4];
    std::uint32_t f = state_[5];
    std::uint32_t g = state_[6];
    std::uint32_t h = state_[7];
    for (int index = 0; index < 64; ++index) {
        const std::uint32_t s1 =
            rotateRight(e, 6) ^ rotateRight(e, 11) ^ rotateRight(e, 25);
        const std::uint32_t choose = (e & f) ^ (~e & g);
        const std::uint32_t temp1 =
            h + s1 + choose + kRoundConstants[index] + schedule[index];
        const std::uint32_t s0 =
            rotateRight(a, 2) ^ rotateRight(a, 13) ^ rotateRight(a, 22);
        const std::uint32_t majority = (a & b) ^ (a & c) ^ (b & c);
        const std::uint32_t temp2 = s0 + majority;
        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }
    state_[0] += a;
    state_[1] += b;
    state_[2] += c;
    state_[3] += d;
    state_[4] += e;
    state_[5] += f;
    state_[6] += g;
    state_[7] += h;
}

void Sha256::update(const void* data, std::size_t size) {
    const auto* bytes = static_cast<const std::uint8_t*>(data);
    length_ += size;
    while (size > 0) {
        const std::size_t room = sizeof buffer_ - buffered_;
        const std::size_t take = std::min(room, size);
        std::memcpy(buffer_ + buffered_, bytes, take);
        buffered_ += take;
        bytes += take;
        size -= take;
        if (buffered_ == sizeof buffer_) {
            compress(buffer_);
            buffered_ = 0;
        }
    }
}

void Sha256::final(std::uint8_t digest[32]) {
    const std::uint64_t bitLength = length_ * 8;
    const auto append = [this](const std::uint8_t* data, std::size_t size) {
        std::size_t remaining = size;
        while (remaining > 0) {
            const std::size_t room = sizeof buffer_ - buffered_;
            const std::size_t take = std::min(room, remaining);
            std::memcpy(buffer_ + buffered_, data, take);
            buffered_ += take;
            data += take;
            remaining -= take;
            if (buffered_ == sizeof buffer_) {
                compress(buffer_);
                buffered_ = 0;
            }
        }
    };
    // 0x80, then zeros until 56 bytes into the block, then the bit length.
    std::uint8_t padding[64] = {0x80};
    const std::size_t padSize = buffered_ < 56 ? 56 - buffered_ : 120 - buffered_;
    append(padding, padSize);
    std::uint8_t tail[8];
    for (int index = 0; index < 8; ++index) {
        tail[index] = static_cast<std::uint8_t>(bitLength >> (56 - 8 * index));
    }
    append(tail, sizeof tail);
    for (int index = 0; index < 8; ++index) {
        digest[index * 4] = static_cast<std::uint8_t>(state_[index] >> 24);
        digest[index * 4 + 1] = static_cast<std::uint8_t>(state_[index] >> 16);
        digest[index * 4 + 2] = static_cast<std::uint8_t>(state_[index] >> 8);
        digest[index * 4 + 3] = static_cast<std::uint8_t>(state_[index]);
    }
}

std::string toHex(const std::uint8_t* bytes, std::size_t size) {
    static const char kDigits[] = "0123456789abcdef";
    std::string text(size * 2, '\0');
    for (std::size_t index = 0; index < size; ++index) {
        text[index * 2] = kDigits[bytes[index] >> 4];
        text[index * 2 + 1] = kDigits[bytes[index] & 0x0F];
    }
    return text;
}

std::string sha256Hex(const void* data, std::size_t size) {
    Sha256 hash;
    hash.update(data, size);
    std::uint8_t digest[32];
    hash.final(digest);
    return toHex(digest, sizeof digest);
}

SignatureCheck verifySignature(const std::vector<std::array<std::uint8_t, 32>>& keys,
                               const std::string& signature, const void* message,
                               std::size_t messageSize) {
    SignatureCheck check;
    if (signature.size() != 129 || signature.back() != '\n') {
        check.error = "the signature file must be 128 hex characters and one newline";
        return check;
    }
    std::uint8_t raw[64];
    for (std::size_t index = 0; index < sizeof raw; ++index) {
        const int high = hexDigit(signature[index * 2]);
        const int low = hexDigit(signature[index * 2 + 1]);
        if (high < 0 || low < 0) {
            check.error = "the signature file is not lowercase hex";
            return check;
        }
        raw[index] = static_cast<std::uint8_t>((high << 4) | low);
    }
    if (keys.empty()) {
        check.error = "no trusted key is configured";
        return check;
    }
    static const std::uint8_t kEmptyMessage = 0;
    const auto* bytes = messageSize == 0
                            ? &kEmptyMessage
                            : static_cast<const std::uint8_t*>(message);
    for (std::size_t index = 0; index < keys.size(); ++index) {
        if (crypto_ed25519_check(raw, keys[index].data(), bytes, messageSize) == 0) {
            check.ok = true;
            check.keyIndex = index;
            return check;
        }
    }
    check.error = "no trusted key verifies this signature";
    return check;
}

}  // namespace update
