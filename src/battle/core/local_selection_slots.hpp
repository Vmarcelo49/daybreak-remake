#pragma once
#include "local_selection_navigation.hpp"
#include "local_character_cursor.hpp"
#include "battle_random.hpp"
#include <vector>
namespace daybreak {
inline void local_selection_sound(std::vector<unsigned>* effects,unsigned id){if(effects)effects->push_back(id);}
inline constexpr std::array<unsigned,16> local_option_counts{{5,5,3,5,5,5,2,4,2,2,3,3,1,2,4,5}}; // 6b7290
// 409340 local selection state transitions. Rendering/audio are caller responsibilities.
struct LocalSelectionSlots {
 LocalSelectionNavigation navigation;
 std::array<int,4> editor{{-1,-1,-1,-1}},owner{{-1,-1,-1,-1}},assignment{{-1,-1,-1,-1}};
 std::array<int,4> character{{-1,-1,-1,-1}},weapon{{-1,-1,-1,-1}},costume{{-1,-1,-1,-1}};
 std::array<unsigned,4> phase{},option{};
 std::array<int,4> choice{};
 std::array<bool,4> flag3cb0{};std::array<unsigned char,4> flag3cd4{};
 std::array<float,4> preview_x{},preview_y{},confirmation_scale{};
 bool menu_requested=false,exit_requested=false;
 // 409340 applies horizontal model-variant input after the phase transition.
 // Exact +/-1 duration only; special-mode choice (legacy costume) is independent.
 void update_variant(unsigned controller,int horizontal){
  const auto mode=phase.at(controller);
  if(mode!=1&&mode!=3&&mode!=4)return;
  const int slot=navigation.actor_slot(controller);
  if(slot<0||slot>=4||character[slot]<0||character[slot]>=16)return;
  const unsigned count=local_option_counts[character[slot]];
  if(horizontal==1)option[slot]=(option[slot]+1)%count;
  else if(horizontal==-1)option[slot]=(option[slot]+count-1)%count;
 }

