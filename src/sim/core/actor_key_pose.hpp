#pragma once
#include "actor_skeleton.hpp"
#include "x_animation_keys.hpp"
#include <algorithm>
namespace daybreak {
// Exact key-time evaluation only. Missing tracks retain the supplied base pose.
// Interpolation, controller registration order and multi-track blending are not inferred here.
inline bool apply_actor_exact_key_pose(ActorSkeleton& skeleton,const XAnimationKeys& animation,std::uint32_t time){
 std::vector<std::pair<unsigned,LegacyMatrix>> updates;
 for(const auto& track:animation.tracks){
  auto id=skeleton.find(track.bone);if(!id)throw std::runtime_error("Animation references unknown bone");
  if(std::any_of(updates.begin(),updates.end(),[&](const auto& u){return u.first==id;}))throw std::runtime_error("Duplicate bone animation track");
  auto it=std::lower_bound(track.keys.begin(),track.keys.end(),time,[](const XMatrixKey& k,std::uint32_t t){return k.time<t;});
  if(it==track.keys.end()||it->time!=time)return false;
  if(it+1!=track.keys.end()&&(it+1)->time==time)throw std::runtime_error("Ambiguous duplicate key time");
  updates.emplace_back(id,it->matrix);
 }
 for(const auto& u:updates)skeleton.bones[u.first].local=u.second;
 skeleton.update();return true;
}
}
