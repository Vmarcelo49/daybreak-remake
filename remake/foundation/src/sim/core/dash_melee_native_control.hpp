#pragma once
#include "ground_melee_native_control.hpp"
#include "roster_ground_dash_melee.hpp"
#include "battle_rena_melee.hpp"
#include "mion_mobile_melee.hpp"
namespace daybreak {
enum class DashMeleeKind {Clear,Capacity,Activate,Statistics,Query,Sound,Voice,State,Phase,Projectile,SceneObject};
struct DashMeleeNativeEvent {DashMeleeKind kind{};int value=0,argument=0,mode=0;};
struct DashMeleeNativeInput : GroundMeleeNativeInput {};
struct DashMeleeNativeMotion : RosterFollowupControlMotion {float pitch=0,pivot=0,extra68=0;};
struct DashMeleeNativeEffects {
 int next_state=-1,next_phase=-1,clock=1,frame_override=-1,next_rank=-1;bool strike=false;
 std::array<DashMeleeNativeEvent,16> events{};unsigned count=0;
};
//Keep the already native-verified scalar body. This adapter adds the original
//ordered service chronology and shared actor words omitted by aggregated effects.
inline DashMeleeNativeEffects advance_dash_melee_native_control(RosterNativeScratch& scratch,DashMeleeNativeMotion& m,const DashMeleeNativeInput& in){
 character_action_dispatch(in.character,in.weapon);if(in.state!=330&&in.state!=331)throw std::invalid_argument("Dash melee330/331 required");
 DashMeleeNativeEffects out;const unsigned ch=in.character,we=in.weapon,st=in.state,p=in.phase,f=in.frame;unsigned contact=in.contact&65535u;
 const auto event=[&](DashMeleeKind k,int value=0,int argument=0,int mode=0){out.events.at(out.count++)={k,value,argument,mode};};
 const auto clear=[&](){event(DashMeleeKind::Clear);contact=0;};
 const auto query=[&](){event(DashMeleeKind::Query,int(contact));return contact;};
 const auto state=[&](int value){event(DashMeleeKind::State,value);out.next_state=value;out.clock=0;};
 const auto phase=[&](int value){event(DashMeleeKind::Phase,value);out.next_phase=value;out.clock=0;};
 if(in.blocked){out.clock=0;return out;}
 KeiichiAttack300 action{int(p),int(f),scratch.e8,scratch.ec,m.speed,m.offset,m.movement};
 KeiichiAirMelee air{scratch.f0,unsigned(scratch.ec),m.vertical,m.gravity,m.pitch,m.pivot};
 KeiichiAttack300Input request;request.grounded=in.grounded;request.animation_complete=in.complete;request.contact=contact;request.distance_squared=in.distance_squared;request.voice_flags=in.voice_flags;
 KeiichiAttack300Effects legacy;int gauge=in.gauge;
 if(ch==0)legacy=advance_rena_melee(we,st,air,action,request,false,0,m.turn,gauge,false);
 else if(ch==1)legacy=advance_mion_mobile_melee(st,we,air,action,request,0);
 else legacy=advance_roster_ground_dash_melee(ch,we,st,air,action,request);
 m.speed=action.speed;m.offset=action.offset;m.movement=action.movement_angle;m.vertical=air.vertical;m.gravity=air.gravity;m.pitch=air.pitch;m.pivot=air.pivot;
 scratch.e8=action.moving;scratch.ec=action.contact_seen;scratch.f0=air.strength;
 out.frame_override=legacy.frame_override;out.strike=legacy.strike;
 if(legacy.next_state==0||legacy.next_state==43){state(legacy.next_state);return out;}
 //Rena1 hopping landing returns before any body/query/presentation work.
 if(ch==0&&we==1&&st==330&&legacy.next_phase==3){phase(3);return out;}
 const bool first=legacy.initialize;
 if(first){
  scratch.known|=1u;
  const bool f0_writer=st==331?(ch!=5):(ch==6||(ch==15&&we==1));if(f0_writer)scratch.known|=4u;
  if((ch==4&&we==2&&st==330)||(ch==10&&st==331))scratch.known|=2u;
  if(ch==8&&we==2){scratch.f8=0;scratch.known|=16u;}
  if(ch==14&&st==330)event(DashMeleeKind::Voice,39,10,1); //422490(39,0,10,0)
  const bool capacity_first=st==330?(ch==0?we!=1:ch==2||ch==3||(ch==4&&we<2)||ch==5||ch==8||ch==11||ch==13||ch==14||ch==15):ch==3;
  const auto statistics=[&](){event(DashMeleeKind::Activate,1);for(int n=0;n<legacy.attack_statistics_count;++n)event(DashMeleeKind::Statistics,1);};
  const auto capacity=[&](){clear();event(DashMeleeKind::Capacity,legacy.contact_capacity>=0?legacy.contact_capacity:1);};
  if(capacity_first){capacity();statistics();}else{statistics();capacity();}
 }
 const auto voice=[&](){if(legacy.voice>=0&&!(first&&ch==14&&st==330))event(DashMeleeKind::Voice,legacy.voice,legacy.voice_argument,ch==9&&st==330&&p==4&&f==4?2:0);};
 const auto presentation=[&](){
  const bool voice_first=st==330?(ch==0||ch==5):(ch==2||ch==3||ch==15);
  if(voice_first)voice();
  if(legacy.effect>=0)event(DashMeleeKind::Sound,legacy.effect,0,0);
  if(legacy.secondary_effect>=0)event(DashMeleeKind::Sound,legacy.secondary_effect,0,1);
  if(!voice_first)voice();
  for(int id:legacy.spawned_states)if(id>=0)event(DashMeleeKind::SceneObject,id);
 };
 const bool voice_before_guard=st==330&&p==2&&f==0&&(ch==1||ch==12);
 if(voice_before_guard)voice();
 if(ch==8&&we==2){
  if(query()!=0&&scratch.f8==0&&in.rank==1){event(DashMeleeKind::Projectile,3);scratch.f8=0;scratch.known|=16u;out.next_rank=0;}
 }
 const bool guard=st==330?(ch==0?we!=1:ch!=7&&ch!=9&&(ch!=4||we<2)):(ch!=3&&ch!=6&&ch!=7&&ch!=11);
 if(guard&&query()&2u){state(392);clear();return out;}
 if(ch==15&&we==1&&st==330&&query()!=0)clear();
 if(st==330&&ch==7&&p==1)query();
 if(st==330&&p==1&&(ch==1||ch==3||ch==12||ch==13||ch==15))m.turn=0;
 //Presentation requests from the scalar body retain their native callback
 //address and explicit422490 variant, rather than dropping secondary sounds.
 if(!voice_before_guard)presentation();
 else{
  if(legacy.effect>=0)event(DashMeleeKind::Sound,legacy.effect);
  if(legacy.secondary_effect>=0)event(DashMeleeKind::Sound,legacy.secondary_effect,0,1);
 }
 if(ch==7&&st==331&&p==1&&f==0){clear();event(DashMeleeKind::Capacity,1);}
 if(legacy.next_state>=0){state(legacy.next_state);return out;}
 if(legacy.next_phase>=0){phase(legacy.next_phase);return out;}
 if(ch==13&&p==2&&f>45){
  if(st==331||((in.direction==3||in.direction==4)&&in.gauge>0)){
   if(query()==0&&in.gauge>0&&(in.direction==3||in.direction==4)&&(st==331||in.grounded)){state(in.direction==3?24:23);return out;}
  }
 }
 //The Satoko tail decrements its timer only on normal returns. The host
 //owns that timer; predict its F8 write here without running the tail twice.
 const std::uint32_t clock=in.mine_clock-1u;std::int32_t signed_clock;std::memcpy(&signed_clock,&clock,4);
 if(ch==3&&we==1&&signed_clock<0){scratch.f8=0;scratch.known|=16u;}
 return out;
}
} //namespace daybreak
