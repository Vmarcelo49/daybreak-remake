#pragma once
#include "character_dispatch.hpp"
#include "keiichi_directional.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace daybreak {

// State 310/311 is not a shared Keiichi animation in the original. These
// profiles come from executing every preview-roster handler in DaybreakDX.exe
// with varied incoming speeds and target distances. The frame schedules below
// are handler events; animation geometry and hit boxes remain DAT driven.
inline float roster_directional_entry_speed(unsigned character,unsigned weapon,unsigned state,float incoming){
 if(state==310){
  switch(character){
   case 3:return std::max(0.f,incoming-1.f);
   case 4:return weapon==2?25.f:15.f;
   case 5:case 9:case 11:case 14:case 15:return 0;
   case 6:case 10:return character==10?incoming:20.f;
   case 7:return weapon==1?17.5f:22.5f;
   case 8:return 22.5f;
   case 12:return 15.f;
   case 13:return 25.f;
  }
 }
 if(state==311){
  switch(character){
   case 3:case 4:case 7:case 10:case 13:case 14:case 15:return 0;
   case 5:return std::max(0.f,incoming-.5f);
   case 6:return weapon==0?14.5f:14.f;
   case 8:return 18.5f;
   case 9:case 11:return 19.5f;
   case 12:return 17.5f;
  }
 }
 return incoming;
}

// The original character handlers gate each attack phase independently.
// Keep the move handler and common animation clock on the same decision.
inline bool roster_directional_airborne_allowed(unsigned character,unsigned state,int phase,int frame){
 if(state==311)return character==14;
 if(state!=310)return false;
 switch(character){
  case 5:return phase==1||phase==2||phase==4;
  case 9:return phase>=1&&phase<=3;
  case 11:return phase==3||phase==4;
  case 15:return phase>0||phase==0&&frame>=5;
  default:return false;
 }
}

// 42d980 -> FLOAT argument to42de80/42dea0 -> PC24 sqrt -> PC24 fdiv.
// Preserve each rounding boundary; a single double sqrt/divide drifts at
// nonintegral approach distances. Existing per-character clamps follow it.
inline float roster_directional_launch_speed(double distance_squared,float divisor){
 volatile float squared=float(distance_squared);
 volatile float root=float(std::sqrt(double(squared)));
 volatile float speed=root/divisor;
 return speed;
}

