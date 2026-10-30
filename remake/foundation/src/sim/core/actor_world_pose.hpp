#pragma once
#include "legacy_matrix.hpp"
#include <cmath>
namespace daybreak {
// 0x420d31..0x420d52 / upright branch: heading + 90 + heading offset + extra yaw.
// Unattached actor. Attachment transforms remain pending.
inline LegacyMatrix actor_upright_world(const std::array<float,3>& position,float heading,float offset=0,float extra_yaw=0){
    volatile float sum=heading+90.f;sum=sum+offset;sum=sum+extra_yaw;
    volatile float product=sum*-3.1415927410125732421875f;
    volatile float radians=product/180.f;
    const float c=float(std::cos(double(radians))),s=float(std::sin(double(radians)));
    return {c,0,-s,0,0,1,0,0,s,0,c,0,position[0],position[1],position[2],1};
}
// 420b30: T(0,-pivot,0) * Rx(pitch) * Ry(yaw) * T(position + pivot).
inline LegacyMatrix actor_world_pose(const std::array<float,3>& position,float heading,float offset,float pitch,float pivot,float extra_yaw=0){
    if(pitch==0)return actor_upright_world(position,heading,offset,extra_yaw);
    const LegacyMatrix lower{1,0,0,0,0,1,0,0,0,0,1,0,0,-pivot,0,1};
    volatile float product=pitch*3.1415927410125732421875f;volatile float radians=product/180.f;
    const float c=float(std::cos(double(radians))),s=float(std::sin(double(radians)));
    const LegacyMatrix tilt{1,0,0,0,0,c,s,0,0,-s,c,0,0,0,0,1};
    const auto yaw=actor_upright_world({0,0,0},heading,offset,extra_yaw);
    const LegacyMatrix translation{1,0,0,0,0,1,0,0,0,0,1,0,position[0],position[1]+pivot,position[2],1};
    return multiply_matrix_scalar24(multiply_matrix_scalar24(multiply_matrix_scalar24(lower,tilt),yaw),translation);
}
}
