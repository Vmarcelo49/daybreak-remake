// ============================================
// Address:  0x00679b40
// Original: FUN_00679b40
// Status:   unreviewed
// ============================================

undefined4 FUN_00679b40(int param_1, int param_2)

{
    if (*(int *)(param_1 + 0x1c) != 0)
    {
        return *(undefined4 *)(*(int *)(param_1 + 0x1c) + param_2 * 4);
    }
    return 0xffffffff;
}
