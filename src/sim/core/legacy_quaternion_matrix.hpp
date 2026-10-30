#pragma once
#include "legacy_matrix.hpp"
#include <array>
namespace daybreak {
// D3DX scalar 0x43fde8, x87 precision control 24 bits.
inline LegacyMatrix quaternion_matrix_scalar24(const std::array<float,4>& q) {
    auto mul=[](float a,float b){volatile float v=a*b;return v;};
    auto add=[](float a,float b){volatile float v=a+b;return v;};
    auto sub=[](float a,float b){volatile float v=a-b;return v;};
    const float x2=mul(2.f,q[0]), y2=mul(2.f,q[1]), z2=mul(2.f,q[2]);
    const float wx=mul(x2,q[3]), wy=mul(y2,q[3]), wz=mul(z2,q[3]);
    const float xx=mul(x2,q[0]), xy=mul(y2,q[0]), xz=mul(z2,q[0]);
    const float yy=mul(y2,q[1]), yz=mul(z2,q[1]), zz=mul(z2,q[2]);
    return {sub(sub(1.f,yy),zz),add(xy,wz),sub(xz,wy),0.f,
            sub(xy,wz),sub(sub(1.f,xx),zz),add(yz,wx),0.f,
            add(xz,wy),sub(yz,wx),sub(sub(1.f,xx),yy),0.f,
            0.f,0.f,0.f,1.f};
}
}
