// ============================================
// Address:  0x0068a9c0
// Original: FUN_0068a9c0
// Status:   unreviewed
// ============================================

int FUN_0068a9c0(int *param_1, int param_2, int param_3, int *param_4)

{
    int local_8;

    if (param_2 == 0)
    {
        local_8 = -0x7fffbffd;
    }
    else
    {
        local_8  = 0;
        *param_4 = 0;
        while ((0 < param_3 && (local_8 = (**(code **)(*param_1 + 0x18))(
                                    param_1, *(undefined4 *)(param_2 + *param_4 * 4)),
                                local_8 == 0)))
        {
            *param_4 = *param_4 + 1;
            param_3  = param_3 + -1;
        }
    }
    return local_8;
}
