#pragma once
#include "battle_magazine.hpp"
#include <algorithm>

namespace daybreak {
struct BattleMagazineHud {
    unsigned rounds=0;
    float fill_fraction=0;
    float initial_charge_fraction=0;
    float followup_charge_fraction=0;
};

// FUN_00642060 snapshots the two shot counts and both charge-stage counters;
// FUN_00644150 renders the corresponding P01 count/fill and two charge strips.
inline BattleMagazineHud battle_magazine_hud(const BattleMagazine& magazine){
    BattleMagazineHud out;
    out.rounds=unsigned(std::max(0,damage_signed(magazine.rounds)));
    const auto maximum=damage_signed(magazine.capacity);
    // FUN_004356b0 publishes a composite display counter for reload modes
    // 1/2: rounds * reload threshold + partial reload progress. The original
    // fill sprite divides that counter by capacity * threshold. Mode 0 is a
    // direct count, so it divides rounds by capacity instead.
    // Empty magazines select different widgets bound to +700/+744 reload
    // progress and +6d0/+714 threshold, independently of magazine capacity.
    if(!out.rounds){
        const auto threshold=damage_signed(magazine.reload_threshold);
        if(threshold>0)out.fill_fraction=std::clamp(float(std::max(0,damage_signed(magazine.reload_progress)))/float(threshold),0.f,1.f);
    }else if(magazine.mode==1||magazine.mode==2){
        const auto display_limit=damage_signed(magazine.word34);
        if(display_limit>0)out.fill_fraction=std::clamp(float(std::max(0,damage_signed(magazine.display)))/float(display_limit),0.f,1.f);
    }else if(maximum>0){
        const auto display=damage_signed(magazine.display);
        out.fill_fraction=std::clamp(float(std::max(0,display))/float(maximum),0.f,1.f);
    }
    const auto first_limit=30;
    if(first_limit>0)out.initial_charge_fraction=std::clamp(float(std::max(0,damage_signed(magazine.word1c)))/float(first_limit),0.f,1.f);
    const auto followup_limit=damage_signed(magazine.word24);
    if(followup_limit>0)out.followup_charge_fraction=std::clamp(float(std::max(0,damage_signed(magazine.word20)))/float(followup_limit),0.f,1.f);
    return out;
}
}
