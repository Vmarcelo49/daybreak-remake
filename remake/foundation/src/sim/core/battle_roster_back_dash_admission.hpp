#pragma once
#include "character_dispatch.hpp"
namespace daybreak {
// Grounded slot7 backward command. Bits are the original state28 branches.
inline int roster_back_dash_admission(unsigned character,unsigned weapon,int state,int gauge,unsigned flags,int priority,unsigned contact,int limit){
 character_action_dispatch(character,weapon);
 if(gauge<=0||!(flags&0x100))return -1;
 static constexpr unsigned cancel_masks[]={3,2,7,3,4,7,7,5,7,7,0,7,0,7,0,3};
 const bool hit=state>299&&state<350&&(contact&1);
 if(hit&&state!=320&&(cancel_masks[character]&(1u<<weapon)))return 28;
 if(priority<=limit||(hit&&((character==0&&weapon!=1)||character==15)))return 27;
 return -1;
}
}
