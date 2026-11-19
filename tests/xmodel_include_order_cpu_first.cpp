// tests/xmodel_include_order_cpu_first.cpp — CPU-first half of the issue #129 seam.
//
// This is the order xmodel.h's old #pragma once coupling forbade: a CPU-only consumer
// (physics/raycast.h) pulls assets/xmodel.h before the renderer sees it. With the WebGPU
// declarations gated behind XMODEL_WEBGPU inside that header, xm::CameraUniform was
// hidden here and this translation unit did not compile. It must now compile in either
// order; the sibling TU does the reverse and main() compares the two fingerprints.
#include "physics/raycast.h"
#include "render/scene_renderer.h"

unsigned xmodelCpuFirstFingerprint() {
    return static_cast<unsigned>(sizeof(xm::CameraUniform) + sizeof(xm::DrawUniform) +
                                 sizeof(xm::Vertex) + sizeof(xm::NprVertex) +
                                 xm::kVertexAttributeCount + xm::kDrawStride);
}
