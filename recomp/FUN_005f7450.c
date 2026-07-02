// ============================================
// Address:  0x005f7450
// Original: FUN_005f7450
// Status:   unreviewed
// ============================================

void __thiscall FUN_005f7450(int param_1,
                             int param_2,
                             undefined4 param_3,
                             undefined4 param_4,
                             undefined4 param_5,
                             undefined1 param_6)

{
    void *pvVar1;
    undefined4 local_2c;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069e64b;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    if (*(int *)(param_1 + 0x13c) != 0)
    {
        ExceptionList = &local_10;
        if (*(int *)(param_1 + 0x13c) != 0)
        {
            ExceptionList = &local_10;
            FUN_005f7700(1);
        }
        *(undefined4 *)(param_1 + 0x13c) = 0;
    }
    pvVar1  = operator_new(0x38);
    local_8 = 0;
    if (pvVar1 == (void *)0x0)
    {
        local_2c = 0;
    }
    else
    {
        local_2c = FUN_004366b0();
    }
    local_8                          = 0xffffffff;
    *(undefined4 *)(param_1 + 0x13c) = local_2c;
    FUN_00436790(*(undefined4 *)(&DAT_006cf448 + param_2 * 4),
                 param_1 + 0x14,
                 param_3,
                 param_4,
                 param_5,
                 param_6);
    ExceptionList = local_10;
    return;
}
