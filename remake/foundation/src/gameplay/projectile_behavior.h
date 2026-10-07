#pragma once

#include <array>

namespace gameplay {
enum class ProjectileContact { Persist, StopOnBlock, Pause };
struct ProjectileBehavior {
    int weapon, parameter;
    float speed;
    int lifetime;
    float gravity = 0.f;
    float launchVertical = 0.f;
    float turn = 0.f;
    float turnDecay = 0.f;
    float turnBase = 0.f;
    int turnCounter = 0;
    float pitchDeadZone = 0.f;
    float modelPitch = 0.f;
    float modelRoll = 0.f;
    bool randomYaw = false;
    int secondaryRow = -1;
    int secondaryInterval = 0;
    int wallRow = -1;
    ProjectileContact contact = ProjectileContact::Persist;
    int hitsPerVictim = 1;
    int contactPause = 0;
    int repeatPause = 0;
    float resumeSpeed = 0.f;
};

// FUN_005f7be0 item 001 -> original FUN_005f91c0. Parameter is
// type*10+status, NOT an item row. Distances and speeds are per original update.
inline constexpr std::array<ProjectileBehavior,9> kProjectileBehavior = {{
    {1,0,37.5f,240,0,0,.2f,0,0,0,3.f,0,0,false,-1,0,5,ProjectileContact::StopOnBlock},
    {1,10,37.5f,240,0,0,.2f,0,0,0,3.f,0,0,false,-1,0,5,ProjectileContact::StopOnBlock},
    {1,20,25.f,1800,.3f,10.f,0,0,0,0,0,0,0,false,-1,0,3},
    {1,30,0.f,51},
    {1,110,45.f,240,0,0,0,.005f,.05f,50,1.f,45.f,0,false,17,2,5,ProjectileContact::Pause,5,5,10,60.f},
    {1,120,45.f,240,0,0,0,.005f,.05f,50,1.f,-45.f,0,false,17,2,5,ProjectileContact::Pause,5,5,10,60.f},
    {1,150,0.f,13,0,0,0,0,0,0,0,0,35.f,false,-1,0,-1,ProjectileContact::Persist,0},
    {1,160,0.f,13,0,0,0,0,0,0,0,90.f,0,false,-1,0,-1,ProjectileContact::Persist,0},
    {1,170,0.f,13,0,0,0,0,0,0,0,0,35.f,true,-1,0,-1,ProjectileContact::Persist,0},
}};
inline const ProjectileBehavior* projectileBehavior(int weapon, int parameter) {
    for (const auto& row : kProjectileBehavior)
        if (row.weapon == weapon && row.parameter == parameter) return &row;
    return nullptr;
}
} // namespace gameplay
