// ============================================
// Address:  0x0042f920
// Original: FUN_0042f920
// Status:   unreviewed
// ============================================

void *__thiscall FUN_0042f920(void *param_1, uint param_2)

{
    FUN_0042f900();
    if ((param_2 & 1) != 0)
    {
        _free(param_1);
    }
    return param_1;
}
