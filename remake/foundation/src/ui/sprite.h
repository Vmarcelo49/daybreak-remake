#pragma once
// Sprite batch: textured 2D quads with alpha blending for the UI/HUD pass.
//
// This is the WebGPU counterpart of the two DX9 2D paths in remake/src/render/:
// hud.cpp (D3DXSprite bars: back quad at full width plus a fill quad truncated
// to (int)(w * frac)) and ui_image.cpp (XYZRHW quads, Z disabled, SrcAlpha /
/// InvSrcAlpha blending). Positions stay in viewport pixels with a top-left
// origin so those call sites transfer verbatim; the ui_wgsl vertex shader maps
// them to NDC.
//
// Frame model: immediate mode, rebuilt every frame from the caller's state —
// the batch holds no clock and no accumulator, so a variable-delta caller just
// re-pushes. The pass uses LoadOp::Load over the 3D frame (no depth buffer),
// and FIFO pacing stays the swapchain's job exactly as in the 3D path.
#include <webgpu/webgpu.h>

#include <cstdint>
#include <string>
#include <vector>

namespace ui {

// Straight-alpha float colour. fromRgb8 converts D3DCOLOR_XRGB-style triples by
// value so surveyed DX9 colours transfer without reinterpretation.
struct UiColor {
    float r = 1.f, g = 1.f, b = 1.f, a = 1.f;
};

inline UiColor fromRgb8(uint8_t r, uint8_t g, uint8_t b, float a = 1.f) {
    return UiColor{r / 255.f, g / 255.f, b / 255.f, a};
}

// Viewport-pixel rect, top-left origin (DX9 viewport pixels, not NDC).
struct UiRect {
    float x = 0.f, y = 0.f, w = 0.f, h = 0.f;
};

struct UiViewport {
    uint32_t w = 0, h = 0;
};

// Optional per-quad clip in viewport pixels. Disabled means unclipped; enabling
// it routes the quad through wgpuRenderPassEncoderSetScissorRect, which is how
// bars and panels stay inside their frames on resize.
struct UiClip {
    bool  enabled = false;
    float x = 0.f, y = 0.f, w = 0.f, h = 0.f;
};

// Clamps a clip to the viewport. Pure host-side so layout code is unit-testable
// without a device.
inline UiClip clampClip(const UiClip& c, const UiViewport& vp) {
    if (!c.enabled) return c;
    UiClip out = c;
    if (out.x < 0.f) { out.w += out.x; out.x = 0.f; }
    if (out.y < 0.f) { out.h += out.y; out.y = 0.f; }
    if (out.x + out.w > (float)vp.w) out.w = (float)vp.w - out.x;
    if (out.y + out.h > (float)vp.h) out.h = (float)vp.h - out.y;
    if (out.w < 0.f) out.w = 0.f;
    if (out.h < 0.f) out.h = 0.f;
    return out;
}

// Resolves a clip to integer scissor pixels. Returns false when the quad is
// fully clipped away (caller skips it); a disabled clip yields the viewport.
inline bool clipToScissor(const UiClip& c, const UiViewport& vp, uint32_t& x, uint32_t& y,
                          uint32_t& w, uint32_t& h) {
    if (!c.enabled) {
        x = 0;
        y = 0;
        w = vp.w;
        h = vp.h;
        return vp.w > 0 && vp.h > 0;
    }
    const UiClip k = clampClip(c, vp);
    if (k.w <= 0.f || k.h <= 0.f) return false;
    x = (uint32_t)k.x;
    y = (uint32_t)k.y;
    w = (uint32_t)k.w;
    h = (uint32_t)k.h;
    if (x >= vp.w || y >= vp.h) return false;
    if (x + w > vp.w) w = vp.w - x;
    if (y + h > vp.h) h = vp.h - y;
    return w > 0 && h > 0;
}

// Viewport pixels (y down) to NDC (y up, WebGPU convention on every backend).
// Mirrors the ui_wgsl mapping so CPU culling math agrees with the shader.
inline void pixelsToNdc(float px, float py, const UiViewport& vp, float& nx, float& ny) {
    nx = px / (float)vp.w * 2.f - 1.f;
    ny = 1.f - py / (float)vp.h * 2.f;
}

// Fill width of a fractional bar in whole pixels. Clamps first, truncates like
// the DX9 Hud::bar (`(int)(w * frac)`), so 0 < frac < 1/w draws nothing and
// frac >= 1 covers the back quad exactly.
inline int barFillWidth(int w, float frac) {
    if (w <= 0) return 0;
    if (frac <= 0.f) return 0;
    if (frac >= 1.f) return w;
    return (int)((float)w * frac);
}

// One CPU-side quad: destination pixels, 0..1 UVs, tint, texture slot.
struct UiQuad {
    UiRect  dst{0.f, 0.f, 0.f, 0.f};
    UiRect  uv{0.f, 0.f, 1.f, 1.f};
    UiColor color{};
    int     texture = -1;   // -1 selects the 1x1 white fallback (solid quads)
    UiClip  clip{};
};

// GPU vertex: pixel position, UV, straight-alpha tint. Must match ui_wgsl.
struct UiVertex {
    float x, y, u, v, r, g, b, a;
};

class SpriteRenderer {
public:
    // Fixed worst case: a full HUD is dozens of quads, so 2048 bounds the
    // vertex buffer up front and turns overflow into a counted, deterministic
    // drop instead of a mid-frame allocation.
    static constexpr uint32_t kMaxQuads = 2048;

