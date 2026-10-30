#pragma once
#include "battle_damage_scaling.hpp"
namespace daybreak {
struct BattleHitTimers{std::uint32_t timer828,long_stop,stop,state,invincible,count,down,down_timer,accum,accum_timer,health,display_health;};
// Original 0x41f580..0x41f73c. State gates retain hit timers during reactions.
inline void tick_battle_hit_timers(BattleHitTimers& s){
 if(s.timer828)--s.timer828;if(s.long_stop)--s.long_stop;
 if(damage_signed(s.stop)>0){--s.stop;return;}
 const auto state=damage_signed(s.state);
 if((state>=124&&state<=129)||state==194){s.invincible=30;s.down=0;s.down_timer=0;s.accum=0;s.accum_timer=0;}
 if(state<100||state>299){
  if(damage_signed(s.invincible)>0)--s.invincible;
  if(damage_signed(s.down_timer)>0)--s.down_timer;else{s.count=0;s.down=0;s.down_timer=0;}
  if(damage_signed(s.display_health)>damage_signed(s.health)){s.display_health-=200;if(damage_signed(s.display_health)<damage_signed(s.health))s.display_health=s.health;}
 }
 if(damage_signed(s.accum_timer)>0)--s.accum_timer;else s.accum=0;
}
}
