#pragma once
// assets/exe_strings.h — reads the original executable's own string tables.
//
// WHY the exe and not a data file: several of the game's user-visible tables are .rdata string
// arrays in DaybreakDX.exe, not assets in daybreakXX.dat. The result titles are the case this
// exists for — a NULL-terminated `const char*` array at VA 0x6b7308 whose 41 entries are the
// earned-title names FUN_00430860 returns (FUN_00430880 picks the index). Reading them from
// the installed exe keeps the game's own text out of this repository, exactly like .X/.cnv,
// and keeps the port honest about where the strings come from.
//
// The reader is a small PE32 mapper: section table -> (VA -> raw offset), which is what turns
// a cited .rdata address into a file position. It rejects anything that is not a PE32 image
// with the named section rather than guessing an offset.
#include <cstdint>
#include <string>
#include <vector>

namespace fnd::assets {

// Reads the NULL-terminated pointer table at `tableVa` and the NUL-terminated Shift-JIS
// strings it points at, converted to UTF-8. Stops at the first null pointer or when `limit`
// entries have been read. Returns false (with a reason) when the image cannot be read, is not
// a PE32 image, or the address is outside every section.
bool readExeStringTable(const std::string& exePath, uint32_t tableVa,
                        std::vector<std::string>& out, std::string& error, int limit = 128);

// Reads `count` bytes at `va` out of the image (the .data byte tables the game indexes, e.g.
// the per-character penalty costume at VA 0x6b72a0). Returns false with a reason when the
// address is outside every section or the range runs past the file.
bool readExeBytes(const std::string& exePath, uint32_t va, size_t count,
                  std::vector<uint8_t>& out, std::string& error);

// Maps a virtual address in a PE32 image to a file offset, without reading the whole image.
// False when the address is in no section.
bool peVaToFileOffset(const std::string& exePath, uint32_t va, uint64_t& offset,
                      std::string& error);

}  // namespace fnd::assets
