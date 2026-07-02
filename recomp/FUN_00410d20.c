// ============================================
// Address:  0x00410d20
// Original: FUN_00410d20
// Status:   unreviewed
// ============================================

void *FUN_00410d20(void *param_1, int param_2, void *param_3)

{
    int iVar1;
    void *pvVar2;

    iVar1  = param_2 - (int)param_1 >> 2;
    pvVar2 = _memmove(param_3, param_1, iVar1 << 2);
    return (void *)((int)pvVar2 + iVar1 * 4);
}
