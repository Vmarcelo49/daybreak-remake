#pragma once
#include "battle_target_selection.hpp"
#include "battle_event_feedback.hpp"
#include <cstdint>
namespace daybreak {
//4201a0 owns these clocks for ALL actors, including actors frozen by828.
// Strict entry (> -6), inclusive completion (<= -6); command completion setsAEC4.
inline bool advance_battle_command_emphasis(float& value){
 if(!(value>-6.f))return false;
 value-=.2f;return value<=-6.f;
}
inline void advance_battle_target_cooldown(BattleTargetSelection& target){
 if(target.cooldown>0)--target.cooldown;
}
template<class Voice> inline void consume_battle_command_notice(unsigned actor,int command,std::uint8_t& notice,Voice voice){
 if(notice!=1)return;
 voice(BattleEventVoiceRequest{actor,34,50,command,-1,0x422730,0,int(actor)});notice=0;
}
//41ffcd..420193: acquired298==1 chooses CPU orders or online HUMAN HP report.
template<class Voice> inline void advance_battle_ally_command(unsigned actor,unsigned ally,unsigned age,bool ally_cpu,bool network,
 std::int32_t health,int& command,int& ally_command,float& emphasis,Voice voice){
 if(age!=1)return;
 if(ally_cpu){if(command>=0){command=(command+1)%6;ally_command=command;emphasis=2.f;}return;}
 if(!network)return;
 const int choice=health<2500?3:health<5000?2:health<7500?1:0;
 voice(BattleEventVoiceRequest{actor,14,25,choice,-1,0x422730,1,int(ally)});
 voice(BattleEventVoiceRequest{actor,14,15,choice,-1,0x422730,0,int(actor)});
}
template<class Notify> inline int battle_incoming_warning(unsigned actor,unsigned opponent,unsigned incoming_target,bool activated,unsigned current_target,Notify notify){
 if(incoming_target!=actor)return 0;
 if(!activated)return 1;
 if(opponent!=current_target)notify(actor,16);
 return 2;
}
}
