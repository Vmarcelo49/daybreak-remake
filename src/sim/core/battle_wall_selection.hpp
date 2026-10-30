#pragma once
#include "battle_horizontal_move.hpp"
#include <algorithm>
#include <vector>
namespace daybreak {
//42d3b0 collects ONE closest candidate per mesh, then publishes/clamps it.
// Geometry providers retain ray/normal generation; these are float ABI fields.
enum class BattleWallPrecision {Float24,Float53};
inline float battle_wall_dot(const BattleVector& a,const BattleVector& b,BattleWallPrecision precision=BattleWallPrecision::Float24){
 if(precision==BattleWallPrecision::Float53)return float(double(a[0])*b[0]+double(a[1])*b[1]+double(a[2])*b[2]);
 volatile float x=a[0]*b[0],y=a[1]*b[1],z=a[2]*b[2];volatile float xy=x+y;return xy+z;
}
struct BattleWallCandidate {
 unsigned mesh=0;float distance=10000,penetration=0;
 double comparison_distance=10000; // x87 compares the sum before its float store.
 BattleVector horizontal{},tangent{};bool selected=false;BattleWallPrecision precision=BattleWallPrecision::Float24;
};
inline BattleWallCandidate make_battle_wall_candidate(unsigned mesh,float ray_distance,float incidence,
 const BattleVector& horizontal,const BattleVector& tangent,BattleWallPrecision precision=BattleWallPrecision::Float24){
 BattleWallCandidate candidate;candidate.mesh=mesh;candidate.horizontal=horizontal;candidate.tangent=tangent;
 volatile float offset=-1.f/incidence;
 candidate.comparison_distance=double(offset)+double(ray_distance);candidate.distance=float(candidate.comparison_distance);
 if(precision==BattleWallPrecision::Float24)candidate.comparison_distance=candidate.distance;
  candidate.precision=precision;
 if(precision==BattleWallPrecision::Float24){volatile float product=incidence*ray_distance;candidate.penetration=1.f-product;}
 else candidate.penetration=float(1.-double(incidence)*double(ray_distance));candidate.selected=true;return candidate;
}
class BattleWallSelection {
 std::vector<BattleWallCandidate> meshes;
public:
 bool observe(const BattleWallCandidate& candidate){
  auto it=std::find_if(meshes.begin(),meshes.end(),[&](const auto& value){return value.mesh==candidate.mesh;});
  if(it==meshes.end()){meshes.push_back({});it=meshes.end()-1;it->mesh=candidate.mesh;}
  if(candidate.selected&&candidate.comparison_distance<it->distance){*it=candidate;return true;}
  return false;
 }
 BattleCollisionResult resolve(const BattleVector& direction,float length,float maximum,unsigned* publishes=nullptr)const{
 BattleCollisionResult result;result.distance=maximum;
 for(const auto& candidate:meshes){
  if(!candidate.selected||!(candidate.distance<result.distance))continue;
  result.distance=candidate.distance; // Global distance updates even beyond this motion.
  if(publishes)++*publishes;
  if(!(candidate.distance<=length))continue;
  result.hit=true;
  if(candidate.distance>0){for(unsigned axis=0;axis<3;++axis)result.correction[axis]=direction[axis]*result.distance;}
  else {result.distance=0;for(unsigned axis=0;axis<3;++axis)result.correction[axis]=-candidate.horizontal[axis]*candidate.penetration;}
  const float along=battle_wall_dot(direction,candidate.tangent,candidate.precision);
  volatile float remaining=length-result.distance;
  for(unsigned axis=0;axis<3;++axis){volatile float scaled=candidate.tangent[axis]*along;result.remainder[axis]=scaled*remaining;}
 }
 return result;
}
};
inline BattleCollisionResult resolve_battle_wall_candidates(const std::vector<BattleWallCandidate>& candidates,const BattleVector& direction,float length,float maximum,unsigned* publishes=nullptr){
 BattleWallSelection selection;for(const auto& candidate:candidates)selection.observe(candidate);
 return selection.resolve(direction,length,maximum,publishes);
}
}
