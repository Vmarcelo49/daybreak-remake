// ============================================
// Address:  0x0068fd50
// Original: FUN_0068fd50
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_0068fd50(int *param_1)

{
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069f9ea;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_0068d950(param_1 + 0x25);
    local_8       = 0;
    param_1[0x1d] = 0;
    if (param_1[0x19] == 1)
    {
        param_1[0x19] = 0;
        (**(code **)(*param_1 + 0x44))();
        timeEndPeriod(1);
    }
    local_8 = 0xffffffff;
    FUN_0068d9a0();
    ExceptionList = local_10;
    return 0;
}
