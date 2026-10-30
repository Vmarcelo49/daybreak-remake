#pragma once
#include "keiichi_normal_projectile.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {
// Original item 37 handler 6251d0, registration 80. The source rebuilds the
// projectile's orbit from the owner every script visit. Actor +f4 persists
// between writes by character 4 weapon 2's full-shot handler.
template<class Host> bool tick_roster_owner_orbit_projectile(KeiichiNormalProjectile& s,Host& host){
 if(s.released)return false;
 if(unsigned(s.item)!=37)throw std::invalid_argument("Unsupported owner-orbit item");
 if(s.frame==0){
  s.scratch_e8=s.scratch_ec=s.scratch_f8=0;
  s.orbit_angle=s.pitch+90.f;s.orbit_side=90.f-s.pitch;s.speed=0;
 }
 const unsigned command=host.owner_projectile_command(s);
 if(s.scratch_ec==0){
  s.scratch_e8=std::min(s.scratch_e8+7u,90u);
  s.orbit_radius=legacy_trig(float(s.scratch_e8),true)*150.f;
  const float owner_angle=host.owner_heading(s)-90.f;
  const float horizontal=legacy_trig(s.orbit_angle,false)*s.orbit_radius;
  const auto owner_position=host.owner_position(s);
  s.position[0]=owner_position[0]+legacy_trig(owner_angle,false)*horizontal;
  s.position[1]=owner_position[1]+legacy_trig(s.orbit_angle,true)*s.orbit_radius+75.f;
  s.position[2]=owner_position[2]+legacy_trig(owner_angle,true)*horizontal;
  s.heading=host.owner_heading(s);s.offset=host.owner_offset(s);
  s.pitch=std::clamp(host.target_elevation(s),-30.f,30.f);
  if(command==1&&s.scratch_f8==0){host.child(s,9,0,0,false);s.scratch_f8=1;}
  if(command==2)s.scratch_ec=2;
 }
 if(command==2||(host.owner_state(s)>99&&host.owner_state(s)<300)){
  host.retarget_owner(s);host.child(s,13,0,0,false);s.released=true;return false;
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
