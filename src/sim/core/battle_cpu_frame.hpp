#pragma once
#include "keiichi_cpu.hpp"
#include "battle_input_channel.hpp"
namespace daybreak {
struct BattleCpuFrame {std::array<bool,4> enabled{};std::array<KeiichiCpuInput,4> slots{};};
// Level bits serve movement/guard handlers only. Admission must use the original
// counters alongside this view: release1 can coexist with held4 or held1.
inline net::Input cpu_input_levels(const KeiichiCpuInput& in){
 //After native disconnect,278/27c can retain HUMAN axis ages until slot5
 //overwrites them. The level carrier stores direction; bodies read raw ages.
 if(in.dash<0||in.dash>4||in.target<0)throw std::invalid_argument("Invalid CPU input");
 for(int v:in.held)if(v<0)throw std::invalid_argument("Negative CPU hold");
 for(int v:in.released)if(v<0)throw std::invalid_argument("Negative CPU release");
 const bool jump=in.held[0]!=0,melee=in.held[1]!=0,shoot=in.held[2]!=0;
 return {unsigned(melee)|(unsigned(jump)<<1)|(unsigned(jump&&melee)<<2)|(unsigned(in.target!=0)<<3)|(unsigned(shoot)<<4)|(unsigned(in.auxiliary[2]==1)<<5),std::int16_t((in.x>0)-(in.x<0)),std::int16_t((in.z>0)-(in.z<0))};
}
}
