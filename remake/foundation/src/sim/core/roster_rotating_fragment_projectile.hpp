#pragma once
#include "keiichi_normal_projectile.hpp"

namespace daybreak {
// Original item handlers 5fdee0/62ae20/62e5d0: DAT-listed visual fragments
// spawned by actor shot scripts and item40 children. No stage, contact or
// owner-state query occurs in these switch cases. RNG calls retain their order.
inline bool roster_rotating_fragment_registration(unsigned item,unsigned registration){
 return (item==6&&registration==90)||
        (item==40&&(registration==10||registration==20||registration==70||registration==90))||
        (item==42&&registration==90);
}
template<class Host> bool tick_roster_rotating_fragment_projectile(
 KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 const unsigned item=unsigned(s.item);
 if(!roster_rotating_fragment_registration(item,registration))
  throw std::runtime_error("Unsupported rotating fragment registration");
 const bool falling=item==42;
 if(s.frame==0){
  if(falling){
   s.scale.fill(5.f);
   s.speed=float(host.random_word()%20u)*.1f+2.f;
   s.rotation[1]=float(host.random_word()%360u);
   s.pitch=90.f;
  }else{
   s.scale.fill(item==40&&(registration==70||registration==90)?1.5f:.7f);
   s.rotation[2]=float(host.random_word()%30u)-15.f;
   s.rotation[1]=float(host.random_word()%30u)-15.f;
   s.rotation[0]=float(host.random_word()%360u);
  }
 }
 if(projectile_signed(s.frame)>(falling?29:14)){
  s.released=true;return false;
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
