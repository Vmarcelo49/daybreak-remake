#pragma once
#include "battle_camera_tracking.hpp"
#include <algorithm>
namespace daybreak {
struct BattleCameraView {std::array<float,3> eye{},look_at{};};
struct BattleCameraProjection {float fov_y,aspect,near_plane,far_plane;};
//633860 ->661740 ->D3DXMatrixPerspectiveFovLH; byte95 selects narrow view.
inline BattleCameraProjection battle_camera_projection(bool narrow){
 return {narrow?.11219973862171173f:.7853981852531433f,1.3333333730697632f,narrow?100.f:50.f,150000.f};
}
//63366f..63384b ordinary (bytes94/95 zero) branch only.632e10 sets distance300;
// callers can override it. Animated/special cameras must use their own path.
inline BattleCameraView ordinary_battle_camera_view(const BattleCameraTracking& s,float distance=300){
 auto length=[](const std::array<float,3>& v){volatile float z=v[2]*v[2],y=v[1]*v[1],x=v[0]*v[0],zy=z+y,total=zy+x;return float(std::sqrt(double(total)));};
 std::array<float,3> direction{};for(unsigned i=0;i<3;++i)direction[i]=s.smoothed_target[i]-s.smoothed_anchor[i];
 float separation=length(direction);
 if(separation<800){float ratio;if(separation<400){ratio=(400.f/separation)/2;separation=400;}else ratio=separation/800;
  for(auto& c:direction)c*=ratio;
 }
 auto back=direction;back[1]-=120;
 float ratio=distance/length(back);if(ratio>1.5f)ratio=1.5f;
 for(auto& c:back)c*=ratio;
 BattleCameraView out;
 for(unsigned i=0;i<3;++i){out.eye[i]=s.smoothed_anchor[i]-back[i];out.look_at[i]=direction[i]+s.smoothed_anchor[i];}
 volatile float base=s.smoothed_anchor[1]+140,raise=separation*.03f,sum=base+raise;
 out.eye[1]=sum-back[1];
 const float cap=(s.smoothed_anchor[1]+200)-back[1];if(cap<out.eye[1])out.eye[1]=cap;
 volatile float look_base=out.look_at[1]+20,lower=separation*.2f;out.look_at[1]=look_base-lower;
 return out;
}
}
