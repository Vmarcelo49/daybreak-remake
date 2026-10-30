#pragma once
#include "actor_skeleton.hpp"
namespace daybreak {
//64e360 includes model world at the root, before descendants. Retained native
//damage boundaries select DLL SIMD matrix order. Locals already include the
//controller/extra transforms; do not apply them a second time here.
inline void combine_actor_world_hierarchy(const ActorSkeleton& pose,const LegacyMatrix& world,
                                          std::vector<LegacyMatrix>& combined){
 combined.resize(pose.bones.size());combined[0]=world;
 struct Host {
  const ActorSkeleton& pose;const LegacyMatrix& world;std::vector<LegacyMatrix>& out;
  unsigned extra(unsigned){return 0;}void multiply_local(unsigned,unsigned){}
  void combine(unsigned frame,unsigned parent){out[frame]=multiply_matrix_simd_order(pose.bones[frame].local,out[parent]);}
  void copy_local(unsigned frame){out[frame]=multiply_matrix_simd_order(pose.bones[frame].local,world);}
  unsigned sibling(unsigned frame){return pose.bones[frame].sibling;}
  unsigned child(unsigned frame){return pose.bones[frame].child;}
  unsigned combined(unsigned frame){return frame;}
 } host{pose,world,combined};
 if(pose.root)update_frame(pose.root,0,host);
}
}
