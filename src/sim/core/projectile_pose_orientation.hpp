#pragma once
#include "projectile_motion_length.hpp"
#include "legacy_quaternion_matrix.hpp"
#include "legacy_asin_domain.hpp"
#include <cmath>
namespace daybreak {
// Original5f6710/5f6281: store the PC24 XYZ length and Y/length ratio
// as floats before calling asin. Stopped projectiles use their elevation.
inline float projectile_radians(float degrees){
 volatile float product=degrees*3.1415927410125732421875f;
 return product/180.f;
}
struct ProjectileDirectionAngles {float pitch,yaw;};
// CRT66c708..714:670295 retains the incoming precision bits. With PC24,
// sqrt((1+x)*(1-x)) is rounded at each operation before FPATAN.
inline float projectile_asin_scalar24(float x){
 if(legacy_asin_outside_unit(x))return legacy_asin_domain_result(x);
 volatile float plus=1.f+x,minus=1.f-x,product=plus*minus;
 const float adjacent=float(std::sqrt(double(product)));
 return float(std::atan2(double(x),double(adjacent)));
}
inline ProjectileDirectionAngles projectile_direction_angles(const std::array<float,3>& velocity,float heading,float offset,float elevation){
 const float length=projectile_motion_length(velocity);
 float pitch;
 if(length==0)pitch=projectile_radians(elevation);
 else {volatile float ratio=velocity[1]/length;pitch=projectile_asin_scalar24(ratio);}
 volatile float sum=heading+offset;
 return {pitch,projectile_radians(-sum)};
}
inline LegacyMatrix projectile_rotation_z(float angle){
 const float c=float(std::cos(double(angle))),s=float(std::sin(double(angle)));
 return {c,s,0,0,-s,c,0,0,0,0,1,0,0,0,0,1};
}
inline LegacyMatrix projectile_rotation_y(float angle){
 const float c=float(std::cos(double(angle))),s=float(std::sin(double(angle)));
 return {c,0,-s,0,0,1,0,0,s,0,c,0,0,0,0,1};
}
inline LegacyMatrix projectile_translation(const std::array<float,3>& position){
 return {1,0,0,0,0,1,0,0,0,0,1,0,position[0],position[1],position[2],1};
}
// DLL scalar42ebe ->40d12 ->3fde8: YPR uses a quaternion, rather than
// multiplying three rotation matrices. Keep each PC24 product/sum store.
// Portable trig is compared with actual DLL FSINCOS on bounded fixtures.
inline LegacyMatrix projectile_rotation_ypr(const std::array<float,3>& degrees){
 volatile float roll=projectile_radians(degrees[2])*.5f;
 volatile float pitch=projectile_radians(degrees[1])*.5f;
 volatile float yaw=projectile_radians(degrees[0])*.5f;
 const float cr=float(std::cos(double(roll))),sr=float(std::sin(double(roll)));
 const float cp=float(std::cos(double(pitch))),sp=float(std::sin(double(pitch)));
 const float cy=float(std::cos(double(yaw))),sy=float(std::sin(double(yaw)));
 volatile float a=sy*cp,b=cy*sp,c=cy*cp,d=sy*sp;
 volatile float xb=cr*b,xa=a*sr,yb=a*cr,ya=b*sr;
 volatile float zb=c*sr,za=d*cr,wb=d*sr,wa=c*cr;
 const std::array<float,4> q{{xb+xa,yb-ya,zb-za,wb+wa}};
 return quaternion_matrix_scalar24(q);
}
}
