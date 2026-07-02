// ============================================
// Address:  0x00693f30
// Original: FUN_00693f30
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_00693f30(undefined4 *param_1, int param_2, int *param_3)

{
    undefined4 uVar1;
    int local_c;
    int local_8;

    if (param_2 != 0)
    {
        local_8 = param_2;
        local_c = 0;
        while (local_8 != 0)
        {
            local_8 = FUN_0068dc80();
            local_c = local_c + 1;
        }
        if (*param_3 != 0)
        {
            FUN_00687260(param_1[1]);
        }
        if (param_1[1] != 0)
        {
            FUN_006940b0(*param_3);
        }
        if (param_3[1] == 0)
        {
            param_3[1] = param_1[1];
        }
        uVar1      = FUN_0068de10();
        param_1[1] = uVar1;
        if (param_1[1] == 0)
        {
            *param_1 = 0;
        }
        *param_3 = param_2;
        if (param_1[1] != 0)
        {
            FUN_006940b0(0);
        }
        FUN_00687260(0);
        param_1[2] = param_1[2] - local_c;
        param_3[2] = param_3[2] + local_c;
    }
    return 1;
}
