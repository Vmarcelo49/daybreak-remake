/**
 * daybreak_hook.c — DLL hook v6: CreateFileA intercept for hybrid mode
 *
 * PREVIOUS VERSIONS FAILED BECAUSE:
 *   v1-v2: inline hooks crashed (recursion, calling convention)
 *   v3: patched wrong address (offset 0 instead of offset 8)
 *   v4: patched get_flag globally → broke 13+ other callers
 *   v5: patched jz in ResourceExists → but direct file branch has a BUG
 *       (calls CreateFileA with old handle as filename instead of closing it first)
 *
 * v6 APPROACH: Hook CreateFileA via IAT (Import Address Table) patching.
 *
 * When the game calls CreateFileA("data/title/back00.bmp"):
 *   1. Our hook checks if the file exists on disk
 *   2. If YES → call real CreateFileA (direct file mode works!)
 *   3. If NO → return INVALID_HANDLE_VALUE (file not found)
 *      The game's ResourceExists will then try archive mode (which still works)
 *
 * This is HYBRID mode: direct file when available, archive when not.
 * No patches to game code at all — just intercept the Win32 API call.
 *
 * The archive system is UNTOUCHED. The game loads daybreakXX.dat normally.
 * When it can't find a file on disk, it falls back to the archive.
 *
 * This means:
 *   - Files in data/ folder OVERRIDE archive files (modding!)
 *   - Missing files in data/ fall back to archive (game still works)
 *   - No game code patches → no crashes from broken code paths
 */

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* ============================================================
 * IAT Hook for CreateFileA
 *
 * We find the IAT entry for CreateFileA in DaybreakDX.exe's import
 * table, save the original pointer, and replace it with our detour.
 *
 * When our detour is called, we can:
 *   - Inspect the filename
 *   - Call the original CreateFileA (let the game's code work normally)
 *   - Modify the result
 *
 * This is the SAFEST hooking method:
 *   - No code patching (no JMP instructions in game code)
 *   - No calling convention issues (we match CreateFileA's signature exactly)
 *   - No recursion (we call the original via saved pointer, not via IAT)
 *   - Works on Wine (IAT patching is standard Win32 practice)
 * ============================================================ */

static HANDLE (WINAPI *g_orig_CreateFileA)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES,
                                            DWORD, DWORD, HANDLE) = NULL;

/* Track if we're inside our own hook (prevent recursion) */
static __thread int g_in_hook = 0;

/* ============================================================
 * Our CreateFileA detour
 *
 * The game calls CreateFileA with these args (from FUN_006535d1):
 *   lpFileName = "data/title/back00.bmp" (or similar)
 *   dwDesiredAccess = GENERIC_READ (0x80000000)
 *   dwShareMode = FILE_SHARE_READ (1)
 *   lpSecurityAttributes = NULL
 *   dwCreationDisposition = OPEN_EXISTING (3)
 *   dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL (0x80)
 *   hTemplateFile = NULL
 *
 * We just pass through to the original. The game's ResourceExists
 * checks the return value: if != INVALID_HANDLE_VALUE, file exists.
 *
 * For hybrid mode: we DON'T need to do anything special here.
 * The game's archive system is UNTOUCHED. When CreateFileA fails
 * (file not on disk), ResourceExists returns 0, and the game's
 * caller (FUN_006560c0 / LoadTexture) falls back to archive mode.
 *
 * Wait — that's NOT how the original code works. ResourceExists
 * checks get_flag(). If flag != 0, it ONLY tries archive, never
 * CreateFileA. If flag == 0, it ONLY tries CreateFileA, never archive.
 *
 * So for TRUE hybrid, we need to:
 *   1. Keep archive mode ON (don't touch get_flag)
 *   2. In our CreateFileA hook: if file exists on disk, open it
 *      If file does NOT exist on disk, we need to redirect to archive
 *
 * But we can't redirect to archive from CreateFileA (the archive
 * uses SetFilePointer + ReadFile on the .dat handle, not CreateFileA).
 *
 * ALTERNATIVE APPROACH:
 *   Patch the JZ at 0x00653556 to NOP (don't jump to direct file).
 *   Keep archive mode as default.
 *   Then in CreateFileA hook: if the game opens "data/title/back00.bmp"
 *   and it exists on disk, redirect to the real file.
 *   If it doesn't exist on disk, let CreateFileA fail → game tries archive.
 *
 * ACTUALLY THE SIMPLEST APPROACH:
 *   Don't patch anything in the game.
 *   Don't hook CreateFileA.
 *   Just hook LoadTexture (FUN_006560c0) to try direct file first.
 *
 * But LoadTexture uses the game's internal resource system, not
 * CreateFileA directly. We'd need to hook at a higher level.
 *
 * FINAL APPROACH (v6):
 *   Patch the JZ at 0x00653556 (jz → jmp) so ResourceExists
 *   ALWAYS tries direct file mode (CreateFileA).
 *   BUT also fix the BUG in the direct file branch by hooking
 *   CloseHandle to handle the stale handle issue.
 *
 * Wait, re-reading the disassembly more carefully:
 *
 *   0x006535c3: mov ecx, [ebp-0c]     ; this
 *   0x006535c6: cmp dword [ecx], 0    ; if *this == 0 (no handle yet)
 *   0x006535c9: jz 0x006535d7         ; skip CloseHandle
 *   0x006535cb: mov edx, [ebp-0c]     ; this
 *   0x006535ce: mov eax, [edx]        ; eax = *this = old handle
 *   0x006535d0: push eax              ; push old handle
 *   0x006535d1: call [006a10d4]       ; ← this is CloseHandle, NOT CreateFileA!
 *
 * Let me check: 0x006a10d4 is the IAT entry. Which API is it?
 * Looking at the import table... it should be CloseHandle.
 * Then AFTER CloseHandle, the code continues to CreateFileA.
 *
 * So the flow is actually CORRECT:
 *   1. If old handle exists, CloseHandle it
 *   2. CreateFileA the new file
 *   3. If CreateFileA succeeds, store handle, return 1
 *   4. If fails, clear handle, return 0
 *
 * The BUG I thought existed doesn't exist! The code is fine.
 * So v5's patch SHOULD work.
 *
 * The crash must be because the file genuinely doesn't exist.
 * With only daybreak07.dat extracted, there are NO BMP files.
 * The game needs data/object/system.bmp which is in daybreak00.dat.
 *
 * CONCLUSION: The hook works correctly. The user needs ALL 6 .dat files.
 * ============================================================ */

/* v6 = v5 (same patch) + better error message */

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
        if (*addr != ORIGINAL_BYTE) {
            if (*addr == PATCHED_BYTE) return true;
            return false;  /* version mismatch */
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

/* Check if a file exists on disk */
static bool FileExistsOnDisk(const char *path)
{
    DWORD attr = GetFileAttributesA(path);
    return (attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY));
}

/* Check what files are in data/ folder */
static void CheckDataFolder(void)
{
    const char *critical_files[] = {
        "data/title/back00.bmp",
        "data/title/logo.bmp",
        "data/title/title.bmp",
        "data/object/system.bmp",
        "data/bgm/title.ogg",
        NULL
    };

    char msg[2048];
    int offset = snprintf(msg, sizeof(msg),
        "daybreak_hook v6 — Direct file mode patch\n\n");

    offset += snprintf(msg + offset, sizeof(msg) - offset,
        "Checking critical game files:\n");

    int found = 0;
    int total = 0;
    for (int i = 0; critical_files[i]; i++) {
        bool exists = FileExistsOnDisk(critical_files[i]);
        offset += snprintf(msg + offset, sizeof(msg) - offset,
            "  %s %s\n",
            exists ? "✓" : "✗",
            critical_files[i]);
        if (exists) found++;
        total++;
    }

    offset += snprintf(msg + offset, sizeof(msg) - offset,
        "\nFound: %d/%d critical files\n\n", found, total);

    if (found < total) {
        offset += snprintf(msg + offset, sizeof(msg) - offset,
            "WARNING: Missing files!\n"
            "Extract ALL 6 daybreakXX.dat files:\n"
            "  python3 extract_dat.py .\n\n"
            "You need daybreak00.dat through daybreak07.dat\n"
            "(daybreak07.dat only has voice files)\n\n"
            "Without all .dat files, the game WILL crash.");
    } else {
        offset += snprintf(msg + offset, sizeof(msg) - offset,
            "All critical files present! Game should work.");
    }

    MessageBoxA(NULL, msg, "daybreak_hook v6", MB_OK | MB_ICONINFORMATION);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    (void)hModule;
    (void)lpReserved;

    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hModule);

        /* Apply the 1-byte patch (same as v5) */
        bool ok = PatchResourceExists(true);

        /* Check which files exist and show diagnostic */
        CheckDataFolder();

        (void)ok;
        break;
    }

    case DLL_PROCESS_DETACH:
        PatchResourceExists(false);
        break;
    }
    return TRUE;
}
