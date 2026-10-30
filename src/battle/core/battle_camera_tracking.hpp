#pragma once
#include <array>
#include <cmath>
namespace daybreak {
// Recovered632e70/633220 state slice. Final eye/look-at construction6333b0,
// Anchor constraint632ed0 is included; projection and obstruction live outside this helper.
struct BattleCameraTracking {
 std::array<float,3> anchor{},smoothed_anchor{},target{},smoothed_target{};
 std::array<float,3> previous_anchor_input{}; // camera+24, updated even without immediate copy
 float animation_time=0,animation_end=0;
 bool animated=false;
};
//632ed0. Portable normalization preserves the observed zero-vector result;
// arbitrary-input bit equivalence with D3DX's CPU dispatch is not claimed.
inline void set_battle_camera_anchor(BattleCameraTracking& s,const std::array<float,3>& position,bool immediate){
 const float dx=s.target[0]-position[0],dz=s.target[2]-position[2];
 const float mx=position[0]-s.previous_anchor_input[0],mz=position[2]-s.previous_anchor_input[2];
 auto norm=[](float x,float z){volatile float xx=x*x,zz=z*z,sum=zz+xx;return float(std::sqrt(double(sum)));};
 const float distance=norm(dx,dz);s.anchor=position;
 if(distance<40){
  const float movement=norm(mx,mz);const float nx=movement?mx/movement:0,nz=movement?mz/movement:0;
  volatile float left=dz*nx,right=dx*nz;float cross=left-right;
  volatile float dotx=dx*nx,dotz=dz*nz;const float dot=dotz+dotx;if(dot<0)cross=-cross;
  const float side_x=cross<=0?mz:-mz,side_z=cross<=0?-mx:mx;
  const float side_length=norm(side_x,side_z);
  volatile float square=distance*distance,remainder=1600-square;const float extent=float(std::sqrt(double(remainder)));
  volatile float shift_x=(side_length?side_x/side_length:0)*extent,shift_z=(side_length?side_z/side_length:0)*extent;
  s.anchor[0]+=shift_x;s.anchor[2]+=shift_z;
 }
 s.previous_anchor_input=position;
 if(immediate||s.animated)s.smoothed_anchor=s.anchor;
}
inline void set_battle_camera_target(BattleCameraTracking& s,const std::array<float,3>& target,bool immediate){
 s.target=target;if(immediate||s.animated)s.smoothed_target=target;
}
inline void advance_battle_camera_tracking(BattleCameraTracking& s){
 auto track=[](const std::array<float,3>& desired,std::array<float,3>& current,float fraction){
  std::array<float,3> delta{};for(unsigned i=0;i<3;++i)delta[i]=current[i]-desired[i];
  volatile float z2=delta[2]*delta[2],y2=delta[1]*delta[1],x2=delta[0]*delta[0];
  volatile float zy=z2+y2,total=zy+x2;const float length=float(std::sqrt(double(total)));
  // Original retains pre-snap delta: a >10000 jump overshoots after snapping.
  if(length>10000)current=desired;
  if(length<=2)current=desired;
  else for(unsigned i=0;i<3;++i){volatile float step=delta[i]*fraction;current[i]-=step;}
 };
 track(s.anchor,s.smoothed_anchor,.2f);track(s.target,s.smoothed_target,.3f);
 // Deliberately no clamp after increment; original tests before adding.016.
 if(s.animated&&s.animation_time<s.animation_end)s.animation_time+=.016f;
}
}
