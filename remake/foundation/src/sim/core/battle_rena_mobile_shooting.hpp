#pragma once
// Native43ffc0/448220/438310;32 actual mobile DAT configurations.
// Projectile admission happens synchronously through the callback so subsequent
// voices inspect consumed rounds. Animation/pool/socket services remain external.
#include "battle_rena_full_charge.hpp"
#include <cmath>
#include <limits>

namespace daybreak {
inline bool rena_mobile_shooting_state(unsigned weapon,unsigned state){
 return weapon<3&&((state>=401&&state<=409&&(weapon!=2||state!=401))||state==450||state==460);
}
struct RenaMobileInput {
 std::uint32_t primary_rounds=0,secondary_rounds=0,primary_reload_timer=0,secondary_reload_timer=0;
 std::uint32_t primary_cooldown=0,secondary_cooldown=0,primary_capacity=0,secondary_capacity=0;
 std::uint32_t primary_interval=0,secondary_interval=0,special_ready=0;
 std::uint8_t special_active=0;
 std::array<int,18> magazine_index{};unsigned projectile_count=0;
 std::array<unsigned,3> phase_duration{};std::array<bool,3> phase_hold{};unsigned phase_count=0;
};
// Defaults are verified DAT metadata; production should pass its actual loaded table.
inline RenaMobileInput rena_mobile_input(unsigned weapon,unsigned state){
 RenaMobileInput in;in.primary_cooldown=in.secondary_cooldown=100;in.special_ready=1;
 if(weapon==0){
  in.magazine_index={0,0,1,0,0,0,0,0,1,0,-1,-1,-1,-1,-1,0,0,0};in.projectile_count=18;
  in.primary_capacity=6;in.secondary_capacity=2;
 }else if(weapon==1){
  in.magazine_index={0,1,-1,1,-1,-1,0,-1,-1,-1};in.projectile_count=10;
  in.primary_capacity=1;in.secondary_capacity=15;
 }else if(weapon==2){
  in.magazine_index={0,-1,0,-1,1,1,-1,-1,-1,-1,-1,-1};in.projectile_count=12;
  in.primary_capacity=in.secondary_capacity=1;
 }
 in.primary_rounds=in.primary_capacity;in.secondary_rounds=in.secondary_capacity;
 in.phase_count=1;
 unsigned duration=22;
 if(weapon==0){
  if(state==401||state==402||(state>=404&&state<=408))duration=50;
  if(state==450)duration=40;if(state==460)duration=39;
 }else if(weapon==1){
  if(state==401||(state>=404&&state<=406))duration=51;
  if(state==402){in.phase_count=3;in.phase_duration={12,1,35};in.phase_hold={false,true,false};return in;}
  if(state==407)duration=1;if(state==408)duration=12;
  if(state==450)duration=43;if(state==460)duration=44;
 }else{
  if(state==402){in.phase_count=2;in.phase_duration={76,78,0};return in;}
  if(state>=404&&state<=408)duration=1;if(state==450)duration=86;if(state==460)duration=76;
 }
 in.phase_duration[0]=duration;return in;
}
enum class RenaMobileRequestKind {attachment,bone,world};
struct RenaMobileRequest {
 RenaMobileRequestKind kind=RenaMobileRequestKind::attachment;
 unsigned slot=0,socket=0;int magazine_index=-1;bool admitted=false;
 int attachment_model=-1;
 unsigned event_index=0;int flag=0;
 std::array<float,3> position{};float forward=0,height=0,right=0,yaw=0,pitch=0;
};
struct RenaMobileEffects: RenaFullChargeEffects {
 std::array<int,2> model_slots{{0,1}};
 std::vector<RenaMobileRequest> requests;
 std::vector<std::array<std::uint32_t,3>> voice_rounds;
 bool dat_phase_unbacked=false;
 float horizontal_squared=0,horizontal_distance=0,target_height=0;
};
inline bool rena_mobile_consume(const RenaMobileRequest& r,RenaMobileInput& in){
 if(r.magazine_index<0)return true;
 if(r.magazine_index>1)throw std::invalid_argument("Unknown native indexed magazine");
 auto& rounds=r.magazine_index?in.secondary_rounds:in.primary_rounds;
 auto& timer=r.magazine_index?in.secondary_reload_timer:in.primary_reload_timer;
 auto& cooldown=r.magazine_index?in.secondary_cooldown:in.primary_cooldown;
 const auto capacity=r.magazine_index?in.secondary_capacity:in.primary_capacity;
 const auto interval=r.magazine_index?in.secondary_interval:in.primary_interval;
 if(rounds==0||rena_full_signed(cooldown)<rena_full_signed(interval))return false;
 if(rounds==capacity)timer=0;--rounds;cooldown=0;if(rounds==0)timer=0;return true;
}
// Accept returns whether the native pool would be called, and must apply all
// relevant magazine side effects to in before returning. Request is emitted even
// when native435920 rejects it. Unlimited(-1) requests never consume ammo.
template<class Random,class Accept>
RenaMobileEffects advance_rena_mobile_shooting(RenaFullChargeMotion& s,RenaMobileInput& in,Random&& random,Accept&& accept){
 if(!rena_mobile_shooting_state(s.weapon,s.state))throw std::invalid_argument("Unsupported Rena mobile DAT state");
 RenaMobileEffects e;if(s.blocked)return e;
 if(s.weapon!=1)s.last_hit_owner=-1;
 auto emit=[&](RenaFullEventKind kind,int id=0){e.events.push_back({kind,id});};
 auto model=[&](unsigned slot,int id){e.model_slots.at(slot)=id;e.events.push_back({RenaFullEventKind::model,id,int(slot)});};
 model(0,0);model(1,1);s.strike_active=false;
 auto state=[&](unsigned value){e.next_state=int(value);emit(RenaFullEventKind::state,int(value));};
 auto phase=[&](unsigned value){
  e.next_phase=int(value);emit(RenaFullEventKind::phase,int(value));
  s.phase=value;s.frame=s.second_frame=0;
  if(value<in.phase_count){s.duration=in.phase_duration[value];s.hold_phase=in.phase_hold[value];}
  else e.dat_phase_unbacked=true;
 };
 auto activate=[&](){s.activated=true;emit(RenaFullEventKind::activate);};
 auto clear=[&](){s.contacts.fill(0);emit(RenaFullEventKind::clear_contact);};
 auto capacity=[&](int n){s.capacity.fill(n);emit(RenaFullEventKind::capacity,n);};
 auto voice=[&](int id){e.events.push_back({RenaFullEventKind::voice,id,-1,10,0});e.voice_rounds.push_back({std::uint32_t(id),in.primary_rounds,in.secondary_rounds});};
 auto draw=[&](){const auto n=random();RenaFullChargeEvent v{RenaFullEventKind::random};v.random_value=n;e.events.push_back(v);++e.random_calls;return n;};
 auto comp=[&](float step){approach_battle_offset_preserving_movement(s.offset,s.movement,step);};
 auto turn=[&](float step){approach_battle_offset(s.offset,0,step);};
 auto decrease=[&](float amount){s.speed-=amount;if(s.speed<0)s.speed=0;};
 auto hide=[&](){model(0,-1);model(1,-1);};
 auto special=[&](){return in.special_active!=0&&in.special_ready!=0;};
 auto aim=[&](int limit){
  volatile float dx=s.position[0]-s.target[0],dz=s.position[2]-s.target[2];
  volatile float x2=float(std::pow(double(dx),2.));
  volatile float squared=float(std::pow(double(dz),2.)+double(x2));
  e.horizontal_squared=squared;e.horizontal_distance=float(std::sqrt(double(squared)));
  volatile float dy=s.target[1]-s.position[1];e.target_height=dy;
  e.root_elevation=battle_target_elevation(s.position,s.target);s.pitch=std::uint32_t(std::clamp(int(e.root_elevation),-limit,limit));
 };
 auto request=[&](RenaMobileRequest r){
  if(r.slot>=in.projectile_count)throw std::invalid_argument("Projectile slot outside actual DAT table");
  r.magazine_index=in.magazine_index[r.slot];r.event_index=unsigned(e.events.size());
  if(r.kind==RenaMobileRequestKind::attachment)r.attachment_model=e.model_slots.at(r.socket);
  RenaFullChargeEvent v{r.kind==RenaMobileRequestKind::world?RenaFullEventKind::world_projectile:RenaFullEventKind::attachment_projectile,int(r.slot)};
  v.choice=int(r.socket);v.flag=r.flag;v.position=r.position;v.yaw=r.yaw;v.pitch=r.pitch;e.events.push_back(v);
  r.admitted=accept(r,in);e.requests.push_back(r);
 };
 auto bullet=[&](unsigned slot,float yaw=0,float pitch=0){RenaMobileRequest r;r.slot=slot;r.yaw=yaw;r.pitch=pitch;request(r);};
 auto bone=[&](unsigned slot,float pitch){RenaMobileRequest r;r.kind=RenaMobileRequestKind::bone;r.slot=slot;r.pitch=pitch;request(r);};
 auto shot=[&](unsigned normal,unsigned awakened,int sound,unsigned limit,int alternate=27){
  emit(RenaFullEventKind::shooting_statistics);emit(RenaFullEventKind::sound,sound);aim(int(limit));voice(in.primary_rounds==1?30:alternate);
  bullet(special()?awakened:normal,0,float(rena_full_signed(s.pitch)));
 };
 auto ratio=[&](){
  s.vertical=-40;
  volatile float dx=s.position[0]-s.target[0],dz=s.position[2]-s.target[2];
  volatile float x2=float(std::pow(double(dx),2.));
  volatile float squared=float(std::pow(double(dz),2.)+double(x2));
  e.horizontal_squared=squared;e.horizontal_distance=float(std::sqrt(double(squared)));
  volatile float dy=s.target[1]-s.position[1];e.target_height=dy;
  volatile float numerator=e.horizontal_distance+1.f;numerator=numerator*s.vertical;
  volatile float speed=numerator/dy;
  // Native comparison order preserves NaN/inf rules: upper min, then lower max.
  const float upper=speed<=10.f?float(speed):10.f;s.speed=0.f<=upper?upper:0.f;
 };
 const bool first=s.phase==0&&s.frame==0;
 const int f=rena_full_signed(s.frame),p=rena_full_signed(s.phase);
 const bool recovery=s.state==403||s.state==409;
 const bool ground=s.state==401||(s.state>=404&&s.state<=407)||s.state==450;
 if(s.weapon==1&&(s.state==450||s.state==460)){model(0,2);model(1,-1);}
 if(s.complete){state(recovery||ground||(s.weapon==1&&s.state!=460)||(s.weapon==2&&s.state==402)?0:43);if(s.state==460&&s.weapon!=1)s.gravity=.5f;return e;}
 if(recovery){
  s.gravity=s.vertical=s.movement=s.turn_step=s.speed=0;
  s.recharge+=rena_full_signed(s.status7f4)<1?40u:5u;if(rena_full_signed(s.recharge)>1000)s.recharge=1000;
 }else if(ground){
  if(!s.grounded){state(43);s.gravity=.5f;return e;}
  if(first){activate();if(s.weapon==1&&s.state<=406)emit(RenaFullEventKind::melee_statistics);if(s.weapon==1&&s.state==401)s.movement=0;if(s.weapon==1&&s.state==450)s.scratch_e8=0;}
  if(s.state==401){
   if(s.weapon==0){if(f<12)comp(20);if(f>13)hide();if(s.phase==0)decrease(.25f);if(s.frame==12)shot(0,6,70,30);}
   else{
    if(f<15)turn(20);if(s.phase==0){if(s.frame==0){clear();capacity(1);}comp(5);decrease(.5f);}
    if(s.frame==7)s.speed=30;
    if(s.frame==15){emit(RenaFullEventKind::sound,67);voice(29);s.speed=0;}
    if(s.frame==18){emit(RenaFullEventKind::sound,77);emit(RenaFullEventKind::shooting_statistics);bullet(special()?0:6);}
    s.strike_active=f>=8&&f<=18;
   }
  }else if(s.state>=404&&s.state<=407){
   const bool back=s.state==407,lateral=s.state==405||s.state==406;
   if(f<10){if(s.state==404)comp(9);else turn(s.weapon==1?9:lateral?15:9);}
   if(f>13)hide();if(f>(lateral?10:30))decrease(lateral?.5f:1.f);
   if(back&&s.phase==0){turn(15);decrease(.25f);}
   if(s.frame==0){s.movement=back?180.f:s.state==405?-90.f:s.state==406?90.f:0.f;s.speed=10;}
   if(s.frame==(s.weapon==1||back?13u:12u)){
    if(back){
     if(s.weapon==1){bullet(4,50,45);bullet(4,-50,45);}
     else{emit(RenaFullEventKind::shooting_statistics);emit(RenaFullEventKind::shooting_statistics);voice(rena_full_signed(in.primary_rounds)<3?30:28);
      if(special()){emit(RenaFullEventKind::shooting_statistics);emit(RenaFullEventKind::shooting_statistics);}
      bullet(4,75,30);bullet(9,-75,30);if(special()){bullet(13,85,20);bullet(14,-85,20);}
     }
    }else if(s.weapon==1){
     emit(RenaFullEventKind::sound,70);aim(30);if(s.state==406)emit(RenaFullEventKind::shooting_statistics);
     bullet(0,0,float(rena_full_signed(s.pitch)));if(s.state!=406)emit(RenaFullEventKind::shooting_statistics);
    }else shot(0,6,s.weapon==2?170:70,30);
   }
  }else{
   if(f<(s.weapon==2?25:10))comp(18);decrease(s.weapon==2?1.5f:.5f);
   if(s.weapon==1){
    if(f>11&&f<27){s.scratch_e8+=4;s.scratch_ec=s.scratch_e8-5u+draw()%10u;
     emit(RenaFullEventKind::shooting_statistics);if(s.frame==15)emit(RenaFullEventKind::sound,63);
     volatile float yaw=float(rena_full_signed(s.scratch_ec));yaw=yaw-30.f;bullet(special()?3:1,yaw,0);
    }
   }else if(s.frame==(s.weapon==2?40u:13u)){
    emit(RenaFullEventKind::shooting_statistics);emit(RenaFullEventKind::sound,s.weapon==2?171:60);voice(in.secondary_rounds==1?30:28);
    if(s.weapon==2){aim(40);bone(special()?5:4,float(rena_full_signed(s.pitch)));}else bullet(special()?8:2,0,45);
   }
  }
 }else if(s.state==402||s.state==408){
  if(s.weapon==1){
   if(s.grounded&&p<2){phase(2);s.vertical=s.speed=0;return e;}
   if(first){activate();if(s.state==402)emit(RenaFullEventKind::melee_statistics);}
   if(s.phase==0){if(s.frame==0){if(s.state==402)s.speed=s.vertical=0;s.movement=0;clear();capacity(1);}if(f<10)turn(s.state==402?20:18);}
   if(s.phase==1&&s.frame==0)ratio();
   if(s.phase==2&&s.frame==0){emit(RenaFullEventKind::sound,s.state==402?67:62);if(s.state==402)voice(29);}
   if(s.phase==2&&s.frame==5){
    emit(RenaFullEventKind::sound,77);
    if(s.state==402){emit(RenaFullEventKind::shooting_statistics);bullet(special()?0:6);if(special())bullet(9);}
    else aim(30);
   }
   s.strike_active=s.phase==2&&f<6;
  }else if(s.weapon==2&&s.state==402){
   if(first){activate();s.movement=0;comp(180);}
   if(s.phase==0){
    s.speed=20;s.movement=0;s.vertical-=.5f;if(f<10)turn(10);
    if(f>17)s.frame=s.second_frame=17;
    if(s.grounded){if(rena_full_signed(s.frame)<15){state(403);s.vertical=s.speed=0;return e;}phase(1);s.frame=s.second_frame=25;s.vertical=0;}
   }
   if(s.phase==1){
    if(!s.grounded){state(43);s.gravity=.5f;return e;}decrease(1);
    if(s.frame==35){s.speed=0;emit(RenaFullEventKind::sound,170);bullet(special()?2:0);voice(in.primary_rounds==1?30:29);
     for(unsigned k=0;k<10;++k){emit(RenaFullEventKind::shooting_statistics);const float pitch=float(draw()%50u)+30.f;const float yaw=90.f-float(draw()%180u);bullet(special()?3:1,yaw,pitch);}
    }
   }
  }else{
   if(s.grounded&&f>0){state(s.state==402?403:409);return e;}
   if(first)activate();if(f<(s.state==402?13:12))comp(20);if(f>(s.state==402?12:13))hide();if(s.frame==0)s.movement=0;
   if(s.state==408){if(s.gravity==0)s.gravity=.5f;s.vertical-=s.gravity;}
   if(s.frame==(s.state==402?13u:12u))shot(s.state==402?1:0,s.state==402?7:6,70,30);
   if(s.state==402){if(s.gravity==0)s.gravity=.5f;s.vertical-=s.gravity;}
  }
 }else{
  if(s.weapon==1){if(s.grounded&&f>0){s.vertical=0;state(469);return e;}}
  else if(s.grounded&&s.vertical<0){state(469);return e;}
  if(first)activate();if(f<10)comp(18);
  if(s.frame==0){s.speed*=.5f;if(s.weapon==1)s.movement=0;if(s.weapon==2){s.vertical-=.5f;s.gravity=.1f;}}
  if(s.weapon==1){
   if(f>14&&f<30){s.scratch_e8+=4;s.scratch_ec=s.scratch_e8-5u+draw()%10u;
    if(s.frame==15)emit(RenaFullEventKind::sound,63);emit(RenaFullEventKind::shooting_statistics);
    volatile float yaw=float(rena_full_signed(s.scratch_ec));yaw=yaw-30.f;bullet(special()?3:1,yaw,0);
   }
  }else if(s.frame==(s.weapon==2?36u:12u)){
   emit(RenaFullEventKind::shooting_statistics);emit(RenaFullEventKind::sound,s.weapon==2?171:60);voice(in.secondary_rounds==1?30:28);
   if(s.weapon==2){aim(40);bone(special()?5:4,float(rena_full_signed(s.pitch)));}else bullet(special()?8:2,0,45);
  }
  if(s.weapon!=2)s.gravity=.5f;s.vertical-=s.gravity;
 }
 ++s.frame;++s.second_frame;e.clock_advanced=true;
 if(rena_full_signed(s.duration)<rena_full_signed(s.frame)&&!s.hold_phase)phase(s.phase+1u);
 return e;
}
template<class Random> RenaMobileEffects advance_rena_mobile_shooting(RenaFullChargeMotion& s,RenaMobileInput& in,Random&& random){
 return advance_rena_mobile_shooting(s,in,std::forward<Random>(random),rena_mobile_consume);
}
}
