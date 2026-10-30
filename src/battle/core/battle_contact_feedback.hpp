#pragma once
#include "battle_sound_mode.hpp"
#include <cstdint>
#include <vector>
namespace daybreak {
// Ordered64ae70 actor SE,64af20 local system SE and64aed0 global system SE.
struct BattleContactSoundRequest {
 unsigned actor=0,id=0;std::array<float,3> position{};
 BattleSoundMode mode=BattleSoundMode::Spatial;
 bool projectile=false,system=false,local_only=false;
};
template<std::size_t N> bool battle_contact_sound_audible(const BattleContactSoundRequest& request,const std::array<unsigned,N>& controlled,unsigned count){
 if(!request.local_only)return true;
 for(unsigned n=0;n<count&&n<N;++n)if(controlled[n]==request.actor)return true;
 return false;
}
struct BattleContactFeedback {
 unsigned victim=0;std::vector<BattleContactSoundRequest> sounds;
 void reset(unsigned slot){victim=slot;sounds.clear();}
 void reaction(std::int32_t id,const std::array<float,3>& position,unsigned spatial){
  sounds.push_back({victim,unsigned(id),position,spatial?BattleSoundMode::Spatial:BattleSoundMode::Plain});
 }
 void notify(unsigned actor,unsigned code){
  if(code==5||code==6)sounds.push_back({actor,code,{},BattleSoundMode::Plain,false,true,true});
 }
 void event(unsigned code){sounds.push_back({victim,code,{},BattleSoundMode::Plain,false,true,false});}
};
}
