// ============================================
// Address:  0x0068b210
// Original: FUN_0068b210
// Status:   unreviewed
// ============================================

undefined4 FUN_0068b210(int param_1, int param_2)

{
    if (param_2 == 0)
    {
        *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & 0xfffffffb;
    }
    else
    {
        *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | 4;
    }
    return 0;
}
