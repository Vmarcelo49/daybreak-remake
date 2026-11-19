// tests/xmodel_include_order_webgpu_first.cpp — renderer-first half of the issue #129 seam.
//
// The order the old application had to use: the renderer (and its WebGPU helper header)
// before the CPU-only raycast header. Compiled together with the cpu-first TU, this pins
// that both orders see identical xm:: layouts and that neither hides the GPU helpers.
#include "render/scene_renderer.h"
#include "physics/raycast.h"

#include <cstdio>

unsigned xmodelCpuFirstFingerprint();  // sibling TU, compiled with the opposite order

unsigned xmodelWebgpuFirstFingerprint() {
    return static_cast<unsigned>(sizeof(xm::CameraUniform) + sizeof(xm::DrawUniform) +
                                 sizeof(xm::Vertex) + sizeof(xm::NprVertex) +
                                 xm::kVertexAttributeCount + xm::kDrawStride);
}

int main() {
    const unsigned cpuFirst = xmodelCpuFirstFingerprint();
    const unsigned webgpuFirst = xmodelWebgpuFirstFingerprint();
    if (cpuFirst == 0 || cpuFirst != webgpuFirst) {
        std::printf("FAIL: cpu-first=%u renderer-first=%u\n", cpuFirst, webgpuFirst);
        return 1;
    }
    std::printf("ok: both include orders see the same xmodel layouts (%u)\n", cpuFirst);
    return 0;
}
