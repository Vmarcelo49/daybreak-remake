// ============================================
// Address:  0x0040fa60
// Original: FUN_0040fa60
// Status:   unreviewed
// ============================================

void *__thiscall FUN_0040fa60(void *param_1, uint param_2)

{
    FUN_0040e9c0();
    if ((param_2 & 1) != 0)
    {
        _free(param_1);
    }
    return param_1;
}
