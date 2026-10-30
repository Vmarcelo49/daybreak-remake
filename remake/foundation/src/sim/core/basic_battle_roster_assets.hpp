#pragma once
#include "battle_actor_assets.hpp"
#include "battle_action_binding.hpp"
#include "character_asset_files.hpp"
#include "local_battle_roster.hpp"
namespace daybreak {
struct BasicBattleRosterAssets {BattleActorAssetSlots assets;BattleActionBindings actions;};
inline BasicBattleRosterAssets load_battle_roster_assets(AssetSearchPath& search,const LocalBattleRoster& roster,const BattleActionBindings& actions){
 BasicBattleRosterAssets result;result.actions=actions;
 // Reject missing handlers before loading models, rather than substituting another fighter.
 for(unsigned i=0;i<4;++i)if(actions[i].character!=unsigned(roster.character[i])||actions[i].weapon!=unsigned(roster.weapon[i]))throw std::invalid_argument("Roster/action binding mismatch");
 for(unsigned i=0;i<4;++i){
  for(unsigned earlier=0;earlier<i;++earlier)if(roster.character[i]==roster.character[earlier]&&roster.weapon[i]==roster.weapon[earlier]&&roster.option[i]==roster.option[earlier]){result.assets[i]=result.assets[earlier];break;}
  if(!result.assets[i]){
   auto files=load_character_asset_files(search,unsigned(roster.character[i]),unsigned(roster.weapon[i]),roster.option[i]);
   result.assets[i]=std::make_shared<const BattleActorAssets>(files.model,files.frames,std::make_shared<const WeaponItemData>(std::move(files.item)));
  }
 }
 return result;
}
inline BasicBattleRosterAssets load_basic_battle_roster_assets(AssetSearchPath& search,const LocalBattleRoster& roster){
 BattleActionBindings actions;for(unsigned i=0;i<4;++i)actions[i]=basic_battle_action(unsigned(roster.character[i]),unsigned(roster.weapon[i]));
 return load_battle_roster_assets(search,roster,actions);
}
}
