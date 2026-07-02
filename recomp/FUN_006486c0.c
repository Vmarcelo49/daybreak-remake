// ============================================
// Address:  0x006486c0
// Original: FUN_006486c0
// Status:   unreviewed
// ============================================

bool __fastcall FUN_006486c0(LPVOID param_1)

{
    bool bVar1;
    DWORD local_c;
    HANDLE local_8;

    local_8 =
        CreateFileA("config.dat", 0x80000000, 0, (LPSECURITY_ATTRIBUTES)0x0, 3, 0x80, (HANDLE)0x0);
    bVar1 = local_8 != (HANDLE)0xffffffff;
    if (bVar1)
    {
        ReadFile(local_8, param_1, 4, &local_c, (LPOVERLAPPED)0x0);
        ReadFile(local_8, (LPVOID)((int)param_1 + 0x5600), 0xd0, &local_c, (LPOVERLAPPED)0x0);
        ReadFile(local_8, (LPVOID)((int)param_1 + 0x54cc), 1, &local_c, (LPOVERLAPPED)0x0);
        ReadFile(local_8, (LPVOID)((int)param_1 + 0x54ca), 1, &local_c, (LPOVERLAPPED)0x0);
        ReadFile(local_8, (LPVOID)((int)param_1 + 0x54cb), 1, &local_c, (LPOVERLAPPED)0x0);
        ReadFile(local_8, (LPVOID)((int)param_1 + 0x54cd), 1, &local_c, (LPOVERLAPPED)0x0);
        ReadFile(local_8, (LPVOID)((int)param_1 + 0x5598), 9, &local_c, (LPOVERLAPPED)0x0);
        ReadFile(local_8, (LPVOID)((int)param_1 + 0x55a1), 4, &local_c, (LPOVERLAPPED)0x0);
        ReadFile(local_8, (LPVOID)((int)param_1 + 0x54d0), 4, &local_c, (LPOVERLAPPED)0x0);
        ReadFile(local_8, (LPVOID)((int)param_1 + 0x54d4), 4, &local_c, (LPOVERLAPPED)0x0);
        ReadFile(local_8, (LPVOID)((int)param_1 + 0x54dc), 4, &local_c, (LPOVERLAPPED)0x0);
        ReadFile(local_8, (LPVOID)((int)param_1 + 0x54d8), 4, &local_c, (LPOVERLAPPED)0x0);
        ReadFile(local_8, (LPVOID)((int)param_1 + 0x55a5), 1, &local_c, (LPOVERLAPPED)0x0);
        ReadFile(local_8, (LPVOID)((int)param_1 + 0x55a6), 2, &local_c, (LPOVERLAPPED)0x0);
        ReadFile(local_8, (LPVOID)((int)param_1 + 0x55a8), 1, &local_c, (LPOVERLAPPED)0x0);
        ReadFile(local_8, (LPVOID)((int)param_1 + 0x54e4), 4, &local_c, (LPOVERLAPPED)0x0);
        CloseHandle(local_8);
    }
    return bVar1;
}
