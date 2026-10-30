#pragma once
#include "asset_search_path.hpp"
#include "x_compression.hpp"
#include "x_collision_text.hpp"
namespace daybreak {
// 40179d/4019b9 ->64d940: separate actor and projectile static models.
// Actor42cb50/42c970 use stage+20; projectile script/free/ground use stage+28.
struct BattleStageCollisionAssets {
    StageCollisionMesh actor,projectile;
    static StageCollisionMesh decode(std::vector<std::uint8_t> bytes){
        if(compressed_x(bytes))bytes=expand_x(bytes);
        auto mesh=bytes.size()>=16&&!std::memcmp(bytes.data()+8,"txt ",4)
            ?XCollisionTextReader(bytes).read():StageCollisionMesh::from_scene(XScene::decode(bytes,XMatrixMode::SimdOrder));
        mesh.prepare_acceleration();return mesh;
    }
    static BattleStageCollisionAssets load(AssetSearchPath& search,const std::string& stage){
        return {decode(search.read(stage+"/collision.x").bytes),decode(search.read(stage+"/collision_tama.x").bytes)};
    }
};
}
