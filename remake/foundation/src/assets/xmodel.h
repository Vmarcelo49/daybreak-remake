// xmodel.h — DirectX 9 ".x" loader + skeletal animation for WebGPU (wgpu-native).
//
// Single header, C++17, depends only on GLM.
//
//   #define XMODEL_IMPLEMENTATION   // in exactly ONE .cpp file, before including
//   #define XMODEL_WEBGPU           // optional: vertex-layout helpers (include webgpu.h first)
//   #include "xmodel.h"
//
// What you get:
//   * xm::Model       frames, meshes (GPU-ready vertex/index data), animation sets
//   * xm::Vertex      pos / normal / uv / color + 4 bone indices + 4 weights, 80 bytes
//   * xm::Controller  2-track animation blending (the D3DX controller subset the game uses)
//   * evalPose()      sample an animation -> one world matrix per frame
//   * buildPalette()  pose -> per-mesh skinning matrices, ready for a storage buffer
//
// Encodings — all three the game ships are read directly, no conversion step:
//   "xof 0303txt 0032"   text
//   "xof 0303bin 0032"   binary token stream (16-bit tokens; see BinaryToText below)
//   "xof 0303bzip0032"   MSZIP-compressed binary; inflated in memory, no dependencies
//   "xof 0302txt 0064"   older header (collision meshes); float size is honoured
//
// Format facts verified against the shipped assets (see tools/x2txt.py, the Python
// reference implementation this code was ported from, and tools/parse_corpus.*):
//   * Binary .x uses 16-bit tokens, not the 32-bit tokens the MSDN text implies.
//   * Binary files omit the standard template definitions (D3DX pre-registers
//     them), so the built-in table below is required to read them at all.
//   * Declared template members are flattened into INTEGER_LIST / REALNUM_LIST
//     runs; only undeclared children and "{ ref }" are real nested objects.
//   * MSZIP blocks are chained: each block's DEFLATE stream uses the previous
//     32 KB of output as its LZ77 dictionary, so blocks cannot be decoded in
//     isolation. The framing is  u32 total, then per block
//     u16 outSize, u16 compSize, "CK", deflate.
//
// Conventions (kept identical to DX9 so existing art and game data still work):
//   * LEFT-handed space, +Y up, triangles wound clockwise when viewed from the front.
//   * Matrices are stored row-vector in the file and transposed on load into GLM's
//     column-vector form, so you use them as  v' = M * v  and  world = parent * local.
//     No translation step is needed anywhere in the hierarchy or palette.
//   * Quaternion keys need NO conjugation; a plain (w,x,y,z) read reproduces the
//     matrix D3DX would build (GLM's mat3_cast is the transpose of D3DX's row-vector
//     form, which is exactly the column-vector equivalent). Kept switchable for A/B.
//   * UV origin is top-left, same as WebGPU -> no V flip needed.
//   * Feed the projection through unchanged (no proj[1][1] negation) and set
//     frontFace = "cw". Verified by rendering real assets offscreen, not assumed:
//     see tools/wgpu_smoke.cpp and model.wgsl.
//
// Not supported: N-patches, DeclData tangents (parsed and counted, not consumed),
// multi-UV sets, >4 influences per vertex (weakest are dropped and the rest
// renormalised; the shipped rigs stay within 4 — XSkinMeshHeader is captured so
// this can be asserted at load time).

#pragma once

#ifndef GLM_ENABLE_EXPERIMENTAL
#define GLM_ENABLE_EXPERIMENTAL
#endif
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

#include <algorithm>
#include <cstdint>
#include <string>
#include <vector>

namespace xm {

// ---------------------------------------------------------------------------------------
// Data model
// ---------------------------------------------------------------------------------------

// Note (issue #25): the secondary lighting normal and its generated shadow mask are NOT
// fields here. They ride a second vertex stream (NprVertex, declared below) precisely so
// this struct — and therefore every vertex stride, every buffer size and every byte the
// default path reads — stays exactly what it was. Adding a field here moved a pixel on the
// bind-pose capture the moment it was tried.
struct Vertex {
    glm::vec3  pos;
    glm::vec3  normal;
    glm::vec2  uv;
    glm::vec4  color{1.f};                 // MeshVertexColors, white when absent
    glm::uvec4 bones{0u, 0u, 0u, 0u};      // indices into Mesh::bones
    glm::vec4  weights{1.f, 0.f, 0.f, 0.f};
};

// Issue #25's secondary lighting normal, in its own vertex stream so the stream above is
// untouched: xyz is the coarser normal the shading reads, w the generated
// shadow-threshold bias in [0,1]. A mesh with no such stream binds a single zero vertex,
// which the shader reads as "no secondary normal" and falls back to the geometric one.
// Plain data, deliberately declared outside the WebGPU guard below: the device-free
// normals builder and its test need it with no webgpu.h in scope.
struct NprVertex {
    glm::vec4 npr{0.f};
};

struct Material {
    glm::vec4   diffuse{1.f};
    float       power = 0.f;
    glm::vec3   specular{0.f};
    glm::vec3   emissive{0.f};
    std::string texture;   // raw bytes as stored (Shift-JIS in the shipped assets)
    // Effect filename from a nested EffectInstance child, when the material has
    // one. Empty in every shipped asset (the template is defined 491x but never
    // instantiated); parsed so future/modded files do not silently lose it, and
    // so routing can key on it instead of the texture-name heuristic.
    std::string effectFile;
};

struct Submesh {           // one draw call: indices [firstIndex, firstIndex + indexCount)
    uint32_t firstIndex = 0;
    uint32_t indexCount = 0;
    int      material   = 0;
};

struct Bone {
    std::string name;
    int         frame  = -1;               // index into Model::frames, -1 if unresolved
    glm::mat4   offset{1.f};               // mesh space -> bone space (inverse bind)
};

struct SkinHeader {                        // XSkinMeshHeader, when the file has one
    bool present = false;
    int  maxWeightsPerVertex = 0;
    int  maxWeightsPerFace   = 0;
    int  bones               = 0;
};

struct Mesh {
    std::string           name;
    int                   frame = -1;      // frame this mesh hangs off, -1 = none
    bool                  skinned = false;
    std::vector<Vertex>   vertices;
    std::vector<uint32_t> indices;
    std::vector<Submesh>  submeshes;
    std::vector<Material> materials;
    std::vector<Bone>     bones;           // palette order; empty when !skinned
    SkinHeader            skinHeader;
    int                   droppedInfluences = 0;  // weights beyond the top 4
    bool                  hasVertexColors   = false;
};

struct Frame {
    std::string name;
    int         parent = -1;
    glm::mat4   bindLocal{1.f};
    // Bind pose split into T/R/S: channels that animate only some components keep
    // the rest from here, which is what D3DX does when a set has no key for them.
    glm::vec3   bindS{1.f};
    glm::vec3   bindT{0.f};
    glm::quat   bindR{1.f, 0.f, 0.f, 0.f};
};

template <class T> struct Key { float t; T v; };   // t in animation ticks

struct Channel {
    std::string                 frameName;
    int                         frame = -1;
    std::vector<Key<glm::quat>> rot;
    std::vector<Key<glm::vec3>> scale;
    std::vector<Key<glm::vec3>> pos;
    // Matrix keys (keyType 3/4) are decomposed into the SRT channels at load time so
    // every track blends in the same space; see the parser's normaliseAnimations().
};

struct AnimSet {
    std::string          name;
    float                duration = 0.f;   // ticks
    std::vector<Channel> channels;
};

struct LoadStats {
    std::string encoding;                  // "txt", "bin" or "bzip"
    int frames = 0, meshes = 0, materials = 0, animSets = 0, channels = 0;
    int rotKeys = 0, posKeys = 0, scaleKeys = 0, matrixKeys = 0;
    int vertices = 0, triangles = 0, submeshes = 0;
    int skinBones = 0, droppedInfluences = 0, maxInfluencesSeen = 0;
    int meshesWithVertexColors = 0;
    bool hadDeclData = false, hadVertexDuplication = false, hadEffectInstance = false;
    double convertMs = 0.0, parseMs = 0.0;  // binary -> text, then text -> Model
    std::string toString() const;
};

struct LoadOptions {
    // .x rotation keys are stored (w,x,y,z) and map straight onto glm::quat; see the
    // convention note at the top. Flip only if an A/B test says otherwise.
    bool conjugateQuats = false;

    // Used when the file has no AnimTicksPerSecond object. 4800 is the D3DX default.
    float ticksPerSecond = 4800.f;

    // When non-null, receives the text form produced for binary/MSZIP inputs
    // (empty for text inputs). Debugging aid; costs one extra copy.
    std::string* convertedTextOut = nullptr;
};

struct Model {
    std::vector<Frame>   frames;   // parents always come before children
    std::vector<Mesh>    meshes;
    std::vector<AnimSet> anims;
    float                ticksPerSecond = 4800.f;
    LoadStats            stats;

    int findFrame(const std::string& n) const;
    int findAnim(const std::string& n) const;
    int findMesh(const std::string& n) const;

    // Sample one animation (nullptr = bind pose) at `seconds` -> world matrix per frame.
    void evalPose(const AnimSet* anim, float seconds, bool loop,
                  std::vector<glm::mat4>& worldOut) const;

    // Skinning matrices for one mesh, ready to memcpy into a palette storage buffer.
    // Unskinned meshes get a single matrix: the frame's world transform.
    void buildPalette(const Mesh& m, const std::vector<glm::mat4>& world,
                      std::vector<glm::mat4>& out) const;

    // Total palette matrices over all meshes; use as the storage-buffer length.
    size_t paletteSize() const;
};

// ---------------------------------------------------------------------------------------
// Controller — the subset of ID3DXAnimationController the game actually drives.
//
// Each track plays one animation set with its own time, speed, weight and enable flag;
// a track that is disabled or has weight 0 contributes nothing. Per frame the enabled
// tracks are blended incrementally in track order:
//
//     value = mix(value, trackValue, trackWeight / (accumulatedWeight + trackWeight))
//
// which reduces to "track N wins" when it is the only weighted track, and gives a proper
// weighted average when several are active. Frames a track does not animate keep whatever
// the earlier tracks produced, so an upper-body overlay on track 1 leaves the legs from
// track 0 alone — the base/overlay split the original game relies on.
// ---------------------------------------------------------------------------------------
class Controller {
public:
    static constexpr int kMaxTracks = 8;

    void bind(const Model* m) { model_ = m; }
    const Model* model() const { return model_; }

    void  setTrackAnimationSet(int track, int animIndex);   // -1 clears the track
    int   trackAnimationSet(int track) const;
    void  setTrackEnable(int track, bool on);
    bool  trackEnable(int track) const;
    void  setTrackWeight(int track, float w);               // clamped to [0,1]
    float trackWeight(int track) const;
    void  setTrackSpeed(int track, float s);
    float trackSpeed(int track) const;
    void  setTrackPosition(int track, double seconds);
    double trackPosition(int track) const;
    void  setTrackLoop(int track, bool loop);
    bool  trackLoop(int track) const;

    bool setAnimation(int animIndex, bool loop = true);     // convenience: track 0 only

    // FUN_00421100: the original binds a move's phase[0] to BOTH tracks
    // (FUN_00421410(0, idx) and FUN_00421410(1, idx), weight 1.0 each). The
    // composite is a no-op until FUN_0041f580 cross-fades track 1 to a later
    // phase; this is the starting state every move begins in.
    bool setAnimationBothTracks(int animIndex, bool loop = true);

    void   advanceTime(float dt);                           // seconds, already scaled
    double time() const;                                    // longest active track time

