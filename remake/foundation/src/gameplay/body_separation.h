#pragma once

#include <glm/glm.hpp>

#include <cmath>

namespace gameplay {

// The recovered body separation. FUN_006394c0 runs once per frame from FUN_00634f60
// (0x63595e), after the actors' motion basis (FUN_004202b0) and contact anchors
// (FUN_00420880) have been refreshed. Its whole body, from the decompilation:
//
//   for (a = 0; a < 4; ++a)
//     for (b = a + 1; b < 4; ++b)
//       if (a != b && !a->aecc && !b->aecc) {
//         dx = a->x - b->x;  dz = a->z - b->z;
//         dist = sqrt(dx*dx + dz*dz);            // FUN_0042df50
//         dy   = fabs(a->y - b->y);              // FUN_0042df90
//         if (dist == 0) { dx = 1.0f; dist = 1.0f; }   // local_24[0] = 0x3f800000
//         if (dist < 60.0f && dy < 60.0f) {
//           half = (60.0f - dist) / 2.0f;
//           a moves  +(dx/dist, 0, dz/dist) * half)   // FUN_004241d0 + FUN_0042cb50
//           b moves  -(dx/dist, 0, dz/dist) * half)   // FUN_0042e0a0 + FUN_0042cb50
//         }
//       }
//
// Three properties are worth stating because they are easy to get wrong:
//   * the push is HORIZONTAL only — the Y delta is a gate, never a direction;
//   * each body takes exactly half of the remaining overlap, so a pair is at 60 units after
//     one frame (the degenerate dist == 0 case leaves 59, which the listing's forced
//     distance of 1 produces: 2 * 29.5);
//   * both halves go through the horizontal mover FUN_0042cb50, so a stage wall clamps each
//     body independently rather than cancelling the pair's push.
//
// The only pair filter is the +0xaecc byte (a "this slot is a proxy/redirect" flag); there is
// no team, HP or hitstop test, so teammates and KO'd bodies are pushed too.
inline constexpr float kBodySeparationDistance = 60.0f;
inline constexpr float kBodySeparationHeight = 60.0f;

struct BodySeparation {
    bool      active = false;   // the pair is close enough that both bodies move
    glm::vec3 push{0.f};        // displacement for the FIRST body (negate it for the second)
};

// Pure function so the formula is testable without a match: `first` and `second` are the two
// bodies' world positions, in either order.
inline BodySeparation body_separation(const glm::vec3& first, const glm::vec3& second) {
    BodySeparation out;
    float dx = first.x - second.x;
    float dz = first.z - second.z;
    float distance = std::sqrt(dx * dx + dz * dz);
    const float height = std::fabs(first.y - second.y);
    if (distance == 0.f) {
        // The listing forces a unit direction here rather than skipping the pair, so two
        // perfectly overlapping bodies still separate (to 59 units, not 60).
        dx = 1.f;
        distance = 1.f;
    }
    if (!(distance < kBodySeparationDistance) || !(height < kBodySeparationHeight)) return out;
    const float half = (kBodySeparationDistance - distance) * 0.5f;
    out.active = true;
    out.push = glm::vec3(dx / distance * half, 0.f, dz / distance * half);
    return out;
}

}  // namespace gameplay
