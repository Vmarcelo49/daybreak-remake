#pragma once
// Line-list debug primitives for the SDL3 + WebGPU foundation: world-space segments
// with per-vertex colour, uploaded per frame and drawn over (or depth-tested against)
// a frame the scene pass already rendered.
//
// Provenance — what the DX9 reference actually is, because the plan's one-line summary
// ("line drawing port") does not match the file. remake/src/render/debug_prim.{h,cpp}
// is a placeholder *cube* pass for un-RE'd VFX: 12 triangles per cube via
// DrawPrimitiveUP, D3DFVF_XYZ|D3DFVF_DIFFUSE, lighting/cull/alpha-test disabled,
// texture stage 0 switched to SELECTARG1(DIFFUSE), an optional identity world matrix,
// and an optional SrcAlpha/One blend. It has no line primitive, no box outline, no
// cross and no ray helper. The semantics carried over verbatim are therefore the ones
// it does have:
//   * world-space positions only — the DX9 pass forces D3DTS_WORLD to identity, and
//     this pipeline has no model matrix at all;
//   * per-vertex colour in D3DCOLOR 0xAARRGGBB, alpha included, Gouraud-interpolated;
//   * no depth write, no culling, no lighting and no alpha test;
//   * the blend pair that pass selects (SrcAlpha/One, its `alphaBlend = true`) plus
//     the straight SrcAlpha/OneMinusSrcAlpha the scene's opaque pass uses.
// The box/cross/ray helpers are new: there is no DX9 code to port them from, so their
// meaning is defined here and pinned by tests/debug_prims_geometry.cpp.
//
// Frame model: immediate mode, rebuilt from the caller's state each frame. The batch
// holds no clock and no accumulator, and vertex order is exactly the caller's line
// order — no sorting, no dedup, no unordered iteration — so two runs of the same frame
// upload byte-identical buffers. That is what the Linux/Wine capture A/B relies on
// (docs/BUILD-linux.md and BUILD-windows.md record the method and the observed hashes).
//
// The geometry half below is device-free on purpose: tests/debug_prims_geometry.cpp
// defines DEBUG_PRIMS_GEOMETRY_ONLY and compiles this header with no WebGPU headers,
// device or window, so vertex generation is unit-tested on the host.

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <vector>

#include <glm/glm.hpp>

#ifndef DEBUG_PRIMS_GEOMETRY_ONLY
#include <string>

#include <webgpu/webgpu.h>

#include "gpu/gpu.h"
#include "render/scene_renderer.h"   // render::Target, shared with the scene pass
#endif

namespace render {

// D3DCOLOR, unchanged: 0xAARRGGBB. Kept as the wire format because every colour a DX9
// call site passes to D3DFVF_DIFFUSE is already this value, so a ported call site
// transfers without swizzling, and because the shader can unpack it with shifts
// (endian-independent) rather than relying on a unorm8 byte order.
using DebugColor = uint32_t;

inline constexpr DebugColor packColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 0xff) {
    return ((DebugColor)a << 24) | ((DebugColor)r << 16) | ((DebugColor)g << 8) | (DebugColor)b;
}
inline constexpr uint8_t colorR(DebugColor c) { return (uint8_t)((c >> 16) & 0xffu); }
inline constexpr uint8_t colorG(DebugColor c) { return (uint8_t)((c >> 8) & 0xffu); }
inline constexpr uint8_t colorB(DebugColor c) { return (uint8_t)(c & 0xffu); }
inline constexpr uint8_t colorA(DebugColor c) { return (uint8_t)((c >> 24) & 0xffu); }

inline constexpr DebugColor kWhite   = 0xffffffffu;
inline constexpr DebugColor kRed     = 0xffff0000u;
inline constexpr DebugColor kGreen   = 0xff00ff00u;
inline constexpr DebugColor kBlue    = 0xff0000ffu;
inline constexpr DebugColor kYellow  = 0xffffff00u;
inline constexpr DebugColor kCyan    = 0xff00ffffu;
inline constexpr DebugColor kMagenta = 0xffff00ffu;