    SpriteRenderer() = default;
    ~SpriteRenderer();
    SpriteRenderer(const SpriteRenderer&) = delete;
    SpriteRenderer& operator=(const SpriteRenderer&) = delete;

    // Borrows device/queue; owns everything it creates. No surface or present
    // call is involved, so no backend #if is needed (see docs/UI-DESIGN.md).
    bool init(WGPUDevice device, WGPUQueue queue, std::string& error);
    void shutdown();

    // Uploads a decoded RGBA8 image, top-down, stride = width * 4 — exactly what
    // xm::CnvImage::rgba holds, so CNV textures transfer without conversion
    // (BMP-backed callers decode to the same layout first). Returns the slot id
    // for pushTextured, or -1 on failure. Slot 0 is the 1x1 white fallback.
    int addTexture(uint32_t w, uint32_t h, const void* rgba, std::string& error);
    // Re-uploads into an existing slot, keeping its id, and recreates the texture when
    // the pixel size changed. The UI text atlas needs this: it grows by doubling its
    // height as glyphs are first drawn, which moves every tile's UV denominator, so the
    // caller re-uploads instead of leaking a slot per growth.
    bool updateTexture(int slot, uint32_t w, uint32_t h, const void* rgba, std::string& error);
    // Drops uploaded textures (scene change); the white fallback survives.
    void clearTextures();

    // Starts a frame's batch. The viewport is re-taken every frame rather than
    // cached, so a resize between frames cannot desynchronise pixels from NDC.
    void beginFrame(uint32_t viewportW, uint32_t viewportH);

    // Pushes one quad; false when the batch is full (counted in dropped()).
    bool pushQuad(const UiQuad& q);
    bool pushSolid(const UiRect& dst, UiColor color, const UiClip& clip = {});
    bool pushTextured(int texture, const UiRect& dst, const UiRect& uv, UiColor tint,
                      const UiClip& clip = {});

    // Encodes the batch as one Load-preserving pass over `view` (the 3D frame
    // stays underneath). `encoder` is the caller's — typically the same encoder
    // the scene renderer just recorded into — so HUD and 3D share one submit
    // and one FIFO present.
    bool render(WGPUCommandEncoder encoder, WGPUTextureView view, WGPUTextureFormat format,
                std::string& error);

    size_t   quads() const { return quads_.size(); }
    size_t   dropped() const { return dropped_; }
    uint32_t viewportW() const { return viewport_.w; }
    uint32_t viewportH() const { return viewport_.h; }

private:
    struct Texture {
        WGPUTexture     tex = nullptr;
        WGPUTextureView view = nullptr;
        WGPUBindGroup   group = nullptr;
    };
    struct Pipeline {
        WGPUTextureFormat  format = WGPUTextureFormat_Undefined;
        WGPURenderPipeline pipeline = nullptr;
    };

    WGPURenderPipeline pipelineFor(WGPUTextureFormat format, std::string& error);
    bool ensureBuffers(std::string& error);
    // Texture + view + bind group as one unit; the pair below is the only place that
    // creates or destroys them, so addTexture/updateTexture/clearTextures cannot drift.
    bool createTexture(Texture& t, uint32_t w, uint32_t h, const void* rgba, std::string& error);
    static void destroyTexture(Texture& t);

    WGPUDevice device_ = nullptr;   // borrowed
    WGPUQueue  queue_ = nullptr;    // borrowed

    WGPUShaderModule    shader_ = nullptr;
    WGPUBindGroupLayout vpLayout_ = nullptr;
    WGPUBindGroupLayout texLayout_ = nullptr;
    WGPUPipelineLayout  layout_ = nullptr;
    WGPUSampler         sampler_ = nullptr;
    WGPUBuffer          vpBuffer_ = nullptr;
    WGPUBindGroup       vpGroup_ = nullptr;
    WGPUBuffer          vbuf_ = nullptr;
    WGPUBuffer          ibuf_ = nullptr;

    std::vector<Texture>  textures_;    // [0] is always the 1x1 white fallback
    std::vector<Pipeline> pipelines_;   // one pipeline per target format
    std::vector<UiQuad>   quads_;

    UiViewport viewport_{0, 0};
    size_t     dropped_ = 0;
};

}  // namespace ui