    // Blended pose for the current time. Frames no enabled track touches stay at bind pose.
    void evalWorld(std::vector<glm::mat4>& worldOut) const;
    void evalLocal(std::vector<glm::vec3>& pos, std::vector<glm::quat>& rot,
                   std::vector<glm::vec3>& scale) const;

private:
    struct Track {
        int    anim   = -1;
        bool   enable = false;
        bool   loop   = true;
        float  weight = 0.f;
        float  speed  = 1.f;
        double time   = 0.0;
    };
    // Every track off, unweighted and rewound. anim/loop/speed deliberately survive:
    // setTrackEnable() can re-enable a track whose set was assigned earlier, and
    // setAnimation() must not silently retarget it.
    void resetTracks() {
        for (Track& t : tracks_) {
            t.enable = false;
            t.weight = 0.f;
            t.time = 0.0;
        }
    }
    // Installs `anim` as one track's whole state. Track{} replaces the previous
    // anim/loop/speed along with the play state, which is what makes the entry points a
    // "start this set" rather than a layer over whatever the track held.
    void initTrack(int i, int animIndex, bool loop) {
        tracks_[i] = Track{};
        tracks_[i].anim = animIndex;
        tracks_[i].enable = true;
        tracks_[i].weight = 1.f;
        tracks_[i].loop = loop;
    }
    bool valid(int t) const { return t >= 0 && t < kMaxTracks; }
    Track*       track(int t) { return valid(t) ? &tracks_[t] : nullptr; }
    const Track* track(int t) const { return valid(t) ? &tracks_[t] : nullptr; }

    const Model* model_ = nullptr;
    Track        tracks_[kMaxTracks];
};

// Throws std::runtime_error on failure. `data` is not retained.
Model loadMemory(const void* data, size_t size, const LoadOptions& opt = {});
Model loadMemory(const std::string& data, const LoadOptions& opt = {});
Model loadFile(const std::string& path, const LoadOptions& opt = {});

}  // namespace xm

// ---------------------------------------------------------------------------------------
// Optional WebGPU helpers. Define XMODEL_WEBGPU and include <webgpu/webgpu.h> first.
//
// Bind group contract expected by model.wgsl (the shader shipped next to this header):
//   group 0, binding 0  uniform Camera { mat4 viewProj; vec4 lightDir; vec4 lightColor; vec4 ambient; }
//   group 0, binding 1  texture_2d<f32>  (the toon ramp, issue #21)
//   group 0, binding 2  sampler
//   group 1, binding 0  uniform Draw   (dynamic offset; see DrawUniform below)
//   group 1, binding 1  storage readonly array<mat4x4<f32>, N>  (bone palettes)
//   group 2, binding 0  texture_2d<f32>
//   group 2, binding 1  sampler
// ---------------------------------------------------------------------------------------
#ifdef XMODEL_WEBGPU

#include <array>
#include <cstddef>

namespace xm {

inline constexpr uint64_t kVertexAttributeCount = 6;

// Per-draw uniform, 176 bytes of payload. Bound with a dynamic offset, so each record
// must start on a minUniformBufferOffsetAlignment boundary (256 on every current
// adapter) — see kDrawStride.
struct DrawUniform {
    glm::mat4 model{1.f};          // entity -> world; identity when the palette bakes it
    glm::vec4 baseColor{1.f};      // multiplies the material diffuse and vertex colour
    // The material's Emissive, alpha 1. This is the original's "MaterialColor" for the
    // toon effect (issue #21): the runtime material records are D3DXMATERIAL copies
    // (0x48 bytes, FUN_00661f60:116 memcpy), so the float4 the effect is handed at
    // material+0x30 is D3DMATERIAL9.Emissive, NOT the diffuse at +0x00 — the fixed-
    // function path's ambient is the diffuse (D3DX sets Ambient := Diffuse for .X
    // materials), which is why baseColor carries that term instead.
    glm::vec4 emissive{0.f, 0.f, 0.f, 1.f};
    // NPR experiment parameters (issue #25), one slot per experiment so a COMPOSED arm
    // (the issue's suggested D/E stack runs bands, key, rim and normals together) keeps
    // each one's own values. They shared one slot at first and the last writer won, which
    // silently turned the composed capture into a rim-only one. Everything here is zero on
    // an unmodified renderer, and the band thresholds are shader constants — see
    // model_wgsl.h — because they were fixed across the whole grid and a uniform that
    // never changes is a uniform that hides the values it was chosen for.
    glm::vec4 nprBand{0.f};   // rgb = shadow tint, w = softness (0 = the hard step, <0 = 3-band)
    glm::vec4 nprKey{0.f};    // xyz = character key direction, w = strength
    glm::vec4 nprRim{0.f};    // rgb = rim tint, w = strength
    glm::vec4 nprSpec{0.f};   // rgb = specular tint, w = strength
    // x = how much of the generated shadow mask (F) the band curve is allowed to read.
    // Its own slot rather than a bit, because 0 (the neutral arm) has to be expressible:
    // the mask is a separate hypothesis from the curve and must not ride along with it.
    glm::vec4 nprMask{0.f};
    uint32_t  paletteOffset = 0;   // first palette matrix for this mesh
    uint32_t  flags = 0;
    uint32_t  pad[2] = {0u, 0u};
};

inline constexpr uint32_t kDrawTextured  = 1u << 0;   // sample group 2
inline constexpr uint32_t kDrawUnlit     = 1u << 1;   // skip the lambert term
inline constexpr uint32_t kDrawAlphaTest = 1u << 2;   // discard alpha < 0.5
// Read the shipped toon ramp at the diffuse term instead of the linear N.L (issue #21).
// Set per frame by SceneRenderer::fillDrawData from the appearance switch, so the toggle
// needs no re-upload; with the bit clear the shader's lighting is the fixed-function term
// bit for bit, which is what keeps the banked captures still.
inline constexpr uint32_t kDrawToon      = 1u << 3;
// Draw the inverted-hull outline instead of the surface (issue #21): the vertex stage
// offsets the clip position along the world normal and the fragment stage returns the
// flat darkened material colour. A separate draw of the same mesh, as in the original.
inline constexpr uint32_t kDrawOutline   = 1u << 4;
// This draw samples the shadow map (issue #21 row 1): the original's stage technique
// (mode 3/4, FUN_00652af0) is the only one that reads the map's alpha, and the port's
// `stage` role is its stand-in. Set per frame by SceneRenderer::fillDrawData from the
// appearance switch, so the toggle needs no re-upload; with the bit clear (and the
// shadow pass off) the fragment stage's arithmetic is the pre-change one bit for bit.
inline constexpr uint32_t kDrawShadowReceiver = 1u << 10;

// ---------------------------------------------------------------------------------------
// NPR experiment bits (issue #25). These are the switches the experiment harness adds
// ON TOP of the recovered toon technique: each one is set per draw by
// SceneRenderer::fillDrawData from Appearance, so an experiment is a draw-time state
// change with no re-upload behind it. With all of them clear the fragment shader takes
// the same branch it took before this issue existed, which is what keeps every banked
// capture byte-identical. They are NOT part of the recovered technique and carry no RE
// provenance: see foundation/docs/NPR-EXPERIMENTS.md for what each one is.
// ---------------------------------------------------------------------------------------
// xyz = draw.nprBand.rgb as the shadow tint instead of a neutral-darkened diffuse; w =
// the band softness, 0 being the hard 2-band step.
inline constexpr uint32_t kDrawNprShadow = 1u << 5;
// Shade with the secondary lighting normal (the NprVertex stream's xyz) instead of the
// geometric one. Its w, the generated shadow mask, rides the toon coordinate's free
// component instead — it is not a switch of its own: the band experiment reads it.
inline constexpr uint32_t kDrawNprNormals = 1u << 6;
// Add a character key light on top of the recovered world light (the experiment's "world
// + weak character key" mode). The key is always a second term beside the world light,
// never a replacement, so the stage's own lighting keeps anchoring the silhouette.
inline constexpr uint32_t kDrawNprKey = 1u << 7;
// Stylized specular: a hard-threshold half-vector lobe tinted by draw.nprBand.rgb.
inline constexpr uint32_t kDrawNprSpec = 1u << 8;
// Character-only rim light: edge term tinted by draw.nprBand.rgb, scaled by draw.nprBand.w.
inline constexpr uint32_t kDrawNprRim = 1u << 9;
// (There is deliberately no bit for the outline-width experiment: the outline entry point
// reads draw.nprBand.w directly, so a bit that only ever meant "multiply by 1.0" would be
// a switch with nothing behind it.)

inline constexpr uint64_t kDrawStride = 256;          // == minUniformBufferOffsetAlignment

struct CameraUniform {
    // LH view * LH projection, used as-is: wgpu normalizes NDC to Y-up for every
    // backend, so unlike a raw Vulkan port there is NO proj[1][1] negation here.
    // Getting this wrong renders every model upside down; see tools/wgpu_smoke.cpp.
    glm::mat4 viewProj{1.f};
    glm::vec4 lightDir{0.f, -1.f, 0.f, 0.f};
    glm::vec4 lightColor{1.f};
    glm::vec4 ambient{0.25f};
    // Stage fog from env.dat: the original sets FOGTABLEMODE = LINEAR with these
    // start/end values and colour (FUN_00650a30), so this reproduces it exactly.
    glm::vec4 fogColor{0.f, 0.f, 0.f, 1.f};
    glm::vec4 fogParams{0.f, 0.f, 0.f, 0.f};   // x = start, y = end, z = enabled
    // Camera eye in world space (issue #25). The rim and stylized-specular experiments
    // need a view vector, and the viewProj alone cannot yield one; the renderer already
    // knows the eye (setEye, for effect-card billboarding) and now publishes it here too.
    // Nothing recovered reads it, so it changes no existing pixel.
    glm::vec4 eye{0.f, 0.f, 0.f, 1.f};
    // Character shadows (issue #21 row 1). `shadowViewProj` is the original's light
    // camera — FUN_006507c0:697-712 and :727-734 build it per view from a hardcoded eye
    // at (1000, 1e6, 5e5) looking at the frame camera's own eye — and `shadowParams` is
    // what the receiver's pixel shader needs from it: x = the recovered depth bias
    // (-0.02 in light NDC, effect_3's vs `c9.w`), y = the recovered depth clamp (0.95,
    // `c10.x`), z = 1 when the shadow pass ran for this view. z is 0 on every frame the
    // appearance does not ask for shadows, which is what keeps those frames' arithmetic
    // untouched. See foundation/docs/SHADOWS.md.
    glm::mat4 shadowViewProj{1.f};
    glm::vec4 shadowParams{0.f};
};

// The secondary lighting-normal stream's layout (issue #25, attribute location 6), or a
// null layout when a pipeline should not carry one. Returns by value so the caller owns
// the single-element attribute array the descriptor points at.
inline WGPUVertexBufferLayout wgpuNprVertexLayout(WGPUVertexAttribute (&attr)[1]) {
    attr[0].format = WGPUVertexFormat_Float32x4;
    attr[0].offset = 0;
    attr[0].shaderLocation = 6;
    WGPUVertexBufferLayout layout = {};
    layout.arrayStride = sizeof(NprVertex);
    layout.stepMode = WGPUVertexStepMode_Vertex;
    layout.attributeCount = 1;
    layout.attributes = attr;
    return layout;
}

// Fills `attrs` (which must hold kVertexAttributeCount entries) and returns a layout
// pointing at it. The array must outlive the pipeline-creation call.
inline WGPUVertexBufferLayout wgpuVertexLayout(WGPUVertexAttribute (&attrs)[kVertexAttributeCount]) {
    // Field-by-field: WGPUVertexAttribute has no aggregate-assignment in C++.
    struct Attr { WGPUVertexFormat format; uint64_t offset; uint32_t location; };
    const Attr spec[kVertexAttributeCount] = {
        {WGPUVertexFormat_Float32x3, offsetof(Vertex, pos),     0},
        {WGPUVertexFormat_Float32x3, offsetof(Vertex, normal),  1},
        {WGPUVertexFormat_Float32x2, offsetof(Vertex, uv),      2},
        {WGPUVertexFormat_Float32x4, offsetof(Vertex, color),   3},
        {WGPUVertexFormat_Uint32x4,  offsetof(Vertex, bones),   4},
        {WGPUVertexFormat_Float32x4, offsetof(Vertex, weights), 5},
    };
    for (uint64_t i = 0; i < kVertexAttributeCount; ++i) {
        attrs[i].format = spec[i].format;
        attrs[i].offset = spec[i].offset;
        attrs[i].shaderLocation = spec[i].location;
    }

    WGPUVertexBufferLayout layout = {};
    layout.arrayStride    = sizeof(Vertex);
    layout.stepMode       = WGPUVertexStepMode_Vertex;
    layout.attributeCount = kVertexAttributeCount;
    layout.attributes     = attrs;
    return layout;
}

}  // namespace xm

