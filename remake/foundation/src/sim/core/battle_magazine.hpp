#pragma once
#include "battle_damage_scaling.hpp"
namespace daybreak {
// 435660/4356b0/435920. Unknown fields are retained for layout/oracle comparison.
struct BattleMagazine {
 std::uint32_t mode=0,reserved04=0,capacity=0,reload_threshold=0,shot_interval=0,refill_step=1,rounds=0;
 std::uint32_t word1c=0,word20=0,word24=0,word28=0,word2c=0,display=0,word34=0,flags=0,reload_progress=0,cooldown=0;
};
static_assert(sizeof(BattleMagazine)==0x44);
inline void reset_battle_magazine(BattleMagazine& s){s.rounds=s.capacity;s.word1c=s.word20=s.word28=0;s.flags&=0xffff0000u;}
inline void tick_battle_magazine(BattleMagazine& s){
 auto less=[](std::uint32_t a,std::uint32_t b){return damage_signed(a)<damage_signed(b);};
 if(s.rounds)s.flags&=0xffff00ffu;
 if(s.mode==2){
  if(s.rounds==0){
   ++s.cooldown;
   if(damage_signed(s.cooldown)>=damage_signed(s.capacity)/2){s.cooldown=0;s.reload_progress+=s.refill_step;}
   if(!less(s.reload_progress,s.reload_threshold)){s.rounds=s.capacity;s.cooldown=s.shot_interval;s.flags=(s.flags&0xffff00ffu)|0x100;}
  }else if(less(s.rounds,s.capacity)){
   s.reload_progress+=s.refill_step;
   if(!less(s.reload_progress,s.reload_threshold)){++s.rounds;s.reload_progress=0;}
  }
  s.display=s.rounds*s.reload_threshold+s.reload_progress;
 }else if(s.mode==1){
  if(less(s.rounds,s.capacity)){s.reload_progress+=s.refill_step;if(!less(s.reload_progress,s.reload_threshold)){++s.rounds;s.reload_progress=0;}}
  s.display=s.rounds*s.reload_threshold+s.reload_progress;
 }else {
  if(s.rounds==0){s.reload_progress+=s.refill_step;if(!less(s.reload_progress,s.reload_threshold)){s.rounds=s.capacity;s.cooldown=s.shot_interval;s.flags=(s.flags&0xffff00ffu)|0x100;}}
  s.display=s.rounds;
 }
 if(less(s.cooldown,s.shot_interval))++s.cooldown;
 if(!(s.flags&0xff))s.word1c=s.word20=s.word28=0;else s.flags&=0xffffff00u;
}
inline bool consume_battle_round(BattleMagazine& s){
 if(s.rounds==0||damage_signed(s.cooldown)<damage_signed(s.shot_interval))return false;
 if(s.rounds==s.capacity)s.reload_progress=0;
 --s.rounds;s.cooldown=0;if(s.rounds==0)s.reload_progress=0;return true;
}
// 43f3e0: word1c initial hold,20 later-stage hold,24 stage threshold,
// 28 current charge stage,2c maximum stage. The tick consumes flags.low-byte.
inline std::uint32_t charge_battle_magazine(BattleMagazine& s){
 if(s.rounds==0)return 0;
 s.flags=(s.flags&0xffffff00u)|1u;
 if(s.word28==0){
  ++s.word1c;
  if(damage_signed(s.word1c)>29){if(s.word2c==1){s.word28=s.word2c;s.word1c=30;}else ++s.word28;}
 }else if(damage_signed(s.word2c)>1){
  ++s.word20;
  if(damage_signed(s.word20)>=damage_signed(s.word24)){
   if(damage_signed(s.word28+1u)<damage_signed(s.word2c)){s.word20=0;++s.word28;}
   else {s.word28=s.word2c;s.word20=s.word24;}
  }
 }
 return s.word28;
}

}
