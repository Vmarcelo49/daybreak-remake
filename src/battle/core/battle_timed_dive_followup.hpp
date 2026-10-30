#pragma once
#include "battle_timed_dive.hpp"
namespace daybreak {
struct BattleTimedDiveFollowupEffects : BattleReboundMeleeEffects {int camera=-1;};
inline BattleTimedDiveFollowupEffects advance_battle_timed_dive_followup(unsigned state,unsigned weapon,KeiichiAirMelee& air,KeiichiAttack300& s,const KeiichiAttack300Input& in){
 character_action_dispatch(7,weapon);
 if(state!=334&&state!=339)throw std::invalid_argument("Unknown timed dive followup");
 BattleTimedDiveFollowupEffects out;
 if(state==339){
  if(in.grounded&&air.vertical<=0){out.next_state=333;air.vertical=0;return out;}
  air.vertical-=air.gravity;return out;
 }
 if(s.phase==0&&s.frame==0){
  s.speed=air.vertical=s.offset=0;out.clear_contact=out.reset_capacity=out.initialize=true;
 }
 out.camera=2;
 if(s.phase==0&&s.frame==11){out.voice=0;out.voice_argument=10;}
 if(s.phase==0&&s.frame==12){s.speed=-6;air.vertical=10;}
 if(s.phase==1||(s.phase==0&&s.frame>12))air.vertical-=air.gravity;
 if(in.grounded&&air.vertical<0){out.next_state=333;air.vertical=0;return out;}
 if(s.phase==1&&s.frame>10){out.next_state=43;return out;}
 return out;
}
}
