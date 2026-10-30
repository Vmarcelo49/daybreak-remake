#pragma once
// Legacy field name cooldown denotes contact flags, not a countdown; see battle_contact_flags.hpp.
#include "battle_damage_scaling.hpp"
namespace daybreak {
struct BattleHitEligibility {
 std::uint32_t owner_id=0,victim_id=0,flags=0,invulnerability=0,blocked=0,cooldown=0,remaining=0,extent=0,same_team=0,healing=0,hit_gate=0,health=0,targeted=0,victim_target_id=0;float offset=0;
};
// 0x637960..0x637aa1, before geometry. Finite angle contract.
inline bool eligible_battle_hit(const BattleHitEligibility& s){
 if(s.owner_id==s.victim_id&&!(s.flags&0x10000))return false;
 if(damage_signed(s.invulnerability)>0||std::uint8_t(s.blocked)||std::uint16_t(s.cooldown))return false;
 if(damage_signed(s.remaining)<=0||!s.extent)return false;
 if(s.same_team&&!s.healing)return false;
 if(!s.hit_gate&&damage_signed(s.health)<=0)return false;
 if(!s.targeted&&(s.flags&0x20000))return false;
 if(s.flags&0x8000)return s.victim_target_id==s.owner_id&&s.offset<90.f&&s.offset> -90.f;
 return true;
}
}
