#pragma once
#include "keiichi_normal_projectile.hpp"
#include <stdexcept>

namespace daybreak {
// 00626f30 cases 0x78,0x82,0x8c: attached visual registrations emitted by
// character 3's throw. These cases do not query stage or contact collision.
inline bool item38_throw_visual_registration(unsigned item,unsigned registration){
 return item==38&&(registration==120||registration==130||registration==140);
}

template<class Host> bool tick_item38_throw_visual(
 KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 if(!item38_throw_visual_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item38 throw visual registration");
 if(s.frame==0){s.scratch_f4=s.scratch_f8=0;s.speed=0;s.scale.fill(0);}
 const unsigned owner_state=host.owner_state(s);
 if(owner_state!=135&&owner_state!=186){s.released=true;return false;}
 s.pitch=0;
 if(s.scale[0]>=1.f)s.scale.fill(1.f);
 else for(auto& axis:s.scale)axis+=.05f;
 if(owner_state==186){
  std::array<float,3> linked_position;
  float linked_heading,linked_offset;
  if(host.owner_linked_pose(s,linked_position,linked_heading,linked_offset)){
   s.heading=linked_heading;s.offset=linked_offset;
   const float angle=90.f-(linked_heading+linked_offset);
   const float radius=registration==120?135.f:125.f;
   s.position={legacy_trig(angle,true)*radius+linked_position[0],
               linked_position[1]+(registration==120?90.f:50.f),
               legacy_trig(angle,false)*radius+linked_position[2]};
  }
 }else{
  s.heading=host.owner_heading(s);
  s.offset=host.owner_offset(s);
  s.position=host.owner_position(s);
  s.position[1]+=85.f;
  // All three cases restore owner's pitch after the common zero assignment.
  s.pitch=host.owner_pitch(s);
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
