#pragma once
#include "battle_steering.hpp"
#include <algorithm>
namespace daybreak {
// State390/391/392 in 438310. Effects/audio and animation-counter advancement
// remain caller-owned. 390 is preparation/hold/release, 391 successful guard,
// 392 the attacker's recoil after being guarded.
struct BattleGuardMotion {
 unsigned state=390,phase=0,frame=0,hold_count=0,contact_flags=0;
 int gauge=1000;
 bool grounded=true,complete=false,button_a=false,button_b=false;
 float speed=0,vertical=0,gravity=0,offset=0;
};
struct BattleGuardStep {int state=-1;int phase=-1;bool clear_contacts=false;};
inline BattleGuardStep advance_battle_guard(BattleGuardMotion& p){
 if(p.complete){if(!p.grounded){p.gravity=.5f;return {43};}return {0,-1,false};}
 if(!p.grounded){p.gravity=.5f;return {p.state==391?103:43};}
 if(p.state==390){
  if(p.phase==1)p.gauge=std::max(0,p.gauge-10);
  bool clear=false;
  if(p.phase==0&&p.frame==0){p.speed=0;p.contact_flags=0;clear=true;}
  if(p.phase==0)approach_battle_offset(p.offset,0.f,20.f);
  if(p.phase==1&&(!p.gauge||!p.button_a||!p.button_b))return {-1,2,false};
  if((p.contact_flags&2)&&p.gauge>0)return {391,-1,true};
  if(p.phase==2)p.speed=std::max(0.f,p.speed-1.f);
  return {-1,-1,clear};
 }
 if(p.state==391||p.state==392){
  if(p.phase==0&&p.frame==0){p.speed=-15.f;p.hold_count=0;}
  if(p.state==391&&p.phase<2&&(p.contact_flags&2))return {391,-1,true};
  if(p.phase==0&&++p.hold_count>20)return {-1,1,false};
  if(p.phase<(p.state==391?3u:2u))p.speed=std::min(0.f,p.speed+1.f);
 }
 return {};
}
}
