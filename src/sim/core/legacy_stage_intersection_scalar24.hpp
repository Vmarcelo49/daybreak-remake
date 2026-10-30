#pragma once
#include <array>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <optional>
namespace daybreak {
// Round an operation to x87 PC24 without narrowing its exponent to float.
// Float-input products/sums in this path fit the double exponent range.
// DWORD stores below deliberately narrow; native QWORD stores do not.
inline double legacy_stage_round24(double value){
 std::uint64_t raw;std::memcpy(&raw,&value,8);
 const auto magnitude=raw&0x7fffffffffffffffull;
 if(magnitude==0||(magnitude&0x7ff0000000000000ull)==0x7ff0000000000000ull)return value;
 constexpr std::uint64_t mask=(std::uint64_t(1)<<29)-1,half=std::uint64_t(1)<<28;
 auto rounded=magnitude&~mask;const auto tail=magnitude&mask;
 if(tail>half||(tail==half&&((rounded>>29)&1)))rounded+=std::uint64_t(1)<<29;
 raw=(raw&0x8000000000000000ull)|rounded;std::memcpy(&value,&raw,8);return value;
}
inline double legacy_stage_mul24(double a,double b){return legacy_stage_round24(a*b);}
inline double legacy_stage_add24(double a,double b){return legacy_stage_round24(a+b);}
inline double legacy_stage_sub24(double a,double b){return legacy_stage_round24(a-b);}
using LegacyStageVector=std::array<float,3>;
struct LegacyStageTriangle {
 std::array<LegacyStageVector,3> vertices{};
 LegacyStageVector e1{},e2{};
 explicit LegacyStageTriangle(const std::array<LegacyStageVector,3>& v):vertices(v){
  for(unsigned i=0;i<3;++i){e1[i]=float(legacy_stage_sub24(v[1][i],v[0][i]));e2[i]=float(legacy_stage_sub24(v[2][i],v[0][i]));}
 }
};
struct LegacyStageRay {
 LegacyStageVector origin{},direction{};
 double threshold=0;
 LegacyStageRay(const LegacyStageVector& o,const LegacyStageVector& d):origin(o),direction(d){
  threshold=d[0]==0?o[0]:-legacy_stage_sub24(legacy_stage_mul24(o[1],d[0]),legacy_stage_mul24(d[1],o[0]));
 }
 bool side(const LegacyStageVector& vertex)const{
  if(direction[0]==0)return vertex[0]>origin[0];
  return legacy_stage_add24(legacy_stage_mul24(-double(direction[0]),vertex[1]),legacy_stage_mul24(direction[1],vertex[0]))>threshold;
 }
 bool admits(const LegacyStageTriangle& triangle)const{
  const bool a=side(triangle.vertices[0]),b=side(triangle.vertices[1]),c=side(triangle.vertices[2]);
  return a!=b||a!=c;
 }
};
inline LegacyStageVector legacy_stage_cross24(const LegacyStageVector& a,const LegacyStageVector& b){
 LegacyStageVector out{};
 for(unsigned i=0;i<3;++i){const unsigned j=(i+1)%3,k=(i+2)%3;out[i]=float(legacy_stage_sub24(legacy_stage_mul24(a[j],b[k]),legacy_stage_mul24(a[k],b[j])));}
 return out;
}
inline double legacy_stage_dot24(const LegacyStageVector& a,const LegacyStageVector& b,unsigned first,unsigned second){
 return legacy_stage_add24(legacy_stage_add24(legacy_stage_mul24(a[first],b[first]),legacy_stage_mul24(a[second],b[second])),legacy_stage_mul24(a[0],b[0]));
}
struct LegacyStageIntersection {float u=0,v=0,distance=0;};
// Actual DLL45b8b6 (also used by45babb). Mesh admission is a separate step.
inline std::optional<LegacyStageIntersection> legacy_stage_intersect_triangle24(const LegacyStageTriangle& triangle,const LegacyStageRay& ray){
 const auto p=legacy_stage_cross24(ray.direction,triangle.e2);
 double determinant=legacy_stage_dot24(p,triangle.e1,2,1);
 if(!(determinant>0)&&!(determinant<0))return {};
 LegacyStageVector delta{};
 for(unsigned i=0;i<3;++i)delta[i]=float(determinant>0?legacy_stage_sub24(ray.origin[i],triangle.vertices[0][i]):legacy_stage_sub24(triangle.vertices[0][i],ray.origin[i]));
 if(determinant<0)determinant=-determinant;
 const double reciprocal=legacy_stage_round24(1./determinant);
 const double u=legacy_stage_dot24(delta,p,2,1);
 if(!(u>=0&&u<=determinant))return {};
 const auto q=legacy_stage_cross24(delta,triangle.e1);
 const double v=legacy_stage_dot24(q,ray.direction,1,2);
 if(!(v>=0&&legacy_stage_add24(v,u)<=determinant))return {};
 const double distance=legacy_stage_dot24(q,triangle.e2,2,1);
 if(!(distance>=0))return {};
 return LegacyStageIntersection{float(legacy_stage_mul24(u,reciprocal)),float(legacy_stage_mul24(v,reciprocal)),float(legacy_stage_mul24(distance,reciprocal))};
}
inline float legacy_stage_closest_ceiling(){std::uint32_t raw=0x799a130c;float value;std::memcpy(&value,&raw,4);return value;}
}