#endif  // XMODEL_WEBGPU

// =======================================================================================
// Implementation
// =======================================================================================
#ifdef XMODEL_IMPLEMENTATION
#ifndef XMODEL_IMPLEMENTATION_DONE
#define XMODEL_IMPLEMENTATION_DONE

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <map>
#include <stdexcept>
#include <unordered_map>

namespace xm {
namespace detail {

// ---------------------------------------------------------------------------------------
// Small helpers
// ---------------------------------------------------------------------------------------
uint16_t rd16(const uint8_t* p) { return (uint16_t)(p[0] | (p[1] << 8)); }
uint32_t rd32(const uint8_t* p) {
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

std::string trimNul(const std::string& s) {
    size_t z = s.find('\0');
    return z == std::string::npos ? s : s.substr(0, z);
}

// ---------------------------------------------------------------------------------------
// DEFLATE (RFC 1951) — enough to inflate MSZIP blocks, no dependencies.
//
// Classic bit-at-a-time Huffman decode, as in zlib's reference "puff" decompressor.
// Decoding appends to a caller-owned buffer that may already hold earlier data: MSZIP
// chains blocks through a shared 32 KB window, and a plain growing output vector makes
// those back-references resolve without any explicit dictionary bookkeeping.
// ---------------------------------------------------------------------------------------
class Inflater {
public:
    static constexpr int kMaxBits = 15;

    struct Huffman {
        short count[kMaxBits + 1];
        short symbol[288];
    };

    // Returns the number of input bytes consumed, or 0 on error. `out` is appended to.
    static size_t decode(const uint8_t* in, size_t len, std::vector<uint8_t>& out) {
        Inflater s(in, len, out);
        if (!s.loops()) return 0;
        // Whole bytes still buffered were read but never used; the stream is
        // self-terminating and byte aligned, so hand the leftover back.
        size_t consumed = s.inPos_ - (size_t)(s.bitCnt_ >> 3);
        return consumed > len ? 0 : consumed;
    }

private:
    Inflater(const uint8_t* in, size_t len, std::vector<uint8_t>& out)
        : in_(in), len_(len), out_(out) {}

    // -- bit reader
    int bits(int need) {
        long val = bitBuf_;
        while (bitCnt_ < need) {
            if (inPos_ >= len_) return -1;
            val |= (long)in_[inPos_++] << bitCnt_;
            bitCnt_ += 8;
        }
        bitBuf_ = (int)(val >> need);
        bitCnt_ -= need;
        return (int)(val & ((1L << need) - 1));
    }
    void alignByte() { bitBuf_ = 0; bitCnt_ = 0; }

    int decodeSym(const Huffman& h) {
        int len, code = 0, first = 0, index = 0;
        for (len = 1; len <= kMaxBits; len++) {
            int b = bits(1);
            if (b < 0) return -1;
            code |= b;
            int count = h.count[len];
            if (code - count < first) return h.symbol[index + (code - first)];
            index += count;
            first += count;
            first <<= 1;
            code <<= 1;
        }
        return -1;
    }

    static bool construct(Huffman& h, const uint8_t* lengths, int n) {
        for (int len = 0; len <= kMaxBits; len++) h.count[len] = 0;
        for (int sym = 0; sym < n; sym++) h.count[lengths[sym]]++;
        if (h.count[0] == n) return true;                 // no codes at all: legal
        int left = 1;
        for (int len = 1; len <= kMaxBits; len++) {
            left <<= 1;
            left -= h.count[len];
            if (left < 0) return false;                   // over-subscribed
        }
        short offs[kMaxBits + 2];
        offs[1] = 0;
        for (int len = 1; len < kMaxBits; len++) offs[len + 1] = (short)(offs[len] + h.count[len]);
        for (int sym = 0; sym < n; sym++)
            if (lengths[sym] != 0) h.symbol[offs[lengths[sym]]++] = (short)sym;
        return true;
    }

    bool put(int byte) { out_.push_back((uint8_t)byte); return true; }
    bool copy(int dist, int len) {
        if (dist <= 0 || (size_t)dist > out_.size()) return false;
        size_t from = out_.size() - (size_t)dist;
        for (int i = 0; i < len; ++i) {
            // Distinct byte first: push_back may reallocate and the source is inside
            // the very vector being grown (overlapping matches are legal in DEFLATE).
            const uint8_t b = out_[from + (size_t)i];
            out_.push_back(b);
        }
        return true;
    }

    bool stored() {
        alignByte();
        if (inPos_ + 4 > len_) return false;
        int len = in_[inPos_] | (in_[inPos_ + 1] << 8);
        int nlen = in_[inPos_ + 2] | (in_[inPos_ + 3] << 8);
        inPos_ += 4;
        if (nlen != (len ^ 0xffff)) return false;
        if (inPos_ + (size_t)len > len_) return false;
        for (int i = 0; i < len; ++i) out_.push_back(in_[inPos_++]);
        return true;
    }

    bool fixed(Huffman& lencode, Huffman& distcode) {
        uint8_t lengths[288];
        int sym = 0;
        for (; sym < 144; sym++) lengths[sym] = 8;
        for (; sym < 256; sym++) lengths[sym] = 9;
        for (; sym < 280; sym++) lengths[sym] = 7;
        for (; sym < 288; sym++) lengths[sym] = 8;
        if (!construct(lencode, lengths, 288)) return false;
        for (sym = 0; sym < 30; sym++) lengths[sym] = 5;
        return construct(distcode, lengths, 30);
    }

    bool dynamic(Huffman& lencode, Huffman& distcode) {
        static const short order[19] =
            {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
        int nlen = 0, ndist = 0, ncode = 0;
        int hlit = bits(5); if (hlit < 0) return false;
        int hdist = bits(5); if (hdist < 0) return false;
        int hclen = bits(4); if (hclen < 0) return false;
        nlen = hlit + 257;
        ndist = hdist + 1;
        ncode = hclen + 4;
        if (nlen > 286 || ndist > 30) return false;

        uint8_t lengths[320];
        std::memset(lengths, 0, sizeof(lengths));
        for (int i = 0; i < ncode; i++) {
            int v = bits(3);
            if (v < 0) return false;
            lengths[order[i]] = (uint8_t)v;
        }
        Huffman lencodeTmp;
        if (!construct(lencodeTmp, lengths, 19)) return false;

        int index = 0;
        while (index < nlen + ndist) {
            int sym = decodeSym(lencodeTmp);
            if (sym < 0) return false;
            if (sym < 16) {
                lengths[index++] = (uint8_t)sym;
            } else {
                int len = 0;
                if (sym == 16) {
                    if (index == 0) return false;
                    len = lengths[index - 1];
                    int n = bits(2); if (n < 0) return false;
                    sym = 3 + n;
                } else if (sym == 17) {
                    int n = bits(3); if (n < 0) return false;
                    sym = 3 + n;
                } else {
                    int n = bits(7); if (n < 0) return false;
                    sym = 11 + n;
                }
                if (index + sym > nlen + ndist) return false;
                while (sym--) lengths[index++] = (uint8_t)len;
            }
        }
        if (lengths[256] == 0) return false;   // no end-of-block code
        if (!construct(lencode, lengths, nlen)) return false;
        return construct(distcode, lengths + nlen, ndist);
    }

    bool codes(const Huffman& lencode, const Huffman& distcode) {
        static const short lens[29] =
            {3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31,
             35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258};
        static const short lext[29] =
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,
             3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0};
        static const short dists[30] =
            {1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193,
             257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145,
             8193, 12289, 16385, 24577};
        static const short dext[30] =
            {0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
             7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13};

        for (;;) {
            int sym = decodeSym(lencode);
            if (sym < 0) return false;
            if (sym < 256) {
                put(sym);
            } else if (sym == 256) {
                return true;
            } else {
                sym -= 257;
                if (sym >= 29) return false;
                int e = bits(lext[sym]); if (e < 0) return false;
                int len = lens[sym] + e;
                int dsym = decodeSym(distcode);
                if (dsym < 0 || dsym >= 30) return false;
                e = bits(dext[dsym]); if (e < 0) return false;
                if (!copy(dists[dsym] + e, len)) return false;
            }
        }
    }

    bool loops() {
        int last = 0;
        do {
            last = bits(1);
            if (last < 0) return false;
            int type = bits(2);
            if (type < 0) return false;
            Huffman lencode, distcode;
            if (type == 0) {
                if (!stored()) return false;
            } else if (type == 1) {
                if (!fixed(lencode, distcode)) return false;
                if (!codes(lencode, distcode)) return false;
            } else if (type == 2) {
                if (!dynamic(lencode, distcode)) return false;
                if (!codes(lencode, distcode)) return false;
            } else {
                return false;
            }
        } while (!last);
        return true;
    }

    const uint8_t*      in_;
    size_t              len_;
    std::vector<uint8_t>& out_;
    size_t              inPos_ = 0;
    int                 bitBuf_ = 0, bitCnt_ = 0;
};

// MSZIP: "xof 0303bzip0032", u32 total uncompressed size (including the 16-byte
// header), then blocks of [u16 outSize][u16 compSize]["CK"][deflate]. Blocks share a
// 32 KB window, so they decode into one continuous buffer.
bool decompressMSZip(const uint8_t* header16, const uint8_t* payload, size_t n,
                     std::vector<uint8_t>& out, std::string& err) {
    (void)header16;
    if (n < 4) { err = "bzip payload truncated"; return false; }
    size_t total = rd32(payload);
    if (total < 16) { err = "bzip size field too small"; return false; }
    size_t want = total - 16;
    out.clear();
    out.reserve(want);

    size_t pos = 4;
    int block = 0;
    while (out.size() < want) {
        if (pos + 4 > n) { err = "bzip block header truncated"; return false; }
        size_t blockOut  = rd16(payload + pos);
        size_t blockComp = rd16(payload + pos + 2);
        pos += 4;
        if (pos + 2 > n || payload[pos] != 'C' || payload[pos + 1] != 'K') {
            err = "bzip block " + std::to_string(block) + ": missing CK signature";
            return false;
        }
        pos += 2;
        size_t before = out.size();
        size_t used = Inflater::decode(payload + pos, n - pos, out);
        if (used == 0) { err = "bzip block " + std::to_string(block) + ": inflate failed"; return false; }
        if (used + 2 != blockComp) {
            err = "bzip block " + std::to_string(block) + ": compressed size " +
                  std::to_string(used + 2) + ", header says " + std::to_string(blockComp);
            return false;
        }
        if (out.size() - before != blockOut) {
            err = "bzip block " + std::to_string(block) + ": produced " +
                  std::to_string(out.size() - before) + " bytes, header says " +
                  std::to_string(blockOut);
            return false;
        }
        pos += used;
        ++block;
    }
    if (out.size() != want) { err = "bzip: decoded size mismatch"; return false; }
    return true;
}

// ---------------------------------------------------------------------------------------
// Binary token stream -> text
//
// The binary form is a tokenised text form: every declared template member is flattened
// into INTEGER_LIST / REALNUM_LIST runs, and only undeclared children and "{ ref }"
// appear as real objects. Emitting text and reusing the text parser keeps one build path
// (and gives a dumpable artefact when something looks wrong); the cost is one string
// per binary model, which is the price of not having two parsers to keep in sync.
// ---------------------------------------------------------------------------------------
enum BinToken : uint16_t {
    kName = 1, kString = 2, kInteger = 3, kGuid = 5, kIntList = 6, kFloatList = 7,
    kOBrace = 10, kCBrace = 11, kOParen = 12, kCParen = 13,
    kOBracket = 14, kCBracket = 15, kOAngle = 16, kCAngle = 17,
    kDot = 18, kComma = 19, kSemi = 20, kTemplate = 31,
    kWord = 40, kDword = 41, kFloat = 42, kDouble = 43,
    kChar = 44, kUchar = 45, kSword = 46, kSdword = 47,
    kVoid = 48, kLpstr = 49, kUnicode = 50, kCstring = 51, kArray = 52,
};

bool isPrimToken(uint16_t t) {
    return (t >= kWord && t <= kCstring);
}
bool isFloatToken(uint16_t t) { return t == kFloat || t == kDouble; }
bool isStringToken(uint16_t t) { return t == kLpstr || t == kUnicode || t == kCstring; }

const char* primTokenName(uint16_t t) {
    switch (t) {
        case kWord: return "WORD";      case kDword: return "DWORD";
        case kFloat: return "FLOAT";    case kDouble: return "DOUBLE";
        case kChar: return "CHAR";      case kUchar: return "UCHAR";
        case kSword: return "SWORD";    case kSdword: return "SDWORD";
        case kVoid: return "VOID";      case kLpstr: return "STRING";
        case kUnicode: return "UNICODE";case kCstring: return "CSTRING";
        default: return "?";
    }
}

class BinaryToText {
public:
    // Assets are shallow (frames, meshes, materials); anything deeper is corrupt and
    // must not be allowed to blow the stack.
    static constexpr int kMaxNesting = 64;

    BinaryToText(const uint8_t* data, size_t n, size_t start, bool float64)
        : d_(data), n_(n), p_(start), f64_(float64) {
        seedStandardTemplates();
    }

    std::string run() {
        while (p_ < n_) {
            size_t save = p_;
            uint16_t t = u16();
            if (failed_) break;
            p_ = save;
            if (t == kTemplate) {
                parseTemplate();
            } else if (t == kName || isPrimToken(t)) {
                object();
                out_ += '\n';
            } else {
                fail("unexpected top-level token " + std::to_string(t));
                break;
            }
        }
        return std::move(out_);
    }

    bool ok() const { return !failed_; }
    const std::string& error() const { return err_; }

private:
    // -- primitive readers
    uint16_t u16() {
        if (p_ + 2 > n_) { fail("truncated stream"); return 0; }
        uint16_t v = rd16(d_ + p_); p_ += 2; return v;
    }
    uint32_t u32() {
        if (p_ + 4 > n_) { fail("truncated stream"); return 0; }
        uint32_t v = rd32(d_ + p_); p_ += 4; return v;
    }
    std::string bytes(size_t n) {
        if (p_ + n > n_) { fail("truncated stream"); return {}; }
        std::string s((const char*)d_ + p_, n); p_ += n; return s;
    }
    // Consumes the NAME token itself.
    std::string readName() {
        uint16_t t = u16();
        if (t != kName) { fail("expected NAME token, got " + std::to_string(t)); return {}; }
        return nameBody();
    }
    // For the many places where the token was already peeked/consumed.
    std::string nameBody() { return bytes(u32()); }
    std::string readString() {
        uint16_t t = u16();
        if (t != kString) { fail("expected STRING token, got " + std::to_string(t)); return {}; }
        std::string s = bytes(u32());
        uint16_t term = u16();
        if (term != kComma && term != kSemi) fail("bad string terminator");
        return trimNul(s);
    }
    [[noreturn]] void fail(const std::string& msg) {
        failed_ = true;
        err_ = "binary .x at offset " + std::to_string(p_) + ": " + msg;
        throw std::runtime_error(err_);
    }

    // -- peeking
    // Reads the next token and puts it back unless it is `expected`. Every optional
    // token in this converter is read this way (a member's name, an object's instance
    // name, a GUID), and the save/restore pair written out at each site is exactly the
    // kind of thing a later edit gets wrong in one of them.
    bool tryToken(uint16_t expected) {
        const size_t save = p_;
        if (u16() == expected) return true;
        p_ = save;
        return false;
    }

    // -- templates
    struct Member {
        enum Kind { Prim, Array, Ref } kind = Prim;
        uint16_t    typeToken = 0;   // Prim; for arrays, 0 means element is a Ref
        std::string typeName;        // Ref / array-of-template element name
        std::string name;
        bool        elemIsRef = false;
        std::vector<int32_t>     dimConst;
        std::vector<std::string> dimName;
    };
    struct Template { std::string name; std::vector<Member> members; };

    Member parseMember(uint16_t t) {
        Member m;
        if (t == kArray) {
            m.kind = Member::Array;
            uint16_t et = u16();
            if (isPrimToken(et)) {
                m.typeToken = et; m.typeName = primTokenName(et); m.elemIsRef = false;
            } else if (et == kName) {
                m.typeName = nameBody(); m.elemIsRef = true;
            } else {
                fail("bad array element type " + std::to_string(et));
            }
            m.name = readName();
            for (;;) {
                uint16_t u = u16();
                if (u == kSemi) break;
                if (u != kOBracket) fail("bad array dimension token " + std::to_string(u));
                uint16_t dt = u16();
                if (dt == kInteger) m.dimConst.push_back((int32_t)u32());
                else if (dt == kName) m.dimName.push_back(nameBody());
                else fail("bad dimension token " + std::to_string(dt));
                if (u16() != kCBracket) fail("expected CBRACKET");
            }
            return m;
        }
        if (isPrimToken(t)) {
            m.kind = Member::Prim; m.typeToken = t; m.typeName = primTokenName(t);
            if (tryToken(kName)) m.name = nameBody();
            if (u16() != kSemi) fail("expected SEMICOLON after primitive member");
            return m;
        }
        if (t == kName) {
            m.kind = Member::Ref; m.typeName = nameBody();
            if (tryToken(kName)) m.name = nameBody();
            if (u16() != kSemi) fail("expected SEMICOLON after template member");
            return m;
        }
        fail("bad member token " + std::to_string(t));
    }

    void parseTemplate() {
        uint16_t t = u16();
        if (t != kTemplate) fail("expected TEMPLATE token");
        Template tpl;
        tpl.name = readName();
        if (u16() != kOBrace) fail("expected OBRACE in template");
        if (u16() != kGuid) fail("expected GUID in template");
        bytes(16);
        for (;;) {
            uint16_t mt = u16();
            if (mt == kCBrace) break;
            if (mt == kOBracket) {                 // [ ... ] open/restricted marker
                int depth = 1;
                while (depth) {
                    uint16_t u = u16();
                    if (u == kOBracket) ++depth;
                    else if (u == kCBracket) --depth;
                }
                continue;
            }
            tpl.members.push_back(parseMember(mt));
        }
        templates_[tpl.name] = std::move(tpl);
    }

    // -- number cursor: pulls from INTEGER_LIST / REALNUM_LIST runs, refilling when the
    //    run is exhausted or the requested kind changes (the writer never mixes kinds).
    struct Cursor {
        explicit Cursor(BinaryToText* owner) : c(owner) {}
        BinaryToText* c;
        std::vector<double> items;
        bool isFloat = false, valid = false;
        size_t i = 0;

        void refill(bool wantFloat) {
            if (valid && i < items.size())
                c->fail("number list kind mismatch (wanted " +
                        std::string(wantFloat ? "float" : "int") + ")");
            uint16_t t = c->u16();
            if (t != kIntList && t != kFloatList)
                c->fail("expected number list, got token " + std::to_string(t));
            uint32_t cnt = c->u32();
            // Bound the count against the untouched input before allocating: a corrupt
            // length field would otherwise ask for gigabytes before any check runs.
            const size_t perItem = (t == kFloatList && c->f64_) ? 8 : 4;
            if ((size_t)cnt * perItem > c->n_ - c->p_) c->fail("number list longer than input");
            items.clear();
            items.resize(cnt);
            if (t == kFloatList) {
                if (c->f64_) {
                    if (c->p_ + (size_t)cnt * 8 > c->n_) c->fail("truncated float list");
                    for (uint32_t k = 0; k < cnt; ++k) {
                        double v; uint64_t bits = (uint64_t)rd32(c->d_ + c->p_) |
                                                  ((uint64_t)rd32(c->d_ + c->p_ + 4) << 32);
                        std::memcpy(&v, &bits, 8); c->p_ += 8; items[k] = v;
                    }
                } else {
                    if (c->p_ + (size_t)cnt * 4 > c->n_) c->fail("truncated float list");
                    for (uint32_t k = 0; k < cnt; ++k) {
                        uint32_t bits = rd32(c->d_ + c->p_); c->p_ += 4;
                        float f; std::memcpy(&f, &bits, 4); items[k] = (double)f;
                    }
                }
                isFloat = true;
            } else {
                if (c->p_ + (size_t)cnt * 4 > c->n_) c->fail("truncated integer list");
                for (uint32_t k = 0; k < cnt; ++k) {
                    items[k] = (double)(int32_t)rd32(c->d_ + c->p_); c->p_ += 4;
                }
                isFloat = false;
            }
            valid = true;
            i = 0;
        }
        double num(bool wantFloat) {
            if (!valid || i >= items.size() || isFloat != wantFloat) refill(wantFloat);
            return items[i++];
        }
        bool drained() const { return !valid || i >= items.size(); }
    };

    // -- output helpers
    void nl() { out_ += '\n'; out_.append((size_t)depth_ * 2, ' '); }
    void emitFloat(double v) {
        char buf[40];
        if (v == (long long)v && std::fabs(v) < 1e15) {
            std::snprintf(buf, sizeof buf, "%lld", (long long)v);
        } else {
            std::snprintf(buf, sizeof buf, "%.9g", v);
        }
        out_ += buf;
    }
    // Names in the binary data can contain anything, including '{', '}' and spaces
    // (the shipped rigs have frames named "_{_f_B" and "_X_J_[_g"). Emitting such a
    // name bare would desynchronise the text parser, so quote when it is not a plain
    // identifier. The lexer returns quoted content verbatim as a single token.
    static bool nameNeedsQuotes(const std::string& s) {
        if (s.empty()) return true;
        for (unsigned char c : s) {
            if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == ';' || c == ',' ||
                c == '{' || c == '}' || c == '"' || c >= 0x80) return true;
        }
        return false;
    }
    void emitNameToken(const std::string& s) {
        if (nameNeedsQuotes(s)) emitString(s);
        else out_ += s;
    }

    void emitString(const std::string& raw) {
        // Always quoted: a CP932 trail byte can be '{', '}' or ';'.
        out_ += '"';
        for (char ch : raw) {
            if (ch == '"' || ch == '\\') out_ += '\\';
            out_ += ch;
        }
        out_ += '"';
    }

    // -- objects
    void object() {
        uint16_t t = u16();
        std::string tpl;
        if (t == kName) tpl = nameBody();
        else if (isPrimToken(t)) tpl = primTokenName(t);
        else fail("bad object identifier token " + std::to_string(t));

        std::string inst;
        if (tryToken(kName)) inst = nameBody();

        if (u16() != kOBrace) fail("expected OBRACE for object " + tpl);
        if (tryToken(kGuid)) bytes(16);

        out_ += tpl;
        // Instance names only matter for objects the parser looks up by name; keeping
        // them everywhere would turn "MeshNormals Foo" into a header the parser cannot
        // match against its known child names.
        if (!inst.empty() &&
            (tpl == "Frame" || tpl == "Mesh" || tpl == "Material" ||
             tpl == "AnimationSet" || tpl == "Animation")) {
            out_ += ' ';
            emitNameToken(inst);
        }
        out_ += " {";
        ++depth_;

        if (depth_ >= kMaxNesting) fail("object nesting too deep");
        auto it = templates_.find(tpl);
        if (it == templates_.end()) fail("object of unknown template " + tpl);

        // Member dimensions resolve against the object's own members (and, for nested
        // refs, the enclosing ones), so each object gets a fresh scope chain.
        std::vector<std::map<std::string, double>> savedScopes;
        savedScopes.swap(scopes_);
        scopes_.emplace_back();
        for (const Member& m : it->second.members) {
            nl();
            readMember(m);
        }
        readChildren();
        scopes_.clear();
        scopes_.swap(savedScopes);

        --depth_;
        nl();
        out_ += '}';
    }

    void readChildren() {
        for (;;) {
            if (tryToken(kCBrace)) return;
            if (tryToken(kOBrace)) {                   // { Name }
                if (u16() != kName) fail("bad data reference");
                std::string ref = nameBody();
                if (tryToken(kGuid)) bytes(16);
                if (u16() != kCBrace) fail("bad data reference end");
                nl();
                out_ += "{ ";
                emitNameToken(ref);
                out_ += " }";
                continue;
            }
            nl();
            object();
        }
    }

    // -- member values
    void readMember(const Member& m) {
        if (m.kind == Member::Prim) {
            if (isStringToken(m.typeToken)) {
                if (!cur_.drained()) fail("pending numbers before string member");
                emitString(readString());
                out_ += ';';
                return;
            }
            double v = cur_.num(isFloatToken(m.typeToken));
            if (!m.name.empty()) scopes_.back()[m.name] = v;
            emitFloat(v);
            out_ += ';';
            return;
        }
        if (m.kind == Member::Array) {
            size_t count = resolveCount(m);
            for (size_t i = 0; i < count; ++i) {
                if (i) out_ += ',';
                if (m.elemIsRef) readRef(m.typeName);
                else emitFloat(cur_.num(isFloatToken(m.typeToken)));
            }
            out_ += ';';
            return;
        }
        readRef(m.typeName);
    }

    void readRef(const std::string& typeName) {
        auto it = templates_.find(typeName);
        if (it == templates_.end()) fail("unknown member template " + typeName);
        scopes_.emplace_back();
        for (const Member& m : it->second.members) readMember(m);
        scopes_.pop_back();
    }

    size_t resolveCount(const Member& m) {
        size_t n = 1;
        for (int32_t c : m.dimConst) n *= (size_t)c;
        for (const std::string& d : m.dimName) {
            bool found = false;
            for (auto s = scopes_.rbegin(); s != scopes_.rend() && !found; ++s) {
                auto v = s->find(d);
                if (v != s->end()) { n *= (size_t)v->second; found = true; }
            }
            if (!found) fail("unresolved dimension '" + d + "' for member " + m.name);
        }
        return n;
    }

    // D3DX pre-registers the standard templates and its binary writer therefore omits
    // their definitions, so a reader that only trusts in-file templates cannot resolve
    // "Frame" or "Mesh" at all. In-file definitions (mesh extensions such as SkinWeights
    // and the effect templates) are parsed later and override these.
    void seedStandardTemplates() {
        auto prim = [](uint16_t t, const char* nm) {
            Member m; m.kind = Member::Prim; m.typeToken = t;
            m.typeName = primTokenName(t); m.name = nm; return m;
        };
        auto arrN = [](uint16_t t, const char* nm, int32_t n) {
            Member m; m.kind = Member::Array; m.typeToken = t;
            m.typeName = primTokenName(t); m.name = nm; m.dimConst = {n}; return m;
        };
        auto arrP = [](uint16_t t, const char* nm, const char* countMember) {
            Member m; m.kind = Member::Array; m.typeToken = t;
            m.typeName = primTokenName(t); m.name = nm; m.dimName = {countMember}; return m;
        };
        auto arrR = [](const char* elem, const char* nm, const char* countMember) {
            Member m; m.kind = Member::Array; m.elemIsRef = true;
            m.typeName = elem; m.name = nm; m.dimName = {countMember}; return m;
        };
        auto ref = [](const char* tn, const char* nm) {
            Member m; m.kind = Member::Ref; m.typeName = tn; m.name = nm; return m;
        };
        auto def = [&](const char* name, std::vector<Member> members) {
            Template t; t.name = name; t.members = std::move(members);
            templates_[t.name] = std::move(t);
        };

        def("Header", {prim(kWord, "major"), prim(kWord, "minor"), prim(kDword, "flags")});
        def("Vector", {prim(kFloat, "x"), prim(kFloat, "y"), prim(kFloat, "z")});
        def("Coords2d", {prim(kFloat, "u"), prim(kFloat, "v")});
        def("Quaternion", {prim(kFloat, "s"), ref("Vector", "v")});
        def("Matrix4x4", {arrN(kFloat, "matrix", 16)});
        def("ColorRGBA", {prim(kFloat, "red"), prim(kFloat, "green"),
                          prim(kFloat, "blue"), prim(kFloat, "alpha")});
        def("ColorRGB", {prim(kFloat, "red"), prim(kFloat, "green"), prim(kFloat, "blue")});
        def("IndexedColor", {prim(kDword, "index"), ref("ColorRGBA", "indexColor")});
        def("Boolean", {prim(kWord, "truefalse")});
        def("Boolean2d", {ref("Boolean", "u"), ref("Boolean", "v")});
        def("Material", {ref("ColorRGBA", "faceColor"), prim(kFloat, "power"),
                         ref("ColorRGB", "specularColor"), ref("ColorRGB", "emissiveColor")});
        def("TextureFilename", {prim(kLpstr, "filename")});
        def("MeshFace", {prim(kDword, "nFaceVertexIndices"),
                         arrP(kDword, "faceVertexIndices", "nFaceVertexIndices")});
        def("MeshFaceWraps", {prim(kDword, "nFaceWrapValues"),
                              arrR("Boolean2d", "faceWrapValues", "nFaceWrapValues")});
        def("MeshTextureCoords", {prim(kDword, "nTextureCoords"),
                                  arrR("Coords2d", "textureCoords", "nTextureCoords")});
        def("MeshNormals", {prim(kDword, "nNormals"),
                            arrR("Vector", "normals", "nNormals"),
                            prim(kDword, "nFaceNormals"),
                            arrR("MeshFace", "faceNormals", "nFaceNormals")});
        def("MeshVertexColors", {prim(kDword, "nVertexColors"),
                                 arrR("IndexedColor", "vertexColors", "nVertexColors")});
        def("MeshMaterialList", {prim(kDword, "nMaterials"), prim(kDword, "nFaceIndexes"),
                                 arrP(kDword, "faceIndexes", "nFaceIndexes")});
        def("Mesh", {prim(kDword, "nVertices"), arrR("Vector", "vertices", "nVertices"),
                     prim(kDword, "nFaces"), arrR("MeshFace", "faces", "nFaces")});
        def("FrameTransformMatrix", {ref("Matrix4x4", "frameMatrix")});
        def("Frame", {});
        def("AnimTicksPerSecond", {prim(kDword, "AnimTicksPerSecond")});
        def("FloatKeys", {prim(kDword, "nValues"), arrP(kFloat, "values", "nValues")});
        def("TimedFloatKeys", {prim(kDword, "time"), ref("FloatKeys", "tfkeys")});
        def("AnimationKey", {prim(kDword, "keyType"), prim(kDword, "nKeys"),
                             arrR("TimedFloatKeys", "keys", "nKeys")});
        def("AnimationOptions", {prim(kDword, "openclosed"), prim(kDword, "positionquality")});
        def("Animation", {});
        def("AnimationSet", {});
        def("VertexElement", {prim(kDword, "Type"), prim(kDword, "Method"),
                              prim(kDword, "Usage"), prim(kDword, "UsageIndex")});
        def("DeclData", {prim(kDword, "nElements"),
                         arrR("VertexElement", "Elements", "nElements"),
                         prim(kDword, "nDWords"), arrP(kDword, "data", "nDWords")});
        def("XSkinMeshHeader", {prim(kWord, "nMaxSkinWeightsPerVertex"),
                                prim(kWord, "nMaxSkinWeightsPerFace"),
                                prim(kWord, "nBones")});
        def("VertexDuplicationIndices", {prim(kDword, "nIndices"),
                                         prim(kDword, "nOriginalVertices"),
                                         arrP(kDword, "indices", "nIndices")});
        def("SkinWeights", {prim(kLpstr, "transformNodeName"), prim(kDword, "nWeights"),
                            arrP(kDword, "vertexIndices", "nWeights"),
                            arrP(kFloat, "weights", "nWeights"),
                            ref("Matrix4x4", "matrixOffset")});
        // Seen in the shipped stage files rather than assumed:
        def("FVFData", {prim(kDword, "dwFVF"), prim(kDword, "nDWords"),
                        arrP(kDword, "data", "nDWords")});
        def("EffectInstance", {prim(kLpstr, "EffectFilename")});
    }

    const uint8_t* d_;
    size_t         n_, p_;
    bool           f64_;
    bool           failed_ = false;
    std::string    err_;
    std::string    out_;
    int            depth_ = 0;
    Cursor         cur_{this};
    std::map<std::string, Template> templates_;
    std::vector<std::map<std::string, double>> scopes_;
};

// ---------------------------------------------------------------------------------------
// Text lexer. Whitespace, ';' and ',' are all separators; that is all the numeric data
// needs, and it makes the tokeniser insensitive to the punctuation differences between
// D3DX-written text files and the text this loader generates for binary ones.
// ---------------------------------------------------------------------------------------
class Lexer {
public:
    explicit Lexer(const std::string& s, size_t start = 0) : src_(s), p_(start) {}

