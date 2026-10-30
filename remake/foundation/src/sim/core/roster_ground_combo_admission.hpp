#pragma once

namespace daybreak {

// Original slot-7 handlers only expose 301->302 on these bindings. A DAT
// animation for 302 by itself does not imply that the input route exists.
inline bool roster_ground_combo_has_second(unsigned character,unsigned weapon){
 switch(character){
 case 2: case 5: case 9: case 11: case 13: return true;
 case 4: return weapon==2;
 case 15: return weapon<2;
 default: return false;
 }
}

// Original slot-7 handlers expose 340->341 only for this landing-combo
// family. Several other DATs contain state341 for different entry paths.
inline bool roster_landing_combo_has_second(unsigned character,unsigned weapon){
 switch(character){
 case 2: case 3: case 5: case 6: case 9: case 11: case 12: case 13: return true;
 case 4:return weapon==2;
 case 15:return weapon<2;
 default:return false;
 }
}

// Grounded ordinary melee admission shared by the recovered actor and the
// preview roster. Original direction checks precede the combo checks; when
// a directional priority fails, a held direction may still enter 301/302.
template<class FirstPriority>
int roster_ground_combo_admission(unsigned character,unsigned weapon,unsigned current,
 bool grounded,unsigned held,unsigned released,int x,int z,unsigned flags,
 int current_priority,FirstPriority first_priority){
 if(!grounded||!(flags&0x100)||!(held==3||(released>0&&released<3)))return -1;
 if(character==12){
  if(z<0&&current_priority<=first_priority(311))return 311;
  if(x&&current_priority<=first_priority(310))return 310;
 }else{
  if(z<0&&current_priority<=first_priority(310))return 310;
  if(x&&current_priority<=first_priority(311))return 311;
  if((character==5||character==11)&&z>0&&current_priority<=first_priority(312))return 312;
 }
 if(current==300&&current_priority<=first_priority(301))return 301;
 if(current==301&&roster_ground_combo_has_second(character,weapon)&&
    current_priority<=first_priority(302))return 302;
 if(current==340&&roster_landing_combo_has_second(character,weapon)&&
    current_priority<=first_priority(341))return 341;
 // The original ordinary-300 fallback also admits an input from 301 when
 // that character has no second combo stage (or its priority check fails).
 if((current==300||current==301||current==0||current==10||current==27)&&
    current_priority<=first_priority(300))return 300;
 return -1;
}

}
