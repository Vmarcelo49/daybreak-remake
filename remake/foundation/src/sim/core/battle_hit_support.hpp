#pragma once
// Legacy field name cooldown denotes contact flags, not a countdown; see battle_contact_flags.hpp.
#include "battle_damage_scaling.hpp"
namespace daybreak {
struct BattleHitSupport {
 std::uint32_t cooldown,remaining,health,healed_total,effect_7e0,effect_7e4;
};
// Original 0x637c89..0x637e0b. True consumes the contact and exits the hit function.
inline bool apply_battle_hit_support(BattleHitSupport& s,bool same_team,std::uint32_t flags,std::uint32_t healing,std::uint32_t duration){
 if(!same_team||!(flags&0x4180))return false;
 s.cooldown=0x80;--s.remaining;
 if(flags&0x4000){
  if(damage_signed(s.health)<=0)return true;
  s.health+=healing;s.healed_total+=healing;
  if(damage_signed(s.health)>=10000)s.health=10000;
 }
 // Both comparisons read 7e4, including the branch that writes 7e0.
 if(flags&0x80)s.effect_7e0=damage_signed(s.effect_7e4)>damage_signed(duration)?s.effect_7e4:duration;
 if(flags&0x100)s.effect_7e4=damage_signed(s.effect_7e4)>damage_signed(duration)?s.effect_7e4:duration;
 return true;
}
}
