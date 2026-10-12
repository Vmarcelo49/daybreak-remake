#pragma once

#include <array>
#include <algorithm>
#include "assets/xmodel.h"

namespace gameplay {
// FUN_0042fff0 keeps twelve history samples; FUN_00430120 expands nine spline
// spans into five subdivisions; FUN_004303b0 draws an anchored triangle fan.
// This geometry is generated at runtime; it is not a missing .X effect asset.
class WeaponTrail {
public:
    static constexpr int kTriangles = 40;
    static constexpr int kVertices = kTriangles + 2;

    void reset() { m_history = {}; m_length = 0; m_ready = false; m_tip = glm::vec3(0.f); }
    // One original ribbon update. The tip sample is the prop's transformed anchor B
    // (FUN_00430120 writes samples[0]/samples[1] once per frame), so a repeated call
    // between frames carries the same value and must NOT shift history again.
    // `active` is the prop's own +0x38 latch, which the executor deactivates every
    // frame and re-asserts inside its phase/tick windows.
    void step(bool active, const glm::vec3& root, const glm::vec3& tip) {
        m_root = root;
        const bool accepted = !m_ready || tip != m_tip;
        if (accepted) {
            if (!m_ready) { m_history.fill(tip); m_ready = true; }
            for (size_t i = m_history.size() - 1; i > 0; --i) m_history[i] = m_history[i - 1];
            m_history[0] = tip;
            m_tip = tip;
            if (active) m_length = std::min(kTriangles, m_length + 5);
        }
        // FUN_0042fff0 decays outside the change branch, so it runs on every call.
        if (!active) m_length = std::max(0, m_length - 2);
    }
    int triangles() const { return m_length; }
    std::array<xm::Vertex, kVertices> vertices() const {
        std::array<xm::Vertex, kVertices> out{};
        for (auto& vertex : out) {
            vertex.pos = m_root;
            vertex.normal = glm::vec3(0.f, 1.f, 0.f);
            vertex.color = glm::vec4(1.f);
        }
        out[0].uv = glm::vec2(0.f,0.f);
        for (int i = 0; i <= m_length && m_length; ++i) {
            const int span = i / 5;
            const float t = static_cast<float>(i % 5) / 5.f;
            const float t2 = t*t, t3 = t2*t;
            glm::vec4 weights;
            if (span == 0) {
                weights = {(1.f-t)*(1.f-t)*(1.f-t), 3.f*t + 1.75f*t3 - 4.5f*t2,
                           1.5f*t2 - .9166667f*t3, t3 / 6.f};
            } else if (span == 1) {
                weights = {(1.f-t)*(1.f-t)*(1.f-t) / 4.f,
                           .25f*t + .5833333f*t3 - 1.25f*t2 + .5833333f,
                           .5f*t + .5f*t2 - .5f*t3 + 1.f/6.f, t3/6.f};
            } else if (span == 7) {
                // FUN_0065d4d0 mirrors the second clamped span.
                weights = {t3/6.f, .5f*t + .5f*t2 - .5f*t3 + 1.f/6.f,
                           .25f*t + .5833333f*t3 - 1.25f*t2 + .5833333f,
                           (1.f-t)*(1.f-t)*(1.f-t) / 4.f};
            } else if (span == 8) {
                // FUN_0065d580 really uses t^2 in its second weight (0x65d5d6).
                weights = {t3/6.f, 1.5f*t2 - .9166667f*t2,
                           3.f*t + 1.75f*t3 - 4.5f*t2,
                           (1.f-t)*(1.f-t)*(1.f-t)};
            } else {
                weights = {(1.f-t)*(1.f-t)*(1.f-t)/6.f, .5f*t3 - t2 + 2.f/3.f,
                           .5f*t + .5f*t2 - .5f*t3 + 1.f/6.f, t3/6.f};
            }
            auto& vertex = out[static_cast<size_t>(i + 1)];
            vertex.pos = glm::vec3(0.f);
            for (int k = 0; k < 4; ++k)
                vertex.pos += m_history[static_cast<size_t>(span + k)] * weights[k];
            // FUN_0042fce0 initializes each non-root vertex with U=1; FUN_004303b0
            // advances V from 0 to 1 along the history. Swapping these axes samples
            // only the transparent edge of Rena+0's kiseki02 ribbon texture.
            vertex.uv = glm::vec2(1.f, static_cast<float>(i) / m_length);
        }
        return out;
    }
private:
    std::array<glm::vec3, 12> m_history{};
    glm::vec3 m_root{0.f};
    glm::vec3 m_tip{0.f};
    int m_length = 0;
    bool m_ready = false;
};
} // namespace gameplay
