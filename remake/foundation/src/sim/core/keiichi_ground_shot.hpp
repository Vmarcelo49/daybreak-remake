#pragma once
#include "battle_steering.hpp"
#include "battle_random.hpp"
#include <algorithm>
#include <stdexcept>
namespace daybreak {
struct RosterShot400Event;
enum class GroundShotOrigin {RightHand,AttachmentZero,LeftHand,ActorSide,World};
struct KeiichiGroundShot {unsigned spread=0;float gravity=0;unsigned charge_hold=0;};
struct GroundShotEffects {
 int next_state=-1,effect=-1,voice=-1;
 int voice_choice=-1;
 unsigned voice_priority=10;
 bool started=false,fire=false;
 unsigned bullet_slot=0;
 float yaw=0,pitch=0;
 GroundShotOrigin origin=GroundShotOrigin::RightHand;
 bool count_attack=true;
 bool hold_clock=false;
 int auxiliary_slot=-1;
 float origin_height=0;
 // FUN_00435450 receives a world-space muzzle computed by the actor handler.
 float world_forward_x=0,world_forward_z=0,world_lateral=0,world_yaw=0;
 bool world_actor_heading_only=false;
 float world_lateral_z=0;
 bool world_lateral_z_override=false;
 unsigned attack_calls=1;
 unsigned attachment_slot=0;
 bool paired_attachments=false;
 int attachment_model=-1;
 // A retained native schedule is an ordered callback program. The aggregate
 // fields above remain useful to action/clock helpers; the host must replay
 // this view to retain repeated sounds and interleaved attack/ammo requests.
 // Tables have static storage; callers supplying another range own its lifetime.
 const RosterShot400Event* callback_first=nullptr;
 const RosterShot400Event* callback_last=nullptr;
 unsigned callback_request_begin=0;
};
// 46a190/473610/47b940 state400. Host resolves 435220 hand or435000
// attachment transforms, statistics, magazine admission and projectile spawn.
inline GroundShotEffects advance_keiichi_ground_shot(KeiichiGroundShot& s,unsigned weapon,
 unsigned phase,unsigned frame,bool complete,bool grounded,float& speed,float& offset,
 float target_elevation,unsigned rounds,bool special,BattleRandom& random){
 if(weapon>2)throw std::invalid_argument("Unsupported Keiichi ground shot");
 GroundShotEffects out;
 if(complete){out.next_state=0;return out;}
 if(!grounded){out.next_state=43;return out;}
 if(phase==0&&frame==0){out.started=true;if(weapon==2)s.spread=0;}
 if(phase==0){
  if(frame<(weapon==2?12u:14u))approach_battle_offset(offset,0.f,20.f);
  speed=std::max(0.f,speed-.5f);
 }
 if(frame==(weapon==2?10u:13u)){out.effect=weapon==0?86:weapon==1?89:174;out.voice=rounds==1?30:27;}
 if(weapon<2&&frame==13){
  out.fire=true;out.pitch=float(std::clamp(int(target_elevation),-30,30));
  out.bullet_slot=special?(weapon==0?3u:1u):0u;
 }
 if(weapon==2&&frame>9&&frame<21){
  s.spread+=2;const auto horizontal=random.next()%10u,vertical=random.next()%10u;
  out.fire=true;out.origin=GroundShotOrigin::AttachmentZero;
  out.yaw=float(s.spread)-15.f+float(horizontal);
  out.pitch=float(vertical)+std::clamp(target_elevation,-30.f,30.f)+5.f;
  out.bullet_slot=special?1u:0u;
 }
 return out;
}
// 42dc20 compensates movement angle only on full turn steps; snapping the
// final small offset does not compensate.402 frame0 then resets movement angle.
inline void turn_air_shot(float& offset,float& movement,float step=20){
 approach_battle_offset_preserving_movement(offset,movement,step);
}
// 46a190/473610/47b940 state401: two successive compensated turns,
// .25 braking only in phase0, frame10 singles or frames10..20 burst.
inline GroundShotEffects advance_keiichi_dash_shot(KeiichiGroundShot& s,unsigned weapon,
 unsigned phase,unsigned frame,bool complete,bool grounded,float& speed,float& offset,float& movement,
 float elevation,unsigned rounds,bool special,BattleRandom& random){
 if(weapon>2)throw std::invalid_argument("Unsupported Keiichi dash shot");
 GroundShotEffects out;
 if(complete){out.next_state=0;return out;}
 if(!grounded){s.gravity=.5f;out.next_state=43;return out;}
 if(phase==0&&frame==0){out.started=true;if(weapon==2)s.spread=0;}
 if(frame<(weapon==2?12u:10u))turn_air_shot(offset,movement,weapon==2?20.f:10.f);
 if(phase==0){turn_air_shot(offset,movement,15);speed=std::max(0.f,speed-.25f);}
 if(frame==10){out.effect=weapon==0?86:weapon==1?89:174;out.voice=rounds==1?30:27;}
 if(weapon<2&&frame==10){out.fire=true;out.pitch=float(std::clamp(int(elevation),-30,30));out.bullet_slot=special?(weapon==0?3u:1u):0u;}
 if(weapon==2&&frame>9&&frame<21){
  s.spread+=2;const auto x=random.next()%10u,y=random.next()%10u;
  out.fire=true;out.origin=GroundShotOrigin::AttachmentZero;
  out.yaw=float(s.spread)-15.f+float(x);out.pitch=float(y)+std::clamp(elevation,-30.f,30.f)+5.f;
  out.bullet_slot=special?1u:0u;
 }
 return out;
}
inline GroundShotEffects advance_keiichi_air_shot(KeiichiGroundShot& s,unsigned weapon,
 unsigned phase,unsigned frame,bool complete,bool grounded,float& offset,float& movement,float& vertical,
 float elevation,unsigned rounds,bool special,BattleRandom& random){
 if(weapon>2)throw std::invalid_argument("Unsupported Keiichi air shot");
 GroundShotEffects out;
 if(complete){out.next_state=43;return out;}
 if(grounded&&frame>0){out.next_state=403;return out;}
 if(frame<(weapon==2?12u:14u))turn_air_shot(offset,movement);
 if(frame==0){movement=0;if(weapon==2)s.spread=0;}
 out.started=frame==0&&(weapon==2||phase==0);
 if(frame==(weapon==2?10u:13u)){out.effect=weapon==0?86:weapon==1?89:174;out.voice=rounds==1?30:weapon==2?27:28;}
 if(weapon<2&&frame==13){
  out.fire=true;int pitch=int(elevation);if(pitch< -30)pitch=-45;if(pitch>30)pitch=45;
  out.pitch=float(pitch);out.bullet_slot=special?(weapon==0?3u:1u):0u;
 }
 if(weapon==2&&frame>9&&frame<21){
  s.spread+=2;const auto x=random.next()%10u,y=random.next()%10u;
  out.fire=true;out.origin=GroundShotOrigin::AttachmentZero;
  out.yaw=float(s.spread)-15.f+float(x);out.pitch=float(y)+std::clamp(elevation,-30.f,30.f)+5.f;
  out.bullet_slot=special?1u:0u;
 }
 if(s.gravity==0)s.gravity=.5f;vertical-=s.gravity;
 return out;
}
// 46a190/473610 cases404..407.407 intentionally has no muzzle-effect call.
inline GroundShotEffects advance_keiichi_directional_shot(KeiichiGroundShot& s,unsigned weapon,unsigned state,
 unsigned phase,unsigned frame,bool complete,bool grounded,float& speed,float& offset,float& movement,
 float elevation,unsigned rounds,bool special){
 if(weapon>1||state<404||state>407)throw std::invalid_argument("Unsupported directional shot");
 GroundShotEffects out;
 if(complete){out.next_state=0;return out;}
 if(!grounded){s.gravity=.5f;out.next_state=43;return out;}
 out.started=phase==0&&frame==0;
 if(state==404){
  if(frame<10)turn_air_shot(offset,movement,10);
  if(frame>30)speed=std::max(0.f,speed-1.f);
 }else if(state==405||state==406){
  if(frame<14)approach_battle_offset(offset,0,10);
  if(frame>20)speed=std::max(0.f,speed-.5f);
 }else {
  if(frame<10)approach_battle_offset(offset,0,9);
  if(frame>30)speed=std::max(0.f,speed-1.f);
  if(phase==0){approach_battle_offset(offset,0,15);speed=std::max(0.f,speed-.25f);}
 }
 // Initialization follows steering/braking, even on a later phase's frame0.
 if(frame==0){movement=state==404?0.f:state==405?-90.f:state==406?90.f:180.f;speed=10;}
 if(frame==13){
  out.fire=true;out.voice=rounds==1?30:28;
  if(state!=407)out.effect=weapon==0?86:89;
  const int limit=state==407?45:30;out.pitch=float(std::clamp(int(elevation),-limit,limit));
  out.bullet_slot=special?(weapon==0?3u:1u):0u;
 }
 return out;
}
// Case408 is distinct from402: gravity precedes fire and pitch clamps to30.
// Bat input selects408; Iron/Shovel ordinary input selects402 instead.
inline GroundShotEffects advance_keiichi_air_dash_shot(KeiichiGroundShot& s,unsigned phase,unsigned frame,
 bool complete,bool grounded,float& offset,float& movement,float& vertical,float elevation,unsigned rounds,bool special){
 GroundShotEffects out;
 if(complete){out.next_state=43;return out;}
 if(grounded&&frame>0){out.next_state=409;return out;}
 out.started=phase==0&&frame==0;
 if(frame<14)turn_air_shot(offset,movement,20);
 if(frame==0)movement=0;
 if(s.gravity==0)s.gravity=.5f;vertical-=s.gravity;
 if(frame==13){out.fire=true;out.effect=86;out.voice=rounds==1?30:28;out.pitch=float(std::clamp(int(elevation),-30,30));out.bullet_slot=special?3u:0u;}
 return out;
}
// Bat450/460; prep frame4 is a spawn without the4230e0 attack-stat call.
inline GroundShotEffects advance_bat_charge_shot(KeiichiGroundShot& s,unsigned state,unsigned phase,unsigned frame,
 bool complete,bool grounded,float& speed,float& offset,float& movement,float& vertical,float elevation,unsigned rounds,bool special){
 if(state!=450&&state!=460)throw std::invalid_argument("Unsupported Bat charge state");
 GroundShotEffects out;const bool air=state==460;
 if(complete){out.next_state=air?43:0;return out;}
 if(!air&&!grounded){s.gravity=.5f;out.next_state=43;return out;}
 if(air&&grounded&&vertical<0){out.next_state=469;return out;}
 out.started=phase==0&&frame==0;
 if(frame<20){if(air)turn_air_shot(offset,movement,18);else approach_battle_offset(offset,0,18);}
 if(air){if(frame==0)speed*=.5f;}else speed=std::max(0.f,speed-.5f);
 if(frame==4){out.fire=true;out.count_attack=false;out.origin=GroundShotOrigin::LeftHand;out.bullet_slot=1;}
 if(frame==20){out.fire=true;out.effect=87;out.voice=rounds==1?30:29;out.origin=GroundShotOrigin::AttachmentZero;out.bullet_slot=special?4:2;out.pitch=float(std::clamp(int(elevation),-40,40));}
 if(air){s.gravity=.5f;vertical-=s.gravity;}
 return out;
}
// Iron473610 and Shovel47b940 states450/460. The added elevation is a
// distance-dependent positive arc; negative root elevation scales it by .95.
inline GroundShotEffects advance_lobbed_charge_shot(KeiichiGroundShot& s,unsigned weapon,unsigned state,unsigned phase,unsigned frame,
 bool complete,bool grounded,float& speed,float& offset,float& movement,float& vertical,float elevation,float distance_squared,unsigned rounds,bool special){
 if((weapon!=1&&weapon!=2)||(state!=450&&state!=460))throw std::invalid_argument("Unsupported lobbed charge state");
 GroundShotEffects out;const bool air=state==460,shovel=weapon==2;const unsigned fire=shovel?13:20;
 if(complete){out.next_state=air?43:0;return out;}
 if(!air&&!grounded){s.gravity=.5f;out.next_state=43;return out;}
 if(air&&grounded&&vertical<0){out.next_state=469;return out;}
 out.started=phase==0&&frame==0;
 if(out.started&&shovel){s.charge_hold=0;if(air)speed*=.5f;}
 if(frame<fire){if(air||shovel)turn_air_shot(offset,movement,18);else approach_battle_offset(offset,0,18);}
 if(air){if(!shovel&&frame==0)speed*=.5f;}else speed=std::max(0.f,speed-(shovel?.75f:.5f));
 if(frame==fire){
  const int base=std::clamp(int(elevation),-40,40);
  float arc=float(std::sqrt(double(distance_squared))*40.0/(shovel?4000.0:5000.0));
  arc=std::clamp(arc,shovel?10.f:0.f,shovel?50.f:40.f);if(base<0)arc*=.95f;
  out.fire=true;out.effect=shovel?175:90;out.voice=rounds==1?30:29;out.origin=GroundShotOrigin::ActorSide;
  out.origin_height=air&&!shovel?20.f:40.f;out.pitch=float(base)+arc;out.bullet_slot=special?3:2;
  if(!shovel)out.auxiliary_slot=9;
 }
 if(shovel){
  if(frame==5){if(s.charge_hold<10){++s.charge_hold;out.hold_clock=true;}else s.charge_hold=0;}
  if(frame==32&&s.charge_hold<15){++s.charge_hold;out.hold_clock=true;}
 }
 if(air){s.gravity=.5f;vertical-=s.gravity;}
 return out;
}
// Bat350/360: full charge, with three4230e0 calls but one registered50 object.
inline GroundShotEffects advance_bat_full_charge_shot(KeiichiGroundShot& s,unsigned state,unsigned phase,unsigned frame,
 bool complete,bool grounded,float& speed,float& offset,float& movement,float& vertical,float elevation){
 if(state!=350&&state!=360)throw std::invalid_argument("Unsupported Bat full charge state");
 GroundShotEffects out;const bool air=state==360;
 if(complete){out.next_state=air?43:0;return out;}
 if(!air&&!grounded){s.gravity=.5f;out.next_state=43;return out;}
 if(air&&grounded&&vertical<0){out.next_state=469;return out;}
 out.started=phase==0&&frame==0;if(out.started)s.charge_hold=0;
 if(frame<15)turn_air_shot(offset,movement,15);
 if(air){if(frame==0){speed*=.25f;vertical*=.25f;s.gravity=.1f;}}
 else speed=std::max(0.f,speed-.5f);
 if(frame==4){out.fire=true;out.count_attack=false;out.bullet_slot=1;out.origin=GroundShotOrigin::AttachmentZero;}
 if(frame==20){
  out.fire=true;out.effect=88;out.voice=33;out.bullet_slot=5;out.attack_calls=3;
  out.pitch=float(std::clamp(int(elevation),-40,40));out.origin=GroundShotOrigin::AttachmentZero;
  if(air){movement=0;speed=-6.5f;vertical=5;s.gravity=.5f;}else s.charge_hold=0;
 }
 if(air)vertical-=s.gravity;
 if(frame==28&&s.charge_hold<30){++s.charge_hold;out.hold_clock=true;}
 return out;
}
//473610 full charge: startup voice, auxiliary10 before main6, fixed60 pitch.
inline GroundShotEffects advance_iron_full_charge_shot(KeiichiGroundShot& s,unsigned state,unsigned phase,unsigned frame,
 bool complete,bool grounded,float& speed,float& offset,float& movement,float& vertical){
 if(state!=350&&state!=360)throw std::invalid_argument("Unsupported Iron full charge state");
 GroundShotEffects out;const bool air=state==360;
 if(complete){out.next_state=air?43:0;return out;}
 if(!air&&!grounded){s.gravity=.5f;out.next_state=43;return out;}
 if(air&&grounded&&vertical<0){out.next_state=469;return out;}
 out.started=phase==0&&frame==0;if(out.started){s.charge_hold=0;out.voice=32;}
 if(frame<15)turn_air_shot(offset,movement,15);
 if(air){if(frame==0){speed*=.25f;vertical*=.25f;s.gravity=.1f;}}
 else speed=std::max(0.f,speed-.5f);
 if(frame==20){
  out.fire=true;out.effect=91;out.bullet_slot=6;out.auxiliary_slot=10;
  out.pitch=60;out.origin=GroundShotOrigin::ActorSide;out.origin_height=20;
  if(air){movement=0;speed=-6.5f;vertical=5;s.gravity=.5f;}else s.charge_hold=0;
 }
 if(air)vertical-=s.gravity;
 if(frame==28&&s.charge_hold<25){++s.charge_hold;out.hold_clock=true;}
 return out;
}
//47b940 full charge: deploy at15, no4230e0 call and no airborne recoil.
inline GroundShotEffects advance_shovel_full_charge_shot(KeiichiGroundShot& s,unsigned state,unsigned phase,unsigned frame,
 bool complete,bool grounded,float& speed,float& offset,float& movement,float& vertical){
 if(state!=350&&state!=360)throw std::invalid_argument("Unsupported Shovel full charge state");
 GroundShotEffects out;const bool air=state==360;
 if(complete){out.next_state=air?43:0;return out;}
 if(!air&&!grounded){s.gravity=.5f;out.next_state=43;return out;}
 if(air&&grounded&&vertical<0){out.next_state=469;return out;}
 out.started=phase==0&&frame==0;if(out.started)s.charge_hold=0;
 if(frame<15)turn_air_shot(offset,movement,15);
 if(air){if(frame==0){speed*=.25f;vertical*=.25f;s.gravity=.1f;}}
 else speed=std::max(0.f,speed-.5f);
 if(frame==15){out.fire=true;out.count_attack=false;out.effect=177;out.voice=39;out.bullet_slot=6;out.origin=GroundShotOrigin::ActorSide;s.charge_hold=0;}
 if(air){if(frame==35)s.gravity=.5f;vertical-=s.gravity;}
 if(frame==28&&s.charge_hold<5){++s.charge_hold;out.hold_clock=true;}
 return out;
}
inline bool keiichi_shooting_state(unsigned state){return (state>=400&&state<=412)||state==350||state==360||state==450||state==460||state==469;}
}
