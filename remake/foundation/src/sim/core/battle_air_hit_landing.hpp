#pragma once

namespace daybreak {
// 428510: all three front air-hit states use actor+280 (held jump) at landing.
// Back air hits have no recovery45 branch, regardless of input/down value.
inline unsigned battle_air_hit_landing_state(unsigned hit_state,int down,bool jump_held){
 if(hit_state==113||hit_state==114||hit_state==115)
  return down<100&&jump_held?45u:118u;
 // Preserve the generic fallback for other states, including non-character-3
 // throw victims. Character 3 state135 is handled before this helper.
 return hit_state<200?118u:119u;
}
}
