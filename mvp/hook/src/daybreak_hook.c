/**
 * daybreak_hook.c — DLL hook for DaybreakDX.exe (v5 — surgical 1-byte patch)
 *
 * v1-v2: hooks crashed (recursion, calling convention)
 * v3: patched WRONG function (set_flag offset 0, but flag is at offset 8)
 * v4: patched get_flag to always return 0 — BROKE all other callers
 *     (sound system, file enumeration, etc. all depend on get_flag)
 * v5: surgical 1-byte patch — only changes ResourceExists behavior
 *
 * ============================================================
 *
 * THE FIX:
 *
 * ResourceExists (FUN_00653540) checks the archive flag:
 *   call get_flag          ; returns flag value
 *   test eax, eax          ; is flag 0?
 *   jz direct_file_mode    ; if 0, use CreateFileA (direct file)
 *
 * We patch the JZ (0x74) to JMP (0xEB) at address 0x00653556.
 * Now ResourceExists ALWAYS uses direct file mode, regardless of flag.
 *
 * All other callers of get_flag are UNTOUCHED:
 *   - Sound system still knows archives are loaded
 *   - File enumeration still works
 *   - Archive management still functions
 *
 * Only the "should I use archive or direct file?" decision is changed,
 * and ONLY in ResourceExists.
 *
 * ============================================================
 *
 * CRASH CAUSE IN v4:
 *   get_flag is called by 13+ functions, not just ResourceExists.
 *   Making it always return 0 broke:
 *   - FUN_00699950 (sound init) — checked get_flag < 1
 *   - FUN_00699ad0 (file enum) — checked get_flag == 0
 *   - FUN_00699b60 (file enum) — checked get_flag == 0
 *   These took wrong code paths → uninitialized objects → NULL pointer → crash
 *
 * v5 only affects ResourceExists. Other functions see the real flag value.
 *
 * ============================================================
 *
 * IMPORTANT: User must extract .dat files to data/ folder first!
 *   python3 extract_dat.py /path/to/game/
 */

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ADDR_RESOURCE_EXISTS    0x00653540
#define PATCH_OFFSET            0x16  /* offset of jz at 0x00653556 */
#define ORIGINAL_BYTE           0x74  /* JZ rel8 */
#define PATCHED_BYTE            0xEB  /* JMP rel8 (unconditional) */
#define ORIGINAL_IMAGE_BASE     0x00400000

static unsigned char g_saved_byte;
static bool g_patched = false;

static bool PatchResourceExists(bool enable_direct_mode)
{
    HMODULE hExe = GetModuleHandleA(NULL);
    if (!hExe) return false;

    unsigned char *addr = (unsigned char *)((uintptr_t)hExe +
        (ADDR_RESOURCE_EXISTS - ORIGINAL_IMAGE_BASE) + PATCH_OFFSET);

    if (enable_direct_mode) {
        /* Verify we're patching the right byte */
        if (*addr != ORIGINAL_BYTE) {
            if (*addr == PATCHED_BYTE) {
                return true;  /* already patched */
            }
            char msg[256];
            snprintf(msg, sizeof(msg),
                "daybreak_hook: VERSION MISMATCH!\n\n"
                "Expected byte 0x%02X at 0x%p\n"
                "Found: 0x%02X\n\n"
                "Patch NOT applied.",
                ORIGINAL_BYTE, addr, *addr);
            MessageBoxA(NULL, msg, "daybreak_hook", MB_OK | MB_ICONERROR);
            return false;
        }
        g_saved_byte = *addr;
    }

    DWORD old_protect;
    if (!VirtualProtect(addr, 1, PAGE_EXECUTE_READWRITE, &old_protect)) {
        return false;
    }

    *addr = enable_direct_mode ? PATCHED_BYTE : g_saved_byte;

    VirtualProtect(addr, 1, old_protect, &old_protect);
    FlushInstructionCache(GetCurrentProcess(), addr, 1);

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

        bool ok = PatchResourceExists(true);

        HMODULE hExe = GetModuleHandleA(NULL);
        void *patch_addr = (void *)((uintptr_t)hExe +
            (ADDR_RESOURCE_EXISTS - ORIGINAL_IMAGE_BASE) + PATCH_OFFSET);

        char msg[512];
        snprintf(msg, sizeof(msg),
            "daybreak_hook v5 loaded!\n\n"
            "Surgical 1-byte patch in ResourceExists:\n"
            "  Address: 0x%p (FUN_00653540 + 0x16)\n"
            "  Original: 0x74 (JZ → direct file only when flag==0)\n"
            "  Patched:  0xEB (JMP → ALWAYS direct file)\n\n"
            "Only ResourceExists is affected.\n"
            "All other systems (sound, archives, etc.) work normally.\n\n"
            "Status: %s\n\n"
            "Make sure data/ folder has extracted files!",
            patch_addr,
            ok ? "SUCCESS" : "FAILED");

        MessageBoxA(NULL, msg, "daybreak_hook v5", MB_OK | MB_ICONINFORMATION);
        break;
    }

    case DLL_PROCESS_DETACH:
        PatchResourceExists(false);
        break;
    }
    return TRUE;
}
