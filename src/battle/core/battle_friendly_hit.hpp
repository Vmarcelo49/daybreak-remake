#pragma once
#include <cstdint>
namespace daybreak {
struct BattleFriendlyHit {std::uint32_t attacker_hits,victim_flag,modifier;};
// Original 0x638287..0x6382d9. Self-hit uses team modifier without friendly-hit flags.
inline void apply_battle_friendly_hit(BattleFriendlyHit& s,bool same_team,bool same_id,std::uint32_t team_modifier){
 s.modifier=100;if(!same_team)return;
 if(!same_id){++s.attacker_hits;s.victim_flag=1;}
 s.modifier=team_modifier;
}
}
