#pragma once
#include <array>
#include <cmath>
namespace daybreak {
// 434c30: target minus live slot0 socket, float32 storage at each source boundary.
inline float full_charge_manual_aim(const std::array<float,3>& socket,const std::array<float,3>& target){
 volatile float x=target[0]-socket[0],y=target[1]-socket[1],z=target[2]-socket[2];y=y+70.f;
 volatile float xx=x*x,zz=z*z,squared=xx+zz,horizontal=float(std::sqrt(double(squared)));
 const auto angle=std::atan2(double(y),double(horizontal));
 volatile float scaled=float(angle*180.f);return scaled/3.1415927410125732421875f;
}
}
