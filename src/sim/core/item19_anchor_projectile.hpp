#pragma once
#include "keiichi_normal_projectile.hpp"
#include <stdexcept>

namespace daybreak {
// Original handler 60fd10 cases 20..70 and 90..110. The DAT selects a
// registration; this table captures the source's three formation patterns.
struct Item19AnchorRule {
 float side,forward,elevation,scale_x,scale_yz;
 bool collidable,owner_state_gated;
};
inline bool item19_anchor_rule(unsigned item,unsigned registration,Item19AnchorRule& out){
 if(item!=19)return false;
 switch(registration){
 case 20:out={1.f,60.f,70.f,1.f,.1f,false,true};return true;
 case 30:out={1.f,60.f,70.f,1.f,1.f,true,true};return true;
 case 40:out={1.f,60.f,70.f,1.25f,1.25f,true,true};return true;
 case 50:out={-1.f,60.f,70.f,1.f,.1f,false,true};return true;
 case 60:out={-1.f,60.f,70.f,1.f,1.f,true,true};return true;
 case 70:out={-1.f,60.f,70.f,1.25f,1.25f,true,true};return true;
 case 90:out={0.f,70.f,55.f,1.f,.1f,false,false};return true;
 case 100:out={0.f,70.f,55.f,1.f,1.f,true,false};return true;
 case 110:out={0.f,60.f,70.f,1.25f,1.25f,true,false};return true;
 default:return false;
 }
}
inline bool item19_anchor_registration(unsigned item,unsigned registration){
 Item19AnchorRule ignored{};return item19_anchor_rule(item,registration,ignored);
}
template<class Host> bool tick_item19_anchor_projectile(
 KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 Item19AnchorRule rule{};
 if(!item19_anchor_rule(unsigned(s.item),registration,rule))
  throw std::invalid_argument("Unsupported item19 anchor registration");
 const int owner_state=int(host.owner_state(s));
 if(!rule.owner_state_gated||(owner_state>=450&&owner_state<=463)){
  const auto owner=host.owner_position(s);
  s.heading=host.owner_heading(s);s.offset=host.owner_offset(s);
  const float angle=s.heading+s.offset;
  const float x_base=float(double(legacy_trig(angle,false))*double(rule.forward)+double(owner[0]));
  const float z_base=float(double(legacy_trig(angle,true))*double(rule.forward)+double(owner[2]));
  if(rule.side==0.f){s.position[0]=x_base;s.position[2]=z_base;}
  else {
   const float side_angle=angle+90.f;
   s.position[0]=float(double(x_base)+double(rule.side)*double(legacy_trig(side_angle,false))*50.0);
   s.position[2]=float(double(z_base)+double(rule.side)*double(legacy_trig(side_angle,true))*50.0);
  }
  s.position[1]=rule.elevation+owner[1];
 }
 const int age=projectile_signed(s.frame);
 if(age==0){
  s.scale={rule.scale_x,rule.scale_yz,rule.scale_yz};
  s.speed=.01f;s.scratch_e8=s.scratch_ec=0;
  s.capacity.fill(rule.collidable?1:0);
 }
 ++s.scratch_e8;s.scratch_ec+=2u;
 if(age==41){s.released=true;return false;}
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
