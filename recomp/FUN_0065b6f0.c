// ============================================
// Address:  0x0065b6f0
// Original: FUN_0065b6f0
// Status:   unreviewed
// ============================================

void __fastcall FUN_0065b6f0(int *param_1)

{
    DWORD local_8;

    FUN_0065b9b0();
    if (param_1[1] != 0)
    {
        FUN_0065d670();
        *(undefined1 *)(param_1 + 0x4d3)       = 0;
        *(undefined1 *)((int)param_1 + 0x134d) = 0;
        FUN_0065d6a0();
        FUN_00667f20();
        local_8 = 0x103;
        while (local_8 == 0x103)
        {
            GetExitCodeThread((HANDLE)param_1[1], &local_8);
        }
        CloseHandle((HANDLE)param_1[1]);
        param_1[1] = 0;
    }
    FUN_006679f0();
    FUN_00668070();
    if (*param_1 != 0)
    {
        CloseHandle((HANDLE)*param_1);
        *param_1 = 0;
    }
    return;
}
