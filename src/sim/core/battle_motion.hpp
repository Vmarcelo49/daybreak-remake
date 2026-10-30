#pragma once
#include "legacy_trig.hpp"
#include <array>
namespace daybreak {
struct BattleMotionState {
    std::array<float,3> position{},velocity{},applied{},angles{};
    float speed=0;
    std::int32_t gate=0;
    std::uint32_t blocked=0,grounded=0;
};
// 0x4202b0. Vertical movement and target facing remain host responsibilities.
template<class Host> void update_battle_motion(BattleMotionState& s,Host& host){
    if(s.gate!=0)return;
    if(s.blocked){s.velocity={0,0,0};s.grounded=0;return;}
    volatile float heading=s.angles[0]+s.angles[1];heading=heading+s.angles[2];
    volatile float x=legacy_trig(heading,false)*s.speed;
    s.velocity[0]=x;s.applied[0]=x;s.applied[1]=s.velocity[1];
    volatile float z=legacy_trig(heading,true)*s.speed;
    s.velocity[2]=z;s.applied[2]=z;
    host.horizontal(s,std::array<float,3>{{s.applied[0],0,s.applied[2]}});
    host.vertical(s,s.applied[1]);host.face_target(s);
    if(s.position[1]<-1000.f)s.position={{-1000,1000,-1000}};
}
}
