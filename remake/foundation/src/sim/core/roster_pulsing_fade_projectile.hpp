#pragma once
#include "keiichi_normal_projectile.hpp"
#include <stdexcept>

namespace daybreak {

// The registration-40 branches in original handlers 605750 and 62e5d0 are
// identical: a stationary pulse whose opacity declines before age 21 release.
inline bool roster_pulsing_fade_registration(unsigned item,unsigned registration){
 return registration==40&&(item==12||item==42);
}
template<class Host> bool tick_roster_pulsing_fade_projectile(
 KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 if(!roster_pulsing_fade_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported pulsing-fade projectile registration");
 const int age=projectile_signed(s.frame);
 if(age==0){s.scale.fill(.5f);s.speed=0;s.capacity.fill(1);s.scratch_e8=255;}
 const float growth=legacy_trig(float(age*4),false)*.2f;
 for(auto& axis:s.scale)axis+=growth;
 if(age>0){
  const int alpha=projectile_signed(s.scratch_e8)-13;
  s.scratch_e8=unsigned(alpha<0?0:alpha);
 }
 if(age>20){s.released=true;return false;}
 host.alpha(s,s.scratch_e8&255u);
 ++s.frame;host.advance_frame(s);return true;
}

} // namespace daybreak
