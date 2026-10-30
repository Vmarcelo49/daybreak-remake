#pragma once
#include "keiichi_normal_projectile.hpp"
namespace daybreak {
// Satoko1 slot6 004b4090, not Ohishi1's reused af60 fields in004d3290.
inline bool satoko_field_tail_state(unsigned state){
 switch(state){
 case 0:case 10:case 20:case 23:case 24:case 27:case 28:case 30:
 case 40:case 41:case 42:case 43:case 44:case 135:case 186:
 case 300:case 301:case 310:case 311:case 320:case 329:case 330:case 331:
 case 332:case 333:case 334:case 340:case 341:case 350:case 360:case 370:
 case 390:case 391:case 392:case 393:case 394:case 400:case 401:case 402:
 case 403:case 404:case 405:case 406:case 407:case 408:case 409:
 case 450:case 451:case 452:case 453:case 460:case 469:return true;
 default:return false;
 }
}
// 4b9a20..4b9ad4. Call only when the actor handler reaches its common tail.
inline bool advance_satoko_field_tail(unsigned& rank,unsigned& timer,unsigned& mine_clock,unsigned& signal,unsigned state){
 --mine_clock;--timer;
 if(projectile_signed(timer)<=0){timer=120;--rank;if(projectile_signed(rank)<0)rank=0;}
 if(projectile_signed(mine_clock)<0)signal=0;
 return projectile_signed(mine_clock)%30==1&&projectile_signed(state)<100;
}
} // namespace daybreak
