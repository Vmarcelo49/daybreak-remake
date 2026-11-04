#pragma once
// update/release_keys.h — the game's trusted release keys.
//
// The owner's 32-byte Ed25519 public half (docs/RELEASE-CHECKLIST.md §9.1). The updater
// takes this list as a parameter and never reads a key from a file or an environment
// variable, so nothing on a player's machine can widen the trust list
// (docs/AUTO-UPDATE.md).
//
// A release build refuses to compile with an empty list, because shipping without a key
// would mean no player could ever update.
#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace update {

inline constexpr std::array<std::array<std::uint8_t, 32>, 1> kReleaseKeys = {{
    {0xd6, 0xde, 0xda, 0x1e, 0x7f, 0xd6, 0xec, 0x09, 0x89, 0xa4, 0xa5, 0xdf, 0x0b, 0x17,
     0xea, 0xed, 0xa6, 0x16, 0x66, 0x68, 0x0a, 0xbe, 0x97, 0x26, 0x04, 0x35, 0x20, 0x63,
     0x4a, 0xfb, 0x47, 0x9f},
}};

#if defined(DAYBREAK_RELEASE_BUILD) && defined(DAYBREAK_UPDATE_TEST_BUILD)
#error "DAYBREAK_UPDATE_TEST_BUILD trusts a throwaway key and must never be a release build"
#endif

#if defined(DAYBREAK_RELEASE_BUILD)
static_assert(kReleaseKeys.size() > 0,
              "a release build needs at least one trusted release key in "
              "src/update/release_keys.h (docs/RELEASE-CHECKLIST.md §9.1)");
#endif

inline std::vector<std::array<std::uint8_t, 32>> releaseKeys() {
    return std::vector<std::array<std::uint8_t, 32>>(kReleaseKeys.begin(),
                                                     kReleaseKeys.end());
}

}  // namespace update
