// ============================================
// Address:  0x00431a50
// Original: FUN_00431a50
// Status:   unreviewed
// ============================================

void __thiscall FUN_00431a50(float *param_1,
                             undefined4 param_2,
                             int param_3,
                             int param_4,
                             int param_5,
                             int param_6,
                             int param_7,
                             float param_8)

{
    int local_18;

    param_5    = param_5 - param_3;
    param_6    = param_6 - param_4;
    *param_1   = (float)param_5;
    param_1[1] = param_8;
    for (local_18 = 0; local_18 < 0xc; local_18 = local_18 + 1)
    {
        FUN_00655af0(param_2,
                     param_3 + (local_18 % param_7) * param_5,
                     param_4 + (local_18 / param_7) * param_6,
                     param_5,
                     param_6);
    }
    FUN_00655690(param_2, param_3, param_4, param_5, param_6);
    return;
}
