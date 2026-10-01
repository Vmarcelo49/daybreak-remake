// ============================================
// Address:  0x00423f50
// Original: FUN_00423f50
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_00423f50(int param_1, undefined1 *param_2)

{
    *param_2   = 0x20;
    param_2[1] = *(undefined1 *)(param_1 + 8);
    param_2[2] = *(undefined1 *)(param_1 + 0xc);
    param_2[3] = *(undefined1 *)(param_1 + 0x10);
    return 4;
}
