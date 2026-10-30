#pragma once
#include <array>
#include <cstdint>
#include <cmath>
namespace daybreak {
// 42e110 calls 4236c0/42e950 on secondary_target. These bytes are cached
// after all slot6/pool scripts and before target selection/movement/contact.
inline std::array<unsigned char,3> battle_melee_voice_flags(unsigned owner,
 int ally_index,std::int32_t target_state,std::uint32_t target_last_owner,
 unsigned target_secondary_target,float target_heading,float target_offset,float heading){
 std::array<unsigned char,3> out{};
 if(target_state>=100&&target_state<300&&target_last_owner!=owner&&ally_index<0){out[0]=1;return out;}
 if(target_secondary_target==owner||ally_index>=0)return out;
 volatile float angle=target_heading+target_offset;angle=angle-heading;
 if(angle< -180.f)angle=angle+360.f;if(angle>180.f)angle=angle-360.f;
 if(std::abs(float(angle))<90.f){out[2]=1;if((target_state>=300&&target_state<380)||target_state>=400)out[1]=1;}
 return out;
}
}
