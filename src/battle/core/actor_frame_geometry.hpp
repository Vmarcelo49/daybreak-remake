#pragma once
#include "actor_frame_data.hpp"
#include "legacy_matrix.hpp"
#include "battle_normal_hit.hpp"
namespace daybreak {
// Retained DLL RVA 0x42040 scalar path, x87 24-bit precision.
inline std::array<float,4> transform_actor_point_scalar24(const std::array<std::int32_t,3>& point,const LegacyMatrix& matrix){
 std::array<float,4> out{};
 for(unsigned c=0;c<4;++c){volatile float x=float(point[0])*matrix[c],y=float(point[1])*matrix[4+c],z=float(point[2])*matrix[8+c];volatile float zy=z+y;volatile float zyx=zy+x;out[c]=zyx+matrix[12+c];}
 return out;
}
// D3DXVec3Transform SSE path (DLL RVA 0x20707d), used by the retained
// original contact traces. Both matrix-alignment branches sum (x+y)+(z+t).
// Keep each float rounding point and the row-vector/no-divide convention.
inline std::array<float,4> transform_actor_point(const std::array<std::int32_t,3>& point,const LegacyMatrix& matrix){
 std::array<float,4> out{};
 for(unsigned c=0;c<4;++c){
  volatile float x=float(point[0])*matrix[c],y=float(point[1])*matrix[4+c],z=float(point[2])*matrix[8+c];
  volatile float xy=x+y,zt=z+matrix[12+c];out[c]=xy+zt;
 }
 return out;
}
inline void bind_actor_frame_geometry(const ActorFrameData& frame,const LegacyMatrix& bone_world,BattleNormalHitContact& geometry){
 geometry.start=transform_actor_point(frame.first,bone_world);geometry.end=transform_actor_point(frame.second,bone_world);geometry.shape=frame.shape;
}
}
