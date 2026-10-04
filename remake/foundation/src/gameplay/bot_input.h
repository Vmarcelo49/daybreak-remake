#pragma once
#include <cmath>
#include "gameplay/fighter.h"

namespace gameplay {
// A deterministic 1v1 sparring policy for the port; original COM tactics are not mapped.
inline void updateBotInput(fnd::input::PlayerState& input, const Fighter& fighter,
                           const Fighter& opponent, uint64_t frame) {
    for (bool& down : input.down) down = false;
    if (fighter.is_alive() && opponent.is_alive()) {
        const glm::vec3 delta = opponent.position() - fighter.position();
        const float distance = std::sqrt(delta.x * delta.x + delta.z * delta.z);
        if (distance > 80.f) {
            input.down[fnd::input::Left] = delta.x < -25.f;
            input.down[fnd::input::Right] = delta.x > 25.f;
            input.down[fnd::input::Up] = delta.z < -25.f;
            input.down[fnd::input::Down] = delta.z > 25.f;
        }
        input.down[fnd::input::AttackA] = distance < 120.f && frame % 40 == 1;
        input.down[fnd::input::Shoot] = distance >= 120.f && frame % 45 == 1;
        input.down[fnd::input::Special] = fighter.hyper_ready() && frame % 30 == 1;
    }
    fnd::input::compute_edges(input);
}
}