    const std::string& peek() {
        if (!has_) { has_ = read(buf_); if (!has_) buf_.clear(); }
        return buf_;
    }
    std::string next() {
        std::string t;
        if (has_) {
            t = std::move(buf_);
            has_ = false;
            if (t.empty() && eof_) fail("unexpected end of file");
            return t;
        }
        if (!read(t)) fail("unexpected end of file");
        return t;
    }
    bool eof() { peek(); return eof_ && !has_; }
    bool lastQuoted() const { return quoted_; }

    float     F() { return std::strtof(next().c_str(), nullptr); }
    int       I() { return (int)std::strtol(next().c_str(), nullptr, 10); }
    glm::vec2 V2() { float x = F(), y = F(); return {x, y}; }
    glm::vec3 V3() { float x = F(), y = F(), z = F(); return {x, y, z}; }
    glm::mat4 M4() {
        glm::mat4 m;
        float* f = &m[0][0];
        for (int i = 0; i < 16; ++i) f[i] = F();
        return m;
    }

    [[noreturn]] void fail(const std::string& msg) const {
        size_t line = 1;
        for (size_t i = 0; i < p_ && i < src_.size(); ++i) if (src_[i] == '\n') ++line;
        throw std::runtime_error("x-file parse error (line " + std::to_string(line) + "): " + msg);
    }

private:
    bool read(std::string& out) {
        out.clear();
        quoted_ = false;
        for (;;) {
            while (p_ < src_.size()) {
                char c = src_[p_];
                if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == ';' || c == ',') ++p_;
                else break;
            }
            if (p_ >= src_.size()) { eof_ = true; return false; }
            char c = src_[p_];
            if (c == '#' || (c == '/' && p_ + 1 < src_.size() && src_[p_ + 1] == '/')) {
                while (p_ < src_.size() && src_[p_] != '\n') ++p_;
                continue;
            }
            if (c == '{' || c == '}') { out = std::string(1, c); ++p_; return true; }
            if (c == '"') {
                ++p_;
                while (p_ < src_.size() && src_[p_] != '"') {
                    if (src_[p_] == '\\' && p_ + 1 < src_.size() && src_[p_ + 1] == '"') ++p_;
                    out += src_[p_++];
                }
                if (p_ < src_.size()) ++p_;
                quoted_ = true;
                return true;
            }
            while (p_ < src_.size()) {
                c = src_[p_];
                if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == ';' || c == ',' ||
                    c == '{' || c == '}' || c == '"') break;
                out += c; ++p_;
            }
            return true;
        }
    }

