#pragma once
#include "battle_hit_death_state.hpp"
namespace daybreak {
struct BattleHitDeathEntry {std::uint32_t next_state=0,bonus_used=0,extra=0;};
// 0x638c20..0x638ca1, reached only after the caller's nonpositive HP check.
inline BattleHitDeathEntry enter_hit_death(std::uint8_t flag84,std::uint32_t flags,std::uint32_t requested,std::uint32_t current,std::uint32_t bonus_used){
    BattleHitDeathEntry r{select_hit_death_state(flag84,flags,requested),bonus_used,0};
    if(current!=198&&current!=199&&current!=196&&(r.next_state==198||r.next_state==199)&&!r.bonus_used){r.bonus_used=1;r.extra=1;}
    return r;
}
}
