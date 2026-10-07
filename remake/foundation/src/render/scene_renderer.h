#pragma once
// Draws an xm::Scene: depth buffer, textured pipeline, per-draw uniforms, stage
// camera and fog. This is the second — and last — place outside gpu/ that includes
// webgpu.h, because building render pipelines is not something gpu/ wraps; the
// asset layer's xm::wgpuVertexLayout() is the contract between the two, which is
// why the asset header has to be pulled in with XMODEL_WEBGPU defined.
#include <webgpu/webgpu.h>

#include <cmath>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>

#include "gpu/gpu.h"

// xmodel.h only declares its WebGPU helpers when this is set, and webgpu.h is
// already in scope above (the header has to be included first).
#define XMODEL_WEBGPU
#include "scene.h"
// After scene.h on purpose: npr_normals.h includes xmodel.h for the plain data types, and
// xmodel.h is #pragma once — pulling it in before XMODEL_WEBGPU is defined would hide the
// WebGPU half from every later include in this translation unit.
#include "render/npr_normals.h"
#include "render/shadow_map.h"

namespace render {

// The depth format every extra pass must declare in its pipeline. WebGPU validates a
// pipeline's depth format against the attachment view's and rejects the whole command
// buffer on a mismatch, so this is not a preference: it is the format ensureDepth
// creates, named once instead of guessed per pass.
inline constexpr WGPUTextureFormat kSceneDepthFormat = WGPUTextureFormat_Depth24PlusStencil8;

// ---------------------------------------------------------------------------------------
// Mip chain for uploaded stage textures.
//
// Why it exists: the original filters stage textures LINEAR **with mips** — its device
// state block sets sampler 0 MAG/MIN/MIP all to D3DTEXF_LINEAR, once at device creation
// and again on every Reset (research/decompiled/FUN_00654f00.c:45-47, called from
// FUN_00654b90.c:63 and FUN_00654d90.c:32). D3D9's default D3DSAMP_MIPFILTER is
// D3DTEXF_NONE, so that write is the game asking for it, and it is the state the prints
// were taken under. The other two sampler properties this renderer must not invent:
// across the whole decompiled dump the only sampler types written anywhere are ADDRESSU/V
// (1, 2), BORDERCOLOR (4) and MAG/MIN/MIPFILTER (5, 6, 7), and sampler 0 receives *only*
// those three filters — 33 call sites over 7 functions, every value either 1 (POINT) or 2
// (LINEAR). So sampler 0's address modes stay at D3D9's WRAP (Repeat), and
// D3DSAMP_MAXANISOTROPY (type 10), MIPMAPLODBIAS (8) and MAXMIPLEVEL (9) are never written
// at all: anisotropy 1, no LOD bias, no level clamp. D3DTEXF_ANISOTROPIC (value 3) never
// appears either; where the value 3 does appear it is ADDRESSU/V on samplers 1 and 2 in
// FUN_00651110, i.e. D3DTADDRESS_MIRROR, a different enum.
//
// Which textures have a chain is the same evidence's other half: the original does not
// *generate* levels, it ships them as precomputed art beside the base image, and only the
// stage directories do — `X.cnv` (128x128) + `X_1.cnv` (64x64) + `X_2.cnv` (32x32), 85
// such groups in stage01 (all 13 stage dirs surveyed). Character, weapon, effect, aura and
// item directories ship none. The loader probes `%s_%d.bmp` from the base name upward,
// creates the texture with exactly the number of levels it found (`D3DXCreateTexture(...,
// levelCount, ...)`) and fills each one with LockRect(level), halving the width per level
// (research/decompiled/FUN_00656c80.c:87-88 and :107-118; reached from the .X material name
// via FUN_00661f60 -> FUN_0064ecd0 -> FUN_006560c0). So a character texture is created with
// MipLevels = 1 in the original: it has no mips to filter with, and MIPFILTER = LINEAR
// degenerates to level 0 for it. This renderer therefore chains `role == "stage"` models
// only; the role is the closest signal it has to "this texture's directory ships levels",
// which is what the original actually tests.
//
// Content check on the shipped levels: shadow01_1.cnv is a 2x2 box average of shadow01.cnv
// to within a mean |delta| of 1.59/255, against 67.97/255 for a shifted control. Those
// files are the higher-fidelity source: levels 1-2 upload the shipped bytes when the
// sibling is present at exactly the halved dims (the FUN_00656c80 width gate), and the
// generated box below is only the fallback past them and for missing art. The filter
// averages raw bytes because D3D9's own filter and the shipped
// levels are byte-space too (the texture is RGBA8Unorm, not sRGB, and the shader treats the
// sampled value as linear).
//
// Both live here, and not in the .cpp, so tests/lighting_test.cpp can pin the arithmetic
// with no device: a wrong level count or a filter that mishandles odd dimensions changes
// every minified pixel in a frame and shows up nowhere else. That test links the asset
// layer but not the render library, so these have to be inline to be reachable from it —
// a .cpp definition would need a CMakeLists change to be testable at all.
// ---------------------------------------------------------------------------------------

// Levels a full chain has: floor(log2(max(w, h))) + 1, i.e. down to a 1-wide/tall edge.
// An empty image has no chain to speak of; buildMipChain returns no levels for one.
inline uint32_t mipLevelCount(uint32_t width, uint32_t height) {
    if (width == 0 || height == 0) return 1;
    uint32_t levels = 1;
    for (uint32_t m = width > height ? width : height; m > 1; m >>= 1) ++levels;
    return levels;
}

// Shipped mip sibling name: "foo.bmp" -> "foo_1.bmp" (FUN_00656c80's
// `%s_%d.bmp` walk; the observed numbering offset is 0, so shipped levels
// start at _1 and stop at _2). Byte-surgical on purpose: material names are
// Shift-JIS, so only the ASCII tail is touched — split at the last dot, and
// a name without one takes the suffix bare. Empty in, empty out (the cache
// resolves empty to nothing anyway).
inline std::string mipSiblingName(const std::string& base, uint32_t level) {
    if (base.empty() || level == 0) return {};
    const size_t dot = base.find_last_of('.');
    if (dot == std::string::npos) return base + "_" + std::to_string(level);
    return base.substr(0, dot) + "_" + std::to_string(level) + ".bmp";
}

// Whether a shipped sibling may stand in for chain level `level`: exactly the
// halved dimensions (floor, clamped at 1 — the same rule buildMipChain uses),
// which is what FUN_00656c80's per-level width gate demands before it copies
// a level in. Anything else keeps the generated box level (B3 sketch
// fallback); the original would truncate the chain there instead — the one
// observed case is a _2 sized like a _1, where truncation would alias harder.
inline bool mipShippedDimsOk(uint32_t baseW, uint32_t baseH, uint32_t sibW, uint32_t sibH,
                             uint32_t level) {
    if (level == 0 || level >= 32 || sibW == 0 || sibH == 0) return false;
    const uint32_t ew = (baseW >> level) > 0 ? (baseW >> level) : 1u;
    const uint32_t eh = (baseH >> level) > 0 ? (baseH >> level) : 1u;
    return sibW == ew && sibH == eh;
}

// Builds `levels` for one RGBA8 image: levels[0] is the base image as authored (uploaded
// unchanged, so a texture sampled at level 0 is byte-identical to before), then each next
// level is the 2x2 box average of the one above at half the size (floor). An odd
// dimension therefore drops its last column/row, the rule D3DX's own box chain uses; at
// the bottom a level of width or height 1 averages the samples that exist along the other
// axis only. Alpha is averaged with colour: these are alpha-tested cutouts, and the
// reference's shipped levels carry authored alpha at every level.
inline void buildMipChain(const uint8_t* rgba, uint32_t width, uint32_t height,
                          std::vector<std::vector<uint8_t>>& levels) {
    levels.clear();
    if (rgba == nullptr || width == 0 || height == 0) return;
    levels.reserve(mipLevelCount(width, height));
    levels.emplace_back(rgba, rgba + (size_t)width * height * 4);
    for (uint32_t w = width, h = height; w > 1 || h > 1;) {
        const uint32_t dw = w > 1 ? w / 2 : 1;
        const uint32_t dh = h > 1 ? h / 2 : 1;
        const std::vector<uint8_t>& src = levels.back();
        std::vector<uint8_t> dst((size_t)dw * dh * 4);
        for (uint32_t y = 0; y < dh; ++y) {
            for (uint32_t x = 0; x < dw; ++x) {
                // The source block is 2x2, narrowing to 2x1/1x2/1x1 only when a
                // dimension is already 1 — the samples that exist, never a clamped
                // duplicate of one that does not.
                uint32_t sum[4] = {0, 0, 0, 0};
                uint32_t n = 0;
                for (uint32_t sy = 2 * y; sy < 2 * y + 2 && sy < h; ++sy) {
                    for (uint32_t sx = 2 * x; sx < 2 * x + 2 && sx < w; ++sx) {
                        const uint8_t* texel = src.data() + ((size_t)sy * w + sx) * 4;
                        for (int c = 0; c < 4; ++c) sum[c] += texel[c];
                        ++n;
                    }
                }
                uint8_t* out = dst.data() + ((size_t)y * dw + x) * 4;
                for (int c = 0; c < 4; ++c) out[c] = (uint8_t)((sum[c] + n / 2) / n);
            }
        }
        levels.push_back(std::move(dst));
        w = dw;
        h = dh;
    }
}

// ---------------------------------------------------------------------------------------
// The fixed-function light and clear colour the DX9 gameplay pass installs. Every value
// is read straight off remake/src/core/scenes.cpp:736-769 — the state block the banked
// reference frames were rendered with, i.e. this track's specification — and they are
// named here rather than inlined at the draw site so tests/lighting_test.cpp can pin
// them device-free. They are load-bearing to the third decimal: a stage lit with any other plausible triple lands 1.5x..2.7x off, and
// nothing short of a 480000-pixel comparison shows it.
//
// The shader evaluates lit = Ca*(Ga + La) + Cd*Ld*saturate(N.L); model_wgsl.h names which
// D3D state selects each term. No RE address is cited for the numbers because
// research/decompiled holds no SetLight/LightEnable call site and no 0.35/0.20/0.85 float
// immediate to attribute them to — the DX9 pass is the specification.
// ---------------------------------------------------------------------------------------
inline constexpr glm::vec3 kLightDirection{0.5f, -1.0f, 0.5f};  // light 0 Direction (scenes.cpp:767)
inline constexpr float kLightDiffuse   = 0.85f;                 // light 0 Diffuse   (scenes.cpp:765)
inline constexpr float kLightAmbient   = 0.20f;                 // light 0 Ambient   (scenes.cpp:766)
inline constexpr float kGlobalAmbient  = 0.35f;                 // D3DRS_AMBIENT     (scenes.cpp:746)
// D3DCOLOR_XRGB(40, 42, 54), the gameplay target's clear colour (scenes.cpp:736-737).
inline constexpr uint8_t kClearRed = 40, kClearGreen = 42, kClearBlue = 54;

// The character shadow pass (issue #21 row 1) lives in render/shadow_map.h: the light
// camera, the projection and the receiver's lookup as pure glm, so a host test can pin
// them with no device. The renderer below consumes it and nothing else.

// Where a frame goes. One struct so a swapchain frame and an offscreen capture run
// the same draw path; the format selects (and caches) the pipeline.
struct Target {
    WGPUCommandEncoder encoder   = nullptr;
    WGPUTextureView    colorView = nullptr;
    WGPUTextureFormat  format    = WGPUTextureFormat_Undefined;
    uint32_t           width     = 0;
    uint32_t           height    = 0;
};

// ---------------------------------------------------------------------------------------
// Per-view rendering (issue #12): the same scene drawn once per local player into
// disjoint cells of one render target.
//
// This is the original's own split-screen shape, FUN_006396f0 @0x006396f0: one D3D
// viewport per view — FUN_00650ab0 @0x00650ab0 writes X/Y/Width/Height and calls
// SetViewport, invoked with the cell rect before each view draws (:121-122) over the
// 400x300 quadrant table at :63-66 and :82-96 — the scene drawn once per view (:111), the
// view's HUD composed afterwards (:185). Depth is shared and cleared once: the cells are
// disjoint, so a later view can never see an earlier one's depth, which is why the port
// clears once and sets viewport AND scissor to the same cell for every view.
// ---------------------------------------------------------------------------------------
struct ViewportRect {
    float x = 0.f, y = 0.f, w = 0.f, h = 0.f;
    bool empty() const { return w <= 0.f || h <= 0.f; }
};

// One view's camera and the cell it draws into. `eye` is per view because effect-card
// billboarding faces the camera that draws the card, not the frame's first camera.
struct ViewCamera {
    glm::mat4    viewProj{1.f};
    glm::vec3    eye{0.f};
    ViewportRect rect{};   // empty -> the whole target (the single-view path)
};

inline constexpr size_t kMaxViewCameras = 4;

// The banding curve a B experiment selects (issue #25). The shader implements all three
// through nprBandWeight(); this is only which parameter set a draw is given.
enum class NprBands : uint8_t {
    Off = 0,     // no band experiment: the recovered arithmetic, untouched
    Hard,        // a step at the terminator: the hard 2-band read
    Soft,        // a short smoothstep across the terminator
    Three,       // Soft plus a second, darker band under it (the chin/hair read)
};

// The key-light arm of a D experiment (issue #25).
enum class NprKey : uint8_t {
    Off = 0,       // world light only
    Fixed,         // world light + a weak key fixed in the character's own frame
    Camera,        // world light + a weak key that leans in from behind the camera
};

// Draw-time switches, as opposed to upload-time ones (Options).
struct Appearance {
    bool fog   = true;   // linear fog from StageEnv (env.dat)
    bool unlit = false;  // skip the lambert term: raw texture/vertex colour
    // Toon ramp (issue #21): read the shipped ramp at the diffuse term on the draws the
    // original's toon technique covers (characters and their weapons). Off by default,
    // and with it off the lighting arithmetic is the pre-existing one bit for bit.
    bool toon  = false;
    // Character shadows (issue #21 row 1): render the light-space caster pass and let the
    // stage's ground sample it. Off by default, and with it off neither the pass nor the
    // receiver branch runs, so the frame is the pre-change frame bit for bit.
    bool shadows = false;
    // ---------------------------------------------------------------------------------
    // NPR experiments (issue #25). Every field defaults to the state in which the
    // fragment shader's arithmetic is the pre-#25 arithmetic bit for bit; none of them
    // is recovered, and none of them is reachable without an explicit --npr flag. They
    // are draw-time switches, so an experiment needs no re-upload — see
    // SceneRenderer::fillDrawData and foundation/docs/NPR-EXPERIMENTS.md.
    // ---------------------------------------------------------------------------------
    NprBands   bands   = NprBands::Off;
    float      bandSoftness = 0.06f;   // half-width of the smoothstep transition
    // The shadow tint (C). The default is the "white cloth -> cool violet/blue-grey" the
    // issue names, chosen over a neutral (1,1,1) because the neutral arm is the control
    // and the control has to be asked for (`--npr=shadow:none`): a default that changes
    // nothing would make `--npr=shadow` look like a no-op. Measured on the bind-pose
    // capture, a near-white tint (0.88,0.78,0.82) moved no pixel at all at 8-bit — the
    // shadowed diffuse is dark enough that a 12% tint rounds away — which is exactly why
    // the default has to be a colour someone chose to see.
    glm::vec3  shadowTint{0.86f, 0.74f, 0.78f};
    NprKey     key     = NprKey::Off;
    float      keyStrength = 0.35f;    // the key's share of the world light's diffuse
    glm::vec3  keyDir{0.35f, -0.55f, 0.76f};   // character-relative key (NprKey::Fixed)
    bool       smoothedNormals = false;   // light the secondary normals (E), keep the mesh
    float      normalMaskBias  = 1.f;     // scale on the generated mask (F), 0 = ignore it
    bool       specular  = false;         // stylized hard-threshold specular (G)
    float      specStrength = 0.35f;
    glm::vec3  specTint{1.f, 1.f, 1.f};
    bool       rim       = false;         // character-only rim light (H)
    float      rimStrength = 0.30f;
    glm::vec3  rimTint{1.f, 1.f, 1.f};
    float      outlineScale = 1.f;        // recovered hull width × this (I), 1 = recovered

