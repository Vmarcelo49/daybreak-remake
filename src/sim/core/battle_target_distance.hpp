#pragma once
#include "legacy_stage_intersection_scalar24.hpp"
namespace daybreak {
// 42d980 ->40da40/40dd60: coordinate differences and each power2 are
// DWORD floats. The final PC24 addition returns ST0 without a DWORD store.
inline double battle_target_distance_squared(const std::array<float,3>& from,const std::array<float,3>& target){
 const float dx=float(legacy_stage_sub24(from[0],target[0]));
 const float dz=float(legacy_stage_sub24(from[2],target[2]));
 const float x_squared=float(legacy_stage_mul24(dx,dx));
 const float z_squared=float(legacy_stage_mul24(dz,dz));
 return legacy_stage_add24(z_squared,x_squared);
}
}
