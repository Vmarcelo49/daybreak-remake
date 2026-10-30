#pragma once
#include <array>
#include <cmath>
#include <limits>
namespace daybreak {
inline float legacy_vector_dot_scalar24(const std::array<float,3>& a,const std::array<float,3>& b){
 volatile float x=a[0]*b[0],y=a[1]*b[1],z=a[2]*b[2],xy=x+y;
 return xy+z;
}
inline std::array<float,3> legacy_vector_cross_scalar24(const std::array<float,3>& a,const std::array<float,3>& b){
 std::array<float,3> out{};
 for(unsigned i=0;i<3;++i){const unsigned j=(i+1)%3,k=(i+2)%3;volatile float first=a[j]*b[k],second=a[k]*b[j];out[i]=first-second;}
 return out;
}
// Actual DLL441f9c/43dec7, explicitly scalar PC24. A near-unit vector is
// copied unchanged; a squared length <=FLT_MIN yields three positive zeros.
// The other branch rounds reciprocal sqrt before multiplying each component.
inline std::array<float,3> legacy_vector_normalize_scalar24(const std::array<float,3>& v){
 const float square=legacy_vector_dot_scalar24(v,v);volatile float difference=square-1.f;
 if(std::abs(difference)<=std::numeric_limits<float>::epsilon())return v;
 if(!(square>std::numeric_limits<float>::min()))return {{0,0,0}};
 const float length=float(std::sqrt(double(square)));volatile float reciprocal=1.f/length;
 std::array<float,3> out{};for(unsigned i=0;i<3;++i)out[i]=reciprocal*v[i];return out;
}
}
