#pragma once
#include "legacy_vector_scalar24.hpp"
#include "legacy_matrix.hpp"
namespace daybreak {
// Original CRT66c708/66cf18 retain PC24: each arithmetic operation before
// FPATAN is rounded. Portable trig is checked on bounded native fixtures.
inline float legacy_camera_angle_scalar24(float x,bool cosine){
 if(std::abs(x)>1.f)return float(cosine?std::acos(double(x)):std::asin(double(x)));
 volatile float plus=1.f+x,minus=1.f-x,product=plus*minus;
 const float adjacent=float(std::sqrt(double(product)));
 return float(cosine?std::atan2(double(adjacent),double(x)):std::atan2(double(x),double(adjacent)));
}
inline LegacyMatrix legacy_axis_rotation_scalar24(std::array<float,3> axis,float angle){
 const float c=float(std::cos(double(angle))),s=float(std::sin(double(angle)));volatile float k=1.f-c;
 axis=legacy_vector_normalize_scalar24(axis);const float x=axis[0],y=axis[1],z=axis[2];
 auto mul=[](float a,float b){volatile float v=a*b;return v;};
 const float xy=mul(mul(y,x),k),yz=mul(mul(y,z),k),xz=mul(mul(z,x),k);
 const float xs=mul(x,s),ys=mul(y,s),zs=mul(z,s);
 return {mul(mul(x,x),k)+c,xy+zs,xz-ys,0,xy-zs,mul(mul(y,y),k)+c,yz+xs,0,xz+ys,yz-xs,mul(mul(z,z),k)+c,0,0,0,0,1};
}
// Actual DLL44032b LookAtLH with the original fixed up=(0,1,0).
inline LegacyMatrix legacy_camera_view_scalar24(const std::array<float,3>& eye,const std::array<float,3>& target){
 std::array<float,3> delta{};for(unsigned i=0;i<3;++i)delta[i]=target[i]-eye[i];
 const auto z=legacy_vector_normalize_scalar24(delta);
 const auto x=legacy_vector_normalize_scalar24(legacy_vector_cross_scalar24({{0,1,0}},z));
 const auto y=legacy_vector_cross_scalar24(z,x);
 return {x[0],y[0],z[0],0,x[1],y[1],z[1],0,x[2],y[2],z[2],0,
         -legacy_vector_dot_scalar24(x,eye),-legacy_vector_dot_scalar24(y,eye),-legacy_vector_dot_scalar24(z,eye),1};
}
// Whole661770: normalize delta, save elevation, zeroY then normalize again;
// signed acos yaw, RotationY * RotationAxis((-horizontalZ,0,horizontalX)).
inline LegacyMatrix legacy_camera_billboard_scalar24(const std::array<float,3>& eye,const std::array<float,3>& target){
 std::array<float,3> delta{};for(unsigned i=0;i<3;++i)delta[i]=target[i]-eye[i];
 auto direction=legacy_vector_normalize_scalar24(delta);const float pitch=legacy_camera_angle_scalar24(direction[1],false);
 direction[1]=0;direction=legacy_vector_normalize_scalar24(direction);
 const auto cross=legacy_vector_cross_scalar24({{1,0,0}},direction);
 float yaw=legacy_camera_angle_scalar24(legacy_vector_dot_scalar24(direction,{{1,0,0}}),true);if(cross[1]<0)yaw=-yaw;
 const float c=float(std::cos(double(yaw))),s=float(std::sin(double(yaw)));
 const LegacyMatrix rotation_y{{c,0,-s,0,0,1,0,0,s,0,c,0,0,0,0,1}};
 return multiply_matrix_scalar24(rotation_y,legacy_axis_rotation_scalar24({{-direction[2],0,direction[0]}},pitch));
}
}
