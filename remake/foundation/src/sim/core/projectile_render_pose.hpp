#pragma once
#include "projectile_contact_pose.hpp"
#include "keiichi_normal_projectile.hpp"
#include "battle_camera_view.hpp"
#include "legacy_camera_scalar24.hpp"
namespace daybreak {
// 661770 stores camera+40;661a20 returns it. The +X model axis follows
// look_at-eye; world-up supplies the other axes (not inverse-view +Z).
inline LegacyMatrix projectile_billboard_matrix(const BattleCameraView& camera){
 return legacy_camera_billboard_scalar24(camera.eye,camera.look_at);
}
// 5f616d..5f6370: scale, independent yaw/pitch/roll, direction policy,
// translation. An external pose replaces all steps after scale.
inline LegacyMatrix projectile_render_pose(const KeiichiNormalProjectile& state,std::uint32_t flags,const LegacyMatrix& billboard,const LegacyMatrix* external=nullptr){
 const LegacyMatrix scale{state.scale[0],0,0,0,0,state.scale[1],0,0,0,0,state.scale[2],0,0,0,0,1};
 if(external)return multiply_matrix_scalar24(scale,*external);
 auto result=multiply_matrix_scalar24(scale,projectile_rotation_ypr(state.rotation));
 if(!(flags&0x5000)){
  const auto angles=projectile_direction_angles(state.velocity,state.heading,state.offset,state.pitch);
  result=multiply_matrix_scalar24(result,projectile_rotation_z(angles.pitch));
  result=multiply_matrix_scalar24(result,projectile_rotation_y(angles.yaw));
 }
 if(flags&0x1000)result=multiply_matrix_scalar24(result,billboard);
 return multiply_matrix_scalar24(result,projectile_translation(state.position));
}
}
