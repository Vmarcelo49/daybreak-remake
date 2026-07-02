// ============================================
// Address:  0x00662ed0
// Original: FUN_00662ed0
// Status:   unreviewed
// ============================================

bool FUN_00662ed0(LPCSTR param_1)

{
    DWORD DVar1;
    bool bVar2;
    undefined4 uVar3;
    undefined1 local_11c[276];
    HANDLE local_8;

    local_8 = CreateFileA(param_1, 0x80000000, 0, (LPSECURITY_ATTRIBUTES)0x0, 3, 0x80, (HANDLE)0x0);
    bVar2   = local_8 != (HANDLE)0xffffffff;
    if (bVar2)
    {
        uVar3 = 0;
        DVar1 = GetFileSize(local_8, (LPDWORD)0x0);
        uVar3 = FUN_006631b0(param_1, DVar1, uVar3);
        FUN_00663270(local_11c, uVar3);
        DVar1 = GetFileSize(local_8, (LPDWORD)0x0);
        _printf("add package %s / %d \n", param_1, DVar1);
        CloseHandle(local_8);
    }
    return bVar2;
}
