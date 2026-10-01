// ============================================
// Address:  0x00423c30
// Original: FUN_00423c30
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_00423c30(int param_1, undefined1 *param_2)

{
    *param_2                     = 0x28;
    param_2[1]                   = *(undefined1 *)(param_1 + 8);
    *(undefined4 *)(param_2 + 2) = *(undefined4 *)(param_1 + 0xc);
    return 6;
}
