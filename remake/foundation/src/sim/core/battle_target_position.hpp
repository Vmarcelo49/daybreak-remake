#pragma once
#include <array>
#include "legacy_target_geometry_scalar24.hpp"
namespace daybreak {
// Actor virtual+4 =421b90: selector2 returns2cc (spine(-25,0,0)),
// selector3 returns2c0 (head origin), every other selector returns root14.
inline std::array<float,3> select_battle_target_position(const std::array<float,3>& root,
 const std::array<std::array<float,4>,2>& body_points,int selector){
 if(selector!=2&&selector!=3)return root;
 const auto& p=body_points[selector==2?1:0];return {p[0],p[1],p[2]};
}
// Root42da80 and selected42dac0 share the same PC24/CRT PC64 graph.
inline float battle_target_elevation(const std::array<float,3>& from,const std::array<float,3>& target){
 return legacy_target_geometry_scalar24(from,target).degrees;
}
}
