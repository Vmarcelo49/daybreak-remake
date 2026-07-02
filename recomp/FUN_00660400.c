// ============================================
// Address:  0x00660400
// Original: FUN_00660400
// Status:   unreviewed
// ============================================

void __thiscall FUN_00660400(undefined4 *param_1,
                             int param_2,
                             undefined4 param_3,
                             undefined4 param_4,
                             undefined4 param_5,
                             uint param_6)

{
    undefined4 local_10;
    undefined4 local_c;
    undefined4 local_8;

    if (param_2 == 0)
    {
        FUN_006603b0(param_3, param_4, param_5, param_6);
    }
    else if (param_1[param_2 + 10] != 0)
    {
        local_c  = param_3;
        local_10 = param_4;
        local_8  = 0;
        (**(code **)(*(int *)*param_1 + 0x38))(
            *param_1, param_1[param_2 + 2], &local_10, 1, param_5, 0, &local_8, param_6 | 0x20);
    }
    return;
}
