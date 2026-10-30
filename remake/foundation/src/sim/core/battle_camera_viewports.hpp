#pragma once
#include "local_battle_roster.hpp"
namespace daybreak {
struct BattleCameraViewport {
 int actor=-1,left=0,top=0,right=0,bottom=0;
 bool active=false;
};
struct BattleCameraViewports {
 std::array<BattleCameraViewport,4> slots{};
 unsigned count=0;
 bool fullscreen=false,clear_background=false;
};
//396f0 layout branch. phase is scene+4a3c, actors are+4424/+4428.
// Actor-disabled bytes correspond to+860. The caller supplies original state;
// zero/unknown modes retain the original empty-layout outcome.
inline BattleCameraViewports battle_camera_viewports(const LocalBattleRoster& roster,
 unsigned phase=0,int phase3_actor=0,int phase45_actor=0,
 const std::array<bool,4>& disabled={}){
 BattleCameraViewports out;
 if(roster.spectating&&phase==0){out.count=1;out.fullscreen=true;out.slots[0]={int(roster.spectator_actor),0,0,800,600,true};return out;}
 if(phase==3||phase==4||phase==5){
  out.count=1;out.fullscreen=true;out.slots[0]={phase==3?phase3_actor:phase45_actor,0,0,800,600,true};return out;
 }
 const unsigned count=roster.controlled_count;
 if(count==1){out.count=1;out.fullscreen=true;out.slots[0]={int(roster.controlled_slots[0]),0,0,800,600,true};}
 else if(count==2){
  out.count=2;out.clear_background=true;
  out.slots={BattleCameraViewport{int(roster.controlled_slots[0]),0,0,400,300,true},
             BattleCameraViewport{int(roster.controlled_slots[1]),400,300,800,600,true},
             BattleCameraViewport{-1,400,0,800,300,false},BattleCameraViewport{-1,0,300,400,600,false}};
 }else if(count==3||count==4){
  out.count=4;out.clear_background=count==3;
  for(unsigned i=0;i<4;++i){
   const bool active=count==4||(!disabled[i]&&roster.owner[i]<4);
   const int x=i<2?0:400,y=(i%2)*300;
   out.slots[i]={active?int(i):-1,x,y,x+400,y+300,active};
  }
 }
 return out;
}
}
