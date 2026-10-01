// ============================================
// Address:  0x00405790
// Original: FUN_00405790
// Status:   unreviewed
// ============================================

void *__thiscall FUN_00405790(void *param_1, uint param_2)

{
    FUN_004055f0();
    if ((param_2 & 1) != 0)
    {
        _free(param_1);
    }
    return param_1;
}
