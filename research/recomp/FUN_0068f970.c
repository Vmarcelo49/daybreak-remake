// ============================================
// Address:  0x0068f970
// Original: FUN_0068f970
// Status:   unreviewed
// ============================================

void __fastcall FUN_0068f970(int *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f9b4;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068d950(param_1 + 0x25);
    local_8 = 0;
    if (param_1[0x30] != 0)
    {
        param_1[0x30] = 0;
        (**(code **)(*param_1 + 0x60))();
    }
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    ExceptionList = local_10;
    return;
}
