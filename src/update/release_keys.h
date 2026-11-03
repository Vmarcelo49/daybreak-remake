#pragma once
// update/release_keys.h — the game's trusted release keys.
//
// The owner generates the real key (docs/RELEASE-CHECKLIST.md §9.1) and pastes its 32-byte
// Ed25519 public half here. The updater takes this list as a parameter and never reads a
// key from a file or an environment variable, so nothing on a player's machine can widen
// the trust list (docs/AUTO-UPDATE.md).
//
// Until the key exists the list is empty: every check reports "untrusted", and a release
// build refuses to compile, because shipping without a key would mean no player could ever
// update.
#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace update {

inline constexpr std::array<std::array<std::uint8_t, 32>, 0> kReleaseKeys = {
    // {0x00, 0x00, ...},
};

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
