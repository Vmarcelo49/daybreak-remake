#pragma once
#include "battle_chasing_air_melee.hpp"

namespace daybreak {
// Original state 0x140 uses the same chase/attack structure in the remaining
// 37 character/weapon handlers. Values below come from those handlers and the
// all-roster x86 oracle, rather than borrowing Keiichi's state-320 timings.
inline ChasingAirMeleePolicy roster_air_melee_policy(unsigned character,unsigned weapon){
 character_action_dispatch(character,weapon);
 if(character<2)return chasing_air_melee_policy(character,weapon);
 if(character==2)throw std::invalid_argument("Keiichi uses his dedicated air melee handler");
 ChasingAirMeleePolicy p;
 p.minimum_vertical=-3;
 p.voice_frame=-1;
 p.approach_timeout=25;
 switch(character){
 case 3: p.initial_speed=12;p.initial_distance_squared=640000;p.initial_strength=160;p.minimum_strength=120;p.strength_decay=2;p.minimum_angle=-30;p.maximum_angle=50;p.turn_step=5;p.attack_distance_squared=70000;p.approach_after=6;p.gravity_after=20;p.landing_after=20;p.voice_frame=11;p.phase2_turn_until=8;p.phase2_turn_step=2;break;
 case 4: p.initial_speed=weapon==2?12:11;p.initial_distance_squared=640000;p.initial_strength=weapon==2?210:175;p.minimum_strength=weapon==2?210:110;p.strength_decay=4;p.minimum_angle=-25;p.maximum_angle=45;p.turn_step=5;p.attack_distance_squared=40000;p.approach_after=15;p.gravity_after=18;p.landing_after=10;p.pitch_bias=p.initial_pitch_bias=25;p.voice_frame=0;p.effect=-1;p.strike_enabled=true;p.strike_begin=weapon==2?6:11;p.strike_end=weapon==2?13:14;break;
 case 5: p.initial_speed=16;p.initial_distance_squared=1000000;p.initial_strength=250;p.minimum_strength=165;p.strength_decay=4;p.minimum_angle=-30;p.maximum_angle=50;p.turn_step=7;p.phase1_turn_step=5;p.attack_distance_squared=60000;p.approach_after=10;p.gravity_after=12;p.landing_after=15;p.voice_frame=0;p.strike_enabled=true;p.strike_begin=2;p.strike_end=9;p.decay_before_velocity=true;p.phase1_moving_increment=true;break;
 case 6: p.initial_speed=13;p.initial_distance_squared=810000;p.initial_strength=210;p.minimum_strength=weapon==0?140:130;p.strength_decay=4;p.minimum_angle=-30;p.maximum_angle=50;p.turn_step=7;p.phase1_turn_step=weapon==0?3:2;p.attack_distance_squared=60000;p.approach_after=6;p.gravity_after=12;p.landing_after=15;p.voice_frame=10;p.phase1_moving_increment=true;p.phase2_turn_until=7;p.phase2_turn_step=3;break;
 case 7: p.initial_speed=12;p.initial_distance_squared=weapon==1?490000:1000000;p.initial_strength=weapon==1?165:220;p.minimum_strength=weapon==1?120:150;p.strength_decay=weapon==1?3:4;p.minimum_angle=-25;p.maximum_angle=30;p.turn_step=5;p.attack_distance_squared=50000;p.approach_after=7;p.gravity_after=15;p.landing_after=20;p.voice_frame=10;p.pitch_bias=p.initial_pitch_bias=5;break;
 case 8: p.initial_speed=10;p.initial_distance_squared=640000;p.initial_strength=180;p.minimum_strength=100;p.strength_decay=4;p.minimum_angle=-35;p.maximum_angle=40;p.turn_step=10;p.attack_distance_squared=50000;p.approach_after=7;p.gravity_after=10;p.landing_after=10;p.voice_frame=0;break;
 case 9: p.initial_speed=13;p.initial_distance_squared=1000000;p.initial_strength=235;p.minimum_strength=130;p.strength_decay=4;p.minimum_angle=-30;p.maximum_angle=50;p.turn_step=7;p.attack_distance_squared=50000;p.approach_after=12;p.gravity_after=13;p.landing_after=13;p.voice_frame=4;p.pitch_bias=p.initial_pitch_bias=15;p.phase1_moving_increment=true;p.phase2_turn_until=5;p.phase2_turn_step=5;break;
 case 10:p.initial_speed=11.5f;p.initial_distance_squared=360000;p.initial_strength=190;p.minimum_strength=110;p.strength_decay=4;p.minimum_angle=-25;p.maximum_angle=35;p.turn_step=5;p.phase1_turn_step=3;p.attack_distance_squared=60000;p.approach_after=10;p.gravity_after=13;p.landing_after=20;p.voice_frame=7;p.pitch_bias=p.initial_pitch_bias=15;p.phase2_turn_until=5;p.phase2_turn_step=3;break;
 case 11:p.initial_speed=12;p.initial_distance_squared=810000;p.initial_strength=220;p.minimum_strength=120;p.strength_decay=4;p.minimum_angle=-30;p.maximum_angle=50;p.turn_step=5;p.phase1_turn_step=4;p.attack_distance_squared=80000;p.approach_after=10;p.gravity_after=10;p.landing_after=18;p.voice_frame=10;p.pitch_bias=p.initial_pitch_bias=10;p.phase2_turn_until=10;p.phase2_turn_step=4;break;
 case 12:p.initial_speed=11.5f;p.initial_distance_squared=360000;p.initial_strength=160;p.minimum_strength=115;p.strength_decay=3;p.minimum_angle=-30;p.maximum_angle=50;p.turn_step=6;p.attack_distance_squared=60000;p.approach_after=3;p.gravity_after=10;p.landing_after=16;p.voice_frame=10;p.phase2_turn_until=10;p.phase2_turn_step=2;break;
 case 13:p.initial_speed=13;p.initial_distance_squared=360000;p.initial_strength=175;p.minimum_strength=130;p.strength_decay=3;p.minimum_angle=-40;p.maximum_angle=30;p.turn_step=5;p.attack_distance_squared=70000;p.approach_after=5;p.gravity_after=10;p.landing_after=15;p.minimum_vertical=-10;p.maximum_vertical=10;p.pitch_bias=p.initial_pitch_bias=15;p.voice_frame=11;p.effect=-1;p.phase2_turn_until=11;p.phase2_turn_step=2;p.phase2_turn_strength_condition=2;p.pitch_recovery_after=35;break;
 case 14:p.initial_speed=weapon==0?10.5f:12.f;p.initial_distance_squared=weapon==0?810000:640000;p.initial_strength=weapon==0?225:180;p.minimum_strength=weapon==0?140:110;p.strength_decay=4;p.minimum_angle=-25;p.maximum_angle=45;p.turn_step=weapon==0?4:5;p.phase1_turn_step=weapon==0?3:2;p.attack_distance_squared=weapon==0?90000:40000;p.approach_after=weapon==0?10:15;p.gravity_after=15;p.landing_after=15;p.pitch_bias=p.initial_pitch_bias=25;p.voice_frame=0;p.effect=-1;if(weapon==0){p.phase2_turn_until=10;p.phase2_turn_step=5;p.phase2_turn_strength_condition=1;}break;
 case 15:p.initial_speed=11.5f;p.initial_distance_squared=1000000;p.initial_strength=230;p.minimum_strength=125;p.strength_decay=4;p.minimum_angle=-30;p.maximum_angle=50;p.turn_step=5;p.attack_distance_squared=40000;p.approach_after=10;p.gravity_after=5;p.landing_after=10;p.voice_frame=3;p.strike_enabled=true;p.strike_begin=3;p.strike_end=7;p.phase2_turn_until=10;p.phase2_turn_step=5;if(weapon==0)p.first_target_bias=0;else {p.initial_pitch_bias=10;p.initial_contact_capacity=3;p.clear_contact_on_hit=true;}break;
 default:throw std::invalid_argument("Unrecovered air melee policy");
 }
 if(character==9)p.pitch_recovery_after=22;
 if(character==10||character==12)p.pitch_recovery_after=20;
 return p;
}
}
