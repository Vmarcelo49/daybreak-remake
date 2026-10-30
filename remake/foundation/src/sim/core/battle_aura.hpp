#pragma once
#include "projectile_model_animation.hpp"
#include "asset_search_path.hpp"
#include "x_compression.hpp"
#include <cstdio>
namespace daybreak {
// 41e180 / 421010: eleven current bone matrices, not motion history.
inline constexpr const char* battle_aura_bones[]={"Bip00","Bip01_Head","Bip01_Spine",
 "Bip01_L_Forearm","Bip01_R_Forearm","Bip00_L_Calf","Bip00_R_Calf",
 "Bip01_L_Hand","Bip01_R_Hand","Bip00_L_Foot","Bip00_R_Foot"};
// 42e110 writes +7d4 before the common model service; preserve it over frozen
// actor visits. The explicit status selection precedes all awakening flags.
inline int battle_status_aura(unsigned state,unsigned phase){
 if((state==104||state==105||state==204||state==205)&&phase==0)return 2;
 if(state==106||state==107||state==108||state==206)return 3;
 return -1;
}
inline int battle_aura_model(int status,bool active0,bool active1,bool active2){
 if(status>=0&&status<=6)return status;
 return active0?0:active2?5:active1?1:-1;
}
inline LegacyMatrix battle_long_stop_aura(const LegacyMatrix& spine){
 const LegacyMatrix scale{128,0,0,0,0,128,0,0,0,0,128,0,0,0,0,1};
 return multiply_matrix_scalar24(scale,spine);
}
struct BattleAuraAsset {
 std::string path;std::vector<std::uint8_t> model;ProjectileModelAnimation animation;
 static BattleAuraAsset load(AssetSearchPath& assets,unsigned index){
  if(index>=7)throw std::out_of_range("Invalid aura model");
  BattleAuraAsset out;char name[32];std::snprintf(name,sizeof name,"data/aura/%02u.x",index);out.path=name;
  out.model=assets.read(out.path).bytes;if(compressed_x(out.model))out.model=expand_x(out.model);
  out.animation=ProjectileModelAnimation::decode(out.model);return out;
 }
};
}
