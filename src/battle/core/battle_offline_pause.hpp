#pragma once
#include "title_scene.hpp"
#include <array>
#include <cstdint>
namespace daybreak {
using BattlePauseCounters=std::array<std::array<std::uint32_t,8>,4>;
// Scene+4430/4431, not actor hitstop/time-stop. Input acquisition continues.
struct BattleOfflinePause {
 bool enabled=false,paused=false,hidden=false;
 unsigned toggle_sounds=0;
 bool hide_hud()const{return paused&&hidden;}
 bool show_badge()const{return paused&&!hidden;}
};
//634fb3..63505e: each acquired ACTOR bank is visited in order, without
//deduplicating shared controllers. The first three words include B4/B5 aliases.
inline void advance_battle_offline_pause(BattleOfflinePause& s,bool offline,unsigned phase,const BattlePauseCounters& acquired){
 s.toggle_sounds=0;
 if(!s.enabled||!offline||phase!=2)return;
 for(const auto& actor:acquired){
  if(actor[7]==1){s.paused=!s.paused;++s.toggle_sounds;}
  if(s.paused)for(unsigned button=0;button<7;++button)if(actor[button]==1)s.hidden=!s.hidden;
 }
}
//633ca0/634215..634243;6396f0/63a0af..b8. Original system.bmp crop,
//pivot(128,32), one full-window submission at(400,300), no invented text.
inline SpriteDraw battle_offline_pause_badge(){return sprite(0,272,268,256,64,.5f,.125f,1,.25f);}
}
