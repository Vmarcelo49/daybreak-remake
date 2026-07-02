/**
 * daybreak_hook.c — DLL hook v8: direct file mode with .cnv conversion
 *
 * PREVIOUS APPROACHES:
 *   v1-v4: various hook/patch attempts, all crashed
 *   v5-v6: forced direct file mode → .cnv files couldn't be read
 *   v7: no patches → game works normally but no modding
 *
 * v8: Same 1-byte patch as v5 (jz→jmp in ResourceExists) BUT
 *     extract_dat.py now CONVERTS .cnv to .bmp/.wav during extraction.
 *
 * HOW IT WORKS:
 *   1. extract_dat.py extracts .dat → .cnv → .bmp/.wav (auto-converted)
 *   2. Hook patches ResourceExists to always use direct file mode
 *   3. Game calls CreateFileA("data/title/back00.bmp")
 *   4. File exists as .bmp on disk → CreateFileA succeeds
 *   5. Game reads BMP data directly → works!
 *
 *   For audio: game calls for "data/voice/.../xxx.wav"
 *   (FUN_00661d10 changes .wav to .cnv, but we have .wav on disk)
 *   Wait — the game CHANGES the extension to .cnv before opening.
 *   So if the game looks for "xxx.cnv", but we have "xxx.wav" on disk...
 *   CreateFileA("xxx.cnv") will FAIL.
 *
 *   SOLUTION: extract_dat.py must keep BOTH .cnv AND .bmp/.wav versions.
 *   Or better: the hook intercepts CreateFileA and redirects .cnv → .bmp/.wav.
 *
 * ACTUALLY: Looking at FUN_00661d10 again:
 *   - It takes "data/title/back00.bmp"
 *   - Changes LAST 3 chars to "cnv" → "data/title/back00.cnv"
 *   - Then calls FUN_00665e70 which calls ResourceExists("data/title/back00.cnv")
 *
 *   So the game opens "data/title/back00.cnv" not "data/title/back00.bmp"!
 *
 *   For direct file mode to work with converted files, we need:
 *   - Keep the .cnv extension on disk BUT with BMP/WAV content
 *   - OR hook CreateFileA to redirect .cnv → .bmp/.wav
 *
 * SIMPLEST: extract_dat.py converts CONTENT but keeps .cnv extension.
 *   - .cnv with BMP content → keep as .cnv (game reads it as BMP)
 *   - .cnv with audio content → convert to WAV but keep as .cnv?
 *     No — the game reads audio .cnv with custom header, not WAV format.
 *
 * FOR AUDIO: the game's audio .cnv reader (FUN_00665020 path) reads
 *   16-byte header + PCM. If we write a WAV file with .cnv extension,
 *   the game would try to parse WAV header as the custom 16-byte header → fail.
 *
 * FOR IMAGES: the game's image .cnv reader checks for "BM" magic.
 *   If the .cnv IS a BMP (starts with "BM"), direct file mode works!
 *   We just need to keep the .cnv extension but with BMP content.
 *
 * CONCLUSION for v8:
 *   - Image .cnv files: already BMP content, keep .cnv extension on disk
 *   - Audio .cnv files: keep original .cnv format (don't convert to WAV)
 *   - extract_dat.py should NOT convert — just extract as-is
 *   - Hook patches ResourceExists to use direct file mode
 *   - Game opens "data/title/back00.cnv" from disk → reads BMP → works!
 *
 * So v8 = v5 patch + extract_dat.py WITHOUT conversion.
 * The .cnv files on disk are readable by the game because:
 *   - Image .cnv = BMP file (game checks "BM" magic)
 *   - Audio .cnv = custom header + PCM (game reads 16-byte header)
 */

#define ADDR_RESOURCE_EXISTS    0x00653540
#define PATCH_OFFSET            0x16
#define ORIGINAL_BYTE           0x74  /* JZ */
#define PATCHED_BYTE            0xEB  /* JMP */
#define ORIGINAL_IMAGE_BASE     0x00400000

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

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
            return false;
        }
        g_saved_byte = *addr;
    }

    DWORD old_protect;
    if (!VirtualProtect(addr, 1, PAGE_EXECUTE_READWRITE, &old_protect))
        return false;

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

        char msg[512];
        snprintf(msg, sizeof(msg),
            "daybreak_hook v8 loaded!\n\n"
            "Patch: ResourceExists jz→jmp (direct file mode)\n"
            "Status: %s\n\n"
            "IMPORTANT: .cnv files must be extracted to data/ folder.\n"
            "The game opens .cnv files directly from disk.\n"
            "Image .cnv = BMP content, audio .cnv = custom WAV.\n"
            "Run: python3 extract_dat.py .",
            ok ? "SUCCESS" : "FAILED");

        MessageBoxA(NULL, msg, "daybreak_hook v8", MB_OK | MB_ICONINFORMATION);
        break;
    }
    case DLL_PROCESS_DETACH:
        PatchResourceExists(false);
        break;
    }
    return TRUE;
}
