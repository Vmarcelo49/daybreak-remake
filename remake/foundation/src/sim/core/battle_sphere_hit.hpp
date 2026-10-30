#pragma once
#include <array>
namespace daybreak {
// Original 0x63b470: strict overlap, tangency is false. Finite bounded inputs.
inline bool battle_spheres_overlap(const std::array<float,3>& a,float ra,const std::array<float,3>& b,float rb){
    volatile float x=a[0]-b[0],y=a[1]-b[1],z=a[2]-b[2];
    volatile float xx=x*x,yy=y*y,zz=z*z;volatile float xy=xx+yy;volatile float distance=xy+zz;
    volatile float radius=ra+rb;volatile float squared=radius*radius;
    return squared>distance;
}
}
