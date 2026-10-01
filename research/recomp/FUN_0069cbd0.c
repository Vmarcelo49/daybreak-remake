// ============================================
// Address:  0x0069cbd0
// Original: FUN_0069cbd0
// Status:   unreviewed
// ============================================

undefined4 FUN_0069cbd0(undefined4 *param_1)

{
    int iVar1;

    if (param_1 != (undefined4 *)0x0)
    {
        if ((void *)*param_1 != (void *)0x0)
        {
            _free((void *)*param_1);
        }
        if ((void *)param_1[4] != (void *)0x0)
        {
            _free((void *)param_1[4]);
        }
        if ((void *)param_1[5] != (void *)0x0)
        {
            _free((void *)param_1[5]);
        }
        for (iVar1 = 0x5a; iVar1 != 0; iVar1 = iVar1 + -1)
        {
            *param_1 = 0;
            param_1  = param_1 + 1;
        }
    }
    return 0;
}
