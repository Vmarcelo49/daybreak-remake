// ============================================
// Address:  0x00691910
// Original: FUN_00691910
// Status:   unreviewed
// ============================================

void FUN_00691910(undefined4 *param_1, int param_2, undefined4 param_3)

{
    int *local_8;

    if ((param_2 == 0) && (param_1[0xd] != 0))
    {
        (**(code **)*param_1)(param_1, &LAB_006ad051_3, &local_8);
        FUN_006883f0(0x15, local_8, 0);
        (**(code **)(*local_8 + 8))(local_8);
    }
    FUN_006882b0(param_1, param_2, param_3);
    return;
}
