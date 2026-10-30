#pragma once
#include "asset_search_path.hpp"
#include "battle_voice_route.hpp"
#include "character_names.hpp"
#include "legacy_image_name.hpp"
#include <array>
#include <cstdio>
#include <map>
#include <string>
#include <vector>

namespace daybreak {
// 006b73b0 / 431e70: contiguous resource series, stopped by the first missing file.
inline constexpr std::array<const char*,40> battle_voice_categories{{
 "addattack","attackA","attackB","attackC","attackKO","backattack",
 "backdamage","battlestart","damage","damagedown","damageKO","fire",
 "guard","guarded","HPcheck","intercept","missdamage","nearLose",
 "nearWin","oyashiro","oyashiroB","poison","provoke","recovery",
 "reloadNG","reloadOK","revival","shotA","shotB","shotC",
 "shotFinal","spark","specialA","specialB","tactics","tagback",
 "tagfront","tagOK","thank","specialC"
}};
inline std::string battle_voice_root(unsigned character,unsigned item,unsigned option,bool alternate_special=false){
 if(character>=character_names.size())throw std::out_of_range("Battle voice character");
 if((character==0&&item==33)||(character==4&&item==37)||
    (character==11&&option==1)||(character==14&&item==32&&alternate_special))
  return std::string(character_names[character])+"B";
 return std::string(character_names[character]);
}
class BattleVoiceInventory {
 const AssetSearchPath& assets_;
 struct Fighter{unsigned character=0,item=0,option=0,style=0;};
 std::array<Fighter,4> fighters_{};
 mutable std::map<std::string,std::vector<std::string>> candidates_;
public:
 explicit BattleVoiceInventory(const AssetSearchPath& assets):assets_(assets){}
 void configure(unsigned slot,unsigned character,unsigned item,unsigned option,unsigned style=0){fighters_.at(slot)={character,item,option,style};}
 bool same_actor_configuration(const BattleVoiceInventory& other,unsigned slot)const{
  const auto& a=fighters_.at(slot);const auto& b=other.fighters_.at(slot);
  return a.character==b.character&&a.item==b.item&&a.option==b.option&&a.style==b.style;
 }
 unsigned bank(unsigned slot,bool active)const{const auto& f=fighters_.at(slot);return battle_voice_bank(f.character,f.item,active);}
 const std::vector<std::string>& names(unsigned slot,unsigned which,unsigned category,unsigned style_override=~0u)const{
  static const std::vector<std::string> empty;
  if(slot>=4||category>=battle_voice_categories.size())return empty;
  const auto& f=fighters_[slot];which=bank(slot,which!=0);
  unsigned style=style_override==~0u?f.style:style_override;
  if(which||(category!=4&&category!=7&&category!=10&&category!=26))style=0;
  const auto base="data/voice/"+battle_voice_root(f.character,f.item,f.option,which!=0)+"/"+battle_voice_categories[category];
  auto stem=base+(style==1?"_B":style==2?"_C":"");
  if(style&&!assets_.contains(legacy_converted_image_name(stem+"/000.wav")))stem=base;
  auto found=candidates_.find(stem);if(found!=candidates_.end())return found->second;
  std::vector<std::string> names;
  for(unsigned i=0;;++i){char suffix[32];std::snprintf(suffix,sizeof suffix,"/%03u.wav",i);auto path=stem+suffix;
   if(!assets_.contains(legacy_converted_image_name(path)))break;names.push_back(std::move(path));
  }
  return candidates_.emplace(stem,std::move(names)).first->second;
 }
};
}
