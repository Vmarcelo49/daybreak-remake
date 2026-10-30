#pragma once
#include "actor_controller_srt.hpp"
#include "stage_collision_mesh.hpp"
namespace daybreak {
//42d2c0 and633930 normalize into a float3 before the ray backend sees it.
// Keep original input/cache untouched. Intersection remains portable double.
inline CollisionPoint battle_stage_ray_direction(const std::array<float,3>& input){
 //42d2e0/63397a select the same669cfc D3DX export as actor/FX inputs.
 const auto v=actor_controller_normalize3(input);return {{v[0],v[1],v[2]}};
}
inline CollisionPoint battle_camera_stage_origin(const std::array<float,3>& anchor){
 volatile float y=anchor[1]+150.f;return {{anchor[0],y,anchor[2]}};
}
inline CollisionPoint battle_camera_stage_direction(const std::array<float,3>& anchor,const std::array<float,3>& target){
 std::array<float,3> delta{};for(unsigned i=0;i<3;++i)delta[i]=anchor[i]-target[i];return battle_stage_ray_direction(delta);
}
}
