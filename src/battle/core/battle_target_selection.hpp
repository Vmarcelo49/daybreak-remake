#pragma once
#include "battle_world.hpp"
namespace daybreak {
struct BattleTargetAvailability {bool changed=false,restricted=false;unsigned paired_actor=~0u;}; // aecb,aecc,aed0
struct BattleTargetSelection {
 int ally_index=-1,cooldown=0;unsigned held=0,joint_ticks=0;
 bool alternate_sound=false;int sound=-1;
};
// 41f580 selection conditions;421e30/421f30 mutations and4201a0 cooldown.
// Caller clears transient changed flags only after ALL actors have selected targets.
inline void advance_battle_target_acquired(BattleWorld& world,unsigned slot,BattleTargetSelection& state,unsigned acquired_held,const std::array<BattleTargetAvailability,4>& availability={}){
 auto& r=world.actors.at(slot).relationships;state.sound=-1;state.held=acquired_held;
 if(state.held==30&&state.cooldown==0&&!r.allies.empty()){
  state.ally_index=0;state.cooldown=15;r.target=r.secondary_target=r.allies[0];state.joint_ticks=0;state.sound=13;
 }
 const bool enemy_changed=!r.opponents.empty()&&state.ally_index<0&&availability.at(r.opponents.at(r.target_index)).changed;
 const bool ally_changed=state.ally_index>=0&&!r.allies.empty()&&availability.at(r.allies[0]).changed;
 const bool paired=availability.at(r.secondary_target).restricted&&r.secondary_target==availability.at(slot).paired_actor;
 if((enemy_changed||ally_changed||paired||(state.held==1&&state.cooldown==0))&&!r.opponents.empty()){
  state.ally_index=-1;auto next=(r.target_index+1u)%r.opponents.size();
  unsigned scanned=0;
  while(availability.at(r.opponents[next]).restricted&&availability.at(r.opponents[next]).paired_actor==slot){
   next=(next+1u)%r.opponents.size();if(++scanned==r.opponents.size())break;
  }
  // Malformed all-excluded rosters would loop forever in the original; retain current target.
  if(scanned==r.opponents.size())next=r.target_index;
  if(next!=r.target_index){r.target_index=unsigned(next);r.target=r.secondary_target=r.opponents[next];state.cooldown=15;
   const bool joint=!r.allies.empty()&&world.actors.at(r.allies[0]).relationships.secondary_target==r.secondary_target;
   state.joint_ticks=joint?180:0;state.sound=joint?(state.alternate_sound?15:14):13;
  }
 }
 if(!r.allies.empty()&&world.actors.at(r.allies[0]).relationships.secondary_target==r.secondary_target)state.joint_ticks=180;
 else if(state.joint_ticks)--state.joint_ticks;
}
// Retained scalar API includes its standalone4201a0 cooldown step. Production
// uses acquired counters and performs that ALL-actor step after41f580 visits.
inline void advance_battle_target(BattleWorld& world,unsigned slot,BattleTargetSelection& state,bool button,const std::array<BattleTargetAvailability,4>& availability={},int direct_held=-1){
 const unsigned held=direct_held>=0?unsigned(direct_held):button?state.held+1:0;
 advance_battle_target_acquired(world,slot,state,held,availability);
 if(state.cooldown>0)--state.cooldown;
}
}
