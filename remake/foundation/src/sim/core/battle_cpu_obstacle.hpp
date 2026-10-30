#pragma once
#include "stage_collision_mesh.hpp"
#include "battle_stage_ray_direction.hpp"
#include "battle_target_position.hpp"
#include "legacy_trig.hpp"
namespace daybreak {
//42cc90: root origin, pitch toward primary target+38, actor yaw+5c.
inline CollisionPoint battle_cpu_obstacle_direction(const std::array<float,3>& root,
 const std::array<float,3>& target,float heading){
 const float pitch=battle_target_elevation(root,target),cp=legacy_trig(pitch,false);
 volatile float x=legacy_trig(heading,false)*cp,z=legacy_trig(heading,true)*cp;
 return {x,legacy_trig(pitch,true),z};
}
struct BattleCpuObstacle {float distance=10000;bool hit=false;};
//42d2c0 traverses raw meshes, with no color/normal filter or frame transform.
// Scalar PC24 normalization and original mesh admission/Tri intersection.
class BattleCpuObstacleQuery {
 const StageCollisionMesh& mesh_;
public:
 explicit BattleCpuObstacleQuery(const StageCollisionMesh& mesh):mesh_(mesh){}
 BattleCpuObstacle ray(const CollisionPoint& root,CollisionPoint direction)const{
  for(auto x:root)if(!std::isfinite(x))throw std::invalid_argument("Invalid CPU ray origin");
  for(auto v:direction)if(!std::isfinite(v))throw std::invalid_argument("Invalid CPU ray direction");
  direction=battle_stage_ray_direction({{float(direction[0]),float(direction[1]),float(direction[2])}});
  BattleCpuObstacle out;
  for(const auto& hit:mesh_.intersect(root,direction)){
   const float distance=float(hit.distance); // D3DXIntersect writes a float.
   if(distance<out.distance)out.distance=distance;
  }
  out.hit=out.distance<10000;return out;
 }
 BattleCpuObstacle query(const std::array<float,3>& root,const std::array<float,3>& primary_target,float heading)const{
  return ray({root[0],root[1],root[2]},battle_cpu_obstacle_direction(root,primary_target,heading));
 }
};
}
