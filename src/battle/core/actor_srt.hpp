#pragma once
#include "actor_matrix_components.hpp"
#include "actor_rotation_basis.hpp"
#include "legacy_matrix_quaternion.hpp"
namespace daybreak {
struct ActorSrt{std::array<float,3> scale;std::array<float,4> rotation;std::array<float,3> translation;};
// Validated for the real Keiichi matrix-key corpus. General reflection,
// degenerate-axis recovery and determinant validation remain unimplemented.
inline ActorSrt decompose_actor_key_srt(const LegacyMatrix& m){auto c=actor_matrix_components(m);auto q=matrix_quaternion_scalar24(actor_rotation_basis(m));q[3]=-q[3];return {c.scale_magnitudes,q,c.translation};}
}
