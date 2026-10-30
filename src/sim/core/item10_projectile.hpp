#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {
// All nonzero DAT registrations of original handler 00602ee0 (item 10).
// Registration zero remains in roster_motion_projectile.hpp.
inline bool item10_projectile_registration(unsigned item,unsigned registration){
 return item==10&&registration>=10&&registration<=100&&registration%10==0;
}
template<class Host> bool tick_item10_projectile(KeiichiNormalProjectile& s,
                                                 unsigned registration,Host& host){
 if(s.released)return false;
 if(!item10_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item10 registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 auto advance=[&](){++s.frame;host.advance_frame(s);return true;};
 auto target_birth=[&](){
  const int state=host.target_state(s);
  if((state>117&&state<122)||state==221){
   const float target=host.target_elevation(s);
   if(s.pitch-target<10.f||s.pitch-target> -10.f)s.pitch=target;
  }
 };
 auto disable_far_steering=[&](){
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
 };
 auto track_pitch=[&](float threshold,float step){
  const float target=host.target_elevation(s);
  if(s.pitch-target>threshold)s.pitch-=step;
  if(s.pitch-host.target_elevation(s)< -threshold)s.pitch+=step;
 };
 auto fade=[&](){
  s.speed=0;s.capacity.fill(0);
  for(auto& axis:s.scale)axis-=.1f;
  return s.scale[2]<=0.f;
 };
 if((registration==10||registration==20||registration==30||registration==80)&&
    (projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(registration==10){
  if(age==0){
   target_birth();s.speed=40.f;s.capacity.fill(1);
   s.scratch_e8=s.scratch_ec=s.scratch_f0=0;
   host.trail(s,3,100.f,30,1,0);
  }
  s.scratch_f0=std::min(s.scratch_f0+1u,60u);
  disable_far_steering();
  if(s.scratch_e8==0){approach_battle_offset(s.offset,0.f,.75f);track_pitch(1.f,.5f);}
  if(age>240||projectile_contacts(s)!=0||host.stage_collision(s)==1){
   for(unsigned i=0;i<16;++i){
    const float pitch=float(host.random_word()%360u);
    const float yaw=float(host.random_word()%360u);
    host.particle(s,5,yaw,pitch);
   }
   s.scratch_ec=1;return finish();
  }
  return advance();
 }
 if(registration==20||registration==30){
  if(age==0){
   target_birth();s.scratch_e8=s.scratch_ec=0;
   s.scratch_f0=registration==20?40u:0u;
   s.speed=55.f;s.capacity.fill(1);
   host.trail(s,registration==20?0u:3u,90.f,registration==20?20u:30u,1,0);
  }
  s.scratch_f0=std::min(s.scratch_f0+1u,100u);
  disable_far_steering();
  if(s.scratch_e8==0){
   const float step=registration==20?.2f:float(projectile_signed(s.scratch_f0))*.005f+.2f;
   approach_battle_offset(s.offset,0.f,step);
   track_pitch(registration==20?3.f:1.f,registration==20?.2f:.3f);
  }
  if(registration==30&&age%2==0)host.visual_child(s,7);
  if(s.scratch_ec==1&&fade())return finish();
  if(age>360||host.stage_collision(s)==1){s.scratch_ec=1;return true;}
  return advance();
 }
 if(registration==40||registration==50){
  if(age==0){
   s.speed=float(host.random_word()%20u)+10.f;
   s.scale.fill(float(host.random_word()%10u)*.1f+.25f);
   s.scratch_e8=255;
  }
  s.speed-=1.f;if(s.speed<0.f)s.speed=0.f;
  for(auto& axis:s.scale)axis-=.01f;
  if(s.scale[2]<=0.f)return finish();
  const int color=std::max(0,projectile_signed(s.scratch_e8)-10);
  s.scratch_e8=unsigned(color);
  if(registration==40)host.color(s,color,color,color,255);
  else host.color(s,color,255,color,color);
  return advance();
 }
 if(registration==60){
  if(age==0){
   s.speed=10.f;
   s.offset=float(host.random_word()%360u);
   s.pitch=float(host.random_word()%360u);
  }
  for(auto& axis:s.scale)axis-=.1f;
  if(s.scale[2]<=0.f)return finish();
  return advance();
 }
 if(registration==70){
  if(age==0){
   s.scale.fill(.7f);
   s.rotation[2]=float(host.random_word()%30u)-15.f;
   s.rotation[1]=float(host.random_word()%30u)-15.f;
   s.rotation[0]=float(host.random_word()%360u);
  }
  if(age>14)return finish();
  return advance();
 }
 if(registration==80){
  if(age==0){
   s.scale.fill(1.f);s.scratch_e8=s.scratch_ec=s.scratch_f0=0;
   s.speed=45.f;s.capacity.fill(1);
   host.trail(s,0,120.f,30,1,0);
  }
  if(age%5==0)host.visual_child(s,9);
  if(s.scratch_f0==0){
   disable_far_steering();
   if(s.scratch_e8==0){approach_battle_offset(s.offset,0.f,.2f);track_pitch(3.f,.2f);}
   if(projectile_contacts(s)&1){
    s.capacity.fill(1);s.contacts.fill(0);host.target_refresh(s);s.scratch_f0=60;
   }
  }
  if(projectile_signed(s.scratch_f0)>0){
   const float step=float(projectile_signed(s.scratch_f0))*.1f;
   approach_battle_offset(s.offset,0.f,step);
   track_pitch(1.f,step);
   --s.scratch_f0;if(s.scratch_f0==0)s.scratch_f0=1;
  }
  if(s.scratch_ec==1&&fade())return finish();
  if(age>360||host.stage_collision(s)==1){s.scratch_ec=1;return true;}
  return advance();
 }
 if(registration==100)s.scale.fill(3.f);
 if(age>int(registration==90?12:14))return finish();
 return advance();
}
} // namespace daybreak
