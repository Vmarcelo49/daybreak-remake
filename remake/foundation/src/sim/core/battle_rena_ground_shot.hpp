#pragma once
#include "battle_steering.hpp"
#include "battle_random.hpp"
#include "character_dispatch.hpp"
#include "legacy_trig.hpp"
#include <algorithm>
#include <vector>
namespace daybreak {
enum class RenaShotEventKind {activate,melee_statistics,shot_statistics,model,sound,voice,attachment_projectile,world_projectile,clear_contact,contact_capacity,strike};
struct RenaShotEvent {
 RenaShotEventKind kind;int id=0,slot=0;std::array<float,3> position{};float yaw=0,pitch=0;
 // The host resolves this predicate at the ordered voice call. A preceding
 // projectile request can consume rounds before the original reads+6dc.
 bool voice_current_rounds=false;int voice_other=-1;
};
struct RenaGroundShotMotion {int phase=0,frame=0,pitch=0;float speed=0,offset=0,movement=0,gravity=0;};
struct RenaGroundShotInput {bool complete=false,grounded=true,special=false;int rounds=0;float elevation=0,heading=0;std::array<float,3> position{};};
struct RenaGroundShotEffects {int next_state=-1;std::vector<RenaShotEvent> events;};
// State400 body after the common update prelude (model slots0/1 and strike off).
// Ordered requests are intentional: weapon2 counts ten secondary shots but
// does not count its leading attachment request; weapon1 can request two
// projectiles for one shot-statistics call. Host performs actual magazine
// admission and resource/attachment resolution at each projectile request.
template<class OnEvent> inline RenaGroundShotEffects advance_rena_ground_shot(unsigned weapon,RenaGroundShotMotion& s,const RenaGroundShotInput& in,BattleRandom& random,OnEvent&& on_event){
 character_action_dispatch(0,weapon);RenaGroundShotEffects out;
 if(in.complete){out.next_state=0;return out;}
 if(!in.grounded){out.next_state=43;s.gravity=.5f;return out;}
 // Services execute at their original statement, including voice RNG before
 // the scattered shots. Retain the event list for diagnostics as well.
 auto publish=[&](RenaShotEvent e){out.events.push_back(e);on_event(e,s);};
 auto emit=[&](RenaShotEventKind kind,int id=0,int slot=0){publish({kind,id,slot});};
 auto attachment=[&](int bullet,float pitch=0){RenaShotEvent e{RenaShotEventKind::attachment_projectile,bullet,0};e.pitch=pitch;publish(e);};
 auto round_voice=[&](int other){RenaShotEvent e{RenaShotEventKind::voice,in.rounds==1?30:other,10};e.voice_current_rounds=true;e.voice_other=other;publish(e);};
 const bool first=s.phase==0&&s.frame==0;
 if(first){emit(RenaShotEventKind::activate);if(weapon==1)emit(RenaShotEventKind::melee_statistics);}
 if(weapon==0){
  if(s.frame>11){emit(RenaShotEventKind::model,-1,0);emit(RenaShotEventKind::model,-1,1);}
  if(s.frame<12)approach_battle_offset(s.offset,0,20);
  if(s.phase==0)s.speed=std::max(0.f,s.speed-.5f);
  if(s.frame==12){
   emit(RenaShotEventKind::sound,70);s.pitch=std::clamp(int(in.elevation),-30,30);
   emit(RenaShotEventKind::shot_statistics);round_voice(27);
   attachment(in.special?6:0,float(s.pitch));
  }
 }else if(weapon==1){
  if(s.frame<15)approach_battle_offset(s.offset,0,20);
  if(s.phase==0){
   if(s.frame==0){s.movement=0;emit(RenaShotEventKind::clear_contact);emit(RenaShotEventKind::contact_capacity,1);}
   approach_battle_offset(s.offset,0,15);s.speed=std::max(0.f,s.speed-.5f);
  }
  if(s.frame==7)s.speed=45;
  if(s.frame==15){emit(RenaShotEventKind::sound,67);emit(RenaShotEventKind::voice,29,10);s.speed=0;}
  if(s.frame==18){emit(RenaShotEventKind::sound,77);emit(RenaShotEventKind::shot_statistics);if(in.special){attachment(0);attachment(9);}else attachment(6);}
  emit(RenaShotEventKind::strike,s.frame>=8&&s.frame<=18);
 }else{
  if(first){emit(RenaShotEventKind::clear_contact);emit(RenaShotEventKind::contact_capacity,1);}
  if(s.frame<20)approach_battle_offset_preserving_movement(s.offset,s.movement,10);
  if(s.phase==0)s.speed=std::max(0.f,s.speed-2.5f);
  if(s.phase==1){
   if(s.frame==0)s.speed=0;
   if(s.frame==25){s.speed=30;s.movement=0;}
   if(s.frame==35){
    s.speed=0;emit(RenaShotEventKind::sound,170);attachment(in.special?2:0);round_voice(29);
    for(unsigned i=0;i<10;++i){
     emit(RenaShotEventKind::shot_statistics);
     const float pitch=float(random.next()%30u)+20.f;
     volatile float facing=in.heading+s.offset;facing=facing+90.f;
     const float yaw=facing-float(random.next()%180u);
     volatile float z=legacy_trig(in.heading,true)*200.f;z=z+in.position[2];
     volatile float y=in.position[1]+30.f;
     volatile float x=legacy_trig(in.heading,false)*200.f;x=x+in.position[0];
     publish({RenaShotEventKind::world_projectile,in.special?3:1,0,{x,y,z},yaw,pitch});
    }
   }
  }
 }
 return out;
}
inline RenaGroundShotEffects advance_rena_ground_shot(unsigned weapon,RenaGroundShotMotion& s,const RenaGroundShotInput& in,BattleRandom& random){
 return advance_rena_ground_shot(weapon,s,in,random,[](const RenaShotEvent&,const RenaGroundShotMotion&){});
}
}
