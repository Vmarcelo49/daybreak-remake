#pragma once
#include "legacy_stage_intersection_scalar24.hpp"
#include "keiichi_normal_projectile.hpp"
#include "legacy_asin_domain.hpp"
namespace daybreak {
// Degree arithmetic keeps PC24's exponent until the caller DWORD store.
inline double projectile_birth_degrees_scalar24(double angle){
 return legacy_stage_mul24(legacy_stage_round24(angle/3.1415927410125732421875),180.);
}
// Actual CRT66c708 arithmetic before FPATAN, at PC24.436625 FST is only
// diagnostic: retain the returned wide angle for the following degree graph.
// Default masked out-of-domain results follow the original CRT bit pattern.
inline double projectile_birth_asin_scalar24(float y){
 if(legacy_asin_outside_unit(y))return double(legacy_asin_domain_result(y));
 const auto product=legacy_stage_mul24(legacy_stage_add24(1.,y),legacy_stage_sub24(1.,y));
 const double adjacent=legacy_stage_round24(std::sqrt(product));
 return std::atan2(double(y),adjacent);
}
struct ProjectileBirthAngles {
 float heading=0,offset=0,pitch=0;
 double target_angle=0,vector_angle=0,elevation_angle=0;
};
// Common5f5ca4..5f5d45: root facing, raw atan2(Z,X)-heading, raw asin(Y).
// No direction normalization/clamp and no parent angular-field inheritance.
inline ProjectileBirthAngles projectile_birth_angles_scalar24(const std::array<float,3>& position,
 const std::array<float,3>& target,const std::array<float,3>& direction){
 ProjectileBirthAngles out;
 const float dx=float(legacy_stage_sub24(target[0],position[0])),dz=float(legacy_stage_sub24(target[2],position[2]));
 out.target_angle=std::atan2(double(dz),double(dx));out.heading=float(projectile_birth_degrees_scalar24(out.target_angle));
 out.vector_angle=std::atan2(double(direction[2]),double(direction[0]));
 out.offset=float(legacy_stage_sub24(projectile_birth_degrees_scalar24(out.vector_angle),out.heading));
 if(out.offset>180.f)out.offset=float(legacy_stage_sub24(out.offset,360.));
 if(out.offset< -180.f)out.offset=float(legacy_stage_add24(out.offset,360.));
 out.elevation_angle=projectile_birth_asin_scalar24(direction[1]);out.pitch=float(projectile_birth_degrees_scalar24(out.elevation_angle));return out;
}
inline void initialize_projectile_birth_angles(KeiichiNormalProjectile& state,const std::array<float,3>& target){
 const auto angles=projectile_birth_angles_scalar24(state.position,target,state.velocity);
 state.heading=angles.heading;state.offset=angles.offset;state.pitch=angles.pitch;
}
//5f6ef0/5f7110 add deltaYaw+parentHeading, then parentOffset. Preserve that
// order before the float trig argument; pitch is deltaPitch+parentPitch.
inline std::array<float,3> projectile_birth_direction_scalar24(float heading,float offset,float pitch,
 float yaw_delta=0,float pitch_delta=0){
 const float angle=float(legacy_stage_add24(legacy_stage_add24(yaw_delta,heading),offset));
 const float elevation=float(legacy_stage_add24(pitch_delta,pitch)),cp=legacy_trig(elevation,false);
 return {{float(legacy_stage_mul24(legacy_trig(angle,false),cp)),legacy_trig(elevation,true),float(legacy_stage_mul24(legacy_trig(angle,true),cp))}};
}
//5f6db0's contact child uses the raw vector unless42df50 length is zero.
//5f6fd0's visual child never takes its dead fallback (XOR sets ZF before JE).
inline std::array<float,3> projectile_contact_child_direction(const KeiichiNormalProjectile& parent){
 return projectile_motion_length(parent.velocity)==0.f
  ?projectile_birth_direction_scalar24(parent.heading,parent.offset,parent.pitch):parent.velocity;
}
}
