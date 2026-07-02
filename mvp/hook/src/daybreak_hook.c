/**
 * daybreak_hook.c — DLL hook for DaybreakDX.exe
 *
 * PURPOSE:
 *   Enables "direct file mode" in DaybreakDX.exe so the game loads assets
 *   (BMPs, OGs, .x meshes) directly from the data/ folder instead of from
 *   the daybreakXX.dat archives.
 *
 *   Additionally, provides a "hybrid mode" that tries direct file first,
 *   then falls back to the .dat archive if the file is not found.
 *
 * HOW IT WORKS:
 *   The original game has an internal flag at a singleton's offset +0 that
 *   controls whether to use archive mode (1) or direct file mode (0).
 *
 *   - FUN_0064d760 (0x0064d760) sets this flag to 1 (enable archive mode)
 *   - FUN_00699fc0 (0x00699fc0) reads the flag
 *   - FUN_00653540 (0x00653540) checks the flag:
 *       if flag == 0 → CreateFileA (direct file mode)
 *       if flag != 0 → archive lookup
 *
 *   This DLL hooks:
 *   1. FUN_0064d760 — to NOT set the flag to 1 (keep it 0 = direct mode)
 *   2. CreateFileA — to implement hybrid mode: try direct file first,
 *      if not found, set flag to 1 temporarily so the game uses archive
 *
 * INJECTION:
 *   Copy this DLL next to DaybreakDX.exe and rename the exe to something
 *   else, then create a launcher that does:
 *       CreateProcess("DaybreakDX.exe", ..., CREATE_SUSPENDED)
 *       LoadLibrary("daybreak_hook.dll")
 *       ResumeThread()
 *
 *   OR simpler: use a DLL loader like LoadDll.exe, or use AppInit_DLLs
 *   registry key, or use the Detours library.
 *
 *   For MVP, we provide a simple launcher (daybreak_launcher.exe) that
 *   injects the DLL on startup.
 */

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

/* ============================================================
 * Configuration
 * ============================================================ */

/* Original binary addresses (from decompilation analysis) */
#define ADDR_SET_ARCHIVE_FLAG    0x0064d760  /* FUN_0064d760 — sets flag to 1 */
#define ADDR_GET_ARCHIVE_FLAG    0x00699fc0  /* FUN_00699fc0 — returns flag */
#define ADDR_RESOURCE_EXISTS     0x00653540  /* FUN_00653540 — checks flag */

/* Image base of DaybreakDX.exe (from PE header) */
#define ORIGINAL_IMAGE_BASE      0x00400000

/* Mode: 0 = direct file only, 1 = archive only, 2 = hybrid (direct first, then archive) */
#define HOOK_MODE_HYBRID         2

static int g_hook_mode = HOOK_MODE_HYBRID;

/* ============================================================
 * Hook installation helpers (minhook-style trampolines)
 * ============================================================ */

/* Simple inline patch: write a JMP rel32 instruction at addr.
 * Original 5 bytes are saved for unhooking. */
typedef struct {
    void *target;
    unsigned char original_bytes[5];
    unsigned char hook_bytes[5];
    bool active;
} InlineHook;

static bool InstallInlineHook(InlineHook *hook, void *target, void *detour)
{
    hook->target = target;
    hook->active = false;

    /* Save original bytes */
    memcpy(hook->original_bytes, target, 5);

    /* Build JMP rel32 to detour */
    DWORD rel = (DWORD)((uintptr_t)detour - (uintptr_t)target - 5);
    hook->hook_bytes[0] = 0xE9;  /* JMP rel32 */
    memcpy(&hook->hook_bytes[1], &rel, 4);

    /* Make target writable */
    DWORD old_protect;
    if (!VirtualProtect(target, 5, PAGE_EXECUTE_READWRITE, &old_protect)) {
        return false;
    }

    /* Write hook bytes */
    memcpy(target, hook->hook_bytes, 5);

    /* Restore protection */
    VirtualProtect(target, 5, old_protect, &old_protect);

    /* Flush instruction cache */
    FlushInstructionCache(GetCurrentProcess(), target, 5);

    hook->active = true;
    return true;
}

static void RemoveInlineHook(InlineHook *hook)
{
    if (!hook->active) return;

    DWORD old_protect;
    VirtualProtect(hook->target, 5, PAGE_EXECUTE_READWRITE, &old_protect);
    memcpy(hook->target, hook->original_bytes, 5);
    VirtualProtect(hook->target, 5, old_protect, &old_protect);
    FlushInstructionCache(GetCurrentProcess(), hook->target, 5);

    hook->active = false;
}

