#include "ui/frontend_launch.h"
#include "assets/asset_source.h"
#include "gameplay/weapon_definition.h"
#include "assets/stage_catalog.h"
#include <cstdio>
#include <vector>

namespace ui {
namespace {
// The roster order lives with the weapon table it indexes
// (gameplay::kCharacterDirs); one copy for selection and simulation.
bool choice(const FrontendSlot& slot,std::string& character,std::string& weapon,int& id,std::string& error) {
    if(slot.character<0 || slot.character>=16 || slot.weapon<0 ||
       slot.weapon>=gameplay::weaponCountForCharacter(slot.character)) {
        error="front end: invalid character or weapon choice"; return false;
    }
    character=std::string("data/")+gameplay::kCharacterDirs[slot.character]+":"+std::to_string(slot.costume);
    id=gameplay::kWeaponIds[slot.character][slot.weapon];
    char path[64]; std::snprintf(path,sizeof(path),"data/item/%03d.dat",id);
    std::vector<uint8_t> bytes;
    if(!fnd::assets::assetSource().read(path,bytes)) {
        error=std::string("front end: cannot read ")+path; return false;
    }
    // The item's first non-empty attachment mesh, through the real parser (no second copy
    // of the slot layout). FUN_00433eb0:90-116 walks every slot and skips the empty names
    // (:111), so a mesh in a later slot is the item's mesh, and an item with none is legal
    // — the id above is what arms the fighter, and the mesh is only what it draws.
    gameplay::WeaponDefinition item;
    std::string parseError;
    if(!item.parse(id,bytes.data(),bytes.size(),parseError)) {
        error="front end: "+parseError; return false;
    }
    weapon.clear();
    for(int slot=0;slot<item.slotCount;++slot) {
        if(!item.slots[slot].meshName.empty()) {
            weapon="data/item/"+item.slots[slot].meshName;
            break;
        }
    }
    return true;
}
}
const char* frontendCharacterDirectory(int index) { return index >= 0 && index < 16 ? gameplay::kCharacterDirs[index] : nullptr; }
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
