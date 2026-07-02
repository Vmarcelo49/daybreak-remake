/**
 * daybreak_hook.c — DLL hook for DaybreakDX.exe (v3 — 1-byte patch ONLY)
 *
 * v1 had infinite recursion → stack overflow
 * v2 had calling convention mismatch (__fastcall vs __thiscall) → page fault
 * v3: NO HOOKS AT ALL. Just a 1-byte binary patch. Cannot crash.
 *
 * ============================================================
 *
 * WHAT IT DOES:
 *   FUN_0064d760 sets the archive mode flag to 1 (archive mode).
 *   The function body is:
 *     mov byte [eax], 1    ; machine code: C6 00 01
 *
 *   We patch the 0x01 → 0x00, so it becomes:
 *     mov byte [eax], 0    ; machine code: C6 00 00
 *
 *   Now the flag is 0 = direct file mode.
 *   ResourceExists checks: if flag == 0 → CreateFileA (direct file).
 *
 *   This is the SAFEST possible modification:
 *   - No code flow changes
 *   - No hooks
 *   - No trampolines
 *   - No calling convention issues
 *   - Just changing a constant from 1 to 0
 *
 * HYBRID MODE (future):
 *   To support "try direct file, then archive", we would need to
 *   hook ResourceExists properly. That requires:
 *   - A length disassembler to find instruction boundaries
 *   - Correct __thiscall calling convention in the detour
 *   - A trampoline that preserves the stack layout exactly
 *
 *   For now, direct file only is the safest option. If a file is
 *   not found on disk, the game will show an error — but it won't crash.
 *
 * ============================================================
 *
 * USAGE:
 *   1. Copy daybreak_hook.dll + daybreak_launcher.exe next to DaybreakDX.exe
 *   2. Extract game assets to data/ folder (use the .dat extractor tool)
 *   3. Run daybreak_launcher.exe
 *
 *   The DLL patches 1 byte at startup, then does nothing else.
 *   Game runs normally but loads all assets from data/ folder.
 */

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* ============================================================
 * Configuration
 * ============================================================ */

#define ADDR_SET_FLAG          0x0064d760
#define ORIGINAL_IMAGE_BASE    0x00400000
#define SET_FLAG_PATCH_OFFSET  0x0C  /* offset of 0x01 in "C6 00 01" */

/* ============================================================
 * 1-byte patch: change 0x01 → 0x00 in FUN_0064d760
 *
 * Before:  C6 00 01  →  mov byte [eax], 1  (archive mode)
 * After:   C6 00 00  →  mov byte [eax], 0  (direct file mode)
 * ============================================================ */

static bool PatchSetFlag(bool enable_direct_mode)
{
    HMODULE hExe = GetModuleHandleA(NULL);
    if (!hExe) return false;

    /* Calculate address of the byte to patch */
    unsigned char *addr = (unsigned char *)((uintptr_t)hExe +
        (ADDR_SET_FLAG - ORIGINAL_IMAGE_BASE) + SET_FLAG_PATCH_OFFSET);

    /* Verify we're patching the right byte */
    if (*addr != 0x01 && *addr != 0x00) {
        char msg[256];
        snprintf(msg, sizeof(msg),
            "daybreak_hook: WARNING!\n\n"
            "Expected byte 0x01 at address 0x%p\n"
            "Found: 0x%02X\n\n"
            "This may be a different version of DaybreakDX.exe.\n"
            "Patch NOT applied.",
            addr, *addr);
        MessageBoxA(NULL, msg, "daybreak_hook", MB_OK | MB_ICONWARNING);
        return false;
    }

    /* Make the byte writable */
    DWORD old_protect;
    if (!VirtualProtect(addr, 1, PAGE_READWRITE, &old_protect)) {
        return false;
    }

    /* Patch: 0x01 → 0x00 (direct mode) or restore 0x01 (archive mode) */
    *addr = enable_direct_mode ? 0x00 : 0x01;

    /* Restore protection */
    VirtualProtect(addr, 1, old_protect, &old_protect);
    FlushInstructionCache(GetCurrentProcess(), addr, 1);

    return true;
}

/* ============================================================
 * DLL entry point
 * ============================================================ */

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    (void)hModule;
    (void)lpReserved;

    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hModule);

        /* Apply the 1-byte patch */
        bool ok = PatchSetFlag(true);

        HMODULE hExe = GetModuleHandleA(NULL);
        char msg[512];
        snprintf(msg, sizeof(msg),
            "daybreak_hook loaded!\n\n"
            "Mode: Direct file only (1-byte patch)\n"
            "Image base: 0x%p\n"
            "Patched byte at: 0x%p (0x01 → 0x00)\n"
            "Result: %s\n\n"
            "Game will load assets from data/ folder.\n"
            "Make sure data/ folder exists with game assets!",
            hExe,
            (void *)((uintptr_t)hExe +
                (ADDR_SET_FLAG - ORIGINAL_IMAGE_BASE) + SET_FLAG_PATCH_OFFSET),
            ok ? "SUCCESS" : "FAILED — see warning");

        MessageBoxA(NULL, msg, "daybreak_hook", MB_OK | MB_ICONINFORMATION);

        /* Restore on unload */
        break;
    }

    case DLL_PROCESS_DETACH:
        PatchSetFlag(false);  /* restore original byte */
        break;
    }
    return TRUE;
}
