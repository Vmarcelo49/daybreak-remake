#pragma once
#include "battle_camera_view.hpp"
#include "legacy_trig.hpp"
#include "title_scene.hpp"
namespace daybreak {
//434d60 reads the controller's stored pitch (+100/actor+7a0), rather than
//recomputing it from a moving target. The original .1-degree table is shared.
inline std::array<float,3> manual_battle_camera_direction(float heading_plus_offset,float pitch){
 const float horizontal=legacy_trig(pitch,false);
 volatile float x=legacy_trig(heading_plus_offset,false)*horizontal;
 volatile float z=legacy_trig(heading_plus_offset,true)*horizontal;
 return {x,legacy_trig(pitch,true),z};
}
//422f90 returns the slot0 socket and that socket plus a 1000-unit look ray.
inline BattleCameraView manual_battle_camera_view(const std::array<float,3>& socket,float heading_plus_offset,float pitch){
 const auto direction=manual_battle_camera_direction(heading_plus_offset,pitch);
 BattleCameraView view;view.eye=socket;
 for(unsigned i=0;i<3;++i){volatile float step=direction[i]*1000.f;view.look_at[i]=socket[i]+step;}
 return view;
}
//642510 initializes receiver6ca280 from all512x512 pixels of original P13.
//643230 scales that image to800x600 (or half of both for a split viewport).
inline SpriteDraw manual_battle_scope_sprite(float left,float top,float scale){
 return sprite(0,left,top,800.f*scale,600.f*scale,0,0,1,1);
}
}
