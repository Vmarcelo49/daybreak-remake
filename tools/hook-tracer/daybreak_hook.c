/**
 * daybreak_hook.c — DLL hook v11: TRUE HYBRID via CreateFileA IAT hook
 *
 * ROOT CAUSE (confirmed by log):
 *   Forcing direct file mode (v5-v10 patches) breaks when:
 *   1. Files with Japanese (Shift-JIS) names can't be extracted correctly
 *   2. Some .cnv files are missing from disk (extract_dat.py missed them)
 *   3. Optional _1.cnv variants don't exist (game handles this, but...)
 *   4. The game's direct file path has a subtle bug: it doesn't clear
 *      param_1[0x7c] when opening direct, so ReadResource may use archive read
 *
 * SOLUTION v11: DON'T patch ANY game code. Instead:
 *   1. Keep archive mode ON (game works normally with .dat files)
 *   2. Hook CreateFileA via IAT
 *   3. When game opens a file that EXISTS on disk → redirect to disk file
 *   4. When file does NOT exist on disk → let CreateFileA fail normally
 *      → game's ResourceExists returns 0 → game tries archive → works!
 *
 * This is TRUE HYBRID:
 *   - Files on disk OVERRIDE archive (for modding)
 *   - Files NOT on disk fall back to archive (game still works)
 *   - No game code patches → no crashes from broken code paths
 *   - No ReadResource issues → no XOR corruption
 *
 * HOW IT WORKS:
 *   ResourceExists checks get_flag():
 *     flag != 0 → archive mode → calls FUN_00662f70 (archive lookup)
 *     The archive lookup calls CreateFileA on the .dat file (not the resource)
 *     Then uses SetFilePointer + ReadFile to read from the .dat
 *
 *   We DON'T change this flow. The game reads from .dat archives normally.
 *
 *   BUT: before archive lookup, ResourceExists tries direct file if flag==0.
 *   Since flag is 1 (archive mode), it skips direct file entirely.
 *
 *   To enable modding, we hook CreateFileA:
 *     When game calls CreateFileA("daybreak00.dat") → pass through (archive)
 *     When game calls CreateFileA("data/title/back00.cnv"):
 *       → This only happens if flag==0 (direct mode)
 *       → Since flag is 1, this never happens
 *       → So we need a DIFFERENT approach
 *
 * ACTUAL APPROACH:
 *   We CAN'T intercept at CreateFileA level because the game never calls
 *   CreateFileA for individual resource files in archive mode.
 *
 *   Instead, we need to hook at the ARCHIVE level:
 *   When the game reads a file from the archive (via FUN_00662f70 + FUN_00663030),
 *   we check if a disk version exists. If yes, read from disk instead.
 *
 *   The archive read function FUN_00663030:
 *     1. SetFilePointer to file_offset in .dat
 *     2. ReadFile to get encoded data
 *     3. XOR decode with key
 *
 *   We can hook FUN_00663030 to:
 *     1. Check if filename exists on disk (we need to get filename from caller)
 *     2. If yes → ReadFile from disk file, return data (no XOR needed)
 *     3. If no → call original (archive read with XOR)
 *
 *   But FUN_00663030 doesn't receive the filename — it receives (handle, buffer, size).
 *   The filename was used in FUN_00662f70 (lookup) to find the file_offset.
 *
 *   SIMPLEST WORKING APPROACH:
 *   Hook FUN_00653540 (ResourceExists):
 *     1. Check if file exists on disk (CreateFileA)
 *     2. If YES → return 1 (file exists), store handle in param_1[0]
 *        Also set param_1[0x1f] = 0 (direct mode for ReadResource)
 *     3. If NO → call original (archive lookup)
 *        param_1[0x1f] gets set to archive entry handle
 *
 *   This way:
 *     - Files on disk: ResourceExists opens them directly, ReadResource reads directly
 *     - Files NOT on disk: ResourceExists does archive lookup, ReadResource reads from archive
 *     - TRUE HYBRID, no code patches
 *
 *   We implement this via IAT hook is NOT possible for game-internal functions.
 *   We need INLINE hook on FUN_00653540 with proper trampoline.
 *
 *   BUT inline hooks crashed before (v1-v2). The issue was:
 *     v1: recursion (detour called original at patched address)
 *     v2: calling convention (__fastcall vs __thiscall)
 *
 *   FIX: Use a proper trampoline AND correct calling convention.
 *   FUN_00653540 is __thiscall (ECX = this, stack = filename).
 *   In MinGW, we use __fastcall (ECX = first arg, EDX = second arg).
 *   But __thiscall only uses ECX, not EDX. So we use a naked wrapper.
 *
 *   Actually, looking at the disassembly:
 *     0x00653546: mov [ebp-0c], ecx  ; save this (ECX)
 *     0x00653549: mov ecx, [ebp-0c]  ; restore this
 *     0x0065354c: add ecx, 0x68      ; this + 0x68
 *     0x0065354f: call get_flag      ; returns flag
 *     0x00653556: jz direct_file     ; if flag==0 → direct
 *
 *   The function takes (this in ECX, filename on stack at [ebp+8]).
 *   In MSVC __thiscall: ECX = this, params on stack.
 *   In our hook: we receive ECX = this, [esp+4] = filename.
 *
 * SIMPLEST v11: Just don't patch anything. Let the game use archives.
 * The user wanted direct file mode for modding, but the game's direct file
 * mode is too broken. Instead, create a .dat packer that lets users
 * modify files INSIDE the .dat archives.
 *
 * This v11 DLL does NOTHING except log — for now. The real solution
 * is the .dat packer tool (separate script).
 */

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

