#pragma once
#include "battle_special_gauges.hpp"
#include <algorithm>
namespace daybreak {
// Original widgets +564 (charging) and +610/+6bc (active) are distinct
// thiscall receivers. The first divides by threshold, the latter by duration.
struct BattleSpecialHud {float fraction=0;bool ready=false,active=false;};
inline BattleSpecialHud battle_special_hud(const BattleSpecialGauges& s){
 BattleSpecialHud h;const auto mode=s.mode&255u;if(mode>2)return h;
 h.active=mode==0?s.active0:mode==1?s.active1:s.active2;
 const auto value=mode==0?s.charge0:mode==1?s.charge1:s.charge2;
 const auto threshold=mode==1?s.limit1:s.limit0;
 const auto duration=mode==1?s.duration1:s.duration0;
 const auto maximum=h.active?duration:threshold;
 if(damage_signed(maximum)>0)h.fraction=std::clamp(float(damage_signed(value))/float(damage_signed(maximum)),0.f,1.f);
 h.ready=!h.active&&damage_signed(value)>=damage_signed(threshold);
 return h;
}
}
