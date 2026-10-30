#pragma once
#include "actor_animation_settings.hpp"
#include "asset_search_path.hpp"
#include "legacy_image_name.hpp"
namespace daybreak {
// 64e7c0 compares DAT source names with the model's original texture names
// using strcmp. CNV conversion/case folding belongs to resource loading only.
inline std::string battle_texture_name_key(const std::string& name){
 return name.substr(0,name.find('\0'));
}
using BattleTextureRemaps=std::map<std::string,std::string>;
inline BattleTextureRemaps battle_texture_remaps(const ActorAnimationSettings& settings,std::int32_t age){
 BattleTextureRemaps result;
 for(const auto& event:settings.events){
  std::array<std::int32_t,3> timing;std::memcpy(timing.data(),event.timing.data(),sizeof timing);
  const auto tick=timing[2]>0?age%timing[2]:age;
  if(timing[0]<=tick&&tick<timing[1])result[battle_texture_name_key(event.source_texture)]=event.replacement_texture;
 }
 return result;
}
}
