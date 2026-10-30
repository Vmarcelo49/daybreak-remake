#pragma once
#include "battle_hit_status.hpp"
#include <vector>
namespace daybreak {
// Original42e110's presentation calls, after body/pool scripts and before
//41f580/movement. Positions use the cached420880 head/spine world points.
struct BattleStatusVisualEvent{char kind='P';unsigned id=0;std::array<float,3> position{};};
struct BattleStatusVisualResult{BattleStatusTickEffects effects{};std::vector<BattleStatusVisualEvent> events;};
inline bool battle_status_reaction(unsigned state){return state==106||state==107||state==108||state==206;}
inline BattleStatusVisualResult advance_battle_status_visuals(BattleHitStatus& status,unsigned state,unsigned frame,std::uint32_t& health,BattleRandom& random,const std::array<float,3>& head,const std::array<float,3>& spine,bool trace_random=false){
 BattleStatusVisualResult result;
 struct Observer{
  BattleStatusVisualResult& out;unsigned state,frame;const std::array<float,3>& head;const std::array<float,3>& spine;bool trace;
  void random(unsigned value){if(trace)out.events.push_back({'G',value,{}});}
  void sound(unsigned id){out.events.push_back({'S',id,{}});}
  void particle(unsigned id,float x,float y,float z){out.events.push_back({'P',id,{x,y,z}});}
  void reaction(BattleRandom& rng){
   if(!battle_status_reaction(state))return;
   if(damage_signed(frame)%7==0){
    const auto rz=rng.next();random(rz);volatile float z=float(rz%60)+spine[2];z=z-30.f;
    const auto ry=rng.next();random(ry);volatile float y=spine[1]-float(ry%80);
    const auto rx=rng.next();random(rx);volatile float x=float(rx%60)+spine[0];x=x-30.f;
    particle(380,x,y,z);
   }
   if(damage_signed(frame)%60==0)sound(36);
  }
  void visual(const BattleStatusPulse& p){
   if(p.slot==6){volatile float y=spine[1]+50.f;particle(p.visual_id,spine[0],y,spine[2]);return;}
   volatile float x=float(p.random_words[0]%100)+head[0];x=x-50.f;
   volatile float y=head[1]+50.f;y=y+float(p.random_words[2]%60);y=y-50.f;
   volatile float z=float(p.random_words[1]%100)+head[2];z=z-50.f;
   particle(p.visual_id,x,y,z);
  }
 } observer{result,state,frame,head,spine,trace_random};
 result.effects=advance_battle_hit_status_observed(status,state,health,random,observer);return result;
}
}
