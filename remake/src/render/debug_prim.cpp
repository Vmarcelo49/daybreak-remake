// =============================================================================
//  debug_prim.cpp — see debug_prim.h.
// =============================================================================
#include "render/debug_prim.h"

#include <cstdint>

namespace daybreak::render {

namespace {

// 12 triangles, two per face; winding is irrelevant (culling is off).
struct CubeVertex {
    float    x, y, z;
    D3DCOLOR c;
};
constexpr DWORD kFvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;

} // namespace

UnlitCubePass::UnlitCubePass(IDirect3DDevice9* device, bool alphaBlend,
                             bool worldSpace)
    : m_device(device), m_worldSpace(worldSpace) {
    if (!m_device) return;
    m_device->GetRenderState(D3DRS_LIGHTING, &m_prevLighting);
    m_device->GetRenderState(D3DRS_CULLMODE, &m_prevCull);
    m_device->GetRenderState(D3DRS_ALPHABLENDENABLE, &m_prevBlend);
    m_device->GetRenderState(D3DRS_ALPHATESTENABLE, &m_prevAlphaTest);
    m_device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
    m_device->GetTextureStageState(0, D3DTSS_COLOROP, &m_prevColorOp);
    m_device->GetTextureStageState(0, D3DTSS_COLORARG1, &m_prevColorArg1);
    m_device->GetTextureStageState(0, D3DTSS_ALPHAOP, &m_prevAlphaOp);
    m_device->GetTextureStageState(0, D3DTSS_ALPHAARG1, &m_prevAlphaArg1);
    m_device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
    m_device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
    m_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
    m_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
    m_device->GetFVF(&m_prevFvf);
    if (m_worldSpace) {
        m_device->GetTransform(D3DTS_WORLD, &m_prevWorld);
        D3DXMATRIX identity;
        D3DXMatrixIdentity(&identity);
        m_device->SetTransform(D3DTS_WORLD, &identity);
    }
    m_device->SetRenderState(D3DRS_LIGHTING, FALSE);
    m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, alphaBlend ? TRUE : FALSE);
    if (alphaBlend) {
        m_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
        m_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
    }
    m_device->SetFVF(kFvf);
}

UnlitCubePass::~UnlitCubePass() {
    if (!m_device) return;
    if (m_worldSpace) m_device->SetTransform(D3DTS_WORLD, &m_prevWorld);
    m_device->SetFVF(m_prevFvf);
    m_device->SetTextureStageState(0, D3DTSS_COLOROP, m_prevColorOp);
    m_device->SetTextureStageState(0, D3DTSS_COLORARG1, m_prevColorArg1);
    m_device->SetTextureStageState(0, D3DTSS_ALPHAOP, m_prevAlphaOp);
    m_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, m_prevAlphaArg1);
    m_device->SetRenderState(D3DRS_ALPHATESTENABLE, m_prevAlphaTest);
    m_device->SetRenderState(D3DRS_ALPHABLENDENABLE, m_prevBlend);
    m_device->SetRenderState(D3DRS_CULLMODE, m_prevCull);
    m_device->SetRenderState(D3DRS_LIGHTING, m_prevLighting);
}

void UnlitCubePass::draw(const D3DXVECTOR3& c, float h, D3DCOLOR color) {
    if (!m_device) return;
    const CubeVertex v[36] = {
        {c.x-h, c.y-h, c.z-h, color}, {c.x-h, c.y+h, c.z-h, color},
        {c.x+h, c.y+h, c.z-h, color}, {c.x-h, c.y-h, c.z-h, color},
        {c.x+h, c.y+h, c.z-h, color}, {c.x+h, c.y-h, c.z-h, color},
        {c.x-h, c.y-h, c.z+h, color}, {c.x+h, c.y+h, c.z+h, color},
        {c.x-h, c.y+h, c.z+h, color}, {c.x-h, c.y-h, c.z+h, color},
        {c.x+h, c.y-h, c.z+h, color}, {c.x+h, c.y+h, c.z+h, color},
        {c.x-h, c.y-h, c.z-h, color}, {c.x-h, c.y-h, c.z+h, color},
        {c.x-h, c.y+h, c.z+h, color}, {c.x-h, c.y-h, c.z-h, color},
        {c.x-h, c.y+h, c.z+h, color}, {c.x-h, c.y+h, c.z-h, color},
        {c.x+h, c.y-h, c.z-h, color}, {c.x+h, c.y+h, c.z+h, color},
        {c.x+h, c.y-h, c.z+h, color}, {c.x+h, c.y-h, c.z-h, color},
        {c.x+h, c.y+h, c.z-h, color}, {c.x+h, c.y+h, c.z+h, color},
        {c.x-h, c.y+h, c.z-h, color}, {c.x-h, c.y+h, c.z+h, color},
        {c.x+h, c.y+h, c.z+h, color}, {c.x-h, c.y+h, c.z-h, color},
        {c.x+h, c.y+h, c.z+h, color}, {c.x+h, c.y+h, c.z-h, color},
        {c.x-h, c.y-h, c.z-h, color}, {c.x+h, c.y-h, c.z+h, color},
        {c.x-h, c.y-h, c.z+h, color}, {c.x-h, c.y-h, c.z-h, color},
        {c.x+h, c.y-h, c.z-h, color}, {c.x+h, c.y-h, c.z+h, color},
    };
    m_device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, v, sizeof(CubeVertex));
}

} // namespace daybreak::render
