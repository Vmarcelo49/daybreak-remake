// ============================================
// Address:  0x005f77d0
// Original: FUN_005f77d0
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_005f77d0(int param_1, undefined1 *param_2)

{
    *param_2                     = 0x3a;
    param_2[1]                   = *(undefined1 *)(param_1 + 8);
    *(undefined4 *)(param_2 + 2) = *(undefined4 *)(param_1 + 0xc);
    return 6;
}
