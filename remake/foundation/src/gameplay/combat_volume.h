#pragma once

#include <algorithm>
#include <glm/glm.hpp>

namespace gameplay {
// FUN_0063b470 / FUN_0063b4d0: two victim spheres against the record's
// transformed sphere or capsule. Equality is outside the collision volume.
inline bool combatVolumeHits(glm::vec3 start, glm::vec3 end, bool capsule,
                              float radius, glm::vec3 head, glm::vec3 chest,
                              float bodyRadius = 30.f) {
    const glm::vec3 segment = end - start;
    const float lengthSquared = glm::dot(segment,segment);
    const auto distance = [&](glm::vec3 point) {
        glm::vec3 closest = start;
        if (capsule && lengthSquared > 0.f)
            closest += segment * std::clamp(glm::dot(point-start,segment)/lengthSquared,0.f,1.f);
        return glm::dot(point-closest,point-closest);
    };
    const float combined = radius + bodyRadius;
    return std::min(distance(head),distance(chest)) < combined * combined;
}
} // namespace gameplay