    const std::string& src_;
    size_t             p_;
    std::string        buf_;
    bool               has_ = false, eof_ = false, quoted_ = false;
};

// ---------------------------------------------------------------------------------------
// Text -> Model
// ---------------------------------------------------------------------------------------
struct RawSkin {
    std::string           bone;
    std::vector<uint32_t> idx;
    std::vector<float>    w;
    glm::mat4             offset{1.f};
};

struct RawMesh {
    std::string                        name;
    int                                frame = -1;
    std::vector<glm::vec3>             pos;
    std::vector<std::vector<uint32_t>> faces;
    std::vector<glm::vec3>             normals;
    std::vector<std::vector<uint32_t>> nfaces;
    std::vector<glm::vec2>             uvs;
    std::vector<glm::vec4>             colors;    // per position index
    std::vector<uint32_t>              faceMat;
    std::vector<Material>              mats;
    std::vector<RawSkin>               skins;
    SkinHeader                         skinHeader;
};

template <class T, class L>
T sampleKeys(const std::vector<Key<T>>& k, float t, L lerp) {
    if (k.empty()) return T{};
    if (t <= k.front().t || k.size() == 1) return k.front().v;
    if (t >= k.back().t) return k.back().v;
    auto hi = std::upper_bound(k.begin(), k.end(), t,
                               [](float tt, const Key<T>& a) { return tt < a.t; });
    auto lo = hi - 1;
    float span = hi->t - lo->t;
    float a = span > 0 ? (t - lo->t) / span : 0.f;
    return lerp(lo->v, hi->v, a);
}

