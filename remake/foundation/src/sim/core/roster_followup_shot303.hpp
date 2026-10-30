#pragma once
#include "keiichi_ground_shot.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace daybreak {

// Original 559970 admits this branch during character 11/weapon 0 state302.
// Unlike ordinary 400, the 302->303 gate ignores the target-state priority.
inline bool roster_followup_shot303_admission(unsigned character,unsigned weapon,
 unsigned current,bool grounded,unsigned flags,unsigned shoot_release,unsigned rounds){
 return character==11&&weapon==0&&current==302&&grounded&&(flags&0x100)&&
  shoot_release>0&&shoot_release<20&&rounds>0;
}

// The same weapon's grounded dash-melee330 has a parallel linked shot route.
inline bool roster_followup_shot335_admission(unsigned character,unsigned weapon,
 unsigned current,bool grounded,unsigned flags,unsigned shoot_release,unsigned rounds){
 return character==11&&weapon==0&&current==330&&grounded&&(flags&0x100)&&
  shoot_release>0&&shoot_release<20&&rounds>0;
}

// Original 551410 states303 and335 share the attachment-1 firing behavior.
inline GroundShotEffects advance_roster_followup_shot303(unsigned character,unsigned weapon,
 unsigned frame,bool complete,bool grounded,float& speed,float& offset,float elevation){
 if(character!=11||weapon!=0)throw std::invalid_argument("Unsupported followup shot303 binding");
 GroundShotEffects out;
 if(complete){out.next_state=0;return out;}
 if(!grounded){out.next_state=43;return out;}
 if(frame==0)out.started=true;
 if(frame<17){approach_battle_offset(offset,0.f,10.f);speed=5.f;}
 else speed=0;
 if(frame==17){
  out.effect=70;out.voice=0;out.fire=true;out.bullet_slot=0;
  // 435000 is __thiscall; the first explicit argument is socket index 1.
  // Its fourth explicit argument is the target-elevation pitch, not yaw.
  out.origin=GroundShotOrigin::AttachmentZero;out.attachment_slot=1;
  out.pitch=std::clamp(float(std::nearbyint(elevation)),-10.f,10.f);
 }
 return out;
}

} // namespace daybreak
