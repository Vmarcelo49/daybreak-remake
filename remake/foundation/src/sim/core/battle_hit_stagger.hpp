#pragma once
#include "battle_damage_scaling.hpp"
#include <cmath>
namespace daybreak {
struct BattleHitStagger{std::uint32_t count,total,accum,timer,down,down_timer,invincible,back_flag,modifier,selected,transition,staggered,extra;float vertical,horizontal,offset,impact;};
struct BattleHitStaggerInput{std::uint32_t gate,resistance,down_add,vertical,horizontal,flags,flag84,state64,state68,current_state,target_same;float heading,relative;};
// flag84 is GROUNDED; state64 applies while grounded below100 down, otherwise state68.
// Original 0x6385bb..0x6387e7. Finite bounded angles, original 24-bit rounding.
inline void apply_battle_hit_stagger(BattleHitStagger& s,const BattleHitStaggerInput& p){
 s.selected=p.current_state;s.transition=0;s.staggered=0;s.extra=0;
 if(damage_signed(p.gate)<=0)return;
 s.accum+=std::uint32_t(damage_divide(damage_multiply(damage_signed(p.gate),damage_signed(p.resistance)),100));s.timer=120;
 if(damage_signed(s.accum)<100)return;
 s.vertical=static_cast<float>(damage_signed(p.vertical));s.horizontal=static_cast<float>(damage_signed(p.horizontal));++s.count;++s.total;s.staggered=1;s.accum=0;s.down+=p.down_add;s.down_timer=120;
 if(p.flags&0x800){s.selected=121;s.modifier=std::uint32_t(damage_divide(damage_multiply(damage_signed(s.modifier),7),10));}
 else s.selected=std::uint8_t(p.flag84)&&damage_signed(s.down)<100?p.state64:p.state68;
 if(std::fabs(p.relative)>90.f){if((damage_signed(p.current_state)<100||damage_signed(p.current_state)>299)&&!p.target_same)s.back_flag=1;s.selected+=100;s.impact+=180.f;}
 if(damage_signed(s.down)>=100)s.invincible=30;
 s.offset=-(p.heading-s.impact);while(s.offset>180.f)s.offset-=360.f;while(s.offset< -180.f)s.offset+=360.f;s.transition=1;
}
}
