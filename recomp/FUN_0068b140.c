// ============================================
// Address:  0x0068b140
// Original: FUN_0068b140
// Status:   unreviewed
// ============================================

undefined4 FUN_0068b140(int param_1, int *param_2, int *param_3)

{
    if (param_2 == (int *)0x0)
    {
        *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & 0xffffffdf;
    }
    else
    {
        *(int *)(param_1 + 0x30) = *param_2;
        *(int *)(param_1 + 0x34) = param_2[1];
        *(int *)(param_1 + 0x38) = *param_3 - *param_2;
        *(uint *)(param_1 + 4)   = *(uint *)(param_1 + 4) | 0x20;
    }
    return 0;
}
