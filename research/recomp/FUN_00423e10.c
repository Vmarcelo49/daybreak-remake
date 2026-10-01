// ============================================
// Address:  0x00423e10
// Original: FUN_00423e10
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_00423e10(int param_1, undefined1 *param_2)

{
    *param_2                     = 0xe;
    param_2[1]                   = *(undefined1 *)(param_1 + 8);
    param_2[2]                   = *(undefined1 *)(param_1 + 9);
    param_2[3]                   = *(undefined1 *)(param_1 + 10);
    *(undefined2 *)(param_2 + 4) = *(undefined2 *)(param_1 + 0xc);
    param_2[6]                   = *(undefined1 *)(param_1 + 0xe);
    return 7;
}
