#pragma once
#include "roster_ground_shot400_world.hpp"

namespace daybreak {

// State401 uses the state400 world-muzzle path for four configurations.
// Character4/weapon1 instead keeps an asymmetric pair fixed to actor heading:
// X uses +/-40 lateral displacement and Z uses +/-50.
inline void apply_roster_shot401_world_geometry(unsigned character,unsigned weapon,
 bool boosted,float elevation,std::vector<GroundShotEffects>& requests){
 if(character==4&&weapon==1){
  unsigned index=0;
  for(auto& shot:requests){
   if(shot.origin!=GroundShotOrigin::World)continue;
   shot.origin_height=boosted?(index<2?100.f:40.f):70.f;
   shot.world_forward_x=shot.world_forward_z=10.f;
   shot.world_lateral=index%2?-40.f:40.f;
   shot.world_lateral_z=index%2?-50.f:50.f;
   shot.world_lateral_z_override=true;
   shot.world_actor_heading_only=true;
   shot.pitch=float(std::clamp(int(elevation),-40,40));
   ++index;
  }
 }else apply_roster_shot400_world_geometry(character,weapon,boosted,elevation,requests);
}

}
