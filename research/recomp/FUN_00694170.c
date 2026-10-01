// ============================================
// Address:  0x00694170
// Original: FUN_00694170
// Status:   unreviewed
// ============================================

void __thiscall FUN_00694170(int *param_1, void *param_2)

{
    if (param_1[1] < *param_1)
    {
        FUN_006940b0(param_1[2]);
        param_1[2] = (int)param_2;
        param_1[1] = param_1[1] + 1;
    }
    else
    {
        _free(param_2);
    }
    return;
}
