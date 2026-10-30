#pragma once
#include <array>
#include <algorithm>
namespace daybreak {
// 6b71d0/6b7210 scaled by48/36;409340 phase2 scans in character-id order.
inline constexpr std::array<float,16> selection_x{{0,-96,-48,0,48,-48,-48,-96,0,48,96,96,48,0,144,-144}};
inline constexpr std::array<float,16> selection_y{{216,144,180,144,180,108,36,72,72,108,144,72,36,0,108,108}};
inline int move_character_cursor(float& x,float& y,int current,int horizontal,int vertical){
 x=std::clamp(x+(horizontal<0?-4.f:horizontal>0?4.f:0.f),-200.f,200.f);
 y=std::clamp(y+(vertical<0?-3.f:vertical>0?3.f:0.f),-60.f,300.f);
 auto distance=[&](unsigned i){const float dx=selection_x[i]-x,dy=selection_y[i]-y;return double(float(double(dx)*dx))+double(dy)*dy;};
 if(current>=0&&current<16&&!horizontal&&!vertical&&distance(unsigned(current))<400){x=selection_x[current];y=selection_y[current];}
 int outer=-1,inner=-1;
 for(unsigned i=0;i<16;++i)if(distance(i)<2500){outer=int(i);break;}
 for(unsigned i=0;i<16;++i)if(distance(i)<900){inner=int(i);break;}
 return inner>=0?inner:outer;
}
}
