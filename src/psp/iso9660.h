#pragma once
// psp/iso9660.h — read one file out of a PSP UMD image without mounting it.
//
// The extractor has to open the player's own ISO and nothing else: mounting would need a
// platform driver on Windows, and the only thing needed is one file inside
// PSP_GAME/USRDIR/_pack, so the primary volume descriptor plus a directory walk is enough.
// Joliet and Rock Ridge are ignored on purpose — the game ships uppercase names, and a
// second namespace would only give a file two possible spellings.
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

namespace psp {

class IsoImage {
public:
    // Throws std::runtime_error with a plain message when `path` is not an ISO9660 image
    // or has no root directory: the caller shows it to the player verbatim.
    static IsoImage open(const std::string& path);

    // The extent and byte length of `path` inside the image ("A/B/C.BIN", leading '/'
    // optional, case folded, ";" version suffix ignored). False when it is not there.
    bool find(const std::string& path, std::uint64_t& offset, std::uint64_t& size) const;

    // Reads `size` bytes at `offset` inside the file `path`, seeking the image once.
    bool read(const std::string& path, std::uint64_t offset, std::uint64_t size,
              std::vector<std::uint8_t>& out) const;

    const std::string& path() const { return path_; }

private:
    struct Record {
        std::uint64_t offset = 0;
        std::uint64_t size = 0;
        bool          directory = false;
    };
    bool children(const Record& directory, std::vector<std::pair<std::string, Record>>& out) const;
    bool lookup(const std::string& name, Record& out) const;
    bool seekRead(std::uint64_t offset, std::uint64_t size, std::vector<std::uint8_t>& out) const;

    mutable std::ifstream file_;
    std::string           path_;
    Record                root_;
};

}  // namespace psp
