#pragma once
// Legacy field name cooldown denotes contact flags, not a countdown; see battle_contact_flags.hpp.
#include <cstdint>
#include <cmath>
namespace daybreak {
struct BattleHitGuard {std::uint32_t word684,last_owner,cooldown,remaining,guard_count,victim_cooldowns[4];};
// 0x637e81..0x637fd8. Impact is the already computed angle, in degrees.
// Finite, bounded angles required so repeated float subtraction makes progress.
inline bool apply_battle_hit_guard(BattleHitGuard& s,float impact,float heading,float offset,std::uint32_t owner,std::uint32_t victim_flags,std::uint32_t attack_flags,float& relative){
 relative=impact-(heading+offset);
 while(relative>180.f)relative-=360.f;
 while(relative< -180.f)relative+=360.f;
 s.word684=0xffffffff;s.last_owner=owner;
 if((!(std::fabs(relative)<=45.f)&&!(victim_flags&0x2000))||!(victim_flags&0x400)||(attack_flags&8))return false;
 s.cooldown=2|((victim_flags&0x8000)?0x100:0);--s.remaining;
 for(auto& c:s.victim_cooldowns)c=2;
 ++s.guard_count;return true;
}
}

