#pragma once
#include "character_dispatch.hpp"

namespace daybreak {
// Original slot-7 input functions: the grounded 20/23/24 melee branch shares
// its priority order. Character4 weapons0/1 select 340 through 340.a;
// character14 weapon0 selects 330 through that same 340.a limit.
template<class Priority>
int roster_ground_dash_melee_admission(unsigned character,unsigned weapon,
 int state,bool grounded,int held,int released,int x,int z,unsigned flags,
 int current_priority,Priority first){
 character_action_dispatch(character,weapon);
 if(!grounded||!(flags&0x100)||!(held==3||(released>0&&released<3)))return -1;
 const bool alternate=(character==4&&weapon<2)||(character==14&&weapon==0);
 const bool gate330=current_priority<=first(alternate?340:330);
 const bool gate331=current_priority<=first(331);
 if(state==20){
  if(x&&gate331)return 331;
  if(gate330)return character==4&&weapon<2?340:330;
 }
 if(state==23||state==24){
  if(z<0&&gate330)return character==4&&weapon<2?340:330;
  if(gate331)return 331;
 }
 return -1;
}
}
