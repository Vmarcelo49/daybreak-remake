// ============================================
// Address:  0x00419190
// Original: FUN_00419190
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_00419190(int param_1, undefined1 *param_2)

{
    *param_2                     = 0x14;
    param_2[1]                   = *(undefined1 *)(param_1 + 0x10);
    *(undefined4 *)(param_2 + 2) = *(undefined4 *)(param_1 + 8);
    *(undefined4 *)(param_2 + 6) = *(undefined4 *)(param_1 + 0xc);
    return 10;
}