/* ============================================================
 * Hook 1: FUN_0064d760 — original sets flag to 1 (archive mode)
 *
 * Our detour: in hybrid mode, we DON'T set the flag — leave it 0
 * so the game uses direct file mode by default.
 *
 * In archive-only mode, we call the original (set flag to 1).
 * ============================================================ */

static InlineHook g_hook_set_flag;
static void (*orig_set_archive_flag)(void *) = NULL;

static void __fastcall hook_set_archive_flag(void *this_ptr)
{
    if (g_hook_mode == 0) {
        /* Direct file only — don't set flag, leave it 0 */
        return;
    }
    if (g_hook_mode == 1) {
        /* Archive only — call original (sets to 1) */
        orig_set_archive_flag(this_ptr);
        return;
    }
    /* Hybrid mode — don't set flag initially. The CreateFileA hook
     * will set it to 1 temporarily when a direct file fails. */
    return;
}

/* ============================================================
 * Hook 2: FUN_00699fc0 — original returns the flag value
 *
 * Our detour: in hybrid mode, return 0 (direct mode) by default.
 * The CreateFileA hook manages flag state for fallback.
 * ============================================================ */

static InlineHook g_hook_get_flag;
static int (*orig_get_archive_flag)(void *) = NULL;

static int __fastcall hook_get_archive_flag(void *this_ptr)
{
    if (g_hook_mode == 0) {
        return 0;  /* Always direct file mode */
    }
    if (g_hook_mode == 1) {
        return orig_get_archive_flag(this_ptr);  /* Use real flag */
    }
    /* Hybrid: return 0 (direct mode) — CreateFileA hook handles fallback */
    return 0;
}

/* ============================================================
 * Hook 3: CreateFileA — for hybrid mode fallback
 *
 * When the game tries to open a file directly (in hybrid mode),
 * if the file doesn't exist, we temporarily switch to archive
 * mode so the archive lookup kicks in.
 * ============================================================ */

static InlineHook g_hook_createfile;
static HANDLE (WINAPI *orig_CreateFileA)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES,
                                          DWORD, DWORD, HANDLE) = NULL;

/* Track if we're in a fallback (archive lookup) */
static __thread bool g_in_fallback = false;

static HANDLE WINAPI hook_CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess,
                                       DWORD dwShareMode,
                                       LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                                       DWORD dwCreationDisposition,
                                       DWORD dwFlagsAndAttributes,
                                       HANDLE hTemplateFile)
{
    /* Always call original first */
    HANDLE result = orig_CreateFileA(lpFileName, dwDesiredAccess, dwShareMode,
                                      lpSecurityAttributes, dwCreationDisposition,
                                      dwFlagsAndAttributes, hTemplateFile);

    /* In hybrid mode, if direct file fails, let the game try archive.
     * The game's ResourceExists checks our hooked get_archive_flag,
     * which returns 0 (direct mode). But if CreateFileA fails here,
     * ResourceExists returns 0 (file not found) and the game reports error.
     *
     * For proper hybrid, we need to intercept at the ResourceExists level
     * (FUN_00653540) rather than CreateFileA. See hook_resource_exists below.
     */
    return result;
}

/* ============================================================
 * Hook 4: FUN_00653540 (ResourceExists) — full hybrid implementation
 *
 * Original behavior:
 *   if (archive_flag != 0) { archive_lookup(filename); }
 *   else { CreateFileA(filename); }
 *
 * Our hybrid behavior:
 *   1. Try CreateFileA(filename) — direct file mode
 *   2. If fails, call original (which will do archive lookup)
 *
 * This requires calling the original FUN_00653540 with the flag set to 1.
 * ============================================================ */

static InlineHook g_hook_resource_exists;

/* The original function signature (thiscall in MSVC, but we're hooking):
 *   bool __thiscall ResourceExists(Resource* this, LPCSTR filename)
 * In MinGW/clang we use __fastcall with this in ECX. */
typedef bool (__fastcall *ResourceExists_t)(void *, LPCSTR);
static ResourceExists_t orig_resource_exists = NULL;

