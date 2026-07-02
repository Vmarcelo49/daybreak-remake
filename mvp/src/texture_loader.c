/**
 * texture_loader.c — D3D texture loading from BMP/DAT files
 *
 * Translated from:
 *   - FUN_006560c0 (Texture loader)
 *   - FUN_00656200 (Texture release)
 *
 * Original behavior:
 *   - FUN_006560c0(path) → loads BMP from file or archive, returns IDirect3DTexture9*
 *   - FUN_00656200(tex) → releases texture
 *   - Texture data could come from loose file OR daybreakXX.dat archive
 *
 * For MVP+3 we use D3DXCreateTextureFromFileA which handles BMP, PNG, JPG, DDS.
 * Archive support is via dat_archive.h (DatResource_LoadFile → D3DXCreateTextureFromFileInMemory).
 */

#include "engine.h"
#include "dat_archive.h"
#include "d3d_utils.h"
#include <stdio.h>

/* ============================================================
 * LoadTextureFromFile — translated from FUN_006560c0
 *
 * Tries:
 *   1. Direct file load via D3DXCreateTextureFromFileA
 *   2. (Future) Archive lookup via DatArchive_ReadFile + D3DXCreateTextureFromFileInMemory
 *
 * Returns: texture pointer or NULL on failure
 * ============================================================ */

IDirect3DTexture9 *LoadTextureFromFile(EngineState *state, const char *path)
{
    if (!state || !state->device || !path) {
        return NULL;
    }

    IDirect3DTexture9 *texture = NULL;

    /* 1. Try direct file load */
    HRESULT hr = D3DXCreateTextureFromFileA(state->device, path, &texture);
    if (SUCCEEDED(hr) && texture) {
        return texture;
    }

    /* 2. Try loading via DatResource (handles archive XOR if needed) */
    uint32_t size = 0;
    void *data = DatResource_LoadFile(path, &size);
    if (data) {
        hr = D3DXCreateTextureFromFileInMemory(state->device, data, size, &texture);
        free(data);
        if (SUCCEEDED(hr) && texture) {
            return texture;
        }
    }

    return NULL;
}

/* ============================================================
 * ReleaseTexture — translated from FUN_00656200
 * ============================================================ */

void ReleaseTexture(IDirect3DTexture9 *texture)
{
    if (texture) {
        IDirect3DTexture9_Release(texture);
    }
}

/* ============================================================
 * GetTextureSize — translated from FUN_00656380
 *
 * Returns width/height of a texture's top-level mipmap.
 * ============================================================ */

void GetTextureSize(IDirect3DTexture9 *texture, uint32_t *width, uint32_t *height)
{
    if (!texture) {
        *width = 0;
        *height = 0;
        return;
    }

    D3DSURFACE_DESC desc;
    HRESULT hr = IDirect3DTexture9_GetLevelDesc(texture, 0, &desc);
    if (SUCCEEDED(hr)) {
        *width = desc.Width;
        *height = desc.Height;
    } else {
        *width = 0;
        *height = 0;
    }
}
