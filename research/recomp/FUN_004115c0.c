// ============================================
// Address:  0x004115c0
// Original: FUN_004115c0
// Status:   unreviewed
// ============================================

void *__thiscall FUN_004115c0(void *param_1, uint param_2)

{
    FUN_00410ed0();
    if ((param_2 & 1) != 0)
    {
        _free(param_1);
    }
    return param_1;
}
