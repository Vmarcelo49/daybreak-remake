#pragma once
#include <array>
#include <cmath>
namespace daybreak {
inline std::array<float,3> normalize_scalar24(std::array<float,3> v){
 volatile float x=v[0]*v[0],y=v[1]*v[1],z=v[2]*v[2];volatile float xy=x+y;volatile float sum=xy+z;volatile float delta=sum-1.f;
 if(delta>=-1.1920928955078125e-7f&&delta<=1.1920928955078125e-7f)return v;
 if(!(sum>1.1754943508222875e-38f))return {0,0,0};
 volatile float length=std::sqrt(sum);volatile float reciprocal=1.f/length;for(auto& value:v)value=value*reciprocal;return v;
}
}
