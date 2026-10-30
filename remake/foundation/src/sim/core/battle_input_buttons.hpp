#pragma once
#include "battle_input_channel.hpp"
namespace daybreak {
// Rebuild carrier: low six bits remain the logical view; bit6 marks the
// physical eight-button mask in bits8..15. It is not an original packet.
inline constexpr unsigned battle_physical_tag=0x40;
inline unsigned battle_physical_buttons(unsigned buttons){
 if(buttons&battle_physical_tag)return (buttons>>8)&255;
 // Untagged callers retain their logical API. Guard is the physical B5 alias.
 return ((buttons&2)?1u:0u)|((buttons&1)?2u:0u)|((buttons&16)?4u:0u)|
  ((buttons&8)?8u:0u)|((buttons&4)?32u:0u)|((buttons&32)?64u:0u);
}
inline unsigned battle_logical_buttons(unsigned physical,bool command_pulse){
 const bool jump=(physical&33)!=0,melee=(physical&50)!=0,shoot=(physical&20)!=0;
 return unsigned(melee)|(unsigned(jump)<<1)|(unsigned(jump&&melee)<<2)|
  ((physical&8)?8u:0u)|(unsigned(shoot)<<4)|(unsigned(command_pulse)<<5);
}
inline unsigned battle_button_carrier(unsigned physical,bool command_pulse=false){
 return battle_physical_tag|((physical&255)<<8)|battle_logical_buttons(physical,command_pulse);
}
}
