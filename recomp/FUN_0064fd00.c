// ============================================
// Address:  0x0064fd00
// Original: FUN_0064fd00
// Status:   unreviewed
// ============================================

void FUN_0064fd00(void *param_1, int param_2, int param_3)

{
    int iVar1;

    iVar1 = param_2 - (int)param_1 >> 2;
    _memmove((void *)(param_3 + iVar1 * -4), param_1, iVar1 << 2);
    return;
}
