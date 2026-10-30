#pragma once
#include <array>
#include <cstdint>
namespace daybreak {
// Explicit state of original 0x65d0c0/0x65d150, for reproducible battle simulation.
struct BattleRandom {
 std::array<std::uint32_t,624> words{};std::uint32_t index=625;
 void seed(std::uint32_t value){words[0]=value;for(index=1;index<624;++index)words[index]=1812433253u*(words[index-1]^(words[index-1]>>30))+index;}
 std::uint32_t next(){
  if(index>=624){
   if(index==625)seed(5489);
   for(unsigned i=0;i<624;++i){const auto y=(words[i]&0x80000000u)|(words[(i+1)%624]&0x7fffffffu);words[i]=words[(i+397)%624]^(y>>1)^((y&1)?0x9908b0dfu:0u);}
   index=0;
  }
  auto y=words[index++];y^=y>>11;y^=(y<<7)&0x9d2c5680u;y^=(y<<15)&0xefc60000u;return y^(y>>18);
 }
};
}
