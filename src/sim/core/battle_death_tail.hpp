#pragma once
#include <cstdint>
namespace daybreak {
struct BattleDeathTail {std::uint32_t health=0;float offset=0;std::uint32_t transition=0;};
// 0x638ef6..0x638f84. Finite, bounded angles required: the original loops
// can fail to make progress for enormous floats or infinities.
inline void finish_hit_death(BattleDeathTail& s,std::uint32_t mode,float heading,float impact_heading){
    s.health=mode==2?0:1;s.transition=1;
    volatile float difference=heading-impact_heading;
    volatile float offset=-difference;
    while(offset>180.f)offset=offset-360.f;
    while(offset< -180.f)offset=offset+360.f;
    s.offset=offset;
}
}
