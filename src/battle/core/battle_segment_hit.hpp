#pragma once
#include <array>
#include <cmath>
namespace daybreak {
inline float hit_dot(const std::array<float,3>& a,const std::array<float,3>& b){volatile float x=a[0]*b[0],y=a[1]*b[1],z=a[2]*b[2];volatile float xy=x+y;return xy+z;}
// Original 0x63b4d0: infinite-line distance plus midpoint bounding sphere,
// not a closest-point capsule. Finite bounded inputs; zero length rejects.
inline bool battle_segment_hit(const std::array<float,3>& point,float radius,const std::array<float,3>& start,const std::array<float,3>& end,float width){
    std::array<float,3> a{},d{},center_delta{};
    for(unsigned i=0;i<3;++i){volatile float x=start[i]-point[i],y=end[i]-start[i];a[i]=x;d[i]=y;}
    volatile float aa=hit_dot(a,a),dot=hit_dot(a,d),dd=hit_dot(d,d),dot2=dot*dot;
    volatile float quotient=dot2/dd,perpendicular=aa-quotient,sum=radius+width,r2=sum*sum;
    if(!(r2>perpendicular))return false;
    for(unsigned i=0;i<3;++i){volatile float add=start[i]+end[i],middle=add*.5f;center_delta[i]=point[i]-middle;}
    volatile float distance=hit_dot(center_delta,center_delta);
    volatile float length=std::sqrt(dd),half=length/2.f,bound=half+sum,bound2=bound*bound;
    return bound2>distance;
}
}
