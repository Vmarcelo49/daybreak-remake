#pragma once
#include "legacy_stage_intersection_scalar24.hpp"
#include "legacy_vector_scalar24.hpp"
#include "projectile_motion_length.hpp"
#include "actor_controller_srt.hpp"
namespace daybreak {
//42cd50/42d3b0: DWORD edges, PC24 cross42e020(e2 cross e1), followed
// by669cfc/IAT6a127c's selected608854 SIMD Normalize, also used by FX.
inline LegacyStageVector legacy_stage_surface_normal(const LegacyStageTriangle& triangle){
 return actor_controller_normalize3(legacy_stage_cross24(triangle.e2,triangle.e1));
}
inline LegacyStageVector legacy_stage_surface_horizontal(const LegacyStageVector& normal){
 return actor_controller_normalize3({{normal[0],0,normal[2]}});
}
inline LegacyStageVector legacy_stage_surface_tangent(const LegacyStageVector& normal){
 return actor_controller_normalize3({{-normal[2],0,normal[0]}});
}
inline LegacyStageVector legacy_stage_wall_origin(const LegacyStageVector& position){
 volatile float y=position[1]+.01f;return {{position[0],y,position[2]}};
}
}
