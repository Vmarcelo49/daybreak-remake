// ============================================
// Address:  0x00699950
// Original: FUN_00699950
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_00699950(int param_1)

{
    int iVar1;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_006a0087;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068d950(param_1 + 0x1c);
    local_8                         = 0;
    *(undefined4 *)(param_1 + 0x34) = 0;
    iVar1                           = FUN_00699fc0();
    if (iVar1 < 1)
    {
        FUN_006919c0();
    }
    else
    {
        FUN_006919a0();
    }
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    ExceptionList = local_10;
    return 0;
}
