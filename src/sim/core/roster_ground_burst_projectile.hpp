#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <stdexcept>

namespace daybreak {
// Original 6322d0 cases 0x0a/0x28/0x32/0x3c. Script updates precede
// ground motion and contact.
inline bool roster_ground_burst_registration(unsigned item,unsigned registration){
 return item==46&&(registration==10||registration==40||registration==50||registration==60);
}
template<class Host> bool tick_roster_ground_burst_projectile(
 KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 if(!roster_ground_burst_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported ground-burst registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 if(registration==10){
  if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
  if(age==0){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221){
    const float target=host.target_elevation(s);
    if(s.pitch-target<10.f||s.pitch-target> -10.f)s.pitch=target;
   }
   s.scale.fill(2.f);s.speed=60.f;s.capacity.fill(1);
  }
  if(host.stage_collision(s)==1||age>10){
   s.capacity.fill(0);
   for(auto& axis:s.scale)axis-=.2f;
   if(s.scale[0]<=0.f)return finish();
  }
 }else if(registration==40){
  if(age==0){
   s.ground_motion=true;s.speed=60.f;s.capacity.fill(99);
   s.scratch_e8=s.scratch_ec=0;s.rotation[1]=45.f;
  }
  ++s.scratch_e8;
  if(projectile_signed(s.scratch_e8)>10){s.scratch_e8=0;s.contacts.fill(0);}
  if(s.scratch_e8==0&&age>0)approach_battle_offset(s.offset,0.f,1.f);
  if((s.frame&1u)==0){host.child(s,5,0,0,false);host.child(s,6,0,0,false);}
  if(!s.surface_flag){
   s.velocity[1]-=.5f;
   ++s.scratch_ec;
   if(projectile_signed(s.scratch_ec)>20)return finish();
  }else s.velocity[1]=0;
  if(age>120){s.capacity.fill(0);return finish();}
 }else if(registration==50){
  if(age==0){
   s.rotation[1]=float(host.random_word()%50u)-25.f;
   s.rotation[2]=float(host.random_word()%50u)-25.f;
  }
  s.scale[0]*=.8f;s.scale[1]+=.1f;s.scale[2]*=.8f;
  if(s.scale[2]<.05f)return finish();
 }else{
  if(age==0){
   s.capacity.fill(1);s.contacts.fill(0);s.scale.fill(.5f);
   s.scratch_e8=255;s.rotation[1]=float(host.random_word()%360u);
  }
  const float growth=legacy_trig(float(age)*4.f,false)*.1f;
  for(auto& axis:s.scale)axis+=growth;
  if(age==6)s.capacity.fill(0);
  if(age>10){
   const int alpha=projectile_signed(s.scratch_e8)-13;
   s.scratch_e8=std::uint32_t(alpha<0?0:alpha);
  }
  const unsigned color=s.scratch_e8&255u;
  host.color(s,color,color,color,255);
  if(projectile_signed(s.scratch_e8)<1)return finish();
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
