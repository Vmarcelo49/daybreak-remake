#pragma once
#include <array>
#include <cmath>
namespace daybreak {
struct BattleMeleeVoice {int id,argument;};
// Repeated close-target voice branch: +aec3, +aebe, +aeb9, in that order.
inline BattleMeleeVoice battle_melee_voice(int ordinary,double distance_squared,float offset,const std::array<unsigned char,3>& flags){
 if(distance_squared<90000.&&std::abs(offset)<30.f)
  for(unsigned i=0;i<3;++i)if(flags[i]==1)return {i==0?0:i==1?15:5,12};
 return {ordinary,10};
}
}
