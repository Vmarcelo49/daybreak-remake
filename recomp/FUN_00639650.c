// ============================================
// Address:  0x00639650
// Original: FUN_00639650
// Status:   unreviewed
// ============================================

void __thiscall FUN_00639650(int param_1, int param_2, int param_3)

{
    *(int *)(param_1 + 0x12b0 + param_2 * 0xc) =
        *(int *)(param_1 + 0x12b0 + param_2 * 0xc) + param_3;
    FUN_006431d0(*(undefined1 *)(param_1 + 0x12ac + param_2 * 0xc), param_3);
    if (DAT_006cfdb0 == '\x01')
    {
        *(undefined2 *)(param_1 + 0x7cc) = *(undefined2 *)(param_1 + 0x12b0);
        *(undefined2 *)(param_1 + 0x7ce) = *(undefined2 *)(param_1 + 0x12bc);
        FUN_00415d30(0, param_1 + 0x7c4, 0, 8);
    }
    return;
}
