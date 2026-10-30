#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {
// Original item38 handler 00626f30: enhanced accelerating shots, the slow
// three-way shell, and the short fields produced by their impact callbacks.
inline bool item38_secondary_registration(unsigned item,unsigned registration){
 return item==38&&(registration==40||registration==50||registration==60||
                   registration==70||registration==80||registration==90||
                   registration==100||registration==110);
}
template<class Host> bool tick_item38_secondary_projectile(
 KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 if(!item38_secondary_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item38 secondary projectile registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 if(registration==40||registration==50){
  const bool large=registration==50;
  if(age==0){
   s.turn_rate=0;s.scratch_e8=0;s.speed=5;s.capacity.fill(1);
   s.scale.fill(large?6.5f:4.f);
   if(large)host.trail(s,2,200.f,25,1,0);
  }
  if(age%3==0)host.visual_child(s,3);
  s.speed=std::min(large?120.f:100.f,s.speed+(large?.75f:.5f));
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   approach_battle_offset(s.offset,0.f,large?1.f:.75f);
   const float target=host.target_elevation(s),step=large?.2f:.1f;
   if(s.pitch-target>1.f)s.pitch-=step;
   if(s.pitch-host.target_elevation(s)< -1.f)s.pitch+=step;
  }
  if(host.stage_collision(s)==1||projectile_contacts(s)!=0||age>240){
   host.sound(s,74);host.child(s,6,0,0,false);return finish();
  }
 }else if(registration==60){
  if(age==0){s.scale.fill(2.f);s.speed=0;s.velocity[1]=0;s.capacity.fill(1);}
  if(age>51)return finish();
 }else if(registration==70){
  if(age==0){
   s.turn_rate=0;s.speed=30;s.capacity.fill(1);s.scale.fill(6.f);
   s.contacts.fill(0);
  }
  s.speed=std::max(4.f,s.speed-.5f);
  if(age%4==0){
   const float pitch_offset=float(host.random_word()%20u)-10.f-2.f*s.pitch;
   const float yaw_offset=float(host.random_word()%20u)+170.f;
   auto particle=s;
   for(unsigned i=0;i<3;++i)particle.position[i]-=150.f*s.velocity[i];
   host.particle(particle,11,yaw_offset,pitch_offset);
  }
  approach_battle_offset(s.offset,0.f,.75f);
  const float target=host.target_elevation(s);
  if(s.pitch-target>1.f)s.pitch-=.3f;
  if(s.pitch-host.target_elevation(s)< -1.f)s.pitch+=.3f;
  if((age>10&&host.stage_collision(s)==1)||projectile_contacts(s)!=0){
   host.sound(s,157);
   host.child(s,8,0,0,false);host.child(s,9,0,0,false);
   host.child(s,10,0,0,false);return finish();
  }
  if(age>1200)return finish();
 }else if(registration==80||registration==90||registration==100){
  if(age==0){
   s.rotation[0]=s.rotation[1]=0;s.rotation[2]=-s.pitch;
   s.speed=0;s.velocity[1]=0;s.scratch_e8=0;s.scratch_ec=255;
   if(registration!=100)s.capacity.fill(registration==80?1:0);
   s.scale.fill(registration==80?4.5f:registration==90?8.f:6.f);
  }
  const float delta=registration==80?(s.scale[0]>=10.f?.0035f:.25f):
    registration==90?(s.scale[0]>=14.f?.005f:.5f):1.f;
  for(auto& axis:s.scale)axis+=delta;
  if(registration==90&&age==17){s.frame=1;return true;}
  if(registration!=100)++s.scratch_e8;
  if(registration==80){
   if(s.scratch_e8>20)s.capacity.fill(0);
   if(s.scratch_e8>90){
    s.scratch_ec-=5;
    if(projectile_signed(s.scratch_ec)<0){s.scratch_e8=0;return finish();}
   }
  }else if(registration==90){
   if(s.scratch_e8>10&&s.scratch_e8%5==0&&s.scratch_e8<120){
    s.capacity.fill(1);s.contacts.fill(0);
   }
   if(s.scratch_e8>120){
    s.capacity.fill(0);s.scratch_ec-=5;
    if(projectile_signed(s.scratch_ec)<0){s.scratch_e8=0;return finish();}
   }
  }else if(age>60){
   s.capacity.fill(0);s.scratch_ec-=15;
   if(projectile_signed(s.scratch_ec)<0){s.scratch_e8=0;return finish();}
  }
  host.alpha(s,s.scratch_ec&255u);
 }else{
  // Registration 110 is the visual-only trail emitted by registration 70.
  // Retiring it after the original fade avoids a growing pool of generic
  // 241-frame visuals during a long shell flight.
  if(age==0){
   s.scratch_e8=255;s.turn_rate=10;
   s.rotation[1]=float(host.random_word()%360u);
   s.speed=30;s.scratch_ec=host.random_word()%100u;
  }
  s.speed=std::max(1.f,s.speed-.5f);
  s.turn_rate=std::max(1.f,s.turn_rate-.5f);
  if(s.scratch_ec<50)s.rotation[1]+=s.turn_rate;
  else s.rotation[1]-=s.turn_rate;
  if(age>4){
   s.scratch_e8-=10;
   if(projectile_signed(s.scratch_e8)<0){s.scratch_e8=0;return finish();}
  }
  host.alpha(s,s.scratch_e8&255u);
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