    // Copies the #25 experiment switches from `other` and NOTHING else: the recovered
    // row (toon) and the frame options (fog, unlit) are not part of this harness, and an
    // assignment of the whole struct silently reset the toon row when it was tried.
    void copyExperimentsFrom(const Appearance& other) {
        bands = other.bands;
        bandSoftness = other.bandSoftness;
        shadowTint = other.shadowTint;
        key = other.key;
        keyStrength = other.keyStrength;
        keyDir = other.keyDir;
        smoothedNormals = other.smoothedNormals;
        normalMaskBias = other.normalMaskBias;
        specular = other.specular;
        specStrength = other.specStrength;
        specTint = other.specTint;
        rim = other.rim;
        rimStrength = other.rimStrength;
        rimTint = other.rimTint;
        outlineScale = other.outlineScale;
    }

    // True when any #25 experiment is on, i.e. the fragment shader will take the NPR
    // path. Only the fillDrawData predicates use this; the shader tests its own bits.
    bool nprActive() const {
        return bands != NprBands::Off || key != NprKey::Off || smoothedNormals ||
               specular || rim;
    }
};

struct Options {
    bool textures = true;   // resolve .cnv textures; false binds a 1x1 white instead
};

struct Stats {
    size_t draws           = 0;
    size_t textures        = 0;
    size_t paletteMatrices = 0;
    int    textured        = 0;
    int    untextured      = 0;
    int    decals          = 0;
    int    effects         = 0;
    int    outlines        = 0;   // toon outline hulls queued (issue #21)
    int    shadowCasters   = 0;   // draws submitted to the shadow map (issue #21 row 1)
    int    shadowReceivers = 0;   // stage draws marked to sample it
    int    nprMeshes       = 0;   // meshes given a secondary lighting normal (issue #25)
    size_t nprVertices     = 0;   // vertices that received one
};

// Which blend/depth/cull variant draws an item. The order below is also the
// submission order: the toon outline hulls first (issue #21 — they belong behind the
// surfaces they surround), then lit opaque geometry, then multiply decals over it, then
// additive effect cards last. Classification lives in scene_renderer.cpp (classifyPass);
// the asset layer's SceneModel::role is the only effect signal the renderer may
// read, because shipped material terms do not distinguish effect cards (R2).
enum class Pass : uint8_t { Outline = 0, Opaque = 1, Decal = 2, Effect = 3 };
inline constexpr size_t kPassCount = 4;

class SceneRenderer {
public:
    SceneRenderer() = default;
    ~SceneRenderer();
    SceneRenderer(const SceneRenderer&) = delete;
    SceneRenderer& operator=(const SceneRenderer&) = delete;

