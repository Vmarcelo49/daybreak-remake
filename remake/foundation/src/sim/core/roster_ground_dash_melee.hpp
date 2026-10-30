#pragma once
#include "keiichi_air_melee.hpp"
#include "character_dispatch.hpp"
#include <algorithm>

namespace daybreak {
// Source: slot-6 case 0x14a/0x14b of the 46 factory actor handlers. Entry and
// continuation policies are checked against the sampled original x86 handlers;
// the runtime still owns collision geometry, animation and rendered effects.
struct RosterGroundDashEntry {
 float speed=0,far_speed=-1,brake=0,turn=0;
 double chase_distance_squared=0;
 bool set_speed=false,copy_movement_to_offset=false,keep_moving=false;
 bool copy_offset_only_when_chasing=false,copy_offset_only_when_far=false;
 bool turn_only_when_chasing=false,clear_offset_when_far=false;
 int capacity=1,statistics=1;
};
inline RosterGroundDashEntry roster_ground_dash_entry(unsigned character,unsigned weapon,unsigned state){
 character_action_dispatch(character,weapon);
 RosterGroundDashEntry p;
 if(state!=330&&state!=331)throw std::invalid_argument("Ground dash melee state");
 if(state==330){
  switch(character){
  case 2:p.brake=1;p.turn=20;break;
  case 3:p.set_speed=true;p.speed=weapon==2?18.5f:20.f;p.turn=5;p.statistics=3;break;
  case 4:p.set_speed=weapon<2;p.speed=12.5f;p.turn=weapon==2?5.f:15.f;p.keep_moving=weapon==2;break;
  case 5:p.set_speed=true;p.speed=25;p.turn=5;break;
  case 6:p.brake=.5f;p.copy_movement_to_offset=true;p.chase_distance_squared=810000.;break;
  case 7:p.set_speed=weapon==1;p.speed=22.5f;p.brake=weapon==1?0.f:1.5f;p.turn=20;break;
  case 8:p.set_speed=true;p.speed=16.5f;p.turn=20;break;
  case 9:p.turn=15;break;
  case 10:p.turn=15;p.keep_moving=true;break;
  case 11:p.set_speed=true;p.speed=0;p.turn=20;break;
  case 12:p.turn=10;p.keep_moving=true;break;
  case 13:p.turn=5;break;
  case 14:p.set_speed=true;p.speed=20;p.turn=15;break;
  case 15:p.brake=.5f;p.turn=5;if(weapon==1)p.capacity=p.statistics=3;break;
  default:throw std::invalid_argument("Unrecovered ground dash entry");
  }
 }else{
  p.set_speed=true;
  switch(character){
  case 2:p.speed=22;p.far_speed=16;p.copy_movement_to_offset=true;p.chase_distance_squared=810000.;break;
  case 3:p.speed=weapon==2?14.f:20.f;p.copy_movement_to_offset=true;p.chase_distance_squared=490000.;break;
  case 4:p.speed=weapon==2?25.f:15.f;p.copy_movement_to_offset=true;p.chase_distance_squared=weapon==2?360000.:490000.;break;
  case 5:p.speed=25;p.turn=15;break;
  case 6:p.speed=0;p.turn=20;p.chase_distance_squared=360000.;p.copy_movement_to_offset=p.copy_offset_only_when_far=p.turn_only_when_chasing=true;break;
  case 7:p.speed=weapon==1?20.5f:22.5f;p.far_speed=16.5f;p.copy_movement_to_offset=true;p.copy_offset_only_when_chasing=true;p.turn=weapon==1?15.f:20.f;p.turn_only_when_chasing=true;p.chase_distance_squared=weapon==1?640000.:810000.;break;
  case 8:p.speed=17.5f;p.copy_movement_to_offset=true;p.chase_distance_squared=490000.;break;
  case 9:p.speed=20;p.turn=30;p.chase_distance_squared=490000.;p.copy_movement_to_offset=p.copy_offset_only_when_far=p.turn_only_when_chasing=true;break;
  case 10:p.speed=18.5f;p.copy_movement_to_offset=true;p.chase_distance_squared=490000.;break;
  case 11:p.speed=22.5f;p.far_speed=17.5f;p.turn=20;p.chase_distance_squared=360000.;p.copy_movement_to_offset=p.copy_offset_only_when_far=p.turn_only_when_chasing=true;p.capacity=3;break;
  case 12:p.speed=17;p.far_speed=15;p.copy_movement_to_offset=true;p.chase_distance_squared=360000.;break;
  case 13:p.speed=20;p.copy_movement_to_offset=true;p.chase_distance_squared=810000.;break;
  case 14:p.speed=weapon==0?20.f:17.5f;p.copy_movement_to_offset=true;p.chase_distance_squared=490000.;break;
  case 15:p.speed=20;p.far_speed=17.5f;p.copy_movement_to_offset=true;p.chase_distance_squared=360000.;break;
  default:throw std::invalid_argument("Unrecovered ground dash entry");
  }
 }
 return p;
}
inline BattleMeleeVoice roster_ground_dash_voice(int ordinary,const KeiichiAttack300Input& input,float offset,double range_squared=40000.){
 if(input.distance_squared<range_squared&&std::abs(offset)<30.f)
  for(unsigned i=0;i<3;++i)if(input.voice_flags[i]==1)
   return {i==0?0:i==1?15:5,12};
 return {ordinary,10};
}
inline bool roster_ground_dash_melee_airborne_allowed(unsigned character,unsigned state,int phase,int frame){
 return (state==330&&character==7&&(phase==1||(phase==0&&frame>=7)))||
  (state==330&&character==9&&(phase==1||phase==2||phase==3))||
  (state==331&&character==6&&(phase==1||phase==2||phase==4));
}
inline KeiichiAttack300Effects advance_roster_ground_dash_melee(
 unsigned character,unsigned weapon,unsigned state,KeiichiAirMelee& air,
 KeiichiAttack300& action,const KeiichiAttack300Input& input){
 const auto p=roster_ground_dash_entry(character,weapon,state);
 KeiichiAttack300Effects out;
 if(input.animation_complete){out.next_state=0;return out;}
 const bool airborne_exception=roster_ground_dash_melee_airborne_allowed(character,state,action.phase,action.frame);
 if(!input.grounded&&!airborne_exception){
  out.next_state=43;air.gravity=.5f;
  if(character==15){action.speed=std::min(action.speed,10.f);air.vertical=0;}
  return out;
 }
 const bool first=action.frame==0&&
  (action.phase==0||(state==331&&character==9));
 if(first){
  out.initialize=out.clear_contact=true;out.contact_capacity=p.capacity;out.attack_statistics_count=p.statistics;
  // 422490 wraps 423d0: character 14 announces state330 on its first frame.
  if(state==330&&character==14){out.voice=39;out.voice_argument=10;}
  if(!p.keep_moving)action.moving=0;
  if(state==330&&character==4&&weapon==2)action.contact_seen=0;
  if(state==331&&character==10)action.contact_seen=0;
  if(state==330&&character==15&&weapon==1)air.strength=0;
  if(p.chase_distance_squared>0)air.strength=input.distance_squared<p.chase_distance_squared?1:0;
  if(p.copy_movement_to_offset&&
     (!p.copy_offset_only_when_chasing||air.strength==1)&&
     (!p.copy_offset_only_when_far||air.strength==0))action.offset=action.movement_angle;
  if(p.clear_offset_when_far&&!air.strength)action.offset=0;
  if(!(character==5&&state==331))action.movement_angle=0;
  if(p.set_speed)action.speed=air.strength==0&&p.far_speed>=0?p.far_speed:p.speed;
  else if(p.brake)action.speed=std::max(0.f,action.speed-p.brake);
  if(p.turn&&(!p.turn_only_when_chasing||air.strength))approach_battle_offset(action.offset,0,p.turn);
  if(state==331&&(character==2||character==3)&&air.strength==1)
   approach_battle_offset(action.offset,0,20);
  if(state==331&&character==4&&air.strength==1)
   approach_battle_offset(action.offset,0,20);
  if(state==331&&air.strength==1){
   const float entry_turn=character==8||character==10||character==12?20.f:
    character==13?50.f:character==14?(weapon==0?25.f:20.f):
    character==15?10.f:0.f;
   if(entry_turn)approach_battle_offset(action.offset,0,entry_turn);
  }
  if(state==330&&character==6&&air.strength==1)
   approach_battle_offset(action.offset,0,20);
  if(state==331&&character==5&&std::abs(action.movement_angle)>0){
   if(action.movement_angle>0)action.movement_angle=std::max(0.f,action.movement_angle-8.f);
   else action.movement_angle=std::min(0.f,action.movement_angle+8.f);
  }
  if(state==331&&character==7&&(!air.strength||input.distance_squared<160000.))out.next_phase=1;
  return out;
 }
 // Shared support-loss and collision boundaries are recovered here. The
 // character-specific acceleration and phase transitions remain separate work.
 const bool guard_contact=state==330?(character!=4||weapon<2)&&character!=7&&character!=9:
  character!=3&&character!=6&&character!=7&&character!=11;
 if(character==2&&state==330&&action.phase==0&&action.frame<11)
  action.speed=std::max(0.f,action.speed-1.f);
 if(character==2&&state==330&&action.phase==0&&action.frame==11)action.speed=30.f;
 if(character==12&&state==330&&action.phase==2){
  if(action.frame==0){
   const auto voice=roster_ground_dash_voice(3,input,action.offset);
   out.voice=voice.id;out.voice_argument=voice.argument;
  }
  if(action.frame>10)action.speed=std::max(0.f,action.speed-.5f);
 }
 if(guard_contact&&(input.contact&2)){out.next_state=392;out.clear_contact=true;return out;}
 if(state==330&&character==15&&weapon==1&&input.contact)out.clear_contact=true;
 // Each actor's weapon variants share this phase body in the source handler.
 if(character==2){
  if(state==330){
   if(action.phase==0){
    approach_battle_offset(action.offset,0,20);
   }else if(action.phase==1){
    if(input.distance_squared<40000.)action.moving=10;
    if(action.frame>5||input.distance_squared<40000.){out.next_phase=2;return out;}
    approach_battle_offset(action.offset,0,3);
    if(action.frame==0){
     out.effect=62;
     const auto voice=roster_ground_dash_voice(1,input,action.offset);
     out.voice=voice.id;out.voice_argument=voice.argument;
    }
   }else if(action.phase==2)action.speed=std::max(0.f,action.speed-3.f);
  }else{
   if(action.phase<2&&air.strength==1)approach_battle_offset(action.offset,0,20);
   if(action.phase==1&&action.frame>5&&
      (input.distance_squared<40000.||action.frame>10||air.strength==0)){out.next_phase=2;return out;}
   if(action.phase==2){
    action.speed=std::max(0.f,action.speed-.5f);
    if(action.frame<7&&air.strength==1)approach_battle_offset(action.offset,0,2);
    if(action.frame==6){out.secondary_effect=63;out.voice=3;out.voice_argument=10;}
    if(action.frame==20)action.speed=0;
   }
  }
 }
 if(character==3){
  if(state==330){
   if(action.phase==0)approach_battle_offset(action.offset,0,5);
   if(action.phase==1){
    action.speed=weapon==2?18.5f:20.f;
    if(action.frame==0){
     const auto voice=roster_ground_dash_voice(2,input,action.offset);
     out.voice=voice.id;out.voice_argument=voice.argument;
    }
    if(action.frame>15){out.next_phase=2;return out;}
   }
   if(action.phase==2)action.speed=std::max(0.f,action.speed-1.f);
  }else{
   if(action.phase<2&&air.strength==1)approach_battle_offset(action.offset,0,20);
   if(action.phase==1&&action.frame>2&&
      (input.distance_squared<40000.||action.frame>10||air.strength==0)){out.next_phase=2;return out;}
   if(action.phase==2){
    if(action.frame<12&&air.strength==1)approach_battle_offset(action.offset,0,8);
    if(action.frame>13)action.speed=std::max(0.f,action.speed-1.f);
    if(action.frame==10){out.secondary_effect=62;out.voice=2;out.voice_argument=10;}
   }
  }
 }
 if(character==4){
  if(state==330){
   if(weapon<2){
    if(action.phase==0)approach_battle_offset(action.offset,0,15);
    if(action.phase==2){
     action.speed=std::max(0.f,action.speed-1.f);
     if(action.frame==2){out.secondary_effect=62;out.voice=3;out.voice_argument=10;}
    }
   }else{
    if(action.phase==0){
     approach_battle_offset(action.offset,0,5);
     if(action.frame==4)action.speed=25.f;
     if(action.frame==10){
      out.effect=61;
      const auto voice=roster_ground_dash_voice(2,input,action.offset);
      out.voice=voice.id;out.voice_argument=voice.argument;
     }
    }
    if(action.phase==1)approach_battle_offset(action.offset,0,1);
    if(action.phase==2&&action.speed>0)action.speed=std::max(0.f,action.speed-1.75f);
   }
  }else{
   if(action.phase<2&&air.strength==1)approach_battle_offset(action.offset,0,20);
   if(action.phase==2){
    if(action.frame<10&&air.strength==1)approach_battle_offset(action.offset,0,20);
    if(action.frame==(weapon==2?2:13)){
     out.secondary_effect=62;out.voice=3;out.voice_argument=10;
    }
    if(action.frame>(weapon==2?10:20))action.speed=std::max(0.f,action.speed-(weapon==2?6.f:1.f));
   }
  }
 }
 if(character==5){
  if(state==330){
   if(action.phase==0){approach_battle_offset(action.offset,0,5);action.speed=25.f;}
   if(action.phase==2){
    if(action.frame==0){
     out.secondary_effect=61;
     const auto voice=roster_ground_dash_voice(1,input,action.offset);
     out.voice=voice.id;out.voice_argument=voice.argument;
    }
    action.speed=std::max(0.f,action.speed-2.5f);
   }
  }else{
   if(action.frame<22){
    if(action.movement_angle>0)action.movement_angle=std::max(0.f,action.movement_angle-8.f);
    else if(action.movement_angle<0)action.movement_angle=std::min(0.f,action.movement_angle+8.f);
   }
   if(action.frame<12)approach_battle_offset(action.offset,0,5);
   else if(action.frame<18)approach_battle_offset(action.offset,0,27);
   if(action.frame==16){out.effect=62;out.voice=2;out.voice_argument=10;action.speed=0;}
  }
 }
 if(character==6&&state==330){
  if(action.frame<10){
   if(air.strength==1)approach_battle_offset(action.offset,0,20);
   action.speed=std::max(0.f,action.speed-.5f);
  }
  if(action.frame==10){
   action.speed=weapon==0?40.f:25.f;out.effect=62;
   const auto voice=roster_ground_dash_voice(2,input,action.offset,90000.);
   out.voice=voice.id;out.voice_argument=voice.argument;
  }
  if(action.frame>15)action.speed=std::max(0.f,action.speed-(weapon==0?4.f:3.f));
 }
 if(character==6&&state==331){
  if(action.phase==1&&action.frame==0){
   const float distance=float(std::sqrt(float(input.distance_squared)));
   action.speed=std::clamp(float(distance/33.f),weapon==0?2.f:12.f,15.f);
   air.vertical=25.f;air.gravity=1.5f;
  }
  if(action.phase==1&&action.frame==20){
   out.effect=63;
   if(std::abs(action.offset)<30.f&&input.voice_flags[1]==1){out.voice=15;out.voice_argument=12;}
   else if(input.distance_squared<30000.&&std::abs(action.offset)<30.f&&input.voice_flags[2]==1){
    out.voice=5;out.voice_argument=12;
   }else{out.voice=1;out.voice_argument=10;}
  }
  if(action.phase==0&&air.strength==1)approach_battle_offset(action.offset,0,20);
  if(action.phase==1&&air.strength==1)approach_battle_offset(action.offset,0,5);
  if(action.phase==2&&action.frame>15){out.next_phase=3;return out;}
  if(action.phase>0&&action.phase<4){
   air.vertical-=air.gravity;
   if(input.grounded&&air.vertical<0){
    air.vertical=air.gravity=action.speed=0;
    out.next_phase=4;return out;
   }
  }
 }
 if(character==7&&state==330){
  if(action.phase==0){
   if(action.frame<7){
    approach_battle_offset(action.offset,0,weapon==1?20.f:15.f);
    if(weapon!=1)action.speed=std::max(0.f,action.speed-1.5f);
   }
   if(weapon!=1)approach_battle_offset(action.offset,0,5);
   if(action.frame==(weapon==1?7:6)){
    if(weapon!=1)action.speed=27.5f;
    air.vertical=2.f;air.gravity=.5f;
    const auto voice=roster_ground_dash_voice(1,input,action.offset);
    out.voice=voice.id;out.voice_argument=voice.argument;
   }
  }
  if(action.phase==1){
   air.vertical-=.2f;
   if(input.contact){out.next_state=334;return out;}
   if(input.grounded&&air.vertical<0){
    action.speed=air.vertical=air.gravity=0;
    out.next_phase=2;return out;
   }
   if(action.frame>30){out.next_state=339;return out;}
  }
 }
 if(character==7&&state==331){
  if(action.phase==0){
   if(air.strength!=1){out.next_phase=1;return out;}
   approach_battle_offset(action.offset,0,weapon==1?15.f:20.f);
   if(input.distance_squared<160000.){out.next_phase=1;return out;}
  }
  if(action.phase==1){
   if(action.frame<15)approach_battle_offset(action.offset,0,weapon==1?7.f:10.f);
   if(action.frame==0){
    approach_battle_offset(action.offset,0,180);
    action.speed=12.5f;action.movement_angle=0;
    out.clear_contact=true;out.contact_capacity=1;
    if(weapon!=1)out.frame_override=5;
   }
   if(action.frame==13)action.speed=16.5f;
   if(action.frame==18){out.voice=3;out.voice_argument=10;}
  }
  if(action.phase==2){
   approach_battle_offset(action.offset,0,10);
   if(action.frame==0)out.effect=62;
   if(action.frame==20){air.vertical=0;out.next_phase=3;return out;}
  }
  if(action.phase==3)action.speed=std::max(0.f,action.speed-1.f);
 }
 if(character==9&&state==330){
  if(action.phase==0)approach_battle_offset(action.offset,0,15);
  if(action.phase==1){
   if(action.frame==0){
    out.voice=1;out.voice_argument=10;
    air.vertical=35.f;air.gravity=2.5f;
    const float distance=float(std::sqrt(float(input.distance_squared)));
    action.speed=std::clamp(float(distance/28.f),5.f,15.f);
   }
   approach_battle_offset(action.offset,0,5);
   if(air.vertical<8.f){action.speed=0;out.next_phase=2;return out;}
  }
  if(action.phase==4&&action.frame==4){
   out.effect=62;out.secondary_effect=168;out.voice=32;out.voice_argument=10;
   out.spawned_states={{300,310}};
  }
  if(action.phase>=1&&action.phase<=3){
   approach_battle_offset(action.offset,0,10);
   air.vertical-=air.gravity;
   if(input.grounded&&air.vertical<0){
    action.speed=air.vertical=air.gravity=0;
    out.next_phase=4;return out;
   }
  }
 }
 if(character==8){
  if(state==330){
   if(action.phase==0)approach_battle_offset(action.offset,0,20);
   if(action.phase==1){
    approach_battle_offset(action.offset,0,5);
    if(action.frame>2&&input.distance_squared<90000.){out.next_phase=2;return out;}
   }
   if(action.phase==2){
    if(action.frame==0)action.speed=22.5f;
    if(action.frame>10)action.speed-=1.5f;
    action.speed=std::max(0.f,action.speed);
    if(action.frame==4){
     const auto voice=roster_ground_dash_voice(1,input,action.offset);
     out.voice=voice.id;out.voice_argument=voice.argument;
    }
   }
  }else{
   if(action.phase<2&&air.strength==1)approach_battle_offset(action.offset,0,20);
   if(action.phase==1&&action.frame>2&&
      (input.distance_squared<60000.||action.frame>20||air.strength==0)){out.next_phase=2;return out;}
   if(action.phase==2){
    if(action.frame==9){out.voice=3;out.voice_argument=10;}
    action.speed=std::max(0.f,action.speed-.3f);
   }
  }
 }
 if(character==9&&state==331){
  if(action.frame<12&&air.strength==1)approach_battle_offset(action.offset,0,30);
  if(action.frame>=12&&action.frame<24&&air.strength==1)
   approach_battle_offset(action.offset,0,5);
  if(action.frame>12)action.speed=std::max(0.f,action.speed-.5f);
  if(action.frame==25)action.speed=0;
  if(action.frame==12){out.effect=62;out.voice=2;out.voice_argument=10;}
 }
 if(character==10){
  if(state==330){
   if(action.phase==0)approach_battle_offset(action.offset,0,15);
   if(action.phase==1){
    approach_battle_offset(action.offset,0,4);
    action.speed=30.f;
    if(input.distance_squared<160000.||action.frame>2){
     const auto voice=roster_ground_dash_voice(1,input,action.offset);
     out.voice=voice.id;out.voice_argument=voice.argument;out.next_phase=2;return out;
    }
   }
   if(action.phase==2){
    if(action.frame==10){out.effect=62;out.voice=2;out.voice_argument=10;}
    if(action.frame==17)action.speed=0;
   }
   if(action.phase>0&&action.frame<17)action.speed=std::max(5.f,action.speed-1.5f);
  }else{
   if(action.phase<2&&air.strength==1)approach_battle_offset(action.offset,0,20);
   if(action.phase==1&&action.frame>2&&
      (input.distance_squared<60000.||action.frame>20||air.strength==0)){
    out.next_phase=2;return out;
   }
   if(action.phase==2){
    if(action.contact_seen==1)approach_battle_offset(action.offset,0,7);
    if(action.frame==8){out.secondary_effect=63;out.voice=2;out.voice_argument=10;}
    if(action.frame==16)action.speed=0;
    action.speed=std::max(0.f,action.speed-.35f);
   }
  }
 }
 if(character==11){
  if(state==330){
   if(action.phase==0)approach_battle_offset(action.offset,0,20);
   if(action.phase==1){
    action.speed=22.5f;
    if(input.distance_squared<90000.||action.frame>10){out.next_phase=2;return out;}
    approach_battle_offset(action.offset,0,10);
   }
   if(action.phase==2){
    if(action.frame==18){
     action.speed=0;out.effect=62;
     const auto voice=roster_ground_dash_voice(3,input,action.offset);
     out.voice=voice.id;out.voice_argument=voice.argument;
    }
    if(action.frame<19)approach_battle_offset(action.offset,0,5);
   }
  }else{
   if(action.phase==0&&air.strength==1)approach_battle_offset(action.offset,0,20);
   if(action.phase==1&&air.strength==1)approach_battle_offset(action.offset,0,10);
   if(action.phase==1&&action.frame>5&&
      (input.distance_squared<60000.||air.strength==0)){out.next_phase=2;return out;}
   if(action.phase==2){
    if(action.frame==6){out.secondary_effect=62;out.voice=2;out.voice_argument=10;}
    action.speed=std::max(0.f,action.speed-.75f);
    if(action.frame==25)action.speed=0;
   }
  }
 }
 if(character==12){
  if(state==330){
   if(action.phase==0)approach_battle_offset(action.offset,0,10);
   if(action.phase==1){
    approach_battle_offset(action.offset,0,5);
    action.speed=20.f;
    if(input.distance_squared<90000.){out.next_phase=2;return out;}
   }
  }else{
   if(action.phase<2&&air.strength==1)approach_battle_offset(action.offset,0,20);
   if(action.phase==1&&(input.distance_squared<60000.||air.strength==0)){
    out.next_phase=2;return out;
   }
   if(action.phase==2){
    if(action.frame<16&&air.strength==1)approach_battle_offset(action.offset,0,5);
    if(action.frame==16){out.secondary_effect=63;out.voice=2;out.voice_argument=10;}
    if(action.frame==19)action.speed=0;
   }
  }
 }
 if(character==13){
  if(state==330){
   if(action.phase==0)approach_battle_offset(action.offset,0,5);
   if(action.phase==1){
    approach_battle_offset(action.offset,0,5);
    action.speed=27.5f;
    if(action.frame>2&&(input.distance_squared<90000.||action.frame==12)){
     out.next_phase=2;return out;
    }
   }
   if(action.phase==2){
    if(action.frame<10)approach_battle_offset(action.offset,0,5);
    if(action.frame==10){
     out.secondary_effect=62;action.speed=0;
     const auto voice=roster_ground_dash_voice(3,input,action.offset);
     out.voice=voice.id;out.voice_argument=voice.argument;
    }
   }
  }else{
   if(action.phase==0&&air.strength==1)approach_battle_offset(action.offset,0,50);
   if(action.phase==1&&action.frame>2&&
      (input.distance_squared<90000.||air.strength==0)){out.next_phase=2;return out;}
   if(action.phase==2){
    if(action.frame==2)action.speed=20.f;
    if(action.frame==13){out.secondary_effect=62;out.voice=3;out.voice_argument=10;}
    if(action.frame==26)action.speed=0;
   }
  }
 }
 if(character==14){
  if(state==330){
   if(action.phase==0)approach_battle_offset(action.offset,0,15);
   if(action.phase==2){
    if(action.frame>20)action.speed=std::max(0.f,action.speed-1.f);
    if(action.frame==2)out.secondary_effect=62;
   }
  }else{
   if(action.phase<2&&air.strength==1)
    approach_battle_offset(action.offset,0,weapon==0?25.f:20.f);
   if(action.phase==2){
    if(action.frame<13&&air.strength==1)approach_battle_offset(action.offset,0,20);
    if(action.frame==13){out.secondary_effect=62;out.voice=3;out.voice_argument=10;}
    if(action.frame>13)action.speed=std::max(0.f,action.speed-1.f);
   }
  }
 }
 if(character==15){
  if(state==330){
   if(action.phase==0){
    action.speed=std::max(0.f,action.speed-.5f);
    approach_battle_offset(action.offset,0,5);
   }
   if(action.phase==1){approach_battle_offset(action.offset,0,5);action.speed=30.f;}
   if(action.phase==2){
    if(action.frame>4)action.speed=std::max(0.f,action.speed-2.f);
    if(action.frame==3){
     out.effect=62;
     const auto voice=roster_ground_dash_voice(2,input,action.offset);
     out.voice=voice.id;out.voice_argument=voice.argument;
    }
   }
  }else{
   if(action.frame<10&&air.strength==1)approach_battle_offset(action.offset,0,10);
   if(action.frame==8){out.effect=62;out.voice=3;out.voice_argument=10;}
   if(action.frame>15)action.speed=std::max(0.f,action.speed-1.f);
  }
 }
 if(state==330&&((character==4&&weapon<2&&action.phase==2&&action.frame>=2&&action.frame<=9)||
                 (character==15&&action.phase==2&&action.frame>=4&&action.frame<=9)))out.strike=true;
 if(state==331&&((character==2&&action.phase==2&&action.frame>=3&&action.frame<=19)||
                 (character==4&&action.phase==2&&action.frame>=(weapon==2?1:14)&&action.frame<=(weapon==2?10:23))||
                 (character==14&&weapon==1&&action.phase==2&&action.frame>=14&&action.frame<=23)||
                 (character==15&&action.frame>=7&&action.frame<=16)))out.strike=true;
 return out;
}
}
