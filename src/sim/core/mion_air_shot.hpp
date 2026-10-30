#pragma once
#include "mion_ground_shot.hpp"
namespace daybreak {
struct MionAirShotEffects : MionGroundShotEffects {
 unsigned shot_count=0;float pitch=0;bool recover_gauge=false;
};
// Original402/403 in4582a0/461810/44fa10. Gravity belongs to the actor;
// preserve it across entry. Caller owns animation clocks and attachment spawns.
inline MionAirShotEffects advance_mion_air_shot(MionGroundShot& s,unsigned weapon,unsigned state,
 unsigned phase,unsigned frame,bool complete,bool grounded,float& speed,float& offset,float& movement,
 float& vertical,float elevation,int rounds,bool special){
 if(weapon>2||(state!=402&&state!=403))throw std::invalid_argument("Unsupported Mion air shot");
 MionAirShotEffects out;
 if(complete){out.next_state=state==402?43:0;return out;}
 if(state==403){s.gravity=0;vertical=speed=movement=0;out.recover_gauge=true;return out;}
 if(grounded){out.next_state=403;return out;}
 if(phase==0&&frame==0){out.activate=true;if(weapon==2)s.hold=0;else s.shots=0;}
 if(weapon==0){if(s.shots<25)turn_air_shot(offset,movement,20);if(s.shots>14&&s.shots<25)turn_air_shot(offset,movement,5);}
 else if(weapon==1){if(phase==0&&frame<14)turn_air_shot(offset,movement,18);}
 else {if(frame<14)turn_air_shot(offset,movement,15);if(frame<19)turn_air_shot(offset,movement,10);}
 if(phase==1&&frame>15){out.next_phase=2;return out;}
 if(weapon!=2)++s.shots;
 const bool fire=weapon==0?(s.shots==15||s.shots==20||s.shots==25):weapon==1?s.shots==13:frame==18;
 if(fire){
  out.fire=true;out.shot_count=weapon==2?1:2;out.pitch=float(std::clamp(int(elevation),-40,40));
  out.bullet_slot=special?(weapon==1?4u:1u):0u;out.sound=weapon==0?72:weapon==1?80:179;
  if(weapon==2){movement=0;speed=-10;vertical=5;++s.shots;s.pitch=int(out.pitch);out.voice=rounds<2?30:28;}
  else {s.ticks=int(out.pitch);if(weapon==1||s.shots==15)out.voice=rounds<(weapon==0?7:3)?30:weapon==0?28:27;}
 }
 if(s.gravity==0)s.gravity=.5f;vertical-=s.gravity;
 if(weapon==2&&frame==23&&s.hold<10){++s.hold;out.hold_clock=true;}
 return out;
}
}