class Parser {
public:
    Parser(Lexer& lx, Model& m, const LoadOptions& o) : lx_(lx), m_(m), opt_(o) {}

    void run() {
        while (!lx_.eof()) {
            std::string t = lx_.next();
            if (t == "template")                  { header(); skipBody(); }
            else if (t == "Frame")                { parseFrame(-1); }
            else if (t == "Mesh")                 { parseMesh(-1); }
            else if (t == "Material")             { Material mt; std::string n = header(); readMaterialBody(mt); if (!n.empty()) named_[n] = mt; }
            else if (t == "AnimTicksPerSecond")   { header(); m_.ticksPerSecond = (float)lx_.I(); skipBody(); }
            else if (t == "AnimationSet")         { parseAnimSet(); }
            else if (t == "EffectInstance" || t == "DeclData" || t == "FVFData") {
                if (t == "DeclData") m_.stats.hadDeclData = true;
                if (t == "EffectInstance") m_.stats.hadEffectInstance = true;
                header(); skipBody();
            }
            else                                  { header(); skipBody(); }
        }
        finish();
    }

private:
    // Reads an optional (possibly multi-word) name up to and including '{'.
    std::string header() {
        std::string name;
        for (;;) {
            std::string t = lx_.next();
            if (t == "{") break;
            if (!name.empty()) name += ' ';
            name += t;
        }
        return name;
    }
    void skipBody() {
        int depth = 1;
        while (depth > 0) {
            std::string t = lx_.next();
            if (t == "{") ++depth;
            else if (t == "}") --depth;
        }
    }
    // onObj(t) must consume the child's header itself and return true if it handled it.
    void children(const std::function<bool(const std::string&)>& onObj,
                  const std::function<void(const std::string&)>& onRef = {}) {
        // Every nesting level in the text form funnels through here, so one guard
        // bounds the recursion for frames and meshes alike. RAII so a parse error
        // thrown from deeper down still unwinds the counter.
        struct DepthGuard {
            int& d;
            explicit DepthGuard(int& depth) : d(depth) { ++d; }
            ~DepthGuard() { --d; }
        } guard(depth_);
        if (depth_ > kMaxNesting) lx_.fail("nesting too deep");
        for (;;) {
            std::string t = lx_.next();
            if (t == "}") return;
            if (t == "{") {
                std::string r, w;
                while ((w = lx_.next()) != "}") r += (r.empty() ? "" : " ") + w;
                if (onRef) onRef(r);
                continue;
            }
            if (!(onObj && onObj(t))) { header(); skipBody(); }
        }
    }
    void skipRest() { children({}, {}); }

    // The cap on every element count this parser reads. A count is a claim about how many
    // elements follow it, and each element costs a 12-to-16-byte vector slot, so a
    // corrupt (or hostile) count of two billion is a one-line way to ask for tens of
    // gigabytes. 2^26 elements is two orders of magnitude past anything the shipped
    // assets use and still an allocation the host can refuse rather than die on.
    static constexpr int kMaxElements = 1 << 26;

    // The one guard for those counts. `max` is per-site because some counts are arities,
    // not element lists, and are bounded far tighter; the message is the caller's so a
    // failure still names the object it came from.
    int readCount(const char* what, int max = kMaxElements) {
        const int n = lx_.I();
        if (n < 0 || n > max) lx_.fail(std::string(what) + " out of range");
        return n;
    }

    void parseFrame(int parent) {
        Frame f;
        f.name = header();
        f.parent = parent;
        int idx = (int)m_.frames.size();
        m_.frames.push_back(f);
        children([&](const std::string& t) {
            if (t == "FrameTransformMatrix") {
                header();
                m_.frames[idx].bindLocal = lx_.M4();
                skipRest();
                return true;
            }
            if (t == "Frame") { parseFrame(idx); return true; }
            if (t == "Mesh")  { parseMesh(idx);  return true; }
            return false;
        });
    }

    void readMaterialBody(Material& mt) {
        mt.diffuse  = {lx_.F(), lx_.F(), lx_.F(), lx_.F()};
        mt.power    = lx_.F();
        mt.specular = lx_.V3();
        mt.emissive = lx_.V3();
        children([&](const std::string& t) {
            if (t == "TextureFilename") {
                header();
                std::string v = lx_.next();
                mt.texture = lx_.lastQuoted() ? v : trimNul(v);
                skipRest();
                return true;
            }
            if (t == "EffectInstance") {
                // Nested effect binding, previously skipped outright here (the
                // binary converter already emits these — the template is seeded).
                // Same shape as TextureFilename (optional name + one string).
                header();
                std::string v = lx_.next();
                mt.effectFile = lx_.lastQuoted() ? v : trimNul(v);
                m_.stats.hadEffectInstance = true;
                skipRest();
                return true;
            }
            return false;
        });
    }

    void parseMesh(int frame) {
        RawMesh r;
        r.name = header();
        r.frame = frame;

        const int nv = readCount("mesh vertex count");
        r.pos.resize((size_t)nv);
        for (auto& p : r.pos) p = lx_.V3();

        const int nf = readCount("mesh face count");
        r.faces.resize((size_t)nf);
        for (auto& f : r.faces) {
            const int n = readCount("face vertex count", 4096);
            f.resize((size_t)n);
            for (auto& i : f) i = (uint32_t)lx_.I();
        }

        children([&](const std::string& t) {
            if (t == "MeshNormals")        { parseMeshNormals(r);       return true; }
            if (t == "MeshTextureCoords")  { parseMeshTextureCoords(r); return true; }
            if (t == "MeshVertexColors")   { parseMeshVertexColors(r);  return true; }
            if (t == "XSkinMeshHeader") {
                header();
                r.skinHeader.present = true;
                r.skinHeader.maxWeightsPerVertex = lx_.I();
                r.skinHeader.maxWeightsPerFace   = lx_.I();
                r.skinHeader.bones               = lx_.I();
                skipRest();
                return true;
            }
            if (t == "VertexDuplicationIndices") {
                header();
                m_.stats.hadVertexDuplication = true;
                skipBody();
                return true;
            }
            if (t == "DeclData") {
                header();
                m_.stats.hadDeclData = true;
                skipBody();
                return true;
            }
            if (t == "MeshMaterialList")   { parseMeshMaterialList(r);  return true; }
            if (t == "SkinWeights")        { parseSkinWeights(r);      return true; }
            return false;
        });
        raws_.push_back(std::move(r));
    }

    void parseMeshNormals(RawMesh& r) {
        header();
        const int n = readCount("normal count");
        r.normals.resize((size_t)n);
        for (auto& v : r.normals) v = lx_.V3();
        const int nfn = readCount("face-normal count");
        r.nfaces.resize((size_t)nfn);
        for (auto& f : r.nfaces) {
            const int c = readCount("face-normal arity", 4096);
            f.resize((size_t)c);
            for (auto& i : f) i = (uint32_t)lx_.I();
        }
        skipRest();
    }

    void parseMeshTextureCoords(RawMesh& r) {
        header();
        const int n = readCount("uv count");
        r.uvs.resize((size_t)n);
        for (auto& v : r.uvs) v = lx_.V2();
        skipRest();
    }

    void parseMeshVertexColors(RawMesh& r) {
        header();
        const int n = readCount("vertex colour count");
        r.colors.assign(r.pos.size(), glm::vec4(1.f));
        for (int i = 0; i < n; ++i) {
            const int idx = lx_.I();
            glm::vec4 c{lx_.F(), lx_.F(), lx_.F(), lx_.F()};
            if (idx >= 0 && (size_t)idx < r.colors.size()) r.colors[(size_t)idx] = c;
        }
        skipRest();
    }

    // Materials named here are also entered in named_, and the list's own {ref} children
    // resolve through it: a MeshMaterialList may reference a Material parsed earlier.
    void parseMeshMaterialList(RawMesh& r) {
        header();
        lx_.I();                 // nMaterials (the actual list follows)
        const int nfi = readCount("face-material count");
        r.faceMat.resize((size_t)nfi);
        for (auto& i : r.faceMat) i = (uint32_t)lx_.I();
        children([&](const std::string& c) {
            if (c == "Material") {
                Material mt;
                std::string n = header();
                readMaterialBody(mt);
                if (!n.empty()) named_[n] = mt;
                r.mats.push_back(mt);
                return true;
            }
            return false;
        }, [&](const std::string& ref) {
            auto it = named_.find(ref);
            r.mats.push_back(it != named_.end() ? it->second : Material{});
        });
    }

    void parseSkinWeights(RawMesh& r) {
        header();
        RawSkin s;
        s.bone = lx_.next();
        const int n = readCount("skin weight count");
        s.idx.resize((size_t)n);
        s.w.resize((size_t)n);
        for (auto& i : s.idx) i = (uint32_t)lx_.I();
        for (auto& w : s.w) w = lx_.F();
        s.offset = lx_.M4();
        skipRest();
        r.skins.push_back(std::move(s));
    }

    void parseAnimSet() {
        AnimSet set;
        set.name = header();
        children([&](const std::string& t) {
            if (t != "Animation") return false;
            header();
            Channel ch;
            children([&](const std::string& c) {
                if (c != "AnimationKey") return false;
                header();
                int type = lx_.I();
                // Tighter than kMaxElements: a key is followed by its own arity, so
                // this count multiplies what the loop below allocates.
                const int nkeys = readCount("animation key count", 1 << 24);
                for (int k = 0; k < nkeys; ++k) {
                    float time = (float)lx_.I();
                    const int nvals = readCount("animation key arity", 64);
                    if (type == 0 && nvals == 4) {
                        float w = lx_.F(), x = lx_.F(), y = lx_.F(), z = lx_.F();
                        glm::quat q(w, x, y, z);            // .x stores (s, v) == (w, x, y, z)
                        if (opt_.conjugateQuats) q = glm::conjugate(q);
                        ch.rot.push_back({time, q});
                    } else if (type == 1 && nvals == 3) {
                        ch.scale.push_back({time, lx_.V3()});
                    } else if (type == 2 && nvals == 3) {
                        ch.pos.push_back({time, lx_.V3()});
                    } else if ((type == 3 || type == 4) && nvals == 16) {
                        glm::mat4 m = lx_.M4();
                        glm::vec3 s, t, skew; glm::vec4 persp; glm::quat r;
                        if (glm::decompose(m, s, r, t, skew, persp)) {
                            ch.scale.push_back({time, s});
                            ch.rot.push_back({time, glm::normalize(r)});
                            ch.pos.push_back({time, t});
                        }
                        m_.stats.matrixKeys++;
                    } else {
                        for (int i = 0; i < nvals; ++i) lx_.F();
                    }
                }
                skipRest();
                return true;
            }, [&](const std::string& ref) { ch.frameName = ref; });
            set.channels.push_back(std::move(ch));
            return true;
        });
        m_.anims.push_back(std::move(set));
    }