static bool __fastcall hook_resource_exists(void *this_ptr, LPCSTR filename)
{
    if (g_hook_mode == 0) {
        /* Direct file only: try direct, never use archive */
        /* Just call original — our get_archive_flag hook returns 0,
         * so original will do CreateFileA only. */
        return orig_resource_exists(this_ptr, filename);
    }

    if (g_hook_mode == 1) {
        /* Archive only: call original (flag is 1, will use archive) */
        return orig_resource_exists(this_ptr, filename);
    }

    /* Hybrid mode: try direct file first */
    /* Temporarily set flag to 0 so original uses direct mode */
    /* But our get_archive_flag hook already returns 0... so original
     * will try direct file. If that fails, we need to try archive. */

    /* Step 1: Try direct file (original with flag=0) */
    bool result = orig_resource_exists(this_ptr, filename);
    if (result) {
        return true;  /* Found as direct file */
    }

    /* Step 2: Try archive mode.
     * We need to call original with flag=1, but our hook returns 0.
     * Solution: temporarily remove the get_flag hook, call original
     * (which will use real flag = 1 since set_flag was called),
     * then re-install hook. */

    /* Save current flag state */
    static bool flag_was_set = false;
    if (!flag_was_set) {
        /* The original set_archive_flag was called at startup,
         * so the real flag is 1. Our hook just returns 0 instead.
         * To use archive mode, we temporarily unhook get_flag. */
        RemoveInlineHook(&g_hook_get_flag);
        flag_was_set = true;
    }

    result = orig_resource_exists(this_ptr, filename);

    /* Re-install the hook to go back to direct mode for next file */
    if (flag_was_set) {
        /* Get the current address (might have moved due to ASLR, but
         * DaybreakDX is 32-bit without ASLR typically) */
        HMODULE hExe = GetModuleHandleA(NULL);
        void *get_flag_addr = (void *)((uintptr_t)hExe +
                                        (ADDR_GET_ARCHIVE_FLAG - ORIGINAL_IMAGE_BASE));
        InstallInlineHook(&g_hook_get_flag, get_flag_addr, hook_get_archive_flag);
        flag_was_set = false;
    }

    return result;
}

/* ============================================================
 * Installation
 * ============================================================ */

static bool InstallHooks(void)
{
    HMODULE hExe = GetModuleHandleA(NULL);
    if (!hExe) {
        MessageBoxA(NULL, "GetModuleHandle failed", "daybreak_hook", MB_OK);
        return false;
    }

    /* Calculate actual addresses (handles ASLR if enabled, though
     * DaybreakDX is typically loaded at its preferred base 0x00400000) */
    uintptr_t base = (uintptr_t)hExe;
    void *addr_set_flag = (void *)(base + (ADDR_SET_ARCHIVE_FLAG - ORIGINAL_IMAGE_BASE));
    void *addr_get_flag = (void *)(base + (ADDR_GET_ARCHIVE_FLAG - ORIGINAL_IMAGE_BASE));
    void *addr_res_exists = (void *)(base + (ADDR_RESOURCE_EXISTS - ORIGINAL_IMAGE_BASE));

    /* Read hook mode from environment variable if set */
    const char *mode_env = getenv("DAYBREAK_HOOK_MODE");
    if (mode_env) {
        g_hook_mode = atoi(mode_env);
    }

    /* Install hooks */
    bool ok = true;

    if (g_hook_mode == 0 || g_hook_mode == 2) {
        /* Hook set_flag: prevent it from enabling archive mode */
        if (!InstallInlineHook(&g_hook_set_flag, addr_set_flag, hook_set_archive_flag)) {
            ok = false;
        }
        /* Calculate trampoline address for calling original */
        orig_set_archive_flag = (void (*)(void *))((uintptr_t)addr_set_flag);
    }

    if (g_hook_mode == 0 || g_hook_mode == 2) {
        /* Hook get_flag: return 0 (direct mode) */
        if (!InstallInlineHook(&g_hook_get_flag, addr_get_flag, hook_get_archive_flag)) {
            ok = false;
        }
        orig_get_archive_flag = (int (*)(void *))((uintptr_t)addr_get_flag);
    }

    if (g_hook_mode == 2) {
        /* Hook resource_exists: hybrid mode */
        if (!InstallInlineHook(&g_hook_resource_exists, addr_res_exists, hook_resource_exists)) {
            ok = false;
        }
        orig_resource_exists = (ResourceExists_t)addr_res_exists;
    }

    /* Show a notification */
    char msg[256];
    snprintf(msg, sizeof(msg),
             "daybreak_hook loaded!\n\n"
             "Mode: %d (%s)\n"
             "Image base: 0x%p\n"
             "Hooks installed: %s",
             g_hook_mode,
             g_hook_mode == 0 ? "Direct file only" :
             g_hook_mode == 1 ? "Archive only" :
             g_hook_mode == 2 ? "Hybrid (direct + archive fallback)" : "Unknown",
             hExe,
             ok ? "Yes" : "Partial");
    MessageBoxA(NULL, msg, "daybreak_hook", MB_OK | MB_ICONINFORMATION);

    return ok;
}

static void RemoveHooks(void)
{
    RemoveInlineHook(&g_hook_set_flag);
    RemoveInlineHook(&g_hook_get_flag);
    RemoveInlineHook(&g_hook_resource_exists);
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
        InstallHooks();
        break;

    case DLL_PROCESS_DETACH:
        RemoveHooks();
        break;
    }
    return TRUE;
}
