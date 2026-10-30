#pragma once
#include "dash_melee_native_control.hpp"
#include "roster_air_melee.hpp"
namespace daybreak {
struct AirMeleeNativeInput : DashMeleeNativeInput {float height=0;};
using AirMeleeNativeMotion=DashMeleeNativeMotion;
using AirMeleeNativeEffects=DashMeleeNativeEffects;
// Scalar pursuit policies are already native-verified. Preserve the shared
// actor EC counter/F0 strength and the ordered services omitted by their host.
inline AirMeleeNativeEffects advance_air_melee_native_control(RosterNativeScratch& scratch,AirMeleeNativeMotion& m,const AirMeleeNativeInput& in){
 character_action_dispatch(in.character,in.weapon);if(in.state!=320)throw std::invalid_argument("Air melee320 required");
 AirMeleeNativeEffects out;const unsigned ch=in.character,we=in.weapon,p=in.phase,f=in.frame;unsigned contact=in.contact&65535u;
 const auto event=[&](DashMeleeKind k,int value=0,int argument=0,int mode=0){out.events.at(out.count++)={k,value,argument,mode};};
 const auto clear=[&](){event(DashMeleeKind::Clear);contact=0;};
 if(in.blocked){out.clock=0;return out;}
 KeiichiAttack300 action{int(p),int(f),scratch.e8,scratch.ec,m.speed,m.offset,m.movement};
 KeiichiAirMelee air{scratch.f0,unsigned(scratch.ec),m.vertical,m.gravity,m.pitch,m.pivot};
 KeiichiAttack300Input request;request.grounded=in.grounded;request.animation_complete=in.complete;request.contact=contact;request.distance_squared=in.distance_squared;request.voice_flags=in.voice_flags;
 KeiichiAttack300Effects legacy;
 if(ch==2)legacy=advance_keiichi_air_melee(air,action,request,in.height);
 else{const auto next=advance_chasing_air_melee(roster_air_melee_policy(ch,we),air,action,request,in.height);legacy=next;legacy.frame_override=next.frame_override;}
 m.speed=action.speed;m.offset=action.offset;m.movement=action.movement_angle;m.vertical=air.vertical;m.gravity=air.gravity;m.pitch=air.pitch;m.pivot=air.pivot;
 scratch.e8=action.moving;scratch.f0=air.strength;std::memcpy(&scratch.ec,&air.ticks,4);
 if(legacy.next_state>=0){event(DashMeleeKind::State,legacy.next_state);out.next_state=legacy.next_state;out.clock=0;return out;}
 if(legacy.initialize){
  scratch.known|=7u;
  const auto stats=[&](){event(DashMeleeKind::Activate,1);event(DashMeleeKind::Statistics,1);};
  if(ch==13)stats();clear();event(DashMeleeKind::Capacity,ch==15&&we==1?3:1);if(ch!=13)stats();
 }
 if(ch==15&&we==1){event(DashMeleeKind::Query,int(contact));if(contact)clear();}
 out.frame_override=legacy.frame_override;out.strike=legacy.strike;
 if(legacy.effect>=0)event(DashMeleeKind::Sound,legacy.effect);
 //These eight bodies call42c8b0. Earlier effect=-1 policies dropped that
 //separate positional callback from their scalar oracle output.
 if(legacy.voice>=0&&(ch==4||ch==13||ch==14))event(DashMeleeKind::Sound,62,0,1);
 if(legacy.voice>=0)event(DashMeleeKind::Voice,legacy.voice,legacy.voice_argument);
 if(legacy.next_phase>=0){event(DashMeleeKind::Phase,legacy.next_phase);out.next_phase=legacy.next_phase;out.clock=0;return out;}
 const std::uint32_t clock=in.mine_clock-1u;std::int32_t signed_clock;std::memcpy(&signed_clock,&clock,4);
 if(ch==3&&we==1&&signed_clock<0){scratch.f8=0;scratch.known|=16u;}
 return out;
}
} //namespace daybreak
