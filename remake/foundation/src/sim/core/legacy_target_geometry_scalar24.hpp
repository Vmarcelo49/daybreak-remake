#pragma once
#include "legacy_stage_intersection_scalar24.hpp"
namespace daybreak {
struct LegacyTargetGeometry {
 float dx=0,dz=0,x_squared=0,z_squared=0,squared=0,horizontal=0,vertical=0;
 double angle=0;float degrees=0;
};
// 42d980/42d9d0 ->40da40/40dd60: exponent2 returns each stored float square.
// 42da80/42dac0 store the sum/sqrt/vertical arguments before CRT atan2.
// CRT66c540 uses PC64 internally and restores PC24;4235be FST does not
// narrow the returned ST0. Only the final degree caller store narrows again.
// std::atan2 is the portable PC64 backend, verified against retained native
// finite profiles; arbitrary CRT/host floating-point parity is not claimed.
inline LegacyTargetGeometry legacy_target_geometry_scalar24(const std::array<float,3>& from,
 const std::array<float,3>& target){
 LegacyTargetGeometry out;
 out.dx=float(legacy_stage_sub24(from[0],target[0]));
 out.dz=float(legacy_stage_sub24(from[2],target[2]));
 out.x_squared=float(legacy_stage_mul24(out.dx,out.dx));
 out.z_squared=float(legacy_stage_mul24(out.dz,out.dz));
 out.squared=float(legacy_stage_add24(out.z_squared,out.x_squared));
 out.horizontal=float(std::sqrt(double(out.squared)));
 out.vertical=float(legacy_stage_sub24(target[1],from[1]));
 out.angle=std::atan2(double(out.vertical),double(out.horizontal));
 const double turns=legacy_stage_round24(out.angle/3.1415927410125732421875);
 out.degrees=float(legacy_stage_mul24(turns,180.));return out;
}
}
