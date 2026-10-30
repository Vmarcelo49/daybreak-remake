#pragma once
#include "roster_ground_shot400_schedule.hpp"
namespace daybreak {
struct RosterChargeShotRoundRange {  unsigned char character,weapon,phase,frame,min_rounds,max_rounds;unsigned short state;signed char frame_delta;unsigned short event_begin,event_count; };
inline constexpr RosterShot400Event roster_charge_shot_round_events[] = {
 {5,0,0,15,RosterShot400Kind::Effect,120,0,0.f,0.f,0.f},
 {5,0,0,15,RosterShot400Kind::AttackCount,0,0,0.f,0.f,0.f},
 {5,0,0,15,RosterShot400Kind::Voice,30,0,0.f,0.f,0.f},
 {5,0,0,15,RosterShot400Kind::Hand,1,0,0.f,0.f,0.f},
 {5,0,0,15,RosterShot400Kind::Effect,120,0,0.f,0.f,0.f},
 {5,0,0,15,RosterShot400Kind::AttackCount,0,0,0.f,0.f,0.f},
 {5,0,0,15,RosterShot400Kind::Voice,30,0,0.f,0.f,0.f},
 {5,0,0,15,RosterShot400Kind::Hand,1,0,0.f,0.f,0.f},
 {5,1,0,15,RosterShot400Kind::Effect,120,0,0.f,0.f,0.f},
 {5,1,0,15,RosterShot400Kind::AttackCount,0,0,0.f,0.f,0.f},
 {5,1,0,15,RosterShot400Kind::Voice,30,0,0.f,0.f,0.f},
 {5,1,0,15,RosterShot400Kind::Attachment,2,0,0.f,0.f,0.f},
 {5,1,0,15,RosterShot400Kind::Effect,120,0,0.f,0.f,0.f},
 {5,1,0,15,RosterShot400Kind::AttackCount,0,0,0.f,0.f,0.f},
 {5,1,0,15,RosterShot400Kind::Voice,30,0,0.f,0.f,0.f},
 {5,1,0,15,RosterShot400Kind::Attachment,2,0,0.f,0.f,0.f},
 {5,2,0,13,RosterShot400Kind::Effect,184,0,0.f,0.f,0.f},
 {5,2,0,13,RosterShot400Kind::AttackCount,0,0,0.f,0.f,0.f},
 {5,2,0,13,RosterShot400Kind::Voice,30,0,0.f,0.f,0.f},
 {5,2,0,13,RosterShot400Kind::World,2,0,30.f,0.f,100.f},
 {5,2,0,13,RosterShot400Kind::Effect,184,0,0.f,0.f,0.f},
 {5,2,0,13,RosterShot400Kind::AttackCount,0,0,0.f,0.f,0.f},
 {5,2,0,13,RosterShot400Kind::Voice,30,0,0.f,0.f,0.f},
 {5,2,0,13,RosterShot400Kind::World,2,0,30.f,0.f,100.f},
};
inline constexpr RosterChargeShotRoundRange roster_charge_shot_round_ranges[] = {
 {5,0,0,15,1,1,450,1,0,4},
 {5,0,0,15,1,1,460,1,4,4},
 {5,1,0,15,1,1,450,1,8,4},
 {5,1,0,15,1,1,460,1,12,4},
 {5,2,0,13,1,1,450,1,16,4},
 {5,2,0,13,1,1,460,1,20,4},
};
} // namespace daybreak
