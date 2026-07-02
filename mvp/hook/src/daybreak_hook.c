/**
 * daybreak_hook.c — DLL hook for DaybreakDX.exe (v2 — no recursion)
 *
 * PREVIOUS VERSION HAD A BUG: detour functions called "original" which
 * pointed to the patched address → infinite recursion → stack overflow.
 *
 * THIS VERSION FIXES IT with two approaches:
 *
 * Mode 0 (Direct file only): 1-byte binary patch — no hooks at all
 * Mode 1 (Archive only):     No patches, no hooks
 * Mode 2 (Hybrid):           1-byte patch + trampoline-based hook on ResourceExists
 *
 * ============================================================
 *
 * REVERSE ENGINEERING (confirmed from PE byte analysis):
 *
 * FUN_0064d760 (set_flag) assembly:
 *   55           push ebp
 *   8B EC        mov ebp, esp
 *   51           push ecx
 *   89 4D FC     mov [ebp-4], ecx       ; save this
 *   8B 45 FC     mov eax, [ebp-4]       ; eax = this
 *   C6 00 01     mov byte [eax], 1      ; ← flag = 1 (archive mode)
 *   8B E5        mov esp, ebp
 *   5D           pop ebp
 *   C3           ret
 *
 * Patching the 0x01 at offset +0x0C to 0x00 makes it set flag = 0 (direct mode).
 * This is a SINGLE BYTE patch — safest possible modification.
 *
 * FUN_00653540 (ResourceExists) first 6 bytes:
 *   55           push ebp           (1 byte)
 *   8B EC        mov ebp, esp       (2 bytes)
 *   83 EC 0C     sub esp, 0x0C      (3 bytes)
 *   → Total: 6 bytes = minimum for trampoline (>= 5 for JMP rel32)
 *
 *   89 4D F4     mov [ebp-0xC], ecx ; save this_ptr
 *   8B 4D F4     mov ecx, [ebp-0xC] ; reload this_ptr
 *   83 C1 68     add ecx, 0x68      ; ecx = this_ptr + 0x68
 *   E8 ...       call FUN_00699fc0  ; get_flag → returns *((this_ptr+0x68)+8)
 *
 * So the archive flag is at: this_ptr + 0x68 + 0x08 = this_ptr + 0x70
 */

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* ============================================================
 * Configuration
 * ============================================================ */

/* Original binary addresses (VA) */
#define ADDR_SET_FLAG         0x0064d760  /* FUN_0064d760 */
#define ADDR_RESOURCE_EXISTS  0x00653540  /* FUN_00653540 */

#define ORIGINAL_IMAGE_BASE   0x00400000

/* Offset of the 0x01 byte we want to patch in FUN_0064d760 */
#define SET_FLAG_PATCH_OFFSET  0x0C  /* offset of the 0x01 in "C6 00 01" */

/* Offset of archive flag from ResourceExists this_ptr */
/* this_ptr + 0x68 → passed to get_flag → get_flag reads +8 → total +0x70 */
#define FLAG_OFFSET_FROM_THIS  0x70

/* Hook modes */
#define MODE_DIRECT   0  /* Direct file only */
#define MODE_ARCHIVE  1  /* Archive only (original behavior) */
#define MODE_HYBRID   2  /* Direct first, archive fallback */

static int g_hook_mode = MODE_HYBRID;
static uintptr_t g_image_base = 0;

/* ============================================================
 * Trampoline — allocates executable memory with original bytes
 *              + JMP back to original+N, so detour can call original
 *              without re-entering the hook (fixes the recursion bug)
 * ============================================================ */

typedef struct Trampoline {
    void *exec_mem;         /* executable memory block */
    void *original_addr;    /* address of original function */
    int   patch_size;       /* number of bytes copied (>= 5) */
    unsigned char saved_bytes[16]; /* original bytes (for unpatch) */
} Trampoline;

static bool CreateTrampoline(Trampoline *t, void *target, int min_bytes)
{
    t->original_addr = target;
    t->exec_mem = NULL;
    t->patch_size = 0;

    /* Read original bytes */
    memcpy(t->saved_bytes, target, 16);

    /* Determine how many bytes to copy.
     * We need at least min_bytes (5 for JMP rel32), and we must
     * end on an instruction boundary.
     *
     * For our specific functions, we know the instruction layout:
     *   FUN_00653540: 55(1) 8BEC(2) 83EC0C(3) = 6 bytes → use 6
     */
    /* Hardcoded for known functions — would need a length disassembler
     * for general case */
    if (min_bytes <= 5) {
        t->patch_size = 6;  /* ResourceExists: push/mov/sub = 6 bytes */
    } else {
        t->patch_size = min_bytes;
    }

    /* Allocate executable memory */
    t->exec_mem = VirtualAlloc(NULL, t->patch_size + 5,
                                MEM_COMMIT | MEM_RESERVE,
                                PAGE_EXECUTE_READWRITE);
    if (!t->exec_mem) {
        return false;
    }

    /* Copy original bytes to trampoline */
    memcpy(t->exec_mem, target, t->patch_size);

    /* Append JMP rel32 to (original + patch_size) */
    unsigned char *jmp_addr = (unsigned char *)t->exec_mem + t->patch_size;
    DWORD rel = (DWORD)((uintptr_t)target + t->patch_size - (uintptr_t)jmp_addr - 5);
    jmp_addr[0] = 0xE9;
    memcpy(&jmp_addr[1], &rel, 4);

    return true;
}