inline void roster_directional_310_motion(unsigned character,unsigned weapon,KeiichiAttack300& s,double distance_squared,bool grounded){
 const int phase=s.phase,frame=s.frame;
 if(phase==0){
  if(frame==0)return;
  float turn=0;
  switch(character){
   case 3:case 5:turn=2;break;
   case 4:turn=weapon==2?20:15;break;
   case 7:turn=weapon==1?5:15;break;
   case 14:turn=15;break;
   case 6:turn=weapon==0?10:5;break;
   case 10:turn=10;break;
   case 8:turn=8;break;
   case 12:turn=frame<17?5:0;break;
   case 13:turn=20;break;
   case 15:turn=frame<5?5:0;break;
   case 11:turn=distance_squared>=40000.?5:0;break;
  }
  if(turn)approach_battle_offset(s.offset,0,turn);
  if(character==3||character==5)s.speed=std::max(0.f,s.speed-1.f);
  if(character==11&&frame==5)s.speed=30;
  if(character==12&&frame==10)s.speed=0;
  if(character==15){
   if(frame==5){s.speed=std::min(15.f,roster_directional_launch_speed(distance_squared,30.f));s.vertical=35;s.gravity=2.25f;}
   else if(frame>5){if(grounded)s.speed=s.vertical=s.gravity=0;else s.vertical-=s.gravity;}
  }
 }else if(phase==1){
  if(character==12&&frame==0){s.movement_angle=0;s.moving=0;s.contact_seen=0;s.speed=15;approach_battle_offset(s.offset,0,180);}
  else if(character==5&&frame==0){s.movement_angle=0;s.moving=0;s.contact_seen=0;s.speed=30;s.vertical=17.5f;}
  else if(character==9&&frame==0){s.vertical=35;s.gravity=2.25f;}
  float turn=0;
  switch(character){
   case 3:turn=2;break;
   case 5:turn=frame==0||!grounded?2:0;break;
   case 9:turn=frame==0||s.vertical>=6.f?2:0;break;
   case 4:turn=weapon==2?20:15;break;
   case 7:turn=weapon==1?5:15;break;
   case 14:turn=15;break;
   case 6:turn=weapon==0?10:5;break;
   case 8:turn=10;break;
   case 10:turn=3;break;
   case 12:turn=frame<17?5:0;break;
   case 11:turn=distance_squared>=40000.&&frame<8?5:0;break;
   case 13:turn=distance_squared>=40000.?2:0;break;
  }
  if(turn)approach_battle_offset(s.offset,0,turn);
  if(character==3)s.speed=weapon==2?18.f:19.f;
  if(character==5){
   if(s.speed>10)s.speed=std::max(10.f,s.speed-1.f);
   s.vertical-=1.f;
   if(grounded&&s.vertical<0){s.speed=s.vertical=s.gravity=0;}
  }
  if(character==9){
   if(frame==0)s.speed=std::min(12.5f,roster_directional_launch_speed(distance_squared,31.f));
   if(frame==0||s.vertical>=6.f)s.vertical-=s.gravity;
  }
  if(character==10)s.speed=frame<17?23.5f:25.f;
  if(character==12&&frame==10)s.speed=0;
 }else if(phase>=2){
  if(character==12&&frame==0){s.movement_angle=0;s.moving=0;s.contact_seen=0;s.speed=15;approach_battle_offset(s.offset,0,180);}
  float turn=0;
  switch(character){
   case 4:turn=phase==2&&frame<4?10:0;break;
   case 6:turn=phase==2&&frame<8?5:0;break;
   case 8:turn=phase==2&&frame<10?6:0;break;
   case 9:turn=phase<=3?2:0;break;
   case 10:turn=phase==2&&frame<8?3:0;break;
   case 12:turn=frame<17?5:0;break;
   case 14:turn=phase==2?(weapon==0?(frame<10?20:0):(frame<4?10:0)):0;break;
   case 11:turn=phase==3&&frame<2?2:0;break;
  }
  if(turn)approach_battle_offset(s.offset,0,turn);
  switch(character){
   case 3:if(phase==2)s.speed=std::max(0.f,s.speed-1.5f);break;
   case 4:if(phase==2&&frame>=(weapon==2?3:6))s.speed=std::max(0.f,s.speed-(weapon==2?3.f:1.5f));break;
   case 5:if(phase==2){if(grounded)s.speed=0;else if(s.speed>10)s.speed=std::max(10.f,s.speed-1.f);}else s.speed=std::max(0.f,s.speed-1.f);break;
   case 9:if(phase==2&&grounded)s.speed=0;break;
   case 6:if(phase==2)s.speed=std::max(0.f,s.speed-2.f);break;
   case 7:if(phase==2)s.speed=weapon!=1&&frame==15?0.f:std::max(0.f,s.speed-.5f);break;
   case 8:if(phase==2)s.speed=std::max(0.f,s.speed-1.f);break;
   case 10:if(phase==2)s.speed=frame==17?0.f:frame<17?std::max(5.f,s.speed-1.5f):s.speed;
           else if(frame<17)s.speed=std::max(5.f,s.speed-1.5f);break;
   case 12:if(frame==10)s.speed=0;break;
   case 13:if(phase==2&&frame==0)s.speed=0;break;
   case 14:if(phase==2){if(frame==6)s.speed=35;else if(frame>=10)s.speed=std::max(0.f,s.speed-4.f);}break;
   case 11:
    if(phase==3&&frame==0){s.movement_angle=0;s.moving=0;s.contact_seen=0;s.speed=10;s.vertical=17.5f;}
    break;
  }
  if(character==9&&phase<=3){s.vertical-=s.gravity;if(grounded&&s.vertical<0){s.vertical=s.gravity=s.speed=0;}}
  if(character==5&&phase==2){if(grounded)s.vertical=s.gravity=0;else s.vertical-=1.f;}
  if(character==11&&(phase==3||phase==4)){
   s.vertical-=1.f;
   if(grounded&&s.vertical<0)s.speed=s.vertical=s.gravity=0;
  }
 }
}

