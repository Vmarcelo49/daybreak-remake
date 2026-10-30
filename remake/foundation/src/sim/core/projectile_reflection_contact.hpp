#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_normal_hit.hpp"
#include "battle_sphere_hit.hpp"
#include "battle_segment_hit.hpp"
namespace daybreak {
// 638fd0, called by637774..637818 only for a flags28&10000 source in another
// pool. Source geometry is always its first point, including shaped sources.
// Target shape selects sphere/segment. This stores a reflection request only;
// the target's own next script performs42c800/42c840/5f72c0 and changes owner.
inline bool mark_projectile_reflection(const KeiichiNormalProjectile& source,
 const ActorFrameData& source_frame,const BattleNormalHitContact& source_geometry,
 KeiichiNormalProjectile& target,const ActorFrameData& target_frame,
 const BattleNormalHitContact& target_geometry){
 if(source.owner==target.owner&&!(source_frame.flags2c&0x10000u))return false;
 if(source.contacts.at(target.owner)||source.capacity.at(target.owner)<=0||
    (target_frame.flags28&0x10000u))return false;
 const std::array<float,3> a{{source_geometry.start[0],source_geometry.start[1],source_geometry.start[2]}},
  b{{target_geometry.start[0],target_geometry.start[1],target_geometry.start[2]}},
  end{{target_geometry.end[0],target_geometry.end[1],target_geometry.end[2]}};
 const float ra=float(projectile_signed(source_frame.extent)),rb=float(projectile_signed(target_frame.extent));
 const bool overlap=target_frame.shape?battle_segment_hit(a,ra,b,end,rb):battle_spheres_overlap(a,ra,b,rb);
 if(!overlap)return false;
 target.contacts.at(source.owner)=0x100;
 return true;
}
}
