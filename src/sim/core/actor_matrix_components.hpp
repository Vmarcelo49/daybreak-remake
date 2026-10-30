#pragma once
#include "legacy_matrix.hpp"
#include <cmath>
namespace daybreak {
struct ActorMatrixComponents {std::array<float,3> scale_magnitudes,translation;};
// Initial stage of scalar MatrixDecompose: no reflection sign or quaternion recovery yet.
inline ActorMatrixComponents actor_matrix_components(const LegacyMatrix& m){
 ActorMatrixComponents result;
 for(unsigned r=0;r<3;++r){volatile float z=m[r*4+2]*m[r*4+2],y=m[r*4+1]*m[r*4+1],x=m[r*4]*m[r*4];volatile float zy=z+y;volatile float sum=zy+x;result.scale_magnitudes[r]=std::sqrt(sum);result.translation[r]=m[12+r];}
 return result;
}
}
