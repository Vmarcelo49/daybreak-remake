#pragma once
#include "roster_native_scratch.hpp"
#include "keiichi_ground_shot.hpp"
#include "legacy_trig.hpp"
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <vector>
namespace daybreak {
inline bool natsumi_charge_state(unsigned state){return state==450||state==451||state==452||state==460||state==461||state==462;}
struct NatsumiChargeInput {
 unsigned state=450,phase=0,frame=0,contact=0;
 bool complete=false,grounded=true,blocked=false,boosted=false,special_melee_voice=false;
 double distance_squared=0;
 float target_elevation=0,heading=0;
};
struct NatsumiChargeMotion {float speed=0,offset=0,movement=0,vertical=0,gravity=0,pitch=0,pivot=0;};
enum class NatsumiChargeEventKind {ClearContacts,Capacity,Projectile,Activate,AttackStatistics,Effect,Voice};
struct NatsumiChargeEvent {NatsumiChargeEventKind kind{};int value=0;GroundShotEffects projectile{};float offset=0,model_pitch=0,pivot=0;};
struct NatsumiChargeEffects {int next_state=-1,next_phase=-1,frame_delta=1;std::vector<NatsumiChargeEvent> events;};
inline float natsumi_motion_elevation(float vertical,float speed){
 return float((std::atan2(double(vertical),double(speed))/double(3.1415927410125732f))*180.);
}
// Original005e2af0 cases1c2..1c4/1cc..1ce. Native counters, relative attachment
// yaw, same-visit first contact and callback order are retained. The consumer
// resolves the real DAT socket/world muzzle and original shared RNG/admission.
template<class Random> NatsumiChargeEffects advance_natsumi_charge(RosterNativeScratch& scratch,
 const NatsumiChargeInput& in,NatsumiChargeMotion& motion,Random&& random){
 if(!natsumi_charge_state(in.state))throw std::invalid_argument("Unsupported Natsumi charge state");
 NatsumiChargeEffects out;const bool air=in.state>=460,parent=in.state==450||in.state==460;
 const auto event=[&](NatsumiChargeEventKind kind,int value=0){out.events.push_back({kind,value,{}});};
 const auto projectile=[&](GroundShotEffects shot){out.events.push_back({NatsumiChargeEventKind::Projectile,0,shot,motion.offset,motion.pitch,motion.pivot});};
 if(in.blocked){out.frame_delta=0;return out;}
 if(in.complete){out.next_state=air?43:0;out.frame_delta=0;if(air&&!parent)motion.pitch=0;return out;}
 if(!air&&!in.grounded){out.next_state=43;out.frame_delta=0;motion.speed=std::min(motion.speed,10.f);motion.vertical=0;motion.gravity=.5f;return out;}
 if(air&&(parent?in.phase==2:in.frame>30)){
  motion.gravity=.5f;motion.vertical-=motion.gravity;
  if(in.grounded){out.next_state=469;out.frame_delta=0;motion.speed=motion.vertical=motion.gravity=0;if(!parent)motion.pitch=0;return out;}
 }
 if(parent&&in.phase==0&&in.frame==0){
  motion.movement=0;event(NatsumiChargeEventKind::ClearContacts);event(NatsumiChargeEventKind::Capacity,1);
  scratch.ec=0;scratch.f8=0;scratch.known|=2u|16u;
  if(air){scratch.f0=in.boosted?300:175;scratch.f4=0;scratch.known|=4u|8u;}
  else motion.speed=15.f;
  // Both parent states first issue projectile1 at forward100,height80.
  GroundShotEffects shot;shot.fire=true;shot.count_attack=false;shot.bullet_slot=1;
  shot.origin=GroundShotOrigin::World;shot.origin_height=80;shot.world_forward_x=shot.world_forward_z=100;
  projectile(shot);
  if(air){approach_battle_offset(motion.offset,0,180);motion.pitch=natsumi_motion_elevation(motion.vertical,motion.speed);motion.pivot=70;}
  event(NatsumiChargeEventKind::Activate);event(NatsumiChargeEventKind::AttackStatistics,1);
  approach_battle_offset(motion.offset,0,180);
  if(in.boosted){if(!air)motion.speed=32.5f;shot.bullet_slot=7;shot.pitch=air?motion.pitch:0;projectile(shot);}
 }
 if(parent){
  if(!air){
   if(in.phase==0&&in.frame==0)approach_battle_offset(motion.offset,0,180);
   else if(in.phase<2){approach_battle_offset(motion.offset,0,10);if(in.boosted)approach_battle_offset(motion.offset,0,20);}
  }else{
   if(in.phase<2){approach_battle_offset(motion.offset,0,10);if(in.boosted)approach_battle_offset(motion.offset,0,10);}
   scratch.ec=native_scratch_increment(scratch.ec);
   if(in.phase<2&&scratch.f0>0){
    float elevation=in.phase==0&&in.frame==0?in.target_elevation:natsumi_motion_elevation(motion.vertical,motion.speed);
    if(in.target_elevation<elevation){elevation-=5;if(elevation<in.target_elevation)elevation=in.target_elevation;}
    if(elevation<in.target_elevation){elevation+=5;if(in.target_elevation<elevation)elevation=in.target_elevation;}
    elevation=std::clamp(elevation,-30.f,50.f);const float strength=float(scratch.f0)*.1f;
    motion.speed=legacy_trig(elevation,false)*strength;motion.vertical=legacy_trig(elevation,true)*strength;
    motion.pitch=natsumi_motion_elevation(motion.vertical,motion.speed);motion.pivot=70;
    approach_battle_offset(motion.offset,0,5);
   }
  }
  if(in.phase==1){
   if(in.distance_squared<250000.){out.next_state=air?461:451;out.frame_delta=0;
    if(std::abs(motion.offset)<30.f&&in.special_melee_voice)out.next_state=air?462:452;return out;}
   if(air){
    if(scratch.f8>20){out.next_phase=2;out.frame_delta=0;motion.speed*=.5f;return out;}
    if(in.frame==4){scratch.f8=native_scratch_increment(scratch.f8);out.frame_delta=0;return out;}
   }else if(in.frame>20){out.next_phase=2;out.frame_delta=0;return out;}
  }
  if(!air&&in.phase==2)motion.speed=std::max(0.f,motion.speed-1.5f);
  return out;
 }
 // Any nonzero aggregate, including guard contact, latches once. Air usesF4;
 // ground usesF8. The model selected before the latch supplies socket0 this visit.
 auto& latch=air?scratch.f4:scratch.f8;
 if((in.contact&0xffffu)!=0&&latch==0){
  event(NatsumiChargeEventKind::Effect,224);latch=1;scratch.known|=air?8u:16u;
  event(NatsumiChargeEventKind::Capacity,0);
  for(unsigned i=0;i<8;++i){
   const float pitch=float(random()%30u)+50.f;const auto yaw_random=random()%180u;
   GroundShotEffects shot;shot.fire=true;shot.count_attack=false;shot.bullet_slot=i<5?8u:9u;
   shot.origin=GroundShotOrigin::AttachmentZero;shot.attachment_slot=0;shot.pitch=pitch;
   shot.yaw=90.f-float(yaw_random);
   if(in.state!=451)shot.yaw=in.heading+motion.offset+90.f-float(yaw_random);
   projectile(shot);
  }
 }
 if(air){
  if(in.frame==0){event(NatsumiChargeEventKind::ClearContacts);event(NatsumiChargeEventKind::Capacity,1);}
  if(in.frame==17)event(NatsumiChargeEventKind::Voice,in.state==461?3:39);
  if(in.frame<17){if(in.boosted)approach_battle_offset(motion.offset,0,10);approach_battle_offset(motion.offset,0,5);}
  if(in.frame>30)approach_battle_offset(motion.pitch,0,5);
 }else{
  if((in.state==451&&in.frame==1)||(in.state==452&&in.frame==0))motion.speed=40;
  if(in.frame==17)event(NatsumiChargeEventKind::Voice,in.state==451?29:39);
  if(in.frame<24){approach_battle_offset(motion.offset,0,5);if(in.boosted)approach_battle_offset(motion.offset,0,10);}
  motion.speed=std::max(0.f,motion.speed-1.5f);if(in.frame==24)motion.speed=0;
 }
 return out;
}
}
