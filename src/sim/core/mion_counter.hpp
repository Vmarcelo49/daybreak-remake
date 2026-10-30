#pragma once
#include "battle_contact_ledger.hpp"
#include "battle_steering.hpp"
#include "battle_throw.hpp"
namespace daybreak {
// Shared370/371 in Mion4582a0/461810/44fa10. Clocks are advanced by the caller
// only if neither next_state nor next_phase is requested.
struct MionCounterMotion {
 unsigned state=370,phase=0,frame=0;
 float speed=0,vertical=0,gravity=0,offset=0,movement_angle=0;
 unsigned invincible=0,counter_e8=0,counter_f8=0;bool activated=false;
 int camera=-1;
};
struct MionCounterStep {int next_state=-1,next_phase=-1;};
inline bool accepts_mion_counter(unsigned melee,unsigned shoot,bool active,bool grounded,unsigned flags,int priority,int required){
 return melee>=1&&melee<=2&&shoot>=1&&shoot<=2&&active&&grounded&&(flags&0x100)&&priority<=required;
}
template<class Host> MionCounterStep advance_mion_counter(MionCounterMotion& s,BattleContactLedger& contacts,bool complete,bool grounded,Host& host){
 MionCounterStep step;
 if(complete){step.next_state=0;return step;}
 if(s.state==370){
  if(!grounded){s.vertical=0;s.gravity=.5f;step.next_state=43;return step;}
  if(s.phase==0){
   if(s.frame==0){
    host.voice(1,-1,10,0);approach_battle_offset(s.offset,0,180);s.movement_angle=0;
    contacts.clear_flags();contacts.set_capacity(0);s.activated=true;host.statistics();
    s.counter_e8=s.counter_f8=0;s.speed=0;
   }
   if(s.frame==9)host.sound(198);
  }
  if(s.phase==1){
   contacts.set_capacity(0);
   if((contacts.combined()&1)&&host.capture()){
    s.invincible=30;contacts.clear_flags();step.next_state=371;return step;
   }
   if(contacts.combined()&2){host.sound(51);host.spark();contacts.clear_flags();host.sound(199);contacts.set_capacity(1);}
   if(s.frame>60){step.next_phase=2;return step;}
  }
 }else if(s.state==371){
  s.invincible=30;
  if(s.frame==20){host.voice(39,0,20,0);host.sound(65);host.release(BattleThrowRelease{115,198,3750,1,0,2500,1500});}
  s.camera=4;
 }else throw std::invalid_argument("Unsupported Mion counter state");
 return step;
}
}
