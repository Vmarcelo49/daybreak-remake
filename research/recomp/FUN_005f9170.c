// ============================================
// Address:  0x005f9170
// Original: FUN_005f9170
// Status:   unreviewed
// ============================================

void *__thiscall FUN_005f9170(void *param_1, uint param_2)

{
    FUN_005f91a0();
    if ((param_2 & 1) != 0)
    {
        _free(param_1);
    }
    return param_1;
}
