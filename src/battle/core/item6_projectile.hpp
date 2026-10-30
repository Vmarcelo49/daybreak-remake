#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <cmath>
#include <stdexcept>

namespace daybreak {
// Original 005fdee0, Shion weapon0. DAT includes case80, which only advances.
inline bool item6_projectile_registration(unsigned item,unsigned registration){
 return item==6&&registration<=90&&registration%10==0;
}
template<class Host> bool tick_item6_projectile(KeiichiNormalProjectile& s,
 unsigned registration,Host& host){
 if(s.released)return false;
 if(!item6_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item6 registration");
 const auto age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 auto birth_aim=[&](){
  const int target=host.target_state(s);
  if((target>117&&target<122)||target==221){
   if(s.pitch-host.target_elevation(s)<10.f)s.pitch=host.target_elevation(s);
   if(s.pitch-host.target_elevation(s)>-10.f)s.pitch=host.target_elevation(s);
  }
 };
 if((registration==0||registration==20)&&(projectile_contacts(s)&0x100))
  reflect_normal_projectile(s);
 if(registration==0||registration==20){
  if(age==0){
   birth_aim();s.speed=registration==0?35.f:60.f;s.capacity.fill(1);
   s.scratch_e8=s.scratch_ec=s.scratch_f0=0;
   if(registration==20)s.scale.fill(1.25f);
  }
  if(registration==20)s.rotation[1]+=15.f;
  if(s.offset>90.f||s.offset<-90.f)s.scratch_e8=0xffffffffu;
  ++s.scratch_f0;if(projectile_signed(s.scratch_f0)>60)s.scratch_f0=60;
  if(s.scratch_e8==0)approach_battle_offset(s.offset,0.f,.1f);
  const auto contact=projectile_contacts(s);
  if(s.scratch_ec==0&&(age>60||(contact!=0&&contact!=1)||host.stage_collision(s)==1))s.scratch_ec=1;
  if(s.scratch_ec==1){
   s.speed=2.f;s.capacity.fill(0);for(auto& axis:s.scale)axis-=.1f;
   if(s.scale[2]<=0.f)return finish();
  }
 }else if(registration==10||registration==30||registration==70){
  if(age==0){
   if(registration!=70){birth_aim();approach_battle_offset(s.offset,0.f,registration==10?10.f:20.f);
    s.speed=registration==10?55.f:80.f;s.capacity.fill(1);}
   s.scratch_e8=0;s.scratch_ec=registration==70?2:0;
   host.child_position(s,5,0,0,0);s.scale.fill(2.f);
  }
  if(registration!=70&&s.scratch_ec==0){
   s.speed-=registration==10?2.f:4.f;
   if(s.speed<=0.f||projectile_contacts(s)!=0||host.stage_collision(s)==1){
    s.speed=0;
    if(projectile_contacts(s)&1){s.scratch_ec=1;host.child_position(s,4,0,0,0);}
    else{s.scratch_ec=2;host.retarget_owner(s);host.owner_signal(s,1);}
   }
  }
  if(registration!=70&&s.scratch_ec==1){
   if(registration==30&&projectile_signed(s.scratch_e8)%10==0)host.particle_offset(s,6,0,0,0);
   s.capacity.fill(0);
   if(registration==30)s.speed=0;
   else{s.speed-=5.f;if(s.speed<2.f)s.speed=2.f;}
   ++s.scratch_e8;
   if(projectile_signed(s.scratch_e8)>30){s.scratch_ec=2;host.retarget_owner(s);host.owner_signal(s,1);}
  }
  if(s.scratch_ec==2){
   if(registration!=70&&(projectile_contacts(s)&1)){host.child_position(s,7,0,0,0);return finish();}
   s.capacity.fill(registration==70?1:0);s.speed=registration==70?50.f:40.f;
   approach_battle_offset(s.offset,0.f,180.f);s.pitch=host.target_elevation(s);
   if(host.target_distance_squared(s)<10000.f){host.owner_signal(s,3);return finish();}
  }
  if(registration==70&&age==5)s.capacity.fill(0);
  std::array<float,3> aim{};
  for(unsigned axis=0;axis<3;++axis)aim[axis]=s.position[axis]+s.velocity[axis]*40.f;
  host.owner_projectile_aim(s,aim);
  const unsigned state=host.owner_state(s);
  if((state>99&&state<300)||(state!=450&&state!=460))return finish();
 }else if(registration==40){
  if(age==0){s.speed=0;s.scratch_e8=s.scratch_ec=0;s.scale.fill(2.f);s.contacts.fill(0);s.capacity.fill(1);}
  if(s.offset>90.f||s.offset<-90.f)s.scratch_e8=0xffffffffu;
  if(age>60)s.scratch_ec=1;
  if(s.scratch_ec==1){
   s.capacity.fill(0);for(auto& axis:s.scale)axis-=.1f;
   if(s.scale[2]<=0.f)return finish();
  }
 }else if(registration==50){
  if(age==0)s.speed=0;
  const unsigned state=host.owner_state(s);
  if((state>99&&state<300)||(state!=450&&state!=460)||host.owner_signal_value(s)==3)return finish();
  const auto aim=host.owner_aim(s);
  const float dx=aim[0]-s.position[0],dy=aim[1]-s.position[1],dz=aim[2]-s.position[2];
  const float horizontal=dx*dx+dz*dz;
  s.scale={std::sqrt(horizontal+dy*dy)/105.f,.5f,.5f};
  s.position=host.owner_right_hand(s);
  constexpr float pi=3.1415927410125732f;
  s.offset=float(std::atan2(double(aim[2]-s.position[2]),double(aim[0]-s.position[0]))/pi*180.0)-s.heading;
  // Original stores the old horizontal squared distance before moving to hand.
  s.pitch=float(std::atan2(double(aim[1]-s.position[1]),double(std::sqrt(horizontal)))/pi*180.0);
 }else if(registration==60){
  if(age==0){s.scale.fill(.5f);s.speed=0;s.capacity.fill(1);s.scratch_e8=255;}
  const float growth=legacy_trig(float(s.frame<<2),false)*.2f;
  for(auto& axis:s.scale)axis+=growth;
  if(age>0){s.scratch_e8-=20;if(projectile_signed(s.scratch_e8)<0)s.scratch_e8=0;}
  if(age>13)return finish();
  host.alpha(s,s.scratch_e8&255u);
 }else if(registration==90){
  if(age==0){
   s.scale.fill(.7f);s.rotation[2]=float(host.random_word()%30u)-15.f;
   s.rotation[1]=float(host.random_word()%30u)-15.f;s.rotation[0]=float(host.random_word()%360u);
  }
  if(age>14)return finish();
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
