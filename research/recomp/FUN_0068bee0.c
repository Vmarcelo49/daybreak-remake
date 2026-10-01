// ============================================
// Address:  0x0068bee0
// Original: FUN_0068bee0
// Status:   unreviewed
// ============================================

void __fastcall FUN_0068bee0(int param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f6ba;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068d950(param_1 + 0xa4);
    local_8                  = 0;
    *(int *)(param_1 + 0xcc) = *(int *)(param_1 + 0xcc) + -1;
    if ((*(int *)(param_1 + 0xcc) == 0) && (*(int *)(param_1 + 0xc4) != 0))
    {
        FUN_0068bc30();
    }
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    ExceptionList = local_10;
    return;
}
