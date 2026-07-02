/**
 * daybreak_hook.c — DLL hook v10: LOGGING version
 *
 * This version hooks CreateFileA via IAT (Import Address Table) and
 * logs EVERY file the game tries to open, with success/failure status.
 *
 * Also applies the 2 patches (ResourceExists + ReadResource jz→jmp).
 *
 * Log file: daybreak_hook.log (next to the game exe)
 *
 * The log will show:
 *   [HH:MM:SS.mmm] CreateFileA("data/title/back00.cnv") = 0x1234 (SUCCESS)
 *   [HH:MM:SS.mmm] CreateFileA("data/voice/xxx.cnv") = INVALID (NOT FOUND)
 *   etc.
 */

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* ============================================================
 * Patch addresses
 * ============================================================ */

#define ADDR_RESOURCE_EXISTS    0x00653540
#define ADDR_READ_RESOURCE      0x00653760
#define RES_PATCH_OFFSET        0x16
#define READ_PATCH_OFFSET       0x0E
#define ORIGINAL_BYTE           0x74
#define PATCHED_BYTE            0xEB
#define ORIGINAL_IMAGE_BASE     0x00400000

/* ============================================================
 * Logging
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
        fprintf(g_log, "=== daybreak_hook v10 LOG ===\n");
        fprintf(g_log, "Image base: 0x%p\n", GetModuleHandleA(NULL));
        fflush(g_log);
    }
}

static void Log(const char *fmt, ...)
{
    if (!g_log) return;
    EnterCriticalSection(&g_log_cs);

    SYSTEMTIME st;
    GetLocalTime(&st);
    fprintf(g_log, "[%02d:%02d:%02d.%03d] ",
            st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

    va_list args;
    va_start(args, fmt);
    vfprintf(g_log, fmt, args);
    va_end(args);

    fprintf(g_log, "\n");
    fflush(g_log);

    LeaveCriticalSection(&g_log_cs);
}

static void LogClose(void)
{
    if (g_log) {
        Log("=== DLL DETACH ===");
        fclose(g_log);
        g_log = NULL;
    }
    DeleteCriticalSection(&g_log_cs);
}

/* ============================================================
 * IAT Hook for CreateFileA
 *
 * Find the IAT entry in the import table and replace it.
 * ============================================================ */

static HANDLE (WINAPI *g_orig_CreateFileA)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES,
                                            DWORD, DWORD, HANDLE) = NULL;

/* Track re-entrancy (some CreateFileA calls are from our own code) */
static __thread int g_in_hook = 0;

static HANDLE WINAPI Hooked_CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess,
                                         DWORD dwShareMode,
                                         LPSECURITY_ATTRIBUTES lpSecurityAttributes,
                                         DWORD dwCreationDisposition,
                                         DWORD dwFlagsAndAttributes,
                                         HANDLE hTemplateFile)
{
    /* Call original first */
    HANDLE result = g_orig_CreateFileA(lpFileName, dwDesiredAccess, dwShareMode,
                                        lpSecurityAttributes, dwCreationDisposition,
                                        dwFlagsAndAttributes, hTemplateFile);

    /* Log only if not inside our own code */
    if (!g_in_hook && g_log && lpFileName) {
        g_in_hook = 1;

        /* Only log file accesses (skip pipes, console, etc.) */
        if (strncmp(lpFileName, "data/", 5) == 0 ||
            strncmp(lpFileName, "movie/", 6) == 0 ||
            strncmp(lpFileName, "daybreak", 8) == 0 ||
            strncmp(lpFileName, "config", 6) == 0 ||
            strstr(lpFileName, ".cnv") ||
            strstr(lpFileName, ".bmp") ||
            strstr(lpFileName, ".dat") ||
            strstr(lpFileName, ".ogg") ||
            strstr(lpFileName, ".wav") ||
            strstr(lpFileName, ".x") ||
            strstr(lpFileName, ".mpg"))
        {
            if (result == INVALID_HANDLE_VALUE) {
                DWORD err = GetLastError();
                Log("CreateFileA(\"%s\") = FAIL (error %lu)", lpFileName, err);
            } else {
                Log("CreateFileA(\"%s\") = 0x%p (OK)", lpFileName, result);
            }
        }

        g_in_hook = 0;
    }

    return result;
}

