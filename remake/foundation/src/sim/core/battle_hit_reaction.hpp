#pragma once
// Legacy field name cooldown denotes contact flags, not a countdown; see battle_contact_flags.hpp.
#include "battle_random.hpp"
namespace daybreak {
struct BattleHitReaction {std::uint32_t cooldown,remaining,selected;};
// 0x63811f..0x6381b7. Selected is the raw 16-bit reaction; dispatch tests it as signed.
inline void select_battle_hit_reaction(BattleHitReaction& s,std::uint32_t reaction,BattleRandom& random){
 s.cooldown=1;--s.remaining;
 s.selected=std::uint16_t(reaction+((reaction==10||reaction==20||reaction==30)?random.next()%3:0));
}
}
