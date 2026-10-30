#pragma once
#include "battle_startup.hpp"
#include "battle_local_result.hpp"
namespace daybreak {
//634f60 gates acquisition-time input;635d40 can change phase before contacts.
inline unsigned battle_scene_phase(const BattleStartup& startup,const BattleLocalResult& result){
 if(startup.warming_up())return 1;
 if(result.winner<0)return 2;
 if(!result.ready)return 3;
 return result.story_mode||result.presentation_phase==5?5:4;
}
struct BattlePhaseAdmission {
 unsigned phase=2,focus=0;
 bool blocks_commands(unsigned actor)const{return phase==1||phase==4||phase==5||(phase==3&&actor!=focus);}
 template<class Input> Input gate(Input input,unsigned actor,bool cpu)const{
  if(phase==1)return battle_startup_input(input,cpu);
  if(blocks_commands(actor)){input.buttons=0;input.x=input.z=0;}return input;
 }
};
struct BattlePhaseNotices {
 float main_scale=1,secondary_scale=1;std::int32_t secondary_ticks=0;
 static void decay(float& value){if(value>1)value-=.5f;if(value<1)value=1;}
 void begin_finish(){main_scale=8;}
 //Called only for phase3 selected before635d40, after main countdown decrements.
 bool advance_finish(unsigned remaining){
  if(secondary_ticks>0)--secondary_ticks;decay(main_scale);decay(secondary_scale);
  if(remaining==120){secondary_ticks=120;secondary_scale=8;return true;}return false;
 }
};

}
