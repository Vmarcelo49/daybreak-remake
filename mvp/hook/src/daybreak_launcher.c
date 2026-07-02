/**
 * daybreak_launcher.c — Launcher that injects daybreak_hook.dll into DaybreakDX.exe
 *
 * Usage:
 *   daybreak_launcher.exe [DaybreakDX.exe path] [daybreak_hook.dll path]
 *
 * If no args, defaults to:
 *   exe:  DaybreakDX.exe (in current directory)
 *   dll:  daybreak_hook.dll (in current directory)
 *
 * The launcher:
 *   1. Creates DaybreakDX.exe in suspended state
 *   2. Allocates memory in the target process for the DLL path
 *   3. Calls LoadLibraryA in the target process to load daybreak_hook.dll
 *   4. Resumes the main thread
 *
 * This is the classic DLL injection technique — works on all Windows versions.
 */

#include <windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <tlhelp32.h>

static DWORD GetProcessIdByName(const char *exe_name)
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) return 0;

    PROCESSENTRY32 pe = {0};
    pe.dwSize = sizeof(pe);

    DWORD pid = 0;
    if (Process32First(snapshot, &pe)) {
        do {
            if (_stricmp(pe.szExeFile, exe_name) == 0) {
                pid = pe.th32ProcessID;
                break;
            }
        } while (Process32Next(snapshot, &pe));
    }
    CloseHandle(snapshot);
    return pid;
}

static bool EnableDebugPrivilege(void)
{
    HANDLE token;
    if (!OpenProcessToken(GetCurrentProcess(),
                          TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token)) {
        return false;
    }

    TOKEN_PRIVILEGES tp;
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (!LookupPrivilegeValueA(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid)) {
        CloseHandle(token);
        return false;
    }

    bool ok = AdjustTokenPrivileges(token, FALSE, &tp, 0, NULL, NULL);
    CloseHandle(token);
    return ok;
}

static bool InjectDll(HANDLE process, const char *dll_path)
{
    SIZE_T path_len = strlen(dll_path) + 1;

    /* 1. Allocate memory in target process for the DLL path string */
    void *remote_mem = VirtualAllocEx(process, NULL, path_len,
                                       MEM_COMMIT | MEM_RESERVE,
                                       PAGE_READWRITE);
    if (!remote_mem) {
        printf("VirtualAllocEx failed (error %lu)\n", GetLastError());
        return false;
    }

    /* 2. Write the DLL path into the target process */
    SIZE_T written;
    if (!WriteProcessMemory(process, remote_mem, dll_path, path_len, &written)) {
        printf("WriteProcessMemory failed (error %lu)\n", GetLastError());
        VirtualFreeEx(process, remote_mem, 0, MEM_RELEASE);
        return false;
    }

    /* 3. Get LoadLibraryA address (same in all processes on same Windows) */
    HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
    FARPROC load_library = GetProcAddress(hKernel32, "LoadLibraryA");
    if (!load_library) {
        printf("GetProcAddress(LoadLibraryA) failed\n");
        VirtualFreeEx(process, remote_mem, 0, MEM_RELEASE);
        return false;
    }

    /* 4. Create remote thread that calls LoadLibraryA(dll_path) */
    HANDLE thread = CreateRemoteThread(process, NULL, 0,
                                        (LPTHREAD_START_ROUTINE)load_library,
                                        remote_mem, 0, NULL);
    if (!thread) {
        printf("CreateRemoteThread failed (error %lu)\n", GetLastError());
        VirtualFreeEx(process, remote_mem, 0, MEM_RELEASE);
        return false;
    }

    /* 5. Wait for the thread to finish (DLL loads) */
    WaitForSingleObject(thread, 10000);  /* 10 sec timeout */

    /* 6. Cleanup */
    CloseHandle(thread);
    VirtualFreeEx(process, remote_mem, 0, MEM_RELEASE);

    return true;
}

int main(int argc, char *argv[])
{
    const char *exe_path = (argc > 1) ? argv[1] : "DaybreakDX.exe";
    const char *dll_path = (argc > 2) ? argv[2] : "daybreak_hook.dll";

    printf("=== daybreak_launcher ===\n");
    printf("EXE: %s\n", exe_path);
    printf("DLL: %s\n", dll_path);
    printf("\n");

    /* Enable debug privilege (helps with injection) */
    EnableDebugPrivilege();

    /* 1. Create the game process in suspended state */
    STARTUPINFOA si = {0};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi = {0};

    char cmd_line[MAX_PATH];
    snprintf(cmd_line, sizeof(cmd_line), "\"%s\"", exe_path);

    /* Set working directory to the game's folder so relative paths work */
    char work_dir[MAX_PATH];
    strncpy(work_dir, exe_path, MAX_PATH - 1);
    work_dir[MAX_PATH - 1] = '\0';
    char *last_slash = strrchr(work_dir, '\\');
    if (last_slash) {
        *last_slash = '\0';
    } else {
        GetCurrentDirectoryA(MAX_PATH, work_dir);
    }

    printf("Working directory: %s\n", work_dir);

    if (!CreateProcessA(NULL, cmd_line, NULL, NULL, FALSE,
                        CREATE_SUSPENDED, NULL, work_dir, &si, &pi)) {
        printf("CreateProcess failed (error %lu)\n", GetLastError());
        printf("Make sure DaybreakDX.exe is in the current directory.\n");
        return 1;
    }

    printf("Created process (PID: %lu) in suspended state\n", pi.dwProcessId);

    /* 2. Inject the DLL */
    printf("Injecting %s...\n", dll_path);
    if (!InjectDll(pi.hProcess, dll_path)) {
        printf("Injection failed!\n");
        TerminateProcess(pi.hProcess, 1);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        return 1;
    }
    printf("DLL injected successfully!\n");

    /* 3. Resume the main thread — game starts with our hooks active */
    printf("Resuming main thread...\n");
    ResumeThread(pi.hThread);

    /* 4. Wait for the game to exit */
    printf("Waiting for game to exit...\n");
    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD exit_code;
    GetExitCodeProcess(pi.hProcess, &exit_code);
    printf("Game exited with code %lu\n", exit_code);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return 0;
}