    void finish() {
        for (auto& f : m_.frames) {
            glm::vec3 skew; glm::vec4 persp;
            if (!glm::decompose(f.bindLocal, f.bindS, f.bindR, f.bindT, skew, persp)) {
                f.bindS = {1.f, 1.f, 1.f};
                f.bindR = glm::quat(1.f, 0.f, 0.f, 0.f);
                f.bindT = glm::vec3(f.bindLocal[3]);
            }
            f.bindR = glm::normalize(f.bindR);
        }

        for (auto& a : m_.anims) {
            for (auto& c : a.channels) {
                c.frame = m_.findFrame(c.frameName);
                auto upd = [&](const auto& v) { if (!v.empty()) a.duration = std::max(a.duration, v.back().t); };
                upd(c.rot); upd(c.scale); upd(c.pos);
                // Keys must be sorted for the sampler; D3DX writers emit them ordered but
                // a sorted guarantee here removes the assumption.
                auto byTime = [](const auto& x, const auto& y) { return x.t < y.t; };
                std::sort(c.rot.begin(), c.rot.end(), byTime);
                std::sort(c.scale.begin(), c.scale.end(), byTime);
                std::sort(c.pos.begin(), c.pos.end(), byTime);
            }
            a.channels.erase(std::remove_if(a.channels.begin(), a.channels.end(),
                             [](const Channel& c) { return c.frame < 0; }), a.channels.end());
        }

        // The reference controller enumerates the sets in reverse file order, and the game
        // binds by that index: FUN_0064d940 loads GetAnimationSet(0)/(1), and the fighter
        // states pass bare indices. Measured on the DLL the original ships (Microsoft
        // d3dx9_25.dll, native under Wine) for data/rika/01.X: set 0 is "Anim-124", the
        // file's last AnimationSet, and set i = file set (N-1-i) for all 124 — the same
        // DLL agrees on 4800 source ticks/s and on every key's S/R/T, so the index order
        // was the only divergence. In file order index 0 was a 170-degree rigid root flip
        // instead of the default whose first key reproduces the bind pose.
        std::reverse(m_.anims.begin(), m_.anims.end());

        for (auto& r : raws_) m_.meshes.push_back(buildMesh(r));

        m_.stats.frames   = (int)m_.frames.size();
        m_.stats.meshes   = (int)m_.meshes.size();
        m_.stats.animSets = (int)m_.anims.size();
        for (const auto& a : m_.anims) {
            m_.stats.channels += (int)a.channels.size();
            for (const auto& c : a.channels) {
                m_.stats.rotKeys += (int)c.rot.size();
                m_.stats.posKeys += (int)c.pos.size();
                m_.stats.scaleKeys += (int)c.scale.size();
            }
        }
    }

    // A position's bone influences, strongest first. The shipped rigs stay within
    // XSkinMeshHeader's limit, but files in the wild can exceed 4, so the eight slots are
    // a candidate pool and the emit step keeps the top four.
    struct Influences { std::array<std::pair<uint32_t, float>, 8> v{}; int n = 0; };

    // Fills that pool from the mesh's SkinWeights: each skin contributes its
    // (position, weight) pairs to the position they name, an overflowing position drops
    // its weakest candidate for a stronger one, and what is left is sorted
    // strongest-first. out.droppedInfluences and the max-influences stat live here
    // because this is the only pass that sees both a candidate and the set it competed
    // with; the caller renormalises what survives.
    std::vector<Influences> buildInfluences(const RawMesh& r, Mesh& out) {
        std::vector<Influences> infl(r.pos.size());
        for (uint32_t bi = 0; bi < r.skins.size(); ++bi) {
            const RawSkin& s = r.skins[bi];
            for (size_t k = 0; k < s.idx.size() && k < s.w.size(); ++k) {
                if (s.idx[k] >= infl.size() || !(s.w[k] > 0.f)) continue;
                Influences& in = infl[s.idx[k]];
                if (in.n < (int)in.v.size()) {
                    in.v[in.n++] = {bi, s.w[k]};
                } else {
                    auto mn = std::min_element(in.v.begin(), in.v.end(),
                                [](const auto& a, const auto& b) { return a.second < b.second; });
                    if (s.w[k] > mn->second) { *mn = {bi, s.w[k]}; out.droppedInfluences++; }
                }
            }
        }
        for (auto& in : infl) {
            std::sort(in.v.begin(), in.v.begin() + in.n,
                      [](const auto& a, const auto& b) { return a.second > b.second; });
            m_.stats.maxInfluencesSeen = std::max(m_.stats.maxInfluencesSeen, in.n);
        }
        return infl;
    }

    // Generated vertex normals for a mesh whose .X carries none (or carries a face-normal
    // list that does not match its faces): the unnormalised geometric normal of each face
    // summed into its three vertices, so the sum weights by area, then normalised where
    // it is non-degenerate.
    std::vector<glm::vec3> buildAutoNormals(const RawMesh& r) {
        std::vector<glm::vec3> autoN(r.pos.size(), glm::vec3(0));
        for (const auto& f : r.faces)
            for (size_t i = 1; i + 1 < f.size(); ++i) {
                if (f[0] >= r.pos.size() || f[i] >= r.pos.size() || f[i + 1] >= r.pos.size())
                    continue;
                // LH + clockwise front faces: cross(a - b, c - b) points outward.
                glm::vec3 n = glm::cross(r.pos[f[i + 1]] - r.pos[f[0]], r.pos[f[i]] - r.pos[f[0]]);
                autoN[f[0]] += n; autoN[f[i]] += n; autoN[f[i + 1]] += n;
            }
        for (auto& n : autoN) if (glm::dot(n, n) > 0.f) n = glm::normalize(n);
        return autoN;
    }

    Mesh buildMesh(const RawMesh& r) {
        Mesh out;
        out.name = r.name;
        out.frame = r.frame;
        out.materials = r.mats;
        if (out.materials.empty()) out.materials.push_back(Material{});
        out.skinned = !r.skins.empty();
        out.skinHeader = r.skinHeader;
        out.hasVertexColors = !r.colors.empty();
        if (out.hasVertexColors) m_.stats.meshesWithVertexColors++;

        for (const auto& s : r.skins) {
            Bone b;
            b.name = s.bone;
            b.offset = s.offset;
            b.frame = m_.findFrame(s.bone);
            out.bones.push_back(b);
        }
        m_.stats.skinBones += (int)out.bones.size();

        std::vector<Influences> infl;
        if (out.skinned) infl = buildInfluences(r, out);

        // The file's own normals are used only when its face-normal list lines up with
        // its face list; otherwise the geometric normals below are generated. autoN is
        // left empty when they are, and the emit step never reads it.
        const bool haveN = !r.normals.empty() && r.nfaces.size() == r.faces.size();
        std::vector<glm::vec3> autoN;
        if (!haveN) autoN = buildAutoNormals(r);

        // One GPU vertex per unique (position, normal) pair; uv and colour follow the
        // position index, which is how the .x format stores them.
        std::unordered_map<uint64_t, uint32_t> remap;
        auto emit = [&](uint32_t pi, uint32_t ni) -> uint32_t {
            uint64_t key = ((uint64_t)pi << 32) | ni;
            auto it = remap.find(key);
            if (it != remap.end()) return it->second;
            Vertex v{};
            v.pos    = r.pos[pi];
            v.normal = haveN ? r.normals[ni] : autoN[pi];
            v.uv     = pi < r.uvs.size() ? r.uvs[pi] : glm::vec2(0.f);
            v.color  = pi < r.colors.size() ? r.colors[pi] : glm::vec4(1.f);
            if (out.skinned) {
                float sum = 0.f;
                const Influences& in = infl[pi];
                for (int k = 0; k < 4; ++k) {
                    if (k < in.n) { v.bones[k] = in.v[k].first; v.weights[k] = in.v[k].second; sum += v.weights[k]; }
                }
                if (sum > 0.f) v.weights /= sum;
                else { v.bones = glm::uvec4(0u); v.weights = glm::vec4(1.f, 0.f, 0.f, 0.f); }
            }
            uint32_t id = (uint32_t)out.vertices.size();
            out.vertices.push_back(v);
            remap.emplace(key, id);
            return id;
        };

        std::vector<std::vector<uint32_t>> buckets(out.materials.size());
        for (size_t fi = 0; fi < r.faces.size(); ++fi) {
            const auto& f = r.faces[fi];
            if (f.size() < 3) continue;
            if (std::any_of(f.begin(), f.end(),
                            [&](uint32_t idx) { return idx >= r.pos.size(); }))
                continue;
            uint32_t mat = fi < r.faceMat.size() ? r.faceMat[fi]
                         : (r.faceMat.size() == 1 ? r.faceMat[0] : 0u);
            if (mat >= buckets.size()) mat = 0;
            auto corner = [&](size_t c) -> uint32_t {
                uint32_t pi = f[c];
                uint32_t ni = 0;
                if (haveN && fi < r.nfaces.size() && c < r.nfaces[fi].size()) {
                    ni = r.nfaces[fi][c];
                    if (ni >= r.normals.size()) ni = 0;
                }
                return emit(pi, ni);
            };
            uint32_t c0 = corner(0);
            for (size_t i = 1; i + 1 < f.size(); ++i) {
                buckets[mat].push_back(c0);
                buckets[mat].push_back(corner(i));
                buckets[mat].push_back(corner(i + 1));
            }
        }
        for (size_t mi = 0; mi < buckets.size(); ++mi) {
            if (buckets[mi].empty()) continue;
            Submesh s;
            s.firstIndex = (uint32_t)out.indices.size();
            s.indexCount = (uint32_t)buckets[mi].size();
            s.material   = (int)mi;
            out.indices.insert(out.indices.end(), buckets[mi].begin(), buckets[mi].end());
            out.submeshes.push_back(s);
        }

        m_.stats.vertices      += (int)out.vertices.size();
        m_.stats.triangles     += (int)out.indices.size() / 3;
        m_.stats.submeshes     += (int)out.submeshes.size();
        m_.stats.materials     += (int)out.materials.size();
        m_.stats.droppedInfluences += out.droppedInfluences;
        return out;
    }

    static constexpr int                      kMaxNesting = 64;
    int                                       depth_ = 0;
    Lexer&                                    lx_;
    Model&                                    m_;
    const LoadOptions&                        opt_;
    std::vector<RawMesh>                      raws_;
    std::unordered_map<std::string, Material> named_;
};

// The name -> index lookup every Model::find* uses. Frames, anim sets and meshes all
// carry a unique name and the first match wins, which is what the original's own lookup
// does; a template so the three cannot drift apart.
template <class T>
int findByName(const std::vector<T>& v, const std::string& n) {
    for (size_t i = 0; i < v.size(); ++i) if (v[i].name == n) return (int)i;
    return -1;
}

// The bind pose as animation channels: what a frame keeps when no enabled track touches
// it, and what a channel that carries no key for a component contributes. Both sample
// paths start from these three vectors, which is why they are filled here and not at
// either site.
void bindChannels(const std::vector<Frame>& frames, std::vector<glm::vec3>& pos,
                  std::vector<glm::quat>& rot, std::vector<glm::vec3>& scale) {
    pos.resize(frames.size());
    rot.resize(frames.size());
    scale.resize(frames.size());
    for (size_t i = 0; i < frames.size(); ++i) {
        pos[i]   = frames[i].bindT;
        rot[i]   = frames[i].bindR;
        scale[i] = frames[i].bindS;
    }
}

// One world matrix per frame, from that frame's local T/R/S and its parent's world
// matrix. Frames are stored parents-first (the Model contract), so one forward pass
// suffices and no separate local-matrix array is needed.
void composeWorld(const std::vector<Frame>& frames, const std::vector<glm::vec3>& pos,
                  const std::vector<glm::quat>& rot, const std::vector<glm::vec3>& scale,
                  std::vector<glm::mat4>& world) {
    world.resize(frames.size());
    for (size_t i = 0; i < frames.size(); ++i) {
        const glm::mat4 local = glm::translate(glm::mat4(1.f), pos[i]) *
                                glm::mat4_cast(rot[i]) * glm::scale(glm::mat4(1.f), scale[i]);
        world[i] = frames[i].parent < 0 ? local : world[(size_t)frames[i].parent] * local;
    }
}

}  // namespace detail

// ---------------------------------------------------------------------------------------
// Model
// ---------------------------------------------------------------------------------------
int Model::findFrame(const std::string& n) const { return detail::findByName(frames, n); }
int Model::findAnim(const std::string& n) const { return detail::findByName(anims, n); }
int Model::findMesh(const std::string& n) const { return detail::findByName(meshes, n); }

void Model::evalPose(const AnimSet* a, float seconds, bool loop,
                     std::vector<glm::mat4>& world) const {
    using namespace detail;
    std::vector<glm::vec3> S, T;
    std::vector<glm::quat> R;
    bindChannels(frames, T, R, S);
    if (a && a->duration > 0.f) {
        float tick = seconds * ticksPerSecond;
        tick = loop ? std::fmod(tick, a->duration) : std::min(tick, a->duration);
        if (tick < 0) tick += a->duration;
        for (const Channel& c : a->channels) {
            if (!c.scale.empty())
                S[c.frame] = sampleKeys(c.scale, tick, [](auto& x, auto& y, float t) { return glm::mix(x, y, t); });
            if (!c.pos.empty())
                T[c.frame] = sampleKeys(c.pos, tick, [](auto& x, auto& y, float t) { return glm::mix(x, y, t); });
            if (!c.rot.empty())
                R[c.frame] = sampleKeys(c.rot, tick, [](auto& x, auto& y, float t) { return glm::slerp(x, y, t); });
        }
        for (size_t i = 0; i < frames.size(); ++i) if (glm::dot(R[i], R[i]) > 0.f) R[i] = glm::normalize(R[i]);
    }

    composeWorld(frames, T, R, S, world);
}

