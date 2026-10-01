// ============================================
// Address:  0x00424020
// Original: FUN_00424020
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_00424020(int param_1, undefined1 *param_2)

{
    *param_2   = 0x21;
    param_2[1] = *(undefined1 *)(param_1 + 8);
    param_2[2] = *(undefined1 *)(param_1 + 0xc);
    return 3;
}
