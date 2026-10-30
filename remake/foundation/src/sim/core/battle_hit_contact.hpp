#pragma once
#include <array>
#include <cstdint>
namespace daybreak {
using BattleContactVector=std::array<float,4>;
struct BattleHitContact {BattleContactVector victim_point,attack_point;};
// 0x637fd8..0x6380c8. At least one contact must have passed geometry.
inline BattleHitContact battle_hit_contact(const BattleContactVector& primary,const BattleContactVector& secondary,const BattleContactVector& start,const BattleContactVector& end,std::uint32_t shape,bool primary_hit,bool secondary_hit){
 BattleHitContact out{{0,0,0,1},start};float count=0;
 if(primary_hit){for(unsigned i=0;i<4;++i)out.victim_point[i]+=primary[i];count+=1;}
 if(secondary_hit){for(unsigned i=0;i<4;++i)out.victim_point[i]+=secondary[i];count+=1;}
 if(shape)for(unsigned i=0;i<4;++i){volatile float sum=start[i]+end[i];out.attack_point[i]=sum*0.5f;}
 const float inverse=1.f/count;
 for(auto& c:out.victim_point)c*=inverse;
 return out;
}
}
