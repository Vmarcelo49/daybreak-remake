#pragma once
#include "dash_melee_native_control.hpp"
#include "roster_directional_melee.hpp"
namespace daybreak {
struct DirectionalMeleeNativeInput : DashMeleeNativeInput {
 bool jump=false;
 // Retained isolated-body samples used a nonmutating421100 terminal.
 // Production must reset phase/clocks immediately, including Tomi's fallthrough.
 bool apply_phase_service=false;
};
using DirectionalMeleeNativeMotion=DashMeleeNativeMotion;
struct DirectionalMeleeNativeEffects : DashMeleeNativeEffects {bool continue_phase=false;};
inline DirectionalMeleeNativeEffects advance_directional_melee_native_control(RosterNativeScratch& scratch,
 DirectionalMeleeNativeMotion& m,const DirectionalMeleeNativeInput& in){
 character_action_dispatch(in.character,in.weapon);if(in.state!=310&&in.state!=311)throw std::invalid_argument("Directional melee310/311 required");
 DirectionalMeleeNativeEffects out;const unsigned ch=in.character,we=in.weapon,st=in.state,p=in.phase,f=in.frame;
 unsigned contact=in.contact&65535u;const auto entry=m;const auto initial=scratch;
 const auto event=[&](DashMeleeKind k,int value=0,int argument=0,int mode=0){out.events.at(out.count++)={k,value,argument,mode};};
 const auto clear=[&](){event(DashMeleeKind::Clear);contact=0;};
 const auto query=[&](){event(DashMeleeKind::Query,int(contact));return contact;};
 const auto state=[&](int value){event(DashMeleeKind::State,value);out.next_state=value;out.clock=0;};
 const auto phase=[&](int value,bool continued=false){event(DashMeleeKind::Phase,value);out.next_phase=value;out.clock=continued?1:0;out.continue_phase=continued;if(in.apply_phase_service)out.frame_override=0;};
 const auto guard=[&](){if(query()&2u){state(392);clear();return true;}return false;};
 const auto increment=[](int value){const std::uint32_t word=std::uint32_t(value)+1u;int result;std::memcpy(&result,&word,4);return result;};
 if(in.blocked){out.clock=0;return out;}
 if(st==311&&ch==14&&!in.complete){
  if(!in.grounded){m.vertical-=m.gravity;if(f>23){state(43);m.gravity=.5f;return out;}}
  else if(f>14&&f<24){out.frame_override=24;out.clock=0;return out;}
 }
 KeiichiAttack300 a{int(p),int(f),scratch.e8,scratch.ec,m.speed,m.offset,m.movement};a.vertical=m.vertical;a.gravity=m.gravity;
 KeiichiAirMelee air{scratch.f0,unsigned(scratch.ec),m.vertical,m.gravity,m.pitch,m.pivot};
 KeiichiAttack300Input request;request.grounded=in.grounded;request.animation_complete=in.complete;request.contact=0;request.distance_squared=in.distance_squared;
 KeiichiAttack300Effects legacy;int gauge=in.gauge;
 if(ch==0)legacy=advance_rena_melee(we,st,air,a,request,false,0,m.turn,gauge,false);
 else if(ch==1)legacy=advance_mion_melee(st,we,a,request);
 else if(ch==2)legacy=advance_keiichi_directional(st,a,{in.complete,in.grounded,false,in.distance_squared,0});
 else legacy=advance_roster_directional_melee(ch,we,st,a,{in.complete,in.grounded,false,in.distance_squared,0});
 if(ch<3){a.vertical=air.vertical;a.gravity=air.gravity;}
 m.speed=a.speed;m.offset=a.offset;m.movement=a.movement_angle;m.vertical=a.vertical;m.gravity=a.gravity;m.pitch=air.pitch;m.pivot=air.pivot;
 scratch.e8=a.moving;scratch.ec=initial.ec;
 if(in.complete){state(ch==15&&st==310?43:legacy.next_state);return out;}
 if(legacy.next_state==43){
  if(ch!=2)m.gravity=.5f;
  if(ch==7&&st==311)m.speed=entry.speed*.5f;
  state(43);return out;
 }
 if(ch==2&&st==310&&p==1)m.turn=0;
 // Shion310's common velocity prefix precedes guard; steering follows it.
 if(ch==5&&st==310){
  m=entry;scratch.e8=initial.e8;legacy={};
  if(p==0&&f==0){m.movement=0;m.speed=0;scratch.e8=0;approach_battle_offset(m.offset,0,180);legacy.initialize=true;}
  if(p==1&&f==0){m.movement=0;m.speed=30;m.vertical=17.5f;scratch.e8=0;legacy.clear_contact=true;legacy.contact_capacity=1;legacy.effect=62;legacy.voice=3;legacy.voice_argument=10;}
  if(m.speed>10)m.speed=std::max(10.f,m.speed-1.f);
  if(p==1||p==2){m.vertical-=1;if(in.grounded&&m.vertical<0){m.speed=m.vertical=m.gravity=0;legacy.next_phase=3;}}
  if(p==1&&f==2&&legacy.next_phase<0)legacy.effect=62;
 }
 if(ch==14&&st==311){
  // Same-visit frame14 launch, then airborne deceleration before Query.
  m.vertical=!in.grounded?entry.vertical-entry.gravity:entry.vertical;m.gravity=entry.gravity;
  if(f==14){m.speed=35;m.vertical=5;m.gravity=.5f;}
  if(!in.grounded&&f>=14)m.speed=std::max(15.f,(f==14?35.f:entry.speed)-1.5f);
  if(we==0&&!in.grounded&&f>14&&f<24){m.offset=entry.offset;approach_battle_offset(m.offset,0,10);}
 }
 if(ch==9&&st==310&&p==2&&in.grounded&&entry.vertical-entry.gravity>=0)m.speed=entry.speed;
 if(ch==11&&st==310&&p<2){
  legacy.next_phase=(p==1&&f>=8)||in.distance_squared<30000.?2:-1;
  if(legacy.next_phase<0){m.offset=entry.offset;if(p==0&&f==0)approach_battle_offset(m.offset,0,180);approach_battle_offset(m.offset,0,5);}
 }
 if(ch==15&&st==311&&f==0)m.vertical=0;
 // The original velocity clamps distinguish negative carried speed from
 // positive deceleration. Close-range launches also have a two-unit floor.
 if(ch==3&&st==310&&p==2&&entry.speed<=0)m.speed=entry.speed;
 if(ch==9&&st==310&&p==1&&f==0)m.speed=std::max(2.f,m.speed);
 if(ch==15&&st==310&&p==0&&f==5)m.speed=std::max(2.f,m.speed);
 if(ch==15&&we==0&&st==311&&p==0)m.speed=std::max(0.f,m.speed);
 if(ch==3&&st==311){
  const bool first=p==0&&f==0;scratch.e8=increment(first?0:initial.e8);
  m.speed=first?0:entry.speed;m.offset=entry.offset;m.movement=first?0:entry.movement;
  if(first)approach_battle_offset(m.offset,0,180);
  if(scratch.e8<15)approach_battle_offset(m.offset,0,12);
  if(scratch.e8==4)m.speed=we==2?16.5f:18.5f;
  if(scratch.e8>16)m.speed=std::max(0.f,m.speed-1.75f);
 }
 if(ch==7&&st==311&&we!=1&&f==9){
  a={int(p),13,initial.e8,initial.ec,entry.speed,entry.offset,entry.movement};a.vertical=entry.vertical;a.gravity=entry.gravity;
  roster_directional_311_motion(ch,we,a,in.distance_squared);m.speed=35;m.offset=a.offset;m.movement=a.movement_angle;
  legacy.effect=60;legacy.voice=2;legacy.voice_argument=10;out.frame_override=13;
 }
 out.strike=legacy.strike;const bool first=legacy.initialize;
 // These two guards precede frame-zero initialization itself.
 if(st==311&&(ch==9||ch==0&&we==2)){if(contact&2){m=entry;scratch=initial;if(guard())return out;}else query();}
 const auto stats=[&](){event(DashMeleeKind::Activate,1);for(int n=0;n<legacy.attack_statistics_count;++n)event(DashMeleeKind::Statistics,1);};
 const auto capacity=[&](int value){event(DashMeleeKind::Capacity,value);};
 if(first){
  const bool stats_first=st==310?(ch==1||ch==7||ch==9||ch==11||ch==12):(ch==0&&we==1||ch==1||ch==3||ch==4||ch==6||ch==7||ch==10||ch==13||ch==14);
  if(stats_first)stats();clear();capacity(ch==5&&st==311?4:ch==15&&we==1&&st==310?3:1);if(!stats_first)stats();
  if(st==310){scratch.known|=1u;if(ch==15){scratch.f0=0;scratch.known|=4u;}}
 }
 // Phase/frame contact reinitializations do not register another attack.
 if(!first&&legacy.clear_contact&&!(st==311&&ch==5&&p==0&&f!=0)){clear();if(legacy.contact_capacity>=0)capacity(legacy.contact_capacity);else if(f==0)capacity(ch==15&&we==1&&st==310?3:1);}
 if(!first&&!legacy.clear_contact&&legacy.contact_capacity>=0)capacity(legacy.contact_capacity);
 const auto presentation=[&](){
  const bool reverse=st==310?(ch==2||ch==5||ch==12):(ch==10||ch==11);
  const bool positioned=st==310?(ch==2||ch==4||ch==5&&p==1&&f==0||ch==9||ch==11&&p==3&&f==0||ch==13||ch==14):(ch==4||ch==10||ch==13||ch==14);
  const auto voice=[&](){if(legacy.voice>=0)event(DashMeleeKind::Voice,legacy.voice,legacy.voice_argument);};
  const auto sound=[&](){if(legacy.effect>=0)event(DashMeleeKind::Sound,legacy.effect,0,positioned?1:0);if(legacy.secondary_effect>=0)event(DashMeleeKind::Sound,legacy.secondary_effect,0,positioned?1:0);};
  if(reverse){voice();sound();}else{sound();voice();}
  for(auto id:legacy.spawned_states)if(id>=0)event(DashMeleeKind::SceneObject,id);
 };
 bool presented=false;
 if(st==310&&ch==5&&p==1&&f==0){presentation();presented=true;}
 if(st==310){
  const bool early=ch==0||ch==1||ch==4||ch==6||ch==7||ch==10||ch==13||ch==14;
  if(early&&contact&2){m=entry;scratch=initial;if(guard())return out;}
  if(early)query();
  if(legacy.next_phase>=0){
   const bool continued=ch==6||ch==8||ch==10;phase(legacy.next_phase,continued);
   if(continued&&in.apply_phase_service){
    m.offset=entry.offset;approach_battle_offset(m.offset,0,ch==10?3.f:ch==8?6.f:5.f);
    m.speed=ch==10?23.5f:std::max(0.f,entry.speed-(ch==8?1.f:2.f));
   }
   return out;
  }
  if(ch==5){if(guard())return out;if(p==0||p==1)approach_battle_offset(m.offset,0,2);}
  if(ch==15&&we==1){
   if(query()!=0){scratch.f0=increment(scratch.f0);scratch.known|=4u;if(scratch.f0>0){scratch.f0=0;clear();}}
  }
  if(!presented){presentation();presented=true;}
  if(p==2&&((ch==0&&we<2||ch==2)&&f>12||(ch==6||ch==13)&&f>15)){
   if((query()&1u)&&in.jump){state(40);return out;}
  }
  if(ch==2&&guard())return out;
 }else{
  const bool mid=ch==7||ch==12;
  if(mid){
   if(ch==7&&we!=1&&f==9){presentation();presented=true;}
   if(contact&2){m=entry;scratch=initial;if(ch==7&&we!=1&&f==9)m.speed=35;if(guard())return out;}else query();
  }
  if(legacy.next_phase>=0){phase(legacy.next_phase);return out;}
  if(legacy.next_state>=0){state(legacy.next_state);return out;}
  if(!presented){presentation();presented=true;}
  if(ch==5&&p==0&&f!=0&&legacy.clear_contact)clear();
  const bool tail=ch!=6&&ch!=7&&ch!=9&&ch!=12&&!(ch==5&&p!=0)&&!(ch==13&&p!=2);
  if(tail){
   if(contact&2&&ch==13&&p==2)m.speed=f==0?10.f:f==21?0.f:entry.speed;
   if(contact&2&&ch==14&&f>23)m.speed=entry.speed;
   if(guard())return out;
  }
  if(ch==14&&f==23){scratch.e8=increment(scratch.e8);scratch.known|=1u;out.clock=0;if(scratch.e8>60){m.gravity=.5f;state(42);}return out;}
 }
 if(legacy.next_state>=0)state(legacy.next_state);
 const std::uint32_t clock=in.mine_clock-1u;std::int32_t signed_clock;std::memcpy(&signed_clock,&clock,4);
 if(ch==3&&we==1&&out.clock&&signed_clock<0){scratch.f8=0;scratch.known|=16u;}
 return out;
}
} // namespace daybreak