// 1:1 mirror of the vertex shader's unpack (shaders/debug_line_wgsl.h). The shader is
// what runs per vertex; this exists so CPU-side colour maths and the geometry test
// agree with it, and the two are pinned together by tests/debug_prims_geometry.cpp.
inline glm::vec4 unpackColor(DebugColor c) {
    return glm::vec4((float)colorR(c), (float)colorG(c), (float)colorB(c), (float)colorA(c)) /
           255.f;
}

// One segment, world space. It becomes two vertices, `a` then `b`.
struct DebugLine {
    glm::vec3  a{0.f};
    glm::vec3  b{0.f};
    DebugColor color = kWhite;
};

// GPU vertex: world position plus D3DCOLOR. Three f32 then the u32, 16 bytes, no
// padding — debug_prims.cpp asserts that layout, because a padded struct would upload
// uninitialised bytes and break byte-identical captures.
struct DebugVertex {
    glm::vec3  pos{0.f};
    DebugColor color = kWhite;
};

// A solid cube: 12 triangles, the DX9 pass's own vertex order (debug_prim.cpp:71-90),
// which is what the game draws for every shot, hit spark and hypermode aura. Kept in
// this header rather than a second pass class because it is the same pass in the DX9
// source — same shader, same states, only the primitive topology differs.
inline constexpr size_t kCubeVertices = 36;
inline constexpr size_t kCubeTriangles = 12;

// Half-extent `h`: the cube spans centre +/- h on every axis.
inline void buildCube(const glm::vec3& c, float h, DebugColor color, DebugVertex* out) {
    const float x0 = c.x - h, x1 = c.x + h;
    const float y0 = c.y - h, y1 = c.y + h;
    const float z0 = c.z - h, z1 = c.z + h;
    const DebugVertex v[kCubeVertices] = {
        {{x0, y0, z0}, color}, {{x0, y1, z0}, color}, {{x1, y1, z0}, color},
        {{x0, y0, z0}, color}, {{x1, y1, z0}, color}, {{x1, y0, z0}, color},
        {{x0, y0, z1}, color}, {{x1, y1, z1}, color}, {{x0, y1, z1}, color},
        {{x0, y0, z1}, color}, {{x1, y0, z1}, color}, {{x1, y1, z1}, color},
        {{x0, y0, z0}, color}, {{x0, y0, z1}, color}, {{x0, y1, z1}, color},
        {{x0, y0, z0}, color}, {{x0, y1, z1}, color}, {{x0, y1, z0}, color},
        {{x1, y0, z0}, color}, {{x1, y1, z1}, color}, {{x1, y0, z1}, color},
        {{x1, y0, z0}, color}, {{x1, y1, z0}, color}, {{x1, y1, z1}, color},
        {{x0, y1, z0}, color}, {{x0, y1, z1}, color}, {{x1, y1, z1}, color},
        {{x0, y1, z0}, color}, {{x1, y1, z1}, color}, {{x1, y1, z0}, color},
        {{x0, y0, z0}, color}, {{x1, y0, z1}, color}, {{x0, y0, z1}, color},
        {{x0, y0, z0}, color}, {{x1, y0, z0}, color}, {{x1, y0, z1}, color},
    };
    for (size_t i = 0; i < kCubeVertices; ++i) out[i] = v[i];
}

// Filled UV sphere: slices x stacks quads, two triangles each, so
// slices * stacks * 6 vertices. Vertex order is stack-major then slice-major and the
// surface point is
//   x = cx + r * sin(phi) * cos(theta),  y = cy + r * cos(phi),  z = cz + r * sin(phi) * sin(theta)
// with phi the stack angle (0 at the top pole) and theta the slice angle. Appending in
// that fixed order is what keeps the buffer byte-identical between runs. A pole row
// emits a degenerate triangle (two of its three vertices coincide): one wasted triangle
// per pole, in exchange for no branch in the inner loop.
inline void buildSphere(const glm::vec3& c, float r, DebugColor color, int slices,
                        int stacks, std::vector<DebugVertex>& out) {
    if (!(r > 0.f) || slices < 3 || stacks < 2) return;
    const float kPi = 3.14159265358979323846f;
    auto point = [&](int stack, int slice, glm::vec3& out3) {
        const float phi = kPi * static_cast<float>(stack) / static_cast<float>(stacks);
        const float theta = 2.0f * kPi * static_cast<float>(slice) / static_cast<float>(slices);
        const float sp = std::sin(phi);
        out3 = c + glm::vec3(r * sp * std::cos(theta), r * std::cos(phi),
                             r * sp * std::sin(theta));
    };
    glm::vec3 a00, a01, a10, a11;
    for (int st = 0; st < stacks; ++st) {
        for (int sl = 0; sl < slices; ++sl) {
            const int sl1 = (sl + 1) % slices;   // wraps so the seam closes
            point(st, sl, a00);
            point(st, sl1, a01);
            point(st + 1, sl, a10);
            point(st + 1, sl1, a11);
            out.push_back({{a00.x, a00.y, a00.z}, color});
            out.push_back({{a10.x, a10.y, a10.z}, color});
            out.push_back({{a11.x, a11.y, a11.z}, color});
            out.push_back({{a00.x, a00.y, a00.z}, color});
            out.push_back({{a11.x, a11.y, a11.z}, color});
            out.push_back({{a01.x, a01.y, a01.z}, color});
        }
    }
}