    // Borrows device/queue/instance from the context; owns everything it creates.
    bool init(const gpu::Context&, std::string& error);
    void shutdown();

    // Uploads geometry, textures and the draw list for `scene`. `worlds` is the posed
    // hierarchy per model (in scene order), `modelMatrices` the entity transform per
    // model — a weapon's is its owning character's attachment frame.
    bool setScene(const xm::Scene& scene, const std::vector<std::vector<glm::mat4>>& worlds,
                  const std::vector<glm::mat4>& modelMatrices, const Options&, std::string& error);

    // Re-fills the palette storage from a new pose. Animation changes the pose every
    // frame while the geometry stays put, so this is deliberately not part of
    // setScene: uploading vertex and index buffers per frame would be the whole cost
    // of the scene for nothing.
    void updatePose(const std::vector<std::vector<glm::mat4>>& worlds);

    // Re-points every draw at new per-model transforms (entity placement, weapon
    // bones following animated rigs). DrawUniforms rebuild from draws_ on every
    // render(), so this takes effect on the next frame; a no-op before setScene.
    void setModelMatrices(const std::vector<glm::mat4>& modelMatrices);

    // Effect-card INSTANCES (issue #17). A scene model has exactly one placement in
    // modelMatrices, so N live cards that share one .X could only ever draw once — the
    // last card won. An instance list adds extra draws of an already-loaded model at
    // arbitrary matrices, which is what a bounded live-card set needs. Instances are
    // rebuilt into the draw list on change; they are meant for Effect-pass models (they
    // are appended last, inside that pass), and setModelMatrices() leaves them alone.
    struct EffectInstance {
        int       modelIndex = -1;
        glm::mat4 model{1.f};
        // Keep the instance's own orientation instead of yawing it to face the camera.
        // An effect CARD is a flat quad and wants the yaw; a shot's model is a solid the
        // original draws with its own transform (FUN_005f60b0 composes scale, rotation and
        // translation into the model's matrix, game/shot_visual.h), so it opts out.
        // Default true keeps every existing instance byte-identical.
        bool      billboard = true;
    };
    void setEffectInstances(const std::vector<EffectInstance>& instances);
    // Grows the per-draw uniform buffer (and rebinds it) when the draw list outgrows it.
    bool ensureDrawCapacity(size_t draws, std::string& error);