inline void roster_directional_311_motion(unsigned character,unsigned weapon,KeiichiAttack300& s,double distance_squared){
 const int phase=s.phase,frame=s.frame;
 const bool restart=frame==0&&(phase==0||character==4||character==6||character==7||
  character==8||character==9||character==10||character==11||character==14||character==15);
 if(restart){
  s.movement_angle=0;
  if(character!=13)approach_battle_offset(s.offset,0,180);
  if(character==6||character==7||character==12||character==14)s.moving=0;
  s.speed=roster_directional_entry_speed(character,weapon,311,s.speed);
 }
 // Character 3 uses a persistent update counter, rather than the animation
 // frame, for its forward strike speed and voice.
 if(character==3){
  if(phase==0&&frame==0){s.moving=0;s.speed=0;}
  ++s.moving;
  if(s.moving<15)approach_battle_offset(s.offset,0,12);
  if(s.moving==4)s.speed=weapon==2?16.5f:18.5f;
  if(s.moving>16)s.speed=std::max(0.f,s.speed-1.75f);
  return;
 }
 if(frame==0){
  if(character==13&&(phase==0||phase==1))approach_battle_offset(s.offset,10,15);
  if(character==12&&phase==1&&distance_squared>=62500.){
   approach_battle_offset(s.offset,0,5);s.speed=std::max(15.f,s.speed-.2f);
  }
  if(character==12&&phase==2)s.speed=std::max(0.f,s.speed-1.f);
  if(character==13&&phase==2)s.speed=10;
  if(character==5&&phase==1)s.speed=std::max(0.f,s.speed-1.5f);
  return;
 }
 float turn=0;
 switch(character){
  case 4:turn=frame<20?5:0;break;
  case 5:turn=phase==0&&frame<32?4:0;break;
  case 6:turn=frame<16?(weapon==0?20:17):0;break;
  case 7:turn=frame<9||weapon==1&&frame==9?16:frame<20?10:0;break;
  case 8:turn=phase==0&&frame<13?15:0;break;
  case 9:turn=phase==0&&frame<15?15:0;break;
  case 10:turn=frame<25?10:0;break;
  case 11:turn=phase==0&&frame<11?20:0;break;
  case 12:turn=phase==0||phase==1&&distance_squared>=62500.?5:0;break;
  case 13:turn=phase==0&&frame<15||phase==1&&frame<10?15:0;break;
  case 14:turn=frame<14?(weapon==0?16:10):weapon==0&&frame==14?10:0;break;
  case 15:turn=phase==0&&frame<20?10:0;break;
 }
 if(turn)approach_battle_offset(s.offset,character==13?10.f:0.f,turn);
 switch(character){
  case 4:if(weapon==2){if(frame==5)s.speed=25;else if(frame>=18)s.speed=std::max(0.f,s.speed-5.f);}
          else if(frame==8)s.speed=15;else if(frame>=21)s.speed=std::max(0.f,s.speed-1.5f);break;
  case 5:if(phase==0){if(frame<6)s.speed=std::max(0.f,s.speed-.5f);else if(frame==6)s.speed=20;
          else if(frame>=33)s.speed=std::max(0.f,s.speed-1.5f);}
         else if(phase==1)s.speed=std::max(0.f,s.speed-1.5f);break;
  case 6:if(frame==14)s.speed=weapon==0?25:23.5f;else if(frame==37)s.speed=0;else s.speed=std::max(0.f,s.speed-.5f);break;
  case 7:if((weapon!=1&&frame==9)||frame==12)s.speed=35;
         else if(frame==22)s.speed=10;else if(frame>22)s.speed=std::max(0.f,s.speed-.5f);break;
  case 8:if(frame==25)s.speed=0;break;
  case 9:if(frame==25)s.speed=0;else s.speed=std::max(0.f,s.speed-.5f);break;
  case 10:if(frame==13)s.speed=18.5f;else if(frame>=21)s.speed=std::max(0.f,s.speed-.75f);break;
  case 11:if(frame==38)s.speed=0;else if(phase==0)s.speed=std::max(0.f,s.speed-.5f);break;
  case 12:if(phase==1&&distance_squared>=62500.)s.speed=std::max(15.f,s.speed-.2f);
          else if(phase==2)s.speed=std::max(0.f,s.speed-1.f);break;
  case 13:if(phase==0&&frame==4)s.speed=22.5f;
          else if(phase==2){if(frame==21)s.speed=0;else if(frame>=16)s.speed=std::max(0.f,s.speed-.65f);}break;
  case 14:if(frame==14){s.speed=35;s.vertical=5;}
          else if(frame>=24)s.speed=std::max(0.f,s.speed-1.f);break;
  case 15:if(weapon==0&&frame==10)s.speed=35;else if(weapon==1&&frame==5)s.speed=25;
          else if(frame==18)s.speed=5;else if(frame>=19)s.speed=std::max(0.f,s.speed-1.f);break;
 }
}

