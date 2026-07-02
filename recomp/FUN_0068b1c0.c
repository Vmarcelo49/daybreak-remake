// ============================================
// Address:  0x0068b1c0
// Original: FUN_0068b1c0
// Status:   unreviewed
// ============================================

undefined4 FUN_0068b1c0(int param_1, int param_2)

{
    if (param_2 == 0)
    {
        *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & 0xfffffffe;
    }
    else
    {
        *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 1;
    }
    return 0;
}
