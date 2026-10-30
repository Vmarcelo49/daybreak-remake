#pragma once
#include "battle_steering.hpp"
#include <cstdint>
#include <stdexcept>
namespace daybreak {
// Vtable slot7 (634f60 calls +1c before +18): Keiichi weapon0/1/2 input handlers.
inline constexpr std::uint32_t keiichi_input_dispatch[3]={0x00471210,0x00479640,0x00482860};
struct KeiichiFollowup {unsigned state=301,phase=0,frame=0;bool contact_seen=false;float speed=0,offset=0,movement_angle=0,turn_step=0;};
struct KeiichiFollowupInput {bool complete=false,grounded=true;unsigned contact=0;double distance_squared=0;};
struct KeiichiFollowupEffects {int next_state=-1,next_phase=-1,effect=-1,voice=-1,voice_argument=0;bool initialize=false,clear_contact=false,reset_capacity=false,strike=false;int contact_mode=-1;};
// 46a190/473610/47b940 states301/302 normalize to identical handler bodies.
// Clock advancement and actual DAT geometry are separate, as in the original.
inline KeiichiFollowupEffects advance_keiichi_followup(KeiichiFollowup& s,const KeiichiFollowupInput& in){
 if(s.state!=301&&s.state!=302)throw std::invalid_argument("Unsupported Keiichi followup");
 KeiichiFollowupEffects out;
 if(in.complete){out.next_state=0;return out;}
 if(!in.grounded){out.next_state=43;return out;}
 const unsigned sound_frame=s.state==301?8:10;
 if(s.contact_seen){out.contact_mode=2;if(s.frame<sound_frame)approach_battle_offset(s.offset,0.f,20.f);}
 if(s.frame==0){s.movement_angle=0;out.clear_contact=out.reset_capacity=true;}
 if(s.phase==0&&s.frame==0)out.initialize=true;
 // Frame-zero clear happens before the contact query.
 if(s.frame!=0&&(in.contact&2)){out.next_state=392;out.clear_contact=true;return out;}
 if(s.frame==sound_frame){out.effect=s.state==301?61:62;out.voice=s.state==301?2:3;out.voice_argument=10;}
 if(s.frame==(s.state==301?1u:2u)){s.speed=s.state==301?12.f:10.f;s.turn_step=0;}
 if(s.frame==15){s.speed=0;s.turn_step=0;}
 out.strike=s.state==301?(s.frame>=8&&s.frame<=14):(s.frame>=12&&s.frame<=17);
 return out;
}
}
