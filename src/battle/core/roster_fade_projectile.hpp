#pragma once
#include "keiichi_normal_projectile.hpp"
#include <stdexcept>

namespace daybreak {

// Original 61d920 case 80 and registration-zero handlers 62ae20/6322d0
// share the same stationary white fade.
template<class Host> bool tick_roster_fade_projectile(KeiichiNormalProjectile& s,Host& host){
 if(s.released)return false;
 const unsigned item=unsigned(s.item);
 if(item!=31&&item!=40&&item!=46)throw std::invalid_argument("Unsupported roster fade projectile");
 if(s.frame==0){s.speed=0.f;s.scratch_e8=255;}
 if(projectile_signed(s.frame)>10){
  const auto faded=projectile_signed(s.scratch_e8)-40;
  s.scratch_e8=faded<0?0u:unsigned(faded);
 }
 host.alpha(s,s.scratch_e8&255u);
 if(projectile_signed(s.frame)>15){s.released=true;return false;}
 ++s.frame;host.advance_frame(s);return true;
}

} // namespace daybreak