// A frame's worth of cubes, in submission order: no sorting, no dedup, so two runs of
// the same frame upload byte-identical buffers. `limit` is a constructor argument so
// the drop path stays testable on the host. A batch also takes spheres (addSphere), in
// the same layout and from the same fixed vertex order.
class CubeBatch {
public:
    explicit CubeBatch(size_t limit = 1024) : limit_(limit) {}
    void clear() { verts_.clear(); dropped_ = 0; }
    void add(const glm::vec3& center, float halfExtent, DebugColor color) {
        if (verts_.size() + kCubeVertices > limit_) {
            dropped_ += kCubeVertices;
            return;
        }
        DebugVertex v[kCubeVertices];
        buildCube(center, halfExtent, color, v);
        verts_.insert(verts_.end(), v, v + kCubeVertices);
    }
    // A FILLED sphere, so a translucent hit volume reads as a volume rather than as a
    // wireframe. Same pipeline and same alpha semantics as the cube: the caller passes a
    // colour whose alpha the blend consumes, and the geometry helper below emits the same
    // DebugVertex layout (position + packed D3DCOLOR), so nothing downstream changes.
    //
    // Why it lives here rather than in the line pass: DebugLineBatch is segments, which
    // cannot express a filled translucent shape. Reusing CubeBatch means one pipeline,
    // one blend mode and no new bind group for a debug view.
    //
    // `slices`/`stacks` are the tessellation; the defaults are deliberately coarse
    // because this is an overlay, and the vertex cost is (slices * stacks * 6).
    void addSphere(const glm::vec3& center, float radius, DebugColor color,
                   int slices = 12, int stacks = 8) {
        const size_t need = static_cast<size_t>(slices) * static_cast<size_t>(stacks) * 6;
        if (!(radius > 0.f) || slices < 3 || stacks < 2) return;
        if (verts_.size() + need > limit_) { dropped_ += need; return; }
        buildSphere(center, radius, color, slices, stacks, verts_);
    }
    const std::vector<DebugVertex>& vertices() const { return verts_; }
    size_t cubes() const { return verts_.size() / kCubeVertices; }
    size_t droppedVertices() const { return dropped_; }
    bool empty() const { return verts_.empty(); }
    size_t limit() const { return limit_; }

private:
    std::vector<DebugVertex> verts_;
    size_t                   limit_;
    size_t                   dropped_ = 0;
};

// ---- vertex generation (device-free) -------------------------------------------------

// Appends one segment: 2 vertices, `a` first.
inline void appendLine(std::vector<DebugVertex>& out, const glm::vec3& a, const glm::vec3& b,
                       DebugColor color = kWhite) {
    out.push_back(DebugVertex{a, color});
    out.push_back(DebugVertex{b, color});
}