    void setCamera(const glm::mat4& viewProj);
    // Camera eye in world space, for effect-card billboarding. The viewProj alone
    // cannot yield it (a perspective product does not separate into eye and
    // projection), and main.cpp is the only caller that knows the eye — so until
    // the caller wires this, billboarding stays dormant and every capture is
    // byte-identical to before. See EFFECTS-BILLBOARD.md.
    void setEye(const glm::vec3& eye);
    void setFog(const xm::StageEnv&);
    void setAppearance(const Appearance&);

    bool render(const Target&, std::string& error);

    // One pass, N views (issue #12). Colour and depth clear once, then each view sets its
    // own viewport and scissor to its cell, binds that view's camera uniform and draws the
    // whole scene. `views.size() <= 1` defers to render() — the byte-identical single-view
    // path the banked captures and parity recipes were made with — and at most
    // kMaxViewCameras views are accepted.
    bool renderViews(const Target&, const std::vector<ViewCamera>& views, std::string& error);

    // Optional UI compositing for verification captures: invoked after the 3D pass
    // into the capture encoder, before copy-to-readback. Uses only WebGPU types so
    // render/ never includes ui/ headers; the caller adapts. Null keeps current
    // behavior, and existing captures byte-identical.
    using UiHook = bool (*)(WGPUCommandEncoder, WGPUTextureView, WGPUTextureFormat,
                            uint32_t, uint32_t, void* userdata);
    // Renders width x height offscreen into an RGBA8Unorm texture and reads the pixels
    // back (RGBA8, tightly packed). Only verification needs this; the window path
    // never calls it. Non-square matters for verification: the DX9 reference frames
    // are 800x600, and comparing them against a square capture would measure the
    // aspect ratio rather than the renderer.
    // Captures a frame that has no 3D scene — a front-end screen — by running only the UI
    // hook into a cleared target. `capture()` cannot serve this: it renders the scene first
    // and fails with "renderer has no scene" when nothing was ever submitted, which is
    // every menu frame. The two share one implementation so the readback path cannot drift.
    // `views` is the split-screen variant of the scene pass: null (or a single view) keeps
    // the historical camera_ path, more than one goes through renderViews.
    bool captureUi(uint32_t width, uint32_t height, std::vector<uint8_t>& rgba,
                   std::string& error, UiHook uiHook = nullptr, void* uiUserdata = nullptr,
                   const std::vector<ViewCamera>* views = nullptr);

