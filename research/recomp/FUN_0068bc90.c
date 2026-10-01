// ============================================
// Address:  0x0068bc90
// Original: FUN_0068bc90
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_0068bc90(int param_1)

{
    undefined4 uVar1;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f696;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068d950(param_1 + 0xa4);
    local_8 = 0;
    if (*(int *)(param_1 + 0xc4) == 0)
    {
        local_8 = 0xffffffff;
        FUN_0068d9a0();
        uVar1 = 1;
    }
    else
    {
        SetEvent(*(HANDLE *)(param_1 + 0xbc));
        if (*(int *)(param_1 + 0xc0) != 0)
        {
            SetEvent(*(HANDLE *)(param_1 + 0xc0));
            CloseHandle(*(HANDLE *)(param_1 + 0xc0));
        }
        *(undefined4 *)(param_1 + 0xc4) = 0;
        *(undefined4 *)(param_1 + 200)  = 0;
        *(undefined4 *)(param_1 + 0xc0) = 0;
        local_8                         = 0xffffffff;
        FUN_0068d9a0();
        uVar1 = 0;
    }
    ExceptionList = local_10;
    return uVar1;
}
