#pragma once
#include <array>
#include <cstdint>
namespace daybreak {
// 634f60 chooses the last actor with a nonzero+828 before calling slot7.
// This snapshot survives both a new time stop and expiry during41f580.
struct BattleFrameSchedule {
 int selected_slot=-1;
 unsigned actor_mask=15,reload_mask=15,owner_motion_mask=15;
 unsigned owner_script_mask(const std::array<unsigned,4>& live828)const{
  if(selected_slot>=0)return 0;
  unsigned mask=0;for(unsigned i=0;i<4;++i)if(live828[i]==0)mask|=1u<<i;
  return mask;
 }
};
inline BattleFrameSchedule make_battle_frame_schedule(const std::array<unsigned,4>& timer828){
 BattleFrameSchedule out;
 for(unsigned i=0;i<4;++i)if(timer828[i]!=0)out.selected_slot=int(i);
 if(out.selected_slot>=0){out.actor_mask=out.reload_mask=1u<<unsigned(out.selected_slot);out.owner_motion_mask=0;}
 return out;
}
}
