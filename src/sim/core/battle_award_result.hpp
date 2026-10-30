#pragma once
#include "battle_award_selector.hpp"
namespace daybreak {
struct BattleAwardResult {
 bool ready=false;
 std::array<unsigned,4> ids{};
 std::array<BattleAwardStatistics,4> records{};
 template<class Random> bool finalize(std::array<BattleAwardStatistics,4> input,Random& random){
  if(ready)return false;
  for(unsigned i=0;i<4;++i)ids[i]=select_battle_award(input[i],random);
  records=input;ready=true;return true;
 }
};
}
