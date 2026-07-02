/**
 * daybreak_hook.c — DLL hook for DaybreakDX.exe (v4 — correct patch target)
 *
 * v1: infinite recursion → stack overflow
 * v2: calling convention mismatch → page fault
 * v3: WRONG ADDRESS — patched FUN_0064d760 (offset 0) but flag is at offset 8
 * v4: CORRECT — patches FUN_00699fc0 (get_flag) to always return 0
 *
 * ============================================================
 *
 * ROOT CAUSE ANALYSIS:
 *
 * The archive system object is at 0x006d842c (global, set up in WinMain).
 * It has multiple fields:
 *   offset 0: "archive system initialized" (set to 1 by FUN_0064d760)
 *   offset 4: "archive count" (set by FUN_006940b0)
 *   offset 8: "use archive mode" flag (read by FUN_00699fc0)
 *
 * v3 patched FUN_0064d760 to set offset 0 = 0 instead of 1.
 * This BROKE archive initialization (game thought archives weren't loaded).
 * But offset 8 (the actual mode flag) was still non-zero → archive mode
 * with broken initialization → CRASH.
 *
 * v4 patches FUN_00699fc0 (get_flag) to always return 0.
 * This means ResourceExists ALWAYS uses direct file mode (CreateFileA).
 * Archive system still initializes normally (FUN_0064d760 untouched).
 *
 * ============================================================
 *
 * FUN_00699fc0 assembly:
 *   +00: 55           push ebp
 *   +01: 8B EC        mov ebp, esp
 *   +03: 51           push ecx
 *   +04: 89 4D FC     mov [ebp-4], ecx
 *   +07: 8B 45 FC     mov eax, [ebp-4]
 *   +0A: 8B 40 08     mov eax, [eax+8]     ← READ FLAG
 *   +0D: 8B E5        mov esp, ebp
 *   +0F: 5D           pop ebp
 *   +10: C3           ret
 *
 * Patch: replace 3 bytes at +0x0A:
 *   8B 40 08  →  33 C0 90
 *   mov eax, [eax+8]  →  xor eax, eax; nop
 *
 * Result: function always returns 0 (direct file mode).
 * Stack frame is still properly set up and torn down. No side effects.
 *
 * ============================================================
 *
 * REQUIREMENT: User must extract .dat files to data/ folder first!
 *   python3 extract_dat.py /path/to/game/
 *
 * Without extracted files, the game will crash (NULL pointer on missing file).
 */

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ADDR_GET_FLAG          0x00699fc0
#define ORIGINAL_IMAGE_BASE    0x00400000
#define GET_FLAG_PATCH_OFFSET  0x0A  /* offset of "8B 40 08" in FUN_00699fc0 */

/* Original bytes: 8B 40 08 (mov eax, [eax+8]) */
/* Patched bytes:  33 C0 90 (xor eax, eax; nop) → always returns 0 */
static const unsigned char PATCHED_BYTES[3] = { 0x33, 0xC0, 0x90 };
static const unsigned char ORIGINAL_BYTES[3] = { 0x8B, 0x40, 0x08 };

static unsigned char g_saved_bytes[3];
static bool g_patched = false;

static bool PatchGetFlag(bool enable_direct_mode)
{
    HMODULE hExe = GetModuleHandleA(NULL);
    if (!hExe) return false;

    unsigned char *addr = (unsigned char *)((uintptr_t)hExe +
        (ADDR_GET_FLAG - ORIGINAL_IMAGE_BASE) + GET_FLAG_PATCH_OFFSET);

    /* Verify we're patching the right bytes */
    if (enable_direct_mode) {
        if (memcmp(addr, ORIGINAL_BYTES, 3) != 0) {
            /* Maybe already patched? */
            if (memcmp(addr, PATCHED_BYTES, 3) == 0) {
                return true;  /* already patched */
            }
            char msg[256];
            snprintf(msg, sizeof(msg),
                "daybreak_hook: VERSION MISMATCH!\n\n"
                "Expected bytes 8B 40 08 at 0x%p\n"
                "Found: %02X %02X %02X\n\n"
                "This may be a different version of DaybreakDX.exe.\n"
                "Patch NOT applied.",
                addr, addr[0], addr[1], addr[2]);
            MessageBoxA(NULL, msg, "daybreak_hook", MB_OK | MB_ICONERROR);
            return false;
        }
        /* Save original bytes */
        memcpy(g_saved_bytes, addr, 3);
    }

    /* Make writable */
    DWORD old_protect;
    if (!VirtualProtect(addr, 3, PAGE_EXECUTE_READWRITE, &old_protect)) {
        return false;
    }

    /* Write patch */
    memcpy(addr, enable_direct_mode ? PATCHED_BYTES : g_saved_bytes, 3);

    /* Restore protection */
    VirtualProtect(addr, 3, old_protect, &old_protect);
    FlushInstructionCache(GetCurrentProcess(), addr, 3);

    g_patched = enable_direct_mode;
    return true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    (void)hModule;
    (void)lpReserved;

    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hModule);

        bool ok = PatchGetFlag(true);

        HMODULE hExe = GetModuleHandleA(NULL);
        void *patch_addr = (void *)((uintptr_t)hExe +
            (ADDR_GET_FLAG - ORIGINAL_IMAGE_BASE) + GET_FLAG_PATCH_OFFSET);

        char msg[512];
        snprintf(msg, sizeof(msg),
            "daybreak_hook v4 loaded!\n\n"
            "Patched FUN_00699fc0 (get_flag) at 0x%p\n"
            "  Original: 8B 40 08 (mov eax, [eax+8])\n"
            "  Patched:  33 C0 90 (xor eax, eax; nop)\n"
            "  Result: always returns 0 = direct file mode\n\n"
            "Status: %s\n\n"
            "IMPORTANT: Make sure data/ folder exists with extracted files!\n"
            "Run: python3 extract_dat.py <game_folder>",
            patch_addr,
            ok ? "SUCCESS" : "FAILED — version mismatch?");

        MessageBoxA(NULL, msg, "daybreak_hook v4", MB_OK | MB_ICONINFORMATION);
        break;
    }

    case DLL_PROCESS_DETACH:
        PatchGetFlag(false);  /* restore original bytes */
        break;
    }
    return TRUE;
}