    bool capture(uint32_t width, uint32_t height, std::vector<uint8_t>& rgba,
                 std::string& error, UiHook uiHook = nullptr, void* uiUserdata = nullptr,
                 const std::vector<ViewCamera>* views = nullptr);

    // Issue #25's cost measurement: render `frames` frames of the CURRENT scene state into
    // one offscreen target, waiting for the GPU after each submit, and report the mean
    // wall-clock milliseconds per frame in `msPerFrame`. This is the only honest number a
    // headless run can produce — the per-iteration delta the demo already prints is a
    // CPU-side loop delta (0.002 ms, i.e. the renderer never blocks), so it says nothing
    // about what a technique costs. Absolute values are a fixed-rate function of this
    // machine and driver; what the experiment compares is the same command with one
    // switch flipped, on the same run of the same binary.
    bool benchmark(uint32_t width, uint32_t height, int frames, double& msPerFrame,
                   std::string& error, const std::vector<ViewCamera>* views = nullptr);
    bool captureImpl(uint32_t width, uint32_t height, std::vector<uint8_t>& rgba,
                     std::string& error, UiHook uiHook, void* uiUserdata, bool withScene,
                     const std::vector<ViewCamera>* views);

    bool capture(uint32_t size, std::vector<uint8_t>& rgba, std::string& error,
                 UiHook uiHook = nullptr, void* uiUserdata = nullptr) {
        return capture(size, size, rgba, error, uiHook, uiUserdata);
    }

