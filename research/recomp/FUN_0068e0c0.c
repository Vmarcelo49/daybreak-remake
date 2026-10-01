// ============================================
// Address:  0x0068e0c0
// Original: FUN_0068e0c0
// Status:   unreviewed
// ============================================

bool FUN_0068e0c0(undefined4 *param_1, undefined4 *param_2)

{
    bool bVar1;
    int *local_c;
    int *local_8;

    if (param_1 == param_2)
    {
        bVar1 = true;
    }
    else
    {
        (**(code **)*param_1)(param_1, &DAT_006ad9a8, &local_c);
        (**(code **)*param_2)(param_2, &DAT_006ad9a8, &local_8);
        (**(code **)(*local_c + 8))(local_c);
        (**(code **)(*local_8 + 8))(local_8);
        bVar1 = local_c == local_8;
    }
    return bVar1;
}