inline int roster_directional_phase(unsigned character,unsigned state,const KeiichiAttack300& s,double distance_squared,float incoming_vertical,bool grounded){
 const int phase=s.phase,frame=s.frame;
 if(state==310){
  if(character==11&&phase==0&&distance_squared<40000.)return 2;
  if(phase==1){
   if(character==3)return frame==25?2:-1;
   if(character==5)return grounded&&frame>0&&s.vertical==0?3:-1;
   if(character==9)return frame>0&&incoming_vertical<6.f?2:-1;
   if(character==10&&frame==2)return 2;
   if(character==11&&frame>=8)return 2;
   if(character==14&&frame>=1)return 2;
   if(character==12||character==15)return -1;
   // Ohishi uses75000 (native6A3304), distinct from Irie's90000 (6A2900).
   unsigned reach=character==8?75000:character==10?90000:40000;
   return distance_squared<double(reach)?2:-1;
  }
  if(phase==2){if(character==5&&grounded)return 3;if(character==9&&grounded&&s.vertical==0)return 4;}
  if(character==9&&phase==3&&grounded&&s.vertical==0)return 4;
  if(character==11&&(phase==3||phase==4)&&grounded&&s.vertical==0)return 5;
 }else if(state==311&&phase==1){
  if(character==12&&distance_squared<62500.)return 2;
  if(character==13&&frame>=11&&distance_squared<40000.)return 2;
 }
 return -1;
}

inline void roster_directional_events(unsigned character,unsigned weapon,unsigned state,const KeiichiAttack300& s,KeiichiAttack300Effects& out){
 const int phase=s.phase,frame=s.frame;
 if(frame==0){
  if(state==310){
   if(phase==0){out.initialize=out.clear_contact=true;out.contact_capacity=character==15&&weapon==1?3:1;}
   if(character==5&&phase==1||character==12&&phase!=0){out.clear_contact=true;out.contact_capacity=1;}
  }else if(state==311){
   if(phase==0||character==4||character==14){out.initialize=true;out.attack_statistics_count=character==5?4:1;}
   if(phase==0||character==4||character==6||character==7||character==8||character==9||
      character==10||character==11||character==14||character==15){
    out.clear_contact=true;out.contact_capacity=character==5&&phase==0?4:1;
   }
  }
 }
 auto cue=[&](int at,int effect,int voice){if(frame==at){out.effect=effect;out.voice=voice;out.voice_argument=10;}};
 if(state==310){
  switch(character){
   case 3:if(phase==1){cue(0,62,3);if(frame==15)out.contact_capacity=0;}break;
   case 4:if(phase==2){cue(2,62,3);out.strike=frame>=2&&frame<=10;}break;
   case 5:if(phase==1)cue(0,62,3);break;
   case 6:if(phase==2)cue(8,62,2);break;
   case 7:if(phase==2)cue(7,60,2);break;
   case 8:if(phase==2)cue(4,62,2);break;
   case 9:if(phase==1&&frame==0){out.voice=1;out.voice_argument=10;}
          if(phase==4){cue(4,62,3);if(frame==4){out.secondary_effect=168;out.spawned_states={{300,310}};}}break;
   case 10:if(phase==2)cue(10,62,2);break;
   case 11:if(phase==3){
            if(frame==0){out.clear_contact=true;out.contact_capacity=1;out.effect=62;}
            if(frame==2)cue(2,62,3);
           }break;
   case 12:if(frame==17){cue(17,151,28);out.clear_contact=true;out.contact_capacity=1;}break;
   case 13:if(phase==2)cue(2,62,3);break;
   case 14:if(phase==2)cue(9,62,3);break;
   case 15:if(phase==0){cue(20,62,3);out.strike=frame>=21&&frame<=25;}
           else if(weapon==1)out.strike=frame>=12&&frame<=16;
           break;
  }
 }else if(state==311){
  switch(character){
   case 3:if(s.moving==10){out.effect=62;out.voice=2;out.voice_argument=10;}break;
   case 4:cue(weapon==2?5:13,62,weapon==2?3:2);
          out.strike=weapon==2?frame>=6&&frame<=19:frame>=14&&frame<=23;break;
   case 5:if(phase==0){
            if(frame==6){out.voice=3;out.voice_argument=10;}
            if(frame==10||frame==15||frame==20){out.effect=62;out.clear_contact=true;}
            out.strike=frame>=11&&frame<=19;
           }break;
   case 6:cue(16,62,3);break;
   case 7:if(weapon!=1)cue(9,60,2);if(frame==12)cue(12,60,2);break;
   case 8:cue(13,62,3);break;
   case 9:cue(12,62,2);break;
   case 10:cue(13,63,2);break;
   case 11:cue(11,62,2);break;
   case 12:if(phase==2)cue(6,62,2);break;
   case 13:if(phase==2)cue(13,62,2);break;
   case 14:cue(13,62,2);break;
   case 15:cue(12,62,3);out.strike=weapon==0&&frame>=12&&frame<=16;break;
  }
 }
}

