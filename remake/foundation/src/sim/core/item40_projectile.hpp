#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <stdexcept>

namespace daybreak {
// Original 0062ae20, item 40. Registrations 0, 10, 20, 70 and 90 are
// handled by the existing fade/rotating-fragment families.
inline bool item40_projectile_registration(unsigned item,unsigned registration){
 return item==40&&(registration==30||registration==40||registration==50||
                   registration==60||registration==80);
}
template<class Host> bool tick_item40_projectile(KeiichiNormalProjectile& s,
                                                  unsigned registration,Host& host){
 if(s.released)return false;
 if(!item40_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item40 registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 auto advance=[&](){++s.frame;host.advance_frame(s);return true;};
 if((registration==40||registration==50)&&(projectile_contacts(s)&0x100))
  reflect_normal_projectile(s);
 if(registration==30){
  if(age==0){s.scale.fill(.25f);s.speed=0.f;s.scratch_e8=255;}
  const float growth=legacy_trig(float(age*5),false)*.05f;
  for(auto& axis:s.scale)axis+=growth;
  if(age>0){
   const int faded=projectile_signed(s.scratch_e8)-15;
   s.scratch_e8=faded<0?0u:unsigned(faded);
  }
  if(age>18)return finish();
  const unsigned color=s.scratch_e8&255u;
  host.color(s,color,color,color,255);
  return advance();
 }
 if(registration==40||registration==50){
  if(age==0){
   s.speed=registration==40?75.f:80.f;s.capacity.fill(1);
   s.scratch_e8=s.scratch_ec=0;
   s.scale.fill(registration==40?2.f:3.f);
  }
  for(auto& axis:s.scale)axis-=.05f;
  if((age&1)==0)host.visual_child(s,registration==40?1u:2u);
  if(s.scratch_e8==0){
   approach_battle_offset(s.offset,0.f,.2f);
   const float elevation=host.target_elevation(s);
   if(s.pitch-elevation>1.f)s.pitch-=.1f;
   if(s.pitch-host.target_elevation(s)<-1.f)s.pitch+=.1f;
  }
  if(age>(registration==40?40:60)||host.stage_collision(s)==1)return finish();
  return advance();
 }
 if(registration==60){
  if(age==0){s.speed=0.f;s.scratch_e8=255;}
  if(age>10){
   const int faded=projectile_signed(s.scratch_e8)-40;
   s.scratch_e8=faded<0?0u:unsigned(faded);
  }
  host.alpha(s,s.scratch_e8&255u);
  if(age>15)return finish();
  return advance();
 }
 if(age==0){
  s.scale.fill(0.f);s.speed=50.f;s.capacity.fill(1);
  s.scratch_e8=s.scratch_ec=0;
 }
 if(age%3==0)host.visual_child(s,9);
 if(age>40||host.stage_collision(s)==1)return finish();
 return advance();
}
} // namespace daybreak
