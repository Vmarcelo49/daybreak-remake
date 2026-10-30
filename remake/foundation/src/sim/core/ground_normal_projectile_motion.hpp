#pragma once
#include "keiichi_normal_projectile.hpp"
#include "stage_floor_collision.hpp"
#include "stage_wall_collision.hpp"

namespace daybreak {
// Ground-constrained 5f5ec0 branch. The horizontal/vertical collision
// adapters share the actor's recovered 42cb50/42c970 control flow. Their
// CPU mesh intersection remains provisional versus original D3DX geometry.
inline void move_normal_projectile_ground(KeiichiNormalProjectile& s,
 float target_x,float target_z,const StageCollisionMesh* stage){
 if(s.released)return;
 const float angle=s.heading+s.offset;
 s.velocity[0]=legacy_trig(angle,false)*s.speed;
 s.velocity[2]=legacy_trig(angle,true)*s.speed;
 if(stage){
  StageWallCollision wall(*stage);
  BattleHorizontalState horizontal;horizontal.position=s.position;
  horizontal.collision_distance=s.remaining_stage_distance;
  horizontal.collided=std::uint8_t(s.wall_contact);
  move_battle_horizontal(horizontal,{s.velocity[0],0,s.velocity[2]},wall);
  s.position=horizontal.position;s.wall_contact=horizontal.collided!=0;
  s.remaining_stage_distance=horizontal.collision_distance;
  StageFloorCollision floor(*stage);
  auto result=floor.query(s.position,s.velocity[1]);
  BattleVerticalState vertical;vertical.position=s.position;
  vertical.grounded=std::uint8_t(s.surface_flag);
  apply_battle_floor(vertical,s.velocity[1],result.floor);
  s.position=vertical.position;s.surface_flag=vertical.grounded!=0;
 }else{
  s.position[0]+=s.velocity[0];s.position[1]+=s.velocity[1];s.position[2]+=s.velocity[2];
 }
 BattleFacing facing{s.heading,s.offset};
 face_battle_target(facing,s.position[0],s.position[2],target_x,target_z);
 s.heading=facing.heading;s.offset=facing.offset;
}
} // namespace daybreak
