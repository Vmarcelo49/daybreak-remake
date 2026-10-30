#pragma once
#include "battle_steering.hpp"
#include <cstdint>
namespace daybreak {
struct BattleAttack300Motion {std::uint32_t phase,frame,secondary_frame,moving;float speed,offset;};
// Rena weapon2 original 0x439917..0x439a5e (NOT Keiichi). Return selects 0x434b30 versus 0x434bd0.
inline bool advance_battle_attack300(BattleAttack300Motion& p){
 if(p.phase==1){
  if(p.frame==0){p.speed=45.f;p.moving=1;}
  if(std::int32_t(p.frame)>=16&&std::int32_t(p.frame)<=28){++p.frame;++p.secondary_frame;}
  if(std::int32_t(p.frame)<19&&std::int32_t(p.moving)>0)approach_battle_offset(p.offset,0.f,3.f);
  p.speed=p.speed-2.f;
  if(p.speed<0.f||p.frame==35)p.speed=0.f;
 }
 return p.phase==1&&std::int32_t(p.frame)>24&&std::int32_t(p.frame)<35;
}
}
