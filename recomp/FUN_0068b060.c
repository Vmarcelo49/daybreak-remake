// ============================================
// Address:  0x0068b060
// Original: FUN_0068b060
// Status:   unreviewed
// ============================================

undefined4 FUN_0068b060(int param_1, undefined4 *param_2, undefined4 *param_3)

{
    if (param_2 == (undefined4 *)0x0)
    {
        *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & 0xfffffeef;
    }
    else if (param_3 == (undefined4 *)0x0)
    {
        *(undefined4 *)(param_1 + 0x20) = *param_2;
        *(undefined4 *)(param_1 + 0x24) = param_2[1];
        *(uint *)(param_1 + 4)          = *(uint *)(param_1 + 4) | 0x10;
        *(uint *)(param_1 + 4)          = *(uint *)(param_1 + 4) & 0xfffffeff;
    }
    else
    {
        *(undefined4 *)(param_1 + 0x20) = *param_2;
        *(undefined4 *)(param_1 + 0x24) = param_2[1];
        *(undefined4 *)(param_1 + 0x28) = *param_3;
        *(undefined4 *)(param_1 + 0x2c) = param_3[1];
        *(uint *)(param_1 + 4)          = *(uint *)(param_1 + 4) | 0x110;
    }
    return 0;
}