/* Find and patch IAT entry for CreateFileA */
static bool HookIAT(void)
{
    HMODULE hExe = GetModuleHandleA(NULL);
    if (!hExe) return false;

    PIMAGE_DOS_HEADER dos = (PIMAGE_DOS_HEADER)hExe;
    PIMAGE_NT_HEADERS nt = (PIMAGE_NT_HEADERS)((BYTE *)hExe + dos->e_lfanew);
    PIMAGE_IMPORT_DESCRIPTOR imports = (PIMAGE_IMPORT_DESCRIPTOR)((BYTE *)hExe +
        nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

    for (PIMAGE_IMPORT_DESCRIPTOR imp = imports; imp->Name != 0; imp++) {
        const char *dll_name = (const char *)((BYTE *)hExe + imp->Name);
        if (_stricmp(dll_name, "kernel32.dll") != 0) continue;

        PIMAGE_THUNK_DATA thunk = (PIMAGE_THUNK_DATA)((BYTE *)hExe + imp->FirstThunk);
        PIMAGE_THUNK_DATA orig_thunk = (PIMAGE_THUNK_DATA)((BYTE *)hExe + imp->OriginalFirstThunk);

        for (; orig_thunk->u1.AddressOfData != 0; thunk++, orig_thunk++) {
            PIMAGE_IMPORT_BY_NAME import = (PIMAGE_IMPORT_BY_NAME)((BYTE *)hExe +
                orig_thunk->u1.AddressOfData);
            if (strcmp(import->Name, "CreateFileA") == 0) {
                /* Found! Save original and replace */
                g_orig_CreateFileA = (HANDLE (WINAPI *)(LPCSTR, DWORD, DWORD,
                    LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE))thunk->u1.Function;

                DWORD old_protect;
                VirtualProtect(&thunk->u1.Function, sizeof(void *),
                               PAGE_READWRITE, &old_protect);
                thunk->u1.Function = (DWORD_PTR)Hooked_CreateFileA;
                VirtualProtect(&thunk->u1.Function, sizeof(void *),
                               old_protect, &old_protect);

                Log("IAT hook: CreateFileA hooked at IAT 0x%p", &thunk->u1.Function);
                return true;
            }
        }
    }
    Log("IAT hook: CreateFileA NOT FOUND in import table");
    return false;
}

/* ============================================================
 * Binary patches (same as v9)
 * ============================================================ */

static unsigned char g_saved_res[1];
static unsigned char g_saved_read[1];

static bool PatchByte(void *addr, unsigned char new_val, unsigned char *saved)
{
    if (*(unsigned char *)addr != ORIGINAL_BYTE) {
        if (*(unsigned char *)addr == PATCHED_BYTE) return true;
        Log("Patch: byte at 0x%p is 0x%02x (expected 0x%02x) — VERSION MISMATCH",
            addr, *(unsigned char *)addr, ORIGINAL_BYTE);
        return false;
    }
    *saved = *(unsigned char *)addr;

    DWORD old_protect;
    if (!VirtualProtect(addr, 1, PAGE_EXECUTE_READWRITE, &old_protect)) return false;
    *(unsigned char *)addr = new_val;
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

    Log("Patching ResourceExists at 0x%p (offset +0x%02x)", res_addr, RES_PATCH_OFFSET);
    Log("  Byte before: 0x%02x", *res_addr);
    bool ok1 = PatchByte(res_addr, PATCHED_BYTE, g_saved_res);
    Log("  Byte after: 0x%02x, result: %s", *res_addr, ok1 ? "OK" : "FAIL");

    Log("Patching ReadResource at 0x%p (offset +0x%02x)", read_addr, READ_PATCH_OFFSET);
    Log("  Byte before: 0x%02x", *read_addr);
    bool ok2 = PatchByte(read_addr, PATCHED_BYTE, g_saved_read);
    Log("  Byte after: 0x%02x, result: %s", *read_addr, ok2 ? "OK" : "FAIL");

    return ok1 && ok2;
}

/* ============================================================
 * DLL entry
 * ============================================================ */

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    (void)hModule;
    (void)lpReserved;

    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        LogInit();
        Log("=== DLL PROCESS ATTACH ===");
        Log("Installing patches...");
        bool patched = InstallPatches();
        Log("Patches: %s", patched ? "OK" : "FAILED");
        Log("Installing IAT hook for CreateFileA...");
        bool hooked = HookIAT();
        Log("IAT hook: %s", hooked ? "OK" : "FAILED");

        /* Check which critical files exist */
        const char *files[] = {
            "data/title/back00.cnv",
            "data/title/logo.cnv",
            "data/title/title.cnv",
            "data/object/system.cnv",
            "data/object/system.bmp",
            "data/object/P04.cnv",
            "data/bgm/title.ogg",
            "daybreak00.dat",
            "daybreak02.dat",
            "daybreak04.dat",
            "daybreak05.dat",
            "daybreak06.dat",
            "daybreak07.dat",
            NULL
        };
        Log("");
        Log("=== File existence check ===");
        for (int i = 0; files[i]; i++) {
            DWORD attr = GetFileAttributesA(files[i]);
            if (attr != INVALID_FILE_ATTRIBUTES) {
                HANDLE h = CreateFileA(files[i], GENERIC_READ, FILE_SHARE_READ, NULL,
                                       OPEN_EXISTING, 0, NULL);
                if (h != INVALID_HANDLE_VALUE) {
                    DWORD size = GetFileSize(h, NULL);
                    CloseHandle(h);
                    Log("  EXISTS: %s (%lu bytes)", files[i], size);
                } else {
                    Log("  EXISTS but can't open: %s (error %lu)", files[i], GetLastError());
                }
            } else {
                Log("  MISSING: %s", files[i]);
            }
        }
        Log("");
        Log("=== Game starting (logging CreateFileA calls) ===");
        break;

    case DLL_PROCESS_DETACH:
        Log("=== DLL PROCESS DETACH ===");
        LogClose();
        break;
    }
    return TRUE;
}
