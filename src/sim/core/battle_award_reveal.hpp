#pragma once
#include "battle_local_result.hpp"
#include <algorithm>
namespace daybreak {
// 63ab9e..63ae87: signed (scene+41dc - 30)/30, capped at four actors.
inline unsigned battle_award_visible_rows(unsigned counter){
 return unsigned(std::clamp(damage_signed(counter-30u)/30,0,4));
}
// 636a02..636b1b. Called before BattleLocalResult advances this frame;
// the native client already owns these sounds in LegacyClientSceneServices.
template<class Emit> void battle_award_reveal_sounds(const BattleLocalResult& result,
 const std::array<unsigned,4>& presses,Emit&& emit){
 if(!result.ready||result.presentation_phase!=5)return;
 if(!result.presentation_offset)emit(22u);
 const unsigned next=result.presentation_offset+1;
 if(next>=60&&next<=150&&next%30==0)emit(21u);
 if(next<150)for(unsigned c=0;c<4;++c)
  if((result.shared_confirmation||c==result.primary_actor)&&(presses[c]&127u)){emit(21u);break;}
}
}
