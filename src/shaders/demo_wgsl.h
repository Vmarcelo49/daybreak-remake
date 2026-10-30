#pragma once
// WGSL embedded in the binary rather than loaded from a file: the web build has no
// filesystem, so shaders (like all assets) must either be embedded or shipped
// through --preload-file. Embedding keeps one code path for every target.
namespace shaders {
inline constexpr const char* kDemoWGSL = R"WGSL(
struct Uniforms {
    transform : mat4x4<f32>,
};

@group(0) @binding(0) var<uniform> u : Uniforms;

struct VSOut {
    @builtin(position) position : vec4<f32>,
    @location(0) color : vec3<f32>,
};

@vertex
fn vs_main(@location(0) position : vec3<f32>, @location(1) color : vec3<f32>) -> VSOut {
    var out : VSOut;
    out.position = u.transform * vec4<f32>(position, 1.0);
    out.color = color;
    return out;
}

@fragment
fn fs_main(in : VSOut) -> @location(0) vec4<f32> {
    return vec4<f32>(in.color, 1.0);
}
)WGSL";
}  // namespace shaders