inline KeiichiAttack300Effects advance_roster_directional_melee(unsigned character,unsigned weapon,unsigned state,
 KeiichiAttack300& s,const KeiichiDirectionalInput& in){
 character_action_dispatch(character,weapon);
 if(state!=310&&state!=311)throw std::invalid_argument("Unsupported roster directional melee");
 KeiichiAttack300Effects out;
 if(in.complete){out.next_state=0;return out;}
 const bool airborne_allowed=roster_directional_airborne_allowed(character,state,s.phase,s.frame);
 if(!in.grounded&&!airborne_allowed){
  if(state==310&&(character==11||character==15)||state==311&&(character==7||character==15))
   s.speed=std::min(s.speed,10.f);
  if(character==15&&!(state==310&&weapon==1))s.vertical=0;
  out.next_state=43;return out;
 }
 const float incoming_vertical=s.vertical;
 if(state==310){
  if(character==11&&(s.phase==3||s.phase==4)&&in.grounded&&s.vertical<1.f&&s.frame!=0){
   s.speed=s.vertical=s.gravity=0;out.next_phase=5;return out;
  }
  if(character==11&&s.phase==4&&in.grounded&&s.vertical<1.f){
   s.speed=s.vertical=s.gravity=0;out.next_phase=5;return out;
  }
  if(s.phase==0&&s.frame==0){
   s.movement_angle=0;s.moving=s.contact_seen=0;
   approach_battle_offset(s.offset,0,180);
   s.speed=roster_directional_entry_speed(character,weapon,state,s.speed);
  }
  roster_directional_310_motion(character,weapon,s,in.distance_squared,in.grounded);
 }else{
  if(character==14&&!in.grounded)s.vertical-=.5f;
  roster_directional_311_motion(character,weapon,s,in.distance_squared);
  if(character==14&&!in.grounded&&s.frame==14)s.speed=std::max(0.f,s.speed-1.5f);
 }
 roster_directional_events(character,weapon,state,s,out);
 out.next_phase=roster_directional_phase(character,state,s,in.distance_squared,incoming_vertical,in.grounded);
 if(state==310&&character==15&&weapon==1&&!in.grounded&&s.phase==0)
  out.strike=out.strike||(s.frame>=12&&s.frame<=16);
 if(state==310&&character==5&&s.phase==1&&s.frame==2&&out.next_phase<0)out.effect=62;
 if(state==310&&character==9&&s.phase==1&&out.next_phase==2)s.speed=0;
 if(state==310&&character==15&&s.phase==0&&s.frame>=6&&in.grounded)out.next_state=329;
 if(state==311&&character==5&&s.phase==1&&s.frame>=11)out.next_state=0;
 if(in.contact&2){out.next_state=392;out.clear_contact=true;}
 return out;
}

} // namespace daybreak
