// ============================================
// Address:  0x00699ce0
// Original: FUN_00699ce0
// Status:   unreviewed
// ============================================

void __fastcall FUN_00699ce0(int param_1)

{
    int iVar1;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_006a00d7;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    while (true)
    {
        FUN_0068d950(param_1 + 0x1c);
        local_8 = 0;
        iVar1   = FUN_00699ad0();
        if (iVar1 == 0)
            break;
        *(int *)(param_1 + 0x70) = *(int *)(param_1 + 0x70) + 1;
        local_8                  = 0xffffffff;
        FUN_0068d9a0();
        FUN_00699180();
        FUN_0068d950(param_1 + 0x1c);
        local_8 = 1;
        FUN_00699ca0(iVar1);
        *(int *)(param_1 + 0x70) = *(int *)(param_1 + 0x70) + -1;
        if ((*(int *)(param_1 + 0x70) == 0) && (*(int *)(param_1 + 0x74) != 0))
        {
            FUN_006919a0();
        }
        local_8 = 0xffffffff;
        FUN_0068d9a0();
    }
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    ExceptionList = local_10;
    return;
}
