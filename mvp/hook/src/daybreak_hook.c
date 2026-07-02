/**
 * daybreak_hook.c — DLL hook v9: TWO patches for correct direct file mode
 *
 * BUG IN v5-v8: Only patched ResourceExists (jz→jmp) to force direct file
 * mode. But ReadResource (FUN_00653760) checks param_1[0x1f] (offset 0x7c)
 * to decide between ReadFile and archive read:
 *   - If param_1[0x7c] == 0 → ReadFile (direct)
 *   - If param_1[0x7c] != 0 → archive read (with XOR + SetFilePointer)
 *
 * In direct file mode, ResourceExists opens the file with CreateFileA but
 * does NOT clear param_1[0x7c]. If it was previously set by archive mode,
 * ReadResource tries archive read on a direct file handle → reads wrong
 * data → .cnv parse fails → NULL texture → CRASH.
 *
 * FIX v9: Patch BOTH functions:
 *   1. ResourceExists (0x00653556): jz→jmp (always use CreateFileA)
 *   2. ReadResource (0x0065376e): jz→jmp (always use ReadFile)
 *
 * This ensures:
 *   - ResourceExists always opens files directly (CreateFileA)
 *   - ReadResource always reads with ReadFile (no archive XOR decode)
 *   - The .cnv data on disk is already XOR-decoded by extract_dat.py
 *   - Game reads correct .cnv data → parses correctly → no crash
 *
 * IMAGE COLORS ISSUE:
 *   "Colored squares" in v8 were caused by ReadResource using archive read
 *   (with XOR) on direct file data. The XOR corrupted the pixel data.
 *   v9 fixes this by forcing ReadFile (no XOR) in ReadResource.
 */

#define ADDR_RESOURCE_EXISTS    0x00653540
#define ADDR_READ_RESOURCE      0x00653760
#define RES_PATCH_OFFSET        0x16  /* jz at 0x00653556 */
#define READ_PATCH_OFFSET       0x0E  /* jz at 0x0065376e */
#define ORIGINAL_BYTE           0x74  /* JZ */
#define PATCHED_BYTE            0xEB  /* JMP */
#define ORIGINAL_IMAGE_BASE     0x00400000

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

static unsigned char g_saved_res[1];
static unsigned char g_saved_read[1];
static bool g_patched = false;

static bool PatchByte(void *addr, unsigned char new_val, unsigned char *saved)
{
    /* Verify current byte is JZ (0x74) */
    if (*(unsigned char *)addr != ORIGINAL_BYTE) {
        if (*(unsigned char *)addr == PATCHED_BYTE) {
            return true; /* already patched */
        }
        return false; /* version mismatch */
    }

    *saved = *(unsigned char *)addr;

    DWORD old_protect;
    if (!VirtualProtect(addr, 1, PAGE_EXECUTE_READWRITE, &old_protect))
        return false;

    *(unsigned char *)addr = new_val;

    VirtualProtect(addr, 1, old_protect, &old_protect);
    FlushInstructionCache(GetCurrentProcess(), addr, 1);
    return true;
}

static bool RestoreByte(void *addr, unsigned char saved)
{
    DWORD old_protect;
    if (!VirtualProtect(addr, 1, PAGE_EXECUTE_READWRITE, &old_protect))
        return false;
    *(unsigned char *)addr = saved;
    VirtualProtect(addr, 1, old_protect, &old_protect);
    FlushInstructionCache(GetCurrentProcess(), addr, 1);
    return true;
}

static bool InstallPatches(void)
{
    HMODULE hExe = GetModuleHandleA(NULL);
    if (!hExe) return false;

    unsigned char *res_addr = (unsigned char *)((uintptr_t)hExe +
        (ADDR_RESOURCE_EXISTS - ORIGINAL_IMAGE_BASE) + RES_PATCH_OFFSET);
    unsigned char *read_addr = (unsigned char *)((uintptr_t)hExe +
        (ADDR_READ_RESOURCE - ORIGINAL_IMAGE_BASE) + READ_PATCH_OFFSET);

    /* Patch 1: ResourceExists — always use CreateFileA (direct file) */
    bool ok1 = PatchByte(res_addr, PATCHED_BYTE, g_saved_res);

    /* Patch 2: ReadResource — always use ReadFile (no archive XOR) */
    bool ok2 = PatchByte(read_addr, PATCHED_BYTE, g_saved_read);

    g_patched = ok1 && ok2;

    char msg[512];
    snprintf(msg, sizeof(msg),
        "daybreak_hook v9 loaded!\n\n"
        "TWO patches for correct direct file mode:\n\n"
        "1. ResourceExists at 0x%p: jz→jmp\n"
        "   Forces CreateFileA (opens .cnv from disk)\n\n"
        "2. ReadResource at 0x%p: jz→jmp\n"
        "   Forces ReadFile (no archive XOR decode)\n"
        "   Fixes: colored squares + NULL crash\n\n"
        "Status: %s",
        res_addr, read_addr,
        g_patched ? "SUCCESS" : (ok1 ? "PARTIAL (patch 2 failed)" : "FAILED"));

    MessageBoxA(NULL, msg, "daybreak_hook v9", MB_OK | MB_ICONINFORMATION);
    return g_patched;
}

static void RemovePatches(void)
{
    if (!g_patched) return;

    HMODULE hExe = GetModuleHandleA(NULL);
    if (!hExe) return;

    unsigned char *res_addr = (unsigned char *)((uintptr_t)hExe +
        (ADDR_RESOURCE_EXISTS - ORIGINAL_IMAGE_BASE) + RES_PATCH_OFFSET);
    unsigned char *read_addr = (unsigned char *)((uintptr_t)hExe +
        (ADDR_READ_RESOURCE - ORIGINAL_IMAGE_BASE) + READ_PATCH_OFFSET);

    RestoreByte(res_addr, g_saved_res[0]);
    RestoreByte(read_addr, g_saved_read[0]);
    g_patched = false;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    (void)hModule;
    (void)lpReserved;

    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        InstallPatches();
        break;
    case DLL_PROCESS_DETACH:
        RemovePatches();
        break;
    }
    return TRUE;
}
