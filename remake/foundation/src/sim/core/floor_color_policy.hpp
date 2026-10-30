#pragma once
#include <cstdint>
namespace daybreak {
struct FloorColorFlags {std::uint8_t red_low_seen=0,fast_crossing=0;};
// 0x42cf67..0x42d053. Inputs are already packed D3DCOLOR channels of
// the triangle's FIRST vertex. Green/alpha and other vertices are not tested.
inline bool accept_floor_color(bool has_color,std::uint8_t red,std::uint8_t blue,float ray_distance,float velocity,FloorColorFlags& flags){
    if(!has_color)return true;
    if(red<128){
        flags.red_low_seen=1;
        volatile float distance=ray_distance-1.f;distance=distance-50.f;
        volatile float moved=distance+velocity;
        if(distance>0 && moved<0 && blue<128 && velocity<-5.f)flags.fast_crossing=1;
    }
    return blue>=128;
}
}
