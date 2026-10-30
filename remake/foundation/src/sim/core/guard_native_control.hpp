#pragma once
#include "roster_followup_control.hpp"
namespace daybreak {
enum class GuardNativeKind {Query,Clear,Sound,Voice,Particle,State,Phase};
struct GuardNativeEvent {GuardNativeKind kind{};int value=0,argument=0;};
struct GuardNativeInput {
 unsigned state=390,phase=0,frame=0,contact=0;
 bool complete=false,grounded=true,blocked=false,jump=false,melee=false;
};
struct GuardNativeMotion : RosterFollowupControlMotion {int gauge=1000;unsigned invincible=0;};
struct GuardNativeEffects {
 int next_state=-1,next_phase=-1,clock=1;
 std::array<GuardNativeEvent,10> events{};unsigned count=0;
};
// All46 slot6 bodies have identical390/391/392 cases. Preserve the shared E8,
// carried vertical/gravity and ordered callbacks, including early returns.
// Source/raw proof: analysis/guard-common-native-20260929-source-audit.md.
inline GuardNativeEffects advance_guard_native_control(RosterNativeScratch& scratch,
 GuardNativeMotion& m,const GuardNativeInput& in){
 if(in.state<390||in.state>392)throw std::invalid_argument("Guard state390/391/392 required");
 GuardNativeEffects out;unsigned contact=in.contact&65535u;
 const auto event=[&](GuardNativeKind k,int value=0,int argument=0){out.events.at(out.count++)={k,value,argument};};
 const auto state=[&](int value){event(GuardNativeKind::State,value);out.next_state=value;out.clock=0;};
 const auto phase=[&](int value){event(GuardNativeKind::Phase,value);out.next_phase=value;out.clock=0;};
 const auto clear=[&](){event(GuardNativeKind::Clear);contact=0;};
 const auto query=[&](){event(GuardNativeKind::Query,int(contact));return contact;};
 if(in.blocked){out.clock=0;return out;}
 if(in.complete){
  if(in.state==391)event(GuardNativeKind::Voice,12,20);
  if(!in.grounded)m.gravity=.5f;
  state(in.grounded?0:43);return out;
 }
 if(!in.grounded){m.gravity=.5f;state(in.state==391?103:43);return out;}
 const bool first=in.phase==0&&in.frame==0;
 if(in.state==390){
  if(in.phase==1)m.gauge=std::max(0,m.gauge-10);
  if(first){event(GuardNativeKind::Sound,4,1);m.movement=m.speed=0;clear();}
  if(in.phase==0)approach_battle_offset(m.offset,0,20);
  if(in.phase==1&&(!m.gauge||!in.jump||!in.melee)){phase(2);return out;}
  if((query()&2u)&&m.gauge>0){
   event(GuardNativeKind::Particle,70);state(391);event(GuardNativeKind::Sound,51,1);clear();return out;
  }
  if(in.phase==2){m.turn=0;m.speed=std::max(0.f,m.speed-1.f);}
  return out;
 }
 if(first){m.movement=0;m.speed=-15;scratch.e8=0;scratch.known|=1u;}
 if(in.state==391&&in.phase<2&&(query()&2u)){
  state(391);event(GuardNativeKind::Particle,70);event(GuardNativeKind::Sound,51);clear();return out;
 }
 if(in.phase==0){
  scratch.e8=native_scratch_increment(scratch.e8);scratch.known|=1u;
  if(scratch.e8>20){phase(1);return out;}
 }
 if(in.state==391&&in.phase==2)m.invincible=45;
 if(in.state==392&&first)event(GuardNativeKind::Voice,13,10);
 if(in.phase<(in.state==391?3u:2u)){m.turn=0;m.speed=std::min(0.f,m.speed+1.f);}
 return out;
}
}