static void DestroyTrampoline(Trampoline *t)
{
    if (t->exec_mem) {
        VirtualFree(t->exec_mem, 0, MEM_RELEASE);
        t->exec_mem = NULL;
    }
}

/* Install 5-byte JMP at target, fill rest with NOPs */
static bool InstallJmpHook(void *target, void *detour, int patch_size)
{
    DWORD old_protect;
    if (!VirtualProtect(target, patch_size, PAGE_EXECUTE_READWRITE, &old_protect)) {
        return false;
    }

    /* Write JMP rel32 */
    unsigned char *p = (unsigned char *)target;
    DWORD rel = (DWORD)((uintptr_t)detour - (uintptr_t)target - 5);
    p[0] = 0xE9;
    memcpy(&p[1], &rel, 4);

    /* Fill remaining bytes with NOP */
    for (int i = 5; i < patch_size; i++) {
        p[i] = 0x90;
    }

    VirtualProtect(target, patch_size, old_protect, &old_protect);
    FlushInstructionCache(GetCurrentProcess(), target, patch_size);
    return true;
}

static void RemoveJmpHook(void *target, const unsigned char *saved, int patch_size)
{
    DWORD old_protect;
    VirtualProtect(target, patch_size, PAGE_EXECUTE_READWRITE, &old_protect);
    memcpy(target, saved, patch_size);
    VirtualProtect(target, patch_size, old_protect, &old_protect);
    FlushInstructionCache(GetCurrentProcess(), target, patch_size);
}

/* ============================================================
 * 1-byte patch for FUN_0064d760 (set_flag)
 *
 * Changes the 0x01 in "C6 00 01" (mov byte [eax], 1) to 0x00
 * so the function sets flag = 0 (direct file mode) instead of 1.
 * ============================================================ */

static bool PatchSetFlag(bool enable_direct_mode)
{
    unsigned char *addr = (unsigned char *)(g_image_base +
        (ADDR_SET_FLAG - ORIGINAL_IMAGE_BASE) + SET_FLAG_PATCH_OFFSET);

    DWORD old_protect;
    if (!VirtualProtect(addr, 1, PAGE_READWRITE, &old_protect)) {
        return false;
    }

    if (enable_direct_mode) {
        *addr = 0x00;  /* set flag to 0 (direct mode) */
    } else {
        *addr = 0x01;  /* restore: set flag to 1 (archive mode) */
    }

    VirtualProtect(addr, 1, old_protect, &old_protect);
    FlushInstructionCache(GetCurrentProcess(), addr, 1);
    return true;
}

/* ============================================================
 * Hook for FUN_00653540 (ResourceExists) — hybrid mode
 *
 * Trampoline lets us call the original function without
 * re-entering our hook (this was the bug in v1).
 *
 * The archive flag is at this_ptr + 0x70.
 * We set it to 0 (direct), call original → tries CreateFileA.
 * If that fails, set to 1 (archive), call original → tries archive.
 * ============================================================ */

static Trampoline g_res_exists_trampoline;
static bool g_trampoline_created = false;

/* Function pointer to trampoline (calls original via saved bytes + JMP) */
typedef bool (__fastcall *ResourceExistsFunc)(void *, const char *);
static ResourceExistsFunc g_orig_resource_exists = NULL;

static bool __fastcall hook_resource_exists(void *this_ptr, const char *filename)
{
    /* The archive flag is at this_ptr + 0x70 */
    volatile int *flag = (volatile int *)((char *)this_ptr + FLAG_OFFSET_FROM_THIS);

    /* Save current flag value */
    int old_flag = *flag;

    /* Step 1: Try direct file mode (flag = 0) */
    *flag = 0;
    bool result = g_orig_resource_exists(this_ptr, filename);
    if (result) {
        *flag = old_flag;  /* restore */
        return true;
    }

    /* Step 2: Fallback to archive mode (flag = 1) */
    *flag = 1;
    result = g_orig_resource_exists(this_ptr, filename);
    *flag = old_flag;  /* restore */

    return result;
}

/* ============================================================
 * Installation
 * ============================================================ */

