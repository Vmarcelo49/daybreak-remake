#pragma once
#include "character_dispatch.hpp"
namespace daybreak {
// Vtable slot7, airborne direction-history branch. Caller handles earlier service updates.
template<class Priority> bool roster_air_dash_admission(unsigned character,unsigned weapon,int state,unsigned command,int& gauge,unsigned flags,int priority,unsigned contact,Priority first,bool airborne=true){
 character_action_dispatch(character,weapon);
 if(command<1||command>4||gauge<=0||!(flags&0x100))return false;
 unsigned target=command==1?20:command==2?27:command==3?24:23;
 if(character==3&&weapon==1&&command==3)target=23; // original4b9e20 uses+b04 for both sides
 bool accepted=priority<=first(target);
 if(command==2&&((character==0&&weapon!=1)||character==15)&&state>299&&state<350&&(contact&1))accepted=true;
 if(command==3||command==4){
  if(character==3&&(priority==19||priority==39)&&(weapon!=1||(contact&0xffff)==0))accepted=true;
  if(character==5&&weapon==1&&(priority==19||priority==39||priority==89)&&(contact&0xffff)==0)accepted=true;
  if(character==6&&weapon==0&&(priority==19||priority==39||priority==98)&&(contact&0xffff)==0)accepted=true;
 }
 if(accepted&&airborne&&character==5&&weapon==1&&state==402&&(command==3||command==4)){if(gauge<500)return false;gauge-=500;}
 return accepted;
}
}