// Appends an axis-aligned box outline: exactly 12 edges, 24 vertices. Corners come from
// per-axis min/max, so an inverted pair (hi < lo) still yields the same box; a
// degenerate one (lo == hi) yields 12 zero-length edges, which rasterise to nothing.
// Edge order is fixed: the four X-aligned edges, then the four Y-aligned, then the four
// Z-aligned, and within each group the other two axes run (lo,lo), (hi,lo), (lo,hi),
// (hi,hi).
inline void appendBox(std::vector<DebugVertex>& out, const glm::vec3& lo, const glm::vec3& hi,
                      DebugColor color = kWhite) {
    const glm::vec3 lo2 = glm::min(lo, hi);
    const glm::vec3 hi2 = glm::max(lo, hi);
    // Corner index bits: 1 = x high, 2 = y high, 4 = z high.
    glm::vec3 c[8];
    for (int i = 0; i < 8; ++i) {
        c[i] = glm::vec3((i & 1) ? hi2.x : lo2.x, (i & 2) ? hi2.y : lo2.y,
                         (i & 4) ? hi2.z : lo2.z);
    }
    static constexpr int kEdges[12][2] = {
        {0, 1}, {2, 3}, {4, 5}, {6, 7},   // along X
        {0, 2}, {1, 3}, {4, 6}, {5, 7},   // along Y
        {0, 4}, {1, 5}, {2, 6}, {3, 7},   // along Z
    };
    for (const int(&e)[2] : kEdges) appendLine(out, c[e[0]], c[e[1]], color);
}

// Appends an axis-aligned cross centred on `c`: 3 segments (X, then Y, then Z), 6
// vertices. `half` is the half extent of each arm, so the cross spans 2 * half.
inline void appendCross(std::vector<DebugVertex>& out, const glm::vec3& c, const glm::vec3& half,
                        DebugColor color = kWhite) {
    appendLine(out, c - glm::vec3(half.x, 0.f, 0.f), c + glm::vec3(half.x, 0.f, 0.f), color);
    appendLine(out, c - glm::vec3(0.f, half.y, 0.f), c + glm::vec3(0.f, half.y, 0.f), color);
    appendLine(out, c - glm::vec3(0.f, 0.f, half.z), c + glm::vec3(0.f, 0.f, half.z), color);
}

inline void appendCross(std::vector<DebugVertex>& out, const glm::vec3& c, float half,
                        DebugColor color = kWhite) {
    appendCross(out, c, glm::vec3(half), color);
}

// Whether appendRay would emit a segment. Kept separate so a counting caller can tell
// "degenerate ray, nothing asked for" from "over budget, dropped" without duplicating
// the predicate.
inline bool isRayDrawable(const glm::vec3& dir, float len) {
    const float sq = glm::dot(dir, dir);
    // Finite, positive length and a direction of finite non-zero magnitude. Every
    // comparison here is false for NaN, so a degenerate ray is skipped rather than
    // emitted as a NaN vertex — or, for an infinite component, as inf * 0.
    return std::isfinite(len) && len > 0.f && std::isfinite(sq) && sq > 0.f;
}

// Appends origin -> origin + dir * len, i.e. a raycast visualisation where `len` is the
// distance budget along `dir`. `dir` need not be normalised. A zero/NaN direction or a
// non-positive length appends nothing.
inline void appendRay(std::vector<DebugVertex>& out, const glm::vec3& origin,
                      const glm::vec3& dir, float len, DebugColor color = kWhite) {
    if (!isRayDrawable(dir, len)) return;
    const glm::vec3 tip = origin + dir * (len / glm::sqrt(glm::dot(dir, dir)));
    appendLine(out, origin, tip, color);
}

// Expands a line list. Each DebugLine is independent, so the output is exactly
// 2 * lines.size() vertices in order.
inline void appendLines(std::vector<DebugVertex>& out, const std::vector<DebugLine>& lines) {
    out.reserve(out.size() + lines.size() * 2);
    for (const DebugLine& l : lines) appendLine(out, l.a, l.b, l.color);
}

// Vertex accumulator with frame reuse. A debug overlay is rebuilt from the caller's
// state every frame; clear() drops the count but keeps the allocation, so steady state
// is one buffer that stops reallocating, and the growth that does happen is a plain
// geometric doubling — nothing here behaves differently for equal-sized frames.
//
// Overflow drops whole primitives and counts the vertices, exactly like ui::SpriteRenderer
// counts dropped quads: a debug overlay is diagnostics, and a silent partial box would
// be worse than a missing one. `limit` is a constructor argument so the drop path is
// testable at a size a test can afford.
class DebugLineBatch {
public:
    static constexpr size_t kDefaultLimit = 65536;   // 32768 lines

