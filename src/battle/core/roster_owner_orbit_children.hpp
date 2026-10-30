#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {
// Original item37 handler 6251d0 cases 0x5a, 0x6e, 0x82, 0x8c. These are
// the complete descendant registration chain of the owner-orbit parent.
inline bool roster_owner_orbit_child_registration(unsigned item,unsigned registration){
 return item==37&&(registration==90||registration==110||registration==130||registration==140);
}
template<class Host> bool tick_roster_owner_orbit_child(
 KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 if(!roster_owner_orbit_child_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported owner-orbit child registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 if(registration==90){
  if(age==0){
   approach_battle_offset(s.offset,0.f,10.f);
   host.child(s,11,0,0,false);
   s.speed=60.f;s.capacity.fill(1);
   s.scratch_e8=s.scratch_ec=s.scratch_f0=s.scratch_f4=0;
   s.scale.fill(1.f);
  }
  if(host.stage_collision(s)==1&&host.stage_collision(s)==1)s.scratch_f0=1;
  if(s.scratch_f0==1){
   s.speed=0;
   for(auto& axis:s.scale)axis-=.05f;
   if(s.scale[0]<=0.f)return finish();
  }
  s.scratch_ec=std::min(s.scratch_ec+2u,100u);
  ++s.scratch_f4;
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(age==60){s.frame=40;return true;}
  if(projectile_signed(s.scratch_f4)>180)return finish();
 }else if(registration==110){
  if(age==0){
   s.scratch_e8=255;
   s.rotation[1]=float(host.random_word()%360u);
   s.scale.fill(.05f);s.speed=0;
  }
  const float growth=legacy_trig(float(age*3),false)*.025f;
  for(auto& axis:s.scale)axis+=growth;
  if(age>6){
   const int alpha=projectile_signed(s.scratch_e8)-10;
   s.scratch_e8=std::uint32_t(alpha<0?0:alpha);
   if(alpha<0)return finish();
  }
  host.alpha(s,s.scratch_e8&255u);
 }else if(registration==130){
  if(age==0){s.speed=0;s.scratch_e8=s.scratch_ec=0;s.scratch_f0=180;}
  approach_battle_offset(s.offset,0.f,180.f);
  s.pitch=host.target_elevation(s);
  s.speed=80.f;
  if(host.target_distance_squared(s)<10000.f){
   for(unsigned n=0;n<3;++n)host.child(s,14,0,0,false);
   return finish();
  }
 }else{
  if(age==0){
   s.pitch=float(host.random_word()%360u);
   s.offset=float(host.random_word()%360u);
   s.speed=float(host.random_word()%20u)+2.f;
   s.rotation[1]=float(host.random_word()%360u);
  }
  s.speed*=.95f;
  if(age>59)return finish();
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
