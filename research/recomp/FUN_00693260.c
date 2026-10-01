// ============================================
// Address:  0x00693260
// Original: FUN_00693260
// Status:   unreviewed
// ============================================

int *FUN_00693260(int *param_1, int *param_2)

{
    if (param_2 != (int *)0x0)
    {
        (**(code **)(*param_2 + 4))(param_2);
    }
    if (*param_1 != 0)
    {
        (**(code **)(*(int *)*param_1 + 8))(*param_1);
    }
    *param_1 = (int)param_2;
    return param_2;
}
