#pragma once
#include "character_dispatch.hpp"
#include "keiichi_special_strike.hpp"
#include <algorithm>

namespace daybreak {
struct RosterSpecialStrikeEffects {
 KeiichiAttack300Effects action;
 bool activate=false;
 bool capture_requested=false,release_requested=false;
 int projectile_slot=-1;
 float projectile_forward=100.f,projectile_height=80.f;
};

// State370 is not a single shared melee action. Character 3's three weapon
// handlers (4a9c40/4b4090/4bc040) use a three-phase chase. Character 7's
// three handlers (531ce0/53bc00/545f00) cast from rest. Character 10's
// three handlers (571ca0/57f600/58a6a0) use passive deceleration.
// Character 12's three handlers (5b0990/5b9680/5c3350) share a cast wind-up.
// Character 13's three handlers (595460/59e630/5a7ea0) share a projectile dash.
// Character 15's two handlers (5e2af0/5ed860) reopen contact for five sweeps.
// Character 14 weapon0 (5cb6a0) repeats a seven-count projectile volley.
// Character 6 weapons0/2 (516230/527880) sustain a stationary visual field.
// Character 8's three handlers (4c57f0/4ccc00/4d5980) launch from a hover.
// Character 9's three handlers (4dee70/4e7680/4f0040) use a six-phase leap.
// Character 4's two DAT-backed handlers (484be0/492f70) enter a linked grab.
// Other non-Keiichi families retain the provisional handler until recovered.
inline RosterSpecialStrikeEffects advance_roster_special_strike(
 unsigned character,unsigned weapon,KeiichiSpecialStrike& saved,
 KeiichiAttack300& action,const KeiichiAttack300Input& request){
 character_action_dispatch(character,weapon);
 RosterSpecialStrikeEffects result;
 if((character!=3&&character!=4&&character!=6&&character!=7&&character!=8&&character!=9&&character!=10&&character!=12&&character!=13&&character!=14&&character!=15)||
    (character==6&&weapon==1)||(character==14&&weapon!=0)){
  result.action=advance_keiichi_special_strike(saved,weapon,action,request);
  result.activate=result.action.initialize;
  if(character==2&&action.frame==0&&result.action.initialize)
   result.action.contact_capacity=1;
  return result;
 }
 saved.hold_clock=false;saved.magazine_gate=-1;
 if(character==4){
  if(request.animation_complete){result.action.next_state=0;return result;}
  if(!request.grounded){result.action.next_state=43;action.gravity=.5f;return result;}
  if(action.phase==0&&action.frame==0){
   action.movement_angle=0;action.speed=0;
   approach_battle_offset(action.offset,0.f,180.f);
   saved.held=0;action.moving=0;action.contact_seen=1;
   result.action.clear_contact=result.action.initialize=result.activate=true;
   result.action.contact_capacity=1;
   return result;
  }
  if(request.contact&0x80u)result.capture_requested=true;
  return result;
 }
 if(character==6){
  if(action.frame==0){
   action.moving=0;result.action.effect=49;
   result.action.clear_contact=true;result.action.contact_capacity=1;
  }
  if(request.animation_complete||action.moving>60){result.action.next_state=0;return result;}
  if(action.moving==0)result.action.spawned_states[0]=360;
  ++action.moving;action.gravity=0;action.movement_angle=0;action.speed=0;
  if(action.frame==44)result.action.frame_override=43;
  return result;
 }
 if(character==8){
  if(request.animation_complete){result.action.next_state=0;return result;}
  if(request.grounded&&action.phase<2&&action.vertical<0){
   result.action.next_phase=2;result.action.effect=40;result.action.secondary_effect=133;
   result.projectile_slot=weapon==0?8:weapon==1?6:27;
   result.projectile_forward=0;result.projectile_height=0;
   action.vertical=0;action.gravity=0;
   return result;
  }
  if(action.phase<2)action.vertical-=action.gravity;
  if(action.phase==2){
   action.speed=std::max(0.f,action.speed-1.f);
   if(!request.grounded){result.action.next_state=43;action.gravity=.5f;return result;}
   if(action.frame==28&&saved.held<30){++saved.held;saved.hold_clock=true;return result;}
  }
  if(action.phase==0){
   approach_battle_offset(action.offset,0.f,1.f);
   if(action.frame==5){
    // 4c8924 converts actor+2c (rotation), not a random value. Every held
    // tick subtracts 20 degrees; the clock resumes only at a full turn.
    if(action.vertical>=0.f||int(std::nearbyint(saved.hover_spin))%360!=0){
     saved.hover_spin-=20.f;saved.hold_clock=true;return result;
    }
    saved.hover_spin=0;
   }
   if(action.frame==0){
    result.action.effect=132;result.action.initialize=result.action.clear_contact=result.activate=true;
    result.action.contact_capacity=1;
    action.speed=5;action.vertical=50;action.gravity=.8f;action.movement_angle=0;
    saved.held=0;
   }
  }
  return result;
 }
 if(character==9){
  if(request.animation_complete){result.action.next_state=0;return result;}
  if((action.phase<2||action.phase==5)&&!request.grounded){result.action.next_state=43;return result;}
  if(action.phase==0&&action.frame==0){
   result.action.initialize=result.action.clear_contact=result.activate=true;
   result.action.contact_capacity=1;
   approach_battle_offset(action.offset,0.f,180.f);
   action.movement_angle=0;action.speed=0;
  }
  if(action.phase==0){
   if(action.frame==6){action.movement_angle=0;action.speed=45;}
   if(action.frame==12)action.speed=0;
   if(action.frame==20){result.action.next_phase=1;return result;}
  }
  if(action.phase==1){
   if(action.frame<5)action.speed=0;
   if(action.frame==3){
    result.action.voice=3;result.action.voice_argument=10;
    action.speed=0;action.vertical=40;action.gravity=1;
    result.action.clear_contact=true;result.action.contact_capacity=7;
   }
  }
  if(action.phase>=2&&action.phase<=4){
   action.vertical-=action.gravity;
   if(request.grounded&&action.vertical<0){
    action.vertical=0;action.gravity=0;action.speed=0;
    result.action.next_phase=5;return result;
   }
  }
  if(action.phase==2){
   if(request.contact){
    if(saved.held>2){saved.held=0;result.action.clear_contact=true;}
    ++saved.held;
   }
   if(action.vertical<0){result.action.next_phase=3;return result;}
  }
  return result;
 }
 if(request.animation_complete){result.action.next_state=0;return result;}
 if(!request.grounded){
  result.action.next_state=43;
  if(character==3||character==12||character==13||character==14||character==15)action.gravity=.5f;
  if(character==13)action.speed*=.5f;
  return result;
 }
 if(character==13){
  unsigned contact=request.contact;
  if(action.phase==0&&action.frame==0){
   action.movement_angle=0;action.moving=action.contact_seen=0;
   saved.held=0;action.speed=30;approach_battle_offset(action.offset,0.f,180.f);
   result.action.clear_contact=result.action.initialize=result.activate=true;
   result.action.contact_capacity=1;result.action.effect=149;contact=0;
  }
  if(action.phase==0&&action.frame==1)
   result.projectile_slot=weapon==0?9:weapon==1?3:7;
  if(contact&2){result.action.next_state=392;result.action.clear_contact=true;return result;}
  if(contact&&!action.contact_seen)action.contact_seen=1;
  if(action.phase<2)approach_battle_offset(action.offset,0.f,7.f);
  if(action.phase==1&&action.frame>0){result.action.next_phase=2;return result;}
  if(action.phase==2){
   ++saved.held;
   if(action.frame>10)action.speed=std::max(0.f,action.speed-6.f);
   if(action.frame==5){result.action.effect=64;result.action.voice=3;result.action.voice_argument=20;}
   if(action.frame==26&&saved.held<10)saved.hold_clock=true;
  }
  return result;
 }
 if(character==15){
  unsigned contact=request.contact;
  if(action.phase==0&&action.frame==0){
   result.activate=result.action.initialize=true;
   action.movement_angle=0;action.moving=0;saved.held=0;action.speed=25;
   approach_battle_offset(action.offset,0.f,180.f);
   result.action.clear_contact=true;contact=0;
  }
  if(contact&2){result.action.next_state=392;result.action.clear_contact=true;return result;}
  if(action.phase<2)approach_battle_offset(action.offset,0.f,20.f);
  if(action.phase==2&&action.frame<5)approach_battle_offset(action.offset,0.f,5.f);
  if(action.phase==2){
   if(action.frame==2||action.frame==8||action.frame==14||action.frame==20||action.frame==30){
    result.action.clear_contact=true;result.action.contact_capacity=1;result.action.effect=62;
   }
   if(action.frame==30)action.speed=35;
   if(action.frame==40)action.speed*=.25f;
   action.speed=std::max(0.f,action.speed-1.f);
   if(action.frame==46&&saved.held<15){++saved.held;saved.hold_clock=true;}
  }
  return result;
 }
 if(character==14){
  if(action.phase==0&&action.frame==0){
   result.activate=result.action.initialize=true;
   action.speed=0;action.movement_angle=0;action.contact_seen=0;saved.held=0;
   result.action.clear_contact=true;result.action.contact_capacity=1;
  }
  if(action.phase==0){
   if(action.frame==15){result.action.effect=61;result.action.voice=33;result.action.voice_argument=20;}
   if(action.frame==22&&saved.held<7){
    if(saved.held%2==0){result.projectile_slot=8;result.projectile_forward=70;result.projectile_height=70;}
    ++saved.held;result.action.frame_override=21;saved.hold_clock=true;return result;
   }
   if(action.frame==23){result.action.next_phase=1;return result;}
   if(action.frame<16)approach_battle_offset(action.offset,0.f,10.f);
   if(action.frame==16)action.speed=35;
  }else if(action.phase==1&&action.frame>0&&action.speed>0){
   action.speed=std::max(0.f,action.speed-2.f);
  }
  return result;
 }
 if(character==12){
  if(action.phase==0&&action.frame==0){
   result.activate=true;result.action.initialize=true;
   if(weapon==1){saved.held=0;saved.burst_ticks=0;}
  }
  if(action.frame==0){
   action.movement_angle=0;action.moving=0;action.speed=15;
   approach_battle_offset(action.offset,0.f,180.f);
   result.action.clear_contact=true;result.action.contact_capacity=1;
  }
  if(action.frame<17)approach_battle_offset(action.offset,0.f,5.f);
  if(action.frame==10)action.speed=0;
  if(weapon==1){
   if(action.frame>=10&&action.frame<19&&++saved.burst_ticks%3==0){
    result.action.clear_contact=true;result.action.effect=155;
    if(action.frame==10){result.action.voice=29;result.action.voice_argument=20;}
   }
   if(action.frame==18&&saved.held<10){++saved.held;saved.hold_clock=true;}
  }else if(action.frame==17){
   result.action.clear_contact=true;result.action.effect=weapon==0?151:205;
   result.action.voice=29;result.action.voice_argument=20;
  }
  return result;
 }
 if(character==3){
  unsigned contact=request.contact;
  if(action.phase==0&&action.frame==0){
   action.movement_angle=0;action.moving=action.contact_seen=0;
   action.speed=30;approach_battle_offset(action.offset,0.f,180.f);saved.held=0;saved.phase2_steer=true;
   result.action.clear_contact=result.action.initialize=result.activate=true;
   result.action.contact_capacity=1;contact=0;
  }
  if(contact&2){result.action.next_state=392;result.action.clear_contact=true;return result;}
  if(action.phase<2)approach_battle_offset(action.offset,0.f,25.f);
  if(action.phase==1){
   ++action.moving;
   if(request.distance_squared<90000.||action.frame>2){result.action.next_phase=2;return result;}
  }
  if(action.phase==2){
   if(action.frame<10&&saved.phase2_steer)approach_battle_offset(action.offset,0.f,15.f);
   if(action.frame==12)result.action.effect=60;
   if(action.frame>10)action.speed=std::max(0.f,action.speed-5.f);
   if(action.frame==24&&saved.held<30){++saved.held;saved.hold_clock=true;}
  }
  return result;
 }
 if(character==7){
  if(action.phase==0&&action.frame==0){
   result.activate=true;
   result.action.voice=33;
   result.action.voice_argument=20;
  }
  if(action.frame<15)approach_battle_offset(action.offset,0.f,10.f);
  if(action.phase==0)action.speed=0;
  if(action.phase==1&&action.frame==15)result.action.effect=154;
  return result;
 }
 if(action.phase==0&&action.frame==0){
  result.activate=true;
  result.action.voice=39;
  result.action.voice_argument=20;
 }
 action.speed=std::max(0.f,action.speed-.5f);
 if(action.phase==1&&action.frame==15)result.action.effect=161;
 return result;
}
inline RosterSpecialStrikeEffects advance_roster_grab_followup(
 KeiichiSpecialStrike& saved,KeiichiAttack300& action,const KeiichiAttack300Input& request){
 RosterSpecialStrikeEffects result;saved.hold_clock=false;
 if(request.animation_complete){result.action.next_state=0;return result;}
 if(action.frame==0){action.speed=action.vertical=0;saved.held=0;action.moving=0;}
 ++action.moving;
 if(action.frame<20)approach_battle_offset(action.offset,0.f,10.f);
 if(action.frame==19){
  if(saved.held<60){++saved.held;saved.hold_clock=true;return result;}
  result.release_requested=true;
 }
 return result;
}
}
