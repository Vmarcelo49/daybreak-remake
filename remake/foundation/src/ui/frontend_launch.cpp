#include "ui/frontend_launch.h"
#include "assets/asset_source.h"
#include "gameplay/weapon_definition.h"
#include "assets/stage_catalog.h"
#include <cstdio>
#include <vector>

namespace ui {
namespace {
const char* const dirs[16]={"rena","mion","keiichi","satoko","rika","shion","tomitake","takano","ohishi","akasaka","irie","chie","kasai","akane","hanyu","natumi"};
// The weapon table itself lives in gameplay/weapon_definition.h (kWeaponIds), which is
// also what the battle parses from; keeping one copy here stops the selection screen and
// the simulation from disagreeing about what is selectable. ASSET-CATALOG §3.3.
bool choice(const FrontendSlot& slot,std::string& character,std::string& weapon,int& id,std::string& error) {
    if(slot.character<0 || slot.character>=16 || slot.weapon<0 ||
       slot.weapon>=gameplay::weaponCountForCharacter(slot.character)) {
        error="front end: invalid character or weapon choice"; return false;
    }
    character=std::string("data/")+dirs[slot.character]+":"+std::to_string(slot.costume);
    id=gameplay::kWeaponIds[slot.character][slot.weapon];
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
    out = {};
    seed ^= 0x9e3779b9u;
    seed ^= seed << 13; seed ^= seed >> 17; seed ^= seed << 5;
    const auto& randomStage = assets::kStages[seed % (sizeof(assets::kStages)/sizeof(assets::kStages[0]))];
    int stage=state.stage==0 ? randomStage.scene + randomStage.timeOfDay*10 : state.stage+state.variation*10;
    if(stage<1 || stage>26 || stage%10<1 || stage%10>6 || (stage>=20 && stage!=21)) {
        error="front end: invalid stage variation"; return false;
    }
    char path[32]; std::snprintf(path,sizeof(path),"data/stage%02d",stage); out.stage=path;
    for (int panel = 0; panel < 4; ++panel) {
        const bool required = panel == 0 || panel == 2;
        const FrontendSlot& selected = state.slots[panel];
        if (!required && selected.character < 0) continue;
        FrontendLaunch::Fighter& fighter = out.fighters[out.fighterCount];
        fighter.panel = panel;
        if (!choice(selected, fighter.character, fighter.weapon, fighter.weaponId, error)) return false;
        ++out.fighterCount;
    }
    if (out.fighterCount < 2) {
        error = "front end: both teams need at least one selected fighter";
        return false;
    }
    // Keep the legacy VS/result fields mapped to the primary blue and red panels.
    for (int i = 0; i < out.fighterCount; ++i) {
        const auto& fighter = out.fighters[i];
        if (fighter.panel == 0) {
            out.character = fighter.character;
            out.weapon = fighter.weapon;
            out.weaponId = fighter.weaponId;
        } else if (fighter.panel == 2) {
            out.enemy = fighter.character;
            out.enemyWeapon = fighter.weapon;
            out.enemyWeaponId = fighter.weaponId;
        }
    }
    return true;
}
}
