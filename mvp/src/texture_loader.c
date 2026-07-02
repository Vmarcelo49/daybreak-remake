/**
 * texture_loader.c — D3D texture loading from .dat archives
 *
 * Translated from:
 *   - FUN_006560c0 (Texture loader)
 *   - FUN_00656200 (Texture release)
 *
 * Original behavior:
 *   - FUN_006560c0(path) → loads BMP via DatResource (which searches .dat archives)
 *   - Returns IDirect3DTexture9* or NULL
 *
 * For MVP+3 we:
 *   1. Look up file in loaded .dat archives via DatArchive_ReadFile
 *   2. Decode the BMP data (XOR already done by DatArchive)
 *   3. Use D3DXCreateTextureFromFileInMemory to create the texture
 *
 * Note: per user feedback, the original game's "direct file" mode is not
 * easily activated, so we ONLY use archive mode (matches original behavior).
 */

#include "engine.h"
#include "dat_archive.h"
#include "d3d_utils.h"
#include <stdio.h>

/* ============================================================
 * LoadTextureFromFile — translated from FUN_006560c0
 *
 * Loads a BMP/texture from the loaded .dat archives.
 * Returns: texture pointer or NULL on failure.
 * ============================================================ */

IDirect3DTexture9 *LoadTextureFromFile(EngineState *state, const char *path)
{
    if (!state || !state->device || !path) {
        return NULL;
    }

    /* 1. Load file from .dat archive (with XOR decode) */
    uint32_t size = 0;
    void *data = DatArchive_ReadFile(NULL, path, &size);
    if (!data || size == 0) {
        free(data);
        return NULL;
    }

    /* 2. Create D3D texture from the decoded BMP data in memory */
    IDirect3DTexture9 *texture = NULL;
    HRESULT hr = D3DXCreateTextureFromFileInMemory(state->device, data, size, &texture);
    free(data);

    if (FAILED(hr) || !texture) {
        return NULL;
    }

    return texture;
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
