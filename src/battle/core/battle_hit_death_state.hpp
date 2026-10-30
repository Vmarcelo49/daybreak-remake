#pragma once
#include <cstdint>
namespace daybreak {
// 0x63ba80: flags from actor's +0x10 record at +0x28.
inline std::uint32_t select_hit_death_state(std::uint8_t flag84,std::uint32_t flags,std::uint32_t requested){
    if(!flag84)return 199;
    if(flags&0x800)return 191;
    switch(requested){
        case 100:case 101:case 200:case 201:return 197;
        case 102:case 202:return 192;
        case 130:case 131:case 230:case 231:return 193;
        default:return 198;
    }
}
}
