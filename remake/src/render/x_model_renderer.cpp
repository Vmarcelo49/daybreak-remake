// =============================================================================
//  x_model_renderer.cpp — view/proj/light setup, ported from X2Blend viewer.
// =============================================================================
#include "x_model_renderer.h"

#include <cmath>

namespace daybreak {

void XModelRenderer::setup_frame(IDirect3DDevice9* device,
                                  int viewportW, int viewportH,
                                  const CameraState& cam) const {
    if (!device) return;

    float theta = cam.yaw;
    float phi   = cam.pitch;
    float x = cam.target.x + cam.distance * cosf(phi) * sinf(theta);
    float y = cam.target.y + cam.distance * sinf(phi);
    float z = cam.target.z - cam.distance * cosf(phi) * cosf(theta);

    D3DXVECTOR3 eye(x, y, z);
    D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
    D3DXMATRIX view;
    D3DXMatrixLookAtLH(&view, &eye, &cam.target, &up);
    device->SetTransform(D3DTS_VIEW, &view);

    float aspect = (viewportH > 0) ? float(viewportW) / float(viewportH) : 1.0f;
    D3DXMATRIX proj;
    D3DXMatrixPerspectiveFovLH(&proj, D3DXToRadian(60.0f), aspect, 0.1f, 1000.0f);
    device->SetTransform(D3DTS_PROJECTION, &proj);

    device->SetRenderState(D3DRS_LIGHTING,         TRUE);
    device->SetRenderState(D3DRS_AMBIENT,          D3DCOLOR_COLORVALUE(0.35f, 0.35f, 0.35f, 1.0f));
    device->SetRenderState(D3DRS_ZENABLE,          TRUE);
    device->SetRenderState(D3DRS_CULLMODE,         D3DCULL_CCW);
    device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    device->SetRenderState(D3DRS_SRCBLEND,         D3DBLEND_SRCALPHA);
    device->SetRenderState(D3DRS_DESTBLEND,        D3DBLEND_INVSRCALPHA);
    device->SetRenderState(D3DRS_ALPHATESTENABLE,  TRUE);
    device->SetRenderState(D3DRS_ALPHAREF,         0x08);
    device->SetRenderState(D3DRS_ALPHAFUNC,        D3DCMP_GREATEREQUAL);

    device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
    device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

    D3DLIGHT9 light{};
    light.Type      = D3DLIGHT_DIRECTIONAL;
    light.Diffuse   = { 0.85f, 0.85f, 0.85f, 1.0f };
    light.Specular  = { 0.30f, 0.30f, 0.30f, 1.0f };
    light.Ambient   = { 0.20f, 0.20f, 0.20f, 1.0f };
    light.Direction = { 0.5f, -1.0f, 0.5f };
    device->SetLight(0, &light);
    device->LightEnable(0, TRUE);
}

} // namespace daybreak