static bool InstallHooks(void)
{
    g_image_base = (uintptr_t)GetModuleHandleA(NULL);
    if (!g_image_base) {
        MessageBoxA(NULL, "GetModuleHandle failed", "daybreak_hook", MB_OK | MB_ICONERROR);
        return false;
    }

    /* Read hook mode from environment variable */
    const char *mode_env = getenv("DAYBREAK_HOOK_MODE");
    if (mode_env) {
        g_hook_mode = atoi(mode_env);
        if (g_hook_mode < 0 || g_hook_mode > 2) {
            g_hook_mode = MODE_HYBRID;
        }
    }

    char msg[512];
    bool ok = true;

    if (g_hook_mode == MODE_ARCHIVE) {
        /* Mode 1: no patches, no hooks — original behavior */
        snprintf(msg, sizeof(msg),
            "daybreak_hook loaded!\n\n"
            "Mode: 1 (Archive only — original behavior)\n"
            "No patches applied.\n"
            "Image base: 0x%p", (void *)g_image_base);
    }
    else if (g_hook_mode == MODE_DIRECT) {
        /* Mode 0: 1-byte patch only — direct file mode */
        void *set_flag_addr = (void *)(g_image_base +
            (ADDR_SET_FLAG - ORIGINAL_IMAGE_BASE));
        ok = PatchSetFlag(true);

        snprintf(msg, sizeof(msg),
            "daybreak_hook loaded!\n\n"
            "Mode: 0 (Direct file only)\n"
            "Image base: 0x%p\n"
            "Patched FUN_0064d760 at 0x%p (1 byte: 0x01 → 0x00)\n"
            "Result: game loads from data/ folder only\n"
            "Hooks installed: %s",
            (void *)g_image_base, set_flag_addr,
            ok ? "Yes" : "FAILED");
    }
    else {
        /* Mode 2: hybrid — 1-byte patch + trampoline hook */
        void *set_flag_addr = (void *)(g_image_base +
            (ADDR_SET_FLAG - ORIGINAL_IMAGE_BASE));
        void *res_exists_addr = (void *)(g_image_base +
            (ADDR_RESOURCE_EXISTS - ORIGINAL_IMAGE_BASE));

        /* Patch set_flag to 0 (direct mode default) */
        ok = PatchSetFlag(true);

        /* Create trampoline for ResourceExists */
        if (ok) {
            g_trampoline_created = CreateTrampoline(&g_res_exists_trampoline,
                                                     res_exists_addr, 5);
            if (g_trampoline_created) {
                g_orig_resource_exists = (ResourceExistsFunc)g_res_exists_trampoline.exec_mem;
                /* Install JMP hook (6 bytes: 5 for JMP + 1 NOP) */
                ok = InstallJmpHook(res_exists_addr, (void *)hook_resource_exists,
                                     g_res_exists_trampoline.patch_size);
            } else {
                ok = false;
            }
        }

        snprintf(msg, sizeof(msg),
            "daybreak_hook loaded!\n\n"
            "Mode: 2 (Hybrid — direct first, archive fallback)\n"
            "Image base: 0x%p\n"
            "Patched set_flag at 0x%p (1 byte)\n"
            "Trampoline for ResourceExists at 0x%p (%d bytes)\n"
            "Trampoline exec mem: 0x%p\n"
            "Hooks installed: %s",
            (void *)g_image_base,
            set_flag_addr,
            res_exists_addr,
            g_trampoline_created ? g_res_exists_trampoline.patch_size : 0,
            g_trampoline_created ? g_res_exists_trampoline.exec_mem : NULL,
            ok ? "Yes" : "PARTIAL — check console");
    }

    MessageBoxA(NULL, msg, "daybreak_hook", MB_OK | MB_ICONINFORMATION);

    /* Also print to console (if available) */
    FILE *console = freopen("CONOUT$", "w", stdout);
    if (console) {
        printf("%s\n", msg);
    }

    return ok;
}

static void RemoveHooks(void)
{
    if (g_hook_mode == MODE_DIRECT || g_hook_mode == MODE_HYBRID) {
        /* Restore set_flag byte */
        PatchSetFlag(false);
    }

    if (g_hook_mode == MODE_HYBRID && g_trampoline_created) {
        /* Restore ResourceExists original bytes */
        void *res_exists_addr = (void *)(g_image_base +
            (ADDR_RESOURCE_EXISTS - ORIGINAL_IMAGE_BASE));
        RemoveJmpHook(res_exists_addr, g_res_exists_trampoline.saved_bytes,
                       g_res_exists_trampoline.patch_size);
        DestroyTrampoline(&g_res_exists_trampoline);
        g_trampoline_created = false;
    }
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
        DisableThreadLibraryCalls(hModule);
        InstallHooks();
        break;

    case DLL_PROCESS_DETACH:
        RemoveHooks();
        break;
    }
    return TRUE;
}
