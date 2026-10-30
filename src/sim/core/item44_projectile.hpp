#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {
// Original 006305b0. Registrations 0/70 retain their already recovered
// simple-family implementation; these are the remaining eight DAT cases.
inline bool item44_projectile_registration(unsigned item,unsigned registration){
 return item==44&&registration<=90&&registration%10==0&&registration!=0&&registration!=70;
}
template<class Host> bool tick_item44_projectile(KeiichiNormalProjectile& s,
                                                  unsigned registration,Host& host){
 if(s.released)return false;
 if(!item44_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item44 registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 auto advance=[&](){++s.frame;host.advance_frame(s);return true;};
 if((registration==10||registration==20||registration==30)&&
    (projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(registration==10||registration==20||registration==30){
  if(age==0){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
   s.speed=registration==10?60.f:45.f;s.capacity.fill(1);s.scratch_e8=0;
   if(registration==10)host.trail(s,0,10.f,20,1,0);
   else s.scratch_ec=40;
  }
  if(registration==10){
   if(age>180||projectile_contacts(s)!=0||host.stage_collision(s)==1)
    return finish();
   return advance();
  }
  if(age%2==0)host.visual_child(s,8);
  s.scratch_ec=std::min(s.scratch_ec+1u,100u);
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   const float step=float(projectile_signed(s.scratch_ec))*.0025f;
   approach_battle_offset(s.offset,0.f,step);
   const float target=host.target_elevation(s);
   if(s.pitch-target>3.f)s.pitch-=step;
   if(s.pitch-host.target_elevation(s)< -3.f)s.pitch+=step;
  }
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1){
   host.sound(s,204);host.child(s,registration==20?4:5,0,0,false);
   host.visual_child(s,9);return finish();
  }
  if(age>240)return finish();
  return advance();
 }
 if(registration==40||registration==50){
  const float growth=registration==40?.2f:.5f;
  const float maximum=registration==40?3.f:5.f;
  s.pitch=0.f;s.rotation[0]+=1.f;
  if(age==0)s.scale[0]=s.scale[2]=0.f;
  if(s.scale[2]>=maximum)s.scale[0]=s.scale[2]=maximum;
  else{
   const float pulse=legacy_trig(float(age*3),true)*growth;
   s.scale[2]+=pulse;s.scale[0]+=pulse;
  }
  if(age%30==0){s.capacity.fill(1);s.contacts.fill(0);}
  if(age%3==0){
   s.scratch_e8=host.random_word()%360u;
   s.scratch_ec=host.random_word()%(registration==40?300u:500u);
   const float angle=float(s.scratch_e8),radius=float(s.scratch_ec);
   host.particle_offset(s,6,legacy_trig(angle,false)*radius,0.f,
                        legacy_trig(angle,true)*radius);
  }
  if(age<361)s.scale[1]=legacy_trig(float(age*6),true)*.25f+.75f;
  else{
   s.capacity.fill(0);s.scale[1]-=.1f;
   if(s.scale[1]<=0.f)return finish();
  }
  return advance();
 }
 if(registration==60){
  if(age==0){
   s.scale.fill(5.f);
   s.speed=float(host.random_word()%20u)*.1f+2.f;
   s.rotation[1]=float(host.random_word()%360u);
   s.pitch=90.f;
  }
  if(age>29)return finish();
  return advance();
 }
 if(registration==80){if(age>29)return finish();return advance();}
 if(age==0)s.capacity.fill(1);
 if(age>51)return finish();
 return advance();
}
} // namespace daybreak
