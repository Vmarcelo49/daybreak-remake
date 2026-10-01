// =============================================================================
//  x_model_renderer.h — view/projection/light state for rendering an XModel.
//
//  Wraps the D3DX camera + lighting setup so main.cpp stays small.
// =============================================================================
#pragma once

#include <d3d9.h>
#include <d3dx9.h>

namespace daybreak {

struct CameraState {
    float yaw      = 0.0f;
    float pitch    = 0.0f;
    float distance = 5.0f;
    D3DXVECTOR3 target{ 0.0f, 0.0f, 0.0f };
};

class XModelRenderer {
public:
    // Sets up viewport-aspect perspective, orbit camera, directional light,
    // and the standard lit render states (z-enable, cull CCW, alpha-test,
    // linear sampler filtering).  Call once per frame before XModel::render.
    void setup_frame(IDirect3DDevice9* device, int viewportW, int viewportH,
                     const CameraState& cam) const;
};

} // namespace daybreak
