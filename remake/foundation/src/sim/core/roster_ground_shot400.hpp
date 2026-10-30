#pragma once
#include "keiichi_ground_shot.hpp"
#include "roster_ground_shot400_schedule.hpp"
#include "roster_ground_shot400_world.hpp"
#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace daybreak {

inline std::uint32_t roster_shot400_key(unsigned character,unsigned weapon,unsigned phase,unsigned frame){
 return character<<24|weapon<<16|phase<<8|frame;
}

// Both state400 and state401 use the same original projectile/effect callback
// ABI. Magazine checks and muzzle transforms remain with the battle host.
inline GroundShotEffects decode_roster_shot_events(
 const RosterShot400Event* first,const RosterShot400Event* last,
 unsigned phase,unsigned frame,std::vector<GroundShotEffects>& requests,int& next_phase){
 GroundShotEffects out;out.attack_calls=0;out.count_attack=false;
 out.callback_first=first;out.callback_last=last;
 out.callback_request_begin=unsigned(requests.size());
 next_phase=-1;
 out.started=phase==0&&frame==0;
 for(auto it=first;it!=last;++it){
  switch(it->kind){
   case RosterShot400Kind::Attachment:
   case RosterShot400Kind::Hand:
   case RosterShot400Kind::World:{
    GroundShotEffects shot;shot.fire=true;shot.bullet_slot=unsigned(it->value);shot.yaw=it->yaw;shot.pitch=it->pitch;
    if(it->kind==RosterShot400Kind::Attachment){shot.origin=GroundShotOrigin::AttachmentZero;shot.attachment_slot=unsigned(it->attachment);}
    else if(it->kind==RosterShot400Kind::Hand)shot.origin=it->attachment?GroundShotOrigin::LeftHand:GroundShotOrigin::RightHand;
    else {shot.origin=GroundShotOrigin::World;shot.origin_height=it->height;}
    requests.push_back(shot);break;
   }
   case RosterShot400Kind::Effect:out.effect=it->value;break;
   case RosterShot400Kind::Voice:out.voice=it->value;break;
   case RosterShot400Kind::AttackCount:++out.attack_calls;break;
   case RosterShot400Kind::NextPhase:next_phase=it->value;break;
   case RosterShot400Kind::NextState:out.next_state=it->value;break;
  }
 }
 out.fire=!requests.empty();out.count_attack=out.attack_calls!=0;
 return out;
}

// Clock helpers may suppress a retained pulse or change its last voice/effect.
// Reconcile those explicit aggregate edits while retaining all earlier callbacks
// and the per-request geometry already amended by the action helper. A helper
// that replaces a volley clears the view and provides its own callback program.
template<class Notify> inline bool replay_roster_shot_callbacks(
 const GroundShotEffects& shot,const std::vector<GroundShotEffects>& requests,
 Notify&& notify){
 if(!shot.callback_first)return false;
 const RosterShot400Event* last_effect=nullptr;const RosterShot400Event* last_voice=nullptr;
 unsigned fire_count=0,attack_count=0;
 for(auto it=shot.callback_first;it!=shot.callback_last;++it){
  switch(it->kind){
   case RosterShot400Kind::Attachment:case RosterShot400Kind::Hand:case RosterShot400Kind::World:++fire_count;break;
   case RosterShot400Kind::Effect:last_effect=it;break;
   case RosterShot400Kind::Voice:last_voice=it;break;
   case RosterShot400Kind::AttackCount:++attack_count;break;
   default:break;
  }
 }
 if(shot.fire&&(shot.callback_request_begin>requests.size()||
     fire_count!=requests.size()-shot.callback_request_begin))return false;
 if(shot.count_attack&&shot.attack_calls!=attack_count)return false;
 unsigned index=shot.callback_request_begin;
 for(auto it=shot.callback_first;it!=shot.callback_last;++it){
  switch(it->kind){
   case RosterShot400Kind::Attachment:case RosterShot400Kind::Hand:case RosterShot400Kind::World:
    if(shot.fire)notify(it->kind,int(index));++index;break;
   case RosterShot400Kind::Effect:
    if(shot.effect>=0)notify(it->kind,it==last_effect?shot.effect:it->value);break;
   case RosterShot400Kind::Voice:
    if(shot.voice>=0)notify(it->kind,it==last_voice?shot.voice:it->value);break;
   case RosterShot400Kind::AttackCount:
    if(shot.count_attack)notify(it->kind,1);break;
   default:break;
  }
 }
 // Scratch-controlled callbacks added after decoding have no table entry.
 if(!last_effect&&shot.effect>=0)notify(RosterShot400Kind::Effect,shot.effect);
 if(!last_voice&&shot.voice>=0)notify(RosterShot400Kind::Voice,shot.voice);
 return true;
}

template<std::size_t N> inline GroundShotEffects advance_roster_shot_schedule(
 const RosterShot400Event (&events)[N],unsigned character,unsigned weapon,
 unsigned phase,unsigned frame,std::vector<GroundShotEffects>& requests,int& next_phase){
 const auto key=roster_shot400_key(character,weapon,phase,frame);
 const auto first=std::lower_bound(std::begin(events),std::end(events),key,
  [](const RosterShot400Event& event,std::uint32_t value){return roster_shot400_key(event.character,event.weapon,event.phase,event.frame)<value;});
 auto last=first;
 while(last!=std::end(events)&&roster_shot400_key(last->character,last->weapon,last->phase,last->frame)==key)++last;
 return decode_roster_shot_events(first,last,phase,frame,requests,next_phase);
}

// The original per-weapon handlers request shots, sounds and phase changes.
inline GroundShotEffects advance_roster_ground_shot400(unsigned character,unsigned weapon,
 unsigned phase,unsigned frame,bool complete,bool grounded,
 std::vector<GroundShotEffects>& requests,int& next_phase,unsigned trigger=0,
 bool boosted=false,float elevation=0){
 if(character<3||character>15||weapon>2||(character>=14&&weapon>1))throw std::invalid_argument("Unsupported roster state400 binding");
 GroundShotEffects out;out.attack_calls=0;out.count_attack=false;
 next_phase=-1;
 if(complete){out.next_state=0;return out;}
 if(!grounded){out.next_state=43;return out;}
 out=boosted?advance_roster_shot_schedule(roster_shot400_boosted_events,character,weapon,phase,frame,requests,next_phase):
  advance_roster_shot_schedule(roster_shot400_events,character,weapon,phase,frame,requests,next_phase);
 apply_roster_shot400_world_geometry(character,weapon,boosted,elevation,requests);
 // 50aea0 case400 reads actor+f8 after its projectile script signals it.
 // Frame0/phase0 clears that word before testing it.
 if(character==5&&weapon==2&&phase<2&&!(phase==0&&frame==0)){
  if(trigger==1)next_phase=2;
  else if(trigger==2)out.next_state=420;
  else if(trigger==3)out.next_state=421;
 }
 return out;
}

}
