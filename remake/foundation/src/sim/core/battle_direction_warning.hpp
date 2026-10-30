#pragma once
#include "legacy_trig.hpp"
namespace daybreak {
// Original actor+850 record: state, direction, retained warning ticks.
struct BattleDirectionWarning {int state=0,direction=0,ticks=0;};
// 4235d0: an attack warning retains its direction for45 ticks, even after
// the incoming lock ends. Repeated attack signals restart the retention.
inline void advance_battle_direction_warning(BattleDirectionWarning& s,int incoming,float angle){
 if(incoming==2)s.ticks=45;else if(s.ticks>0)--s.ticks;
 if(incoming<2&&s.ticks!=0)return;
 s.state=incoming;
 const float sine=legacy_trig(angle,true),cosine=legacy_trig(angle,false);
 if(cosine>legacy_trig(45.f,false))s.direction=0;
 else if(cosine<legacy_trig(135.f,false))s.direction=1;
 else s.direction=sine<=0?3:2;
}
}
