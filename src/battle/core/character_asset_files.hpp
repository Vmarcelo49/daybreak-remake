#pragma once
#include "weapon_item_data.hpp"
#include "character_names.hpp"
#include "asset_search_path.hpp"
#include "actor_animation_settings.hpp"
#include "x_compression.hpp"
namespace daybreak {
struct CharacterAssetFiles {
 std::string frame_path,model_path,item_path;
 WeaponItemData item;
 std::vector<std::uint8_t> frames,model;
 ActorFrameFile frame_data;ActorAnimationSection settings;
};
inline CharacterAssetFiles load_character_asset_files(AssetSearchPath& assets,unsigned character,unsigned weapon,unsigned variant=0){
 if(character>=character_names.size()||weapon>=(character<14?3u:2u))throw std::out_of_range("Invalid character/weapon");
 if(variant>5)throw std::out_of_range("Invalid model variant");
 CharacterAssetFiles out;auto folder=std::string("data/")+std::string(character_names[character])+"/";
 char file[16];std::snprintf(file,sizeof file,"%02u.dat",weapon);out.frame_path=folder+file;
 out.frames=assets.read(out.frame_path).bytes;out.frame_data=read_actor_frame_data(out.frames);
 out.settings=read_actor_animation_settings(out.frames,out.frame_data.consumed);
 if(out.settings.consumed!=out.frames.size())throw std::runtime_error("Unconsumed character data: "+out.frame_path);
 // 41e180 overwrites its weapon argument from DAT parameter3 before433eb0.
 const auto item_id=out.frame_data.parameters[3];if(item_id>127)throw std::runtime_error("Unsupported signed-byte item ID");
 char item_file[40];std::snprintf(item_file,sizeof item_file,"data/item/%03u.dat",item_id);out.item_path=item_file;
 const auto item_bytes=assets.read(out.item_path).bytes;out.item=read_weapon_item_data(item_bytes);
 // DAT names the model: weapon number is not generally the model number.
 // 41e180 selects only the model directory; DAT and weapon item remain shared.
 const auto model_folder=variant?std::string("data/")+std::string(character_names[character])+"_"+char('A'+variant)+"/":folder;
 out.model_path=model_folder+out.frame_data.model;out.model=assets.read(out.model_path).bytes;
 if(compressed_x(out.model))out.model=expand_x(out.model);
 // Model animation count and settings count are intentionally independent.
 // Original Ohishi and Hanyu weapon1 assets contain 124 sets but 122 settings.
 return out;
}
}