void Model::buildPalette(const Mesh& m, const std::vector<glm::mat4>& world,
                         std::vector<glm::mat4>& out) const {
    if (!m.skinned) {
        out.assign(1, m.frame >= 0 && (size_t)m.frame < world.size() ? world[m.frame] : glm::mat4(1.f));
        return;
    }
    out.resize(m.bones.size());
    for (size_t i = 0; i < m.bones.size(); ++i) {
        const Bone& b = m.bones[i];
        const glm::mat4& w = (b.frame >= 0 && (size_t)b.frame < world.size())
                                 ? world[b.frame] : glm::mat4(1.f);
        out[i] = w * b.offset;
    }
}

size_t Model::paletteSize() const {
    size_t n = 0;
    for (const Mesh& m : meshes) n += m.skinned ? m.bones.size() : 1;
    return n;
}

// ---------------------------------------------------------------------------------------
// Controller
// ---------------------------------------------------------------------------------------
void Controller::setTrackAnimationSet(int t, int animIndex) {
    if (Track* tr = track(t)) tr->anim = animIndex;
}
int Controller::trackAnimationSet(int t) const {
    const Track* tr = track(t);
    return tr ? tr->anim : -1;
}
void Controller::setTrackEnable(int t, bool on) {
    if (Track* tr = track(t)) tr->enable = on;
}
bool Controller::trackEnable(int t) const {
    const Track* tr = track(t);
    return tr && tr->enable;
}
void Controller::setTrackWeight(int t, float w) {
    if (Track* tr = track(t)) tr->weight = glm::clamp(w, 0.f, 1.f);
}
float Controller::trackWeight(int t) const {
    const Track* tr = track(t);
    return tr ? tr->weight : 0.f;
}
void Controller::setTrackSpeed(int t, float s) {
    if (Track* tr = track(t)) tr->speed = s;
}
float Controller::trackSpeed(int t) const {
    const Track* tr = track(t);
    return tr ? tr->speed : 1.f;
}
void Controller::setTrackPosition(int t, double seconds) {
    if (Track* tr = track(t)) tr->time = seconds;
}
double Controller::trackPosition(int t) const {
    const Track* tr = track(t);
    return tr ? tr->time : 0.0;
}
void Controller::setTrackLoop(int t, bool loop) {
    if (Track* tr = track(t)) tr->loop = loop;
}
bool Controller::trackLoop(int t) const {
    const Track* tr = track(t);
    return tr && tr->loop;
}

bool Controller::setAnimation(int animIndex, bool loop) {
    if (!model_ || animIndex < 0 || (size_t)animIndex >= model_->anims.size()) return false;
    resetTracks();
    initTrack(0, animIndex, loop);
    return true;
}

bool Controller::setAnimationBothTracks(int animIndex, bool loop) {
    if (!model_ || animIndex < 0 || (size_t)animIndex >= model_->anims.size()) return false;
    resetTracks();
    initTrack(0, animIndex, loop);
    initTrack(1, animIndex, loop);
    return true;
}

void Controller::advanceTime(float dt) {
    if (!model_) return;
    for (Track& t : tracks_) {
        if (!t.enable || t.anim < 0) continue;
        t.time += (double)dt * (double)t.speed;
        if (t.time < 0.0) t.time = 0.0;
    }
}

double Controller::time() const {
    double best = 0.0;
    for (const Track& t : tracks_)
        if (t.enable && t.anim >= 0) best = std::max(best, t.time);
    return best;
}

void Controller::evalLocal(std::vector<glm::vec3>& pos, std::vector<glm::quat>& rot,
                           std::vector<glm::vec3>& scale) const {
    using namespace detail;
    if (!model_) {                 // no bind pose to start from: empty channels, as ever
        pos.clear();
        rot.clear();
        scale.clear();
        return;
    }
    bindChannels(model_->frames, pos, rot, scale);
    const size_t nf = model_->frames.size();

    std::vector<float> accW(nf, 0.f);
    for (const Track& t : tracks_) {
        if (!t.enable || t.weight <= 0.f || t.anim < 0) continue;
        if ((size_t)t.anim >= model_->anims.size()) continue;
        const AnimSet& set = model_->anims[(size_t)t.anim];
        if (set.duration <= 0.f) continue;

        double seconds = t.time;
        float tick = (float)(seconds * (double)model_->ticksPerSecond);
        tick = t.loop ? std::fmod(tick, set.duration) : std::min(tick, set.duration);
        if (tick < 0.f) tick += set.duration;

        for (const Channel& c : set.channels) {
            if (c.frame < 0 || (size_t)c.frame >= nf) continue;
            float w = t.weight;
            float aw = accW[c.frame];
            float alpha = w / (aw + w);       // incremental weighted blend
            if (!c.scale.empty()) {
                glm::vec3 v = sampleKeys(c.scale, tick, [](auto& x, auto& y, float f) { return glm::mix(x, y, f); });
                scale[c.frame] = aw <= 0.f ? v : glm::mix(scale[c.frame], v, alpha);
            }
            if (!c.pos.empty()) {
                glm::vec3 v = sampleKeys(c.pos, tick, [](auto& x, auto& y, float f) { return glm::mix(x, y, f); });
                pos[c.frame] = aw <= 0.f ? v : glm::mix(pos[c.frame], v, alpha);
            }
            if (!c.rot.empty()) {
                glm::quat v = sampleKeys(c.rot, tick, [](auto& x, auto& y, float f) { return glm::slerp(x, y, f); });
                if (glm::dot(v, v) > 0.f) v = glm::normalize(v);
                rot[c.frame] = aw <= 0.f ? v : glm::slerp(rot[c.frame], v, alpha);
            }
            accW[c.frame] = aw + w;
        }
    }
    for (size_t i = 0; i < nf; ++i) if (glm::dot(rot[i], rot[i]) > 0.f) rot[i] = glm::normalize(rot[i]);
}

void Controller::evalWorld(std::vector<glm::mat4>& world) const {
    std::vector<glm::vec3> S, T;
    std::vector<glm::quat> R;
    evalLocal(T, R, S);
    // No model: the channel vectors come back empty (evalLocal clears them), so the
    // world matrix array is cleared too — the bounds the old loop computed on its own.
    if (!model_) {
        world.clear();
        return;
    }
    detail::composeWorld(model_->frames, T, R, S, world);
}

std::string LoadStats::toString() const {
    char buf[512];
    std::snprintf(buf, sizeof buf,
        "%s: %d frames, %d meshes, %d materials, %d anim sets, %d channels "
        "(rot %d / pos %d / scale %d / mat %d), %d verts, %d tris, %d submeshes, "
        "%d skin bones, max influences %d, dropped %d, %d colour meshes%s%s%s",
        encoding.c_str(), frames, meshes, materials, animSets, channels,
        rotKeys, posKeys, scaleKeys, matrixKeys, vertices, triangles, submeshes,
        skinBones, maxInfluencesSeen, droppedInfluences, meshesWithVertexColors,
        hadDeclData ? ", DeclData" : "", hadVertexDuplication ? ", VertexDuplicationIndices" : "",
        hadEffectInstance ? ", EffectInstance" : "");
    return buf;
}

// ---------------------------------------------------------------------------------------
// Entry points
// ---------------------------------------------------------------------------------------
namespace detail {

// `start` skips the 16-byte "xof ..." header for on-disk text files. Text produced by
// the binary converter has no header, so it starts at 0. Getting this wrong does not
// fail loudly: the lexer treats the header line as the name of an unknown object and
// swallows the first real object along with it, which silently drops geometry from
// any text asset whose first entry is a Frame or Mesh rather than a template.
void parseTextInto(Model& m, const std::string& text, size_t start,
                   const LoadOptions& opt) {
    Lexer lx(text, start);
    Parser(lx, m, opt).run();
}

// One Model from one text form: the encoding it came in as, the ticks-per-second default
// the file itself may override (AnimTicksPerSecond), and the parse timing every
// text-bearing path reports. `t0` is the caller's own clock start, so a file's parseMs
// and a compressed one's convertMs are measured from the same instant.
Model parseTextModel(const std::string& text, size_t start, const char* encoding,
                     const LoadOptions& opt, std::chrono::steady_clock::time_point t0) {
    Model m;
    m.stats.encoding = encoding;
    m.ticksPerSecond = opt.ticksPerSecond;
    parseTextInto(m, text, start, opt);
    auto t1 = std::chrono::steady_clock::now();
    m.stats.parseMs = std::chrono::duration<double, std::milli>(t1 - t0).count();
    return m;
}

Model parseBinaryStream(const uint8_t* data, size_t size, size_t start, bool float64,
                        const char* encoding, const LoadOptions& opt,
                        std::chrono::steady_clock::time_point t0) {
    auto t1 = std::chrono::steady_clock::now();
    BinaryToText conv(data, size, start, float64);
    std::string text = conv.run();
    if (!conv.ok()) throw std::runtime_error(conv.error());
    if (opt.convertedTextOut) *opt.convertedTextOut = text;
    auto t2 = std::chrono::steady_clock::now();

    Model m = parseTextModel(text, 0, encoding, opt, t2);
    m.stats.convertMs = std::chrono::duration<double, std::milli>(t1 - t0).count();
    return m;
}

}  // namespace detail

Model loadMemory(const void* data, size_t size, const LoadOptions& opt) {
    using namespace detail;
    if (!data || size < 16) throw std::runtime_error("x-file too short");
    const uint8_t* p = (const uint8_t*)data;
    if (std::memcmp(p, "xof ", 4) != 0) throw std::runtime_error("not a DirectX .x file");

    char fmt[5] = {0};
    std::memcpy(fmt, p + 8, 4);
    const bool float64 = std::memcmp(p + 12, "0064", 4) == 0;
    std::string fmtStr(fmt);
    while (!fmtStr.empty() && fmtStr.back() == ' ') fmtStr.pop_back();
    auto t0 = std::chrono::steady_clock::now();

    if (fmtStr == "txt") {
        // AnimTicksPerSecond in the file overrides the default parseTextModel installs.
        return parseTextModel(std::string((const char*)p, size), 16, "txt", opt, t0);
    }
    if (fmtStr == "bin") {
        return parseBinaryStream(p, size, 16, float64, "bin", opt, t0);
    }
    if (fmtStr == "bzip" || fmtStr == "tzip") {
        std::vector<uint8_t> out;
        std::string err;
        if (!decompressMSZip(p, p + 16, size - 16, out, err))
            throw std::runtime_error("MSZIP: " + err);
        // A decompressed payload carries no header of its own, so the token stream
        // starts at offset 0. "tzip" would decompress to text: sniff and fall through.
        if (out.size() >= 4 && std::memcmp(out.data(), "xof ", 4) == 0) {
            return parseTextModel(std::string((const char*)out.data(), out.size()), 0, "tzip",
                                  opt, t0);
        }
        return parseBinaryStream(out.data(), out.size(), 0, float64, "bzip", opt, t0);
    }
    throw std::runtime_error("unsupported .x encoding '" + fmtStr + "'");
}

Model loadMemory(const std::string& data, const LoadOptions& opt) {
    return loadMemory(data.data(), data.size(), opt);
}

Model loadFile(const std::string& path, const LoadOptions& opt) {
    std::FILE* f = std::fopen(path.c_str(), "rb");
    if (!f) throw std::runtime_error("cannot open " + path);
    std::fseek(f, 0, SEEK_END);
    long n = std::ftell(f);
    std::fseek(f, 0, SEEK_SET);
    if (n < 0) { std::fclose(f); throw std::runtime_error("cannot size " + path); }
    std::string buf((size_t)n, '\0');
    size_t got = std::fread(&buf[0], 1, (size_t)n, f);
    std::fclose(f);
    buf.resize(got);
    return loadMemory(buf, opt);
}

}  // namespace xm
#endif  // XMODEL_IMPLEMENTATION_DONE
#endif  // XMODEL_IMPLEMENTATION
