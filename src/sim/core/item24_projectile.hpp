#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {
// Item 24, original 00616aa0. Registrations 0 and 70 already use their
// recovered cadence implementation; these are the remaining DAT routes.
inline bool item24_projectile_registration(unsigned item,unsigned registration){
 return item==24&&registration<=90&&registration%10==0&&registration!=0&&registration!=70;
}
template<class Host> bool tick_item24_projectile(KeiichiNormalProjectile& s,
                                                  unsigned registration,Host& host){
 if(s.released)return false;
 if(!item24_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item24 registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 auto advance=[&](){++s.frame;host.advance_frame(s);return true;};
 if(registration==10){
  if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
  if(age==0){s.speed=75.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;s.scale.fill(2.f);}
  for(auto& axis:s.scale)axis-=.1f;
  if(age%2==0)host.visual_child(s,7);
  if(s.scratch_e8==0){
   approach_battle_offset(s.offset,0.f,.1f);
   const float target=host.target_elevation(s);
   if(s.pitch-target>1.f)s.pitch-=.1f;
   if(s.pitch-host.target_elevation(s)<-1.f)s.pitch+=.1f;
  }
  if(age>20||host.stage_collision(s)==1)return finish();
  return advance();
 }
 if(registration==20||registration==30){
  if(age==0){s.scale.fill(.25f);s.speed=0.f;s.scratch_e8=255;}
  const float growth=legacy_trig(float(age*5),false)*.05f;
  for(auto& axis:s.scale)axis+=growth;
  if(age>0)s.scratch_e8=unsigned(std::max(0,projectile_signed(s.scratch_e8)-15));
  if(age>18)return finish();
  const unsigned color=s.scratch_e8&255u;
  host.color(s,color,color,color,255);
  return advance();
 }
 if(registration==60){
  if(age==0)s.speed=0.f;
  if(age>15)return finish();
  s.scratch_ec=std::uint32_t(std::min(30,projectile_signed(s.scratch_ec)+1));
  if(s.offset>90.f||s.offset<-90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0&&age>0){
   approach_battle_offset(s.offset,0.f,float(projectile_signed(s.scratch_ec))*.033f);
   const float target=host.target_elevation(s);
   if(s.pitch-target>3.f)s.pitch-=.5f;
   if(s.pitch-host.target_elevation(s)<-3.f)s.pitch+=.5f;
  }
  s.speed=std::max(20.f,s.speed-1.f);
  return advance();
 }
 if(registration==80){
  if(age==0){s.scale.fill(0.f);s.speed=50.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;}
  if(age%3==0)host.visual_child(s,9);
  if(age>40||host.stage_collision(s)==1)return finish();
  return advance();
 }
 if(registration==90){
  if(age==0){
   s.scale.fill(1.5f);
   s.rotation[2]=float(host.random_word()%30u)-15.f;
   s.rotation[1]=float(host.random_word()%30u)-15.f;
   s.rotation[0]=float(host.random_word()%360u);
  }
  if(age>14)return finish();
  return advance();
 }
 // 40 and 50 have no case in 00616aa0; the original only advances animation.
 return advance();
}
} // namespace daybreak
