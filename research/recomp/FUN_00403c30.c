// ============================================
// Address:  0x00403c30
// Original: FUN_00403c30
// Status:   unreviewed
// ============================================

void *__thiscall FUN_00403c30(void *param_1, uint param_2)

{
    FUN_00403b00();
    if ((param_2 & 1) != 0)
    {
        _free(param_1);
    }
    return param_1;
}
