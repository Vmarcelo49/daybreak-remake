#pragma once
#include <array>
#include <cstdint>
#include <stdexcept>

namespace daybreak {
struct SpriteVertex {float x,y,z,rhw;std::uint32_t color;float u,v;};
static_assert(sizeof(SpriteVertex)==28,"Original XYZRHW / diffuse / UV vertex layout");
struct SpriteDraw {unsigned texture;std::array<SpriteVertex,4> vertices;};
// Recovered non-rotated sprite paths 0x655d60 / 0x655830, using half-pixel offset.
inline SpriteDraw sprite(unsigned texture,float left,float top,float width,float height,
                         float u0,float v0,float u1,float v1,float z=0) {
    left-=0.5f;top-=0.5f;
    return {texture,{{{left,top,z,1,0xffffffff,u0,v0},{left+width,top,z,1,0xffffffff,u1,v0},
                     {left,top+height,z,1,0xffffffff,u0,v1},{left+width,top+height,z,1,0xffffffff,u1,v1}}}};
}
// Constructor 0x410d60, draw 0x4114f0. Source textures are padded to powers of two.
inline std::array<SpriteDraw,8> title_draws(unsigned selected) {
    if(selected>=6) throw std::out_of_range("Title selection must be 0..5");
    std::array<SpriteDraw,8> draws;
    draws[0]=sprite(0,0,0,800,600,0,0,800.0f/1024,600.0f/1024);
    draws[1]=sprite(1,144,-20,512,300,0,0,1,300.0f/512);
    for(unsigned i=0;i<6;++i) {
        const float column=i==selected?0.0f:192.0f;
        draws[i+2]=sprite(2,304,285.0f+48*i,192,48,column/512,48.0f*i/512,
                          (column+192)/512,48.0f*(i+1)/512,0.5f);
    }
    return draws;
}
}
