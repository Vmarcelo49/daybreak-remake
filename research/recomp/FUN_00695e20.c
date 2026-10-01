// ============================================
// Address:  0x00695e20
// Original: FUN_00695e20
// Status:   unreviewed
// ============================================

undefined4 FUN_00695e20(int param_1, undefined4 *param_2, undefined8 *param_3)

{
    undefined8 uVar1;
    undefined4 extraout_var;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069fccd;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    if (param_2 != (undefined4 *)0x0)
    {
        ExceptionList = &local_10;
        *param_2      = 0;
        param_2[1]    = 0;
    }
    if (param_3 != (undefined8 *)0x0)
    {
        FUN_0068d950(*(undefined4 *)(param_1 + 0x34));
        local_8  = 0;
        uVar1    = FUN_00697fc0(extraout_var);
        *param_3 = uVar1;
        local_8  = 0xffffffff;
        FUN_0068d9a0();
    }
    ExceptionList = local_10;
    return 0;
}
