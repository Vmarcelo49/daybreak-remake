#pragma once
#include "local_selection_slots.hpp"
#include "local_match_rules.hpp"
#include "battle_random.hpp"
#include "battle_player_name.hpp"
#include <optional>
#include <type_traits>
#include <stdexcept>
namespace daybreak {
// Local data writes in 40d130. Input object allocation is represented as an effect.
struct LocalBattleRoster {
 std::array<int,4> owner{},character{},weapon{},controller_actor{{-1,-1,-1,-1}};
 // Legacy names: costume stores6cfb48 -> actor318 special mode; option is the model variant.
 std::array<unsigned char,4> costume{},option{},flags{};
 std::array<unsigned,4> controlled_slots{};unsigned controlled_count=0,stage=0;
 std::array<BattlePlayerName,4> player_names{}; // frozen online controller names; empty for local/CPU slots.
 bool networked=false; // local runtime role, never serialized.
 bool story_mode=false;int story_music=0; // 6cfce9 and signed app+53bf[round]; never serialized.
 bool fallback_input=false;
 std::optional<BattleRandom> simulation_random; //carry the selection RNG state into combat; not a wire field.
 bool spectating=false;unsigned spectator_actor=0;
 std::array<int,4> rule_values{{100,100,100,100}}; // HP divisor, special charge scale, blue/red resource limits.
};
template<class Random> void inherit_roster_random(LocalBattleRoster& roster,const Random& random){
 if constexpr(std::is_same_v<std::decay_t<Random>,BattleRandom>)roster.simulation_random=random;
}
inline unsigned local_random_stage(unsigned value){const unsigned n=value%13;return n<6?n+1:n<12?n+5:21;}
template<class Random>
LocalBattleRoster prepare_default_battle_roster(Random& random,unsigned player_character=2){
 if(player_character>=16)throw std::invalid_argument("Invalid default player character");
 LocalBattleRoster result;result.character[0]=int(player_character);result.weapon[0]=0;result.owner[0]=0;
 result.controller_actor[0]=0;
 result.controlled_slots[0]=0;result.controlled_count=1;
 for(unsigned i=1;i<4;++i){
  // 40d130 draws each unselected slot independently with next()%16.
  const unsigned character=random.next()%16;
  result.character[i]=int(character);result.owner[i]=4;
  result.weapon[i]=int(random.next()%(character<14?3:2));
  result.costume[i]=static_cast<unsigned char>(random.next()%3);
  result.option[i]=static_cast<unsigned char>(random.next()%local_option_counts[character]);
 }
 inherit_roster_random(result,random);return result;
}
template<class Random>
LocalBattleRoster prepare_local_roster(LocalSelectionSlots& slots,LocalMatchRules& rules,Random& random){
 LocalBattleRoster result;
 result.rule_values=rules.values;
 for(unsigned i=0;i<4;++i){
  if(slots.character[i]<0){
   result.character[i]=int(random.next()%16);result.owner[i]=4;
   result.weapon[i]=int(random.next()%(result.character[i]<14?3:2));
   result.costume[i]=static_cast<unsigned char>(random.next()%3);
   slots.option[i]=random.next()%local_option_counts[result.character[i]];
  }else{
   result.character[i]=slots.character[i];result.owner[i]=slots.owner[i];result.flags[i]=slots.flag3cd4[i];
   if(result.owner[i]>=0&&result.owner[i]<4)result.controller_actor[result.owner[i]]=int(i);
   result.weapon[i]=slots.weapon[i];result.costume[i]=static_cast<unsigned char>(slots.costume[i]);
   // Original tests signed owner<4 here, unlike the controller_actor index guard.
   if(result.owner[i]<4)result.controlled_slots[result.controlled_count++]=i;
  }
  result.option[i]=static_cast<unsigned char>(slots.option[i]);
 }
 if(!result.controlled_count){result.controlled_count=1;result.controlled_slots[0]=0;result.fallback_input=true;}
 if(rules.stage==0){result.stage=local_random_stage(random.next());rules.variant=int(result.stage);}
 else result.stage=unsigned(rules.variant*10+rules.stage);
 inherit_roster_random(result,random);return result;
}
}
