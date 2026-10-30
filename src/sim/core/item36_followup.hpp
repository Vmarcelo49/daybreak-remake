#pragma once
#include <algorithm>
#include <stdexcept>

namespace daybreak {

// Character 5 weapon 2, handler 50aea0, states 420–423. The original uses
// the same frame-15 attack callback in all four states. The first pair brake
// during phase 0 on the ground; the second pair keeps its speed and can
// continue in the air.
struct Item36FollowupState {
 unsigned state=420,phase=0,frame=0;
 bool complete=false,grounded=true;
 float speed=0,offset=0,movement=0,vertical=0,gravity=0;
};
struct Item36FollowupEffects {
 int next_state=-1,effect=-1,voice=-1,voice_argument=0;
 unsigned shooting_attacks=0;
};
inline Item36FollowupEffects advance_item36_followup(Item36FollowupState& action){
 if(action.state<420||action.state>423)throw std::invalid_argument("Unsupported item36 followup state");
 Item36FollowupEffects result;
 const bool ground_pair=action.state<=421;
 if(action.complete){result.next_state=ground_pair?0:43;return result;}
 if(ground_pair&&!action.grounded){action.gravity=.5f;result.next_state=43;return result;}
 if(ground_pair&&action.phase==0)action.speed=std::max(0.f,action.speed-.25f);
 if(action.frame==15){
  result.effect=183;
  result.voice=28;
  result.voice_argument=10;
  result.shooting_attacks=1;
 }
 return result;
}

} // namespace daybreak
