#pragma once
#include <array>
#include <stdexcept>

namespace daybreak {

struct RosterGroundShotAdmission {int state;unsigned priority_state;};

// Original slot-7 short-release handlers, sampled for every preview-roster
// character/weapon pair and all nine directions in states 20/23/24/27.
// A state of -1 means the original handler consumes the shot input without
// changing action (the neutral forward-dash branch).
inline RosterGroundShotAdmission roster_ground_shot_admission(unsigned character,unsigned weapon,
                                                             unsigned current,int x,int z){
 if((character>0&&character<3)||character>=16||weapon>2||(character>=14&&weapon>1))
  throw std::invalid_argument("Unsupported roster short-shot binding");
 if(current!=20&&current!=23&&current!=24&&current!=27)
  throw std::invalid_argument("Unsupported roster short-shot source state");
 //445ee0/44d850/43ded0 compare the same moving gates, but the shovel
 //always requests400; the iron cleaver requests401 for all four sources.
 if(character==0){
  const unsigned gate=current==20?402u:current==23?405u:406u;
  return {weapon==2?400:weapon==1||current==20?401:current==23?405:current==24?406:407,gate};
 }
 constexpr std::array<std::array<unsigned char,3>,16> groups{{
  {{0,0,0}},{{0,0,0}},{{0,0,0}},{{1,2,1}},{{3,3,3}},{{3,4,4}},{{3,4,3}},{{5,6,5}},
  {{7,4,4}},{{7,7,4}},{{5,5,5}},{{3,7,3}},{{5,5,8}},{{3,4,4}},{{3,3,0}},{{9,9,0}}
 }};
 const auto group=groups[character][weapon];
 if(!group)throw std::logic_error("Missing original short-shot policy");
 constexpr std::array<std::array<unsigned short,3>,16> forward_gates{{
  {{0,0,0}},{{0,0,0}},{{0,0,0}},{{402,402,402}},{{404,404,404}},{{404,402,404}},{{404,404,404}},{{404,404,404}},
  {{401,400,400}},{{402,402,400}},{{404,404,404}},{{404,401,404}},{{404,404,404}},{{404,404,404}},{{404,404,0}},{{402,402,0}}
 }};
 const bool plain_guard=(character==8&&weapon!=0)||(character==9&&weapon==2);
 const bool uniform_401=(character==8&&weapon==0)||(character==11&&weapon==1);
 unsigned gate=current==20?forward_gates[character][weapon]:plain_guard?400u:uniform_401?401u:current==23?405u:406u;
 if(current==27&&((character==6&&weapon==2)||(character==12&&weapon==1)))gate=407;
 if(current==27&&character==15&&weapon==0)gate=401;
 if(current==20){
  switch(group){
   case 1:case 7:case 9:return {401,gate};
   case 2:case 4:return {400,gate};
   case 3:return {404,gate};
   case 5:return {z?404:x<0?406:x>0?405:-1,gate};
   case 6:return {z<0?404:(x||z)?401:-1,gate};
   case 8:return {x||z?401:-1,gate};
  }
 }
 if(group==4)return {400,gate};
 if(group==6||group==7||group==8)return {401,gate};
 if(group==9&&current==27)return {401,gate};
 return {current==23?405:current==24?406:407,gate};
}

}
