#pragma once
#include <array>
#include <cstdint>
namespace daybreak {
using BattleVector=std::array<float,3>;
struct BattleHorizontalState {BattleVector position{};float collision_distance=0;std::uint8_t collided=0;};
struct BattleCollisionResult {bool hit=false;float distance=10000;BattleVector correction{},remainder{};};
// 0x42cb50. Host owns the original length test and collision geometry.
template<class Host> void move_battle_horizontal(BattleHorizontalState& s,const BattleVector& motion,Host& host){
    if(!host.has_motion(motion))return;
    s.collided=0;
    const auto first=host.collide(s.position,motion,10000.f);
    s.collision_distance=first.distance;
    if(!first.hit){s.position[0]+=motion[0];s.position[2]+=motion[2];return;}
    for(unsigned i=0;i<3;++i)s.position[i]+=first.correction[i];
    s.collided=0;
    const auto second=host.collide(s.position,first.remainder,10000.f);
    if(second.hit){for(unsigned i=0;i<3;++i)s.position[i]+=second.correction[i];}
    else{s.position[0]+=first.remainder[0];s.position[2]+=first.remainder[2];}
    // Original keeps first distance even after the second collision query.
    s.collided=1;
}
}
