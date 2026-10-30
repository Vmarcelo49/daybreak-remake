#pragma once
#include "legacy_matrix.hpp"
#include "weapon_item_data.hpp"
#include <algorithm>
#include <cmath>
namespace daybreak {
using WeaponTrailPoint=std::array<float,4>;
inline WeaponTrailPoint weapon_trail_transform(const WeaponTrailPoint& point,const LegacyMatrix& matrix){
 WeaponTrailPoint out{};
 for(unsigned axis=0;axis<4;++axis){double value=double(point[0])*matrix[axis];
  for(unsigned k=1;k<4;++k)value+=double(point[k])*matrix[k*4+axis];out[axis]=float(value);
 }return out;
}
// 65d2f0/380/430/4d0/580: the stored float constants and boundary bases
// are recovered from x86, including 65d580's squared (not cubed) term.
inline WeaponTrailPoint weapon_trail_basis(unsigned segment,float fraction){
 const double t=fraction,t2=t*t,t3=t2*t,remaining=1.-t;
 constexpr double sixth=double(0.1666666716337204f),seven_twelfths=double(0.5833333134651184f),
  minus_eleven_twelfths=double(-0.9166666865348816f),two_thirds=double(0.6666666865348816f);
 WeaponTrailPoint out;
 if(segment==0||segment==8){
  out={float(remaining*remaining*remaining),float((t3*1.75-t2*4.5)+3.*t),
   float((segment==8?t2:t3)*minus_eleven_twelfths+t2*1.5),float(t3*sixth)};
 }else if(segment==1||segment==7){
  out={float(remaining*remaining*remaining*.25),float((t3*seven_twelfths-t2*1.25)+.25*t+seven_twelfths),
   float((t3*-.5+t2*.5)+.5*t+sixth),float(t3*sixth)};
 }else out={float(remaining*remaining*remaining*sixth),float((t3*.5-t2)+two_thirds),
   float((t3*-.5+t2*.5)+.5*t+sixth),float(t3*sixth)};
 if(segment>=7)std::reverse(out.begin(),out.end());return out;
}
// One object per DAT model record, rather than one per selected hand. Native
// +38 and +3c/history survive model hiding and selecting it again. The original
// constructor leaves vectors unspecified; use defined zero initialization.
struct WeaponModelTrail {
 WeaponTrailPoint previous_tip{};
 std::array<WeaponTrailPoint,13> history{}; // +88 root, +98 current tip, old tips
 std::array<WeaponTrailPoint,46> curve{}; // +158 root followed by nine*five samples
 LegacyMatrix matrix{};
 float animation_time=0;
 int triangles=0;
 bool enabled=false;
 void advance(const LegacyMatrix& bound){ // 42fff0, also invoked by434a70
  animation_time+=.01600000075995922f;
  if(previous_tip!=history[1]){
   previous_tip=history[1];
   for(unsigned i=12;i>1;--i)history[i]=history[i-1];
   if(enabled)triangles=std::min(40,triangles+5);
  }
  if(!enabled&&triangles>0)triangles-=2; // a count of1 becomes−1, as native
  matrix=bound;
 }
 void pose(const WeaponAttachmentData& attachment){ // 430120, no clock advance
  WeaponTrailPoint root{float(attachment.position[0]),float(attachment.position[1]),float(attachment.position[2]),1};
  WeaponTrailPoint tip{float(attachment.rotation[0]),float(attachment.rotation[1]),float(attachment.rotation[2]),1};
  history[0]=weapon_trail_transform(root,matrix);history[1]=weapon_trail_transform(tip,matrix);curve[0]=history[0];
  for(unsigned segment=0;segment<9;++segment)for(unsigned sample=0;sample<5;++sample){
   const auto weights=weapon_trail_basis(segment,float(sample)/5.f);WeaponTrailPoint point{};
   for(unsigned axis=0;axis<4;++axis){
    // 430790 stores each product, and4306f0 each left-to-right sum.
    point[axis]=float(double(history[segment+1][axis])*weights[0]);
    for(unsigned k=1;k<4;++k){const float term=float(double(history[segment+k+1][axis])*weights[k]);point[axis]+=term;}
   }curve[1+segment*5+sample]=point;
  }
 }
};
struct WeaponTrailVertex {float x=0,y=0,z=0,rhw=1;std::uint32_t color=0xffffffff;float u=0,v=0;};
// 4303b0 projects a triangle fan into the player viewport. Its rhw becomes1
// after4307e0 divides all four components; peripheral texture U=1, V=i/count.
inline unsigned weapon_trail_vertices(const WeaponModelTrail& trail,const LegacyMatrix& clip,
 unsigned left,unsigned top,unsigned width,unsigned height,std::array<WeaponTrailVertex,42>& out){
 if(trail.triangles<=0)return 0;const unsigned count=unsigned(trail.triangles);
 for(unsigned i=0;i<count+2;++i){
  auto point=weapon_trail_transform(trail.curve[i],clip);
  // Native emits invalid floats for w==0/behind the eye. Suppress that fan
  // instead of feeding infinities to the driver; normal front-facing data is unchanged.
  if(!std::isfinite(point[3])||point[3]<=1e-6f)return 0;
  const float inverse=1.f/point[3];for(auto& value:point)value*=inverse;
  for(float value:point)if(!std::isfinite(value))return 0;
  out[i]={point[0]*(float(width)/2.f)+float(left+(width>>1)),
   -point[1]*(float(height)/2.f)+float(top+(height>>1)),point[2],point[3],0xffffffff,
   i?1.f:0.f,i?float(i-1)/float(count):0.f};
 }return count+2;
}
}
