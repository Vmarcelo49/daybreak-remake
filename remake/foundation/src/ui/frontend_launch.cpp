#include "ui/frontend_launch.h"
#include "assets/asset_source.h"
#include "assets/stage_catalog.h"
#include <cstdio>
#include <vector>

namespace ui {
namespace {
const char* const dirs[16]={"rena","mion","keiichi","satoko","rika","shion","tomitake","takano","ohishi","akasaka","irie","chie","kasai","akane","hanyu","natumi"};
// ASSET-CATALOG §3.3; FUN_0041e180 reads each character DAT's weapon id at 0x114.
constexpr int ids[16][3]={{1,3,33},{2,4,35},{5,18,34},{8,17,38},{7,19,37},{6,20,36},{12,21,42},{11,22,41},{9,23,39},{10,24,40},{13,26,43},{14,25,44},{15,27,45},{16,28,46},{31,32,0},{29,30,0}};
bool choice(const FrontendSlot& slot,std::string& character,std::string& weapon,int& id,std::string& error) {
    if(slot.character<0 || slot.character>=16 || slot.weapon<0 || slot.weapon>=(slot.character<14?3:2)) {
        error="front end: invalid character or weapon choice"; return false;
    }
    character=std::string("data/")+dirs[slot.character]+":"+std::to_string(slot.costume);
    id=ids[slot.character][slot.weapon];
    char path[64]; std::snprintf(path,sizeof(path),"data/item/%03d.dat",id);
    std::vector<uint8_t> bytes;
    if(!fnd::assets::assetSource().read(path,bytes) || bytes.size()<76) {
        error=std::string("front end: cannot read ")+path; return false;
    }
    // FUN_00433eb0: 2 dwords + 30-byte gauge name + 2 dwords, then first 30-byte mesh name.
    size_t end=46;
    while(end<76 && bytes[end]) ++end;
    if(end==76) { error="front end: unterminated item mesh name"; return false; }
    weapon.clear();
    if(end>46) weapon="data/item/"+std::string(reinterpret_cast<const char*>(bytes.data()+46),end-46);
    return true;
}
}
const char* frontendCharacterDirectory(int index) { return index >= 0 && index < 16 ? dirs[index] : nullptr; }
bool frontendLaunch(const FrontendState& state,FrontendLaunch& out,std::string& error,uint32_t seed) {
    for(int i : {1,3}) if(state.slots[i].ready && state.slots[i].controller<4) {
        error="front end: four-player battles are not implemented; use the two upper panels"; return false;
    }
    seed ^= 0x9e3779b9u;
    seed ^= seed << 13; seed ^= seed >> 17; seed ^= seed << 5;
    const auto& randomStage = assets::kStages[seed % (sizeof(assets::kStages)/sizeof(assets::kStages[0]))];
    int stage=state.stage==0 ? randomStage.scene + randomStage.timeOfDay*10 : state.stage+state.variation*10;
    if(stage<1 || stage>26 || stage%10<1 || stage%10>6 || (stage>=20 && stage!=21)) {
        error="front end: invalid stage variation"; return false;
    }
    char path[32]; std::snprintf(path,sizeof(path),"data/stage%02d",stage); out.stage=path;
    return choice(state.slots[0],out.character,out.weapon,out.weaponId,error) &&
           choice(state.slots[2],out.enemy,out.enemyWeapon,out.enemyWeaponId,error);
}
}
