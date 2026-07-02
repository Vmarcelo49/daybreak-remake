/**
 * d3d_utils.h — Helper macros for D3D9 error handling
 */
#ifndef DAYBREAK_D3D_UTILS_H
#define DAYBREAK_D3D_UTILS_H

#include <d3d9.h>

/* Safe release macros for COM objects — uses MinGW COM-style method macros */
#define SAFE_RELEASE_D3D9(p) do { \
    if ((p)) { IDirect3D9_Release(p); (p) = NULL; } \
} while (0)
#define SAFE_RELEASE_DEVICE(p) do { \
    if ((p)) { IDirect3DDevice9_Release(p); (p) = NULL; } \
} while (0)
#define SAFE_RELEASE_EFFECT(p) do { \
    if ((p)) { ID3DXEffect_Release(p); (p) = NULL; } \
} while (0)
#define SAFE_RELEASE_DINPUT(p) do { \
    if ((p)) { IDirectInput8_Release(p); (p) = NULL; } \
} while (0)
#define SAFE_RELEASE_DIDEVICE(p) do { \
    if ((p)) { IDirectInputDevice8_Release(p); (p) = NULL; } \
} while (0)

/* Convert HRESULT to boolean, log on failure */
#define HR_BOOL(hr, msg) ((hr) >= 0 ? true : (ShowError(msg, "D3D Error"), false))

/* Check HRESULT and return false on failure */
#define HR_RETURN(hr, msg) do { \
    if ((hr) < 0) { \
        ShowError(msg, "D3D Error"); \
        return false; \
    } \
} while (0)

/* ARGB color helper */
#define COLOR_ARGB(a, r, g, b) (((DWORD)(a) << 24) | ((DWORD)(r) << 16) | ((DWORD)(g) << 8) | (DWORD)(b))

#define COLOR_BLACK   COLOR_ARGB(0xff, 0x00, 0x00, 0x00)
#define COLOR_WHITE   COLOR_ARGB(0xff, 0xff, 0xff, 0xff)
#define COLOR_RED     COLOR_ARGB(0xff, 0xff, 0x00, 0x00)
#define COLOR_GREEN   COLOR_ARGB(0xff, 0x00, 0xff, 0x00)
#define COLOR_BLUE    COLOR_ARGB(0xff, 0x00, 0x00, 0xff)

#endif /* DAYBREAK_D3D_UTILS_H */
