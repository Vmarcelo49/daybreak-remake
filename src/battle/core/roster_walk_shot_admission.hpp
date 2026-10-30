#pragma once
#include <stdexcept>

namespace daybreak {

// Original slot-7 walking (state 10) short-release branches for the 37
// generic character/weapon bindings. The gate is the animation-priority row
// actually compared by the original handler, which may differ from the shot
// animation it selects. A failed 401 gate falls through to ordinary 400.
template<class FirstPriority>
int roster_walk_shot_admission(unsigned character,unsigned weapon,int z,float offset,
                               int current_priority,FirstPriority first_priority){
 if((character>0&&character<3)||character>=16||weapon>2||(character>=14&&weapon>1))
  throw std::invalid_argument("Unsupported walking-shot binding");
 //All three Rena slot7 handlers compare401.a without a direction test.
 //Weapons0/1 select401; weapon2 selects400 even through that gate.
 if(character==0){
  if(weapon<2&&current_priority<=first_priority(401))return 401;
  return current_priority<=first_priority(400)?400:-1;
 }
 int shot=400;unsigned gate=400;
 const bool angle_shot=(character==4&&weapon==0)||(character==5&&weapon==0)||
  (character==7&&weapon==0)||character==10||character==14;
 if(angle_shot&&offset>=-100.f&&offset<=100.f)
  shot=offset>=40.f?412:offset<=-40.f?411:410;
 else if(character==6&&weapon==2&&offset>=-100.f&&offset<=100.f)shot=410;
 else if(((character==3||character==9)&&weapon!=(character==9?2u:1u))||
         (character==7&&weapon==2&&offset>=-100.f&&offset<=100.f)||
         character==15||(character==13&&weapon==0&&z<0))shot=401;
 if((character==5&&weapon==2)||(character==6&&weapon==1)||
    (character==13&&weapon==2&&z<0))gate=0;
 else if((character==3&&weapon!=1)||(character==5&&weapon==0)||
         (character==6&&weapon==2)||(character==7&&(weapon==0||weapon==2))||
         (character==9&&weapon!=2)||character==15||(character==13&&weapon==0&&z<0))gate=401;
 if(gate&&current_priority>first_priority(gate))return gate==401?400:-1;
 return shot;
}

}
