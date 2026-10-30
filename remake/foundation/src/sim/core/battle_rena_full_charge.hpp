#pragma once
#include "battle_steering.hpp"
#include "battle_target_position.hpp"
#include "legacy_trig.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>

namespace daybreak {
// Recovered live actor350/360/370/469 in43ffc0/448220/438310.
// All original DAT-backed Rena full shooters share this adapter.350 for
// weapons0/1 is a separate awakened melee; weapon2's350 is a full shot.
inline bool rena_full_charge_actor_state(unsigned weapon,unsigned state){
 return state==350||state==360||state==469||(weapon<2&&state==370);
}
inline bool rena_full_charge_shooting_state(unsigned weapon,unsigned state){
 return state==469||state==360||(weapon<2&&state==370)||(weapon==2&&state==350);
}
struct RenaFullChargeMotion {
 unsigned weapon=0,state=0,phase=0,frame=0,second_frame=0,duration=0;
 bool complete=false,blocked=false,grounded=false,hold_phase=false,activated=false;
 float speed=0,vertical=0,gravity=0,movement=0,offset=0,heading=0,turn_step=0;
 std::array<float,3> position{},target{};
 std::uint32_t pitch=0,held=0,rewind=0,scratch_e8=0,scratch_ec=0,attack_flag=0,recharge=0,status7f4=0;
 int last_hit_owner=0;
 bool strike_active=false;
 std::array<std::uint16_t,4> contacts{};
 std::array<std::int32_t,4> capacity{};
};
enum class RenaFullEventKind {state,phase,sound,voice,random,activate,clear_contact,capacity,
 shooting_statistics,melee_statistics,world_projectile,attachment_projectile,particle,model,strike};
struct RenaFullChargeEvent {
 RenaFullEventKind kind;int id=0,choice=0,priority=0,flag=0;
 std::uint32_t random_value=0;
 std::array<float,3> position{};
 float yaw=0,pitch=0;
};
struct RenaFullChargeEffects {
 int next_state=-1,next_phase=-1;
 bool clock_advanced=false;
 unsigned random_calls=0;
 float root_elevation=0;
 std::vector<RenaFullChargeEvent> events;
};
inline int rena_full_signed(std::uint32_t value){int out;std::memcpy(&out,&value,4);return out;}
template<class Random> RenaFullChargeEffects advance_rena_full_charge(RenaFullChargeMotion& s,Random&& random){
 if(s.weapon>2||!rena_full_charge_actor_state(s.weapon,s.state))throw std::invalid_argument("Unsupported Rena full-charge actor state");
 RenaFullChargeEffects e;
 if(s.blocked)return e;
 if(s.weapon!=1)s.last_hit_owner=-1;
 // The native prefix binds both default sockets and disables the weapon trail.
 s.strike_active=false;
 auto emit=[&](RenaFullEventKind kind,int id=0){e.events.push_back({kind,id});};
 auto state=[&](unsigned value){e.next_state=int(value);emit(RenaFullEventKind::state,int(value));};
 auto phase=[&](unsigned value){e.next_phase=int(value);emit(RenaFullEventKind::phase,int(value));};
 auto activate=[&](){s.activated=true;emit(RenaFullEventKind::activate);};
 auto clear=[&](){s.contacts.fill(0);emit(RenaFullEventKind::clear_contact);};
 auto capacity=[&](int value){s.capacity.fill(value);emit(RenaFullEventKind::capacity,value);};
 auto voice=[&](int id,int choice,int priority,int flag=0){e.events.push_back({RenaFullEventKind::voice,id,choice,priority,flag});};
 auto draw=[&](){const auto value=random();RenaFullChargeEvent event{RenaFullEventKind::random};event.random_value=value;e.events.push_back(event);++e.random_calls;return value;};
 auto aim=[&](){e.root_elevation=battle_target_elevation(s.position,s.target);s.pitch=std::uint32_t(std::clamp(int(e.root_elevation),-40,40));};
 auto bullet=[&](unsigned slot,const std::array<float,3>& position,float yaw,float pitch){
  RenaFullChargeEvent event{RenaFullEventKind::world_projectile,int(slot)};event.position=position;event.yaw=yaw;event.pitch=pitch;e.events.push_back(event);
 };
 auto relative=[&](unsigned slot,float yaw,float pitch){RenaFullChargeEvent event{RenaFullEventKind::attachment_projectile,int(slot)};event.yaw=yaw;event.pitch=pitch;e.events.push_back(event);};
 auto particle=[&](unsigned id,float yaw,float pitch){RenaFullChargeEvent event{RenaFullEventKind::particle,int(id)};event.position=s.position;event.yaw=yaw;event.pitch=pitch;e.events.push_back(event);};
 auto model=[&](unsigned slot,int id){e.events.push_back({RenaFullEventKind::model,id,int(slot)});};
 auto pair=[&](){
  // CW007f multiplication/addition and intermediate fstp boundaries. The
  // muzzle uses actor heading alone; the two directions use heading+offset.
  volatile float side=s.heading+90.f;
  volatile float x=legacy_trig(s.heading,false)*70.f;x=x+s.position[0];
  volatile float z=legacy_trig(s.heading,true)*70.f;z=z+s.position[2];
  volatile float sx=legacy_trig(side,false)*70.f,sz=legacy_trig(side,true)*70.f;
  volatile float y=s.position[1]+70.f;
  for(unsigned k=0;k<2;++k){
   volatile float bx=k?x-sx:x+sx,bz=k?z-sz:z+sz;
   volatile float yaw=s.heading+s.offset;yaw=k?yaw-1.f:yaw+1.f;
   emit(RenaFullEventKind::shooting_statistics);bullet(11+k,{bx,y,bz},yaw,float(rena_full_signed(s.pitch)));
  }
 };
 const bool first=s.phase==0&&s.frame==0;
 const auto frame=rena_full_signed(s.frame),current_phase=rena_full_signed(s.phase);
 if(s.state==469){
  if(s.complete){state(0);return e;}
  s.gravity=s.vertical=s.movement=s.turn_step=s.speed=0;
  s.recharge+=rena_full_signed(s.status7f4)<1?40u:5u;
  if(rena_full_signed(s.recharge)>1000)s.recharge=1000;
 }else if(s.state==350&&s.weapon<2){
  if(s.weapon==0){model(0,-1);model(1,-1);}
  if(s.complete){state(0);return e;}
  if(!s.grounded){state(43);s.gravity=.5f;return e;}
  if(first){activate();if(s.weapon==1)emit(RenaFullEventKind::melee_statistics);}
  if(s.frame==0){s.movement=0;if(s.weapon==0){s.rewind=s.held=s.scratch_e8=0;}else{clear();capacity(1);s.speed=0;}}
  if(s.weapon==0){
   // Clear occurs every visit up to35.
   // Do not coalesce it: native statistics/contact calls retain their order.
   if(frame<36||s.frame==55){clear();capacity(1);}
   if(s.frame==0)voice(32,0,20);
   if(s.frame==11||s.frame==15||s.frame==19||s.frame==23||s.frame==27||s.frame==31||s.frame==35||s.frame==56){emit(RenaFullEventKind::sound,61);emit(RenaFullEventKind::melee_statistics);}
   auto scatter=[&](unsigned id){s.scratch_ec=draw()%40u-20u;s.pitch=draw()%40u-20u;volatile float yaw=s.heading+s.offset;yaw=yaw+float(rena_full_signed(s.scratch_ec));particle(id,yaw,float(rena_full_signed(s.pitch)));};
   if(s.frame==7||s.frame==15||s.frame==23||s.frame==31)scatter(320);
   if(s.frame==7||s.frame==22||s.frame==37)scatter(350);
   if(s.frame==56){volatile float yaw=s.heading+s.offset;particle(340,yaw,0);voice(33,-1,20);}
   s.attack_flag=s.scratch_e8?1u:0u;
   unsigned contact=0;for(auto flags:s.contacts)contact|=flags;
   if((contact&1)&&s.frame==50)s.scratch_e8=1;
   if(s.frame==1){s.speed=10;s.turn_step=0;}
   if(s.frame==10){s.speed=0;s.turn_step=0;}
   if(frame>0&&frame<10){if(rena_full_signed(s.rewind)<1){++s.rewind;--s.frame;--s.second_frame;}else s.rewind=0;}
   if(s.frame==70&&rena_full_signed(s.rewind)<8){++s.rewind;s.frame=s.second_frame=66;return e;}
  }else{
   if(s.frame==25||s.frame==45||s.frame==65)emit(RenaFullEventKind::sound,68);
   if(frame<8)approach_battle_offset(s.offset,0,25);
   if(s.frame==20){s.speed=8.5f;s.turn_step=0;}
   if(frame>20)s.attack_flag=0;
   if(s.frame==73){s.speed=0;s.turn_step=0;}
   s.strike_active=frame>=21&&frame<=64;
  }
 }else{
  const bool air=s.weapon<2?s.state==370:s.state==360;
  if(s.complete){state(air?43:0);if(air)s.gravity=.5f;return e;}
  //448220/360 initializes before its second completion/support check.
  if(s.weapon==1&&!air&&s.frame==0){voice(32,draw()%100u<50?4:3,20);clear();activate();}
  if(!air&&!s.grounded){state(43);s.gravity=.5f;return e;}
  if(air&&s.grounded&&s.vertical<0){s.vertical=0;state(469);return e;}
  if(s.weapon==0){
   if(air)s.vertical-=s.gravity;
   else {s.speed-=.75f;if(s.speed<0)s.speed=0;}
   if(first){if(air)s.speed=s.vertical=s.gravity=0;clear();activate();s.held=0;}
   if(current_phase<2)approach_battle_offset_preserving_movement(s.offset,s.movement,15);
   if(s.phase==2){
    if(s.frame==2){
     if(air){s.movement=0;s.speed=-9.5f;s.vertical=10;s.gravity=.5f;}
     voice(32,draw()%100u<51?2:1,20);emit(RenaFullEventKind::sound,83);aim();pair();
    }
    if(s.frame==13){if(rena_full_signed(s.held)<10){++s.held;return e;}s.held=0;}
   }
  }else if(s.weapon==1){
   if(air&&first){activate();voice(32,draw()%100u<50?4:3,15);}
   if(frame<10)approach_battle_offset_preserving_movement(s.offset,s.movement,18);
   if(air){if(s.frame==0){s.speed*=.5f;s.vertical=0;}}
   else {s.speed-=1.5f;if(s.speed<0)s.speed=0;}
   if(s.frame==16){emit(RenaFullEventKind::sound,64);relative(8,0,70);emit(RenaFullEventKind::shooting_statistics);}
   if(air){s.gravity=.5f;s.vertical-=s.gravity;}
  }else{
   if(air)s.vertical-=s.gravity;
   else {s.speed-=.75f;if(s.speed<0)s.speed=0;}
   if(first){
    voice(32,draw()%100u<51?0:1,20);
    if(air){s.speed*=.1f;s.vertical*=.1f;s.gravity=.05f;}
    clear();activate();s.held=0;
   }
   if(frame<42)approach_battle_offset_preserving_movement(s.offset,s.movement,15);
   if(!air&&frame>116){model(0,-1);model(1,-1);}
   if(s.frame==42)s.frame=s.second_frame=95;
   if(s.frame==116){
    emit(RenaFullEventKind::sound,172);aim();emit(RenaFullEventKind::shooting_statistics);
    volatile float x=legacy_trig(s.heading,false)*150.f;x=x+s.position[0];
    volatile float z=legacy_trig(s.heading,true)*150.f;z=z+s.position[2];
    volatile float y=s.position[1]+70.f,yaw=s.heading+s.offset;yaw=yaw+1.f;
    bullet(8,{x,y,z},yaw,float(rena_full_signed(s.pitch)));
   }
  }
 }
 ++s.frame;++s.second_frame;e.clock_advanced=true;
 if(rena_full_signed(s.duration)<rena_full_signed(s.frame)&&!s.hold_phase)phase(s.phase+1u);
 return e;
}
}
