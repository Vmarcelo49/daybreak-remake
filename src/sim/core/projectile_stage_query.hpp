#pragma once
#include "keiichi_normal_projectile.hpp"
namespace daybreak {
// 5f6a90: +130 direction cache; query only when the three float components
// change. Position and speed do not invalidate the original cache. The host
// supplies a world-distance ray query, whose D3DX backend remains provisional.
template<class Closest> unsigned query_projectile_stage(KeiichiNormalProjectile& s,
 std::array<float,3>& cached_velocity,Closest&& closest,bool enabled=true){
 if(!enabled||(s.angular&&s.speed==0.f))return 0;
 if(cached_velocity!=s.velocity){
  cached_velocity=s.velocity;
  s.remaining_stage_distance=closest(s.position,s.velocity);
 }
 const float travel=s.angular?s.speed:projectile_motion_length(s.velocity);
 return travel>=s.remaining_stage_distance?1u:0u;
}
}
