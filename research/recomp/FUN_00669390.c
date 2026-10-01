// ============================================
// Address:  0x00669390
// Original: FUN_00669390
// Status:   unreviewed
// ============================================

void *__thiscall FUN_00669390(void *param_1, uint param_2)

{
    FUN_00668b30();
    if ((param_2 & 1) != 0)
    {
        _free(param_1);
    }
    return param_1;
}
