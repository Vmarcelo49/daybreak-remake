// ============================================
// Address:  0x0065cb60
// Original: FUN_0065cb60
// Status:   unreviewed
// ============================================

void *__thiscall FUN_0065cb60(void *param_1, uint param_2)

{
    FUN_0065cb40();
    if ((param_2 & 1) != 0)
    {
        _free(param_1);
    }
    return param_1;
}
