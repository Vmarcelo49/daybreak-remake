/**
 * shader_load.c — CreateAllShaders (translated from FUN_0064ff80)
 *
 * Original loads 10 D3DX effects from data embedded in the binary:
 *   - 0x006a5f68 (3499 bytes)
 *   - 0x006a6cd8 (3640 bytes)
 *   - 0x006a7b10 (812 bytes)
 *   - 0x006a7e40 (1964 bytes)
 *   - 0x006a85f0 (1744 bytes)
 *   - 0x006a8cc0 (1920 bytes)
 *   - 0x006a9440 (1932 bytes)
 *   - + 3 more (total 10)
 *
 * For MVP, we load them from `shaders/effect_N.bin` files instead of
 * embedding in the binary. This is cleaner and lets us inspect/edit them.
 *
 * If the shaders directory is missing, MVP continues with a warning
 * (shaders are not needed for clear-screen rendering).
 */

#include "engine.h"
#include "d3d_utils.h"
#include <unknwn.h>
#include <stdio.h>

/* Shader file paths — must match the order in original FUN_0064ff80 */
static const char *const SHADER_FILES[NUM_SHADERS] = {
    "shaders/effect_0.bin",
    "shaders/effect_1.bin",
    "shaders/effect_2.bin",
    "shaders/effect_3.bin",
    "shaders/effect_4.bin",
    "shaders/effect_5.bin",
    "shaders/effect_6.bin",
    "shaders/effect_7.bin",
    "shaders/effect_8.bin",
    "shaders/effect_9.bin",
};

static bool LoadShaderFile(const char *path, void **out_data, DWORD *out_size)
{
    FILE *f = fopen(path, "rb");
    if (!f) {
        return false;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (size <= 0) {
        fclose(f);
        return false;
    }
    void *data = malloc(size);
    if (!data) {
        fclose(f);
        return false;
    }
    if (fread(data, 1, size, f) != (size_t)size) {
        free(data);
        fclose(f);
        return false;
    }
    fclose(f);
    *out_data = data;
    *out_size = (DWORD)size;
    return true;
}

bool CreateAllShaders(EngineState *state)
{
    int loaded = 0;

    for (int i = 0; i < NUM_SHADERS; i++) {
        void *shader_data = NULL;
        DWORD shader_size = 0;

        if (!LoadShaderFile(SHADER_FILES[i], &shader_data, &shader_size)) {
            /* MVP: continue without shader if file is missing.
             * Real game would show error and exit. */
            char msg[256];
            snprintf(msg, sizeof(msg),
                     "Warning: shader %d not found at %s\n"
                     "Continuing without shaders (visual artifacts expected).",
                     i, SHADER_FILES[i]);
            MessageBoxA(NULL, msg, "Shader Warning", MB_OK | MB_ICONWARNING);
            state->effects[i] = NULL;
            continue;
        }

        HRESULT hr = D3DXCreateEffect(
            state->device,
            shader_data,
            shader_size,
            NULL,  /* pDefines */
            NULL,  /* pInclude */
            0,     /* dwFlags */
            NULL,  /* pPool */
            &state->effects[i],
            NULL); /* ppCompilationErrors */

        free(shader_data);

        if (FAILED(hr)) {
            char msg[256];
            snprintf(msg, sizeof(msg),
                     "D3DXCreateEffect failed for shader %d (hr=0x%08lX)",
                     i, (unsigned long)hr);
            ShowError(msg, "Shader Error");
            state->effects[i] = NULL;
            continue;
        }

        loaded++;
    }

    /* MVP: succeed even if 0 shaders loaded (we just want to render clear screen) */
    if (loaded == 0) {
        MessageBoxA(NULL,
                    "No shaders loaded. MVP will only show clear screen.\n"
                    "Extract shaders from original DaybreakDX.exe to enable rendering.",
                    "Shader Notice",
                    MB_OK | MB_ICONINFORMATION);
    }

    return true;  /* always succeed in MVP */
}

void DestroyAllShaders(EngineState *state)
{
    for (int i = 0; i < NUM_SHADERS; i++) {
        if (state->effects[i]) {
            /* ID3DXEffect inherits IUnknown via ID3DXBaseEffect.
             * Use IUnknown vtable directly — Release is at index 2 in vtable. */
            IUnknown *unk = (IUnknown *)state->effects[i];
            unk->lpVtbl->Release(unk);
            state->effects[i] = NULL;
        }
    }
}
