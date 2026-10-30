#pragma once
#include "battle_event_feedback.hpp"
#include "battle_random.hpp"
namespace daybreak {
// Resolve at the actor call, before later combat draws and before audio admission.
// Modern network worlds use canonical HUMAN ownership, never the local camera mask.
inline void resolve_battle_voice_selection(BattleEventVoiceRequest& request,unsigned bank,
 unsigned count,BattleRandom& random,unsigned human_mask=15){
 request.bank=int(bank);request.selection_resolved=true;request.selected_choice=-1;
 if((request.source==0x422560||request.source==0x422730)&&
    (request.recipient<0||request.recipient>=4||!(human_mask&(1u<<unsigned(request.recipient)))))return;
 if(!count)return;
 const bool specific=request.source==0x422300||request.source==0x422490||request.source==0x422730||
  (request.source==0&&request.choice>=0);
 if(specific){if(request.choice>=0&&unsigned(request.choice)<count)request.selected_choice=request.choice;}
 else request.selected_choice=int(random.next()%count);
}
}
