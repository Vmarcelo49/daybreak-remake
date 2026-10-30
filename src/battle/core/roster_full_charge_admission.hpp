#pragma once
#include <cstdint>
namespace daybreak {
// Original slot7 full-charge release. Rena's first two weapons use360/370;
//350 is their awakened melee chord, not their grounded full-charge shot.
inline unsigned roster_full_charge_state(unsigned character,unsigned weapon,bool grounded){
 return character==0&&weapon<2?(grounded?360u:370u):(grounded?350u:360u);
}
template<class Priority> int roster_full_charge_admission(unsigned character,unsigned weapon,
 int current,bool grounded,int release,int stage,int rounds,int priority,Priority first){
 if(release<=0||stage!=2||rounds<=0||(current>=100&&current<=299))return -1;
 const auto state=roster_full_charge_state(character,weapon,grounded);
 return priority<=first(state)?int(state):-1;
}
inline int roster_awakened_strike_state(unsigned character,unsigned weapon){
 if(character==0)return weapon<2?350:-1;
 return 370;
}
}
