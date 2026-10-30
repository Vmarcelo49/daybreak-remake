#pragma once
#include "battle_events.hpp"
#include <array>
#include <vector>
namespace daybreak {
struct BattleEventVoiceRequest {
 unsigned actor=0,category=0,priority=10;int choice=-1,bank=-1;unsigned source=0,option=0;
 int recipient=-1; //422560/730 recipient is distinct from ECX speaker/voice bank.
 int selected_choice=-1;bool selection_resolved=false; //original call choice remains intact.
};
template<std::size_t N> bool battle_event_voice_audible(const BattleEventVoiceRequest& request,const std::array<unsigned,N>& controlled,unsigned count){
 if(request.recipient<0)return true;
 for(unsigned i=0;i<count&&i<N;++i)if(controlled[i]==unsigned(request.recipient))return true;
 return false;
}
// Slot9:45 wrappers call428250; Akasaka0 calls4e6970 (self HP warning).
struct BattleEventFeedback {
 unsigned actor=0,ally=0;std::int32_t target_resource=0;bool self_warning=false;
 unsigned query_calls=0,ally_calls=0;std::vector<BattleEventVoiceRequest> voices;
 void paired_event(unsigned category,int choice,unsigned ally_priority,unsigned own_priority,unsigned option){
  if(self_warning)voices.push_back({actor,category,own_priority,choice,-1,0x422490,option});
  else{
   ++ally_calls;voices.push_back({actor,category,ally_priority,choice,-1,0x422730,option,int(ally)});
   voices.push_back({actor,category,own_priority,choice,-1,0x422730,option,int(actor)});
  }
 }
 std::int32_t query(){++query_calls;return target_resource;} // [actor+308]->421930
 void event(unsigned source,unsigned category,unsigned priority,unsigned option){voices.push_back({actor,category,priority,-1,-1,source,option});}
};
inline BattleEventFeedback advance_battle_event_feedback(BattleEventState& state,unsigned actor,unsigned ally,std::int32_t target_resource,bool self_warning){
 BattleEventFeedback feedback;feedback.actor=actor;feedback.ally=ally;feedback.target_resource=target_resource;feedback.self_warning=self_warning;
 update_battle_events(state,feedback);return feedback;
}
}