    const Stats& stats() const { return stats_; }

    // The depth attachment the last frame rendered into, so a later pass on the same
    // encoder can depth-test against the scene instead of drawing over it (debug_prims
    // is the caller). Owned here and valid until the next render()/capture(); the
    // format is pinned to Depth24PlusStencil8, which such a pass must match, because
    // WebGPU validates attachment formats rather than coercing them.
    WGPUTextureView depthView() const { return depthView_; }

    // Writes view 0's shadow map (its alpha channel) as a binary PGM (issue #21 row 1).
    // Verification only: a map that silently stays empty looks exactly like a receiver bug
    // from the outside, and this is the only way to tell the two apart in a headless run.
    // main.cpp gates it behind DSH_DUMP_SHADOW.
    bool dumpShadowMap(const std::string& path, std::string& error);

private:
    struct DrawItem {
        WGPUBuffer vbuf = nullptr, ibuf = nullptr;   // borrowed; owned by buffers_
        // Borrowed secondary lighting-normal stream (issue #25), or the shared zero
        // stream for a mesh that has none. Always valid: the pipeline's second vertex
        // layout is present on every pass.
        WGPUBuffer nprbuf = nullptr;
        uint32_t   firstIndex = 0, indexCount = 0;
        uint32_t   paletteOffset = 0;
        uint32_t   flags = 0;                        // from the material, per draw
        int        texture = -1;                     // -1 -> the 1x1 white fallback
        Pass       pass = Pass::Opaque;
        size_t     modelIndex = 0;   // owning model, for per-frame re-placement
        glm::mat4  model{1.f};
        glm::vec4  baseColor{1.f};                   // material diffuse (D3DX faceColor)
        glm::vec4  emissive{0.f, 0.f, 0.f, 1.f};     // material Emissive (the toon effect's
                                                     // MaterialColor, issue #21)
        // Cylindrical-billboard candidate: mesh-space pivot (submesh bounds center),
        // authored facing yaw, plus the verdict from setScene. Only Effect-pass
        // draws from unskinned meshes are ever marked; ground-plane cards are
        // excluded (see .cpp).
        glm::vec3  bbCenter{0.f};
        float      bbYaw0 = 0.f;
        bool       billboard = false;
        // True for an extra draw added by setEffectInstances: its matrix comes from the
        // instance list, so the per-model upload must not overwrite it.
        bool       instance = false;
        // This draw is one the original's toon technique covers (character or weapon):
        // the appearance switch turns it into kDrawToon at uniform-fill time.
        bool       toon = false;
        // This draw receives the character shadow (issue #21 row 1): the original's stage
        // technique is the only one that samples the map. Set for the stage role, and the
        // appearance switch turns it into kDrawShadowReceiver at uniform-fill time.
        bool       receiver = false;
        // Whether this mesh carries a secondary lighting normal (issue #25, E). The
        // per-frame tint/strength an experiment uses rides the draw uniform instead,
        // filled in fillDrawData from the appearance — the experiments are all
        // artist-chosen values, so nothing per-material is read here.
        bool       nprNormals = false;
    };

    // What updatePose() needs to rebuild one mesh's slice of the palette storage.
    struct MeshRecord {
        const xm::Model* model = nullptr;
        const xm::Mesh*  mesh  = nullptr;
        size_t           modelIndex = 0;
        uint32_t         paletteOffset = 0;
    };

    // The scene's own draws, before instances: setEffectInstances() rebuilds draws_ from
    // these so a frame with no instances costs exactly what it did before.
    size_t drawCapacity_ = 0;   // draws the uniform buffer currently holds (per view)
    std::vector<DrawItem> baseDrawList_;   // setScene's own draws, for the fallback path
    int    baseEffects_ = 0, baseDecals_ = 0;   // setScene's counts, before instances
    std::vector<DrawItem> drawTemplates_;
    std::vector<EffectInstance> effectInstances_;

