#pragma once
#include <cstdint>
#include <cstring>
#include <stdexcept>
namespace daybreak {
inline std::int32_t battle_vision_signed(std::uint32_t value){std::int32_t out;std::memcpy(&out,&value,4);return out;}
// 4201a0 updates byte+824 after all41f580 services, including frozen actors.
// Byte arithmetic wraps; the original does not clamp arbitrary byte seeds.
inline void advance_battle_vision_alpha(std::uint8_t& alpha,std::uint32_t white,std::uint32_t black){
 if(battle_vision_signed(white)<1&&battle_vision_signed(black)<1){if(alpha)alpha=std::uint8_t(alpha-5);}
 else if(alpha!=255)alpha=std::uint8_t(alpha+5);
}
struct BattleVisionEffect{bool obscured=false;unsigned actor_mask=15;std::uint32_t color=0;};
// 6396f0 observes the camera owner, not the selected target. Equality uses
// black; nonzero timers select this branch even for signed-negative seeds.
inline BattleVisionEffect battle_vision_effect(unsigned viewer,std::uint32_t white,std::uint32_t black,std::uint8_t alpha){
 if(viewer>=4)throw std::out_of_range("Vision camera owner");
 const bool obscured=white!=0||black!=0;
 return {obscured,obscured?1u<<viewer:15u,(std::uint32_t(alpha)<<24)|(battle_vision_signed(black)<battle_vision_signed(white)?0xffffffu:0u)};
}
}
