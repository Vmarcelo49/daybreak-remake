#pragma once
#include <array>
#include <cmath>
namespace daybreak {
// 42df50: PC24 products, X+Y then Z, float argument to42dea0, PC24 sqrt.
// Keep the returned length float before collision comparison and subtraction.
inline float projectile_motion_length(const std::array<float,3>& velocity){
 volatile float x=velocity[0]*velocity[0],y=velocity[1]*velocity[1],z=velocity[2]*velocity[2];
 volatile float xy=x+y,total=xy+z;
 return float(std::sqrt(double(total)));
}
}
