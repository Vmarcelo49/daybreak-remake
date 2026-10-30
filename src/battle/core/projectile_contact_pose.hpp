#pragma once
#include "actor_frame_geometry.hpp"
#include "projectile_pose_orientation.hpp"
namespace daybreak {
// 5f6710 uses frame-local points directly, not the frame's named model bone.
// Contact orientation is Rz(elevation) * Ry(-(heading+offset)) * T(position).
inline LegacyMatrix projectile_contact_pose(const std::array<float,3>& position,const std::array<float,3>& velocity,float heading,float offset,float elevation){
 const auto angles=projectile_direction_angles(velocity,heading,offset,elevation);
 return multiply_matrix_scalar24(
   multiply_matrix_scalar24(projectile_rotation_z(angles.pitch),projectile_rotation_y(angles.yaw)),
   projectile_translation(position));
}
}
