#pragma once
#include "battle_vertical_move.hpp"
#include "legacy_stage_surface_scalar24.hpp"
#include "floor_color_policy.hpp"
namespace daybreak {
// 42cd50 response reduction. Original device flags select x87 precision24;
// geometry providers supply normalized float components. Ray/normal backend
// parity is separate from this finite response/packed-color boundary.
struct BattleFloorSelection {
 BattleFloorResult floor;FloorColorFlags flags;
 bool accept(bool has_color,std::uint8_t red,std::uint8_t blue,float ray,float velocity){
  return accept_floor_color(has_color,red,blue,ray,velocity,flags);
 }
 unsigned observe(float ray,float velocity,const BattleVector& normal){
  volatile float squared_y=normal[1]*normal[1];
  volatile float distance=ray-1.f;distance=distance-50.f;
  if(squared_y>=0.10000000149011612f||velocity>0){
   if(distance<floor.distance){floor.distance=distance;return 1;}return 0;
  }
  volatile float push=distance+velocity;push=-push;
  if(!(push>floor.push_amount))return 0;
  //42d19d normalizes even a zero horizontal vector, then stores push/absY.
  floor.correction=legacy_stage_surface_horizontal(normal);
  floor.push_amount=push;floor.normal_y_abs=std::abs(normal[1]);return 2;
 }
};
}
