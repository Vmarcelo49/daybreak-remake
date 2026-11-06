#pragma once
#include "character_dispatch.hpp"
#include "psp_roster.hpp"
namespace daybreak {
// The shared roster policy drives DAT-backed common actions; dedicated policies
// override character-specific behavior where that handler has been recovered.
enum class BattleActionPolicy { legacy_test, keiichi_basic, mion_counter, rena_melee, roster_shared, data_driven_preview=roster_shared };
// Two identities in one binding (plan D-2). `character`/`weapon` are the DISPATCH pair: the PC
// combo whose recovered update body, [16][3] tunings, character*3+weapon switch and per-row
// bodies run. `roster_character`/`roster_weapon` are the fighter the match announces: they
// select the assets, the voice bank and the victory identity. For all 46 PC combos the two are
// equal, so no recovered site changes; a PSP fighter (16..18) keeps its roster pair and borrows
// a PC dispatch pair, which is the only way past the ~50 rows that throw for an unknown pair.
struct BattleActionBinding {
 BattleActionPolicy policy=BattleActionPolicy::legacy_test;
 unsigned character=~0u,weapon=~0u;
 std::uint32_t original_update=0;
 unsigned roster_character=~0u,roster_weapon=~0u;
};
using BattleActionBindings=std::array<BattleActionBinding,4>;
inline BattleActionBinding basic_battle_action(unsigned character,unsigned weapon){
 const auto& original=character_action_dispatch(character,weapon);
 if(character==0)return {BattleActionPolicy::rena_melee,character,weapon,original.update,character,weapon};
 if(character==1)return {BattleActionPolicy::mion_counter,character,weapon,original.update,character,weapon};
 // Shared DAT-backed movement, melee, jump and weapon action pipeline.
 if(character!=2)return {BattleActionPolicy::roster_shared,character,weapon,original.update,character,weapon};
 return {BattleActionPolicy::keiichi_basic,character,weapon,original.update,character,weapon};
}
// A binding whose policy and dispatch metadata come from one PC combo while the roster pair
// names another fighter. basic_battle_action(dispatch) keeps original_update equal to the
// dispatch table's entry, which is the consistency check development_animated_combat applies.
inline BattleActionBinding dispatched_battle_action(unsigned roster_character,unsigned roster_weapon,unsigned dispatch_character,unsigned dispatch_weapon){
 BattleActionBinding out=basic_battle_action(dispatch_character,dispatch_weapon);
 out.roster_character=roster_character;out.roster_weapon=roster_weapon;
 return out;
}
// The binding a roster slot gets. PC combos dispatch to themselves; PSP fighters borrow theirs.
inline BattleActionBinding roster_battle_action(unsigned character,unsigned weapon){
 if(is_psp_character(character))return dispatched_battle_action(character,weapon,psp_dispatch_character(character),psp_dispatch_weapon(character,weapon));
 return basic_battle_action(character,weapon);
}
// Historical policy name retained for existing fixtures; the ordinary roster now
// exposes Mion's connected local combat set. Whole-fighter equivalence is unproven.
inline BattleActionBinding mion_counter_action(unsigned weapon){
 const auto& original=character_action_dispatch(1,weapon);
 return {BattleActionPolicy::mion_counter,1,weapon,original.update,1,weapon};
}
inline BattleActionBindings repeated_battle_actions(bool keiichi){
 BattleActionBinding action=keiichi?basic_battle_action(2,0):BattleActionBinding{};
 return {{action,action,action,action}};
}
}
