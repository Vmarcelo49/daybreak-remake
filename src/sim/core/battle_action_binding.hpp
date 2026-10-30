#pragma once
#include "character_dispatch.hpp"
namespace daybreak {
// The shared roster policy drives DAT-backed common actions; dedicated policies
// override character-specific behavior where that handler has been recovered.
enum class BattleActionPolicy { legacy_test, keiichi_basic, mion_counter, rena_melee, roster_shared, data_driven_preview=roster_shared };
struct BattleActionBinding {
 BattleActionPolicy policy=BattleActionPolicy::legacy_test;
 unsigned character=~0u,weapon=~0u;
 std::uint32_t original_update=0;
};
using BattleActionBindings=std::array<BattleActionBinding,4>;
inline BattleActionBinding basic_battle_action(unsigned character,unsigned weapon){
 const auto& original=character_action_dispatch(character,weapon);
 if(character==0)return {BattleActionPolicy::rena_melee,character,weapon,original.update};
 if(character==1)return {BattleActionPolicy::mion_counter,character,weapon,original.update};
 // Shared DAT-backed movement, melee, jump and weapon action pipeline.
 if(character!=2)return {BattleActionPolicy::roster_shared,character,weapon,original.update};
 return {BattleActionPolicy::keiichi_basic,character,weapon,original.update};
}
// Historical policy name retained for existing fixtures; the ordinary roster now
// exposes Mion's connected local combat set. Whole-fighter equivalence is unproven.
inline BattleActionBinding mion_counter_action(unsigned weapon){
 const auto& original=character_action_dispatch(1,weapon);
 return {BattleActionPolicy::mion_counter,1,weapon,original.update};
}
inline BattleActionBindings repeated_battle_actions(bool keiichi){
 BattleActionBinding action=keiichi?basic_battle_action(2,0):BattleActionBinding{};
 return {{action,action,action,action}};
}
}
