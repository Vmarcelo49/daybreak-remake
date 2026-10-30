#pragma once
#include "keiichi_normal_projectile.hpp"
#include <stdexcept>

namespace daybreak {

// Original 00620290 cases 10/30. The two DAT registrations differ only in
// launch speed and initial scale; the direct-flight and opacity script is shared.
inline bool item33_direct_fade_registration(unsigned item,unsigned registration){
 return item==33&&(registration==10||registration==30);
}

template<class Host> bool tick_item33_direct_fade_projectile(
 KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 if(!item33_direct_fade_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item33 direct-fade registration");
 const int age=projectile_signed(s.frame);
 if(age==0){
  s.speed=registration==10?20.f:35.f;
  if(registration==30)s.scale.fill(.5f);
  s.capacity.fill(1);s.scratch_e8=255;
 }
 if(age==1)normal_projectile_direct_velocity(s);
 s.velocity[1]-=1.f;
 if(host.stage_collision(s)==1){s.released=true;return false;}
 if(age>60){
  s.capacity.fill(0);
  const int opacity=projectile_signed(s.scratch_e8)-13;
  s.scratch_e8=static_cast<std::uint32_t>(opacity);
  if(opacity<0){s.scratch_e8=0;s.released=true;return false;}
  host.alpha(s,s.scratch_e8&255u);
 }
 ++s.frame;host.advance_frame(s);return true;
}

} // namespace daybreak
