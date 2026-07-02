/**
 * input_init.c — DirectInput 8 keyboard init
 *
 * Translated from:
 *   - InitDirectInput (FUN_00658260)
 *   - InitKeyboard (FUN_00658410)
 *
 * Uses MinGW COM-style macros (IDirectInput8_Method(p, args)) for C compatibility.
 */

#include "engine.h"
#include "d3d_utils.h"

bool InitDirectInput(EngineState *state, HINSTANCE hinstance)
{
    HRESULT hr = DirectInput8Create(
        hinstance,
        DIRECTINPUT_VERSION,  /* 0x0800 — matches original 0x800 */
        &IID_IDirectInput8A,
        (LPVOID *)&state->dinput,
        NULL);

    if (FAILED(hr)) {
        ShowError("DirectInput8Create failed. DirectInput 8 may not be available.",
                  "Input Init Error");
        return false;
    }
    return true;
}

bool InitKeyboard(EngineState *state)
{
    /* 1. Create keyboard device */
    HRESULT hr = IDirectInput8_CreateDevice(state->dinput,
                                             &GUID_SysKeyboard,
                                             &state->keyboard,
                                             NULL);

    if (FAILED(hr)) {
        ShowError("Failed to create keyboard device",
                  "Input Init Error");
        return false;
    }

    /* 2. Set data format (c_dfDIKeyboard = 256-byte array) */
    hr = IDirectInputDevice8_SetDataFormat(state->keyboard,
                                            &c_dfDIKeyboard);
    if (FAILED(hr)) {
        ShowError("SetDataFormat failed for keyboard",
                  "Input Init Error");
        return false;
    }

    /* 3. Set cooperative level
     * Original used: DISCL_NONEXCLUSIVE | DISCL_FOREGROUND (0x16)
     */
    hr = IDirectInputDevice8_SetCooperativeLevel(state->keyboard,
                                                   state->hwnd,
                                                   DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

    if (FAILED(hr)) {
        ShowError("SetCooperativeLevel failed for keyboard",
                  "Input Init Error");
        return false;
    }

    /* 4. Acquire */
    hr = IDirectInputDevice8_Acquire(state->keyboard);
    /* Note: Acquire can fail if window isn't foreground yet — non-fatal */

    return true;
}

void ReadKeyboardState(EngineState *state, uint8_t keys[256])
{
    if (!state->keyboard) {
        memset(keys, 0, 256);
        return;
    }

    HRESULT hr = IDirectInputDevice8_GetDeviceState(state->keyboard, 256, keys);
    if (FAILED(hr)) {
        /* Lost focus — try to reacquire */
        memset(keys, 0, 256);
        IDirectInputDevice8_Acquire(state->keyboard);
    }
}

void ShutdownInput(EngineState *state)
{
    if (state->keyboard) {
        IDirectInputDevice8_Unacquire(state->keyboard);
        IDirectInputDevice8_Release(state->keyboard);
        state->keyboard = NULL;
    }
    if (state->dinput) {
        IDirectInput8_Release(state->dinput);
        state->dinput = NULL;
    }
}
