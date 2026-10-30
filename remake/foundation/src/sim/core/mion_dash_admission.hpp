#pragma once
namespace daybreak {
template<class Priority> int mion_dash_admission(unsigned weapon,int state,int command,bool grounded,int gauge,
 unsigned flags,int priority,unsigned contact,Priority first){
 if(command<1||command>4||gauge<=0||!(flags&0x100))return -1;
 if(weapon==1&&command==2&&grounded&&state>299&&state<350&&state!=320&&(contact&1))return 28;
 const int target=command==1?20:command==2?27:command==3?24:23;
 return priority<=first(target)?(grounded?target:30):-1;
}
}
