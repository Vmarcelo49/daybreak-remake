#pragma once
#include "battle_steering.hpp"
#include "battle_melee_voice.hpp"
#include <array>
#include <cmath>
#include <cstdint>
namespace daybreak {
// Keiichi weapon0, 46a190 state300. +e8/+ec are persistent handler scratch words.
struct KeiichiAttack300 {
 int phase=0,frame=0,moving=0,contact_seen=0;
 float speed=0,offset=0,movement_angle=0;
 float vertical=0,gravity=.5f; // Original actor +40/+58, used by airborne follow-through.
};
struct KeiichiAttack300Input {
 bool animation_complete=false,grounded=true;
 double distance_squared=0;
 unsigned contact=0;
 std::array<unsigned char,3> voice_flags{}; // +aec3,+aebe,+aeb9 in branch order.
};
struct KeiichiAttack300Effects {
 int next_state=-1,next_phase=-1;
 bool initialize=false,clear_contact=false,strike=false;
 int effect=-1,voice=-1,voice_argument=0;
 int secondary_effect=-1;
 std::array<int,2> spawned_states{{-1,-1}}; // virtual object birth requests from late directional phases
 // Some original handlers open several contact slots or register several
 // attacks on one entry (for example character 5 state 311).
 int contact_capacity=-1,attack_statistics_count=1;
 int frame_override=-1; // Original actor handlers may skip into an animation phase.
};
inline KeiichiAttack300Effects advance_keiichi_attack300(KeiichiAttack300& s,const KeiichiAttack300Input& in){
 KeiichiAttack300Effects out;
 if(in.animation_complete){out.next_state=0;return out;}
 if(!in.grounded){out.next_state=43;return out;}
 unsigned contact=in.contact;
 if(s.phase==0&&s.frame==0){
  s.movement_angle=0;s.moving=1;s.contact_seen=0;
  s.speed=in.distance_squared>=640000.?15.5f:25.5f;
  approach_battle_offset(s.offset,0.f,180.f);
  out.initialize=true;out.clear_contact=true;contact=0;
 }
 if(contact&2){out.next_state=392;out.clear_contact=true;return out;}
 if(contact&&!s.contact_seen)s.contact_seen=1;
 if(s.phase<2)approach_battle_offset(s.offset,0.f,20.f);
 if(s.phase==2&&s.frame<4)approach_battle_offset(s.offset,0.f,10.f);
 if(s.phase==1&&(in.distance_squared<90000.||!s.moving||s.frame>10)){out.next_phase=2;return out;}
 if(s.phase==2&&s.frame==4){
  out.effect=60;
  const auto voice=battle_melee_voice(1,in.distance_squared,s.offset,in.voice_flags);
  out.voice=voice.id;out.voice_argument=voice.argument;
 }
 if(s.phase==2){s.speed-=1.5f;if(s.speed<0)s.speed=0;}
 out.strike=s.phase==2&&s.frame>1&&s.frame<10;
 return out;
}
}
