#pragma once
#include "keiichi_normal_projectile.hpp"
#include "item30_projectile.hpp"
#include <cmath>
#include <stdexcept>

namespace daybreak {

// Original registration-zero handlers 5f91c0 and 61b8e0 share normal-shot
// steering. Item30's registration zero is served by its full item switch.
template<class Host> bool tick_roster_homing_projectile(KeiichiNormalProjectile& s,Host& host){
 if(s.released)return false;
 const unsigned item=unsigned(s.item);
 if(item==30)return tick_item30_projectile(s,0,host);
 if(item!=1&&item!=29)throw std::invalid_argument("Unsupported roster homing projectile");
 if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
 const float step=item==29?.1f:.2f;
 if(s.frame==0){
  const int target_state=host.target_state(s);
  if((target_state>117&&target_state<122)||target_state==221)
   s.pitch=host.target_elevation(s);
  const auto& profile=roster_projectile_birth_profiles[item];
  s.speed=profile.speed;s.capacity.fill(profile.capacity);
  s.scratch_e8=s.scratch_ec=0;
 }
 ++s.scratch_ec;if(projectile_signed(s.scratch_ec)>75)s.scratch_ec=75;
 if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
 if(s.scratch_e8==0){
  if(std::abs(s.offset)<step)s.offset=0;
  else if(s.offset<0)s.offset+=step;
  else if(s.offset>0)s.offset-=step;
  const float target_pitch=host.target_elevation(s);
  if(s.pitch-target_pitch>3.f)s.pitch-=step;
  if(s.pitch-target_pitch< -3.f)s.pitch+=step;
 }
 const auto contact=projectile_contacts(s);
 const bool expire=projectile_signed(s.frame)>240;
 if(item==1&&host.stage_collision(s)==1){host.visual_child(s,5);s.released=true;return false;}
 if(expire||(contact!=0&&contact!=1)){s.released=true;return false;}
 if(item!=1&&host.stage_collision(s)==1){
  s.released=true;return false;
 }
 ++s.frame;host.advance_frame(s);return true;
}

} // namespace daybreak
