#pragma once
#include "asset_search_path.hpp"
#include "actor_animation_settings.hpp"
#include "weapon_item_data.hpp"
#include "x_compression.hpp"
#include "projectile_model_animation.hpp"
namespace daybreak {
struct ProjectileAssetFiles {
 std::string frame_path,model_path,model_source_path,material_path;
 std::vector<std::uint8_t> frames,model;
 ActorFrameFile variants;ActorAnimationSection settings;
 unsigned selected_variant=0;
 ProjectileModelAnimation model_animation;
 const ActorStateData& selected()const{
  // 5f8510 overwrites the selected record on each matching ID; last match wins.
  for(auto i=variants.states.rbegin();i!=variants.states.rend();++i)if(i->id==selected_variant)return *i;
  throw std::runtime_error("Projectile variant missing");
 }
};
// 5f60b0:22-34: before the shot's model is drawn, its material intervals are applied to
// the shot's own frame counter (+0x154). FUN_00424230 yields each {start, end, period,
// source, target} record and FUN_0064e820 swaps the texture for that draw, so the
// window is half-open, a positive period wraps, and the last matching record for one
// source wins — exactly actor_texture_remaps. The record is the one the variant's phase
// binds (the same phase-value -> animation-index rule the actor tracks use).
//
// An empty target name is authored data (item 41 rows 0/31-36 blink 発信機 -> '' ->
// 発信機2). What the original binds for it — a null texture, or the model's own — is not
// recovered, so the entry is returned as authored and the caller leaves the material
// alone; only a non-empty target is a texture swap.
inline std::map<std::string,std::string> projectile_texture_remaps(const ProjectileAssetFiles& files,std::int32_t frame){
 const auto& state=files.selected();
 if(state.phases.empty())return {};
 const auto id=state.phases[0].value;
 if(id>=files.settings.animations.size())return {};
 return actor_texture_remaps(files.settings.animations[id],frame);
}
inline ProjectileAssetFiles load_projectile_asset_files(AssetSearchPath& search,unsigned item,const WeaponBulletData& bullet){
 const auto id=bullet.registration_id();if(id<0)throw std::runtime_error("Negative projectile registration ID");
 ProjectileAssetFiles out;char folder[48],path[64];std::snprintf(folder,sizeof folder,"data/bullet/%03u/",item);std::snprintf(path,sizeof path,"%s%03d.dat",folder,id/10);
 out.frame_path=path;out.selected_variant=unsigned(id%10);out.frames=search.read(path).bytes;
 // 5f8510 starts variants at264, with the same154-byte frame records as actors.
 out.variants=read_actor_frame_data(out.frames,false);
 out.settings=read_actor_animation_settings(out.frames,out.variants.consumed);
 if(out.settings.consumed!=out.frames.size())throw std::runtime_error("Unconsumed projectile data: "+out.frame_path);
 out.selected();out.model_path=std::string(folder)+out.variants.model;
 out.model_source_path=out.material_path=out.model_path;
 // The supplied item32 DAT references 032/08.X, absent from its archives.
 // Five other directories supply byte-identical 08.X models. Item31's
 // registration60 likewise references absent 031/50.X. Borrow the same-named
 // 043/50.X in memory, retaining the original frame DAT and model path.
 if(out.model_path=="data/bullet/032/08.X"&&!search.contains(out.model_path))
  out.model_source_path="data/bullet/037/08.X";
 if(out.model_path=="data/bullet/031/50.X"&&!search.contains(out.model_path)){
  out.model_source_path="data/bullet/043/50.X";
  // The donor model names a texture absent under item31, but present beside
  // its source model. Resolve that same-named texture from the donor folder.
  out.material_path=out.model_source_path;
 }
 // Item13 registrations40/50 retain their own DAT. The missing 30.X has a
 // same-named donor beside byte-identical item43/005.dat and base004.dat.
 // Its texture is supplied beside that donor, not under item13.
 if(out.model_path=="data/bullet/013/30.X"&&!search.contains(out.model_path)){
  out.model_source_path=out.material_path="data/bullet/043/30.X";
 }
 // Rena1/005.dat also names the absent30.X. Twenty-one supplied bullet
 // folders share the identical generic30.X mesh. Retain Rena's original
 // frame/damage data and borrow the verified donor's display/material only.
 if(out.model_path=="data/bullet/003/30.X"&&!search.contains(out.model_path)){
  out.model_source_path=out.material_path="data/bullet/043/30.X";
 }
 out.model=search.read(out.model_source_path).bytes;
 if(compressed_x(out.model))out.model=expand_x(out.model);
 out.model_animation=ProjectileModelAnimation::decode(out.model);
 return out;
}
inline unsigned weapon_projectile_registration(const WeaponItemData& weapon,unsigned slot){
 const auto registration=weapon.bullets.at(slot).registration_id();
 if(registration<0)throw std::runtime_error("Negative projectile registration for weapon slot "+std::to_string(slot));
 return unsigned(registration);
}
}
