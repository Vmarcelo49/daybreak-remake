#pragma once
// frontend/result_title.h — the names of the earned titles. The core picks the title
// (FUN_00430880, battle_awards); the report draws its name from the 41-entry string table at
// VA 0x6b7308 (FUN_00430860 returns one, FUN_0063a740:64-85 draws row i).
#include <cstdint>
#include <string>
#include <vector>

namespace gameplay {

// The title the original grants for the "penalty game" (index 0x28): every branch rolls for it
// with a small percentage, and earning it sets a session flag (FUN_00635d40:377-380).
inline constexpr int kResultTitlePenalty = 40;
inline constexpr int kResultTitleCount = 41;

// The recovered name table (VA 0x6b7308, 41 entries). Loaded from the installed exe so the
// game's own text stays out of this repository (assets/exe_strings.h).
struct ResultTitleTable {
    std::vector<std::string> titles;
    bool loaded() const { return titles.size() == (size_t)kResultTitleCount; }
    const char* text(int index) const {
        return index >= 0 && index < (int)titles.size() ? titles[(size_t)index].c_str() : "";
    }
};

// `exePath` is the installed DaybreakDX.exe.
bool loadResultTitles(const std::string& exePath, ResultTitleTable& out, std::string& error);

}  // namespace gameplay