 enum class Event {none,menu,exit,cleared,edit,weapon,costume,cancelled,ownership,committed,released};
 // Raw input duration counters: vertical=local_c[1], cycle=[4], modifier=[5].
 // Modifier with either action held suppresses phases 1/3/4, including movement.
 Event update_options(unsigned controller,int vertical,unsigned confirm,unsigned cancel,
                      unsigned cycle=0,unsigned modifier=0,std::vector<unsigned>* sounds=nullptr){
  const auto state=phase.at(controller);
  if(state!=1&&state!=3&&state!=4&&state!=8)return Event::none;
  const auto slot=unsigned(navigation.actor_slot(controller));
  if(state==8){
   if(confirmation_scale.at(slot)<=1.f){local_selection_sound(sounds,3);phase[controller]=0;editor[slot]=-1;return Event::released;}
   confirmation_scale[slot]-=.2f;return Event::none;
  }
  if(modifier&&(confirm||cancel))return Event::none;
  if(state==1){
   if((vertical==1||vertical==-1)&&assignment[controller]<0){local_selection_sound(sounds,2);choice[slot]=(choice[slot]+2+vertical)%2;}
   if(confirm==1){
    local_selection_sound(sounds,0);
    flag3cd4[slot]=false;
    if(choice[slot]==0){assignment[controller]=int(slot);owner[slot]=int(controller);}
    else owner[slot]=4;
    phase[controller]=8;confirmation_scale[slot]=4.f;flag3cb0[slot]=true;
    // Local entry voice: 649770(character), suffix B only for characters 0/4 weapon 2.
    return Event::committed;
   }
   if(cancel==1){
    local_selection_sound(sounds,1);
    if(assignment[controller]==int(slot))assignment[controller]=-1;
    phase[controller]=4;choice[slot]=costume[slot];owner[slot]=-1;return Event::costume;
   }
   return Event::none;
  }
  const int count=state==3&&character[slot]>=14?2:3;
  if(cycle)choice[slot]=(choice[slot]+1)%count;
  if(vertical==1||vertical==-1){local_selection_sound(sounds,2);choice[slot]=(choice[slot]+count+vertical)%count;}
  if(state==3){
   weapon[slot]=choice[slot];
   if(confirm==1){local_selection_sound(sounds,0);phase[controller]=4;choice[slot]=0;return Event::costume;}
   if(cancel==1){local_selection_sound(sounds,1);weapon[slot]=-1;phase[controller]=2;choice[slot]=character[slot];character[slot]=-1;option[slot]=0;return Event::edit;}
  }else{
   costume[slot]=choice[slot];
   if(confirm==1){
    local_selection_sound(sounds,0);
    phase[controller]=1;
    if(assignment[controller]==int(slot)){assignment[controller]=-1;choice[slot]=0;}
    else choice[slot]=assignment[controller]>=0?1:0;
    return Event::ownership;
   }
   if(cancel==1){local_selection_sound(sounds,1);phase[controller]=3;costume[slot]=-1;choice[slot]=weapon[slot];return Event::weapon;}
  }
  return Event::none;
 }
 Event update_character(unsigned controller,int horizontal,int vertical,unsigned confirm,unsigned cancel,BattleRandom& random,std::vector<unsigned>* sounds=nullptr){
  if(phase.at(controller)!=2)return Event::none;
  const auto slot=unsigned(navigation.actor_slot(controller));
  const int previous=choice.at(slot);
  character.at(slot)=choice.at(slot)=move_character_cursor(preview_x.at(slot),preview_y.at(slot),previous,horizontal,vertical);
  if(choice[slot]>=0&&choice[slot]!=previous)local_selection_sound(sounds,2);
  if(confirm==1){
   local_selection_sound(sounds,0);
   if(character[slot]<0){character[slot]=int(random.next()%16);weapon[slot]=int(random.next()%(character[slot]<14?3:2));phase[controller]=4;}
   else phase[controller]=3;
   option[slot]=0;choice[slot]=0;
   // Caller loads data/select/wNN.bmp at this point (40d700).
   return phase[controller]==3?Event::weapon:Event::costume;
  }
  if(cancel==1){
   local_selection_sound(sounds,1);
   option[slot]=0;if(assignment[controller]==int(slot))assignment[controller]=-1;
   phase[controller]=0;editor[slot]=owner[slot]=character[slot]=-1;return Event::cancelled;
  }
  return Event::none;
 }
 Event update(unsigned controller,int horizontal,int vertical,unsigned confirm,unsigned cancel,std::vector<unsigned>* sounds=nullptr){
  if(phase.at(controller))return Event::none;
  const bool inactive=navigation.cursor.at(controller)<0;
  navigation.update(controller,horizontal,vertical,confirm);
  if(inactive)return Event::none;
  if(horizontal==1||horizontal==-1||vertical==1||vertical==-1)local_selection_sound(sounds,2);
  const int cell=navigation.cursor[controller];
  if(cell==2||cell==5){
   if(confirm!=1)return Event::none;
   if(cell==5){local_selection_sound(sounds,1);exit_requested=true;return Event::exit;}
   for(auto p:phase)if(p)return Event::none;
   local_selection_sound(sounds,0);
   choice[0]=0;menu_requested=true;return Event::menu;
  }
  const auto slot=unsigned(navigation.actor_slot(controller));
  if(cancel==1&&editor[slot]<0&&(owner[slot]==int(controller)||owner[slot]==4)){
   character[slot]=-1;if(owner[slot]==int(controller))assignment[controller]=-1;
   owner[slot]=weapon[slot]=costume[slot]=-1;option[slot]=0;flag3cb0[slot]=flag3cd4[slot]=false;
   return Event::cleared;
  }
  if(confirm==1&&editor[slot]<0&&owner[slot]<0){
   local_selection_sound(sounds,0);
   editor[slot]=int(controller);phase[controller]=2;choice[slot]=option[slot]=0;
   flag3cb0[slot]=flag3cd4[slot]=false;
   // 6b71d0[0]*48 and6b7210[0]*36 after choice reset.
   preview_x[slot]=0;preview_y[slot]=216;return Event::edit;
  }
  return Event::none;
 }
};
}
