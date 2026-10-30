#pragma once
#include "character_dispatch.hpp"
namespace daybreak {
// Melee branch of445ee0/44d850/43ded0. The caller preserves earlier chord,
// dash, guard and shooting branches. DAT supplies each target state's limit.
template<class Priority> int rena_melee_admission(unsigned weapon,int state,int phase,bool grounded,int held,int released,int x,int z,unsigned flags,int priority,bool special,bool ready,unsigned contact,Priority first){
 character_action_dispatch(0,weapon);
 if(held!=3&&!(released>0&&released<3))return -1;
 const bool normal=flags&0x100,boosted=special&&ready&&state>299&&state<350;
 const bool enabled=normal||(boosted&&contact!=0);
 auto gate=[&](int next){return priority<=first(next);};
 if(!grounded){
  if(weapon!=2&&state==30&&phase<2&&normal&&gate(332))return 332;
  return enabled&&(gate(320)||(boosted&&state!=320))?320:-1;
 }
 if(normal){
  if(state==20&&x&&gate(331))return 331;
  if(state==20&&gate(330))return 330;
  if((state==23||state==24)&&z<0&&gate(330))return 330;
  if((state==23||state==24)&&gate(331))return 331;
 }
 if(z<0&&(weapon!=2||state!=310)&&enabled&&(gate(310)||(boosted&&state!=310)))return 310;
 if(x&&(weapon!=2||state!=311)&&enabled&&(gate(311)||(boosted&&state!=311)))return 311;
 const bool combo=state==300||state==301||state==302||state==340||state==341;
 if(weapon!=2){
  if((state==329||state==333||state==44)&&enabled&&(gate(340)||(boosted&&!combo)))return 340;
  if(weapon==0&&state==340&&normal&&gate(341))return 341;
  if(state==300&&normal&&gate(301))return 301;
  if(weapon==0&&state==301&&normal&&gate(302))return 302;
 }
 if((weapon!=2||state!=300)&&enabled&&(gate(300)||(boosted&&!combo&&state!=320)))return 300;
 return -1;
}
}
