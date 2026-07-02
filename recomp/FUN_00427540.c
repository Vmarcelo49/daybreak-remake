// ============================================
// Address:  0x00427540
// Original: FUN_00427540
// Status:   unreviewed
// ============================================

undefined4 *FUN_00427540(undefined4 *param_1, undefined4 *param_2, undefined4 *param_3)

{
    while (param_1 != param_2)
    {
        param_3[-3] = param_2[-3];
        param_3[-2] = param_2[-2];
        param_3[-1] = param_2[-1];
        param_2     = param_2 + -3;
        param_3     = param_3 + -3;
    }
    return param_3;
}