    // One uploaded image and the view onto it. A scoped owner rather than a pair of
    // raw handles because two kinds of site release them: the vector that holds every
    // texture the current scene uploaded (setScene and shutdown share one releaser),
    // and a local that never reaches that vector at all — a failed upload, a capture
    // or benchmark target. The second kind is why the destructor exists: `benchmark`
    // alone has five exits, and an early return added to any of them would leak the
    // target silently. Movable (construction and assignment) so the type behaves in a
    // container; the moved-from handles are null, so exactly one Texture owns them.
    struct Texture {
        WGPUTexture     tex  = nullptr;
        WGPUTextureView view = nullptr;

        Texture() = default;
        ~Texture();
        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;
        Texture(Texture&&) noexcept;
        Texture& operator=(Texture&&) noexcept;
        void release();
    };

    // The pipelines for one target format, indexed [pass][npr]: Pass's own order is the
    // submission order the draw list is partitioned into, and npr selects the experiment
    // vertex entry point. Slots are created lazily and are null until asked for.
    //
    // What each pass carries:
    //   * outline: the toon hull, front-face culled (issue #21);
    //   * opaque: lit, depth-writing;
    //   * decal: multiply blend, no depth write, no cull;
    //   * effect: additive, unlit, no depth write, no cull.
    // The npr variant of each is the same state with shader entry `vs_npr`, which reads
    // the secondary lighting-normal stream and the outline-width uniform. A SEPARATE
    // entry point, not a branch inside one: a branch (or a `select`) changes how the
    // driver compiles the unmodified path too, and the OFF frame moved by a pixel when it
    // was tried — the identity every banked capture rests on. With no --npr flag no npr
    // slot is ever created, and only the opaque cell's is reachable at all: the render
    // loop asks for the experiment entry point on Opaque draws alone.
    struct Pipelines {
        WGPUTextureFormat  format = WGPUTextureFormat_Undefined;
        WGPURenderPipeline slots[kPassCount][2] = {};
    };

    // `npr` selects the experiment vertex entry point (issue #25); the pipeline is cached
    // per (format, pass, entry) so enabling an experiment builds one extra variant.
    WGPURenderPipeline pipelineFor(WGPUTextureFormat, Pass, bool npr, std::string& error);
    bool ensureDepth(uint32_t width, uint32_t height, std::string& error);
    // A 1x1 RGBA8 texture of one colour and its view: the two placeholders the bind
    // groups need (white where a material resolves no texture, opaque black where no
    // shadow map was rendered). Leaves both handles null if creation fails, for the
    // caller's own completeness check.
    void createSolidTexture(uint32_t rgba, WGPUTexture& tex, WGPUTextureView& view);
    // The sampler state every binding here shares, differing only in address mode; see
    // the definition. Null if creation fails, which init()'s check catches.
    WGPUSampler createSampler(WGPUAddressMode addressMode);
    // Uploads the texture a material names and hands back its index in textures_
    // through `index`. False is a failed upload, and the caller must give up the
    // scene; true with an index of -1 is the ordinary "this draw has no texture".
    // The definition says why those two are not both -1.
    bool uploadTexture(const xm::SceneModel&, const std::string& name, bool mipmapped, int& index,
                       std::string& error);
    // The shadow map (issue #21 row 1). One light-space target per view, because the
    // original builds its light matrix and runs the caster pass inside the per-view loop
    // (FUN_006396f0:0x639b80/0x639b8c); a view's receiver reads the map its own caster
    // pass wrote. Created on first use by the appearance switch, so a run with shadows
    // off allocates nothing beyond the 1x1 placeholder the bind group needs.
    struct ShadowTarget {
        WGPUTexture     tex = nullptr, depth = nullptr;
        WGPUTextureView view = nullptr, depthView = nullptr;
        WGPUBindGroup   group = nullptr;   // group 3: the map + its sampler
    };
    // Lazy creation of the caster pass's pipeline, which needs only the shadow layout
    // and the model shader; cached for the process like the main pipelines.
    bool ensureShadowPipeline(std::string& error);
    bool ensureShadowTarget(size_t view, std::string& error);
    // The caster pass itself (issue #21 row 1): one render pass per view into that
    // view's map, drawing the toon technique's own surface set. `views` as in renderImpl.
    bool renderShadowCasters(const Target&, const std::vector<ViewCamera>* views,
                             std::string& error);
    void releaseShadowTargets();
    // Every GPU object that belongs to the loaded scene: the vertex/index buffers, the
    // uploaded textures and their bind groups, the draw bind group and the palette and
    // draw uniform buffers. setScene() calls it to replace a scene, shutdown() to tear
    // one down; keeping it in one place is what stops the two release lists drifting.
    void releaseSceneResources();
    // The shared scene pass. `views` null (or a single entry) is the single-view path:
    // camera_, cameraBuffer_, drawBuffer_ offset 0, no viewport/scissor calls. More than
    // one entry is the split-screen path, and needs ensureViewCameras().
    bool renderImpl(const Target&, const std::vector<ViewCamera>* views, std::string& error);
    // One camera uniform buffer + bind group per view cell, created on first use. Four
    // separate buffers rather than one strided buffer: an offset binding has to respect
    // the adapter's minUniformBufferOffsetAlignment, and separate buffers cannot get it
    // wrong (the uniform itself is tens of bytes).
    bool ensureViewCameras(std::string& error);
    // Per-draw uniforms for every draw in draws_, written from `dst` with
    // xm::kDrawStride spacing. Split out because billboard yaw is per camera: each view
    // needs its own copy of the draw block.
    void fillDrawData(const glm::vec3& eye, bool haveEye, uint8_t* dst);