    explicit DebugLineBatch(size_t limit = kDefaultLimit) : limit_(limit) {}

    // Count = 0, capacity kept, drop counter reset: per-frame semantics.
    void clear() {
        verts_.clear();
        dropped_ = 0;
    }
    void reserve(size_t vertices) { verts_.reserve(vertices); }

    void line(const glm::vec3& a, const glm::vec3& b, DebugColor color = kWhite) {
        if (!fits(2)) return;
        appendLine(verts_, a, b, color);
    }
    void box(const glm::vec3& lo, const glm::vec3& hi, DebugColor color = kWhite) {
        if (!fits(24)) return;
        appendBox(verts_, lo, hi, color);
    }
    void cross(const glm::vec3& c, const glm::vec3& half, DebugColor color = kWhite) {
        if (!fits(6)) return;
        appendCross(verts_, c, half, color);
    }
    void cross(const glm::vec3& c, float half, DebugColor color = kWhite) {
        if (!fits(6)) return;
        appendCross(verts_, c, half, color);
    }
    void ray(const glm::vec3& origin, const glm::vec3& dir, float len,
             DebugColor color = kWhite) {
        if (!isRayDrawable(dir, len)) return;   // nothing asked for, nothing dropped
        if (!fits(2)) return;
        appendRay(verts_, origin, dir, len, color);
    }
    void append(const std::vector<DebugLine>& lines) {
        for (const DebugLine& l : lines) line(l.a, l.b, l.color);
    }

    const std::vector<DebugVertex>& vertices() const { return verts_; }
    size_t vertexCount() const { return verts_.size(); }
    size_t lineCount() const { return verts_.size() / 2; }
    size_t capacity() const { return verts_.capacity(); }
    size_t droppedVertices() const { return dropped_; }
    size_t limit() const { return limit_; }
    bool   empty() const { return verts_.empty(); }

private:
    bool fits(size_t vertices) {
        if (verts_.size() + vertices > limit_) {
            dropped_ += vertices;
            return false;
        }
        return true;
    }

    std::vector<DebugVertex> verts_;
    size_t                   limit_;
    size_t                   dropped_ = 0;
};

#ifndef DEBUG_PRIMS_GEOMETRY_ONLY

// Draws world-space line lists. Borrows device/queue from the context and owns
// everything it creates, with the same init/shutdown lifecycle as SceneRenderer and
// ui::SpriteRenderer.
//
// Submission is a second render pass on the caller's encoder, over the frame the scene
// pass already produced: color LoadOp is Load (never Clear — this pass annotates, it
// does not replace), and the depth attachment, when given, is loaded and stored
// unchanged. Lines never write depth, so an overlay cannot occlude the scene it is
// annotating.
class DebugPrims {
public:
    struct Options {
        // Depth-test against `depthView`. Ignored when no depth view is passed: the
        // pass then has no depth attachment at all and the lines draw over everything.
        bool depthTest = true;
        // false: SrcAlpha/OneMinusSrcAlpha, the scene's opaque-pass pair.
        // true:  SrcAlpha/One, the DX9 UnlitCubePass(alphaBlend = true) pair.
        bool additive = false;
        // The split-screen cell this pass draws into (issue #12). Empty — the default —
        // leaves the full-attachment viewport alone, so a single-view frame is
        // byte-identical to one drawn before the multi-view path existed.
        ViewportRect viewport{};
    };

    struct Stats {
        size_t lines = 0;            // segments the last submission drew
        size_t cubes = 0;            // cubes the last drawCubes submission drew
        size_t vertices = 0;         // == 2 * lines (or 36 * cubes), after any trim
        size_t droppedVertices = 0;  // trimmed by kMaxVertices, or reported by the batch
        size_t passes = 0;           // 1 when a pass was recorded, 0 when nothing was queued
    };

    // One uint32 draw call can address far more; this is a runaway guard, not a limit
    // anything real should reach.
    static constexpr size_t kMaxVertices = DebugLineBatch::kDefaultLimit;

    DebugPrims() = default;
    ~DebugPrims();
    DebugPrims(const DebugPrims&) = delete;
    DebugPrims& operator=(const DebugPrims&) = delete;

