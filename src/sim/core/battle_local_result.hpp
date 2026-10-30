#pragma once
#include "battle_actor_resource.hpp"
#include "battle_presentation_input.hpp"
#include <array>
#include "battle_random.hpp"
namespace daybreak {
// 635d40 local case2 timeout/defeat scan and case3 main countdown.
// Camera, sound and result-screen animation remain external.
struct BattleLocalResult {
 unsigned primary_actor=0;
 bool shared_confirmation=false;
 bool story_mode=false,story_horizontal_press=false,retry_requested=false;
 unsigned story_choice=0;int story_sound=-1;
 std::array<unsigned,4> previous_buttons{};bool exit_requested=false;
 std::array<unsigned,4> input_edges(const std::array<unsigned,4>& buttons){auto edges=buttons;for(unsigned i=0;i<4;++i){edges[i]=battle_presentation_button_edges(buttons[i],previous_buttons[i]);previous_buttons[i]=buttons[i];}return edges;}
 //636a94..636b3f: controller order, then physical button order; no early break.
 void confirm_statistics(const std::array<unsigned,4>& presses){
  for(unsigned c=0;c<4;++c)if(shared_confirmation||c==primary_actor)
   for(unsigned b=0;b<7;++b)if(presses[c]&(1u<<b)){
    if(presentation_offset<150)presentation_offset=150;else exit_requested=true;
   }
 }
 bool finishes_with_inputs(const std::array<unsigned,4>& buttons)const{
  if(!ready||presentation_phase!=5)return false;
  auto next=*this;++next.presentation_offset;next.confirm_statistics(next.input_edges(buttons));return next.exit_requested;
 }
 bool timed=false,timed_out=false;unsigned remaining_ticks=0;
 void configure_time_limit(unsigned ticks){timed=true;remaining_ticks=ticks;}
 unsigned presentation_phase=0,presentation_offset=1056;
 int winner=-1;unsigned focus=0,countdown=0;bool ready=false;
 void advance(const std::array<unsigned,2>& limits,const std::array<unsigned,2>& used,const std::array<bool,4>& defeated,const std::array<unsigned,4>& presses={}){
  story_sound=-1;
  if(winner>=0){
   if(ready){
    // 635d40 case4/substate0 then1: check before subtracting 8 or16.
    if(presentation_phase==0){if(damage_signed(presentation_offset)<1){presentation_phase=story_mode?2:1;presentation_offset=512;}else presentation_offset-=8;}
    else if(story_mode&&presentation_phase==2){
     if(damage_signed(presentation_offset)>0)presentation_offset-=16;
     else if(presses[0]&1u){presentation_phase=3;presentation_offset=255;}
    }else if(story_mode&&presentation_phase==3){
     if(!exit_requested){
      if(damage_signed(presentation_offset)>0)presentation_offset-=5;
      // 636746: only a fresh horizontal axis count (+/-1); direction precedes B0.
      if(story_horizontal_press){story_choice=1-story_choice;story_sound=2;}
      else if(presses[0]&1u){story_sound=0;if(story_choice)exit_requested=true;else{presentation_phase=4;presentation_offset=255;}}
     }
    }else if(story_mode&&presentation_phase==4){
     if(damage_signed(presentation_offset)<1){presentation_offset=0;retry_requested=true;}
     else presentation_offset-=5;
    }
    else if(presentation_phase==1){
     if(presentation_offset)presentation_offset-=16;
     else {for(auto pressed:presses)if(pressed&battle_result_confirmation_buttons){presentation_phase=5;presentation_offset=0;break;}}
    }else if(presentation_phase==5){
     ++presentation_offset;
     confirm_statistics(presses);
    }
   }else {if(countdown)--countdown;if(!countdown){
    // 635d40 story victory skips portraits/statistics and returns to dialogue.
    if(story_mode&&winner==0){countdown=1;exit_requested=true;}
    else {ready=true;presentation_phase=0;presentation_offset=1056;}
   }}
   return;
  }
  for(unsigned i=0;i<4;++i)if(defeated[i]&&remaining_battle_resource(limits[i/2],used[i/2])<=0){
   winner=i<2?1:0;focus=i;if(!countdown)countdown=180;
  }
 }
 void advance(const std::array<unsigned,2>& limits,const std::array<unsigned,2>& used,const std::array<bool,4>& defeated,const std::array<unsigned,4>& health,BattleRandom& random,const std::array<unsigned,4>& presses={}){
  if(winner<0&&timed){
   // Original checks zero before decrement and resolves timeout before defeat events.
   if(!remaining_ticks){
    const auto left=damage_signed(used[0]),right=damage_signed(used[1]);
    const auto hp0=damage_signed(health[0]+health[1]),hp1=damage_signed(health[2]+health[3]);
    winner=left<right?0:right<left?1:hp0>hp1?0:hp1>hp0?1:int(random.next()%2);
    focus=unsigned(winner)*2;countdown=180;timed_out=true;return;
   }
   --remaining_ticks;
  }
  advance(limits,used,defeated,presses);
 }
};
}
