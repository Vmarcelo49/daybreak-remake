#pragma once
#include "battle_score_feedback.hpp"
#include "battle_damage_scaling.hpp"
namespace daybreak {
// 6430f0, after all4201a0 services and before6358c0/contact dispatch.
// Score callbacks before this point decay immediately; later contacts retain60.
inline void advance_battle_score_presentation(BattleScoreFeedback& feedback,
 const std::array<std::uint32_t,2>& score,std::array<float,2>& displayed){
 for(unsigned team=0;team<2;++team){
  if(feedback.timer[team])--feedback.timer[team];
  const double target=double(damage_signed(score[team])); //FILD compares the exact signed integer.
  if(displayed[team]<target)displayed[team]+=.5f;
  if(target<displayed[team])displayed[team]-=.5f;
 }
}
}
