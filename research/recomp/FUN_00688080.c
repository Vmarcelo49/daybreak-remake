// ============================================
// Address:  0x00688080
// Original: FUN_00688080
// Status:   unreviewed
// ============================================

uint FUN_00688080(int param_1, int *param_2)

{
    uint uVar1;
    void *pvVar2;
    int local_1c;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8   = 0xffffffff;
    puStack_c = &LAB_0069f4c5;
    local_10  = ExceptionList;
    if (param_2 == (int *)0x0)
    {
        uVar1 = 0x80004003;
    }
    else
    {
        ExceptionList = &local_10;
        pvVar2        = operator_new(0x30);
        local_8       = 0;
        if (pvVar2 == (void *)0x0)
        {
            local_1c = 0;
        }
        else
        {
            local_1c = FUN_00688650(param_1 + -0xc, 0);
        }
        *param_2 = local_1c;
        uVar1    = (*param_2 != 0) - 1 & 0x8007000e;
    }
    ExceptionList = local_10;
    return uVar1;
}
