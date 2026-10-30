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
    // Q25 rows (item 001 parameters 40/60/70/90/130/140): FUN_005f91c0 writes an
    // initial yaw offset to +0x30 (degrees) and steers by a per-tick degree step.
    // Existing entries leave both at 0, so their aggregate initialisers are unchanged.
    float turnGrow = 0.f;    // extra degrees/tick per counted tick (capped by turnCounter)
    float initialYaw = 0.f;  // degrees added to the spawn yaw
};

// FUN_005f7be0 item 001 -> original FUN_005f91c0. Parameter is
// type*10+status, NOT an item row. Distances and speeds are per original update.
// Q25 rows: parameters 40/60/70/90/130/140 (item rows 4/6/7/9/13/14) carry the recovered
// speed, lifetime, wall child 5 and initial yaw offset (+-45/+-60 at +0x30). Remaining
// approximations are named: 0x3c's +0x34 vertical 20 is not applied, the sub-degree inner
// steering (0.0035/0.004 x counter) is replaced by the dominant 3-degree approach, and
// FUN_0042dac0's aim jitter plus the 0xf/0x10 particles are not modelled.
inline constexpr std::array<ProjectileBehavior,17> kProjectileBehavior = {{
    {1,0,37.5f,240,0,0,.2f,0,0,0,3.f,0,0,false,-1,0,5,ProjectileContact::StopOnBlock},
    {1,10,37.5f,240,0,0,.2f,0,0,0,3.f,0,0,false,-1,0,5,ProjectileContact::StopOnBlock},
    {1,20,25.f,1800,.3f,10.f,0,0,0,0,0,0,0,false,-1,0,3},
    {1,30,0.f,51},
    // Item 001 powered charge: FUN_005f91c0's 80/100 cases share the
    // gravity arc and lifetime of 20/30, but spawn explosion row 10.
    {1,80,25.f,1800,.3f,10.f,0,0,0,0,0,0,0,false,-1,0,10},
    {1,100,0.f,51},
    {1,110,45.f,240,0,0,0,.005f,.05f,50,1.f,45.f,0,false,17,2,5,ProjectileContact::Pause,5,5,10,60.f},
    {1,120,45.f,240,0,0,0,.005f,.05f,50,1.f,-45.f,0,false,17,2,5,ProjectileContact::Pause,5,5,10,60.f},
    {1,150,0.f,13,0,0,0,0,0,0,0,0,35.f,false,-1,0,-1,ProjectileContact::Persist,0},
    {1,160,0.f,13,0,0,0,0,0,0,0,90.f,0,false,-1,0,-1,ProjectileContact::Persist,0},
    {1,170,0.f,13,0,0,0,0,0,0,0,0,35.f,true,-1,0,-1,ProjectileContact::Persist,0},
    // Q25: 407's launch rows. Speeds/lifetimes/wall child from FUN_005f91c0 cases
    // 0x28/0x5a/0x82/0x8c; the +-45/+-60 initial yaw is +0x30. The first-tick 3-degree
    // approach is the dominant steering; the sub-degree inner step is not modelled.
    {1,40,30.f,480,0,0,3.f,0,0,0,3.f,0,0,false,-1,0,5,ProjectileContact::Persist,0,0,0,0.f,0.f,45.f},
    {1,90,30.f,480,0,0,3.f,0,0,0,3.f,0,0,false,-1,0,5,ProjectileContact::Persist,0,0,0,0.f,0.f,-45.f},
    {1,130,25.f,480,0,0,3.f,0,0,0,3.f,0,0,false,-1,0,5,ProjectileContact::Persist,0,0,0,0.f,0.f,60.f},
    {1,140,25.f,480,0,0,3.f,0,0,0,3.f,0,0,false,-1,0,5,ProjectileContact::Persist,0,0,0,0.f,0.f,-60.f},
    // Q25: the powered taps' rows 6/7 (cases 0x3c/0x46): speed 45, lifetime 240 and the
    // growing approach counter*0.01+0.25 capped at 120 (turnBase + turnGrow).
    {1,60,45.f,240,0,0,0,0,.25f,120,3.f,0,0,false,-1,0,5,ProjectileContact::Persist,0,0,0,0.f,.01f,0.f},
    {1,70,45.f,240,0,0,0,0,.25f,120,3.f,0,0,false,-1,0,5,ProjectileContact::Persist,0,0,0,0.f,.01f,0.f},
}};
inline const ProjectileBehavior* projectileBehavior(int weapon, int parameter) {
    for (const auto& row : kProjectileBehavior)
        if (row.weapon == weapon && row.parameter == parameter) return &row;
    return nullptr;
}
} // namespace gameplay
