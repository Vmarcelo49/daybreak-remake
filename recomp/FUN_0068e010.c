// ============================================
// Address:  0x0068e010
// Original: FUN_0068e010
// Status:   unreviewed
// ============================================

/* WARNING: Type propagation algorithm not settling */

undefined4 FUN_0068e010(int *param_1)

{
    undefined4 uVar1;
    int local_18[2];
    int *local_10;
    int *local_c;
    LONG local_8;

    local_8 = InterlockedDecrement(param_1 + 2);
    if (local_8 == 0)
    {
        param_1[2] = param_1[2] + 1;
        local_10   = param_1;
        local_c    = param_1;
        if (param_1 != (int *)0x0)
        {
            (**(code **)(*param_1 + 0xc))(1);
        }
        uVar1 = 0;
    }
    else
    {
        local_18[1] = 1;
        local_18[0] = param_1[2];
        uVar1       = FUN_0068e130(local_18, local_18 + 1);
    }
    return uVar1;
}
