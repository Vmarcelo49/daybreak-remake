#pragma once
#include <array>
#include <cstdint>
#include <cstring>
#include <vector>
#include <stdexcept>
namespace daybreak {
// First 21 little-endian words read by 0x4011f0 from env.dat.
struct StageEnvironment {
    float fog_start=0,fog_end=0;std::uint32_t fog_color=0;
    std::array<std::uint32_t,4> settings{};
    std::array<std::array<float,3>,4> positions{};
    // 4011f0 stores env words5..8 at stage+34..40; 421bd0 uses this rectangle.
    std::array<std::int32_t,4> respawn_bounds()const{
        std::array<std::int32_t,4> out{};std::memcpy(out.data(),settings.data(),16);return out;
    }
    static StageEnvironment decode(const std::vector<std::uint8_t>& bytes){
        if(bytes.size()<84)throw std::runtime_error("Truncated stage environment");
        auto word=[&](unsigned index){std::uint32_t v=0;for(unsigned i=0;i<4;++i)v|=std::uint32_t(bytes[index*4+i])<<(i*8);return v;};
        auto number=[&](unsigned index){auto v=word(index);std::int32_t signed_value;std::memcpy(&signed_value,&v,4);return static_cast<float>(signed_value);};
        StageEnvironment out;out.fog_start=number(0);out.fog_end=number(1);out.fog_color=((word(2)&255)<<16)|((word(3)&255)<<8)|(word(4)&255);
        for(unsigned i=0;i<4;++i){out.settings[i]=word(5+i);for(unsigned j=0;j<3;++j)out.positions[i][j]=number(9+i*3+j);}return out;
    }
};
}