    bool init(const gpu::Context&, std::string& error);
    void shutdown();

    // The entry point. `viewProj` is the same matrix the scene pass received — the
    // lines are transformed by it alone. `depthView` is the scene pass's depth
    // attachment; pass null for an always-on-top overlay.
    bool draw(const Target&, const glm::mat4& viewProj, const std::vector<DebugLine>&,
              WGPUTextureView depthView, const Options&, std::string& error);
    bool draw(const Target&, const glm::mat4& viewProj, const DebugLineBatch&,
              WGPUTextureView depthView, const Options&, std::string& error);
    // The DX9 pass's other half: solid cubes, same shader and states, triangle topology.
    bool drawCubes(const Target&, const glm::mat4& viewProj, const CubeBatch&,
                   WGPUTextureView depthView, const Options&, std::string& error);

    // Overlay convenience: no depth attachment, default Options (straight alpha). It
    // takes no Options on purpose — a caller that wants additive or the depth test has
    // to say so explicitly through the six-argument form above, and cannot do it by
    // accident here. Present because a caller with no depth view wired yet still gets a
    // correct, visible overlay out of it.
    bool draw(const Target&, const glm::mat4& viewProj, const std::vector<DebugLine>&,
              std::string& error);
    bool draw(const Target&, const glm::mat4& viewProj, const DebugLineBatch&,
              std::string& error);

    // For callers that generated vertices with the append* helpers directly.
    bool drawVertices(const Target&, const glm::mat4& viewProj,
                      const std::vector<DebugVertex>&, WGPUTextureView depthView,
                      const Options&, std::string& error);

    const Stats& stats() const { return stats_; }

private:
    // All three are pipeline state, so each combination is its own pipeline (see
    // debug_prims.cpp). Named rather than a bare uint8_t because they are what selects
    // that pipeline: a 0/1 literal at the call site says nothing about which.
    enum DepthMode : uint8_t { kNoDepth = 0, kDepthTested = 1, kDepthAlways = 2 };
    // Straight alpha is the scene's opaque-pass pair; additive is the DX9
    // UnlitCubePass(alphaBlend = true) pair.
    enum BlendMode : uint8_t { kStraightAlpha = 0, kAdditive = 1 };
    enum Topology : uint8_t { kLineList = 0, kTriangleList = 1 };

    struct PipelineEntry {
        WGPUTextureFormat  format = WGPUTextureFormat_Undefined;
        DepthMode          depthMode = kNoDepth;
        BlendMode          blend = kStraightAlpha;
        Topology           topology = kLineList;
        WGPURenderPipeline pipeline = nullptr;
    };

    // The one pass both entry points below write: attachments, pipeline selection, the
    // vertex upload and the draw. `count` is already trimmed by the caller, and 0 means
    // "nothing to queue" — the frame is left untouched, but the device and target are
    // still validated, which is what the entry points' early returns used to do.
    bool drawBatch(const Target&, const glm::mat4& viewProj,
                   const std::vector<DebugVertex>& verts, size_t count,
                   WGPUTextureView depthView, const Options&, Topology, std::string& error);

    WGPURenderPipeline pipelineFor(WGPUTextureFormat, DepthMode depthMode, BlendMode blend,
                                   Topology topology, std::string& error);
    bool               ensureVertexBuffer(uint64_t bytes, std::string& error);

    WGPUDevice device_ = nullptr;   // borrowed
    WGPUQueue  queue_ = nullptr;    // borrowed

    WGPUShaderModule    shader_ = nullptr;
    WGPUBindGroupLayout bgl_ = nullptr;
    WGPUPipelineLayout  layout_ = nullptr;
    WGPUBindGroup       group_ = nullptr;
    WGPUBuffer          ubuf_ = nullptr;
    WGPUBuffer          vbuf_ = nullptr;
    uint64_t            vbufCapacity_ = 0;

    std::vector<PipelineEntry> pipelines_;   // created lazily, one per (format, mode, blend)
    DebugLineBatch             staging_;     // reused by the std::vector<DebugLine> forms
    Stats                      stats_{};
};

#endif  // DEBUG_PRIMS_GEOMETRY_ONLY

}  // namespace render
