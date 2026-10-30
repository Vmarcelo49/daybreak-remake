#pragma once
#include "battle_input_channel.hpp"
#include "battle_world_motion.hpp"
namespace daybreak {
// Shared by local Runtime and network-driven verification. Control tuning is
// developmental: eight directions, speed 2, gravity .5; buttons not implemented.
// Original character state machines must replace this policy, not the transport.
template<class Wall,class Floor> void update_development_battle_frame(BattleWorld& world,const net::InputChannel::Frame& inputs,Wall& wall,const Floor& floor,unsigned frozen_mask=0){
    for(const auto& input:inputs)if(!net::valid_input(input))throw std::invalid_argument("Invalid battle frame input");
    for(unsigned i=0;i<4;++i){if(frozen_mask&(1u<<i))continue;auto& a=world.actors[i];const int x=(inputs[i].x>0)-(inputs[i].x<0),z=(inputs[i].z>0)-(inputs[i].z<0);
        float offset;std::memcpy(&offset,&a.relationships.heading_offset_bits,4);
        a.motion.speed=(x||z)?2.f:0.f;
        if(x||z){const float desired=float(std::atan2(double(z),double(x))*180/3.141592653589793);a.motion.angles[1]=desired-a.heading-offset;}
        if(a.grounded)a.motion.velocity[1]=0;else a.motion.velocity[1]-=.5f;
        update_world_motion(world,i,wall,floor);
        for(float value:a.position)if(!std::isfinite(value))throw std::runtime_error("Nonfinite battle frame position");
    }
}
}
