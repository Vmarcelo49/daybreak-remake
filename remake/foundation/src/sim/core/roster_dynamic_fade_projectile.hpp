#pragma once
#include "keiichi_normal_projectile.hpp"
#include <stdexcept>

namespace daybreak {

// Original handlers 60fd10 and 611e30 use different motion and opacity
// counters. Item 19 registrations 0/10 share a data-driven fade. Registration
// 80 is the separate full-shot script in
// 60fd10; its frame cursor deliberately stops at age 20 while opacity fades.
template<class Host> bool tick_roster_dynamic_fade_projectile(KeiichiNormalProjectile& s,Host& host,unsigned registration=0){
 if(s.released)return false;
 const unsigned item=unsigned(s.item);
 if(item==19&&registration==80){ // Original 60fd10 case 0x50, full-shot.
  if(s.frame==0){
   s.scale.fill(.2f);s.speed=50.f;s.capacity.fill(1);
   s.scratch_e8=255;s.scratch_ec=0;
  }
  for(auto& axis:s.scale)axis+=.01f;
  if(s.scale[0]>.5f)s.scale.fill(.5f);
  ++s.scratch_ec;
  if(host.stage_collision(s)==1){s.released=true;return false;}
  if(projectile_signed(s.scratch_ec)>40){
   s.capacity.fill(0);
   const int faded=projectile_signed(s.scratch_e8)-13;
   s.scratch_e8=std::uint32_t(faded);
   if(faded<0){s.released=true;return false;}
  }
  const unsigned color=s.scratch_e8&255u;
  host.color(s,color,255,color,color);
  if(s.frame==20)return true; // Source holds the frame cursor while fading.
  ++s.frame;host.advance_frame(s);return true;
 }
 if(item==19){
  if(registration!=0&&registration!=10)throw std::invalid_argument("Unsupported item19 dynamic fade registration");
  const bool heavier=registration==10;
  if(s.frame==0){
   s.scale.fill(1.f);s.speed=heavier?45.f:40.f;
   s.scratch_e8=255;s.scratch_ec=s.scratch_f0=0;
   s.capacity.fill(1);
   normal_projectile_direct_velocity(s);
   s.ground_motion=true;
  }
  s.frame=1;
  ++s.scratch_ec;
  host.color(s,s.scratch_e8&255u,s.scratch_e8&255u,s.scratch_e8&255u,255);
  for(auto& axis:s.scale)axis+=heavier?.1f:.05f;
  s.speed-=heavier?.65f:.75f;
  s.velocity[1]=legacy_trig(s.pitch,true)*s.speed;
  if(s.surface_flag)s.speed*=.75f;
  if(s.speed<3.f)s.speed=3.f;
  if(projectile_signed(s.scratch_ec)>40||s.wall_contact||projectile_contacts(s)!=0)s.scratch_f0=1;
  if(projectile_signed(s.scratch_f0)>0){
   const auto faded=projectile_signed(s.scratch_e8)-5;
   s.scratch_e8=static_cast<std::uint32_t>(faded);
   if(faded<64)s.capacity.fill(0);
   if(faded<0){s.scratch_e8=0;s.released=true;return false;}
  }
  ++s.frame;host.advance_frame(s);return true;
 }
 if(item==21){
  if(registration!=0&&registration!=10)throw std::invalid_argument("Unsupported item21 dynamic fade registration");
  const bool wide=registration==10;
  if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
  if(s.frame==0){
   s.speed=wide?45.f:35.f;s.capacity.fill(1);
   s.scratch_e8=0;s.scratch_ec=255;s.scratch_f0=1;
  }
  s.scratch_f0+=5;
  if(projectile_signed(s.scratch_f0)>90)s.scratch_f0=90;
  if(projectile_signed(s.scratch_f0)<0)s.scratch_f0=0;
  const float size=legacy_trig(float(projectile_signed(s.scratch_f0)),true)*(wide?.85f:.5f);
  s.scale.fill(size);
  ++s.scratch_e8;
  const int fade_after=wide?90:50;
  if(projectile_signed(s.scratch_e8)>fade_after){
   const auto faded=projectile_signed(s.scratch_ec)-20;
   s.scratch_ec=static_cast<std::uint32_t>(faded);
   s.capacity.fill(0);
   if(faded<0){s.scratch_ec=0;s.released=true;return false;}
  }
  host.alpha(s,s.scratch_ec&255u);
  if(host.stage_collision(s)==1&&projectile_signed(s.scratch_e8)<fade_after)s.scratch_e8=std::uint32_t(fade_after);
  if(s.frame==20)return true;
  ++s.frame;host.advance_frame(s);return true;
 }
 throw std::invalid_argument("Unsupported roster dynamic fade projectile");
}

} // namespace daybreak
