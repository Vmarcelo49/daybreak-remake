// ============================================
// Address:  0x00696020
// Original: FUN_00696020
// Status:   unreviewed
// ============================================

undefined4 FUN_00696020(int param_1, double *param_2)

{
    undefined4 uVar1;
    float10 fVar2;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8   = 0xffffffff;
    puStack_c = &LAB_0069fcf1;
    local_10  = ExceptionList;
    if (param_2 == (double *)0x0)
    {
        uVar1 = 0x80004003;
    }
    else
    {
        ExceptionList = &local_10;
        FUN_0068d950(*(undefined4 *)(param_1 + 0x38));
        local_8  = 0;
        fVar2    = (float10)FUN_00697f40();
        *param_2 = (double)fVar2;
        local_8  = 0xffffffff;
        FUN_0068d9a0();
        uVar1 = 0;
    }
    ExceptionList = local_10;
    return uVar1;
}
