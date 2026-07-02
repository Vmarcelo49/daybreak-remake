// ============================================
// Address:  0x0041dc80
// Original: FUN_0041dc80
// Status:   unreviewed
// ============================================

undefined4 __thiscall
FUN_0041dc80(int param_1, undefined4 param_2, undefined4 param_3, undefined1 param_4)

{
    *(undefined4 *)(param_1 + 8)     = param_2;
    *(undefined1 *)(param_1 + 0x318) = param_4;
    FUN_0041efa0(param_3);
    return 1;
}
