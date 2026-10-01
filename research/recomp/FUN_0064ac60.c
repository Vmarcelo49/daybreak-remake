// ============================================
// Address:  0x0064ac60
// Original: FUN_0064ac60
// Status:   unreviewed
// ============================================

void __thiscall FUN_0064ac60(int param_1, undefined4 param_2)

{
    void *pvVar1;
    undefined4 local_2c;
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069eb07;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    if (*(int *)(param_1 + 0x52d0) != 0)
    {
        ExceptionList = &local_10;
        if (*(int *)(param_1 + 0x52d0) != 0)
        {
            ExceptionList = &local_10;
            FUN_0064c7f0(1);
        }
        *(undefined4 *)(param_1 + 0x52d0) = 0;
    }
    pvVar1  = operator_new(0xbc);
    local_8 = 0;
    if (pvVar1 == (void *)0x0)
    {
        local_2c = 0;
    }
    else
    {
        local_2c = FUN_00401030();
    }
    local_8                           = 0xffffffff;
    *(undefined4 *)(param_1 + 0x52d0) = local_2c;
    if (*(char *)(param_1 + 0x54ca) == '\0')
    {
        FUN_0064cea0();
    }
    else
    {
        FUN_0064ce80();
    }
    FUN_0064cec0();
    FUN_004011f0(param_2);
    ExceptionList = local_10;
    return;
}
