#pragma once
#include "roster_shot401.hpp"

namespace daybreak {

struct RosterShot401Clock {unsigned frame10_visits=0;};
// 527880/5b9680 emit auxiliary bullet2 from socket0 BEFORE 4230e0,
// followed by the primary bullet from the same socket. The effect/voice
// payloads below are replaced by the actor-specific aggregate values.
inline constexpr RosterShot400Event roster_held401_voice[]={{0,0,0,0,RosterShot400Kind::Voice,27,0,0,0,0}};
inline constexpr RosterShot400Event roster_held401_first[]={{0,0,0,0,RosterShot400Kind::Voice,27,0,0,0,0},
 {0,0,0,0,RosterShot400Kind::Effect,0,0,0,0,0},{0,0,0,0,RosterShot400Kind::Attachment,2,0,0,0,0},
 {0,0,0,0,RosterShot400Kind::AttackCount,0,0,0,0,0},{0,0,0,0,RosterShot400Kind::Attachment,0,0,0,0,0}};
inline constexpr RosterShot400Event roster_held401_later[]={{0,0,0,0,RosterShot400Kind::Effect,0,0,0,0,0},
 {0,0,0,0,RosterShot400Kind::Attachment,2,0,0,0,0},{0,0,0,0,RosterShot400Kind::AttackCount,0,0,0,0,0},
 {0,0,0,0,RosterShot400Kind::Attachment,0,0,0,0,0}};

inline int advance_roster_shot401_clock(unsigned character,unsigned weapon,
 unsigned phase,unsigned frame,unsigned rounds,RosterShot401Clock& clock,GroundShotEffects& effect,
 std::vector<GroundShotEffects>& requests,int default_delta,bool boosted=false,float elevation=0){
 if(!((character==6&&weapon==2)||(character==12&&weapon==1)))return default_delta;
 if(phase==0&&frame==0)clock.frame10_visits=0;
 if(phase!=0||frame!=10)return default_delta;
 const unsigned visit=clock.frame10_visits++;
 effect.callback_first=effect.callback_last=nullptr;
 requests.clear();effect.fire=false;effect.effect=-1;
 effect.voice=visit<=2?(rounds<3?30:27):-1;
 if(effect.voice>=0){effect.callback_first=std::begin(roster_held401_voice);effect.callback_last=std::end(roster_held401_voice);effect.callback_request_begin=0;}
 effect.attack_calls=0;effect.count_attack=false;
 if(!rounds)return 31; // Original skips to frame41 when the volley has no ammunition.
 if(visit==2||visit==9){
  effect.effect=character==6?230:155;
  effect.fire=true;effect.attack_calls=1;effect.count_attack=true;
  const auto* first=visit==2?std::begin(roster_held401_first):std::begin(roster_held401_later);
  effect.callback_first=first;effect.callback_last=first+(visit==2?std::size(roster_held401_first):std::size(roster_held401_later));
  effect.callback_request_begin=0;
  for(unsigned n=0;n<2;++n){
   GroundShotEffects shot;shot.fire=true;shot.bullet_slot=n==0?2u:boosted?1u:0u;
   shot.origin=GroundShotOrigin::AttachmentZero;shot.attachment_slot=0;
   if(n)shot.pitch=float(std::clamp(int(elevation),-45,45));
   requests.push_back(shot);
  }
 }
 return visit>=9?31:0;
}

}
