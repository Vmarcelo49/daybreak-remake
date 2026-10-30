#pragma once
namespace daybreak {
// Common melee branch in45f4d0/467d70/456030. Earlier dash/chord/guard/
// shooting branches retain priority in the host. Both air branches resolve320.
template<class Priority> int mion_melee_admission(int state,bool grounded,int held,int released,
 int x,int z,unsigned flags,int priority,bool special,bool ready,unsigned contact,Priority first){
 if(held!=3&&!(released>0&&released<3))return -1;
 const bool normal=flags&0x100,boosted=special&&ready&&state>299&&state<350;
 const bool enabled=normal||(boosted&&contact!=0);
 auto gate=[&](int next){return priority<=first(next);};
 if(!grounded)return enabled&&(gate(320)||(boosted&&state!=320))?320:-1;
 if(normal){
  if(state==20&&x&&gate(331))return 331;
  if(state==20&&gate(330))return 330;
  if((state==23||state==24)&&z<0&&gate(330))return 330;
  if((state==23||state==24)&&gate(331))return 331;
 }
 if(z<0&&enabled&&(gate(310)||(boosted&&state!=310)))return 310;
 if(x&&enabled&&(gate(312)||(boosted&&state!=312)))return 312;
 const bool ordinary_combo=state==300||state==301||state==302||state==340||state==341;
 if((state==329||state==333||state==44)&&enabled&&(gate(340)||(boosted&&!ordinary_combo)))return 340;
 if(state==340&&normal&&gate(341))return 341;
 if(state==300&&normal&&gate(301))return 301;
 if(enabled&&(gate(300)||(boosted&&!ordinary_combo&&state!=320)))return 300;
 return -1;
}
}
