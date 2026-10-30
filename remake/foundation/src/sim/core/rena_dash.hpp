#pragma once
#include "battle_ground_dash.hpp"
#include "battle_air_dash.hpp"
namespace daybreak {
// 445ee0/44d850/43ded0: ordered direction-history branch before melee.
template<class Priority> int rena_dash_admission(unsigned weapon,int state,unsigned command,bool grounded,int gauge,unsigned flags,int priority,unsigned contact,Priority first){
 if(weapon>2)throw std::invalid_argument("Rena dash weapon");
 if(command<1||command>4||gauge<=0||!(flags&0x100))return -1;
 const bool hit=state>299&&state<350&&(contact&1);
 if(weapon!=2&&command==2&&grounded&&state!=320&&hit)return 28;
 const unsigned target=command==1?20:command==2?27:command==3?24:23;
 return priority<=first(target)||(weapon!=1&&command==2&&hit)?(grounded?int(target):30):-1;
}
inline BattleAirDashStep advance_rena_air_dash(BattleAirDash& s,unsigned weapon){
 if(weapon>2)throw std::invalid_argument("Rena air dash weapon");
 return advance_battle_air_dash(s,weapon==2?11.5f:16.5f,weapon==2?14:11,weapon==2);
}
inline BattleGroundDashTuning rena_ground_dash_tuning(unsigned weapon){
 if(weapon>2)throw std::invalid_argument("Rena dash weapon");
 return {12,weapon==0?17.f:weapon==1?16.5f:30.f,20.f,14.5f,weapon==2?2.5f:.75f,.5f,12.5f,.7f,1.f,true,true,9,weapon==2?5:-1,weapon!=2};
}
}