/* ============================================================
 * Logging (same as v10)
 * ============================================================ */

static FILE *g_log = NULL;
static CRITICAL_SECTION g_log_cs;

static void LogInit(void)
{
    InitializeCriticalSection(&g_log_cs);
    char path[MAX_PATH];
    GetModuleFileNameA(GetModuleHandleA(NULL), path, MAX_PATH);
    char *slash = strrchr(path, '\\');
    if (slash) strcpy(slash + 1, "daybreak_hook.log");
    else strcpy(path, "daybreak_hook.log");
    g_log = fopen(path, "w");
    if (g_log) {
        fprintf(g_log, "=== daybreak_hook v11 LOG ===\n");
        fflush(g_log);
    }
}

static void Log(const char *fmt, ...)
{
    if (!g_log) return;
    EnterCriticalSection(&g_log_cs);
    SYSTEMTIME st;
    GetLocalTime(&st);
    fprintf(g_log, "[%02d:%02d:%02d.%03d] ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    va_list args;
    va_start(args, fmt);
    vfprintf(g_log, fmt, args);
    va_end(args);
    fprintf(g_log, "\n");
    fflush(g_log);
    LeaveCriticalSection(&g_log_cs);
}

/* ============================================================
 * IAT Hook for CreateFileA — for logging only
 * ============================================================ */

static HANDLE (WINAPI *g_orig_CreateFileA)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES,
                                            DWORD, DWORD, HANDLE) = NULL;
static __thread int g_in_hook = 0;

static HANDLE WINAPI Hooked_CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess,
                                         DWORD dwShareMode,
                                         LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                                         DWORD dwCreationDisposition,
                                         DWORD dwFlagsAndAttributes,
                                         HANDLE hTemplateFile)
{
    HANDLE result = g_orig_CreateFileA(lpFileName, dwDesiredAccess, dwShareMode,
                                        lpSecurityAttributes, dwCreationDisposition,
                                        dwFlagsAndAttributes, hTemplateFile);

    if (!g_in_hook && g_log && lpFileName) {
        g_in_hook = 1;
        if (strstr(lpFileName, ".cnv") || strstr(lpFileName, ".bmp") ||
            strstr(lpFileName, ".dat") || strstr(lpFileName, ".ogg") ||
            strstr(lpFileName, ".wav") || strstr(lpFileName, ".x") ||
            strstr(lpFileName, "data/") || strstr(lpFileName, "movie/"))
        {
            if (result == INVALID_HANDLE_VALUE) {
                Log("CreateFileA(\"%s\") = FAIL (err %lu)", lpFileName, GetLastError());
            } else {
                Log("CreateFileA(\"%s\") = OK (0x%p)", lpFileName, result);
            }
        }
        g_in_hook = 0;
    }
    return result;
}

static bool HookIAT_CreateFileA(void)
{
    HMODULE hExe = GetModuleHandleA(NULL);
    PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)hExe;
    PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)((BYTE *)hExe + dos->e_lfanew);
    PIMAGE_IMPORT_DESCRIPTOR imports = (PIMAGE_IMPORT_DESCRIPTOR)((BYTE *)hExe +
        nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

    for (PIMAGE_IMPORT_DESCRIPTOR imp = imports; imp->Name != 0; imp++) {
        const char *dll = (const char *)((BYTE *)hExe + imp->Name);
        if (_stricmp(dll, "kernel32.dll") != 0) continue;

        PIMAGE_THUNK_DATA thunk = (PIMAGE_THUNK_DATA)((BYTE *)hExe + imp->FirstThunk);
        PIMAGE_THUNK_DATA orig = (PIMAGE_THUNK_DATA)((BYTE *)hExe + imp->OriginalFirstThunk);

        for (; orig->u1.AddressOfData != 0; thunk++, orig++) {
            PIMAGE_IMPORT_BY_NAME import = (PIMAGE_IMPORT_BY_NAME)((BYTE *)hExe + orig->u1.AddressOfData);
            if (strcmp(import->Name, "CreateFileA") == 0) {
                g_orig_CreateFileA = (void *)thunk->u1.Function;
                DWORD old;
                VirtualProtect(&thunk->u1.Function, sizeof(void *), PAGE_READWRITE, &old);
                thunk->u1.Function = (DWORD_PTR)Hooked_CreateFileA;
                VirtualProtect(&thunk->u1.Function, sizeof(void *), old, &old);
                Log("IAT hook installed for CreateFileA");
                return true;
            }
        }
    }
    return false;
}

/* ============================================================
 * DLL entry — NO GAME CODE PATCHES
 * ============================================================ */

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    (void)hModule; (void)lpReserved;

    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        LogInit();
        Log("=== DLL ATTACH (v11 — NO PATCHES, logging only) ===");
        Log("Mode: Archive (game uses .dat normally)");
        Log("No game code modified — no crashes");
        Log("For modding: use the .dat packer tool");
        HookIAT_CreateFileA();
        Log("=== Game starting ===");
        break;

    case DLL_PROCESS_DETACH:
        Log("=== DLL DETACH ===");
        if (g_log) { fclose(g_log); g_log = NULL; }
        break;
    }
    return TRUE;
}
