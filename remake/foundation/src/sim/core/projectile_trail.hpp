#pragma once
#include "weapon_model_trail.hpp"
#include <vector>
namespace daybreak {
// 5f7450/436790: an independent trail owned by one live projectile. Width
// is in world units; count bounds its history, not the projectile lifetime.
struct ProjectileTrail {
 unsigned texture=0,count=0,subdivisions=1,flags=0;
 float width=0;int age=-1;
 std::vector<WeaponTrailPoint> history;
 void configure(unsigned image,float size,unsigned samples,unsigned divisions,unsigned render_flags,const std::array<float,3>& position){
  if(image>=10||!samples||!divisions||samples>4096||divisions>128)throw std::runtime_error("Invalid projectile trail parameters");
  texture=image;width=size;count=samples;subdivisions=divisions;flags=render_flags;age=-1;
  history.assign(count+4,WeaponTrailPoint{position[0],position[1],position[2],1});
 }
 void advance(const std::array<float,3>& position){ // 5f5ec0 ->4369c0
  for(unsigned i=unsigned(history.size())-1;i>0;--i)history[i]=history[i-1];
  history[0]={position[0],position[1],position[2],1};if(age<int(count))++age;
 }
 std::vector<WeaponTrailPoint> curve()const{ // 436ed0; the four end bases depend on live age.
  if(age<0)return {};
  std::vector<WeaponTrailPoint> result((unsigned(age)+1)*subdivisions);
  for(unsigned segment=0;segment<=unsigned(age);++segment)for(unsigned k=0;k<subdivisions;++k){
   unsigned basis=2;
   if(segment==0)basis=0;else if(segment==1)basis=1;
   else if(segment==unsigned(age)-1)basis=7;else if(segment==unsigned(age))basis=8;
   const auto weights=weapon_trail_basis(basis,float(k)/float(subdivisions));WeaponTrailPoint point{};
   for(unsigned axis=0;axis<4;++axis){
    point[axis]=float(double(history[segment][axis])*weights[0]);
    for(unsigned j=1;j<4;++j){const float term=float(double(history[segment+j][axis])*weights[j]);point[axis]+=term;}
   }
   result[segment*subdivisions+k]=point;
  }
  return result;
 }
};
struct ProjectileTrailStrip {std::vector<WeaponTrailVertex> vertices;};
// 436ab0 uses adjacent projected curve points to form a camera-facing ribbon.
// Preserve the native U(0/1), V(0..1), white color and perspective width. Its
// invalid/behind-eye coordinates are clipped here before reaching the driver.
inline std::vector<ProjectileTrailStrip> projectile_trail_strips(const ProjectileTrail& trail,const LegacyMatrix& clip,unsigned left,unsigned top,unsigned width,unsigned height){
 std::vector<ProjectileTrailStrip> result;if(trail.age<=1)return result;
 const auto curve=trail.curve();const unsigned points=unsigned(trail.age)*trail.subdivisions;
 ProjectileTrailStrip strip;
 for(unsigned i=0;i<points;++i){
  auto p=weapon_trail_transform(curve[i],clip),next=weapon_trail_transform(curve[i+1],clip);
  bool valid=std::isfinite(p[3])&&std::isfinite(next[3])&&p[3]>1e-6f&&next[3]>1e-6f;
  for(float v:p)valid&=std::isfinite(v);for(float v:next)valid&=std::isfinite(v);
  if(valid){
   float px=next[1]/next[3]-p[1]/p[3],py=p[0]/p[3]-next[0]/next[3];
   const float length=std::sqrt(px*px+py*py);if(length>0){const float scale=trail.width/p[3];px=px/length*scale;py=py/length*scale;}else px=py=0;
   const float inverse=1.f/p[3];for(auto& v:p)v*=inverse;
   valid=p[2]>=0;
   if(valid){const float cx=float(left+(width>>1)),cy=float(top+(height>>1)),sx=float(width)/2.f,sy=float(height)/2.f,v=float(i)/float(points);
    strip.vertices.push_back({(p[0]+px)*sx+cx,-(p[1]+py)*sy+cy,p[2],p[3],0xffffffff,0,v});
    strip.vertices.push_back({(p[0]-px)*sx+cx,-(p[1]-py)*sy+cy,p[2],p[3],0xffffffff,1,v});
   }
  }
  if(!valid){if(strip.vertices.size()>3)result.push_back(std::move(strip));strip={};}
 }
 if(strip.vertices.size()>3)result.push_back(std::move(strip));return result;
}
}