    WGPUInstance instance_ = nullptr;   // borrowed from the context
    WGPUDevice   device_   = nullptr;
    WGPUQueue    queue_    = nullptr;

    WGPUBindGroupLayout bindGroupLayouts_[4] = {nullptr, nullptr, nullptr, nullptr};
    WGPUPipelineLayout  pipelineLayout_ = nullptr;
    // The caster pass's own layout: groups 0 and 1 only. The map is the *target* of that
    // pass, not a binding, and a pipeline layout that names group 3 would force every
    // shadow draw to bind it for nothing.
    WGPUPipelineLayout  shadowPipelineLayout_ = nullptr;
    WGPURenderPipeline  shadowPipeline_ = nullptr;
    WGPUShaderModule    shader_ = nullptr;
    WGPUSampler         sampler_ = nullptr;

    WGPUTexture     whiteTex_ = nullptr;
    WGPUTextureView whiteView_ = nullptr;
    // The toon ramp (issue #21), uploaded once at init through the same bundle-first
    // read + xm::decodeCnvImage the texture cache uses. `toonRampView_` falls back to
    // whiteView_ when the game data has no ramp, and `toonRampReady_` stays false so the
    // toon flag is never set: without the shipped bitmap the toggle has nothing honest
    // to sample, and ON must not become a constant standing in for it.
    WGPUTexture     toonRampTex_ = nullptr;
    WGPUTextureView toonRampView_ = nullptr;
    WGPUSampler     toonRampSampler_ = nullptr;
    bool            toonRampReady_ = false;
    WGPUBindGroup   cameraGroup_ = nullptr;
    WGPUBindGroup   drawGroup_ = nullptr;                    // group 1, dynamic offset
    std::vector<WGPUBindGroup> textureGroups_;               // [0] = white, then one per texture
    // The shadow map's sampler (issue #21 row 1): clamp + linear, which is as close as
    // WebGPU gets to the original's border-clamped Tex1 — the shader's own range test
    // supplies the border behaviour the address mode cannot.
    WGPUSampler     shadowSampler_ = nullptr;
    // The placeholder group 3 for frames without the shadow pass (and for views whose map
    // was never created): a 1x1 opaque-black texture, i.e. exactly what the original's
    // cleared map reads as. Every pipeline that samples the map binds this or a real map,
    // so no draw ever runs against an incomplete group.
    WGPUTexture     shadowPlaceholderTex_ = nullptr;
    WGPUTextureView shadowPlaceholderView_ = nullptr;
    WGPUBindGroup   shadowPlaceholderGroup_ = nullptr;
    ShadowTarget    shadowTargets_[kMaxViewCameras];

    WGPUBuffer cameraBuffer_ = nullptr;
    // Split-screen camera slots (issue #12): one uniform buffer and bind group per view
    // cell, created by ensureViewCameras() the first time a frame has more than one view.
    WGPUBuffer   viewCameraBuffers_[kMaxViewCameras] = {};
    WGPUBindGroup viewCameraGroups_[kMaxViewCameras] = {};
    WGPUBuffer drawBuffer_ = nullptr;
    WGPUBuffer paletteBuffer_ = nullptr;

    std::vector<Pipelines> pipelines_;
    std::vector<DrawItem>  draws_;
    std::vector<MeshRecord> meshes_;
    std::vector<WGPUBuffer> buffers_;      // owned vertex/index buffers
    std::vector<Texture>    textures_;     // owned, deduplicated by image
    // Images are shared between materials, so each is uploaded once and draws index
    // into textures_ through this map. Keyed by image pointer and cleared with the
    // list it indexes (releaseSceneResources), never separately.
    std::unordered_map<const xm::CnvImage*, int> texIndex_;
    std::vector<glm::mat4>  palette_;      // CPU copy, uploaded by updatePose()

    WGPUTexture     depthTex_ = nullptr;
    WGPUTextureView depthView_ = nullptr;
    uint32_t        depthWidth_ = 0, depthHeight_ = 0;

    xm::CameraUniform camera_{};
    Appearance        appearance_{};
    Stats             stats_{};
    // Billboard eye. haveEye_ is false until setEye() runs, which keeps the
    // billboard path dormant (and captures byte-identical) on callers that were
    // written before it existed.
    glm::vec3         eye_{0.f};
    bool              haveEye_ = false;
};

}  // namespace render
