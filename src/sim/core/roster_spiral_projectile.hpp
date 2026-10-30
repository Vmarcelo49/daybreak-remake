#pragma once
#include "keiichi_normal_projectile.hpp"
#include <stdexcept>

namespace daybreak {
// Original item 37 handler 0x6251d0, registrations 40/50/60/70. The four
// weapon-DAT entries share one lifetime and turn clock; only the turn side
// alternates. Script update runs before the shared projectile movement.
inline bool roster_spiral_projectile_registration(unsigned item,unsigned registration){
 return item==37&&(registration==40||registration==50||registration==60||registration==70);
}
template<class Host> bool tick_roster_spiral_projectile(
 KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 if(!roster_spiral_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item 37 spiral registration");
 if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
 const int age=projectile_signed(s.frame);
 if(age==0){
  s.scale.fill(1.f);s.capacity.fill(1);
  const int state=host.target_state(s);
  if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
  s.speed=42.5f;s.scratch_e8=0;s.scratch_ec=120;s.scratch_f0=0;
 }
 const int clock=projectile_signed(s.scratch_ec)-1;
 s.scratch_ec=unsigned(clock<0?0:clock);
 const float turn=float(projectile_signed(s.scratch_ec))*.01f;
 s.heading+=(registration==40||registration==60)?turn:-turn;
 if(age>240||host.stage_collision(s)==1){s.released=true;return false;}
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
