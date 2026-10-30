#pragma once
#include "legacy_matrix.hpp"
#include "legacy_normalize.hpp"
namespace daybreak {
// Nondegenerate, nonreflected matrix basis extraction. Full decomposition's
// fallback axes, reflection correction and determinant rejection are not implemented.
inline LegacyMatrix actor_rotation_basis(const LegacyMatrix& input){
 LegacyMatrix out={1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
 for(unsigned r=0;r<3;++r){auto v=normalize_scalar24({input[r*4],input[r*4+1],input[r*4+2]});for(unsigned c=0;c<3;++c)out[r*4+c]=v[c];}
 return out;
}
}
