// ============================================
// Address:  0x004039f0
// Original: FUN_004039f0
// Status:   unreviewed
// ============================================

void *__thiscall FUN_004039f0(void *param_1, uint param_2)

{
    FUN_004039d0();
    if ((param_2 & 1) != 0)
    {
        _free(param_1);
    }
    return param_1;
}
