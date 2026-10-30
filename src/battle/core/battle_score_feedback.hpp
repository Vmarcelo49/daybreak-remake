#pragma once
#include <array>
#include <cstdint>
#include <stdexcept>
namespace daybreak {
struct BattleScoreFeedback {
    std::array<std::uint32_t,2> value{},timer{};
    // 0x6431d0, valid display labels 0/1. Invalid labels in original write
    // outside these globals; reject them instead of reproducing corruption.
    void changed(std::uint8_t label,std::uint32_t delta){
        if(label>=2)throw std::out_of_range("Battle score feedback label");
        value[label]=delta;timer[label]=60;
    }
};
}
