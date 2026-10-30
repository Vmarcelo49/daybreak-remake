#pragma once
#include "keiichi_attack300.hpp"
namespace daybreak {
struct KeiichiSpecialStrike {unsigned held=0;bool hold_clock=false;int magazine_gate=-1;bool phase2_steer=false;unsigned burst_ticks=0;float hover_spin=0;};
//46a190/473610/47b940 state370. magazine_gate=-1 means the handler returned
//before434b30/434bd0, so prior flags must survive that frame.
inline KeiichiAttack300Effects advance_keiichi_special_strike(KeiichiSpecialStrike& s,unsigned weapon,KeiichiAttack300& action,const KeiichiAttack300Input& in){
 KeiichiAttack300Effects e;s.hold_clock=false;s.magazine_gate=-1;
 if(in.animation_complete){e.next_state=0;return e;}
 if(!in.grounded){e.next_state=43;return e;}
 unsigned contact=in.contact;const auto frame=unsigned(action.frame);
 if(action.phase==0){
  if(frame<14){volatile float v=action.speed-1.f;action.speed=v;}
  if(frame>23){volatile float v=action.speed-.5f;action.speed=v;}
  if(action.speed<0)action.speed=0;
  if(frame<14)approach_battle_offset(action.offset,0,15);
  if(frame<32)approach_battle_offset(action.offset,0,5);
 }
 if(frame==0){s.held=0;e.initialize=e.clear_contact=true;contact=0;}
 if(frame==19){e.effect=62;e.voice=weapon==1?32:33;e.voice_argument=20;}
 if(frame==(weapon==1?10u:13u)&&s.held<5){++s.held;s.hold_clock=true;return e;}
 if(frame==14){action.movement_angle=0;action.speed=35;}
 if(frame==23)action.speed=10;
 if(contact&2){e.next_state=392;e.clear_contact=true;return e;}
 s.magazine_gate=frame>=16&&frame<=29?1:0;
 return e;
}
}
