#pragma once
#include "keiichi_normal_projectile.hpp"
#include <stdexcept>

namespace daybreak {
// Both impact children use the same original case 0x8c in handlers 605d60
// and 62f180. They are real DAT bullet registrations, not visual pool entries.
inline bool roster_impact_spark_registration(unsigned item,unsigned registration){
 return (item==13||item==43)&&registration==140;
}
template<class Host> bool tick_roster_impact_spark_projectile(
 KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 if(!roster_impact_spark_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported impact-spark projectile registration");
 const int age=projectile_signed(s.frame);
 s.pitch=0;s.rotation[0]+=1.f;
 if(age==0)s.scale.fill(.5f);
 if(age%5==0){
  const float z=float(host.random_word()%200u)-100.f;
  const float x=float(host.random_word()%200u)-100.f;
  host.particle_offset(s,8,x,0.f,z);
 }
 if(age>0){
  s.capacity.fill(0);
  s.scale[1]-=.025f;s.scale[0]+=.05f;s.scale[2]+=.05f;
  if(s.scale[1]<=0.f){s.released=true;return false;}
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
